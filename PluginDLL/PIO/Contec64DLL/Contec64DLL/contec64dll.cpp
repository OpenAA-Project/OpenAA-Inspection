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
#include "contec64dll.h"
#include "AIP_IO.h"
#include "math.h"
#include "CDio.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>

//static short Id;

//#define	PIO_NAME	"IOLIB_PIO64"
#define	PIO_NAME	"IOLIB_PIO32"
//#define	PIO_NAME	"IOLIB_PIO16"


IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str=PIO_NAME;
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "CONTEC PIO : " PIO_NAME;
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
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{

	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	short Id;
	char DeviceName[256];
	char Device[256];
	for(int i=0;i<256;i++){
		Ret = DioQueryDeviceName ( i , DeviceName , Device );
		if(Ret!=DIO_ERR_SUCCESS)
			return NULL;
		Ret = DioInit ( DeviceName , &Id );
		if(Ret != 0)
			return NULL;
		break;
	}



//	Ret = DioInit ( "DIO000" , &Id );
//	if(Ret != 0)
//		return(false);

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
				Ret=DioSetDigitalFilter(Id,DigitalFilter);
			}
		}
	}
	return((void *)Id);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	long Ret;
	BYTE InData;
	short Id=(short)handle;

	Ret = DioInpBit ( Id , bitIndex , &InData );
	return(InData);
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	short Id=(short)handle;

	Ret = DioInpByte ( Id , byteIndex , &InData );
	return(InData);
}

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	long Ret;
	short Id=(short)handle;

	Ret = DioOutByte ( Id , byteIndex , data );
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	short Id=(short)handle;

	Ret = DioEchoBackByte ( Id , byteIndex , &InData );
	return(InData);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	long Ret;
	short Id=(short)handle;
	Ret = DioExit ( Id );
	if(Ret != 0){
		return(false);
	}
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	

	return(true);
}
