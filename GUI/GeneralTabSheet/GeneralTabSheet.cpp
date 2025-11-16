#include "GeneralTabSheetResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabSheet\GeneralTabSheet.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralTabSheet.h"
#include "swap.h"

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"TabSheet";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General TabSheet");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralTabSheet(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"Msgs";
	Data[0].Pointer				 =&((GeneralTabSheet *)Instance)->Msgs;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"North,West,East,South";
	Data[1].VariableNameWithRoute=/**/"TabPosition";
	Data[1].Pointer				 =&((GeneralTabSheet *)Instance)->TabPosition;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"StartTop";
	Data[2].Pointer				 =&((GeneralTabSheet *)Instance)->StartTop;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"Font";
	Data[3].Pointer				 =&((GeneralTabSheet *)Instance)->Font;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralTabSheet.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================


GeneralTabPage::GeneralTabPage(LayersBase *Base ,GeneralTabSheet *p,QWidget *parent)
:GUIFormBase(Base,parent)
,Parent(p)
{
	SetKeyGrab(false);
}
GeneralTabPage::~GeneralTabPage(void)
{
}
void	GeneralTabPage::Prepare(void)
{
}
void	GeneralTabPage::ResizeAction(void)
{
}
bool	GeneralTabPage::IsShown(void)
{
	if(Parent->GetTopTabWizardPage()==this){
		return Parent->IsShown();
	}
	return false;
}
/*
void	GeneralTabPage::keyPressEvent ( QKeyEvent * event )
{
	QObjectList Q=children();

	for(int i=0;i<Q.count();i++){
		GUIFormBase *C=dynamic_cast<GUIFormBase *>(Q[i]);
		if(C==NULL)
			continue;
		C->keyPressEvent (event);
	}
}
*/

GeneralTabSheet::GeneralTabSheet(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	TabPosition=/**/"North";
	StartTop	=-1;
	Msgs.append(QString(/**/"Default"));
	Msgs.append(QString(/**/"Page1"));
	resize(400,400);
	MainTab.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

GeneralTabSheet::~GeneralTabSheet(void)
{
	while(Msgs.count()<MainTab.count()){
		MainTab.removeTab(Msgs.count());
	}
}

void	GeneralTabSheet::Prepare(void)
{
	for(int i=0;i<Msgs.count();i++){
		if(MainTab.count()>i){
			MainTab.setTabText(i,Msgs.value(i));
		}
		else{
			GeneralTabPage	*p=new GeneralTabPage(GetLayersBase(),this,NULL);
			p->SetComment(Msgs.value(i));
			MainTab.addTab(p,Msgs.value(i));
		}
	}
	while(Msgs.count()<MainTab.count()){
		MainTab.removeTab(Msgs.count());
	}
	connect(&MainTab,SIGNAL(currentChanged(int)),this,SLOT(TabCurrentChanged(int)));

	if(TabPosition==/**/"North")
		MainTab.setTabPosition(QTabWidget::North);
	else if(TabPosition==/**/"South")
		MainTab.setTabPosition(QTabWidget::South);
	else if(TabPosition==/**/"East")
		MainTab.setTabPosition(QTabWidget::East);
	else if(TabPosition==/**/"West")
		MainTab.setTabPosition(QTabWidget::West);

	if(0<=StartTop && StartTop<MainTab.count())
		MainTab.setCurrentIndex(StartTop);

	setFont(Font);

	ResizeAction();
}
GUIFormBase	*GeneralTabSheet::GetTopTabWizardPage(void)
{
	QWidget	*w=MainTab.currentWidget();
	GeneralTabPage	*W=dynamic_cast<GeneralTabPage *>(w);
	if(W!=NULL){
		return W;
	}
	return NULL;
}

int	GeneralTabSheet::GetChildCount()
{
	return MainTab.count();
}
GUIFormBase	*GeneralTabSheet::GetChild(int index)	const
{
	return dynamic_cast<GUIFormBase*>(MainTab.widget(index));
}

GUIFormBase	*GeneralTabSheet::GetTopSurfaceWidget(int x ,int y)
{
	return dynamic_cast<GUIFormBase*>(MainTab.currentWidget());
}


void	GeneralTabSheet::ResizeAction()
{
	MainTab.resize(width(),height());
}

/*
void	GeneralTabSheet::keyPressEvent ( QKeyEvent * event )
{
	QObjectList Q=children();

	for(int i=0;i<Q.count();i++){
		GUIFormBase *C=dynamic_cast<GUIFormBase *>(Q[i]);
		if(C==NULL)
			continue;
		C->keyPressEvent (event);
	}
}
*/
void	GeneralTabSheet::SwapTab(QWidget *TabStack ,int index1 ,int index2)
{
	if(index1<index2)
		swap(index1,index2);
	QWidget *w=MainTab.widget(index1);
	QString tabstring=MainTab.tabText(index1);
	MainTab.removeTab(index1);
	MainTab.insertTab(index2,w,tabstring);
}

void	GeneralTabSheet::TabCurrentChanged( int index )
{
	GeneralTabPage	*p=dynamic_cast<GeneralTabPage	*>(MainTab.widget(index));
	if(p!=NULL){
		p->BroadcastChildrenAndOwnDirectly(GUIFormBase::_BC_StartPage,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
	showEvent(NULL);
}

void	GeneralTabSheet::showEvent(QShowEvent * event )
{
	for(int i=0;i<MainTab.count();i++){
		GeneralTabPage	*w=(GeneralTabPage *)MainTab.widget(i);
		if(MainTab.currentIndex()==i){
			w->BroadcastSetViewingOnChildrenWithMe(true);
		}
		else{
			w->BroadcastSetViewingOnChildrenWithMe(false);
		}
	}
}

QWidgetList	GeneralTabSheet::GetTabChildren(void)
{
	QWidgetList	ret;
	ret.append(&MainTab);
	return ret;
}
void	GeneralTabSheet::RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)
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
void	GeneralTabSheet::CommandShowPage(const QString &PageName)
{
	for(int i=0;i<Msgs.count();i++){
		if(Msgs[i]==PageName){
			MainTab.setCurrentIndex(i);
			break;
		}
	}
}
void	GeneralTabSheet::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	OpenTabPageSpecifiedBroadcaster	*OpenTabPageSpecifiedBroadcasterVar=dynamic_cast<OpenTabPageSpecifiedBroadcaster *>(v);
	if(OpenTabPageSpecifiedBroadcasterVar!=NULL){
		CommandShowPage(OpenTabPageSpecifiedBroadcasterVar->TabPageName);
		return;
	}
}