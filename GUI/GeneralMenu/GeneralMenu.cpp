#include "GeneralMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralMenu\GeneralMenu.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralMenu.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XGUI.h"
#include <QMessageBox>

static	const char	*sRoot=/**/"General";
static	const char	*sName=/**/"GeneralMenu";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Add General menu");
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
	return(new GeneralMenu(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralMenu.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GeneralMenu::GeneralMenu(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	//GUIFormBase	*MainForm=GetTopParent();
	//QWidget	*MainForm=parentWidget();
	MenuBar.setParent(this);
	resize(100,18);
}
void	GeneralMenu::Prepare(void)
{
	MenuBar.setGeometry(0,0,width()-4,18);
	SetEnabledBroadcast(true);
}
GeneralMenu::~GeneralMenu(void)
{
}

void	GeneralMenu::BuildForShow(void)
{
	TabChanged();
}

static	int	SortMenuPointer(const void *a ,const void *b)
{
	MenuInfoList	*ta=*((MenuInfoList **)a);
	MenuInfoList	*tb=*((MenuInfoList **)b);
	int	ret=ta->GetMenuNumber() - tb->GetMenuNumber();
	if(ret!=0){
		return ret;
	}
	int	N=ta->ID - tb->ID;
	return N;
}

void	GeneralMenu::TabChanged(void)
{
	if(GetEditMode()==false){
		setFrameShape(QFrame::NoFrame);
	}

	MenuBar.clear();
	AllMenus.RemoveAll();

	GUIInstancePack		*GUIPack=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack();
	for(GUIItemInstance *f=GUIPack->NPListPack<GUIItemInstance>::GetFirst();f!=NULL;f=f->GetNext()){
		MenuInfoContainer *MenuInfo=new MenuInfoContainer;
		f->GetForm()->GetMenuInfo(*MenuInfo);
		if(f->GetForm()->GetViewing()==false){
			for(MenuInfoList *d=MenuInfo->NPListPack<MenuInfoList>::GetFirst();d!=NULL;){
				if(d->ShowingAttribute==MenuInfoList::_Constant){
					d=d->GetNext();
				}
				else{
					MenuInfoList *DNext=d->GetNext();
					MenuInfo->NPListPack<MenuInfoList>::RemoveList(d);
					delete	d;
					d=DNext;
				}
			}
		}
		if(MenuInfo->NPListPack<MenuInfoList>::GetCount()!=0){
			AllMenus.AppendList(MenuInfo);
		}
		else{
			delete	MenuInfo;
		}
	}
	QStringList	__MenuItems;
	for(MenuInfoContainer *c=AllMenus.GetFirst();c!=NULL;c=c->GetNext()){
		for(MenuInfoList *d=c->NPListPack<MenuInfoList>::GetFirst();d!=NULL;d=d->GetNext()){
			int	i;
			for(i=0;i<__MenuItems.count();i++){
				if(__MenuItems[i]==d->MenuPath){
					break;
				}
			}
			if(i>=__MenuItems.count()){
				__MenuItems.append(d->MenuPath);
			}
		}
	}

	QStringList	MenuItems;
	for(int i=0;i<__MenuItems.count();i++){
		if(__MenuItems[i].toLower()==/**/"file"){
			MenuItems.append(__MenuItems[i]);
			__MenuItems.removeAt(i);
			break;
		}
	}
	for(int i=0;i<__MenuItems.count();i++){
		if(__MenuItems[i].toLower()==/**/"edit"){
			MenuItems.append(__MenuItems[i]);
			__MenuItems.removeAt(i);
			break;
		}
	}
	while(__MenuItems.count()>0){
		QString	TopItem=__MenuItems[0];
		int	Index=0;
		for(int i=1;i<__MenuItems.count();i++){
			if(__MenuItems[i]<TopItem){
				TopItem=__MenuItems[i];
				Index=i;
			}
		}
		MenuItems.append(TopItem);
		__MenuItems.removeAt(Index);
	}

	for(int i=0;i<MenuItems.count();i++){
		QMenu	*m=MenuBar.addMenu(MenuItems[i]);
		MenuInfoList *MenuPointer[1000];
		int			MenuCount=0;
		for(MenuInfoContainer *c=AllMenus.GetFirst();c!=NULL;c=c->GetNext()){
			for(MenuInfoList *d=c->NPListPack<MenuInfoList>::GetFirst();d!=NULL;d=d->GetNext()){
				if(MenuItems[i]==d->MenuPath){
					MenuPointer[MenuCount]=d;
					MenuCount++;
				}
			}
		}
		QSort(MenuPointer,MenuCount,sizeof(MenuPointer[0]),SortMenuPointer);

		QString	LastRoot;
		QString	CurrentRoot;
		QString	LastName;
		QString	CurrentName;
		QString	LastMenuTitle;
		int	LastID=-1;
		for(int j=0;j<MenuCount;j++){
			if(j>1){
				CurrentRoot=MenuPointer[j]->Base->GetDLLRoot();
				CurrentName=MenuPointer[j]->Base->GetDLLName();
				if(CurrentRoot==LastRoot && CurrentName==LastName){
					if(LastID==MenuPointer[j]->ID){
						continue;
					}
				}
				LastRoot=CurrentRoot;
				LastName=CurrentName;
				LastID	=MenuPointer[j]->ID;
			}
			if(LastMenuTitle==MenuPointer[j]->MenuTitle && MenuPointer[j]->CancelDuplication==true){
				continue;
			}
			LastMenuTitle=MenuPointer[j]->MenuTitle;
			MenuPointer[j]->AddMenu(m);
		}
	}
}

void	GeneralMenu::StartPage	(void)
{
	TabChanged();
}