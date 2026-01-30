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

#include "EasyPropertyAlignmentResource.h"
#include "SelectActionLibraryDialog.h"
#include "ui_SelectActionLibraryDialog.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SelectActionLibraryDialog::SelectActionLibraryDialog(LayersBase *base
                                                    ,EasyPropertyAlignmentForm *P
                                                    ,bool DeleteButton
                                                    ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),Parent(P),
    ui(new Ui::SelectActionLibraryDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    ::SetColumnWidthInTable(ui->tableWidgetLibrary,0, 20);
    ::SetColumnWidthInTable(ui->tableWidgetLibrary,1, 80);

    for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
        AlgorithmBase   *ABase=a->GetInstance();
        if(ABase!=NULL){
            AlgorithmLibraryContainer   *AContainer=ABase->GetLibraryContainer();
            if(AContainer!=NULL){
                LibTypeList.Add(ABase->GetLibType());
            }
        }
    }
    for(IntClass *c=LibTypeList.GetFirst();c!=NULL;c=c->GetNext()){
        AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(c->GetValue());   
        ui->listWidgetLibType->addItem(ABase->GetNameByCurrentLanguage());
    }
    ui->toolButtonRemoveLibrary->setVisible(DeleteButton);
}

SelectActionLibraryDialog::~SelectActionLibraryDialog()
{
    delete ui;
}

void SelectActionLibraryDialog::on_listWidgetLibType_clicked(const QModelIndex &index)
{
    CurrentLibList.RemoveAll();
    int cRow=ui->listWidgetLibType->currentRow();
    if(cRow>=0){
        int LibType=LibTypeList[cRow];
        AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LibType);   
        AlgorithmLibraryContainer	*AContainer=ABase->GetLibraryContainer();
        if(AContainer!=NULL){
            AContainer->EnumLibrary(CurrentLibList);
        }
    }
    ui->tableWidgetLibrary->setRowCount(CurrentLibList.GetCount());
	int	Row=0;
	for(AlgorithmLibraryList *a=CurrentLibList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetLibrary,0, Row, QString::number(a->GetLibID()));
		QString	LibName=GetLayersBase()->GetLibraryName(a->GetLibType(),a->GetLibID());
		::SetDataToTable(ui->tableWidgetLibrary,1, Row, LibName);
	}
}

void SelectActionLibraryDialog::on_toolButtonAddLibrary_clicked()
{
    int Row=ui->tableWidgetLibrary->currentRow();
    if(Row>=0){
        AlgorithmLibraryList *a=CurrentLibList[Row];
        if(a!=NULL){
            Selected=*a;
            done(1);
        }
    }
}

void SelectActionLibraryDialog::on_toolButtonRemoveLibrary_clicked()
{
    done(2);
}

void SelectActionLibraryDialog::on_tableWidgetLibrary_doubleClicked(const QModelIndex &index)
{
    on_toolButtonAddLibrary_clicked();
}
