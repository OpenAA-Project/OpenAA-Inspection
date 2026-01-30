/*
 * Copyright (C) 2024
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

#ifndef SETTINGREVERSELENS_H
#define SETTINGREVERSELENS_H

#include <QDialog>
#include "ui_SettingReverseLens.h"
#include "XServiceForLayers.h"

class SettingReverseLens : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingReverseLens(LayersBase *base
						,double _Strength ,double _Width
						,int32 StartX,int32 EndX
						, QWidget *parent = 0);
	~SettingReverseLens();

	double Strength ,Width;
	int32	StartX;
	int32	EndX;
private:
	Ui::SettingReverseLensClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGREVERSELENS_H