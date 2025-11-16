/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\StatisticHistogramForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef STATISTICHISTOGRAMFORM_H
#define STATISTICHISTOGRAMFORM_H

#include <QWidget>
#include "ui_StatisticHistogramForm.h"
#include <QToolBar>

#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "mtColorFrame.h"
#include "XPasswordQWidget.h"

class StatisticHistogramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
	Q_OBJECT

public:
	StatisticHistogramForm(LayersBase *Base,QWidget *parent = 0);
	~StatisticHistogramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::StatisticHistogramFormClass ui;

	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraph;
	mtGStick						GraphColMaster;
	mtGStick						GraphColTarget;
	mtGStick						GraphThresh;
	AlgorithmItemIndependentPack	*IData;
	int								YMax;

	double	Avr;
	double	Sigma;

	double	BrightWidthL;		//à√ë§ãPìxïù
	double	BrightWidthH;		//ñæë§ãPìxïù

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);

	mtColorFrame	*MasterPanel;
	mtColorFrame	*TargetPanel;
	mtColorFrame	*ThresholdPanel;

private slots:
	void on_checkUseMorphology_toggled(bool checked);
	void on_EditBrightWidthH_textChanged(const QString &);
	void on_EditBrightWidthL_textChanged(const QString &);
	void on_ButtonCalc_clicked();
	void on_ButtonClose_clicked();
	void on_pushButtonChangeLib_clicked();
	void on_ButtonRelrectSaveParts_clicked();
	void on_ButtonRelrectOnlyBlock_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonReflectAllBlocks_clicked();
	void on_tabWidgetInspect_currentChanged(int);
	void	SlotLineGraphDClick(int X,int Y);
	void	SlotLayerClicked();
};

#endif // STATISTICHistogRAMFORM_H
