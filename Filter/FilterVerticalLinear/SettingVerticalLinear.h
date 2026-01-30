/*
 * Copyright (C) 2017
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

#ifndef SETTINGVERTICALLINEAR_H
#define SETTINGVERTICALLINEAR_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingVerticalLinear;
}

class SettingVerticalLinear : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingVerticalLinear(LayersBase *base
										,double _Strength 
										, bool _WholeImage
										, bool	_TopSide   ,bool _BottomSide
										,BoolList &_Layers
										,double	Gamma
										, QWidget *parent = 0);
    ~SettingVerticalLinear();

	BoolList	Layers;
	double	Strength;
	bool	WholeImage;
	bool	TopSide;
	bool	BottomSide;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingVerticalLinear *ui;
};

#endif // SETTINGVERTICALLINEAR_H