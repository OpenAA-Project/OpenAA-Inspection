/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "CCSControlByLAN.h"
#include "IPAddressDialog.h"

SettingDialog::SettingDialog(CCSControlByLAN *p ,LayersBase *base ,QWidget *parent) :
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
	Data->ChannelInfoData[currentChannel].Mode	=ui->comboBoxMode->currentIndex();
	Data->ChannelInfoData[currentChannel].ON	=ui->checkBoxON->isChecked();
}
void	SettingDialog::SetToWindow(int NewChannel)
{
	ui->lineEditName->setText			(Data->ChannelInfoData[NewChannel].Name);
	ui->spinBoxPower->setValue			(Data->ChannelInfoData[NewChannel].Power);
	ui->comboBoxMode->setCurrentIndex	(Data->ChannelInfoData[NewChannel].Mode);
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