/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSetTactTime\ButtonSetTactTimeForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
