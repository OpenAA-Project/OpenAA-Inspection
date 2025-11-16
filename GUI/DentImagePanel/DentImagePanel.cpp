//#include "DentImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DentImagePanel\DentImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DentImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XDentInspection.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyDentPacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"DentImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"DentImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqDentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendDentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddDent(QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));

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
	DentImagePanel	*B=new DentImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DentImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((DentImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DentImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DentInspection"));
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

DentImagePanel::DentImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"DentInspection",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	DentImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	DentImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	DentImagePanel::SlotMouseLDown(int globalX,int globalY)
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
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDent" ,/**/"");
		if(GProp!=NULL){
			CmdExecuteMouseLDown	Da(GetLayersBase());
			Da.CurrentItem=CurrentItem;
			Da.PageList=PageList;
			GProp->TransmitDirectly(&Da);
		}
	}
}

AlgorithmDrawAttr	*DentImagePanel::CreateDrawAttrPointer(void)
{
	DentBase	*Base=(DentBase *)GetAlgorithmBase();
	if(Base!=NULL){
		DentDrawAttr	*p=new DentDrawAttr(GetLayersBase()
								,Base->ColorDentNormal		,100
								,Base->ColorDentSelected	,100
								,Base->ColorDentActive		,100
								,Base->ColorPickup			,80
								,Base->DentColor0
								,Base->DentColor1
								,Base->DentColor2
								,Base->DentColor3
								,Base->DentColor4
								,Base->DentColor5
								,Base->DentColor6
								,Base->DentColor7		);
		p->Master	=GetDisplayType()==DisplayImage::__Master;
		GetActiveLayerList(p->LayerList);
		return p;
	}
	return NULL;
}

void	DentImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDent" ,/**/"");
	if(GProp!=NULL){
		CmdDentDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	DentImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdDentDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDent" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);

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

void	DentImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================
GUICmdReqDentInfo::GUICmdReqDentInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqDentInfo::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdReqDentInfo::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdReqDentInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDentInfo	*SendBack=GetSendBack(GUICmdSendDentInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage,LocalX, LocalY ,*GetLayersBase());
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendDentInfo::GUICmdSendDentInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendDentInfo::Load(QIODevice *f)
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
bool	GUICmdSendDentInfo::Save(QIODevice *f)
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

void	GUICmdSendDentInfo::MakeData(int localPage, int localX, int localY ,LayersBase	&LocalLBase)
{
	AlgorithmBase	*AL=LocalLBase.GetAlgorithmBase(/**/"Basic" ,/**/"DentInspection");
	if(AL==NULL)
		return;
	DentBase	*BL=dynamic_cast<DentBase *>(AL);
	if(BL==NULL)
		return;
	LocalX=localX;
	LocalY=localY;
	/*
	DentInPage	*P=(DentInPage *)BL->GetPageData(localPage);
	for(int L=0;L<P->GetLayerNumb();L++){
		AlgorithmItemPI	*Item=P->GetItem(localX,localY);
		if(Item!=NULL){
			DentItem	*BItem=(DentItem *)Item;
			LibIDList.AppendList(new IntClass(BItem->GetLibID()));
			LayerList.AppendList(new IntClass(L));
		}
	}
	*/
}

void	GUICmdSendDentInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================


