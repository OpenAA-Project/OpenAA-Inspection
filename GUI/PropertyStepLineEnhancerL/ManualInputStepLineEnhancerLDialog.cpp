#include "ManualInputStepLineEnhancerLDialog.h"
#include "ui_ManualInputStepLineEnhancerLDialog.h"

ManualInputStepLineEnhancerLDialog::ManualInputStepLineEnhancerLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualInputStepLineEnhancerLDialog)
{
    ui->setupUi(this);
}

ManualInputStepLineEnhancerLDialog::~ManualInputStepLineEnhancerLDialog()
{
    delete ui;
}

void ManualInputStepLineEnhancerLDialog::on_tableWidgetLibList_clicked(const QModelIndex &index)
{

}

void ManualInputStepLineEnhancerLDialog::on_ButtonOK_clicked()
{

}

void ManualInputStepLineEnhancerLDialog::on_ButtonCancel_clicked()
{

}
