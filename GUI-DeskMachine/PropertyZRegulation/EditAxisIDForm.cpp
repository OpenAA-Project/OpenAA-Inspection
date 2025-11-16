#include "EditAxisIDForm.h"

EditAxisIDForm::EditAxisIDForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

EditAxisIDForm::~EditAxisIDForm()
{

}

void	EditAxisIDForm::SetData(int axisID ,int centerInMaster ,int okZone)
{
	ui.spinBoxAxisID->setValue(axisID);
	ui.spinBoxCenterInMaster->setValue(centerInMaster);
	ui.spinBoxOKZone		->setValue(okZone);
}


void EditAxisIDForm::on_pushButtonOK_clicked()
{
	AxisID			=ui.spinBoxAxisID		->value();
	CenterInMaster	=ui.spinBoxCenterInMaster->value();
	OKZone			=ui.spinBoxOKZone		->value();
	done(true);
}

void EditAxisIDForm::on_pushButtonCancel_clicked()
{
	done(false);
}