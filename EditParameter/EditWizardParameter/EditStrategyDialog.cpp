#include "EditStrategyDialog.h"
#include "ui_EditStrategyDialog.h"

EditStrategyDialog::EditStrategyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStrategyDialog)
{
    ui->setupUi(this);
}

EditStrategyDialog::~EditStrategyDialog()
{
    delete ui;
}
