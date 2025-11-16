#include "XCommandServer.h"
#include "XMLServerCommon.h"
#include "ThreadLogger.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#include "XErrorCode.h"
#include "XCriticalFunc.h"
#include <omp.h>

void	XMLTxQueueListContainer::Push(XMLTxQueueList *s)
{
	AccessMutex.lock();
	AppendList(s);
	AccessMutex.unlock();
}

XMLTxQueueList	*XMLTxQueueListContainer::Pop(void)
{
	AccessMutex.lock();
	XMLTxQueueList	*r=GetFirst();
	if(r!=NULL){
		RemoveList(r);
	}
	AccessMutex.unlock();
	return r;
}


XMLServerComm::XMLServerComm(QObject * parent)
:FastComm(parent),XMLStocker(parent),ThreadCommand(parent,this),CommServerComm(this)
{
	Parent	=(XMLServerV3 *)parent;

	PortNumber		=12345;
	RootPathes		="c:/data";
	Extension		="dxml";
	LogOut			=false;
	LogDetail		=false;
	LogOutPath		=/**/"C:/XMLLog";
	LoggedDays		=14;
	IdleTimeForSave	=120;
	Accessed		=false;
	SecondToKillByNoAccess	=4*3600;	//4 hours

	SetParam(&PortNumber	, /**/"Global"	,/**/"PortNumber"	,"TCP Port number"				,1000,65535);
	SetParamPath(&RootPathes, /**/"Global"	,/**/"RootPath"		,"XML-Database path"			,0);
	SetParam(&Extension		, /**/"Global"	,/**/"Extension"	,"XML-Database file extension"	);

	SetParam	(&LogOut	, /**/"Global"	,/**/"LogOut"		,"LogOut mode"			);
	SetParam	(&LogDetail	, /**/"Global"	,/**/"LogDetail"	,"LogOut detail mode"	);
	SetParamPath(&LogOutPath, /**/"Global"	,/**/"LogOutPath"	,"LogOut path"			);
	SetParam	(&LoggedDays, /**/"Global"	,/**/"LoggedDays"	,"Logged Days"			);
	SetParam	(&IdleTimeForSave, /**/"Global"	,/**/"IdleTimeForSave"	,"Idle Time(Sec) for Save data"			);
	SetParam	(&SecondToKillByNoAccess, /**/"Global"	,/**/"SecondToKillByNoAccess"	,"Time(second) to kill socket instance when it has no access"	);

	SetParam	(&CommunicatedServerIP0	, /**/"OtherServer"	,/**/"CommunicatedServerIP0"		,"Communicated Server IP-0"			);
	SetParam	(&CommunicatedServerIP1	, /**/"OtherServer"	,/**/"CommunicatedServerIP1"		,"Communicated Server IP-1"			);
	SetParam	(&CommunicatedServerIP2	, /**/"OtherServer"	,/**/"CommunicatedServerIP2"		,"Communicated Server IP-2"			);
	SetParam	(&CommunicatedServerIP3	, /**/"OtherServer"	,/**/"CommunicatedServerIP3"		,"Communicated Server IP-3"			);
	SetParam	(&CommunicatedServerIP4	, /**/"OtherServer"	,/**/"CommunicatedServerIP4"		,"Communicated Server IP-4"			);
	SetParam	(&CommunicatedServerIP5	, /**/"OtherServer"	,/**/"CommunicatedServerIP5"		,"Communicated Server IP-5"			);
	SetParam	(&CommunicatedServerIP6	, /**/"OtherServer"	,/**/"CommunicatedServerIP6"		,"Communicated Server IP-6"			);
	SetParam	(&CommunicatedServerIP7	, /**/"OtherServer"	,/**/"CommunicatedServerIP7"		,"Communicated Server IP-7"			);
	SetParam	(&CommunicatedServerIP8	, /**/"OtherServer"	,/**/"CommunicatedServerIP8"		,"Communicated Server IP-8"			);
	SetParam	(&CommunicatedServerIP9	, /**/"OtherServer"	,/**/"CommunicatedServerIP9"		,"Communicated Server IP-9"			);

	Logger=new ThreadLogger(this);
	Logger->start();

	TimerForBackup.setInterval(3000);
	TimerForBackup.setSingleShot(false);
	connect(&TimerForBackup,SIGNAL(timeout()),SLOT(SlotTimeOut()));
	TimerForBackup.start();

	ThreadCommand.start();
	CommServerComm.StartServer(CommunicatedServerPort);
}
XMLServerComm::~XMLServerComm(void)
{
	ThreadCommand.Terminated=true;
	ThreadCommand.wait(1000);

	Logger->Close();
	Logger->wait(5000);
	delete	Logger;
}
SClient	*XMLServerComm::GetSClient(int ClientID)
{
	return (SClient	*)GetLeaf(ClientID);
}

void	XMLServerComm::StartServer(void)
{
	FastComm::StartServer(PortNumber);
}

void	XMLServerComm::SlotTimeOut()
{
	if(Accessed==true){
		if(GetComputerMiliSec()-LastAccessTime>IdleTimeForSave*1000){
			WriteOutAll();
			Accessed=false;
		}
	}
	/*
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*C=GetSClient(i);
		if(C==NULL){
			continue;
		}
		if(C->IsConnected()==false){
			SlotDisconnected(i);
			delete	C;
		}
	}
	*/
	emit	SignalShowClient(-1);
}

void	XMLServerComm::SendCommandWriteOut(void)
{
	CommServerComm.SendCommandWriteOut();
}

void	XMLServerComm::SlotReceived(int ID,int Cmd)
{
	SClient	*s=GetSClient(ID);
	//s->LastReceivedTime.setTime_t(s->GetLastReceivingTime());
	s->LastReceivedTime=XDateTime::currentDateTime();
}

void	XMLServerComm::SlotNewConnection (int id)
{
	FastComm::SlotNewConnection (id);
	emit	SignalShowClient(id);
}

