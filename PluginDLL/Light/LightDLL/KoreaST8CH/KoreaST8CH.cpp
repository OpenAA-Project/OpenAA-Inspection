#include "KoreaST8CH.h"

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLightDLL.h"
#include <QDir.h>
#include <QFile.h>
#include "SettingKoreaST8ChDialog.h"
#include "ThreadSequence.h"
#include "XGUIFormBase.h"
#include "qextserialport.h"
#include "XCriticalFunc.h"

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLLightMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="KoreaST8Ch";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2015.8";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Control ST-8Ch in Korea";
}

LightDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &LightParamStr,bool OutputMode)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	KoreaST8ChPanel	*H=new KoreaST8ChPanel(base,LightParamStr);
	H->Initial(OutputMode);
	return H;
}

bool		_cdecl	DLL_Close(LightDLLBaseClass *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	KoreaST8ChPanel	*H=(KoreaST8ChPanel *)handle;
	if(H!=NULL){
		H->Close();
		delete	H;
	}

	return true;
}

bool		_cdecl	DLL_Load(LightDLLBaseClass *handle ,QIODevice &str)
//	Load light attribution(setting) information of handle
//	This function must load information from stream
//	In this function, light attribution information must be set to a handle
//	if process fails, it returns false
{
	KoreaST8ChPanel	*p=static_cast<KoreaST8ChPanel *>(handle);
	bool	Ret=p->Load(&str);
	if(Ret==true){
		p->Transfer(0,NULL);
	}
	return Ret;
}

bool		_cdecl	DLL_Save(LightDLLBaseClass *handle ,QIODevice &str)
//	Save light attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	KoreaST8ChPanel	*p=static_cast<KoreaST8ChPanel *>(handle);
	return p->Save(&str);
}

bool		_cdecl	DLL_ShowSetting(LightDLLBaseClass *handle, QWidget *parent)
//	This function shows dialog to set light(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Lighting pattern(Which light is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	KoreaST8ChPanel	*p=static_cast<KoreaST8ChPanel *>(handle);
	SettingKoreaST8ChDialog	*LightForm=new SettingKoreaST8ChDialog(p);
	bool	Ret=LightForm->exec();
	delete LightForm;

	return Ret;
}

int		_cdecl	DLL_GetLightPatternCount(LightDLLBaseClass *handle)
//	This function must return Pattern-Count on handle
{
	return 1;
}

bool		_cdecl	DLL_LightOn(LightDLLBaseClass *handle)
//	Turn on handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	KoreaST8ChPanel	*p=static_cast<KoreaST8ChPanel *>(handle);
	p->SetOnOff(true);
	return true;
}

bool		_cdecl	DLL_LightOff(LightDLLBaseClass *handle)
//	Turn off handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	KoreaST8ChPanel	*p=static_cast<KoreaST8ChPanel *>(handle);
	p->SetOnOff(false);
	return true;
}

bool		_cdecl	DLL_SetPattern(LightDLLBaseClass *handle ,int PatternNo)
//	This function set Light-pattern
//	This function must return as soon as possible
//	If LightOff was set before this function, Light must be enlightened with this pattern when LightOn function is called
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	return true;
}

bool		_cdecl	DLL_ReqLightError(LightDLLBaseClass *handle ,QStringList &Msg)
//	Request light error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false
{
	return true;
}

//=================================================================================================

KoreaST8ChPanel::KoreaST8ChPanel(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	sio=NULL;
	bool	ok;
	CommPort	=LightParamStr.toInt(&ok);
	if(ok==false){
		CommPort=0;
	}
	CountOfLED=MaxCountOfLED;
	for(int i=0;i<MaxCountOfLED;i++){
		ChannelDim[i].LightValue	=0;
		ChannelDim[i].OnOff			=false;
	}
}	

