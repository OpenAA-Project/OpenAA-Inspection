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

#ifndef SETTINGCAMERADIALOG_H
#define SETTINGCAMERADIALOG_H

#include <QDialog>
#include "XCameraCommon.h"

namespace Ui {
class SettingCameraDialog;
}
class	CLHS_PX8Setting;
class	featureCtrl;

class SettingCameraDialog : public QDialog
{
    Q_OBJECT

	CLHS_PX8Setting	*Setting;
	featureCtrl		*Feature;

public:
    explicit SettingCameraDialog(CLHS_PX8Setting *s ,featureCtrl *f ,QWidget *parent = nullptr);
    ~SettingCameraDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SettingCameraDialog *ui;
};

#endif // SETTINGCAMERADIALOG_H