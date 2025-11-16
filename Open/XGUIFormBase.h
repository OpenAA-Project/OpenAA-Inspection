/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XGUIFormBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XGUIFORMBASEH)
#define	XGUIFORMBASEH

#include"XTypeDef.h"
#include<QFrame>
#include<QString>
#include<QKeySequence>
#include<QIcon>
#include<QMutex>
#include<QByteArray>
#include<QAbstractButton>
#include<QMouseEvent>
#include"NList.h"
#include"XDLLType.h"
#include"XParamBase.h"
#include"XExecuteInspectBase.h"
#include"XGUIPacketForDLL.h"

const int	GUIFormMergin=4;
class	GUIFormBase;
class	PropertyList;
class	GUIItemInstance;
class	MouseEater;
class	EditGUI;
class	GUIDirectMessage;
class	LayersBase;
class	GUIInitializer;
class	GUIInstancePack;
class	ParamGlobal;
class	ParamComm;
class	ParamGUI;
class	GuiDLLItem;
class	PasswordFilter;
class	FunctionServerClass;
class	PasswordInControl;
class	PasswordFilterPointerList;
class	KeyPressIgnorer;
class	ExportFuncForMacro;
class	LanguageStringList;
class	GUILanguageContainer;

class	QMenu;
class	QMouseEvent;
class	QAction;
class	QIODevice;
class	QSqlDatabase;

class	MenuInfoList : public QObject ,public NPList<MenuInfoList>
{
    Q_OBJECT

	QAction		*Action;
public:
	int			ID;
	QString		MenuPath;
	QString		MenuTitle;
	GUIFormBase	*Base;
	enum	__ShowingAttribute{
		_SwicthInTab
		,_Constant
	}ShowingAttribute;
	QKeySequence	ShortcutKey;
	QIcon		MenuIcon;
	int			MenuNumber;			//メニュー表示の順番の目安。（優先度）
	bool		CancelDuplication;	//同じ項目が２個になるとき２個目以下を破棄する
									//デフォルトではtrue

	MenuInfoList(void);
	~MenuInfoList(void);
	MenuInfoList(int id ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base);
	void	Set(int id ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base);
	MenuInfoList(int id ,const QIcon &icon ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base);
	void	Set(int id ,const QIcon &icon ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base);
	
	const	QIcon	&GetMenuIcon(void)			{	return MenuIcon;	}
	GUIFormBase	*GetBaseForm(void)				{	return Base;		}
	const QKeySequence	&GetShortcutKey(void)	{	return ShortcutKey;	}
	void	SetMenuNumber(int n){	MenuNumber=n;	}
	int		GetMenuNumber(void){	return MenuNumber;	}

	void	SetShowingAttributeAsSwicthInTab(void){		ShowingAttribute=_SwicthInTab;	}

	void	AddMenu(QMenu *menu);
	bool	GetCancelDuplication(void)		{	return CancelDuplication;	}
	void	SetCancelDuplication(bool b)	{	CancelDuplication=b;		}

signals:
	void	SignalTriggeredFromMenu(int id);
private slots:
	void	SlotTrigger();
};
class	MenuInfoContainer : public NPListPack<MenuInfoList> , public NPList<MenuInfoContainer>
{
public:
	MenuInfoContainer(void){}
};


class	TextMessageList : public NPList<TextMessageList>
{
public:
	QString	PathAndName;
	QString	Message;

	TextMessageList(void){}

	TextMessageList	&operator=(const TextMessageList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TextMessageContainer: public NPListPack<TextMessageList>
{
public:
	TextMessageContainer(void){}

	TextMessageContainer	&operator=(const TextMessageContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	SelectedWindow : public QWidget
{
	friend	class	GUIFormBase;

	GUIFormBase		*Partner;
public:
	explicit    SelectedWindow(GUIFormBase *partner);
	~SelectedWindow(void);

private:
	virtual	void paintEvent(QPaintEvent *e)			override;
};

class	InitializedSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	InitializedSpecifiedBroadcaster(void){}
};

class	LoadMasterBeforeFinilizeSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	LoadMasterBeforeFinilizeSpecifiedBroadcaster(void){}
};

class	LoadMasterSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	LoadMasterSpecifiedBroadcaster(void){}
};

class	CreateNewMasterPreSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	CreateNewMasterPreSpecifiedBroadcaster(void){}
};

class	CreateNewMasterSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	CreateNewMasterSpecifiedBroadcaster(void){}
};

class	CreateUpdateMasterPreSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	CreateUpdateMasterPreSpecifiedBroadcaster(void){}
};

class	CreateUpdateMasterSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	CreateUpdateMasterSpecifiedBroadcaster(void){}
};

class	WorkedSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	GUIFormBase	*WorkedComponent;
	explicit    WorkedSpecifiedBroadcaster(GUIFormBase *Own)	{	WorkedComponent=Own;	}
};

class	OpenTabPageSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	QString	TabPageName;
	OpenTabPageSpecifiedBroadcaster(void){}
};

class	CloseApplicationSpecifiedBroadcaster : public SpecifiedBroadcaster
{
public:
	CloseApplicationSpecifiedBroadcaster(void){}
};

class	CmdCancelSelection : public SpecifiedBroadcaster
{
public:
	CmdCancelSelection(void){}
};

class	KeyPressIgnorerPointer : public NPList<KeyPressIgnorerPointer>
{
public:
	KeyPressIgnorer	*Pointer;
	QString			ObjName;

	KeyPressIgnorerPointer(KeyPressIgnorer *p ,const QString &Objname):Pointer(p),ObjName(Objname){}
};

class	GUIFormPointer : public NPList<GUIFormPointer>
{
	GUIFormBase	*Base;
public:
	explicit    GUIFormPointer(GUIFormBase *base):Base(base){}

	void		SetGUIFormBase(GUIFormBase	*f)	{	Base=f;	}
	GUIFormBase	*GetGUIFormBase(void)	{	return Base;	}
};

class	GUIFormPointerContainer : public NPListPack<GUIFormPointer>
{
public:
	GUIFormPointerContainer(void){}
};

class	SyncCommandList : public NPList<SyncCommandList>
{
public:
	QByteArray	Array;

	SyncCommandList(void){}
};

class	ImageBuffer;
class	ListFuncAbstruct : public NPList<ListFuncAbstruct>
{
public:
	virtual	void	Execute(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)=0;
};

template <typename t_ListFunc>
class ListFuncElement : public ListFuncAbstruct
{
private:
    typedef void (t_ListFunc::*FPFUNC)(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse);  // 処理関数の型

private:
    t_ListFunc* m_pHandleParent;         // 操作対象
	FPFUNC	m_func;

public:
    ListFuncElement(t_ListFunc* rHandleParent ,FPFUNC fpFunc)
        : m_pHandleParent(rHandleParent),m_func(fpFunc){}

	virtual	void	Execute(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse)	override
	{
		if(m_pHandleParent!=NULL){
			(m_pHandleParent->*m_func)(Buffer ,BufferDimCounts,XReverse ,YReverse);
		}
	}
};

class ButtonRightClickEnabler : public QObject
{
    Q_OBJECT
public:
    explicit    ButtonRightClickEnabler(QAbstractButton * button): QObject(button), _button(button) {
		if(button!=NULL){
			button->installEventFilter(this);
		}
    };

protected:
    inline bool eventFilter(QObject *watched, QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress)
        {
            auto mouseEvent = (QMouseEvent*)event;
            if (mouseEvent->button() == Qt::RightButton){
                //_button->click();
				emit	RightClicked(_button);
			}
        }
		else
		if (event->type() == QEvent::MouseButtonDblClick)
        {
            auto mouseEvent = (QMouseEvent*)event;
            if (mouseEvent->button() == Qt::LeftButton){
                //_button->click();
				emit	DoubleClicked(_button);
			}
        }
       return false;
    }

private:
    QAbstractButton* _button;
signals:
	void	RightClicked(QAbstractButton *obj);
	void	DoubleClicked(QAbstractButton *obj);
};

/*
	EditGUIでくっつけるベースになる部分にはGUIFormBaseから導出したクラスを使用しなければならない
*/

class	GUIFormBase : public QFrame,public IdentifiedClass
{
    Q_OBJECT
friend class	GUIItemInstance;
friend	class	MouseEater;
friend	class	EditGUI;
friend	class	SelectedWindow;

	enum	CurrentActionMode{
		_CA_Nothing
		,_CA_ChangingSizeBottomRight
		,_CA_ChangingSizeTopLeft
		,_CA_ChangingSizeTopRight
		,_CA_ChangingSizeBottomLeft
		,_CA_ExtendingLeft
		,_CA_ExtendingTop
		,_CA_ExtendingRight
		,_CA_ExtendingBottom
		,_CA_Moving
	};
	LayersBase	*LayersBasePoint;
	int32		TargetPage;

