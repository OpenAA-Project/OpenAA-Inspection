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

#include "ui_CameraSettingForm.h"

class CameraSettingForm : public QDialog
{
	Q_OBJECT

public:
	CameraSettingForm(int *r, int *g, int *b, QWidget *parent=NULL);

public:
	int getRed();
	int getGreen();
	int getBlue();
	void ResetRGB(int *r, int *g, int *b);

public slots:
	void setRed(int value);
	void setGreen(int value);
	void setBlue(int value);
	void cancel();
	void ok();

private:
	Ui::CameraSettingClass ui;
	int *cur_red, *cur_green, *cur_blue;
	int old_red, old_green, old_blue;
};