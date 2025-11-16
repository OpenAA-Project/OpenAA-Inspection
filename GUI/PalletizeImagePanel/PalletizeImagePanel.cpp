/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PalletizeImagePanel\PalletizeImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define _USE_MATH_DEFINES
#include <math.h>
#include "PalletizeImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XPalletize.h"
#include "SelectPages.h"
#include "XGUI.h"
#include "ImagePanelTools.h"
#include "PropertyPalletizeForm.h"
#include "XPropertyPalletizePacket.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"PalletizeImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Palletize ImagePanel");
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
	PalletizeImagePanel	*B=new PalletizeImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	PalletizeImagePanel *InstancePtr=dynamic_cast<PalletizeImagePanel *>((PalletizeImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((PalletizeImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PalletizeImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Palletize"));
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

PalletizeImagePanel::PalletizeImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Palletize",QString(sRoot),QString(sName),__Target,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	PalletizeImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	PalletizeImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	PalletizeImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*PalletizeImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
	if(Ab!=NULL){
		PalletizeBase	*M=(PalletizeBase *)Ab;
		PalletizeDrawAttr	*mattr=new PalletizeDrawAttr(GetLayersBase()
								  ,M->ColorArea			,128
								  ,M->ColorSelected		,128
								  ,M->ColorActive		,128);
		
		return mattr;
	}
	return new PalletizeDrawAttr(GetLayersBase());
}

void	PalletizeImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
	if(Ab==NULL)
		return;
	PalletizeBase	*MBase=dynamic_cast<PalletizeBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyPalletize" ,/**/"");
	CmdPalletizeDrawEnd	Da(GetLayersBase());
	if(GProp!=NULL){
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}
void	PalletizeImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	PalletizeImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyPalletize" ,/**/"");
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
void	PalletizeImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

