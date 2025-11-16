#include "XVirtualPIODirectAccess.h"
#include<QFile>
#include<QElapsedTimer>
#include "XGeneralFunc.h"
#include "swap.h"
#include "XVirtualPIOServer.h"


//Server side function

XVirtualPIODirectAccessServer::XVirtualPIODirectAccessServer(PIOServer *_Server)
	:AttachedMem("VirtualPIODIrectAccess")
	,Server(_Server)
{
	MemMap=NULL;
}
XVirtualPIODirectAccessServer::~XVirtualPIODirectAccessServer(void)
{
	if(AttachedMem.isAttached()==true){
		AttachedMem.detach();
	}
	MemMap	=NULL;
}


bool	XVirtualPIODirectAccessServer::InitialServer(void)
{

	if(AttachedMem.attach()==false){
		if(AttachedMem.create(sizeof(struct	PIOMemoryMap))==true){
			MemMap=(struct PIOMemoryMap *)AttachedMem.data();
			return true;
		}
		else{
			MemMap=NULL;
		}
	}
	else{
		MemMap=(struct PIOMemoryMap *)AttachedMem.data();
		return true;
	}
	return false;
}

struct	BitStruct
{
	int		BitNumber;
	BYTE	Data;
};

int	SortBitStruct(const void *a ,const void *b)
{
	struct	BitStruct	*pa=(struct	BitStruct *)a;
	struct	BitStruct	*pb=(struct	BitStruct *)b;
	int	ret=pa->BitNumber - pb->BitNumber;
	return ret;
}
int		XVirtualPIODirectAccessServer::GetAckCommand(void)
{
	AttachedMem.lock();
	int	ret=MemMap->AckCommand;
	AttachedMem.unlock();
	return ret;
}

void		XVirtualPIODirectAccessServer::ClearAckCommand(void)
{
	AttachedMem.lock();
	MemMap->AckCommand=0;
	AttachedMem.unlock();
}

