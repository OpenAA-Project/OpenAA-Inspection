/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\restorepath.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "restorepath.h"
#include "ui_restorepath.h"
#include "datamanagementResource.h"

extern QString Path;
RestorePath::RestorePath(QStringList &PathList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestorePath)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	ui->listWidget->addItems(PathList);
}

RestorePath::~RestorePath()
{
    delete ui;
}

void RestorePath::on_okButton_clicked()
{
	Path=ui->listWidget->currentItem()->text();
	done(true);
}

void RestorePath::on_cancelButton_clicked()
{
	done(false);
}
