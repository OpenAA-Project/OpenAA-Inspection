#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\AddMonoManualItemForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AddMonoManualItemForm.h"
#include "XRememberer.h"

AddMonoManualItemForm::AddMonoManualItemForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent) ,ServiceForLayers(base)
{
	ui.setupUi(this);

	AbsLR=AbsHR	=0;
	EnsmallDot	=3;
	EnlargeDot	=5;
	BlockWidth	=100;
	BlockHeight	=100;
	OpeType=DynamicMaskingPIThreshold::_PickupMask;
	DrawColR	=100;
	AbsLR2=AbsHR2	=0;
	EnsmallDot2	=3;
	EnlargeDot2	=5;
	DrawColR2	=100;
	MinSize		=0;

	ui.spinBoxDark		->setValue(ControlRememberer::GetInt(ui.spinBoxDark,0));
	ui.spinBoxLight		->setValue(ControlRememberer::GetInt(ui.spinBoxLight,30));
	ui.spinBoxEnsmall	->setValue(ControlRememberer::GetInt(ui.spinBoxEnsmall,3));
	ui.spinBoxEnlarge	->setValue(ControlRememberer::GetInt(ui.spinBoxEnlarge,9));
	ui.spinBoxBlockWidth->setValue(ControlRememberer::GetInt(ui.spinBoxBlockWidth,100));
	ui.spinBoxBlockHeight->setValue(ControlRememberer::GetInt(ui.spinBoxBlockHeight,100));
	ui.spinBoxMinSize	->setValue(ControlRememberer::GetInt(ui.spinBoxMinSize,0));

	ui.radioButtonPickupMask->setChecked(ControlRememberer::GetBool(ui.radioButtonPickupMask,true));
	ui.radioButtonDrawMask	->setChecked(ControlRememberer::GetBool(ui.radioButtonDrawMask,false));
	ui.radioButtonDrawMask_2->setChecked(ControlRememberer::GetBool(ui.radioButtonDrawMask_2,false));

	on_radioButtonPickupMask_toggled(true);
	on_radioButtonDrawMask_toggled(true);
	on_radioButtonDrawMask_2_toggled(true);
	ui.spinBoxDrawCol->setValue(ControlRememberer::GetInt(ui.spinBoxDrawCol,100));

	ui.spinBoxDark_2	->setValue(ControlRememberer::GetInt(ui.spinBoxDark_2,0));
	ui.spinBoxLight_2	->setValue(ControlRememberer::GetInt(ui.spinBoxLight_2,30));
	ui.spinBoxEnsmall_2	->setValue(ControlRememberer::GetInt(ui.spinBoxEnsmall_2,3));
	ui.spinBoxEnlarge_2	->setValue(ControlRememberer::GetInt(ui.spinBoxEnlarge_2,9));
	ui.spinBoxDrawCol_2->setValue(ControlRememberer::GetInt(ui.spinBoxDrawCol_2,100));

	ui.spinBoxDarkG		->setValue(ControlRememberer::GetInt(ui.spinBoxDarkG,0));
	ui.spinBoxLightG	->setValue(ControlRememberer::GetInt(ui.spinBoxLightG,30));
	ui.spinBoxDarkB		->setValue(ControlRememberer::GetInt(ui.spinBoxDarkB,0));
	ui.spinBoxLightB	->setValue(ControlRememberer::GetInt(ui.spinBoxLightB,30));

	int	Page=0;
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui.framePickupLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(false);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		connect(LayerButton,SIGNAL(clicked()),this,SLOT(on_toolButtonLayer_clicked()));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerPickupButtons.append(LayerButton);
	}
	QToolButton	*LayerB0=LayerPickupButtons[0];
	LayerB0->setChecked(true);
	on_toolButtonLayer_clicked();

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

	if(OpeType==DynamicMaskingPIThreshold::_PickupMask)
		ui.radioButtonPickupMask->setChecked(true);
	if(OpeType==DynamicMaskingPIThreshold::_DrawMask)
		ui.radioButtonDrawMask->setChecked(true);
	if(OpeType==DynamicMaskingPIThreshold::_DynamicDrawMask)
		ui.radioButtonDrawMask_2->setChecked(true);
		;
	ui.spinBoxDrawCol		->setValue(DrawColR);

	ui.spinBoxDark_2		->setValue(AbsLR2);
	ui.spinBoxLight_2		->setValue(AbsHR2);
	ui.spinBoxEnsmall_2		->setValue(EnsmallDot2);
	ui.spinBoxEnlarge_2		->setValue(EnlargeDot2);
	ui.spinBoxDrawCol_2		->setValue(DrawColR2);

	ui.spinBoxDarkG			->setValue(AbsLG);
	ui.spinBoxLightG		->setValue(AbsHG);
	ui.spinBoxDarkB			->setValue(AbsLB);
	ui.spinBoxLightB		->setValue(AbsHB);
	int	Page=0;
	for(IntClass *a=AdaptedPickupLayers.GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(Page)){
			LayerPickupButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		bool	Found=false;
		for(IntClass *a=AdaptedPickupLayers.GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerPickupButtons[Layer]->setChecked(false);
		}
	}
	on_toolButtonLayer_clicked();
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

	if(ui.radioButtonPickupMask->isChecked()==true)
		OpeType=DynamicMaskingPIThreshold::_PickupMask;
	if(ui.radioButtonDrawMask->isChecked()==true)
		OpeType=DynamicMaskingPIThreshold::_DrawMask;
	if(ui.radioButtonDrawMask_2->isChecked()==true)
		OpeType=DynamicMaskingPIThreshold::_DynamicDrawMask;
	DrawColR	=ui.spinBoxDrawCol->value();

	AbsLR2		=ui.spinBoxDark_2		->value();
	AbsHR2		=ui.spinBoxLight_2		->value();
	EnsmallDot2	=ui.spinBoxEnsmall_2	->value();
	EnlargeDot2	=ui.spinBoxEnlarge_2	->value();
	DrawColR2	=ui.spinBoxDrawCol_2	->value();

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

	ControlRememberer::SetValue(ui.radioButtonPickupMask,ui.radioButtonPickupMask->isChecked()	);
	ControlRememberer::SetValue(ui.radioButtonDrawMask	,ui.radioButtonDrawMask->isChecked()	);
	ControlRememberer::SetValue(ui.radioButtonDrawMask_2,ui.radioButtonDrawMask_2->isChecked()	);
	ControlRememberer::SetValue(ui.spinBoxDrawCol		,ui.spinBoxDrawCol->value()				);

	ControlRememberer::SetValue(ui.spinBoxDark_2		,ui.spinBoxDark_2->value()		);
	ControlRememberer::SetValue(ui.spinBoxLight_2		,ui.spinBoxLight_2->value()		);
	ControlRememberer::SetValue(ui.spinBoxEnsmall_2		,ui.spinBoxEnsmall_2->value()		);
	ControlRememberer::SetValue(ui.spinBoxEnlarge_2		,ui.spinBoxEnlarge_2->value()		);
	ControlRememberer::SetValue(ui.spinBoxDrawCol_2		,ui.spinBoxDrawCol_2->value()				);

	IntList	LayersPickupList;
	for(int Layer=0;Layer<LayerPickupButtons.count();Layer++){
		if(LayerPickupButtons[Layer]->isChecked()==true){
			LayersPickupList.Add(Layer);
		}
	}
	AdaptedPickupLayers=LayersPickupList;

	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}


