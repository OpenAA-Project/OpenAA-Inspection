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

#ifndef SETTINGRESOLUTIONDIALOG_H
#define SETTINGRESOLUTIONDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class SettingResolutionDialog;
}

class SettingResolutionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingResolutionDialog(double _XZoom ,double _YZoom ,int _Cx ,int _Cy
                                    ,LayersBase *Base
                                    ,QWidget *parent = 0);
    ~SettingResolutionDialog();

	double	XZoom;
	double	YZoom;
	int		Cx,Cy;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingResolutionDialog *ui;
};

#endif // SETTINGCOLORSHIFTDIALOG_H