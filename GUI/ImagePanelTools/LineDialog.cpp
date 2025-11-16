#include "LineDialog.h"
#include "ui_LineDialog.h"

LineDialog::LineDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::LineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

LineDialog::~LineDialog()
{
    delete ui;
}

void LineDialog::on_pushButtonOK_clicked()
{
	x1=ui->spinBoxX1->value();
	y1=ui->spinBoxY1->value();
	x2=ui->spinBoxX2->value();
	y2=ui->spinBoxY2->value();
	done(true);
}

void LineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
