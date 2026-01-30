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

#ifndef SETAREACOLORDIALOG_H
#define SETAREACOLORDIALOG_H

#include <QDialog>
#include "ui_SetAreaColorDialog.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	FlexArea;
class	RGBStock;

class SetAreaColorDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SetAreaColorDialog(RGBStock &PickupColor ,FlexArea &Area
						,LayersBase *Base,QWidget *parent = 0);
	~SetAreaColorDialog();

private:
	Ui::SetAreaColorDialogClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonAdd_clicked();
	void on_pushButtonReplace_clicked();
};

#endif // SETAREACOLORDIALOG_H