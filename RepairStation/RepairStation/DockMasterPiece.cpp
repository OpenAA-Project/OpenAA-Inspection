/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\DockMasterPiece.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "DockMasterPiece.h"

DockMasterPiece::DockMasterPiece(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leNGMasterPixTitle=new QLineEdit();
	LangSolver.SetUI(this);

	leNGMasterPixTitle->setReadOnly(true);
	leNGMasterPixTitle->setAlignment(Qt::AlignCenter);
	leNGMasterPixTitle->setText(LangSolver.GetString(DockMasterPiece_LS,LID_53)/*"Master Image"*/);
	setTitleBarWidget(leNGMasterPixTitle);
}

DockMasterPiece::~DockMasterPiece()
{
}

void DockMasterPiece::SetTitle(bool Enabled)
{
	if(Enabled){
		leNGMasterPixTitle=new QLineEdit();
		leNGMasterPixTitle->setReadOnly(true);
		leNGMasterPixTitle->setAlignment(Qt::AlignCenter);
		leNGMasterPixTitle->setText(LangSolver.GetString(DockMasterPiece_LS,LID_53)/*"Master Image"*/);
		setTitleBarWidget(leNGMasterPixTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leNGMasterPixTitle;
		setWindowTitle(LangSolver.GetString(DockMasterPiece_LS,LID_53)/*"Master Image"*/);
	}
}
