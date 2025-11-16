#include "RotRectangleDialog.h"
#include "ui_RotRectangleDialog.h"

RotRectangleDialog::RotRectangleDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RotRectangleDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

RotRectangleDialog::~RotRectangleDialog()
{
    delete ui;
}

void RotRectangleDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Width	=ui->spinBoxWidth->value();
	Height	=ui->spinBoxHeight->value();
	S		=ui->doubleSpinBoxS->value();
	done(true);
}

void RotRectangleDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
