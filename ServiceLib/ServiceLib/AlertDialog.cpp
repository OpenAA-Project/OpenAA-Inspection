#include "XTypeDef.h"
#include "AlertDialog.h"
#include "ui_AlertDialog.h"

AlertDialog::AlertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlertDialog)
{
    ui->setupUi(this);
}

AlertDialog::AlertDialog(const QString &Msg ,QWidget *parent):
    QDialog(parent),
    ui(new Ui::AlertDialog)
{
    ui->setupUi(this);
	ui->label->setText(Msg);
}

AlertDialog::~AlertDialog()
{
    delete ui;
}

void AlertDialog::on_pushButtonOK_clicked()
{
	close();
}
