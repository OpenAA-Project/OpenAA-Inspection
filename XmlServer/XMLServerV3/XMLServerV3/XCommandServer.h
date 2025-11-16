#if	!defined(XCOMMANDSERVER_H)
#define	XCOMMANDSERVER_H

#include "XFastComm.h"
#include <QThread>
#include "XParamBase.h"
#include "XMLConstruction.h"
#include "XErrorCode.h"
#include "XCommunicatedServer.h"

class	XMLServerComm;
class	XMLServerV3;
class	SClient;
class	ThreadLogger;

const	int		MaxXMLCharactersInSentense	=1000000;
const	int		MaxSelectedSentenses		=1000000;
const	int		CommunicatedServerPort		=12349;

class	XMLTxQueueList : public NPList<XMLTxQueueList>
{
public:
	int		cmd;
	int		OpeHandleCode;
	QBuffer	Buff;
	ErrorCodeList ErrorData;

	XMLTxQueueList(int Cmd, int opeHandleCode);
};

class	XMLTxQueueListContainer : public NPListPack<XMLTxQueueList>
{
	QMutex	AccessMutex;
public:
	XMLTxQueueListContainer(void){}

	void	Push(XMLTxQueueList *s);
	XMLTxQueueList	*Pop(void);
};

//=====================================================================================
class	XMLCommandExecuter : public QThread
{
    Q_OBJECT
		
	SClient	*Comm;
	XMLServerComm *GrandParent;
public:
	volatile	bool	Terminated;
	volatile	bool3	Halt;

	XMLCommandExecuter(SClient *parent ,XMLServerComm *grandParent);

	virtual	void	run();

private:
	bool	Analize(int32 OpeHandleCode,int32 Cmd,QBuffer &Buff);

	void	TxData(XMLTxQueueList *r);
	bool	GetShowCommandList(void);
	XMLServerComm *GetServer(void)	{	return GrandParent;	}

public:
	void	LogOut(const QString &Cmd ,bool Result);
	void	LogOut(const QString &Cmd ,const QStringList &Msg,bool Result);

signals:
	void	SignalShowClient(int id);
	void	SignalTx();
	void	SignalAnalize(QDateTime tm , int ClientID, int OpeHandleCode, QString Command,int milisec);
};

class	ClientOperation : public NPList<ClientOperation>
{
	SClient		*Parent;
	int			OpeHandleCode;
	QString		TableStr;

	XMLElement			*SelectElement;
	OutputFormat		*OutputElement;
	OrderAttrsContainer	*OrderAttrs;

	int			CurrentPoint;
	XMLElement	**SortDim;
	int			SortDimCount;

	int			ChildCurrentPoint;
	XMLElement	**ChildSortDim;
	int			ChildSortDimCount;

	bool		RebuildMode;
	bool		RebuildChildMode;

	XMLElement			*ChildSelectElement;
	OutputFormat		*ChildOutputElement;
	OrderAttrsContainer	*ChildOrderAttrs;

	int	MaxEDimCount;
	int	OmpCount;
	wchar_t	*TmpWCharBuff;

public:
	ClientOperation(int opeHandleCode,const QString &TableStr ,SClient *parent);
	~ClientOperation(void);

	int	GetOpeHandleCode(void)			{	return OpeHandleCode;	}
	const QString	&GetTableStr(void)	{	return TableStr;		}
	XMLServerComm	*GetServer(void);
	bool	CopyDupFrom(ClientOperation *src);

	bool	Select	(const QString &OutputStr
					,const QString &SelectStr
					,const QString &OrderStr
					,QStringList &RetStringList
					,QString &ErrorMsg);

	bool	SelectFirst	(const QString &OutputStr
						,const QString &SelectStr
						,const QString &OrderStr
						,QString &RetString
						,QString &ErrorMsg);

	bool	SelectLast	(const QString &OutputStr
						,const QString &SelectStr
						,const QString &OrderStr
						,QString &RetString
						,QString &ErrorMsg);

	bool	SelectNext	(QString &RetString
						,QString &ErrorMsg);

	bool	SelectPrev	(QString &RetString
						,QString &ErrorMsg);

	bool	ChildSelect	(const QString &OutputStr
						,const QString &SelectStr
						,const QString &OrderStr
						,QStringList &RetStringList
						,QString &ErrorMsg);