	CurrentActionMode	Mode;
	QPoint	StartPos;
	struct{
		bool	EntereedKeyEvent	:1;
		bool	KeyGrabMode			:1;
		bool	RootForm			:1;
		bool	ModeStartPage		:1;
		bool	ForceWindowMode		:1;


		bool	PassedEvent			:1;
		bool	CreatedInGUIDLL		:1;
		bool	IgnoreKeyEvent		:1;
		bool	EnabledBroadcast	:1;
		bool	Viewing				:1;		//Tabなどに隠されていなければtrue

		bool	ReEntryStackedViewPlayer			:1;
		bool	ReEntryStackedOnTheWayPlayer		:1;
		bool	ReEntryStackedRunByEveryInspection	:1;
		bool	ReEntryStackedViewScanning			:1;
	};
	int32	FormBaseID;
	QString	Name;
	QString	Comment;
	QString	Alignment;

	NPListPack<KeyPressIgnorerPointer>	KeyPressIgnorerContainer;
	QMutex	SyncCommandMutex;
	NPListPack<SyncCommandList>			SyncCommandListContainer;
protected:
	GUIInitializer	*GUIInitializerPoint;
	GUIInstancePack	*GUIInstancePackPoint;
	GUIFormPointerContainer				ShouldCloseWindow;
private:
	TextMessageContainer	TextMessageContainerData;
	MenuInfoContainer		MenuInfo;
	DWORD	LastShowingMilisec;
	DWORD	LastRunningMilisec;
	DWORD	LastEdittingMilisec;
	DWORD	LastScanningMilisec;
	int32	ClientX1,ClientY1;	//相対座標
	int32	ClientX2,ClientY2;
	int32	ReEntrantCount;
	int32	StackedViewPlayerCount;
	int32	StackedRunByEveryInspectionCount;
	int32	StackedViewScanningCount;
	int32	ShowingOrder;
public:
	enum	_BroadcastCommand{
		 _BC_BuildForShow	=1
		,_BC_ShowInPlayer	=2
		,_BC_OnTheWayInPlayer		=20
		,_BC_RunByEveryInspection	=19
		,_BC_ShowInEdit		=3
		,_BC_ShowInScanning	=18
		,_BC_DoneCalc		=4
		,_BC_StartPage		=5	//表示されるTAB内のGUIに対してのみ送出される
		,_BC_LeavePage		=6	//表示されるTAB内のGUIに対してのみ送出される
		,_BC_WroteResult	=7
		,_BC_SetViewing		=8
		,_BC_TabChanged		=9	//すべてのGUIに送出される
		,_BC_ShowInDelayed	=10
		,_BC_Terminated		=11
		,_BC_ReadyParam		=12
		,_BC_StartLot		=13
		,_BC_SetupLibFolder	=14
		,_BC_ResizeAction	=15
		,_BC_RepaintAll		=16
		,_BC_SetTargetPage	=17
		,_BC_RefreshCache	=21
		,_BC_StartInitial	=22
		,_BC_ReadyTerminate	=23
	};
protected:
	GUIFormBase	*ChainedParent;		//多重に起動したときの親
	QByteArray	ChainedContent;		//多重に起動したときのデータ
	GuiDLLItem	*GuiDLLPoint;
	bool		TopForm;
	int			OnIdleCounter;
	GUIFormBase	*DeridedParent;
	QPoint		LeftClickGlobalPoint;
	QPoint		RightClickGlobalPoint;
public:

