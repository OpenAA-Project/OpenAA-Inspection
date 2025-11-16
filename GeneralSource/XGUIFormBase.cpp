/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUIFormBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XGUIInterfaceDLL.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XGUIFormBase.h"
#include <QMouseEvent>
#include <QMenu>
#include <QDrag>
#include <QMimeData>
#include <QToolBox>
#include <QStackedWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QApplication>
#include <QAbstractSpinBox>
#include <QTabWidget>
#include <QTabBar>
#include <QGuiApplication>
#include "itemlistwindow.h"
#include "SelectTabTop.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "GUITurnUpDownForm.h"
#include "XGUI.h"
#include "XPassword.h"
#include "XGeneralFunc.h"
#include "XAnyData.h"
#include "EditTextMessages.h"
#include "XSyncGUI.h"
#include "XLotInformation.h"
#include "XIntegrationComm.h"
#include "EditStatusDialog.h"
#include "XStatusController.h"
#include "XGeneralDialog.h"
#include "ThreadSequence.h"
#include "XShadowTree.h"
#include "XGUILanguage.h"
#include "XGeneralStocker.h"
#include <omp.h>

extern	ItemListWindow	*MainItem;

MenuInfoList::MenuInfoList(void)
{
	ID					=0;
	Action				=NULL;
	Base				=NULL;
	ShowingAttribute	=_Constant;
	MenuNumber			=1000;
	CancelDuplication	=true;
}
MenuInfoList::~MenuInfoList(void)
{
	if(Base!=NULL && Action!=NULL){
		Base->disconnect(Action,SIGNAL(triggered()),this,SLOT(SlotTrigger()));
	}
	Base=NULL;
	if(Action!=NULL){
		delete	Action;
		Action=NULL;
	}

}

MenuInfoList::MenuInfoList(int id ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base)
{
	Action	=NULL;
	ShowingAttribute	=_Constant;
	MenuNumber			=1000;
	Set(id,menupath ,menutitle ,base);
	CancelDuplication	=true;
}
MenuInfoList::MenuInfoList(int id ,const QIcon &icon ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base)
{
	Action	=NULL;
	ShowingAttribute	=_Constant;
	MenuNumber			=1000;
	Set(id,icon,menupath ,menutitle ,base);
	CancelDuplication	=true;
}

void	MenuInfoList::Set(int id ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base)
{
	ID			=id;
	Base		=base;
	MenuPath	=menupath;
	MenuTitle	=menutitle;
}

void	MenuInfoList::Set(int id ,const QIcon &icon ,const QString &menupath ,const QString &menutitle ,GUIFormBase *base)
{
	ID			=id;
	Base		=base;
	MenuIcon	=icon;
	MenuPath	=menupath;
	MenuTitle	=menutitle;
}

void	MenuInfoList::AddMenu(QMenu *menu)
{
	if(Action!=NULL){
		delete	Action;
		Action=NULL;
	}
	if(MenuTitle=="Separator"){
		menu->addSeparator();
	}
	else{
		Action=menu->addAction(MenuTitle);
		if(GetShortcutKey().isEmpty()==false){
			Action->setShortcut(GetShortcutKey());
		}
		Base->connect(Action,SIGNAL(triggered()),this,SLOT(SlotTrigger()));
		Base->connect(this  ,SIGNAL(SignalTriggeredFromMenu(int)),Base ,SLOT(SlotTriggerMenu(int)),Qt::QueuedConnection);
		Action->setData(ID);
	}
}
void	MenuInfoList::SlotTrigger()
{
	emit	SignalTriggeredFromMenu(ID);
}


//===========================================================================

bool MouseEater::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress){
		QMouseEvent	*ev=dynamic_cast<QMouseEvent *>(event);
		QWidget	*w=dynamic_cast<QWidget *>(obj);
		
		if(Parent->GetEditMode()==true && ev->modifiers()==Qt::ShiftModifier){
			QStringList	List;
			for(QWidget *m=w;m!=NULL;m=m->parentWidget()){
				QString	ObjName=m->objectName();
				List.append(ObjName);
			}
			EditStatusDialog	D(Parent->GetLayersBase(),w);
			D.GUIRoot=Parent->GetDLLRoot();
			D.GUIName=Parent->GetDLLName();
			D.GUIInst=Parent->GetName();
			D.ObjectPath=List;
			if(D.exec()==true){
			}
		}

		QPoint	p=w->mapToGlobal (ev->pos());
		QMouseEvent	Ev( ev->type()
						, Parent->mapFromGlobal(p)
						, ev->button(), ev->buttons(), ev->modifiers() );
		Parent->mousePressEvent(&Ev);
		return true;
	}
	else if(event->type() == QEvent::MouseMove){
		QMouseEvent	*ev=(QMouseEvent *)event;
		QMouseEvent	Ev( ev->type()
						, Parent->mapFromGlobal(((QWidget *)obj)->mapToGlobal (ev->pos()))
						, ev->button(), ev->buttons(), ev->modifiers() );
		Parent->mouseMoveEvent(&Ev);
		return true;
	}
	else if(event->type() == QEvent::MouseButtonRelease){
		QMouseEvent	*ev=(QMouseEvent *)event;
		QMouseEvent	Ev( ev->type()
						, Parent->mapFromGlobal(((QWidget *)obj)->mapToGlobal (ev->pos()))
						, ev->button(), ev->buttons(), ev->modifiers() );
		Parent->mouseReleaseEvent(&Ev);
		return true;
	}
	else if(event->type() == QEvent::MouseButtonDblClick){
		QMouseEvent	*ev=(QMouseEvent *)event;
		QMouseEvent	Ev( ev->type()
						, Parent->mapFromGlobal(((QWidget *)obj)->mapToGlobal (ev->pos()))
						, ev->button(), ev->buttons(), ev->modifiers() );
		Parent->mouseDoubleClickEvent(&Ev);
		return true;
	}
	else{
		return QObject::eventFilter(obj, event);
	}
}

TextMessageList	&TextMessageList::operator=(const TextMessageList &src)
{
	PathAndName	=src.PathAndName;
	Message		=src.Message;
	return *this;
}

bool	TextMessageList::Save(QIODevice *f)
{
	if(::Save(f,PathAndName)==false){
		return false;
	}
	if(::Save(f,Message)==false){
		return false;
	}
	return true;
}
bool	TextMessageList::Load(QIODevice *f)
{
	if(::Load(f,PathAndName)==false){
		return false;
	}
	if(::Load(f,Message)==false){
		return false;
	}
	return true;
}


TextMessageContainer	&TextMessageContainer::operator=(const TextMessageContainer &src)
{
	RemoveAll();
	for(TextMessageList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		TextMessageList	*b=new TextMessageList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

bool	TextMessageContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(TextMessageList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	TextMessageContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		TextMessageList *a=new TextMessageList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

//----------------------------------------------------------------------------------------------

GUIFormBase::GUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent):QFrame(parent)
{
	LayersBasePoint		=_LayersBasePoint;
	TargetPage			=-1;
	RootForm			=false;
	GUIInitializerPoint	=NULL;
	GUIInstancePackPoint=NULL;
	ChainedParent		=NULL;

	FormBaseID			=0;
	QFrame::Shape	__Shape= QFrame::NoFrame;
	if (_LayersBasePoint->GetEntryPoint() != NULL) {
		if (_LayersBasePoint->GetEntryPoint()->GUIIsEditMode() == true) {
			__Shape = QFrame::StyledPanel;
		}
	}
	setFrameShape(__Shape);
	setFrameShadow(QFrame::Raised);
	setLineWidth(2);
	setMidLineWidth(2);
    setMouseTracking(true);
	Mode				=_CA_Nothing;
	Alignment			="None";
	CreatedInGUIDLL		=false;
	GuiDLLPoint			=NULL;
	LastShowingMilisec	=0;
	LastRunningMilisec	=0;
	LastEdittingMilisec	=0;
	LastScanningMilisec	=0;
	ShowingOrder		=10000;

	CurrentActiveItem	=NULL;
	EditMode			=false;
	GridUnitForEditMode	=1;
	Selected			=false;
	SelectedWindowPointer=NULL;
	StackedViewPlayerCount			=0;
	StackedRunByEveryInspectionCount=0;
	StackedViewScanningCount		=0;

	InstPoint			=NULL;
	EntereedKeyEvent	=false;
	KeyGrabMode			=false;
	PassedEvent			=false;
	IgnoreKeyEvent		=false;
	EnabledBroadcast	=false;
	Viewing				=true;
	TopForm				=false;
	ModeStartPage		=true;
	ForceWindowMode		=false;
	ReEntryStackedViewPlayer			=false;
	ReEntryStackedOnTheWayPlayer		=false;
	ReEntryStackedRunByEveryInspection	=false;
	ReEntryStackedViewScanning			=false;
	OnIdleCounter		=0;
	ReEntrantCount		=0;
	DeridedParent		=NULL;

	EntryPointBase	*e=_LayersBasePoint->GetEntryPoint();
	if(e!=NULL)
		EditMode=e->GUIIsEditMode();
	//if(parent==NULL)	
	//	grabKeyboard ();
	connect( this,SIGNAL(SignalRefreshInPlayer(int64))
			,this,SLOT(SlotRefreshInPlayer(int64))
			,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalOnTheWayInPlayer(int64))
			,this,SLOT(SlotOnTheWayInPlayer(int64))
			,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalRefreshByEveryInspection(int64))
			,this,SLOT(SlotRefreshByEveryInspection(int64))
			,Qt::QueuedConnection);
	connect(this,SIGNAL(SignalRefreshInEdit())
			,this,SLOT(SlotRefreshInEdit())
			,Qt::QueuedConnection);
	connect(this,SIGNAL(SignalRefreshInScanning(int64))
			,this,SLOT(SlotRefreshInScanning(int64))
			,Qt::QueuedConnection);
	connect(this,SIGNAL(SignalRepaint())
			,this,SLOT(SlotRepaint())
			,Qt::QueuedConnection);

	qRegisterMetaType<GUIFormBase *>("GUIFormBase *");
	qRegisterMetaType<ExecuteInspectBase::MotionMode>("ExecuteInspectBase::MotionMode");

	connect(this,SIGNAL(SignalDoneExecute(int64,ExecuteInspectBase::MotionMode)),this,SLOT(SlotDoneExecute(int64,ExecuteInspectBase::MotionMode)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalPushButton()),this,SLOT(SlotPushButton()),Qt::QueuedConnection);
}

void	GUIFormBase::Set(GUIInitializer	*_GUIInitializerPoint ,GUIInstancePack	*_GUIInstancePackPoint)
{
	GUIInitializerPoint	=_GUIInitializerPoint;
	GUIInstancePackPoint=_GUIInstancePackPoint;
	RootForm	=true;
}
void	GUIFormBase::SetParent(GUIInitializer	*_GUIInitializerPoint ,GUIInstancePack	*_GUIInstancePackPoint)
{
	GUIInitializerPoint	=_GUIInitializerPoint;
	GUIInstancePackPoint=_GUIInstancePackPoint;
}
LayersBase	*GUIFormBase::GetLayersBase(void)	const
{
	LayersBase	*L;

	L=LayersBasePoint;
	while(L!=NULL){
		if(L->GetCurrentShadowNumber()<0){
			return L;
		}
		L=L->GetShadowLayersBase(L->GetCurrentShadowNumber());
	}

	return NULL;
}

static	void _BroadcastEvent( QObject *obj ,QEvent * event )
{
	if(event->isAccepted()==true){
		return;
	}
	if(obj==NULL){
		return;
	}
	GUIFormBase	*WL=dynamic_cast<GUIFormBase *>(obj);
	if(WL!=NULL && WL->IsPassedEvent()==true){
		return;
	}
	const QObjectList &Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QObject *C=Q[i];
		if(C==NULL){
			continue;
		}
		GUIFormBase	*W=dynamic_cast<GUIFormBase *>(C);
		if(W!=NULL){
			if(event->isAccepted()==false && W->GetKeyGrab()==true && W->IsPassedEvent()==false){
				QCoreApplication::sendEvent ( W, event );
				W->SetPassedEvent(true);
				if(event->isAccepted()==true){
					return;
				}
			}
		}
		_BroadcastEvent( C ,event );
	}
}

