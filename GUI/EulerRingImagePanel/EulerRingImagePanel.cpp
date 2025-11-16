#include "EulerRingImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EulerRingImagePanel\EulerRingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "EulerRingImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XEulerRing.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"EulerRingImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EulerRingImagePanel");
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
	EulerRingImagePanel	*B=new EulerRingImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EulerRingImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((EulerRingImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EulerRingImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"EulerRing"));
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

EulerRingImagePanel::EulerRingImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"EulerRing",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	EulerRingImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	EulerRingImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	EulerRingImagePanel::SlotMouseLDown(int globalX,int globalY)
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
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyEulerRing" ,/**/"");
	if(GProp!=NULL){
		CmdExecuteMouseLDown	Da(GetLayersBase());
		Da.CurrentItem=CurrentItem;
		Da.PageList=PageList;
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*EulerRingImagePanel::CreateDrawAttrPointer(void)
{
	EulerRingBase	*Base=(EulerRingBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new EulerRingDrawAttr(GetLayersBase()
								,Base->EulerRingNormal		,100
								,Base->EulerRingSelected	,100
								,Base->EulerRingActive		,100
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

void	EulerRingImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyEulerRing" ,/**/"");
	if(GProp!=NULL){
		CmdEulerRingDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	EulerRingImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyEulerRingForm" ,"");
	if(GProp!=NULL){
		CmdExecuteMouseRDownWithShift	Da;
		GProp->TransmitDirectly(&Da);
	}
}
*/
	CmdEulerRingDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyEulerRing" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
		if(Da.Mode==EulerRingDrawAttr::_CreatedBlock){

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
				ShowAndSetItemsEulerRing	ShowAndSetItemsEulerRingData;
				ShowAndSetItemsEulerRingData.Form=GetLayersBase()->FindByName(LangSolver.GetString(EulerRingImagePanel_LS,LID_0)/*"Inspection"*/ ,LangSolver.GetString(EulerRingImagePanel_LS,LID_1)/*"EulerRingImagePanel"*/ ,/**/"");
				L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,&ShowAndSetItemsEulerRingData);
			}
		}
	}
}

void	EulerRingImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}


//=======================================================================
GUICmdReqEulerRingInfo::GUICmdReqEulerRingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqEulerRingInfo::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdReqEulerRingInfo::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdReqEulerRingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendEulerRingInfo	*SendBack=GetSendBack(GUICmdSendEulerRingInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage,LocalX, LocalY ,*GetLayersBase());
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendEulerRingInfo::GUICmdSendEulerRingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendEulerRingInfo::Load(QIODevice *f)
{
	if(LibIDList.Load(f)==false)
		return false;
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdSendEulerRingInfo::Save(QIODevice *f)
{
	if(LibIDList.Save(f)==false)
		return false;
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdSendEulerRingInfo::MakeData(int localPage, int localX, int localY ,LayersBase	&LocalLBase)
{
	AlgorithmBase	*AL=LocalLBase.GetAlgorithmBase(/**/"Basic" ,/**/"EulerRing");
	if(AL==NULL)
		return;
	EulerRingBase	*BL=dynamic_cast<EulerRingBase *>(AL);
	if(BL==NULL)
		return;
	LocalX=localX;
	LocalY=localY;

	EulerRingInPage	*P=(EulerRingInPage *)BL->GetPageData(localPage);

	AlgorithmItemPI	*Item=P->GetItem(localX,localY);
	if(Item!=NULL){
		EulerRingItem	*BItem=(EulerRingItem *)Item;
		LibIDList.Add(BItem->GetLibID());
	}
}

void	GUICmdSendEulerRingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================
