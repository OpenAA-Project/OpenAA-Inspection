/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\PickupColorForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PICKUPCOLORFORM_H
#define PICKUPCOLORFORM_H

#include <QDialog>
#include "ui_PickupColorForm.h"
#include "XServiceForLayers.h"

class PickupColorForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	PickupColorForm(LayersBase *base, QWidget *parent);
	~PickupColorForm();

private:
	Ui::PickupColorFormClass ui;
};

#endif // PICKUPCOLORFORM_H
