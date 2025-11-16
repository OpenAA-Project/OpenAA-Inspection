#include "JioTestModeDialog.h"
#include "ui_JioTestModeDialog.h"

JioTestModeDialog::JioTestModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JioTestModeDialog)
{
    ui->setupUi(this);
}

JioTestModeDialog::~JioTestModeDialog()
{
    delete ui;
}
