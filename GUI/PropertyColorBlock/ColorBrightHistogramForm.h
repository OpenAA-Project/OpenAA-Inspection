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


#ifndef COLORBRIGHTHISTOGRAMFORM_H
#define COLORBRIGHTHISTOGRAMFORM_H

#include <QDialog>
#include "ui_ColorBrightHistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XFlexArea.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"

class	ColorBlockImagePanel;

class ColorBrightHistogramForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ColorBrightHistogramForm(FlexArea &area ,ColorBlockImagePanel *parentPanel 
													,int pickupRL,int pickupRH
													,int pickupGL,int pickupGH
													,int pickupBL,int pickupBH
													,QWidget *parent);
	~ColorBrightHistogramForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThreshR;
	mtGStick						GraphThreshG;
	mtGStick						GraphThreshB;
	FlexArea						GlobalArea;
	ColorBlockImagePanel			*ParentPanel;
	int								PickupRL;
	int								PickupRH;
	int								PickupGL;
	int								PickupGH;
	int								PickupBL;
	int								PickupBH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect( int pickupRL ,int pickupRH
					,int pickupGL ,int pickupGH
					,int pickupBL ,int pickupBH);

private:
	Ui::ColorBrightHistogramFormClass ui;

	mtToolButtonColored	*SelRButton;
	mtToolButtonColored	*SelGButton;
	mtToolButtonColored	*SelBButton;
	int	MaxY;
	int	CurrentColor;

private slots:
	void on_toolButtonL3_clicked();
	void on_toolButtonL2_clicked();
	void on_toolButtonL1_clicked();
	void on_EditPickupBH_valueChanged(int);
	void on_EditPickupBL_valueChanged(int);
	void on_EditPickupGH_valueChanged(int);
	void on_EditPickupGL_valueChanged(int);
	void on_EditPickupRH_valueChanged(int);
	void on_EditPickupRL_valueChanged(int);
	void on_ButtonClose_clicked();
	void on_ButtonReflect_clicked();
	void	SlotLineGraphDClick(int ,int );
};


#endif // COLORBRIGHTHISTOGRAMFORM_H