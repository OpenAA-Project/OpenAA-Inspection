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

#ifndef SETTINGFILTERHORIZONTALBAND_H
#define SETTINGFILTERHORIZONTALBAND_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingFilterHorizontalBand;
}

class SettingFilterHorizontalBand : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingFilterHorizontalBand(LayersBase *base
										,double	Gain
										,int CenterX
										,int BandWidth
										,int GradationWidth
										,BoolList &_Layers
										,double	Gamma
										,QWidget *parent = 0);
    ~SettingFilterHorizontalBand();

	BoolList	Layers;
	double	Gain;
	int		CenterX;
	int		BandWidth;
	int		GradationWidth;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingFilterHorizontalBand *ui;
};

#endif // SETTINGFILTERHORIZONTALBAND_H