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

#ifndef SELECTSETTINGDIALOG_H
#define SELECTSETTINGDIALOG_H

#include <QDialog>
#include "CameraProvider.h"


namespace Ui {
class SelectSettingDialog;
}

class SelectSettingDialog : public QDialog
{
    Q_OBJECT

	CameraProvider	*ParentMain;
	int				Number;
public:
    explicit SelectSettingDialog(CameraProvider *ParentMain,int number ,QWidget *parent = 0);
    ~SelectSettingDialog();

private slots:
    void on_pushButtonSetting_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectSettingDialog *ui;
};

#endif // SELECTSETTINGDIALOG_H