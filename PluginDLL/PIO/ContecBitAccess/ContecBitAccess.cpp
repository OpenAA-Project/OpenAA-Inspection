#include "ContecBitAccess.h"
#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include "CDio.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

//static short Id;


IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="PIO-BitAccess";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "CONTEC PIO Bit access";
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
	Contecboard	*PIO=(Contecboard *)handle;
	if(PIO==NULL)
		return 0;
	long Ret;
	short InPortNum;
	short OutPortNum;
	Ret = DioGetMaxPorts(PIO->Id, &InPortNum, &OutPortNum);
	if(Ret!=DIO_ERR_SUCCESS)
		return 0;

	return(InPortNum*8);
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	Contecboard	*PIO=(Contecboard *)handle;
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
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	bool	ok;
	int	BoardNo=Something.toInt(&ok);
	if(ok==false)
		BoardNo=0;
	char DeviceName[256];
	char Device[256];

	Ret = DioQueryDeviceName ( BoardNo , DeviceName , Device );
	if(Ret==DIO_ERR_INI_NO_MATCH_DRV_VERSION){
		QMessageBox::critical(NULL,"Error"
							  ,"Driver/CDIO.dll and software version is mismatched");
		return NULL;
	}
	if(Ret!=DIO_ERR_SUCCESS)
		return NULL;
	Contecboard	*PIO=new Contecboard();
	PIO->DeviceName	=DeviceName;
	PIO->Device		=Device;
	Ret = DioInit ( DeviceName , &PIO->Id );
	if(Ret != 0){
		delete	PIO;
		return NULL;
	}


	//デジ?ルフィル?の設定（PIO_DigitalFilter.datフ?イルの読み込み）
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
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	long Ret;
	BYTE InData;
	Contecboard	*PIO=(Contecboard *)handle;

	Ret = DioInpBit (PIO->Id , bitIndex , &InData );
	return(InData);
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	Contecboard	*PIO=(Contecboard *)handle;

	Ret = DioInpByte (PIO->Id , byteIndex , &InData );
	return(InData);
}

void  _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
{
	Contecboard	*PIO=(Contecboard *)handle;
	DioOutBit(PIO->Id ,bitIndex,data);
}
/*
BYTE  _cdecl AIP_IO_SetByte(int boardNumber , BYTE byteIndex , BYTE data)
{
	long Ret;

	Ret = DioOutByte ( Id , byteIndex , data );
	return(data);
}
*/

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	Contecboard	*PIO=(Contecboard *)handle;

	Ret = DioEchoBackByte (PIO->Id , byteIndex , &InData );
	return(InData);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	long Ret;

	Contecboard	*PIO=(Contecboard *)handle;
	Ret = DioExit (PIO->Id );
	if(Ret != 0){
		return(false);
	}
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}
