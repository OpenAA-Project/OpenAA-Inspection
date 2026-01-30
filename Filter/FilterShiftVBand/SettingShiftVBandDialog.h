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

#ifndef SETTINGSHIFTVBANDDIALOG_H
#define SETTINGSHIFTVBANDDIALOG_H

#include <QDialog>
#include "FilterShiftVBand.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingShiftVBandDialog;
}

class SettingShiftVBandDialog : public QDialog
{
    Q_OBJECT

public:
    VBandInfoContainer  VBands;

    explicit SettingShiftVBandDialog(LayersBase *base
                                    ,VBandInfoContainer &List
                                    ,QWidget *parent = nullptr);
    ~SettingShiftVBandDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonAddLine_clicked();

    void on_pushButtonDelLine_clicked();

private:
    Ui::SettingShiftVBandDialog *ui;
};

#endif // SETTINGSHIFTVBANDDIALOG_H