#include "PropertyRasterResource.h"
#include "EditZoomDialog.h"
#include "ui_EditZoomDialog.h"
#include "XRememberer.h"

EditZoomDialog::EditZoomDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditZoomDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ControlRememberer::RestoreForm(this);

	InstallOperationLog(this);
}

EditZoomDialog::~EditZoomDialog()
{
    delete ui;
}

void EditZoomDialog::on_pushButtonOK_clicked()
{
	XZoomDir		=ui->doubleSpinBoxXZoomDir	->value();
	YZoomDir		=ui->doubleSpinBoxYZoomDir	->value();
	ControlRememberer::SaveForm(this);
	done(true);
}

void EditZoomDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
