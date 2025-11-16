#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(ContecNC4DInfo *info ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Data=info;

	ui->spinBoxAccel1			->setValue(Data->AxisX.AccelRate);
	ui->spinBoxPulsePerRot1		->setValue(Data->AxisX.PulsePerRot);
	ui->spinBoxPitch1			->setValue(Data->AxisX.Pitch);
	ui->spinBoxMaxVerocity1		->setValue(Data->AxisX.MaxVelocity);
	ui->spinBoxJogVerocity1		->setValue(Data->AxisX.JogVelocity);
	ui->spinBoxOriginVelocity1	->setValue(Data->AxisX.OriginVelocity);
	ui->spinBoxMaxPulse1		->setValue(Data->AxisX.MaxLength);

	ui->spinBoxAccel2			->setValue(Data->AxisY.AccelRate);
	ui->spinBoxPulsePerRot2		->setValue(Data->AxisY.PulsePerRot);
	ui->spinBoxPitch2			->setValue(Data->AxisY.Pitch);
	ui->spinBoxMaxVerocity2		->setValue(Data->AxisY.MaxVelocity);
	ui->spinBoxJogVerocity2		->setValue(Data->AxisY.JogVelocity);
	ui->spinBoxOriginVelocity2	->setValue(Data->AxisY.OriginVelocity);
	ui->spinBoxMaxPulse2		->setValue(Data->AxisY.MaxLength);

	ui->spinBoxAccel3			->setValue(Data->AxisZ.AccelRate);
	ui->spinBoxPulsePerRot3		->setValue(Data->AxisZ.PulsePerRot);
	ui->spinBoxPitch3			->setValue(Data->AxisZ.Pitch);
	ui->spinBoxMaxVerocity3		->setValue(Data->AxisZ.MaxVelocity);
	ui->spinBoxJogVerocity3		->setValue(Data->AxisZ.JogVelocity);
	ui->spinBoxOriginVelocity3	->setValue(Data->AxisZ.OriginVelocity);
	ui->spinBoxMaxPulse3		->setValue(Data->AxisZ.MaxLength);

	ui->spinBoxAccel4			->setValue(Data->AxisW.AccelRate);
	ui->spinBoxPulsePerRot4		->setValue(Data->AxisW.PulsePerRot);
	ui->spinBoxPitch4			->setValue(Data->AxisW.Pitch);
	ui->spinBoxMaxVerocity4		->setValue(Data->AxisW.MaxVelocity);
	ui->spinBoxJogVerocity4		->setValue(Data->AxisW.JogVelocity);
	ui->spinBoxOriginVelocity4	->setValue(Data->AxisW.OriginVelocity);
	ui->spinBoxMaxPulse4		->setValue(Data->AxisW.MaxLength);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	Data->AxisX.AccelRate		=	ui->spinBoxAccel1			->value();
	Data->AxisX.PulsePerRot		=	ui->spinBoxPulsePerRot1		->value();
	Data->AxisX.Pitch			=	ui->spinBoxPitch1			->value();
	Data->AxisX.MaxVelocity		=	ui->spinBoxMaxVerocity1		->value();
	Data->AxisX.JogVelocity		=	ui->spinBoxJogVerocity1		->value();
	Data->AxisX.OriginVelocity	=	ui->spinBoxOriginVelocity1	->value();
	Data->AxisX.MaxLength		=	ui->spinBoxMaxPulse1		->value();

	Data->AxisY.AccelRate		=	ui->spinBoxAccel2			->value();
	Data->AxisY.PulsePerRot		=	ui->spinBoxPulsePerRot2		->value();
	Data->AxisY.Pitch			=	ui->spinBoxPitch2			->value();
	Data->AxisY.MaxVelocity		=	ui->spinBoxMaxVerocity2		->value();
	Data->AxisY.JogVelocity		=	ui->spinBoxJogVerocity2		->value();
	Data->AxisY.OriginVelocity	=	ui->spinBoxOriginVelocity2	->value();
	Data->AxisY.MaxLength		=	ui->spinBoxMaxPulse2		->value();

	Data->AxisZ.AccelRate		=	ui->spinBoxAccel3			->value();
	Data->AxisZ.PulsePerRot		=	ui->spinBoxPulsePerRot3		->value();
	Data->AxisZ.Pitch			=	ui->spinBoxPitch3			->value();
	Data->AxisZ.MaxVelocity		=	ui->spinBoxMaxVerocity3		->value();
	Data->AxisZ.JogVelocity		=	ui->spinBoxJogVerocity3		->value();
	Data->AxisZ.OriginVelocity	=	ui->spinBoxOriginVelocity3	->value();
	Data->AxisZ.MaxLength		=	ui->spinBoxMaxPulse3		->value();

	Data->AxisW.AccelRate		=	ui->spinBoxAccel4			->value();
	Data->AxisW.PulsePerRot		=	ui->spinBoxPulsePerRot4		->value();
	Data->AxisW.Pitch			=	ui->spinBoxPitch4			->value();
	Data->AxisW.MaxVelocity		=	ui->spinBoxMaxVerocity4		->value();
	Data->AxisW.JogVelocity		=	ui->spinBoxJogVerocity4		->value();
	Data->AxisW.OriginVelocity	=	ui->spinBoxOriginVelocity4	->value();
	Data->AxisW.MaxLength		=	ui->spinBoxMaxPulse4		->value();

	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
