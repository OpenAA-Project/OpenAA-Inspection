/*
 * Copyright (C) 2017
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

#include "OutlineInspectionResource.h"
#include "SetColorForm.h"

SetColorForm::SetColorForm(ColorLogic &data ,LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),RegistPanel(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ColorPanel.setParent(ui.frameColorPanel);
	ColorPanel.Fit(ui.frameColorPanel);
	ColorPanel.Cube=data;

	RegistPanel.setParent(ui.frameRegistPanel);
	RegistPanel.move(0,0);

	connect(&RegistPanel,SIGNAL(SignalSelectCData()),this,SLOT(SlotSelectCData()));
	connect(&RegistPanel,SIGNAL(SignalBeforeSave()) ,this,SLOT(SlotBeforeSave()));

	InstallOperationLog(this);
}

SetColorForm::~SetColorForm()
{

}
void	SetColorForm::SlotSelectCData()
{
	ColorLogic	*c=RegistPanel.CData.GetColorLogic();
	if(c!=NULL){
		ColorPanel.Cube=*c;
		ColorPanel.InitializedDoneCube();
		ColorPanel.Repaint();
	}
}
void	SetColorForm::SlotBeforeSave()
{
	RegistPanel.CData.Set(ColorPanel.Cube);
}

void SetColorForm::on_pushButtonOK_clicked()
{
	Col=ColorPanel.Cube;
	done(true);
}

void SetColorForm::on_pushButtonCancel_clicked()
{
	done(false);
}