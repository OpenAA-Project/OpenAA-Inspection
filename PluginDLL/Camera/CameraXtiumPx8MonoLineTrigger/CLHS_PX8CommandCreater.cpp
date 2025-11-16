#include "CLHS_PX8CommandCreater.h"
#include "XGeneralFunc.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"

CLHS_PX8Setting::CLHS_PX8Setting()
{
	RedBrightness	=0;			//Red
	RedContrast		=0;
	RedGamma		=0;
	RedFloor		=0;
	RedCeiling		=0;
	RedApply		=true;

	LineRate	=25000;
	ExposureTime=40;	//Microsec
	TDIDirection=false;

	GainRed		=1.153076;
	OffsetRed	=0;

	GainRedL		=1;
	OffsetRedL	=0;

	GainRedR	=1;
	OffsetRedR	=0;

	MultipleRed		=1.0;
	OffsetXRed		=0;
	OffsetYRed		=0;

	HorizontalBinning	=1;
	VerticalBinning		=1;

	LeftRight		=false;
	ExternalTrigger	=true;
	AutoBlackLevel	=false;
	CalibrateFPN	=false;
	LightOffMilisec	=10000;
	LightOnMilisec	=3000;
}

bool	CLHS_PX8Setting::Save(QIODevice *f)
{
	int32	Ver=7;

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

	if(::Save(f,OffsetRed	)==false)
		return false;

	if(::Save(f,GainRedL	)==false)
		return false;
	if(::Save(f,OffsetRedL	)==false)
		return false;

	if(::Save(f,GainRedR	)==false)
		return false;
	if(::Save(f,OffsetRedR	)==false)
		return false;

	if(::Save(f,MultipleRed		)==false)
		return false;
	if(::Save(f,OffsetXRed	)==false)
		return false;
	if(::Save(f,OffsetYRed	)==false)
		return false;

	if(::Save(f,HorizontalBinning	)==false)
		return false;
	if(::Save(f,VerticalBinning		)==false)
		return false;
	if(::Save(f,LeftRight		)==false)
		return false;
	if(::Save(f,ExternalTrigger	)==false)
		return false;
	if(::Save(f,AutoBlackLevel	)==false)
		return false;
	if(::Save(f,CalibrateFPN	)==false)
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
	if(::Load(f,OffsetRed	)==false)
		return false;

	if(Ver>=3){
		if(::Load(f,GainRedL	)==false)
			return false;
		if(::Load(f,OffsetRedL	)==false)
			return false;
		if(::Load(f,GainRedR	)==false)
			return false;
		if(::Load(f,OffsetRedR	)==false)
			return false;
	}
	if(::Load(f,MultipleRed		)==false)
		return false;
	if(::Load(f,OffsetXRed	)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,OffsetYRed	)==false)
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
		if(::Load(f,AutoBlackLevel	)==false)
			return false;
		if(::Load(f,CalibrateFPN	)==false)
			return false;
		if(::Load(f,LightOffMilisec	)==false)
			return false;
		if(::Load(f,LightOnMilisec	)==false)
			return false;
	}
	return true;
}
bool	CLHS_PX8Setting::LoadFromCam(featureCtrl *f)
{
	//if(f->getFeatureValue(featureCtrl::EN_BinningHorizontal	, &HorizontalBinning)==false)
	//	return false;
	//HorizontalBinning &=0xFF;
	//if(f->getFeatureValue(featureCtrl::EN_BinningVertical	, &VerticalBinning)==false)
	//	return false;
	//VerticalBinning &=0xFF;

	if(f->getFeatureValue(featureCtrl::EN_AcquisitionLineRate, &LineRate)==false)
		return false;
	if(f->getFeatureValue(featureCtrl::EN_ExposureTime, &ExposureTime)==false)
		return false;
	if(f->getFeatureValue(featureCtrl::EN_SensorScanDirection, &TDIDirection)==false)
		return false;

	if(f->getFeatureValue(featureCtrl::EN_Gain, &GainRed)==false)
		return false;
	if(f->getFeatureValue(featureCtrl::EN_BlackLevel, &OffsetRed)==false)
		return false;

	return true;
}
bool	CLHS_PX8Setting::StoreToCam(featureCtrl *f)
{
	//if(f->setFeatureValue(featureCtrl::EN_BinningHorizontal	, HorizontalBinning)==false)
	//	return false;
	//if(f->setFeatureValue(featureCtrl::EN_BinningVertical	, VerticalBinning)==false)
	//	return false;

	if(f->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, LineRate)==false)
		return false;
	if(f->setFeatureValue(featureCtrl::EN_ExposureTime, ExposureTime)==false)
		return false;
	if(f->setFeatureValue(featureCtrl::EN_SensorScanDirection, TDIDirection)==false)
		return false;

	//if(f->setFeatureValue(featureCtrl::EN_GainExtended, "Enable")==false)
	//	return false;

	if(f->setFeatureValue(featureCtrl::EN_Gain, GainRed)==false)
		return false;
	if(f->setFeatureValue(featureCtrl::EN_BlackLevel, OffsetRed)==false)
		return false;

	if(ExternalTrigger==true){
		f->setFeatureValue(featureCtrl::EN_TriggerMode, "External");
	}
	else{
		f->setFeatureValue(featureCtrl::EN_TriggerMode, "Internal");
	}
	BOOL	Ret;

	if(HorizontalBinning>=2){
		UINT64 BinningHorizontal;
		UINT64 BinningVertical;
		Ret=f->getFeatureValue("BinningHorizontal", &BinningHorizontal);
		Ret=f->getFeatureValue("BinningVertical"	 , &BinningVertical);

		bool	StopMode;
		StopMode=true;
		BOOL isAvailable;

		//SapFeature feature;
		//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

		//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
		BinningHorizontal=2;
		Ret=f->setFeatureValueWithStop("BinningHorizontal", BinningHorizontal);
		Ret=f->setFeatureValue(featureCtrl::EN_AcquisitionStart, true);

		BinningHorizontal=0;
		Ret=f->getFeatureValue("BinningHorizontal", &BinningHorizontal);
		Ret=f->getFeatureValue("BinningVertical"	 , &BinningVertical);
	}
	else {
		UINT64 BinningHorizontal;
		UINT64 BinningVertical;
		Ret = f->getFeatureValue("BinningHorizontal", &BinningHorizontal);
		Ret = f->getFeatureValue("BinningVertical", &BinningVertical);

		bool	StopMode;
		StopMode = true;
		BOOL isAvailable;

		//SapFeature feature;
		//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

		//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
		BinningHorizontal = 1;
		Ret = f->setFeatureValueWithStop("BinningHorizontal", BinningHorizontal);
		Ret = f->setFeatureValue(featureCtrl::EN_AcquisitionStart, true);

		BinningHorizontal = 0;
		Ret = f->getFeatureValue("BinningHorizontal", &BinningHorizontal);
		Ret = f->getFeatureValue("BinningVertical", &BinningVertical);
	}

	if(VerticalBinning>=2){
		UINT64 BinningVertical;
		Ret=f->getFeatureValue("BinningVertical"	 , &BinningVertical);

		bool	StopMode;
		StopMode=true;
		BOOL isAvailable;
		GSleep(3000);

		//SapFeature feature;
		//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

		//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
		BinningVertical=2;
		Ret=f->setFeatureValueWithStop("BinningVertical", BinningVertical);

		GSleep(1000);

		Ret=f->setFeatureValue("AcquisitionStart", true);

		BinningVertical=0;
		Ret=f->getFeatureValue("BinningVertical"	, &BinningVertical);
	}
	else{
		UINT64 BinningVertical;
		Ret=f->getFeatureValue("BinningVertical"	 , &BinningVertical);

		bool	StopMode;
		StopMode=true;
		BOOL isAvailable;

		GSleep(3000);

		//SapFeature feature;
		//Ret=fc->GetFeatureInfo("AcquisitionStop", &feature);

		//Ret=fc->setFeatureValue("AcquisitionStop", StopMode);
		BinningVertical=1;
		Ret=f->setFeatureValueWithStop("BinningVertical", BinningVertical);

		GSleep(1000);

		Ret=f->setFeatureValue("AcquisitionStart", true);

		BinningVertical=0;
		Ret=f->getFeatureValue("BinningVertical"	 , &BinningVertical);
	}

	return true;
}
