#include "XRegulusWorldClient.h"
#include "swap.h"
#include "XGeneralFunc.h"

RWClientSocket::RWClientSocket(RegulusWorld *p,QObject *parent)
	:QTcpSocket(parent)
	,Parent(p)
{
	OnRBuff=NULL;
	LastReceivingTime	=0;
	NowOnPoint			=0;
	NowOnXByte			=0;
	NowCmd				=0;
	RxState				=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;

	connect(this,SIGNAL(readyRead())	,this,SLOT(SlotReadyRead()));
	connect(this,SIGNAL(disconnected())	,this ,SLOT(SlotDisconnected()));
}

const	int		MaxWaitingSecondInPacketReceive=30;
void	RWClientSocket::SlotReadyRead()
{
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>MaxWaitingSecondInPacketReceive))){
			int Len=read(((char *)&Pct)+LastPacketLoadedSize, sizeof(Pct)-LastPacketLoadedSize);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			if((Len+LastPacketLoadedSize)!=sizeof(Pct)){
				LastPacketLoadedSize+=Len;
				FastCommLeafRxReEntrant--;
				return;
			}
			LastPacketLoadedSize=0;

			NowOnXByte	=Pct.NowOnXByte	;
			NowCmd		=Pct.NowCmd		;
			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new RWRecList(NowOnXByte);
			OnRBuff->Cmd			=NowCmd;
			OnRBuff->EmitterNameLen	=Pct.EmitterNameLen;
			OnRBuff->ClassNameLen	=Pct.ClassNameLen;
			OnRBuff->ErrorCode		=Pct.ErrorCode;
			OnRBuff->ErrorLevel		=Pct.ErrorLevel;
			OnRBuff->ErrorMessageLen=Pct.ErrorMessageLen;
			OnRBuff->ErrorTimeLen	=Pct.ErrorTimeLen;
			OnRBuff->IDForUndo		=Pct.IDForUndo;

			NowOnPoint=0;
		
			int	N=bytesAvailable();
			if(N!=0){
				if(NowOnXByte>=N){
					Len=read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
				else if(NowOnXByte!=0){
					Len=read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
			}
			RxState=_NowOnReceiving;
		}
		else{
			//qint64	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte-NowOnPoint);
			int	N=bytesAvailable();
			int	RByte=min(OnRBuff->Len-NowOnPoint,N);
			int	Len=read((char *)(OnRBuff->GetPointer()+NowOnPoint),RByte);
			//int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			NowOnPoint+=Len;
		}

		LastReceivingTime=time(NULL);
		if(NowOnXByte<=NowOnPoint){
			RxState=_NowOnWaiting;
			MuteRecData.lock();
			RecData.AppendList(OnRBuff);
			OnRBuff=NULL;
			MuteRecData.unlock();
			emit	SignalReceived(ID ,NowCmd);
		}
	}while(bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}
void	RWClientSocket::SlotDisconnected()
{
	emit	SignalDisconnected(ID);
	deleteLater();
}
bool	RWClientSocket::TxData(int32 cmd ,const QString &EmitterNameString,const QString &CmdClassString 
					,QBuffer *f,int32 IDForUndo,ErrorCodeList &ErrorData)
{
	waitForBytesWritten(5000);

	int32	Len=f->size();
	char	EmitterName[1000];
	QString2Char(EmitterNameString ,EmitterName,sizeof(EmitterName));
	char	CmdClass[1000];
	QString2Char(CmdClassString ,CmdClass,sizeof(CmdClass));

	if(isTextModeEnabled()==true){
		setTextModeEnabled(false);
	}	
	int32	EmitterNameLen	=strlen(EmitterName);	
	int32	CmdClassLen		=strlen(CmdClass);	
	struct	RWTxRxLowPacket	Pct;
	Pct.NowOnXByte	=Len+CmdClassLen+1
					+EmitterNameLen+1
					+sizeof(Len);
	Pct.NowCmd			=cmd;
	Pct.EmitterNameLen	=EmitterNameLen;
	Pct.ClassNameLen	=CmdClassLen;
	Pct.IDForUndo		=IDForUndo;

	Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
	char	ErrorMessage[1000];
	char	ETime[30];
	if(ErrorData.GetLevel()!=ErrorCodeList::_None){
		Pct.ErrorCode	=ErrorData.GetErrorCode();
		QString2Char(ErrorData.GetMessageStr() ,ErrorMessage,sizeof(ErrorMessage));
		Pct.ErrorMessageLen	=strlen(ErrorMessage);
		Pct.NowOnXByte +=Pct.ErrorMessageLen+1;
		QString	t=ErrorData.GetErrorTime().toString("d/M/yy h:m:s.z");
		QString2Char(t,ETime,sizeof(ErrorMessage));
		Pct.ErrorTimeLen=strlen(ETime);
		Pct.NowOnXByte +=Pct.ErrorTimeLen+1;
	}
	if(write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
		return(false);
	}
	if(write((char *)EmitterName,EmitterNameLen+1)!=(EmitterNameLen+1)){
		return(false);
	}
	if(write((char *)CmdClass,CmdClassLen+1)!=(CmdClassLen+1)){
		return(false);
	}
	if(ErrorData.GetLevel()!=ErrorCodeList::_None){
		if(write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
			return(false);
		}
		if(write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
			return(false);
		}
	}
	if(write((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(write(f->buffer().data(),Len)!=Len){
		return(false);
	}
	if(flush()==false){
		return false;
	}
	return(true);

}

bool	RWClientSocket::WaitForReadyRead(int milisec)
{
	return waitForReadyRead(milisec);
}