	explicit    GUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent=NULL);
	virtual	~GUIFormBase();

	bool	IsPassedEvent(void)			const	{	return PassedEvent;			}
	void	SetPassedEvent(bool	b)				{	PassedEvent=b;				}
	bool	IsIgnoreKeyEvent(void)		const	{	return IgnoreKeyEvent;		}
	void	SetIgnoreKeyEvent(bool b)			{	IgnoreKeyEvent=b;			}
	bool	IsEnabledBroadcast(void)	const	{	return EnabledBroadcast;	}
	void	SetEnabledBroadcast(bool b)			{	EnabledBroadcast=b;			}
	bool	IsCreatedInGUIDLL(void)		const	{	return CreatedInGUIDLL;		}
	void	SetCreatedInGUIDLL(bool b)			{	CreatedInGUIDLL=b;			}
	QString	GetName(void)				const	{	return Name;				}
	void	SetName(const QString &s)			{	Name=s;						}
	QString	GetComment(void)			const	{	return Comment;				}
	void	SetComment(const QString &s)		{	Comment=s;					}
	QString	GetAlignment(void)			const	{	return Alignment;			}
	void	SetAlignment(const QString &s)		{	Alignment=s;				}
	GuiDLLItem	*GetGuiDLLPoint(void)	const	{	return GuiDLLPoint;			}
	void	SetGuiDLLPoint(GuiDLLItem *s)		{	GuiDLLPoint=s;				}

	int32	GetFormBaseID(void)			const	{	return FormBaseID;			}
	void	_SetFormBaseID(int32 id)			{	FormBaseID=id;				}
	GUIFormBase	*GetChainedParent(void)	const	{	return ChainedParent;		}
	void	SetChainedParent(GUIFormBase *b)	{	ChainedParent=b;			}
	void	SetModeStartPage(bool b)			{	ModeStartPage=b;			}
	bool	GetModeStartPage(void)		const	{	return ModeStartPage;		}

	virtual	QString	GetDLLRoot(void)	const;
	virtual	QString	GetDLLName(void)	const;
	bool	CheckDLL(const QString &FDLLRoot,const QString &FDLLName);
	virtual void	AssociateComponent	(ComponentListContainer &List);

	bool	HasParent(QWidget *p);
	GUIFormBase	*GetTopClass(void);
	virtual void	InitialPrepare(void){}
	virtual void	Prepare(void);
	virtual void	AfterPrepare(void){}
	virtual void	ReadyParam(void){}
	virtual void	AfterStartSequence(void){}
	void	ChangedValue(void);

	void	SetEditMode(void);
	bool	GetEditMode(void)	const;
	void	SetGridUnitForEditMode(int n);
	int		GetGridUnitForEditMode(void)	const;
	void	SetSelectedInEditMode(bool b);
	bool	GetSelectedInEditMode(void)		const;
	virtual	void	CreatedInEditMode(GUIFormBase *PutTop){}
	void	EnumChildren(GUIFormPointerContainer &Children);
	virtual	void	SetSignal(QObject *target,const char *signal,const char *slotfunc);

	void	SetKeyGrab(bool t)			{	KeyGrabMode=t;	}
	bool	GetKeyGrab(void)	const	{	return KeyGrabMode;	}
	virtual	void	ReflectAlignment(void);
	void	ReflectResize(void);
	void	ReflectSize(void);
	void	GiveName(QObject *parent);
	void	SetViewing(bool v)				{	Viewing=v;		}
	bool	GetViewing(void)	const		{	return Viewing;	}
	bool	IsForceWindowMode(void)	const	{	return ForceWindowMode;	}

	int32	GetClientX1(void)	const	{	return ClientX1;	}
	int32	GetClientY1(void)	const	{	return ClientY1;	}
	int32	GetClientX2(void)	const	{	return ClientX2;	}
	int32	GetClientY2(void)	const	{	return ClientY2;	}
	void	SetClientX1(int n)			{	ClientX1=n;			}
	void	SetClientY1(int n)			{	ClientY1=n;			}
	void	SetClientX2(int n)			{	ClientX2=n;			}
	void	SetClientY2(int n)			{	ClientY2=n;			}

	int32	GetStackedViewPlayerCount(void)		const	{	return StackedViewPlayerCount;		}
	int32	GetStackedViewScanningCount(void)	const	{	return StackedViewScanningCount;	}

	GUIFormBase	*GetTopParent()			const;
	GUIFormBase	*GetParentFormBase()	const;
	GUIFormBase	*GetFormByName(QString name)	const;
	GUIFormBase	*GetFormByNumber(int index)		const;

	int		DeliverGetMaxIDForChildren(int NowID);
	GUIFormBase	*DeliverFindForChildren(int ID);
	virtual	GUIFormBase	*GetTopSurfaceWidget(int x ,int y);
	void	SetFormBaseID(int ID);
	virtual	void	SwapTab(QWidget *TabStack ,int index1 ,int index2);
	void	OpenTabToShow(QWidget *target);
	void	ExecAsDialog(QWidget * parent);
	void	ExecAsWindow(QWidget * parent ,bool StayOnTop=true);

	void	ViewRefreshInPlayer		(int64 shownInspectionID);
				//emit SignalRefreshInPlayer
	void	ViewOnTheWayInPlayer	(int64 shownInspectionID);
				//emit SignalOnTheWayInPlayer
	void	RefreshByEveryInspection(int64 shownInspectionID);
				//emit SignalRefreshInPlayer
	void	ViewRefreshInEdit	(void);							//emit SignalRefreshInEdit
	void	ViewRefreshInScanning(int64 shownInspectionID);		//emit SignalRefreshInPlayer

	void	DoneExecuteFromGUI(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode);
	virtual	int	GetChildCount();
	void	Set		(GUIInitializer	*_GUIInitializerPoint ,GUIInstancePack	*_GUIInstancePackPoint);
	void	SetParent(GUIInitializer	*_GUIInitializerPoint ,GUIInstancePack	*_GUIInstancePackPoint);
	virtual	GUIFormBase	*GetChild(int index)	const;					//常に同じGUIFormBaseを取り出さなければならない

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	bool				SaveInPacket(QIODevice *f ,GUIDirectMessage *packet);
			QString				LoadInPacket(QIODevice *f);
	virtual	GUIDirectMessage	*LoadInPacket(QIODevice *f ,const QString &ClassName)	{	return NULL;	}

	virtual	void	Repaint(void)		{}
	void	EmitRepaint(void);
	virtual	void	SetAreaSize(void)	{}
	void	ActivePhaseList(IntList &PhaseList);
	
	void SetTextMessage(void);
	bool	SaveTextMessageContainerData(QIODevice *f);
	bool	LoadTextMessageContainerData(QIODevice *f);
	bool	SetDeridedParent(GUIFormBase *p);
	virtual	void	CalledFromDeridedParent(GUIFormBase *Parent, QEvent * event){}

	void	SetEnableBroadcastForAll(bool flag);
	void	SetEnabledForChildren(bool flag);
	void	BroadcastDirectly(_BroadcastCommand cmd ,int64 shownInspectionID ,int64 cmd2=0);
	virtual void	BuildForShow(void);
	virtual void	ShowInPlayer		(int64 shownInspectionID=-1);
	virtual void	OnTheWayInPlayer	(int64 shownInspectionID=-1);
	virtual void	RunByEveryInspection(int64 shownInspectionID=-1);
	virtual void	ShowInEdit	(void);
	virtual void	ShowInScanning(int64 shownInspectionID=-1);
	virtual void	SetupLibFolder(int LibFolderID,int originalLibFolder){}
	virtual void	StartLot	(void);
	virtual void	ShowInDelayed(void);
	virtual void	StartPage	(void);
	virtual void	LeavePage	(void);
	virtual void	DoneCalc(int64 shownInspectionID=-1);
	virtual void	DoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode){}
	virtual void	WroteResult(int64 shownInspectionID=-1){}
	virtual void	TabChanged(void){}
	virtual void	ReadyTerminate(void){}
	virtual void	Terminated(void){}
	virtual	void	RefreshCache(void){}
	virtual void	RepaintAll(void);
	virtual	void	StartInitial(void)	{}
	virtual	bool	IsShown(void);

	bool	SetLanguage(const QString &MemberName,LanguageStringList *s);
	void	PickupGUILanguage(GUILanguageContainer &GUILanguageContainerInst);
	void	ReflectGUILanguage(void);

	virtual	void	SetTargetPage(int page);
	int				GetTargetPage(void)	const;

	virtual	void	SetShowingOrder(int32 d)	{	ShowingOrder=d;			}
	int32			GetShowingOrder(void)		{	return ShowingOrder;	}

	DWORD	GetShowingMilisec(void)		const	{	return LastShowingMilisec;	}
	DWORD	GetRunningMilisec(void)		const	{	return LastRunningMilisec;	}
	DWORD	GetEdittingMilisec(void)	const	{	return LastEdittingMilisec;	}
	DWORD	GetScanningMilisec(void)	const	{	return LastScanningMilisec;	}

	virtual void	BroadcastBuildForShow(void);
	virtual void	BroadcastShowInPlayer		 (int64 shownInspectionID=-1);
	virtual void	BroadcastOnTheWayInPlayer	 (int64 shownInspectionID=-1);
	virtual void	BroadcastRunByEveryInspection(int64 shownInspectionID=-1);
	virtual void	BroadcastShowInEdit(void);
	virtual void	BroadcastShowInScanning(int64 shownInspectionID=-1);
	virtual void	BroadcastSetupLibFolder(int LibFolderID ,int originalLibFolder);
	virtual void	BroadcastStartLot(void);
	virtual void	BroadcastShowInDelayed(void);
	virtual void	BroadcastStartPage(void);
	virtual void	BroadcastLeavePage(void);
	virtual void	BroadcastWroteResult(int64 shownInspectionID=-1);
	virtual void	BroadcastSetViewingOnChildrenWithMe(bool viewing);
	virtual void	BroadcastTabChanged(void);
	virtual void	BroadcastReadyTerminate(void);
	virtual void	BroadcastTerminated(void);
	virtual void	BroadcastReadyParam(void);
	virtual void	BroadcastResizeAction(void);
	virtual void	BroadcastRefreshCache(void);
	virtual void	BroadcastRepaintAll(void);
	virtual	void	BroadcastSetTargetPage(int Page);
	virtual void	BroadcastStartInitial(void);


	void	RegisterExecuteStartByInspection(void);
	void	RegisterExecutePreAlignment		(void);
	void	RegisterExecuteAlignment		(void);
	void	RegisterExecutePreProcessing	(void);
	void	RegisterExecuteProcessing		(void);
	void	RegisterExecuteProcessingRevived(void);
	void	RegisterExecutePostProcessing	(void);

	//これらはインスタンスの登録が必要
	virtual ExeResult	ExecuteStartByInspection(void)	{	return _ER_true;	}
	virtual ExeResult	ExecutePreAlignment		(void)	{	return _ER_true;	}
	virtual ExeResult	ExecuteAlignment		(void)	{	return _ER_true;	}
	virtual ExeResult	ExecutePreProcessing	(void)	{	return _ER_true;	}
	virtual ExeResult	ExecuteProcessing		(void)	{	return _ER_true;	}
	virtual ExeResult	ExecuteProcessingRevived(void)	{	return _ER_true;	}
	virtual ExeResult	ExecutePostProcessing	(void)	{	return _ER_true;	}
	virtual ExeResult	ExecuteFinished			(void)	{	return _ER_true;	}

	virtual void	PushButton(void);

	void	BroadcastChildrenAndOwnDirectly(_BroadcastCommand cmd ,int64 shownInspectionID ,int64 cmd2=0);

	void	BroadcastSpecifiedDirectly(SpecifiedBroadcaster *v);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v){}

	void BroadcastEvent( QEvent * event );
	void ResetPassedEventFlag(void);
	void ClearIgnoreEventFlag(void);

	virtual	void	RequireHooks(GUIFormBase *mother){}
	virtual	void	ReleaseHook(FunctionServerClass *f){}

	LayersBase	*GetLayersBase(void)	const;
	int		GetCurrentShadowLevel(void)	const;	//Top:0
	int		GetPageNumb(void)		const;
	int		GetPhaseNumb(void)		const;
	int		GetLayerNumb(int page)		const;
	bool	IsValid(int page ,int layer)const;

	int		GetCountAllMasterBuff(void)			const;
	int		GetCountOnlyMasterBuff(void)		const;
	int		GetCountDispatchMasterBuff(void)	const;

	int			GetDotPerLine(int page)		const;
	int			GetMaxLines(int page)		const;
	ParamGlobal	*GetParamGlobal(void)		const;
	ParamComm	*GetParamComm(void)			const;
	ParamGUI	*GetParamGUI(void)			const;
	void		SetChildNumber(void);
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	Reallocate(int newPhaseNumb);
	virtual	bool	ReallocateMasterCount(int CountMaster);
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

	virtual	QStringList	GetRelatedForm(void){	return QStringList();	}
			QStringList	GetAllRelatedForm(void);

	bool	ExecuteMacro(const QString &FuncName, QStringList &Args, bool &ExeReturn);
	void	InstallEventHandler(PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData);
	void	InstallEventHandlerOnlyPassword(PasswordFilter *f,PasswordInControl *c);

	virtual	bool	SaveContent(QIODevice *f){		return true;	}
	virtual	bool	LoadContent(QIODevice *f){		return true;	}

	QIODevice	*GetChainedDevice(void);
	bool	SaveAll(QIODevice *f);
	bool	LoadAll(QIODevice *f);

	void	SetError(int errorCode , const QString &errorMessage ,ErrorCodeList::CautionLevel level);

	bool			TxSync(QByteArray &f,int MilisecToWaitForAck=30000);
	void			TxSyncNoBlock(QByteArray &f);
	virtual	void	RxSync(QByteArray &f){}
	virtual	void	RxIntegration(QByteArray &f){}

	virtual	void	GetMenuInfo(MenuInfoContainer &Info){}
	virtual	void	ExecuteMenu(int ID){}

	void	_ShowInPlayer			(int64 shownInspectionID=-1);
	void	_OnTheWayInPlayer		(int64 shownInspectionID=-1);
	void	_RunByEveryInspection	(int64 shownInspectionID=-1);
	void	_ShowInEdit		(void);
	void	_ShowInScanning	(int64 shownInspectionID=-1);
	void	_ShowInDelayed	(void);
	void	_ResizeAction	(void);
	void	_SetupLibFolder(int LibFolderID,int originalLibFolder);

	void	SetAcceptDropsForAll(void);
	void	InstallIgnoreKeyForChild( int *_EffectiveKey=NULL ,int _EffectiveKeyCount=0);

	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);
	void	GetMacroNames(QStringList &Str);
	void	ExecuteMacro(const QString &FunctionName ,const QString &Arg1=/**/""
													 ,const QString &Arg2=/**/""
													 ,const QString &Arg3=/**/""
													 ,const QString &Arg4=/**/""
													 ,const QString &Arg5=/**/""
													 ,const QString &Arg6=/**/""
													 ,const QString &Arg7=/**/""
													 ,const QString &Arg8=/**/""
													 ,const QString &Arg9=/**/""
													 ,const QString &Arg10=/**/"");
	//----------- Unit-------------
	bool	IsUnitMode(void);
	double	TransformPixelToUnit	(int Page,double pixel);
	double	TransformUnitToPixel	(int Page,double unit);
	QString	TransformPixelToUnitStr	(int Page,double pixel);
	QString	GetUnitStr(double unit);
	double	TransformPixelToUnitSquare(int Page,double pixel);
	double	TransformUnitToPixelSquare(int Page,double unit);
	QString	TransformPixelToUnitSquareStr(int Page,double pixel);
	QString	GetUnitSquareStr(double unit);

	//---------- Select in EditMode -------
	void	CreateSelectedWindow(void);

	//---------- Property QByteArray -------
	virtual	bool	ShowQByteArrayDialog(const QString &VariableName)	{	return true;	}

