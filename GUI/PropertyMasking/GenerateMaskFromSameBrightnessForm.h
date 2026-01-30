/*
 * Copyright (C) 2012
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

#ifndef GENERATEMASKFROMSAMEBRIGHTNESSFORM_H
#define GENERATEMASKFROMSAMEBRIGHTNESSFORM_H

#include <QDialog>
#include "ui_GenerateMaskFromSameBrightnessForm.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"


class GenerateMaskFromSameBrightnessForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	GenerateMaskFromSameBrightnessForm(LayersBase *Base,QWidget *parent = 0);
	~GenerateMaskFromSameBrightnessForm();

	int		PickupL;
	int		PickupH;
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int		MinPickupSize;
	int		MaxPickupSize;
	int		MinPickupDots;
	int		MaxPickupDots;
	int		Erosion;

private:
	Ui::GenerateMaskFromSameBrightnessFormClass ui;

	void GetParamFromWindow(void);
	void SetParamToWindow(void);

private slots:
	void on_pushButtonLimited_clicked();
	void on_pushButton_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonNotEffective_clicked();
	void on_ButtonEffective_clicked();
};

#endif // GENERATEMASKFROMSAMEBRIGHTNESSFORM_H