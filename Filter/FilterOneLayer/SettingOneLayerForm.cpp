#include "SettingOneLayerForm.h"

SettingOneLayerForm::SettingOneLayerForm(LayersBase *base
					,int _Layer ,int _LayerNumb
					,int _MethodValue
					,int _Param
					,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	ui.comboBoxLayer->clear();
	for(int i=0;i<_LayerNumb;i++){
		ui.comboBoxLayer->addItem(QString(/**/"Layer-")+QString::number(i));
	}
	ui.comboBoxLayer	->setCurrentIndex(_Layer);
	ui.comboBoxProcess	->setCurrentIndex(_MethodValue);
	ui.spinBoxParam	->setValue(_Param);

	InstallOperationLog(this);
}

SettingOneLayerForm::~SettingOneLayerForm()
{

}


void SettingOneLayerForm::on_pushButtonOK_clicked()
{
	Layer		=ui.comboBoxLayer	->currentIndex();
	MethodValue	=ui.comboBoxProcess	->currentIndex();
	Param		=ui.spinBoxParam	->value();
	done(true);
}

void SettingOneLayerForm::on_pushButtonCancel_clicked()
{
	done(false);
}