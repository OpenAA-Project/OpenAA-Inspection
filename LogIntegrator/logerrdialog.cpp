#include "logerrdialog.h"

LogErrDialog::LogErrDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

LogErrDialog::~LogErrDialog()
{

}

void LogErrDialog::setSuccess(clsLogItemContainer &SuccList) {
	ui.tableWidget_succ->setColumnWidth(0,120);
	ui.tableWidget_succ->setColumnWidth(1,150);
	ui.tableWidget_succ->setColumnWidth(2,50);
	ui.tableWidget_succ->setColumnWidth(3,80);
	ui.tableWidget_succ->setColumnWidth(4,60);
	ui.tableWidget_succ->setColumnWidth(5,150);
//	ui.tableWidget_succ->setColumnWidth(6,100);
	ui.tableWidget_succ->setRowCount(SuccList.GetNumber());
	clsLogItem *cur = SuccList.GetFirst();
	int row = 0;
	while( cur != NULL ) {
		setCellItem(ui.tableWidget_succ,row,0,cur->Hinsyu);
		setCellItem(ui.tableWidget_succ,row,1,cur->LotNo);
		setCellItem(ui.tableWidget_succ,row,2,cur->BaseNo);
		setCellItem(ui.tableWidget_succ,row,3,bindDate(cur->SaveDate));
		setCellItem(ui.tableWidget_succ,row,4,bindTime(cur->SaveTime));
		setCellItem(ui.tableWidget_succ,row,5,cur->HDName);
//		setCellItem(ui.tableWidget_succ,row,6,QString::number(cur->nCnt));
		row++;
		cur = cur->GetNext();
	}
}

void LogErrDialog::setError(clsLogItemContainer &ErrList) {
	ui.tableWidget_err->setColumnWidth(0,120);
	ui.tableWidget_err->setColumnWidth(1,150);
	ui.tableWidget_err->setColumnWidth(2,50);
	ui.tableWidget_err->setColumnWidth(3,80);
	ui.tableWidget_err->setColumnWidth(4,60);
	ui.tableWidget_err->setColumnWidth(5,150);
//	ui.tableWidget_err->setColumnWidth(6,100);
	ui.tableWidget_err->setRowCount(ErrList.GetNumber());
	clsLogItem *cur = ErrList.GetFirst();
	int row = 0;
	while( cur != NULL ) {
		setCellItem(ui.tableWidget_err,row,0,cur->Hinsyu);
		setCellItem(ui.tableWidget_err,row,1,cur->LotNo);
		setCellItem(ui.tableWidget_err,row,2,cur->BaseNo);
		setCellItem(ui.tableWidget_err,row,3,bindDate(cur->SaveDate));
		setCellItem(ui.tableWidget_err,row,4,bindTime(cur->SaveTime));
		setCellItem(ui.tableWidget_err,row,5,cur->HDName);
//		setCellItem(ui.tableWidget_err,row,6,QString::number(cur->nCnt));
		row++;
		cur = cur->GetNext();
	}
}

QString LogErrDialog::bindDate(QString src) {
	QString ret = src.mid(0,4);
	ret += "/"+src.mid(4,2);
	ret += "/"+src.mid(6);
	return ret;
}

QString LogErrDialog::bindTime(QString src) {
	QString ret = src.mid(0,2);
	ret += ":"+src.mid(2,2);
	ret += ":"+src.mid(4,2);
	return ret;
}

void LogErrDialog::ClearLogs(void)
{
	while( ui.tableWidget_err->rowCount() != 0 )
		removeCellItem(ui.tableWidget_err,0);
	while( ui.tableWidget_succ->rowCount() != 0 )
		removeCellItem(ui.tableWidget_succ,0);
}

bool LogErrDialog::IsErrLog(void)
{
	if(ui.tableWidget_err->rowCount()>0){
		return true;
	}
	return false;
}

void LogErrDialog::setCellItem(QTableWidget *tableWidget, int row, int col, QString val) {
	QTableWidgetItem *itm;
	itm = tableWidget->item(row,col);
	if ( itm == NULL ) {
		tableWidget->setItem(row,col,(itm=new QTableWidgetItem()));
		itm->setFlags(Qt::ItemIsEnabled);
	}
	itm->setText(val);
}

void LogErrDialog::removeCellItem(QTableWidget *tableWidget, int row)
{
	QTableWidgetItem *itm;
	for(int col=0; col<tableWidget->columnCount(); col++){
		itm = tableWidget->item(row,col);
		if ( itm != NULL )
			delete itm;
	}
	tableWidget->removeRow(row);
}

void LogErrDialog::on_pushButton_clicked()
{
	accept();
}

void LogErrDialog::on_pbCancel_clicked()
{
	reject();
}
