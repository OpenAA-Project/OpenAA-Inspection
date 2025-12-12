#include "XGeneralFuncCore.h"
#include "ActivationLib.h"
#include "XTypeDef.h"
#include "XSimpleCrypt.h"

bool	SerialNumberClass::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)				==false)	return false;
	if(::Save(f,OSSerial)			==false)	return false;
	if(::Save(f,BiosSerial)			==false)	return false;
	if(::Save(f,NetworkMacAddress)	==false)	return false;
	if(::Save(f,UserFirstHDD)		==false)	return false;
	return true;
}

bool	SerialNumberClass::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)				==false)	return false;
	if(::Load(f,OSSerial)			==false)	return false;
	if(::Load(f,BiosSerial)			==false)	return false;
	if(::Load(f,NetworkMacAddress)	==false)	return false;
	if(::Load(f,UserFirstHDD)		==false)	return false;
	return true;
}
SerialNumberClass	&SerialNumberClass::operator=(const SerialNumberClass &src)
{
	OSSerial			=src.OSSerial;
	BiosSerial			=src.BiosSerial;
	NetworkMacAddress	=src.NetworkMacAddress;
	UserFirstHDD		=src.UserFirstHDD;
	return *this;
}
bool	SerialNumberClass::isMatch(SerialNumberClass &s)
{
	int	Matching=0;
	if(OSSerial==s.OSSerial)
		Matching++;
	if(BiosSerial==s.BiosSerial)
		Matching++;
	for(int i=0;i<NetworkMacAddress.count();i++){
		for(int j=0;j<s.NetworkMacAddress.count();j++){
			QString	a=NetworkMacAddress[i];
			QString	b=s.NetworkMacAddress[j];
			if(a==b){
				Matching++;
			}
		}
	}
	if(UserFirstHDD==s.UserFirstHDD)
		Matching++;
	if(Matching>=2){
		return true;
	}
	return false;
}

//======================================================================

AuthenticatedProgramList::AuthenticatedProgramList(void)
{
	ApplicationAutoCode		=-1;
}
bool	AuthenticatedProgramList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)				==false)	return false;
	if(CategoryAutoCount.Save(f)	==false)	return false;
	if(::Save(f,ApplicationAutoCode)==false)	return false;
	if(::Save(f,StartTime)			==false)	return false;
	if(::Save(f,EndTime)			==false)	return false;
	return true;
}
bool	AuthenticatedProgramList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)				==false)	return false;
	if(CategoryAutoCount.Load(f)	==false)	return false;
	if(::Load(f,ApplicationAutoCode)==false)	return false;
	if(::Load(f,StartTime)			==false)	return false;
	if(::Load(f,EndTime)			==false)	return false;
	return true;
}
AuthenticatedProgramList	*AuthenticatedProgramContainer::Create(void)
{
	return new AuthenticatedProgramList();
}

//======================================================================

AuthenticatedComponentList::AuthenticatedComponentList(void)
{
	AuthenticatedID=-1;
}
bool	AuthenticatedComponentList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)			==false)	return false;
	if(::Save(f,DLLRoot)		==false)	return false;
	if(::Save(f,DLLName)		==false)	return false;
	if(::Save(f,AuthenticatedID)==false)	return false;
	if(::Save(f,StartTime)		==false)	return false;
	if(::Save(f,EndTime)		==false)	return false;
	return true;
}
bool	AuthenticatedComponentList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)			==false)	return false;
	if(::Load(f,DLLRoot)		==false)	return false;
	if(::Load(f,DLLName)		==false)	return false;
	if(::Load(f,AuthenticatedID)==false)	return false;
	if(::Load(f,StartTime)		==false)	return false;
	if(::Load(f,EndTime)		==false)	return false;
	return true;
}
AuthenticatedComponentList	*AuthenticatedComponentContainer::Create(void)
{
	return new AuthenticatedComponentList();
}

//======================================================================
#define	CryptoKey		431267509334028634LL

bool	AuthenticatedInfo::Save(QIODevice *f)
{
	QBuffer	Buff;

	Buff.open(QIODevice::WriteOnly);

	int32	Ver=1;
	if(::Save(&Buff,Ver)			==false)	return false;
	if(AuthenticatedUser.Save(&Buff)==false)	return false;
	if(Programs.Save(&Buff)			==false)	return false;
	if(Components.Save(&Buff)		==false)	return false;

	QByteArray	Data=Buff.buffer();
	SimpleCrypt	Crypto(CryptoKey);
	QByteArray	HashCode=Crypto.encryptToByteArray(Data) ;

	if(::Save(f,HashCode)	==false)	return false;

	return true;
}
bool	AuthenticatedInfo::Load(QIODevice *f)
{
	QByteArray	HashCode;
	if(::Load(f,HashCode)	==false)	return false;

	SimpleCrypt	Crypto(CryptoKey);
	QByteArray Data=Crypto.decryptToByteArray(HashCode) ;

	QBuffer	Buff(&Data);

	Buff.open(QIODevice::ReadOnly);

	int32	Ver;
	if(::Load(&Buff,Ver)			==false)	return false;
	if(AuthenticatedUser.Load(&Buff)==false)	return false;
	if(Programs.Load(&Buff)			==false)	return false;
	if(Components.Load(&Buff)		==false)	return false;

	return true;
}