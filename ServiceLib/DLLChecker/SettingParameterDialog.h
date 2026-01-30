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

#ifndef SETTINGPARAMETERDIALOG_H
#define SETTINGPARAMETERDIALOG_H

#include <QDialog>
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

class	ParamBase;

namespace Ui {
    class SettingParameterDialog;
}

class SettingParameterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ParamBase			*PBase;
	WEditParameterTab	*WTabGeneral;

public:
    explicit SettingParameterDialog(LayersBase *Base,ParamBase *p, QWidget *parent = 0);
    ~SettingParameterDialog();

private slots:
        void on_pushButtonOk_clicked();

private:
    Ui::SettingParameterDialog *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // SETTINGPARAMETERDIALOG_H