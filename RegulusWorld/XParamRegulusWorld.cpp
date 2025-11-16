#include "XParamRegulusWorld.h"
#include "XGeneralFunc.h"

RWDeviceParamList::RWDeviceParamList(void)
{
	DeviceID=-1;
}
RWDeviceParamList::RWDeviceParamList(const RWDeviceParamList &src)
{
	DeviceID	=src.DeviceID;
	DLLFileName	=src.DLLFileName;
	Parameter	=src.Parameter;
}
bool	RWDeviceParamList::Save(QIODevice *f)
{
	if(::Save(f,DeviceID)==false){
		return false;
	}
	if(::Save(f,DLLFileName)==false){
		return false;
	}
	if(::Save(f,Parameter)==false){
		return false;
	}
	return true;
}
bool	RWDeviceParamList::Load(QIODevice *f)
{
	if(::Load(f,DeviceID)==false){
		return false;
	}
	if(::Load(f,DLLFileName)==false){
		return false;
	}
	if(::Load(f,Parameter)==false){
		return false;
	}
	return true;
}
RWDeviceParamList	&RWDeviceParamList::operator=(const RWDeviceParamList &src)
{
	DeviceID	=src.DeviceID;
	DLLFileName	=src.DLLFileName;
	Parameter	=src.Parameter;
	return *this;
}


RWDeviceParamListContainer::RWDeviceParamListContainer(const RWDeviceParamListContainer &src)
{
	for(RWDeviceParamList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RWDeviceParamList	*d=new RWDeviceParamList(*s);
		AppendList(d);
	}
}
RWDeviceParamList	*RWDeviceParamListContainer::Create(void)
{
	return new RWDeviceParamList();
}
RWDeviceParamListContainer	&RWDeviceParamListContainer::operator=(const RWDeviceParamListContainer &src)
{
	for(RWDeviceParamList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		RWDeviceParamList	*d=new RWDeviceParamList(*s);
		AppendList(d);
	}
	return *this;
}

//=======================================================================================================

ParamRegulusWorld::ParamRegulusWorld(RegulusWorld *base)
	:Parent(base)
{
	PageNumb		=1;
	DataFilePath	=/**/"D:\\Data";
	ErrorLogFile	=/**/"D:\\Data\\ErrorLog.dat";

	SetParam(&PageNumb		,/**/"Global"	,/**/"PageNumb"		,"Page count");
	SetParam(&DataFilePath	,/**/"File"		,/**/"DataFilePath"	,"Data path for objects");
	SetParam(&ErrorLogFile	,/**/"File"		,/**/"ErrorLogFile"	,"Error log file name with path");
}

bool	ParamRegulusWorld::SaveParam(QIODevice *f ,int EnableCondition)
{
	if(ParamBase::SaveParam(f,EnableCondition)==false){
		return false;
	}
	if(RWDeviceParams.Save(f)==false){
		return false;
	}
	return true;
}
bool	ParamRegulusWorld::LoadParam(QIODevice *f ,int EnableCondition)
{
	if(ParamBase::LoadParam(f,EnableCondition)==false){
		return false;
	}
	if(RWDeviceParams.Load(f)==false){
		return false;
	}
	return true;
}
bool	ParamRegulusWorld::LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition)
{
	if(ParamBase::LoadParam(f,StartPoint,EndPoint,EnableCondition)==false){
		return false;
	}
	if(RWDeviceParams.Load(f)==false){
		return false;
	}
	return true;
}

