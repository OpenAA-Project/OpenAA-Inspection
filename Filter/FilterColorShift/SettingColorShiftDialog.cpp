#include "SettingColorShiftDialog.h"
#include "ui_SettingColorShiftDialog.h"

SettingColorShiftDialog::SettingColorShiftDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingColorShiftDialog)
{
    ui->setupUi(this);
}

SettingColorShiftDialog::~SettingColorShiftDialog()
{
    delete ui;
}

void SettingColorShiftDialog::on_pushButtonOK_clicked()
{

}

void SettingColorShiftDialog::on_pushButtonCancel_clicked()
{

}
