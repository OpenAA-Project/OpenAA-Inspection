#include "cltSimulator.h"

#include <QTableWidgetItem>
#include "clsLog.h"

cltSimulator::cltSimulator(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnExit,SIGNAL(clicked()),this,SLOT(exitApp()));
	connect(ui.btnStart,SIGNAL(clicked()),this,SLOT(startExec()));

	objMain = new clsMainThread(this);
	connect(objMain,SIGNAL(setTime(int,double)),this,SLOT(setTime(int,double)),Qt::QueuedConnection);
	connect(objMain,SIGNAL(showMess(QString)),this,SLOT(showMess(QString)),Qt::QueuedConnection);
	nResRow = 1;
}

cltSimulator::~cltSimulator()
{

}

void cltSimulator::exitApp() {
	close();
}

void cltSimulator::startExec() {
	//nResRow ++;
	objMain->svr = ui.txtSvr->text();
	objMain->port = ui.spnPort->value();
	objMain->WaitTime = ui.spnWait->value();
	objMain->logDir = ui.txtLogDir->text();
	objMain->nThrCnt = ui.spnThrCnt->value();
	objMain->nLotId = ui.spnLotId->value();
	objMain->nStartEid = ui.spnStartEid->value();
	objMain->nExecCnt = ui.spnExecCnt->value();
	objMain->nNgCnt = ui.spnNgCnt->value();

	ui.tableWidget_2->clearContents();
	ui.tableWidget_2->setRowCount(objMain->nThrCnt);
	objMain->start();
}

void cltSimulator::setTime(int col, double val) {
	ui.tableWidget->setRowCount(nResRow);
	QTableWidgetItem *itm = ui.tableWidget->item(nResRow-1,col);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nResRow-1,col,itm);
	}
	itm->setText(QString::number(val,'f',3));
	if ( col >= 4 ) {
		writeRes();
		nResRow ++;
	}
}

void cltSimulator::setCntThr(int row, int col, double val) {
	QTableWidgetItem *itm = ui.tableWidget_2->item(row,col);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget_2->setItem(row,col,itm);
	}
	itm->setText(QString::number(val,'f',3));
}

void cltSimulator::showMess(QString mess) {
	ui.txtMess->setText(mess);
}

bool cltSimulator::writeRes() {
	return true;
}

