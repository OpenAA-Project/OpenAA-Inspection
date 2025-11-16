#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#define	_USE_MATH_DEFINES
#include <math.h>

SettingDialog::SettingDialog(LayersBase *base
							,int _Layer
							,  double _Strength ,double _Width
							,  bool	_LeftSide   ,bool _RightSide
							, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int L=0;L<LayerNumb;L++){
		ui->comboBoxLayer->addItem(GetParamGlobal()->GetLayerName(L));
	}

	ui->comboBoxLayer		->setCurrentIndex (_Layer);
	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->doubleSpinBoxWidth	->setValue(_Width);	
	ui->checkBoxLeftSide	->setChecked(_LeftSide);
	ui->checkBoxRightSide	->setChecked(_RightSide);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	Layer		=ui->comboBoxLayer			->currentIndex ();
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();
	LeftSide	=ui->checkBoxLeftSide	->isChecked();
	RightSide	=ui->checkBoxRightSide	->isChecked();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_pushButtonTest_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();

	int	Xn=GetDotPerLine(-1);
	double	s=-GetDotPerLine(-1)/2;
	s=s/GetDotPerLine(-1)*2;
	double	G=cos(s*M_PI*Width);
	double	K=1.0;
	if(G>0){
		K=(Strength/G);
	}
	s=0;
	G=cos(s*M_PI*Width);
	double	C=1.0;
	if(G>0){
		C=(Strength/G);
	}

	ui->labelTestLeft	->setText(QString("Left end : ") +QString::number(K));
	ui->labelTestCenter	->setText(QString("Center   : ") +QString::number(C));
}
