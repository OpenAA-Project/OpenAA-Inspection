/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\SelectLotForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "CommonGUIDLLResource.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include "SelectLotForm.h"
#include "ui_SelectLotForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "XGUIFormBase.h"
#include "XDateTime.h"
#include "XSyncGUI.h"

SelectLotForm::SelectLotForm(LayersBase *pbase ,QWidget *parent, QWidget *parentGUI ,int MaxLines) :
    QWidget(parent)
    ,ServiceForLayers(pbase)
    ,ui(new Ui::SelectLotForm)
    
{
    ui->setupUi(this);
    LangCGSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangCGSolver.SetUI(this);

    ParentGUI=dynamic_cast<GUIFormBase*>(parentGUI);

    RetMode=false;
    ui->tableWidgetLot->setColumnWidth ( 0, 120);
    ui->tableWidgetLot->setColumnWidth ( 1, 120);
    ui->tableWidgetLot->setColumnWidth ( 2, 80);
    ui->tableWidgetLot->setColumnWidth ( 3, 120);

    QString	SCount=QString(/**/"SELECT count(*) FROM INSPECTIONLOT WHERE MASTERCODE=")
                +QString::number(GetLayersBase()->GetMasterCode());
    QSqlQuery querySCount(SCount ,GetLayersBase()->GetDatabase());
    if(querySCount.next ()==true){
        int	RowCount=querySCount.value(0).toInt();
        ui->tableWidgetLot->setRowCount(RowCount);
    }

    QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT WHERE MASTERCODE=")
            +QString::number(GetLayersBase()->GetMasterCode())
            +QString(/**/" order by LASTUPDATED DESC");
    QSqlQuery query(S ,GetLayersBase()->GetDatabase());
    int	L=0;
    if(query.next ()==true){
        do{
            if(L>=MaxLines){
                break;
            }
            int			LotAutoCount=query.value(query.record().indexOf(/**/"LOTAUTOCOUNT"	)).toInt();
            QString		IDName		=query.value(query.record().indexOf(/**/"IDNAME"		)).toString();
            QString		LotName		=query.value(query.record().indexOf(/**/"LOTNAME"		)).toString();
            XDateTime	LastUpdated(query.value(query.record().indexOf(/**/"LASTUPDATED"	)).toDateTime());
            QString		Remark		=query.value(query.record().indexOf(/**/"REMARK"		)).toString();
            LotAutoCounts.Add(LotAutoCount);
            SetDataToTable(ui->tableWidgetLot,0,L,IDName);
            SetDataToTable(ui->tableWidgetLot,1,L,LotName);
            SetDataToTable(ui->tableWidgetLot,2,L,LastUpdated.toString(/**/"yy/MM/dd hh:mm:ss"));
            SetDataToTable(ui->tableWidgetLot,3,L,Remark);
            L++;
        }while(query.next ()==true);
    }
    InstallOperationLog(this);
}

SelectLotForm::~SelectLotForm()
{
    delete ui;
}

void SelectLotForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}
void SelectLotForm::on_tableWidgetLot_clicked(const QModelIndex &index)
{
    SelectLotAction();
}

void SelectLotForm::on_tableWidgetLot_doubleClicked(const QModelIndex &index)
{

}

void SelectLotForm::on_ButtonCreate_clicked()
{
    SelectedLotID		=ui->EditID		->text();
    SelectedLotName		=ui->EditName	->text();
//	if(SelectedLotID.isEmpty()==true && SelectedLotName.isEmpty()==false){
//		SelectedLotID=SelectedLotName;
//		ui->EditID->setText(SelectedLotID);
//	}
    if(SelectedLotID.isEmpty()==false && SelectedLotName.isEmpty()==true){
        SelectedLotName=SelectedLotID;
        ui->EditName->setText(SelectedLotName);
    }

    SelectedRemark		=ui->EditRemark	->text();

    if(ExecuteCreateNew()==false){
        return;
    }

    if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
        if(QMessageBox::question(NULL,LangCGSolver.GetString(SelectLotForm_LS,LID_0)/*"Synchronized"*/
                                    ,LangCGSolver.GetString(SelectLotForm_LS,LID_1)/*"???u?a??????E??E?U??E?c?H"*/
                                    ,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
            QBuffer	Buff;
            Buff.open(QIODevice::ReadWrite);
            int	Cmd=1;
            ::Save(&Buff,Cmd);
            ::Save(&Buff,SelectedLotID);
            ::Save(&Buff,SelectedLotName);
            ::Save(&Buff,SelectedRemark);

            if(ParentGUI!=NULL){
                TxSync(Buff);
            }
        }
    }


    RetMode=true;
    emit	SignalClose();
}

