#include "HioTestModeDialog.h"
#include "ui_HioTestModeDialog.h"

HioTestModeDialog::HioTestModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HioTestModeDialog)
{
    ui->setupUi(this);
}

HioTestModeDialog::~HioTestModeDialog()
{
    delete ui;
}
