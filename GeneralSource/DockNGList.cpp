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
#include "DockNGList.h"

DockNGList::DockNGList(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
	leNGListTitle=new QLineEdit();
	LangSolver.SetUI(this);

	//mtQWidget?I?z?u
	twNGList=new mtQTableWidget();
//	ui.dwTableList->setWidget(twNGList);
	delete ui.dwTableList;
	ui.splitter->insertWidget(0,twNGList);

	//?F?I?Y?e
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leNGCount->setPalette(palette);
	leNGListTitle->setReadOnly(true);
	leNGListTitle->setAlignment(Qt::AlignCenter);
	leNGListTitle->setText(LangSolver.GetString(DockNGList_LS,LID_58)/*"NG List"*/);
	setTitleBarWidget(leNGListTitle);
}

DockNGList::~DockNGList()
{
}

void DockNGList::SetTitle(bool Enabled)
{
	if(Enabled){
		leNGListTitle=new QLineEdit();
		leNGListTitle->setReadOnly(true);
		leNGListTitle->setAlignment(Qt::AlignCenter);
		leNGListTitle->setText(LangSolver.GetString(DockNGList_LS,LID_58)/*"NG List"*/);
		setTitleBarWidget(leNGListTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leNGListTitle;
		setWindowTitle(LangSolver.GetString(DockNGList_LS,LID_58)/*"NG List"*/);
	}
}

void DockNGList::SetFont(QFont &f)
{
	//Font
//	ui.label				->setFont(QFont("Helvetica",10));
	ui.label				->setFont(f);
	ui.leNGCount			->setFont(f);
	leNGListTitle			->setFont(f);
}

bool DockNGList::Save(QIODevice *file)
{
	//?e?ISave?O???d?A?O
	if(WindowBase::Save(file)==false){
		return false;
	}

	int W,H;
	W=twNGList->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=twNGList->height();
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

bool DockNGList::Load(QIODevice *file)
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

	twNGList->setMinimumSize(W,H);
	twNGList->setMaximumSize(W,H);

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