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

#ifndef SETCOLORFORM_H
#define SETCOLORFORM_H

#include <QDialog>
#include "ui_SetColorForm.h"
#include "ShowRGBSamples.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

class	RGBStock;

class SetColorForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	SelectColorSample	RegistPanel;
	ShowRGBSpace		ColorPanel;
public:
	SetColorForm(ColorLogic &data ,LayersBase *Base,QWidget *parent = 0);
	~SetColorForm();

	ColorLogic	Col;
private:
	Ui::SetColorFormClass ui;
	void	SlotSelectCData();
	void	SlotBeforeSave();

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETCOLORFORM_H