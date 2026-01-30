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

#include "RemoteLightControllerResource.h"
#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XLightClass.h"

extern	LightClassPack		*LightPack;
LightAccessList *LightPointer=NULL;

SettingDialog::SettingDialog(LayersBase *Base ,RemoteLightContainer &src ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,RemoteLightData(src)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	ui->listWidgetLightDLL->clear();
	for(LightAccessList *G=LightPack->GetFirst();G!=NULL;G=G->GetNext()){
		ui->listWidgetLightDLL->addItem(G->GetFileName());
	}
	ShowRegisteredItemList();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void	SettingDialog::ShowRegisteredItemList(void)
{
	ui->listWidgetRegisteredItemList->clear();
	for(RemoteLightItem *s=RemoteLightData.GetFirst();s!=NULL;s=s->GetNextD(RemoteLightData)){
		ui->listWidgetRegisteredItemList->addItem(s->RegName);
	}
}

void SettingDialog::on_listWidgetLightDLL_clicked(const QModelIndex &index)
{
	int	R=ui->listWidgetLightDLL->currentRow();
	if(R<0)
		return;
	LightAccessList *G=LightPack->GetItem(R);
	if(G!=NULL){
		ui->lineEditDLLFileName->setText(G->GetFileName());
	}
}

void SettingDialog::on_listWidgetRegisteredItemList_clicked(const QModelIndex &index)
{
	int	R=ui->listWidgetRegisteredItemList->currentRow();
	if(R<0)
		return;
	RemoteLightItem *s=RemoteLightData.GetItem(R);
	if(s!=NULL){
		ui->lineEditDLLFileName		->setText(s->DLLFileName);
		ui->lineEditRegistredName	->setText(s->RegName);
		ui->lineEditIPAddress		->setText(s->IPAddress);
		ui->spinBoxPortNumber		->setValue(s->PortNumber);
		ui->lineEditInitialString	->setText(s->InitialString);
	}
}

void SettingDialog::on_pushButtonSaveNew_clicked()
{
	RemoteLightItem *s=new RemoteLightItem(GetLayersBase(),&RemoteLightData);

	s->DLLFileName	=ui->lineEditDLLFileName	->text();
	s->RegName		=ui->lineEditRegistredName	->text();
	s->IPAddress	=ui->lineEditIPAddress		->text();
	s->PortNumber	=ui->spinBoxPortNumber		->value();
	s->InitialString=ui->lineEditInitialString	->text();
	s->ID=RemoteLightData.GetMaxID()+1;

	RemoteLightData.AppendList(s);
	ShowRegisteredItemList();
}

void SettingDialog::on_pushButtonUpdate_clicked()
{
	int	R=ui->listWidgetRegisteredItemList->currentRow();
	if(R<0)
		return;
	RemoteLightItem *s=RemoteLightData.GetItem(R);
	if(s!=NULL){
		s->DLLFileName	=ui->lineEditDLLFileName	->text();
		s->RegName		=ui->lineEditRegistredName	->text();
		s->IPAddress	=ui->lineEditIPAddress		->text();
		s->PortNumber	=ui->spinBoxPortNumber		->value();
		s->InitialString=ui->lineEditInitialString	->text();

		ShowRegisteredItemList();
	}
}

void SettingDialog::on_pushButtonDelete_clicked()
{
	int	R=ui->listWidgetRegisteredItemList->currentRow();
	if(R<0)
		return;
	RemoteLightItem *s=RemoteLightData.GetItem(R);
	if(s!=NULL){
		RemoteLightData.RemoveList(s);
		delete	s;
	}
	ShowRegisteredItemList();
}

void SettingDialog::on_pushButtonClose_clicked()
{
	close();
}