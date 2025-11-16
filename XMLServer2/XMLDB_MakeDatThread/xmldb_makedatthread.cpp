#include "xmldb_makedatthread.h"

XMLDB_MakeDatThread::XMLDB_MakeDatThread(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnExit,SIGNAL(clicked()),this,SLOT(exitApp()));
	connect(ui.btnMkIst,SIGNAL(clicked()),this,SLOT(execMakeDat()));

	thrMakeDat1 = NULL;
	thrMakeDat2 = NULL;
	nRow1 = 0;
	nRow2 = 0;
}

XMLDB_MakeDatThread::~XMLDB_MakeDatThread()
{

}

void XMLDB_MakeDatThread::exitApp() {
	close();
}

void XMLDB_MakeDatThread::execMakeDat() {
	clearMakeDatObj();
	thrMakeDat1 = new clsMakeDat("1");
	thrMakeDat2 = new clsMakeDat("2");
	connect(thrMakeDat1,SIGNAL(drawMess(QString,bool)),this,SLOT(showMess1(QString,bool)),Qt::QueuedConnection);
	connect(thrMakeDat2,SIGNAL(drawMess(QString,bool)),this,SLOT(showMess2(QString,bool)),Qt::QueuedConnection);

	thrMakeDat1->setKeyVal(QString::number(ui.spnLotIt->value()),QString::number(ui.spnEID->value()),ui.txtVer->text(),ui.txtDbFile_2->text());
	if ( thrMakeDat1->mkData(ui.spnCnt_2->value(),ui.spnNgCnt->value(),ui.spnNgCnt_2->value()) == false ) {
		return;
	}
	qDebug() << "thr(1) Cnt=["+QString::number(ui.spnCnt_2->value())+"]";
	showMess1("start:"+QString::number(ui.spnCnt_2->value()),false);

	thrMakeDat2->setKeyVal(QString::number(ui.spnLotIt->value()+1),QString::number(ui.spnEID->value()),ui.txtVer->text(),ui.txtDbFile_2->text());
	if ( thrMakeDat2->mkData(ui.spnCnt_2->value(),ui.spnNgCnt->value(),ui.spnNgCnt_2->value()) == false ) {
		return;
	}
	qDebug() << "thr(2) Cnt=["+QString::number(ui.spnCnt_2->value())+"]";
	showMess2("start:"+QString::number(ui.spnCnt_2->value()),false);
}

void XMLDB_MakeDatThread::showMess1(QString mess,bool bWait) {
	ui.txtOut_1->setPlainText(mess);
	if ( bWait == true ) {
		if ( thrMakeDat1->isFinished() == false ) {
			for( int i=0; i<10; i++ ) {
				if ( thrMakeDat1->wait(1000) == true ) break;
			}
		}
		ui.tblRes_1->setRowCount(nRow1+1);
		setResRow(nRow1,
				ui.tblRes_1,
				thrMakeDat1->dMax,
				thrMakeDat1->dMin,
				thrMakeDat1->dAvg,
				thrMakeDat1->dCnt,
				thrMakeDat1->dSum
				);
		nRow1++;
	}
}

void XMLDB_MakeDatThread::showMess2(QString mess, bool bWait) {
	ui.txtOut_2->setPlainText(mess);
	if ( bWait == true ) {
		if ( thrMakeDat2->isFinished() == false ) {
			for( int i=0; i<10; i++ ) {
				if ( thrMakeDat2->wait(1000) == true ) break;
			}
		}
		ui.tblRes_2->setRowCount(nRow2+1);
		setResRow(nRow2,
				ui.tblRes_2,
				thrMakeDat2->dMax,
				thrMakeDat2->dMin,
				thrMakeDat2->dAvg,
				thrMakeDat2->dCnt,
				thrMakeDat2->dSum
				);
		nRow2++;
	}
}

void XMLDB_MakeDatThread::setResRow(int nRow, QTableWidget *wid, double dMax, double dMin, double dAvg, double dCnt, double dSum) {
	QTableWidgetItem *itm = wid->item(nRow,0);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		wid->setItem(nRow,0,itm);
	}
	itm->setText(QString::number(dMax,'f',3));

	itm = wid->item(nRow,1);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		wid->setItem(nRow,1,itm);
	}
	itm->setText(QString::number(dMin,'f',3));

	itm = wid->item(nRow,2);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		wid->setItem(nRow,2,itm);
	}
	itm->setText(QString::number(dAvg,'f',3));
qDebug() << "****AVG****=["+QString::number(dAvg,'f',3)+"]**********";
	itm = wid->item(nRow,3);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		wid->setItem(nRow,3,itm);
	}
	qDebug() << "cnt=["+QString::number(dCnt,'f',3)+"]";
	itm->setText(QString::number(dCnt,'f',3));

	itm = wid->item(nRow,4);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		wid->setItem(nRow,4,itm);
	}
	qDebug() << "sum=["+QString::number(dSum,'f',3)+"]";
	itm->setText(QString::number(dSum,'f',3));
}

void XMLDB_MakeDatThread::clearMakeDatObj() {
	if ( thrMakeDat1 != NULL ) {
		delete(thrMakeDat1);
		thrMakeDat1 = NULL;
	}
	if ( thrMakeDat2 != NULL ) {
		delete(thrMakeDat2);
		thrMakeDat2 = NULL;
	}
}
