#include "XContecNC2DInfo.h"
#include "XGeneralFunc.h"

ContecNC2DInfo::ContecNC2DInfo(void)
{
	StartPosX		=10000;
	StartPosY		=1000;
	StartVelocity	=10000;
	AccelRate		=200;
	ScanPulse		=10000;
	ScanVelocity	=10000;
	StepPulse		=10000;
	StepVelocity	=10000;
	ScanCount		=4;
	CurentScan		=0;
	OriginVelocity	=2000;
	MaxPulseX		=30000;
	MaxPulseY		=20000;
}

bool	ContecNC2DInfo::Save(QIODevice *f)
{
	if(::Save(f,StartPosX)==false)
		return false;
	if(::Save(f,StartPosY)==false)
		return false;
	if(::Save(f,StartVelocity)==false)
		return false;
	if(::Save(f,AccelRate)==false)
		return false;
	if(::Save(f,ScanPulse)==false)
		return false;
	if(::Save(f,ScanVelocity)==false)
		return false;
	if(::Save(f,StepPulse)==false)
		return false;
	if(::Save(f,StepVelocity)==false)
		return false;
	if(::Save(f,ScanCount)==false)
		return false;
	if(::Save(f,CurentScan)==false)
		return false;
	if(::Save(f,OriginVelocity)==false)
		return false;
	if(::Save(f,MaxPulseX)==false)
		return false;
	if(::Save(f,MaxPulseY)==false)
		return false;
	return true;
}

bool	ContecNC2DInfo::Load(QIODevice *f)
{
	if(::Load(f,StartPosX)==false)
		return false;
	if(::Load(f,StartPosY)==false)
		return false;
	if(::Load(f,StartVelocity)==false)
		return false;
	if(::Load(f,AccelRate)==false)
		return false;
	if(::Load(f,ScanPulse)==false)
		return false;
	if(::Load(f,ScanVelocity)==false)
		return false;
	if(::Load(f,StepPulse)==false)
		return false;
	if(::Load(f,StepVelocity)==false)
		return false;
	if(::Load(f,ScanCount)==false)
		return false;
	if(::Load(f,CurentScan)==false)
		return false;
	if(::Load(f,OriginVelocity)==false)
		return false;
	if(::Load(f,MaxPulseX)==false)
		return false;
	if(::Load(f,MaxPulseY)==false)
		return false;
	return true;
}