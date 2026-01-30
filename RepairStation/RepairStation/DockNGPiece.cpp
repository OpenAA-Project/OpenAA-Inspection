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
#include "DockNGPiece.h"

DockNGPiece::DockNGPiece(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leNGInspectionPixTitle=new QLineEdit();
	LangSolver.SetUI(this);

	leNGInspectionPixTitle->setReadOnly(true);
	leNGInspectionPixTitle->setAlignment(Qt::AlignCenter);
	leNGInspectionPixTitle->setText(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
	setTitleBarWidget(leNGInspectionPixTitle);
}

DockNGPiece::~DockNGPiece()
{
}

void DockNGPiece::SetTitle(bool Enabled)
{
	if(Enabled){
		leNGInspectionPixTitle=new QLineEdit();
		leNGInspectionPixTitle->setReadOnly(true);
		leNGInspectionPixTitle->setAlignment(Qt::AlignCenter);
		leNGInspectionPixTitle->setText(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
		setTitleBarWidget(leNGInspectionPixTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leNGInspectionPixTitle;
		setWindowTitle(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
	}
}