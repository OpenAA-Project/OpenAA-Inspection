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

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="SharedPIO";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "Shared PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2020";
	return true;
}

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
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

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
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

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
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

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
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

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
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

void  _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
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

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
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


int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
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

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
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
