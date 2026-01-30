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

#include "SetZFormResource.h"
#include "SetZForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

SetZForm::SetZForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	GetParamGUI()->SetParam(&ZHeight, /**/"SetZ",/**/"ZHeight"		,/**/"Z Height(um)"		);
	LimitMax=99999999;
}

SetZForm::~SetZForm()
{

}

void	SetZForm::Prepare(void)
{
	double	m=((double)ZHeight)/1000.0;
	ui.doubleSpinBox->setValue(m);
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		Param->ZHeight=ZHeight;
	}
}

void	SetZForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"ZHEIGHT", data)==true){
		bool ok;
		int	d=data.toInt(&ok);
		if(ok==true){
			double	m=((double)d)/1000.0;
			ui.doubleSpinBox->setValue(m);
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
				Param->ZHeight=d;
			}
		}
	}
	else{
		double	m=((double)ZHeight)/1000.0;
		ui.doubleSpinBox->setValue(m);
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			Param->ZHeight=ZHeight;
		}
	}
}

void SetZForm::on_pushButtonOK_clicked()
{
	int	d=ui.doubleSpinBox->value()*1000.0;
	QVariant	data(d);
	if(GetLayersBase()->AddMasterFieldData(/**/"ZHEIGHT", data)==false){
		QMessageBox::warning ( NULL, LangSolver.GetString(SetZForm_LS,LID_0)/*"Error"*/
									, LangSolver.GetString(SetZForm_LS,LID_1)/*"Can't set ZHEIGHT in MasterData"*/
									, QMessageBox::Ok);
	}
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		Param->ZHeight=d;
	}
	ZHeight=d;
	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}

void	SetZForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateNewMasterSpecifiedBroadcaster	*C=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(C!=NULL){
		on_pushButtonOK_clicked();
	}
}