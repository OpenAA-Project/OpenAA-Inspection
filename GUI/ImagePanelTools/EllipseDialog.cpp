#include "EllipseDialog.h"
#include "ui_EllipseDialog.h"

EllipseDialog::EllipseDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EllipseDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

EllipseDialog::~EllipseDialog()
{
    delete ui;
}

void EllipseDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Rx	=ui->spinBoxRx->value();
	Ry	=ui->spinBoxRy->value();
	done(true);
}

void EllipseDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
