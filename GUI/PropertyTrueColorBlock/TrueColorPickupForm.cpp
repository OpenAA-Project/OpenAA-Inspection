/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\TrueColorPickupForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TrueColorFormResource.h"
#include "TrueColorPickupForm.h"
#include "XDataInLayer.h"

TrueColorPickupForm::TrueColorPickupForm(LayersBase *Base
										,RGBStock *Stocker
										,ColorLogic *ArgLogic
										,QWidget *parent )
	: QDialog(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ColorPanel.Cube.ClearAll();
	ColorPanel.setParent(ui.frameColorCube);
	if(ArgLogic!=NULL){
		ColorPanel.Cube=*ArgLogic;
	}
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

TrueColorPickupForm::~TrueColorPickupForm()
{

}


void TrueColorPickupForm::on_pushButtonClose_clicked()
{
	done((int)false);
}


void	TrueColorPickupForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorPanel.Cube);
}
void	TrueColorPickupForm::SlotColorSampleSelectOne()
{
	ColorPanel.Cube=*ColorSamples.CData.GetColorLogic();
	ColorPanel.InitializedDoneCube();
	ColorPanel.Repaint();
}


void TrueColorPickupForm::on_pushButtonSetToColor_clicked()
{
	done((int)true);
}

void TrueColorPickupForm::on_pushButtonEliminateColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()!=NULL){
		ColorPanel.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
		ColorPanel.Repaint();
	}
}

void TrueColorPickupForm::on_pushButtonAddColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()!=NULL){
		ColorPanel.Cube.Add(*ColorSamples.CData.GetColorLogic());
		ColorPanel.Repaint();
	}
}

void TrueColorPickupForm::on_pushButtonClearColor_clicked()
{
	ColorPanel.Cube.ClearAll();
	ColorPanel.Repaint();
}

void TrueColorPickupForm::on_pushButtonClearBaseColor_clicked()
{
	ColorPanel.Cube.ClearBase();
	ColorPanel.Repaint();
}

void TrueColorPickupForm::on_pushButtonClearEliminateColor_clicked()
{
	ColorPanel.Cube.ClearEliminate();
	ColorPanel.Repaint();
}