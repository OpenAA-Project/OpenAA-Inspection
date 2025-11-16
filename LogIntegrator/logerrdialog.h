#ifndef LOGERRDIALOG_H
#define LOGERRDIALOG_H

#include <QDialog>
#include "ui_logerrdialog.h"
#include "LogIntegrator_pack.h"

class LogErrDialog : public QDialog
{
	Q_OBJECT

public:
	LogErrDialog(QWidget *parent = 0);
	~LogErrDialog();

	void setError(clsLogItemContainer &ErrList);
	void setSuccess(clsLogItemContainer &List);
	void ClearLogs(void);

	bool IsErrLog(void);

private:
	Ui::LogErrDialogClass ui;

	void setCellItem(QTableWidget *tableWidget, int row, int col, QString val);
	void removeCellItem(QTableWidget *tableWidget, int row);
	QString bindDate(QString src);
	QString bindTime(QString src);

private slots:
	void on_pbCancel_clicked();
	void on_pushButton_clicked();
};

#endif // LOGERRDIALOG_H
