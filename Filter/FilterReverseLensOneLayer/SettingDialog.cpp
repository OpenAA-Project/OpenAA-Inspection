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

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#define	_USE_MATH_DEFINES
#include <math.h>

SettingDialog::SettingDialog(LayersBase *base
							,int _Layer
							,  double _Strength ,double _Width
							,  bool	_LeftSide   ,bool _RightSide
							, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int L=0;L<LayerNumb;L++){
		ui->comboBoxLayer->addItem(GetParamGlobal()->GetLayerName(L));
	}

	ui->comboBoxLayer		->setCurrentIndex (_Layer);
	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->doubleSpinBoxWidth	->setValue(_Width);	
	ui->checkBoxLeftSide	->setChecked(_LeftSide);
	ui->checkBoxRightSide	->setChecked(_RightSide);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	Layer		=ui->comboBoxLayer			->currentIndex ();
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();
	LeftSide	=ui->checkBoxLeftSide	->isChecked();
	RightSide	=ui->checkBoxRightSide	->isChecked();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_pushButtonTest_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();

	int	Xn=GetDotPerLine(-1);
	double	s=-GetDotPerLine(-1)/2;
	s=s/GetDotPerLine(-1)*2;
	double	G=cos(s*M_PI*Width);
	double	K=1.0;
	if(G>0){
		K=(Strength/G);
	}
	s=0;
	G=cos(s*M_PI*Width);
	double	C=1.0;
	if(G>0){
		C=(Strength/G);
	}

	ui->labelTestLeft	->setText(QString("Left end : ") +QString::number(K));
	ui->labelTestCenter	->setText(QString("Center   : ") +QString::number(C));
}