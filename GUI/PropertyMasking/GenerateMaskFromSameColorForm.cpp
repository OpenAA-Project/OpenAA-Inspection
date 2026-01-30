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
#include "GenerateMaskFromSameColorForm.h"
#include "XDataInLayerCommander.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include "XPropertyMaskingPacket.h"
#include "SelectLibraryInMaskForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GenerateMaskFromSameColorForm::GenerateMaskFromSameColorForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);

	ColorThre		.setParent(ui.frameThreshold);
	ColorThre		.Fit(ui.frameThreshold);

	connect(&ColorThre,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorThre,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	RGBPanel.setParent(ui.frameShowColorSmples);
	RGBPanel.Fit(ui.frameShowColorSmples);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"MaskingImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*Display=dynamic_cast<DisplayImage *>(GProp);
		if(Display!=NULL){
			PickupColor=Display->GetPickedColor();
			PickupColorFrame.setParent(ui.framePickupColor);
			PickupColorFrame.move(0,0);
			PickupColorFrame.resize(ui.framePickupColor->width(),ui.framePickupColor->height());
			PickupColorFrame.SetColor(PickupColor);
			RGBPanel.Cube=Display->GetRGBStock();
			RGBPanel.InitializedDoneCube();
		}
	}

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	MinPickupSize	=0;
	MaxPickupSize	=100000;
	MinPickupDots	=0;
	MaxPickupDots	=100000000;
	Erosion			=0;

	SetParamToWindow();
	InstallOperationLog(this);
}

GenerateMaskFromSameColorForm::~GenerateMaskFromSameColorForm()
{

}



void GenerateMaskFromSameColorForm::GetParamFromWindow(void)
{
	MinPickupSize	=ui.EditMinPickupSize->value();
	MaxPickupSize	=ui.EditMaxPickupSize->value();
	MinPickupDots	=ui.EditMinPickupDots->value();
	MaxPickupDots	=ui.EditMaxPickupDots->value();
	Erosion			=ui.EditErosion->value();
}

void GenerateMaskFromSameColorForm::SetParamToWindow(void)
{
	ui.EditMinPickupSize->setValue(MinPickupSize);
	ui.EditMaxPickupSize->setValue(MaxPickupSize);
	ui.EditMinPickupDots->setValue(MinPickupDots);
	ui.EditMaxPickupDots->setValue(MaxPickupDots);
	ui.EditErosion		->setValue(Erosion);
}

void GenerateMaskFromSameColorForm::ShowThresholdList(void)
{
	ui.listWidgetBaseColor->clear();
	ui.listWidgetEliminatedColor->clear();
	int	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstBase();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetBaseColor->addItem(QString::number(N));
	}
	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstEliminated();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetEliminatedColor->addItem(QString::number(N));
	}
}

void GenerateMaskFromSameColorForm::on_pushButtonAddColor_clicked()
{
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_pushButtonEliminateColor_clicked()
{
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(),ui.spinBoxMerginAddPickupColor->value());
	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(),ui.spinBoxMerginSubPickupColor->value());
	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_pushButtonAddColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube,RGBPanel.Ext);
	ColorThre.Cube.Add(*Sample.GetColorLogic(),0);

	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_pushButtonEliminateColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube);
	ColorThre.Cube.Eliminate(*Sample.GetColorLogic(),0);

	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetBaseColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetBase(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveBase(c);
		delete	c;
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetEliminatedColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetEliminated(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void GenerateMaskFromSameColorForm::on_pushButton_clicked()
{
	GetParamFromWindow();

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		GUICmdGenerateMaskInSameColor	Cmd(GetLayersBase(),sRoot,sName,page);
		Cmd.MinPickupSize	=MinPickupSize;
		Cmd.MaxPickupSize	=MaxPickupSize;
		Cmd.MinPickupDots	=MinPickupDots;
		Cmd.MaxPickupDots	=MaxPickupDots;
		Cmd.Erosion			=Erosion;
		Cmd.TestMode		=true;
		PouredColor=ColorThre.Cube;
		Cmd.PickupColor		=PouredColor;
		Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
	}
}


void GenerateMaskFromSameColorForm::on_pushButtonEffective_clicked()
{
	PouredColor=ColorThre.Cube;
	GetParamFromWindow();
	Effective=true;
	LimitedLib.RemoveAll();
	done(true);
}

void GenerateMaskFromSameColorForm::on_pushButtonNonEffective_clicked()
{
	PouredColor=ColorThre.Cube;
	GetParamFromWindow();
	Effective=false;
	LimitedLib.RemoveAll();
	done(true);
}

void GenerateMaskFromSameColorForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void GenerateMaskFromSameColorForm::on_pushButtonLimited_clicked()
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	D.exec();
	if(DForm->RetOK==false)
		return;
	PouredColor=ColorThre.Cube;
	GetParamFromWindow();
	LimitedLib	=DForm->GetSelectedList();
	Effective	=DForm->Effective;
	done(true);
}