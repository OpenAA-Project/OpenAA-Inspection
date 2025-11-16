#include "EditLineWidthDialog.h"
#include "ui_EditLineWidthDialog.h"
#include "XRememberer.h"

EditLineWidthDialog::EditLineWidthDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditLineWidthDialog)
{
    ui->setupUi(this);

    ui->spinBoxLineWidth->setValue(ControlRememberer::GetInt(ui->spinBoxLineWidth));

    InstallOperationLog(this);
}

EditLineWidthDialog::~EditLineWidthDialog()
{
    delete ui;
}

void EditLineWidthDialog::on_pushButtonOK_clicked()
{
    LineWidth=ControlRememberer::SetValue(ui->spinBoxLineWidth);
    done(true);
}

