#include "xmlserver_if.h"

XMLServer_IF::XMLServer_IF(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnExit,SIGNAL(clicked()),this,SLOT(exitApp()));
	connect(ui.btnConnect,SIGNAL(clicked()),this,SLOT(connectSvr()));
	connect(ui.btnStatus,SIGNAL(clicked()),this,SLOT(chkStats()));
	connect(ui.btnDisConnect,SIGNAL(clicked()),this,SLOT(disConnectSvr()));
	connect(ui.btnSelect,SIGNAL(clicked()),this,SLOT(selectXML()));
	connect(ui.btnFirst,SIGNAL(clicked()),this,SLOT(firstXML()));
	connect(ui.btnNext,SIGNAL(clicked()),this,SLOT(nextXML()));

	connect(ui.btnAdd,SIGNAL(clicked()),this,SLOT(addXML()));
	connect(ui.btnAppend,SIGNAL(clicked()),this,SLOT(appendXML()));

	connect(ui.btnUpdate,SIGNAL(clicked()),this,SLOT(updXML()));
	connect(ui.btnDelete,SIGNAL(clicked()),this,SLOT(delXML()));

	showMess("DisConnect");
	handle = NULL;

	QString tmp = "";
	tmp = "<IST DAY=\"100412095642\" NGJ=\"NGImage/080312-09/5642-*.jdt\" MAC=\"0\">";
	tmp += "<TIM>08/03/12 09:56:42</TIM>";
	tmp += "<VSN>2007.3.31A</VSN>";
	tmp += "<MNM MID=\"10\">data01-B</MNM>";
	tmp += "<INSPECT EID=\"1\"></INSPECT>";
	tmp += "<LOT LID=\"17\">17</LOT>";
	tmp += "</IST> FROM PPP";
	ui.txtAddSql->setPlainText(tmp);

	tmp = "<IST>";
	tmp += "<NGP X=\"1485\" Y=\"2750\" MX=\"36\" MY=\"36\" HX=\"8\" HY=\"16\" RS1=\"533\" RS2=\"3452816845\" ";
	tmp += "RAL=\"Basic:ColorBlockInspection\" PG=\"1\" LY=\"0\"></NGP>";
	tmp += "</IST> FROM PPP ";
	tmp += "WHERE <IST MID='10' MAC='0' DAY='100412095642' />";
	ui.txtAppendSql->setPlainText(tmp);
}

XMLServer_IF::~XMLServer_IF()
{

}

void XMLServer_IF::exitApp() {
	close();
}

void XMLServer_IF::showMess(QString mess) {
	ui.statusBar->setText(mess);
}

void XMLServer_IF::connectSvr() {
	showMess("");
	handle = XML_Connect(ui.txtSvr->text(),ui.spnPort->value(),ui.spnWaitTime->value());
	if ( handle == NULL ) {
		showMess("Connect Error");
		return;
	}
	showMess("Connected port:"+handle->getPort());
}

void XMLServer_IF::chkStats() {
	showMess("");
	if ( handle == NULL ) {
		return;
	}
	bool ret;
	if ( XML_GetState(handle,ret) == false ) {
		showMess("GetState Error:"+handle->errorMess());
		return;
	}
	if ( ret == false ) {
		showMess("GetState return false");
	} else {
		showMess("GetState return true");
	}
}

void XMLServer_IF::disConnectSvr() {
	showMess("");
	if ( handle == NULL ) {
		return;
	}
	if ( XML_Close(handle) == false ) {
		showMess("Close Error:"+handle->errorMess());
		return;
	}
	showMess("DisConnect");
}

void XMLServer_IF::selectXML() {
	showMess("");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}
	QString sql = ui.txtSelect->toPlainText();
	QStringList lst;
	lst.clear();
	if ( XML_Select(handle,sql,lst) == false ) {
		showMess("Select Error:"+handle->errorMess());
		return;
	}
	QString buf = "";
	for( int i=0; i<lst.size(); i++ ) {
		if ( buf != ""  ) buf += "\n";
		buf += lst.at(i);
	}
	ui.txtResult->setPlainText(buf);
	showMess("Select End");
}

void XMLServer_IF::firstXML() {
	showMess("");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}
	QString sql = ui.txtSelect->toPlainText();
	QString buf;
	if ( XML_SelectFirst(handle,sql,buf) == false ) {
		showMess("Select Error:"+handle->errorMess());
		return;
	}
	ui.txtResult->setPlainText(buf);
	showMess("First End");
}

void XMLServer_IF::nextXML() {
	showMess("");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}
	QString sql = ui.txtSelect->toPlainText();
	QString buf;
	if ( XML_SelectNext(handle,buf) == false ) {
		showMess("Select Error:"+handle->errorMess());
		return;
	}
	ui.txtResult->setPlainText(buf);
	showMess("Next End");
}

void XMLServer_IF::addXML() {
	showMess("addXML start");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}
	QString sql = ui.txtAddSql->toPlainText();
	if ( XML_Insert(handle,sql) == false ) {
		showMess("addXML Error:"+handle->errorMess());
		return;
	}
	showMess("addXML End");
}

void XMLServer_IF::appendXML() {
	showMess("appendXML start");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}
	QString sql = ui.txtAppendSql->toPlainText();
	if ( XML_Append(handle,sql) == false ) {
		showMess("appendXML Error:"+handle->errorMess());
		return;
	}
	showMess("appendXML End");
}

void XMLServer_IF::updXML() {
	showMess("updateXML start");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}

	QString sql = ui.txtUpdSql->toPlainText();
	if ( XML_Update(handle,sql) == false ) {
		showMess("updateXML Error:"+handle->errorMess());
		return;
	}
	showMess("updateXML End");
}

void XMLServer_IF::delXML() {
	showMess("deleteXML start");
	if ( handle == NULL ) {
		showMess("Not Connect");
		return;
	}

	QString sql = ui.txtUpdSql->toPlainText();
	if ( XML_Delete(handle,sql) == false ) {
		showMess("deleteXML Error:"+handle->errorMess());
		return;
	}
	showMess("deleteXML End");
}
