/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLightForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SelectLightForm.h"
#include "ui_SelectLightForm.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "XLightClass.h"
#include <QSqlQuery>
#include <QMessageBox>


SelectLightForm::SelectLightForm(LayersBase *pbase ,bool ShowSelectButtons ,bool EditPanel, int SelectMachineCode ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(pbase)
    ,ui(new Ui::SelectLightForm)
{
    ui->setupUi(this);
    //LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    //LangLibSolver.SetUI(this);

    SelectedLightID=-1;
    int	Y=0;
    if(ShowSelectButtons==true){
        ui->frameOkCancel->setVisible(true);
        Y+=ui->tableWidgetLight->geometry().height();
        Y+=ui->frameOkCancel->geometry().height();
    }
    else{
        ui->frameOkCancel->setVisible(false);
    }
    if(EditPanel==true){
        ui->frameEditPanel->setVisible(true);
        ui->frameEditPanel->move(0,Y);
        Y+=ui->frameEditPanel->geometry().height();
    }
    else{
        ui->frameEditPanel->setVisible(false);
    }
    resize(geometry().width(),Y);
    ui->tableWidgetLight->setColumnWidth (0,40);
    ui->tableWidgetLight->setColumnWidth (0,160);
    ui->tableWidgetLight->setColumnWidth (0,160);
    ui->tableWidgetLight->setColumnWidth (0,80);

    SelectedMachineID	=GetLayersBase()->GetMachineID();
    ui->pushButtonUpdate->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
    ShowList();

    InstallOperationLog(this);
}

SelectLightForm::~SelectLightForm()
{
    delete ui;
}

void SelectLightForm::on_tableWidgetLight_doubleClicked(const QModelIndex &index)
{
    on_pushButtonSelect_clicked();
}

void SelectLightForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void SelectLightForm::ShowList(void)
{
    std::shared_ptr<DatabaseLoader>		DL=GetLayersBase()->GetDatabaseLoader();

    QSqlQuery *query=DL->S_LightFindFirst(GetLayersBase()->GetDatabase() ,SelectedMachineID);
    int	N=0;
    if(query!=NULL){
        while(DL->S_FindNext(query)==true){
            N++;
        }
    }
    DL->S_DeleteQuery(query);

    ui->tableWidgetLight->setRowCount(N);
    LightLines.RemoveAll();
    query=DL->S_LightFindFirst(GetLayersBase()->GetDatabase() ,SelectedMachineID);
    int	row=0;
    if(query!=NULL){
        while(DL->S_FindNext(query)==true){
            LightPacket	*L=new LightPacket();
            QVariant vLIGHTID;
            if(DL->S_GetFieldValue(query,/**/"LIGHTID",vLIGHTID)==true){
                L->LightID=vLIGHTID.toInt();
                QTableWidgetItem *W=ui->tableWidgetLight->item ( row, 0);
                if(W==NULL){
                    W=new QTableWidgetItem();
                    ui->tableWidgetLight->setItem ( row, 0,W);
                    W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }
                W->setText(QString::number(vLIGHTID.toInt()));
            }
            QVariant vMACHINEID;
            if(DL->S_GetFieldValue(query,/**/"MACHINEID",vMACHINEID)==true){
                L->MachineID=vMACHINEID.toInt();
            }
            LightLines.AppendList(L);

            QVariant vNAME;
            if(DL->S_GetFieldValue(query,/**/"NAME",vNAME)==true){
                QTableWidgetItem *W=ui->tableWidgetLight->item ( row, 1);
                if(W==NULL){
                    W=new QTableWidgetItem();
                    ui->tableWidgetLight->setItem ( row, 1,W);
                    W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }
                W->setText(vNAME.toString());
            }
            QVariant vREMARK;
            if(DL->S_GetFieldValue(query,/**/"REMARK",vREMARK)==true){
                QTableWidgetItem *W=ui->tableWidgetLight->item ( row, 2);
                if(W==NULL){
                    W=new QTableWidgetItem();
                    ui->tableWidgetLight->setItem ( row, 2,W);
                    W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }
                W->setText(vREMARK.toString());
            }
            QVariant vDLLIDNAME;
            if(DL->S_GetFieldValue(query,/**/"DLLIDNAME",vDLLIDNAME)==true){
                QTableWidgetItem *W=ui->tableWidgetLight->item ( row, 3);
                if(W==NULL){
                    W=new QTableWidgetItem();
                    ui->tableWidgetLight->setItem ( row, 3,W);
                    W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }
                W->setText(vDLLIDNAME.toString());
            }
            row++;
        }
    }
    DL->S_DeleteQuery(query);
}

void SelectLightForm::on_pushButtonSelect_clicked()
{
    int	row=ui->tableWidgetLight->currentRow();
    if(row<0){
        return;
    }
    if(GetLayersBase()->GetLightBase()==NULL){
        return;
    }
    SelectOne();

    QBuffer	Buff(&SelectedLight);
    Buff.open(QIODevice::ReadOnly);
    if(GetLayersBase()->GetLightBase()->Load(&Buff)==false){
        QMessageBox::warning (NULL
                            , "Error"
                            , "Error occurs from Load-function in Light-DLL");
        return;
    }

    emit	SignalClose();
}

void SelectLightForm::on_pushButtonCancel_clicked()
{
    emit	SignalClose();
}

void SelectLightForm::on_pushButtonCreateNew_clicked()
{
    if(GetLayersBase()->GetLightBase()==NULL){
        return;
    }
    std::shared_ptr<DatabaseLoader>	DL=GetLayersBase()->GetDatabaseLoader();
    QString Name	=ui->lineEditName	->text();
    QString Remark	=ui->lineEditRemark	->text();
    QBuffer	Buff;
    Buff.open(QIODevice::WriteOnly);
    if(GetLayersBase()->GetLightBase()->Save(&Buff)==false){
        QMessageBox::warning (NULL
                            , "Error"
                            , "Error occurs from Save-function in Light-DLL");
        return;
    }
    QByteArray LightData=Buff.buffer ();
    QByteArray LightImage;
    if(DL->S_CreateNewLight(GetLayersBase()->GetDatabase(),GetLayersBase()->GetMachineID()
                        ,GetLayersBase()->GetLightBase()->GetFirst()->GetDLLName()
                        ,Name ,Remark ,LightData ,LightImage)==false){
        QMessageBox::warning (NULL
                            , "Error"
                            , "Error occurs from AddRecord-function in Database");
        return;
    }
    QSqlQuery *Qr=DL->S_LightFindLast(GetLayersBase()->GetDatabase(),GetLayersBase()->GetMachineID());
    if(Qr!=NULL){
        QVariant v;
        if(DL->S_GetFieldValue(Qr,/**/"LIGHTID",v)==true){
            SelectedMachineID	=GetLayersBase()->GetMachineID();
            SelectedLightID		=v.toInt();
            SelectedLight		=LightData;
        }
    }
    DL->S_DeleteQuery(Qr);
    ShowList();
}

void SelectLightForm::on_pushButtonUpdate_clicked()
{
    if(SelectedLightID==-1){
        return;
    }
    std::shared_ptr<DatabaseLoader>	DL=GetLayersBase()->GetDatabaseLoader();
    QString Name	=ui->lineEditName	->text();
    QString Remark	=ui->lineEditRemark	->text();
    QByteArray LightImage;
    if(DL->S_UpdateLight(GetLayersBase()->GetDatabase(),SelectedMachineID,SelectedLightID,Name ,Remark ,SelectedLight ,LightImage)==false){
        QMessageBox::warning (NULL
                            , "Error"
                            , "Error occurs from UpdateRecord-function in Database");
        return;
    }
    ShowList();
}

void SelectLightForm::on_pushButtonDelete_clicked()
{
    if(SelectedLightID==-1){
        return;
    }
    if(QMessageBox::warning (NULL
        , "Confirm"
        , "Delete OK?"
        , QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){

        std::shared_ptr<DatabaseLoader>	DL=GetLayersBase()->GetDatabaseLoader();
        if(DL->S_DeleteLight(GetLayersBase()->GetDatabase(),SelectedMachineID,SelectedLightID)==false){
            QMessageBox::warning (NULL
                                , "Error"
                                , "Error occurs from DeleteRecord-function in Database");
            return;
        }
        SelectedLightID=-1;
        ui->pushButtonUpdate->setEnabled(false);
        ui->pushButtonDelete->setEnabled(false);
        ShowList();
    }
}

void SelectLightForm::on_tableWidgetLight_clicked(const QModelIndex &ItemIndex)
{
    SelectOne();
}
void SelectLightForm::SelectOne(void)
{
    int	row=ui->tableWidgetLight->currentRow();
    std::shared_ptr<DatabaseLoader>	DL=GetLayersBase()->GetDatabaseLoader();
    LightPacket *L=LightLines.GetItem(row);
    if(L!=NULL){
        QSqlQuery *query=DL->S_GetLight(GetLayersBase()->GetDatabase() ,L->MachineID,L->LightID);
        if(query!=NULL && DL->S_FindNext(query)==true){
            QVariant vNAME;
            if(DL->S_GetFieldValue(query,/**/"NAME",vNAME)==true){
                ui->lineEditName->setText(vNAME.toString());
            }
            else{
                ui->lineEditName->setText(QString());
            }
            QVariant vREMARK;
            if(DL->S_GetFieldValue(query,/**/"REMARK",vREMARK)==true){
                ui->lineEditRemark->setText(vREMARK.toString());
            }
            else{
                ui->lineEditRemark->setText(QString());
            }
            QVariant vDLLIDNAME;
            if(DL->S_GetFieldValue(query,/**/"DLLIDNAME",vDLLIDNAME)==true){
                ui->lineEditDLLName->setText(vDLLIDNAME.toString());
            }
            else{
                ui->lineEditDLLName->setText(QString());
            }

            QVariant	vMachineID;
            if(DL->S_GetFieldValue(query,/**/"MACHINEID",vMachineID)==true){
                SelectedMachineID=vMachineID.toInt();
            }
            QVariant	vLightID;
            if(DL->S_GetFieldValue(query,/**/"LIGHTID",vLightID)==true){
                SelectedLightID=vLightID.toInt();
            }
            QVariant	vLightData;
            if(DL->S_GetFieldValue(query,/**/"LIGHTDATA",vLightData)==true){
                SelectedLight=vLightData.toByteArray();
            }
            ui->pushButtonUpdate->setEnabled(true);
            ui->pushButtonDelete->setEnabled(true);
            return;
        }
    }
    ui->lineEditName->setText(QString());
    ui->lineEditRemark->setText(QString());
    ui->lineEditDLLName->setText(QString());
}
