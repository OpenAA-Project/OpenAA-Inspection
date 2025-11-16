/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicClassify\PickupColorForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PICKUPCOLORFORM_H
#define PICKUPCOLORFORM_H

#include <QDialog>
#include "ui_PickupColorForm.h"
#include "XFlexArea.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	DynamicClassifyImagePanel;

class PickupColorForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	PickupColorForm(LayersBase *Base
						,RGBStock *Stocker
						,ColorLogic *ArgLogic
						,QWidget *parent = 0);
	~PickupColorForm();

	ShowRGBSpace		ColorPanel;
	SelectColorSample	ColorSamples;
private:
	Ui::PickupColorFormClass ui;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonClearEliminateColor_clicked();
	void on_pushButtonClearBaseColor_clicked();
	void on_pushButtonClearColor_clicked();
	void on_pushButtonSetToColor_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // PICKUPCOLORFORM_H