private:
	bool	EditMode;
	bool	Selected;
	SelectedWindow	*SelectedWindowPointer;
	int		GridUnitForEditMode;
	GUIFormBase	*CurrentActiveItem;
	GUIItemInstance	*InstPoint;
	KeyPressIgnorer	*FindKeyPressIgnorer(const QString &objname);
	bool	SelectedItemExists(void);
protected:
	virtual	void keyPressEvent ( QKeyEvent * event )			override;
	virtual	void keyReleaseEvent ( QKeyEvent * event )			override;

	virtual	void mouseMoveEvent ( QMouseEvent * event )			override;
	virtual	void mousePressEvent ( QMouseEvent * event )		override; 
	virtual	void mouseReleaseEvent ( QMouseEvent * event )		override; 
	virtual	void enterEvent ( QEnterEvent * event )				override;
	virtual	void leaveEvent ( QEvent * event )					override;
	virtual	void mouseDoubleClickEvent ( QMouseEvent * Event )	override;
	virtual	void resizeEvent ( QResizeEvent * event )			override;
	virtual	void changeEvent ( QEvent * event )					override;
	virtual	void closeEvent ( QCloseEvent * event )				override;
	virtual	void moveEvent ( QMoveEvent * event )				override;

	virtual	void	RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage);
	void	SendSyncCommand(void);
	virtual	bool eventFilter ( QObject * watched, QEvent * event )	override;

	virtual	QWidgetList	GetTabChildren(void);

