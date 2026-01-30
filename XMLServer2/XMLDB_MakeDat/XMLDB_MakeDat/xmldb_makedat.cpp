/*
 * Copyright (C) 2012
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

#include "xmldb_makedat.h"
#include <QFileDialog>
#include <QMessageBox>

XMLDB_MakeDat::XMLDB_MakeDat(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnMkIst,SIGNAL(clicked()),this,SLOT(addIst()));
	connect(ui.btnExit,SIGNAL(clicked()),this,SLOT(exitWin()));
	connect(ui.btnCreate,SIGNAL(clicked()),this,SLOT(execCreate()));
	connect(ui.btnDbFile,SIGNAL(clicked()),this,SLOT(fileSel()));

	objThr = new clsMakeDat(this);
	connect(objThr,SIGNAL(drawMess(QString)),this,SLOT(showMess(QString)),Qt::QueuedConnection);
	connect(objThr,SIGNAL(updLotID(QString)),this,SLOT(updLotID(QString)),Qt::QueuedConnection);
}

XMLDB_MakeDat::~XMLDB_MakeDat()
{
	if ( objThr != NULL ) {
		delete(objThr);
	}
}

void XMLDB_MakeDat::addIst() {
	objThr->setKeyVal(QString::number(ui.spnLotIt->value()),QString::number(ui.spnEID->value()),ui.txtVer->text(),ui.txtDbFile_2->text());
	if ( objThr->mkData(ui.spnCnt->value(),ui.spnNgCnt->value(),ui.spnNgCnt_2->value()) == false ) {
		return;
	}
	showMess("start:"+QString::number(ui.spnCnt->value()));
}

void XMLDB_MakeDat::exitWin() {

	close();
}

void XMLDB_MakeDat::showMess(QString mess) {
	ui.lblMess->setText(mess);
}

void XMLDB_MakeDat::fileSel() {
	QString tmp = QFileDialog::getSaveFileName(this,tr("dbfile"),tr("please select database file"));
	if ( tmp != "" ) {
		dbFile = tmp;
	}
	ui.txtDbFile->setText(dbFile);
	ui.txtDbFile_2->setText(dbFile);
}

void XMLDB_MakeDat::execCreate() {
	clsDb *db = new clsDb();
	db->setPrm(ui.txtDbFile->text());
	if ( db->createDb(ui.txtDbFile->text()) == false ) {
		QMessageBox::warning(this,tr("createdb"),tr("create db error:")+db->SQLCODE+":"+ui.txtDbFile->text());
	}
}

void XMLDB_MakeDat::updLotID(QString lid) {
	int n = lid.toInt();
	ui.spnLotIt->setValue(n);
}