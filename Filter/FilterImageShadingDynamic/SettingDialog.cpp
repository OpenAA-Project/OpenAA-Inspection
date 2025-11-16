#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include <QFileDialog>
#include "XIntClass.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "FilterImageShadingDynamic.h"

SettingDialog::SettingDialog(LayersBase *base,FilterImageShadingDynamic *p ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,Parent(p)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->spinBoxRefStartX    ->setValue(Parent->RefStartX);
    ui->spinBoxRefStartY    ->setValue(Parent->RefStartY);
    ui->spinBoxRefEndX      ->setValue(Parent->RefEndX);
    ui->spinBoxRefEndY      ->setValue(Parent->RefEndY);

    ui->spinBoxBrightnessLR ->setValue(Parent->DataR.BrightnessL);
    ui->spinBoxBrightnessLG ->setValue(Parent->DataG.BrightnessL);
    ui->spinBoxBrightnessLB ->setValue(Parent->DataB.BrightnessL);
    ui->spinBoxBrightnessHR ->setValue(Parent->DataR.BrightnessH);
    ui->spinBoxBrightnessHG ->setValue(Parent->DataG.BrightnessH);
    ui->spinBoxBrightnessHB ->setValue(Parent->DataB.BrightnessH);

    ui->spinBoxIdealR   ->setValue(Parent->DataR.Ideal);
    ui->spinBoxIdealG   ->setValue(Parent->DataG.Ideal);
    ui->spinBoxIdealB   ->setValue(Parent->DataB.Ideal);

    ui->spinBoxOffsetR  ->setValue(Parent->DataR.Offset);
    ui->spinBoxOffsetG  ->setValue(Parent->DataG.Offset);
    ui->spinBoxOffsetB  ->setValue(Parent->DataB.Offset);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
    Parent->RefStartX   =ui->spinBoxRefStartX    ->value();
    Parent->RefStartY   =ui->spinBoxRefStartY    ->value();
    Parent->RefEndX     =ui->spinBoxRefEndX      ->value();
    Parent->RefEndY     =ui->spinBoxRefEndY      ->value();

    Parent->DataR.BrightnessL=ui->spinBoxBrightnessLR ->value();
    Parent->DataG.BrightnessL=ui->spinBoxBrightnessLG ->value();
    Parent->DataB.BrightnessL=ui->spinBoxBrightnessLB ->value();
    Parent->DataR.BrightnessH=ui->spinBoxBrightnessHR ->value();
    Parent->DataG.BrightnessH=ui->spinBoxBrightnessHG ->value();
    Parent->DataB.BrightnessH=ui->spinBoxBrightnessHB ->value();

    Parent->DataR.Ideal     =ui->spinBoxIdealR->value();
    Parent->DataG.Ideal     =ui->spinBoxIdealG->value();
    Parent->DataB.Ideal     =ui->spinBoxIdealB->value();

    Parent->DataR.Offset    =ui->spinBoxOffsetR->value();
    Parent->DataG.Offset    =ui->spinBoxOffsetG->value();
    Parent->DataB.Offset    =ui->spinBoxOffsetB->value();

   done(true);
}


void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

