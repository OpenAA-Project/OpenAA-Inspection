#include "RotEllipseDialog.h"
#include "ui_RotEllipseDialog.h"

RotEllipseDialog::RotEllipseDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RotEllipseDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

RotEllipseDialog::~RotEllipseDialog()
{
    delete ui;
}

void RotEllipseDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Rx	=ui->spinBoxRx->value();
	Ry	=ui->spinBoxRy->value();
	S	=ui->doubleSpinBoxS->value();
	done(true);
}

void RotEllipseDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