void GUIFormBase::BroadcastEvent( QEvent * event )
{
	_BroadcastEvent( GetTopParent() ,event );
	//_BroadcastEvent( this ,event );
}

static	void _ResetPassedEventFlag( QObject *obj)
{
	if(obj==NULL){
		return;
	}
	const QObjectList &Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QObject *C=Q[i];
		if(C==NULL){
			continue;
		}
		GUIFormBase	*W=dynamic_cast<GUIFormBase *>(C);
		if(W!=NULL){
			W->SetPassedEvent(false);
			W->SetIgnoreKeyEvent(true);
		}
		_ResetPassedEventFlag(C);
	}
}

void GUIFormBase::ResetPassedEventFlag(void)
{
	_ResetPassedEventFlag( GetTopParent() );
	//_BroadcastEvent( this ,event );
}

static	void _ClearIgnoreEventFlag( QObject *obj)
{
	if(obj==NULL){
		return;
	}
	const QObjectList &Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QObject *C=Q[i];
		if(C==NULL){
			continue;
		}
		GUIFormBase	*W=dynamic_cast<GUIFormBase *>(C);
		if(W!=NULL){
			W->SetIgnoreKeyEvent(false);
		}
		_ResetPassedEventFlag(C);
	}
}

void GUIFormBase::ClearIgnoreEventFlag(void)
{
	_ClearIgnoreEventFlag( GetTopParent() );
}
void GUIFormBase::changeEvent ( QEvent * event )
{
	QFrame::changeEvent ( event );
	return ;
	/*
	if(event->type()==QEvent::ActivationChange){
		if(isActiveWindow()==true){
			if(parent()==NULL){
				grabKeyboard ();
			}
		}
		else{
			if(parent()==NULL){
				releaseKeyboard ();
			}
		}
	}
	*/
}

GUIFormBase::~GUIFormBase()
{
	if(GetLayersBase()!=NULL){
		GetLayersBase()->DelAuthentication(this);
	}
	if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
		GetLayersBase()->GetEntryPoint()->GUIRemoveItem(this);
	}
	//if(_CrtCheckMemory()==false){
	//	return;
	//}
	if(ChainedParent!=NULL){
		QIODevice	*f=ChainedParent->GetChainedDevice();
		f->open(QIODevice::WriteOnly);
		SaveAll(f);
		delete	f;
	}
	if(SelectedWindowPointer!=NULL){
		delete	SelectedWindowPointer;
		SelectedWindowPointer=NULL;
	}
	if(DeridedParent!=NULL){
		removeEventFilter (this);
	}
	disconnect(this,SLOT(SlotRefreshInPlayer(int64)));
	disconnect(this,SLOT(SlotOnTheWayInPlayer(int64)));
	disconnect(this,SLOT(SlotRefreshByEveryInspection(int64)));
	disconnect(this,SLOT(SlotRefreshInEdit()));
	disconnect(this,SLOT(SlotRefreshInScanning(int64)));
	disconnect(this,SLOT(SlotDoneExecute(int64,ExecuteInspectBase::MotionMode)));
	disconnect(this,SLOT(SlotPushButton()));
}

QIODevice	*GUIFormBase::GetChainedDevice(void)
{
	QBuffer	*f=new QBuffer(&ChainedContent);
	return f;
}

GUIFormBase	*GUIFormBase::GetTopParent()	const
{
	const	GUIFormBase *LastTop=this;
	const	QWidget	*c=this;
	for(;;){
		c=c->parentWidget();
		if(c==NULL){
			break;
		}
		const	GUIFormBase *d=dynamic_cast<const GUIFormBase *>(c);
		if(d!=NULL){
			LastTop=d;
		}
	}
	return((GUIFormBase	*)LastTop);
}

bool	GUIFormBase::IsValid(int page ,int layer)const
{
	return GetParamGlobal()->IsValid(page ,layer);
}

GUIFormBase	*GUIFormBase::GetTopSurfaceWidget(int x ,int y)
{
	return this;
}

GUIFormBase	*GUIFormBase::GetParentFormBase()	const
{
	const	QWidget	*c=this;
	for(;;){
		c=c->parentWidget();
		if(c==NULL){
			break;
		}
		const GUIFormBase *d=dynamic_cast<const GUIFormBase *>(c);
		if(d!=NULL){
			return((GUIFormBase	*)d);
		}
	}
	return(NULL);
}

static	int	DeliverGetMaxIDForChildren(QObject *b ,int NowID)
{
	if(b==NULL){
		return 0;
	}
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(b);
	if(base!=NULL){
		if(base->GetFormBaseID()>NowID){
			NowID=base->GetFormBaseID();
		}
	}

	const QObjectList &Q=b->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		NowID=DeliverGetMaxIDForChildren(Q[i],NowID);
	}
	return(NowID);
}

int	GUIFormBase::DeliverGetMaxIDForChildren(int NowID)
{
	NowID=::DeliverGetMaxIDForChildren(this,NowID);
	return(NowID);
}

static	GUIFormBase	*DeliverFindForChildren(QObject *b,int ID)
{
	if(b==NULL){
		return NULL;
	}
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(b);
	if(base!=NULL){
		if(base->GetFormBaseID()==ID){
			return(base);
		}
	}

	const QObjectList &Q=b->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*e=DeliverFindForChildren(Q[i],ID);
		if(e!=NULL){
			return(e);
		}
	}
	return NULL;
}

GUIFormBase	*GUIFormBase::DeliverFindForChildren(int ID)
{
	return ::DeliverFindForChildren(this,ID);
}

void	GUIFormBase::SetFormBaseID(int ID)
{
	FormBaseID=ID;
	ID++;
	for(int i=0;i<GetChildCount();i++){
		GUIFormBase	*w=GetChild(i);
		w->FormBaseID=ID;
		ID++;
	}
}

void	GUIFormBase::AssociateComponent	(ComponentListContainer &List)
{
	if(GuiDLLPoint!=NULL){
		GuiDLLPoint->AssociateComponent(List);
	}
}

int	GUIFormBase::GetChildCount()
{
	return 0;
}
GUIFormBase	*GUIFormBase::GetChild(int index)	const
{
	return NULL;
}


static	void	PutID(GUIFormBase *topParent,QObject *thisForm)
{
	GUIFormBase	*B=dynamic_cast<GUIFormBase*>(thisForm);
	if(B!=NULL){
		B->_SetFormBaseID(topParent->DeliverGetMaxIDForChildren(0)+1);
	}

	const QObjectList &Q=thisForm->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		PutID(topParent,Q[i]);
	}
}

void	GUIFormBase::SetChildNumber(void)
{
	if(InstPoint!=NULL){
		GUIFormBase	*w=InstPoint->Handle->GetParentFormBase();
		if(w!=NULL){
			InstPoint->ChildNumber=w->FormBaseID;
		}
		else{
			InstPoint->ChildNumber=-1;
		}
	}
}


void GUIFormBase::mouseDoubleClickEvent ( QMouseEvent * Event )  
{
	if(EditMode==true){
		if(Event->button()==Qt::LeftButton){
			Mode=_CA_Nothing;
			if(GetTopClass()->CurrentActiveItem==NULL){
				GUIFormBase	*q=GetLayersBase()->GetEntryPoint()->GUIMouseLeftDownInEdit(this,Event);
				if(q!=NULL){
					PutID(GetTopParent(),q);
					GetTopClass()->CurrentActiveItem=q;
					//q->SetChildNumber();
				}
			}
			else{
				if(GetTopClass()->CurrentActiveItem==this){
					GUIFormBase	*q=GetLayersBase()->GetEntryPoint()->GUIMouseLeftDownInEdit(this,Event);
					if(GetTopClass()!=GetTopClass()->CurrentActiveItem){
						//parentWidget()->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
					}
					if(q!=NULL){
						PutID(GetTopParent(),q);
						GetTopClass()->CurrentActiveItem=q;
						GetLayersBase()->SetZoneWindow(q);
					}
					else{
			            QDrag *drag = new QDrag(this);
			            QMimeData *mimeData = new QMimeData;
						QBuffer	Buff;
						Buff.open(QIODevice::ReadWrite);
						Buff.write((const char *)&FormBaseID,sizeof(FormBaseID));
						int	X=Event->globalPos().x();
						int	Y=Event->globalPos().y();
						QPoint	Rp=mapToGlobal(QPoint(x(),y()));
						int	rX=Rp.x();
						int	rY=Rp.y();
						Buff.write((const char *)&X,sizeof(X));
						Buff.write((const char *)&Y,sizeof(Y));
						Buff.write((const char *)&rX,sizeof(rX));
						Buff.write((const char *)&rY,sizeof(rY));
						mimeData->setData("FormBase", Buff.buffer());
			            drag->setMimeData(mimeData);

			            //Qt::DropAction dropAction = drag->start();						
					}
				}
				else{
					if(GetTopClass()!=GetTopClass()->CurrentActiveItem){
					}
					GetTopClass()->CurrentActiveItem=this;
				}
			}			
		}
	}
}


void	GUIFormBase::Prepare(void)
{
}
void	GUIFormBase::ChangedValue(void)
{
	InitialPrepare();
	Prepare();
}

static	void	SetEditModeInChild(GUIFormBase *base ,QWidget *f)
{
	const QObjectList &Q=f->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget *C=dynamic_cast<QWidget *>(Q[i]);
		if(C==NULL){
			continue;
		}
		MouseEater	*ms=new MouseEater(base);
		C->installEventFilter(ms);				//remove automatically in this delete function
		SetEditModeInChild(base ,C);
	}
}

void	GUIFormBase::SetEditMode(void)
{
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget *C=dynamic_cast<QWidget *>(Q[i]);
		if(C==NULL){
			continue;
		}
		MouseEater	*ms=new MouseEater(this);
		C->installEventFilter(ms);				//remove automatically in this delete function
		SetEditModeInChild(this ,C);
	}
}

void	GUIFormBase::ViewRefreshInPlayer(int64 shownInspectionID)		//emit SignalRefresh
{
	if(ReEntryStackedViewPlayer==false){
		StackedViewPlayerCount++;
		emit	SignalRefreshInPlayer(shownInspectionID);
	}
}

void	GUIFormBase::ViewOnTheWayInPlayer(int64 shownInspectionID)		//emit SignalRefresh
{
	if(ReEntryStackedOnTheWayPlayer==false){
		emit	SignalOnTheWayInPlayer(shownInspectionID);
	}
}

void	GUIFormBase::RefreshByEveryInspection(int64 shownInspectionID)		//emit SignalRefresh
{
	StackedRunByEveryInspectionCount++;
	emit	SignalRefreshByEveryInspection(shownInspectionID);
}
void	GUIFormBase::ViewRefreshInEdit(void)		//emit SignalRefresh
{
	if(GetViewing()==true){
		emit	SignalRefreshInEdit();
	}
}
void	GUIFormBase::ViewRefreshInScanning(int64 shownInspectionID)		//emit SignalRefresh
{
	StackedViewScanningCount++;
	emit	SignalRefreshInScanning(shownInspectionID);
}

void	GUIFormBase::SlotRefreshInPlayer(int64 shownInspectionID)	//Display again
{
	if(ReEntryStackedViewPlayer==true){
		return;
	}
	ReEntryStackedViewPlayer=true;
	_ShowInPlayer(shownInspectionID);
	StackedViewPlayerCount--;
	ReEntryStackedViewPlayer=false;
}

void	GUIFormBase::SlotOnTheWayInPlayer(int64 shownInspectionID)	//Display again
{
	if(ReEntryStackedOnTheWayPlayer==true){
		return;
	}
	ReEntryStackedOnTheWayPlayer=true;
	_OnTheWayInPlayer(shownInspectionID);
	ReEntryStackedOnTheWayPlayer=false;
}
void	GUIFormBase::SlotRefreshByEveryInspection(int64 shownInspectionID)	//Display again
{
	if(ReEntryStackedRunByEveryInspection==true){
		return;
	}
	ReEntryStackedRunByEveryInspection=true;
	_RunByEveryInspection(shownInspectionID);
	StackedRunByEveryInspectionCount--;
	ReEntryStackedRunByEveryInspection=false;
}

