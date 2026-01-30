/*
 * Copyright (C) 2025
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

#include "CartonMenuResource.h"
#include "SettingCartonDialog.h"
#include "ui_SettingCartonDialog.h"
#include "CartonMenuForm.h"
#include "AdjustTriggerForm.h"
#include "WEditParameterTab.h"
#include "LibraryUsageDialog.h"

SettingCartonDialog::SettingCartonDialog(LayersBase *Base,CartonMenuForm *PForm,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),Parent(PForm),
    ui(new Ui::SettingCartonDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	WTabGeneral=new WEditParameterTab(Parent->GetParam(),-1,this);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(width(),height()-40);

}

SettingCartonDialog::~SettingCartonDialog()
{
    delete ui;
}

void SettingCartonDialog::on_pushButtonOK_clicked()
{
	WTabGeneral->LoadFromWindow();
	done(true);
}

void SettingCartonDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingCartonDialog::on_pushButtonTrigger_clicked()
{
	AdjustTriggerForm	*d=new AdjustTriggerForm(Parent);
	d->show();

	WTabGeneral->LoadFromWindow();
	done(true);
}

void SettingCartonDialog::on_pushButtonUsageLibrary_clicked()
{
	LibraryUsageDialog	D(GetLayersBase(),Parent);
	D.exec();
}

void	SettingCartonDialog::AdjustTrigger(void)
{
	AdjustTriggerForm	*d=new AdjustTriggerForm(Parent);
	d->show();

	WTabGeneral->LoadFromWindow();
}