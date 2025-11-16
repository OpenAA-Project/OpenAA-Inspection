#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "CCSControlByLANVer2.h"
#include "IPAddressDialog.h"

SettingDialog::SettingDialog(CCSControlByLANVer2 *p ,LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Panel(p)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	CurrentChannel	=0;
	Data=new CCSControlByLANParam();

	*Data=Panel->Data;
	SetToWindow(CurrentChannel);
}

SettingDialog::~SettingDialog()
{
    delete ui;
	delete	Data;
	Data=NULL;
}

void	SettingDialog::LoadFromWindow(int currentChannel)
{
	Data->ChannelInfoData[currentChannel].Name	=ui->lineEditName->text();
	Data->ChannelInfoData[currentChannel].Power	=ui->spinBoxPower->value();
	Data->ChannelInfoData[currentChannel].ON	=ui->checkBoxON->isChecked();
}
void	SettingDialog::SetToWindow(int NewChannel)
{
	ui->lineEditName->setText			(Data->ChannelInfoData[NewChannel].Name);
	ui->spinBoxPower->setValue			(Data->ChannelInfoData[NewChannel].Power);
	ui->checkBoxON->setChecked			(Data->ChannelInfoData[NewChannel].ON);
}

void SettingDialog::on_comboBoxChannel_currentIndexChanged(int index)
{
	if(CurrentChannel>=0){
		LoadFromWindow(CurrentChannel);
	}
	CurrentChannel=ui->comboBoxChannel->currentIndex();
	SetToWindow(CurrentChannel);
}

void SettingDialog::on_horizontalSliderPower_valueChanged(int value)
{
	ui->spinBoxPower->setValue(ui->horizontalSliderPower->value());
}

void SettingDialog::on_spinBoxPower_valueChanged(int arg1)
{
	ui->horizontalSliderPower->setValue(ui->spinBoxPower->value());
}

void SettingDialog::on_pushButtonSet_clicked()
{
	CurrentChannel=ui->comboBoxChannel->currentIndex();
	LoadFromWindow(CurrentChannel);
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_pushButtonIPAddress_clicked()
{
	IPAddressDialog	D(this,GetLayersBase());
	if(D.exec()==(int)true){
		Panel->SetIPAddress(*Data);
	}
}
