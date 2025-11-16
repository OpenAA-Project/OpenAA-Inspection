/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\GenerateMaskFromSameColorForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERATEMASKFROMSAMECOLORFORM_H
#define GENERATEMASKFROMSAMECOLORFORM_H

#include <QDialog>
#include "ui_GenerateMaskFromSameColorForm.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"
#include "ShowRGBSamples.h"


class GenerateMaskFromSameColorForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	GenerateMaskFromSameColorForm(LayersBase *Base,QWidget *parent);
	~GenerateMaskFromSameColorForm();

	ColorLogic	PouredColor;
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int		MinPickupSize;
	int		MaxPickupSize;
	int		MinPickupDots;
	int		MaxPickupDots;
	int		Erosion;

private:
	Ui::GenerateMaskFromSameColorFormClass ui;

	ShowRGBSpace		ColorThre;
	SelectColorSample	ColorSamples;
	ShowRGBSamples		RGBPanel;
	QColor PickupColor;
	mtColorFrame	PickupColorFrame;

	void ShowThresholdList(void);
	void GetParamFromWindow(void);
	void SetParamToWindow(void);

private slots:
	void on_pushButtonLimited_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonNonEffective_clicked();
	void on_pushButtonEffective_clicked();
	void on_pushButton_clicked();
	void on_listWidgetEliminatedColor_doubleClicked(QModelIndex);
	void on_listWidgetBaseColor_doubleClicked(QModelIndex);
	void on_pushButtonEliminateColorArea_clicked();
	void on_pushButtonAddColorArea_clicked();
	void on_pushButtonSubPickupColor_clicked();
	void on_pushButtonAddPickupColor_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
};

#endif // GENERATEMASKFROMSAMECOLORFORM_H
