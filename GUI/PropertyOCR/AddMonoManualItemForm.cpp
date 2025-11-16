//#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOCR\AddMonoManualItemForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AddMonoManualItemForm.h"
#include "XRememberer.h"
#include "XDataInLayer.h"

AddMonoManualItemForm::AddMonoManualItemForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent) ,ServiceForLayers(base)
{
	ui.setupUi(this);

	AbsLR=AbsHR	=0;
	EnsmallDot	=3;
	EnlargeDot	=5;
	BlockWidth	=100;
	BlockHeight	=100;
	MinSize		=0;

	ui.spinBoxDark		->setValue(ControlRememberer::GetInt(ui.spinBoxDark,0));
	ui.spinBoxLight		->setValue(ControlRememberer::GetInt(ui.spinBoxLight,30));
	ui.spinBoxEnsmall	->setValue(ControlRememberer::GetInt(ui.spinBoxEnsmall,3));
	ui.spinBoxEnlarge	->setValue(ControlRememberer::GetInt(ui.spinBoxEnlarge,9));
	ui.spinBoxBlockWidth->setValue(ControlRememberer::GetInt(ui.spinBoxBlockWidth,100));
	ui.spinBoxBlockHeight->setValue(ControlRememberer::GetInt(ui.spinBoxBlockHeight,100));
	ui.spinBoxMinSize	->setValue(ControlRememberer::GetInt(ui.spinBoxMinSize,0));

	ui.spinBoxDarkG		->setValue(ControlRememberer::GetInt(ui.spinBoxDarkG,0));
	ui.spinBoxLightG	->setValue(ControlRememberer::GetInt(ui.spinBoxLightG,30));
	ui.spinBoxDarkB		->setValue(ControlRememberer::GetInt(ui.spinBoxDarkB,0));
	ui.spinBoxLightB	->setValue(ControlRememberer::GetInt(ui.spinBoxLightB,30));

	ui.spinBoxDark_2		->setValue(ControlRememberer::GetInt(ui.spinBoxDark_2,0));
	ui.spinBoxLight_2		->setValue(ControlRememberer::GetInt(ui.spinBoxLight_2,30));
	ui.spinBoxEnsmall_2		->setValue(ControlRememberer::GetInt(ui.spinBoxEnsmall_2,3));
	ui.spinBoxEnlarge_2		->setValue(ControlRememberer::GetInt(ui.spinBoxEnlarge_2,9));
	ui.spinBoxBlockWidth_2	->setValue(ControlRememberer::GetInt(ui.spinBoxBlockWidth_2,100));
	ui.spinBoxBlockHeight_2	->setValue(ControlRememberer::GetInt(ui.spinBoxBlockHeight_2,100));
	ui.spinBoxMinSize_2		->setValue(ControlRememberer::GetInt(ui.spinBoxMinSize_2,0));

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb==1)
		ui.stackedWidget->setCurrentIndex(2);
	else
		ui.stackedWidget->setCurrentIndex(0);

	InstallOperationLog(this);
}

AddMonoManualItemForm::~AddMonoManualItemForm()
{

}

void	AddMonoManualItemForm::SetInitial(void)
{
	ui.spinBoxDark			->setValue(AbsLR);
	ui.spinBoxLight			->setValue(AbsHR);
	ui.spinBoxEnsmall		->setValue(EnsmallDot);
	ui.spinBoxEnlarge		->setValue(EnlargeDot);
	ui.spinBoxBlockWidth	->setValue(BlockWidth);
	ui.spinBoxBlockHeight	->setValue(BlockHeight);
	ui.spinBoxMinSize		->setValue(MinSize);

	ui.spinBoxDark_2		->setValue(AbsLR);
	ui.spinBoxLight_2		->setValue(AbsHR);
	ui.spinBoxEnsmall_2		->setValue(EnsmallDot);
	ui.spinBoxEnlarge_2		->setValue(EnlargeDot);
	ui.spinBoxBlockWidth_2	->setValue(BlockWidth);
	ui.spinBoxBlockHeight_2	->setValue(BlockHeight);
	ui.spinBoxMinSize_2		->setValue(MinSize);

	ui.spinBoxDarkG			->setValue(AbsLG);
	ui.spinBoxLightG		->setValue(AbsHG);
	ui.spinBoxDarkB			->setValue(AbsLB);
	ui.spinBoxLightB		->setValue(AbsHB);
}

void AddMonoManualItemForm::on_pushButtonOK_clicked()
{
	AbsLR		=ui.spinBoxDark		->value();
	AbsHR		=ui.spinBoxLight	->value();
	EnsmallDot	=ui.spinBoxEnsmall	->value();
	EnlargeDot	=ui.spinBoxEnlarge	->value();
	BlockWidth	=ui.spinBoxBlockWidth->value();
	BlockHeight	=ui.spinBoxBlockHeight->value();
	MinSize		=ui.spinBoxMinSize	->value();

	AbsLG	=ui.spinBoxDarkG		->value();
	AbsHG	=ui.spinBoxLightG		->value();
	AbsLB	=ui.spinBoxDarkB		->value();
	AbsHB	=ui.spinBoxLightB		->value();

	ControlRememberer::SetValue(ui.spinBoxDark			,ui.spinBoxDark->value()		);
	ControlRememberer::SetValue(ui.spinBoxLight			,ui.spinBoxLight->value()		);
	ControlRememberer::SetValue(ui.spinBoxEnsmall		,ui.spinBoxEnsmall->value()		);
	ControlRememberer::SetValue(ui.spinBoxEnlarge		,ui.spinBoxEnlarge->value()		);
	ControlRememberer::SetValue(ui.spinBoxBlockWidth	,ui.spinBoxBlockWidth->value()	);
	ControlRememberer::SetValue(ui.spinBoxBlockHeight	,ui.spinBoxBlockHeight->value()	);
	ControlRememberer::SetValue(ui.spinBoxMinSize		,ui.spinBoxMinSize->value()		);

	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}



void AddMonoManualItemForm::on_pushButtonOK_2_clicked()
{
	AbsLR		=ui.spinBoxDark_2		->value();
	AbsHR		=ui.spinBoxLight_2		->value();
	EnsmallDot	=ui.spinBoxEnsmall_2	->value();
	EnlargeDot	=ui.spinBoxEnlarge_2	->value();
	BlockWidth	=ui.spinBoxBlockWidth_2	->value();
	BlockHeight	=ui.spinBoxBlockHeight_2->value();
	MinSize		=ui.spinBoxMinSize_2	->value();

	ControlRememberer::SetValue(ui.spinBoxDark_2		,ui.spinBoxDark_2		->value()	);
	ControlRememberer::SetValue(ui.spinBoxLight_2		,ui.spinBoxLight_2		->value()	);
	ControlRememberer::SetValue(ui.spinBoxEnsmall_2		,ui.spinBoxEnsmall_2	->value()	);
	ControlRememberer::SetValue(ui.spinBoxEnlarge_2		,ui.spinBoxEnlarge_2	->value()	);
	ControlRememberer::SetValue(ui.spinBoxBlockWidth_2	,ui.spinBoxBlockWidth_2	->value()	);
	ControlRememberer::SetValue(ui.spinBoxBlockHeight_2	,ui.spinBoxBlockHeight_2->value()	);
	ControlRememberer::SetValue(ui.spinBoxMinSize_2		,ui.spinBoxMinSize_2	->value()	);

	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_2_clicked()
{
	done(false);
}
