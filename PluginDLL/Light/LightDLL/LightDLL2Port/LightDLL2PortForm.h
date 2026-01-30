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

#ifndef LIGHTDLL2PORTFORM_H
#define LIGHTDLL2PORTFORM_H

#include <QDialog>
#include "ui_LightDLL2PortForm.h"
#include "LightDLL1.h"
#include "LED64CTRLib.h"

class LightDLL2PortForm : public QDialog
{
	Q_OBJECT

public:
	LightDLL2PortForm(LightDLL1	*p,QWidget *parent = 0);
	~LightDLL2PortForm();

	LightDLLBase	*InspectionLight;
	LightDLL1		BLight;
	static	int		BasePort[LEDBARNUMB];

private:
	Ui::LightDLL2PortFormClass ui;

	QCheckBox	*ChkList[2][64];
	QLabel		*LabelList[2][64];

	virtual	void	showEvent (QShowEvent * event)	override;

private slots:
	void on_pushButtonSet_clicked();
	void on_tbLeft_15_clicked();
	void on_tbLeft_14_clicked();
	void on_tbLeft_13_clicked();
	void on_tbLeft_12_clicked();
	void on_tbLeft_11_clicked();
	void on_tbLeft_10_clicked();
	void on_tbLeft_9_clicked();
	void on_tbLeft_0_clicked();
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
	void on_pbClearSelect_clicked();
	void on_pbAllSelect_clicked();
	void on_tbOnOff_clicked();
	void on_pbTransport_clicked();
	void on_sbBrightness_valueChanged(int);
	void on_vsBrightness_valueChanged(int);
	void on_tbLeft_8_clicked();
	void on_tbLeft_7_clicked();
	void on_tbLeft_6_clicked();
	void on_tbLeft_5_clicked();
	void on_tbLeft_4_clicked();
	void on_tbLeft_3_clicked();
	void on_tbLeft_2_clicked();
	void on_tbLeft_1_clicked();
	void on_tb_2_clicked();
	void on_tb_1_clicked();
};

#endif // LIGHTDLL2PORTFORM_H