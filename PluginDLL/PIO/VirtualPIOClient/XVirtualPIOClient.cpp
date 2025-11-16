#include "XVirtualPIOClient.h"
#include<QFile>
#include<QElapsedTimer>
#include "XGeneralFunc.h"
#include "swap.h"

PIOAdapter::PIOAdapter(QWidget *parent,const QString &IPAddress,int PortNumber,const QString &AccessMemoryName)
	:PIOSocket(parent,IPAddress,PortNumber)
	,MemoryMap(AccessMemoryName)
{
	ServerIPAddress	=IPAddress;
	ServerPortNumber=PortNumber;
	FlagAckInformation=false;
	ROutStreamBitData	=NULL;
	RInStreamBitData	=NULL;
	MaxBitCountIN		=0;
	MaxBitCountOUT		=0;

	if(MemoryMap.isAttached()==false){
		if(MemoryMap.create(sizeof(struct	PIOMemoryMap))==true){
			MemMap=(struct PIOMemoryMap *)MemoryMap.data();
		}
		else{
			MemMap=NULL;
		}
	}
	else{
		MemMap=(struct PIOMemoryMap *)MemoryMap.data();
	}
	connect(this,SIGNAL(SignalConnected()),this,SLOT(SlotlConnected()),Qt::QueuedConnection);
}

PIOAdapter::~PIOAdapter(void)
{
	if(ROutStreamBitData!=NULL){
		delete	[]ROutStreamBitData;
		ROutStreamBitData=NULL;
	}
	if(RInStreamBitData!=NULL){
		delete	[]RInStreamBitData;
		RInStreamBitData=NULL;
	}
	if(MemoryMap.isAttached()==true){
		MemoryMap.detach();
	}
	MemMap	=NULL;
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

bool	PIOAdapter::LoadDefFile(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		PortBitsIn.RemoveAll();
		PortBitsOut.RemoveAll();
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
				}
			}
		}
		if(SendInformation()==true){
			return true;
		}
	}
	return false;
}

int		PIOAdapter::GetBitData(int bitnumber)
{
	return RInStreamBitData[bitnumber];
}
bool	PIOAdapter::SetBitData(int bitnumber ,int data)
{
	ROutStreamBitData[bitnumber]=data;
	return true;
}
int		PIOAdapter::GetBitOutData(int bitnumber)
{
	MemoryMap.lock();
	int	d=MemMap->OUTData[bitnumber];
	MemoryMap.unlock();

	return d;
}

void	PIOAdapter::SlotlConnected()
{
	SendInformation();
}

bool	PIOAdapter::CommGetBitInDataStream(void)
{
	QByteArray	Array;

	short	BitNumbers[1024];
	int	k=0;
	for(PortBit *a=PortBitsIn.GetFirst();a!=NULL;a=a->GetNext()){
		BitNumbers[k]=a->BitNumber;
		k++;
	}
	Array.append((char *)&k,4);
	Array.append((char *)BitNumbers,sizeof(short)*k);

	if(IsConnected()==false){
		ConnectToHost();
	}
	if(IsConnected()==false){
		return false;
	}
	RStreamFlag	=false;
	if(Send(ReqInDataStream,Array)==false)
		return false;
	QElapsedTimer	TM;
	TM.start();
	while(TM.hasExpired(1000)==false && RStreamFlag==false){
		WaitReadyRead(1);
		if(qApp->thread()==QThread::currentThread()){
			QCoreApplication::processEvents();
		}
	}
	if(RStreamFlag==true){
		return true;
	}
	return false;
}
bool	PIOAdapter::CommSetBitOutDataStream(void)
{
	QByteArray	Array;

	short	BitNumbers[1024];
	int	N=0;
	MemoryMap.lock();
	for(PortBit *a=PortBitsOut.GetFirst();a!=NULL;a=a->GetNext()){
		BitNumbers[N]=a->BitNumber;
		ROutStreamBitData[N]=MemMap->OUTData[a->BitNumber];
		N++;
	}
	MemoryMap.unlock();

	Array.append((char *)&N,4);
	Array.append((char *)BitNumbers,sizeof(short)*N);
	Array.append((char *)ROutStreamBitData,N);
	if(IsConnected()==false){
		ConnectToHost();
	}
	if(IsConnected()==false){
		return false;
	}
	RStreamFlag	=false;
	if(Send(SendOutDataStream,Array)==false)
		return false;
	QElapsedTimer	TM;
	TM.start();
	while(TM.hasExpired(1000)==false && RStreamFlag==false){
		WaitReadyRead(1);
		if(qApp->thread()==QThread::currentThread()){
			QCoreApplication::processEvents();
		}
	}
	if(RStreamFlag==true){
		return true;
	}
	return false;
}
bool	PIOAdapter::CommGetBitOutDataStream(void)
{
	QByteArray	Array;

	short	BitNumbers[1024];
	int	k=0;
	for(PortBit *a=PortBitsOut.GetFirst();a!=NULL;a=a->GetNext()){
		BitNumbers[k]=a->BitNumber;
		k++;
	}
	Array.append((char *)&k,4);
	Array.append((char *)BitNumbers,sizeof(short)*k);
	if(IsConnected()==false){
		ConnectToHost();
	}
	if(IsConnected()==false){
		return false;
	}
	RStreamFlag	=false;
	if(Send(ReqOutDataStream,Array)==false)
		return false;
	QElapsedTimer	TM;
	TM.start();
	while(TM.hasExpired(1000)==false && RStreamFlag==false){
		WaitReadyRead(1);
		if(qApp->thread()==QThread::currentThread()){
			QCoreApplication::processEvents();
		}
	}
	if(RStreamFlag==true){
		return true;
	}
	return false;
}

