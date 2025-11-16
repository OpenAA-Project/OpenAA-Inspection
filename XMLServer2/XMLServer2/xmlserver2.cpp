#include "xmlserver2.h"
#include "clsParam.h"
#include <QDebug>

#include <crtdbg.h>
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

XMLServer2::XMLServer2(QWidget *parent) :
	QWidget(parent) {
	ui.setupUi(this);
	connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(exitApp()));
	connect(ui.btnPrm, SIGNAL(clicked()),this,SLOT(popParam()));

	objSvr = new clsTcpSvr(this);
	connect(objSvr, SIGNAL(drawRequest(int,QString,QString)), this,
			SLOT(drawRequest(int,QString,QString)), Qt::QueuedConnection);
}

XMLServer2::~XMLServer2() {

}

void XMLServer2::exitApp() {
	//_CrtDumpMemoryLeaks();
	close();
}

void XMLServer2::popParam() {
	clsParam *objPrm = new clsParam();
	objPrm->exec();
}

void XMLServer2::drawRequest(int port, QString svr, QString sts) {
	int nRow = ui.tableWidget->rowCount();
	if (nRow <= 0) {
		addRow(port, svr, sts);
		return;
	}
	for (int i = 0; i < nRow; i++) {
		int nPort = ui.tableWidget->item(i, 2)->text().toInt();
		if (nPort == port) {
			ui.tableWidget->item(i, 1)->setText(svr); // 20100427
			ui.tableWidget->item(i, 3)->setText(sts);
			return;
		}
	}
	addRow(port, svr, sts);
}

void XMLServer2::addRow(int port, QString svr, QString sts) {
	int nRow = ui.tableWidget->rowCount();
	ui.tableWidget->setRowCount(nRow + 1);

	QTableWidgetItem *itm = ui.tableWidget->item(nRow, 0);
	if (itm == NULL) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow, 0, itm);
	}
	itm->setText(QString::number(nRow + 1));

	itm = ui.tableWidget->item(nRow, 1);
	if (itm == NULL) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow, 1, itm);
	}
	itm->setText(svr);

	itm = ui.tableWidget->item(nRow, 2);
	if (itm == NULL) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow, 2, itm);
	}
	itm->setText(QString::number(port));

	itm = ui.tableWidget->item(nRow, 3);
	if (itm == NULL) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow, 3, itm);
	}
	itm->setText(sts);
}

void XMLServer2::drawRowMstId(int port, const QByteArray &MstId) {
	int nRow = ui.tableWidget->rowCount();
	for( int i=0; i<nRow; i++ ) {
		if ( ui.tableWidget->item(i,2)->text().toInt() == port ) {
			QTableWidgetItem *itm = ui.tableWidget->item(i,4);
			if ( itm == NULL ) {
				itm = new QTableWidgetItem();
				ui.tableWidget->setItem(i, 4, itm);
			}
			itm->setText(MstId);
			break;
		}
	}
}
