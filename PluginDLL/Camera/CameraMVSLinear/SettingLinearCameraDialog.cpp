#include "SettingLinearCameraDialog.h"
#include "ui_SettingLinearCameraDialog.h"
#include "XGeneralFunc.h"

SettingLinearCameraDialog::SettingLinearCameraDialog(CameraMVSLinear *Cam,QWidget *parent)
    : QDialog(parent)
	,Parent(Cam)
    , ui(new Ui::SettingLinearCameraDialog)
{
    ui->setupUi(this);

    ExposureAuto        =Cam->ExposureAuto        ;
    ExposureMode        =Cam->ExposureMode        ;
	ExposureTime        =Cam->ExposureTime        ;
	Gain                =Cam->Gain                ;
	GainR               =Cam->GainR               ;
    GainG               =Cam->GainG               ;
    GainB               =Cam->GainB               ;
	LineRate			=Cam->LineRate           ;
    LineTriggerMode     =Cam->LineTriggerMode     ;   
    LineTriggerSource   =Cam->LineTriggerSource   ; 
    FrameTriggerMode    =Cam->FrameTriggerMode    ;   
    FrameTriggerSource  =Cam->FrameTriggerSource  ; 
	Line0Format			=Line0Format			;
	Line1Format			=Line1Format			;
	Line2Format			=Line2Format			;
	Line3Format			=Line3Format			;
	Line4Format			=Line4Format			;
    BinningHMode        =Cam->BinningHMode        ;
    BinningVMode        =Cam->BinningVMode        ;
    DecimationH         =Cam->DecimationH         ;
    DecimationV         =Cam->DecimationV         ;
    ReverseX            =Cam->ReverseX            ;
    ReverseTDIY         =Cam->ReverseTDIY         ;
    AOIMode             =Cam->AOIMode             ;
    AOIOffsetX          =Cam->AOIOffsetX          ;
    AOIWidth            =Cam->AOIWidth            ;
	BlackLevelEnable		=Cam->BlackLevelEnable;
	BlackLevel				=Cam->BlackLevel      ;
	ImageCompression	= Cam->ImageCompression;
	AcquisitionLineRateEnable = Cam->AcquisitionLineRateEnable;
	GammaEnable			=Cam->GammaEnable;
	Gamma				=Cam->Gamma      ;
    FrameDelay			=Cam->FrameDelay ;

	ui->lineEditDeviceName->setText(Cam->UserName);
	ui->lineEditIPAddress->setText(Cam->IPAddress);

	SetColumnWidthInTable(ui->tableWidgetIO ,0, 45);
	SetColumnWidthInTable(ui->tableWidgetIO ,1, 45);

	float	CurrentFloatValue ,MaxFloatValue ,MinFloatValue;
	if(Cam->GetfloatValue("ExposureTime",CurrentFloatValue ,MaxFloatValue ,MinFloatValue)==true){
		ui->doubleSpinBoxExposureTime	->setMaximum(MaxFloatValue);
		ui->doubleSpinBoxExposureTime	->setMinimum(MinFloatValue);
		ui->doubleSpinBoxExposureTime	->setValue	(CurrentFloatValue);
	}

	float	CurrentFloatGainValue ,MaxFloatGainValue ,MinFloatGainValue;
	if(Cam->GetfloatValue("Gain",CurrentFloatGainValue ,MaxFloatGainValue ,MinFloatGainValue)==true){
		ui->doubleSpinBoxGain	->setMaximum(MaxFloatGainValue);
		ui->doubleSpinBoxGain	->setMinimum(MinFloatGainValue);
		ui->doubleSpinBoxGain	->setValue	(CurrentFloatGainValue);
	}
	if(Cam->SetEnumValueByString("BalanceRatioSelector", "Red")==true){
		int64	CurrentGainValue ,MaxGainValue ,MinGainValue;
		if(Cam->GetIntValue("BalanceRatio",CurrentGainValue ,MaxGainValue ,MinGainValue)==true){
	        ui->doubleSpinBoxGainR	->setMaximum(MaxGainValue);
		    ui->doubleSpinBoxGainR	->setMinimum(MinGainValue);
			ui->doubleSpinBoxGainR	->setValue	(CurrentGainValue);
		}
	}
	if(Cam->SetEnumValueByString("BalanceRatioSelector", "Green")==true){
		int64	CurrentGainValue ,MaxGainValue ,MinGainValue;
		if(Cam->GetIntValue("BalanceRatio",CurrentGainValue ,MaxGainValue ,MinGainValue)==true){
	        ui->doubleSpinBoxGainG	->setMaximum(MaxGainValue);
		    ui->doubleSpinBoxGainG	->setMinimum(MinGainValue);
			ui->doubleSpinBoxGainG	->setValue	(CurrentGainValue);
		}
	}
	if(Cam->SetEnumValueByString("BalanceRatioSelector", "Blue")==true){
		int64	CurrentGainValue ,MaxGainValue ,MinGainValue;
		if(Cam->GetIntValue("BalanceRatio",CurrentGainValue ,MaxGainValue ,MinGainValue)==true){
	        ui->doubleSpinBoxGainB	->setMaximum(MaxGainValue);
		    ui->doubleSpinBoxGainB	->setMinimum(MinGainValue);
			ui->doubleSpinBoxGainB	->setValue	(CurrentGainValue);
		}
	}

	int64	CurrentLineRateValue ,MaxLineValue ,MinLineValue;
	if(Cam->GetIntValue("AcquisitionLineRate",CurrentLineRateValue ,MaxLineValue ,MinLineValue)==true){
	    ui->spinBoxLineRate	->setMaximum(MaxLineValue);
	    ui->spinBoxLineRate	->setMinimum(MinLineValue);
		ui->spinBoxLineRate	->setValue	(CurrentLineRateValue);
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

	if(Cam->SetEnumValueByString("TriggerSelector", "LineStart")==true){
		if(Cam->GetEnumValue ("TriggerMode",CurrentIntValue ,EnumLineTriggerModeData,EnumCount)==true){
			ui->comboBoxLineTriggerMode->clear();
			for(int i=0;i<EnumCount;i++){
				QString Str;
				if(Cam->GetEnumSymblic ("TriggerMode",EnumLineTriggerModeData[i] ,Str)==true){
					ui->comboBoxLineTriggerMode->addItem(Str);
					if(CurrentIntValue==EnumLineTriggerModeData[i]){
						ui->comboBoxLineTriggerMode->setCurrentIndex(i);
					}
				}
			}
		}
		if(Cam->GetEnumValue ("TriggerSource",CurrentIntValue ,EnumLineTriggerSourceData,EnumCount)==true){
			ui->comboBoxLineTriggerSource->clear();
			for(int i=0;i<EnumCount;i++){
				QString Str;
				if(Cam->GetEnumSymblic ("TriggerSource",EnumLineTriggerSourceData[i] ,Str)==true){
					ui->comboBoxLineTriggerSource->addItem(Str);
					if(CurrentIntValue==EnumLineTriggerSourceData[i]){
						ui->comboBoxLineTriggerSource->setCurrentIndex(i);
					}
				}
			}
		}
	}

	if(Cam->SetEnumValueByString("TriggerSelector", "FrameBurstStart")==true){
		if(Cam->GetEnumValue ("TriggerMode",CurrentIntValue ,EnumFrameTriggerModeData,EnumCount)==true){
			ui->comboBoxFrameTriggerMode->clear();
			for(int i=0;i<EnumCount;i++){
				QString Str;
				if(Cam->GetEnumSymblic ("TriggerMode",EnumFrameTriggerModeData[i] ,Str)==true){
					ui->comboBoxFrameTriggerMode->addItem(Str);
					if(CurrentIntValue==EnumFrameTriggerModeData[i]){
						ui->comboBoxFrameTriggerMode->setCurrentIndex(i);
					}
				}
			}
		}
		if(Cam->GetEnumValue ("TriggerSource",CurrentIntValue ,EnumFrameTriggerSourceData,EnumCount)==true){
			ui->comboBoxFrameTriggerSource->clear();
			for(int i=0;i<EnumCount;i++){
				QString Str;
				if(Cam->GetEnumSymblic ("TriggerSource",EnumFrameTriggerSourceData[i] ,Str)==true){
					ui->comboBoxFrameTriggerSource->addItem(Str);
					if(CurrentIntValue==EnumFrameTriggerSourceData[i]){
						ui->comboBoxFrameTriggerSource->setCurrentIndex(i);
					}
				}
			}
		}
	}

	for(int LineNo=0;LineNo<=4;LineNo++){
		QString StrLineSelector = "Line" + QString::number(LineNo);
		QByteArray LineSelectorArray = StrLineSelector.toLocal8Bit();
		char	*LineSelector=LineSelectorArray.data();	
		if(Cam->SetEnumValueByString("LineSelector", LineSelector)==true){
			if(Cam->GetEnumValue ("LineFormat",CurrentIntValue ,EnumLineFormatData[LineNo],EnumCount)==true){
				QStringList	List;
				int	Index=0;
				for(int i=0;i<EnumCount;i++){
					QString Str;
					if(Cam->GetEnumSymblic ("LineFormat",EnumLineFormatData[LineNo][i] ,Str)==true){
						List.append(Str);
					}
					if(CurrentIntValue==EnumLineFormatData[LineNo][i]){
						Index=i;
					}
				}
				QComboBox	*r=::SetDataToTableComboBox(ui->tableWidgetIO, 1, LineNo, List, Index);
			}
			if(Cam->GetEnumValue ("LineMode",CurrentIntValue ,EnumLineModeData[LineNo],EnumCount)==true){
				QStringList	List;
				int	Index=0;
				for(int i=0;i<EnumCount;i++){
					QString Str;
					if(Cam->GetEnumSymblic ("LineMode",EnumLineModeData[LineNo][i] ,Str)==true){
						List.append(Str);
					}
					if(CurrentIntValue==EnumLineFormatData[LineNo][i]){
						Index=i;
					}
				}
				QComboBox	*r=::SetDataToTableComboBox(ui->tableWidgetIO, 0, LineNo, List, Index);
			}
		}
	}
	bool	CurrentBlackLevelEnable;
	if(Cam->GetBoolValue("BlackLevelEnable",CurrentBlackLevelEnable )==true){
		ui->checkBoxBlackLevelEnable->setChecked(CurrentBlackLevelEnable);
	}

	int	CurrentBlackLevel,MaxBlackLevel,MinBlackLevel;
	if(Cam->GetIntValue("BlackLevel",CurrentBlackLevel ,MaxBlackLevel ,MinBlackLevel)==true){
		ui->spinBoxBlackLevel	->setMaximum(MaxBlackLevel);
		ui->spinBoxBlackLevel	->setMinimum(MinBlackLevel);
		ui->spinBoxBlackLevel	->setValue	(CurrentBlackLevel);
	}

	bool	CurrentBoolValue;
	if(Cam->GetBoolValue("ReverseX",CurrentBoolValue )==true){
		ui->checkBoxReverseX	->setChecked(CurrentBoolValue);
	}
	if(Cam->Cam.GetTDIDirection(CurrentBoolValue )==true){
		ui->checkBoxReverseY	->setChecked(CurrentBoolValue);
	}
	if(Cam->GetBoolValue("AcquisitionLineRateEnable",CurrentBoolValue )==true){
		ui->checkBoxLineRateEnable	->setChecked(CurrentBoolValue);
	}
	if(Cam->GetBoolValue("GammaEnable",CurrentBoolValue )==true){
		ui->checkBoxGammaEnable	->setChecked(CurrentBoolValue);
	}
	float	CurrentGamma,MaxGamma,MinGamma;
	if(Cam->GetfloatValue("Gamma",CurrentGamma ,MaxGamma ,MinGamma)==true){
		ui->doubleSpinBoxGamma	->setMaximum(MaxGamma);
		ui->doubleSpinBoxGamma	->setMinimum(MinGamma);
		ui->doubleSpinBoxGamma	->setValue	(CurrentGamma);
	}

	if(Cam->SetEnumValueByString("TriggerSelector", "FrameBurstStart")==true){
		float	CurrentFrameDelay,MaxFrameDelay,MinFrameDelay;
		if(Cam->GetfloatValue("TriggerDelay",CurrentFrameDelay ,MaxFrameDelay ,MinFrameDelay)==true){
			ui->doubleSpinBoxFrameDelay	->setMaximum(MaxFrameDelay);
			ui->doubleSpinBoxFrameDelay	->setMinimum(MinFrameDelay);
			ui->doubleSpinBoxFrameDelay	->setValue	(CurrentFrameDelay);
		}
	}

	if(Cam->GetEnumValue ("ImageCompressionMode",CurrentIntValue ,EnumImageCompression,EnumCount)==true){
		ui->comboBoxImageCompression->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Cam->GetEnumSymblic ("ImageCompressionMode",EnumImageCompression[i] ,Str)==true){
				ui->comboBoxImageCompression->addItem(Str);
				if(CurrentIntValue==EnumImageCompression[i]){
					ui->comboBoxImageCompression->setCurrentIndex(i);
				}
			}
		}
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
	if(Cam->GetIntValue("Width",CurrentIntValue ,MaxIntValue ,MinIntValue)==true){
		ui->spinBoxAOIWidth		->setMaximum(MaxIntValue);
		ui->spinBoxAOIWidth		->setMinimum(MinIntValue);
		ui->spinBoxAOIWidth		->setValue	(CurrentIntValue);
	}

}

