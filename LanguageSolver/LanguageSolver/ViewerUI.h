/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\ViewerUI.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef VIEWERUI_H
#define VIEWERUI_H

#include <QDialog>
#include "ui_ViewerUI.h"
#include "XLanguageSolver.h"
#include "XLSProject.h"

class ViewerUI : public QDialog
{
	Q_OBJECT
	
	LanguageStocker *CurrentLanguageStocker;

public:
	ViewerUI(LanguageStocker &_CurrentLanguageStocker,QWidget *parent);
	~ViewerUI();

private:
	Ui::ViewerUIClass ui;

private slots:
	void on_pushButton_clicked();
};

#endif // VIEWERUI_H
