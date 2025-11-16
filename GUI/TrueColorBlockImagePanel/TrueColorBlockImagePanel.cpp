#include "TrueColorBlockImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TrueColorBlockImagePanel\TrueColorBlockImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TrueColorBlockImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XTrueColorBlock.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"TrueColorBlockImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"TrueColorBlockImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdPickupTestList(Base,QString(sRoot),QString(sName));

	//new GUICmdReqBlockBmp(QString(sRoot),QString(sName));
	//new GUICmdSendBlockBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddBlock(QString(sRoot),QString(sName));

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
	TrueColorBlockImagePanel	*B=new TrueColorBlockImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((TrueColorBlockImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((TrueColorBlockImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/TrueColorBlockImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"TrueColorBlock"));
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

TrueColorBlockImagePanel::TrueColorBlockImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"TrueColorBlock",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	TrueColorBlockImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	TrueColorBlockImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	TrueColorBlockImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	__DrawingMode	DMode=GetImageDrawingMode();
	DisplayImageWithAlgorithm::SlotMouseLDown(globalX,globalY);
	if(GetLastHookResult()==false)
		return;
	if(DMode!=_ItemMove){
		IntList PageList;
		GetLayersBase()->GetGlobalPage(globalX,globalY,globalX,globalY,PageList);
		if(PageList.GetCount()>1){
			SelectPages	D(GetLayersBase(),PageList,0);
			if(D.exec()==(int)true){
				PageList=D.SelectedPages;
			}
		}
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyTrueColorBlockForm" ,/**/"");
		if(GProp!=NULL){
			CmdExecuteMouseLDown	Da(GetLayersBase());
			Da.CurrentItem=CurrentItem;
			Da.PageList=PageList;
			GProp->TransmitDirectly(&Da);
		}
	}
}

AlgorithmDrawAttr	*TrueColorBlockImagePanel::CreateDrawAttrPointer(void)
{
	TrueColorBlockBase	*Base=(TrueColorBlockBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new TrueColorBlockDrawAttr(GetLayersBase()
								,Base->TrueColorBlockNormal		,100
								,Base->TrueColorBlockSelected	,100
								,Base->TrueColorBlockActive		,100
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

void	TrueColorBlockImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyTrueColorBlockForm" ,/**/"");
	if(GProp!=NULL){
		CmdTrueColorBlockDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	TrueColorBlockImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyTrueColorBlockForm" ,"");
	if(GProp!=NULL){
		CmdExecuteMouseRDownWithShift	Da;
		GProp->TransmitDirectly(&Da);
	}
}
*/
	CmdTrueColorBlockDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyTrueColorBlockForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
		if(Da.Mode==CmdTrueColorBlockDrawModePacket::_CreatedBlock){

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
				ShowAndSetItemsTrueColor	ShowAndSetItemsTrueColorData;
				ShowAndSetItemsTrueColorData.Form=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"TrueColorBlockImagePanel" ,/**/"");
				L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,&ShowAndSetItemsTrueColorData);
			}
		}
	}
}

void	TrueColorBlockImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}


//=======================================================================
GUICmdReqTrueColorBlockInfo::GUICmdReqTrueColorBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqTrueColorBlockInfo::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdReqTrueColorBlockInfo::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdReqTrueColorBlockInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendTrueColorBlockInfo	*SendBack=GetSendBack(GUICmdSendTrueColorBlockInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage,LocalX, LocalY ,*GetLayersBase());
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendTrueColorBlockInfo::GUICmdSendTrueColorBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendTrueColorBlockInfo::Load(QIODevice *f)
{
	if(LibIDList.Load(f)==false)
		return false;
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdSendTrueColorBlockInfo::Save(QIODevice *f)
{
	if(LibIDList.Save(f)==false)
		return false;
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdSendTrueColorBlockInfo::MakeData(int localPage, int localX, int localY ,LayersBase	&LocalLBase)
{
	AlgorithmBase	*AL=LocalLBase.GetAlgorithmBase(/**/"Basic" ,/**/"TrueColorBlock");
	if(AL==NULL)
		return;
	TrueColorBlockBase	*BL=dynamic_cast<TrueColorBlockBase *>(AL);
	if(BL==NULL)
		return;
	LocalX=localX;
	LocalY=localY;

	TrueColorBlockInPage	*CP=(TrueColorBlockInPage *)BL->GetPageData(localPage);
	if(CP==NULL)
		return;

	CmdFindTrueColorBlockItem	RCmd(GetLayersBase());
	RCmd.LocalX=localX;
	RCmd.LocalY=localY;
	CP->TransmitDirectly(&RCmd);
	AlgorithmItemPI	*Item=RCmd.TrueColorBlock;
	if(Item!=NULL){
		TrueColorBlockItem	*BItem=(TrueColorBlockItem *)Item;
		LibIDList.Add(BItem->GetLibID());
	}
}

void	GUICmdSendTrueColorBlockInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

