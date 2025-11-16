#include "InputCodeDialogResource.h"
#include "InputCodeDialog.h"
#include "ui_InputCodeDialog.h"

InputCodeDialog::InputCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputCodeDialog)
{
    ui->setupUi(this);
}

InputCodeDialog::~InputCodeDialog()
{
    delete ui;
}

void InputCodeDialog::on_pushButtonOK_clicked()
{
	BarCode	=ui->lineEditBarcode->text();
	done(true);
}

void InputCodeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
