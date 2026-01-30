/*
 * Copyright (C) 2014
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

#include "ButtonThresholdResource.h"
#include "ThresholdSettingForm.h"
#include "DetailSettingForm.h"
#include "ButtonThreshold.h"
#include "XGUIDLL.h"

ThresholdSettingForm::ThresholdSettingForm(QWidget *parent,GUIFormBase *Base,PixelInspectionBase *PBase,ChosenPhase *Phase)
	: QDialog(parent)
{
//	Q_INIT_RESOURCE
//	setStyleSheet("border-style: none;font-size: 12pt;");

	ui.setupUi(this);

	GUIBase		=Base;
	PixelBase	=PBase;
	chosenPhase =Phase;

	QString DetailSettingImageBmpFile[5]={
		/**/":Resources/DetailSettingImage.bmp",	//���{��
		/**/":Resources/DetailSettingImage-en.bmp",	//English
		/**/":Resources/DetailSettingImage-en.bmp",	//�ȑ̒���
		/**/":Resources/DetailSettingImage-en.bmp",	//�ɑ̒���
		/**/":Resources/DetailSettingImage-en.bmp"	//Korean
	};

	DecisionImageBmpFile[0]=/**/":Resources/DecisionImage.bmp";		//���{��
	DecisionImageBmpFile[1]=/**/":Resources/DecisionImage-en.bmp";	//English
	DecisionImageBmpFile[2]=/**/":Resources/DecisionImage-en.bmp";	//�ȑ̒���
	DecisionImageBmpFile[3]=/**/":Resources/DecisionImage-en.bmp";	//�ɑ̒���
	DecisionImageBmpFile[4]=/**/":Resources/DecisionImage-en.bmp";	//Korean

	CancelImageBmpFile[0]=/**/":Resources/CancelImage.bmp";		//���{��
	CancelImageBmpFile[1]=/**/":Resources/CancelImage-en.bmp";	//English
	CancelImageBmpFile[2]=/**/":Resources/CancelImage-en.bmp";	//�ȑ̒���
	CancelImageBmpFile[3]=/**/":Resources/CancelImage-en.bmp";	//�ɑ̒���
	CancelImageBmpFile[4]=/**/":Resources/CancelImage-en.bmp";	//Korean

	//�{�^��
	QImage DecisionImage(DecisionImageBmpFile[((ButtonThreshold *)GUIBase)->LanguageCode]);
	BtnDecision=new mtImageToolButton(ui.lbDecision,false);
	BtnDecision->setImageBmp(DecisionImage);
	BtnDecision->setIconSize(QSize(DecisionImage.width(),DecisionImage.height()));
	connect(BtnDecision,SIGNAL(SignalClicked()),this,SLOT(SlotBtnDecisionClicked()));

	QImage DetailSettingImage(DetailSettingImageBmpFile[((ButtonThreshold *)GUIBase)->LanguageCode]);
	BtnDetailSetting=new mtImageToolButton(ui.lbDetailSetting,false);
	BtnDetailSetting->setImageBmp(DetailSettingImage);
	BtnDetailSetting->setIconSize(QSize(DetailSettingImage.width(),DetailSettingImage.height()));
	connect(BtnDetailSetting,SIGNAL(SignalClicked()),this,SLOT(SlotBtnDetailSettingClicked()));
	BtnDetailSetting->setObjectName(/**/"BtnDetailSetting");

	QImage CancelImage(CancelImageBmpFile[((ButtonThreshold *)GUIBase)->LanguageCode]);
	BtnCancel=new mtImageToolButton(ui.lbCancel,false);
	BtnCancel->setImageBmp(CancelImage);
	BtnCancel->setIconSize(QSize(CancelImage.width(),CancelImage.height()));
	connect(BtnCancel,SIGNAL(SignalClicked()),this,SLOT(SlotBtnCancelClicked()));

	//�X���C�_�[
	QImage SliderImage(/**/":Resources/slider.bmp");
	QImage SliderBackImage(/**/":Resources/slider-back.bmp");
//	ImageSlider=new mtImageSlider(SliderImage,SliderBackImage,ui.lbSlider);
//	ImageSlider=new mtImageSlider(1,9,SliderImage,SliderBackImage,ui.lbSlider);
	ImageSlider=new mtImageSlider(1,9,7,25,32,SliderImage,SliderBackImage,ui.lbSlider);

	if(chosenPhase!=NULL)
		PixelBase->GetLayersBase()->TF_SetCurrentScanPhaseNumber(chosenPhase->getPhaseNumber());
	SetInspectionLevel(PixelBase->getInspectionLevel());
}

ThresholdSettingForm::~ThresholdSettingForm()
{
}

void ThresholdSettingForm::SetInspectionLevel(int Value)
{
	int Level;
	if(Value<196){
		Level=1;
	}
	else if(Value<204){
		Level=2;
	}
	else if(Value<212){
		Level=3;
	}
	else if(Value<220){
		Level=4;
	}
	else if(Value<228){
		Level=5;
	}
	else if(Value<236){
		Level=6;
	}
	else if(Value<244){
		Level=7;
	}
	else if(Value<252){
		Level=8;
	}
	else{
		Level=9;
	}
	ImageSlider->setValue(Level);
	InspectionLevel=Level;
}

void ThresholdSettingForm::SlotBtnDecisionClicked()
{
	InspectionLevel=ImageSlider->getValue();
	accept();
}

void ThresholdSettingForm::SlotBtnDetailSettingClicked()
{
	//�ڍ׉���
	DetailSettingForm	DetailSetting(this,GUIBase,PixelBase);

	//�������x���̑ޔ�
	InspectionLevel=ImageSlider->getValue();

	if(DetailSetting.exec()==false){
///		return;
	}

	//���ʐݒ�
///	ImageSlider->setValue(InspectionLevel);
}

void ThresholdSettingForm::SlotBtnCancelClicked()
{
	reject();
}