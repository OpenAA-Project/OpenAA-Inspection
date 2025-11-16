#include "AdjustMoveAllAfterLoadMasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AdjustMoveAllAfterLoadMaster\AdjustMoveAllAfterLoadMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AdjustMoveAllAfterLoadMaster.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "ListOfAdjustMoveAll.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"AdjustMoveAllAfterLoadMaster";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Adjust MoveAll XY after Loading master data");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdMoveAll(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AdjustMoveAllAfterLoadMaster(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((AdjustMoveAllAfterLoadMaster *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((AdjustMoveAllAfterLoadMaster *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((AdjustMoveAllAfterLoadMaster *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((AdjustMoveAllAfterLoadMaster *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"SavedFileName";
	Data[4].Pointer				 =&((AdjustMoveAllAfterLoadMaster *)Instance)->SavedFileName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AdjustMoveAllAfterLoadMaster.png")));
}

//==================================================================================================
AdjustMoveAllAfterLoadMaster::AdjustMoveAllAfterLoadMaster(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	setObjectName(QString::fromUtf8(/**/"AdjustMoveAllAfterLoadMasterObj"));
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Adjust MoveAll after LoadMaster";
	Button.setObjectName(/**/"AdjustMoveAllAfterLoadMaster");
	resize(60,25);
	SavedFileName=/**/"AdjustMoveAllAfterLoadMaster.dat";
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

AdjustMoveAllAfterLoadMaster::~AdjustMoveAllAfterLoadMaster(void)
{
}

void	AdjustMoveAllAfterLoadMaster::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	LoadFile();
}

void	AdjustMoveAllAfterLoadMaster::ResizeAction()
{
	Button.resize(width(),height());
}

bool	AdjustMoveAllAfterLoadMaster::LoadFile(void)
{
	QDir	dir;
	if(dir.cd(GetLayersBase()->GetUserPath())==true){
		QFile	file(SavedFileName);
		if(file.open(QIODevice::ReadOnly)==true){
			if(MoveXY.Load(&file)==false){
				return false;
			}
			MoveXY.SetPageCount(GetLayersBase()->GetPageNumb());
			return true;
		}
	}
	return false;
}
bool	AdjustMoveAllAfterLoadMaster::SaveFile(void)
{
	QDir	dir;
	if(dir.cd(GetLayersBase()->GetUserPath())==true){
		QFile	file(SavedFileName);
		if(file.open(QIODevice::WriteOnly)==true){
			if(MoveXY.Save(&file)==false){
				return false;
			}
			return true;
		}
	}
	return false;
}
void AdjustMoveAllAfterLoadMaster::SlotClicked (bool checked)
{
	ListOfAdjustMoveAll	D(this);
	D.exec();
}


void	AdjustMoveAllAfterLoadMaster::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(111
										,/**/"File"
										,LangSolver.GetString(AdjustMoveAllAfterLoadMaster_LS,LID_0)/*"Set to Move all after loading MasterData"*/
										,this);
	p->SetMenuNumber(111);
	Info.AppendList(p);
}
void	AdjustMoveAllAfterLoadMaster::ExecuteMenu(int ID)
{
	if(ID==111){
		SlotClicked(true);
	}
}

