/*
 * Copyright (C) 2022
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

#include "NGTypeDialog.h"
#include "ui_NGTypeDialog.h"
#include "XOutlineLibrary.h"

NGTypeDialog::NGTypeDialog(LayersBase *base ,OutlineInspectLibNGTypeItem *item ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Item(item),ColorSamples(base)
    ,ui(new Ui::NGTypeDialog)
{
    ui->setupUi(this);

	ui->spinBoxMinSize		->setValue(Item->MinSize);
	ui->spinBoxMaxSize		->setValue(Item->MaxSize);
	ui->spinBoxMinRoundRate	->setValue(Item->MinRoundRate);
	ui->spinBoxMaxRoundRate	->setValue(Item->MaxRoundRate);

	ColorZone			=Item->ColorZone;
	ColorZoneRGB		.setParent(ui->frameThreshold);
	ColorZoneRGB		.Fit(ui->frameThreshold);

	ColorZoneRGB.Cube=ColorZone;
	ColorZoneRGB.InitializedDoneCube();

	connect(&ColorZoneRGB,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorZoneRGB,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));

	
	ColorSamples.setParent(ui->frameColorSample);
	ColorSamples.move(0,0);

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	InstallOperationLog(this);
}

NGTypeDialog::~NGTypeDialog()
{
    delete ui;
}

void NGTypeDialog::on_pushButtonAddColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorZoneRGB.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorZoneRGB.Repaint();

	ColorZone	=ColorZoneRGB.Cube;
}

void NGTypeDialog::on_pushButtonEliminateColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorZoneRGB.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorZoneRGB.Repaint();

	ColorZone	=ColorZoneRGB.Cube;
}

void	NGTypeDialog::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorZoneRGB.Cube);
}
void	NGTypeDialog::SlotColorSampleSelectOne()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorZoneRGB.Cube=*ColorSamples.CData.GetColorLogic();
	ColorZoneRGB.InitializedDoneCube();
	ColorZoneRGB.Repaint();
	
	ColorZone	=ColorZoneRGB.Cube;
}
void	NGTypeDialog::SlotAddEliminated(void)
{
	ColorZone	=ColorZoneRGB.Cube;
}
void	NGTypeDialog::SlotDelEliminated(void)
{
	ColorZone	=ColorZoneRGB.Cube;
}
void NGTypeDialog::on_pushButtonOK_clicked()
{
	Item->ColorZone		=ColorZone;
	Item->MinSize		=ui->spinBoxMinSize->value();
	Item->MaxSize		=ui->spinBoxMaxSize->value();
	Item->MinRoundRate	=ui->spinBoxMinRoundRate->value();
	Item->MaxRoundRate	=ui->spinBoxMaxRoundRate->value();
	done(true);
}

void NGTypeDialog::on_pushButtonClear_clicked()
{
	ColorZone.ClearAll();
	ColorZoneRGB.Cube=ColorZone;
	ColorZoneRGB.InitializedDoneCube();
	ColorZoneRGB.Repaint();
}