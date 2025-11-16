#include "ImacControlByLAN.h"
#include "XGeneralFunc.h"
#include <string.h>
#include "SettingDialog.h"

#define	WaitingMilisecForConnection	3000


ImacControlByLANParam::ChannelInfo::ChannelInfo(void)
{
	Power	=0;
	Mode	=0;
	Delay		=0;
	OutputTime	=1;
}
ImacControlByLANParam::ChannelInfo	&ImacControlByLANParam::ChannelInfo::operator=(ImacControlByLANParam::ChannelInfo &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	ImacControlByLANParam::ChannelInfo::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Power)==false)
		return false;
	if(::Save(f,Mode)==false)
		return false;
	if(::Save(f,Delay)==false)
		return false;
	if(::Save(f,OutputTime)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	return true;
}
bool	ImacControlByLANParam::ChannelInfo::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Power)==false)
		return false;
	if(::Load(f,Mode)==false)
		return false;
	if(::Load(f,Delay)==false)
		return false;
	if(::Load(f,OutputTime)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	return true;
}

ImacControlByLANParam::ImacControlByLANParam(void)
{
	IPAddress			=/**/"192.168.0.30";
	Port				=1000;
	SubnetMask			=/**/"255.255.255.0";
	DefaultGateway		=/**/"192.168.0.1";
}

ImacControlByLANParam	&ImacControlByLANParam::operator=(ImacControlByLANParam &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	ImacControlByLANParam::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,Port)==false)
		return false;
	if(::Save(f,SubnetMask)==false)
		return false;
	if(::Save(f,DefaultGateway)==false)
		return false;

	for(int i=0;i<8;i++){
		if(ChannelInfoData[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	ImacControlByLANParam::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,Port)==false)
		return false;
	if(::Load(f,SubnetMask)==false)
		return false;
	if(::Load(f,DefaultGateway)==false)
		return false;

	for(int i=0;i<8;i++){
		if(ChannelInfoData[i].Load(f)==false)
			return false;
	}
	return true;
}

//============================================================================
ImacControlByLAN::ImacControlByLAN(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	if(LightParamStr.isEmpty()==false)
		Data.IPAddress=LightParamStr;
}

ImacControlByLAN::~ImacControlByLAN(void)
{
	Close();
}


bool	ImacControlByLAN::ReadLine(char *Text,int Len)
{
	Text[0]=0;
	int	RxLen=0;
	while(RxLen<Len){
		int	i;
		for(i=0;Sock.bytesAvailable ()==0 && i<1000;i++){
			Sock.waitForReadyRead(1);
		}
		if(i>=1000){
			return false;
		}
		char	Str[1000];
		int	n=Sock.read(Str,1000);
		Str[n]=0;
		strcat(Text,Str);
		RxLen+=n;
	}
	return true;
}

bool	ImacControlByLAN::Open(void)
{
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		Sock.connectToHost(Data.IPAddress,Data.Port);
		Sock.waitForConnected(WaitingMilisecForConnection);
	}
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		if(Sock.isOpen()==false){
			Sock.open(QIODevice::ReadWrite);
		}
		if(Sock.state()!=QAbstractSocket::ConnectedState){
			Sock.connectToHost(Data.IPAddress,Data.Port);
			Sock.waitForConnected(WaitingMilisecForConnection);
		}
		if(Sock.state()!=QAbstractSocket::ConnectedState){
			return false;
		}
	}
	return true;
}

bool	ImacControlByLAN::Initial(void)
{
	if(Open()==false){
		return false;
	}
	if(Transfer(0,NULL)==false)
		return false;
	return true;
}

bool	ImacControlByLAN::Close(void)
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

bool	ImacControlByLAN::SetON(bool ON)
{
	if(Open()==false){
		return false;
	}
	char	Text[200];

	for(int i=0;i<8 && i<ChannelCount;i++){
		sprintf(Text,"W11%02d" "%04d",(i+1),(ON==true)?Data.ChannelInfoData[i].Power:0);
		int	Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		ReadLine(Text,7);
	}
	return true;
}

int	GetValue4(char *Text)
{
	int	n=(Text[0]-'0')*1000+(Text[1]-'0')*100+(Text[2]-'0')*10+(Text[3]-'0');
	return n;
}