void	XMLServerComm::SlotDisconnected(int id)
{
	FastComm::SlotDisconnected (id);

	for(XMLElement *s=XMLElements.GetFirst();s!=NULL;){
		XMLElement *NextS=s->GetNext();
		XMLElementRoot *Root=(XMLElementRoot *)s;
		bool	Used=false;
		for(int i=0;i<MaxCommLeafNumb;i++){
			SClient	*C=GetSClient(i);
			if(C==NULL){
				continue;
			}
			if(C->IsDealingTable(Root->GetTableName())==true){
				Used=true;
				break;
			}
		}
		if(Used==false){
			LockMutex.lockForWrite();
			Root->TableReadLock();
			XMLElements.RemoveList(Root);
			Root->TableUnLock();
			LockMutex.unlock();

			ThreadServerComm::ThreadSaveDeleteTable	*a=new ThreadServerComm::ThreadSaveDeleteTable(&ThreadCommand,Root);
			ThreadCommand.PushCommand(a);
		}
		s=NextS;
	}
	emit	SignalShowClient(-1);
}
QStringList	XMLServerComm::GetRootPath(void)
{
	QStringList	L=RootPathes.split(';');
	return L;
}
void	XMLServerComm::ShowClient(int id)
{
	emit	SignalShowClient(id);
}

void	XMLServerComm::StepProgress(void)
{
	emit	SignalProgress();
}

void	XMLServerComm::SlotShowClient(int id)
{
	ShowClient(id);
}

void	XMLServerComm::SlotAnalize(QDateTime tm , int ClientID, int OpeHandleCode, QString Command,int milisec)
{
	emit	SignalAnalize(tm , ClientID, OpeHandleCode, Command ,milisec);
}


void	XMLServerComm::CloseAllOperation(const QString &TableStr)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*SData=GetSClient(i);
		if(SData!=NULL){
			SData->CloseAllOperation(TableStr);
		}
	}
}

void	XMLServerComm::SaveOpenedTable(const QString &TableStr)
{
	bool	Used=false;
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*C=GetSClient(i);
		if(C==NULL){
			continue;
		}
		if(C->IsDealingTable(TableStr)==true){
			Used=true;
			break;
		}
	}
	if(Used==true){
		for(XMLElement *s=XMLElements.GetFirst();s!=NULL;s=s->GetNext()){
			XMLElementRoot *Root=(XMLElementRoot *)s;
			if(TableStr==Root->GetTableName()){
				Root->TableReadLock();
				Root->SaveFile();
				Root->TableUnLock();
			}
		}
	}
}

void	XMLServerComm::SlotCheckUnsedTable()
{
	//return;
	XDateTime	NowTime=XDateTime::currentDateTime();
	bool	Removed=false;
	LockMutex.lockForWrite();
	for(XMLElement *s=XMLElements.GetFirst();s!=NULL;){
		XMLElementRoot *Root=(XMLElementRoot *)s;
		int	Sec=Root->GetLoadedAndAccessTime().secsTo(NowTime);
		if(Sec<10){
			s=s->GetNext();
			continue;
		}
		bool	FoundFlag=false;
		for(int i=0;i<MaxCommLeafNumb;i++){
			SClient	*SData=GetSClient(i);
			if(SData!=NULL){
				SData->SClientLock();
				for(ClientOperation *d=SData->GetFirst();d!=NULL;d=d->GetNext()){
					if(Root->GetTableName()==d->GetTableStr()){
						FoundFlag=true;
						break;
					}
				}
				SData->SClientUnlock();
			}
			if(FoundFlag==true){
				break;
			}
		}
		if(FoundFlag==false){
			XMLElement *NextS=s->GetNext();
			XMLElements.RemoveList(s);

			FoundFlag=false;
			for(int i=0;i<MaxCommLeafNumb;i++){
				SClient	*SData=GetSClient(i);
				if(SData!=NULL){
					SData->SClientLock();
					for(ClientOperation *d=SData->GetFirst();d!=NULL;d=d->GetNext()){
						if(Root->GetTableName()==d->GetTableStr()){
							FoundFlag=true;
							break;
						}
					}
					SData->SClientUnlock();
				}
				if(FoundFlag==true){
					break;
				}
			}
			if(FoundFlag==false){
				ThreadServerComm::ThreadSaveDeleteTable	*a=new ThreadServerComm::ThreadSaveDeleteTable(&ThreadCommand,Root);
				ThreadCommand.PushCommand(a);

				s=NextS;
				Removed=true;
			}
			else{
				XMLElements.AppendList(s);
				s=NextS;
			}
		}
		else{
			s=s->GetNext();
		}
	}
	LockMutex.unlock();

	if(Removed==true){
		emit	SignalShowClient(-1);
	}
}

void	XMLServerComm::ShowClient(void)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*SData=GetSClient(i);
		if(SData!=NULL){
			emit	SignalShowClient(SData->GetID());
		}
	}
}

//===============================================================
SClient::SClient(int id,XMLServerComm *parent)
	:FastCommLeaf(id,parent),ExeProg(this,parent)
{
	Parent=parent;
	ExeProg.start();
	connect(&ExeProg,SIGNAL(SignalTx()),this,SLOT(SlotTx()),Qt::QueuedConnection);
	connect(&ExeProg,SIGNAL(SignalAnalize(QDateTime, int , int , QString,int))
			,Parent,SLOT(SlotAnalize(QDateTime , int , int , QString,int))
			,Qt::QueuedConnection);
	connect(this,SIGNAL(SignalCheckUnsedTable()),parent,SLOT(SlotCheckUnsedTable()),Qt::QueuedConnection);
}

SClient::~SClient(void)
{
	ExeProg.Terminated=true;
	ExeProg.wait();
}

XMLServerComm *SClient::GetServer(void)
{
	return Parent;
}
bool	SClient::IsDealingTable(const QString &TableStr)
{
	for(ClientOperation *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetTableStr()==TableStr){
			return true;
		}
	}
	return false;
}

