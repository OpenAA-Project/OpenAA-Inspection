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

#ifndef SETTINGFILTERHORIZONTALLINEAR_H
#define SETTINGFILTERHORIZONTALLINEAR_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingFilterHorizontalLinear;
}

class SettingFilterHorizontalLinear : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingFilterHorizontalLinear(LayersBase *base
										,double _Strength 
										, bool WholeImage
										, bool	_LeftSide   ,bool _RightSide
										,BoolList &_Layers
										,double	Gamma
										, QWidget *parent = 0);
    ~SettingFilterHorizontalLinear();

	BoolList	Layers;
	double	Strength;
	bool	WholeImage;
	bool	LeftSide;
	bool	RightSide;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_checkBoxWholeImage_clicked();

private:
    Ui::SettingFilterHorizontalLinear *ui;
};

#endif // SETTINGFILTERHORIZONTALLINEAR_H