void	GUIFormBase::SlotRefreshInEdit()	//Display again
{
	_ShowInEdit();
}

void	GUIFormBase::SlotRefreshInScanning(int64 shownInspectionID)	//Display again
{
	if(ReEntryStackedViewScanning==true){
		return;
	}
	ReEntryStackedViewScanning=true;
	_ShowInScanning(shownInspectionID);
	StackedViewScanningCount--;
	ReEntryStackedViewScanning=false;
}

void	GUIFormBase::DoneExecuteFromGUI(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode)
{
	emit	SignalDoneExecute(shownInspectionID,mode);
}
void	GUIFormBase::SlotDoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode)
{
	DoneExecute(shownInspectionID,mode);
}

GUIFormBase	*GUIFormBase::GetTopClass(void)
{
	QWidget	*p=this;
	for(;;){
		QWidget	*q=p->parentWidget ();
		if(q==NULL){
			return((GUIFormBase *)p);
		}
		p=q;
	}
	return(NULL);
}

bool	GUIFormBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	return true;
}
bool	GUIFormBase::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{	
	return true;
}
bool	GUIFormBase::Reallocate(int newPhaseNumb)
{	
	return true;
}
bool	GUIFormBase::ReallocateMasterCount(int CountMaster)
{	
	return true;
}
bool	GUIFormBase::InsertPage(int IndexPage)	//Create page before Indexed page
{	
	return true;
}
bool	GUIFormBase::RemovePage(int IndexPage)
{	
	return true;
}

static	GUIFormBase	*GetFormByName(QObject *f,QString &name)
{
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(f);
	if(base!=NULL){
		if(base->GetName()==name){
			return(base);
		}
	}

	const QObjectList &Q=f->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*ret=::GetFormByName(Q[i],name);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}
bool	GUIFormBase::IsShown(void)
{
	const	QRect	R=geometry();
	if(R.bottom()<0 || R.right()<0){
		return false;
	}
	QWidget	*XP=parentWidget();
	if(XP!=NULL){
		int	W=XP->width();
		int	H=XP->height();
		if(R.top()>=H || R.left()>=W){
			return false;
		}
	}

	QWidget	*p=this;
	for(;;){
		p=p->parentWidget();
		if(p==NULL){
			return true;
		}
		GUIFormBase	*f=dynamic_cast<GUIFormBase *>(p);
		if(f!=NULL){
			return f->IsShown();
		}
	}	
}

QString	GUIFormBase::GetDLLRoot(void)	const
{
	if(GuiDLLPoint!=NULL){
		return GuiDLLPoint->RootName;
	}
	return QString(/**/"");
}
QString	GUIFormBase::GetDLLName(void)	const
{
	if(GuiDLLPoint!=NULL){
		return GuiDLLPoint->Name;
	}
	return QString(/**/"");
}
bool	GUIFormBase::CheckDLL(const QString &FDLLRoot,const QString &FDLLName)
{
	if(GuiDLLPoint!=NULL){
		if(GuiDLLPoint->RootName==FDLLRoot
		&& GuiDLLPoint->Name==FDLLName){
			return true;
		}
	}
	else{
		if(FDLLRoot.isEmpty()==true && FDLLName.isEmpty()==true){
			return true;
		}
	}
	return false;
}

GUIFormBase	*GUIFormBase::GetFormByName(QString name)	const
{
	GUIFormBase	*q=GetTopParent();
	return ::GetFormByName(q,name);
}

static	GUIFormBase	*GetFormByNumber(QObject *f,int &Number ,int index)
{
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(f);
	if(base!=NULL){
		if(Number==index){
			return(base);
		}
		Number++;
	}

	const QObjectList &Q=f->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*ret=::GetFormByNumber(Q[i],Number ,index);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}

GUIFormBase	*GUIFormBase::GetFormByNumber(int index)	const
{
	GUIFormBase	*q=GetTopParent();
	if(index==0){
		return q;
	}
	int	r=0;
	return ::GetFormByNumber(q,r,index);
}

bool	GUIFormBase::SelectedItemExists(void)
{
	LayersBase	*Base=GetLayersBase();
	if(Base!=NULL){
		EntryPointBase	*E=Base->GetEntryPoint();
		if(E!=NULL){
			for(GUIInstancePack *h=E->GetGUIInstancePack();h!=NULL;h=h->GetNext()){
				for(GUIItemInstance *c=h->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
					if(c->Handle->GetSelectedInEditMode()==true)
						return true;
				}
			}
		}
	}
	return false;
}

void	GUIFormBase::ReleaseAllSelectedInEditMode()
{
	for(GUIInstancePack *h=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack();h!=NULL;h=h->GetNext()){
		for(GUIItemInstance *c=h->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
			c->Handle->SetSelectedInEditMode(false);
		}
	}
}

void GUIFormBase::RemoveAction()
{
	#ifdef _MSC_VER
	if(_CrtCheckMemory()==false)
		return;
	#endif
	for(GUIInstancePack *h=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack();h!=NULL;h=h->GetNext()){
		for(GUIItemInstance *c=h->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
			if(c==InstPoint){
				h->RemoveList(c);
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					return;
				}
				#endif

				if(c->Handle!=NULL){
					//c->Handle->setParent(NULL);
					//delete	c->Handle;
					c->Handle=NULL;
				}
				delete	c;
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					return;
				}
				#endif

				GetLayersBase()->GetEntryPoint()->GUISetProperty(NULL,NULL);
				break;
			}
		}
	}
	close();
}
void GUIFormBase::ForcusProperty()
{
}

static QString	GetPathForParent(QObject *obj)
{
	if(obj==NULL){
		return /**/"";
	}
	return GetPathForParent(obj->parent())+::GetSeparator()+obj->objectName();
}


static	void	MakeTextMessageList(QObject *obj,TextMessageContainer &TextMessageContainerData)
{
	QAbstractButton	*QAbstractButtonVar	=dynamic_cast<QAbstractButton *>(obj);
	if(QAbstractButtonVar!=NULL){
		if(QAbstractButtonVar->text()!=/**/""){
			TextMessageList	*L=new TextMessageList();
			L->PathAndName=GetPathForParent(obj);
			L->Message=QAbstractButtonVar->text();
			TextMessageContainerData.AppendList(L);
		}
		return;
	}
	QLabel	*QLabelVar	=dynamic_cast<QLabel *>(obj);
	if(QLabelVar!=NULL){
		if(QLabelVar->text()==/**/""){
			TextMessageList	*L=new TextMessageList();
			L->PathAndName=GetPathForParent(obj);
			L->Message=QLabelVar->text();
			TextMessageContainerData.AppendList(L);
		}
		return;
	}
	const QObjectList	&Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		MakeTextMessageList(Q[i],TextMessageContainerData);
	}
}


void GUIFormBase::ChangeTextAction()
{
	if(TextMessageContainerData.IsEmpty()==true){
		MakeTextMessageList(this,TextMessageContainerData);
	}
	EditTextMessages	Q(GetLayersBase(),TextMessageContainerData,this);
	if(Q.exec()==(int)true){
		TextMessageContainerData=Q.TextMessageContainerData;
		SetTextMessage();		
	}
	
}

static	void SetTextMessage(QObject *obj,TextMessageList *L)
{
	QString PathAndName=GetPathForParent(obj);
	if(PathAndName==L->PathAndName){
		QAbstractButton	*QAbstractButtonVar	=dynamic_cast<QAbstractButton *>(obj);
		if(QAbstractButtonVar!=NULL){
			if(QAbstractButtonVar->statusTip()!=/**/"Languaged"){
				#pragma omp critical
				{
					QAbstractButtonVar->setText(L->Message);
				}
			}
			return;		
		}
		QLabel	*QLabelVar	=dynamic_cast<QLabel *>(obj);
		if(QLabelVar!=NULL){
			if(QLabelVar->statusTip()!=/**/"Languaged"){
				#pragma omp critical
				{
					QLabelVar->setText(L->Message);
				}
			}
			return;
		}
	}
	const QObjectList	&Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		SetTextMessage(Q[i],L);
	}
}

void GUIFormBase::SetTextMessage(void)
{
	TextMessageList *a;
	//#pragma omp parallel
	//#pragma omp single private(a)
	for(a=TextMessageContainerData.GetFirst();a!=NULL;a=a->GetNext()){
		//#pragma omp task
		{
			::SetTextMessage(this,a);
		}
	}
}

bool	GUIFormBase::SaveTextMessageContainerData(QIODevice *f)
{
	return TextMessageContainerData.Save(f);
}

bool	GUIFormBase::LoadTextMessageContainerData(QIODevice *f)
{
	return TextMessageContainerData.Load(f);
}

void GUIFormBase::mouseMoveEvent ( QMouseEvent * Event )
{
	if(EditMode==true && Mode!=_CA_Nothing){
		int	dx=Event->globalPos().x()-StartPos.x();
		int	dy=Event->globalPos().y()-StartPos.y();
		if(Mode==_CA_ChangingSizeBottomRight){
			setGeometry(geometry().left(),geometry().top(),geometry().width()+dx,geometry().height()+dy);
		}
		else if(Mode==_CA_ChangingSizeTopLeft){
			setGeometry(geometry().left()+dx,geometry().top()+dy,geometry().width()-dx,geometry().height()-dy);
		}
		else if(Mode==_CA_ChangingSizeTopRight){
			setGeometry(geometry().left(),geometry().top()+dy,geometry().width()+dx,geometry().height()-dy);
		}
		else if(Mode==_CA_ChangingSizeBottomLeft){
			setGeometry(geometry().left()+dx,geometry().top(),geometry().width()-dx,geometry().height()+dy);
		}
		else if(Mode==_CA_ExtendingLeft){
			setGeometry(geometry().left()+dx,geometry().top(),geometry().width()-dx,geometry().height());
		}
		else if(Mode==_CA_ExtendingTop){
			setGeometry(geometry().left(),geometry().top()+dy,geometry().width(),geometry().height()-dy);
		}
		else if(Mode==_CA_ExtendingRight){
			setGeometry(geometry().left(),geometry().top(),geometry().width()+dx,geometry().height());
		}
		else if(Mode==_CA_ExtendingBottom){
			setGeometry(geometry().left(),geometry().top(),geometry().width(),geometry().height()+dy);
		}
		else if(Mode==_CA_Moving){
			move(geometry().left()+dx,geometry().top()+dy);
			emit	SignalMove();
		}
		StartPos=Event->globalPos();
		GetLayersBase()->SetMoveZoneWindow(this);
	}
}

static	bool	ContainGUIFormBase(QWidget *base)
{
	GUIFormBase	*f=dynamic_cast<GUIFormBase *>(base);
	if(f!=NULL){
		return true;
	}
	const QObjectList &Q=base->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget *C=dynamic_cast<QWidget *>(Q[i]);
		if(C==NULL){
			continue;
		}
		if(ContainGUIFormBase(C)==true){
			return true;
		}
	}
	return false;
}

static	void	__GetTabChildren(QWidgetList	&ret ,QWidget *base)
{
	const QObjectList &Q=base->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget *C=dynamic_cast<QWidget *>(Q[i]);
		if(C==NULL){
			continue;
		}
		QStackedWidget	*Ds=dynamic_cast<QStackedWidget *>(C);
		if(Ds!=NULL){
			if(ContainGUIFormBase(Ds)==true){
				ret.append(Ds);
			}
		}
		QTabWidget	*Dt=dynamic_cast<QTabWidget *>(C);
		if(Dt!=NULL){
			if(ContainGUIFormBase(Dt)==true){
				ret.append(Dt);
			}
		}
		__GetTabChildren(ret,C);
	}
}

