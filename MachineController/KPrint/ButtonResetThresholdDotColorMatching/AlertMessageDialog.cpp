#include "AlertMessageDialog.h"
#include "ui_AlertMessageDialog.h"

AlertMessageDialog::AlertMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlertMessageDialog)
{
    ui->setupUi(this);
}

AlertMessageDialog::~AlertMessageDialog()
{
    delete ui;
}

void AlertMessageDialog::on_toolButtonYes_clicked()
{
	done(true);
}

void AlertMessageDialog::on_toolButtonNo_clicked()
{
	done(false);
}
