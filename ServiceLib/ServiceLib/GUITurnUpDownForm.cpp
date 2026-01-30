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

#include "ServiceLibResource.h"
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
