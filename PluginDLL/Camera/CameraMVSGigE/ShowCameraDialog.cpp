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
	BlackLevelEnable		=Cam->BlackLevelEnable;
	BlackLevel				=Cam->BlackLevel      ;
	WhiteBalance			=Cam->WhiteBalance;
	BalanceRatioR               =Cam->BalanceRatioR               ;
	BalanceRatioG               =Cam->BalanceRatioG               ;
	BalanceRatioB               =Cam->BalanceRatioB               ;
	BalanceColorTemperatureMode =Cam->BalanceColorTemperatureMode ;

	ui->lineEditDeviceName->setText(Cam->UserName);
	ui->lineEditIPAddress->setText(Cam->IPAddress);
	ShowData();
}

void	ShowCameraDialog::ShowData(void)
{
	float	CurrentFloatValue ,MaxFloatValue ,MinFloatValue;
	if(Parent->GetfloatValue("ExposureTime",CurrentFloatValue ,MaxFloatValue ,MinFloatValue)==true){
		ui->doubleSpinBoxExposureTime	->setMaximum(MaxFloatValue);
		ui->doubleSpinBoxExposureTime	->setMinimum(MinFloatValue);
		ui->doubleSpinBoxExposureTime	->setValue	(CurrentFloatValue);
	}
	if(Parent->GetfloatValue("Gain",CurrentFloatValue ,MaxFloatValue ,MinFloatValue)==true){
		ui->doubleSpinBoxGain	->setMaximum(MaxFloatValue);
		ui->doubleSpinBoxGain	->setMinimum(MinFloatValue);
		ui->doubleSpinBoxGain	->setValue	(CurrentFloatValue);
	}

	int CurrentIntValue;
	int	EnumCount;
	if(Parent->GetEnumValue ("ExposureAuto",CurrentIntValue ,EnumExposureAutoData,EnumCount)==true){
		ui->comboBoxExposureAuto->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("ExposureAuto",EnumExposureAutoData[i] ,Str)==true){
				ui->comboBoxExposureAuto->addItem(Str);
				if(CurrentIntValue==EnumExposureAutoData[i]){
					ui->comboBoxExposureAuto->setCurrentIndex(i);
				}
			}
		}
	}
	if(Parent->GetEnumValue ("ExposureMode",CurrentIntValue ,EnumExposureModeData,EnumCount)==true){
		ui->comboBoxExposureMode->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("ExposureMode",EnumExposureModeData[i] ,Str)==true){
				ui->comboBoxExposureMode->addItem(Str);
				if(CurrentIntValue==EnumExposureModeData[i]){
					ui->comboBoxExposureMode->setCurrentIndex(i);
				}
			}
		}
	}

	if(Parent->Cam.SetEnumValue ("BalanceRatioSelector",(int)0)==MV_OK){
		int		CurrentIntBalanceRatio ,MaxIntBalanceRatio ,MinIntBalanceRatio;
		if(Parent->GetIntValue("BalanceRatio",CurrentIntBalanceRatio ,MaxIntBalanceRatio ,MinIntBalanceRatio)==true){
			ui->spinBoxBalanceRatioR	->setMaximum(MaxIntBalanceRatio);
			ui->spinBoxBalanceRatioR	->setMinimum(MinIntBalanceRatio);
			ui->spinBoxBalanceRatioR	->setValue	(CurrentIntBalanceRatio);
		}
	}
	if(Parent->Cam.SetEnumValue ("BalanceRatioSelector",(int)1)==MV_OK){
		int		CurrentIntBalanceRatio ,MaxIntBalanceRatio ,MinIntBalanceRatio;
		if(Parent->GetIntValue("BalanceRatio",CurrentIntBalanceRatio ,MaxIntBalanceRatio ,MinIntBalanceRatio)==true){
			ui->spinBoxBalanceRatioG	->setMaximum(MaxIntBalanceRatio);
			ui->spinBoxBalanceRatioG	->setMinimum(MinIntBalanceRatio);
			ui->spinBoxBalanceRatioG	->setValue	(CurrentIntBalanceRatio);
		}
	}
	if(Parent->Cam.SetEnumValue ("BalanceRatioSelector",(int)2)==MV_OK){
		int		CurrentIntBalanceRatio ,MaxIntBalanceRatio ,MinIntBalanceRatio;
		if(Parent->GetIntValue("BalanceRatio",CurrentIntBalanceRatio ,MaxIntBalanceRatio ,MinIntBalanceRatio)==true){
			ui->spinBoxBalanceRatioB	->setMaximum(MaxIntBalanceRatio);
			ui->spinBoxBalanceRatioB	->setMinimum(MinIntBalanceRatio);
			ui->spinBoxBalanceRatioB	->setValue	(CurrentIntBalanceRatio);
		}
	}

	if(Parent->GetEnumValue ("BalanceColorTemperatureMode",CurrentIntValue ,EnumBalanceColorTemperatureModeData,EnumCount)==true){
		ui->comboBoxBalanceColorTemperatureMode->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("BalanceColorTemperatureMode",EnumBalanceColorTemperatureModeData[i] ,Str)==true){
				ui->comboBoxBalanceColorTemperatureMode->addItem(Str);
				if(CurrentIntValue==EnumBalanceColorTemperatureModeData[i]){
					ui->comboBoxBalanceColorTemperatureMode->setCurrentIndex(i);
				}
			}
		}
	}
	if(Parent->GetEnumValue ("BalanceWhiteAuto",CurrentIntValue ,EnumWhiteBalanceData,EnumCount)==true){
		ui->comboBoxWhiteBalance->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("BalanceWhiteAuto",EnumWhiteBalanceData[i] ,Str)==true){
				ui->comboBoxWhiteBalance->addItem(Str);
				if(CurrentIntValue==EnumWhiteBalanceData[i]){
					ui->comboBoxWhiteBalance->setCurrentIndex(i);

					if(CurrentIntValue==0){
						ui->stackedWidget->setCurrentIndex(0);
					}
					else if(CurrentIntValue==1){
						ui->stackedWidget->setCurrentIndex(1);
					}
				}
			}
		}
	}
	int		CurrentIntValueH ,MaxIntValueH ,MinIntValueH;
	int		CurrentIntValueV ,MaxIntValueV ,MinIntValueV;
	bool	RetH=Parent->GetIntValue("BinningHorizontal",CurrentIntValueH ,MaxIntValueH ,MinIntValueH);
	bool	RetV=Parent->GetIntValue("BinningVertical"	 ,CurrentIntValueV ,MaxIntValueV ,MinIntValueV);
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

	RetH=Parent->GetIntValue("DecimationHorizontal",CurrentIntValueH ,MaxIntValueH ,MinIntValueH);
	RetV=Parent->GetIntValue("DecimationVertical"	,CurrentIntValueV ,MaxIntValueV ,MinIntValueV);
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


	if(Parent->GetEnumValue ("TriggerMode",CurrentIntValue ,EnumTriggerModeData,EnumCount)==true){
		ui->comboBoxTriggerMode->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("TriggerMode",EnumTriggerModeData[i] ,Str)==true){
				ui->comboBoxTriggerMode->addItem(Str);
				if(CurrentIntValue==EnumTriggerModeData[i]){
					ui->comboBoxTriggerMode->setCurrentIndex(i);
				}
			}
		}
	}
	if(Parent->GetEnumValue ("TriggerSource",CurrentIntValue ,EnumTriggerSourceData,EnumCount)==true){
		ui->comboBoxTriggerSource->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("TriggerSource",EnumTriggerSourceData[i] ,Str)==true){
				ui->comboBoxTriggerSource->addItem(Str);
				if(CurrentIntValue==EnumTriggerSourceData[i]){
					ui->comboBoxTriggerSource->setCurrentIndex(i);
				}
			}
		}
	}
	bool	CurrentBoolValue;
	if(Parent->GetBoolValue("ReverseX",CurrentBoolValue )==true){
		ui->checkBoxReverseX	->setChecked(CurrentBoolValue);
	}
	if(Parent->GetBoolValue("ReverseY",CurrentBoolValue )==true){
		ui->checkBoxReverseY	->setChecked(CurrentBoolValue);
	}

	bool	CurrentBlackLevelEnable;
	if(Parent->GetBoolValue("BlackLevelEnable",CurrentBlackLevelEnable )==true){
		ui->checkBoxBlackLevelEnable->setChecked(CurrentBlackLevelEnable);
	}

	int	CurrentBlackLevel,MaxBlackLevel,MinBlackLevel;
	if(Parent->GetIntValue("BlackLevel",CurrentBlackLevel ,MaxBlackLevel ,MinBlackLevel)==true){
		ui->spinBoxBlackLevel	->setMaximum(MaxBlackLevel);
		ui->spinBoxBlackLevel	->setMinimum(MinBlackLevel);
		ui->spinBoxBlackLevel	->setValue	(CurrentBlackLevel);
	}

	int	Width ,Height;
	Parent->GetResolution(Width ,Height);
	int	MaxIntValue ,MinIntValue;
	int	CurrentOffsetXValue,CurrentOffsetYValue;
	if(Parent->GetIntValue("OffsetX",CurrentOffsetXValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIOffsetX	->setMaximum(Width);
		ui->spinBoxAOIOffsetX	->setMinimum(MinIntValue);
		ui->spinBoxAOIOffsetX	->setValue	(CurrentOffsetXValue);
	}
	if(Parent->GetIntValue("OffsetY",CurrentOffsetYValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIOffsetY	->setMaximum(Height);
		ui->spinBoxAOIOffsetY	->setMinimum(MinIntValue);
		ui->spinBoxAOIOffsetY	->setValue	(CurrentOffsetYValue);
	}
	if(Parent->GetIntValue("Width",CurrentIntValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIWidth		->setMaximum(MaxIntValue);
		ui->spinBoxAOIWidth		->setMinimum(MinIntValue);
		ui->spinBoxAOIWidth		->setValue	(CurrentIntValue);
	}
	if(Parent->GetIntValue("Height",CurrentIntValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIHeight	->setMaximum(MaxIntValue);
		ui->spinBoxAOIHeight	->setMinimum(MinIntValue);
		ui->spinBoxAOIHeight	->setValue	(CurrentIntValue);
	}


	if(Parent->GetEnumValue ("UserSetSelector",CurrentIntValue ,EnumUserSetSelectorData,EnumCount)==true){
		ui->comboBoxUserSetSelector->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("UserSetSelector",EnumUserSetSelectorData[i] ,Str)==true){
				ui->comboBoxUserSetSelector->addItem(Str);
				if(CurrentIntValue==EnumUserSetSelectorData[i]){
					ui->comboBoxUserSetSelector->setCurrentIndex(i);
				}
			}
		}
	}
}

ShowCameraDialog::~ShowCameraDialog()
{
    delete ui;
}

void ShowCameraDialog::on_pushButtonOK_clicked()
{
	GetFromWindow();
	done(true);
}
void ShowCameraDialog::GetFromWindow(void)
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


	int	WhiteBalanceIndex=ui->comboBoxWhiteBalance->currentIndex();
	WhiteBalance	=EnumWhiteBalanceData[WhiteBalanceIndex];

	BalanceRatioR	=ui->spinBoxBalanceRatioR	->value();
	BalanceRatioG	=ui->spinBoxBalanceRatioG	->value();
	BalanceRatioB	=ui->spinBoxBalanceRatioB	->value();

	int	BalanceColorTemperatureModeIndex=ui->comboBoxBalanceColorTemperatureMode->currentIndex();
	BalanceColorTemperatureMode	=EnumBalanceColorTemperatureModeData[BalanceColorTemperatureModeIndex];


	BlackLevelEnable=ui->checkBoxBlackLevelEnable->isChecked();
	BlackLevel		=ui->spinBoxBlackLevel		->value	();

	ReverseX	=ui->checkBoxReverseX	->isChecked();
	ReverseY	=ui->checkBoxReverseY	->isChecked();

	AOIOffsetX	=ui->spinBoxAOIOffsetX	->value();
	AOIOffsetY	=ui->spinBoxAOIOffsetY	->value();
	AOIWidth	=ui->spinBoxAOIWidth	->value();
	AOIHeight	=ui->spinBoxAOIHeight	->value();
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


void ShowCameraDialog::on_comboBoxWhiteBalance_currentIndexChanged(int index)
{
	int	Index=ui->comboBoxWhiteBalance->currentIndex();


	int	WhiteBalanceIndex=ui->comboBoxWhiteBalance->currentIndex();
	WhiteBalance	=EnumWhiteBalanceData[WhiteBalanceIndex];
    int	nRet = Parent->Cam.SetEnumValue("BalanceWhiteAuto", (int)WhiteBalance);
    if (MV_OK != nRet){
        return;
    }
	if(Index==0){
		ui->stackedWidget->setCurrentIndex(0);
	}
	else if(Index==2){
		ui->stackedWidget->setCurrentIndex(1);

		int	CurrentIntValue;
		int	EnumCount;
		if(Parent->GetEnumValue ("BalanceColorTemperatureMode",CurrentIntValue ,EnumBalanceColorTemperatureModeData,EnumCount)==true){
			ui->comboBoxBalanceColorTemperatureMode->clear();
			for(int i=0;i<EnumCount;i++){
				QString Str;
				if(Parent->GetEnumSymblic ("BalanceColorTemperatureMode",EnumBalanceColorTemperatureModeData[i] ,Str)==true){
					ui->comboBoxBalanceColorTemperatureMode->addItem(Str);
					if(CurrentIntValue==EnumBalanceColorTemperatureModeData[i]){
						ui->comboBoxBalanceColorTemperatureMode->setCurrentIndex(i);
					}
				}
			}
		}
	}
}


void ShowCameraDialog::on_pushButtonUserSetSave_clicked()
{
	int	Index=ui->comboBoxUserSetSelector->currentIndex();
	int	SelectNo=EnumUserSetSelectorData[Index];

	GetFromWindow();
	Parent->Set(*this);

	int	nRet = Parent->Cam.SetEnumValue("UserSetSelector", (int)SelectNo);
	if (MV_OK != nRet){
		return;
	}
	nRet = Parent->Cam.CommandExecute("UserSetSave");
	if (MV_OK != nRet){
		return;
	}
}


void ShowCameraDialog::on_pushButtonUserSetLoad_clicked()
{
	int	Index=ui->comboBoxUserSetSelector->currentIndex();
	int	SelectNo=EnumUserSetSelectorData[Index];

	int	nRet = Parent->Cam.SetEnumValue("UserSetSelector", (int)SelectNo);
	if (MV_OK != nRet){
		Parent->RecoverFromError();
		return;
	}
	nRet = Parent->Cam.CommandExecute("UserSetLoad");
	if (MV_OK != nRet){
		Parent->RecoverFromError();
		return;
	}
	ShowData();
}

