//#include "GeneralStackFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralStackForm\GeneralStackForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralStackForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include "XStatusController.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XMacroFunction.h"
#include "XEntryPoint.h"


static	bool	MacroShowPage(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"StackForm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General stack form");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeTab(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralStackForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"Msgs";
	Data[0].Pointer				 =&((GeneralStackForm *)Instance)->Msgs;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"RegNo";
	Data[1].Pointer				 =&((GeneralStackForm *)Instance)->RegNo;
	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralStackForm.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShowPage";
		Functions[ret].Explain.append(/**/"Show tab page");
		Functions[ret].ArgName.append(/**/"tab page name");
		Functions[ret].DLL_ExcuteMacro	=MacroShowPage;
		ret++;
	}
	return ret;
}
static	bool	MacroShowPage(GUIFormBase *Instance ,QStringList &Args)
{
	GeneralStackForm	*V=dynamic_cast<GeneralStackForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	PageName=Args[0];

	V->CommandShowPage(PageName);

	return true;
}
//==================================================================================================

GeneralStackPage::GeneralStackPage(LayersBase *Base ,GeneralStackForm *p,QWidget *parent)
:GUIFormBase(Base,parent)
,Parent(p)
{
	SetKeyGrab(false);
	SetAlignment(/**/"Client");
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
GeneralStackPage::~GeneralStackPage(void)
{
}
void	GeneralStackPage::Prepare(void)
{
}
void	GeneralStackPage::ResizeAction(void)
{
}
bool	GeneralStackPage::IsShown(void)
{
	if(Parent->GetTopTabWizardPage()==this){
		return Parent->IsShown();
	}
	return false;
}
//void	GeneralStackPage::LeavePage(void)
//{
//	//GUIFormBase::LeavePage();
//	BroadcastLeavePage();
//}


GeneralStackForm::GeneralStackForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	FromSync	=false;
	oPageNumber=NULL;
	LastID		=-1;
	RegNo		=550;
	Msgs.append(QString(/**/"Default"));
	Msgs.append(QString(/**/"Page1"));
	resize(400,400);
	MainTab.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

GeneralStackForm::~GeneralStackForm(void)
{
}

void	GeneralStackForm::Prepare(void)
{
	if(Msgs.count()>MainTab.count()){
		for(int i=MainTab.count();i<Msgs.count();i++){
			GeneralStackPage	*w=new GeneralStackPage(GetLayersBase(),this,&MainTab);
			MainTab.addWidget(w);
		}
	}
	else if(Msgs.count()<MainTab.count()){
		while(Msgs.count()<MainTab.count()){
			MainTab.removeWidget(MainTab.widget(0));
		}
	}

	for(int i=0;i<Msgs.count();i++){
		QString	S=Msgs.value(i);
		QWidget	*w=MainTab.widget(i);
		GeneralStackPage	*wt=dynamic_cast<GeneralStackPage *>(w);
		if(wt!=NULL){
			wt->setWindowTitle(S);
			wt->SetName(S);
		}
	}

	ResizeAction();
	update();

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			oPageNumber	=new SignalOperandInt(this,RegNo,/**/"GeneralStackForm:oPageNumber");
			connect(oPageNumber	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(oPageNumber,&Error)==false){
				oPageNumber->ShowErrorMessage(Error);
			}
		}
	}
	SlotIDClicked(0);
}

int	GeneralStackForm::GetChildCount()
{
	return MainTab.count()+1;
}
GUIFormBase	*GeneralStackForm::GetChild(int index)	const
{
	if(index<MainTab.count())
		return dynamic_cast<GUIFormBase*>(MainTab.widget(index));
	return (GUIFormBase	*)this;
}

GUIFormBase	*GeneralStackForm::GetTopSurfaceWidget(int x ,int y)
{
	if(MainTab.geometry().left()<=x && x<MainTab.geometry().right()
		&& MainTab.geometry().top()<=y && y<MainTab.geometry().bottom()){
		return dynamic_cast<GUIFormBase*>(MainTab.currentWidget());
	}
	return this;
}
 GUIFormBase	*GeneralStackForm::GetTopTabWizardPage(void)
 {
	QWidget	*w=MainTab.currentWidget();
	GeneralStackPage	*W=dynamic_cast<GeneralStackPage *>(w);
	if(W!=NULL){
		return W;
	}
	return NULL;

 }

void	GeneralStackForm::ResizeAction()
{
	MainTab.move(0,0);
	int	W=width();
	int	H=height();
	MainTab.resize(W,H);

	for(int i=0;i<MainTab.count();i++){
		GeneralStackPage	*w=dynamic_cast<GeneralStackPage *>(MainTab.widget(i));
		if(w!=NULL){
			w->resize(W,H);
		}
	}
}

void	GeneralStackForm::SlotIDClicked(int id)
{
	if(LastID>=0){
		GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(LastID);
		w->BroadcastLeavePage();
	}

	MainTab.setCurrentIndex(id);
	
	for(int i=0;i<MainTab.count();i++){
		GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(i);
		if(i==id){
			w->BroadcastSetViewingOnChildrenWithMe(true);
			w->BroadcastStartPage();
			w->SetKeyGrab(true);
		}
		else{
			w->BroadcastSetViewingOnChildrenWithMe(false);
			w->BroadcastLeavePage();
			w->SetKeyGrab(false);
		}
	}
	GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(id);
	if(w!=NULL){
		w->BroadcastStartPage();
		BroadcastTabChanged();
		LastID=id;
		if(oPageNumber!=NULL){
			oPageNumber->Set(id);
		}
	}
}

