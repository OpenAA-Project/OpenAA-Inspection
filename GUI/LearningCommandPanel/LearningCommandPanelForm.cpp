/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "LearningCommandPanelForm.h"
#include "ui_LearningCommandPanelForm.h"
#include "XLearningRegist.h"
#include "XLearningServerComm.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithmList.h"
#include <QBuffer>

LearningCommandPanelForm::LearningCommandPanelForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::LearningCommandPanelForm)
{
    ui->setupUi(this);

    ServerIP    =/**/"localhost";
    Sock        =NULL;
    ReflectAfterMasterLoad  =false;
    ModeShowExecuteButton   =true;
    ModeShowReflectButton   =true;

	GetParamGUI()->SetParam(&ReflectAfterMasterLoad, /**/"LearningCommandPanel",/**/"ReflectAfterMasterLoad"	
												,QString("マスターデータ読込後の学習サーバーからの反映")	);
	GetParamGUI()->SetParam(&ModeShowExecuteButton, /**/"LearningCommandPanel",/**/"ModeShowExecuteButton"	
												,QString("実行ボタン表示モード")	);
	GetParamGUI()->SetParam(&ModeShowReflectButton, /**/"LearningCommandPanel",/**/"ModeShowReflectButton"	
												,QString("反映ボタンの表示モード")	);
}

LearningCommandPanelForm::~LearningCommandPanelForm()
{
    delete ui;
    if(Sock!=NULL){
        Sock->deleteLater();
        Sock=NULL;
    }
}
void	LearningCommandPanelForm::Prepare(void)
{
    if(ModeShowExecuteButton==false){
        ui->pushButtonReqExecute->setVisible(false);
    }
    if(ModeShowReflectButton==false){
        ui->pushButtonReflectFromServer->setVisible(false);
    }
}
void	LearningCommandPanelForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
    LoadMasterSpecifiedBroadcaster  *LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
    if(LoadMasterSpecifiedBroadcasterVar!=NULL){
        if(ReflectAfterMasterLoad==true){
            on_pushButtonReflectFromServer_clicked();
        }
        return;
    }
}
void LearningCommandPanelForm::on_pushButtonReqExecute_clicked()
{
    if(ConnectToServer()==true){
        LibInfoListContainer    Container;
        GetLayersBase()->GatherUsedLibInfoList(Container);

        QBuffer Buff;
        Buff.open(QIODevice::ReadWrite);

        int32   Cmd=CmdLearningExecute;
        if(Buff.write((const char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd)){
            return;
        }
        Container.Save(&Buff);
        QByteArray  Data=Buff.buffer();

        if(Sock->write(Data)!=Data.size()){
            return;
        }
        Sock->flush();
    }
}


void LearningCommandPanelForm::on_pushButtonReflectFromServer_clicked()
{
    if(ConnectToServer()==true){
        LibInfoListContainer    Container;
        GetLayersBase()->GatherUsedLibInfoList(Container);

        QBuffer Buff;
        Buff.open(QIODevice::ReadWrite);

        int32   Cmd=CmdLearningReqThreshold;
        if(Buff.write((const char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd)){
            return;
        }
        Container.Save(&Buff);
        QByteArray  Data=Buff.buffer();

        if(Sock->write(Data)!=Data.size()){
            return;
        }
        Sock->flush();

        Sock->waitForReadyRead();
    }
}

bool    LearningCommandPanelForm::ConnectToServer(void)
{
    if(Sock==NULL){
        Sock=new QTcpSocket(this);
        Sock->connectToHost(ServerIP,LearningServerPort);
        Sock->waitForConnected(3000);
        connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyReadFromServer()));
    }
    if(Sock->state()==QAbstractSocket::ConnectedState){
        return true;
    }
    return false;
}

static  bool Func(void *caller,AlgorithmItemRoot *item)
{
    int LibID=*((int *)caller);
    if(item->GetLibID()==LibID){
        return true;
    }
    return false;
}

void    LearningCommandPanelForm::SlotReadyReadFromServer()
{
    if(Sock->bytesAvailable()>0){
        QByteArray  Data=Sock->readAll();
        QBuffer Buff(&Data);
        Buff.open(QIODevice::ReadWrite);

        int32   Cmd;
        if(Buff.read((char *)&Cmd,sizeof(Cmd))!=sizeof(Cmd)){
            return;
        }
        if(Cmd==CmdLearningAckThreshold){
            LibDataListContainer    Container;
            if(Container.Load(&Buff)==true){
                for(LibDataList *a=Container.GetFirst();a!=NULL;a=a->GetNext()){
                    GetLayersBase()->SetLibDataList(*a);
                }
            }
        }
    }
}