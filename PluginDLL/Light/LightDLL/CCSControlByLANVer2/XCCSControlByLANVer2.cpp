#include "CCSControlByLANVer2.h"
#include "XGeneralFunc.h"
#include <string.h>
#include "SettingDialog.h"

#define	WaitingMilisecForConnection	3000

CCSControlByLANParam::ChannelInfo::ChannelInfo(void)
{
	Power	=0;
	Mode	=0;
	ON		=false;
}

CCSControlByLANParam::ChannelInfo	&CCSControlByLANParam::ChannelInfo::operator=(CCSControlByLANParam::ChannelInfo &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	CCSControlByLANParam::ChannelInfo::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Power)==false)
		return false;
	if(::Save(f,Mode)==false)
		return false;
	if(::Save(f,ON)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	return true;
}
bool	CCSControlByLANParam::ChannelInfo::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Power)==false)
		return false;
	if(::Load(f,Mode)==false)
		return false;
	if(::Load(f,ON)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	return true;
}

CCSControlByLANParam::CCSControlByLANParam(void)
{
	IPAddress			=/**/"192.168.0.2";
	Port				=40001;
	SubnetMask			=/**/"255.255.255.0";
	DefaultGateway		=/**/"192.168.0.1";
	ReturnToIPAddress	=/**/"192.168.0.16";
	ReturnToPort		=30001;
}

CCSControlByLANParam	&CCSControlByLANParam::operator=(CCSControlByLANParam &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

bool	CCSControlByLANParam::Save(QIODevice *f)
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
	if(::Save(f,ReturnToIPAddress)==false)
		return false;
	if(::Save(f,ReturnToPort)==false)
		return false;

	for(int i=0;i<8;i++){
		if(ChannelInfoData[i].Save(f)==false)
			return false;
	}
	return true;
}
bool	CCSControlByLANParam::Load(QIODevice *f)
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
	if(::Load(f,ReturnToIPAddress)==false)
		return false;
	if(::Load(f,ReturnToPort)==false)
		return false;

	for(int i=0;i<8;i++){
		if(ChannelInfoData[i].Load(f)==false)
			return false;
	}
	return true;
}

//============================================================================
CCSControlByLANVer2::CCSControlByLANVer2(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	if(LightParamStr.isEmpty()==false)
		Data.IPAddress=LightParamStr;
}

CCSControlByLANVer2::~CCSControlByLANVer2(void)
{
	Close();
}

int	SetChecksum(char *Text)
{
	int	C=0;
	for(int j=0;Text[j]!=0;j++){
		C+=Text[j];
	}
	int	Checksum=C&0xFF;
	char	CStr[20];
	sprintf(CStr,"%02X\r\n",Checksum);
	strcat(Text,CStr);
	return strlen(Text);
}

bool	CCSControlByLANVer2::ReadLine(char *Text)
{
	Text[0]=0;
	if(strchr(Text,'\n')==NULL){
		int	i;
		for(i=0;Sock.bytesAvailable ()==0 && i<1000;i++){
			Sock.waitForReadyRead(1);
		}
		if(i>=1000){
			return false;
		}
		char	Str[1000];
		int	Len=Sock.read(Str,1000);
		Str[Len]=0;
		strcat(Text,Str);
	}
	return true;
}


bool	CCSControlByLANVer2::Initial(void)
{
	if(Transfer(0,NULL)==false)
		return false;
	return true;
}

bool	CCSControlByLANVer2::Close(void)
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

bool	CCSControlByLANVer2::SetON(bool ON)
{
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		Sock.connectToHost(Data.IPAddress,Data.Port);
		Sock.waitForConnected(WaitingMilisecForConnection);
	}
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		return false;
	}
	if(Sock.isOpen()==false){
		Sock.open(QIODevice::ReadWrite);
	}
	char	Text[200];
	int		Len;
	for(int i=0;i<8;i++){
		sprintf(Text,"@%02d" "F\r\n",i);
		//Len=SetChecksum(Text);
		Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;
		int	Power=-1;
		int	iON=-1;
		if(strchr(Text,'O')!=NULL){
			Power=(Text[4]-'0')*1000 + (Text[5]-'0')*100 + (Text[6]-'0')*10 + (Text[7]-'0');
		}
		sprintf(Text,"@%02d" "L\r\n",i);
		//Len=SetChecksum(Text);
		Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;

		if(strchr(Text,'O')!=NULL){
			iON	 =(Text[4]-'0');
		}
		int	CurrentON=(ON==true)?1:0;
		if(CurrentON!=iON){
			sprintf(Text,"@%02d" "L%d\r\n",i,CurrentON);
			//int	Len=SetChecksum(Text);
			Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text)==false)
				return false;
		}
	}
	return true;
}