static	QWidgetList	__GetTabChildren(GUIFormBase *f)
{
	QWidgetList	ret;
	const QObjectList &Q=f->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget *C=dynamic_cast<QWidget *>(Q[i]);
		if(C==NULL){
			continue;
		}
		QStackedWidget	*Ds=dynamic_cast<QStackedWidget *>(C);
		if(Ds!=NULL){
			ret.append(Ds);
		}
		QTabWidget	*Dt=dynamic_cast<QTabWidget *>(C);
		if(Dt!=NULL){
			ret.append(Dt);
		}
		__GetTabChildren(ret,C);
	}
	return(ret);
}

QWidgetList	GUIFormBase::GetTabChildren(void)
{
	return __GetTabChildren(this);
}
void GUIFormBase::mousePressEvent ( QMouseEvent * Event )
{
	if(EditMode==true){
		int	ControlSize=5;
		//grabMouse();
		if(Event->button()==Qt::LeftButton){
			LeftClickGlobalPoint=Event->globalPos();
			int	x=Event->x();
			int	y=Event->y();
			GUIFormBase	*PutTop=GetTopSurfaceWidget(x,y);
			GetLayersBase()->GetEntryPoint()->GUISetProperty(this,PutTop);
			if(Mode==_CA_Nothing && GetParentFormBase()!=NULL){
				if(width()-ControlSize<=Event->pos().x() && Event->pos().x()<width() && height()-ControlSize<=Event->pos().y() && Event->pos().y()<height()){
					Mode=_CA_ChangingSizeBottomRight;
				}
				else if(0<=Event->pos().x() && Event->pos().x()<ControlSize && 0<=Event->pos().y() && Event->pos().y()<ControlSize){
					Mode=_CA_ChangingSizeTopLeft;
				}
				else if(0<=Event->pos().x() && Event->pos().x()<ControlSize && height()-ControlSize<=Event->pos().y() && Event->pos().y()<height()){
					Mode=_CA_ChangingSizeBottomLeft;
				}
				else if(width()-ControlSize<=Event->pos().x() && Event->pos().x()<width() && 0<=Event->pos().y() && Event->pos().y()<ControlSize){
					Mode=_CA_ChangingSizeTopRight;
				}
				else if(ControlSize<=Event->pos().x() && Event->pos().x()<width()-ControlSize && 0<=Event->pos().y() && Event->pos().y()<ControlSize){
					Mode=_CA_ExtendingTop;
				}
				else if(0<=Event->pos().x() && Event->pos().x()<ControlSize && ControlSize<=Event->pos().y() && Event->pos().y()<height()-ControlSize){
					Mode=_CA_ExtendingLeft;
				}
				else if(width()-ControlSize <=Event->pos().x() && Event->pos().x()<width() && ControlSize<=Event->pos().y() && Event->pos().y()<height()-ControlSize){
					Mode=_CA_ExtendingRight;
				}
				else if(ControlSize<=Event->pos().x() && Event->pos().x()<width()-ControlSize && height()-ControlSize<=Event->pos().y() && Event->pos().y()<height()){
					Mode=_CA_ExtendingBottom;
				}
				else if(ControlSize<=Event->pos().x() && Event->pos().x()<(width()-ControlSize) && ControlSize<=Event->pos().y() && Event->pos().y()<(height()-ControlSize)){
					if((Event->modifiers() & Qt::ShiftModifier)!=0){
						if(GetSelectedInEditMode()==false)
							SetSelectedInEditMode(true);
						else
							SetSelectedInEditMode(false);
					}
					else{
						Mode=_CA_Moving;
					}
				}
				StartPos=Event->globalPos();
			}
			GetLayersBase()->SetZoneWindow(this);
		}
		else
		if(Event->button()==Qt::RightButton){
			RightClickGlobalPoint=Event->globalPos();
			int	x=Event->x();
			int	y=Event->y();
			GUIFormBase	*PutTop=GetTopSurfaceWidget(x,y);
			if(PutTop->GetSelectedInEditMode()==false && SelectedItemExists()==true){
				ReleaseAllSelectedInEditMode();
			}
			else{
				GetLayersBase()->GetEntryPoint()->GUISetProperty(this,PutTop);
				QMenu	Menu(this);
				Menu.addAction (QString(tr("Remove")), this, SLOT(RemoveAction()), Qt::Key_Delete);
				Menu.addAction (QString(tr("Property")), this, SLOT(ForcusProperty()));
				Menu.addAction (QString(tr("Text")), this, SLOT(ChangeTextAction()));
				if(SelectedItemExists()==true){
					Menu.addAction (QString(tr("Release selection")), this, SLOT(ReleaseAllSelectedInEditMode()));
				}
				Menu.addAction (QString(tr("Z order up")), this, SLOT(SlotZOrderUp()));
				QWidgetList	L=GetTabChildren();
				if(L.count()!=0){
					Menu.addAction (QString(tr("Change Tab top")), this, SLOT(ChangeTabTop()));
					Menu.addAction (QString(tr("Turn UpDown")), this, SLOT(TurnUpDown()));
					Menu.addAction (QString(tr("Delete Tab page")), this, SLOT(DeleteTabPage()));
				}
				QPoint	Q=mapToGlobal(Event->pos());
				Menu.exec(Q);
			}
		}
	}
}

void	GUIFormBase::ReflectAlignment(void)
{
	QScreen	*Scr=qGuiApp->screens()[0];
	if(Alignment=="Top"){
		QRect	r=geometry();
		GUIFormBase	*p=GetParentFormBase();
		if(p==NULL){
			setGeometry(0,0,Scr->geometry().width(),r.height());
		}
		else{
			setGeometry( p->GetClientX1()					,p->GetClientY1()
						,p->GetClientX2()-p->GetClientX1()	,r.height());		
			p->SetClientY1(p->GetClientY1()+r.height());
		}
	}
	else if(Alignment=="Left"){
		QRect	r=geometry();
		GUIFormBase	*p=GetParentFormBase();
		if(p==NULL){
			setGeometry(0,0,r.width(),Scr->geometry().height());
		}
		else{
			setGeometry( p->GetClientX1()	,p->GetClientY1()
						,r.width()			,p->GetClientY2()-p->GetClientY1());		
			//setGeometry(0,0,r.width(),p->geometry().height());
			p->SetClientX1(p->GetClientX1()+r.width());
		}
	}
	else if(Alignment=="Right"){
		QRect	r=geometry();
		GUIFormBase	*p=GetParentFormBase();
		if(p==NULL){
			setGeometry(Scr->geometry().right()-r.width(),0,r.width(),Scr->geometry().height());
		}
		else{
			//setGeometry(p->geometry().width()-r.width(),0,r.width(),p->geometry().height());		
			setGeometry( p->GetClientX2()-r.width()	,p->GetClientY1()
						,r.width()					,p->GetClientY2()-p->GetClientY1());
			p->SetClientX2(p->GetClientX2()-r.width());
		}
	}
	else if(Alignment=="Bottom"){
		QRect	r=geometry();
		GUIFormBase	*p=GetParentFormBase();
		if(p==NULL){
			setGeometry(0,Scr->geometry().bottom()-r.height(),Scr->geometry().width(),r.height());
		}
		else{
			//setGeometry(0,p->geometry().height()-r.height(),p->geometry().width(),r.height());		
			setGeometry( p->GetClientX1()					,p->GetClientY2()-r.height()
						,p->GetClientX2()-p->GetClientX1()	,r.height());
			p->SetClientY2(p->GetClientY2()-r.height());
		}
	}
	else if(Alignment=="Client"){
		GUIFormBase	*p=GetParentFormBase();
		if(p==NULL){
			setGeometry(0,0,Scr->geometry().width(),Scr->geometry().height());
		}
		else{
			//setGeometry(0,0,p->geometry().width(),p->geometry().height());
			setGeometry( p->GetClientX1()					,p->GetClientY1()
						,p->GetClientX2()-p->GetClientX1()	,p->GetClientY2()-p->GetClientY1());
		}
	}
}

void GUIFormBase::mouseReleaseEvent ( QMouseEvent * event )
{
	if(event->button()==Qt::LeftButton){
		emit	SignalRelease();
		Mode=_CA_Nothing;
	}
}

void GUIFormBase::enterEvent ( QEnterEvent * event )
{
	if(EditMode==true){
		if(Mode==_CA_Nothing){
			if (frameShape() != QFrame::StyledPanel) {
				setFrameShape(QFrame::StyledPanel);
			}
		}
		else{
			Mode=_CA_Nothing;
			if (frameShape() != QFrame::StyledPanel) {
				setFrameShape(QFrame::StyledPanel);
			}
		}
	}
	QFrame::enterEvent ( event );
}

void GUIFormBase::leaveEvent ( QEvent * event )
{
	if(EditMode==true && Mode==_CA_Nothing){
		setFrameShape(QFrame::NoFrame);
	}
}

void GUIFormBase::resizeEvent ( QResizeEvent * event )
{
	ClientY1=0;
	if(ClientX2!=width() || ClientY2!=height()){
		ReflectResize();
	}
	event->accept();
}
void GUIFormBase::ReflectResize(void)
{
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	ClientX1=0;
	ClientY1=0;

	ClientX2=width();
	ClientY2=height();

	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*C=dynamic_cast<GUIFormBase *>(Q[i]);
		if(C==NULL){
			continue;
		}
		C->ReflectAlignment();
	}
	//QRect	SelectedWindowRect;
	//if(SelectedWindowPointer!=NULL){
	//	SelectedWindowRect=SelectedWindowPointer->geometry();
	//	SelectedWindowPointer->setGeometry(0,0,1,1);
	//}
	emit	SignalResize();
	//QCoreApplication::processEvents();
	//
	//if(SelectedWindowPointer != NULL) {
	//	SelectedWindowPointer->setGeometry(SelectedWindowRect);
	//	SelectedWindowPointer->show();
	//}
	if(EditMode==true){
		GetLayersBase()->SetMoveZoneWindow(this);
	}
}
void	GUIFormBase::ReflectSize(void)
{
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	emit	SignalResize();

	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*C=dynamic_cast<GUIFormBase *>(Q[i]);
		if(C==NULL){
			continue;
		}
		C->ReflectSize();
	}
}
void GUIFormBase::moveEvent ( QMoveEvent * event )
{
	if(EditMode==true){
		GetLayersBase()->SetMoveZoneWindow(this);
	}
}

void GUIFormBase::ChangeTabTop()
{
	QWidgetList	L=GetTabChildren();
	SelectTabTop	D(GetLayersBase(),L,this);
	D.exec();
	if(D.RetMode==true){
		if(D.SelectedTabSheet!=NULL){
			D.SelectedTabSheet->setCurrentWidget(D.SelectedTabSheet->widget(D.SelectedTabPage));
		}
		else if(D.SelectedStackedSheet!=NULL){
			D.SelectedStackedSheet->setCurrentWidget(D.SelectedStackedSheet->widget(D.SelectedTabPage));
		}
	}
}

