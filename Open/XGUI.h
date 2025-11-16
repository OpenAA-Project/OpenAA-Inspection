/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Open\XGUI.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XGUI_H)
#define	XGUI_H

#include "NList.h"
#include <QString>
#include <QStringList>
#include <QIODevice>
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include <QtGui>
#include <QVariant>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XMacroFunction.h"
#include "XGUIFormBase.h"
#include "XSingleExecuteBySocket.h"
#include "XDataComponent.h"
#include "XEntryPoint.h"

class	StructList;
class	GUIInitializer;
class	ErrorCodeList;
class	GUIFastComm;
class	ShowLoadingDLLForm;
class	IntegrationCommPack;
class	GUIIntegrationCommPack;
class	GuiDLLItem;
class	GuiDLLItemContainer;
class	GUILanguageContainer;


class	StructListPack : public NPListPack<StructList>
{
public:
	StructListPack(void){}
	~StructListPack(void){}

	char	*Analyze(char *fp ,DWORD &ErrorCode);
	StructListPack	&operator=(StructListPack &src);
	void	CopyFrom(StructListPack &src);

	void		GetLineNumb(int &N);
	StructList	*GetStructItem(int LineNo ,int &depthNo);
	StructList	*FindStructItem(const QString &VName);
	void	ReplaceParam(LayersBase *base);

	bool	Save(QIODevice *);
	bool	Load(QIODevice *);
private:
	StructList	*GetStructItem(int LineNo ,int &depthNo ,int &N);

};

class	StructList : public NPList<StructList>
{
public:	
	DirectValueType	VType;
	QStringList	Enum;
	QString		VName;
	void		*Variable;
	StructListPack	StructInstance;
	bool		Opened;
	bool		DeleteOk;

	StructList(void);
	~StructList(void);

	StructList	&operator=(StructList &src);
	void	CopyFrom(StructList &src);
	void	DeleteVariable(void);

	bool	Save(QIODevice *);
	bool	Load(QIODevice *);
	bool	LoadNoClear(QIODevice *);

	void	SetType(const QString &VType,void *Pointer);

	void	SetValueTo(void *v);
	void	SetValue(bool v);
	void	SetValue(BYTE v);
	void	SetValue(short v);
	void	SetValue(int32 v);
	void	SetValue(int64 v);
	void	SetValue(const QString &v);
	void	SetValue(double v);
	void	SetValue(float v);
	void	SetEnumValue(const QString &v);
	void	SetValue(const QColor &v);
	void	SetValue(const QFont &v);
	void	SetValue(const IntList &v);
	void	SetValue(const QStringList &v);
	void	SetValue(const QImage &v);
	void	SetValue(const QByteArray &v);
	void	SetTunableValue(const QStringList &v);
	void	SetFileNameValue(const QString &v);
	void	SetPathNameValue(const QString &v);
	void	SetFileNamesValue(const QStringList &v);
	void	SetIntListValue(const IntList &v);

	bool		GetBool(void);
	BYTE		GetByte(void);
	short		GetShort(void);
	int			GetInt(void);
	int32		GetInt32(void);
	int64		GetInt64(void);
	QString		GetQString(void);
	double		GetDouble(void);
	float		GetFloat(void);
	QString		GetEnum(void);
	QColor		GetColor(void);
	QFont		GetFont(void);
	QStringList	GetQStringList(void);
	QStringList	GetTunableList(void);
	IntList		GetValue(void);
	QImage		GetQImage(void);
	QByteArray	GetQByteArray(void);
	IntList		GetIntList(void);

	void	ReplaceParam(LayersBase *base);
private:
	static	void	*CreateVariable(DirectValueType c);
	QString	ReplaceParam(const QString &Src ,LayersBase *base);
};

//================================================================================
class	DelayedViewThread : public QThread
{
	Q_OBJECT

	int		WaitMilisec;
	int64	ShownInspectionID;
	GUIInstancePack	*Parent;
public:
	explicit	DelayedViewThread(GUIInstancePack *obj);
	virtual void run ();
	void	SetViewRefreshInPlayer (int64 shownInspectionID ,int Milisec);
signals:
	void	SignalViewRefreshInPlayer (int shownInspectionID);
};

