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

#include "CreateManualEulerRingFormResource.h"
#include "EulerRingPickupForm.h"
#include "XDataInLayer.h"

EulerRingPickupForm::EulerRingPickupForm(LayersBase *Base
						,RGBStock *Stocker
						,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);

	ColorPanel.setParent(ui.frameColorCube);
	if(Stocker!=NULL){
		ColorSphere	*b=new ColorSphere();
		b->Create(*Stocker);
		ColorPanel.Cube.AddBase(b);
		ColorPanel.InitializedDoneCube();
	}
	ColorPanel.Fit(ui.frameColorCube);

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	InstallOperationLog(this);
}

EulerRingPickupForm::~EulerRingPickupForm()
{

}

void	EulerRingPickupForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorPanel.Cube);
}
void	EulerRingPickupForm::SlotColorSampleSelectOne()
{
	ColorPanel.Cube=*ColorSamples.CData.GetColorLogic();
	ColorPanel.InitializedDoneCube();
	ColorPanel.Repaint();
}

void EulerRingPickupForm::on_pushButtonSetToColor_clicked()
{
	done((int)true);
}

void EulerRingPickupForm::on_pushButtonClearColor_clicked()
{
	ColorPanel.Cube.ClearAll();
	ColorPanel.Repaint();
}

void EulerRingPickupForm::on_pushButtonClearBaseColor_clicked()
{
	ColorPanel.Cube.ClearBase();
	ColorPanel.Repaint();
}

void EulerRingPickupForm::on_pushButtonClearEliminateColor_clicked()
{
	ColorPanel.Cube.ClearEliminate();
	ColorPanel.Repaint();
}

void EulerRingPickupForm::on_pushButtonClose_clicked()
{
	done((int)false);
}

void EulerRingPickupForm::on_pushButtonAddColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()!=NULL){
		ColorPanel.Cube.Add(*ColorSamples.CData.GetColorLogic());
		ColorPanel.Repaint();
	}
}

void EulerRingPickupForm::on_pushButtonEliminateColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()!=NULL){
		ColorPanel.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
		ColorPanel.Repaint();
	}
}