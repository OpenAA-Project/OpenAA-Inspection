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

#include "AddManualItemFormResource.h"
#include "AddManualItemForm.h"
#include "XRememberer.h"

AddManualItemForm::AddManualItemForm(LayersBase *Base, QWidget *parent)
	: QDialog(parent)
	,ServiceForLayers(Base)
	,ColorSamples(Base)
{
	ui.setupUi(this);

	ColorMap		.setParent(ui.frameCurrentItem);
	ColorMap		.Fit(ui.frameCurrentItem);
	Mergin			=20;

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	EnsmallDot=0;
	EnlargeDot=0;
	InstallOperationLog(this);
}

AddManualItemForm::~AddManualItemForm()
{

}

void	AddManualItemForm::Initial(void)
{
	ColorMap.Cube=MaskingColor;
	ColorMap.Cube.AddMerginInBases(Mergin);
	ColorMap.InitializedDoneCube();

	ui.spinBoxMergin	->setValue(Mergin);
	ui.spinBoxEnsmall	->setValue(EnsmallDot);
	ui.spinBoxEnlarge	->setValue(EnlargeDot);
}

void	AddManualItemForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorMap.Cube);
}

void	AddManualItemForm::SlotColorSampleSelectOne()
{
	ColorMap.Cube=*ColorSamples.CData.GetColorLogic();		
	MaskingColor	=ColorMap.Cube;

	ColorMap.Cube.AddMerginInBases(Mergin);
	ColorMap.InitializedDoneCube();
	ColorMap.Repaint();
}

void AddManualItemForm::on_pushButtonAddColor_clicked()
{
	MaskingColor.Add(*ColorSamples.CData.GetColorLogic());
	ColorMap.Cube=MaskingColor;
	ColorMap.Cube.AddMerginInBases(Mergin);
	ColorMap.InitializedDoneCube();
	ColorMap.Repaint();
}

void AddManualItemForm::on_pushButtonEliminateColor_clicked()
{
	MaskingColor.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorMap.Cube=MaskingColor;
	ColorMap.Cube.AddMerginInBases(Mergin);
	ColorMap.InitializedDoneCube();
	ColorMap.Repaint();
}

void AddManualItemForm::on_pushButtonSetMergin_clicked()
{
	Mergin=ui.spinBoxMergin->value();
	ColorMap.Cube=MaskingColor;
	ColorMap.Cube.AddMerginInBases(Mergin);
	ColorMap.InitializedDoneCube();
	ColorMap.Repaint();
}

void AddManualItemForm::on_pushButtonOK_clicked()
{
	Mergin		=ui.spinBoxMergin->value();
	EnsmallDot	=ui.spinBoxEnsmall->value();
	EnlargeDot	=ui.spinBoxEnlarge->value();

	done(true);
}

void AddManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}