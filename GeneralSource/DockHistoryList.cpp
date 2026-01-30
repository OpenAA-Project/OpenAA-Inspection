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
#include "DockHistoryList.h"

#include "PasswordEventOperator.h"

DockHistoryList::DockHistoryList(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);

	leHistoryListTitle=new QLineEdit();
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbChangeLot);
	peo->addButton(ui.pbUpdate);

	//?F?I?Y?e
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leHistoryNumb->setPalette(palette);
	leHistoryListTitle->setReadOnly(true);
	leHistoryListTitle->setAlignment(Qt::AlignCenter);
	leHistoryListTitle->setText(LangSolver.GetString(DockHistoryList_LS,LID_55)/*"History List"*/);
	setTitleBarWidget(leHistoryListTitle);
}

DockHistoryList::~DockHistoryList()
{
}

void DockHistoryList::SetTitle(bool Enabled)
{
	if(Enabled){
		leHistoryListTitle=new QLineEdit();
		leHistoryListTitle->setReadOnly(true);
		leHistoryListTitle->setAlignment(Qt::AlignCenter);
		leHistoryListTitle->setText(LangSolver.GetString(DockHistoryList_LS,LID_55)/*"History List"*/);
		setTitleBarWidget(leHistoryListTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leHistoryListTitle;
		setWindowTitle(LangSolver.GetString(DockHistoryList_LS,LID_55)/*"History List"*/);
	}
}

void DockHistoryList::SetFont(QFont &f)
{
	//Font
//	ui.label				->setFont(QFont("Helvetica",10));
	ui.label				->setFont(f);
	ui.leHistoryNumb		->setFont(f);
	ui.chReverseOrderDisplay->setFont(f);
	ui.pbChangeLot			->setFont(f);
	ui.pbUpdate				->setFont(f);
	leHistoryListTitle		->setFont(f);
}

bool DockHistoryList::Save(QIODevice *file)
{
	//?e?ISave?O???d?A?O
	if(WindowBase::Save(file)==false){
		return false;
	}

	int W,H;
	W=ui.twHistoryList->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=ui.twHistoryList->height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	W=ui.layoutWidget->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=ui.layoutWidget->height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	return true;
}

bool DockHistoryList::Load(QIODevice *file)
{
	//?e?ILoad?O???d?A?O
	if(WindowBase::Load(file)==false){
		return false;
	}

	int W,H;
	if(file->read((char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	if(file->read((char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	ui.twHistoryList->setMinimumSize(W,H);
	ui.twHistoryList->setMaximumSize(W,H);

	if(file->read((char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	if(file->read((char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	ui.layoutWidget->setMinimumSize(W,H);
	ui.layoutWidget->setMaximumSize(W,H);

	return true;
}