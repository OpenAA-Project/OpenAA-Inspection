#include "SelectShareNoDialog.h"
#include "ui_SelectShareNoDialog.h"

SelectShareNoDialog::SelectShareNoDialog(int _ShareNo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectShareNoDialog)
{
    ui->setupUi(this);
	ShareNo	=_ShareNo;
	ui->spinBoxShareNo->setValue(ShareNo);
}

SelectShareNoDialog::~SelectShareNoDialog()
{
    delete ui;
}

void SelectShareNoDialog::on_pushButtonOK_clicked()
{
	ShareNo=ui->spinBoxShareNo->value();
	done(true);
}

void SelectShareNoDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