class	GUIItemInstance : public QWidget ,public NPList<GUIItemInstance>
{
    Q_OBJECT
	TextMessageContainer	TextMessageContainerData;
public:
	GuiDLLItem	*DLLAccess;
	GUIFormBase	*Handle;
	StructListPack	StructInstance;
	int32			GUIPositionX1;
	int32			GUIPositionY1;
	int32			GUIPositionX2;
	int32			GUIPositionY2;
	int32			InstanceID;
	int32			ParentInstanceID;
	int32			FormBaseID;
	int32			ChildNumber;
	QString			RealName;
	QString			RealComment;
	QString			RealAlignment;
	QString			tmpComment;
	QString			tmpAlignment;
	QString			tmpName;
	GUIInstancePack	*Parent;
	
	explicit	GUIItemInstance(GUIInstancePack *p,GuiDLLItem	*seed=NULL);
	~GUIItemInstance(void);

	bool	Initial(LayersBase *Base,QWidget *parent ,DWORD &ErrorCode ,GuiDLLItem *access=NULL);
	void	Clear(void);
	bool	ReflectToFormData(DWORD &ErrorCode , GuiDLLItem *access);
	GUIItemInstance	&operator=(GUIItemInstance &src);
	GUIFormBase	*GetForm(void){	return Handle;	}
	LayersBase	*GetLayersBase(void);
	bool	HasParent(QWidget *p)	{	return Handle->HasParent(p);	}
	QString	GetDLLRoot(void);
	QString	GetDLLName(void);
	void	AssociateComponent(ComponentListContainer &List);

	void	ChangedValue(void);
	bool	SaveInstance(QIODevice *f);
	bool	LoadInstance(QIODevice *f ,QString &ErrorMsg);
	bool	SaveInstanceMessage(QIODevice *f);
	bool	LoadInstanceMessage(QIODevice *f);
	void	ReflectMessage(void);
	virtual	bool	SetLanguage(const QString &MemberName,LanguageStringList *s);
	virtual	void	PickupGUILanguage(GUILanguageContainer &GUILanguageContainerInst);

	void	ViewRefreshInPlayer		(int64 shownInspectionID);
	void	ViewOnTheWayInPlayer	(int64 shownInspectionID);
	void	RefreshByEveryInspection(int64 shownInspectionID);
	void	ViewRefreshInEdit	(void);
	void	ViewRefreshInScanning	(int64 shownInspectionID);

	void	DoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode);
	void	SetAcceptDropsForAll(void);

	void	SetGridUnitForEditMode(int n);
	int		GetGridUnitForEditMode(void);

	int		GetUnitPos(int x);
	void	InitialInPaste(int dx,int dy);
	bool	RaiseUp(void);
	void	ReplaceParam(void);
private:
	int32	GetChildNumber(void);
private slots:
	void	SlotMove();
	void	SlotRelease();
	void	SlotRaiseUp();
public slots:
	void	SlotResize();
};

class	TimerIdleFunctionList : public NPList<TimerIdleFunctionList>
{
public:
	void	(*Func)(LayersBase *base);
};

