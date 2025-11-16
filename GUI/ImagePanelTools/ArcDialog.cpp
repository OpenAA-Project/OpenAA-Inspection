#include "ArcDialog.h"
#include "ui_ArcDialog.h"

ArcDialog::ArcDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::ArcDialog)
{
    ui->setupUi(this);
	//setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Rx	=ui->spinBoxRx->value();
	Ry	=ui->spinBoxRy->value();
	StartS	=ui->doubleSpinBoxStartS->value();
	EndS	=ui->doubleSpinBoxEndS->value();
	done(true);
}

void ArcDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
