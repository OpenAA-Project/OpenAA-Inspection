#include "XCCSControl.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

LightCCSControl::LightCCSControl(LayersBase *base ,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	Commander=HidCommand::Create((QWidget *)this);

	Opened=false;
	Param=LightParamStr;
	CurrentPattern	=0;
	InData	=0;

	for(int t=0;t<sizeof(Brightness)/sizeof(Brightness[0]);t++){
		Brightness[t]	=0;
		OnMode[t]		=true;
	}
	int	Number=0;
	if(LightParamStr.isNull()==false){
		Number=LightParamStr.toInt();
	}
	if(Commander->OpenHid(0x1255, 0x0001,Number)==true){
		if(Commander->IsOpened()==true){
			Commander->SendStr((BYTE *)"V",1);
			BYTE	RecData[256];
			int		ReceivedLen;
			GSleep(100);
			if(Commander->ReceiveStr(RecData,ReceivedLen)==true){
				VersionStr=((char *)RecData);
			}
		}
	}
	SendInt(true);
	//SendExtOut(true);
}

LightCCSControl::~LightCCSControl(void)
{
	delete	Commander;
}

bool	LightCCSControl::Save(QIODevice *f)
{
	int32	N=sizeof(Brightness)/sizeof(Brightness[0]);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(::Save(f,Brightness[i])==false){
			return false;
		}
		if(::Save(f,OnMode[i])==false){
			return false;
		}
	}
	return true;
}
bool	LightCCSControl::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N && i<sizeof(Brightness)/sizeof(Brightness[0]);i++){
		if(::Load(f,Brightness[i])==false){
			return false;
		}
		if(::Load(f,OnMode[i])==false){
			return false;
		}
	}
	Transfer(0,NULL);
	SendOnOff(OnMode[0]);

	return true;
}


bool	LightCCSControl::SetOnOff(bool d)
{
	SendOnOff(d);
	OnMode[0]=d;
	SendON2(d);
	OnMode[1]=d;

	return true;
}


void	LightCCSControl::Transfer(int PatternNumber ,QProgressBar *Bar)
{
	SendWR(1);
	SendCH(0);
	SendOutData(Brightness[0]);
	SendWR(0);
	GSleep(10);
	SendWR(1);

}

bool	LightCCSControl::SendOutData(int n)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='D';
		TxBuff[1]=n;
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
	return true;
}
	
bool	LightCCSControl::SendInt(bool n)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='I';
		TxBuff[1]=(n==true)?'1':'0';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
	return true;
}

bool	LightCCSControl::SendWR(bool n)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='W';
		TxBuff[1]=(n==true)?'1':'0';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
	return true;
}

bool	LightCCSControl::SendOnOff(bool onMode)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='F';
		TxBuff[1]=(onMode==true)?'1':'0';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				OnMode[0]=onMode;
				break;
			}
		}
	}
	return true;
}

bool	LightCCSControl::SendCH(int n)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='H';
		TxBuff[1]=(n==true)?'1':'0';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
	return true;
}

bool	LightCCSControl::SendON2(bool n)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='2';
		TxBuff[1]=(n==true)?'1':'0';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				OnMode[1]=n;
				break;
			}
		}
	}
	return true;
}

bool	LightCCSControl::SendExtOut(bool n)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='E';
		TxBuff[1]=(n==true)?'1':'0';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]==0x0a){
				break;
			}
		}
	}
	return true;
}

void	LightCCSControl::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLightSetValue	*CmdLightSetValueVar=dynamic_cast<CmdLightSetValue *>(packet);
	if(CmdLightSetValueVar!=NULL){
		Brightness[0]=CmdLightSetValueVar->Value;
		Transfer(0,NULL);
		return;
	}
	CmdLightSetOnOff	*CmdLightSetOnOffVar=dynamic_cast<CmdLightSetOnOff *>(packet);
	if(CmdLightSetOnOffVar!=NULL){
		SendOnOff(CmdLightSetOnOffVar->OnMode);
		return;
	}
	CmdLightReqData		*CmdLightReqDataVar=dynamic_cast<CmdLightReqData *>(packet);
	if(CmdLightReqDataVar!=NULL){
		CmdLightReqDataVar->OnMode=OnMode[0];
		CmdLightReqDataVar->Value=Brightness[0];
		return;
	}
	CmdReqInput	*CmdReqInputVar=dynamic_cast<CmdReqInput *>(packet);
	if(CmdReqInputVar!=NULL){
		CmdReqInputVar->Data=InData;
		return;
	}
}

void	LightCCSControl::LoopOnIdle(void)
{
	BYTE	TxBuff[64];
	BYTE	RecData[256];
	int		ReceivedLen;

	if(Commander->IsOpened()==true){
		TxBuff[0]='G';
		Commander->SendStr(TxBuff,64);
		for(int i=0;i<10;i++){
			GSleep(100);
			Commander->ReceiveStr(RecData,ReceivedLen);
			if(RecData[0]=='g'){
				InData	=RecData[1];
				break;
			}
		}
	}
}
bool	LightCCSControl::ShowSettingDialog(void)
{
	SettingDialog	*LightForm=new SettingDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	return Ret;
}

	//Don't call directly
bool	LightCCSControl::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}
bool	LightCCSControl::ReflectPhysical(void)
{
	Transfer(0,NULL);
	return true;
}
bool	LightCCSControl::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}
