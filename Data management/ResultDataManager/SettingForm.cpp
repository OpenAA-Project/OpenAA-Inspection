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

#include "ResultDataManagerResource.h"
#include "SettingForm.h"
#include "ui_SettingForm.h"
#include "XDataInLayer.h"

SettingForm::SettingForm(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SettingForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SParam=Param;
	WTabGeneral=new WEditParameterTab(SParam,-1,ui->frame);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(ui->frame->width(),ui->frame->height());
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::showEvent ( QShowEvent * event )
{
	WTabGeneral->ShowToWindow();
}

void SettingForm::on_pushButtonOk_clicked()
{
	WTabGeneral->LoadFromWindow();
	SParam->SaveDefault(GetLayersBase()->GetUserPath());
	close();
}