	bool	ChildSelectFirst(const QString &OutputStr
							,const QString &SelectStr
							,const QString &OrderStr
							,QString &RetString
							,QString &ErrorMsg);

	bool	ChildSelectLast (const QString &OutputStr
							,const QString &SelectStr
							,const QString &OrderStr
							,QString &RetString
							,QString &ErrorMsg);

	bool	ChildSelectNext	(QString &RetString
							,QString &ErrorMsg);

	bool	ChildSelectPrev	(QString &RetString
							,QString &ErrorMsg);

	bool	Insert(const QString &SelectStr
					,const QString &InsertedStr
					,QString &ErrorMsg);

	bool	Insert(const QString &SelectStr
					,const QStringList &InsertedStrs
					,QString &ErrorMsg);

	bool	Update(const QString &UpdatedStr
					,QString &ErrorMsg);

	bool	Delete(QString &ErrorMsg);
	bool	Delete(const QString &SelectStr 
					,QString &ErrorMsg);

	bool	InsUpdateAttr(const QString &InsertedStr
						,QString &ErrorMsg);

	bool	DeleteAttr(const QString &DeletedString
						,QString &ErrorMsg);

	bool	CopyPointerFromChild(QString &ErrorMsg);

private:
	bool	MakeSortDimForSelect(const QString &OutputStr
								,const QString &SelectStr
								,const QString &OrderStr
								,QString &ErrorMsg);
	bool	MakeUnSortDimForSelect(const QString &_SelectStr
								 ,QString &ErrorMsg);

	bool	MakeChildSortDimForSelect(const QString &OutputStr
									,const QString &SelectStr
									,const QString &OrderStr
									,QString &ErrorMsg);

	bool	CheckCurrentPoint(XMLElement *Ref);
	bool	CheckChildCurrentPoint(XMLElement *Ref);
	bool	RebuildCurrentPoint(void);
	bool	RebuildChildCurrentPoint(void);

public:
	void	LogOut(const QString &Cmd ,bool Result);
	void	LogOut(const QString &Cmd ,const QStringList &Msg,bool Result);
};


class	SClient : public FastCommLeaf ,public NPListPack<ClientOperation>
{
    Q_OBJECT

	XMLCommandExecuter	ExeProg;
	QMutex	MutexClientOperation;
	XMLServerComm	*Parent;
public:
	XDateTime	LastReceivedTime;
	XMLTxQueueListContainer	XMLTxQueue;
	XDateTime		LastAccessTime;

	SClient(int id,XMLServerComm *parent);
	~SClient(void);

	XMLServerComm *GetServer(void);

	int	GetMaxOpeHandleCode(void);
	void	AddClientOperation(ClientOperation *r);
	void	DelClientOperation(ClientOperation *r);
	void	RemoveClientOperation(const QString &TableName);
	ClientOperation	*GetClientOperation(int OpeHandleCode);
	bool	IsDealingTable(const QString &TableStr);

	bool	EnumTables(const QString &TableNameFilter ,QStringList &RetStringList);
	bool	DeleteTable(const QString &TableStr);
	bool	FindTable(const QString &TableStr,bool &Ret);
	bool	GetTableAllData		(const QString &TableStr ,QByteArray &AllData);
	bool	ReplaceTableAllData	(const QString &TableStr ,QByteArray &AllData);
	void	CloseAllOperation(const QString &TableStr);

	void	CheckUnsedTable(void);
	void	HaltCommandAnalyzer(void);
	void	RestartCommandAnalyzer(void);
	void	SClientLock(void)	{	MutexClientOperation.lock();	}
	void	SClientUnlock(void)	{	MutexClientOperation.unlock();	}

signals:
	void	SignalCheckUnsedTable();
public slots:
	void	SlotTx();
};

class	ThreadServerComm : public QThread
{
	XMLServerComm	*Server;
public:
	ThreadServerComm(QObject *parent ,XMLServerComm *server);

	class	ThreadServerCommCommandBase : public NPList<ThreadServerCommCommandBase>
	{
		ThreadServerComm	*Parent;
	public:
		ThreadServerCommCommandBase(ThreadServerComm *parent):Parent(parent){}