public:
	virtual	void OnIdleCountUp(void);		//Don't call

	virtual	bool LoopOnIdle(void);	//Don't call
	virtual	bool OnIdle(void){	return true;	}	//if it wants to be called again ,return false.

private:
	GUIFormBase	*SearchFormInChild(const QString &SRoot,const QString &SName,const QString &InstName);
signals:
	void	SignalRefreshInPlayer(int64 shownInspectionID);
	void	SignalOnTheWayInPlayer(int64 shownInspectionID);
	void	SignalRefreshByEveryInspection(int64 shownInspectionID);
	void	SignalRefreshInEdit();							//Display again
	void	SignalRefreshInScanning(int64 shownInspectionID);	//Display again

	void	SignalDoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode);
	void	SignalResize();
	void	SignalMove();
	void	SignalRelease();
	void	SignalClose(GUIFormBase *form);
	void	SignalPushButton();
	void	SignalRaiseUp();
	void	SignalRepaint();
public slots:
	void	SlotRefreshInPlayer(int64 shownInspectionID);	//Display again
	void	SlotOnTheWayInPlayer(int64 shownInspectionID);	//Display again
	void	SlotRefreshByEveryInspection(int64 shownInspectionID);
	void	SlotRefreshInEdit();							//Display again
	void	SlotRefreshInScanning(int64 shownInspectionID);	//Display again
	void	SlotDoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode);
	void	SlotCommand(int cmd);
	void	SlotWroteSlave(XDateTime tm);
	void	SlotChangeLotInfo(int DeliveryNo);
	void	SlotZOrderUp();

	virtual	void RemoveAction();
	virtual	void ForcusProperty();
	virtual	void ReleaseAllSelectedInEditMode();
	virtual	void ChangeTabTop();
	virtual	void TurnUpDown();
	virtual	void DeleteTabPage();
	virtual	void ChangeTextAction();
	virtual	void SlotPushButton(){}
	void	SlotRepaint();
