#include "XLight500.h"
#include "qextserialport.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "SettingLED500Dialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

LED500Panel::LED500Panel(LayersBase *base)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	RxData=new unsigned char[1024];
	RxByte	=0;
	RxWPoint=0;
	RxNumb	=0;
	RxCmd	=0;
	sio=NULL;

	SyncMode		=false;
	SyncForward		=0;
	SyncPulsePerBar	=100;
	SyncBackward	=0;

	CommPort		=0;
	for(int s=0;s<SheetCountInSystem;s++){
		for(int c=0;c<LEDCountInSheet;c++){
			Brightness[s][c]	=0;
		}
	}
	GradValue = 1.0;
}

LED500Panel::~LED500Panel(void)
{
	Close();
	delete	[]RxData;
	RxData=NULL;
}

bool	LED500Panel::Open(int port)
{
	CommPort=port;
	if(sio==NULL){

		int	Character=8;
		int	Parity=0;
		int	Stopbit=1;
		int	BPS	=38400;
		char *portName;
		PortSettings portSet;

		switch(CommPort){
			case 0:
				portName="COM1";
				break;
			case 1:
				portName="COM2";
				break;
			case 2:
				portName="COM3";
				break;
			case 3:
				portName="COM4";
				break;
			case 4:
				portName="COM5";
				break;
			case 5:
				portName="COM6";
				break;
			case 6:
				portName="COM7";
				break;
			case 7:
				portName="COM8";
				break;
			case 8:
				portName="COM9";
				break;
			case 9:
				portName="COM10";
				break;
            case 10:
                portName="\\\\.\\COM10";
                break;
            case 11:
                portName="\\\\.\\COM11";
                break;
            case 12:
                portName="\\\\.\\COM12";
                break;
            case 13:
                portName="\\\\.\\COM13";
                break;
            case 14:
                portName="\\\\.\\COM14";
                break;
            case 15:
                portName="\\\\.\\COM15";
                break;
            case 16:
                portName="\\\\.\\COM16";
                break;
            case 17:
                portName="\\\\.\\COM17";
                break;
            case 18:
                portName="\\\\.\\COM18";
                break;
            case 19:
                portName="\\\\.\\COM19";
                break;
            case 20:
                portName="\\\\.\\COM20";
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
bool	LED500Panel::Close(void)
{
	if(sio!=NULL){
		sio->close();
		delete	sio;
		sio=NULL;
	}
	return true;
}

void	LED500Panel::SetAll(int brightness, qreal grad)
{
	SetLeft(brightness, grad);
	SetRight(brightness, grad);
	//for(int s=0;s<SheetCountInSystem;s++){
	//	for(int c=0;c<LEDCountInSheet;c++){
	//		Brightness[s][c]	=brightness;
	//	}
	//}
}

void	LED500Panel::SetLeft(int brightness, qreal grad)
{
	int startVal = brightness;
	qreal stepVal = (grad - 1)*brightness / (SheetCountInSystem/2 - 1);

	for(int s=0; s<SheetCountInSystem/2; s++){
		for(int c=0;c<LEDCountInSheet;c++){
			Brightness[s][c]	=qBound(0, (int)(startVal + stepVal * s), 4095);
		}
	}
}

void	LED500Panel::SetRight(int brightness, qreal grad)
{
	int startVal = brightness;
	qreal stepVal = (grad - 1)*brightness / (SheetCountInSystem/2 - 1);

	for(int s=SheetCountInSystem/2; s<SheetCountInSystem; s++){
		for(int c=0;c<LEDCountInSheet;c++){
			Brightness[s][c]	=qBound(0, (int)(brightness + stepVal * (s-SheetCountInSystem/2)), 4095);
		}
	}
}

bool	LED500Panel::Save(QIODevice *f)
{
	if(::Save(f,SyncMode)==false)
		return false;
	if(::Save(f,SyncForward)==false)
		return false;
	if(::Save(f,SyncPulsePerBar)==false)
		return false;
	if(::Save(f,SyncBackward)==false)
		return false;

	if(::Save(f,CommPort)==false)
		return false;

	if(::Save(f,SheetCountInSystem)==false)
		return false;
	if(::Save(f,LEDCountInSheet)==false)
		return false;
	for(int s=0;s<SheetCountInSystem;s++){
		for(int c=0;c<LEDCountInSheet;c++){
			if(::Save(f,Brightness[s][c])==false){
				return false;
			}
		}
	}

	SaveCommon();

	return true;
}
bool	LED500Panel::Load(QIODevice *f)
{
	if(::Load(f,SyncMode)==false)
		return false;
	if(::Load(f,SyncForward)==false)
		return false;
	if(::Load(f,SyncPulsePerBar)==false)
		return false;
	if(::Load(f,SyncBackward)==false)
		return false;

	if(::Load(f,CommPort)==false)
		return false;

	int	iSheetCountInSystem;
	if(::Load(f,iSheetCountInSystem)==false)
		return false;
	int	iLEDCountInSheet;
	if(::Load(f,iLEDCountInSheet)==false)
		return false;

	int	s;
	for(s=0;s<iSheetCountInSystem && s<SheetCountInSystem;s++){
		int	c;
		for(c=0;c<iLEDCountInSheet && c<LEDCountInSheet;c++){
			if(::Load(f,Brightness[s][c])==false){
				return false;
			}
		}
		for(;c<iLEDCountInSheet;c++){
			int	dummy=0;
			if(::Load(f,dummy)==false){
				return false;
			}
		}
	}
	for(;s<iSheetCountInSystem;s++){
		for(int c=0;c<iLEDCountInSheet;c++){
			int	dummy=0;
			if(::Load(f,dummy)==false){
				return false;
			}
		}
	}

	LoadCommon();

	return true;
}

void	LED500Panel::SaveCommon()
{
	QFile file(/**/"LED500Common.dat");
	if(file.open(QIODevice::WriteOnly)==true){
		QDataStream stream(&file);
		stream << GradValue;
	}
}

void	LED500Panel::LoadCommon()
{
	QFile file(/**/"LED500Common.dat");
	if(file.open(QIODevice::ReadOnly)==true){
		QDataStream stream(&file);
		qreal val;
		stream >> val;
		if(val<0){
			val = 1.0;
		}
		GradValue = val;
	}
}

unsigned int	GetCPUMilisec(void)
{
	return GetComputerMiliSec();
}

void    Wait1ms(void)
{
    for(unsigned int t=GetCPUMilisec();GetCPUMilisec()-t<=1;);
}

void    ChangeEndian(bool src, unsigned char dest[])
{
	if(src==true){
		dest[0]=0xFF;
		dest[1]=0xFF;
	}
	else{
		dest[0]=0;
		dest[1]=0;
	}
}

void    ChangeEndian(int src, unsigned char dest[])
{
    unsigned char *p=(unsigned char *)&src;

    dest[0]=*(p+3);
    dest[1]=*(p+2);
    dest[2]=*(p+1);
    dest[3]=*(p+0);
}
void    ChangeEndian(DWORD src, unsigned char dest[])
{
    ChangeEndian((int)src, dest);
}
void    ChangeEndian(short src, unsigned char dest[])
{
    unsigned char *p=(unsigned char *)&src;

    dest[0]=*(p+1);
    dest[1]=*(p+0);
}
void    ChangeEndian(WORD src, unsigned char dest[])
{
    ChangeEndian((short)src, dest);
}

void    ChangeEndian(unsigned char src[],bool &dest)
{
	if(src[0]==0){
		dest=false;
	}
	else{
		dest=true;
	}
}
void    ChangeEndian(unsigned char src[],int &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+3)=src[0];
    *(p+2)=src[1];
    *(p+1)=src[2];
    *(p+0)=src[3];
}
void    ChangeEndian(unsigned char src[],short &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+1)=src[0];
    *(p+0)=src[1];
}

void    ChangeEndian(unsigned char src[],DWORD &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+3)=src[0];
    *(p+2)=src[1];
    *(p+1)=src[2];
    *(p+0)=src[3];
}
void    ChangeEndian(unsigned char src[],WORD &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+1)=src[0];
    *(p+0)=src[1];
}
//============================================================================
#define	WaitingMilisec		5000