void	GUIFormBase::OpenTabToShow(QWidget *target)
{
	QWidget	*w=target;
	QWidget	*LastW=target;
	while((w=w->parentWidget())!=NULL){
		QTabWidget	*t=dynamic_cast<QTabWidget *>(w);
		if(t!=NULL){
			for(int i=0;i<t->count();i++){
				if(t->widget(i)==LastW){
					t->setCurrentIndex(i);
					break;
				}
			}
			//t->setCurrentWidget(LastW);
		}
		QStackedWidget	*s=dynamic_cast<QStackedWidget *>(w);
		if(s!=NULL){
			QWidget	*p=s->parentWidget();
			QTabWidget	*ww=NULL;
			if(p!=NULL){
				ww=dynamic_cast<QTabWidget *>(p);
			}
			if(ww!=NULL){		
				for(int i=0;i<s->count();i++){
					if(s->widget(i)==LastW){
						ww->setCurrentIndex(i);
						w=ww;
						break;
					}
				}
			}
			else{
				for(int i=0;i<s->count();i++){
					if(s->widget(i)==LastW){
						s->setCurrentIndex(i);
						break;
					}
				}
			}
			//s->setCurrentWidget(LastW);
		}
		QToolBox	*b=dynamic_cast<QToolBox *>(w);
		if(b!=NULL){
			b->setCurrentWidget(LastW);
		}
		LastW=w;
	}
}
void	GUIFormBase::ExecAsDialog(QWidget * parent)
{
	show();
	GeneralDialog	D(GetLayersBase(),this ,parent,false);
	D.exec();
	hide();
}
void	GUIFormBase::ExecAsWindow(QWidget * parent ,bool StayOnTop)
{
	GUIFormBase	*p=GetTopParent();
	if(p!=NULL){
		p->ShouldCloseWindow.AppendList(new GUIFormPointer(this));
	}
	setParent(NULL);
	if(StayOnTop==true)
		setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	else
		setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

	ForceWindowMode=true;
	show();
}
void GUIFormBase::TurnUpDown()
{
	GUITurnUpDownForm	*D=new GUITurnUpDownForm(GetTabChildren(),this);
	D->exec();
	delete	D;
}
void GUIFormBase::DeleteTabPage()
{
	QWidgetList	L=GetTabChildren();
	SelectTabTop	*D=new SelectTabTop(GetLayersBase(),L,this);
	D->exec();
	if(D->RetMode==true){
		if(QMessageBox::question(NULL,"Warning","Delete OK?")==QMessageBox::Yes){
			if(D->SelectedTabSheet!=NULL){
				QWidget	*selD=D->SelectedTabSheet->widget(D->SelectedTabPage);
				D->SelectedTabSheet->setCurrentWidget(selD);
				for(GUIItemInstance *f=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();f!=NULL;){
					if(f->HasParent(selD)==true){
						GUIItemInstance *NextF=f->GetNext();
						GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::RemoveList(f);
						f=NextF;
					}
					else{
						f=f->GetNext();
					}
				}
				RemovedTabSheet(D->SelectedTabSheet,selD);
				selD=D->SelectedTabSheet->widget(0);
				if(selD!=NULL){
					D->SelectedTabSheet->setCurrentWidget(selD);
				}
			}
			else if(D->SelectedStackedSheet!=NULL){
				QWidget	*selD=D->SelectedStackedSheet->widget(D->SelectedTabPage);
				D->SelectedStackedSheet->setCurrentWidget(selD);
				for(GUIItemInstance *f=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();f!=NULL;){
					if(f->HasParent(selD)==true){
						GUIItemInstance *NextF=f->GetNext();
						GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::RemoveList(f);
						f=NextF;
					}
					else{
						f=f->GetNext();
					}
				}
				RemovedTabSheet(D->SelectedStackedSheet,selD);
				selD=D->SelectedStackedSheet->widget(0);
				if(selD!=NULL){
					D->SelectedStackedSheet->setCurrentWidget(selD);
				}
			}
		}
	}
	delete	D;
}

void	GUIFormBase::RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)
{
	QStackedWidget	*StackedW=dynamic_cast<QStackedWidget *>(TabRoot);
	if(StackedW!=NULL){
		StackedW->removeWidget(RemovedPage);
	}
}

static	bool	HasParent(QWidget *Obj ,QWidget *p)
{
	if(Obj->parentWidget()==p){
		return true;
	}
	if(Obj->parentWidget()==NULL){
		return false;
	}
	return HasParent(Obj->parentWidget(),p);
}

bool	GUIFormBase::HasParent(QWidget *p)
{
	if(parentWidget()==p){
		return true;
	}
	if(parentWidget()==NULL){
		return false;
	}
	return ::HasParent(parentWidget(),p);
}

void	GUIFormBase::SwapTab(QWidget *TabStack ,int index1 ,int index2)
{
}

void	GUIFormBase::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	__EnumChildren(QObject *parent ,GUIFormPointerContainer &Children)
{
	GUIFormBase	*f=dynamic_cast<GUIFormBase	*>(parent);
	if(f!=NULL){
		Children.AppendList(new GUIFormPointer(f));
	}
	const QObjectList &Q=parent->children ();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		__EnumChildren(Q[i],Children);
	}
}
void	GUIFormBase::EnumChildren(GUIFormPointerContainer &Children)
{
	const QObjectList &Q=children ();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		__EnumChildren(Q[i],Children);
	}
}

void	GUIFormBase::RepaintAll(void)
{
	Repaint();
}

