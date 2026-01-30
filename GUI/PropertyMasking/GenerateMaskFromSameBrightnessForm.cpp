/*
 * Copyright (C) 2025
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


#include "PropertyMaskingFormResource.h"
#include "GenerateMaskFromSameBrightnessForm.h"
#include "XPropertyMaskingPacket.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GenerateMaskFromSameBrightnessForm::GenerateMaskFromSameBrightnessForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	PickupL=0;
	PickupH=255;
	Effective=true;
	MinPickupSize	=0;
	MaxPickupSize	=100000;
	MinPickupDots	=0;
	MaxPickupDots	=100000000;
	Erosion			=0;

	SetParamToWindow();
	InstallOperationLog(this);
}

GenerateMaskFromSameBrightnessForm::~GenerateMaskFromSameBrightnessForm()
{

}

void GenerateMaskFromSameBrightnessForm::GetParamFromWindow(void)
{
	PickupL=ui.spinBoxL->value();
	PickupH=ui.spinBoxH->value();

	MinPickupSize	=ui.EditMinPickupSize->value();
	MaxPickupSize	=ui.EditMaxPickupSize->value();
	MinPickupDots	=ui.EditMinPickupDots->value();
	MaxPickupDots	=ui.EditMaxPickupDots->value();
	Erosion			=ui.EditErosion->value();
}

void GenerateMaskFromSameBrightnessForm::SetParamToWindow(void)
{
	ui.spinBoxL->setValue(PickupL);
	ui.spinBoxH->setValue(PickupH);

	ui.EditMinPickupSize->setValue(MinPickupSize);
	ui.EditMaxPickupSize->setValue(MaxPickupSize);
	ui.EditMinPickupDots->setValue(MinPickupDots);
	ui.EditMaxPickupDots->setValue(MaxPickupDots);
	ui.EditErosion		->setValue(Erosion);
}

void GenerateMaskFromSameBrightnessForm::on_ButtonEffective_clicked()
{
	GetParamFromWindow();
	Effective=true;
	LimitedLib.RemoveAll();
	done(true);
}

void GenerateMaskFromSameBrightnessForm::on_ButtonNotEffective_clicked()
{
	GetParamFromWindow();
	Effective=false;
	LimitedLib.RemoveAll();
	done(true);
}

void GenerateMaskFromSameBrightnessForm::on_ButtonCancel_clicked()
{
	done(false);
}

void GenerateMaskFromSameBrightnessForm::on_pushButton_clicked()
{
	GetParamFromWindow();

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		GUICmdGenerateMaskInSameColor	Cmd(GetLayersBase(),sRoot,sName,page);
		Cmd.PickupL			=PickupL;
		Cmd.PickupH			=PickupH;
		Cmd.MinPickupSize	=MinPickupSize;
		Cmd.MaxPickupSize	=MaxPickupSize;
		Cmd.MinPickupDots	=MinPickupDots;
		Cmd.MaxPickupDots	=MaxPickupDots;
		Cmd.Erosion			=Erosion;
		Cmd.TestMode		=true;
		Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
	}
}

void GenerateMaskFromSameBrightnessForm::on_pushButtonLimited_clicked()
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	D.exec();
	if(DForm->RetOK==false)
		return;

	GetParamFromWindow();
	LimitedLib	=DForm->GetSelectedList();
	Effective	=DForm->Effective;
	done(true);
}