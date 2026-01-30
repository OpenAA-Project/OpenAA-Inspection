/*
 * Copyright (C) 2022
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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_USBStandardCameraExecuter.h"
#include "XUSBCameraExecuter.h"

class USBStandardCameraExecuter : public QMainWindow
{
    Q_OBJECT

	WMFCamera	*Cam[100];
	int	CamCount=0;

public:
    USBStandardCameraExecuter(WMFCamera	*Cam[] ,int	CamCount,QWidget *parent = Q_NULLPTR);

private:
    Ui::USBStandardCameraExecuterClass ui;

private slots:
	void	SlotUpdateSetting(int ID);
};