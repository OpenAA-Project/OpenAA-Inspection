#include "XBooter.h"
#include "XGeneralFunc.h"

bool	ExecuteApplicationList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Program)==false)
		return false;
	if(::Save(f,Parameter)==false)
		return false;
	return true;
}

bool	ExecuteApplicationList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Program)==false)
		return false;
	if(::Load(f,Parameter)==false)
		return false;
	return true;
}

BooterParameter::BooterParameter(void)
{
	DefaultFileName=/**/"BooterParameter.dat";
}

bool	BooterParameter::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,WindowMessage)==false)
		return false;
	if(::Save(f,ButtonMessage)==false)
		return false;
	if(::Save(f,RemoteReceiver)==false)
		return false;
	if(BeforeBoot.Save(f)==false)
		return false;
	if(::Save(f,ExecuteBeforeBooter)==false)
		return false;
	if(AfterBoot.Save(f)==false)
		return false;
	if(::Save(f,ExecuteAfterBooter)==false)
		return false;
	return true;
}

bool	BooterParameter::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,WindowMessage)==false)
		return false;
	if(::Load(f,ButtonMessage)==false)
		return false;
	if(::Load(f,RemoteReceiver)==false)
		return false;
	if(BeforeBoot.Load(f)==false)
		return false;
	if(::Load(f,ExecuteBeforeBooter)==false)
		return false;
	if(AfterBoot.Load(f)==false)
		return false;
	if(::Load(f,ExecuteAfterBooter)==false)
		return false;
	return true;
}