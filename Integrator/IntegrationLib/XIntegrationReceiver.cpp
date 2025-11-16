#include "XIntegrationComm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XIntegrationBase.h"
#include "XParamIntegrationMaster.h"
#include "XGeneralFunc.h"

const	int		MaxWaitingSecondInPacketReceive=30;

void IntegrationCommPipe::ExeReadyRead(QTcpSocket *Sock)
{
	RxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>MaxWaitingSecondInPacketReceive))){
			int Len=Sock->read(((char *)&Pct)+LastPacketLoadedSize, sizeof(Pct)-LastPacketLoadedSize);
			if(Len<0){
				RxReEntrant--;
				return;
			}
			if((Len+LastPacketLoadedSize)!=sizeof(Pct)){
				LastPacketLoadedSize+=Len;
				RxReEntrant--;
				return;
			}
			LastPacketLoadedSize=0;

			NowOnXByte	=Pct.NowOnXByte	;
			NowCmd		=Pct.NowCmd		;
			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new IntegrationRecList(NowOnXByte);
			OnRBuff->Cmd			=NowCmd;
			OnRBuff->SlaveNo		=SlaveNo;
			OnRBuff->EmitterRootLen	=Pct.EmitterRootLen;
			OnRBuff->EmitterNameLen	=Pct.EmitterNameLen;
			OnRBuff->ClassNameLen	=Pct.ClassNameLen;
			OnRBuff->ErrorCode		=Pct.ErrorCode;
			OnRBuff->ErrorLevel		=Pct.ErrorLevel;
			OnRBuff->ErrorMessageLen=Pct.ErrorMessageLen;
			OnRBuff->ErrorTimeLen	=Pct.ErrorTimeLen;
			OnRBuff->IDForUndo		=Pct.IDForUndo;

			NowOnPoint=0;
		
			int	N=Sock->bytesAvailable();
			if(N!=0){
				if(NowOnXByte>=N){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
					if(Len<0){
						RxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
				else if(NowOnXByte!=0){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte);
					if(Len<0){
						RxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
			}
			RxState=_NowOnReceiving;
		}
		else{
			//qint64	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte-NowOnPoint);
			int	N=Sock->bytesAvailable();
			int	RByte=min(OnRBuff->Len-NowOnPoint,N);
			int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint),RByte);
			//int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
			if(Len<0){
				RxReEntrant--;
				return;
			}
			NowOnPoint+=Len;
		}

		LastReceivingTime=time(NULL);
		if(NowOnXByte<=NowOnPoint){
			RxState=_NowOnWaiting;
			if(OnRBuff!=NULL && OnRBuff->EmitterRootLen==0 && OnRBuff->EmitterNameLen==0 && OnRBuff->ClassNameLen!=0){
				SlaveNo=OnRBuff->Cmd;
				GetLayersBase()->GetIntegrationBasePointer()->SlaveConnected();
			}
			else{
				MuteRecData.lock();
				RecData.AppendList(OnRBuff);
				OnRBuff=NULL;
				MuteRecData.unlock();
				emit	SignalReceived(SlaveNo ,NowCmd);
			}
		}
	}while(Sock->bytesAvailable()!=0);
	RxReEntrant--;
}
