#include "PropertyRasterResource.h"
#include "EditShearDialog.h"
#include "ui_EditShearDialog.h"
#include "XRememberer.h"

EditShearDialog::EditShearDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditShearDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ControlRememberer::RestoreForm(this);

	InstallOperationLog(this);
}

EditShearDialog::~EditShearDialog()
{
    delete ui;
}

void EditShearDialog::on_pushButtonOK_clicked()
{
	Shear	=ui->doubleSpinBoxShear	->value();
	XMode	=ui->radioButtonXDir	->isChecked();
	ControlRememberer::SaveForm(this);
	done(true);
}

void EditShearDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
