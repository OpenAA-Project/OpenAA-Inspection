#include "SettingResolutionDialog.h"
#include "ui_SettingResolutionDialog.h"

SettingResolutionDialog::SettingResolutionDialog(double _XZoom ,double _YZoom ,int _Cx ,int _Cy
                                                ,LayersBase *Base
                                                ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SettingResolutionDialog)
{
    ui->setupUi(this);

    ui->doubleSpinBoxXZoom  ->setValue(_XZoom);
    ui->doubleSpinBoxYZoom  ->setValue(_YZoom);
    ui->spinBoxCx           ->setValue(_Cx);
    ui->spinBoxCy           ->setValue(_Cy);
}

SettingResolutionDialog::~SettingResolutionDialog()
{
    delete ui;
}

void SettingResolutionDialog::on_pushButtonOK_clicked()
{
    XZoom   =ui->doubleSpinBoxXZoom  ->value();
    YZoom   =ui->doubleSpinBoxYZoom  ->value();
    Cx      =ui->spinBoxCx           ->value();
    Cy      =ui->spinBoxCy           ->value();
    done(true);
}

void SettingResolutionDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
