#include "HLineDialog.h"
#include "ui_HLineDialog.h"

HLineDialog::HLineDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::HLineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

HLineDialog::~HLineDialog()
{
    delete ui;
}

void HLineDialog::on_pushButtonOK_clicked()
{
	x1=ui->spinBoxX1->value();
	y1=ui->spinBoxY1->value();
	Len=ui->spinBoxLen->value();
	done(true);
}

void HLineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
