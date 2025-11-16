#include "PropertyGerberFastFormResource.h"
#include "InputEchingFactorDialog.h"
#include "ui_InputEchingFactorDialog.h"

InputEchingFactorDialog::InputEchingFactorDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::InputEchingFactorDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	InstallOperationLog(this);
}

InputEchingFactorDialog::~InputEchingFactorDialog()
{
    delete ui;
}

void InputEchingFactorDialog::on_pushButtonOK_clicked()
{
	ConerR	=ui->doubleSpinBoxCornerR->value();
	done(true);
}

void InputEchingFactorDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
