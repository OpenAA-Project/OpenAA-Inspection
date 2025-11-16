#include "ShowStrategicNumberResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowStrategicNumber\ShowStrategicNumberForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowStrategicNumberForm.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"

ShowStrategicNumberForm::ShowStrategicNumberForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ShowStrategicNumberForm::~ShowStrategicNumberForm()
{

}

void	ShowStrategicNumberForm::Prepare(void)
{
	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentStrategicNumber())	,this,SLOT(SlotChangeCurrentStrategicNumber())		,Qt::QueuedConnection);
	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentStrategicNumberSeq())	,this,SLOT(SlotChangeCurrentStrategicNumberSeq())	,Qt::QueuedConnection);
}

void	ShowStrategicNumberForm::ShowInPlayer(int64 shownInspectionID)
{
	int	n=GetLayersBase()->GetCurrentStrategicNumber();
	ui.spinBoxNumber->setValue(n);
}

void ShowStrategicNumberForm::on_spinBoxNumber_valueChanged(int)
{
	int	n=ui.spinBoxNumber->value();
	GetLayersBase()->SetCurrentStrategicNumber(n);
	
	n=GetLayersBase()->GetCurrentStrategicNumber();
	ui.spinBoxNumber->setValue(n);
}

void	ShowStrategicNumberForm::BuildForShow(void)
{
	ShowInPlayer(-1);
}

void	ShowStrategicNumberForm::SlotChangeCurrentStrategicNumber()
{
	ShowInPlayer(-1);
}
void	ShowStrategicNumberForm::SlotChangeCurrentStrategicNumberSeq()
{
	ShowInPlayer(-1);
}