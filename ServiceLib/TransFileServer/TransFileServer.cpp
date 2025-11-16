#include "TransFileServer.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"
#include "XTransFile.h"

TrFileApp::TrFileApp(const QString &filename)
	:QFile(filename)
{
}

qint64 TrFileApp::bytesAvailable () const
{
	return QFile::bytesAvailable ();
}
qint64 TrFileApp::bytesToWrite () const
	{
	return QFile::bytesToWrite ();
}
	
bool TrFileApp::canReadLine () const
{
	return QFile::canReadLine ();
}

void TrFileApp::close ()
{
	QFile::close ();
}

bool TrFileApp::isSequential () const
{
	return QFile::isSequential ();
}

bool TrFileApp::open ( OpenMode mode )
{
	return QFile::open (mode);
}

qint64 TrFileApp::pos () const
{
	return QFile::pos ();
}

bool TrFileApp::reset ()
{
	return QFile::reset ();
}

bool TrFileApp::seek ( qint64 pos )
{
	return QFile::seek (pos);
}

qint64 TrFileApp::size () const
{
	return QFile::size ();
}

bool TrFileApp::waitForBytesWritten ( int msecs )
{
	return QFile::waitForBytesWritten ( msecs );
}

bool TrFileApp::waitForReadyRead ( int msecs )
{
	return QFile::waitForReadyRead ( msecs );
}


qint64 TrFileApp::readData ( char * data, qint64 maxSize )
{
	return QFile::readData ( data, maxSize );
}

qint64 TrFileApp::readLineData ( char * data, qint64 maxSize )
{
	return QFile::readLineData ( data, maxSize );
}

qint64 TrFileApp::writeData ( const char * data, qint64 maxSize )
{
	return QFile::writeData ( data, maxSize );
}

//============================================================

TrAppSocket::TrAppSocket(TrAppServer *parent)
	:Parent(parent),WFifo(this,parent)
{
	ID=0;
	RealFile	=NULL;
	CachedFile	=NULL;
	LogTurn		=0;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalPutLog(const QString &,int ,const QString &,const QString &)),parent,SLOT(SlotPutLog(const QString &,int ,const QString &,const QString &)),Qt::QueuedConnection);
	WFifo.start();
}

TrAppSocket::~TrAppSocket(void)
{
	while(WFifo.Exist()==true){
		GSleep(100);
	}
	WFifo.Terminated=true;
	WFifo.wait(1000);

	if(RealFile!=NULL){
		delete	RealFile;
		RealFile=NULL;
	}
	if(CachedFile!=NULL){
		delete	CachedFile;
		CachedFile=NULL;
	}
}

