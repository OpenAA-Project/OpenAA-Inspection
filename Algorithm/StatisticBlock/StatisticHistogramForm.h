/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

	double	BrightWidthL;		//�Ñ��P�x��
	double	BrightWidthH;		//�����P�x��

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