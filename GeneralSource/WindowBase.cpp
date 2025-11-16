/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\WindowBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "WindowBase.h"

WindowBase::WindowBase(const QString &title, QWidget *parent)
	: QDockWidget(title,parent)
{
}

WindowBase::~WindowBase()
{
}

bool WindowBase::Save(QIODevice *file)
{
	int W=width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W))
		return false;

	int H=height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H))
		return false;

	return true;
}

bool WindowBase::Load(QIODevice *file)
{
	int W;
	if(file->read((char *)&W,sizeof(W))!=sizeof(W))
		return false;

	int H;
	if(file->read((char *)&H,sizeof(H))!=sizeof(H))
		return false;

	setMinimumSize(W,H);
	setMaximumSize(W,H);

	return true;
}
