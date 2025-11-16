/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\progressbar.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "progressbar.h"
#include "ui_progressbar.h"
#include "datamanagementResource.h"

Progressbar::Progressbar(QWidget *parent) :
    QWidget(parent)//,
{
	P.setupUi(this);
	LangSolver.SetUI(this);
	P.progressBar->setRange(0,100);
	//P.progressBar->setRange(0,0);
}

Progressbar::~Progressbar()
{
}
