/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\contec64dll.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "windows.h"
#include "contec64dll2.h"
#include "AIP_IO.h"
#include "math.h"
#include "CDio.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>

int	QString2Char(const QString &str ,char *buff ,int buffsize);

//static short Id[2];

//#define	PIO_NAME	"IOLIB_PIO64"
#define	PIO_NAME	"IOLIB_PIO32"
//#define	PIO_NAME	"IOLIB_PIO16"

//#define	PIO_NAME2	"IOLIB_PIO64-2"
#define	PIO_NAME2	"IOLIB_PIO32-2"
//#define	PIO_NAME2	"IOLIB_PIO16-2"


IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str=PIO_NAME2;
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "CONTEC PIO : " PIO_NAME2;
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

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return 2;
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	Contec2boards	*PIO=(Contec2boards *)handle;
	if(PIO==NULL)
		return 0;
		
	short InPortNum;
	short OutPortNum;
	long Ret = DioGetMaxPorts(PIO->Id, &InPortNum, &OutPortNum);
	if(Ret!=DIO_ERR_SUCCESS)
		return 0;

	return(InPortNum*8);
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	Contec2boards	*PIO=(Contec2boards *)handle;
	if(PIO==NULL)
		return 0;
	long Ret;
	short InPortNum;
	short OutPortNum;
	Ret = DioGetMaxPorts(PIO->Id, &InPortNum, &OutPortNum);
	if(Ret!=DIO_ERR_SUCCESS)
		return 0;

	return(OutPortNum*8);
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{

	return true;
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	char DeviceName[256];
	char Device[256];
	Ret = DioQueryDeviceName ( boardNumber , DeviceName , Device );
	if(Ret!=DIO_ERR_SUCCESS)
		return NULL;

	Contec2boards	*PIO=new Contec2boards();
	PIO->DeviceName	=DeviceName;
	PIO->Device		=Device;
	Ret = DioInit ( DeviceName , &PIO->Id );
	if(Ret != 0){
		delete	PIO;
		return NULL;
	}		

/*
	//ビットの初期化
	int IOBit;
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		IOBit=16;
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		IOBit=32;
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		IOBit=64;

	for(int Cnt=0;Cnt<(IOBit>>3);Cnt++)
		AIP_IO_SetByte(0,Cnt,0);
*/
	//デジタルフィルタの設定（PIO_DigitalFilter.datファイルの読み込み）
	QStringList strList;
	QFile	mfile("./PIO_DigitalFilter.dat");
	if(mfile.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&mfile);
		QString myString;
		while (!mystream.atEnd()){
			myString=mystream.readLine();
			strList << myString;
		}
		mfile.close();

		if(strList.count()>0){
			bool ok=false;
			short DigitalFilter=strList[0].toShort(&ok);
			if(ok==true && (DigitalFilter>=0 && DigitalFilter<=20)){
				Ret=DioSetDigitalFilter(PIO->Id,DigitalFilter);
			}
		}
	}
	return PIO;
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	long Ret;
	BYTE InData;
	Contec2boards	*PIO=(Contec2boards *)handle;

	Ret = DioInpBit ( PIO->Id , bitIndex , &InData );
	return InData;
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	Contec2boards	*PIO=(Contec2boards *)handle;

	Ret = DioInpByte (  PIO->Id , byteIndex , &InData );
	return InData;
}

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	long Ret;
	Contec2boards	*PIO=(Contec2boards *)handle;

	Ret = DioOutByte (  PIO->Id, byteIndex , data );
	return data;
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	Contec2boards	*PIO=(Contec2boards *)handle;

	Ret = DioEchoBackByte (  PIO->Id , byteIndex , &InData );
	return InData;
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	long Ret;
	Contec2boards	*PIO=(Contec2boards *)handle;

	Ret = DioExit (  PIO->Id );
	if(Ret != 0){
		return false;
	}

	return true;
}

bool  _cdecl AIP_IO_Release(void)
{	

	return true;
}
