#include "CL_MX4CommandCreater.h"
#include "XGeneralFunc.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"
#include <QMessageBox>

CL_MX4Setting::CL_MX4Setting(void)
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

	LeftRight		=false;
	CameraControl	=true;
}

bool	CL_MX4Setting::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver	)==false)
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

	if(::Save(f,LeftRight		)==false)
		return false;
	if(::Save(f,CameraControl	)==false)
		return false;

	return true;
}
bool	CL_MX4Setting::Load(QIODevice *f)
{
	int32	Ver=0;
	if(::Load(f,Ver	)==false)
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

	if(::Load(f,LeftRight	)==false)
		return false;

	if(::Load(f,CameraControl	)==false)
		return false;

	return true;
}