bool	ImacControlByLAN::Transfer(int PatternNumber,QProgressBar *Bar)
{
	if(Open()==false){
		return false;
	}
	char	Text[200];
	int		Len;
	
	strcpy(Text,/**/"R260000");
	Len=strlen(Text);
	Sock.write(Text,Len);
	if(ReadLine(Text,7)==false)
		return false;
	ChannelCount=GetValue4(&Text[3]);

	strcpy(Text,/**/"R110000");
	Len=strlen(Text);
	Sock.write(Text,Len);
	Sock.flush();
	if(ReadLine(Text,3+6*ChannelCount)==false)
		return false;
	int	Power[256];
	for(int i=0;i<8 && i<ChannelCount;i++){
		Power[i]=GetValue4(&Text[5+6*i]);
	}
	for(int i=0;i<8 && i<ChannelCount;i++){
		if(Data.ChannelInfoData[i].Power!=Power[i]){
			sprintf(Text,"W11%02d" "%04d",(i+1),Data.ChannelInfoData[i].Power);
			Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text,7)==false)
				return false;
		}
	}

	strcpy(Text,/**/"R090000");
	Len=strlen(Text);
	Sock.write(Text,Len);
	Sock.flush();
	if(ReadLine(Text,3+6*ChannelCount)==false)
		return false;
	int	Mode[256];
	for(int i=0;i<8 && i<ChannelCount;i++){
		Mode[i]=GetValue4(&Text[5+6*i]);
	}
	for(int i=0;i<8 && i<ChannelCount;i++){
		if(Data.ChannelInfoData[i].Mode!=Mode[i]){
			sprintf(Text,"W11%02d" "%04d",(i+1),Data.ChannelInfoData[i].Mode);
			int	Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text,7)==false)
				return false;
		}
	}

	strcpy(Text,/**/"R130000");
	Len=strlen(Text);
	Sock.write(Text,Len);
	Sock.flush();
	if(ReadLine(Text,3+6*ChannelCount)==false)
		return false;
	int	Delay[256];
	for(int i=0;i<8 && i<ChannelCount;i++){
		Delay[i]=GetValue4(&Text[5+6*i]);
	}
	for(int i=0;i<8 && i<ChannelCount;i++){
		if(Data.ChannelInfoData[i].Delay!=Delay[i]){
			sprintf(Text,"W13%02d" "%04d",(i+1),Data.ChannelInfoData[i].Delay);
			int	Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text,7)==false)
				return false;
		}
	}

	strcpy(Text,/**/"R180000");
	Len=strlen(Text);
	Sock.write(Text,Len);
	Sock.flush();
	if(ReadLine(Text,3+6*ChannelCount)==false)
		return false;
	int	OutputTime[256];
	for(int i=0;i<8 && i<ChannelCount;i++){
		OutputTime[i]=GetValue4(&Text[5+6*i]);
	}
	for(int i=0;i<8 && i<ChannelCount;i++){
		if(Data.ChannelInfoData[i].OutputTime!=OutputTime[i]){
			sprintf(Text,"W18%02d" "%04d",(i+1),Data.ChannelInfoData[i].OutputTime);
			int	Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text,7)==false)
				return false;
		}
	}
	return true;
}

void	ImacControlByLAN::SetIPAddress(ImacControlByLANParam &data)
{
	if(Open()==false){
		return;
	}
	char	Text[200];

	if(Data.IPAddress!=data.IPAddress){
		strcpy(Text,"W20");
		char	*fp=strchr(Text,0);
		QString2Char(data.IPAddress ,fp,100);
		int	Len=strlen(Text);
		ReadLine(Text,7);
		Data.IPAddress=data.IPAddress;
	}
	if(Data.SubnetMask!=data.SubnetMask){
		strcpy(Text,"W21");
		char	*fp=strchr(Text,0);
		QString2Char(data.SubnetMask,fp,100);
		int	Len=strlen(Text);
		ReadLine(Text,7);
		Data.SubnetMask=data.SubnetMask;
	}
	if(Data.DefaultGateway!=data.DefaultGateway){
		strcpy(Text,"W22");
		char	*fp=strchr(Text,0);
		QString2Char(data.DefaultGateway,fp,100);
		int	Len=strlen(Text);
		ReadLine(Text,7);
		Data.DefaultGateway=data.DefaultGateway;
	}
	if(Data.Port!=data.Port){
		sprintf(Text,"W23%05d",data.Port);
		int	Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		ReadLine(Text,7);
		Data.Port=data.Port;
	}
}

bool	ImacControlByLAN::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

bool	ImacControlByLAN::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

void	ImacControlByLAN::TransmitDirectly(GUIDirectMessage *packet)
{
}

bool	ImacControlByLAN::ShowSettingDialog(void)
{
	SettingDialog	D(this,GetLayersBase());
	if(D.exec()==(int)true){
		Data=*D.Data;
		Initial();
		return true;
	}
	return false;
}

bool	ImacControlByLAN::InitialPhysical(const QString &Param)
{
	return true;
}

bool	ImacControlByLAN::ReflectPhysical(void)
{
	Initial();

	return true;
}

bool	ImacControlByLAN::ReflectPhysicalTurnOn(bool LightOn)
{
	if(SetON(LightOn)==false)
		return false;

	return true;
}