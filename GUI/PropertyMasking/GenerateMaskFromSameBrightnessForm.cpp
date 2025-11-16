/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\GenerateMaskFromSameColorForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
