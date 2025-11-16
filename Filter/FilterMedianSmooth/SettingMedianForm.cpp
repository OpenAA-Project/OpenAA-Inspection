#include "SettingMedianForm.h"

SettingMedianForm::SettingMedianForm(LayersBase *base,int _FilterDot,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	FilterDot=_FilterDot;
	ui.spinBoxFilterDot	->setValue(_FilterDot);

	InstallOperationLog(this);
}

SettingMedianForm::~SettingMedianForm()
{

}


void SettingMedianForm::on_pushButtonOK_clicked()
{
	FilterDot	=ui.spinBoxFilterDot->value();
	done(true);
}

void SettingMedianForm::on_pushButtonCancel_clicked()
{
	done(false);
}