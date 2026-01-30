/*
 * Copyright (C) 2018
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

#include "OutlineOffsetForm.h"
#include "ui_OutlineOffsetForm.h"
#include "XGUIFormBase.h"


OutlineOffsetForm::OutlineOffsetForm(LayersBase *base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),
    ui(new Ui::OutlineOffsetForm)
{
    ui->setupUi(this);

	for(int phase=0;phase<GetPhaseNumb();phase++){
		SavedData[phase]=new XYData[GetPageNumb()];
	}

	WTabFormOutlineOffset=new EditOutlineOffset(GetLayersBase(),ui->ButtonOK->geometry().top()-4 ,this);
	WTabFormOutlineOffset->move(0,0);
	connect(WTabFormOutlineOffset,SIGNAL(Reflect()),this,SLOT(SlotReflect()));
	connect(WTabFormOutlineOffset,SIGNAL(ChangedValue()),this,SLOT(SlotReflect()));

}

OutlineOffsetForm::~OutlineOffsetForm()
{
    delete ui;

	for(int phase=0;phase<GetPhaseNumb();phase++){
		delete	[]SavedData[phase];
	}
}

void OutlineOffsetForm::showEvent ( QShowEvent * event )
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			SavedData[phase][page]=*Ph->GetPageData(page)->GetOutlineOffset();
		}
	}
	WTabFormOutlineOffset->SetGrid();
}

void OutlineOffsetForm::on_ButtonOK_clicked()
{
	GetLayersBase()->SaveOutlineOffsetForDatabase();
	close();
}

void OutlineOffsetForm::on_ButtonCancel_clicked()
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			*Ph->GetPageData(page)->GetOutlineOffset()=SavedData[phase][page];
		}
	}
	close();

}
void OutlineOffsetForm::SlotReflect()
{
	GetLayersBase()->GetMainWidget()->BroadcastDirectly(GUIFormBase::_BC_ShowInEdit,GetLayersBase()->GetCurrentInspectIDForDisplay());
}