bool	CCSControlByLANVer2::SetON(bool ON ,int Ch)
{
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		Sock.connectToHost(Data.IPAddress,Data.Port);
		Sock.waitForConnected(WaitingMilisecForConnection);
	}
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		return false;
	}
	if(Sock.isOpen()==false){
		Sock.open(QIODevice::ReadWrite);
	}
	char	Text[200];
	{
		int	CurrentON=(ON==true)?1:0;
		sprintf(Text,"@%02d" "L%d\r\n",Ch,CurrentON);
		//int	Len=SetChecksum(Text);
		int	Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;
	}
	return true;
}
bool	CCSControlByLANVer2::Transfer(int PatternNumber,QProgressBar *Bar)
{
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		Sock.connectToHost(Data.IPAddress,Data.Port);
		Sock.waitForConnected(WaitingMilisecForConnection);
	}
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		return false;
	}
	if(Sock.isOpen()==false){
		Sock.open(QIODevice::ReadWrite);
	}
	char	Text[200];
	int		Len;
	for(int i=0;i<8;i++){
		sprintf(Text,"@%02d" "F\r\n",i);
		//Len=SetChecksum(Text);
		Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;
		int	Power=-1;
		int	ON=-1;
		if(strchr(Text,'O')!=NULL){
			Power=(Text[4]-'0')*1000 + (Text[5]-'0')*100 + (Text[6]-'0')*10 + (Text[7]-'0');
		}
		sprintf(Text,"@%02d" "L\r\n",i);
		//Len=SetChecksum(Text);
		Len=strlen(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;

		if(strchr(Text,'O')!=NULL){
			ON	 =(Text[4]-'0');
		}
		if(Data.ChannelInfoData[i].Power!=Power){
			sprintf(Text,"@%02d" "F%04d\r\n",i,Data.ChannelInfoData[i].Power);
			//int	Len=SetChecksum(Text);
			Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text)==false)
				return false;
		}
		int	CurrentON=(Data.ChannelInfoData[i].ON==true)?1:0;
		if(CurrentON!=ON){
			sprintf(Text,"@%02d" "L%d\r\n",i,CurrentON);
			//int	Len=SetChecksum(Text);
			Len=strlen(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text)==false)
				return false;
		}
		if(Bar!=NULL){
			Bar->setValue(Bar->value()+1);
		}
	}
	return true;
}

void	CCSControlByLANVer2::SetIPAddress(CCSControlByLANParam &data)
{
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		Sock.connectToHost(Data.IPAddress,Data.Port);
		Sock.waitForConnected(WaitingMilisecForConnection);
	}
	if(Sock.state()!=QAbstractSocket::ConnectedState){
		return;
	}
	if(Sock.isOpen()==false){
		Sock.open(QIODevice::ReadWrite);
	}
	char	Text[200];

	if(Data.IPAddress!=data.IPAddress){
		strcpy(Text,"@00E01");
		char	*fp=strchr(Text,0);
		QString2Char(data.IPAddress ,fp,100);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		ReadLine(Text);
		Data.IPAddress=data.IPAddress;
	}
	if(Data.SubnetMask!=data.SubnetMask){
		strcpy(Text,"@00E02");
		char	*fp=strchr(Text,0);
		QString2Char(data.SubnetMask,fp,100);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		ReadLine(Text);
		Data.SubnetMask=data.SubnetMask;
	}
	if(Data.DefaultGateway!=data.DefaultGateway){
		strcpy(Text,"@00E03");
		char	*fp=strchr(Text,0);
		QString2Char(data.DefaultGateway,fp,100);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		ReadLine(Text);
		Data.DefaultGateway=data.DefaultGateway;
	}
	if(Data.ReturnToIPAddress!=data.ReturnToIPAddress){
		strcpy(Text,"@00E05");
		char	*fp=strchr(Text,0);
		QString2Char(data.ReturnToIPAddress,fp,100);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		ReadLine(Text);
		Data.ReturnToIPAddress=data.ReturnToIPAddress;
	}
	if(Data.Port!=data.Port){
		sprintf(Text,"@00" "E04%05d",data.Port);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		Sock.flush();
		ReadLine(Text);
		Data.Port=data.Port;
	}
	if(Data.ReturnToPort!=data.ReturnToPort){	
		sprintf(Text,"@00" "E04%06d",data.ReturnToPort);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		Sock.flush();
		ReadLine(Text);
		Data.ReturnToPort=data.ReturnToPort;
	}
}

bool	CCSControlByLANVer2::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

bool	CCSControlByLANVer2::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

void	CCSControlByLANVer2::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetOnOffByChannel	*CmdSetOnOffByChannelVar=dynamic_cast<CmdSetOnOffByChannel *>(packet);
	if(CmdSetOnOffByChannelVar!=NULL){
		SetON(CmdSetOnOffByChannelVar->ON,CmdSetOnOffByChannelVar->Channel);
		return;
	}
}

bool	CCSControlByLANVer2::ShowSettingDialog(void)
{
	SettingDialog	D(this,GetLayersBase());
	if(D.exec()==(int)true){
		Data=*D.Data;
		Initial();
		return true;
	}
	return false;
}

bool	CCSControlByLANVer2::InitialPhysical(const QString &Param)
{
	return true;
}

bool	CCSControlByLANVer2::ReflectPhysical(void)
{
	Initial();

	return true;
}

bool	CCSControlByLANVer2::ReflectPhysicalTurnOn(bool LightOn)
{
	if(SetON(LightOn)==false)
		return false;

	return true;
}