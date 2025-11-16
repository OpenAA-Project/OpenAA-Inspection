/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\DockMasterWhole1.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "DockMasterWhole1.h"

DockMasterWhole1::DockMasterWhole1(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leMasterImage1Title=new QLineEdit();
	LangSolver.SetUI(this);

	leMasterImage1Title->setReadOnly(true);
	leMasterImage1Title->setAlignment(Qt::AlignCenter);
	leMasterImage1Title->setText(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
	setTitleBarWidget(leMasterImage1Title);
}

DockMasterWhole1::~DockMasterWhole1()
{
}

void DockMasterWhole1::SetTitle(bool Enabled)
{
	if(Enabled){
		leMasterImage1Title=new QLineEdit();
		leMasterImage1Title->setReadOnly(true);
		leMasterImage1Title->setAlignment(Qt::AlignCenter);
		leMasterImage1Title->setText(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
		setTitleBarWidget(leMasterImage1Title);
	}
	else{
		setTitleBarWidget(0);
		delete leMasterImage1Title;
		setWindowTitle(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
	}
}
