#include "SettingFilterHorizontalBand.h"
#include "ui_SettingFilterHorizontalBand.h"

SettingFilterHorizontalBand::SettingFilterHorizontalBand(LayersBase *base
														,double	_Gain
														,int _CenterX
														,int _BandWidth
														,int _GradationWidth
														,BoolList &_Layers
														,double	Gamma
														,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingFilterHorizontalBand)
{
    ui->setupUi(this);

	Gain			=_Gain;
	CenterX			=_CenterX;
	BandWidth		=_BandWidth;
	GradationWidth	=_GradationWidth;
	Layers			=_Layers;

	ui->doubleSpinBoxGain	->setValue(Gain);
	ui->spinBoxCenterX		->setValue(CenterX);
	ui->spinBoxBandWidth	->setValue(BandWidth);
	ui->spinBoxGradationWidth->setValue(GradationWidth);
	ui->doubleSpinBoxGamma	->setValue(Gamma);

	if(Layers.GetCount()>0)
		ui->cbLayer0	->setChecked((bool)Layers[0]);
	if(Layers.GetCount()>1)
		ui->cbLayer1	->setChecked((bool)Layers[1]);
	if(Layers.GetCount()>2)
		ui->cbLayer2	->setChecked((bool)Layers[2]);

	InstallOperationLog(this);
}

SettingFilterHorizontalBand::~SettingFilterHorizontalBand()
{
    delete ui;
}

void SettingFilterHorizontalBand::on_pushButtonOK_clicked()
{
	Gain			=ui->doubleSpinBoxGain		->value();
	CenterX			=ui->spinBoxCenterX			->value();
	BandWidth		=ui->spinBoxBandWidth		->value();
	GradationWidth	=ui->spinBoxGradationWidth	->value();
	Gamma			=ui->doubleSpinBoxGamma		->value();

	if(Layers.GetCount()>0)
		Layers.GetItem(0)->SetValue(ui->cbLayer0->isChecked());
	if(Layers.GetCount()>1)
		Layers.GetItem(1)->SetValue(ui->cbLayer1->isChecked());
	if(Layers.GetCount()>2)
		Layers.GetItem(2)->SetValue(ui->cbLayer2->isChecked());

	done(true);
}

void SettingFilterHorizontalBand::on_pushButtonCancel_clicked()
{
	done(false);
}
