#include "xmldb_local.h"

#include <QMessageBox>

XMLDB_Local::XMLDB_Local(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnExit,SIGNAL(clicked()),this,SLOT(exitApp()));
	connect(ui.btnInspect,SIGNAL(clicked()),this,SLOT(selInspect()));
	connect(ui.btnLot,SIGNAL(clicked()),this,SLOT(selLot()));

	objXml = NULL;
	db = NULL;

	nRow = 0;
	clearTime(true);
}

XMLDB_Local::~XMLDB_Local()
{

}

void XMLDB_Local::exitApp() {
	close();
}

void XMLDB_Local::selInspect() {
	cleanObj();
	makeObj();
	clearTime(true);

	int cnt = ui.spnCnt->value();
	int eid = ui.txtEid->text().toInt();
	QString sql = "";

	if ( db->Connect() == false ) {
		messError("connect error","Connect Error:"+db->mess);
		return;
	}
	for( int i=0; i<cnt; i++ ) {
		sql = mkSelectInspectSql(QString::number(eid));

		if ( objXml->lexSelSql(sql) == false ) {
			messError("lexSelSql","SELECT SQL Format Error:"+objXml->errMess);
			db->DisConnect();
			return;
		}

		timeStart();
		if ( objXml->searchXml(1) == false ) {
			if ( objXml->errMess != "not found" ) {
				messError("searchXml","searchXml Error:"+objXml->errMess);
				db->DisConnect();
				return;
			}
		}
		timeEnd();
		calcTime();
		drawRes();
		eid ++;

		if ( objXml->errMess != "not found" ) {
			ui.textEdit->setPlainText(objXml->lstResult.at(0));
		}
	}
	db->DisConnect();

	dAvg = dSum / dCnt;
	drawRes();
	nRow ++;
}

void XMLDB_Local::selLot() {
	cleanObj();
	makeObj();
}

QString XMLDB_Local::mkSelectInspectSql(QString eid) {
	QString ret = "<IST DAY MAC NGJ><TIM /><LOT LID /><INSPECT EID /><NGI */><NGP */></IST> FROM ";
	ret += ui.txtTbl->text();
	ret += " WHERE <LST ><LOT LID='"+ui.txtLot->text()+"'/><INSPECT EID='"+eid+"'/></IST>";
	return ret;
}

void XMLDB_Local::makeObj() {
	objXml = new clsXmlUpd();
	db = new clsDb();

	// TODO
	db->setPrm();
	objXml->db = db;
}

void XMLDB_Local::cleanObj() {
	if ( objXml != NULL ) {
		delete(objXml);
		objXml = NULL;
	}

	if ( db != NULL ) {
		delete(db);
		db = NULL;
	}
}

void XMLDB_Local::messError(QString tit, QString mess) {
	QMessageBox::warning(this,tit,mess);
}

void XMLDB_Local::timeStart() {
	curTim.start();
}

void XMLDB_Local::timeEnd() {
	int n = curTim.elapsed();
	qDebug() << "time =["+QString::number(n)+"]";
	dRes = (double)n/1000.0;
	qDebug() << "dtime=["+QString::number(dRes,'f',3)+"]";

	QFile file("D:\\Data\\XMLServerLog\\seltime.log");
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		qDebug() << "error file";
		return;
	}
	QTextStream out(&file);
	out << QString::number(dRes,'f',3)+"\n";
	file.close();
}

void XMLDB_Local::calcTime() {
	if ( dRes > dMax ) {
		dMax = dRes;
	}
	if ( dRes < dMin ) {
		dMin = dRes;
	}
	dSum += dRes;
	dCnt += 1.0;
}

void XMLDB_Local::clearTime(bool flg) {
	dRes = 0.0;
	if ( flg == true ) {
		dMax = 0.0;
		dMin = 9999.0;
		dAvg = 0.0;
		dErr = 0.0;
		dSum = 0.0;
		dCnt = 0.0;
	}
}

void XMLDB_Local::drawRes() {
	ui.tableWidget->setRowCount(nRow+1);
	QTableWidgetItem *itm = ui.tableWidget->item(nRow,0);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow,0,itm);
	}
	itm->setText(QString::number(dMax,'f',3));

	itm = ui.tableWidget->item(nRow,1);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow,1,itm);
	}
	itm->setText(QString::number(dMin,'f',3));

	itm = ui.tableWidget->item(nRow,2);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow,2,itm);
	}
	itm->setText(QString::number(dAvg,'f',3));

	itm = ui.tableWidget->item(nRow,3);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow,3,itm);
	}
	qDebug() << "cnt=["+QString::number(dCnt,'f',3)+"]";
	itm->setText(QString::number(dCnt,'f',3));

	itm = ui.tableWidget->item(nRow,4);
	if ( itm == NULL ) {
		itm = new QTableWidgetItem();
		ui.tableWidget->setItem(nRow,4,itm);
	}
	qDebug() << "sum=["+QString::number(dSum,'f',3)+"]";
	itm->setText(QString::number(dSum,'f',3));
}
