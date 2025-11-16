#include "IPAddressDialog.h"
#include "ui_IPAddressDialog.h"
#include "SettingDialog.h"
#include "CCSControlByLANVer2.h"

IPAddressDialog::IPAddressDialog(SettingDialog *d ,LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,SettingD(d)
    ,ui(new Ui::IPAddressDialog)
{
    ui->setupUi(this);

	ui->lineEditCurrentIP			->setText	(SettingD->Data->IPAddress);
	ui->spinBoxCurrentPort			->setValue	(SettingD->Data->Port);
	ui->lineEditNewIP				->setText	(SettingD->Data->IPAddress);
	ui->spinBoxNewPort				->setValue	(SettingD->Data->Port);
	ui->lineEditNewSubnetMask		->setText	(SettingD->Data->SubnetMask);
	ui->lineEditNewDefaultGateway	->setText	(SettingD->Data->DefaultGateway);
	ui->lineEditNewReturnIP			->setText	(SettingD->Data->ReturnToIPAddress);
	ui->spinBoxNewReturnPort		->setValue	(SettingD->Data->ReturnToPort);
}

IPAddressDialog::~IPAddressDialog()
{
    delete ui;
}

void IPAddressDialog::on_pushButtonSet_clicked()
{
	SettingD->Data->IPAddress			=ui->lineEditNewIP				->text	();
	SettingD->Data->Port				=ui->spinBoxNewPort				->value	();
	SettingD->Data->SubnetMask			=ui->lineEditNewSubnetMask		->text	();
	SettingD->Data->DefaultGateway		=ui->lineEditNewDefaultGateway	->text	();
	SettingD->Data->ReturnToIPAddress	=ui->lineEditNewReturnIP		->text	();
	SettingD->Data->ReturnToPort		=ui->spinBoxNewReturnPort		->value	();
	done(true);
}

void IPAddressDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
