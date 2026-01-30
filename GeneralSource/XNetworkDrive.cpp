/*
 * Copyright (C) 2021
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



#include "XNetworkDrive.h"


#ifdef _MSC_VER
#include <windows.h>

#define	DEFFUNCEX		__declspec(dllexport) 


extern	"C"{

DEFFUNCEX	bool	CreateNetworkDrive(bool tInitialConnect 
						,int DriveCode				//A drive=0 ,B drive=1 ,,, Z drive=25
						,const QString  &tRemoteDiskName
						,const QString  &tPassword
						,const QString  &tUserName);
DEFFUNCEX	bool	DisconnectNetworkDrive(int DriveCode);

};
bool	CreateNetworkDrive(bool tInitialConnect 
						,int DriveCode 
						,const QString &tRemoteDiskName
						,const QString &tPassword
						,const QString &tUserName)
{
    NETRESOURCE nr;
	memset(&nr,0,sizeof(nr));
    WCHAR    DriveName[10];

    DriveName[0]='A'+DriveCode;
    DriveName[1]=':';
    DriveName[2]=0;

    nr.dwType=RESOURCETYPE_DISK;
    nr.lpLocalName=DriveName;
	wchar_t	tRemoteDiskNameBuff[256];
	memset(tRemoteDiskNameBuff,0,sizeof(tRemoteDiskNameBuff));
	tRemoteDiskName.toWCharArray (tRemoteDiskNameBuff);
	for(int i=0;i<wcslen(tRemoteDiskNameBuff);i++){
		if(tRemoteDiskNameBuff[i]=='/'){
			tRemoteDiskNameBuff[i]='\\';
		}
	}
	nr.lpRemoteName   =tRemoteDiskNameBuff;
    nr.lpProvider=NULL;
    if(tInitialConnect==true){
		if((tPassword.length()==0)
		&& (tUserName.length()==0)){
			if(::WNetAddConnection2(&nr ,NULL
				,NULL,CONNECT_UPDATE_PROFILE)==NO_ERROR){
                return(true);
			}
		}
		else{
			wchar_t	tPasswordBuff[256];
			memset(tPasswordBuff,0,sizeof(tPasswordBuff));
			tPassword.toWCharArray (tPasswordBuff);
			wchar_t	tUserNameBuff[256];
			memset(tUserNameBuff,0,sizeof(tUserNameBuff));
			tUserName.toWCharArray (tUserNameBuff);
			if(::WNetAddConnection2(&nr ,tPasswordBuff
				,tUserNameBuff,CONNECT_UPDATE_PROFILE)==NO_ERROR){
				return(true);
			}
		}
	}
    else{
		if((tPassword.length()==0)
		&& (tUserName.length()==0)){
			if(::WNetAddConnection2(&nr ,NULL
				,NULL,0)==NO_ERROR){
				return(true);
			}
		}
		else{
			wchar_t	tPasswordBuff[256];
			memset(tPasswordBuff,0,sizeof(tPasswordBuff));
			tPassword.toWCharArray (tPasswordBuff);
			wchar_t	tUserNameBuff[256];
			memset(tUserNameBuff,0,sizeof(tUserNameBuff));
			tUserName.toWCharArray (tUserNameBuff);
			if(::WNetAddConnection2(&nr ,tPasswordBuff
				,tUserNameBuff,0)==NO_ERROR){
				return(true);
			}
		}
	}
	return(false);

}

bool	DisconnectNetworkDrive(int DriveCode)
{
    WCHAR    DriveName[10];

    DriveName[0]='A'+DriveCode;
    DriveName[1]=':';
    DriveName[2]=0;

	WNetCancelConnection2(DriveName,0,false);

	return true;
}

#else
bool	CreateNetworkDrive(bool tInitialConnect 
						,int DriveCode 
						,const QString &tRemoteDiskName
						,const QString &tPassword
						,const QString &tUserName)
{
	return true;
}
bool	DisconnectNetworkDrive(int DriveCode)
{
	return true;
}

#endif