bool	LED500Panel::SetOnOff(bool OnMode)
{
	if(Open(CommPort)==false)
		return false;

	unsigned char data[1024];
    ChangeEndian(OnMode		,&data[0]);

	SendTx('C' ,(char *)data, 2);

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
		}
	}

	return false;
}
bool	LED500Panel::SendSync(void)
{
	if(Open(CommPort)==false)
		return false;

	unsigned char data[1024];
    ChangeEndian(SyncMode		,&data[0]);
    ChangeEndian(SyncForward	,&data[2]);
    ChangeEndian(SyncPulsePerBar,&data[6]);
    ChangeEndian(SyncBackward	,&data[10]);

	SendTx('B' ,(char *)data, 14);

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
		}
	}

	return false;
}

bool	LED500Panel::SendBrightness(short _SheetCountInSystem,short _LEDCountInSheet)
{
	if(Open(CommPort)==false)
		return false;

	unsigned char data[1024];
    ChangeEndian(_SheetCountInSystem	,&data[0]);
    ChangeEndian(_LEDCountInSheet		,&data[2]);
    ChangeEndian(Brightness[_SheetCountInSystem][_LEDCountInSheet],&data[4]);

	SendTx('D' ,(char *)data, 8);

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
		}
	}

	return false;
}

bool	LED500Panel::SendBrightnessAllLED(short _SheetCountInSystem)
{
	if(Open(CommPort)==false)
		return false;

	unsigned char data[1024];
    ChangeEndian(_SheetCountInSystem	,&data[0]);
    ChangeEndian(Brightness[_SheetCountInSystem][0],&data[2]);

	SendTx('F' ,(char *)data, 6);

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
		}
	}

	return false;
}

