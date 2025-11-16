#include "LogIntegratorProcessForm.h"

LogIntegratorProcessForm::LogIntegratorProcessForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

LogIntegratorProcessForm::~LogIntegratorProcessForm()
{
}

void LogIntegratorProcessForm::SetUpdate(int value)
{
	ui.pgbProcessing->setValue(value);
	update();
}

void LogIntegratorProcessForm::SetLotNo(QString LotNo)
{
	ui.lbLotNo->setText(LotNo);
}

void LogIntegratorProcessForm::SetExecCount(int Count)
{
	ui.lbCount->setText(QString::number(Count));
}

void LogIntegratorProcessForm::SetExecNo(int No)
{
	ui.lbNo->setText(QString::number(No));
}
