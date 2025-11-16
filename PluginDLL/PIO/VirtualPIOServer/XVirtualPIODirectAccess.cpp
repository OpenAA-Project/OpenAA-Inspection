#include "XVirtualPIODirectAccess.h"
#include<QFile>
#include<QElapsedTimer>
#include "XGeneralFunc.h"
#include "swap.h"

XVirtualPIODirectAccessClient::XVirtualPIODirectAccessClient(void)
	:AttachedMem("VirtualPIODIrectAccess")
{
	MemMap=NULL;
}
XVirtualPIODirectAccessClient::~XVirtualPIODirectAccessClient(void)
{
	if(AttachedMem.isAttached()==true){
		AttachedMem.detach();
	}
	MemMap	=NULL;
}


bool	XVirtualPIODirectAccessClient::InitialClient(void)
{
	AttachedMem.setKey("VirtualPIODIrectAccess");
	if(AttachedMem.attach()==false)
		return false;
	if(AttachedMem.isAttached()==true){
		MemMap=(struct PIOMemoryMap *)AttachedMem.data();
		MemMap->AckCommand	=0;
		MemMap->ReqCommand	=OpenPIO;
		while(MemMap->AckCommand==0){
			GSleep(1);
		}
		if(MemMap->AckCommand==AckPIO){
			MemHandle=MemMap->AckIndex;
		}
		return true;
	}
	else{
		MemMap	=NULL;
		MemHandle=-1;
	}
	return false;
}

QString	GetNumber(QString s,int &Number ,bool &ok)
{
	Number=0;
	ok=false;
	int	i;
	for(i=0;i<5 && i<s.count();i++){
		QChar	a=s.at(i);
		if(a.isDigit()==true){
			Number*=10;
			Number+=a.digitValue ();
			ok=true;
		}
		else{
			break;
		}
	}
	return s.mid(i).trimmed();
}

bool	XVirtualPIODirectAccessClient::LoadDefFile(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		QTextStream	Txt(&File);
		while(Txt.atEnd()==false){
			QString	s1=Txt.readLine(1000);
			QString	s=s1.trimmed();
			if(s.left(2).toUpper()==QString("IN")){
				QString	h=s.mid(2);
				int	n;
				bool	ok;
				QString	m=GetNumber(h,n,ok);
				if(ok==true){
					if(m.left(1)=="\""){
						m=m.mid(1);
					}
					if(m.right(1)=="\""){
						int	L=m.count();
						m=m.left(L-1);
					}
					PortBit	*a=new PortBit();
					a->BitNumber	=n;
					a->BitName		=m;
					PortBitsIn.AppendList(a);

					RegisterInBit(n ,m);
				}
			}
			else if(s.left(3).toUpper()==QString("OUT")){
				QString	h=s.mid(3);
				int	n;
				bool	ok;
				QString	m=GetNumber(h,n,ok);
				if(ok==true){
					if(m.left(1)=="\""){
						m=m.mid(1);
					}
					if(m.right(1)=="\""){
						int	L=m.count();
						m=m.left(L-1);
					}
					PortBit	*a=new PortBit();
					a->BitNumber	=n;
					a->BitName		=m;
					PortBitsOut.AppendList(a);

					RegisterOutBit(n ,m);
				}
			}
		}
	}
	return false;
}

//Client side function

	
bool	XVirtualPIODirectAccessClient::RegisterInBit(int BitNumber ,const QString &BitName)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=BitNumber;
		QString2Char(BitName ,(char *)MemMap->ReqData ,sizeof(MemMap->ReqData));
		MemMap->ReqCommand	=RegInBit;
		AttachedMem.unlock();
		int	ret;
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
	
bool	XVirtualPIODirectAccessClient::RegisterOutBit(int BitNumber ,const QString &BitName)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=BitNumber;
		QString2Char(BitName ,(char *)MemMap->ReqData ,sizeof(MemMap->ReqData));
		MemMap->ReqCommand	=RegOutBit;
		AttachedMem.unlock();
		int	ret;
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


int		XVirtualPIODirectAccessClient::GetAckCommand(void)
{
	AttachedMem.lock();
	int	ret=MemMap->AckCommand;
	AttachedMem.unlock();
	return ret;
}

void		XVirtualPIODirectAccessClient::ClearAckCommand(void)
{
	AttachedMem.lock();
	MemMap->AckCommand=0;
	AttachedMem.unlock();
}



int		XVirtualPIODirectAccessClient::GetBitData(int bitnumber)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=bitnumber;
		MemMap->ReqCommand	=ReqInData;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(1);
		}
		if(ret==AckPIO){
			int	d=MemMap->AckData[0];
			ClearAckCommand();
			Mutex.unlock();
			return d;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return 0;
}
bool	XVirtualPIODirectAccessClient::SetBitData(int bitnumber ,int data)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=bitnumber;
		MemMap->ReqData[0]	=data;
		MemMap->ReqCommand	=SendOutData;
		AttachedMem.unlock();
		int	ret;
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
int		XVirtualPIODirectAccessClient::GetBitOutData(int bitnumber)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=bitnumber;
		MemMap->ReqCommand	=ReqOutData;
		AttachedMem.unlock();
		int	ret;
		while((ret=GetAckCommand())==0){
			GSleep(1);
		}
		if(ret==AckPIO){
			int	d=MemMap->AckData[0];
			ClearAckCommand();
			Mutex.unlock();
			return d;
		}
		ClearAckCommand();
	}
	Mutex.unlock();
	return 0;
}

bool	XVirtualPIODirectAccessClient::GetBitInDataStream(BYTE BitData[] ,int BitNumb)
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
			GSleep(1);
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
bool	XVirtualPIODirectAccessClient::SetBitOutDataStream(BYTE BitData[] ,int BitNumb)
{
	Mutex.lock();
	if(MemHandle>=0){
		AttachedMem.lock();
		MemMap->Handle		=MemHandle;
		MemMap->AckCommand	=0;
		MemMap->Index		=BitNumb;
		memcpy(MemMap->ReqData,BitData,BitNumb);
		MemMap->ReqCommand	=SendOutDataStream;
		AttachedMem.unlock();
		int	ret;
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
bool	XVirtualPIODirectAccessClient::GetBitOutDataStream(BYTE BitData[] ,int BitNumb)
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
			GSleep(1);
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
