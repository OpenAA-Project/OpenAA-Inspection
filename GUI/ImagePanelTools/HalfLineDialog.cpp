#include "HalfLineDialog.h"
#include "ui_HalfLineDialog.h"

HalfLineDialog::HalfLineDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::HalfLineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

HalfLineDialog::~HalfLineDialog()
{
    delete ui;
}

void HalfLineDialog::on_pushButtonOK_clicked()
{
	x		=ui->spinBoxX->value();
	y		=ui->spinBoxY->value();
	S		=ui->doubleSpinBox->value();
	Length	=ui->doubleSpinBoxLength->value();
	done(true);
}

void HalfLineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
