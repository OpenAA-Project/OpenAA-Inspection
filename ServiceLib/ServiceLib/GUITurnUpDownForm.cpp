#include "ServiceLibResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\GUITurnUpDownForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "GUITurnUpDownForm.h"
#include "ui_GUITurnUpDownForm.h"
#include "XGUIFormBase.h"

GUITurnUpDownForm::GUITurnUpDownForm(const QWidgetList &list,GUIFormBase *form ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUITurnUpDownForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    TabList	=list;
    Form	=form;

    SelectedTabSheet=NULL;
    SelectedStackedSheet=NULL;
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
    ui->comboBTabSheet->setCurrentIndex(0);
}

GUITurnUpDownForm::~GUITurnUpDownForm()
{
    delete ui;
}

void GUITurnUpDownForm::closeEvent ( QCloseEvent * event )
{
    QDialog::closeEvent (event);
    deleteLater ();
}

void	GUITurnUpDownForm::ShowList(void)
{
    int	index=ui->comboBTabSheet->currentIndex();
    QTabWidget	*wtab=dynamic_cast<QTabWidget *>(TabList[index]);
    if(wtab!=NULL){
        SelectedTabSheet=wtab;
        ui->listWidgetList->clear();
        for(int i=0;i<wtab->count();i++){
            ui->listWidgetList->addItem(wtab->tabText(i));
        }
        return;
    }
    QStackedWidget	*wsw=dynamic_cast<QStackedWidget *>(TabList[index]);
    if(wsw!=NULL){
        SelectedStackedSheet=wsw;
        ui->listWidgetList->clear();
        for(int i=0;i<wsw->count();i++){
            ui->listWidgetList->addItem(wsw->widget(i)->windowTitle());
        }
        return;
    }
}

void GUITurnUpDownForm::on_pushButtonUp_clicked()
{
    int	NowIndex=ui->listWidgetList->currentRow();
    if(NowIndex<=0)
        return;
    int	index=ui->comboBTabSheet->currentIndex();
    QTabWidget	*wtab=dynamic_cast<QTabWidget *>(TabList[index]);
    if(wtab!=NULL){
        Form->SwapTab(wtab ,NowIndex-1,NowIndex);
        ShowList();
        return;
    }
    QStackedWidget	*wsw=dynamic_cast<QStackedWidget *>(TabList[index]);
    if(wsw!=NULL){
        Form->SwapTab(wsw ,NowIndex-1,NowIndex);
        ShowList();
        return;
    }
}

void GUITurnUpDownForm::on_pushButtonDown_clicked()
{
    int	NowIndex=ui->listWidgetList->currentRow();
    int	index=ui->comboBTabSheet->currentIndex();
    QTabWidget	*wtab=dynamic_cast<QTabWidget *>(TabList[index]);
    if(wtab!=NULL){
        if(NowIndex>=wtab->count()-1)
            return;
        Form->SwapTab(wtab ,NowIndex,NowIndex+1);
        ShowList();
        return;
    }
    QStackedWidget	*wsw=dynamic_cast<QStackedWidget *>(TabList[index]);
    if(wsw!=NULL){
        if(NowIndex>=wsw->count()-1)
            return;
        Form->SwapTab(wsw ,NowIndex,NowIndex+1);
        ShowList();
        return;
    }
}

void GUITurnUpDownForm::on_pushButtonOK_clicked()
{
    done(true);
}

void GUITurnUpDownForm::on_comboBTabSheet_currentIndexChanged(int)
{
    ShowList();
}

