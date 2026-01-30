/*
 * Copyright (C) 2024
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

#include "SettingParamDialog.h"
#include "ui_SettingParamDialog.h"
#include "DustReducerAI.h"
#include "XIntClass.h"
#include <QFileDialog>
#include "XDataInLayer.h"

SettingParamDialog::SettingParamDialog(LayersBase *base ,DustReducerAI *P,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),Parent(P),
    ui(new Ui::SettingParamDialog)
{
    ui->setupUi(this);

	ui->spinBoxXLen					->setValue(Parent->XLen);
	ui->spinBoxYLen					->setValue(Parent->YLen);
	ui->doubleSpinBoxMinMatchRate	->setValue(Parent->MinMatchRate);
	ui->lineEditRegPackFileName		->setText(Parent->RegPackFileName);

	ui->toolButtonLayer0->setChecked(false);
	ui->toolButtonLayer1->setChecked(false);
	ui->toolButtonLayer2->setChecked(false);

	if(GetLayersBase()->GetMaxLayerNumb()==1){
		ui->toolButtonLayer1->setVisible(false);
		ui->toolButtonLayer2->setVisible(false);
	}
	if(GetLayersBase()->GetMaxLayerNumb()==2){
		ui->toolButtonLayer2->setVisible(false);
	}
	for(IntClass *c=Parent->AdaptedLayer.GetFirst();c!=NULL;c=c->GetNext()){
		int	layer=c->GetValue();
		if(layer==0)
			ui->toolButtonLayer0->setChecked(true);
		if(layer==1)
			ui->toolButtonLayer1->setChecked(true);
		if(layer==2)
			ui->toolButtonLayer2->setChecked(true);
	}
}

SettingParamDialog::~SettingParamDialog()
{
    delete ui;
}

void SettingParamDialog::on_pushButtonSelectFile_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL,"Select Registration library file"
														,QString()
														,/**/"Dat file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		ui->lineEditRegPackFileName->setText(FileName);
	}
}

void SettingParamDialog::on_pushButtonOK_clicked()
{
	Parent->XLen			=ui->spinBoxXLen				->value();
	Parent->YLen			=ui->spinBoxYLen				->value();
	Parent->MinMatchRate	=ui->doubleSpinBoxMinMatchRate	->value();
	Parent->RegPackFileName	=ui->lineEditRegPackFileName->text();

	Parent->AdaptedLayer.RemoveAll();
	if(ui->toolButtonLayer0->isChecked()==true)
		Parent->AdaptedLayer.Add(0);
	if(ui->toolButtonLayer1->isChecked()==true)
		Parent->AdaptedLayer.Add(1);
	if(ui->toolButtonLayer2->isChecked()==true)
		Parent->AdaptedLayer.Add(2);

	done(true);
}

void SettingParamDialog::on_pushButtonCancel_clicked()
{
	done(false);
}