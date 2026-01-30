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



#ifndef LIGHTDLL1FORM_H
#define LIGHTDLL1FORM_H

#include <QDialog>
#include "LightDLL1.h"
#include "LED64CTRLib.h"
#include "ui_LightDLL1Form.h"

class LightDLL1Form : public QDialog
{
	Q_OBJECT

public:
	LightDLL1Form(LightDLL1	*p, QWidget *parent=0);
	~LightDLL1Form();

	LightDLL1		BLight;
    int				LEDAutoCount;
    LightDLLBase	*InspectionLight;
    LightDLL1		SavedLight;

private slots:
	void tb_1Toggled			(bool	Tog);
	void tb_2Toggled			(bool	Tog);
	void tb_3Toggled			(bool	Tog);
	void tb_4Toggled			(bool	Tog);
	void tb_5Toggled			(bool	Tog);
	void tb_6Toggled			(bool	Tog);
	void tbLeft_1Toggled		(bool	Tog);
	void tbLeft_2Toggled		(bool	Tog);
	void tbLeft_3Toggled		(bool	Tog);
	void tbLeft_4Toggled		(bool	Tog);
	void tbLeft_5Toggled		(bool	Tog);
	void tbLeft_6Toggled		(bool	Tog);
	void tbLeft_7Toggled		(bool	Tog);
	void tbLeft_8Toggled		(bool 	Tog);
	void tbRight_1Toggled		(bool	Tog);
	void tbRight_2Toggled		(bool	Tog);
	void tbRight_3Toggled		(bool	Tog);
	void tbRight_4Toggled		(bool	Tog);
	void tbRight_5Toggled		(bool	Tog);
	void tbRight_6Toggled		(bool	Tog);
	void tbRight_7Toggled		(bool	Tog);
	void tbRight_8Toggled		(bool	Tog);
	void tbLeftToggled			(bool	Tog);
	void tbRightToggled			(bool	Tog);
	void tbOnOffToggled			(bool	Tog);
	void sbBrightnessValueChanged(int	Val);
	void vsBrightnessValueChanged(int	Val);
	void pbTransportClicked		();
	void pbAllSelectClicked		();
	void pbClearSelectClicked	();
	void pbOKClicked			();
	void pbCancelClicked		();

private:
	Ui::LightDLL1FormClass ui;
//	LED64ctr	 CLED[LEDBARNUMB];
	QCheckBox	*ChkList[LEDBARNUMB*LEDsNumb];
	QLabel		*LabelList[LEDBARNUMB*LEDsNumb];
	QCheckBox	*ChkSortList[LEDBARNUMB*LEDsNumb];
	QLabel		*LabelSortList[LEDBARNUMB*LEDsNumb];
/*
	QCheckBox	*ChkList[192];
	QLabel		*LabelList[192];
	QCheckBox	*ChkSortList[192];
	QLabel		*LabelSortList[192];
*/
	void SetCheckBox(int First,int End,bool Tog);
};

#endif // LIGHTDLLFORM_H