#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterDynamicBrightness.h"

SettingDialog::SettingDialog(LayersBase *base,FilterDynamicBrightness *v ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,FParent(v)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->spinBoxCheckPointX      ->setValue(v->CheckPointX);
    ui->spinBoxCheckPointWidth  ->setValue(v->CheckPointWidth);
    ui->spinBoxStartX       ->setValue(v->ExeX1);
    ui->spinBoxEndX         ->setValue(v->ExeX2);
    ui->doubleSpinBoxGainP  ->setValue(v->GainP);
    ui->doubleSpinBoxGainM  ->setValue(v->GainM);
    ui->doubleSpinBoxStatic ->setValue(v->StaticBrightness);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
    FParent->CheckPointX        =ui->spinBoxCheckPointX     ->value();
    FParent->CheckPointWidth    =ui->spinBoxCheckPointWidth ->value();
    FParent->ExeX1              =ui->spinBoxStartX          ->value();
    FParent->ExeX2              =ui->spinBoxEndX            ->value();
    FParent->GainP              =ui->doubleSpinBoxGainP     ->value();
    FParent->GainM              =ui->doubleSpinBoxGainM     ->value();
    FParent->StaticBrightness   =ui->doubleSpinBoxStatic    ->value();
    done(true);
}


void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

