/*
 * Copyright (C) 2021
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

#include "MoveAllFormResource.h"
#include "MoveAllForm.h"

MoveAllForm::MoveAllForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.scrollArea->setWidget(&FrameCheckBox);
	FrameCheckBox.resize(60,500);

	AllocCheckedPage=GetPageNumb();
	CheckedPage=new QCheckBox*[AllocCheckedPage];
	int	Y=0;
	for(int page=0;page<AllocCheckedPage;page++){
		CheckedPage[page]=new QCheckBox(&FrameCheckBox);
		CheckedPage[page]->move(0,Y);
		Y+=20;
		CheckedPage[page]->setText(LangSolver.GetString(MoveAllForm_LS,LID_2)/*"Page "*/+QString::number(page));
		CheckedPage[page]->setCheckable(true);
		CheckedPage[page]->setChecked(true);
	}
	InstallOperationLog(this);
}

MoveAllForm::~MoveAllForm()
{
	if(CheckedPage!=NULL){
		for(int page=0;page<AllocCheckedPage;page++){
			CheckedPage[page]->deleteLater();
		}
		delete	[]CheckedPage;
	}
	CheckedPage=NULL;
}


void MoveAllForm::on_pushButtonOK_clicked()
{
	MovX=ui.spinBoxMoveX->value();
	MovY=ui.spinBoxMoveY->value();
	MoveMasterImage=ui.checkBoxMoveMasterImage->isChecked();
	MoveTargetImage=ui.checkBoxMoveTargetImage->isChecked();

	AppliedPages.RemoveAll();
	for(int page=0;page<AllocCheckedPage;page++){
		if(CheckedPage[page]->isChecked()==true){
			AppliedPages.Add(page);
		}
	}
	done(true);
}

void MoveAllForm::on_pushButtonCancel_clicked()
{
	done(false);
}