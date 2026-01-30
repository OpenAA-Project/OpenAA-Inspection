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

#include "SelectLibraryInMaskResource.h"

#include "SelectLibraryInMaskForm.h"
#include "XDLLOnly.h"
#include "XParamDatabase.h"
#include "SelectLibrariesForAnyType.h"

SelectLibraryInMaskForm::SelectLibraryInMaskForm(bool NewMode ,LayersBase *Base ,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	
	Libs=new SelectLibrariesForAnyType(Base,this);
	Libs->setParent(ui.frameLibrary);
	Libs->setGeometry(0,0,ui.frameLibrary->width(),ui.frameLibrary->height());

	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Load(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);
	RetOK		=false;
	DeleteMode	=false;
	if(NewMode==true){
		ui.pushButtonDelete->setVisible(false);
	}
	else{
		ui.pushButtonDelete->setVisible(true);
	}
	InstallOperationLog(this);
}

SelectLibraryInMaskForm::~SelectLibraryInMaskForm()
{
	delete	Libs;
	Libs=NULL;
}
void SelectLibraryInMaskForm::resizeEvent(QResizeEvent *event)
{
	ui.frame->setGeometry(0,height()-ui.frame->height()
							,width(),ui.frame->height());
	ui.frameLibrary->resize(width(),height()-ui.frame->height());
	Libs->setGeometry(0,0,ui.frameLibrary->width(),ui.frameLibrary->height());
}

void	SelectLibraryInMaskForm::SetSelected(AlgorithmLibraryListContainer &selectedList)
{
	Libs->SelectedList=selectedList;
	Libs->ShowSelectedList();
}

void SelectLibraryInMaskForm::on_ButtonEffective_clicked()
{
	Effective=true;
	RetOK	=true;
	DeleteMode=false;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);
	emit	SignalClose();		
}

void SelectLibraryInMaskForm::on_ButtonNotEffective_clicked()
{
	Effective=false;
	RetOK	=true;
	DeleteMode=false;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);
	emit	SignalClose();
}

void SelectLibraryInMaskForm::on_ButtonCancel_clicked()
{
	RetOK=false;
	DeleteMode=false;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);
	emit	SignalClose();		
}

AlgorithmLibraryListContainer	SelectLibraryInMaskForm::GetSelectedList(void)
{
	return Libs->SelectedList;
}
void SelectLibraryInMaskForm::on_pushButtonDelete_clicked()
{
	DeleteMode=true;
	RetOK=true;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);
	emit	SignalClose();	
}
