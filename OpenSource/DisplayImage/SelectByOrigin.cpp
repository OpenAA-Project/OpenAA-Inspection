/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectByOrigin.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectByOrigin.h"
#include "ui_SelectByOrigin.h"
#include "XGeneralFunc.h"
#include "XDisplayImagePacket.h"

SelectByOrigin::SelectByOrigin(LayersBase *Base,NPListPack<OriginNames>	&originNameList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectByOrigin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);

    SetWidgetCenter(this);

    Selected=NULL;
    OriginNameList.RemoveAll();
    for(OriginNames *v=originNameList.GetFirst();v!=NULL;v=v->GetNext()){
        OriginNames	*d=new OriginNames();
        *d=*v;
        OriginNameList.AppendList(d);
    }
    ui->tableWidget->setRowCount(OriginNameList.GetNumber());
    int	Row=0;
    for(OriginNames *v=OriginNameList.GetFirst();v!=NULL;v=v->GetNext(),Row++){
        QTableWidgetItem *w;
        w=ui->tableWidget->item (Row, 0);
        if(w==NULL){
            ui->tableWidget->setItem(Row,0,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(v->DLLRoot);

        w=ui->tableWidget->item (Row, 1);
        if(w==NULL){
            ui->tableWidget->setItem(Row,1,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(v->DLLName);

        w=ui->tableWidget->item (Row, 2);
        if(w==NULL){
            ui->tableWidget->setItem(Row,2,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(QString::number(v->Numb));
    }
    Base->InstallOperationLog(this);
}

SelectByOrigin::~SelectByOrigin()
{
    delete ui;
}

void SelectByOrigin::on_tableWidget_cellDoubleClicked(int row, int column)
{
    on_pushButtonSelect_clicked();
}

void SelectByOrigin::on_pushButtonSelect_clicked()
{
    int	r=ui->tableWidget->currentRow();
    if(r>=0){
        Selected=OriginNameList.GetItem(r);
        done((int)true);
    }
}

void SelectByOrigin::on_pushButtonCancel_clicked()
{
    done((int)false);
}
