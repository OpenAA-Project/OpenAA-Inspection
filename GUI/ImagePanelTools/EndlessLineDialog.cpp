#include "EndlessLineDialog.h"
#include "ui_EndlessLineDialog.h"

EndlessLineDialog::EndlessLineDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EndlessLineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

EndlessLineDialog::~EndlessLineDialog()
{
    delete ui;
}

void EndlessLineDialog::on_pushButtonOK_clicked()
{
	x=ui->spinBoxX->value();
	y=ui->spinBoxY->value();
	S=ui->doubleSpinBox->value();
	done(true);
}

void EndlessLineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