		virtual	void	Execute(void)=0;
		XMLServerComm	*GetServer(void){	return Parent->Server;	}
	};

	class	ThreadSaveDeleteTable : public ThreadServerCommCommandBase
	{
		XMLElementRoot *Root;
	public:
		ThreadSaveDeleteTable(ThreadServerComm *parent ,XMLElementRoot *root);

		virtual	void	Execute(void);
		const QString	&GetRootTableName(void){	return Root->GetTableName();	}
	};
	class	ThreadWatchSClient
	{
		ThreadServerComm	*Parent;
	public:
		ThreadWatchSClient(ThreadServerComm *parent):Parent(parent){}

		virtual	void	Execute(void);
	};

public:
	void						PushCommand(ThreadServerCommCommandBase *a);
	ThreadServerCommCommandBase	*PopCommand(void);

	volatile	bool	Terminated;
	virtual	void	run();
private:
	QMutex		CommandMutex;
	NPListPack<ThreadServerCommCommandBase>		CommandList;
};

class	XMLServerComm : public FastComm , public ParamBase, public XMLStocker
{
	Q_OBJECT

	XMLServerV3		*Parent;
	ThreadLogger	*Logger;
	ThreadServerComm		ThreadCommand;
	CommunicatedServerComm	CommServerComm;

	int				PortNumber;
	QString			RootPathes;
	QString			Extension;
	bool			ShowCommandList;
	QTimer			TimerForBackup;
public:
	bool			LogOut;
	bool			LogDetail;
	QString			LogOutPath;
	int				LoggedDays;
	int				IdleTimeForSave;
	DWORD			LastAccessTime;
	bool			Accessed;
	int				SecondToKillByNoAccess;

	QString			CommunicatedServerIP0;
	QString			CommunicatedServerIP1;
	QString			CommunicatedServerIP2;
	QString			CommunicatedServerIP3;
	QString			CommunicatedServerIP4;
	QString			CommunicatedServerIP5;
	QString			CommunicatedServerIP6;
	QString			CommunicatedServerIP7;
	QString			CommunicatedServerIP8;
	QString			CommunicatedServerIP9;

public:
	XMLServerComm(QObject * parent);
	~XMLServerComm(void);

	void	StartServer(void);
	
	XMLServerV3		*GetParent(void)	{	return Parent;	}

	virtual	FastCommLeaf *CreateNewLeaf(int ID){		return new SClient(ID ,this);	}
	SClient	*GetSClient(int ClientID);

	virtual	QStringList	GetRootPath(void);
	virtual	QString		GetExtension(void)		{	return Extension;		}

	virtual	void	SlotReceived(int ID,int Cmd);
	virtual	void	SlotNewConnection (int id);
	virtual	void	SlotDisconnected(int id);

	virtual	QString	GetSavedFileName(void)	{	return QString("XMLServerV3Setting.dat");	}
	virtual	QString	GetDataText(void)		{	return QString("XMLServerV3Setting");		}

	void	ShowClient(int id);
	void	CloseAllOperation(const QString &TableStr);
	void	SaveOpenedTable(const QString &TableStr);

	void	SetShowCommandList(bool b)	{	ShowCommandList=b;	}
	bool	GetShowCommandList(void)	{	return ShowCommandList;	}

	ThreadLogger	*GetLogger(void)	{	return Logger;		}
	void	ShowClient(void);
	void	StepProgress(void);
	void	SendCommandWriteOut(void);

	void	LockForRead(void)	{	LockMutex.lockForRead();	}
	void	LockForWrite(void)	{	LockMutex.lockForWrite();	}
	void	Unlock(void)		{	LockMutex.unlock();	}

protected:
	virtual	QString	GetDefaultFileName(void){	return QString("XMLServerV3Setting.dat");	}
public slots:
	void	SlotShowClient(int id);
	void	SlotAnalize(QDateTime tm , int ClientID, int OpeHandleCode, QString Command ,int milisec);
	void	SlotCheckUnsedTable();
signals:
	void	SignalShowClient(int id);
	void	SignalAnalize(QDateTime tm , int ClientID, int OpeHandleCode, QString Command,int milisec);
	void	SignalProgress();
private slots:
	void	SlotTimeOut();
};

#endif