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

#include "ButtonChangeServerFormResource.h"
#include "SettingServerInfoDialog.h"
#include "ui_SettingServerInfoDialog.h"
#include "XDataInLayer.h"

SettingServerInfoDialog::SettingServerInfoDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingServerInfoDialog)
{
    ui->setupUi(this);


	QString	FileName=GetLayersBase()->GetUserPath() + ::GetSeparator() +ServerList.GetFileName();
	QFile	File(FileName);

	if(File.open(QIODevice::ReadOnly)==true){
		ServerList.Load(&File);
	}
	DrawList();

	InstallOperationLog(this);
}

SettingServerInfoDialog::~SettingServerInfoDialog()
{
    delete ui;
}
void	SettingServerInfoDialog::DrawList(void)
{
	ui->listWidgetServer->clear();
	for(ChangeServerInfo *L=ServerList.GetFirst();L!=NULL;L=L->GetNext()){
		ui->listWidgetServer->addItem(L->ServerName);
	}
}
void SettingServerInfoDialog::on_pushButtonCreateNew_clicked()
{
	ChangeServerInfo	*d=new ChangeServerInfo();
	d->ServerName	=ui->lineEditServerName	->text();
	d->DBIPAddress	=ui->lineEditDBIPAddress->text();
	d->DBFileName	=ui->lineEditDBFileName	->text();
	d->DBPort		=ui->spinBoxDBPort		->value();
	d->ImagePath	=ui->lineEditImgePath	->text();
	ServerList.AppendList(d);
	DrawList();
}

void SettingServerInfoDialog::on_pushButtonUpdate_clicked()
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		ServerList[R]->ServerName	=ui->lineEditServerName	->text();
		ServerList[R]->DBIPAddress	=ui->lineEditDBIPAddress->text();
		ServerList[R]->DBFileName	=ui->lineEditDBFileName	->text();
		ServerList[R]->DBPort		=ui->spinBoxDBPort		->value();
		ServerList[R]->ImagePath	=ui->lineEditImgePath	->text();
	}

}

void SettingServerInfoDialog::on_pushButtonDelete_clicked()
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		ChangeServerInfo	*d=ServerList[R];
		ServerList.RemoveList(d);
		delete	d;

		DrawList();
	}
}

void SettingServerInfoDialog::on_pushButtonClose_clicked()
{
	QString	FileName=GetLayersBase()->GetUserPath() + ::GetSeparator() +ServerList.GetFileName();
	QFile	File(FileName);

	if(File.open(QIODevice::WriteOnly)==true){
		ServerList.Save(&File);
	}
	done(true);
}

void SettingServerInfoDialog::on_listWidgetServer_clicked(const QModelIndex &index)
{
	int	R=ui->listWidgetServer->currentRow();
	if(R>=0){
		ui->lineEditServerName	->setText(ServerList[R]->ServerName	);
		ui->lineEditDBIPAddress	->setText(ServerList[R]->DBIPAddress);
		ui->lineEditDBFileName	->setText(ServerList[R]->DBFileName	);
		ui->spinBoxDBPort		->setValue(ServerList[R]->DBPort	);
		ui->lineEditImgePath	->setText(ServerList[R]->ImagePath	);
	}
}