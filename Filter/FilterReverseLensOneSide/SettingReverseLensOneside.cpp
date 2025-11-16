#include "SettingReverseLensOneside.h"
#include "ui_SettingReverseLensOneside.h"

SettingReverseLensOneside::SettingReverseLensOneside(LayersBase *base
													,double _Strength ,double _Width
													,  bool	_LeftSide   ,bool _RightSide
													, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingReverseLensOneside)
{
    ui->setupUi(this);
	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->doubleSpinBoxWidth	->setValue(_Width);	
	ui->checkBoxLeftSide	->setChecked(_LeftSide);
	ui->checkBoxRightSide	->setChecked(_RightSide);

	InstallOperationLog(this);
}

SettingReverseLensOneside::~SettingReverseLensOneside()
{
    delete ui;
}

void SettingReverseLensOneside::on_pushButtonOK_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();
	LeftSide	=ui->checkBoxLeftSide	->isChecked();
	RightSide	=ui->checkBoxRightSide	->isChecked();
	done(true);
}

void SettingReverseLensOneside::on_pushButtonCancel_clicked()
{
	done(false);
}
