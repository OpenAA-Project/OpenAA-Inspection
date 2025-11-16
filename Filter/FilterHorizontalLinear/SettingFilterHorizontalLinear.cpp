#include "SettingFilterHorizontalLinear.h"
#include "ui_SettingFilterHorizontalLinear.h"

SettingFilterHorizontalLinear::SettingFilterHorizontalLinear(LayersBase *base
															,double _Strength 
															, bool _WholeImage
															, bool	_LeftSide   ,bool _RightSide
															,BoolList &_Layers
															,double	Gamma
															, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingFilterHorizontalLinear)
{
    ui->setupUi(this);

	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->checkBoxWholeImage	->setChecked(_WholeImage);	
	ui->checkBoxLeftSide	->setChecked(_LeftSide);
	ui->checkBoxRightSide	->setChecked(_RightSide);
	ui->doubleSpinBoxGamma	->setValue(Gamma);
	Layers			=_Layers;

	if(Layers.GetCount()>0)
		ui->cbLayer0	->setChecked((bool)Layers[0]);
	if(Layers.GetCount()>1)
		ui->cbLayer1	->setChecked((bool)Layers[1]);
	if(Layers.GetCount()>2)
		ui->cbLayer2	->setChecked((bool)Layers[2]);

	on_checkBoxWholeImage_clicked();

	InstallOperationLog(this);
}

SettingFilterHorizontalLinear::~SettingFilterHorizontalLinear()
{
    delete ui;
}

void SettingFilterHorizontalLinear::on_pushButtonOK_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	WholeImage	=ui->checkBoxWholeImage		->isChecked();
	LeftSide	=ui->checkBoxLeftSide		->isChecked();
	RightSide	=ui->checkBoxRightSide		->isChecked();
	Gamma		=ui->doubleSpinBoxGamma		->value();
	if(Layers.GetCount()>0)
		Layers.GetItem(0)->SetValue(ui->cbLayer0	->isChecked());
	if(Layers.GetCount()>1)
		Layers.GetItem(1)->SetValue(ui->cbLayer1	->isChecked());
	if(Layers.GetCount()>2)
		Layers.GetItem(2)->SetValue(ui->cbLayer2	->isChecked());
	done(true);
}

void SettingFilterHorizontalLinear::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingFilterHorizontalLinear::on_checkBoxWholeImage_clicked()
{
	//if(ui->checkBoxWholeImage->isChecked()==true){
	//	ui->checkBoxLeftSide	->setEnabled(false);
	//	ui->checkBoxRightSide	->setEnabled(false);
	//}
	//else{
	//	ui->checkBoxLeftSide	->setEnabled(true);
	//	ui->checkBoxRightSide	->setEnabled(true);
	//}
}
