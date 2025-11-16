#include "RepairStationResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\DockMasterWhole.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "DockMasterWhole.h"

DockMasterWhole::DockMasterWhole(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leMasterImageTitle=new QLineEdit();
	LangSolver.SetUI(this);

	leMasterImageTitle->setReadOnly(true);
	leMasterImageTitle->setAlignment(Qt::AlignCenter);
	leMasterImageTitle->setText(LangSolver.GetString(DockMasterWhole_LS,LID_446)/*"Master Whole Image"*/);
	setTitleBarWidget(leMasterImageTitle);
}

DockMasterWhole::~DockMasterWhole()
{
}

void DockMasterWhole::SetTitle(bool Enabled)
{
	if(Enabled){
		leMasterImageTitle=new QLineEdit();
		leMasterImageTitle->setReadOnly(true);
		leMasterImageTitle->setAlignment(Qt::AlignCenter);
		leMasterImageTitle->setText(LangSolver.GetString(DockMasterWhole_LS,LID_447)/*"Master Whole Image"*/);
		setTitleBarWidget(leMasterImageTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leMasterImageTitle;
		setWindowTitle(LangSolver.GetString(DockMasterWhole_LS,LID_448)/*"Master Whole Image"*/);
	}
}