class	GUIInstancePack : public QObject 
						 ,public NPListPack<GUIItemInstance> 
						 ,public NPList<GUIInstancePack>
						 ,public ServiceForLayers
{
	Q_OBJECT
	DelayedViewThread	DThread;
public:
	enum	_FormPosition{
		_Center			=1
		,_AttachTop		=2
		,_AttachLeft	=3
		,_AttachBottom	=4
		,_AttachRight	=5
		,_None			=6
	};
	QTimer	IdleTimer;
	RootNameListContainer				AlgorithmList;
	QMutex	MutexTimerFunc;
	NPListPack<TimerIdleFunctionList>	TimerFuncList;
	GUIInitializer						*Parent;

	GUIFormBasePointerContainer	RegisteredStartByInspection	;
	GUIFormBasePointerContainer	RegisteredPreAlignment		;
	GUIFormBasePointerContainer	RegisteredAlignment			;
	GUIFormBasePointerContainer	RegisteredPreProcessing		;
	GUIFormBasePointerContainer	RegisteredProcessing		;
	GUIFormBasePointerContainer	RegisteredProcessingRevived	;
	GUIFormBasePointerContainer	RegisteredPostProcessing	;

	explicit	GUIInstancePack(LayersBase *Base,GUIInitializer *p,QObject *parent=NULL);
	virtual	~GUIInstancePack(void);

	bool	InitialLayers(QString &Msg ,bool NoDatabase=false);
	GUIInitializer	*GetParent(void)	{	return Parent;	}

	bool	SaveInstances(QIODevice *f);
	bool	LoadInstances(QIODevice *f ,QString &ErrorMsg);
	bool	LoadOnlyAlgorithm(QIODevice *f);
	void	ReflectMessage(void);
	void	SetAcceptDropsForAll(void);
	int32	GetMaxInstanceID(void);
	void	GetEntryAlgorithm(RootNameListContainer &List);
	virtual	void	AssociateComponent(ComponentListContainer &List);

	GUIFormBase	*CreateMainForm(LayersBase *LayersBasePointer ,_FormPosition Pos 
									,bool ModeAddSystemMenu=false);
	void	ShowAll(GUIFormBase	*f
					,LayersBase *LayersBasePointer
					,ParamBase *PBase
					,bool EditMode=false);
	void	ReadyParam(GUIFormBase	*f);
	void	AfterPrepare(void);
	void	AfterStartSequence(void);

	void	CloseAll(void);
	GUIItemInstance	*Search(GUIFormBase *m);

	void	ViewRefreshInPlayer		(int64 shownInspectionID);
	void	ViewOnTheWayInPlayer	(int64 shownInspectionID);
	void	RefreshByEveryInspection(int64 shownInspectionID);
	void	ViewRefreshInEdit(void);
	void	ViewRefreshInScanning	(int64 shownInspectionID);

	void	DelayedViewRefreshInPlayer(int64 shownInspectionID ,int MiliSec);
	void	DoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode);
	GUIFormBase	*GetFirstForm(void);
	GUIFormBase	*FindByName(const QString &FormRoot ,const QString &FormName ,const QString &InstName);
	GUIFormBase	*FindByName(const QString &InstName);
	void	SetAreaSizeInImagePanel(bool DrawWholeMode=false);
	int EnumGUIInst(const QString &FormRoot ,const QString &FormName ,GUIFormBase *Ret[] ,int MaxRet);
	int EnumGUIInst(GUIFormBase *Ret[] ,int MaxRet);

	void	AppendTimerFunc(void (*Func)(LayersBase *));
	void	RemoveTimerFunc(void (*Func)(LayersBase *));

	void	SetGridUnitForEditMode(int n);
	int		GetGridUnitForEditMode(void);
	void	RemoveUselessGUI(GuiDLLItem *g);

	ExeResult	ExecuteStartByInspection(void);
	ExeResult	ExecutePreAlignment		(void);
	ExeResult	ExecuteAlignment		(void);
	ExeResult	ExecutePreProcessing	(void);
	ExeResult	ExecuteProcessing		(void);
	ExeResult	ExecuteProcessingRevived(void);
	ExeResult	ExecutePostProcessing	(void);
	ExeResult	ExecuteFinished			(void);
protected slots:
	void	TimeOutForIdle(void);
	void	SlotViewRefreshInPlayer (int shownInspectionID);
	void	SlotViewOnTheWayInPlayer (int shownInspectionID);
	void	SlotViewRefreshInScanning(int shownInspectionID);

private:
	void	SetupInstance(LayersBase *LayersBasePointer ,GUIItemInstance *parent,int32 parentid ,ParamBase *PBase ,bool EditMode);
	void	ShowInstance(int32 parentid);
};

//================================================================================


class	ReplaceNameList : public NPList<ReplaceNameList>
{
public:
	QString	OldRoot;
	QString	OldName;
	QString	NewRoot;
	QString	NewName;

