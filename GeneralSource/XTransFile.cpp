#include "XTypeDef.h"
#include "XTransFile.h"
#include "XGeneralFunc.h"
#include "swap.h"

TrFileSocket::TrFileSocket(TrFile *parent)
{
	Parent=parent;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)));//,Qt::QueuedConnection);
}

void	TrFileSocket::SlotReceived(int)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		BYTE	Cmd=*p;
		p++;
		
		if(Cmd==CMD_Constructor){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckID);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_bytesAvailable){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,RetBytesAvailable);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_bytesToWrite){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,RetBytesAvailable);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_canReadLine){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_close){
			RootCmd=Cmd;
			Ack=true3;
		}
		else if(Cmd==CMD_isSequential){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_open){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_pos){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckPos);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_reset){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_seek){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_size){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckSize);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_waitForBytesWritten){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_waitForReadyRead){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_readData){
			bool3	RetValue;
			if(p!=NULL){
				int	RSize;
				p=R->GetPointer(p,RSize);
				AckSize=RSize;
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			if(RetValue==true3){
				memcpy(ReadPointer,p,AckSize);
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_readLineData){
			bool3	RetValue;
			if(p!=NULL){
				int	RSize;
				p=R->GetPointer(p,RSize);
				AckSize=RSize;
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			if(RetValue==true3){
				memcpy(ReadPointer,p,AckSize);
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_writeData){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,WAckSize);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_atEnd){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_remove){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_rename){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_resize){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_exists){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_filename){
			QBuffer ret;
			p=R->GetPointer(p ,ret);
			ret.open(QIODevice::ReadWrite);

			bool3	RetValue;
			if(::Load(&ret,AckFileName)==true){
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		else if(Cmd==CMD_flush){
			bool3	RetValue;
			if(p!=NULL){
				p=R->GetPointer(p,AckBool);
				RetValue=true3;
			}
			else{
				RetValue=false3;
			}
			RootCmd=Cmd;
			Ack=RetValue;
		}
		delete	R;
	}
}
//====================================================

TrFile::TrFile(const QString &FileName
			, const QString &TransFileHost
			, int TransFilePort)
			:WFifo(this)
{
	Sock=new TrFileSocket(this);
	Sock->Set(NULL, TransFileHost ,TransFilePort);
	if(Sock->StartConnect()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_Constructor;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,FileName)==false){
			return;
		}
		QByteArray	Data=Buff.buffer();
		AccessSock.lock();
		if(Sock->TxData(Cmd,&Data)==false){
			AccessSock.unlock();
			return;
		}
		while(Sock->RootCmd!=CMD_Constructor){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		AccessSock.unlock();
	}
}

TrFile::~TrFile(void)
{
	WFifo.ForceWrite();
	delete	Sock;
	Sock=NULL;
}

qint64 TrFile::bytesAvailable () const
{
	WFifo.ForceWrite();
	AccessSock.lock();
	Sock->FlushRead();
	qint64	Ret=0;
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_bytesAvailable;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return 0;
		}
		while(Sock->RootCmd!=CMD_bytesAvailable){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->RetBytesAvailable;
	}
	AccessSock.unlock();
	return Ret;
}
qint64 TrFile::bytesToWrite () const
{
	WFifo.ForceWrite();
	AccessSock.lock();
	Sock->FlushRead();
	qint64	Ret=0;
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_bytesToWrite;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return 0;
		}
		while(Sock->RootCmd!=CMD_bytesToWrite){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->RetBytesAvailable;
	}
	AccessSock.unlock();
	return Ret;
}
	
bool TrFile::canReadLine () const
{
	WFifo.ForceWrite();
	AccessSock.lock();
	Sock->FlushRead();
	bool	Ret=false;
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_canReadLine;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_canReadLine){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}
void TrFile::close ()
{
	WFifo.ForceWrite();
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_close;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return;
		}
		while(Sock->RootCmd!=CMD_close){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
	}
	AccessSock.unlock();
}
bool TrFile::isSequential () const
{
	WFifo.ForceWrite();
	AccessSock.lock();
	Sock->FlushRead();
	bool	Ret=false;
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_isSequential;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_isSequential){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret= Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}
bool TrFile::open ( OpenMode mode )
{
	WFifo.ForceWrite();
	QIODevice::open(mode);
	AccessSock.lock();
	Sock->FlushRead();
	bool	Ret=false;
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_open;

		int32	Mode=(int32)mode;
		if(Sock->TxData(Cmd,Mode)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_open){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}
/*
qint64 TrFile::pos () const
{
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_pos;

		if(Sock->TxData(Cmd)==false)
			return 0;
		while(Sock->RootCmd!=CMD_pos){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		return Sock->AckPos;
	}
	return 0;
}
*/
bool TrFile::reset ()
{
	WFifo.ForceWrite();
	bool	Ret=false;
	QIODevice::reset ();
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_reset;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_reset){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}
/*
bool TrFile::seek ( qint64 pos )
{
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_seek;

		if(Sock->TxData(Cmd,pos)==false)
			return false;
		while(Sock->RootCmd!=CMD_seek){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		return Sock->AckBool;
	}
	return false;
}
*/
qint64 TrFile::size () const
{
	WFifo.ForceWrite();
	qint64	Ret=0;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_size;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return 0;
		}
		while(Sock->RootCmd!=CMD_size){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckSize;
	}
	AccessSock.unlock();
	return Ret;
}
bool TrFile::waitForBytesWritten ( int msecs )
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_waitForBytesWritten;

		if(Sock->TxData(Cmd,msecs)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_waitForBytesWritten){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}
