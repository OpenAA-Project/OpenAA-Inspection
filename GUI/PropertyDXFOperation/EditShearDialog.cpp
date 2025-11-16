#include "PropertyDXFOperationResource.h"
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

	ui->doubleSpinBoxShear	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxShear,0));
	ui->radioButtonXDir		->setChecked(ControlRememberer::GetBool(ui->radioButtonXDir));

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
	ControlRememberer::SetValue(ui->doubleSpinBoxShear	,ui->doubleSpinBoxShear->value());
	ControlRememberer::SetValue(ui->radioButtonXDir		,ui->radioButtonXDir->isChecked());
	done(true);
}

void EditShearDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
