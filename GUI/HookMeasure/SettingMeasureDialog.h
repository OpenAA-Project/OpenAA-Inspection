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

#ifndef SETTINGMEASUREDIALOG_H
#define SETTINGMEASUREDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingMeasureDialog;
}

class	HookMeasureForm;

class SettingMeasureDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	HookMeasureForm	*Parent;
public:
    explicit SettingMeasureDialog(LayersBase *Base ,HookMeasureForm *P, QWidget *parent = 0);
    ~SettingMeasureDialog();

private slots:
    void on_toolButtonLineColor_clicked();
    void on_toolButtonCircleColor_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingMeasureDialog *ui;
};

#endif // SETTINGMEASUREDIALOG_H