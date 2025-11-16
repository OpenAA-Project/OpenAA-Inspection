#include "GioTestModeDialog.h"
#include "ui_GioTestModeDialog.h"

GioTestModeDialog::GioTestModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GioTestModeDialog)
{
    ui->setupUi(this);
}

GioTestModeDialog::~GioTestModeDialog()
{
    delete ui;
}