static	GUIFormBase	*_BroadcastDirectly(QObject *b,GUIFormBase::_BroadcastCommand cmd,int64 shownInspectionID ,int64 cmd2)
{
	if(b==NULL){
		return NULL;
	}
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(b);
	if(base!=NULL){
		switch(cmd){
			case GUIFormBase::_BC_BuildForShow:
				if(base->IsEnabledBroadcast()==true){
					base->BuildForShow();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ShowInPlayer:
				if(base->IsEnabledBroadcast()==true){
					base->_ShowInPlayer(shownInspectionID);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_OnTheWayInPlayer:
				if(base->IsEnabledBroadcast()==true){
					base->_OnTheWayInPlayer(shownInspectionID);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_RunByEveryInspection:
				if(base->IsEnabledBroadcast()==true){
					base->_RunByEveryInspection(shownInspectionID);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ShowInEdit:
				if(base->IsEnabledBroadcast()==true){
					base->_ShowInEdit();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ShowInScanning:
				if(base->IsEnabledBroadcast()==true){
					base->_ShowInScanning(shownInspectionID);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ShowInDelayed:
				if(base->IsEnabledBroadcast()==true){
					base->_ShowInDelayed();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_DoneCalc:
				if(base->IsEnabledBroadcast()==true){
					base->DoneCalc();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_StartPage:
				//if(base->IsEnabledBroadcast()==true){
					base->StartPage();
					base->SetModeStartPage(true);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				//}
				break;
			case GUIFormBase::_BC_LeavePage:
				//if(base->IsEnabledBroadcast()==true){
					if(base->GetModeStartPage()==true){
						base->LeavePage();
						base->SetModeStartPage(false);
					}
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				//}
				break;
			case GUIFormBase::_BC_WroteResult:
				if(base->IsEnabledBroadcast()==true){
					base->WroteResult(shownInspectionID);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_SetViewing:
				base->SetViewing((bool)shownInspectionID);
				if(base->GetChainedParent()!=NULL){
					base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
				}
				break;
			case GUIFormBase::_BC_TabChanged:
				if(base->IsEnabledBroadcast()==true){
					base->TabChanged();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_Terminated:
				if(base->IsEnabledBroadcast()==true){
					base->Terminated();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ReadyTerminate:
				if(base->IsEnabledBroadcast()==true){
					base->ReadyTerminate();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ReadyParam:
				if(base->IsEnabledBroadcast()==true){
					base->ReadyParam();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_StartLot:
				if(base->IsEnabledBroadcast()==true){
					base->StartLot();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_SetupLibFolder:
				if(base->IsEnabledBroadcast()==true){
					base->_SetupLibFolder(shownInspectionID,cmd2);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_ResizeAction:
				if(base->IsEnabledBroadcast()==true){
					base->_ResizeAction();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_RefreshCache:
				if(base->IsEnabledBroadcast()==true){
					base->RefreshCache();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_RepaintAll:
				if(base->IsEnabledBroadcast()==true){
					base->RepaintAll();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_SetTargetPage:
				if(base->IsEnabledBroadcast()==true){
					base->SetTargetPage(shownInspectionID);
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
			case GUIFormBase::_BC_StartInitial:
				if(base->IsEnabledBroadcast()==true){
					base->StartInitial();
					if(base->GetChainedParent()!=NULL){
						base->GetChainedParent()->BroadcastDirectly(cmd ,shownInspectionID,cmd2);
					}
				}
				break;
		}
	}

	const QObjectList &Q=b->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*e=_BroadcastDirectly(Q[i],cmd,shownInspectionID,cmd2);
		if(e!=NULL){
			return(e);
		}
	}
	return NULL;
}
static	GUIFormBase	*_BroadcastSpecifiedDirectly(QObject *b,SpecifiedBroadcaster *v)
{
	if(b==NULL){
		return NULL;
	}
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(b);
	if(base!=NULL){
		if(base->IsEnabledBroadcast()==true){
			base->SpecifiedDirectly(v);
		}
	}

	const QObjectList &Q=b->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*e=_BroadcastSpecifiedDirectly(Q[i],v);
		if(e!=NULL){
			return(e);
		}
	}
	return NULL;
}

static	GUIFormBase	*_SetEnableBroadcastForAll(QObject *b,bool flag)
{
	GUIFormBase *base=dynamic_cast<GUIFormBase *>(b);
	if(base!=NULL){
		base->SetEnabledBroadcast(flag);
	}

	const QObjectList &Q=b->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase	*e=_SetEnableBroadcastForAll(Q[i],flag);
		if(e!=NULL){
			return(e);
		}
	}
	return NULL;
}

void	GUIFormBase::SetEnableBroadcastForAll(bool flag)
{
	_SetEnableBroadcastForAll(this,flag);
}
void	GUIFormBase::SetEnabledForChildren(bool flag)
{
	::SetEnabledForChildren(this,flag);
}
void	GUIFormBase::BroadcastDirectly(_BroadcastCommand cmd ,int64 shownInspectionID ,int64 cmd2)
{
	if(EnabledBroadcast==true){
		_BroadcastDirectly(GetTopClass(),cmd,shownInspectionID,cmd2);
	}
}
void	GUIFormBase::BroadcastChildrenAndOwnDirectly(_BroadcastCommand cmd ,int64 shownInspectionID ,int64 cmd2)
{
	if(EnabledBroadcast==true){
		_BroadcastDirectly(this,cmd,shownInspectionID,cmd2);
	}
}
void	GUIFormBase::BroadcastSpecifiedDirectly(SpecifiedBroadcaster *v)
{
	if(EnabledBroadcast==true){
		_BroadcastSpecifiedDirectly(GetTopClass(),v);
		GetLayersBase()->GetEntryPoint()->SpecifiedDirectly(v);
		GetLayersBase()->GetGeneralStocker()->SpecifiedDirectly(v);
	}
}

static	void	_SetAcceptDropsForAll(QObject *obj)
{
	QWidget	*w=dynamic_cast<QWidget	*>(obj);
	if(w!=NULL){
		w->setAcceptDrops(true);
	}
	const QObjectList &Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		_SetAcceptDropsForAll(Q[i]);
	}
}

void	GUIFormBase::SetAcceptDropsForAll(void)
{
	setAcceptDrops(true);
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		_SetAcceptDropsForAll(Q[i]);
	}
}

void	GUIFormBase::BuildForShow(void)
{
}
void	GUIFormBase::ShowInPlayer(int64 shownInspectionID)
{
}
void	GUIFormBase::OnTheWayInPlayer(int64 shownInspectionID)
{
}
void	GUIFormBase::RunByEveryInspection(int64 shownInspectionID)
{
}
void	GUIFormBase::StartLot(void)
{
}
void	GUIFormBase::ShowInEdit(void)
{
}
void	GUIFormBase::ShowInScanning(int64 shownInspectionID)
{
}
void	GUIFormBase::ShowInDelayed(void)
{
}
void	GUIFormBase::_ShowInPlayer(int64 shownInspectionID)
{
	DWORD	t	=GetComputerMiliSec();
	ShowInPlayer(shownInspectionID);
	LastShowingMilisec=GetComputerMiliSec()-t;
}
void	GUIFormBase::_OnTheWayInPlayer(int64 shownInspectionID)
{
	DWORD	t	=GetComputerMiliSec();
	OnTheWayInPlayer(shownInspectionID);
	LastShowingMilisec=GetComputerMiliSec()-t;
}
void	GUIFormBase::_RunByEveryInspection(int64 shownInspectionID)
{
	DWORD	t	=GetComputerMiliSec();
	RunByEveryInspection(shownInspectionID);
	LastRunningMilisec=GetComputerMiliSec()-t;
}
void	GUIFormBase::_ShowInEdit(void)
{
	DWORD	t	=GetComputerMiliSec();
	ShowInEdit();
	LastEdittingMilisec=GetComputerMiliSec()-t;
}
void	GUIFormBase::_ShowInScanning(int64 shownInspectionID)
{
	DWORD	t	=GetComputerMiliSec();
	ShowInScanning(shownInspectionID);
	LastScanningMilisec=GetComputerMiliSec()-t;
}
void	GUIFormBase::_ShowInDelayed(void)
{
	DWORD	t	=GetComputerMiliSec();
	ShowInDelayed();
	LastShowingMilisec=GetComputerMiliSec()-t;
}
void	GUIFormBase::_ResizeAction	(void)
{
	//ReflectAlignment();
	emit	SignalResize();
}
void	GUIFormBase::DoneCalc(int64 shownInspectionID)
{
}
void	GUIFormBase::_SetupLibFolder(int LibFolderID,int originalLibFolder)
{
	SetupLibFolder(LibFolderID,originalLibFolder);
}
void	GUIFormBase::StartPage(void)
{
	SetKeyGrab(true);
	SetModeStartPage(true);
}
void	GUIFormBase::LeavePage(void)
{
	SetKeyGrab(false);
	SetModeStartPage(false);
}
void	GUIFormBase::BroadcastBuildForShow(void)
{
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow,-1);
}
void	GUIFormBase::BroadcastRefreshCache(void)
{
	BroadcastDirectly(GUIFormBase::_BC_RefreshCache,-1);
	GetLayersBase()->ShadowBroadcastRefreshCache();
}
void	GUIFormBase::BroadcastRepaintAll(void)
{
	BroadcastDirectly(GUIFormBase::_BC_RepaintAll,-1);
	GetLayersBase()->ShadowBroadcastRepaintAll();
}
void	GUIFormBase::BroadcastShowInPlayer(int64 shownInspectionID)
{
	BroadcastDirectly(GUIFormBase::_BC_ShowInPlayer,shownInspectionID);
	GetLayersBase()->ShadowBroadcastShowInPlayer(shownInspectionID);
}
void	GUIFormBase::BroadcastOnTheWayInPlayer(int64 shownInspectionID)
{
	BroadcastDirectly(GUIFormBase::_BC_OnTheWayInPlayer,shownInspectionID);
	GetLayersBase()->ShadowBroadcastOnTheWayInPlayer(shownInspectionID);
}
void	GUIFormBase::BroadcastRunByEveryInspection(int64 shownInspectionID)
{
	BroadcastDirectly(GUIFormBase::_BC_RunByEveryInspection,shownInspectionID);
	GetLayersBase()->ShadowBroadcastRunByEveryInspection(shownInspectionID);
}
void	GUIFormBase::BroadcastStartInitial(void)
{
	BroadcastDirectly(GUIFormBase::_BC_StartInitial,-1);
}

void	GUIFormBase::BroadcastShowInEdit(void)
{
	int64	Dummy=0;
	BroadcastDirectly(GUIFormBase::_BC_ShowInEdit,Dummy);
	GetLayersBase()->ShadowBroadcastShowInEdit();
}
void	GUIFormBase::BroadcastShowInScanning(int64 shownInspectionID)
{
	BroadcastDirectly(GUIFormBase::_BC_ShowInScanning,shownInspectionID);
}
void	GUIFormBase::BroadcastShowInDelayed(void)
{
	int64	Dummy=0;
	BroadcastDirectly(GUIFormBase::_BC_ShowInDelayed,Dummy);
}
void	GUIFormBase::BroadcastSetupLibFolder(int LibFolderID,int originalLibFolder)
{
	BroadcastDirectly(GUIFormBase::_BC_SetupLibFolder,LibFolderID,originalLibFolder);
}
void	GUIFormBase::BroadcastStartLot(void)
{
	BroadcastDirectly(GUIFormBase::_BC_StartLot,-1);
}
void	GUIFormBase::BroadcastStartPage(void)
{
	_BroadcastDirectly(this,GUIFormBase::_BC_StartPage,-1,0);
}
void	GUIFormBase::BroadcastLeavePage(void)
{
	if(GetLayersBase()->GetOnTerminating()==false){
		_BroadcastDirectly(this,GUIFormBase::_BC_LeavePage,-1,0);
	}
}
void	GUIFormBase::BroadcastWroteResult(int64 shownInspectionID)
{
	BroadcastDirectly(GUIFormBase::_BC_WroteResult,shownInspectionID);
}
void	GUIFormBase::BroadcastSetViewingOnChildrenWithMe(bool viewing)
{
	_BroadcastDirectly(this,GUIFormBase::_BC_SetViewing,(int64)viewing,0);
}
void	GUIFormBase::BroadcastTabChanged(void)
{
	BroadcastDirectly(GUIFormBase::_BC_TabChanged,-1);
}
void	GUIFormBase::BroadcastReadyTerminate(void)
{
	BroadcastDirectly(GUIFormBase::_BC_ReadyTerminate,-1);
}
void	GUIFormBase::BroadcastTerminated(void)
{
	BroadcastDirectly(GUIFormBase::_BC_Terminated,-1);
}
void	GUIFormBase::BroadcastResizeAction(void)
{
	BroadcastDirectly(GUIFormBase::_BC_ResizeAction,-1);
}
void	GUIFormBase::BroadcastReadyParam(void)
{
	BroadcastDirectly(GUIFormBase::_BC_ReadyParam,-1);
}
void	GUIFormBase::BroadcastSetTargetPage(int Page)
{
	BroadcastDirectly(GUIFormBase::_BC_SetTargetPage,Page);
}
void	GUIFormBase::PushButton(void)
{
	emit	SignalPushButton();
}

void GUIFormBase::MessageOutFunc(int N)
{
	//if(LayersBasePoint->MesssageOutForSequence!=NULL){
	//	LayersBasePoint->MesssageOutForSequence(N);
	//}
	ThreadSequenceAbstract	*s=GetLayersBase()->GetSequenceInstance();
	s->MessageOutExec(N);
}


void	GUIFormBase::keyPressEvent ( QKeyEvent * event )
{
	QFrame::keyPressEvent ( event );
	//event->ignore();
	//return;

	if(EntereedKeyEvent==true){
		return;
	}
	if(GetKeyGrab()==true){
		EntereedKeyEvent=true;
		if(GetLayersBase()->GetAnyData()->Exist("GUIFormBasekeyPressEvent")==false){
			GetLayersBase()->GetAnyData()->Set("GUIFormBasekeyPressEvent" ,0);
		//if(IgnoreKeyEvent==false){
			ResetPassedEventFlag();
			event->ignore();
			BroadcastEvent(event);
			ClearIgnoreEventFlag();
			AnyDataBase	*a=GetLayersBase()->GetAnyData()->Find("GUIFormBasekeyPressEvent");
			if(a!=NULL){
				GetLayersBase()->GetAnyData()->RemoveList(a);
				delete	a;
			}
		}
	}
	const QObjectList &Q=children();
	int	ChildCount=Q.count();

	for(int i=0;i<Q.count() && i<ChildCount;i++){
		if(event->isAccepted ()==true){
			break;
		}
		QWidget	*w=dynamic_cast<QWidget	*>(Q[i]);
		if(w!=NULL){
			if(FindKeyPressIgnorer(w->objectName())==NULL){
				((LQWidget *)w)->KeyPressEvent (event);
			}
		}
	}

	EntereedKeyEvent=false;
}

void	GUIFormBase::keyReleaseEvent ( QKeyEvent * event )
{
	QFrame::keyReleaseEvent ( event );

	if(EntereedKeyEvent==true){
		return;
	}
	if(GetKeyGrab()==false){
		return;
	}
	EntereedKeyEvent=true;
	if(GetLayersBase()->GetAnyData()->Exist("GUIFormBasekeyReleaseEvent")==false){
		GetLayersBase()->GetAnyData()->Set("GUIFormBasekeyReleaseEvent" ,0);
	//if(IgnoreKeyEvent==false){
		ResetPassedEventFlag();
		event->ignore();
		BroadcastEvent(event);
		ClearIgnoreEventFlag();
		AnyDataBase	*a=GetLayersBase()->GetAnyData()->Find("GUIFormBasekeyReleaseEvent");
		if(a!=NULL){
			GetLayersBase()->GetAnyData()->RemoveList(a);
			delete	a;
		}
	}
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QWidget	*w=dynamic_cast<QWidget	*>(Q[i]);
		if(w!=NULL){
			((LQWidget *)w)->KeyReleaseEvent (event);
		}
	}

	EntereedKeyEvent=false;
}


static	void	GiveName(QObject *parent,QObject *a)
{
	if(a->objectName()==/**/""){
		QString		VNameStr=QString(a->metaObject()->className())+QString("_");
		const QObjectList &Q=parent->children();
		int	ChildCount=Q.count();
		for(int v=1;;v++){
			QString	VName=VNameStr+QString::number(v);
			int	i;		
			for(i=0;i<Q.count() && i<ChildCount;i++){
				if(Q[i]->objectName()==VName){
					break;
				}
			}
			if(i>=Q.count()){
				a->setObjectName(VName);
				break;
			}
		}
	}
	const QObjectList &Q=a->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GiveName(a,Q[i]);
	}
}

void	GUIFormBase::GiveName(QObject *parent)
{
	if(objectName()==/**/""){
		for(int v=1;;v++){
			QString	VName=QString(metaObject()->className())+QString("_")+QString::number(v);
			if(parent!=NULL){
				int	i;
				const QObjectList &Q=parent->children();
				int	ChildCount=Q.count();
				for(i=0;i<Q.count() && i<ChildCount;i++){
					if(Q[i]->objectName()==VName){
						break;
					}
				}
				if(i>=Q.count()){
					setObjectName(VName);
					break;
				}
			}
			else{
				setObjectName(VName);
				break;
			}
		}
	}
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		::GiveName(this,Q[i]);
	}
}


static	void	InstallEventHandlerChild(QObject *c,LayersBase *Base,PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData)
{
	PasswordFilter *k;
	/*
	QAbstractButton	*vButton=dynamic_cast<QAbstractButton *>(c);
	if(vButton!=NULL){
		k=f->CreateNew(Base,c);
		PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(k));
		vButton->installEventFilter(k);
		vButton->setAcceptDrops(true);
	}
	QLineEdit	*LEdit=dynamic_cast<QLineEdit *>(c);
	if(LEdit!=NULL){
		k=f->CreateNew(Base,c);
		PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(k));
		LEdit->installEventFilter(k);
		LEdit->setAcceptDrops(true);
	}
	QAbstractSpinBox	*SBox=dynamic_cast<QAbstractSpinBox	*>(c);
	if(SBox!=NULL){
		k=f->CreateNew(Base,c);
		PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(k));
		SBox->installEventFilter(k);
		SBox->setAcceptDrops(true);
	}
	QFrame	*SFrame=dynamic_cast<QFrame	*>(c);
	if(SFrame!=NULL){
		k=f->CreateNew(Base,c);
		PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(k));
		SFrame->installEventFilter(k);
		SFrame->setAcceptDrops(true);
	}
	*/
	QWidget	*d=dynamic_cast<QWidget	*>(c);
	if(d!=NULL){
		k=f->CreateNew(Base,c);
		PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(k));
		d->installEventFilter(k);
		d->setAcceptDrops(true);
	}

	const QObjectList &Q=c->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		InstallEventHandlerChild(Q[i],Base,f,PasswordFilterPointerData);
	}
	QTabWidget	*STab=dynamic_cast<QTabWidget	*>(c);
	if(STab!=NULL){
		QTabBar *STabBar=STab->tabBar();
		int	N=STabBar->count();
		const QObjectList &Qb=STabBar->children();
		for(int i=0;i<N;i++){
			InstallEventHandlerChild(Qb[i],Base,f,PasswordFilterPointerData);
		}
	}
}

void	GUIFormBase::InstallEventHandler(PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData)
{
	installEventFilter(f);
	PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(f));
	setAcceptDrops(true);

	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		InstallEventHandlerChild(Q[i],GetLayersBase(),f,PasswordFilterPointerData);
	}
}

QString	GetdObjPath(QObject *d)
{
	QString	Ret;

	while(d->parent()!=NULL){
		if(Ret.isEmpty()==false){
			Ret=d->objectName()+::GetSeparator()+Ret;
		}
		else{
			Ret=d->objectName();
		}
		if(dynamic_cast<GUIFormBase *>(d)!=NULL){
			return Ret;
		}
		d=d->parent();
	}
	return /**/"";
}


static	void	InstallEventHandlerOnlyPasswordChild(QObject *c,LayersBase *Base,PasswordFilter *f,PasswordInControl *m)
{
	QString	CurrentPath=GetdObjPath(c);
	if(m->GetControlPathName()==CurrentPath){
		QAbstractButton	*vButton=dynamic_cast<QAbstractButton *>(c);
		if(vButton!=NULL){
			vButton->installEventFilter(f->CreateNew(Base,c));
			vButton->setAcceptDrops(true);
		}
		QLineEdit	*LEdit=dynamic_cast<QLineEdit *>(c);
		if(LEdit!=NULL){
			LEdit->installEventFilter(f->CreateNew(Base,c));
			LEdit->setAcceptDrops(true);
		}
		QAbstractSpinBox	*SBox=dynamic_cast<QAbstractSpinBox	*>(c);
		if(SBox!=NULL){
			SBox->installEventFilter(f->CreateNew(Base,c));
			SBox->setAcceptDrops(true);
		}
	}
	const QObjectList &Q=c->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		InstallEventHandlerOnlyPasswordChild(Q[i],Base,f,m);
	}
}

void	GUIFormBase::InstallEventHandlerOnlyPassword(PasswordFilter *f,PasswordInControl *c)
{
	QString	ObjPath;
	GetObjectPath(this,ObjPath);
	if(c->GetControlPathName()==ObjPath && c->GetControlName()==objectName()){
		installEventFilter(f->CreateNew(GetLayersBase(),this));
		setAcceptDrops(true);
	}
	const QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		InstallEventHandlerOnlyPasswordChild(Q[i],GetLayersBase(),f,c);
	}
}


void ChildLoopOnIdleCountUp(QObject *g)
{
	const QObjectList Q=g->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase *b=dynamic_cast<GUIFormBase *>(Q[i]);
		if(b!=NULL){
			b->OnIdleCountUp();
		}
		else{
			ChildLoopOnIdleCountUp(Q[i]);
		}
	}
}
void GUIFormBase::OnIdleCountUp(void)
{
	OnIdleCounter++;

	const	QObjectList Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase *b=dynamic_cast<GUIFormBase *>(Q[i]);
		if(b!=NULL){
			b->OnIdleCountUp();
		}
		else{
			ChildLoopOnIdleCountUp(Q[i]);
		}
	}
	SendSyncCommand();
}

bool ChildLoopOnIdle(QObject *g)
{
	bool	Ret=true;
	const QObjectList &Q=g->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase *b=dynamic_cast<GUIFormBase *>(Q[i]);
		if(b!=NULL){
			if(b->LoopOnIdle()==false){
				Ret=false;
			}
		}
		else{
			if(ChildLoopOnIdle(Q[i])==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool GUIFormBase::LoopOnIdle(void)
{
	bool	Ret=true;
	if(OnIdle()==false){
		Ret=false;
	}
	const	QObjectList &Q=children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		GUIFormBase *b=dynamic_cast<GUIFormBase *>(Q[i]);
		if(b!=NULL){
			if(b->LoopOnIdle()==false){
				Ret=false;
			}
		}
		else{
			if(ChildLoopOnIdle(Q[i])==false){
				Ret=false;
			}
		}
	}
	SendSyncCommand();
	return Ret;
}

void GUIFormBase::closeEvent ( QCloseEvent * event )
{
	if(ForceWindowMode==true){
		event->ignore();
		hide();
		emit	SignalClose(this);
	}
	else{
		emit	SignalClose(this);
		if(RootForm==true){
			GUIInitializerPoint->GUIInstanceRoot.RemoveList(GUIInstancePackPoint);
			delete	GUIInstancePackPoint;
		}
		QFrame::closeEvent (event);
		deleteLater ();
	}
}

void	GUIFormBase::SlotCommand(int cmd)
{
	GetLayersBase()->MainFormCommand(cmd);
}

void	GUIFormBase::SlotWroteSlave(XDateTime tm)
{
	QString	LStr=tm.toString("hhmmss");	
	GetLayersBase()->WroteSlave(tm);
}

void	GUIFormBase::SlotChangeLotInfo(int DeliveryNo)
{
	if(GetLayersBase()->GetLot(DeliveryNo)!=NULL){
		GetLayersBase()->GetLot(DeliveryNo)->ChangeLotInfo();
	}
}

int		GUIFormBase::GetPageNumb(void)			const	{	return GetLayersBase()->GetPageNumb();		}
int		GUIFormBase::GetPhaseNumb(void)			const	{	return GetLayersBase()->GetPhaseNumb();		}
int		GUIFormBase::GetLayerNumb(int page)		const	{	return GetLayersBase()->GetLayerNumb(page);		}
int		GUIFormBase::GetCountAllMasterBuff(void)	const	{	return GetLayersBase()->GetCountAllMasterBuff();		}
int		GUIFormBase::GetCountOnlyMasterBuff(void)	const	{	return GetLayersBase()->GetCountOnlyMasterBuff();		}
int		GUIFormBase::GetCountDispatchMasterBuff(void)const	{	return GetLayersBase()->GetCountDispatchMasterBuff();	}
int		GUIFormBase::GetDotPerLine(int page)	const
{
	return GetLayersBase()->GetDotPerLine(page);
}
int		GUIFormBase::GetMaxLines(int page)	const
{
	return GetLayersBase()->GetMaxLines(page);
}
void	GUIFormBase::SetTargetPage(int page)			{	TargetPage=page;	}
int		GUIFormBase::GetTargetPage(void)		const	{	return TargetPage;	}

ParamGlobal	*GUIFormBase::GetParamGlobal(void)		const	{	return GetLayersBase()->GetParamGlobal();	}
ParamComm	*GUIFormBase::GetParamComm(void)		const	{	return GetLayersBase()->GetParamComm();		}
ParamGUI	*GUIFormBase::GetParamGUI(void)			const	{	return GetLayersBase()->GetParamGUI();		}
int			GUIFormBase::GetCurrentShadowLevel(void)const	{	return GetLayersBase()->GetCurrentShadowLevel();	}

bool	GUIFormBase::ExecuteMacro(const QString &FuncName, QStringList &Args, bool &ExeReturn)
{
	if(GuiDLLPoint!=NULL){
		ExportFuncForMacro	*f=GuiDLLPoint->SearchMacroFunc(FuncName);
		if(f!=NULL){
			if(f->DLL_ExcuteMacro!=NULL){
				ExeReturn=f->DLL_ExcuteMacro(this,Args);
				return true;
			}
		}
	}
	return false;
}

static	bool	_SaveAll(QObject *obj,QIODevice *f ,int32 &N)
{
	if(obj==NULL){
		return true;
	}
	GUIFormBase	*W=dynamic_cast<GUIFormBase *>(obj);
	if(W!=NULL && W->GetGuiDLLPoint()!=NULL){
		if(::Save(f,W->GetGuiDLLPoint()->RootName)==false){
			return false;
		}
		if(::Save(f,W->GetGuiDLLPoint()->Name)==false){
			return false;
		}
		if(::Save(f,W->GetName())==false){
			return false;
		}
		if(W->SaveContent(f)==false){
			return false;
		}
		N++;
	}

	const QObjectList &Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QObject *C=Q[i];
		if(C==NULL){
			continue;
		}
		if(::_SaveAll(C,f,N)==false){
			return false;
		}
	}
	return true;
}

bool	GUIFormBase::SaveAll(QIODevice *f)
{
	int32	N=0;
	QByteArray	ABuff;
	QBuffer	Buff(&ABuff);
	Buff.open(QIODevice::WriteOnly);
	bool	ret=_SaveAll(this,&Buff,N);
	if(ret==false){
		return false;
	}
	if(::Save(f,N)==false){
		return false;
	}
	if(::Save(f,ABuff)==false){
		return false;
	}
	return true;
}

bool	GUIFormBase::LoadAll(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	QByteArray	ABuff;
	if(::Load(f,ABuff)==false){
		return false;
	}

	QBuffer	Buff(&ABuff);
	Buff.open(QIODevice::ReadOnly);
	for(int i=0;i<N;i++){
		QString	SRoot;
		QString	SName;
		QString	InstName;

		if(::Load(&Buff,SRoot)==false){
			return false;
		}
		if(::Load(&Buff,SName)==false){
			return false;
		}
		if(::Load(&Buff,InstName)==false){
			return false;
		}
		GUIFormBase	*c=SearchFormInChild(SRoot,SName,InstName);
		if(c==NULL){
			return false;
		}
		if(c->LoadContent(&Buff)==false){
			return false;
		}
	}
	return true;
}
void	GUIFormBase::ActivePhaseList(IntList &PhaseList)
{
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}
}

QStringList	GUIFormBase::GetAllRelatedForm(void)
{
	QStringList	Ret;
	if(ReEntrantCount>0)
		return Ret;
	ReEntrantCount++;
	QStringList	List=GetRelatedForm();
	Ret=List;
	for(int i=0;i<List.count();i++){
		GUIFormBase	*L=GetLayersBase()->FindByName(List[i]);
		if(L!=NULL && L!=this){
			QStringList	D=L->GetAllRelatedForm();
			int	N=Ret.count();
			for(int k=0;k<D.count();k++){
				bool	Found=false;
				for(int j=0;j<N;j++){
					if(Ret[j]==D[k]){
						Found=true;
						break;
					}
				}
				if(Found==false){
					Ret+=D[k];
				}
			}
		}
	}
	ReEntrantCount--;
	return Ret;
}

bool	GUIFormBase::SetDeridedParent(GUIFormBase *p)
{
	if(typeid(*this).name()==typeid(*p).name()){
		if(DeridedParent!=NULL){
			p->removeEventFilter (this);
		}

		p->installEventFilter(this);
		DeridedParent=p;
		return true;
	}
	return false;
}

bool GUIFormBase::eventFilter ( QObject * watched, QEvent * event )
{
	CalledFromDeridedParent(DeridedParent,event);
	return QObject::eventFilter(watched, event);
}

static	GUIFormBase	*_SearchFormInChild(QObject *obj
										,const QString &SRoot
										,const QString &SName
										,const QString &InstName)
{
	if(obj==NULL){
		return NULL;
	}
	GUIFormBase	*W=dynamic_cast<GUIFormBase *>(obj);
	if(W!=NULL && W->GetGuiDLLPoint()!=NULL){
		if(W->GetGuiDLLPoint()->RootName==SRoot && W->GetGuiDLLPoint()->Name==SName && W->GetName()==InstName){
			return W;
		}
	}

	const QObjectList &Q=obj->children();
	int	ChildCount=Q.count();
	for(int i=0;i<Q.count() && i<ChildCount;i++){
		QObject *C=Q[i];
		if(C==NULL){
			continue;
		}
		GUIFormBase	*d=_SearchFormInChild(C
										,SRoot
										,SName
										,InstName);
		if(d!=NULL){
			return d;
		}
	}
	return NULL;
}

GUIFormBase	*GUIFormBase::SearchFormInChild(const QString &SRoot,const QString &SName,const QString &InstName)
{
	return _SearchFormInChild(this,SRoot,SName,InstName);
}

void	GUIFormBase::SetError(int errorCode , const QString &errorMessage ,ErrorCodeList::CautionLevel level)
{
	GetLayersBase()->SendErrorToMaster(errorCode , errorMessage ,level);
}
void	GUIFormBase::SlotZOrderUp()
{
	emit	SignalRaiseUp();
}
bool	GUIFormBase::TxSync(QByteArray &f,int MilisecToWaitForAck)
{
	bool	Ret=false;
	GuiDLLItem	*s=GetGuiDLLPoint();
	if(s!=NULL && GetLayersBase()->GetSyncGUIData()!=NULL){
		Ret=GetLayersBase()->GetSyncGUIData()->Send(s->RootName,s->Name,Name,f,MilisecToWaitForAck);
	}
	return Ret;
}
void	GUIFormBase::TxSyncNoBlock(QByteArray &f)
{
	SyncCommandMutex.lock();
	int	n=SyncCommandListContainer.GetCount();
	while(n>100){
		SyncCommandList	*s=SyncCommandListContainer.GetFirst();
		SyncCommandListContainer.RemoveList(s);
		delete	s;
		n--;
	}
	SyncCommandMutex.unlock();

	SyncCommandList	*t=new SyncCommandList();
	t->Array=f;
	SyncCommandMutex.lock();
	SyncCommandListContainer.AppendList(t);
	SyncCommandMutex.unlock();
}

void	GUIFormBase::SendSyncCommand(void)
{
	SyncCommandMutex.lock();
	SyncCommandList	*s=SyncCommandListContainer.GetFirst();
	SyncCommandMutex.unlock();

	if(s!=NULL){
		if(TxSync(s->Array,200)==true){
			SyncCommandMutex.lock();
			SyncCommandListContainer.RemoveList(s);
			SyncCommandMutex.unlock();
			delete	s;
		}
	}
}

void	GUIFormBase::SlotTriggerMenu(int ID)
{
	ExecuteMenu(ID);
}
int		GUIFormBase::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	if(GuiDLLPoint!=NULL){
		return GuiDLLPoint->RegistMacroFunction(Functions,MaxBuffer);
	}
	return -1;
}
void	GUIFormBase::GetMacroNames(QStringList &Str)
{
	if(GuiDLLPoint!=NULL){
		GuiDLLPoint->GetMacroNames(Str);
	}
}
void	GUIFormBase::ExecuteMacro(const QString &FunctionName,const QString &Arg1
															 ,const QString &Arg2
															 ,const QString &Arg3
															 ,const QString &Arg4
															 ,const QString &Arg5
															 ,const QString &Arg6
															 ,const QString &Arg7
															 ,const QString &Arg8
															 ,const QString &Arg9
															 ,const QString &Arg10)
{
	if(GuiDLLPoint!=NULL){
		GuiDLLPoint->ExecuteMacro(this,FunctionName
											,Arg1
											,Arg2
											,Arg3
											,Arg4
											,Arg5
											,Arg6
											,Arg7
											,Arg8
											,Arg9
											,Arg10);
	}
}
	
//----------- Unit-------------
	
bool	GUIFormBase::IsUnitMode(void)
{
	return GetParamGlobal()->IsUnitMode();
}

double	GUIFormBase::TransformPixelToUnit(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnit(Page,pixel);
}

double	GUIFormBase::TransformUnitToPixel(int Page,double unit)
{
	return GetParamGlobal()->TransformUnitToPixel(Page,unit);
}

QString	GUIFormBase::TransformPixelToUnitStr(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitStr(Page,pixel);
}

QString	GUIFormBase::GetUnitStr(double unit)
{
	return GetParamGlobal()->GetUnitStr(unit);
}


double	GUIFormBase::TransformPixelToUnitSquare(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquare(Page,pixel);
}

double	GUIFormBase::TransformUnitToPixelSquare(int Page,double unit)
{
	return GetParamGlobal()->TransformUnitToPixelSquare(Page,unit);
}

QString	GUIFormBase::TransformPixelToUnitSquareStr(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquareStr(Page,pixel);
}

QString	GUIFormBase::GetUnitSquareStr(double unit)
{
	return GetParamGlobal()->GetUnitSquareStr(unit);
}

//==============================================================

KeyPressIgnorer::KeyPressIgnorer ( int *_EffectiveKey ,int _EffectiveKeyCount ,QObject * parent)
	:QObject(parent)
{
	if(_EffectiveKeyCount!=0){
		EffectiveKey	=new int[_EffectiveKeyCount];
		EffectiveKeyCount=_EffectiveKeyCount;
		for(int i=0;i<EffectiveKeyCount;i++){
			EffectiveKey[i]=_EffectiveKey[i];
		}
	}
	else{
		EffectiveKey=NULL;
		EffectiveKeyCount=0;
	}
}
KeyPressIgnorer::~KeyPressIgnorer(void)
{
	if(EffectiveKey!=NULL){
		delete	[]EffectiveKey;
		EffectiveKey=NULL;
		EffectiveKeyCount=0;
	}
}


 bool KeyPressIgnorer::eventFilter(QObject *obj, QEvent *event)
 {
     if (event->type() == QEvent::KeyPress) {
         QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		 if(keyEvent!=NULL){
			 for(int i=0;i<EffectiveKeyCount;i++){
				 if(EffectiveKey[i]==keyEvent->key()){
					 return false;
				 }
			 }
			 /*
			if(keyEvent->key()==Qt::Key_Up
			|| keyEvent->key()==Qt::Key_Down
			|| keyEvent->key()==Qt::Key_Left
			|| keyEvent->key()==Qt::Key_Right
			|| keyEvent->key()==Qt::Key_Return
			|| keyEvent->key()==Qt::Key_Escape
			*/
			 keyEvent->ignore();
			return true;
		 }
     } 
	// standard event processing
	return QObject::eventFilter(obj, event);
 }
static	void	InstallIgnoreKeyForChild(QObject *Obj ,QObject *Parent 
										,int *EffectiveKey ,int EffectiveKeyCount
										,NPListPack<KeyPressIgnorerPointer>	&KeyPressIgnorerContainer)
{
	KeyPressIgnorer	*n=new KeyPressIgnorer(EffectiveKey ,EffectiveKeyCount ,Parent);
	KeyPressIgnorerContainer.AppendList(new KeyPressIgnorerPointer(n,Obj->objectName()));
	Obj->installEventFilter(n);
	const QObjectList Q=Obj->children();	//Not &.  & increase Q
	for(int i=0;i<Q.count();i++){ 
		::InstallIgnoreKeyForChild(Q[i],Parent,EffectiveKey ,EffectiveKeyCount,KeyPressIgnorerContainer);
	}
}

void	GUIFormBase::InstallIgnoreKeyForChild(int *EffectiveKey ,int EffectiveKeyCount)
{
	KeyPressIgnorerContainer.RemoveAll();
	const QObjectList Q=children();	//Not &.  & increase Q
	for(int i=0;i<Q.count();i++){
		::InstallIgnoreKeyForChild(Q[i],this,EffectiveKey ,EffectiveKeyCount,KeyPressIgnorerContainer);
	}
}

KeyPressIgnorer	*GUIFormBase::FindKeyPressIgnorer(const QString &objname)
{
	for(KeyPressIgnorerPointer *s=KeyPressIgnorerContainer.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ObjName==objname){
			return s->Pointer;
		}
	}
	return NULL;
}

