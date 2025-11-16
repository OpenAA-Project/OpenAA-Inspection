#include "IntegrationHistoryResource.h"
#include "ShowOldDataDialog.h"
#include "ui_ShowOldDataDialog.h"

ShowOldDataDialog::ShowOldDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowOldDataDialog)
{
    ui->setupUi(this);
}

ShowOldDataDialog::~ShowOldDataDialog()
{
    delete ui;
}
