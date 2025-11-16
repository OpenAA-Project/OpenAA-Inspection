#include "SettingSmoothingForm.h"

SettingSmoothingForm::SettingSmoothingForm(LayersBase *base,int methodValue ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	MethodValue=methodValue;
	ui.comboBoxMethod->setCurrentIndex(MethodValue);

	InstallOperationLog(this);
}

SettingSmoothingForm::~SettingSmoothingForm()
{

}


void SettingSmoothingForm::on_pushButtonOK_clicked()
{
	MethodValue=ui.comboBoxMethod->currentIndex();
	done(true);
}

void SettingSmoothingForm::on_pushButtonCancel_clicked()
{
	done(false);
}