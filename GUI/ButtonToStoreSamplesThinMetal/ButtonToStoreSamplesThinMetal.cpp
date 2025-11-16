#include "ButtonToStoreSamplesThinMetalResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AdjustMoveAllAfterLoadMaster\AdjustMoveAllAfterLoadMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonToStoreSamplesThinMetal.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XDistinguishPixCommon.h"
#include "XThinMetal.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"StoreSamplesThinMetal";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Store Samples on ThinMetal");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdStoreSamplesThinMetal		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdStoreSamplesThinMetalStart	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdStoreSamplesThinMetalEnd	(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonToStoreSamplesThinMetal(Base,parent));
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
	Data[0].Pointer				 =&((ButtonToStoreSamplesThinMetal *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonToStoreSamplesThinMetal *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonToStoreSamplesThinMetal *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonToStoreSamplesThinMetal *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"Additional";
	Data[4].Pointer				 =&((ButtonToStoreSamplesThinMetal *)Instance)->Additional;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToStoreSamplesThinMetal.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonToStoreSamplesThinMetal::ButtonToStoreSamplesThinMetal(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	setObjectName(QString::fromUtf8(/**/"ButtonToStoreSamplesThinMetalObj"));
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Store all Judgements in ThinMetal";
	Button.setObjectName(/**/"AdjustMoveAllAfterLoadMaster");
	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	Additional	=false;
}

ButtonToStoreSamplesThinMetal::~ButtonToStoreSamplesThinMetal(void)
{
}

void	ButtonToStoreSamplesThinMetal::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonToStoreSamplesThinMetal::ResizeAction()
{
	Button.resize(width(),height());
}


void ButtonToStoreSamplesThinMetal::SlotClicked (bool checked)
{
	FileListContainer		*FileData=NULL;
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"List",/**/"DistinguishPix",/**/"");
	if(f!=NULL){
		CmdReqFileListContainer	Cmd(GetLayersBase());
		f->TransmitDirectly(&Cmd);
		FileData=Cmd.Container;
	}

	if(Additional==false){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdStoreSamplesThinMetalStart	Requester(GetLayersBase(),sRoot,sName);
			Requester.Send(NULL,GlobalPage,0);
		}
	}
	if(FileData!=NULL){
		for(FileListLeaf *a=FileData->GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Judgement==0)
				continue;
			if(f!=NULL){
				CmdReqLoadImageIntoTarget	Cmd(GetLayersBase());
				Cmd.Pointer	=a;
				f->TransmitDirectly(&Cmd);
				if(Cmd.Success==false)
					continue;
			}
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdStoreSamplesThinMetal	Requester(GetLayersBase(),sRoot,sName);
				Requester.Judgement	=a->Judgement;
				Requester.JudgeStr	=a->JudgeStr;
				Requester.TargetFolder	=a->UFolderName;
				Requester.TargetFileName=a->FileName;
				Requester.Send(NULL,GlobalPage,0);
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdStoreSamplesThinMetalEnd	Requester(GetLayersBase(),sRoot,sName);
			Requester.Send(NULL,GlobalPage,0);
		}
	}
}


void	ButtonToStoreSamplesThinMetal::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(111,/**/"Execute"
											,LangSolver.GetString(ButtonToStoreSamplesThinMetal_LS,LID_0)/*"Store all judgements"*/
											,this);
	p->SetMenuNumber(111);
	Info.AppendList(p);
}
void	ButtonToStoreSamplesThinMetal::ExecuteMenu(int ID)
{
	if(ID==111){
		SlotClicked(true);
	}
}


//==============================================================================================

GUICmdStoreSamplesThinMetal::GUICmdStoreSamplesThinMetal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{	
}
bool	GUICmdStoreSamplesThinMetal::Load(QIODevice *f)
{
	if(::Load(f,Judgement)==false)
		return false;
	if(::Load(f,JudgeStr)==false)
		return false;
	if(::Load(f,TargetFolder)==false)
		return false;
	if(::Load(f,TargetFileName)==false)
		return false;
	return true;
}
bool	GUICmdStoreSamplesThinMetal::Save(QIODevice *f)
{
	if(::Save(f,Judgement)==false)
		return false;
	if(::Save(f,JudgeStr)==false)
		return false;
	if(::Save(f,TargetFolder)==false)
		return false;
	if(::Save(f,TargetFileName)==false)
		return false;
	return true;
}

void	GUICmdStoreSamplesThinMetal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(PBase==NULL)
		return;

	ThinMetalInPage	*PPage=dynamic_cast<ThinMetalInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqStoreThinMetal	RCmd(GetLayersBase());
		RCmd.Judgement		=Judgement;
		RCmd.JudgeStr		=JudgeStr;
		RCmd.TargetFolder	=TargetFolder;
		RCmd.TargetFileName	=TargetFileName;
		PPage->TransmitDirectly(&RCmd);
	}
}

	
GUICmdStoreSamplesThinMetalStart::GUICmdStoreSamplesThinMetalStart(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{	
}

void	GUICmdStoreSamplesThinMetalStart::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(PBase==NULL)
		return;

	ThinMetalInPage	*PPage=dynamic_cast<ThinMetalInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqStoreThinMetalStart	RCmd(GetLayersBase());
		PPage->TransmitDirectly(&RCmd);
	}
}

	
GUICmdStoreSamplesThinMetalEnd::GUICmdStoreSamplesThinMetalEnd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{	
}

void	GUICmdStoreSamplesThinMetalEnd::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
	if(PBase==NULL)
		return;

	ThinMetalInPage	*PPage=dynamic_cast<ThinMetalInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqStoreThinMetalEnd	RCmd(GetLayersBase());
		PPage->TransmitDirectly(&RCmd);
	}
}
