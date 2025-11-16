#include "SettingVerticalLinear.h"
#include "ui_SettingVerticalLinear.h"


SettingVerticalLinear::SettingVerticalLinear(LayersBase *base
											,double _Strength 
											, bool _WholeImage
											, bool	_TopSide   ,bool _BottomSide
											,BoolList &_Layers
											,double	Gamma
											, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingVerticalLinear)
{
    ui->setupUi(this);

	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->checkBoxWholeImage	->setChecked(_WholeImage);	
	ui->checkBoxTopSide	->setChecked(_TopSide);
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

SettingVerticalLinear::~SettingVerticalLinear()
{
    delete ui;
}

void SettingVerticalLinear::on_pushButtonOK_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	WholeImage	=ui->checkBoxWholeImage		->isChecked();
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

void SettingVerticalLinear::on_pushButtonCancel_clicked()
{
	done(false);
}