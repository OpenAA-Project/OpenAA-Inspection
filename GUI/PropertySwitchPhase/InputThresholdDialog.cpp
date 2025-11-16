#include "PropertySwitchPhaseResource.h"
#include "InputThresholdDialog.h"
#include "ui_InputThresholdDialog.h"

InputThresholdDialog::InputThresholdDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::InputThresholdDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
}

InputThresholdDialog::~InputThresholdDialog()
{
    delete ui;
}

void	InputThresholdDialog::Initialize(int searchdot)
{
	SearchDot=searchdot;
	ui->spinBoxSearchDot->setValue(SearchDot);
}

void InputThresholdDialog::on_pushButtonOK_clicked()
{
	SearchDot	=ui->spinBoxSearchDot->value();
	done(true);
}

void InputThresholdDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