bool	KoreaST8ChPanel::Initial(bool OutputMode)
{
	if(OutputMode==false)
		return false;

	if(sio==NULL){
		int	Character=8;
		int	Parity=0;
		int	Stopbit=1;
		int	BPS	=19200;
		char *portName;
		PortSettings portSet;

		switch(CommPort){
			case 0:
				portName="COM1";
				break;
			case 1:
				portName="COM1";
				break;
			case 2:
				portName="COM2";
				break;
			case 3:
				portName="COM3";
				break;
			case 4:
				portName="COM4";
				break;
			case 5:
				portName="COM5";
				break;
			case 6:
				portName="COM6";
				break;
			case 7:
				portName="COM7";
				break;
			case 8:
				portName="COM8";
				break;
			case 9:
				portName="COM9";
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
		portSet.Timeout_Sec=1;
		portSet.Timeout_Millisec=0;
		sio=new QextSerialPort((const char*)portName,*((PortSettings const *)&portSet));
		sio->setDtr(true);
		sio->setRts(true);

		sio->open(QIODevice::ReadWrite);
		Opened=true;
	}
	return true;
}

bool	KoreaST8ChPanel::Close(void)
{
	if(sio!=NULL){
		sio->close();
		delete	sio;
		sio=NULL;
	}
	return true;
}


KoreaST8ChPanel::~KoreaST8ChPanel(void)
{
}

bool	KoreaST8ChPanel::Save(QIODevice *f)
{
	for(int i=0;i<MaxCountOfLED;i++){
		if(::Save(f,ChannelDim[i].LightValue)==false){
			return false;
		}
		if(::Save(f,ChannelDim[i].OnOff)==false){
			return false;
		}
	}
	return true;
}
bool	KoreaST8ChPanel::Load(QIODevice *f)
{
	for(int i=0;i<MaxCountOfLED;i++){
		if(::Load(f,ChannelDim[i].LightValue)==false){
			return false;
		}
		if(::Load(f,ChannelDim[i].OnOff)==false){
			return false;
		}
	}

	for(int i=0;i<MaxCountOfLED;i++){
		Transfer(i,NULL);
	}

	return true;
}


bool	KoreaST8ChPanel::SetOnOff(int number ,bool d)
{
	if(0<=number && number<CountOfLED){
		ChannelDim[number].OnOff=d;
		return Transfer(number,NULL);
	}
	return true;
}
bool	KoreaST8ChPanel::SetOnOff(bool __OnMode)
{
	for(int i=0;i<CountOfLED;i++){
		SetOnOff(i,__OnMode);
	}
	return true;
}

bool	KoreaST8ChPanel::SetValue(int number ,BYTE data,bool OnOff)
{
	if(0<=number && number<CountOfLED){
		ChannelDim[number].OnOff		=OnOff;
		ChannelDim[number].LightValue	=data;
		return Transfer(number,NULL);
	}
	return true;
}

bool	KoreaST8ChPanel::Transfer(int Ch ,QProgressBar *Bar)
{
	BYTE	TxBuff[6];
	int		WaitingMilisec=100;
	BYTE	RxBuff[6];

	TxBuff[0]=0x95;
	TxBuff[1]=0x02;
	TxBuff[2]=Ch+1;
	TxBuff[3]=(ChannelDim[Ch].OnOff==true)?1:0;
	TxBuff[4]=ChannelDim[Ch].LightValue;
	TxBuff[5]=TxBuff[0]+TxBuff[1]+TxBuff[2]+TxBuff[3]+TxBuff[4];
	if(sio!=NULL && Opened==true){
		if(sio->write((char *)TxBuff,6)!=6){
			return false;
		}
		sio->flush();
		return true;
		int	RxLen=0;
		for(int i=0;i<6;i++){
			for(DWORD d=GetComputerMiliSec();GetComputerMiliSec()-d<WaitingMilisec;){
				int	c=GetChar();
				if(c>=0){
					RxBuff[RxLen]=c;
					RxLen++;
					break;
				}
			}
		}
		if(RxLen==6){
			return true;
		}
	}
	return false;
}

int		KoreaST8ChPanel::GetChar(void)
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


void	KoreaST8ChPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLightSetValue	*CmdLightSetValueVar=dynamic_cast<CmdLightSetValue *>(packet);
	if(CmdLightSetValueVar!=NULL){
		ChannelDim[CmdLightSetValueVar->Number].LightValue	=CmdLightSetValueVar->Value;
		ChannelDim[CmdLightSetValueVar->Number].OnOff		=CmdLightSetValueVar->OnMode;
		Transfer(CmdLightSetValueVar->Number,NULL);
		return;
	}
	CmdLightSetOnOff	*CmdLightSetOnOffVar=dynamic_cast<CmdLightSetOnOff *>(packet);
	if(CmdLightSetOnOffVar!=NULL){
		SetOnOff(CmdLightSetOnOffVar->Number,CmdLightSetOnOffVar->OnMode);
		return;
	}
	CmdLightReqData		*CmdLightReqDataVar=dynamic_cast<CmdLightReqData *>(packet);
	if(CmdLightReqDataVar!=NULL){
		CmdLightReqDataVar->OnMode	=ChannelDim[CmdLightReqDataVar->Number].OnOff;
		CmdLightReqDataVar->Value	=ChannelDim[CmdLightReqDataVar->Number].LightValue;
		return;
	}
}


bool	KoreaST8ChPanel::ShowSettingDialog(void)	
{
	return true;
}
	//Don't call directly
bool	KoreaST8ChPanel::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}
bool	KoreaST8ChPanel::ReflectPhysical(void)		
{
	Transfer(0,NULL);
	return true;
}
bool	KoreaST8ChPanel::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}

