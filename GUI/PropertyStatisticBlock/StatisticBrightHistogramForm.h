/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticBlock\StatisticBrightHistogramForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef STATISTICBRIGHTHISTOGRAMFORM_H
#define STATISTICBRIGHTHISTOGRAMFORM_H

#include <QDialog>
#include "ui_StatisticBrightHistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

class	StatisticBlockImagePanel;

class StatisticBrightHistogramForm : public QDialog
{
	Q_OBJECT

public:
	StatisticBrightHistogramForm(FlexArea &area ,StatisticBlockImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent);
	~StatisticBrightHistogramForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	StatisticBlockImagePanel		*ParentPanel;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect(int PickupL ,int PickupH);

private:
	Ui::StatisticBrightHistogramFormClass ui;
	int	MaxY;

private slots:
	void on_ButtonReflect_clicked();
	void on_ButtonClose_clicked();
	void on_EditPickupH_valueChanged(int);
	void on_EditPickupL_valueChanged(int);
	void	SlotLineGraphDClick(int ,int );
};

#endif // STATISTICBRIGHTHISTOGRAMFORM_H
