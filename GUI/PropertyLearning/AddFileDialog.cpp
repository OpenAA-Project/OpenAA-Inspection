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

#include "AddFileDialogResource.h"
#include "AddFileDialog.h"
#include "PropertyLearningForm.h"
#include "XDataInLayer.h"

AddFileDialog::AddFileDialog(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

AddFileDialog::~AddFileDialog()
{

}

void AddFileDialog::showEvent ( QShowEvent * event ) 
{
	PropertyLearningForm	*PForm=dynamic_cast<PropertyLearningForm *>(parent());
	if(PForm!=NULL){
		ui.comboBoxPage->clear();
		for(int page=0;page<PForm->GetPageNumb();page++){
			ui.comboBoxPage->addItem(QString(/**/"Page ")+QString::number(page));
		}
		ui.comboBoxPage->setCurrentIndex(0);
	}

	ShowList();
	SelectedList.RemoveAll();
}

void	AddFileDialog::ShowList()
{
	PropertyLearningForm	*PForm=dynamic_cast<PropertyLearningForm *>(parent());
	if(PForm!=NULL){
		int	Page=ui.comboBoxPage->currentIndex();
		if(Page>=0){
			ui.tableWidget->setRowCount(PForm->StoredList[Page].GetNumber());
			int	i=0;
			for(LearningFileList *a=PForm->StoredList[Page].GetFirst();a!=NULL;a=a->GetNext(),i++){
				QTableWidgetItem *w;
				w=ui.tableWidget->item (i, 0);
				if(w==NULL){
					ui.tableWidget->setItem(i,0,(w=new QTableWidgetItem()));
					w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				w->setText(QString::number(a->ID));
	
				w=ui.tableWidget->item (i, 1);
				if(w==NULL){
					ui.tableWidget->setItem(i,1,(w=new QTableWidgetItem()));
					w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				w->setText(a->FileName);
			}
		}
	}
}



void AddFileDialog::on_pushButtonAdd_clicked()
{
	PropertyLearningForm	*PForm=dynamic_cast<PropertyLearningForm *>(parent());
	if(PForm!=NULL){
		SelectedPage=ui.comboBoxPage->currentIndex();

		QList<QTableWidgetItem *> SItems=ui.tableWidget->selectedItems ();
		for(int i=0;i<SItems.count();i++){
			QTableWidgetItem *s=SItems[i];
			if(s->column()!=0)
				continue;
			int	r=s->row();
			LearningFileList *a=PForm->StoredList[SelectedPage].GetItem(r);
			LearningFileList *b=new LearningFileList();
			*b=*a;
			SelectedList.AppendList(b);
		}
	}

	done(true);
}

void AddFileDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void AddFileDialog::on_comboBoxPage_textChanged(QString)
{
	ShowList();
}

void AddFileDialog::on_comboBoxPage_currentIndexChanged(int)
{
	ShowList();
}