void	SClient::SlotTx()
{
	XMLTxQueueList	*r=XMLTxQueue.Pop();
	if(r!=NULL){
		struct EntryPointBase::EntryPointPacketInfo	Info(r->cmd
														,0
														,0
														,0
														,/**/""
														,/**/"" 
														,/**/"");
		TxData(r->OpeHandleCode,Info,&(r->Buff),r->ErrorData);
		delete	r;
	}
}
int		SClient::GetMaxOpeHandleCode(void)
{
	int	MaxOpeHandleCode=0;
	MutexClientOperation.lock();
	for(ClientOperation *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetOpeHandleCode()>MaxOpeHandleCode){
			MaxOpeHandleCode=c->GetOpeHandleCode();
		}
	}
	MutexClientOperation.unlock();
	return MaxOpeHandleCode;
}
void	SClient::AddClientOperation(ClientOperation *r)
{
	MutexClientOperation.lock();
	AppendList(r);
	MutexClientOperation.unlock();
}
void	SClient::DelClientOperation(ClientOperation *r)
{
	MutexClientOperation.lock();
	RemoveList(r);
	MutexClientOperation.unlock();
}
void	SClient::RemoveClientOperation(const QString &TableName)
{
	MutexClientOperation.lock();
	for(ClientOperation *r=GetFirst();r!=NULL;r=r->GetNext()){
		if(r->GetTableStr()==TableName){
			RemoveList(r);
			delete	r;
			break;
		}
	}
	MutexClientOperation.unlock();
}
ClientOperation	*SClient::GetClientOperation(int OpeHandleCode)
{
	ClientOperation *Ret=NULL;
	MutexClientOperation.lock();
	for(ClientOperation *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetOpeHandleCode()==OpeHandleCode){
			Ret=c;
		}
	}
	MutexClientOperation.unlock();
	return Ret;
}

