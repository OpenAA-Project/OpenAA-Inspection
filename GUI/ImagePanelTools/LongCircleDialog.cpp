#include "LongCircleDialog.h"
#include "ui_LongCircleDialog.h"

LongCircleDialog::LongCircleDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::LongCircleDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

LongCircleDialog::~LongCircleDialog()
{
    delete ui;
}

void LongCircleDialog::on_pushButtonOK_clicked()
{
	Cx1	=ui->spinBoxCx1->value();
	Cy1	=ui->spinBoxCy1->value();
	Cx2	=ui->spinBoxCx2->value();
	Cy2	=ui->spinBoxCy2->value();
	R	=ui->spinBoxR->value();
	done(true);
}

void LongCircleDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
