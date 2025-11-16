#include "XVirtualPIOServer.h"
#include "XGeneralFunc.h"


AllocatedClient::AllocatedClient(PIOServer *parent,QTcpSocket *sv)
	:PIOSocket(parent,sv),Parent(parent)
{
	if(sv!=NULL){
		ClientIP		=sv->peerAddress ().toString();
		ClientPortNumber=sv->peerPort();
	}
	else{
		ClientIP			=/**/"DirectAccess";
		ClientPortNumber	=-1;
	}
}

int	AllocatedClient::GetOutData(const QString &BitName)
{
	for(BindedIOBit *a=Parent->IOBitsToShow.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitOut!=NULL && a->BitOut->BitPoint!=NULL 
		&& a->BitOut->BitPoint->BitName==BitName){
			return a->BitOut->BitPoint->CurrentOutput;
		}
	}
	return -1;
}

void	AllocatedClient::Received(int cmd ,QByteArray &data)
{
	if(cmd==SendInfoData){
		BitPorts.RemoveAll();
		QBuffer	Buff(&data);
		Buff.open(QIODevice::ReadOnly);
		int32	iInBitCount;
		if(::Load(&Buff,iInBitCount)==false)
			return;
		int32	iOutBitCount;
		if(::Load(&Buff,iOutBitCount)==false)
			return;
		for(int i=0;i<iInBitCount;i++){
			int32	iBitNumber;
			if(::Load(&Buff,iBitNumber)==false)
				return;
			QString	iBitName;
			if(::Load(&Buff,iBitName)==false)
				return;
			ClientBitPort	*a=new ClientBitPort();
			a->BitNumber	=iBitNumber;
			a->BitName		=iBitName;
			a->Output		=false;
			a->CurrentOutput=0;
			BitPorts.AppendList(a);
		}
		for(int i=0;i<iOutBitCount;i++){
			int32	iBitNumber;
			if(::Load(&Buff,iBitNumber)==false)
				return;
			QString	iBitName;
			if(::Load(&Buff,iBitName)==false)
				return;
			ClientBitPort	*a=new ClientBitPort();
			a->BitNumber	=iBitNumber;
			a->BitName		=iBitName;
			a->Output		=true;
			a->CurrentOutput=0;
			BitPorts.AppendList(a);
		}
		Parent->BindData();
		QByteArray	Array;
		Send(AckSendInfoData ,Array);
	}
	else if(cmd==ReqInData){
		int	iBitNumber=data.at(0);
		ClientBitPort	*a=FindInBit(iBitNumber);
		if(a!=NULL){
			ClientBitPort	*p=Parent->SearchOutputBit(a->BitName);
			if(p!=NULL){
				QByteArray	Array;
				Array.append((char)iBitNumber);
				Array.append((char)p->CurrentOutput);
				Send(AckReqInData ,Array);
			}
			else{
				QByteArray	Array;
				Array.append((char)iBitNumber);
				Array.append((char)0);
				Send(AckReqInData ,Array);
			}
		}
	}
	else if(cmd==SendOutData){
		int	iBitNumber	=data.at(0);
		int	iBitData	=data.at(1);
		ClientBitPort	*a=FindOutBit(iBitNumber);
		if(a!=NULL){
			a->CurrentOutput=iBitData;
			QByteArray	Array;
			Array.append((char)iBitNumber);
			Send(AckSendOutData ,Array);
		}
	}
	else if(cmd==ReqOutData){
		int	iBitNumber	=data.at(0);
		ClientBitPort	*a=FindOutBit(iBitNumber);
		if(a!=NULL){
			QByteArray	Array;
			Array.append((char)iBitNumber);
			Array.append((char)a->CurrentOutput);
			Send(AckReqOutData ,Array);
		}
	}
	else if(cmd==ReqInDataStream){
		int32	BitNumb;
		char	*fp=data.data();
		memcpy(&BitNumb,fp,4);
		fp+=4;
		short	BitNumbers[1024];
		memcpy(BitNumbers,fp,sizeof(short)*BitNumb);

		BYTE	BitData[1024];
		for(int k=0;k<BitNumb;k++){
			BitData[k]=0xFF;
			for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Output==false && a->BitNumber==BitNumbers[k]){
					BitData[k]=GetOutData(a->BitName);
				}
			}
		}

		QByteArray	Array;
		Array.append((char *)&BitNumb,4);
		Array.append((char *)BitData,sizeof(BitData[0])*BitNumb);
		Send(AckReqInDataStream ,Array);
	}
	else if(cmd==SendOutDataStream){
		int	BitNumb;
		char	*fp=data.data();
		memcpy(&BitNumb,fp,4);
		fp+=4;
		short	BitNumbers[1024];
		BYTE	BitData[1024];
		memcpy(BitNumbers,fp,sizeof(short)*BitNumb);
		fp+=sizeof(short)*BitNumb;
		memcpy(BitData,fp,sizeof(BitData[0])*BitNumb);

		for(int k=0;k<BitNumb;k++){
			for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Output==true && a->BitNumber==BitNumbers[k]){
					a->CurrentOutput=BitData[k];
				}
			}
		}

		QByteArray	Array;
		Send(AckSendOutDataStream ,Array);
	}
	else if(cmd==ReqOutDataStream){
		int32	BitNumb;
		char	*fp=data.data();
		memcpy(&BitNumb,fp,4);
		fp+=4;
		short	BitNumbers[1024];
		memcpy(BitNumbers,fp,sizeof(short)*BitNumb);

		BYTE	BitData[1024];
		for(int k=0;k<BitNumb;k++){
			BitData[k]=0xFF;
			for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Output==true && a->BitNumber==BitNumbers[k]){
					BitData[k]=a->CurrentOutput;
				}
			}
		}

		QByteArray	Array;
		Array.append((char *)&BitNumb,4);
		Array.append((char *)BitData,sizeof(BitData[0])*BitNumb);
		Send(AckReqOutDataStream ,Array);
	}
}

