#include "CCSControlByLAN.h"
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
CCSControlByLAN::CCSControlByLAN(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	if(LightParamStr.isEmpty()==false)
		Data.IPAddress=LightParamStr;
}

CCSControlByLAN::~CCSControlByLAN(void)
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

bool	CCSControlByLAN::ReadLine(char *Text)
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


bool	CCSControlByLAN::Initial(void)
{
	if(Transfer(0,NULL)==false)
		return false;
	return true;
}

bool	CCSControlByLAN::Close(void)
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

bool	CCSControlByLAN::SetON(bool ON)
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

	for(int i=0;i<8;i++){
		sprintf(Text,"@%02d" "M",i);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;
		char	*ep=strchr(Text,0);
		*(ep-2)=0;
		int	Ch=-1;
		int	Power=-1;
		int	Mode=-1;
		int	iON=-1;
		if(strchr(Text,'O')!=NULL){
			matchscanf(Text,"@%dOF%d.S%d.L%d",&Ch,&Power,&Mode,&iON);
		}
		int	CurrentON=(ON==true)?1:0;
		if(CurrentON!=iON){
			sprintf(Text,"@%02d" "L%d",i,CurrentON);
			int	Len=SetChecksum(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text)==false)
				return false;
		}
	}
	return true;
}

bool	CCSControlByLAN::SetON(bool ON ,int Ch)
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
		sprintf(Text,"@%02d" "L%d",Ch,CurrentON);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;
	}
	return true;
}
bool	CCSControlByLAN::Transfer(int PatternNumber,QProgressBar *Bar)
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

	for(int i=0;i<8;i++){
		sprintf(Text,"@%02d" "M",i);
		int	Len=SetChecksum(Text);
		Sock.write(Text,Len);
		Sock.flush();
		if(ReadLine(Text)==false)
			return false;
		int	Ch=-1;
		int	Power=-1;
		int	Mode=-1;
		int	ON=-1;
		if(strchr(Text,'O')!=NULL){
			Power=(Text[5]-'0')*100 + (Text[6]-'0')*10 + (Text[7]-'0');
			Mode =(Text[10]-'0')*10 + (Text[11]-'0');
			ON	 =(Text[14]-'0');
		}
		if(Data.ChannelInfoData[i].Power!=Power){
			sprintf(Text,"@%02d" "F%03d",i,Data.ChannelInfoData[i].Power);
			int	Len=SetChecksum(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text)==false)
				return false;
		}
		if(Data.ChannelInfoData[i].Mode!=Mode){
			sprintf(Text,"@%02d" "S%02d",i,Data.ChannelInfoData[i].Mode);
			int	Len=SetChecksum(Text);
			Sock.write(Text,Len);
			Sock.flush();
			if(ReadLine(Text)==false)
				return false;
		}
		int	CurrentON=(Data.ChannelInfoData[i].ON==true)?1:0;
		if(CurrentON!=ON){
			sprintf(Text,"@%02d" "L%d",i,CurrentON);
			int	Len=SetChecksum(Text);
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

void	CCSControlByLAN::SetIPAddress(CCSControlByLANParam &data)
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

bool	CCSControlByLAN::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

bool	CCSControlByLAN::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

void	CCSControlByLAN::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetOnOffByChannel	*CmdSetOnOffByChannelVar=dynamic_cast<CmdSetOnOffByChannel *>(packet);
	if(CmdSetOnOffByChannelVar!=NULL){
		SetON(CmdSetOnOffByChannelVar->ON,CmdSetOnOffByChannelVar->Channel);
		return;
	}
}

bool	CCSControlByLAN::ShowSettingDialog(void)
{
	SettingDialog	D(this,GetLayersBase());
	if(D.exec()==(int)true){
		Data=*D.Data;
		Initial();
		return true;
	}
	return false;
}

bool	CCSControlByLAN::InitialPhysical(const QString &Param)
{
	return true;
}

bool	CCSControlByLAN::ReflectPhysical(void)
{
	Initial();

	return true;
}

bool	CCSControlByLAN::ReflectPhysicalTurnOn(bool LightOn)
{
	if(SetON(LightOn)==false)
		return false;

	return true;
}