bool	PIOAdapter::SendInformation(void)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);

	int	iMaxBitCountIN	=GetBitCountIn();
	int	iMaxBitCountOUT	=GetBitCountOut();

	int32	BitCountIn	=PortBitsIn.GetCount();
	int32	BitCountOut	=PortBitsOut.GetCount();

	if(ROutStreamBitData!=NULL && iMaxBitCountOUT!=MaxBitCountOUT){
		delete	[]ROutStreamBitData;
		ROutStreamBitData=NULL;
	}
	MaxBitCountOUT=iMaxBitCountOUT;
	if(ROutStreamBitData==NULL){
		ROutStreamBitData=new BYTE [MaxBitCountOUT];
	}

	if(RInStreamBitData!=NULL && iMaxBitCountIN!=MaxBitCountIN){
		delete	[]RInStreamBitData;
		RInStreamBitData=NULL;
	}
	MaxBitCountIN=iMaxBitCountIN;
	if(RInStreamBitData==NULL){
		RInStreamBitData=new BYTE [MaxBitCountIN];
	}

	::Save(&Buff,BitCountIn);
	::Save(&Buff,BitCountOut);
	for(PortBit *a=PortBitsIn.GetFirst();a!=NULL;a=a->GetNext()){
		::Save(&Buff,(int32)a->BitNumber);
		::Save(&Buff,a->BitName);
	}
	for(PortBit *a=PortBitsOut.GetFirst();a!=NULL;a=a->GetNext()){
		::Save(&Buff,(int32)a->BitNumber);
		::Save(&Buff,a->BitName);
	}
	if(IsConnected()==false){
		ConnectToHost();
	}
	if(IsConnected()==false){
		return false;
	}
	FlagAckInformation=false;
	for(int i=0;i<3;i++){
		if(Send(SendInfoData,Buff.buffer())==false)
			return false;
		QElapsedTimer	TM;
		TM.start();
		while(TM.hasExpired(1000)==false && FlagAckInformation==false){
			WaitReadyRead(10);
			if(qApp->thread()==QThread::currentThread()){
				QCoreApplication::processEvents();
			}
		}
		if(FlagAckInformation==true){
			return true;
		}
	}
	return true;
}

void	PIOAdapter::Received(int cmd ,QByteArray &data)
{
	if(cmd==AckSendInfoData){
		FlagAckInformation=true;
	}
	else if(cmd==AckReqInData){
		int	bitNumber=data.at(0);
		int	D		 =data.at(1);
		PortBit	*a=FindInBit(bitNumber);
		if(a!=NULL){
			a->CurrentData=D;
			a->RecievedFlag=true;
		}
	}
	else if(cmd==AckSendOutData){
		int	bitNumber=data.at(0);
		PortBit	*a=FindOutBit(bitNumber);
		if(a!=NULL){
			a->RecievedFlag=true;
		}
	}
	else if(cmd==AckReqOutData){
		int	bitNumber=data.at(0);
		int	D		 =data.at(1);
		PortBit	*a=FindOutBit(bitNumber);
		if(a!=NULL){
			a->CurrentData=D;
			a->RecievedFlag=true;
		}
	}
	else if(cmd==AckReqInDataStream){
		int32	BitNumb;
		char	*fp=data.data();
		memcpy((char *)&BitNumb,fp,sizeof(BitNumb));
		fp+=sizeof(BitNumb);
		memcpy(RInStreamBitData,fp,BitNumb);
		if(MemMap!=NULL){
			int	n=0;
			MemoryMap.lock();
			for(PortBit *a=PortBitsIn.GetFirst();a!=NULL;a=a->GetNext(),n++){
				MemMap->INData[a->BitNumber]=RInStreamBitData[n];
				a->CurrentData	=RInStreamBitData[n];
			}
			MemoryMap.unlock();
		}
		RStreamFlag=true;
	}
	else if(cmd==AckSendOutDataStream){
		RStreamFlag=true;
	}
	else if(cmd==AckReqOutDataStream){
		int32	BitNumb;
		char	*fp=data.data();
		memcpy((char *)&BitNumb,fp,sizeof(BitNumb));
		fp+=sizeof(BitNumb);
		memcpy(ROutStreamBitData,fp,BitNumb);
		if(MemMap!=NULL){
			int	n=0;
			MemoryMap.lock();
			for(PortBit *a=PortBitsOut.GetFirst();a!=NULL;a=a->GetNext(),n++){
				MemMap->OUTData[a->BitNumber]=ROutStreamBitData[n];
			}
			MemoryMap.unlock();
		}
		RStreamFlag=true;
	}
}

