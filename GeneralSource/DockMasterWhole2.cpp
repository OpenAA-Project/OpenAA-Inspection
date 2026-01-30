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
#include "DockMasterWhole2.h"

DockMasterWhole2::DockMasterWhole2(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leMasterImage2Title=new QLineEdit();
	LangSolver.SetUI(this);

	leMasterImage2Title->setReadOnly(true);
	leMasterImage2Title->setAlignment(Qt::AlignCenter);
	leMasterImage2Title->setText(LangSolver.GetString(DockMasterWhole2_LS,LID_57)/*"Master Whole Image"*/);
	setTitleBarWidget(leMasterImage2Title);
}

DockMasterWhole2::~DockMasterWhole2()
{
}

void DockMasterWhole2::SetTitle(bool Enabled)
{
	if(Enabled){
		leMasterImage2Title=new QLineEdit();
		leMasterImage2Title->setReadOnly(true);
		leMasterImage2Title->setAlignment(Qt::AlignCenter);
		leMasterImage2Title->setText(LangSolver.GetString(DockMasterWhole2_LS,LID_57)/*"Master Whole Image"*/);
		setTitleBarWidget(leMasterImage2Title);
	}
	else{
		setTitleBarWidget(0);
		delete leMasterImage2Title;
		setWindowTitle(LangSolver.GetString(DockMasterWhole2_LS,LID_57)/*"Master Whole Image"*/);
	}
}