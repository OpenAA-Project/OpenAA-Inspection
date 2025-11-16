#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "ShareMasterChangeMultiplyDialog.h"
#include "ui_ShareMasterChangeMultiplyDialog.h"

ShareMasterChangeMultiplyDialog::ShareMasterChangeMultiplyDialog(double MultiplyLayer[],QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShareMasterChangeMultiplyDialog)
{
    ui->setupUi(this);
}

ShareMasterChangeMultiplyDialog::~ShareMasterChangeMultiplyDialog()
{
    delete ui;
}
