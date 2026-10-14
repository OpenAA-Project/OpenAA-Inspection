#include "EditAngleRangeDialog.h"
#include "ui_EditAngleRangeDialog.h"

EditAngleRangeDialog::EditAngleRangeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditAngleRangeDialog)
{
    ui->setupUi(this);
}

EditAngleRangeDialog::~EditAngleRangeDialog()
{
    delete ui;
}

void    EditAngleRangeDialog::Initial(double MinAngle,double MaxAngle)
{
    RetMinAngle=MinAngle;
    RetMaxAngle=MaxAngle;
    ui->EditMinAngleDegree->setValue(MinAngle);
    ui->EditMaxAngleDegree->setValue(MaxAngle);
}

void EditAngleRangeDialog::on_pushButtonOK_clicked()
{
	RetMinAngle = ui->EditMinAngleDegree->value();
	RetMaxAngle = ui->EditMaxAngleDegree->value();

    done(true);
}

void EditAngleRangeDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

