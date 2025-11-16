#include "XWatchdogRebooter.h"
#include "XGeneralFunc.h"
#include "XTypeDef.h"
#include <QProcess>
#include "XForWindows.h"	

WatchdogTarget::WatchdogTarget(WatchdogPack *p,QObject * parent)
	:QObject(parent),Parent(p)
{	
	PID		=-1;
	WatchTerm=180;
	Sock	=NULL;
}
bool	WatchdogTarget::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,PathFileName)==false)
		return false;
	if(::Save(f,Arguments)==false)
		return false;
	if(::Save(f,WorkingPath)==false)
		return false;
	if(::Save(f,WatchTerm)==false)
		return false;
	return true;
}

bool	WatchdogTarget::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,PathFileName)==false)
		return false;
	if(::Load(f,Arguments)==false)
		return false;
	if(::Load(f,WorkingPath)==false)
		return false;
	if(::Load(f,WatchTerm)==false)
		return false;
	return true;
}

WatchdogTarget	&WatchdogTarget::operator=(WatchdogTarget &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	Parent=src.Parent;
	return *this;
}

bool	WatchdogTarget::StartUp(void)
{
	PID=-1;
	QStringList	AList=Arguments.split (" ");

	bool	Ret=QProcess::startDetached ( PathFileName, AList, WorkingPath, &PID);
	if(Ret==true){
		LastAccessed=XDateTime::currentDateTime();
		emit	SignalShow();

		QFileInfo	Info(PathFileName);
		QString	Name=Info.fileName();
		emit	SignalWatchdogEvent("Bootup",Name,PID);
	}
	return Ret;
}
void WatchdogTarget::SlotReadyRead ()
{
	LastAccessed=XDateTime::currentDateTime();
	
	if(Sock!=NULL){
		QByteArray R=Sock->readAll();
		QString	AStr(R);
		ArgStr=AStr;
	}
}

bool	WatchdogTarget::IsAlive(void)
{
	int	Sec=LastAccessed.secsTo(XDateTime::currentDateTime());
	if(Sec>WatchTerm/3){
		return false;
	}
	return true;
}
bool	WatchdogTarget::IsOpen(void)
{
	if(Sock!=NULL){
		if(Sock->isOpen()==true)
			return true;
	}
	return false;
}
bool	WatchdogTarget::IsConnected(void)
{
	if(IsOpen()==true){
		if(Sock->isValid()==true){
			return true;
		}
	}
	return false;
}

bool	WatchdogTarget::TryConnection(DWORD ProcessID)
{
	PID=ProcessID;
	QFileInfo	Info(PathFileName);
	QString	Name=Info.baseName()+QString::number(PID);
	Sock=new QLocalSocket(parent());
	connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Sock->connectToServer (Name);
	if(Sock->waitForConnected (3000)==false){
		Sock->deleteLater();
		Sock=NULL;
		return false;
	}
	else{
		Sock->write("ARG",4);
		Sock->waitForReadyRead(2000);
		QStringList	LArg=Arguments.split(" ");
		QString	arg;
		for(int i=0;i<LArg.count();i++){
			if(LArg[i]==QString(" ") || LArg[i]==QString("\t") || LArg[i]==QString(/**/"")){
				continue;
			}
			arg+=LArg[i];
			if((i+1)<LArg.count()){
				arg+=" ";
			}
		}
		if(ArgStr==arg){
			LastAccessed=XDateTime::currentDateTime();
			emit	SignalShow();

			QFileInfo	Info(PathFileName);
			QString	Name=Info.fileName();
			emit	SignalWatchdogEvent("Caught",Name,PID);
		}
		else{
			Sock->deleteLater();
			Sock=NULL;
			return false;
		}
	}
	return true;
}

void	WatchdogTarget::TimerFunc(void)
{
	if(IsOpen()==true && Sock->isValid()==true){
		Sock->write("Req",4);
		Sock->flush();
		Sock->waitForReadyRead(2000);
	}
	else{
		if(SearchProcess()==false){
			StartUp();
			GSleep(2000);
		}
		QFileInfo	Info(PathFileName);
		QString	Name=Info.fileName();
		emit	SignalWatchdogEvent("Retouched",Name,PID);
	}
	if(IsOpen()==false && PID>=0){
		QFileInfo	Info(PathFileName);
		QString	Name=Info.baseName()+QString::number(PID);
		Sock=new QLocalSocket(parent());
		connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
		Sock->connectToServer (Name);
		Sock->waitForConnected (3000);
	}
	int	Sec=LastAccessed.secsTo(XDateTime::currentDateTime());
	if(Sec>WatchTerm){
		if(Sock!=NULL){
			if(IsOpen()==true){
				Sock->close();
				Sock->disconnectFromServer();
				Sock->waitForDisconnected(1000);
				Sock->deleteLater();
				Sock=NULL;
			}
		}
		if(IsOpen()==false || Sock->isValid()==true){
			GSleep(2000);
			if(SearchProcess()==true){
				QFileInfo	Info(PathFileName);
				QString	Name=Info.fileName();
				emit	SignalWatchdogEvent("Retouched",Name,PID);
			}
			else{
				if(KillProcess(PID, 0)==true){
					emit	SignalShow();

					QFileInfo	Info(PathFileName);
					QString	Name=Info.fileName();
					emit	SignalWatchdogEvent("Killed",Name,PID);
					PID=-1;
				}
			}
		}
	}

}
bool	WatchdogTarget::SearchProcess(void)
{
	PID=-1;
	QFileInfo	Info(PathFileName);
	QString	SearchedName=Info.fileName();

	DWORD ProcessID[16384];
	int	N=MtEnumProcess(ProcessID, sizeof(ProcessID)/sizeof(ProcessID[0]));
	for(int i=0;i<N;i++){
		QString ProcessName;
		if(GetProcessName(ProcessID[i] ,ProcessName)==false){
			continue;
		}
		bool	Found=false;
		for(WatchdogTarget *a=Parent->GetFirst();a!=NULL;a=a->GetNext()){
			if(ProcessID[i]==a->GetPID()){
				Found=true;
				break;
			}
		}
		if(Found==true){
			continue;
		}
		if(ProcessName==SearchedName){
			if(IsConnected()==false){
				if(TryConnection(ProcessID[i])==true){
					return true;
				}
			}
		}
	}
	return false;
}

void	WatchdogTarget::Kill(void)
{
	KillProcess(PID, 0);
}

WatchdogTarget	*WatchdogPack::Create(void)
{
	WatchdogTarget	*a=new WatchdogTarget(this);
	connect(a,SIGNAL(SignalShow()),this,SLOT(SlotShow()));
	connect(a,SIGNAL(SignalWatchdogEvent(const QString &,const QString & ,int )),this,SLOT(SlotWatchdogEvent(const QString &,const QString & ,int )));
	return a;
}

void	WatchdogPack::SlotWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid)
{
	emit	SignalWatchdogEvent(ErrorType,FileName ,pid);
}

void	WatchdogPack::SlotShow(void)
{
	emit	SignalShow();
}