private slots:
	void MessageOutFunc(int N);
	void	SlotTriggerMenu(int id);
};
inline	bool	GUIFormBase::GetEditMode(void)	const
{
	return EditMode;
}
	
inline	void	GUIFormBase::SetGridUnitForEditMode(int n)
{
	GridUnitForEditMode=n;
}
	
inline	int		GUIFormBase::GetGridUnitForEditMode(void)	const
{
	return GridUnitForEditMode;
}
inline	void	GUIFormBase::SetSelectedInEditMode(bool b)
{
	if(SelectedWindowPointer!=NULL){
		if(Selected!=b){
			Selected=b;
			SelectedWindowPointer->update();
		}
	}
	Selected=b;
}

inline	bool	GUIFormBase::GetSelectedInEditMode(void)	const
{
	return Selected;
}

class	ParamGUI : public QObject ,public ParamBase
{
	Q_OBJECT
public:
	ParamGUI(void){}
	~ParamGUI(void){}

	virtual	QString	GetDataText(void)		override	{	return("GUI Data");	};
	virtual	QString	GetDefaultFileName(void)override	{	return("GUI.dat");	}

	virtual	void	ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)	override;

signals:
	void	SignalExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
};

class	LQWidget : public QWidget
{
public:
	void KeyPressEvent ( QKeyEvent * event )	{	keyPressEvent(event);	}
	void KeyReleaseEvent ( QKeyEvent * event )	{	keyReleaseEvent(event);	}
};

