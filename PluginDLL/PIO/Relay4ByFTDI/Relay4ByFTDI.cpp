#include "Relay4ByFTDI.h"
#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>


IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="Relay4ByFTDI";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "Relay 4 port boards through FTDI-USB (FTDI-245R)";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2019";
	return true;
}

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	return(4);
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	bool	ok;
	int	DeviceNumber=Something.toInt(&ok);
	if(ok==false)
		DeviceNumber=0;

	Relay4ByFTDI	*H=new Relay4ByFTDI;
	H->OutD=0;

	FT_STATUS ret=FT_Open (DeviceNumber, &H->Handle);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	ret=FT_SetBitMode(H->Handle, 0xF, 1);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	ret=FT_SetBaudRate(H->Handle, 9600);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	/*
	ret=FT_SetDataCharacteristics(H->Handle,FT_BITS_8,FT_STOP_BITS_1,FT_PARITY_NONE);
	if(ret!=FT_OK){
		delete	H;
		return NULL;
	}
	*/

	return(H);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	return(0);
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	return(0);
}


void  _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
{
	Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
	DWORD	BytesWriten;

	if(data==0)
		PIO->OutD &=~(1<<bitIndex);
	else
		PIO->OutD |= (1<<bitIndex);


	FT_STATUS	ret=FT_Write(PIO->Handle, &PIO->OutD, 1, &BytesWriten);
	if(ret!=FT_OK || BytesWriten!=1){
		PIO->Error=true;
	}
}

/*
BYTE  _cdecl AIP_IO_SetByte(void *handle ,BYTE byteIndex , BYTE data)
{
	Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
	DWORD	BytesWriten;

	FT_STATUS	ret=FT_Write(PIO->Handle, &data, 1, &BytesWriten);
	if(ret!=FT_OK || BytesWriten!=1){
		PIO->Error=true;
	}
	return data;
}
*/

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	return(0);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	Relay4ByFTDI	*PIO=(Relay4ByFTDI *)handle;
	FT_STATUS ret=FT_Close (PIO->Handle);
	if(ret==FT_OK){
		return(true);
	}
	return false;
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}