void SelectLotForm::on_ButtonSelect_clicked()
{
    if(SelectLotAction()==true){
            if(ParentGUI!=NULL)
                ParentGUI->BroadcastStartLot();

            if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
            if(QMessageBox::question(NULL,LangCGSolver.GetString(SelectLotForm_LS,LID_2)/*"Synchronized"*/
                                        ,LangCGSolver.GetString(SelectLotForm_LS,LID_3)/*"???u?a?C?Y???Y?U??E?c?H"*/
                                        ,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
                QBuffer	Buff;
                Buff.open(QIODevice::ReadWrite);
                int	Cmd=2;
                ::Save(&Buff,Cmd);
                ::Save(&Buff,SelectedLotID);
                ::Save(&Buff,SelectedLotName);
                ::Save(&Buff,SelectedRemark);

                TxSync(Buff);
            }
        }
        RetMode=true;
        emit	SignalClose();
    }
}

void SelectLotForm::on_ButtonCancel_clicked()
{
    RetMode=false;
    emit	SignalClose();
}

void	SelectLotForm::CreateNewLot(const QString &LotID ,const QString &LotName ,bool Synchronized)
{
    ui->EditID		->setText(LotID);
    ui->EditName		->setText(LotName);
    SelectedLotID	=LotID;
    SelectedLotName	=LotName;

    if(SelectedLotID.isEmpty()==false && SelectedLotName.isEmpty()==true){
        SelectedLotName=SelectedLotID;
        ui->EditName->setText(SelectedLotName);
    }

    SelectedRemark		=/**/"";

    if(ExecuteCreateNew()==false){
        return;
    }

    if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
        if(Synchronized==true){
            QBuffer	Buff;
            Buff.open(QIODevice::ReadWrite);
            int	Cmd=1;
            ::Save(&Buff,Cmd);
            ::Save(&Buff,SelectedLotID);
            ::Save(&Buff,SelectedLotName);
            ::Save(&Buff,SelectedRemark);

            if(ParentGUI!=NULL){
                TxSync(Buff);
            }
        }
    }
    if(ParentGUI!=NULL)
        ParentGUI->BroadcastStartLot();

    RetMode=true;
    emit	SignalClose();
}

bool SelectLotForm::ExecuteCreateNew(void)
{
    QString	SGetMax=QString(/**/"SELECT MAX(LOTAUTOCOUNT) FROM INSPECTIONLOT WHERE MASTERCODE=")
                +QString::number(GetLayersBase()->GetMasterCode());
    QSqlQuery querySGetMax(SGetMax,GetLayersBase()->GetDatabase());
    int	MaxAutoCount=0;
    if(querySGetMax.next ()==true){
        MaxAutoCount=querySGetMax.value(0).toInt();
    }
    MaxAutoCount++;
    SelectedLotAutoCount=MaxAutoCount;
    SelectedLastUpdated	=XDateTime::currentDateTime();
    if(SelectedLotID.isEmpty()==true){
        SelectedLotID=SelectedLastUpdated.toString(/**/"yyyy-MM-dd--hh-mm-ss");
    }

    try{
        QSqlQuery queryInsrt(GetLayersBase()->GetDatabase());
        queryInsrt.prepare(QString(/**/"INSERT INTO INSPECTIONLOT(LOTAUTOCOUNT,MASTERCODE,LASTUPDATED,IDNAME,LOTNAME,REMARK) ")
            +QString(/**/"VALUES(:LOTAUTOCOUNT,:MASTERCODE,:LASTUPDATED,:IDNAME,:LOTNAME,:REMARK);"));
        queryInsrt.bindValue(0	, SelectedLotAutoCount);
        queryInsrt.bindValue(1	, GetLayersBase()->GetMasterCode());
        queryInsrt.bindValue(2	, SelectedLastUpdated.GetQDateTime());
        queryInsrt.bindValue(3	, SelectedLotID);
        queryInsrt.bindValue(4	, SelectedLotName);
        queryInsrt.bindValue(5	, SelectedRemark);

        if(queryInsrt.exec()==false){
            return false;
        }
    }
    catch(...){
        return false;
    }
    return true;
}

