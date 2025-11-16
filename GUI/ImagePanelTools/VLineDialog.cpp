#include "VLineDialog.h"
#include "ui_VLineDialog.h"

VLineDialog::VLineDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::VLineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

VLineDialog::~VLineDialog()
{
    delete ui;
}

void VLineDialog::on_pushButtonOK_clicked()
{
	x1=ui->spinBoxX1->value();
	y1=ui->spinBoxY1->value();
	Len=ui->spinBoxLen->value();
	done(true);
}

void VLineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
