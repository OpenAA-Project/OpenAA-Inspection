/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\SampleUI.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SAMPLEUI_H
#define SAMPLEUI_H

#include <QWidget>
#include "ui_SampleUI.h"

class SampleUI : public QWidget
{
	Q_OBJECT

public:
	SampleUI(QWidget *parent = 0);
	~SampleUI();

private:
	Ui::SampleUIClass ui;
};

#endif // SAMPLEUI_H
