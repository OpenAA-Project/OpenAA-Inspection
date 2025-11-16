#include "XContecNC4DInfo.h"
#include "XGeneralFunc.h"


ContecNCAxis::ContecNCAxis(void)
{
	AccelRate	=10;
	PulsePerRot	=500;
	Pitch		=5;
	MaxVelocity	=50;
	JogVelocity	=10;
	JogPulse	=500;
	OriginVelocity=20;
	MaxLength	=500;
}

bool	ContecNCAxis::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,AccelRate)==false)
		return false;
	if(::Save(f,PulsePerRot)==false)
		return false;
	if(::Save(f,Pitch)==false)
		return false;
	if(::Save(f,MaxVelocity)==false)
		return false;
	if(::Save(f,JogVelocity)==false)
		return false;
	if(::Save(f,JogPulse)==false)
		return false;
	if(::Save(f,OriginVelocity)==false)
		return false;
	if(::Save(f,MaxLength)==false)
		return false;
	return true;
}
bool	ContecNCAxis::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,AccelRate)==false)
		return false;
	if(::Load(f,PulsePerRot)==false)
		return false;
	if(::Load(f,Pitch)==false)
		return false;
	if(::Load(f,MaxVelocity)==false)
		return false;
	if(::Load(f,JogVelocity)==false)
		return false;
	if(::Load(f,JogPulse)==false)
		return false;
	if(::Load(f,OriginVelocity)==false)
		return false;
	if(::Load(f,MaxLength)==false)
		return false;
	return true;
}

int		ContecNCAxis::GetPulseFromMM(double  mm)
{
	return PulsePerRot*((double)mm)/Pitch;
}
double	ContecNCAxis::GetMMFromPulse(double  pulse)
{
	return ((double)pulse)/((double)PulsePerRot)*((double)Pitch);
}

ContecNC4DInfo::ContecNC4DInfo(void)
{
	StartPosX=0;
	StartPosY=0;
	StartVelocity	=10;
	ScanLength		=1000;
	ScanVelocity	=10;
	StepLength		=70*100;
	StepVelocity	=10;
	PulseZ			=500;
	VelocityZ		=10;
	ScanCount		=4;
	EnableAreaSensor	=false;
	EnableDoorSensor	=false;
}

bool	ContecNC4DInfo::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(AxisX.Save(f)==false)
		return false;
	if(AxisY.Save(f)==false)
		return false;
	if(AxisZ.Save(f)==false)
		return false;
	if(AxisW.Save(f)==false)
		return false;

	if(::Save(f,StartPosX)==false)
		return false;
	if(::Save(f,StartPosY)==false)
		return false;
	if(::Save(f,StartVelocity)==false)
		return false;
	if(::Save(f,ScanLength)==false)
		return false;
	if(::Save(f,ScanVelocity)==false)
		return false;
	if(::Save(f,StepLength)==false)
		return false;
	if(::Save(f,StepVelocity)==false)
		return false;
	if(::Save(f,PulseZ)==false)
		return false;
	if(::Save(f,VelocityZ)==false)
		return false;
	if(::Save(f,ScanCount)==false)
		return false;
	if(::Save(f,EnableAreaSensor)==false)
		return false;
	if(::Save(f,EnableDoorSensor)==false)
		return false;
	if(::Save(f,PosZ)==false)
		return false;
	return true;
}
bool	ContecNC4DInfo::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(AxisX.Load(f)==false)
		return false;
	if(AxisY.Load(f)==false)
		return false;
	if(AxisZ.Load(f)==false)
		return false;
	if(AxisW.Load(f)==false)
		return false;

	if(::Load(f,StartPosX)==false)
		return false;
	if(::Load(f,StartPosY)==false)
		return false;
	if(::Load(f,StartVelocity)==false)
		return false;
	if(::Load(f,ScanLength)==false)
		return false;
	if(::Load(f,ScanVelocity)==false)
		return false;
	if(::Load(f,StepLength)==false)
		return false;
	if(::Load(f,StepVelocity)==false)
		return false;
	if(::Load(f,PulseZ)==false)
		return false;
	if(::Load(f,VelocityZ)==false)
		return false;
	if(::Load(f,ScanCount)==false)
		return false;
	if(::Load(f,EnableAreaSensor)==false)
		return false;
	if(::Load(f,EnableDoorSensor)==false)
		return false;
	if(::Load(f,PosZ)==false)
		return false;
	return true;
}
