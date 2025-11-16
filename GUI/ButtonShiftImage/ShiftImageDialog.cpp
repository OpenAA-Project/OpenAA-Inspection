#include "ShiftImageDialog.h"
#include "ui_ShiftImageDialog.h"
#include "XRememberer.h"

ShiftImageDialog::ShiftImageDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::ShiftImageDialog)
{
    ui->setupUi(this);

    ui->checkBoxMasterImage	->setChecked(ControlRememberer::GetBool(ui->checkBoxMasterImage));
    ui->checkBoxTargetImage	->setChecked(ControlRememberer::GetBool(ui->checkBoxTargetImage));
    ui->spinBoxX1		->setValue(ControlRememberer::GetInt(ui->spinBoxX1));
    ui->spinBoxX2		->setValue(ControlRememberer::GetInt(ui->spinBoxX2));
    ui->spinBoxShiftY	->setValue(ControlRememberer::GetInt(ui->spinBoxShiftY));
    ui->spinBoxY1		->setValue(ControlRememberer::GetInt(ui->spinBoxY1));
    ui->spinBoxY2		->setValue(ControlRememberer::GetInt(ui->spinBoxY2));
    ui->spinBoxShiftX	->setValue(ControlRememberer::GetInt(ui->spinBoxShiftX));
}

ShiftImageDialog::~ShiftImageDialog()
{
    delete ui;
}

void ShiftImageDialog::on_pushButtonExecuteShiftY_clicked()
{
    ModeMasterImage =ControlRememberer::SetValue(ui->checkBoxMasterImage);
    ModeTargetImage =ControlRememberer::SetValue(ui->checkBoxTargetImage);
    StartPos        =ControlRememberer::SetValue(ui->spinBoxX1);
    EndPos          =ControlRememberer::SetValue(ui->spinBoxX2);
    ShiftN          =ControlRememberer::SetValue(ui->spinBoxShiftY);
    done(1);
}


void ShiftImageDialog::on_pushButtonCancelY_clicked()
{
    done(-1);
}


void ShiftImageDialog::on_pushButtonExecuteShiftX_clicked()
{
    ModeMasterImage =ControlRememberer::SetValue(ui->checkBoxMasterImage);
    ModeTargetImage =ControlRememberer::SetValue(ui->checkBoxTargetImage);
    StartPos        =ControlRememberer::SetValue(ui->spinBoxY1);
    EndPos          =ControlRememberer::SetValue(ui->spinBoxY2);
    ShiftN          =ControlRememberer::SetValue(ui->spinBoxShiftX);
    done(1);
}


void ShiftImageDialog::on_pushButtonCancelX_clicked()
{
    done(-1);
}

