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

#ifndef LEARNINGSETTINGDIALOG_H
#define LEARNINGSETTINGDIALOG_H

#include <QDialog>
#include "ui_LearningSettingDialog.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

class LearningSettingDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	LearningSettingDialog(LayersBase *Base,ParamBase *base,QWidget *parent = 0);
	~LearningSettingDialog();

private:
	Ui::LearningSettingDialogClass ui;

	WEditParameterTab	*WTabGeneral;
	ParamBase *Base;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
};

#endif // LEARNINGSETTINGDIALOG_H