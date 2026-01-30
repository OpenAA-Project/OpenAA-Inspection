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


#include "ButtonInspectionIDResource.h"
#include "ButtonInspectionIDForm.h"

ButtonInspectionIDForm::ButtonInspectionIDForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	ReEntrant=false;
}

ButtonInspectionIDForm::~ButtonInspectionIDForm()
{

}

void	ButtonInspectionIDForm::BuildForShow(void)
{
	ShowInPlayer(-1);
}

void	ButtonInspectionIDForm::ShowInPlayer(int64 shownInspectionID)
{
	ReEntrant=true;
	ui.spinBoxID->setValue(GetLayersBase()->GetCurrentInspectIDForExecute());
	ReEntrant=false;
}
void ButtonInspectionIDForm::on_spinBoxID_valueChanged(int n)
{
	if(ReEntrant==false){
		GetLayersBase()->SetCurrentInspectID(n);
		GetLayersBase()->SetForceChangedInspectID();
	}
}