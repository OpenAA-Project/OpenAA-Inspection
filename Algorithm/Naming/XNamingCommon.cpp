#include "XNaming.h"


bool	NamingGroupList::Save(QIODevice *f)
{
	if(::Save(f,GroupName)==false)
		return false;
	if(::Save(f,GroupID)==false)
		return false;
	return true;
}

bool	NamingGroupList::Load(QIODevice *f)
{
	if(::Load(f,GroupName)==false)
		return false;
	if(::Load(f,GroupID)==false)
		return false;
	return true;
}
