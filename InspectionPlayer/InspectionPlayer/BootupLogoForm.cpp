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

#include "InspectionPlayerResource.h"
#include "BootupLogoForm.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "XOpenAA.h"

BootupLogoForm::BootupLogoForm(const QString &UserPath,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	FileRegistry	FRegistry(::GetUserPath(UserPath)+QDir::separator()+DefaultMachineInfoFileName);
	int	LanguageCode=FRegistry.LoadRegInt(/**/"Language",0);
	switch(LanguageCode){
		case 1:
			ui.label->setText(/**/"On booting...");
			break;
		case 2:
			ui.label->setText(/**/"正在启动...");
			break;
		case 3:
			ui.label->setText(/**/"正在啟動...");
			break;
		case 4:
			ui.label->setText(/**/"부팅...");
			break;
	}
}

BootupLogoForm::~BootupLogoForm()
{

}