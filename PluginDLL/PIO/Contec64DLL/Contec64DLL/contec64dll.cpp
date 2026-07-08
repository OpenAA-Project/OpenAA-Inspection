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
#include "contec64dll.h"
#include "AIP_IO.h"
#include "math.h"
#include "CDio.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "XIODLL.h"

//static short Id;

//#define	PIO_NAME	"IOLIB_PIO64"
#define	PIO_NAME	"IOLIB_PIO32"
//#define	PIO_NAME	"IOLIB_PIO16"

class	PIOHandle :public PIODLLBaseClass
{
public:
	short Id;
};


DEFFUNCEX WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

DEFFUNCEX bool	DLL_GetName(QString &str)
{
	str=PIO_NAME;
	return true;
}
DEFFUNCEX const char	*DLL_GetExplain(void)
{
	return "CONTEC PIO : " PIO_NAME;
}
DEFFUNCEX WORD	DLL_GetVersion(void)
{
	return 1;
}
DEFFUNCEX bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2011";
	return true;
}


DEFFUNCEX	int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

DEFFUNCEX	int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

DEFFUNCEX	int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

DEFFUNCEX	bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{

	return(true);
}

DEFFUNCEX	PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	PIOHandle *Handle = new PIOHandle;
	char DeviceName[256];
	char Device[256];
	for(int i=0;i<256;i++){
		Ret = DioQueryDeviceName ( i , DeviceName , Device );
		if(Ret!=DIO_ERR_SUCCESS)
			return NULL;
		Ret = DioInit ( DeviceName , &Handle->Id );
		if(Ret != 0)
			return NULL;
		break;
	}

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
				Ret=DioSetDigitalFilter(Handle->Id,DigitalFilter);
			}
		}
	}
	return(Handle);
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	long Ret;
	BYTE InData;
	PIOHandle	*Handle=(PIOHandle *)handle;

	Ret = DioInpBit ( Handle->Id , bitIndex , &InData );
	return(InData);
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	PIOHandle	*Handle=(PIOHandle *)handle;

	Ret = DioInpByte ( Handle->Id , byteIndex , &InData );
	return(InData);
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	long Ret;
	PIOHandle	*Handle=(PIOHandle *)handle;

	Ret = DioOutByte ( Handle->Id , byteIndex , data );
	return(data);
}

DEFFUNCEX	int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	PIOHandle	*Handle=(PIOHandle *)handle;

	Ret = DioEchoBackByte ( Handle->Id , byteIndex , &InData );
	return(InData);
}

DEFFUNCEX	bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	long Ret;
	PIOHandle	*Handle=(PIOHandle *)handle;
	Ret = DioExit ( Handle->Id );
	if(Ret != 0){
		return(false);
	}
	return(true);
}

DEFFUNCEX	bool  _cdecl AIP_IO_Release(void)
{	

	return(true);
}