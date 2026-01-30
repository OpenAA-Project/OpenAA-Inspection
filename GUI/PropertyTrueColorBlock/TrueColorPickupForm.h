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


#ifndef TRUECOLORPICKUPFORM_H
#define TRUECOLORPICKUPFORM_H

#include <QDialog>
#include "ui_TrueColorPickupForm.h"
#include "XFlexArea.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	TrueColorBlockImagePanel;

class TrueColorPickupForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	TrueColorPickupForm(LayersBase *Base
						,RGBStock *Stocker
						,ColorLogic *ArgLogic
						,QWidget *parent);
	~TrueColorPickupForm();
	ShowRGBSpace		ColorPanel;
	SelectColorSample	ColorSamples;
private:
	Ui::TrueColorPickupFormClass ui;

private slots:
	void on_pushButtonClearEliminateColor_clicked();
	void on_pushButtonClearBaseColor_clicked();
	void on_pushButtonClearColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonSetToColor_clicked();
	void on_pushButtonClose_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // TRUECOLORPICKUPFORM_H