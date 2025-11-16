#include "XTypeDef.h"
#include "ParameterHelpDialog.h"
#include "ui_ParameterHelpDialog.h"
#include "XParameterHelp.h"

ParameterHelpDialog::ParameterHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterHelpDialog)
{
    ui->setupUi(this);
}

ParameterHelpDialog::~ParameterHelpDialog()
{
    delete ui;
}
