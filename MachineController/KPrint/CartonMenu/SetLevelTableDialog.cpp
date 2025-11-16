#include "CartonMenuResource.h"
#include "SetLevelTableDialog.h"
#include "ui_SetLevelTableDialog.h"

SetLevelTableDialog::SetLevelTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLevelTableDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
}

SetLevelTableDialog::~SetLevelTableDialog()
{
    delete ui;
}

void SetLevelTableDialog::on_pushButtonCancel_clicked()
{

}

void SetLevelTableDialog::on_pushButtonSaveClose_clicked()
{

}
