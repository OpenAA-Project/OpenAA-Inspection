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

#include "ButtonSetRailWidthResource.h"

#include "ButtonSetRailWidthForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

ButtonSetRailWidthForm::ButtonSetRailWidthForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	MaxSize	=251;
	InitialWidth=100;
}

ButtonSetRailWidthForm::~ButtonSetRailWidthForm()
{

}

void	ButtonSetRailWidthForm::Prepare(void)
{
	ui.doubleSpinBoxRailWidth	->setMaximum(MaxSize);
	ui.doubleSpinBoxRailWidth	->setValue(InitialWidth);
}

void	ButtonSetRailWidthForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"RAILWIDTH", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/10.0;
			ui.doubleSpinBoxRailWidth->setValue(m);
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
				if(Param!=NULL){
					Param->RailWidth=d;
				}
			}
		}
	}
}


void ButtonSetRailWidthForm::on_pushButtonSet_clicked()
{
	int	d=ui.doubleSpinBoxRailWidth->value()*10.0;
	QVariant	data(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"RAILWIDTH", data)==false){
		QMessageBox::warning ( NULL
							, LangSolver.GetString(ButtonSetRailWidthForm_LS,LID_0)/*"Error"*/
							, LangSolver.GetString(ButtonSetRailWidthForm_LS,LID_1)/*"Can't set RailWidth in MasterData"*/
							, QMessageBox::Ok);
	}
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			Param->RailWidth=d;
		}
	}
}