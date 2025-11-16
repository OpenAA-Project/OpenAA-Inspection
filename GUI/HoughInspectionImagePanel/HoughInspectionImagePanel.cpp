#include "HoughInspectionImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HoughInspectionImagePanel\HoughInspectionImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HoughInspectionImagePanel.h"
#include "XAlgorithmDLL.h"

#include "XCrossObj.h"
#include "XHoughInspection.h"
#include "XGeneralDialog.h"
#include "XHoughInspectionPacket.h"
#include "SelectPages.h"
#include "XDisplayImagePacket.h"
#include "XAlgorithmBase.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"HoughImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Image panel for Hough transform inspection");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddAlignment(QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	HoughInspectionImagePanel	*B=new HoughInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((HoughInspectionImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((HoughInspectionImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HoughInspectionImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Hough"));
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

//==================================================================================================
HoughInspectionImagePanel::HoughInspectionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Hough",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	HoughInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	HoughInspectionImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*HoughInspectionImagePanel::CreateDrawAttrPointer(void)
{
	HoughBase	*a=dynamic_cast<HoughBase *>(GetAlgorithmBase());
	if(a!=NULL){
		HoughDrawAttr	*c=new HoughDrawAttr(a->ColorMask		,a->TransparentLevel
											,  a->ColorSelected	,a->TransparentLevel
											,  a->ColorActive	,a->TransparentLevel
											,a->NegColorMask
											,a->NegColorSelected);

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyHoughInspection" ,/**/"");
		if(GProp!=NULL){
			CmdHoughDrawPacket	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			c->DMode	=Da.DMode;
		}
		return c;
	}
	else{
		HoughDrawAttr	*c=new HoughDrawAttr();
		return c;
	}
}

void	HoughInspectionImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	HoughInspectionImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
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
void	HoughInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyHoughInspection" ,/**/"");
	if(GProp!=NULL){
		CmdHoughDrawEnd	Da(GetLayersBase());
		Da.Area			=area;
		GetActiveLayerList(Da.LayerList);
		GProp->TransmitDirectly(&Da);
	}
}

void	HoughInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