class	GuiAdditionalDatabase : public NPList<GuiAdditionalDatabase>
{
public:
	QString		TableName;
	QString		FieldName;
	QVariant	DefaultData;

	GuiAdditionalDatabase(void){}
	GuiAdditionalDatabase(const QString &_TableName
						 ,const QString &_FieldName
						 ,const QVariant &_DefaultData)
		:TableName(_TableName),FieldName(_FieldName),DefaultData(_DefaultData){}
	bool	InitialAdditionalFieldFromGUI(const QSqlDatabase &DB);
};

class KeyPressIgnorer : public QObject
{
     Q_OBJECT

	int *EffectiveKey;
	int EffectiveKeyCount;
public:
	KeyPressIgnorer ( int *_EffectiveKey ,int _EffectiveKeyCount ,QObject * parent = 0 );
	~KeyPressIgnorer(void);

protected:
     bool eventFilter(QObject *obj, QEvent *event);
 };

class	ZoneWindowForEdit : public QFrame
{
public:
	ZoneWindowForEdit(QWidget * parent = 0);

protected:
	virtual	void 	paintEvent ( QPaintEvent * event )		override;
};

//============================================================================================

class	GUIFormBasePointer : public NPList<GUIFormBasePointer>
{
	GUIFormBase	*Form;
public:
	explicit    GUIFormBasePointer(GUIFormBase *s):Form(s){}

	GUIFormBase	*GetForm(void)	const	{	return Form;	}
};

class	GUIFormBasePointerContainer : public NPListPack<GUIFormBasePointer>
{
public:
	GUIFormBasePointerContainer(void){}

	void	Add(GUIFormBase *s)	{	AppendList(new GUIFormBasePointer(s));	}
	void	Repaint(void);
};


//============================================================================================
#endif
