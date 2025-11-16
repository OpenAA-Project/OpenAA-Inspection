#include "DotColorMatchingImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DotColorMatchingImagePanel\DotColorMatchingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DotColorMatchingImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "SelectBlockBySpecialDialog.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"DotColorMatchingImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"DotColorMatchingImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdPickupTestList(Base,QString(sRoot),QString(sName));

	//new GUICmdReqDotColorMatchingBmp(QString(sRoot),QString(sName));
	//new GUICmdSendDotColorMatchingBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddDotColorMatching(QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));

	(*Base)=new GUICmdReqItemIndependentPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendIndependentPack		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectByLibOutline		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	DotColorMatchingImagePanel	*B=new DotColorMatchingImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DotColorMatchingImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((DotColorMatchingImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DotColorMatchingImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
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

DotColorMatchingImagePanel::DotColorMatchingImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"DotColorMatching",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	DotColorMatchingImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	DotColorMatchingImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	DotColorMatchingImagePanel::SlotMouseLDown(int globalX,int globalY)
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
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDotColorMatching" ,/**/"");
		if(GProp!=NULL){
			CmdExecuteMouseLDown	Da(GetLayersBase());
			Da.CurrentItem=CurrentItem;
			Da.PageList=PageList;
			GProp->TransmitDirectly(&Da);
		}
	}
}

AlgorithmDrawAttr	*DotColorMatchingImagePanel::CreateDrawAttrPointer(void)
{
	DotColorMatchingBase	*Base=(DotColorMatchingBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new DotColorMatchingDrawAttr(GetLayersBase()
								,Base->ColorDotColorMatchingNormal		,100
								,Base->ColorDotColorMatchingSelected	,100
								,Base->ColorDotColorMatchingActive		,100
								,Base->ColorPickup			,80
								,Base->DotColorMatchingColor0
								,Base->DotColorMatchingColor1
								,Base->DotColorMatchingColor2
								,Base->DotColorMatchingColor3
								,Base->DotColorMatchingColor4
								,Base->DotColorMatchingColor5
								,Base->DotColorMatchingColor6
								,Base->DotColorMatchingColor7);
	}
	return NULL;
}

void	DotColorMatchingImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDotColorMatching" ,/**/"");
	if(GProp!=NULL){
		CmdDotColorMatchingDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	DotColorMatchingImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdDotColorMatchingDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDotColorMatching" ,/**/"");
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

void	DotColorMatchingImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	DotColorMatchingImagePanel::AddMenuSelectMenuBtn(QMenu &menu)
{
    menu.addAction (LangSolver.GetString(DotColorMatchingImagePanel_LS,LID_0)/*"Select by Lib/Outline"*/	, this, SLOT(SlotSelectByLibOutline()));
}
void	DotColorMatchingImagePanel::SlotSelectByLibOutline()
{
	SelectBlockBySpecialDialog	D(DefLibTypeDotColorMatchingInspect,GetLayersBase());
	if(D.exec()==(int)true){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectByLibOutline	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
			for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				for(AlgorithmLibraryList *a=D.Libs.SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
					SelectLibList	*v=new SelectLibList();
					v->LibType	=a->GetLibType();
					v->LibID	=a->GetLibID();
					v->Layer	=c->GetValue();
					Cmd.SelectedList.AppendList(v);
				}
			}
			Cmd.OutlineMode=D.OutlineMode;
			if(Cmd.SendOnly(GlobalPage,1)==false){
				SetError(Error_Comm , /**/"Send error :SlotSelectLibrary",ErrorCodeList::_Alart);
			}
		}


	}
}

//=======================================================================
GUICmdReqDotColorMatchingInfo::GUICmdReqDotColorMatchingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqDotColorMatchingInfo::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false)
		return false;
	if(::Load(f,LocalY)==false)
		return false;
	return true;
}
bool	GUICmdReqDotColorMatchingInfo::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false)
		return false;
	if(::Save(f,LocalY)==false)
		return false;
	return true;
}

void	GUICmdReqDotColorMatchingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDotColorMatchingInfo	*SendBack=GetSendBack(GUICmdSendDotColorMatchingInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	SendBack->MakeData(localPage,LocalX, LocalY ,*GetLayersBase());
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendDotColorMatchingInfo::GUICmdSendDotColorMatchingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendDotColorMatchingInfo::Load(QIODevice *f)
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
bool	GUICmdSendDotColorMatchingInfo::Save(QIODevice *f)
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

void	GUICmdSendDotColorMatchingInfo::MakeData(int localPage, int localX, int localY ,LayersBase	&LocalLBase)
{
	AlgorithmBase	*AL=LocalLBase.GetAlgorithmBase(/**/"Basic" ,/**/"DotColorMatching");
	if(AL==NULL)
		return;
	DotColorMatchingBase	*BL=dynamic_cast<DotColorMatchingBase *>(AL);
	if(BL==NULL)
		return;
	LocalX=localX;
	LocalY=localY;

	DotColorMatchingInPage	*P=(DotColorMatchingInPage *)BL->GetPageData(localPage);
	CmdDotColorMatchingGetItemInfo	Cmd(GetLayersBase());
	Cmd.LocalX=LocalX;
	Cmd.LocalY=LocalY;
	P->TransmitDirectly(&Cmd);
	LibIDList=Cmd.LibIDList;
	LayerList=Cmd.LayerList;
}

void	GUICmdSendDotColorMatchingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================