bool	SClient::EnumTables(const QString &TableNameFilter ,QStringList &RetStringList)
{
	Parent->SendCommandWriteOut();
	if(TableNameFilter.isEmpty()==true){
		QStringList	Roots=Parent->GetRootPath();
		for(int i=0;i<Roots.count();i++){
			QStringList	FileSearchFilter;
			FileSearchFilter.append(QString("*.")+Parent->GetExtension());
			QDir	SearchName(Roots[i]);
			QStringList	FileList=SearchName.entryList(FileSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
			for(int j=0;j<FileList.count();j++){
				QFileInfo	LInfo(FileList[j]);
				QString		LBase=LInfo.baseName();
				if(LBase.isEmpty()==false){
					RetStringList.append(LBase);
				}
			}
		}
	}
	else{
		QStringList	Roots=Parent->GetRootPath();
		for(int k=0;k<Roots.count();k++){
			QString		RootPath=Roots[k];
			QDir		DPath(RootPath);
			QStringList	FolderFilter;
			FolderFilter.append(TableNameFilter);
			QStringList	PathList=DPath.entryList(FolderFilter,QDir::Dirs | QDir::NoDotAndDotDot);
			for(int i=0;i<PathList.count();i++){
				QStringList	FileSearchFilter;
				FileSearchFilter.append(QString("*.")+Parent->GetExtension());
				QString	AbsPath=RootPath+::GetSeparator()+PathList[i];
				QDir	SearchName(AbsPath);
				QStringList	FileList=SearchName.entryList(FileSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
				for(int j=0;j<FileList.count();j++){
					QFileInfo	LInfo(AbsPath+::GetSeparator()+FileList[j]);
					QString		LBase=LInfo.baseName();
					int	LenHead	=RootPath.count();
					QString		FilePath=LInfo.absolutePath();
					QString		FilePath2=FilePath.remove(0,LenHead+1);
					if(FilePath2.isEmpty()==true){
						RetStringList.append(LBase);
					}
					else{
						QString		FinalTableStr=FilePath2+::GetSeparator()+LBase;
						RetStringList.append(FinalTableStr);
					}
				}
			}
		}
	}
	return true;
}

bool	SClient::DeleteTable(const QString &TableStr)
{
	Parent->CloseAllOperation(TableStr);
	QStringList	Roots=Parent->GetRootPath();
	for(int k=0;k<Roots.count();k++){
		QString		RootPath=Roots[k];
		QString	AbsFileName=RootPath+::GetSeparator()+TableStr+QString(".")+Parent->GetExtension();
		if(QFile::exists(AbsFileName)==true){
			QFile	File(AbsFileName);
			bool	Ret=File.remove();
			if(Ret==true){
				//フォルダ内のファイル数が０のとき、フォルダ削除
				QFileInfo	FInfo(AbsFileName);
				QDir	SearchDir(FInfo.absolutePath());
				QStringList	NameFilter;
				NameFilter.append(QString("*.")+Parent->GetExtension());
				QStringList	FileList=SearchDir.entryList(NameFilter,QDir::Files | QDir::NoDotAndDotDot);
				if(FileList.count()==0){
					SearchDir.rmdir(FInfo.absolutePath());
				}
			}
			return Ret;
		}
	}
	return false;
}

bool	SClient::FindTable(const QString &TableStr,bool &Ret)
{
	Parent->CloseAllOperation(TableStr);
	QStringList	Roots=Parent->GetRootPath();
	for(int k=0;k<Roots.count();k++){
		QString		RootPath=Roots[k];
		QString	AbsFileName=RootPath+::GetSeparator()+TableStr+QString(".")+Parent->GetExtension();
		if(QFile::exists(AbsFileName)==true){
			Ret=true;
			return true;
		}
	}
	Ret=false;
	
	return true;
}

bool	SClient::GetTableAllData	(const QString &TableStr ,QByteArray &AllData)
{
	Parent->SendCommandWriteOut();
	Parent->SaveOpenedTable(TableStr);
	QStringList	Roots=Parent->GetRootPath();
	for(int k=0;k<Roots.count();k++){
		QString		RootPath=Roots[k];
		QString	AbsFileName=RootPath+::GetSeparator()+TableStr+QString(".")+Parent->GetExtension();
		if(QFile::exists(AbsFileName)==true){
			QFile	File(AbsFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				AllData=File.readAll();
				return true;
			}
		}
	}
	return false;
}

bool	SClient::ReplaceTableAllData(const QString &TableStr ,QByteArray &AllData)
{
	Parent->CloseAllOperation(TableStr);
	QStringList	Roots=Parent->GetRootPath();
	bool	Wrote=false;
	for(int k=0;k<Roots.count();k++){
		QString		RootPath=Roots[k];
		QString	AbsFileName=RootPath+::GetSeparator()+TableStr+QString(".")+Parent->GetExtension();
		if(QFile::exists(AbsFileName)==true){
			QFileInfo	FInfo(AbsFileName);
			ForceDirectories(FInfo.absolutePath());

			QFile	File(AbsFileName);
			if(File.open(QIODevice::WriteOnly)==true){
				Wrote=true;
				File.write(AllData);
				return true;
			}
		}
	}
	if(Wrote==false){
		QString		RootPath=Roots[0];
		QString	AbsFileName=RootPath+::GetSeparator()+TableStr+QString(".")+Parent->GetExtension();

		QFileInfo	FInfo(AbsFileName);
		ForceDirectories(FInfo.absolutePath());

		QFile	File(AbsFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			Wrote=true;
			File.write(AllData);
			return true;
		}
	}
	return false;
}

void	SClient::CloseAllOperation(const QString &TableStr)
{
	ReTry:;
	for(ClientOperation *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetTableStr()==TableStr){
			DelClientOperation(c);
			goto	ReTry;
		}
	}
	CheckUnsedTable();
}
	
void	SClient::HaltCommandAnalyzer(void)
{
	ExeProg.Halt=true3;
	while(ExeProg.Halt==true3){
		GSleep(10);
	}
}

void	SClient::RestartCommandAnalyzer(void)
{
	ExeProg.Halt=none3;
	GSleep(20);
}

void	SClient::CheckUnsedTable(void)
{
	emit	SignalCheckUnsedTable();
}

//===============================================================
ThreadServerComm::ThreadServerComm(QObject *parent ,XMLServerComm *server)
	:QThread(parent),Server(server)
{
	Terminated=false;
}
	
void	ThreadServerComm::PushCommand(ThreadServerComm::ThreadServerCommCommandBase *a)
{
	CommandMutex.lock();
	CommandList.AppendList(a);
	CommandMutex.unlock();
}

ThreadServerComm::ThreadServerCommCommandBase	*ThreadServerComm::PopCommand(void)
{
	CommandMutex.lock();
	ThreadServerComm::ThreadServerCommCommandBase	*a=CommandList.GetFirst();
	if(a!=NULL){
		CommandList.RemoveList(a);
	}
	CommandMutex.unlock();
	return a;
}

void	ThreadServerComm::run()
{
	while(Terminated==false){
		ThreadServerComm::ThreadServerCommCommandBase	*a;
		while((a=PopCommand())!=NULL){
			a->Execute();
			delete	a;
			if(Terminated==true)
				return;
		}
		msleep(100);
		Server->StepProgress();
	}
}

ThreadServerComm::ThreadSaveDeleteTable::ThreadSaveDeleteTable(ThreadServerComm *parent ,XMLElementRoot *root)
	:ThreadServerCommCommandBase(parent),Root(root)
{
}

void	ThreadServerComm::ThreadSaveDeleteTable::Execute(void)
{
	//GSleep(50);
	if(Root->IsModified()==true){
		Root->TableReadLock();
		Root->SaveFile();
		Root->TableUnLock();
	}
	//GSleep(50);
	delete	Root;
	Root=NULL;

	GetServer()->ShowClient();
}


//===============================================================

XMLCommandExecuter::XMLCommandExecuter(SClient *parent ,XMLServerComm *grandParent)
:Comm(parent),GrandParent(grandParent)
{
	Terminated=false;
	connect(this,SIGNAL(SignalShowClient(int)),grandParent,SLOT(SlotShowClient(int)),Qt::QueuedConnection);
	Halt=none3;
}

void	XMLCommandExecuter::LogOut(const QString &Cmd,bool Result)
{
	QStringList	Msgs;
	Msgs.append(Cmd);
	GetServer()->GetLogger()->AddLog(-1,Msgs,Result);
}

void	XMLCommandExecuter::LogOut(const QString &Cmd ,const QStringList &Msg,bool Result)
{
	QStringList	Msgs;
	Msgs.append(Cmd);
	Msgs.append(Msg);
	GetServer()->GetLogger()->AddLog(-1,Msgs,Result);
}


void	XMLCommandExecuter::run()
{
	while(Terminated==false){
		if(Halt==true3){
			Halt=false3;
			while(Halt==false3){
				msleep(10);
			}
		}
		RecList	*R=Comm->UnpackTopRxBuff();
		if(R!=NULL){
			const char	*EmitterRoot;
			char	EmitterRootBuff[100];
			const char	*EmitterName;
			char	EmitterNameBuff[100];
			const char	*CmdClass;
			char	CmdClassBuff[100];
			BYTE	*fp	=R->GetClassNamePointer(EmitterRootBuff ,EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
			if(fp==NULL){
				delete	R;
				return;
			}

			ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
			if(ErrorData.GetLevel()!=ErrorCodeList::_None){
				fp	=R->GetError(fp,ErrorData);
			}
			GrandParent->Accessed		=true;
			GrandParent->LastAccessTime	=GetComputerMiliSec();

			EmitterRoot	=EmitterRootBuff;
			EmitterName	=EmitterNameBuff;
			CmdClass	=CmdClassBuff;
			QBuffer buff;
			R->GetPointer(fp ,buff);
			buff.open(QIODevice::ReadOnly);
			Analize(R->GlobalPage ,R->Cmd ,buff);
			Comm->LastAccessTime=XDateTime::currentDateTime();
			delete	R;
			emit	SignalShowClient(Comm->GetID());
		}
		msleep(10);
	}		
}

void	XMLCommandExecuter::TxData(XMLTxQueueList *r)
{
	Comm->XMLTxQueue.Push(r);
	emit	SignalTx();
}

bool	XMLCommandExecuter::GetShowCommandList(void)
{
	return GrandParent->GetShowCommandList();
}

XMLTxQueueList::XMLTxQueueList(int Cmd, int opeHandleCode)
{
	cmd=Cmd;
	OpeHandleCode=opeHandleCode;
	Buff.open(QIODevice::WriteOnly);
}

bool	XMLCommandExecuter::Analize(int32 OpeHandleCode,int32 Cmd, QBuffer &Buff)
{
	int32	OpCmd;
	ErrorCodeList ErrorData;
	DWORD	CurrentTime=GetComputerMiliSec();
	QString	ErrorMsg;
	QString	CommandMsg;
	
	if(Cmd==XML_Server_OpenConnection){
		int32	ClientID=Comm->GetID();
		LogOut("OpenConnection",true);
		if(GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), ClientID, -1, "Open connection",GetComputerMiliSec()-CurrentTime);
		}
		XMLTxQueueList	*r=new XMLTxQueueList(XML_Server_OpenConnection,-1);
		::Save(&r->Buff,ClientID);
		TxData(r);
		return true;
	}
	else if(Cmd==XML_Operation_OpenOperation){
		QString	TableStr;
		bool	Ret=false;
		OpeHandleCode=-1;
		CommandMsg	="Open Operation";
		if(::Load(&Buff,TableStr)==true){
			OpeHandleCode=Comm->GetMaxOpeHandleCode()+1;
			//GrandParent->LockForRead();
			ClientOperation	*r=new ClientOperation(OpeHandleCode,TableStr,Comm);
			//GrandParent->Unlock();
			r->LogOut("OpenOperation",true);
			Comm->AddClientOperation(r);
			Ret=true;
		}
		else{
			LogOut("Error OpenOperation",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_OpenOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +QString("Not found TableStr");
		}
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_OpenOperationAgain){
		QString	TableStr;
		bool	Ret=false;
		CommandMsg	="Open Operation Again";
		if(::Load(&Buff,TableStr)==true){
			//GrandParent->LockForRead();
			ClientOperation	*r=new ClientOperation(OpeHandleCode,TableStr,Comm);
			//GrandParent->Unlock();
			r->LogOut("OpenOperationAgain",true);
			Comm->AddClientOperation(r);
			Ret=true;
		}
		else{
			LogOut("Error OpenOperation",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_OpenOperationAgain,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +QString("Not found TableStr");
		}
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_DupOperation){
		bool	Ret=false;
		int32	dOpeHandleCode=-1;
		QString	TmpOpeHandleTableStr;
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		CommandMsg	="Dup Operation";
		if(sOpe!=NULL){
			dOpeHandleCode=Comm->GetMaxOpeHandleCode()+1;
			TmpOpeHandleTableStr=sOpe->GetTableStr();
			//GrandParent->LockForRead();
			ClientOperation	*r=new ClientOperation(dOpeHandleCode,TmpOpeHandleTableStr,Comm);
			//GrandParent->Unlock();

			QStringList	LogMsg;
			if(GetServer()->LogOut==true){
				LogMsg.append(QString("Source Handle : ")+QString::number(OpeHandleCode));
				if(GetServer()->LogDetail==true){
					LogMsg.append(QString("Dup table : ")+TmpOpeHandleTableStr);
				}
			}
			if(r->CopyDupFrom(sOpe)==true){
				r->LogOut("DupOperation",LogMsg,true);
				Comm->AddClientOperation(r);
				Ret=true;
			}
			else{
				r->LogOut("DupOperation",LogMsg,false);
			}
		}
		else{
			LogOut("Error DupOperation",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_DupOperation,dOpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +QString("Not found OpeHandle");
		}
		::Save(&s->Buff,TmpOpeHandleTableStr);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), dOpeHandleCode,CommandMsg ,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_CloseOperation){
		bool	Ret=false;
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		CommandMsg	="Close Operation";
		if(sOpe!=NULL){
			sOpe->LogOut("CloseOperation",true);
			Comm->DelClientOperation(sOpe);
			Comm->CheckUnsedTable();
			delete	sOpe;
			Ret=true;
		}
		else{
			LogOut("Error CloseOperation",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_CloseOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +QString("Not found OpeHandle");
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_SelectOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QStringList	RetStringList;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	OutputStr;
			QString	SelectStr;
			QString	OrderStr;
			QStringList	Msgs;
			if(::Load(&Buff,OutputStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: ")+OutputStr);
				}
				if(::Load(&Buff,SelectStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: ")+SelectStr);
					}
					if(::Load(&Buff,OrderStr)==true){
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: ")+OrderStr);
						}
						Ret=sOpe->Select(OutputStr,SelectStr,OrderStr,RetStringList,ErrorMsg);
						CommandMsg	="Select";
						if(Ret==true){
							if(GetServer()->LogOut==true){
								if(GetServer()->LogDetail==true){
									for(int i=0;i<RetStringList.count();i++){
										Msgs.append(QString("OutResult: ")+RetStringList[i]);
									}
								}
							}
							LogOut("Select",Msgs,true);
						}
						else{
							if(GetServer()->LogOut==true){
								Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
							}
							LogOut("Select",Msgs,false);
						}
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: Error"));
						}
						LogOut("Error Select",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: Error"));
					}
					LogOut("Error Select",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: Error"));
				}
				LogOut("Error Select",Msgs,false);
			}
		}
		else{
			LogOut("Error Select : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_SelectOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetStringList);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode,CommandMsg ,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_SelectFirstOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	OutputStr;
			QString	SelectStr;
			QString	OrderStr;
			QStringList	Msgs;
			if(::Load(&Buff,OutputStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: ")+OutputStr);
				}
				if(::Load(&Buff,SelectStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: ")+SelectStr);
					}
					if(::Load(&Buff,OrderStr)==true){
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: ")+OrderStr);
						}
						Ret=sOpe->SelectFirst(OutputStr,SelectStr,OrderStr,RetString,ErrorMsg);
						CommandMsg	="SelectFirst";
						if(Ret==true){
							if(GetServer()->LogOut==true){
								if(GetServer()->LogDetail==true){
									Msgs.append(QString("OutResult: ")+RetString);
								}
							}
							LogOut("SelectFirst",Msgs,true);
						}
						else{
							if(GetServer()->LogOut==true){
								Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
							}
							LogOut("SelectFirst",Msgs,false);
						}
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: Error"));
						}
						LogOut("Error SelectFirst",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: Error"));
					}
					LogOut("Error SelectFirst",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: Error"));
				}
				LogOut("Error SelectFirst",Msgs,false);
			}
		}
		else{
			LogOut("Error SelectFirst : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_SelectFirstOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_SelectLastOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	OutputStr;
			QString	SelectStr;
			QString	OrderStr;
			QStringList	Msgs;
			if(::Load(&Buff,OutputStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: ")+OutputStr);
				}
				if(::Load(&Buff,SelectStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: ")+SelectStr);
					}
					if(::Load(&Buff,OrderStr)==true){
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: ")+OrderStr);
						}
						Ret=sOpe->SelectLast(OutputStr,SelectStr,OrderStr,RetString,ErrorMsg);
						CommandMsg	="SelectLast";
						if(Ret==true){
							if(GetServer()->LogOut==true){
								if(GetServer()->LogDetail==true){
									Msgs.append(QString("OutResult: ")+RetString);
								}
							}
							LogOut("SelectLast",Msgs,true);
						}
						else{
							if(GetServer()->LogOut==true){
								Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
							}
							LogOut("SelectLast",Msgs,false);
						}
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: Error"));
						}
						LogOut("Error SelectLast",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: Error"));
					}
					LogOut("Error SelectLast",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: Error"));
				}
				LogOut("Error SelectLast",Msgs,false);
			}
		}
		else{
			LogOut("Error SelectLast : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_SelectLastOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_SelectNextOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			Ret=sOpe->SelectNext(RetString,ErrorMsg);
			CommandMsg	="SelectNext";
			if(Ret==true){
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					if(GetServer()->LogDetail==true){
						Msgs.append(QString("OutResult: ")+RetString);
					}
					LogOut("SelectNext",Msgs,true);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					LogOut("SelectNext",Msgs,false);
				}
			}
		}
		else{
			LogOut("Error SelectNext : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_SelectNextOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_SelectPrevOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			Ret=sOpe->SelectPrev(RetString,ErrorMsg);
			CommandMsg	="SelectPrev";
			if(Ret==true){
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					if(GetServer()->LogDetail==true){
						Msgs.append(QString("OutResult: ")+RetString);
					}
					LogOut("SelectPrev",Msgs,true);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					LogOut("SelectPrev",Msgs,false);
				}
			}
		}
		else{
			LogOut("Error SelectPrev : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_SelectPrevOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_ChildSelectOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QStringList	RetStringList;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	OutputStr;
			QString	SelectStr;
			QString	OrderStr;
			QStringList	Msgs;
			if(::Load(&Buff,OutputStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: ")+OutputStr);
				}
				if(::Load(&Buff,SelectStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: ")+SelectStr);
					}
					if(::Load(&Buff,OrderStr)==true){
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: ")+OrderStr);
						}
						Ret=sOpe->ChildSelect(OutputStr,SelectStr,OrderStr,RetStringList,ErrorMsg);
						CommandMsg	="ChildSelect";
						if(Ret==true){
							if(GetServer()->LogOut==true){
								if(GetServer()->LogDetail==true){
									for(int i=0;i<RetStringList.count();i++){
										Msgs.append(QString("OutResult: ")+RetStringList[i]);
									}
								}
							}
							LogOut("ChildSelect",Msgs,true);
						}
						else{
							if(GetServer()->LogOut==true){
								Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
							}
							LogOut("ChildSelect",Msgs,false);
						}
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: Error"));
						}
						LogOut("Error ChildSelect",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: Error"));
					}
					LogOut("Error ChildSelect",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: Error"));
				}
				LogOut("Error ChildSelect",Msgs,false);
			}
		}
		else{
			LogOut("Error ChildSelect : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_ChildSelectOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetStringList);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_ChildSelectFirstOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	OutputStr;
			QString	SelectStr;
			QString	OrderStr;
			QStringList	Msgs;
			if(::Load(&Buff,OutputStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: ")+OutputStr);
				}
				if(::Load(&Buff,SelectStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: ")+SelectStr);
					}
					if(::Load(&Buff,OrderStr)==true){
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: ")+OrderStr);
						}
						Ret=sOpe->ChildSelectFirst(OutputStr,SelectStr,OrderStr,RetString,ErrorMsg);
						CommandMsg	="ChildSelectFirst";
						if(Ret==true){
							if(GetServer()->LogOut==true){
								if(GetServer()->LogDetail==true){
									Msgs.append(QString("OutResult: ")+RetString);
								}
							}
							LogOut("ChildSelectFirst",Msgs,true);
						}
						else{
							if(GetServer()->LogOut==true){
								Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
							}
							LogOut("ChildSelectFirst",Msgs,false);
						}
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: Error"));
						}
						LogOut("Error ChildSelectFirst",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: Error"));
					}
					LogOut("Error ChildSelectFirst",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: Error"));
				}
				LogOut("Error ChildSelectFirst",Msgs,false);
			}
		}
		else{
			LogOut("Error ChildSelectFirst : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_ChildSelectFirstOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_ChildSelectLastOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	OutputStr;
			QString	SelectStr;
			QString	OrderStr;
			QStringList	Msgs;
			if(::Load(&Buff,OutputStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: ")+OutputStr);
				}
				if(::Load(&Buff,SelectStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: ")+SelectStr);
					}
					if(::Load(&Buff,OrderStr)==true){
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: ")+OrderStr);
						}
						Ret=sOpe->ChildSelectLast(OutputStr,SelectStr,OrderStr,RetString,ErrorMsg);
						CommandMsg	="ChildSelectLast";
						if(Ret==true){
							if(GetServer()->LogOut==true){
								if(GetServer()->LogDetail==true){
									Msgs.append(QString("OutResult: ")+RetString);
								}
							}
							LogOut("ChildSelectLast",Msgs,true);
						}
						else{
							if(GetServer()->LogOut==true){
								Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
							}
							LogOut("ChildSelectLast",Msgs,false);
						}
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("Order: Error"));
						}
						LogOut("Error ChildSelectLast",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Select: Error"));
					}
					LogOut("Error ChildSelectLast",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Output: Error"));
				}
				LogOut("Error ChildSelectLast",Msgs,false);
			}
		}
		else{
			LogOut("Error ChildSelectLast : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_ChildSelectLastOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_ChildSelectNextOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			Ret=sOpe->ChildSelectNext(RetString,ErrorMsg);
			CommandMsg	="ChildSelectNext";
			if(Ret==true){
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					if(GetServer()->LogDetail==true){
						Msgs.append(QString("OutResult: ")+RetString);
					}
					LogOut("ChildSelectNext",Msgs,true);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					LogOut("ChildSelectNext",Msgs,false);
				}
			}
		}
		else{
			LogOut("Error ChildSelectNext : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_ChildSelectNextOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_ChildSelectPrevOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		QString	RetString;
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			Ret=sOpe->ChildSelectPrev(RetString,ErrorMsg);
			CommandMsg	="ChildSelectPrev";
			if(Ret==true){
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					if(GetServer()->LogDetail==true){
						Msgs.append(QString("OutResult: ")+RetString);
					}
					LogOut("ChildSelectPrev",Msgs,true);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					LogOut("ChildSelectPrev",Msgs,false);
				}
			}
		}
		else{
			LogOut("Error ChildSelectPrev : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_ChildSelectPrevOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetString);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_InsertOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		QString	InsertedStr;
		QString	WhereStr;
		QStringList	Msgs;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			if(::Load(&Buff,WhereStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Where: ")+WhereStr);
				}
				if(::Load(&Buff,InsertedStr)==true){
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Inserted: ")+InsertedStr);
					}
					Ret=sOpe->Insert(WhereStr,InsertedStr,ErrorMsg);
					CommandMsg	="InsertXML";
					if(Ret==true){
						LogOut("InsertXML",Msgs,true);
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
						}
						LogOut("InsertXML",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Inserted: Error"));
					}
					LogOut("InsertXML",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Where: Error"));
				}
				LogOut("InsertXML",Msgs,false);
			}
		}
		else{
			LogOut("Error InsertXML : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_InsertOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_InsertMultiOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		QStringList	InsertedStrs;
		QString	WhereStr;
		QStringList	Msgs;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			if(::Load(&Buff,WhereStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Where: ")+WhereStr);
				}
				if(::Load(&Buff,InsertedStrs)==true){
					if(GetServer()->LogOut==true){
						if(GetServer()->LogDetail==true){
							for(int i=0;i<InsertedStrs.count();i++){
								Msgs.append(QString("Inserted: ")+InsertedStrs[i]);
							}
						}
					}
					Ret=sOpe->Insert(WhereStr,InsertedStrs,ErrorMsg);
					CommandMsg	="InsertXML multi";
					if(Ret==true){
						LogOut("InsertXMLmulti",Msgs,true);
					}
					else{
						if(GetServer()->LogOut==true){
							Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
						}
						LogOut("InsertXMLmulti",Msgs,false);
					}
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("Inserted: Error"));
					}
					LogOut("InsertXMLmulti",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("Where: Error"));
				}
				LogOut("InsertXMLmulti",Msgs,false);
			}
		}
		else{
			LogOut("Error InsertXMLmulti : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_InsertMultiOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_CopyPointerFromChild){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			Ret=sOpe->CopyPointerFromChild(ErrorMsg);
			CommandMsg	="CopyPointerFromChild";
			if(Ret==true){
				LogOut("CopyPointerFromChild",true);
			}
			else{
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					LogOut("CopyPointerFromChild",Msgs,false);
				}
			}
		}
		else{
			LogOut("Error CopyPointerFromChild : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_CopyPointerFromChild,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_UpdateOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QString	UpdatedStr;
			QStringList	Msgs;
			if(::Load(&Buff,UpdatedStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("UpdatedStr: ")+UpdatedStr);
				}
				Ret=sOpe->Update(UpdatedStr,ErrorMsg);
				CommandMsg	="UpdateXML";
				if(Ret==true){
					LogOut("UpdateXML",Msgs,true);
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					}
					LogOut("UpdateXML",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("UpdatedStr: Error"));
				}
				LogOut("UpdateXML",Msgs,false);
			}
		}
		else{
			LogOut("Error UpdateXML : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_UpdateOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_DeleteOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			Ret=sOpe->Delete(ErrorMsg);
			CommandMsg	="DeleteXML";
			if(Ret==true){
				LogOut("DeleteXML",true);
			}
			else{
				if(GetServer()->LogOut==true){
					QStringList	Msgs;
					Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					LogOut("DeleteXML",false);
				}
			}
		}
		else{
			LogOut("Error DeleteXML : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_DeleteOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_DeleteAllOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		QString	WhereStr;
		QStringList	Msgs;
		if(sOpe!=NULL){
			if(::Load(&Buff,WhereStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("WhereStr: ")+WhereStr);
				}
				Ret=sOpe->Delete(WhereStr,ErrorMsg);
				CommandMsg	="DeleteXML";
				if(Ret==true){
					LogOut("DeleteXML",Msgs,true);
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					}
					LogOut("DeleteXML",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("WhereStr: Error"));
				}
				LogOut("DeleteXML",Msgs,false);
			}
		}
		else{
			LogOut("Error DeleteXML : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_DeleteAllOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_InsUpdateAttrOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		QStringList	Msgs;
		if(sOpe!=NULL){
			QString	InsertedStr;
			if(::Load(&Buff,InsertedStr)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("InsertedStr: ")+InsertedStr);
				}
				Ret=sOpe->InsUpdateAttr(InsertedStr,ErrorMsg);
				CommandMsg	="InsUpdateAttr";
				if(Ret==true){
					LogOut("InsUpdateAttr",Msgs,true);
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					}
					LogOut("InsUpdateAttr",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("InsertedStr: Error"));
				}
				LogOut("InsUpdateAttr",Msgs,false);
			}
		}
		else{
			LogOut("Error InsUpdateAttr : Invalid OpeHandle",false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_InsUpdateAttrOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_DeleteAttrOperation){
		ClientOperation	*sOpe=Comm->GetClientOperation(OpeHandleCode);
		bool	Ret=false;
		CommandMsg	="No OpeHandle or Error";
		if(sOpe!=NULL){
			QStringList	Msgs;
			QString	DeletedString;
			if(::Load(&Buff,DeletedString)==true){
				if(GetServer()->LogOut==true){
					Msgs.append(QString("DeletedStr: ")+DeletedString);
				}
				Ret=sOpe->DeleteAttr(DeletedString,ErrorMsg);
				CommandMsg	="DeleteAttr";
				if(Ret==true){
					LogOut("DeleteAttr",Msgs,true);
				}
				else{
					if(GetServer()->LogOut==true){
						Msgs.append(QString("ErrorMsg: ")+ErrorMsg);
					}
					LogOut("DeleteAttr",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("DeletedStr: Error"));
				}
				LogOut("DeleteAttr",Msgs,false);
			}
		}
		else{
			LogOut("Error DeleteAttr : Invalid OpeHandle",false);
		}		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_DeleteAttrOperation,OpeHandleCode);
		if(Ret==false){
			s->ErrorData.SetError(XML_ErrorFormat ,ErrorMsg,ErrorCodeList::_Critical,QDateTime::currentDateTime());
			CommandMsg	=QString("Error:") +ErrorMsg;
		}
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), OpeHandleCode, CommandMsg,GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Server_EnumTables){
		QString	FilterStr;
		bool	Ret=false;
		QStringList	RetStringList;
		QStringList	Msgs;
		if(::Load(&Buff,FilterStr)==true){
			if(GetServer()->LogOut==true){
				Msgs.append(QString("FilterStr: ")+FilterStr);
			}
			Ret=Comm->EnumTables(FilterStr,RetStringList);
			if(Ret==true){
				if(GetServer()->LogOut==true){
					if(GetServer()->LogDetail==true){
						for(int i=0;i<RetStringList.count();i++){
							Msgs.append(QString("OutResult: ")+RetStringList[i]);
						}
					}
				}
				LogOut("EnumTables",Msgs,true);
			}
			else{
				LogOut("EnumTables",Msgs,false);
			}
		}
		else{
			if(GetServer()->LogOut==true){
				Msgs.append(QString("FilterStr: Error"));
			}
			LogOut("EnumTables",Msgs,false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Server_EnumTables,-1);
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,RetStringList);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), -1, "EnumTables",GetComputerMiliSec()-CurrentTime);
		}
		return true;

	}
	else if(Cmd==XML_Operation_GetTableAllData){
		bool	Ret=false;
		QString	TableStr;
		QByteArray	AllData;
		QStringList	Msgs;
		if(::Load(&Buff,TableStr)==true){
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: ")+TableStr);
			}
			Ret=Comm->GetTableAllData(TableStr,AllData);
			if(Ret==true){
				LogOut("GetTableAllData",Msgs,true);
			}
			else{
				LogOut("GetTableAllData",Msgs,false);
			}
		}
		else{
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: Error"));
			}
			LogOut("GetTableAllData",Msgs,false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_GetTableAllData,-1);
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,AllData);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), -1, "GetTableAllData",GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_ReplaceTableAllData){
		bool	Ret=false;
		QString	TableStr;
		QByteArray	AllData;
		QStringList	Msgs;
		if(::Load(&Buff,TableStr)==true){
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: ")+TableStr);
			}
			if(::Load(&Buff,AllData)==true){
				Ret=Comm->ReplaceTableAllData(TableStr,AllData);
				if(Ret==true){
					LogOut("ReplaceTableAllData",Msgs,true);
				}
				else{
					LogOut("ReplaceTableAllData",Msgs,false);
				}
			}
			else{
				if(GetServer()->LogOut==true){
					Msgs.append(QString("AllData: Error"));
				}
				LogOut("ReplaceTableAllData",Msgs,false);
			}
		}
		else{
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: Error"));
			}
			LogOut("ReplaceTableAllData",Msgs,false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_ReplaceTableAllData,-1);
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), -1, "ReplaceTableAllData",GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_DeleteTable){
		bool	Ret=false;
		QString	TableStr;
		QStringList	Msgs;
		if(::Load(&Buff,TableStr)==true){
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: ")+TableStr);
			}
			Ret=Comm->DeleteTable(TableStr);
			if(Ret==true){
				LogOut("DeleteTable",Msgs,true);
			}
			else{
				LogOut("DeleteTable",Msgs,false);
			}
		}
		else{
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: Error"));
			}
			LogOut("DeleteTable",Msgs,false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_DeleteTable,-1);
		::Save(&s->Buff,Ret);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), -1, "DeleteTable",GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	else if(Cmd==XML_Operation_FindTable){
		bool	Ret=false;
		QString	TableStr;
		QStringList	Msgs;
		bool	mRet=false;
		if(::Load(&Buff,TableStr)==true){
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: ")+TableStr);
			}
			Ret=Comm->FindTable(TableStr,mRet);
			if(Ret==true){
				LogOut("FindTable",Msgs,true);
			}
			else{
				LogOut("FindTable",Msgs,false);
			}
		}
		else{
			if(GetServer()->LogOut==true){
				Msgs.append(QString("TableStr: Error"));
			}
			LogOut("FindTable",Msgs,false);
		}
		XMLTxQueueList	*s=new XMLTxQueueList(XML_Operation_FindTable,-1);
		::Save(&s->Buff,Ret);
		::Save(&s->Buff,mRet);
		TxData(s);
		if(Ret==false || GetShowCommandList()==true){
			emit	SignalAnalize(QDateTime::currentDateTime(), Comm->GetID(), -1, "FindTable",GetComputerMiliSec()-CurrentTime);
		}
		return true;
	}
	return false;
}
