/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectMachine\SelectMachineForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTMACHINEFORM_H
#define SELECTMACHINEFORM_H

#include <QDialog>
#include "ui_SelectMachineForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XServiceForLayers.h"

class	ButtonSelectMachine;

class SelectMachineForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	ButtonSelectMachine	*Parent;
public:
	SelectMachineForm(LayersBase *Base,QWidget *parent);
	~SelectMachineForm();

private slots:
	void pbOKClicked	();
	void pbCancelClicked();

private:
	Ui::SelectMachineFormClass ui;

	LayersBase *LBase;
	QStringList MFieldNames;
};

#endif // SELECTMACHINEFORM_H
