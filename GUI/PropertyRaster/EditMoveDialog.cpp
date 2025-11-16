#include "PropertyRasterResource.h"
#include "EditMoveDialog.h"
#include "ui_EditMoveDialog.h"
#include "XRememberer.h"

EditMoveDialog::EditMoveDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditMoveDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ControlRememberer::RestoreForm(this);

	InstallOperationLog(this);
}

EditMoveDialog::~EditMoveDialog()
{
    delete ui;
}

void EditMoveDialog::on_pushButtonOK_clicked()
{
	XDir		=ui->doubleSpinBoxXDir	->value();
	YDir		=ui->doubleSpinBoxYDir	->value();
	PixelMode	=ui->radioButtonPixel	->isChecked();
	ControlRememberer::SaveForm(this);
	done(true);
}

void EditMoveDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
