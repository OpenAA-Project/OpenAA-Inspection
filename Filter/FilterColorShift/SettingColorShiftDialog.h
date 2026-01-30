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

#ifndef SETTINGCOLORSHIFTDIALOG_H
#define SETTINGCOLORSHIFTDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingColorShiftDialog;
}

class SettingColorShiftDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingColorShiftDialog(QWidget *parent = 0);
    ~SettingColorShiftDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingColorShiftDialog *ui;
};

#endif // SETTINGCOLORSHIFTDIALOG_H