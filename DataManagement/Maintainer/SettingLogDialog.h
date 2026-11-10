/*
 * Copyright (C) 2020
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

#ifndef SETTINGLOGDIALOG_H
#define SETTINGLOGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingLogDialog;
}
class Maintainer;

class SettingLogDialog : public QDialog
{
    Q_OBJECT
    Maintainer	*Parent;

public:
    explicit SettingLogDialog(Maintainer *p,QWidget *parent = 0);
    ~SettingLogDialog();
    
private slots:
    void on_pushButtonSelectFile_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingLogDialog *ui;
};

#endif // SETTINGLOGDIALOG_H