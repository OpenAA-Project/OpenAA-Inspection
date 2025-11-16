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

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	return(32);
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	PIOForCameraExecuter	*PIO=(PIOForCameraExecuter *)handle;
	return(32);
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	int	BoardNo=Something.toInt();
	PIOForCameraExecuter	*PIO	=new PIOForCameraExecuter(BoardNo);
	PIO->Start();
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
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

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
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

void  _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
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

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
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

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
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

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
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
