#include "ChooseSelectCameraDialog.h"
#include "ui_ChooseSelectCameraDialog.h"

ChooseSelectCameraDialog::ChooseSelectCameraDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseSelectCameraDialog)
{
    ui->setupUi(this);
}

ChooseSelectCameraDialog::~ChooseSelectCameraDialog()
{
    delete ui;
}
