#include "RelayLCUS2.h"

#include <QWidget>
#include <QString>
#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include <QThread>

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="RelayLCUS2";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "Relay 2 port LCUS2";
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
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	return(2);
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;

	RelayLCUS2	*H=new RelayLCUS2;
	QString COM="COM"+QString::number(H->ComPort);
	if(Something.isEmpty()==false)
		COM=Something;

	H->port = new QSerialPort(mainW);
	H->port->setPortName(COM);

	H->port->setBaudRate(9600);
	H->port->setFlowControl(QSerialPort::NoFlowControl);
	H->port->setParity	(QSerialPort::NoParity);
	H->port->setDataBits(QSerialPort::Data8);
	H->port->setStopBits(QSerialPort::OneAndHalfStop);
	if(H->port->open(QIODevice::ReadWrite)==false){
		QMessageBox::warning(NULL,"Error","can not open Com");
	}


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
class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}

//==
void	RelayLCUS2::Push(char *fp)
{
	for(int i=0;i<4;i++){
		port->write(&fp[i],1);
		GSleep(1);
	}
}

void  _cdecl AIP_IO_SetBit(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data)
{
	RelayLCUS2	*H=(RelayLCUS2 *)handle;
	DWORD	BytesWriten;

	int	DataNumb=4;
	if(bitIndex==0 && data==0){
		char	*fp="\xa0\x01\x01\xa2\r\n";
		H->Push(fp);
		H->port->flush();
	}
	if(bitIndex==0 && data==1){
		char	*fp="\xa0\x01\x00\xa1\r\n";
		H->Push(fp);
		H->port->flush();
	}
	if(bitIndex==1 && data==0){
		char	*fp="\xa0\x02\x01\xa3\r\n";
		H->Push(fp);
		H->port->flush();
	}
	if(bitIndex==1 && data==1){
		char	*fp="\xa0\x02\x00\xa2\r\n";
		H->Push(fp);
		H->port->flush();
	}
}


int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	return(0);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	RelayLCUS2	*H=(RelayLCUS2 *)handle;

	H->port->close();
	return false;
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}
