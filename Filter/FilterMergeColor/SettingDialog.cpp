#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterMergeColor.h"

SettingDialog::SettingDialog(LayersBase *base,FilterMergeColor *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),Parent(p),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->doubleSpinBoxR1 ->setValue(Parent->R1);
    ui->doubleSpinBoxB1 ->setValue(Parent->B1);
    ui->doubleSpinBoxR2 ->setValue(Parent->R2);
    ui->doubleSpinBoxB2 ->setValue(Parent->B2);
    ui->doubleSpinBoxGain->setValue(Parent->Gain);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
    Parent->R1      =ui->doubleSpinBoxR1 ->value();
    Parent->B1      =ui->doubleSpinBoxB1 ->value();
    Parent->R2      =ui->doubleSpinBoxR2 ->value();
    Parent->B2      =ui->doubleSpinBoxB2 ->value();
    Parent->Gain    =ui->doubleSpinBoxGain->value();
    done(true);
}


void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

