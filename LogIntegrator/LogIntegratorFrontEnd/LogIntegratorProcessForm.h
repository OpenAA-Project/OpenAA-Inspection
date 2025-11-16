#ifndef LOGINTEGRATORPROCESSFORM_H
#define LOGINTEGRATORPROCESSFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_LogIntegratorProcessForm.h"

class LogIntegratorProcessForm : public QWidget
{
	Q_OBJECT

public:
	LogIntegratorProcessForm(QWidget *parent = 0);
	~LogIntegratorProcessForm();

	void SetLotNo		(QString LotNo);
	void SetExecCount	(int Count);
	void SetExecNo		(int No);

public slots:
	void SetUpdate		(int value);

private:
	Ui::LogIntegratorProcessFormClass ui;
};

#endif // LOGINTEGRATORPROCESSFORM_H