PortBit	*PIOAdapter::FindInBit(int BitNumber)
{
	for(PortBit *a=PortBitsIn.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitNumber==BitNumber)
			return a;
	}
	return NULL;
}

PortBit	*PIOAdapter::FindOutBit(int BitNumber)
{
	for(PortBit *a=PortBitsOut.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitNumber==BitNumber)
			return a;
	}
	return NULL;
}

int		PIOAdapter::GetBitCountIn(void)
{
	int	MaxBit=-1;
	for(PortBit *a=PortBitsIn.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitNumber>MaxBit){
			MaxBit=a->BitNumber;
		}
	}
	return MaxBit+1;
}

int		PIOAdapter::GetBitCountOut(void)
{
	int	MaxBit=-1;
	for(PortBit *a=PortBitsOut.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitNumber>MaxBit){
			MaxBit=a->BitNumber;
		}
	}
	return MaxBit+1;
}

int		PIOAdapter::GetAckCommand(void)
{
	MemoryMap.lock();
	int	ret=MemMap->AckCommand;
	MemoryMap.unlock();
	return ret;
}
void	PIOAdapter::MemMapOperator(void)
{
	MemoryMap.lock();
	if(MemMap!=NULL){
		if(MemMap->ReqCommand==OpenPIO){
			MemMap->ReqCommand=0;
			MemMap->AckCommand=AckPIO;
			MemoryMap.unlock();
			while(GetAckCommand()!=0){
				GSleep(1);
			}
			return;
		}
		else if(MemMap->ReqCommand==PIOReqLoadDefFile){
			MemMap->ReqCommand=0;
			QString	FileName=(char *)MemMap->ReqData;
			if(LoadDefFile(FileName)==true){
				MemMap->AckCommand=AckPIO;
				MemoryMap.unlock();
				while(GetAckCommand()!=0){
					GSleep(1);
				}
				return;
			}
			MemMap->AckCommand=NackPIO;
		}
		else if(MemMap->ReqCommand==SendOutDataStream){
			MemMap->ReqCommand=0;
			if(CommSetBitOutDataStream()==true){
				MemMap->AckCommand=AckPIO;
				MemoryMap.unlock();
				while(GetAckCommand()!=0){
					GSleep(10);
				}
				return;
			}
			MemMap->AckCommand=NackPIO;
		}
		else if(MemMap->ReqCommand==ReqOutDataStream){
			MemMap->ReqCommand=0;
			if(CommGetBitOutDataStream()==true){
				MemMap->AckCommand=AckPIO;
				MemoryMap.unlock();
				while(GetAckCommand()!=0){
					GSleep(10);
				}
				return;
			}
			MemMap->AckCommand=NackPIO;
		}
		else if(MemMap->ReqCommand==ReqPIOINBitCount){
			MemMap->ReqCommand=0;
			MemMap->AckIndex=GetBitCountIn();
			MemMap->AckCommand=AckPIO;
			MemoryMap.unlock();
			while(GetAckCommand()!=0){
				GSleep(10);
			}
			return;
		}
		else if(MemMap->ReqCommand==ReqPIOOUTBitCount){
			MemMap->ReqCommand=0;
			MemMap->AckIndex=GetBitCountOut();
			MemMap->AckCommand=AckPIO;
			MemoryMap.unlock();
			while(GetAckCommand()!=0){
				GSleep(10);
			}
			return;
		}
	}
	MemoryMap.unlock();
}