	ReplaceNameList(void){}

};

class	GUINameClassified : public NPList<GUINameClassified>
{
public:
	GuiDLLItem	*Point;
	explicit	GUINameClassified(GuiDLLItem *p){	Point=p;	}
};
class	GUIRootClassified : public NPList<GUIRootClassified>
{
public:
	QString	Root;
	NPListPack<GUINameClassified>	NameList;

	explicit	GUIRootClassified(const QString &root){	Root=root;	}
};


class	GUIInitializer : public ServiceForLayers
{
public:
	GuiDLLItemContainer						*GuiDLLPack;
	NPListPack<GUIInstancePack>				GUIInstanceRoot;
	NPListPack<GUIRootClassified>			RootList;
	NPListPack<ReplaceNameList>				ReplaceNameListData;

	explicit	GUIInitializer(LayersBase *base);
	~GUIInitializer(void);

	void	Release(void);

	bool	CheckSystemVersion(QStringList &Str);

	GUIInstancePack	*GetGUIInstanceRoot(void){	return GUIInstanceRoot.GetFirst();	}

	bool	Initial(LayersBase *Base,DWORD &ErrorCode,QString &ErrorMsg,bool LoadAll);
	void	InitialMultiComputer(QObject * parent);
	void	InitialMultiComputerAgain(QObject * parent);
	void	InitialIntegration(void);
	bool	CheckDuplicated(QStringList &Error);
	void	AfterStartSequence(void);

	virtual	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int CommID ,QBuffer *f
					,ErrorCodeList &ErrorData);
	virtual	bool	TxData(int32 globalPage 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,int CommID ,QByteArray *f
					,ErrorCodeList &ErrorData);
	virtual	bool	TxIntegrationData(int32 slaveNo 
					,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
					,QBuffer *f
					,ErrorCodeList &ErrorData);

	virtual	QTcpSocket	*GetSocket(int ComNo);
	virtual	QTcpSocket	*GetIntegrationSocket(int SlaveNo);

	GuiDLLItem	*Search(QString &rootName ,QString &name);
	bool	LoadReplaceNameList(FILE *file);
	bool	InitialAdditionalFieldFromGUI(QSqlDatabase &DB,QString &ErrorMsg);
	bool	CreateExcludedList(ExcludedListPack &EList);
	void	WaitReadyReadAll(int milisec);
	void	SetLanguageCode(int LanguageCode);

	void	ViewRefreshInPlayer(int64 shownInspectionID);
			//Call by ExecuteInspect without ReEntrant, 
			//it may sometimes be skipped
	void	ViewOnTheWayInPlayer(int64 shownInspectionID);
	void	RefreshByEveryInspection(int64 shownInspectionID);
			//This is absolutely called in ExecuteInspect everytime
	void	ViewRefreshInEdit(void);
	void	ViewRefreshInScanning(int64 shownInspectionID);

	void	DelayedViewRefreshInPlayer(int64 shownInspectionID ,int MiliSec);

	void	SetAcceptDropsForAll(void);

	void	SetGridUnitForEditMode(int n);
	int		GetGridUnitForEditMode(void);
	void	RemoveUselessGUI(void);
	const	GUIIntegrationCommPack	*GetIntegrationComm(void)	{	return IntegrationComm;	}

	ExeResult	ExecuteStartByInspection(void);
	ExeResult	ExecutePreAlignment		(void);
	ExeResult	ExecuteAlignment		(void);
	ExeResult	ExecutePreProcessing	(void);
	ExeResult	ExecuteProcessing		(void);
	ExeResult	ExecuteProcessingRevived(void);
	ExeResult	ExecutePostProcessing	(void);
	ExeResult	ExecuteFinished			(void);

private:
	bool	SearchAddDLL(LayersBase *Base,const QStringList &path
						,DWORD &ErrorCode ,QString &ErrorMsg,bool LoadAll);
	bool	LoadExcludedFileList(const QString &GUIExcludedListFile,QStringList	&ExcludedFiles);

	GUIFastComm	*CommRoot[10];
	int		CommRootNumb;

	GUIIntegrationCommPack				*IntegrationComm;

