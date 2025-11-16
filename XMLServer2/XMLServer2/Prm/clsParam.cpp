#include "clsParam.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>

#include <crtdbg.h>
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsParam::clsParam(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);

	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(closeWin()));
	connect(ui.btnFolder, SIGNAL(clicked()), this, SLOT(selFolder()));
	connect(ui.btnFile, SIGNAL(clicked()), this, SLOT(selDbFile()));
	connect(ui.btnCreate, SIGNAL(clicked()), this, SLOT(createDbFile()));
	connect(ui.btnSave, SIGNAL(clicked()), this, SLOT(saveParam()));

	connect(ui.btnTagAdd,SIGNAL(clicked()),this,SLOT(addTag()));
	connect(ui.btnTagDel,SIGNAL(clicked()),this,SLOT(delTag()));
	connect(ui.tlwTag,SIGNAL(cellClicked(int,int)),this,SLOT(chgTag(int,int)));
	connect(ui.btnAttrAdd,SIGNAL(clicked()),this,SLOT(addAttr()));
	connect(ui.btnAttrDel,SIGNAL(clicked()),this,SLOT(delAttr()));

	connect(ui.btnDbFolder,SIGNAL(clicked()),this,SLOT(selDbFolder()));

	prm = clsParamDef::GetInstance();
	putParam();

	nTagCnt = 1;
	nCurTagRow = 0;
	nAttrCnt = 0;
	nCurAttrRow = 0;
	setInitTag();
}

clsParam::~clsParam() {

}

void clsParam::closeWin() {
	close();
}

void clsParam::getParam() {
	prm->nPort = ui.spnPort->value();
	prm->nTimeOut = ui.spnTimeOut->value();
	prm->logDir = ui.txtLogDir->text();
	prm->logSts = 4 - ui.cmbLogLvl->currentIndex();

	prm->dbFile = ui.txtDbFile->text();
	prm->dbUsr = ui.txtUser->text();
	prm->dbPwd = ui.txtPwd->text();

	prm->dbFolder = ui.txtDbFolder->text();
	prm->nChgDbDay = ui.spnChgDbDay->value();
}

void clsParam::putParam() {
	ui.spnPort->setValue(prm->nPort);
	ui.spnTimeOut->setValue(prm->nTimeOut);
	ui.txtLogDir->setText(prm->logDir);
	ui.cmbLogLvl->setCurrentIndex(4 - prm->logSts);

	ui.txtDbFile->setText(prm->dbFile);
	ui.txtUser->setText(prm->dbUsr);
	ui.txtPwd->setText(prm->dbPwd);

	ui.txtDbFolder->setText(prm->dbFolder);
	ui.spnChgDbDay->setValue(prm->nChgDbDay);
}

void clsParam::selFolder() {
	QString tmp = QFileDialog::getExistingDirectory(this, tr("Log Directory"),
			ui.txtLogDir->text(), QFileDialog::ShowDirsOnly
					| QFileDialog::DontResolveSymlinks);
	if (!tmp.isEmpty()) {
		ui.txtLogDir->setText(tmp);
	}
}

void clsParam::selDbFile() {
	QString tmp = QFileDialog::getSaveFileName(this, tr("DbFile"),
			"/home/firebird", tr("FDB(*.fdb)"));
	if (!tmp.isEmpty()) {
		ui.txtDbFile->setText(tmp);
	}
}

void clsParam::createDbFile() {
	if (ui.txtDbFile->text().isEmpty() == true) {
		return;
	}
	if (clsDb::createDb(ui.txtUser->text(), ui.txtPwd->text(),
			ui.txtDbFile->text()) == false) {
		QMessageBox::warning(this, tr("create db error"), ui.txtDbFile->text()
				+ " create error");
		return;
	}
	clsDb *db = new clsDb();
	db->connNam = "makedb";
	clsLog *log = new clsLog();
	log->startLog("makedb");
	db->log = log;
	db->setPrm(QString("QIBASE"), QString("localhost"), ui.txtDbFile->text(), ui.txtUser->text(),
			ui.txtPwd->text());
	if (db->Connect() == false) {
		QMessageBox::warning(this, tr("create db connect error"),
				ui.txtDbFile->text() + " connect error:" + db->mess);
		return;
	}
	if (db->mkMasterTbl() == false) {
		QMessageBox::warning(this, tr("create db connect error"),
				ui.txtDbFile->text() + " connect error:" + db->mess);
		return;
	}
	db->DisConnect();
	delete (db);
	delete (log);
	QMessageBox::information(this, tr("create db"), ui.txtDbFile->text()
			+ "create success");
}

