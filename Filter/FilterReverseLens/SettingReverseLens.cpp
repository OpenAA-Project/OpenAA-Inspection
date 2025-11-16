#include "SettingReverseLens.h"

SettingReverseLens::SettingReverseLens(LayersBase *base
										,double _Strength ,double _Width,int32 _StartX,int32 _EndX
										, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.doubleSpinBoxStrength->setValue(_Strength);
	ui.doubleSpinBoxWidth	->setValue(_Width);
	ui.spinBoxStartX		->setValue(_StartX);
	ui.spinBoxEndX			->setValue(_EndX);
	InstallOperationLog(this);
}

SettingReverseLens::~SettingReverseLens()
{

}


void SettingReverseLens::on_pushButtonOK_clicked()
{
	Strength	=ui.doubleSpinBoxStrength	->value();
	Width		=ui.doubleSpinBoxWidth		->value();
	StartX		=ui.spinBoxStartX			->value();
	EndX		=ui.spinBoxEndX				->value();
	done(true);
}

void SettingReverseLens::on_pushButtonCancel_clicked()
{
	done(false);
}