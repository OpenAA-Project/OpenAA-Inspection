#include "BlockImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\BlockImagePanel\BlockImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "BlockImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"BlockImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"BlockImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdPickupTestList(Base,QString(sRoot),QString(sName));


	(*Base)=new GUICmdReqSelectedItemCount		(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount		(Base ,QString(sRoot) ,QString(sName));

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
	BlockImagePanel	*B=new BlockImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((BlockImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type					=/**/"QString";
	Data[N].VariableNameWithRoute	=/**/"ImageControlToolsName";
	Data[N].Pointer					=&((BlockImagePanel *)Instance)->ImageControlToolsName;
	Data[N+1].Type					=/**/"bool";
	Data[N+1].VariableNameWithRoute	=/**/"ShiftRightClicked";
	Data[N+1].Pointer				=&((BlockImagePanel *)Instance)->ShiftRightClicked;
	return(N+2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/BlockImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"BlockInspection"));
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

BlockImagePanel::BlockImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"BlockInspection",QString(sRoot),QString(sName),__Master,parent)
{
	ShiftRightClicked	=true;
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	BlockImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	BlockImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	BlockImagePanel::SlotMouseLDown(int globalX,int globalY)
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
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBlockForm" ,/**/"");
		if(GProp!=NULL){
			CmdExecuteMouseLDown	Da(GetLayersBase());
			Da.CurrentItem=CurrentItem;
			Da.PageList=PageList;
			GProp->TransmitDirectly(&Da);
		}
	}
}

void	BlockImagePanel::SlotMouseRDown(int globalX,int globalY)
{
	DisplayImageWithAlgorithm::SlotMouseRDown(globalX,globalY);

	__DrawingMode	DMode=GetImageDrawingMode();
	DisplayImageWithAlgorithm::SlotMouseRDown(globalX,globalY);
	if(DMode!=_ItemMove){
		IntList PageList;
		GetLayersBase()->GetGlobalPage(globalX,globalY,globalX,globalY,PageList);
		if(PageList.GetCount()>1){
			SelectPages	D(GetLayersBase(),PageList,0);
			if(D.exec()==(int)true){
				PageList=D.SelectedPages;
			}
		}
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBlockForm" ,/**/"");
		if(GProp!=NULL){
			CmdExecuteMouseLDown	Da(GetLayersBase());
			Da.CurrentItem=CurrentItem;
			Da.PageList=PageList;
			GProp->TransmitDirectly(&Da);
		}
	}
}

AlgorithmDrawAttr	*BlockImagePanel::CreateDrawAttrPointer(void)
{
	BlockBase	*Base=(BlockBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new BlockDrawAttr(GetLayersBase()
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

void	BlockImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBlockForm" ,/**/"");
	if(GProp!=NULL){
		CmdBlockDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	BlockImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	if(ShiftRightClicked==false)
		return;

	CmdBlockDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBlockForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
		if(Da.Mode==CmdBlockDrawModePacket::_CreatedBlock){

			DataInPage *P=GetLayersBase()->GetPageDataByPoint(globalX ,globalY);
			if(P==NULL)
				return;
			GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.TargetPhase=ShowFixedPhase;
			P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
			GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,RecPacket);
			if(RecPacket.IsReceived()==true){
				IntList LayerList;
				GetActiveLayerList(LayerList);

				if(LayerList.IsEmpty()==false){
					ListLayerAndID SelectedItem;
					if(SelectOneItem(globalX ,globalY ,SelectedItem)==true){
						for(AlgorithmItemIndependent *p=RecPacket.IData.Items.GetFirst();p!=NULL;){
							IntClass *L;
							for(L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
								if(L->GetValue()==p->Layer){
									break;
								}
							}
							if(L==NULL || p->ItemID!=SelectedItem.ID){
								AlgorithmItemIndependent *NextP=p->GetNext();
								RecPacket.IData.Items.RemoveList(p);
								delete	p;
								p=NextP;
							}
							else{
								p=p->GetNext();
							}
						}
					}
				}
				if(RecPacket.IData.Items.IsEmpty()==false){
					LogicDLL	*L=GetAlgorithmBase()->GetLogicDLL();
					L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,NULL);
				}
			}
		}
	}
}
void	BlockImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================
GUICmdReqBlockInfo::GUICmdReqBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqBlockInfo::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdReqBlockInfo::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdReqBlockInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBlockInfo	*SendBack=GetSendBack(GUICmdSendBlockInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage,LocalX, LocalY ,*GetLayersBase());
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendBlockInfo::GUICmdSendBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendBlockInfo::Load(QIODevice *f)
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
bool	GUICmdSendBlockInfo::Save(QIODevice *f)
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

void	GUICmdSendBlockInfo::MakeData(int localPage, int localX, int localY ,LayersBase	&LocalLBase)
{
	AlgorithmBase	*AL=LocalLBase.GetAlgorithmBase(/**/"Basic" ,/**/"BlockInspection");
	if(AL==NULL)
		return;
	BlockBase	*BL=dynamic_cast<BlockBase *>(AL);
	if(BL==NULL)
		return;
	LocalX=localX;
	LocalY=localY;

	BlockInPage	*P=(BlockInPage *)BL->GetPageData(localPage);
	for(int L=0;L<P->GetLayerNumb();L++){
		AlgorithmInLayerPLI	*AinL=P->GetLayerDataPLI(L);
		AlgorithmItemPLI	*Item=AinL->GetItem(localX,localY);
		if(Item!=NULL){
			BlockItem	*BItem=(BlockItem *)Item;
			LibIDList.Add(BItem->GetLibID());
			LayerList.Add(L);
		}
	}
}

void	GUICmdSendBlockInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================


