/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\DockMasterWhole2.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "DockMasterWhole2.h"

DockMasterWhole2::DockMasterWhole2(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leMasterImage2Title=new QLineEdit();
	LangSolver.SetUI(this);

	leMasterImage2Title->setReadOnly(true);
	leMasterImage2Title->setAlignment(Qt::AlignCenter);
	leMasterImage2Title->setText(LangSolver.GetString(DockMasterWhole2_LS,LID_57)/*"Master Whole Image"*/);
	setTitleBarWidget(leMasterImage2Title);
}

DockMasterWhole2::~DockMasterWhole2()
{
}

void DockMasterWhole2::SetTitle(bool Enabled)
{
	if(Enabled){
		leMasterImage2Title=new QLineEdit();
		leMasterImage2Title->setReadOnly(true);
		leMasterImage2Title->setAlignment(Qt::AlignCenter);
		leMasterImage2Title->setText(LangSolver.GetString(DockMasterWhole2_LS,LID_57)/*"Master Whole Image"*/);
		setTitleBarWidget(leMasterImage2Title);
	}
	else{
		setTitleBarWidget(0);
		delete leMasterImage2Title;
		setWindowTitle(LangSolver.GetString(DockMasterWhole2_LS,LID_57)/*"Master Whole Image"*/);
	}
}
