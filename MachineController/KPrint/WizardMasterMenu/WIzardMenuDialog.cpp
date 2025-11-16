#include "WIzardMenuDialog.h"
#include "ui_WIzardMenuDialog.h"

WIzardMenuDialog::WIzardMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WIzardMenuDialog)
{
    ui->setupUi(this);
}

WIzardMenuDialog::~WIzardMenuDialog()
{
    delete ui;
}
