#include "XTypeDef.h"
#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base,double	_Gain
										,int _Length
										,BoolList &_Layers
										,bool	_Vertical
										,bool	_BPF
										,int	_PassWidth
										,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);


	Gain			=_Gain;
	Length			=_Length;
	Vertical		=_Vertical;
	Layers			=_Layers;
	BPF				=_BPF;
	PassWidth		=_PassWidth;

	ui->doubleSpinBoxGain	->setValue(Gain);
	ui->spinBoxLength		->setValue(Length);
	ui->cbVertical			->setChecked(Vertical);

	if(Layers.GetCount()>0)
		ui->cbLayer0	->setChecked((bool)Layers[0]);
	if(Layers.GetCount()>1)
		ui->cbLayer1	->setChecked((bool)Layers[1]);
	if(Layers.GetCount()>2)
		ui->cbLayer2	->setChecked((bool)Layers[2]);

	ui->groupBoxBPF			->setChecked(BPF);
	ui->spinBoxPassWidth	->setValue(PassWidth);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	Gain			=ui->doubleSpinBoxGain	->value();
	Length			=ui->spinBoxLength		->value();
	Vertical		=ui->cbVertical			->isChecked();

	if(Layers.GetCount()>0)
		Layers.GetItem(0)->SetValue(ui->cbLayer0->isChecked());
	if(Layers.GetCount()>1)
		Layers.GetItem(1)->SetValue(ui->cbLayer1->isChecked());
	if(Layers.GetCount()>2)
		Layers.GetItem(2)->SetValue(ui->cbLayer2->isChecked());

	BPF			=ui->groupBoxBPF		->isChecked();
	PassWidth	=ui->spinBoxPassWidth	->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
