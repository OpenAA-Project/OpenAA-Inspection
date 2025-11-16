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
	ExposureTime=40;	//Microsec
	TDIDirection=false;

	GainRed		=1.153076;
	GainGreen	=1.179932;
	GainBlue	=1.6;
	OffsetRed	=0;
	OffsetGreen	=0;
	OffsetBlue	=0;
}

bool	CLHS_PX8Setting::Save(QIODevice *f)
{
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

	return true;
}
bool	CLHS_PX8Setting::Load(QIODevice *f)
{
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

	return true;
}
bool	CLHS_PX8Setting::LoadFromCam(featureCtrl *f)
{
	if(f->getFeatureValue(featureCtrl::EN_AcquisitionLineRate, &LineRate)==false)
		return false;
	if(f->getFeatureValue(featureCtrl::EN_ExposureTime, &ExposureTime)==false)
		return false;
	if(f->getFeatureValue(featureCtrl::EN_SensorScanDirection, &TDIDirection)==false)
		return false;

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

	return true;
}
bool	CLHS_PX8Setting::StoreToCam(featureCtrl *f)
{
	if(f->setFeatureValue(featureCtrl::EN_AcquisitionLineRate, LineRate)==false)
		return false;
	if(f->setFeatureValue(featureCtrl::EN_ExposureTime, ExposureTime)==false)
		return false;
	if(f->setFeatureValue(featureCtrl::EN_SensorScanDirection, TDIDirection)==false)
		return false;

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

	return true;
}
