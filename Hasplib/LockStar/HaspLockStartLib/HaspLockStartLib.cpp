/*
 * Copyright (C) 2025
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

#include "HaspLockStartLib.h"
#include "XLockStarKey.h"
#include <stdlib.h>


static	int	CountOfLockStar;
static	GUID	USBKeyGUIDDImLockStar[100];
static	struct	LockStartKeyStruct	Data64;


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

bool	CheckHasp(int ProductCode ,int ProductVersion ,HaspErrorCode &ErrorCode)
{
	BOOL	B=SKAPIInitialize();
	if(B==false){
		ErrorCode=Hasp_NoDriver;
		return false;
	}
	CountOfLockStar=0;
	SKAPIEnumDevices((ENUMDEVICEPROC)EnumDeviceProc, 0);
	if(CountOfLockStar==0){
		SKAPIClose();
		ErrorCode=Hasp_NoKey;
		return false;
	}
	ErrorCode=Hasp_NoKey;
	for(int i=0;i<CountOfLockStar;i++){
		SKCONTROLDATA	pcd;
		B=SKAPIGetControlData(&USBKeyGUIDDImLockStar[i], (const BYTE *)/**/"12345678", &pcd);
		if(B==false){
			continue;
		}

		GUID ProductGUID;
		HRESULT	R=FormatStringToGUID(/**/"{FD01B805-3285-4D03-9ABE-AC132E2A990A}",&ProductGUID);

		B=PKAPIGetUserData(&USBKeyGUIDDImLockStar[i], &ProductGUID, 0x83A92EC2, (BYTE*)&Data64);
		if(B==false){
			ErrorCode=Hasp_TimeUp;
			continue;
		}
		for(int row=0;row<Data64.DataNumb;row++){
			if(Data64.ProductData[row].ProductCode==ProductCode
			&& Data64.ProductData[row].ProductVersion<=ProductVersion){
				SKAPIClose();
				ErrorCode=Hasp_OK;
				return true;
			}
		}
		ErrorCode=Hasp_NoLicense;
	}
	SKAPIClose();
	
	return false;
}