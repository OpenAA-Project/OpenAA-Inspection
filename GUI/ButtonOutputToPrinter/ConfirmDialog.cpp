#include "ConfirmDialog.h"
#include "ui_ConfirmDialog.h"
#include "ButtonOutputToPrinter.h"
#include "XPrinterDLLBaseClass.h"

ConfirmDialog::ConfirmDialog(ButtonOutputToPrinter *p ,PrinterClass *PC ,LayersBase *pbase ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
	,ServiceForLayers(pbase)
	,Parent(p)
{
    ui->setupUi(this);

	QStringList StrList;
	PC->GetHandle()->OutputPrinter(StrList);

	QString	Txt;
	for(int i=0;i<StrList.count();i++){
		Txt += StrList[i];
		Txt += QString(/**/"\r\n");
	}
	ui->plainTextEdit->setPlainText(Txt);
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::on_pushButtonClose_clicked()
{
	close();
}
