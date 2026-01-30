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

#ifndef SETTINGPARAMFORM_H
#define SETTINGPARAMFORM_H

#include <QWidget>
#include "WEditParameterTab.h"

namespace Ui {
    class SettingParamForm;
}

class	XMLServerComm;

class SettingParamForm : public QWidget
{
    Q_OBJECT

	XMLServerComm	&SMain;
	WEditParameterTab	*WTabGeneral;

public:
    explicit SettingParamForm(XMLServerComm	&sMain ,QWidget *parent = 0);
    ~SettingParamForm();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::SettingParamForm *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // SETTINGPARAMFORM_H