/*
 * Copyright (C) 2015
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

namespace Ui {
class SettingDialog;
}

class	LightCCSControlByPIO2Ch;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	LightCCSControlByPIO2Ch *Panel;

public:
    explicit SettingDialog(LightCCSControlByPIO2Ch *p,QWidget *parent = 0);
    ~SettingDialog();
    
	void	ShowValue(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_toolButtonOnOff1_clicked();
    void on_toolButtonOnOff2_clicked();
    void on_spinBoxBrightness1_valueChanged(int arg1);
    void on_spinBoxBrightness2_valueChanged(int arg1);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H