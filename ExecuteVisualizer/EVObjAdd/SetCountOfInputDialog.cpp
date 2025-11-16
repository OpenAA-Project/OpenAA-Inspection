#include "SetCountOfInputDialog.h"
#include "ui_SetCountOfInputDialog.h"

SetCountOfInputDialog::SetCountOfInputDialog(int inputNumb ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCountOfInputDialog)
{
    ui->setupUi(this);
	InputNumb=inputNumb;
	ui->spinBoxCountOfInput->setValue(InputNumb);
}

SetCountOfInputDialog::~SetCountOfInputDialog()
{
    delete ui;
}

void SetCountOfInputDialog::on_pushButtonOK_clicked()
{
	InputNumb	=ui->spinBoxCountOfInput->value();
	done(true);
}
