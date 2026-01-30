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