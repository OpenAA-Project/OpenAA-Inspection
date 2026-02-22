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

#include "PIOForCameraExecuter.h"
#include "AIP_IO.h"

PIOForCameraExecuter::PIOForCameraExecuter(int n)
	:MemoryMapIN(QString("IOMapIN")+QString::number(n))
	,MemoryMapOUT(QString("IOMapOUT")+QString::number(n))
{
	PointerIN=NULL;
	PointerOUT=NULL;
}

PIOForCameraExecuter::~PIOForCameraExecuter()
{

}

bool	PIOForCameraExecuter::Start(void)
{
	if(MemoryMapIN.attach()==true && MemoryMapOUT.attach()==true){
		PointerIN=(BYTE *)MemoryMapIN.data();
		PointerOUT=(BYTE *)MemoryMapOUT.data();
		return true;
	}
	return false;
}

//=========================================================================
//PIOForCameraExecuter	*PIO;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="PIO for CameraExecuter";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "PIO for CameraExecuter";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2018";
	return true;
}

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	return(32);
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	return(32);
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

PIODLLBaseClass  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	int	BoardNo=Something.toInt();
	PIOForCameraExecuter	*PIO	=new PIOForCameraExecuter(BoardNo);
	PIO->Start();
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	if(PIO==NULL)
		return 0;
	if(PIO->PointerIN==NULL)
		return 0;

	PIO->MemoryMapIN.lock();
	BYTE	d=((PIO->PointerIN[bitIndex>>3] & (1<<(bitIndex&7)))==0)?0:1;
	PIO->MemoryMapIN.unlock();
	return d;
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	if(PIO==NULL)
		return 0;
	if(PIO->PointerIN==NULL)
		return 0;

	PIO->MemoryMapIN.lock();
	BYTE	d=PIO->PointerIN[byteIndex];
	PIO->MemoryMapIN.unlock();
	return d;
}

void  _cdecl AIP_IO_SetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	if(PIO==NULL)
		return;
	if(PIO->PointerOUT==NULL)
		return;
	PIO->MemoryMapOUT.lock();
	if(data==0)
		PIO->PointerOUT[bitIndex>>3] &= ~(1<<(bitIndex&7));
	else
		PIO->PointerOUT[bitIndex>>3] |= (1<<(bitIndex&7));
	PIO->MemoryMapOUT.unlock();
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	if(PIO==NULL)
		return 0;
	if(PIO->PointerOUT==NULL)
		return 0;
	PIO->MemoryMapOUT.lock();
	PIO->PointerOUT[byteIndex] = data;
	PIO->MemoryMapOUT.unlock();
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	if(PIO==NULL)
		return 0;
	if(PIO->PointerOUT==NULL)
		return 0;
	PIO->MemoryMapOUT.lock();
	int	d=(PIO->PointerOUT[byteIndex]);
	PIO->MemoryMapOUT.unlock();
	return d;
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	delete	PIO;
	//PIO=NULL;
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}