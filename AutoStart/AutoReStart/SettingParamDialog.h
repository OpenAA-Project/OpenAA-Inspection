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

#ifndef SETTINGPARAMDIALOG_H
#define SETTINGPARAMDIALOG_H

#include <QDialog>

namespace Ui {
class SettingParamDialog;
}

class AutoReStart;

class SettingParamDialog : public QDialog
{
    Q_OBJECT

    AutoReStart *Parent;
public:
    explicit SettingParamDialog(AutoReStart *p ,QWidget *parent = nullptr);
    ~SettingParamDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSelectFileName_clicked();
    void on_pushButtonSelectPath_clicked();

private:
    Ui::SettingParamDialog *ui;
};

#endif // SETTINGPARAMDIALOG_H