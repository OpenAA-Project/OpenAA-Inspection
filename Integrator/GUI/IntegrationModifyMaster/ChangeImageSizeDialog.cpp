/*
 * Copyright (C) 2025
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

#include "IntegrationModifyMasterResource.h"
#include "ChangeImageSizeDialog.h"
#include "ui_ChangeImageSizeDialog.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

ChangeImageSizeDialog::ChangeImageSizeDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ChangeImageSizeDialog)
{
    ui->setupUi(this);

    IntegrationBase *IBase=GetLayersBase()->GetIntegrationBasePointer();
    int N=IBase->GetIntegrationSlaveCount();
    if(N>0){
        ui->tableWidget->setColumnCount(N);
        for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
            IntegrationReqXYPixels  RCmd(GetLayersBase(),sRoot,sName ,SlaveNo);
            IntegrationAckXYPixels  ACmd(GetLayersBase(),sRoot,sName ,SlaveNo);
            if(RCmd.Send(SlaveNo,0,ACmd)==true){
                ::SetDataToTable(ui->tableWidget, SlaveNo, 0, QString::number(ACmd.XLen));
                ::SetDataToTable(ui->tableWidget, SlaveNo, 1, QString::number(ACmd.XLen/((double)ACmd.NanoMeterPerDotX/1000000000.0),'f',2)+QString(/**/"mm"));
                ::SetDataToTable(ui->tableWidget, SlaveNo, 2, QString::number(ACmd.XLen),Qt::ItemIsEditable);
                ::SetDataToTable(ui->tableWidget, SlaveNo, 3, QString::number(ACmd.YLen));
                ::SetDataToTable(ui->tableWidget, SlaveNo, 4, QString::number(ACmd.YLen/((double)ACmd.NanoMeterPerDotY/1000000000.0),'f',2)+QString(/**/"mm"));
                ::SetDataToTable(ui->tableWidget, SlaveNo, 5, QString::number(ACmd.XLen),Qt::ItemIsEditable);
            }
        }
    }
}

ChangeImageSizeDialog::~ChangeImageSizeDialog()
{
    delete ui;
}

void ChangeImageSizeDialog::resizeEvent(QResizeEvent *event)
{
    ui->tableWidget->resize(width(),height()-ui->frame->height());
    ui->frame->move(0,height()-ui->frame->height());
}

void ChangeImageSizeDialog::on_pushButtonGo_clicked()
{
    IntegrationBase *IBase=GetLayersBase()->GetIntegrationBasePointer();
    int N=IBase->GetIntegrationSlaveCount();
    if(N>0){
        for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
            QString sx=GetDataToTable(ui->tableWidget, SlaveNo, 2);
            QString sy=GetDataToTable(ui->tableWidget, SlaveNo, 5);
            IntegrationSetXYPixels  RCmd(GetLayersBase(),sRoot,sName ,SlaveNo);
            bool    ok;
            RCmd.XLen   =sx.toInt(&ok);
            if(ok==false)
                continue;
            RCmd.YLen   =sy.toInt(&ok);
            if(ok==false)
                continue;
            RCmd.Send(NULL,SlaveNo,0);
        }
    }
    done(true);
}


void ChangeImageSizeDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


//================================================================================
IntegrationReqXYPixels::IntegrationReqXYPixels(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqXYPixels::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckXYPixels	*SendBack=GetSendBackIntegration(IntegrationAckXYPixels,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	SendBack->XLen  =GetDotPerLine(0);
	SendBack->YLen  =GetMaxLines(0);
    SendBack->NanoMeterPerDotX=GetParamGlobal()->ResolutionXNano;
    SendBack->NanoMeterPerDotY=GetParamGlobal()->ResolutionYNano;

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckXYPixels::IntegrationAckXYPixels(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckXYPixels::Load(QIODevice *f)
{
    if(::Load(f,XLen            )==false)  return false;
    if(::Load(f,YLen            )==false)  return false;
    if(::Load(f,NanoMeterPerDotX)==false)  return false;
    if(::Load(f,NanoMeterPerDotY)==false)  return false;
    return true;
}
bool	IntegrationAckXYPixels::Save(QIODevice *f)
{
    if(::Save(f,XLen            )==false)  return false;
    if(::Save(f,YLen            )==false)  return false;
    if(::Save(f,NanoMeterPerDotX)==false)  return false;
    if(::Save(f,NanoMeterPerDotY)==false)  return false;
    return true;
}

IntegrationSetXYPixels::IntegrationSetXYPixels(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationSetXYPixels::Load(QIODevice *f)
{
    if(::Load(f,XLen            )==false)  return false;
    if(::Load(f,YLen            )==false)  return false;
    return true;
}
bool	IntegrationSetXYPixels::Save(QIODevice *f)
{
    if(::Save(f,XLen            )==false)  return false;
    if(::Save(f,YLen            )==false)  return false;
    return true;
}

void	IntegrationSetXYPixels::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
    GUIFormBase *f=GetLayersBase()->FindByName(/**/"Button",/**/"Change",/**/"");
    if(f!=NULL){
		QStringList Args;

        Args.append(QString::number(GetLayersBase()->GetPhaseNumb()));
        Args.append(QString::number(GetLayersBase()->GetPageNumb()));
        Args.append(QString::number(GetLayersBase()->GetLayerNumb(0)));
        Args.append(QString::number(YLen));
		bool ExeReturn;
		f->ExecuteMacro(/**/"Change", Args, ExeReturn);
    }
}