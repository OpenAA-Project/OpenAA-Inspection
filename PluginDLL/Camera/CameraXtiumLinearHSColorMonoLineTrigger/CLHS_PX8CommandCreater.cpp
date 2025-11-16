#include "CLHS_PX8CommandCreater.h"
#include "XGeneralFunc.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"

CLHS_PX8Setting::CLHS_PX8Setting(bool _ColorMode)
{
	ColorMode	=_ColorMode;

	RedBrightness	=0;			//Red
	RedContrast		=0;
	RedGamma		=0;
	RedFloor		=0;
	RedCeiling		=0;
	RedApply		=true;
	GreenBrightness	=0;		//Green
	GreenContrast	=0;
	GreenGamma		=0;
	GreenFloor		=0;
	GreenCeiling	=0;
	GreenApply		=true;
	BlueBrightness	=0;		//Blue
	BlueContrast	=0;
	BlueGamma		=0;
	BlueFloor		=0;
	BlueCeiling		=0;
	BlueApply		=true;

	LineRate	=25000;
	BrightValue	=0;
	//ExposureTime=40;	//Microsec
	TDIDirection=false;

	AnalogGain	=1;
	GainRed		=1.153076;
	GainGreen	=1.179932;
	GainBlue	=1.6;
	OffsetRed	=0;
	OffsetGreen	=0;
	OffsetBlue	=0;

	GainRedL		=1;
	GainGreenL	=1;
	GainBlueL	=1;
	OffsetRedL	=0;
	OffsetGreenL=0;
	OffsetBlueL	=0;

	GainRedR	=1;
	GainGreenR	=1;
	GainBlueR	=1;
	OffsetRedR	=0;
	OffsetGreenR=0;
	OffsetBlueR	=0;

	MultipleRed		=1.0;
	MultipleGreen	=1.0;
	MultipleBlue	=1.0;
	OffsetXRed		=0;
	OffsetXGreen	=0;
	OffsetXBlue		=0;
	OffsetYRed		=0;
	OffsetYGreen	=0;
	OffsetYBlue		=0;

	HorizontalBinning	=1;
	VerticalBinning		=1;

	LeftRight		=false;
	ExternalTrigger	=true;
	CameraControl	=true;
	AutoBlackLevel	=false;
	CalibrateFPN	=false;
	ROIOffset		=0;
	AddedGainR		=0;
	AddedGainG		=0;
	AddedGainB		=0;
}