void	XVirtualPIODirectAccessServer::PollingInServer(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	AttachedMem.lock();
	if(MemMap->ReqCommand==OpenPIO){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=new AllocatedClient(Server,NULL);
		Server->DeleteDirectAccess();
		Server->AppendList(d);
		MemMap->AckIndex=Server->GetCount()-1;
		d->HandleNumber=MemMap->AckIndex;
		MemMap->AckCommand=AckPIO;
		AttachedMem.unlock();
		while(GetAckCommand()!=0){
			GSleep(1);
		}
		ReEntrant=false;
		return;
	}
	else if(MemMap->ReqCommand==RegInBit){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			ClientBitPort	*a=new ClientBitPort();
			a->BitNumber	=MemMap->Index;
			a->BitName		=(char *)MemMap->ReqData;
			a->Output		=false;
			a->CurrentOutput=0;
			d->BitPorts.AppendList(a);

			Server->BindData();

			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==RegOutBit){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			ClientBitPort	*a=new ClientBitPort();
			a->BitNumber	=MemMap->Index;
			a->BitName		=(char *)MemMap->ReqData;
			a->Output		=true;
			a->CurrentOutput=0;
			d->BitPorts.AppendList(a);

			Server->BindData();

			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==ReqInData){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			for(BindedIOBit *b=Server->IOBitsToShow.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->BitOut!=NULL){
					for(BindedBit *k=b->BitIn.GetFirst();k!=NULL;k=k->GetNext()){
						if(k->ClientPoint==d && k->BitPoint->BitNumber==MemMap->Index){
							MemMap->AckData[0]=b->BitOut->BitPoint->CurrentOutput;
							MemMap->AckCommand=AckPIO;
							AttachedMem.unlock();
							while(GetAckCommand()!=0){
								GSleep(1);
							}
							ReEntrant=false;
							return;
						}
					}
				}
			}
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==SendOutData){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			for(ClientBitPort *b=d->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Output==true && b->BitNumber==MemMap->Index){
					b->CurrentOutput=MemMap->ReqData[0];
					MemMap->AckCommand=AckPIO;
					AttachedMem.unlock();
					while(GetAckCommand()!=0){
						GSleep(1);
					}
					ReEntrant=false;
					return;
				}
			}
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==ReqOutData){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			for(ClientBitPort *b=d->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Output==true && b->BitNumber==MemMap->Index){
					MemMap->AckData[0]=b->CurrentOutput;
					MemMap->AckCommand=AckPIO;
					AttachedMem.unlock();
					while(GetAckCommand()!=0){
						GSleep(1);
					}
					ReEntrant=false;
					return;
				}
			}
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==ReqInDataStream){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			struct	BitStruct	StrData[1024];
			int					BitNumb=0;
			for(BindedIOBit *b=Server->IOBitsToShow.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->BitOut!=NULL){
					for(BindedBit *k=b->BitIn.GetFirst();k!=NULL;k=k->GetNext()){
						if(k->ClientPoint==d){
							StrData[BitNumb].BitNumber	=k->BitPoint->BitNumber;
							StrData[BitNumb].Data		=b->BitOut->BitPoint->CurrentOutput;
							BitNumb++;
						}
					}
				}
			}
			QSort(StrData,BitNumb,sizeof(struct	BitStruct),SortBitStruct);
			for(int i=0;i<MemMap->Index;i++){
				MemMap->AckData  [i]=0;
				for(int k=0;k<BitNumb;k++){
					if(StrData[k].BitNumber==i){
						MemMap->AckData  [i]=StrData[k].Data;
					}
				}
			}
			MemMap->AckIndex	=BitNumb;
			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==SendOutDataStream){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			struct	BitStruct	StrData[1024];
			int					BitNumb=0;
			for(ClientBitPort *b=d->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Output==true){
					StrData[BitNumb].BitNumber	=b->BitNumber;
					BitNumb++;
				}
			}
			QSort(StrData,BitNumb,sizeof(struct	BitStruct),SortBitStruct);
			for(int i=0;i<BitNumb && i<MemMap->Index;i++){
				StrData[i].Data	=MemMap->ReqData[i];
				for(ClientBitPort *b=d->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
					if(b->Output==true && b->BitNumber==StrData[i].BitNumber){
						b->CurrentOutput	= MemMap->ReqData[i];
						break;
					}
				}
			}
			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==ReqOutDataStream){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			struct	BitStruct	StrData[1024];
			int					BitNumb=0;
			for(ClientBitPort *b=d->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Output==true && b->BitNumber==MemMap->Index){
					StrData[BitNumb].BitNumber	=b->BitNumber;
					StrData[BitNumb].Data		=MemMap->ReqData[0];
					BitNumb++;
				}
			}
			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==ReqPIOINBitCount){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			struct	BitStruct	StrData[1024];
			int					BitNumb=0;
			for(BindedIOBit *b=Server->IOBitsToShow.GetFirst();b!=NULL;b=b->GetNext()){
				for(BindedBit *k=b->BitIn.GetFirst();k!=NULL;k=k->GetNext()){
					if(k->ClientPoint==d){
						StrData[BitNumb].BitNumber	=k->BitPoint->BitNumber;
						BitNumb++;
					}
				}
			}
			MemMap->AckIndex	=BitNumb;
			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	else if(MemMap->ReqCommand==ReqPIOOUTBitCount){
		MemMap->ReqCommand=0;
		AllocatedClient	*d=Server->GetAllocatedClient(MemMap->Handle);
		if(d!=NULL){
			struct	BitStruct	StrData[1024];
			int					BitNumb=0;
			for(ClientBitPort *b=d->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
				if(b->Output==true && b->BitNumber==MemMap->Index){
					BitNumb++;
				}
			}
			MemMap->AckIndex=BitNumb;
			MemMap->AckCommand=AckPIO;
			AttachedMem.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			ReEntrant=false;
			return;
		}
		MemMap->AckCommand=NackPIO;
	}
	AttachedMem.unlock();
	ReEntrant=false;
}
