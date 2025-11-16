#include "SettingShrinkForm.h"

SettingShrinkForm::SettingShrinkForm(LayersBase *base,int _ShrinkRate,int _ShrinkMethod,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.spinBoxShrinkRate	->setValue(_ShrinkRate);
	ui.comboBoxShrinkMethod->setCurrentIndex(_ShrinkMethod)	;

	InstallOperationLog(this);
}

SettingShrinkForm::~SettingShrinkForm()
{

}


void SettingShrinkForm::on_pushButtonOK_clicked()
{
	ShrinkRate	=ui.spinBoxShrinkRate	->value();
	ShrinkMethod=ui.comboBoxShrinkMethod->currentIndex();
	done(true);
}

void SettingShrinkForm::on_pushButtonCancel_clicked()
{
	done(false);
}