#include "XTypeDef.h"
#include "XFileThread.h"
#include "XDataInLayer.h"
#include "XDateTime.h"
#include <QTextCodec>
#include <QDateTime>
#include <QBitArray>
#include <QBuffer>
#include <QDir>
#include "XIntClass.h"
#include "XCriticalFunc.h"

FileThread::FileThread(LayersBase *Base ,const QString &_FileName)
	:ServiceForLayers(Base) ,FileName(_FileName)
{

}
FileThread::~FileThread()
{
	flush();
}

bool	FileThread::open(QIODevice::OpenMode mode)
{
	Mode=mode;
	return true;
}
qint64	FileThread::write(const char *data, qint64 maxSize)
{
	Data.append(QByteArray(data,maxSize));
	return maxSize;
}
qint64	FileThread::write(const QByteArray &byteArray)
{
	Data.append(byteArray);
	return byteArray.size();
}
bool	FileThread::flush()
{
	if(Data.size()>0){
		FileThreadListContainer	*C=GetLayersBase()->GetFileThreadListContainer();
		if(C!=NULL){
			if(C->Append(this)==false){
				return false;
			}
		}
		Data.clear();
	}
	return true;
}
bool	FileThread::Save(int8 d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(int32 d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(uint32 d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(int64 d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(short d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(WORD d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(DWORD d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(float d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(double d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(BYTE d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(const QChar& d)
{
	ushort	unicode=d.unicode();
	Data.append(QByteArray((const char *)&unicode,sizeof(unicode)));
	return true;
}
bool	FileThread::Save(char d)
{
	Data.append(QByteArray(&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(bool d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(bool3 d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(const char* d, int64 len)
{
	Data.append(QByteArray((const char *)&len,sizeof(len)));
	Data.append(QByteArray(d,len));
	return true;
}
bool	FileThread::Save(const QString& d)
{
	int32	Len=d.length()*2;
	Data.append(QByteArray((const char *)&Len,sizeof(Len)));
	Data.append(QByteArray((const char *)d.constData(),Len));
	return true;
}
bool	FileThread::Save(const QStringList& d)
{
	int32	N=d.count();
	Data.append(QByteArray((const char *)&N,sizeof(N)));
	for(int i=0;i<N;i++){
		QString	A=d.value(i);
		if(Save(A)==false){
			return false;
		}
	}
	return true;
}
bool	FileThread::Save(const XYData& d)
{
	Data.append(QByteArray((const char *)&d,sizeof(d)));
	return true;
}
bool	FileThread::Save(const QDateTime& d)
{
	WORD	wyear	=d.date().year();
	BYTE	wmonth	=d.date().month();
	BYTE	wday	=d.date().day();
	BYTE	whour	=d.time().hour();
	BYTE	wminute	=d.time().minute();
	BYTE	wsec	=d.time().second();

	Data.append(QByteArray((const char *)&wyear		,sizeof(wyear)));
	Data.append(QByteArray((const char *)&wmonth	,sizeof(wmonth)));
	Data.append(QByteArray((const char *)&wday		,sizeof(wday)));
	Data.append(QByteArray((const char *)&whour		,sizeof(whour)));
	Data.append(QByteArray((const char *)&wminute	,sizeof(wminute)));
	Data.append(QByteArray((const char *)&wsec		,sizeof(wsec)));

	return true;
}
bool	FileThread::Save(const QDate& d)
{
	WORD	wyear	=d.year();
	BYTE	wmonth	=d.month();
	BYTE	wday	=d.day();

	Data.append(QByteArray((const char *)&wyear		,sizeof(wyear)));
	Data.append(QByteArray((const char *)&wmonth	,sizeof(wmonth)));
	Data.append(QByteArray((const char *)&wday		,sizeof(wday)));

	return true;
}
bool	FileThread::Save(const QTime& d)
{
	BYTE	whour	=d.hour();
	BYTE	wminute	=d.minute();
	BYTE	wsec	=d.second();

	Data.append(QByteArray((const char *)&whour		,sizeof(whour)));
	Data.append(QByteArray((const char *)&wminute	,sizeof(wminute)));
	Data.append(QByteArray((const char *)&wsec		,sizeof(wsec)));

	return true;
}
bool	FileThread::Save(const XDateTime& d)
{
	WORD	wyear	=d.year();
	BYTE	wmonth	=d.month();
	BYTE	wday	=d.day();
	BYTE	whour	=d.hour();
	BYTE	wminute	=d.minute();
	BYTE	wsec	=d.second();

	Data.append(QByteArray((const char *)&wyear		,sizeof(wyear)));
	Data.append(QByteArray((const char *)&wmonth	,sizeof(wmonth)));
	Data.append(QByteArray((const char *)&wday		,sizeof(wday)));
	Data.append(QByteArray((const char *)&whour		,sizeof(whour)));
	Data.append(QByteArray((const char *)&wminute	,sizeof(wminute)));
	Data.append(QByteArray((const char *)&wsec		,sizeof(wsec)));

	return true;
}
//bool	FileThread::Save(QRgb &d);
bool	FileThread::Save(const QByteArray& d)
{
	int64	Len=d.size();
	Data.append(QByteArray((const char *)&Len,sizeof(Len)));
	Data.append(QByteArray(d.constData(),Len));
	return true;
}

bool	FileThread::Save(const QByteArrayList& d)
{
	int32	Count=d.count();
	Data.append(QByteArray((const char *)&Count,sizeof(Count)));
	for(int i=0;i<Count;i++){
		QByteArray	a=d[i];
		int64	Len=a.size();
		if(Save(Len)==false){
			return false;
		}
		Data.append(QByteArray(a.constData(),Len));
	}
	return true;
}
bool	FileThread::Save(BYTE** Point, int XLen, int YLen)
{
	for(int y=0;y<YLen;y++){
		Data.append(QByteArray((const char *)Point[y],XLen));
	}
	return true;
}
bool	FileThread::SaveText(char* s)
{
	int	Len=strlen(s);
	Data.append(QByteArray((const char *)s,Len));
	return true;
}

bool	FileThread::Save(const QPoint& d)
{
	int32	P[2];
	P[0]=d.x();
	P[1]=d.y();

	Data.append(QByteArray((const char *)P	,sizeof(P)));
	return true;
}

//===========================================================
DirectoryThread::DirectoryThread(LayersBase *Base)
:ServiceForLayers(Base)
{
}
DirectoryThread::~DirectoryThread()
{
}


bool DirectoryThread::ForceDirectories( const QString &path )
{
	FileName=path;
	FileThreadListContainer	*C=GetLayersBase()->GetFileThreadListContainer();
	if(C!=NULL){
		if(C->Append(this)==true){
			return true;
		}
	}
	return false;
}
//===========================================================
FileStatusList::FileStatusList(void)
{
	File	=NULL;
	Mode	=QIODevice::Append;
	Opened		=false;
	Flushed		=true;
	LastAccessTime=0;
}

FileStatusList::~FileStatusList(void)
{
	if(File!=NULL){
		delete	File;
		File=NULL;
	}
}

//===========================================================

FileThreadList::FileThreadList(void)
{
}

FileThreadListContainer::FileThreadListContainer(LayersBase *Base)
:ServiceForLayers(Base)
{
	Terminated=false;
	for(int i=0;i<sizeof(FileThreadListDim)/sizeof(FileThreadListDim[0]);i++){
		FileThreadListDim[i]=NULL;
	}
	StockedCount=0;
	WPoint		=0;
	RPoint		=0;
}

FileThreadListContainer::~FileThreadListContainer(void)
{
	for(int i=0;i<sizeof(FileThreadListDim)/sizeof(FileThreadListDim[0]);i++){
		if(FileThreadListDim[i]!=NULL){
			delete	FileThreadListDim[i];
			FileThreadListDim[i]=NULL;
		}
	}
	StockedCount=0;
	WPoint		=0;
	RPoint		=0;
}

bool	FileThreadListContainer::Append(FileThread *f)
{
	Mutex.lock();
	if(StockedCount>=MaxBufferedFileList){
		Mutex.unlock();
		return false;
	}
	int	tWPoint=WPoint;
	if(FileThreadListDim[WPoint]==NULL){
		FileThreadListDim[WPoint]=new FileThreadList();
	}
	WPoint++;
	if(WPoint>=MaxBufferedFileList){
		WPoint=0;
	}
	Mutex.unlock();

	FileThreadList	*t=FileThreadListDim[tWPoint];
	t->FileName	=f->FileName;
	t->Data		=f->Data;
	t->Mode		=f->Mode;
	t->Command	=0;

	Mutex.lock();
	StockedCount++;
	Mutex.unlock();

	return true;
}

bool	FileThreadListContainer::Append(DirectoryThread *f)
{
	Mutex.lock();
	if(StockedCount>=MaxBufferedFileList){
		Mutex.unlock();
		return false;
	}
	int	tWPoint=WPoint;
	if(FileThreadListDim[WPoint]==NULL){
		FileThreadListDim[WPoint]=new FileThreadList();
	}
	WPoint++;
	if(WPoint>=MaxBufferedFileList){
		WPoint=0;
	}
	Mutex.unlock();

	FileThreadList	*t=FileThreadListDim[tWPoint];
	t->FileName	=f->FileName;
	t->Data		=f->Data;
	t->Command	=1;

	Mutex.lock();
	StockedCount++;
	Mutex.unlock();

	return true;
}

void	FileThreadListContainer::SetTerminate(bool b)
{
	Terminated=b;
}

void	FileThreadListContainer::run()
{
	//while(Terminated==false){
	//	if(StockedCount==0){
	//		msleep(100);
	//	}
	//	else{
	//		Mutex.lock();
	//		FileThreadList	*f=FileThreadListDim[RPoint];
	//		RPoint++;
	//		if(RPoint>=MaxBufferedFileList){
	//			RPoint=0;
	//		}
	//		StockedCount--;
	//		Mutex.unlock();
	//
	//		if(f->Command==0){
	//			QFile	File(f->FileName);
	//			if(File.open(f->Mode)==true){
	//				File.write(f->Data);
	//				File.flush();
	//			}
	//		}
	//		else
	//		if(f->Command==1){
	//			ForceDirectories(f->FileName);
	//		}
	//	}
	//}

	while(Terminated==false){
		for(FileStatusList *s=FileStatusContainer.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->Flushed==false && s->Opened==true){
				s->File->flush();
				s->Flushed=true;
			}
			if(s->Opened==true){
				s->File->close();
				s->Opened=false;
			}
		}
		DWORD	CurrentTime=::GetComputerMiliSec();
		for(FileStatusList *s=FileStatusContainer.GetFirst();s!=NULL;){
			FileStatusList *NextS=s->GetNext();
			if(s->LastAccessTime-CurrentTime>10000){
				FileStatusContainer.RemoveList(s);
				delete	s;
			}
			s=NextS;
		}
		msleep(1000);
	
		while(StockedCount!=0){
			Mutex.lock();
			FileThreadList	*f=FileThreadListDim[RPoint];
			RPoint++;
			if(RPoint>=MaxBufferedFileList){
				RPoint=0;
			}
			StockedCount--;
			Mutex.unlock();
	
			if(f->Command==0){
				bool	Done=false;
				for(FileStatusList *s=FileStatusContainer.GetFirst();s!=NULL;s=s->GetNext()){
					if(s->FileName==f->FileName){
						if(s->Opened==false){
							if(s->File->open(f->Mode)==true){
								s->Opened=true;
							}
						}
						if(s->Opened==true){
							s->File->write(f->Data);
							s->LastAccessTime=::GetComputerMiliSec();
							s->Flushed=false;
						}
						Done=true;
						break;
					}
				}
				if(Done==false){
					FileStatusList *s=new FileStatusList();
					FileStatusContainer.AppendList(s);
					s->FileName=f->FileName;
					s->File=new QFile(f->FileName);
					if(s->File->open(f->Mode)==true){
						s->Opened=true;
					}
					if(s->Opened==true){
						s->File->write(f->Data);
						s->LastAccessTime=::GetComputerMiliSec();
						s->Flushed=false;
					}
					Done=true;
				}
			}
			else
			if(f->Command==1){
				ForceDirectories(f->FileName);
			}
		}
	}



}

