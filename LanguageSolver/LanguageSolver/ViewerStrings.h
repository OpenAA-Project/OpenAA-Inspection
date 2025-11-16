/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\ViewerStrings.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef VIEWERSTRINGS_H
#define VIEWERSTRINGS_H

#include <QDialog>
#include "ui_ViewerStrings.h"
#include "XLanguageSolver.h"
#include "XLSProject.h"

class ViewerStrings : public QDialog
{
	Q_OBJECT

	LanguageStocker *CurrentLanguageStocker;
public:
	ViewerStrings(LanguageStocker &_CurrentLanguageStocker,QWidget *parent);
	~ViewerStrings();

private:
	Ui::ViewerStringsClass ui;

private slots:
	void on_pushButton_clicked();
};

#endif // VIEWERSTRINGS_H
