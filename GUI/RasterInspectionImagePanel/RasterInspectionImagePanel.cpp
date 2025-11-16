/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RasterInspectionImagePanel\RasterInspectionImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define _USE_MATH_DEFINES
#include <math.h>
#include "RasterInspectionImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XRasterInspection.h"
#include "SelectPages.h"
#include "XGUI.h"
//#include "ImagePanelTools.h"
#include "PropertyRasterInspectionForm.h"
#include "XPropertyRasterInspectionPacket.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"RasterInspectionImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"RasterInspection ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	RasterInspectionImagePanel	*B=new RasterInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	RasterInspectionImagePanel *InstancePtr=dynamic_cast<RasterInspectionImagePanel *>((RasterInspectionImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((RasterInspectionImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RasterInspectionImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"RasterInspection"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

RasterInspectionImagePanel::RasterInspectionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"RasterInspection",QString(sRoot),QString(sName),__Target,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	RasterInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	RasterInspectionImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	RasterInspectionImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*RasterInspectionImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
	if(Ab!=NULL){
		RasterInspectionBase	*M=(RasterInspectionBase *)Ab;
		RasterInspectionDrawAttr	*mattr=new RasterInspectionDrawAttr(GetLayersBase()
								  ,M->ColorArea			,128
								  ,M->ColorSelected		,128
								  ,M->ColorActive		,128);
		
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRasterInspection" ,/**/"");
		if(GProp!=NULL){
			CmdRasterInspectionDrawAttr	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			mattr->ModeShowPDF		=Da.ModeShowPDF;
			mattr->ModeShowItemImage=Da.ModeShowItemImage;
		}
		return mattr;
	}
	return new RasterInspectionDrawAttr(GetLayersBase());
}

void	RasterInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
	if(Ab==NULL)
		return;
	RasterInspectionBase	*MBase=dynamic_cast<RasterInspectionBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRasterInspection" ,/**/"");
	CmdRasterInspectionDrawEnd	Da(GetLayersBase());
	if(GProp!=NULL){
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}
void	RasterInspectionImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	RasterInspectionImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyRasterInspection" ,/**/"");
	if(GProp!=NULL){
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
void	RasterInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

