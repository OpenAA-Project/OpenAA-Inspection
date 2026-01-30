/*
 * Copyright (C) 2024
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

#include "CheckEverydayResource.h"
#include "ShowResultForm.h"
#include "ui_ShowResultForm.h"

ShowResultForm::ShowResultForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),
	ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
    ,ui(new Ui::ShowResultForm)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

ShowResultForm::~ShowResultForm()
{
    delete ui;
}

void	ShowResultForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
}

void ShowResultForm::on_pushButtonSet_clicked()
{

}

void ShowResultForm::on_pushButtonClose_clicked()
{

}