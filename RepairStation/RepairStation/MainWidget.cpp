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
#include "MainWidget.h"

#include "PasswordEventOperator.h"

MainWidget::MainWidget(const QString &title, QWidget *parent)
	: WindowBase(title,parent)
{
	ui.setupUi(this);
//	leMainFrameTitle=new QLineEdit();
	leMainFrameTitle=new QLabel();
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbMasterSelect);
	peo->addButton(ui.pbSearch);

//	ui.pbSearch->setVisible(false);
//	leMainFrameTitle->setReadOnly(true);
	leMainFrameTitle->setAlignment(Qt::AlignCenter);
//	leMainFrameTitle->setMinimumHeight(70);
	setTitleBarWidget(leMainFrameTitle);

	//Color
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leLotName		->setPalette(palette);
	ui.leProductCount	->setPalette(palette);
	ui.leLotCount		->setPalette(palette);
	leMainFrameTitle	->setAutoFillBackground(true);
}

MainWidget::~MainWidget()
{
}

void MainWidget::SetTitle(bool Enabled)
{
	if(Enabled){
//		leMainFrameTitle=new QLineEdit();
		leMainFrameTitle=new QLabel();
//		leMainFrameTitle->setReadOnly(true);
		leMainFrameTitle->setAlignment(Qt::AlignCenter);
		setTitleBarWidget(leMainFrameTitle);
	}
	else{
		setTitleBarWidget(0);
		delete leMainFrameTitle;
//		setWindowTitle(LangSolver.GetString(DockMasterWhole1_LS,LID_56)/*"Master Whole Image"*/);
	}
}

void MainWidget::SetFont(QFont &f)
{
	//Font
//	ui.label				->setFont(QFont("Helvetica",10));
	ui.lbLotName			->setFont(f);
	ui.lbProductCount		->setFont(f);
	ui.lbLotCount			->setFont(f);
	ui.chNGPoint			->setFont(f);
	ui.pbSearch				->setFont(f);
	ui.pbMasterSelect		->setFont(f);
	ui.lbMessage			->setFont(f);
	ui.chShowPieceLine		->setFont(f);

	QFont F=f;
	F.setPointSize(f.pointSize()*1.5);
	ui.leLotName			->setFont(F);
	ui.leProductCount		->setFont(F);
	ui.leLotCount			->setFont(F);
	leMainFrameTitle		->setFont(F);
}

bool MainWidget::Save(QIODevice *file)
{
	//?e?ISave?O????A?O
	if(WindowBase::Save(file)==false){
		return false;
	}

	int W,H;
	W=ui.trMasterList->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=ui.trMasterList->height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	W=ui.twMasterList->width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	H=ui.twMasterList->height();
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

bool MainWidget::Load(QIODevice *file)
{
	//?e?ILoad?O????A?O
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

	ui.trMasterList->setMinimumSize(W,H);
	ui.trMasterList->setMaximumSize(W,H);

	if(file->read((char *)&W,sizeof(W))!=sizeof(W)){
		return false;
	}

	if(file->read((char *)&H,sizeof(H))!=sizeof(H)){
		return false;
	}

	ui.twMasterList->setMinimumSize(W,H);
	ui.twMasterList->setMaximumSize(W,H);

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