void	AllocatedClient::SlotDisconnected()
{
	Parent->RemoveList(this);
	Parent->BindData();
	PIOSocket::SlotDisconnected();
	deleteLater();
}

int		AllocatedClient::GetBitCountIn(void)
{
	int	Count=0;
	for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Output==false)
			Count++;
	}
	return Count;
}

int		AllocatedClient::GetBitCountOut(void)
{
	int	Count=0;
	for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Output==true)
			Count++;
	}
	return Count;
}

ClientBitPort	*AllocatedClient::FindInBit(int BitNumber)
{
	for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitNumber==BitNumber && a->Output==false)
			return a;
	}
	return NULL;
}

ClientBitPort	*AllocatedClient::FindOutBit(int BitNumber)
{
	for(ClientBitPort *a=BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitNumber==BitNumber && a->Output==true)
			return a;
	}
	return NULL;
}

PIOServer::PIOServer(QObject *parent)
	:QTcpServer(parent)
{
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}

void	PIOServer::StartServer(int PortNumber)
{
	listen(QHostAddress::Any,PortNumber);
}
void	PIOServer::DeleteDirectAccess(void)
{
	Again:;
	for(AllocatedClient *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ClientPortNumber<0){
			RemoveList(a);
			delete	a;
			goto	Again;
		}
	}
}

ClientBitPort	*PIOServer::SearchOutputBit(const QString &BitName)
{
	for(AllocatedClient *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(ClientBitPort *b=a->BitPorts.GetFirst();b!=NULL;b=b->GetNext()){
			if(b->Output==true && b->BitName==BitName){
				return b;
			}
		}
	}
	return NULL;
}

BindedIOBit::BindedIOBit(void)
{	
	BitOut	=NULL;
	Duplicated=false;
}

BindedIOBit::~BindedIOBit(void)
{
	delete	BitOut;
	BitOut=NULL;
}

BindedIOBit	*BindedIOBitContainer::FindOutBit(const QString &BitName)
{
	for(BindedIOBit *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->BitOut!=NULL && a->BitOut->BitPoint->BitName==BitName){
			return a;
		}
	}
	return NULL;
}

void	PIOServer::BindData(void)
{
	IOBitsToShow.RemoveAll();
	for(AllocatedClient *p=GetFirst();p!=NULL;p=p->GetNext()){
		for(ClientBitPort *a=p->BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Output==true){
				BindedIOBit	*s=IOBitsToShow.FindOutBit(a->BitName);
				if(s!=NULL){
					s->Duplicated=true;
					BindedIOBit	*t=new BindedIOBit();
					t->BitOut	=new BindedBit();
					t->BitOut->BitPoint		=a;
					t->BitOut->ClientPoint	=p;
					t->Duplicated=true;
					IOBitsToShow.AppendList(t);
				}
				else{
					BindedIOBit	*t=new BindedIOBit();
					t->BitOut	=new BindedBit();
					t->BitOut->BitPoint		=a;
					t->BitOut->ClientPoint	=p;
					t->Duplicated=false;
					IOBitsToShow.AppendList(t);
				}
			}
		}
	}
	for(AllocatedClient *p=GetFirst();p!=NULL;p=p->GetNext()){
		for(ClientBitPort *a=p->BitPorts.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Output==false){
				BindedIOBit	*s=IOBitsToShow.FindOutBit(a->BitName);
				if(s!=NULL){
					BindedBit	*k=new BindedBit();
					k->BitPoint		=a;
					k->ClientPoint	=p;
					s->BitIn.AppendList(k);
				}
				else{
					BindedBit	*k=new BindedBit();
					k->BitPoint		=a;
					k->ClientPoint	=p;
					BindedIOBit	*t=new BindedIOBit();
					t->BitIn.AppendList(k);
					IOBitsToShow.AppendList(t);
				}
			}
		}
	}
	emit	SignalStructureChanged();
}

void PIOServer::SlotNewConnection ()
{
	QTcpSocket *p=nextPendingConnection ();
	AllocatedClient	*a=new AllocatedClient(this,p);
	a->HandleNumber=GetCount()-1;
	AppendList(a);
}
AllocatedClient	*PIOServer::GetAllocatedClient(int handle)
{
	for(AllocatedClient *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->HandleNumber==handle)
			return a;
	}
	return NULL;
}