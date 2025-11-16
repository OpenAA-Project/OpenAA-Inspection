#include "XForceRebooter.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <QElapsedTimer>
#include <QDir>
#include "ForceRebooter.h"
#include "XForWindows.h"	

PartnerInfo::PartnerInfo(void)
{
	PortNumber	=DefaultForceRebooterPortNumber;
}

bool	PartnerInfo::Save(QIODevice *f)
{
	int32		Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,HostName)==false)
		return false;
	if(::Save(f,PortNumber)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	return true;
}

bool	PartnerInfo::Load(QIODevice *f)
{
	int32		Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,HostName)==false)
		return false;
	if(::Load(f,PortNumber)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	return true;
}

PartnerInfo	&PartnerInfo::operator=(PartnerInfo &src)
{
	HostName	=src.HostName;
	PortNumber	=src.PortNumber;
	Remark		=src.Remark;
	return *this;
}

RebooterParam::RebooterParam(void)
{
	OwnPortNumber=DefaultForceRebooterPortNumber;
}

PartnerInfo	*RebooterParam::Create(void)
{
	return new PartnerInfo();
}

bool	RebooterParam::Save(QIODevice *f)
{
	if(NPListPackSaveLoad<PartnerInfo>::Save(f)==false)
		return false;
	if(::Save(f,OwnPortNumber)==false)
		return false;
	if(::Save(f,RebootedPrograms)==false)
		return false;
	return true;
}

bool	RebooterParam::Load(QIODevice *f)
{
	if(NPListPackSaveLoad<PartnerInfo>::Load(f)==false)
		return false;
	if(::Load(f,OwnPortNumber)==false)
		return false;
	if(::Load(f,RebootedPrograms)==false)
		return false;
	return true;
}

bool	RebooterParam::Save(void)
{
	QString	FileName=GetDefaultFileName();

	QDir	dir;
	dir.cd(QCoreApplication::applicationDirPath ());
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(Save(&File)==true)
			return true;
	}
	return false;
}

bool	RebooterParam::Load(void)
{
	QString	FileName=GetDefaultFileName();

	QDir	dir;
	dir.cd(QCoreApplication::applicationDirPath ());
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(Load(&File)==true)
			return true;
	}
	return false;
}


//================================================================

RebooterSocket::RebooterSocket(QWidget *parent,const RebooterParam &param ,PartnerInfo *info)
	:Param(param)
{
	if(info!=NULL){
		Info=*info;
	}
	RecvCmd=-1;
	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)));
}

void	RebooterSocket::SlotReceived(int)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		BYTE	Cmd=*p;
		if(Cmd==Cmd_RebootPrograms){
			RealRebootPrograms();
		}
		else if(Cmd==Cmd_RebootPC){
			RealRebootPC();
		}
		else if (Cmd == Cmd_ShutDownPC) {
			RealShutdownPC();
		}
NextPoint:;
		delete	R;
	}
}

bool	RebooterSocket::RebootPrograms(void)
{
	Set(NULL, Info.HostName,Info.PortNumber);
	if(StartConnect()==true){
		RecvCmd	=0;
		BYTE	Cmd=Cmd_RebootPrograms;

		if(TxData(Cmd)==false)
			return false;
		QElapsedTimer	timer;
		timer.start();
		while(timer.elapsed()<2000){
			if(RecvCmd=Cmd_RebootPrograms){
				break;
			}
			WaitReadyRead(1);
		}
		deleteLater();
		return true;
	}
	deleteLater();
	return false;
}

bool	RebooterSocket::RebootPC(void)
{
	Set(NULL, Info.HostName,Info.PortNumber);
	if(StartConnect()==true){
		RecvCmd	=0;
		BYTE	Cmd=Cmd_RebootPC;

		if(TxData(Cmd)==false)
			return false;
		QElapsedTimer	timer;
		timer.start();
		while(timer.elapsed()<2000){
			if(RecvCmd=Cmd_RebootPC){
				break;
			}
			WaitReadyRead(1);
		}
		deleteLater();
		return true;
	}
	deleteLater();
	return false;
}

bool	RebooterSocket::ShutdownPC(void)
{
	Set(NULL, Info.HostName, Info.PortNumber);
	if (StartConnect() == true) {
		RecvCmd = 0;
		BYTE	Cmd = Cmd_ShutDownPC;

		if (TxData(Cmd) == false)
			return false;
		QElapsedTimer	timer;
		timer.start();
		while (timer.elapsed() < 2000) {
			if (RecvCmd = Cmd_ShutDownPC) {
				break;
			}
			WaitReadyRead(1);
		}
		deleteLater();
		return true;
	}
	deleteLater();
	return false;
}

void	RebooterSocket::RealRebootPrograms(void)
{
	DWORD ProcessID[16384];
	int	N=MtEnumProcess(ProcessID, sizeof(ProcessID)/sizeof(ProcessID[0]));
	for(int i=0;i<N;i++){
		QString ProcessName;
		if(GetProcessName(ProcessID[i] ,ProcessName)==false){
			continue;
		}
		for(int j=0;j<Param.RebootedPrograms.count();j++){
			if(Param.RebootedPrograms[j]==ProcessName){
				KillProcess(ProcessID[i], 0);
			}
		}
	}
}

void	RebooterSocket::RealRebootPC(void)
{
	MtShutdownSelfPC( true, true);
}

void	RebooterSocket::RealShutdownPC(void)
{
	MtShutdownSelfPC(true, false);
}

//=============================================================
RebooterServer::RebooterServer(QWidget *parent)
	:TrSocketServer(parent),Parent(parent)
{
	BaseID=0;
	Param.Load();
}
RebooterSocket	*RebooterServer::NewSocket(void)
{
	return new RebooterSocket(Parent,Param,NULL);
}
	
bool	RebooterServer::RebootPrograms(void)
{
	bool	Ret=true;
	for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
		RebooterSocket	S(Parent,Param,a);
		if(S.RebootPrograms()==false){
			Ret=false;
		}
	}
	return true;
}
	
bool	RebooterServer::RebootPC(void)
{
	bool	Ret=true;
	for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
		RebooterSocket	S(Parent,Param,a);
		if(S.RebootPC()==false){
			Ret=false;
		}
	}
	return true;
}
	
bool	RebooterServer::ShutdownPC(void)
{
	bool	Ret=true;
    for(PartnerInfo *a=Param.GetFirst();a!=NULL;a=a->GetNext()){
        RebooterSocket	S(Parent,Param,a);
        if(S.ShutdownPC()==false){
			Ret=false;
		}
	}
	return true;
}