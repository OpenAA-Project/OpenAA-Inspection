#include "RingDialog.h"
#include "ui_RingDialog.h"

RingDialog::RingDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RingDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

RingDialog::~RingDialog()
{
    delete ui;
}

void RingDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Rx1	=ui->spinBoxRx1->value();
	Ry1	=ui->spinBoxRy1->value();
	Rx2	=ui->spinBoxRx2->value();
	Ry2	=ui->spinBoxRy2->value();
	done(true);
}

void RingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