void	GeneralStackForm::SlotIDClicked(int id
				,bool EnableBroadcastLeavePage
				,bool EnableBroadcastStartPage
				,bool EnableBroadcastTabChanged)
{
	if(LastID>=0){
		if(EnableBroadcastLeavePage==true){
			GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(LastID);
			w->BroadcastLeavePage();
		}
	}

	MainTab.setCurrentIndex(id);
	
	for(int i=0;i<MainTab.count();i++){
		GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(i);
		if(i==id){
			w->BroadcastSetViewingOnChildrenWithMe(true);
			if(EnableBroadcastStartPage==true){
				w->BroadcastStartPage();
			}
			w->SetKeyGrab(true);
		}
		else{
			w->BroadcastSetViewingOnChildrenWithMe(false);
			if(EnableBroadcastLeavePage==true){
				w->BroadcastLeavePage();
			}
			w->SetKeyGrab(false);
		}
	}
	GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(id);
	if(EnableBroadcastStartPage==true){
		w->BroadcastStartPage();
	}
	if(EnableBroadcastTabChanged==true){
		BroadcastTabChanged();
	}
	LastID=id;
	if(oPageNumber!=NULL){
		oPageNumber->Set(id);
	}
}

void	GeneralStackForm::showEvent(QShowEvent * event )
{
	for(int i=0;i<MainTab.count();i++){
		GeneralStackPage	*w=(GeneralStackPage *)MainTab.widget(i);
	}
}

void	GeneralStackForm::CommandShowPage(const QString &PageName)
{
	for(int i=0;i<Msgs.count();i++){
		if(Msgs[i]==PageName){
			SlotIDClicked(i);
			break;
		}
	}
}

void	GeneralStackForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowPage	*CmdShowPageVar=dynamic_cast<CmdShowPage *>(packet);
	if(CmdShowPageVar!=NULL){
		if(CmdShowPageVar->ID>=0){
			SlotIDClicked(CmdShowPageVar->ID);
		}
		else if(CmdShowPageVar->PageName.isEmpty()==false){
			for(int i=0;i<Msgs.count();i++){
				QString	S=Msgs.value(i);
				if(CmdShowPageVar->PageName==S){
					SlotIDClicked(i);
					break;
				}
			}
		}
		return;
	}
	CmdGetShowPage	*CmdGetShowPageVar=dynamic_cast<CmdGetShowPage *>(packet);
	if(CmdGetShowPageVar!=NULL){
		int	index=MainTab.currentIndex();
		CmdGetShowPageVar->ID=index;
		CmdGetShowPageVar->PageName=Msgs[index];
		return;
	}
	CmdShowPageCommand	*CmdShowPageCommandVar=dynamic_cast<CmdShowPageCommand *>(packet);
	if(CmdShowPageCommandVar!=NULL){
		if(CmdShowPageCommandVar->ID>=0){
			SlotIDClicked(CmdShowPageCommandVar->ID
				,CmdShowPageCommandVar->EnableBroadcastLeavePage
				,CmdShowPageCommandVar->EnableBroadcastStartPage
				,CmdShowPageCommandVar->EnableBroadcastTabChanged);
		}
		else if(CmdShowPageCommandVar->PageName.isEmpty()==false){
			for(int i=0;i<Msgs.count();i++){
				QString	S=Msgs.value(i);
				if(CmdShowPageCommandVar->PageName==S){
					SlotIDClicked(i				
						,CmdShowPageCommandVar->EnableBroadcastLeavePage
						,CmdShowPageCommandVar->EnableBroadcastStartPage
						,CmdShowPageCommandVar->EnableBroadcastTabChanged);
					break;
				}
			}
		}
	}
}
void	GeneralStackForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	OpenTabPageSpecifiedBroadcaster	*OpenTabPageSpecifiedBroadcasterVar=dynamic_cast<OpenTabPageSpecifiedBroadcaster *>(v);
	if(OpenTabPageSpecifiedBroadcasterVar!=NULL){
		CommandShowPage(OpenTabPageSpecifiedBroadcasterVar->TabPageName);
		return;
	}
}
void	GeneralStackForm::SwapTab(QWidget *TabStack ,int index1 ,int index2)
{
	if(index1<index2)
		swap(index1,index2);
	QWidget *w=MainTab.widget(index1);
	MainTab.removeWidget(w);
	MainTab.insertWidget(index2,w);

	Swap(Msgs,index1,index2);
}
QWidgetList	GeneralStackForm::GetTabChildren(void)
{
	QWidgetList	ret;
	ret.append(&MainTab);
	return ret;
}
void	GeneralStackForm::RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)
{
	for(int i=0;i<MainTab.count();i++){
		QWidget	*w=MainTab.widget(i);
		if(w==RemovedPage){
			Msgs.removeAt(i);
			delete	w;
		}
	}
	GUIFormBase::RemovedTabSheet(TabRoot ,RemovedPage);
}

void	GeneralStackForm::RxSync(QByteArray &f)
{
	int	*p=(int*)f.data();
	int	PushedID=*p;

	SlotIDClicked(PushedID);
	FromSync	=false;
}
void	GeneralStackForm::OperandChanged()
{
	int	Page=oPageNumber->Get();
	SlotIDClicked(Page);
}

GUICmdChangeTab::GUICmdChangeTab(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeTab::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,TabName)==false)
		return false;
	return true;
}
bool	GUICmdChangeTab::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,TabName)==false)
		return false;
	return true;
}
void	GUICmdChangeTab::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,TabName);
	if(f!=NULL){
		GeneralStackForm	*G=dynamic_cast<GeneralStackForm *>(f);
		if(G!=NULL){
			G->SlotIDClicked(ID);
		}
	}
}

