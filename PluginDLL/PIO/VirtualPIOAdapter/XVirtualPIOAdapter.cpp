#include "XVirtualPIOAdapter.h"
#include<QFile>
#include<QElapsedTimer>
#include "XGeneralFunc.h"
#include "swap.h"

PIOAdapter::PIOAdapter(QWidget *parent,const QString &IPAddress,int PortNumber,const QString &MemName)
	:AttachedMem(MemName)
{
	Mutex.lock();
	if(AttachedMem.attach()==true){
		MemMap=(struct PIOMemoryMap *)AttachedMem.data();
		AttachedMem.lock();
		::QString2Char(IPAddress,(char *)MemMap->ReqData,sizeof(MemMap->ReqData));
		MemMap->Index		=PortNumber;
		MemMap->AckCommand	=0;
		MemMap->ReqCommand	=OpenPIO;
		AttachedMem.unlock();
		while(GetAckCommand()==0){
			GSleep(1);
		}
		AttachedMem.lock();
		if(MemMap->AckCommand==AckPIO){
			MemHandle=MemMap->AckIndex;
		}
		MemMap->AckCommand=0;
		AttachedMem.unlock();
	}
	else{
		MemMap	=NULL;
		MemHandle=-1;
	}
	Mutex.unlock();
}

PIOAdapter::~PIOAdapter(void)
{
	if(AttachedMem.isAttached()==true){
		AttachedMem.detach();
	}
	MemMap	=NULL;
	MemHandle=-1;
}

int		PIOAdapter::GetAckCommand(void)
{
	AttachedMem.lock();
	int	ret=MemMap->AckCommand;
	AttachedMem.unlock();
	return ret;
}

void		PIOAdapter::ClearAckCommand(void)
{
	AttachedMem.lock();
	MemMap->AckCommand=0;
	AttachedMem.unlock();
}

bool	PIOAdapter::LoadDefFile(const QString &FileName)
{
	Mutex.lock();
	if(MemHandle>=0){
		::QString2Char(FileName,(char *)MemMap->ReqData,sizeof(MemMap->ReqData));
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->ReqCommand	=PIOReqLoadDefFile;
		AttachedMem.unlock();
		int		ret;
		while((ret=GetAckCommand())==0){
			GSleep(1);
		}
		if(ret==AckPIO){
			ClearAckCommand();
			Mutex.unlock();
			return true;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return false;
}
	
int		PIOAdapter::GetBitCountIn(void)
{	
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->ReqCommand	=ReqPIOINBitCount;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(10);
		}
		if(ret==AckPIO){
			int	N=MemMap->AckIndex;
			ClearAckCommand();
			Mutex.unlock();
			return N;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return 0;
}

int		PIOAdapter::GetBitCountOut(void)
{	
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->ReqCommand	=ReqPIOOUTBitCount;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(10);
		}
		if(ret==AckPIO){
			int	N=MemMap->AckIndex;
			ClearAckCommand();
			Mutex.unlock();
			return N;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return 0;
}
int		PIOAdapter::GetBitData(int bitnumber)
{
	AttachedMem.lock();
	int	d=MemMap->INData[bitnumber];
	AttachedMem.unlock();
	return d;
}
bool	PIOAdapter::SetBitData(int bitnumber ,int data)
{
	AttachedMem.lock();
	MemMap->OUTData[bitnumber]=data;
	AttachedMem.unlock();
	return true;
}
int		PIOAdapter::GetBitOutData(int bitnumber)
{
	AttachedMem.lock();
	int	d=MemMap->OUTData[bitnumber];
	AttachedMem.unlock();
	return d;
}

bool	PIOAdapter::GetBitInDataStream(BYTE BitData[] ,int BitNumb)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=BitNumb;
		MemMap->ReqCommand	=ReqInDataStream;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(10);
		}
		if(ret==AckPIO){
			memcpy(BitData,MemMap->AckData,BitNumb);
			ClearAckCommand();
			Mutex.unlock();
			return true;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return false;
}
bool	PIOAdapter::SetBitOutDataStream(BYTE BitData[] ,int BitNumb)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=BitNumb;
		memcpy(MemMap->AckData,BitData,BitNumb);
		MemMap->ReqCommand	=SendOutDataStream;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(10);
		}
		if(ret==AckPIO){
			ClearAckCommand();
			Mutex.unlock();
			return true;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return false;
}
bool	PIOAdapter::GetBitOutDataStream(BYTE BitData[] ,int BitNumb)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=BitNumb;
		MemMap->ReqCommand	=ReqOutDataStream;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(10);
		}
		if(ret==AckPIO){
			memcpy(BitData,MemMap->AckData,BitNumb);
			ClearAckCommand();
			Mutex.unlock();
			return true;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return false;
}
