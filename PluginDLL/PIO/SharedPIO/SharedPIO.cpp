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

#include "SharedPIO.h"
#include "SharedPIOCommon.h"
#include "AIP_IO.h"

SharedPIO::SharedPIO(const QString &Key)
	:PIOMemory(Key)
{
	PIOMemory.attach();
}

SharedPIO::~SharedPIO()
{

}
//====================================================

DEFFUNCEX WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

DEFFUNCEX bool	DLL_GetName(QString &str)
{
	str="SharedPIO";
	return true;
}
DEFFUNCEX const char	*DLL_GetExplain(void)
{
	return "Shared PIO";
}
DEFFUNCEX WORD	DLL_GetVersion(void)
{
	return 1;
}
DEFFUNCEX bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2020";
	return true;
}

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short InBitNum=0;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		InBitNum=p->InBitCount;
		PIO->PIOMemory.unlock();
	}
	return InBitNum;
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short OutBitNum=0;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		OutBitNum=p->OutBitCount;
		PIO->PIOMemory.unlock();
	}
	return(OutBitNum);
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
/*
	Something	=	PIO name
*/
{
	long Ret;

	SharedPIO	*PIO=NULL;
	if(Something.isEmpty()==false){
		PIO=new SharedPIO(Something);
	}
	else{
		PIO=new SharedPIO(/**/"SharedPIO");
	}
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short OutBitNum;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		BYTE	d=p->InData[bitIndex>>3]&(0x01<<(bitIndex&7));
		PIO->PIOMemory.unlock();
		if(d==0)
			return 0;
		else
			return 1;
	}
	return 0;
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short OutBitNum;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		BYTE	d=p->InData[byteIndex];
		PIO->PIOMemory.unlock();
		return d;
	}
	return 0;
}

void  _cdecl AIP_IO_SetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return;
	short OutBitNum;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		if(data!=0)
			p->OutData[bitIndex>>3] |=(0x01<<(bitIndex&7));
		else
			p->OutData[bitIndex>>3] &=~(0x01<<(bitIndex&7));
		PIO->PIOMemory.unlock();
	}
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short OutBitNum;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		p->OutData[byteIndex] =data;
		PIO->PIOMemory.unlock();
		return data;
	}
	return 0;
}


int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short OutBitNum;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.lock();
		struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIO->PIOMemory.data();
		BYTE	d=p->OutData[byteIndex];
		PIO->PIOMemory.unlock();
		return d;
	}
	return 0;

}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	SharedPIO	*PIO=(SharedPIO *)handle;
	if(PIO==NULL)
		return 0;
	short OutBitNum;
	if(PIO->PIOMemory.isAttached()==true){
		PIO->PIOMemory.detach();
	}
	delete	PIO;

	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}