void	TrAppSocket::SlotReceived(int)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		BYTE	Cmd=*p;
		p++;

		if(Cmd==CMD_Constructor){
			QBuffer Buff;
			p=R->GetPointer(p ,Buff);
			Buff.open(QIODevice::ReadWrite);

			if(::Load(&Buff,RealFileName)==false){
				goto	NextPoint;
			}
			ID=Parent->GetMaxID();

			if(RealFile!=NULL){
				delete	RealFile;
			}
			RealFile	=new TrFileApp(RealFileName);
			QFileInfo	RealFInfo(RealFileName);
			CachedFileName=Parent->GetChachePath()+QDir::separator()+RealFInfo.fileName();
			if(CachedFile!=NULL){
				delete	CachedFile;
				CachedFile=NULL;
			}
			QFileInfo	CacheFInfo(CachedFileName);
			CachedFile	=new TrFileApp(CachedFileName);

			if(RealFInfo.path().toUpper()==CacheFInfo.path().toUpper()){
				delete	RealFile;
				RealFile=NULL;
			}

			if(RealFile!=NULL){
				RealExist	=RealFile->exists();
			}
			else{
				RealExist	=true;
			}
			CacheExist	=CachedFile->exists();
			SameAsCache	=false;
			if(RealExist==true && CacheExist==true){
				QFileInfo	RealInfo(RealFileName);
				QFileInfo	CacheInfo(CachedFileName);
				QDateTime	RTime=RealInfo.lastModified();
				QDateTime	CTime=CacheInfo.lastModified();
				int	d=RTime.secsTo(CTime);
				if(-10<=d && d<10 && (RealFile==NULL || RealFile->size()==CachedFile->size())){
					SameAsCache=true;
				}
			}

			if(TxData(Cmd,ID)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_Constructor" ,/**/"");
		}
		else if(Cmd==CMD_bytesAvailable){
			qint64	bytesSize;
			if(SameAsCache==true){
				bytesSize=CachedFile->bytesAvailable();
			}
			else{
				if(RealExist!=NULL){
					bytesSize=RealFile->bytesAvailable();
				}
				else{
					bytesSize=CachedFile->bytesAvailable();
				}
			}

			if(TxData(Cmd,bytesSize)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_bytesAvailable" ,QString::number(bytesSize));
		}
		else if(Cmd==CMD_bytesToWrite){
			qint64	bytesSize=(RealFile!=NULL)?RealFile->bytesToWrite():CachedFile->bytesToWrite();

			if(TxData(Cmd,bytesSize)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_bytesToWrite" ,QString::number(bytesSize));
		}
		else if(Cmd==CMD_canReadLine){
			bool	BoolCanReadLine;
			if(SameAsCache==true){
				BoolCanReadLine=CachedFile->canReadLine();
			}
			else{
				if(RealFile!=NULL){
					BoolCanReadLine=RealFile->canReadLine();
				}
				else{
					BoolCanReadLine=CachedFile->canReadLine();
				}
			}

			if(TxData(Cmd,BoolCanReadLine)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_canReadLine" ,(BoolCanReadLine==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_close){
			if(CachedFile->isOpen()==true)
				CachedFile->close();
			if(RealFile!=NULL && RealFile->isOpen()==true)
				RealFile->close();

			if(TxData(Cmd)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_close" ,/**/"");
		}
		else if(Cmd==CMD_isSequential){
			bool	BoolIsSequential;
			if(SameAsCache==true){
				BoolIsSequential=CachedFile->isSequential();
			}
			else{
				if(RealFile!=NULL){
					BoolIsSequential=RealFile->isSequential();
				}
				else{
					BoolIsSequential=CachedFile->isSequential();
				}
			}

			if(TxData(Cmd,BoolIsSequential)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_isSequential" ,(BoolIsSequential==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_open){
			int32	Mode;
			p=R->GetPointer(p,Mode);

			QIODevice::OpenMode	mode=(QIODevice::OpenMode)Mode;
			bool	RetValue;
			if(SameAsCache==true){
				if(mode==QIODevice::ReadOnly){
					RetValue=CachedFile->open(mode);
				}
				else{
					if(RealFile!=NULL){
						bool	RetValue1=CachedFile->open(mode);
						bool	RetValue2=RealFile->open(mode);
						if(RetValue1==true && RetValue2==true){
							RetValue=true;
						}
						else{
							RetValue=false;
						}
					}
					else{
						RetValue=CachedFile->open(mode);
					}
				}
			}
			else{
				if(RealExist==false && mode==QIODevice::ReadOnly){
					RetValue=false;
				}
				else{
					if(RealFile!=NULL){
						bool	RetValue1=CachedFile->open(QIODevice::ReadWrite);
						bool	RetValue2=RealFile->open(mode);
						if(RetValue1==true && RetValue2==true){
							RetValue=true;
						}
						else{
							RetValue=false;
						}
					}
					else{
						RetValue=false;
					}
				}
			}

			if(TxData(Cmd,RetValue)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_open" ,(RetValue==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_pos){
			qint64	Pos;
			if(SameAsCache==true){
				Pos=CachedFile->pos();
			}
			else{
				if(RealFile!=NULL){
					Pos=RealFile->pos();
				}
				else{
					Pos=CachedFile->pos();
				}
			}

			if(TxData(Cmd,Pos)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_pos" ,QString::number(Pos));
		}
		else if(Cmd==CMD_reset){
			bool	BoolReset;
			if(SameAsCache==true){
				BoolReset=CachedFile->reset();
			}
			else{
				if(RealFile!=NULL){
					bool	BoolReset1=CachedFile->reset();
					bool	BoolReset2=RealFile->reset();
					if(BoolReset1==true && BoolReset2==true){
						BoolReset=true;
					}
					else{
						BoolReset=false;
					}
				}
				else{
					BoolReset=false;
				}
			}

			if(TxData(Cmd,BoolReset)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_reset" ,(BoolReset==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_seek){
			qint64	Pos;
			p=R->GetPointer(p,Pos);
			bool	BoolReset;
			if(SameAsCache==true){
				BoolReset=CachedFile->seek(Pos);
			}
			else{
				if(RealFile!=NULL){
					bool	BoolReset1=CachedFile->seek(Pos);
					bool	BoolReset2=RealFile->seek(Pos);
					if(BoolReset1==true && BoolReset2==true){
						BoolReset=true;
					}
					else{
						BoolReset=false;
					}
				}
				else{
					BoolReset=false;
				}
			}

			if(TxData(Cmd,BoolReset)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_seek" ,(BoolReset==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_size){
			qint64	Sz;
			if(SameAsCache==true){
				Sz=CachedFile->size();
			}
			else{
				if(RealFile!=NULL){
					Sz=RealFile->size();
				}
				else{
					Sz=CachedFile->size();
				}
			}

			if(TxData(Cmd,Sz)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_size" ,QString::number(Sz));
		}
		else if(Cmd==CMD_waitForBytesWritten){
			int		msec;
			p=R->GetPointer(p,msec);

			bool	BoolRet;

			if(RealFile!=NULL){
				bool	BoolRet1=CachedFile->waitForBytesWritten(msec);
				bool	BoolRet2=RealFile->waitForBytesWritten(msec);
				if(BoolRet1==true && BoolRet2==true){
					BoolRet=true;
				}
				else{
					BoolRet=false;
				}
			}
			else{
				BoolRet=CachedFile->waitForBytesWritten(msec);
			}

			if(TxData(Cmd,BoolRet)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_waitForBytesWritten" ,(BoolRet==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_waitForReadyRead){
			int		msec;
			p=R->GetPointer(p,msec);

			bool	BoolRet;
			if(SameAsCache==true){
				BoolRet=CachedFile->waitForReadyRead(msec);
			}
			else{
				if(RealFile!=NULL){
					bool	BoolRet1=CachedFile->waitForReadyRead(msec);
					bool	BoolRet2=RealFile->waitForReadyRead(msec);
					if(BoolRet1==true && BoolRet2==true){
						BoolRet=true;
					}
					else{
						BoolRet=false;
					}
				}
				else{
					BoolRet=CachedFile->waitForReadyRead(msec);
				}
			}

			if(TxData(Cmd,BoolRet)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_waitForReadyRead" ,(BoolRet==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_readData){
			qint64		maxSize;
			qint64		RetSize;
			p=R->GetPointer(p,maxSize);

			const	int	BuffSize=20000;
			char	DataBuff[BuffSize];
			char	*Buff;
			if(maxSize<BuffSize){
				Buff=DataBuff;
			}
			else{
				Buff=new char[maxSize];
			}
			if(SameAsCache==true || RealFile==NULL){
				RetSize=CachedFile->readData(Buff,maxSize);
			}
			else{
				int	pos=RealFile->pos();
				QIODevice::OpenMode	RMode=RealFile->openMode();
				QIODevice::OpenMode	CMode=CachedFile->openMode();
				bool	ROpened=false;
				bool	COpened=false;
				if(RealFile->isOpen()==true){
					RealFile->close();
					ROpened=true;
				}
				if(CachedFile->isOpen()==true){
					CachedFile->close();
					COpened=true;
				}
				::MTCopyFile(RealFileName ,CachedFileName ,false);
				if(ROpened==true){
					RealFile->open(RMode);
					RealFile->seek(pos);
				}
				if(COpened==true){
					CachedFile->open(CMode);
					CachedFile->seek(pos);
				}
				else{
					CachedFile->open(RMode);
					CachedFile->seek(pos);
				}
				RetSize=CachedFile->readData(Buff,maxSize);
				if(RealFile->isOpen()==true){
					RealFile->seek(pos+RetSize);
				}
				SameAsCache=true;
				CacheExist=true;
			}
			/*
			QBuffer		rplyBuff;
			rplyBuff.open(QIODevice::WriteOnly);
			if(::Save(&rplyBuff,Cmd)==false)
				goto	NextPoint;
			if(::Save(&rplyBuff,RetSize)==false)
				goto	NextPoint;
			rplyBuff.write(Buff,RetSize);
			QByteArray	Data=rplyBuff.buffer();
			if(TxData(&Data)==false)
				goto	NextPoint;
			*/


			if(TxData(Cmd,(BYTE *)Buff,(int)RetSize)==false)
				goto	NextPoint;

			if(Buff!=DataBuff){
				delete	[]Buff;
			}
			PutLog(ID ,"CMD_readData" ,QString::number(RetSize));
		}
		else if(Cmd==CMD_readLineData){
			qint64		maxSize;
			qint64		RetSize;
			p=R->GetPointer(p,maxSize);

			const	int	BuffSize=20000;
			char	DataBuff[BuffSize];
			char	*MemBuff;
			if(maxSize<BuffSize){
				MemBuff=DataBuff;
			}
			else{
				MemBuff=new char[maxSize];
			}
			if(SameAsCache==true || RealFile==NULL){
				RetSize=CachedFile->readLineData(MemBuff,maxSize);
			}
			else{
				int	pos=RealFile->pos();
				QIODevice::OpenMode	RMode=RealFile->openMode();
				QIODevice::OpenMode	CMode=CachedFile->openMode();
				bool	ROpened=false;
				bool	COpened=false;
				if(RealFile->isOpen()==true){
					RealFile->close();
					ROpened=true;
				}
				if(CachedFile->isOpen()==true){
					CachedFile->close();
					COpened=true;
				}
				::MTCopyFile(RealFileName ,CachedFileName ,false);
				if(ROpened==true){
					RealFile->open(RMode);
					RealFile->seek(pos);
				}
				if(COpened==true){
					CachedFile->open(CMode);
					CachedFile->seek(pos);
				}
				else{
					CachedFile->open(RMode);
					CachedFile->seek(pos);
				}
				RetSize=CachedFile->readData(MemBuff,maxSize);
				if(RealFile->isOpen()==true){
					RealFile->seek(pos+RetSize);
				}
				SameAsCache=true;
				CacheExist=true;
			}


			if(TxData(Cmd,(BYTE *)MemBuff,(int)RetSize)==false)
				goto	NextPoint;
			delete	[]MemBuff;
			PutLog(ID ,"CMD_readLineData" ,QString::number(RetSize));
		}
		else if(Cmd==CMD_writeData){
			int32		maxSize;
			qint64		RetSize;
			p=R->GetPointer(p,maxSize);
			char	*MemBuff=(char *)p;

			RetSize=CachedFile->writeData(MemBuff,maxSize);
			if(RetSize==maxSize){
				CacheExist	=true;
			}
			/*
			if(RealFile!=NULL){
				RetSize=RealFile->writeData(MemBuff,maxSize);
			}

			if(RetSize==maxSize){
				RealExist	=true;
			}
			*/
			QWFifo	*v=new QWFifo(MemBuff,maxSize);
			WFifo.Push(v);

			if(CacheExist==true && RealExist==true){
				SameAsCache	=true;
			}

			if(TxData(Cmd,RetSize)==false)
				goto	NextPoint;
			
			PutLog(ID ,"CMD_writeData" ,QString::number(RetSize));
		}
		else if(Cmd==CMD_atEnd){
			bool	BoolAtEnd;
			if(SameAsCache==true || RealFile==NULL){
				BoolAtEnd=CachedFile->atEnd();
			}
			else{
				BoolAtEnd=RealFile->atEnd();
			}

			if(TxData(Cmd,BoolAtEnd)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_atEnd" ,(BoolAtEnd==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_remove){
			bool	RetValue=CachedFile->remove();
			if(RealFile!=NULL){
				RetValue=RealFile->remove();
			}

			if(TxData(Cmd,RetValue)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_remove" ,(RetValue==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_rename){
			QBuffer Buff;
			p=R->GetPointer(p ,Buff);
			Buff.open(QIODevice::ReadWrite);

			QString		newName;
			if(::Load(&Buff,newName)==false){
				goto	NextPoint;
			}
			bool	RetValue=CachedFile->rename(newName);
			if(RealFile!=NULL){
				RetValue=RealFile->rename(newName);
			}

			if(TxData(Cmd,RetValue)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_rename" ,(RetValue==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_resize){
			qint64		newSize;
			p=R->GetPointer(p,newSize);

			bool	RetValue=CachedFile->resize(newSize);
			if(RealFile!=NULL){
				RetValue=RealFile->resize(newSize);
			}

			if(TxData(Cmd,RetValue)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_resize" ,(RetValue==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_exists){
			if(TxData(Cmd,RealExist)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_exists" ,(RealExist==true)?QString("true"):QString("false"));
		}
		else if(Cmd==CMD_filename){
			QString	RetStr=(RealFile!=NULL)?RealFile->fileName():CachedFile->fileName();

			QBuffer		rplyBuff;
			rplyBuff.open(QIODevice::WriteOnly);
			if(::Save(&rplyBuff,Cmd)==false)
				goto	NextPoint;
			if(::Save(&rplyBuff,RetStr)==false)
				goto	NextPoint;
			QByteArray	Data=rplyBuff.buffer();
			if(TxData(Cmd,&Data)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_filename" ,RetStr);
		}
		else if(Cmd==CMD_flush){
			bool	RetValue=CachedFile->flush();
			if(RetValue!=NULL){
				RetValue=RealFile->flush();
			}

			if(TxData(Cmd,RetValue)==false)
				goto	NextPoint;
			PutLog(ID ,"CMD_flush" ,(RetValue==true)?QString("true"):QString("false"));
		}
NextPoint:;
		delete	R;
	}
}
void	TrAppSocket::PutLog(int ResultServerID ,const QString &Message ,const QString &Value)
{
	emit	SignalPutLog(GetPartnerIP(),ResultServerID ,Message ,Value);
}

bool	TrAppSocket::WriteData(char *Point ,int Size)
{
	if(RealFile!=NULL){
		qint64	RetSize=RealFile->writeData(Point,Size);
		if(RetSize==Size){
			return true;
		}
		return false;
	}
	return true;
}


QWFifo::QWFifo(char *buff, int size)
{
	if(size>256){
		MemPoint=new char[size];
	}
	else{
		MemPoint=DimBuff;
	}
	MemSize=size;
	memcpy(MemPoint,buff,MemSize);
}
QWFifo::~QWFifo(void)
{
	if(MemPoint!=DimBuff){
		delete	[]MemPoint;
	}
	MemPoint=NULL;
	MemSize	=0;
}

QWFifoContainer::QWFifoContainer(TrAppSocket *sock ,TrAppServer *parent)
	:QThread(parent)
	,Parent(parent)
	,Sock(sock)
{
	Terminated=false;
}
void QWFifoContainer::run ()
{
	while(Terminated==false){
		QWFifo	*a=Pop();
		if(a!=NULL){
			Sock->WriteData(a->MemPoint,a->MemSize);
			delete	a;
		}
		else{
			msleep(1);
		}
	}
}

QWFifo	*QWFifoContainer::Pop(void)
{
	Mutex.lock();
	QWFifo	*a=GetFirst();
	if(a!=NULL){
		RemoveList(a);
	}
	Mutex.unlock();
	return a;
}
void	QWFifoContainer::Push(QWFifo *v)
{
	Mutex.lock();
	AppendList(v);
	Mutex.unlock();
}

bool	QWFifoContainer::Exist(void)
{
	Mutex.lock();
	QWFifo	*a=GetFirst();
	Mutex.unlock();
	if(a!=NULL){
		return true;
	}
	return false;
}


//==========================================================

TrAppServer::TrAppServer(TransFileServer * parent)
	:TrSocketServer(parent),Parent(parent)
{
	BaseID=0;
}
TrAppSocket	*TrAppServer::NewSocket(void)
{
	return new TrAppSocket(this);
}

QString	TrAppServer::GetChachePath(void)
{
	return Parent->CachePath;
}

int		TrAppServer::GetMaxID(void)
{
	int	ret=BaseID;
	BaseID++;
	return ret;
}
void	TrAppServer::SlotPutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value)
{
	Parent->PutLog(PartnerIP,ResultServerID ,Message ,Value);
}
//==========================================================

TransFileServer::TransFileServer(bool _LogMode
								,int _ServerPort
								,const QString &_CachePath
								,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,TrServer(this),WDog(this)
{
	ui.setupUi(this);
	LogMode=_LogMode;
	ServerPort	=_ServerPort;
	CachePath	=_CachePath;

	setWindowTitle(QString(/**/"TransFileServer-")+QString::number(ServerPort));

	TrServer.StartServer(ServerPort);

	ui.spinBoxTransPort	->setValue(ServerPort);
	ui.lineEditCachePath->setText(CachePath);
	ui.progressBar->setValue(0);
	WDog.Start();
}

TransFileServer::~TransFileServer()
{

}

void	TransFileServer::PutLog(const QString &PartnerIP ,int ResultServerID ,const QString &Message ,const QString &Value)
{
	int	V=ui.progressBar->value()+1;
	if(V>ui.progressBar->maximum()){
		V=0;
	}
	ui.progressBar->setValue(V);

	if(LogMode==true){
		QString		FileName=QString("TransDBLog")+QString::number(ServerPort)+QString(".txt");
		QFile	File(FileName);
		if(File.open(QIODevice::Append)==true){
			QTextStream	Txt(&File);
			Txt<<QDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss");
			Txt<<'\t';
			Txt<<QString(/**/"IP=")+PartnerIP<<QString('\t');
			Txt<<QString(/**/"ResID=")+QString::number(ResultServerID)<<QString('\t');
			Txt<</**/"\n\t";
			Txt<<Message;
			Txt<</**/"\n\t";
			Txt<<Value;
			Txt<</**/"\n\n";
		}
	}
}