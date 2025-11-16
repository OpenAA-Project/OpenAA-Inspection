#include "MakeLockStarKey.h"

#define	_AMD64_

#include <ObjBase.h>
#include <WTypes.h>
#include <Guiddef.h>         // MFC core and standard components
#include <WinDef.h>         // MFC core and standard components
#include "XLockStarKey.h"

int	CountOfLockStar;
GUID	USBKeyGUIDDImLockStar[100];

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
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return 0;
}


MakeLockStarKey::MakeLockStarKey(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	BOOL	B=SKAPIInitialize();
	B=SKAPIEnumDevices((ENUMDEVICEPROC)EnumDeviceProc, 0);

	SKCONTROLDATA	pcd;
	B=SKAPIGetControlData(&USBKeyGUIDDImLockStar[0],(const BYTE *) /**/"12345678", &pcd);

	//struct	LockStartKeyStruct	LData;
	GUID ProductGUID;
	HRESULT	R=FormatStringToGUID(/**/"{FD01B805-3285-4D03-9ABE-AC132E2A990A}",&ProductGUID);

	struct	LockStartKeyStruct	Data64;
	B=PKAPIGetUserData(&USBKeyGUIDDImLockStar[0], &ProductGUID, 0x83A92EC2, (BYTE*)&Data64);
	SKAPIClose();
}

MakeLockStarKey::~MakeLockStarKey()
{

}
