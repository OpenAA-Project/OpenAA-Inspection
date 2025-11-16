//#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOCR\AddManualItemForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AddManualItemForm.h"
#include "XRememberer.h"

AddManualItemForm::AddManualItemForm(LayersBase *Base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
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

	ui.spinBoxEnsmall	->setValue(ControlRememberer::GetInt(ui.spinBoxEnsmall,3));
	ui.spinBoxEnlarge	->setValue(ControlRememberer::GetInt(ui.spinBoxEnlarge,9));
	ui.spinBoxBlockWidth->setValue(ControlRememberer::GetInt(ui.spinBoxBlockWidth,100));
	ui.spinBoxBlockHeight->setValue(ControlRememberer::GetInt(ui.spinBoxBlockHeight,100));
	ui.spinBoxMinSize	->setValue(ControlRememberer::GetInt(ui.spinBoxMinSize,0));

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

	ui.spinBoxMergin		->setValue(Mergin);
	ui.spinBoxEnsmall		->setValue(EnsmallDot);
	ui.spinBoxEnlarge		->setValue(EnlargeDot);
	ui.spinBoxBlockWidth	->setValue(BlockWidth);
	ui.spinBoxBlockHeight	->setValue(BlockHeight);
	ui.spinBoxMinSize		->setValue(MinSize);
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
	Mergin		=ui.spinBoxMergin		->value();
	EnsmallDot	=ui.spinBoxEnsmall		->value();
	EnlargeDot	=ui.spinBoxEnlarge		->value();
	BlockWidth	=ui.spinBoxBlockWidth	->value();
	BlockHeight	=ui.spinBoxBlockHeight	->value();
	MinSize		=ui.spinBoxMinSize		->value();

	ControlRememberer::SetValue(ui.spinBoxEnsmall		,ui.spinBoxEnsmall->value()		);
	ControlRememberer::SetValue(ui.spinBoxEnlarge		,ui.spinBoxEnlarge->value()		);
	ControlRememberer::SetValue(ui.spinBoxBlockWidth	,ui.spinBoxBlockWidth->value()	);
	ControlRememberer::SetValue(ui.spinBoxBlockHeight	,ui.spinBoxBlockHeight->value()	);
	ControlRememberer::SetValue(ui.spinBoxMinSize		,ui.spinBoxMinSize->value()		);

	done(true);
}

void AddManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}
