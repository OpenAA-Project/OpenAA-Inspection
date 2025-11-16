#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base
							,double	_Strength
							,double	_Width
							,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->doubleSpinBoxWidth	 ->setValue(_Width);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	Strength	=ui->doubleSpinBoxStrength->value();
	Width		=ui->doubleSpinBoxWidth	  ->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
