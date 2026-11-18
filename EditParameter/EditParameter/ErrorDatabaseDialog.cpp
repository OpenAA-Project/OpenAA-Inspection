#include "ErrorDatabaseDialog.h"
#include "ui_ErrorDatabaseDialog.h"

ErrorDatabaseDialog::ErrorDatabaseDialog(QString &RetErr, QStringList &RetDrvList,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ErrorDatabaseDialog)
{
    ui->setupUi(this);

    ui->lineEditErrorMessage->setText(RetErr);
    ui->listWidgetDrivers->addItems(RetDrvList);
}

ErrorDatabaseDialog::~ErrorDatabaseDialog()
{
    delete ui;
}

void ErrorDatabaseDialog::on_pushButtonOK_clicked()
{
    done(true);
}

