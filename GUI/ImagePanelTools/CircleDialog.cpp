#include "CircleDialog.h"
#include "ui_CircleDialog.h"

CircleDialog::CircleDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CircleDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

CircleDialog::~CircleDialog()
{
    delete ui;
}

void CircleDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	R	=ui->spinBoxR->value();
	done(true);
}

void CircleDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
