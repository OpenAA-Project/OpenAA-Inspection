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