bool TrFile::waitForReadyRead ( int msecs )
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_waitForReadyRead;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,msecs)==false){
			AccessSock.unlock();
			return false;
		}
		QByteArray	Data=Buff.buffer();
		if(Sock->TxData(Cmd,&Data)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_waitForReadyRead){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}

qint64 TrFile::readData ( char * data, qint64 maxSize )
{
	WFifo.ForceWrite();
	qint64	Ret=-1;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_readData;
		Sock->ReadPointer=data;

		if(Sock->TxData(Cmd,maxSize)==false){
			AccessSock.unlock();
			return -1;
		}
		while(Sock->RootCmd!=CMD_readData){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckSize;
	}
	AccessSock.unlock();
	return Ret;
}
qint64 TrFile::readLineData ( char * data, qint64 maxSize )
{
	WFifo.ForceWrite();
	qint64	Ret=-1;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_readLineData;
		Sock->ReadPointer=data;

		if(Sock->TxData(Cmd,maxSize)==false){
			AccessSock.unlock();
			return -1;
		}
		while(Sock->RootCmd!=CMD_readLineData){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckSize;
	}
	AccessSock.unlock();
	return Ret;
}
qint64 TrFile::writeData ( const char * data, qint64 maxSize )
{
	/*
	qint64	Ret=-1;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_writeData;

		if(Sock->TxData(Cmd,(BYTE *)data,(int)maxSize)==false){
			AccessSock.unlock();
			return -1;
		}
		while(Sock->RootCmd!=CMD_writeData){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckSize;
	}
	AccessSock.unlock();
	return Ret;
	*/
	if(WFifo.GetCurrentSize()+maxSize>=SWFifoSize){
		WFifo.ForceWrite();
	}
	if(maxSize>=SWFifoSize){
		RWriteData((char *)data,maxSize);
	}
	else{
		WFifo.Push((BYTE *)data,maxSize);
	}
	return maxSize;
}

bool TrFile::atEnd () const
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_atEnd;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_atEnd){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}

bool TrFile::remove ()
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_remove;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_remove){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}

bool TrFile::rename ( const QString & newName )
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_rename;

		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		if(::Save(&Buff,newName)==false){
			AccessSock.unlock();
			return false;
		}
		QByteArray	Data=Buff.buffer();
		if(Sock->TxData(Cmd,&Data)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_rename){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}

bool TrFile::resize ( qint64 sz )
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_resize;

		if(Sock->TxData(Cmd,sz)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_resize){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}

bool TrFile::exists () const
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_exists;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_exists){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}

QString TrFile::fileName () const
{
	WFifo.ForceWrite();
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_filename;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return /**/"";
		}
		while(Sock->RootCmd!=CMD_filename){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		QString	s=Sock->AckFileName;
		AccessSock.unlock();
		return s;
	}
	AccessSock.unlock();
	return "";
}

bool TrFile::flush ()
{
	WFifo.ForceWrite();
	bool	Ret=false;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_flush;

		if(Sock->TxData(Cmd)==false){
			AccessSock.unlock();
			return false;
		}
		while(Sock->RootCmd!=CMD_flush){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->AckBool;
	}
	AccessSock.unlock();
	return Ret;
}


qint64	TrFile::RWriteData(char *Point ,int Size)
{
	qint64	Ret=-1;
	AccessSock.lock();
	Sock->FlushRead();
	if(Sock->IsConnected()==true){
		Sock->RootCmd=0;
		BYTE	Cmd=CMD_writeData;

		if(Sock->TxData(Cmd,(BYTE *)Point,(int)Size)==false){
			AccessSock.unlock();
			return -1;
		}
		while(Sock->RootCmd!=CMD_writeData){
			Sock->WaitReadyRead(WaitTimeMilisec);
		}
		Ret=Sock->WAckSize;
	}
	AccessSock.unlock();
	return Ret;
}

SWFifoContainer::SWFifoContainer(TrFile *parent)
	:Parent(parent)
{
	Buffer=new BYTE[SWFifoSize];
	CurrentPointer=0;
}
SWFifoContainer::SWFifoContainer(const SWFifoContainer &src)
	:Parent(src.Parent)
{
	Buffer=new BYTE[SWFifoSize];
	memcpy(Buffer,src.Buffer,SWFifoSize);
	CurrentPointer=src.CurrentPointer;
}
SWFifoContainer::~SWFifoContainer(void)
{
	delete	[]Buffer;
	Buffer=NULL;
	CurrentPointer=0;
}

SWFifoContainer &SWFifoContainer::operator=(const SWFifoContainer &src)
{
	memcpy(Buffer,src.Buffer,SWFifoSize);
	CurrentPointer=src.CurrentPointer;
	return *this;
}

void	SWFifoContainer::ForceWrite(void)
{
	if(CurrentPointer!=0){
		Parent->RWriteData((char *)Buffer,CurrentPointer);
		CurrentPointer=0;
	}
}


int		SWFifoContainer::Push(BYTE *s ,int size)
{
	memcpy(&Buffer[CurrentPointer],s,size);
	CurrentPointer+=size;
	return CurrentPointer;
}

