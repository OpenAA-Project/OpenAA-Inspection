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

#ifndef EULERRINGHISTGRAMFORM_H
#define EULERRINGHISTGRAMFORM_H

#include <QWidget>
#include "ui_EulerRingHistgramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"

class EulerRingHistgramForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	EulerRingHistgramForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent = 0);
	~EulerRingHistgramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private:
	Ui::EulerRingHistgramFormClass ui;
	AlgorithmLibraryListContainer	LibIDList;

	AlgorithmItemIndependentPack	*IData;

	ShowRGBSpace		ColorRaw;
	ShowRGBSpace		ColorThre;
	SelectColorSample	ColorSamples;
	QColor PickupColor;
	mtColorFrame	PickupColorFrame;

	QRgb	CenterBright;
	ColorLogic	InspectionColor;
	ColorLogic	AbsInspectionColor;

	ColorLogic	MasterColor;
	ColorLogic	TargetColor;
	int			CurrentTabIndex;
	double		Multiplier;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	ShowThresholdList(void);

private slots:
	void on_pushButtonChangeLib_clicked();
	void on_ButtonClose_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_ButtonCalc_clicked();
	void on_ButtonRefrectOnlyBlock_clicked();
	void on_pushButtonSubPickupColor_clicked();
	void on_pushButtonAddPickupColor_clicked();
	void on_pushButtonSub_clicked();
	void on_pushButtonAdd_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonReflectAllBlocks_clicked();
	void on_listWidgetEliminatedColor_doubleClicked(QModelIndex);
	void on_listWidgetBaseColor_doubleClicked(QModelIndex);
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
	void	SlotAddEliminated(void);
	void	SlotDelEliminated(void);
};

#endif // EULERRINGHISTGRAMFORM_H