bool	CLHS_PX8Setting::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver	)==false)
		return false;
	if(::Save(f,LineRate	)==false)
		return false;
	//if(::Save(f,ExposureTime)==false)
	//	return false;
	if(::Save(f,TDIDirection)==false)
		return false;
	if(::Save(f,AnalogGain)==false)
		return false;
	if(::Save(f,GainRed		)==false)
		return false;
	if(::Save(f,GainGreen	)==false)
		return false;
	if(::Save(f,GainBlue	)==false)
		return false;
	if(::Save(f,OffsetRed	)==false)
		return false;
	if(::Save(f,OffsetGreen	)==false)
		return false;
	if(::Save(f,OffsetBlue	)==false)
		return false;

	if(::Save(f,GainRedL	)==false)
		return false;
	if(::Save(f,GainGreenL	)==false)
		return false;
	if(::Save(f,GainBlueL	)==false)
		return false;
	if(::Save(f,OffsetRedL	)==false)
		return false;
	if(::Save(f,OffsetGreenL)==false)
		return false;
	if(::Save(f,OffsetBlueL	)==false)
		return false;

	if(::Save(f,GainRedR	)==false)
		return false;
	if(::Save(f,GainGreenR	)==false)
		return false;
	if(::Save(f,GainBlueR	)==false)
		return false;
	if(::Save(f,OffsetRedR	)==false)
		return false;
	if(::Save(f,OffsetGreenR)==false)
		return false;
	if(::Save(f,OffsetBlueR	)==false)
		return false;

	if(::Save(f,MultipleRed		)==false)
		return false;
	if(::Save(f,MultipleGreen	)==false)
		return false;
	if(::Save(f,MultipleBlue	)==false)
		return false;
	if(::Save(f,OffsetXRed	)==false)
		return false;
	if(::Save(f,OffsetXGreen	)==false)
		return false;
	if(::Save(f,OffsetXBlue	)==false)
		return false;
	if(::Save(f,OffsetYRed	)==false)
		return false;
	if(::Save(f,OffsetYGreen	)==false)
		return false;
	if(::Save(f,OffsetYBlue	)==false)
		return false;
	if(::Save(f,HorizontalBinning	)==false)
		return false;
	if(::Save(f,VerticalBinning		)==false)
		return false;
	if(::Save(f,LeftRight		)==false)
		return false;
	if(::Save(f,ExternalTrigger	)==false)
		return false;
	if(::Save(f,CameraControl	)==false)
		return false;
	if(::Save(f,AutoBlackLevel	)==false)
		return false;
	if(::Save(f,CalibrateFPN	)==false)
		return false;
	if(::Save(f,ROIOffset	)==false)
		return false;

	return true;
}
bool	CLHS_PX8Setting::Load(QIODevice *f)
{
	int32	Ver=0;
	if(::Load(f,Ver	)==false)
		return false;

	if(::Load(f,LineRate	)==false)
		return false;
	//if(::Load(f,ExposureTime)==false)
	//	return false;
	if(::Load(f,TDIDirection)==false)
		return false;
	if(::Load(f,AnalogGain)==false)
		return false;
	if(::Load(f,GainRed		)==false)
		return false;
	if(::Load(f,GainGreen	)==false)
		return false;
	if(::Load(f,GainBlue	)==false)
		return false;
	if(::Load(f,OffsetRed	)==false)
		return false;
	if(::Load(f,OffsetGreen	)==false)
		return false;
	if(::Load(f,OffsetBlue	)==false)
		return false;

	if(::Load(f,GainRedL	)==false)
		return false;
	if(::Load(f,GainGreenL	)==false)
		return false;
	if(::Load(f,GainBlueL	)==false)
		return false;
	if(::Load(f,OffsetRedL	)==false)
		return false;
	if(::Load(f,OffsetGreenL)==false)
		return false;
	if(::Load(f,OffsetBlueL	)==false)
		return false;

	if(::Load(f,GainRedR	)==false)
		return false;
	if(::Load(f,GainGreenR	)==false)
		return false;
	if(::Load(f,GainBlueR	)==false)
		return false;
	if(::Load(f,OffsetRedR	)==false)
		return false;
	if(::Load(f,OffsetGreenR)==false)
		return false;
	if(::Load(f,OffsetBlueR	)==false)
		return false;
	
	if(::Load(f,MultipleRed		)==false)
		return false;
	if(::Load(f,MultipleGreen	)==false)
		return false;
	if(::Load(f,MultipleBlue	)==false)
		return false;
	if(::Load(f,OffsetXRed	)==false)
		return false;
	if(::Load(f,OffsetXGreen	)==false)
		return false;
	if(::Load(f,OffsetXBlue	)==false)
		return false;

	if(::Load(f,OffsetYRed	)==false)
		return false;
	if(::Load(f,OffsetYGreen	)==false)
		return false;
	if(::Load(f,OffsetYBlue	)==false)
		return false;

	if(::Load(f,HorizontalBinning	)==false)
		return false;
	if(::Load(f,VerticalBinning		)==false)
		return false;

	if(::Load(f,LeftRight	)==false)
		return false;
	
	if(::Load(f,ExternalTrigger	)==false)
		return false;
	if(::Load(f,CameraControl	)==false)
		return false;

	if(::Load(f,AutoBlackLevel	)==false)
		return false;
	if(::Load(f,CalibrateFPN	)==false)
		return false;
	
	if(::Load(f,ROIOffset	)==false)
		return false;
	
	return true;
}
bool	CLHS_PX8Setting::LoadFromCam(featureCtrl *f)
{
	if(CameraControl==false)
		return true;

	//if(f->getFeatureValue(featureCtrl::EN_BinningHorizontal	, &HorizontalBinning)==false)
	//	return false;
	//HorizontalBinning &=0xFF;
	//if(f->getFeatureValue(featureCtrl::EN_BinningVertical	, &VerticalBinning)==false)
	//	return false;
	//VerticalBinning &=0xFF;

	if(f->getFeatureValue(featureCtrl::EN_AcquisitionLineRate, &LineRate)==false)
		return false;
	//double	tExposureTime;
	//if(f->getFeatureValue(featureCtrl::EN_ExposureTime, &tExposureTime)==false)
	//	return false;
	//ExposureTime=tExposureTime-BrightValue;

	char	featureString[256];
	if(f->getFeatureValue(featureCtrl::EN_SensorScanDirection, featureString, sizeof(featureString))==false)
		return false;
	//if(f->getFeatureValue(featureCtrl::EN_SensorScanDirection, &TDIDirection)==false)
	//	return false;
	if(strcmp(featureString,"Forward")==0)
		TDIDirection=true;
	else
		TDIDirection=false;

	char	sAnalogGain[256];
	if (f->getFeatureValue("AnalogGain",sAnalogGain, sizeof(sAnalogGain))==false)
		return false;
	if(QString(sAnalogGain)==QString("One"))
		AnalogGain=0;
	else
	if(QString(sAnalogGain)==QString("Two"))
		AnalogGain=1;
	else
	if(QString(sAnalogGain)==QString("Four"))
		AnalogGain=2;
	else
	if(QString(sAnalogGain)==QString("Eight"))
		AnalogGain=3;


	if(ColorMode==false){
		f->setFeatureValue( "GainSelector", "System");
		if(f->getFeatureValue(featureCtrl::EN_Gain, &GainBlue)==false)
			return false;
		if(f->getFeatureValue(featureCtrl::EN_BlackLevel, &OffsetBlue)==false)
			return false;
	}
	else{
		f->setFeatureValue( "GainSelector", "Blue");
		if(f->getFeatureValue(featureCtrl::EN_Gain, &GainBlue)==false)
			return false;
		if(f->getFeatureValue(featureCtrl::EN_BlackLevel, &OffsetBlue)==false)
			return false;
		
		f->setFeatureValue("GainSelector", "Green");
		if(f->getFeatureValue(featureCtrl::EN_Gain, &GainGreen)==false)
			return false;
		if(f->getFeatureValue(featureCtrl::EN_BlackLevel, &OffsetGreen)==false)
			return false;
		
		f->setFeatureValue("GainSelector", "Red");
		if(f->getFeatureValue(featureCtrl::EN_Gain, &GainRed)==false)
			return false;
		if(f->getFeatureValue(featureCtrl::EN_BlackLevel, &OffsetRed)==false)
			return false;

		//if(AddedGainB!=0)
		//	GainBlue	/=AddedGainB;
		//if(AddedGainG!=0)
		//	GainGreen	/=AddedGainG;
		//if(AddedGainR!=0)
		//	GainRed		/=AddedGainR;
	}

	return true;
}
bool	CLHS_PX8Setting::StoreToCam(featureCtrl *f)
{
	if(CameraControl==false)
		return true;

	//if(f->setFeatureValue(featureCtrl::EN_BinningHorizontal	, HorizontalBinning)==false)
	//	return false;
	//if(f->setFeatureValue(featureCtrl::EN_BinningVertical	, VerticalBinning)==false)
	//	return false;

	//double	tExposureTime=ExposureTime+BrightValue;
	//if(f->setFeatureValue(featureCtrl::EN_ExposureTime, tExposureTime)==false)
	//	return false;
	if(f->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, LineRate)==false)
		return false;
	//f->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, LineRate);

	if(TDIDirection==true){
		if(f->setFeatureValue(featureCtrl::EN_SensorScanDirection, "Forward")==false)
			return false;
	}
	else{
		if(f->setFeatureValue(featureCtrl::EN_SensorScanDirection, "Reverse")==false)
			return false;
	}
	switch(AnalogGain){
		case 0:	if (f->setFeatureValue("AnalogGain","One")==false)
					return false;
				break;
		case 1:	if (f->setFeatureValue("AnalogGain","Two")==false)
					return false;
				break;
		case 2:	if (f->setFeatureValue("AnalogGain","Four")==false)
					return false;
				break;
		case 3:	if (f->setFeatureValue("AnalogGain","Eight")==false)
					return false;
				break;
	}
	if(ColorMode==false){
		f->setFeatureValue("GainSelector", "System");
		if(f->setFeatureValue(featureCtrl::EN_Gain, GainRed)==false)
			return false;
		if(f->setFeatureValue(featureCtrl::EN_BlackLevel, OffsetRed)==false)
			return false;
		//if(f->setFeatureValue("sensorTDIModeSelection", "TdiSum")==false)
		if(f->setFeatureValue("sensorTDIModeSelection", "Tdi")==false)
			return false;
		//if(f->setFeatureValue("sensorTDIStagesSelection", "Lines3")==false)
		if(f->setFeatureValue("sensorTDIStagesSelection", "Lines64")==false)
			return false;
	}
	else{
		f->setFeatureValue("GainSelector", "Blue");
		if(f->setFeatureValue(featureCtrl::EN_Gain, GainBlue)==false)
			return false;
		if(f->setFeatureValue(featureCtrl::EN_BlackLevel, OffsetBlue)==false)
			return false;
		
		f->setFeatureValue("GainSelector", "Green");
		if(f->setFeatureValue(featureCtrl::EN_Gain, GainGreen)==false)
			return false;
		if(f->setFeatureValue(featureCtrl::EN_BlackLevel, OffsetGreen)==false)
			return false;
		
		f->setFeatureValue("GainSelector", "Red");
		if(f->setFeatureValue(featureCtrl::EN_Gain, GainRed)==false)
			return false;
		if(f->setFeatureValue(featureCtrl::EN_BlackLevel, OffsetRed)==false)
			return false;
	}

	if(ExternalTrigger==true){
		f->setFeatureValue(featureCtrl::EN_TriggerMode, "External");
	}
	else{
		f->setFeatureValue(featureCtrl::EN_TriggerMode, "Internal");
	}
	return true;
}

bool	CLHS_PX8Setting::SetQuickProperty(featureCtrl *f,CameraQuickProperty Attr, double RelativeValue)
{
	if(CameraControl==false)
		return true;
	if(Attr==CameraQuickProperty_Brighter){
		BrightValue=RelativeValue;
		AddedGainR	=RelativeValue;
		AddedGainG	=RelativeValue;
		AddedGainB	=RelativeValue;
		//if(ColorMode==true){
		//	f->setFeatureValue("GainSelector", "Blue");
		//	if(f->setFeatureValue(featureCtrl::EN_Gain, GainBlue*AddedGainB)==false)
		//		return false;			
		//	f->setFeatureValue("GainSelector", "Green");
		//	if(f->setFeatureValue(featureCtrl::EN_Gain, GainGreen*AddedGainG)==false)
		//		return false;			
		//	f->setFeatureValue("GainSelector", "Red");
		//	if(f->setFeatureValue(featureCtrl::EN_Gain, GainRed*AddedGainR)==false)
		//		return false;
		//}
	}
	return true;
}