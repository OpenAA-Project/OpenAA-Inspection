/*
 * Copyright (C) 2019
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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	mtLineGraph		LGraph;
	mtGStick		GraphBrightness;
public:
	double ThresholdBrightness;
	double ThresholdWidth;

    explicit SettingDialog(double _ThresholdBrightness ,double _ThresholdWidth ,LayersBase *base,QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_doubleSpinBoxThresholdBrightness_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdWidth_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

	void	ShowGraph(void);
};

#endif // SETTINGDIALOG_H