void	GUIFormBase::SetSignal(QObject *target,const char *signal,const char *slotfunc)
{
	connect(target,signal	,this,slotfunc);
}

void	GUIFormBase::CreateSelectedWindow(void)
{
	if(SelectedWindowPointer==NULL){
		SelectedWindowPointer=new SelectedWindow(this);
		raise();
	}
	SelectedWindowPointer->show();
	SelectedWindowPointer->update();
}
	
bool	GUIFormBase::SaveInPacket(QIODevice *f ,GUIDirectMessage *packet)
{
	QString	ClassName=typeid(packet).name();
	if(::Save(f,ClassName)==false)
		return false;
	return packet->Save(f);
}
	
QString		GUIFormBase::LoadInPacket(QIODevice *f)
{
	//return packet->Load(f);
	QString	ClassName;
	if(::Load(f,ClassName)==false)
		return /**/"";
	return ClassName;
}
void	GUIFormBase::RegisterExecuteStartByInspection	(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredStartByInspection.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredStartByInspection.Add(this);
	}
}
void	GUIFormBase::RegisterExecutePreAlignment		(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredPreAlignment.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredPreAlignment.Add(this);
	}
}
void	GUIFormBase::RegisterExecuteAlignment			(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredAlignment.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredAlignment.Add(this);
	}
}
void	GUIFormBase::RegisterExecutePreProcessing		(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredPreProcessing.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredPreProcessing.Add(this);
	}
}
void	GUIFormBase::RegisterExecuteProcessing			(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredProcessing.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredProcessing.Add(this);
	}
}
void	GUIFormBase::RegisterExecuteProcessingRevived	(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredProcessingRevived.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredProcessingRevived.Add(this);
	}
}
void	GUIFormBase::RegisterExecutePostProcessing		(void)
{
	if(GUIInstancePackPoint!=NULL){
		for(GUIFormBasePointer *f=GUIInstancePackPoint->RegisteredPostProcessing.GetFirst();f!=NULL;f=f->GetNext()){
			if(f->GetForm()==NULL){
				return;
			}
		}
		GUIInstancePackPoint->RegisteredPostProcessing.Add(this);
	}
}

