#include "OutlineImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\OutlineImagePanel\OutlineImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineImagePanel.h"
//#include "ImagePanelTools.h"
#include "XCrossObj.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "XOutlineInspect.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"



const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"OutlineImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Color Outline ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdPickupTestList(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	OutlineImagePanel	*B=new OutlineImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((OutlineImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((OutlineImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/OutlineImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"OutlineInspection"));
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

OutlineImagePanel::OutlineImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"OutlineInspection",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	OutlineImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*OutlineImagePanel::CreateDrawAttrPointer(void)
{
	OutlineBase	*Base=(OutlineBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new OutlineDrawAttr(GetLayersBase()
									,Base->BlockNormal,100
									,Base->BlockSelected,100
									,Base->BlockActive  ,100
									,Base->ColorPickup	 ,80);
	}
	return NULL;
}

void	OutlineImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyOutlineForm" ,/**/"");
	if(GProp!=NULL){
		CmdOutlineDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}

void	OutlineImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	OutlineImagePanel::SlotMouseLDown(int globalX,int globalY)
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
			if(D.exec()==true){
				PageList=D.SelectedPages;
			}
		}
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyOutlineForm" ,/**/"");
		if(GProp!=NULL){
			CmdExecuteMouseLDown	Da(GetLayersBase());
			Da.CurrentItem=CurrentItem;
			Da.PageList=PageList;
			GProp->TransmitDirectly(&Da);
		}
	}
}
void	OutlineImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdOutlineDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName/**/(LangSolver.GetString(OutlineImagePanel_LS,LID_0)/*"Button"*/ ,/**/"PropertyOutlineForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
		if(Da.Mode==CmdOutlineDrawModePacket::_CreatedBlock){

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
//=======================================================================
