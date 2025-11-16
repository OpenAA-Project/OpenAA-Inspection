#include "StatisticBlockImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StatisticBlockImagePanel\StatisticBlockImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "StatisticBlockImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XStatisticBlock.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"StatisticBlockImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Statistic Block ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqBlockBmp(QString(sRoot),QString(sName));
	//new GUICmdSendBlockBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddBlock(QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSelectedItemCount	(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount	(Base ,QString(sRoot) ,QString(sName));

	(*Base)=new GUICmdReqItemIndependentPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendIndependentPack		(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	StatisticBlockImagePanel	*B=new StatisticBlockImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((StatisticBlockImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((StatisticBlockImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StatisticBlockImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticBlock"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

StatisticBlockImagePanel::StatisticBlockImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"StatisticBlock",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	StatisticBlockImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	StatisticBlockImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	StatisticBlockImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	DisplayImageWithAlgorithm::SlotMouseLDown(globalX,globalY);
	if(GetLastHookResult()==false)
		return;
	IntList PageList;
	GetLayersBase()->GetGlobalPage(globalX,globalY,globalX,globalY,PageList);
	if(PageList.GetCount()>1){
		SelectPages	D(GetLayersBase(),PageList,0);
		if(D.exec()==(int)true){
			PageList=D.SelectedPages;
		}
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyStatisticBlockForm" ,/**/"");
	if(GProp!=NULL){
		CmdExecuteMouseLDown	Da(GetLayersBase());
		Da.CurrentItem=CurrentItem;
		Da.PageList=PageList;
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*StatisticBlockImagePanel::CreateDrawAttrPointer(void)
{
	StatisticBlockBase	*Base=(StatisticBlockBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new StatisticBlockDrawAttr(GetLayersBase()
								,Base->ColorBlockNormal		,100
								,Base->ColorBlockSelected	,100
								,Base->ColorBlockActive		,100
								,Base->ColorPickup			,80
								,Base->BlockColor0
								,Base->BlockColor1
								,Base->BlockColor2
								,Base->BlockColor3
								,Base->BlockColor4
								,Base->BlockColor5
								,Base->BlockColor6
								,Base->BlockColor7);
	}
	return NULL;
}

void	StatisticBlockImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyStatisticBlockForm" ,/**/"");
	if(GProp!=NULL){
		CmdStatisticBlockDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	StatisticBlockImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyBlockForm" ,"");
	if(GProp!=NULL){
		CmdExecuteMouseRDownWithShift	Da;
		GetActiveLayerList(Da.LayerList);
		GProp->TransmitDirectly(&Da);
	}
}

void	BlockImagePanel::SlotMouseLDownWithShift(int globalX,int globalY)
{
	*/
	CmdStatisticBlockDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyStatisticBlockForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
		if(Da.Mode==CmdStatisticBlockDrawModePacket::_CreatedBlock){

			DataInPage *P=GetLayersBase()->GetPageDataByPoint(globalX ,globalY);
			if(P==NULL)
				return;
			GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.TargetPhase=ShowFixedPhase;
			P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
			GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,RecPacket);
			if(RecPacket.IsReceived()==true){
				LogicDLL	*L=GetAlgorithmBase()->GetLogicDLL();
				L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,NULL);
			}
		}
	}
}
void	StatisticBlockImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================
GUICmdReqStatisticBlockInfo::GUICmdReqStatisticBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqStatisticBlockInfo::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdReqStatisticBlockInfo::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdReqStatisticBlockInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendStatisticBlockInfo	*SendBack=GetSendBack(GUICmdSendStatisticBlockInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage,LocalX, LocalY ,*GetLayersBase());
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendStatisticBlockInfo::GUICmdSendStatisticBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendStatisticBlockInfo::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false)
		return false;
	if(LibIDList.Load(f)==false)
		return false;
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdSendStatisticBlockInfo::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false)
		return false;
	if(LibIDList.Save(f)==false)
		return false;
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdSendStatisticBlockInfo::MakeData(int localPage, int localX, int localY ,LayersBase	&LocalLBase)
{
	AlgorithmBase	*AL=LocalLBase.GetAlgorithmBase(/**/"Basic" ,/**/"StatisticBlock");
	if(AL==NULL)
		return;
	StatisticBlockBase	*BL=dynamic_cast<StatisticBlockBase *>(AL);
	if(BL==NULL)
		return;
	LocalX=localX;
	LocalY=localY;

	StatisticBlockInPage	*P=(StatisticBlockInPage *)BL->GetPageData(localPage);
	for(int L=0;L<P->GetLayerNumb();L++){
		AlgorithmInLayerPLI	*AinL=P->GetLayerDataPLI(L);
		AlgorithmItemPLI	*Item=AinL->GetItem(localX,localY);
		if(Item!=NULL){
			StatisticBlockItem	*BItem=(StatisticBlockItem *)Item;
			LibIDList.Add(BItem->GetLibID());
			LayerList.Add(L);
		}
	}
}

void	GUICmdSendStatisticBlockInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

