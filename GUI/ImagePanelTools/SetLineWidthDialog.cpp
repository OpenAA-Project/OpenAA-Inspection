#include "SetLineWidthDialog.h"
#include "ui_SetLineWidthDialog.h"

SetLineWidthDialog::SetLineWidthDialog(double _LineWidth,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLineWidthDialog)
{
    ui->setupUi(this);

    ui->spinBoxLineWidth->setValue(_LineWidth);
}

SetLineWidthDialog::~SetLineWidthDialog()
{
    delete ui;
}

void SetLineWidthDialog::on_pushButtonOK_clicked()
{
    LineWidth   =ui->spinBoxLineWidth->value();
    done(true);
}


void SetLineWidthDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

