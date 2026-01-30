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

#ifndef LIGHTDLL2FORM_H
#define LIGHTDLL2FORM_H

#include <QDialog>
#include "ui_LightDLL2Form.h"
#include "LightDLL1.h"
#include "LED64CTRLib.h"
#include "ui_LightDLL1Form.h"

class LightDLL2Form : public QDialog
{
	Q_OBJECT

public:
	LightDLL2Form(LightDLL1 *p, QWidget *parent = 0);
	~LightDLL2Form();

	LightDLL1		BLight;
    int				LEDAutoCount;
    LightDLLBase	*InspectionLight;
    LightDLL1		SavedLight;

private:
	Ui::LightDLL2FormClass ui;

//	LED64ctr	 CLED[LEDBARNUMB];
	QCheckBox	*ChkList[192];
	QLabel		*LabelList[192];
	QCheckBox	*ChkSortList[192];
	QLabel		*LabelSortList[192];

	static	int		BasePort[LEDBARNUMB];

	void SetCheckBox(int First,int End,bool Tog);

private slots:
	void tb_1Toggled			(bool	Tog);
	void tb_2Toggled			(bool	Tog);
	void tbLeft_1Toggled		(bool	Tog);
	void tbLeft_2Toggled		(bool	Tog);
	void tbLeft_3Toggled		(bool	Tog);
	void tbLeft_4Toggled		(bool	Tog);
	void tbLeft_5Toggled		(bool	Tog);
	void tbLeft_6Toggled		(bool	Tog);
	void tbLeft_7Toggled		(bool	Tog);
	void tbLeft_8Toggled		(bool 	Tog);
	void tbOnOffToggled			(bool	Tog);
	void sbBrightnessValueChanged(int	Val);
	void vsBrightnessValueChanged(int	Val);
	void pbTransportClicked		();
	void pbAllSelectClicked		();
	void pbClearSelectClicked	();
	void pbOKClicked			();
	void pbCancelClicked		();
};

#endif // LIGHTDLL2FORM_H