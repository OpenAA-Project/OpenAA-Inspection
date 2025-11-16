#include "WizardMasterMenuResource.h"
#include "ChangeNewMasterDialog.h"
#include "ui_ChangeNewMasterDialog.h"

ChangeNewMasterDialog::ChangeNewMasterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeNewMasterDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
}

ChangeNewMasterDialog::~ChangeNewMasterDialog()
{
    delete ui;
}

void ChangeNewMasterDialog::on_PushButtonCreateNewMaster_clicked()
{
    done(1);
}

void ChangeNewMasterDialog::on_PushButtonOnlyImage_clicked()
{
    done(2);
}
