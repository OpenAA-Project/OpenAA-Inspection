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
#include "SelectLibraryForm.h"
#include "ui_SelectLibraryForm.h"
#include "LibFolderForm.h"
#include "XDataInLayer.h"


SelectLibraryForm::SelectLibraryForm(int libType ,LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectLibraryForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
    LibType         =libType;
    SelectedLibID   =-1;

    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    ui->tableWidgetLibList->setColumnWidth (0, 30);
    ui->tableWidgetLibList->setColumnWidth (1, 80);

    InstallOperationLog(this);
}

SelectLibraryForm::~SelectLibraryForm()
{
    delete ui;
}

void SelectLibraryForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonSelect_clicked();
}


void SelectLibraryForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}


void	SelectLibraryForm::ShowFolder(int LibType)
{
    pLibFolderForm->SetLibType(LibType);
}
void SelectLibraryForm::on_pushButtonSelect_clicked()
{
    int	R=ui->tableWidgetLibList->currentRow();
    if(R<0)
        return;
    AlgorithmLibraryList	*d=LibIDList.GetItem(R);
    if(d!=NULL){
        SelectedLibID	=d->GetLibID();
        SelectedLibName	=d->GetLibName();
        emit	SignalClose();
    }
}

void SelectLibraryForm::on_pushButtonCancel_clicked()
{
    SelectedLibID	=-1;
    SelectedLibName	=/**/"";
    emit	SignalClose();
}

void	SelectLibraryForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
    LibFolderID=libFolderID;
    ui->tableWidgetLibList->setRowCount(0);
    AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
    LibIDList.RemoveAll();
    LibList.EnumLibrary(GetLayersBase()->GetDatabase(),LibType,LibFolderID ,LibIDList);

    int	row=0;
    ui->tableWidgetLibList->setRowCount(LibIDList.GetNumber());
    for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
        QTableWidgetItem *W;
        W=ui->tableWidgetLibList->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibList->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        W=ui->tableWidgetLibList->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibList->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}