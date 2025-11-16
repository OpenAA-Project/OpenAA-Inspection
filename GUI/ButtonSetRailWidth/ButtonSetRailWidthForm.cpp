#include "ButtonSetRailWidthResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSetRailWidth\ButtonSetRailWidthForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
