/*
 * Copyright (C) 2023
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
#include "Dask64.h"
#include "XIODLL.h"

//Adlink PCI-7230

//static	I16	CardID;
static	U32 OutData;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="ADLink PCI-7230";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "ADLink PCI-7230";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2011";
	return true;
}

class	PIOHandle :public PIODLLBaseClass
{
public:
	I16	CardID;
};

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 16;
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 16;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

PIODLLBaseClass  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	bool	ok;
	int	num=Something.toInt(&ok);
	if(ok==false){
		num=0;
	}
	PIOHandle	*Handle=new PIOHandle();
	Handle->CardID=Register_Card(PCI_7230, num);

	return((void *)Handle);
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	PIOHandle	*Handle=(PIOHandle	*)handle;
	U32 InData;

	I16	Ret = DI_ReadPort(Handle->CardID,0,&InData);
	if(((InData>>bitIndex) & 0x01)!=0)
		return 1;
	return 0;
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOHandle	*Handle=(PIOHandle	*)handle;
	U32 InData;

	I16	Ret = DI_ReadPort(Handle->CardID,0,&InData);
	return ((BYTE *)&InData)[byteIndex];
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PIOHandle	*Handle=(PIOHandle	*)handle;
	long Ret;

	((BYTE *)&OutData)[byteIndex]=data;
	DO_WritePort(Handle->CardID,boardNumber, OutData);
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOHandle	*Handle=(PIOHandle	*)handle;
	U32 InData;

	I16	Ret = DO_ReadPort(Handle->CardID,0,&InData);
	return ((BYTE *)&InData)[byteIndex];
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	PIOHandle	*Handle=(PIOHandle	*)handle;
	I16 Release_Card (Handle->CardID);
	delete	Handle;
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	

	return(true);
}