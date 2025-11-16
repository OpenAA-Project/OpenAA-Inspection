#include "LightBowl240RGBW.h"
#include "XGeneralFunc.h"
#include "SettingLightBowl240RGBDialog.h"



ParamLightInfo	&ParamLightInfo::operator=(const ParamLightInfo &src)
{
	PatternName	=src.PatternName;
	ParamLight::operator=(src);
	return *this;
}

bool    ParamLightInfo::SaveInfo(QIODevice *f)
{
	int	Ver=1;
	if(::Save(f,Ver)==false)	return false;
	if(::Save(f,PatternName)==false)	return false;
	if(ParamLight::Save(f)==false)		return false;
	return true;
}

bool    ParamLightInfo::LoadInfo(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Ver)==false)	return false;
	if(::Load(f,PatternName)==false)	return false;
	if(ParamLight::Load(f)==false)		return false;
	return true;
}


//============================================================================
LightBowl240RGBW::LightBowl240RGBW(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	IPAddress	=/**/"192.168.0.100";
	CountOfLightDataDim=0;
	CurrentIndex		=0;
}

LightBowl240RGBW::~LightBowl240RGBW(void)
{
	Close();
}

bool	LightBowl240RGBW::Open(void)
{
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		Sock.connectToHost(IPAddress,RobotPI_Port);
		Sock.waitForConnected(WaitingMilisecForConnection);
	}
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		if(Sock.isOpen()==false){
			Sock.open(QIODevice::ReadWrite);
		}
		if(Sock.state()!=QAbstractSocket::ConnectedState){
			Sock.connectToHost(IPAddress,RobotPI_Port);
			Sock.waitForConnected(WaitingMilisecForConnection);
		}
		if(Sock.state()!=QAbstractSocket::ConnectedState){
			return false;
		}
	}
	return true;
}

bool	LightBowl240RGBW::Initial(void)
{
	if(Open()==false){
		return false;
	}
	if(Transfer(LightDataDim[CurrentIndex],ONMode)==false)
		return false;
	return true;
}

bool	LightBowl240RGBW::Close(void)
{
	if(Sock.state()==QAbstractSocket::ConnectedState){
		Sock.disconnectFromHost();
		if(Sock.waitForDisconnected()==false){
			return false;
		}
	}
	Sock.close();
	return true;
}

bool	LightBowl240RGBW::SetON(bool ON)
{
	if(Open()==false){
		return false;
	}
	ONMode=ON;
	Transfer(LightDataDim[CurrentIndex],ONMode);

	return true;
}

bool	LightBowl240RGBW::Transfer(ParamLightInfo &Ptn ,bool _OnMode)
{
	if(Open()==false){
		return false;
	}
	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);

	::Save(&Buff,_OnMode);
	Ptn.ParamLight::Save(&Buff);
	QByteArray	Data=Buff.buffer();

	Sock.write(Data);
	Sock.flush();
	return true;
}

bool	LightBowl240RGBW::Save(QIODevice *f)
{
	if(::Save(f,CountOfLightDataDim)==false)	return false;
	for(int i=0;i<CountOfLightDataDim && i<MaxDimCountLightBowl240RGBW;i++){
		if(LightDataDim[i].SaveInfo(f)==false)		return false;
	}
	if(::Save(f,ONMode)==false)			return false;
	if(::Save(f,CurrentIndex)==false)	return false;

	return true;
}

bool	LightBowl240RGBW::Load(QIODevice *f)
{
	if(::Load(f,CountOfLightDataDim)==false)	return false;
	for(int i=0;i<CountOfLightDataDim && i<MaxDimCountLightBowl240RGBW;i++){
		if(LightDataDim[i].LoadInfo(f)==false)		return false;
	}
	if(::Load(f,ONMode)==false)			return false;
	if(::Load(f,CurrentIndex)==false)	return false;


	return true;
}

void	LightBowl240RGBW::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool	LightBowl240RGBW::ShowSettingDialog(void)
{
	SettingLightBowl240RGBDialog	D(this,GetLayersBase());
	D.SetInitial(this);
	if(D.exec()==(int)true){
		for(int i=0;i<MaxDimCountLightBowl240RGBW;i++){
		    LightDataDim[i]=D.LightDataDim[i];
		}
		CountOfLightDataDim =D.CountOfLightDataDim;
		CurrentIndex		=D.CurrentDimRow;
		IPAddress			=D.IPAddress;
		return true;
	}
	return false;
}

bool	LightBowl240RGBW::InitialPhysical(const QString &Param)
{
	return true;
}

bool	LightBowl240RGBW::ReflectPhysical(void)
{
	if(Open()==false){
		return false;
	}

	Transfer(LightDataDim[CurrentIndex],ONMode);

	return true;
}

bool	LightBowl240RGBW::ReflectPhysicalTurnOn(bool LightOn)
{
	if(SetON(LightOn)==false)
		return false;

	return true;
}