SettingLinearCameraDialog::~SettingLinearCameraDialog()
{
    delete ui;
}

void SettingLinearCameraDialog::on_pushButtonOK_clicked()
{
	ExposureTime	=ui->doubleSpinBoxExposureTime	->value();
	Gain			=ui->doubleSpinBoxGain		->value();
	GainR			=ui->doubleSpinBoxGainR		->value();
	GainG			=ui->doubleSpinBoxGainG		->value();
	GainB			=ui->doubleSpinBoxGainB		->value();

	int	IndexExposureMode	=ui->comboBoxExposureMode->currentIndex();
	ExposureMode	=EnumExposureModeData[IndexExposureMode];
	int	IndexExposureAuto	=ui->comboBoxExposureAuto->currentIndex();
	ExposureAuto	=EnumExposureAutoData[IndexExposureAuto];

	LineRate		=ui->spinBoxLineRate	->value();

	AcquisitionLineRateEnable	=ui->checkBoxLineRateEnable	->isChecked();

	int	LineTriggerModeIndex=ui->comboBoxLineTriggerMode->currentIndex();
	int	tLineTriggerMode		=EnumLineTriggerModeData[LineTriggerModeIndex];
	if(Parent->SetEnumValueByString("TriggerSelector", "LineStart")==true){
		QString Str;
		if(Parent->GetEnumSymblic ("TriggerMode" ,tLineTriggerMode ,Str)==true){
			if(Str=="Off"){
				LineTriggerMode=false;
			}
			else{
				LineTriggerMode=true;
			}
		}
	}
	int	LineTriggerSourceIndex=ui->comboBoxLineTriggerSource->currentIndex();
	LineTriggerSource	= EnumLineTriggerSourceData[LineTriggerSourceIndex];

	int	FrameTriggerModeIndex=ui->comboBoxFrameTriggerMode->currentIndex();
	int	tFrameTriggerMode		=EnumFrameTriggerModeData[FrameTriggerModeIndex];
	if(Parent->SetEnumValueByString("TriggerSelector", "FrameBurstStart")==true){
		QString Str;
		if(Parent->GetEnumSymblic ("TriggerMode" ,tFrameTriggerMode ,Str)==true){
			if(Str=="Off"){
				FrameTriggerMode=false;
			}
			else{
				FrameTriggerMode=true;
			}
		}
	}
	int	FrameTriggerSourceIndex=ui->comboBoxFrameTriggerSource->currentIndex();
	FrameTriggerSource	= EnumFrameTriggerSourceData[FrameTriggerSourceIndex];

	for(int LineNo=0;LineNo<=4;LineNo++){
		int	Index=GetDataToTableComboBoxIndex(ui->tableWidgetIO, 1, LineNo);
		if(LineNo==0)
			Line0Format = EnumLineFormatData[LineNo][Index];
		else if(LineNo==1)
			Line1Format = EnumLineFormatData[LineNo][Index];
		else if(LineNo==2)
			Line2Format = EnumLineFormatData[LineNo][Index];
		else if(LineNo==3)
			Line3Format = EnumLineFormatData[LineNo][Index];
		else if(LineNo==4)
			Line4Format = EnumLineFormatData[LineNo][Index];
	}

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

	int	ImageCompressionIndex=ui->comboBoxImageCompression->currentIndex();
	ImageCompression	=EnumImageCompression[ImageCompressionIndex];

	BlackLevelEnable=ui->checkBoxBlackLevelEnable->isChecked();
	BlackLevel		=ui->spinBoxBlackLevel		->value	();

	GammaEnable	=ui->checkBoxGammaEnable	->isChecked();
	Gamma		=ui->doubleSpinBoxGamma		->value();

	FrameDelay	=ui->doubleSpinBoxFrameDelay->value();


	ReverseX	=ui->checkBoxReverseX	->isChecked();
	ReverseTDIY	=ui->checkBoxReverseY	->isChecked();

	AOIOffsetX	=ui->spinBoxAOIOffsetX	->value();
	AOIWidth	=ui->spinBoxAOIWidth	->value();

	done(true);
}


void SettingLinearCameraDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

