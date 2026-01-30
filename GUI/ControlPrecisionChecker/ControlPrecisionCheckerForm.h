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

#ifndef CONTROLPRECISIONCHECKERFORM_H
#define CONTROLPRECISIONCHECKERFORM_H

#include "XGUIFormBase.h"
#include "ui_ControlPrecisionCheckerForm.h"
#include "PrecisionCheckerLib.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ControlPrecisionCheckerForm : public GUIFormBase,public PrecisionCheckerLib
{
	Q_OBJECT

public:
	ControlPrecisionCheckerForm(LayersBase *Base ,QWidget *parent = 0);
	~ControlPrecisionCheckerForm();

private:
	Ui::ControlPrecisionCheckerFormClass ui;

private slots:
	void on_comboBoxPage_currentIndexChanged(int index);
	void on_pushButtonAngle_clicked();
	void on_pushButtonResolution_clicked();
	void on_pushButtonBrightness_clicked();
	void on_pushButtonFocus_clicked();
	void on_pushButtonGrp_clicked();
	void on_pushButtonSetParam_clicked();
};

#endif // CONTROLPRECISIONCHECKERFORM_H