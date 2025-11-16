/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\DockNGPiece.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RepairStationResource.h"
#include "DockNGPiece.h"

DockNGPiece::DockNGPiece(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leNGInspectionPixTitle=new QLineEdit();
	LangSolver.SetUI(this);

	leNGInspectionPixTitle->setReadOnly(true);
	leNGInspectionPixTitle->setAlignment(Qt::AlignCenter);
	leNGInspectionPixTitle->setText(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
	setTitleBarWidget(leNGInspectionPixTitle);
}

DockNGPiece::~DockNGPiece()
{
}

void DockNGPiece::SetTitle(bool Enabled)
{
	if(Enabled){
		leNGInspectionPixTitle=new QLineEdit();
		leNGInspectionPixTitle->setReadOnly(true);
		leNGInspectionPixTitle->setAlignment(Qt::AlignCenter);
		leNGInspectionPixTitle->setText(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
		setTitleBarWidget(leNGInspectionPixTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leNGInspectionPixTitle;
		setWindowTitle(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
	}
}
