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

#ifndef SETTINGVERTICALREVERSE_H
#define SETTINGVERTICALREVERSE_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingVerticalReverse;
}

class SettingVerticalReverse : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingVerticalReverse(LayersBase *base
									,double _Strength ,double _Width
									,  bool	_TopSide   ,bool _BottomSide
									,BoolList &_Layers
									,double	Gamma
									,QWidget *parent = 0);
    ~SettingVerticalReverse();

	BoolList	Layers;
	double Strength ,Width;
	bool	TopSide;
	bool	BottomSide;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingVerticalReverse *ui;
};

#endif // SETTINGVERTICALREVERSE_H