#include "SettingLinearCameraDialog.h"
#include "ui_SettingLinearCameraDialog.h"

SettingLinearCameraDialog::SettingLinearCameraDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingLinearCameraDialog)
{
    ui->setupUi(this);
}

SettingLinearCameraDialog::~SettingLinearCameraDialog()
{
    delete ui;
}
