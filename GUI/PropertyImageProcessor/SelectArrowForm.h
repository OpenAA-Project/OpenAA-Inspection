/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageProcessor\SelectArrowForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTARROWFORM_H
#define SELECTARROWFORM_H

#include <QWidget>
#include "ui_SelectArrowForm.h"
#include "XServiceForLayers.h"

class SelectArrowForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectArrowForm(LayersBase *base, QWidget *parent = 0);
	~SelectArrowForm();

private:
	Ui::SelectArrowFormClass ui;
};

#endif // SELECTARROWFORM_H
