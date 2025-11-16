#include "CreateManualEulerRingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\EulerRingPickupForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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