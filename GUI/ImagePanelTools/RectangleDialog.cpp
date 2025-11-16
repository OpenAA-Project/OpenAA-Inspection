#include "RectangleDialog.h"
#include "ui_RectangleDialog.h"

RectangleDialog::RectangleDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RectangleDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

RectangleDialog::~RectangleDialog()
{
    delete ui;
}

void RectangleDialog::on_pushButtonOK_clicked()
{
	x1=ui->spinBoxX1->value();
	y1=ui->spinBoxY1->value();
	x2=ui->spinBoxX2->value();
	y2=ui->spinBoxY2->value();
	done(true);
}

void RectangleDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
