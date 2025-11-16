/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonInspectionID\ButtonInspectionIDForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
