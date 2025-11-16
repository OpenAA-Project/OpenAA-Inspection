#include "Arc2Dialog.h"
#include "ui_Arc2Dialog.h"

Arc2Dialog::Arc2Dialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::Arc2Dialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

Arc2Dialog::~Arc2Dialog()
{
    delete ui;
}

void Arc2Dialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Rx	=ui->spinBoxRx->value();
	Ry	=ui->spinBoxRy->value();
	StartS	=ui->doubleSpinBoxStartS->value();
	EndS	=ui->doubleSpinBoxEndS->value();
	done(true);
}

void Arc2Dialog::on_pushButtonCancel_clicked()
{
	done(false);
}
