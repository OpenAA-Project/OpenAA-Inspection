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


#ifndef BRIGHTHISTOGRAMFORM_H
#define BRIGHTHISTOGRAMFORM_H

#include <QDialog>
#include "ui_BrightHistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XServiceForLayers.h"

class	AlignmentFlexAreaImagePanel;

class BrightHistogramForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	BrightHistogramForm(FlexArea &area ,AlignmentFlexAreaImagePanel *parentPanel ,int pickupL,int pickupH,LayersBase *base ,QWidget *parent);
	~BrightHistogramForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	AlignmentFlexAreaImagePanel					*ParentPanel;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect(int PickupL ,int PickupH);

private:
	Ui::BrightHistogramFormClass ui;

	int	MaxY;

private slots:
	void on_ButtonClose_clicked();
	void on_ButtonReflect_clicked();
	void on_EditPickupH_valueChanged(int);
	void on_EditPickupL_valueChanged(int);
	void	SlotLineGraphDClick(int ,int );
};


#endif // BRIGHTHISTOGRAMFORM_H