public:
	IntegrationCommPack				*GetIntegrationCommPointer(void)			{	return (IntegrationCommPack *)IntegrationComm;				}
};

//===========================================

class	GUICmdPacketBase;
class	DirectCommPacketBase;
class	IntegrationCmdPacketBase;
class	ReceiverList : public NPList<ReceiverList>
{
public:
	QString				EmitterRoot;
	QString				EmitterName;
	QString				ClassName;
	struct{
		GUICmdPacketBase	*Point;
		IntegrationCmdPacketBase				*IntegrationPoint;
	};

	ReceiverList(void)	{	Point=NULL;	IntegrationPoint=NULL;	}
	~ReceiverList(void)
	{	
		Point=NULL;
		IntegrationPoint=NULL;
	}
	ReceiverList(const QString &emitterRoot ,const QString &emitterName ,const QString &classname , GUICmdPacketBase *p)
	{	
		EmitterRoot	=emitterRoot;	
		EmitterName	=emitterName;	
		ClassName	=classname;	
		Point		=p;
		IntegrationPoint	=NULL;
	}
	ReceiverList(const QString &emitterRoot ,const QString &emitterName ,const QString &classname , IntegrationCmdPacketBase *p)
	{	
		EmitterRoot		=emitterRoot;	
		EmitterName		=emitterName;	
		ClassName		=classname;	
		Point			=NULL;
		IntegrationPoint=p;
	}
};



//===========================================
class	MainGUIFormBase;

#pragma	pack(push,1)
struct	SocketForMainGUIPacketHeader
{
	BYTE	Cmd;
	int32	DataLen;
};
#pragma	pack(pop)

#define	Cmd_SocketForMainGUIPacketHeader_AckMask		0x80		

#define	Cmd_SocketForMainGUIPacketHeader_ReqAck			1
#define	Cmd_SocketForMainGUIPacketHeader_ReqPID			2
#define	Cmd_SocketForMainGUIPacketHeader_SetGeometry	3
#define	Cmd_SocketForMainGUIPacketHeader_ReqClose		4
#define	Cmd_SocketForMainGUIPacketHeader_Maximize		5
#define	Cmd_SocketForMainGUIPacketHeader_Minimize		6


class	SocketForMainGUI : public QObject , public NPList<SocketForMainGUI>
{
    Q_OBJECT

	friend	class	MainGUIFormBase;

	QLocalSocket	*Sock;
	MainGUIFormBase	*Parent;
public:
	SocketForMainGUI(QLocalSocket *s,MainGUIFormBase *p);

private slots:
	void	SlotDisconnected();
	void	SlotReadyRead ();
};


class	MainGUIFormBase : public GUIFormBase
{
    Q_OBJECT

	friend	class	SocketForMainGUI;

	CheckSingleExecution	*Execution;
	QLocalServer			IdentificationServer;
	NPListPack<SocketForMainGUI>	IdentificationSocket;

public:
	bool	CloseCompletely;
	GUIInstancePack::_FormPosition	FormPosition;

	explicit	MainGUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent=NULL);

	virtual	void closeEvent ( QCloseEvent * event )	override;
	void	OutputPosition(void);
	virtual	void	ReflectAlignment(void)	override;

	void	SetSingleExecution(const QString &IdentifiedName);
	bool	CheckDoubleBoot(void);
	bool	RequirePrebootedSoftwareToTerminate(void);
	void	StartIdentificationServer(const QString &IdentificationName);

protected:
	virtual	void	moveEvent ( QMoveEvent * event )	override;
	virtual	void	resizeEvent ( QResizeEvent * event )override;
private:
	QString	GetPositionFileName(void);
signals:
	void	QuitFromMenu();
	void	QuitUnconditionally();
	void	SignalMoveWindow(int PosX ,int PosY);
	void	SignalCloseEvent();
private slots:
	void	SlotTerminateFromOther();
	void	SlotNewConnection ();
};

EntryPointBase	*MakeEntryPointForGlobal(void);

#endif