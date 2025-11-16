#include "InputPathListDialog.h"
#include "ui_InputPathListDialog.h"

InputPathListDialog::InputPathListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPathListDialog)
{
    ui->setupUi(this);
}

InputPathListDialog::~InputPathListDialog()
{
    delete ui;
}
