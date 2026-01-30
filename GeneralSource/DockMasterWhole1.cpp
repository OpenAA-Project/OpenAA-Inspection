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



#include "RepairStationResource.h"
#include "DockMasterWhole1.h"

DockMasterWhole1::DockMasterWhole1(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leMasterImage1Title=new QLineEdit();
	LangSolver.SetUI(this);

	leMasterImage1Title->setReadOnly(true);
	leMasterImage1Title->setAlignment(Qt::AlignCenter);
	leMasterImage1Title->setText(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
	setTitleBarWidget(leMasterImage1Title);
}

DockMasterWhole1::~DockMasterWhole1()
{
}

void DockMasterWhole1::SetTitle(bool Enabled)
{
	if(Enabled){
		leMasterImage1Title=new QLineEdit();
		leMasterImage1Title->setReadOnly(true);
		leMasterImage1Title->setAlignment(Qt::AlignCenter);
		leMasterImage1Title->setText(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
		setTitleBarWidget(leMasterImage1Title);
	}
	else{
		setTitleBarWidget(0);
		delete leMasterImage1Title;
		setWindowTitle(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
	}
}