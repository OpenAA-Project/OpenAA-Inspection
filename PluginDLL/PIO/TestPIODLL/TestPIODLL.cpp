#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include "CDio.h"
#include "TestPIODLL.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "TestForm.h"

//static	TestForm	*TestFormDim;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="TestPIO";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "CONTEC PIO (No Name) and Test";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2013";
	return true;
}

int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	long Ret;
	short InPortNum;
	short OutPortNum;
	TestForm	*PIO=(TestForm *)handle;

	TestForm::IOAccess.lock();
	Ret = DioGetMaxPorts(PIO->BoardID, &InPortNum, &OutPortNum);
	TestForm::IOAccess.unlock();
	if(Ret!=DIO_ERR_SUCCESS)
		return 0;

	return(InPortNum*8);
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	long Ret;
	short InPortNum;
	short OutPortNum;
	TestForm	*PIO=(TestForm *)handle;

	TestForm::IOAccess.lock();
	Ret = DioGetMaxPorts(PIO->BoardID, &InPortNum, &OutPortNum);
	TestForm::IOAccess.unlock();
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

	int	BoardNo=Something.toInt();
	char DeviceName[256];
	char Device[256];

	Ret = DioQueryDeviceName ( BoardNo , DeviceName , Device );
	if(Ret!=DIO_ERR_SUCCESS)
		return NULL;
	short	Id;
	Ret = DioInit ( DeviceName , &Id );
	if(Ret != 0){
		return NULL;
	}


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
	TestForm	*TestFormDim=new TestForm(Id);
	TestFormDim->show();
	return TestFormDim;
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	BYTE InData;
	TestForm	*PIO=(TestForm *)handle;

	if(PIO!=NULL){
		InData=PIO->GetBufferedInBit(bitIndex);
	}
	else{
		long Ret;
		TestForm::IOAccess.lock();
		Ret = DioInpBit ( PIO->BoardID , bitIndex , &InData );
		TestForm::IOAccess.unlock();
	}
	return(InData);
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	BYTE InData;
	TestForm	*PIO=(TestForm *)handle;

	if(PIO!=NULL){
		InData=PIO->GetBufferedInByte(byteIndex);
	}
	else{
		long Ret;
		TestForm::IOAccess.lock();
		Ret = DioInpByte ( PIO->BoardID , byteIndex , &InData );
		TestForm::IOAccess.unlock();
	}
	return(InData);
}

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	long Ret;
	TestForm	*PIO=(TestForm *)handle;

	TestForm::IOAccess.lock();
	Ret = DioOutByte ( PIO->BoardID , byteIndex , data );
	TestForm::IOAccess.unlock();
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	long Ret;
	BYTE InData;
	TestForm	*PIO=(TestForm *)handle;

	TestForm::IOAccess.lock();
	Ret = DioEchoBackByte ( PIO->BoardID , byteIndex , &InData );
	TestForm::IOAccess.unlock();
	return(InData);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	long Ret;
	TestForm	*PIO=(TestForm *)handle;

	TestForm::IOAccess.lock();
	Ret = DioExit ( PIO->BoardID );
	TestForm::IOAccess.unlock();
	if(Ret != 0){
		return(false);
	}
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}
