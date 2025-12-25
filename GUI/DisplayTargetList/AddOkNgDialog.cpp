#include "AddOkNgDialog.h"
#include "ui_AddOkNgDialog.h"

AddOkNgDialog::AddOkNgDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddOkNgDialog)
{
    ui->setupUi(this);

    Ret=-1;
}

AddOkNgDialog::~AddOkNgDialog()
{
    delete ui;
}

void AddOkNgDialog::on_pushButtonOK_clicked()
{
    Ret=1;
    done(Ret);
}
void AddOkNgDialog::on_pushButtonNG_clicked()
{
    Ret=2;
    done(Ret);
}
void AddOkNgDialog::on_pushButtonCancel_clicked()
{
    Ret=-1;
    done(Ret);
}
    
    
