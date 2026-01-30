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

#ifndef EULERRINGPICKUPFORM_H
#define EULERRINGPICKUPFORM_H

#include <QDialog>
#include "ui_EulerRingPickupForm.h"
#include "XFlexArea.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	EulerRingImagePanel;

class EulerRingPickupForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EulerRingPickupForm(LayersBase *Base
						,RGBStock *Stocker
						,QWidget *parent);
	~EulerRingPickupForm();

	ShowRGBSpace		ColorPanel;
	SelectColorSample	ColorSamples;

private:
	Ui::EulerRingPickupFormClass ui;

private slots:
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_pushButtonClose_clicked();
	void on_pushButtonClearEliminateColor_clicked();
	void on_pushButtonClearBaseColor_clicked();
	void on_pushButtonClearColor_clicked();
	void on_pushButtonSetToColor_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
};

#endif // EULERRINGPICKUPFORM_H