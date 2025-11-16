#include "ButtonChangeServerFormResource.h"
#include "XChangeServerInfo.h"
#include "XGeneralFunc.h"


bool	ChangeServerInfo::Save(QIODevice *f)
{
	if(::Save(f,ServerName)==false)
		return false;
	if(::Save(f,DBIPAddress)==false)
		return false;
	if(::Save(f,DBPort)==false)
		return false;
	if(::Save(f,DBFileName)==false)
		return false;
	if(::Save(f,ImagePath)==false)
		return false;
	return true;
}

bool	ChangeServerInfo::Load(QIODevice *f)
{
	if(::Load(f,ServerName)==false)
		return false;
	if(::Load(f,DBIPAddress)==false)
		return false;
	if(::Load(f,DBPort)==false)
		return false;
	if(::Load(f,DBFileName)==false)
		return false;
	if(::Load(f,ImagePath)==false)
		return false;
	return true;
}
ChangeServerInfo	&ChangeServerInfo::operator=(ChangeServerInfo &src)
{
	ServerName	=src.ServerName;
	DBIPAddress	=src.DBIPAddress;
	DBPort		=src.DBPort;
	DBFileName	=src.DBFileName;
	ImagePath	=src.ImagePath;
	return *this;
}