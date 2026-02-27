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



#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "ShowIOForm.h"

//ShowIOForm	*Panel=NULL;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="Dummy PIO";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "16Bit dummy PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2012";
	return true;
}



IO_DLLFUNC int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return 1;
}

int IO_DLLFUNC _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	return 16;
}
int IO_DLLFUNC _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	return 16;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return true;
}
PIODLLBaseClass  IO_DLLFUNC _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	ShowIOForm	*Panel=new ShowIOForm();
	Panel->show();
	return Panel;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		if(Panel->InBit[bitIndex]==true)
			return 1;
		else
			return 0;
	}
	return 0;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		BYTE	Ret=0;
		for(int i=0;i<8;i++){
			if(Panel->InBit[byteIndex*8+i]==true)
				Ret |=1<<i;
		}
		return Ret;
	}
	return 0;
}
BYTE  IO_DLLFUNC _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		BYTE	Ret=0;
		for(int i=0;i<8;i++){
			if((data & (1<<i))!=0){
				Panel->OutBit[byteIndex*8+i]=true;
			}
			else{
				Panel->OutBit[byteIndex*8+i]=false;
			}
		}
		Panel->ShowOut();
		return data;
	}
	return 0;
}
int  IO_DLLFUNC _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		BYTE	Ret=0;
		for(int i=0;i<8;i++){
			if(Panel->OutBit[byteIndex*8+i]==true)
				Ret |=1<<i;
		}
		return Ret;
	}
	return 0;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	ShowIOForm	*Panel=(ShowIOForm	*)handle;
	if(Panel!=NULL){
		Panel->close();
	}
	return true;
}
bool  IO_DLLFUNC _cdecl AIP_IO_Release(void)
{
	return true;
}