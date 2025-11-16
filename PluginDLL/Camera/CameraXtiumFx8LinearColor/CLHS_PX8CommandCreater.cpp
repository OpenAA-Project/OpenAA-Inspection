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
	ExposureTime=40;	//Microsec
	TDIDirection=false;

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

	LightOffMilisec	=10000;
	LightOnMilisec	=3000;
}

bool	CLHS_PX8Setting::Save(QIODevice *f)
{
	int32	Ver=10;

	if(::Save(f,Ver	)==false)
		return false;
	if(::Save(f,LineRate	)==false)
		return false;
	if(::Save(f,ExposureTime)==false)
		return false;
	if(::Save(f,TDIDirection)==false)
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
	if(::Save(f,LightOffMilisec	)==false)
		return false;
	if(::Save(f,LightOnMilisec	)==false)
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
	if(::Load(f,ExposureTime)==false)
		return false;
	if(::Load(f,TDIDirection)==false)
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

	if(Ver>=3){
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
	}
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
	if(Ver>=2){
		if(::Load(f,OffsetYRed	)==false)
			return false;
		if(::Load(f,OffsetYGreen	)==false)
			return false;
		if(::Load(f,OffsetYBlue	)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(f,HorizontalBinning	)==false)
			return false;
		if(::Load(f,VerticalBinning		)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,LeftRight	)==false)
			return false;
	}
	if(Ver>=6){
		if(::Load(f,ExternalTrigger	)==false)
			return false;
	}
	if(Ver>=7){
		if(::Load(f,CameraControl	)==false)
			return false;
	}
	if(Ver>=8){
		if(::Load(f,AutoBlackLevel	)==false)
			return false;
		if(::Load(f,CalibrateFPN	)==false)
			return false;
	}
	if(Ver>=9){
		if(::Load(f,ROIOffset	)==false)
			return false;
	}
	if(Ver>=10){
		if(::Load(f,LightOffMilisec	)==false)
			return false;
		if(::Load(f,LightOnMilisec	)==false)
			return false;
	}
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
	double	tExposureTime;
	if(f->getFeatureValue(featureCtrl::EN_ExposureTime, &tExposureTime)==false)
		return false;
	ExposureTime=tExposureTime-BrightValue;

	char	featureString[256];
	if(f->getFeatureValue(featureCtrl::EN_SensorScanDirection, featureString, sizeof(featureString))==false)
		return false;
	//if(f->getFeatureValue(featureCtrl::EN_SensorScanDirection, &TDIDirection)==false)
	//	return false;
	if(strcmp(featureString,"Forward")==0)
		TDIDirection=true;
	else
		TDIDirection=false;

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

	double	tExposureTime=ExposureTime+BrightValue;
	if(f->setFeatureValue(featureCtrl::EN_ExposureTime, tExposureTime)==false)
		return false;
	//if(f->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, LineRate)==false)
	//	return false;
	//f->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, LineRate);

	if(TDIDirection==true){
		if(f->setFeatureValue(featureCtrl::EN_SensorScanDirection, "Forward")==false)
			return false;
	}
	else{
		if(f->setFeatureValue(featureCtrl::EN_SensorScanDirection, "Reverse")==false)
			return false;
	}

	if(ColorMode==false){
		f->setFeatureValue("GainSelector", "System");
		if(f->setFeatureValue(featureCtrl::EN_Gain, GainRed)==false)
			return false;
		if(f->setFeatureValue(featureCtrl::EN_BlackLevel, OffsetRed)==false)
			return false;
		if(f->setFeatureValue("sensorTDIModeSelection", "TdiSum")==false)
			return false;
		if(f->setFeatureValue("sensorTDIStagesSelection", "Lines3")==false)
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
		double	tExposureTime=ExposureTime+BrightValue;
		if(f->setFeatureValue(featureCtrl::EN_ExposureTime, tExposureTime)==false){
			return false;
		}
	}
	return true;
}