#include "XHaspDLL.h"

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XGeneralFunc.h"
#include <QDir.h>
#include <QFile.h>

#include "XLockStarKey.h"
#include "LockStarDLL.h"

static	int	CountOfLockStar;
static	GUID	USBKeyGUIDDImLockStar[100];



extern "C" {
BOOL WINAPI EnumDeviceProc(GUID* pidDevice, DWORD dwParam);


BOOL WINAPI EnumDeviceProc(GUID* pidDevice, DWORD dwParam)
{
	USBKeyGUIDDImLockStar[CountOfLockStar]=*pidDevice;
	CountOfLockStar++;
	return TRUE;
}

};

HRESULT FormatStringToGUID(char *szGUID,GUID *pguid)
{
	OLECHAR wszGUID[39];
	mbstowcs(wszGUID,szGUID,39);
	wszGUID[38] = 0;
	return CLSIDFromString(wszGUID,pguid);
}

HRESULT FormatGUIDToString(GUID guid, char *szGUID, int size)
{
	if (size < 39)
	{
		return false;
	}
	sprintf(szGUID, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		 (unsigned int)guid.Data1
		,(unsigned int)guid.Data2
		,(unsigned int)guid.Data3
		,(unsigned int)guid.Data4[0]
		,(unsigned int)guid.Data4[1]
		,(unsigned int)guid.Data4[2]
		,(unsigned int)guid.Data4[3]
		,(unsigned int)guid.Data4[4]
		,(unsigned int)guid.Data4[5]
		,(unsigned int)guid.Data4[6]
		,(unsigned int)guid.Data4[7]);

	return 0;
}

LockStarDLL::~LockStarDLL(void)
{
}

bool3	LockStarDLL::PermitByDate(const QString &DLLRoot ,const QString &DLLName
								,qint64 SpanSecFromInstall
								,const QString &_CurrentVersion
								,QString &FailMessage
								,int &ErrorCode)
{
	return none3;
}

bool3	LockStarDLL::PermitByProgram(const QString &ProgramCode
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)
{
	BOOL	B;
	SKCONTROLDATA	pcd;
	B=SKAPIGetControlData(&USBKeyGUID, (const BYTE *)/**/"12345678", &pcd);
	if(B==false){
		ErrorCode=Error_Authentic_NotRecognized;
		return false3;
	}

	GUID ProductGUID;
	HRESULT	R=FormatStringToGUID(/**/"{FD01B805-3285-4D03-9ABE-AC132E2A990A}",&ProductGUID);

	struct	LockStartKeyStruct	Data64;
	B=PKAPIGetUserData(&USBKeyGUID, &ProductGUID, 0x83A92EC2, (BYTE*)&Data64);
	if(B==false){
		ErrorCode=Error_Authentic_NotRecognized;
		return false3;
	}
	if(ProgramCode==/**/"je8398hw"){
		for(int row=0;row<Data64.DataNumb;row++){
			if(Data64.ProductData[row].ProductCode==6){
			//&& Data64.ProductData[row].ProductVersion<=ProductVersion){
				SKAPIClose();
				return true3;
			}
			if(Data64.ProductData[row].ProductCode==7){
			//&& Data64.ProductData[row].ProductVersion<=ProductVersion){
				SKAPIClose();
				return true3;
			}
		}
	}
	if(ProgramCode==/**/"hs3fp6w"){
		for(int row=0;row<Data64.DataNumb;row++){
			if(Data64.ProductData[row].ProductCode==8){
			//&& Data64.ProductData[row].ProductVersion<=ProductVersion){
				SKAPIClose();
				return true3;
			}
		}
	}
	ErrorCode=Error_Authentic_InvalidLicenseKey;
	return false3;
}
bool3	LockStarDLL::PermitByID(const QString &DLLRoot ,const QString &DLLName ,int id
									,const QString &_CurrentVersion
									,QString &FailMessage
									,int &ErrorCode)
{
	return none3;
}

bool3	NoLockStarDLL::PermitByDate(const QString &DLLRoot ,const QString &DLLName
											,qint64 SpanSecFromInstall
											,const QString &_CurrentVersion
											,QString &FailMessage
											,int &ErrorCode)
{
	return false3;
}
bool3	NoLockStarDLL::PermitByProgram(const QString &ProgramCode
											,const QString &_CurrentVersion
											,QString &FailMessage
											,int &ErrorCode)
{
	return false3;
}

bool3	NoLockStarDLL::PermitByID(const QString &DLLRoot ,const QString &DLLName, int id
											,const QString &_CurrentVersion
											,QString &FailMessage
											,int &ErrorCode)
{
	return false3;
}

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLHaspMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LockStarHaspDLL";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Hasp DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2021.06";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Hasp control for LockStar";
}

HaspHandleContainer		*_cdecl	DLL_Initial(LayersBase *base,const QString &ParamStr)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	HaspHandleContainer	*H=new HaspHandleContainer();
	BOOL	B=SKAPIInitialize();
	if(B==TRUE){
		CountOfLockStar=0;
		SKAPIEnumDevices((ENUMDEVICEPROC)EnumDeviceProc, 0);
		if(CountOfLockStar!=0){
			for(int i=0;i<CountOfLockStar;i++){
				LockStarDLL	*d=new LockStarDLL();
				d->USBKeyGUID=USBKeyGUIDDImLockStar[i];
				d->Number=i;
				H->AppendList(d);
			}
		}
		else{
			NoLockStarDLL	*d=new NoLockStarDLL();
			H->AppendList(d);
		}
		SKAPIClose();
	}
	else{
		NoLockStarDLL	*d=new NoLockStarDLL();
		H->AppendList(d);
	}
	return H;
}

bool		_cdecl	DLL_Close(HaspHandleContainer *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	HaspHandleContainer	*H=(HaspHandleContainer *)handle;
	if(H!=NULL){
		delete	H;
	}

	return true;
}

//=======================================================================================


