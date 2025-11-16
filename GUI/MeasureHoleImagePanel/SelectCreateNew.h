/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MeasureHoleImagePanel\SelectCreateNew.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SELECTCREATENEW_H
#define SELECTCREATENEW_H

#include <QDialog>
#include "ui_SelectCreateNew.h"

class SelectCreateNew : public QDialog
{
	Q_OBJECT

public:
	SelectCreateNew(QWidget *parent);
	~SelectCreateNew();

private:
	Ui::SelectCreateNewClass ui;

private slots:
	void on_pushButtonGetColorMap_clicked();
	void on_pushButtonCreateNew_clicked();
};

#endif // SELECTCREATENEW_H
