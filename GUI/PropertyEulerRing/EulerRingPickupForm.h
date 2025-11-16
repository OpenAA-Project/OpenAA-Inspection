/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\EulerRingPickupForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef EULERRINGPICKUPFORM_H
#define EULERRINGPICKUPFORM_H

#include <QDialog>
#include "ui_EulerRingPickupForm.h"
#include "XFlexArea.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	EulerRingImagePanel;

class EulerRingPickupForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EulerRingPickupForm(LayersBase *Base
						,RGBStock *Stocker
						,QWidget *parent);
	~EulerRingPickupForm();

	ShowRGBSpace		ColorPanel;
	SelectColorSample	ColorSamples;

private:
	Ui::EulerRingPickupFormClass ui;

private slots:
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_pushButtonClose_clicked();
	void on_pushButtonClearEliminateColor_clicked();
	void on_pushButtonClearBaseColor_clicked();
	void on_pushButtonClearColor_clicked();
	void on_pushButtonSetToColor_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // EULERRINGPICKUPFORM_H
