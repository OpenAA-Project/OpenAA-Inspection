#include "XCommToTrigger.h"
#include "CartonMenuForm.h"

CommToTrigger::CommToTrigger(CartonMenuForm *p)
	:Sock(this),Parent(p)
{
	connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

bool	CommToTrigger::Connect(void)
{
	Sock.connectToHost(Parent->Param.SystemTriggerIPAddress,TriggerControllerPort);
	Sock.waitForConnected(1000);
	if(Sock.state()==QAbstractSocket::ConnectedState){
		return true;
	}
	return false;
}
bool	CommToTrigger::IsConnected(void)
{
	if(Sock.state()==QAbstractSocket::ConnectedState){
		return true;
	}
	return false;
}
bool	CommToTrigger::Send(struct	TriggerInfo &Data)
{
	BYTE	Cmd[2];
	Cmd[0]=0x0F;
	Cmd[1]=0x1A;

	if(Sock.state()==QAbstractSocket::ConnectedState){
		if(Sock.write((const char *)Cmd,2)!=2)
			return false;
		if(Sock.write((const char *)&Data,sizeof(Data))!=sizeof(Data))
			return false;
		Sock.flush();
		return true;
	}
	return false;
}

bool	CommToTrigger::Request(struct	TriggerInfo &Data)
{
	BYTE	Cmd[2];
	Cmd[0]=0x0F;
	Cmd[1]=0x1B;
	if(Sock.state()==QAbstractSocket::ConnectedState){
		Received=false;
		if(Sock.write((const char *)Cmd,2)!=2)
			return false;
		Sock.waitForReadyRead(500);
		if(Received==true){
			Data=ReceivedData;
			return true;
		}
	}
	return false;
}
bool	CommToTrigger::RequestCounter(struct ResultCounterInfo &Data)
{
	BYTE	Cmd[2];
	Cmd[0]=0x0F;
	Cmd[1]=0x30;
	if(Sock.state()==QAbstractSocket::ConnectedState){
		Received=false;
		if(Sock.write((const char *)Cmd,2)!=2)
			return false;
		Sock.waitForReadyRead(500);
		if(Received==true){
			Data=CounterData;
			return true;
		}
	}
	return false;
}
bool	CommToTrigger::ResetCounter(void)
{
	BYTE	Cmd[2];
	Cmd[0]=0x0F;
	Cmd[1]=0x31;

	if(Sock.state()==QAbstractSocket::ConnectedState){
		if(Sock.write((const char *)Cmd,2)!=2)
			return false;
		Sock.flush();
		return true;
	}
	return false;
}

bool	CommToTrigger::Send(struct	DropPassInfo &Data)
{
	BYTE	Cmd[2];
	Cmd[0]=0x0F;
	Cmd[1]=0x1C;

	if(Sock.state()==QAbstractSocket::ConnectedState){
		if(Sock.write((const char *)Cmd,2)!=2)
			return false;
		if(Sock.write((const char *)&Data,sizeof(Data))!=sizeof(Data))
			return false;
		Sock.flush();
		return true;
	}
	return false;
}

bool	CommToTrigger::Request(struct	DropPassInfo &Data)
{
	BYTE	Cmd[2];
	Cmd[0]=0x0F;
	Cmd[1]=0x1D;
	if(Sock.state()==QAbstractSocket::ConnectedState){
		Received=false;
		if(Sock.write((const char *)Cmd,2)!=2)
			return false;
		Sock.waitForReadyRead(500);
		if(Received==true){
			Data=DropPassData;
			return true;
		}
	}
	return false;
}
void	CommToTrigger::SlotReadyRead()
{
	int	Len=Sock.bytesAvailable();
	if(Len>1){
		BYTE	Cmd;
		Sock.read((char *)&Cmd,1);
		Len--;
		if(Cmd==0x1E && Len>=sizeof(ReceivedData)){
			int	n=Sock.read((char *)&ReceivedData,sizeof(ReceivedData));
			if(n==sizeof(ReceivedData)){
				Received=true;
			}
			Len-=n;
		}
		else if(Cmd==0x1F && Len>=sizeof(DropPassData)){
			int	n=Sock.read((char *)&DropPassData,sizeof(DropPassData));
			if(n==sizeof(DropPassData)){
				Received=true;
			}
			Len-=n;
		}
		else if(Cmd==0x30 && Len>=sizeof(CounterData)){
			if(Parent->Param.CommToOldController==true){
				int	n=Sock.read((char *)&CounterDataOld,sizeof(CounterDataOld));
				if(n==sizeof(CounterDataOld)){
					CounterData.TotalCount	=CounterDataOld.TotalCount	;
					CounterData.TMCount		=CounterDataOld.TMCount		;
					CounterData.OKCount		=CounterDataOld.OKCount		;
					CounterData.NGCount		=CounterDataOld.NGCount		;
					CounterData.Mismatch	=false;
					Received=true;
				}
				Len-=n;
			}
			else{
				int	n=Sock.read((char *)&CounterData,sizeof(CounterData));
				if(n==sizeof(CounterData)){
					Received=true;
				}
				Len-=n;
			}
		}
		if(Len!=0){
			QByteArray	Dummy=Sock.readAll();
		}
	}
}
