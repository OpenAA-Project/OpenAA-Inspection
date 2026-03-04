/*
 * Copyright (C) 2021
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

#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "ClosingForm.h"
#include "ui_ClosingForm.h"
#include "XOpenAA.h"

ClosingForm::ClosingForm(const QString &UserPath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClosingForm)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	FileRegistry	FRegistry(::GetUserPath(UserPath)+QDir::separator()+DefaultMachineInfoFileName);
	int	LanguageCode=FRegistry.LoadRegInt(/**/"Language",0);
	switch(LanguageCode){
		case 1:
			ui->label->setText(/**/"On closing...");
			break;
	}
}

ClosingForm::~ClosingForm()
{
    delete ui;
}