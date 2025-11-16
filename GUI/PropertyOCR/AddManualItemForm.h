/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\AddManualItemForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef ADDMANUALITEMFORM_H
#define ADDMANUALITEMFORM_H

#include <QDialog>
#include "ui_AddManualItemForm.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"

class AddManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddManualItemForm(LayersBase *Base, QWidget *parent);
	~AddManualItemForm();

	void	Initial(void);

	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	ColorLogic	MaskingColor;

	int			Mergin;
	int			EnsmallDot;
	int			EnlargeDot;

private:
	Ui::AddManualItemFormClass ui;

	ShowRGBSpace		ColorMap;
	SelectColorSample	ColorSamples;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_pushButtonSetMergin_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // ADDMANUALITEMFORM_H
