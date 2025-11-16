/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\TrueColorPickupForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef TRUECOLORPICKUPFORM_H
#define TRUECOLORPICKUPFORM_H

#include <QDialog>
#include "ui_TrueColorPickupForm.h"
#include "XFlexArea.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	TrueColorBlockImagePanel;

class TrueColorPickupForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	TrueColorPickupForm(LayersBase *Base
						,RGBStock *Stocker
						,ColorLogic *ArgLogic
						,QWidget *parent);
	~TrueColorPickupForm();
	ShowRGBSpace		ColorPanel;
	SelectColorSample	ColorSamples;
private:
	Ui::TrueColorPickupFormClass ui;

private slots:
	void on_pushButtonClearEliminateColor_clicked();
	void on_pushButtonClearBaseColor_clicked();
	void on_pushButtonClearColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonSetToColor_clicked();
	void on_pushButtonClose_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // TRUECOLORPICKUPFORM_H
