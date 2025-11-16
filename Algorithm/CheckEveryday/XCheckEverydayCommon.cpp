#include "XCheckEverydayCommon.h"



CheckEverydayLightInfo::CheckEverydayLightInfo(void)
{
	Page	=0;
	Layer	=0;
	ID		=0;
	BrightnessLow	=0;
	BrightnessHigh	=255;
	CurrentValue	=0;
	Result		=true;
	x1=y1=x2=y2=0;
}

bool	CheckEverydayLightInfo::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,BrightnessLow)==false)
		return false;
	if(::Load(f,BrightnessHigh)==false)
		return false;
	if(::Load(f,CurrentValue)==false)
		return false;
	if(::Load(f,Result)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	CheckEverydayLightInfo::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,BrightnessLow)==false)
		return false;
	if(::Save(f,BrightnessHigh)==false)
		return false;
	if(::Save(f,CurrentValue)==false)
		return false;
	if(::Save(f,Result)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}


CheckEverydayFocusInfo::CheckEverydayFocusInfo(void)
{
	Page		=0;
	Layer		=0;
	ID			=0;
	FocusLow	=0;
	CurrentValue=0;
	Result		=true;
	x1=y1=x2=y2=0;
}


bool	CheckEverydayFocusInfo::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,FocusLow)==false)
		return false;
	if(::Load(f,CurrentValue)==false)
		return false;
	if(::Load(f,Result)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	CheckEverydayFocusInfo::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,FocusLow)==false)
		return false;
	if(::Save(f,CurrentValue)==false)
		return false;
	if(::Save(f,Result)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}