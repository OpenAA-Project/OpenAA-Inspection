#include "AutofocusControlResource.h"
#include "XAutofocusControl.h"
#include "qextserialport.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

AFControl::AFControl(void)
{
	CommPort	=0;
	sio			=0;
}

bool	AFControl::OpenPort(int port)
{
	CommPort	=port;

	if(sio==NULL){
		int	Character=8;
		int	Parity=0;
		int	Stopbit=2;
		int	BPS	=19200;
		char *portName;
		PortSettings portSet;

		switch(CommPort){
			case 0:
				portName=/**/"COM1";
				break;
			case 1:
				portName=/**/"COM1";
				break;
			case 2:
				portName=/**/"COM2";
				break;
			case 3:
				portName=/**/"COM3";
				break;
			case 4:
				portName=/**/"COM4";
				break;
			case 5:
				portName=/**/"COM5";
				break;
			case 6:
				portName=/**/"COM6";
				break;
			case 7:
				portName=/**/"COM7";
				break;
			case 8:
				portName=/**/"COM8";
				break;
			case 9:
				portName=/**/"COM9";
				break;
			case 10:
				portName=/**/"\\\\.\\COM10";
				break;
		}
		switch(Character){
			case 5:
				portSet.DataBits=DATA_5;
				break;
			case 6:
				portSet.DataBits=DATA_6;
				break;
			case 7:
				portSet.DataBits=DATA_7;
				break;
			case 8:
				portSet.DataBits=DATA_8;
				break;
		}
		switch(Parity){
			case 0:
				portSet.Parity=PAR_NONE;
				break;
			case 1:
				portSet.Parity=PAR_ODD;
				break;
			case 2:
				portSet.Parity=PAR_EVEN;
				break;
		}
		switch(Stopbit){
			case 1:
				portSet.StopBits=STOP_1;
				break;
			case 2:
				portSet.StopBits=STOP_2;
				break;
			case 3:
				portSet.StopBits=STOP_1_5;
				break;
		}
		switch(BPS){
			case 110:
				portSet.BaudRate=BAUD110;
				break;
			case 300:
				portSet.BaudRate=BAUD300;
				break;
			case 600:
				portSet.BaudRate=BAUD600;
				break;
			case 1200:
				portSet.BaudRate=BAUD1200;
				break;
			case 2400:
				portSet.BaudRate=BAUD2400;
				break;
			case 4800:
				portSet.BaudRate=BAUD4800;
				break;
			case 9600:
				portSet.BaudRate=BAUD9600;
				break;
			case 14400:
				portSet.BaudRate=BAUD14400;
				break;
			case 19200:
				portSet.BaudRate=BAUD19200;
				break;
			case 38400:
				portSet.BaudRate=BAUD38400;
				break;
			case 56000:
				portSet.BaudRate=BAUD56000;
				break;
			case 57600:
				portSet.BaudRate=BAUD57600;
				break;
			case 115200:
				portSet.BaudRate=BAUD115200;
				break;
		}
		portSet.FlowControl=FLOW_OFF;
		portSet.Timeout_Sec=0;
		portSet.Timeout_Millisec=1;
		sio=new QextSerialPort((const char*)portName,*((PortSettings const *)&portSet));
		sio->setDtr(true);
		sio->setRts(true);

		sio->open(QIODevice::ReadWrite);
	}
	return true;
}
bool	AFControl::ClosePort(void)
{
	if(sio!=NULL){
		sio->close();
		delete	sio;
		sio=NULL;
	}
	return true;
}
bool	AFControl::IsOpened(void)
{
	if(sio!=NULL){
		return true;
	}
	return false;
}

bool	AFControl::GoAutofocus(void)
{
	char	buff[200];
	ReTryQ:;
	SendStr(/**/"Q\x0d");
	do{
		if(GetStr(buff ,sizeof(buff))==false)
			goto	ReTryQ;
	}while(buff[0]!='K');

	GSleep(100);
	do{
		SendStr(/**/"SC0\x0d");
	}while(GetStr(buff ,sizeof(buff))==false);
	return true;
}

int		AFControl::GetCurrentZ(void)
{
	char	buff[200];
	ReTryQ:;
	SendStr(/**/"Q\x0d");
	do{
		if(GetStr(buff ,sizeof(buff))==false)
			goto	ReTryQ;
	}while(buff[0]!='K');
	GSleep(100);
	do{
		SendStr(/**/"DP\x0d");
	}while(GetStr(buff ,sizeof(buff))==false);

	QString	s=buff;
	bool	ok;
	int	d=s.toInt(&ok);
	if(ok==true){
		return d;
	}
	return 0;
}

bool	AFControl::ChangeNumber(char number)
{
	char	buff[200];
ReTryQ1:;
	SendStr(/**/"Q\x0d");
	do{
		if(GetStr(buff ,sizeof(buff))==false)
			goto	ReTryQ1;
	}while(buff[0]!='K');

	GSleep(100);

	ReTryQ:;
	if(number=='A'){
		SendStr(/**/"XA\x0d");
	}
	else if(number=='B'){
		SendStr(/**/"XB\x0d");
	}
	else if(number=='C'){
		SendStr(/**/"XC\x0d");
	}
	else if(number=='D'){
		SendStr(/**/"XD\x0d");
	}
	do{
		if(GetStr(buff ,sizeof(buff))==false)
			goto	ReTryQ;
	}while(buff[0]!='K');
	GSleep(100);
	return true;
}


int		AFControl::GetChar(void)
{
		char	buff[1];
	if(sio!=NULL && sio->bytesAvailable()>0){
		sio->read(buff,1);
		return (unsigned char)buff[0];
	}
	else{
		return -1;
	}
}
void	AFControl::SendChar(unsigned char d)
{
	if(sio!=NULL){
		sio->write((char *)&d,sizeof(d));
	}
}

	
bool	AFControl::SendStr(char *s)
{
	while(*s!=0){
		SendChar(*s);
		s++;
	}
	return true;
}

bool	AFControl::GetStr(char buff[] ,int maxlen)
{
	int	L=0;
	QElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<5000){
		int	c=GetChar();
		if(c>=0){
			buff[L]=c;
			L++;
			if(L>=maxlen){
				return true;
			}
			if(c=='\x0a'){
				if(buff[L-2]=='\x0d')
					buff[L-2]=0;
				else
					buff[L-1]=0;
				return true;
			}
		}
	}
	return false;
}

