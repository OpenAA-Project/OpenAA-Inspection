#include "InspectionPlayerResource.h"
#include "ErrorMessageDialog.h"
#include "ui_ErrorMessageDialog.h"
#include "XGeneralFunc.h"

ErrorMessageDialog::ErrorMessageDialog(NPListPack<ErrorInfoList> &Errors ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessageDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth ( 0, 60);
	ui->tableWidget->setColumnWidth ( 1, 300);

	int	RCount=0;
	for(ErrorInfoList *e=Errors.GetFirst();e!=NULL;e=e->GetNext()){
		RCount+=e->Messages.count();
	}
	ui->tableWidget->setRowCount(RCount);
	int	Row=0;
	for(ErrorInfoList *e=Errors.GetFirst();e!=NULL;e=e->GetNext()){
		for(int i=0;i<e->Messages.count();i++){
			::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(e->Page));
			::SetDataToTable(ui->tableWidget ,1,Row ,e->Messages[i]);
			Row++;
		}
	}
}

ErrorMessageDialog::~ErrorMessageDialog()
{
    delete ui;
}

void ErrorMessageDialog::on_pushButtonOK_clicked()
{
    close();
}