void	GUIFormBase::EmitRepaint(void)
{
	emit	SignalRepaint();
}
void	GUIFormBase::SlotRepaint()
{
	repaint();
}

void	ParamGUI::ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	emit	SignalExecuteForByteArray(Category ,KeyName ,data);
}
//--------------------------------------------------------------------------------------------------------

SelectedWindow::SelectedWindow(GUIFormBase *partner)
	:QWidget(partner->parentWidget())
{
	Partner=partner;
}
SelectedWindow::~SelectedWindow(void)
{
	Partner->SelectedWindowPointer=NULL;
}

void SelectedWindow::paintEvent(QPaintEvent *e)
{
	setGeometry( Partner->geometry().left()-3,Partner->geometry().top()-3
				,Partner->geometry().width()+6 ,Partner->geometry().height()+6);

	if(Partner->GetSelectedInEditMode()==true){
	    QPainter p(this);
		p.fillRect(rect(), QColor(0, 255, 0, 255));
	}
	else{
	    QPainter p(this);
		p.fillRect(rect(), QColor(0, 0, 0, 0));
	}
}

//--------------------------------------------------------------------------------------------------------
ZoneWindowForEdit::ZoneWindowForEdit(QWidget * parent)
	:QFrame(parent)
{
	//setWindowFlags(Qt::CustomizeWindowHint);
	setAutoFillBackground(true);
}

void ZoneWindowForEdit::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);

	pnt.setPen(Qt::red);
	pnt.drawLine(0,0,width()-1,0);
	pnt.drawLine(width()-1,0,width()-1,height()-1);
	pnt.drawLine(0,height()-1,width()-1,height()-1);
	pnt.drawLine(0,0,0,height());

	pnt.setPen(Qt::blue);
	pnt.drawLine(1,1,width()-2,1);
	pnt.drawLine(width()-2,1,width()-2,height()-2);
	pnt.drawLine(1,height()-2,width()-2,height()-2);
	pnt.drawLine(1,1,1,height()-1);
}
//--------------------------------------------------------------------------------------------------------
void	GUIFormBasePointerContainer::Repaint(void)
{
	for(GUIFormBasePointer *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->GetForm()->Repaint();
	}
}
bool	GUIFormBase::SetLanguage(const QString &MemberName,LanguageStringList *s)
{
	if(InstPoint!=NULL){
		return InstPoint->SetLanguage(MemberName,s);
	}
	return false;
}

void	GUIFormBase::PickupGUILanguage(GUILanguageContainer &GUILanguageContainerInst)
{
	if(InstPoint!=NULL){
		InstPoint->PickupGUILanguage(GUILanguageContainerInst);
	}
}
void	GUIFormBase::ReflectGUILanguage(void)
{
	for(GUILanguageList *L=GetLayersBase()->GetGUILanguageContainer().GetFirst();L!=NULL;L=L->GetNext()){
		if(L->DLLRoot==GetDLLRoot() && L->DLLName==GetDLLName()
		&& L->InstName==GetName()){
			int	LangCode=GetLayersBase()->GetLanguageCode();
			LanguageStringList	*s=L->LanguageText.FindLanguage(LangCode);
			if(s!=NULL){
				if(LangCode!=0){
					if(s->Text.isEmpty()==true && s->TextList.count()==0){
						s=L->LanguageText.FindLanguage(0);
					}
				}
				SetLanguage(L->MemberName,s);
			}
		}
	}
}