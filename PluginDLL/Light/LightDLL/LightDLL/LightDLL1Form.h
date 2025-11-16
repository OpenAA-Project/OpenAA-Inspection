/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Light\LightDLL\LightDLL\LightDLL1Form.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
