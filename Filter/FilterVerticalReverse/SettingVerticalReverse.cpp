#include "SettingVerticalReverse.h"
#include "ui_SettingVerticalReverse.h"


SettingVerticalReverse::SettingVerticalReverse(LayersBase *base
											,double _Strength ,double _Width
											,  bool	_TopSide   ,bool _BottomSide
											,  BoolList &_Layers
											,  double	Gamma
											, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingVerticalReverse)
{
    ui->setupUi(this);
	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->doubleSpinBoxWidth	->setValue(_Width);	
	ui->checkBoxTopSide		->setChecked(_TopSide);
	ui->checkBoxBottomSide	->setChecked(_BottomSide);
	ui->doubleSpinBoxGamma	->setValue(Gamma);
	Layers			=_Layers;

	if(Layers.GetCount()>0)
		ui->cbLayer0	->setChecked((bool)Layers[0]);
	if(Layers.GetCount()>1)
		ui->cbLayer1	->setChecked((bool)Layers[1]);
	if(Layers.GetCount()>2)
		ui->cbLayer2	->setChecked((bool)Layers[2]);

	InstallOperationLog(this);
}

SettingVerticalReverse::~SettingVerticalReverse()
{
    delete ui;
}

void SettingVerticalReverse::on_pushButtonOK_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();
	TopSide		=ui->checkBoxTopSide		->isChecked();
	BottomSide	=ui->checkBoxBottomSide		->isChecked();
	Gamma		=ui->doubleSpinBoxGamma		->value();
	if(Layers.GetCount()>0)
		Layers.GetItem(0)->SetValue(ui->cbLayer0->isChecked());
	if(Layers.GetCount()>1)
		Layers.GetItem(1)->SetValue(ui->cbLayer1->isChecked());
	if(Layers.GetCount()>2)
		Layers.GetItem(2)->SetValue(ui->cbLayer2->isChecked());
	done(true);
}

void SettingVerticalReverse::on_pushButtonCancel_clicked()
{
	done(false);
}
