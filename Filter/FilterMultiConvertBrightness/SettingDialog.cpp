#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void    SettingDialog::Init( double	_StrengthL
							,double	_WidthL
							,double	_InclineL
							,double	_AddVL
							,double	_AddBL

							,double	_StrengthR
							,double	_WidthR
							,double	_InclineR
							,double	_AddVR
							,double	_AddBR)
{
	StrengthL	=_StrengthL;
	WidthL		=_WidthL;
	InclineL	=_InclineL;
	AddVL		=_AddVL;
	AddBL		=_AddBL;

	StrengthR	=_StrengthR;
	WidthR		=_WidthR;
	InclineR	=_InclineR;
	AddVR		=_AddVR;
	AddBR		=_AddBR;

	ui->doubleSpinBoxInclineL	->setValue(InclineL);
	ui->doubleSpinBoxAddVL		->setValue(AddVL);
	ui->doubleSpinBoxStrengthL	->setValue(StrengthL);
	ui->doubleSpinBoxWidthL		->setValue(WidthL);
	ui->doubleSpinBoxAddBL		->setValue(AddBL);

	ui->doubleSpinBoxInclineR	->setValue(InclineR);
	ui->doubleSpinBoxAddVR		->setValue(AddVR);
	ui->doubleSpinBoxStrengthR	->setValue(StrengthR);
	ui->doubleSpinBoxWidthR		->setValue(WidthR);
	ui->doubleSpinBoxAddBR		->setValue(AddBR);
}

void SettingDialog::on_pushButtonOK_clicked()
{
	InclineL	=ui->doubleSpinBoxInclineL	->value();
	AddVL		=ui->doubleSpinBoxAddVL		->value();
	StrengthL	=ui->doubleSpinBoxStrengthL	->value();
	WidthL		=ui->doubleSpinBoxWidthL	->value();
	AddBL		=ui->doubleSpinBoxAddBL		->value();

	InclineR	=ui->doubleSpinBoxInclineR	->value();
	AddVR		=ui->doubleSpinBoxAddVR		->value();
	StrengthR	=ui->doubleSpinBoxStrengthR	->value();
	WidthR		=ui->doubleSpinBoxWidthR	->value();
	AddBR		=ui->doubleSpinBoxAddBR		->value();

	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
