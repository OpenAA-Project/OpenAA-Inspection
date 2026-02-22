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

#include "ShowCameraDialog.h"
#include "ui_ShowCameraDialog.h"

ShowCameraDialog::ShowCameraDialog(CameraMVSGigE *Cam,QWidget *parent) :
    QDialog(parent)
    ,Parent(Cam)
    ,ui(new Ui::ShowCameraDialog)
{
    ui->setupUi(this);

	ExposureTime			=Cam->ExposureTime			;
	Gain					=Cam->Gain					;
	FrameRate				=Cam->FrameRate				;
	bSoftWareTriggerCheck	=Cam->bSoftWareTriggerCheck	;
	TriggerSource			=Cam->TriggerSource			;
    TriggerMode				=Cam->TriggerMode			;
    TriggerSource			=Cam->TriggerSource			;
    ExposureMode			=Cam->ExposureMode	;
    BinningHMode			=Cam->BinningHMode	;
	BinningVMode			=Cam->BinningVMode	;
    DecimationH				=Cam->DecimationH	;
	DecimationV				=Cam->DecimationV	;
    ReverseX				=Cam->ReverseX    ;
    ReverseY				=Cam->ReverseY    ;   
    AOIMode					=Cam->AOIMode     ;
    AOIOffsetX				=Cam->AOIOffsetX  ;
    AOIOffsetY				=Cam->AOIOffsetY  ;
    AOIWidth				=Cam->AOIWidth    ;
    AOIHeight				=Cam->AOIHeight   ;

	ui->lineEditDeviceName->setText(Cam->UserName);
	ui->lineEditIPAddress->setText(Cam->IPAddress);

	float	CurrentFloatValue ,MaxFloatValue ,MinFloatValue;
	if(Cam->GetfloatValue("ExposureTime",CurrentFloatValue ,MaxFloatValue ,MinFloatValue)==true){
		ui->doubleSpinBoxExposureTime	->setMaximum(MaxFloatValue);
		ui->doubleSpinBoxExposureTime	->setMinimum(MinFloatValue);
		ui->doubleSpinBoxExposureTime	->setValue	(CurrentFloatValue);
	}
	if(Cam->GetfloatValue("Gain",CurrentFloatValue ,MaxFloatValue ,MinFloatValue)==true){
		ui->doubleSpinBoxGain	->setMaximum(MaxFloatValue);
		ui->doubleSpinBoxGain	->setMinimum(MinFloatValue);
		ui->doubleSpinBoxGain	->setValue	(CurrentFloatValue);
	}

	int CurrentIntValue;
	int	EnumCount;
	if(Cam->GetEnumValue ("ExposureAuto",CurrentIntValue ,EnumExposureAutoData,EnumCount)==true){
		ui->comboBoxExposureAuto->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Cam->GetEnumSymblic ("ExposureAuto",EnumExposureAutoData[i] ,Str)==true){
				ui->comboBoxExposureAuto->addItem(Str);
				if(CurrentIntValue==EnumExposureAutoData[i]){
					ui->comboBoxExposureAuto->setCurrentIndex(i);
				}
			}
		}
	}
	if(Cam->GetEnumValue ("ExposureMode",CurrentIntValue ,EnumExposureModeData,EnumCount)==true){
		ui->comboBoxExposureMode->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Cam->GetEnumSymblic ("ExposureMode",EnumExposureModeData[i] ,Str)==true){
				ui->comboBoxExposureMode->addItem(Str);
				if(CurrentIntValue==EnumExposureModeData[i]){
					ui->comboBoxExposureMode->setCurrentIndex(i);
				}
			}
		}
	}

	int		CurrentIntValueH ,MaxIntValueH ,MinIntValueH;
	int		CurrentIntValueV ,MaxIntValueV ,MinIntValueV;
	bool	RetH=Cam->GetIntValue("BinningHorizontal",CurrentIntValueH ,MaxIntValueH ,MinIntValueH);
	bool	RetV=Cam->GetIntValue("BinningVertical"	 ,CurrentIntValueV ,MaxIntValueV ,MinIntValueV);
	int	BinningIndex=0;
	if(RetH==true && RetV==true){
		ui->comboBoxBinning->clear();
		int	Index;
		for(int x=MinIntValueH;x<=MaxIntValueH;x++){
			for(int y=MinIntValueV;y<=MaxIntValueV;y++){
				QString	s=QString::number(x) + QString(" X ") + QString::number(y);
				int	Data=y*1000+x;
				ui->comboBoxBinning->addItem(s,QVariant(Data));
				if(CurrentIntValueH==x && CurrentIntValueV==y){
					BinningIndex=Index;
				}
				Index++;
			}
		}
	}
	ui->comboBoxBinning->setCurrentIndex(BinningIndex);

	RetH=Cam->GetIntValue("DecimationHorizontal",CurrentIntValueH ,MaxIntValueH ,MinIntValueH);
	RetV=Cam->GetIntValue("DecimationVertical"	,CurrentIntValueV ,MaxIntValueV ,MinIntValueV);
	int	DecimationIndex=0;
	if(RetH==true && RetV==true){
		ui->comboBoxDecimation->clear();
		int	Index;
		for(int x=MinIntValueH;x<=MaxIntValueH;x++){
			for(int y=MinIntValueV;y<=MaxIntValueV;y++){
				QString	s=QString::number(x) + QString(" X ") + QString::number(y);
				int	Data=y*1000+x;
				ui->comboBoxDecimation->addItem(s,QVariant(Data));
				if(CurrentIntValueH==x && CurrentIntValueV==y){
					DecimationIndex=Index;
				}
				Index++;
			}
		}
	}
	ui->comboBoxDecimation->setCurrentIndex(DecimationIndex);


	if(Cam->GetEnumValue ("TriggerMode",CurrentIntValue ,EnumTriggerModeData,EnumCount)==true){
		ui->comboBoxTriggerMode->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Cam->GetEnumSymblic ("TriggerMode",EnumTriggerModeData[i] ,Str)==true){
				ui->comboBoxTriggerMode->addItem(Str);
				if(CurrentIntValue==EnumTriggerModeData[i]){
					ui->comboBoxTriggerMode->setCurrentIndex(i);
				}
			}
		}
	}
	if(Cam->GetEnumValue ("TriggerSource",CurrentIntValue ,EnumTriggerSourceData,EnumCount)==true){
		ui->comboBoxTriggerSource->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Cam->GetEnumSymblic ("TriggerSource",EnumTriggerSourceData[i] ,Str)==true){
				ui->comboBoxTriggerSource->addItem(Str);
				if(CurrentIntValue==EnumTriggerSourceData[i]){
					ui->comboBoxTriggerSource->setCurrentIndex(i);
				}
			}
		}
	}
	bool	CurrentBoolValue;
	if(Cam->GetBoolValue("ReverseX",CurrentBoolValue )==true){
		ui->checkBoxReverseX	->setChecked(CurrentBoolValue);
	}
	if(Cam->GetBoolValue("ReverseY",CurrentBoolValue )==true){
		ui->checkBoxReverseY	->setChecked(CurrentBoolValue);
	}

	int	Width ,Height;
	Parent->GetResolution(Width ,Height);
	int	MaxIntValue ,MinIntValue;
	int	CurrentOffsetXValue,CurrentOffsetYValue;
	if(Cam->GetIntValue("OffsetX",CurrentOffsetXValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIOffsetX	->setMaximum(Width);
		ui->spinBoxAOIOffsetX	->setMinimum(MinIntValue);
		ui->spinBoxAOIOffsetX	->setValue	(CurrentOffsetXValue);
	}
	if(Cam->GetIntValue("OffsetY",CurrentOffsetYValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIOffsetY	->setMaximum(Height);
		ui->spinBoxAOIOffsetY	->setMinimum(MinIntValue);
		ui->spinBoxAOIOffsetY	->setValue	(CurrentOffsetYValue);
	}
	if(Cam->GetIntValue("Width",CurrentIntValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIWidth		->setMaximum(MaxIntValue);
		ui->spinBoxAOIWidth		->setMinimum(MinIntValue);
		ui->spinBoxAOIWidth		->setValue	(CurrentIntValue);
	}
	if(Cam->GetIntValue("Height",CurrentIntValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIHeight	->setMaximum(MaxIntValue);
		ui->spinBoxAOIHeight	->setMinimum(MinIntValue);
		ui->spinBoxAOIHeight	->setValue	(CurrentIntValue);
	}
}

ShowCameraDialog::~ShowCameraDialog()
{
    delete ui;
}

void ShowCameraDialog::on_pushButtonOK_clicked()
{
	ExposureTime	=ui->doubleSpinBoxExposureTime	->value();
	Gain			=ui->doubleSpinBoxGain		->value();

	int	IndexExposureMode	=ui->comboBoxExposureMode->currentIndex();
	ExposureMode	=EnumExposureModeData[IndexExposureMode];
	int	IndexExposureAuto	=ui->comboBoxExposureAuto->currentIndex();
	ExposureAuto	=EnumExposureAutoData[IndexExposureAuto];

	int	TriggerModeIndex=ui->comboBoxTriggerMode->currentIndex();
	TriggerMode		=EnumTriggerModeData[TriggerModeIndex];
	int	TriggerSourceIndex=ui->comboBoxTriggerSource->currentIndex();
	TriggerSource	= EnumTriggerSourceData[TriggerSourceIndex];

	int	BinningIndex=ui->comboBoxBinning->currentIndex();
	QVariant	VBinningData=ui->comboBoxBinning->currentData();
	int	BinningData=VBinningData.toInt();
	BinningHMode	=BinningData%1000;
	BinningVMode	=BinningData/1000;

	int	DecimationIndex=ui->comboBoxDecimation->currentIndex();
	QVariant	VDecimationData=ui->comboBoxDecimation->currentData();
	int	DecimationData=VDecimationData.toInt();
	DecimationH 	=DecimationData%1000;
	DecimationV 	=DecimationData/1000;


	ReverseX	=ui->checkBoxReverseX	->isChecked();
	ReverseX	=ui->checkBoxReverseY	->isChecked();

	AOIOffsetX	=ui->spinBoxAOIOffsetX	->value();
	AOIOffsetY	=ui->spinBoxAOIOffsetY	->value();
	AOIWidth	=ui->spinBoxAOIWidth	->value();
	AOIHeight	=ui->spinBoxAOIHeight	->value();

	done(true);
}


void ShowCameraDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void ShowCameraDialog::on_spinBoxAOIOffsetX_valueChanged(int arg1)
{
	int	tAOIOffsetX	=ui->spinBoxAOIOffsetX	->value();

	int	Width ,Height;
	Parent->GetResolution(Width ,Height);
	int	W=Width-tAOIOffsetX;
	W=W & 0xFFF0;
	ui->spinBoxAOIWidth	->setMaximum(W);
}


void ShowCameraDialog::on_spinBoxAOIOffsetY_valueChanged(int arg1)
{
	int	tAOIOffsetY	=ui->spinBoxAOIOffsetY	->value();

	int	Width ,Height;
	Parent->GetResolution(Width ,Height);
	int	H=Height-tAOIOffsetY;
	H=H & 0xFFF0;
	ui->spinBoxAOIHeight->setMaximum(H);
}

