#include "XDestination.h"
#include "XGeneralFunc.h"

bool	DestinationPartner::Save(QIODevice *f)
{
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,LocalPath)==false)
		return false;
	return true;
}

bool	DestinationPartner::Load(QIODevice *f)
{
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,LocalPath)==false)
		return false;
	return true;
}