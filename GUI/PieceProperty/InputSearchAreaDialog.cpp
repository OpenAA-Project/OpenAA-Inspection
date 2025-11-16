#include "PiecePropertyFormResource.h"
#include "InputSearchAreaDialog.h"
#include "ui_InputSearchAreaDialog.h"
#include "XRememberer.h"

InputSearchAreaDialog::InputSearchAreaDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::InputSearchAreaDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->spinBoxSearchDot	->setValue(ControlRememberer::GetInt(ui->spinBoxSearchDot ,100));
	InstallOperationLog(this);
}

InputSearchAreaDialog::~InputSearchAreaDialog()
{
    delete ui;
}

void InputSearchAreaDialog::on_pushButtonOK_clicked()
{
	SearchDot	=ui->spinBoxSearchDot->value();
	ControlRememberer::SetValue(ui->spinBoxSearchDot	,ui->spinBoxSearchDot->value());

	accept();
}

void InputSearchAreaDialog::on_pushButtonCancel_clicked()
{
	reject();
}
