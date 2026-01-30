/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
