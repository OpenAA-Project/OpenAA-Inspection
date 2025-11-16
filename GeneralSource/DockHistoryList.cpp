/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\DockHistoryList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "DockHistoryList.h"

#include "PasswordEventOperator.h"

DockHistoryList::DockHistoryList(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);

	leHistoryListTitle=new QLineEdit();
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbChangeLot);
	peo->addButton(ui.pbUpdate);

	//?F?I?Y?e
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leHistoryNumb->setPalette(palette);
	leHistoryListTitle->setReadOnly(true);
	leHistoryListTitle->setAlignment(Qt::AlignCenter);
	leHistoryListTitle->setText(LangSolver.GetString(DockHistoryList_LS,LID_55)/*"History List"*/);
	setTitleBarWidget(leHistoryListTitle);
}

DockHistoryList::~DockHistoryList()
{
}

void DockHistoryList::SetTitle(bool Enabled)
{
	if(Enabled){
		leHistoryListTitle=new QLineEdit();
		leHistoryListTitle->setReadOnly(true);
		leHistoryListTitle->setAlignment(Qt::AlignCenter);
		leHistoryListTitle->setText(LangSolver.GetString(DockHistoryList_LS,LID_55)/*"History List"*/);
		setTitleBarWidget(leHistoryListTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leHistoryListTitle;
		setWindowTitle(LangSolver.GetString(DockHistoryList_LS,LID_55)/*"History List"*/);
	}
}

void DockHistoryList::SetFont(QFont &f)
{
	//Font
//	ui.label				->setFont(QFont("Helvetica",10));
	ui.label				->setFont(f);
	ui.leHistoryNumb		->setFont(f);
	ui.chReverseOrderDisplay->setFont(f);
	ui.pbChangeLot			->setFont(f);
	ui.pbUpdate				->setFont(f);
	leHistoryListTitle		->setFont(f);
}

bool DockHistoryList::Save(QIODevice *file)
{
	//?e?ISave?O???d?A?O
	if(WindowBase::Save(file)==false){
		return false;
	}

	int W,H;
	W=ui.twHistoryList->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=ui.twHistoryList->height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	W=ui.layoutWidget->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=ui.layoutWidget->height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	return true;
}

bool DockHistoryList::Load(QIODevice *file)
{
	//?e?ILoad?O???d?A?O
	if(WindowBase::Load(file)==false){
		return false;
	}

	int W,H;
	if(file->read((char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	if(file->read((char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	ui.twHistoryList->setMinimumSize(W,H);
	ui.twHistoryList->setMaximumSize(W,H);

	if(file->read((char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	if(file->read((char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	ui.layoutWidget->setMinimumSize(W,H);
	ui.layoutWidget->setMaximumSize(W,H);

	return true;
}