void	AdjustMoveAllAfterLoadMaster::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		LoadFile();
		MoveAllInMaster	*D=MoveXY.FindMasterData(GetLayersBase()->GetMasterCode());
		if(D!=NULL){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdMoveAll	PushRequester(GetLayersBase(),sRoot,sName);
				PushRequester.MovX	=(*D)[page]->x;
				PushRequester.MovY	=(*D)[page]->y;
				PushRequester.MoveMasterImage	=true;
				PushRequester.MoveTargetImage	=false;
				PushRequester.ChangeChanged		=true;
				PushRequester.Send(NULL,GlobalPage,0);
			}
		}
		return;
	}
	CreateUpdateMasterPreSpecifiedBroadcaster	*CreateUpdateMasterPreSpecifiedBroadcasterVar=dynamic_cast<CreateUpdateMasterPreSpecifiedBroadcaster *>(v);
	if(CreateUpdateMasterPreSpecifiedBroadcasterVar!=NULL){
		LoadFile();
		MoveAllInMaster	*D=MoveXY.FindMasterData(GetLayersBase()->GetMasterCode());
		if(D!=NULL){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdMoveAll	PushRequester(GetLayersBase(),sRoot,sName);
				PushRequester.MovX	=-(*D)[page]->x;
				PushRequester.MovY	=-(*D)[page]->y;
				PushRequester.MoveMasterImage	=true;
				PushRequester.MoveTargetImage	=false;
				PushRequester.ChangeChanged		=false;
				PushRequester.Send(NULL,GlobalPage,0);
			}
		}
		return;
	}
	CreateUpdateMasterSpecifiedBroadcaster	*CreateUpdateMasterSpecifiedBroadcasterVar=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	if(CreateUpdateMasterSpecifiedBroadcasterVar!=NULL){
		LoadFile();
		MoveAllInMaster	*D=MoveXY.FindMasterData(GetLayersBase()->GetMasterCode());
		if(D!=NULL){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdMoveAll	PushRequester(GetLayersBase(),sRoot,sName);
				PushRequester.MovX	=(*D)[page]->x;
				PushRequester.MovY	=(*D)[page]->y;
				PushRequester.MoveMasterImage	=true;
				PushRequester.MoveTargetImage	=false;
				PushRequester.ChangeChanged		=true;
				PushRequester.Send(NULL,GlobalPage,0);
			}
		}
		return;
	}

}


//==============================================================================================

bool	MoveAllInMaster::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(XYClass *a=XYClassContainer::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}
bool	MoveAllInMaster::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		XYClass *a=new XYClass();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}
void	MoveAllInMaster::SetPageCount(int n)
{
	while(XYClassContainer::GetCount()>n){
		XYClass	*a=XYClassContainer::GetLast();
		RemoveList(a);
		delete	a;
	}
	while(XYClassContainer::GetCount()<n){
		XYClass	*a=new XYClass();
		XYClassContainer::AppendList(a);
	}
}


bool	MoveAllInfo::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(MoveAllInMaster *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	MoveAllInfo::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		MoveAllInMaster *a=new MoveAllInMaster();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

void	MoveAllInfo::SetPageCount(int n)
{
	for(MoveAllInMaster *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetPageCount(n);
	}
}

MoveAllInMaster	*MoveAllInfo::FindMasterData(int mastercode)
{
	for(MoveAllInMaster *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->MasterCode==mastercode){
			return a;
		}
	}
	for(MoveAllInMaster *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->MasterCode==-1){
			return a;
		}
	}
	return NULL;
}
//==============================================================================================

GUICmdMoveAll::GUICmdMoveAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	
}
bool	GUICmdMoveAll::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	if(::Load(f,MoveMasterImage)==false)
		return false;
	if(::Load(f,MoveTargetImage)==false)
		return false;
	if(::Load(f,ChangeChanged)==false)
		return false;
	return true;
}
bool	GUICmdMoveAll::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	if(::Save(f,MoveMasterImage)==false)
		return false;
	if(::Save(f,MoveTargetImage)==false)
		return false;
	if(::Save(f,ChangeChanged)==false)
		return false;
	return true;
}

void	GUICmdMoveAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	if(MovX!=0 || MovY!=0){
		for(int i=0;i<GetLayerNumb(localPage);i++){
			DataInLayer	*L=P->GetLayerData(i);
			if(MoveMasterImage==true){
				L->GetMasterBuff().MoveImage(MovX,MovY);
				if(ChangeChanged==true){
					L->GetMasterBuff().SetChanged(false);
				}
			}
			if(MoveTargetImage==true){
				L->GetTargetBuff().MoveImage(MovX,MovY);
				if(ChangeChanged==true){
					L->GetTargetBuff().SetChanged(false);
				}
			}
		}
		for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*ABase=L->GetInstance();
			AlgorithmInPageRoot	*APage=ABase->GetPageData(localPage);
			APage->ExecuteMove(MovX,MovY,true);
		}
	}
}
