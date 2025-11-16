#include "perf1.h"

#include <QTableWidgetItem>
#include <QDebug>

perf1::perf1(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	connect(ui.btnClose,SIGNAL(clicked()),this,SLOT(exitWin()));
	connect(ui.btnStart,SIGNAL(clicked()),this,SLOT(execStart()));

	objThr = NULL;
	nCurCnt = -1;

	ui.tableWidget_2->setRowCount(1);
	QTableWidgetItem *itm = ui.tableWidget_2->item(0,0);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget_2->setItem(0,0,itm);
	}
	itm->setText("0.0");
	itm = ui.tableWidget_2->item(0,1);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget_2->setItem(0,1,itm);
	}
	itm->setText("0.0");
}

perf1::~perf1()
{

}

void perf1::exitWin() {
	if ( objThr != NULL ) {
		while( 1 ) {
			if ( objThr->isRunning() == false ) {
				delete(objThr);
				break;
			} else {
				if ( objThr->wait(500) == false ) {
					continue;
				}
			}
		}
	}
	close();
}

void perf1::execStart() {
	nCurCnt ++;
	objThr = new clsExecIns(ui.spnExecCnt->value(),this);
	objThr->dStartX = ui.tableWidget_2->item(0,0)->text().toDouble();
	objThr->dStartY = ui.tableWidget_2->item(0,1)->text().toDouble();
	connect(objThr,SIGNAL(drawExecAns(double,double,double,double,double,int)),
		this,SLOT(drawExecAns(double,double,double,double,double,int)),Qt::QueuedConnection);
	objThr->start();
}

void perf1::drawExecAns(double dMax,double dMin,double dAvg, double dSum, double dErr,int cnt) {
	ui.tableWidget->setRowCount(nCurCnt+1);
	QTableWidgetItem *itm = ui.tableWidget->item(nCurCnt,0);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nCurCnt,0,itm);
	}
	itm->setText(QString::number(dMax,'f',3));

	itm = ui.tableWidget->item(nCurCnt,1);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nCurCnt,1,itm);
	}
	itm->setText(QString::number(dMin,'f',3));

	itm = ui.tableWidget->item(nCurCnt,2);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nCurCnt,2,itm);
	}
	itm->setText(QString::number(dAvg,'f',3));

	itm = ui.tableWidget->item(nCurCnt,3);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nCurCnt,3,itm);
	}
	qDebug() << "cnt=["+QString::number(dSum,'f',3)+"]";
	itm->setText(QString::number(dSum,'f',3));

	itm = ui.tableWidget->item(nCurCnt,4);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nCurCnt,4,itm);
	}
	qDebug() << "cnt=["+QString::number(cnt)+"]";
	itm->setText(QString::number(cnt));

	itm = ui.tableWidget->item(nCurCnt,5);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nCurCnt,5,itm);
	}
	itm->setText(QString::number(dErr,'f',0));
}
