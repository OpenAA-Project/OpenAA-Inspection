/*
 * Copyright (C) 2022
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

#include "XVirtualPIOAdapter.h"
#include "AIP_IO.h"


//===============================================================================

//PIOAdapter	*PIO=NULL;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="VirtualPIOAdapter";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "PIO Client for network PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2016.6";
	return true;
}


int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	PIOAdapter	*PIO=(PIOAdapter *)handle;
	if(PIO==NULL)
		return 0;
	return PIO->GetBitCountIn();
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	PIOAdapter	*PIO=(PIOAdapter *)handle;
	if(PIO==NULL)
		return 0;
	return PIO->GetBitCountOut();
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	QStringList	List=Something.split(QChar(','));

	QString	IPAddress	=/**/"localhost";
	int		PortNumber	=28200;
	QString	DefFileName	=/**/"IODef.dat";
	QString	MemName		=/**/"VirtualPIO";

	if(List.count()>=1){
		IPAddress	=List[0];
	}
	if(List.count()>=2){
		bool	ok;
		int	iPortNumber	=List[1].toInt(&ok);
		if(ok==true)
			PortNumber=iPortNumber;
	}
	if(List.count()>=3){
		DefFileName=List[2];
	}
	if(List.count()>=4){
		MemName=List[3];
	}

	PIOAdapter	*PIO=new PIOAdapter(mainW,IPAddress,PortNumber,MemName);
	PIO->LoadDefFile(DefFileName);
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	PIOAdapter	*PIO=(PIOAdapter	*)handle;
	if(PIO!=NULL && PIO->GetBitData(bitIndex)!=0)
		return 1;
	return 0;
}
void  _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
{
	PIOAdapter	*PIO=(PIOAdapter	*)handle;
	if(PIO!=NULL){
		PIO->SetBitData(bitIndex ,data);
	}
}

int  _cdecl AIP_IO_GetOutBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	PIOAdapter	*PIO=(PIOAdapter	*)handle;
	if(PIO!=NULL && PIO->GetBitOutData(bitIndex)!=0)
		return 1;
	return 0;
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	PIOAdapter	*PIO=(PIOAdapter	*)handle;
	delete	PIO;
	//PIO=NULL;

	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{
	return(true);
}