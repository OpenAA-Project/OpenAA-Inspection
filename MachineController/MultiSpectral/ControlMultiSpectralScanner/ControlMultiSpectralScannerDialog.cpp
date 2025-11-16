#include "ControlMultiSpectralScannerDialog.h"
#include "ui_ControlMultiSpectralScannerDialog.h"

ControlMultiSpectralScannerDialog::ControlMultiSpectralScannerDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ControlMultiSpectralScannerDialog)
{
    ui->setupUi(this);
}

ControlMultiSpectralScannerDialog::~ControlMultiSpectralScannerDialog()
{
    delete ui;
}

void ControlMultiSpectralScannerDialog::on_pushButtonOK_clicked()
{
    JDim=ui->doubleSpinBoxJDim->value();
    ConstV=ui->spinBoxConstV->value();
    done(true);
}

