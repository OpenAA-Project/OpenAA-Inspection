#include "PropertyDXFOperationResource.h"
#include "SetWidthDialog.h"
#include "ui_SetWidthDialog.h"

SetWidthDialog::SetWidthDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SetWidthDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
}

SetWidthDialog::~SetWidthDialog()
{
    delete ui;
}

void SetWidthDialog::on_pushButtonOK_clicked()
{
	Width=ui->spinBoxLineWidth->value();
	done(true);
}

void SetWidthDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
