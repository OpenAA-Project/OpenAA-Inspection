/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectTabTop.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectTabTop.h"
#include "ui_SelectTabTop.h"
#include "XDataInLayer.h"


SelectTabTop::SelectTabTop(LayersBase *lbase ,QWidgetList &list ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::SelectTabTop)
{
    ui->setupUi(this);
    LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangLibSolver.SetUI(this);
    //setWindowFlags(Qt::WindowCloseButtonHint);

    SelectedTabSheet=NULL;
    SelectedStackedSheet=NULL;
    SelectedTabPage	=-1;
    RetMode=false;
    TabList	=list;
    ui->comboBTabSheet->clear();
    for(int i=0;i<TabList.count();i++){
        QTabWidget	*wtab=dynamic_cast<QTabWidget *>(TabList[i]);
        if(wtab!=NULL){
            QString	B=QString::number(i+1)+QString(/**/" : ")+wtab->objectName();
            ui->comboBTabSheet->addItem(B,QVariant(i));
        }
        QStackedWidget	*wstack=dynamic_cast<QStackedWidget *>(TabList[i]);
        if(wstack!=NULL){
            QString	B=QString::number(i+1)+QString(/**/" : ")+wstack->objectName();
            ui->comboBTabSheet->addItem(B,QVariant(i));
        }
    }

    int	MaxN=0;
    int	MaxNTurn=0;
    for(int	k=0;k<ui->comboBTabSheet->count();k++){
        ui->comboBTabSheet->setCurrentIndex(k);
        on_comboBTabSheet_currentIndexChanged(k);
        if(ui->comboBTabPage->count()>MaxNTurn){
            MaxNTurn=ui->comboBTabPage->count();
            MaxN=k;
        }
    }
    ui->comboBTabSheet->setCurrentIndex(MaxN);
    on_comboBTabSheet_currentIndexChanged(MaxN);

	InstallOperationLog(this);
}

SelectTabTop::~SelectTabTop()
{
    delete ui;
}

void SelectTabTop::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    //deleteLater ();
}
void SelectTabTop::on_comboBTabSheet_currentIndexChanged(int index)
{
    QTabWidget	*wtab=dynamic_cast<QTabWidget *>(TabList[index]);
    if(wtab!=NULL){
        SelectedTabSheet=wtab;
        ui->comboBTabPage->clear();
        for(int i=0;i<wtab->count();i++){
            ui->comboBTabPage->addItem(wtab->tabText(i),QVariant(i));
        }
        SelectedStackedSheet=NULL;
        return;
    }
    QStackedWidget	*wsw=dynamic_cast<QStackedWidget *>(TabList[index]);
    if(wsw!=NULL){
        SelectedStackedSheet=wsw;
        ui->comboBTabPage->clear();
        for(int i=0;i<wsw->count();i++){
            ui->comboBTabPage->addItem(wsw->widget(i)->windowTitle(),QVariant(i));
        }
        SelectedTabSheet=NULL;
        return;
    }
}

void SelectTabTop::on_comboBTabPage_currentIndexChanged(int index)
{
    SelectedTabPage=index;
}

void SelectTabTop::on_OKButton_clicked()
{
    RetMode=true;
    close();
}

void SelectTabTop::on_CancelButton_clicked()
{
    close();
}