bool SelectLotForm::SelectLotAction(void)
{
    QModelIndex Index=ui->tableWidgetLot->currentIndex();
    int	R=Index.row();
    if(R<0){
        return false;
    }
    IntClass	*c=LotAutoCounts.GetItem(R);
    if(c==NULL){
        return false;
    }
    int	LotAutoCount=c->GetValue();
    QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT WHERE MASTERCODE=")
            +QString::number(GetLayersBase()->GetMasterCode())
            +QString(/**/" and LOTAUTOCOUNT=")
            +QString::number(LotAutoCount);
    QSqlQuery query(S ,GetLayersBase()->GetDatabase());
    if(query.next ()==true){
        SelectedLotAutoCount=query.value(query.record().indexOf(/**/"LOTAUTOCOUNT"	)).toInt();
        SelectedLotID		=query.value(query.record().indexOf(/**/"IDName"		)).toString();
        SelectedLotName		=query.value(query.record().indexOf(/**/"LOTNAME"		)).toString();
        SelectedLastUpdated	=query.value(query.record().indexOf(/**/"LASTUPDATED"	)).toDateTime();
        SelectedRemark		=query.value(query.record().indexOf(/**/"REMARK"		)).toString();
        ui->EditID		->setText(SelectedLotID);
        ui->EditName		->setText(SelectedLotName);
        ui->EditRemark	->setText(SelectedRemark);

        return true;
    }
    return false;
}

void	SelectLotForm::TxSync(QBuffer &Buff)
{
    ParentGUI->TxSync(Buff.buffer());
}

bool	SelectLotForm::RxSync(QByteArray &f)
{
    QBuffer	Buff(&f);
    Buff.open(QIODevice::ReadWrite);
    bool	ret=RxSync(Buff);
    return ret;
}

bool	SelectLotForm::RxSync(QIODevice &Buff)
{
    int	Cmd;
    ::Load(&Buff,Cmd);
    if(Cmd==1){
        ::Load(&Buff,SelectedLotID);
        ::Load(&Buff,SelectedLotName);
        ::Load(&Buff,SelectedRemark);
        if(ExecuteCreateNew()==false){
            return false;
        }
        if(ParentGUI!=NULL)
            ParentGUI->BroadcastStartLot();
        return true;
    }
    else if(Cmd==2){
        ::Load(&Buff,SelectedLotID);
        ::Load(&Buff,SelectedLotName);
        ::Load(&Buff,SelectedRemark);

        QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT WHERE MASTERCODE=")
                +QString::number(GetLayersBase()->GetMasterCode())
                +QString(/**/" and IDNAME=\'")
                +SelectedLotID
                +QString(/**/"\'");
        QSqlQuery query(S ,GetLayersBase()->GetDatabase());
        if(query.next ()==true){
            SelectedLotAutoCount=query.value(query.record().indexOf(/**/"LOTAUTOCOUNT"	)).toInt();
            SelectedLotID		=query.value(query.record().indexOf(/**/"IDName"		)).toString();
            SelectedLotName		=query.value(query.record().indexOf(/**/"LOTNAME"		)).toString();
            SelectedLastUpdated	=query.value(query.record().indexOf(/**/"LASTUPDATED"	)).toDateTime();
            SelectedRemark		=query.value(query.record().indexOf(/**/"REMARK"		)).toString();
            if(ParentGUI!=NULL)
                ParentGUI->BroadcastStartLot();
            return true;
        }
    }
    return false;
}

