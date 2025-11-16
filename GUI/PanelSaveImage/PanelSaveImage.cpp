#include "PanelSaveImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelSaveImage\PanelSaveImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelSaveImage.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralFunc.h"
#include "XAutoSaveImage.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"PanelSaveImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel saving image");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PanelSaveImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeCurrentFolder			(Base,QString(sRoot),QString(sName));

	//new GUICmdReqOkNG	(Base,sRoot,sName);
	//new GUICmdSendOkNG	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"MessageSize";
	Data[0].Pointer				 =&((PanelSaveImage *)Instance)->MessageSize;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelSaveImage.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoSaveImage"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
PanelSaveImage::PanelSaveImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(250,250);
	MainList.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&MainList,SIGNAL(itemDoubleClicked (QListWidgetItem *)), this ,SLOT(itemDoubleClicked (QListWidgetItem *)));
}

void	PanelSaveImage::Prepare(void)
{
	MainList.setFont(MessageSize);
}

void	PanelSaveImage::BuildForShow(void)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoSaveImage");
	if(PBase==NULL)
		return;

	CmdReqFolderList	Cmd(GetLayersBase());
	PBase->TransmitDirectly(&Cmd);
	MainList.clear();
	MainList.addItems(Cmd.FolderList);
}

void	PanelSaveImage::ShowInEdit(void)
{
	//repaint();
}
void	PanelSaveImage::ResizeAction()
{
	MainList.resize(width(),height());
}

void PanelSaveImage::itemDoubleClicked ( QListWidgetItem * item )
{
	int	R=MainList.currentRow();
	if(R<0)
		return;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdChangeCurrentFolder	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.FolderNumber=R;
		RCmd.Send(NULL,GlobalPage,0);
	}
}

//==================================================================================================
GUICmdChangeCurrentFolder::GUICmdChangeCurrentFolder(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FolderNumber=-1;
}

bool	GUICmdChangeCurrentFolder::Load(QIODevice *f)
{
	if(::Load(f,FolderNumber)==false)
		return false;
	return true;
}

bool	GUICmdChangeCurrentFolder::Save(QIODevice *f)
{
	if(::Save(f,FolderNumber)==false)
		return false;
	return true;
}

void	GUICmdChangeCurrentFolder::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoSaveImage");
	if(PBase==NULL)
		return;
	CmdSetFolderNumber	Cmd(GetLayersBase());
	Cmd.FolderNumber=FolderNumber;
	PBase->TransmitDirectly(&Cmd);
	SendAck(localPage);
}