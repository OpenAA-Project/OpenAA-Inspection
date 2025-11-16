#include "XCCSControl2.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

LightCCSControl2::LightCCSControl2(LayersBase *base ,const QString &LightParamStr)
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

LightCCSControl2::~LightCCSControl2(void)
{
	delete	Commander;
}

bool	LightCCSControl2::Save(QIODevice *f)
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
bool	LightCCSControl2::Load(QIODevice *f)
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


bool	LightCCSControl2::SetOnOff(bool d)
{
	SendOnOff(d);
	SendON2(d);

	return true;
}

bool	LightCCSControl2::SetOnOff(int number ,bool d)
{
	if(number==0)
		SendOnOff(d);
	else if(number==1)
		SendON2(d);

	return true;
}

void	LightCCSControl2::Transfer(int PatternNumber ,QProgressBar *Bar)
{
	Transfer1(PatternNumber ,Bar);
	Transfer2(PatternNumber ,Bar);
}


void	LightCCSControl2::Transfer1(int PatternNumber ,QProgressBar *Bar)
{
	SendWR(1);
	SendCH(0);
	SendOutData(Brightness[0]);
	SendWR(0);
	GSleep(10);
	SendWR(1);
}

void	LightCCSControl2::Transfer2(int PatternNumber ,QProgressBar *Bar)
{
	SendWR(1);
	SendCH(1);
	SendOutData(Brightness[1]);
	SendWR(0);
	GSleep(10);
	SendWR(1);
}

bool	LightCCSControl2::SendOutData(int n)
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
	
bool	LightCCSControl2::SendInt(bool n)
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

bool	LightCCSControl2::SendWR(bool n)
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

bool	LightCCSControl2::SendOnOff(bool onMode)
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

bool	LightCCSControl2::SendCH(int n)
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

bool	LightCCSControl2::SendON2(bool n)
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

bool	LightCCSControl2::SendExtOut(bool n)
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

void	LightCCSControl2::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLightSetValue1	*CmdLightSetValue1Var=dynamic_cast<CmdLightSetValue1 *>(packet);
	if(CmdLightSetValue1Var!=NULL){
		Brightness[0]=CmdLightSetValue1Var->Value1;
		Transfer1(0,NULL);
		return;
	}
	CmdLightSetValue2	*CmdLightSetValue2Var=dynamic_cast<CmdLightSetValue2 *>(packet);
	if(CmdLightSetValue2Var!=NULL){
		Brightness[1]=CmdLightSetValue2Var->Value2;
		Transfer2(0,NULL);
		return;
	}
	CmdLightSetOnOff	*CmdLightSetOnOffVar=dynamic_cast<CmdLightSetOnOff *>(packet);
	if(CmdLightSetOnOffVar!=NULL){
		SendOnOff(CmdLightSetOnOffVar->OnMode1);
		SendON2  (CmdLightSetOnOffVar->OnMode2);
		return;
	}
	CmdLightReqData		*CmdLightReqDataVar=dynamic_cast<CmdLightReqData *>(packet);
	if(CmdLightReqDataVar!=NULL){
		CmdLightReqDataVar->OnMode1=OnMode[0];
		CmdLightReqDataVar->OnMode2=OnMode[1];
		CmdLightReqDataVar->Value1=Brightness[0];
		CmdLightReqDataVar->Value2=Brightness[1];
		return;
	}
	CmdReqInput	*CmdReqInputVar=dynamic_cast<CmdReqInput *>(packet);
	if(CmdReqInputVar!=NULL){
		CmdReqInputVar->Data=InData;
		return;
	}
}

void	LightCCSControl2::LoopOnIdle(void)
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

bool	LightCCSControl2::ShowSettingDialog(void)
{
	SettingDialog	*LightForm=new SettingDialog(this);
	bool	Ret=LightForm->exec();
	delete LightForm;
	return Ret;
}

	//Don't call directly
bool	LightCCSControl2::InitialPhysical(const QString &Param)
{
	Initial(true);
	return true;
}
bool	LightCCSControl2::ReflectPhysical(void)
{
	Transfer(0,NULL);
	return true;
}
bool	LightCCSControl2::ReflectPhysicalTurnOn(bool LightOn)
{
	SetOnOff(LightOn);
	return true;
}
