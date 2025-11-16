/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\DockNGList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "DockNGList.h"

DockNGList::DockNGList(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leNGListTitle=new QLineEdit();
	LangSolver.SetUI(this);

	//mtQWidget?I?z?u
	twNGList=new mtQTableWidget();
//	ui.dwTableList->setWidget(twNGList);
	delete ui.dwTableList;
	ui.splitter->insertWidget(0,twNGList);

	//?F?I?Y?e
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leNGCount->setPalette(palette);
	leNGListTitle->setReadOnly(true);
	leNGListTitle->setAlignment(Qt::AlignCenter);
	leNGListTitle->setText(LangSolver.GetString(DockNGList_LS,LID_58)/*"NG List"*/);
	setTitleBarWidget(leNGListTitle);
}

DockNGList::~DockNGList()
{
}

void DockNGList::SetTitle(bool Enabled)
{
	if(Enabled){
		leNGListTitle=new QLineEdit();
		leNGListTitle->setReadOnly(true);
		leNGListTitle->setAlignment(Qt::AlignCenter);
		leNGListTitle->setText(LangSolver.GetString(DockNGList_LS,LID_58)/*"NG List"*/);
		setTitleBarWidget(leNGListTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leNGListTitle;
		setWindowTitle(LangSolver.GetString(DockNGList_LS,LID_58)/*"NG List"*/);
	}
}

void DockNGList::SetFont(QFont &f)
{
	//Font
//	ui.label				->setFont(QFont("Helvetica",10));
	ui.label				->setFont(f);
	ui.leNGCount			->setFont(f);
	leNGListTitle			->setFont(f);
}

bool DockNGList::Save(QIODevice *file)
{
	//?e?ISave?O???d?A?O
	if(WindowBase::Save(file)==false){
		return false;
	}

	int W,H;
	W=twNGList->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=twNGList->height();
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

bool DockNGList::Load(QIODevice *file)
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

	twNGList->setMinimumSize(W,H);
	twNGList->setMaximumSize(W,H);

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