void AddMonoManualItemForm::on_radioButtonPickupMask_toggled(bool)
{
	if(ui.radioButtonPickupMask->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(0);
	}
}

void AddMonoManualItemForm::on_radioButtonDrawMask_toggled(bool)
{
	if(ui.radioButtonDrawMask->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(1);
	}
}

void AddMonoManualItemForm::on_pushButtonOKDrawMask_clicked()
{
	on_pushButtonOK_clicked();
}

void AddMonoManualItemForm::on_pushButtonCancelDrawMask_clicked()
{
	done(false);
}

void AddMonoManualItemForm::on_radioButtonDrawMask_2_toggled(bool)
{
	if(ui.radioButtonDrawMask_2->isChecked()==true){
		ui.stackedWidget->setCurrentIndex(2);
	}
}

void AddMonoManualItemForm::on_pushButtonCancelDrawMask_2_clicked()
{
	done(false);
}

void AddMonoManualItemForm::on_pushButtonOKDrawMask_2_clicked()
{
	on_pushButtonOK_clicked();
}
void AddMonoManualItemForm::on_toolButtonLayer_clicked()
{
	for(int Layer=0;Layer<3;Layer++){
		if(Layer<GetLayerNumb(0)){
			QToolButton	*LayerB=LayerPickupButtons[Layer];
			if(LayerB->isChecked()==true){
				if(Layer==0){
					ui.spinBoxDark	->setEnabled(true);
					ui.spinBoxLight->setEnabled(true);
				}
				else if(Layer==1){
					ui.spinBoxDarkG	->setEnabled(true);
					ui.spinBoxLightG	->setEnabled(true);
				}
				else if(Layer==2){
					ui.spinBoxDarkB	->setEnabled(true);
					ui.spinBoxLightB	->setEnabled(true);
				}
			}
			else{
				if(Layer==0){
					ui.spinBoxDark	->setEnabled(false);
					ui.spinBoxLight->setEnabled(false);
				}
				else if(Layer==1){
					ui.spinBoxDarkG	->setEnabled(false);
					ui.spinBoxLightG	->setEnabled(false);
				}
				else if(Layer==2){
					ui.spinBoxDarkB	->setEnabled(false);
					ui.spinBoxLightB	->setEnabled(false);
				}
			}
		}
		else{
			if(Layer==0){
				ui.spinBoxDark	->setEnabled(false);
				ui.spinBoxLight->setEnabled(false);
			}
			else if(Layer==1){
				ui.spinBoxDarkG	->setEnabled(false);
				ui.spinBoxLightG	->setEnabled(false);
			}
			else if(Layer==2){
				ui.spinBoxDarkB	->setEnabled(false);
				ui.spinBoxLightB	->setEnabled(false);
			}
		}
	}

}
