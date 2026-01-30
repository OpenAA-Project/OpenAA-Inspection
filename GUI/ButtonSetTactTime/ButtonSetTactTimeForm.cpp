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


#include "ButtonSetTactTimeResource.h"
#include "ButtonSetTactTimeForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

ButtonSetTactTimeForm::ButtonSetTactTimeForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
}

ButtonSetTactTimeForm::~ButtonSetTactTimeForm()
{

}


void ButtonSetTactTimeForm::on_pushButtonSet_clicked()
{
	int	d=ui.spinBoxTactTime->value();
	QVariant	data(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"TACTTIME", data)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(ButtonSetTactTimeForm_LS,LID_1)/*"Error"*/, LangSolver.GetString(ButtonSetTactTimeForm_LS,LID_2)/*"Can't set TactTime in MasterData"*/, QMessageBox::Ok);
	}
	SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	Param->TactTimeMilisec=d;
}

void	ButtonSetTactTimeForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"TACTTIME", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			ui.spinBoxTactTime->setValue(d);
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
				if(Param!=NULL){
					Param->TactTimeMilisec=d;
				}
			}
		}
	}
}