void clsParam::saveParam() {
	getParam();
	prm->saveParam();
}

void clsParam::setInitTag() {
	if (prm->lstTag.size() == 0) {
		nTagCnt = 1;
		nCurTagRow = 0;
		ui.tlwTag->setRowCount(nTagCnt);
		return;
	}
	nTagCnt = prm->lstTag.size();
	ui.tlwTag->setRowCount(nTagCnt);
	for (int i = 0; i < prm->lstTag.size(); i++) {
		QTableWidgetItem *itm = ui.tlwTag->item(i, 0);
		if (itm == NULL) {
			itm = new QTableWidgetItem();
			ui.tlwTag->setItem(i, 0, itm);
		}
		itm->setText(prm->lstTag.at(i)->tag);
		itm = ui.tlwTag->item(i, 1);
		if (itm == NULL) {
			itm = new QTableWidgetItem();
			ui.tlwTag->setItem(i, 1, itm);
		}
		itm->setText(QString::number(prm->lstTag.at(i)->arrItm.size()));
	}
   setTagAttr(nCurTagRow);
}

void clsParam::addTag() {
	nTagCnt ++;
	ui.tlwTag->setRowCount(nTagCnt);
}

void clsParam::delTag() {
	ui.tlwTag->removeRow(nCurTagRow);
	nTagCnt = ui.tlwTag->rowCount();
}

void clsParam::chgTag(int row, int /*col*/ ) {
	clsTagAttrRec *rec = prm->lstTag.at(nCurTagRow);
	rec->arrItm.clear();
	rec->arrTblCol.clear();
	for( int i=0; i<ui.tlwAttr->rowCount(); i++ ) {
		rec->arrItm.append(ui.tlwAttr->item(i,1)->text());
		rec->arrTblCol.append(ui.tlwAttr->item(i,2)->text());
	}

	nCurTagRow = row;
	setTagAttr(nCurTagRow);
}

void clsParam::setTagAttr(int row) {
	qDebug() << "tag row=["+QString::number(row)+"]";
	if ( row >= prm->lstTag.size() || row < 0 ) return;
	clsTagAttrRec *rec = prm->lstTag.at(row);
	if ( rec == NULL ) return;
	nAttrCnt = rec->arrItm.size();
	ui.tlwAttr->clearContents();
	ui.tlwAttr->setRowCount(nAttrCnt);
	for( int i=0; i<nAttrCnt; i++ ) {
		QTableWidgetItem *itm = ui.tlwAttr->item(i, 0);
		if (itm == NULL) {
			itm = new QTableWidgetItem();
			ui.tlwAttr->setItem(i, 0, itm);
		}
		itm->setText(QString::number(i+1));
		itm = ui.tlwAttr->item(i, 1);
		if (itm == NULL) {
			itm = new QTableWidgetItem();
			ui.tlwAttr->setItem(i, 1, itm);
		}
		itm->setText(rec->arrItm.at(i));
		itm = ui.tlwAttr->item(i, 2);
		if (itm == NULL) {
			itm = new QTableWidgetItem();
			ui.tlwAttr->setItem(i, 2, itm);
		}
		itm->setText(rec->arrTblCol.at(i));
	}
	nCurAttrRow = 0;
}

void clsParam::addAttr() {
	nAttrCnt ++;
	ui.tlwAttr->setRowCount(nAttrCnt);
}

void clsParam::delAttr() {
	ui.tlwAttr->removeRow(nCurAttrRow);
	nAttrCnt = ui.tlwAttr->rowCount();
}

void clsParam::selDbFolder() {
	QString tmp = QFileDialog::getExistingDirectory(this, tr("Database Directory"),
			ui.txtDbFolder->text(), QFileDialog::ShowDirsOnly
					| QFileDialog::DontResolveSymlinks);
	if (!tmp.isEmpty()) {
		ui.txtDbFolder->setText(tmp);
	}
}