bool	LED500Panel::IsSameBrightness(short _SheetCountInSystem)
{
	for(int LED=1;LED<LEDCountInSheet;LED++){
		if(Brightness[_SheetCountInSystem][0]!=Brightness[_SheetCountInSystem][LED]){
			return false;
		}
	}
	return true;
}


bool	LED500Panel::SendAllBrightness(void)
{
	if(Open(CommPort)==false)
		return false;

	for(int s=0;s<SheetCountInSystem;s++){
		if(IsSameBrightness(s)==true){
			if(SendBrightnessAllLED(s)==false){
				return false;
			}
		}
		else{
			for(int c=0;c<LEDCountInSheet;c++){
				if(SendBrightness(s,c)==false){
					return false;
				}
			}
		}
	}
	return true;
}

bool	LED500Panel::SendReflect(void)
{
	if(Open(CommPort)==false)
		return false;

	unsigned char data[1024];

	SendTx('E' ,(char *)data, 0);

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
		}
	}

	return false;
}

bool	LED500Panel::GetRx(int &Cmd ,unsigned char *data ,int buffsize)
{
	int d=GetChar();
	if(d<0)
		return false;
	if(RxNumb==0){
		if(d!='\x1b')
			return false;
		RxNumb++;
	}
	else if(RxNumb==1){
		RxByte=d;
		RxNumb++;
	}
	else if(RxNumb==2){
		RxByte|=d<<8;
		RxNumb++;
	}
	else if(RxNumb==3){
		RxCmd=d;
		RxNumb++;
		RxWPoint=0;
	}
	else{
		RxData[RxWPoint]=d;
		RxWPoint++;
		if(RxWPoint>=1024)
			RxWPoint=1023;
	}
	if(RxNumb==4){
		if(RxWPoint>=RxByte){
			Cmd=RxCmd;
            if(RxByte<buffsize)
			    memcpy(data,RxData,RxByte);
            else
                memcpy(data,RxData,buffsize);
			RxByte	=0;
			RxWPoint=0;
			RxNumb	=0;
			RxCmd	=0;
			return true;
		}
	}
	return false;
}
int		LED500Panel::GetChar(void)
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
void	LED500Panel::SendChar(unsigned char d)
{
	sio->write((char *)&d,sizeof(d));
}
void LED500Panel::SendTx(char Cmd ,char *Buff, unsigned short datalen)
{
	short	i;
    Wait1ms();
	SendChar('\x1b') ;
    Wait1ms();
	unsigned char	KSum=(unsigned char)(datalen+1);
	SendChar((char)((datalen+1))) 	;
    Wait1ms();
	KSum+=(char)((datalen+1)>>8);
	SendChar((char)((datalen+1)>>8));
    Wait1ms();
	KSum+=Cmd;
	SendChar(Cmd) ;
    Wait1ms();
	for(i=0;i<datalen;i++){
		KSum+=Buff[i];
		SendChar(Buff[i]) ;
        Wait1ms();
	}
	SendChar(KSum) ;
}


bool	LED500Panel::ShowSettingDialog(void)
{
	SettingLED500Dialog	*LightForm=new SettingLED500Dialog(GetLayersBase(),this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	return Ret;
}

	//Don't call directly

bool	LED500Panel::InitialPhysical(const QString &Param)
{
	if(Open(CommPort)==false)
		return false;
	return true;
}

bool	LED500Panel::ReflectPhysical(void)
{
	SendAllBrightness();
	return true;
}

bool	LED500Panel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}
