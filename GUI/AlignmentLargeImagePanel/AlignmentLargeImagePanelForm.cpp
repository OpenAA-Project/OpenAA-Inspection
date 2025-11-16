#include "AlignmentLargeImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentLargeImagePanel\AlignmentLargeImagePanelForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AlignmentLargeImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "AlignmentLargeImagePropertyPacket.h"
#include "XGeneralFunc.h"
#include "XPacketAlignmentLarge.h"
#include "ImagePanelTools.h"
#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"
#include "SelectAreaDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==================================================================================================
AlignmentLargeImagePanel::AlignmentLargeImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AlignmentLarge",QString(sRoot),QString(sName),__Master,parent)
{
	HasBitbuffData=false;
}

AlignmentLargeImagePanel::~AlignmentLargeImagePanel(void)
{
}


void	AlignmentLargeImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	if(GetParamGlobal()->AllocBitBuffer==false)
		ChangeDisplayType(__BitBuff);
}

void	AlignmentLargeImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*AlignmentLargeImagePanel::CreateDrawAttrPointer(void)
{
	GUICmdReqAlignmentLargeDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}

	AlignmentLargeDrawAttr	*A=new AlignmentLargeDrawAttr();
	A->AList	=DrawMode.AList;
	A->DrawKind	=DrawMode.Mode;

	return A;
}

void	AlignmentLargeImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentLargeDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.MultiSelect=GetMultiSelect();
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentLargeImagePanel::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentLargeReflectChangeItems	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentLargeImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();

	HasBitbuffData=false;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentLargeCheckBitBuff	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckAlignmentLargeCheckBitBuff	ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true){
			if(ACmd.HasData==true){
				HasBitbuffData=true;
			}
		}
	}
	GUIFormBase	*f=GetLayersBase()->FindByName(ImageControlToolsName);
	if(f!=NULL){
		CmdSetBitBuffMode	RCmd(GetLayersBase());
		RCmd.BitBuffMode=HasBitbuffData;
		f->TransmitDirectly(&RCmd);
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		CmdReqImageLayer	DModeCmd(GetLayersBase(),LayerNumb);
		f->TransmitDirectly(&DModeCmd);
		ChangeDisplayType(DModeCmd.DType);
		Repaint();
	}

}

void	AlignmentLargeImagePanel::CanvasSlotOnPaint(QPainter &pnt)
{
	if(GetDisplayType()==DisplayImage::__BitBuff){
		AlgorithmBase	*A=GetAlgorithmBase();
		AlignmentLargeBase	*Ab=dynamic_cast<AlignmentLargeBase *>(A);
		if(Ab!=NULL){
			SetTransparentLevelInBitBuff(Ab->TransparentLevelInBitBuff);
		}
	}
	DisplayImageWithAlgorithm::CanvasSlotOnPaint(pnt);
}

void	AlignmentLargeImagePanel::MultiSelectBtnDown()
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
	if(GProp!=NULL){
		CmdSetMultiSelectAlignmentLarge	Da(GetLayersBase());
		Da.MultiSelect	=GetMultiSelect();
		GProp->TransmitDirectly(&Da);
	}
	DisplayImageWithAlgorithm::MultiSelectBtnDown();
}

void	AlignmentLargeImagePanel::SelectArea(IntList &LayerList, FlexArea &Area)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectItemsAlignmentLarge	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
		if(GProp!=NULL){
			CmdReqAlignmentLargeSelectedAreaID	RCmd(GetLayersBase());
			RCmd.Page=page;
			GProp->TransmitDirectly(&RCmd);
			hCmd.AreaIDList=RCmd.AreaIDList;
		}
		hCmd.Area=Area;
		hCmd.MultiSelect	=GetMultiSelect();
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			hCmd.LayerList=LayerList;
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :SelectArea",ErrorCodeList::_Alart);
			}
		}
	}
}
void	AlignmentLargeImagePanel::ExeCutItems(FlexArea &Area)
{
	AlgorithmBase	*Base=GetAlgorithmBase();
	if(Base==NULL){
		return;
	}
	IntList	LayerList;
	GetActiveLayerList(LayerList);
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Cut items");
                             
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCutItemsAlignmentLarge	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												,/**/"");
		if(GProp!=NULL){
			CmdReqAlignmentLargeSelectedAreaID	RCmd(GetLayersBase());
			RCmd.Page=page;
			GProp->TransmitDirectly(&RCmd);
			hCmd.AreaIDList=RCmd.AreaIDList;
		}
		hCmd.Area=Area;
		hCmd.MultiSelect	=GetMultiSelect();
		if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
			hCmd.LayerList=LayerList;
			if(hCmd.SendOnly(globalPage ,0)==false){
				SetError(Error_Comm , /**/"Send error :ExeCutItems",ErrorCodeList::_Alart);
			}
		}
	}
}
void	AlignmentLargeImagePanel::ExecuteMouseLDownWithShift(int globalX ,int globalY)
{
	GUICmdReqAlignmentLargeDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												   ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	if(DrawMode.Mode==AlignmentLargeDrawAttr::_Area){
		IntList PageList;
		IntList	PickedPageList;
		ListLayerIDLibNamePack		PickedItems;
		ListAreaIDInfoContainer		PickedAreasWithPage;
		GetLayersBase()->GetGlobalPage(globalX ,globalY,globalX ,globalY ,PageList);
		for(IntClass *d=PageList.GetFirst();d!=NULL;d=d->GetNext()){
			int	globalPage=d->GetValue();
			if(globalPage<0){
				return;
			}
			IntList	LayerList;
			GetActiveLayerList(LayerList);

			int	localX ,localY;
			GetLayersBase()->GetPageData(globalPage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);

			GUICmdReqAreaOnLocalPoint	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
			Cmd.LocalX		=localX;
			Cmd.LocalY		=localY;
			Cmd.LayerList	=LayerList;
			GUICmdSendAreaOnLocalPoint	Receiver(GetLayersBase(),EmitterRoot,EmitterName ,globalPage);
			if(Cmd.Send(globalPage,0,Receiver)==true){
				if(Receiver.AreaList.GetCount()>0){
					PickedPageList.Merge(globalPage);
					for(ListAreaIDInfo *a=Receiver.AreaList.GetFirst();a!=NULL;a=a->GetNext()){
						a->GlobalPage=globalPage;
					}
					PickedAreasWithPage.AddMove(Receiver.AreaList);
				}
			}
		}
		if(PickedAreasWithPage.GetCount()==1){
			ListAreaIDInfo	*f=PickedAreasWithPage.GetFirst();
			GUICmdSelectAreaByIDs	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,f->GlobalPage);
			Cmd.AreaList=PickedAreasWithPage;
			Cmd.SendOnly(f->GlobalPage,0);
		}
		else if(PickedAreasWithPage.GetCount()>1){
			SelectAreaDialog	Q(PickedAreasWithPage,GetLayersBase());
			if(Q.exec()==(int)true && Q.SelectedAreas.GetCount()>0){
				IntList	GPage;
				for(ListAreaIDInfo *a=Q.SelectedAreas.GetFirst();a!=NULL;a=a->GetNext()){
					GPage.Merge(a->GlobalPage);
				}
				for(IntClass *c=GPage.GetFirst();c!=NULL;c=c->GetNext()){
					int	GlobalPage=c->GetValue();
					GUICmdSelectAreaByIDs	Cmd(GetLayersBase(),EmitterRoot,EmitterName ,GlobalPage);
					for(ListAreaIDInfo *a=Q.SelectedAreas.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->GlobalPage==GlobalPage){
							ListAreaIDInfo	*k=new ListAreaIDInfo();
							*k=*a;
							Cmd.AreaList.AppendList(k);
						}
					}
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		}
	}
	else
	if(DrawMode.Mode==AlignmentLargeDrawAttr::_Point){
		DisplayImageWithAlgorithm::ExecuteMouseLDownWithShift(globalX ,globalY);
	}
}

void	AlignmentLargeImagePanel::ExeSelectItems(FlexArea &Area)
{
	GUICmdReqAlignmentLargeDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentLargeForm" 
												   ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	if(DrawMode.Mode==AlignmentLargeDrawAttr::_Area){
		IntList	LayerList;
		GetActiveLayerList(LayerList);

		ExecuteReleaseAllSelection();
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSelectAreaByArea	hCmd(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
			hCmd.Area	=Area;
			hCmd.Phase	=ShowFixedPhase;
			hCmd.MultiSelect	=GetMultiSelect();
			if(GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(hCmd.Area)==true){
				hCmd.LayerList=LayerList;
				if(hCmd.SendOnly(globalPage ,0)==false){
					SetError(Error_Comm , /**/"Send error :SelectArea",ErrorCodeList::_Alart);
				}
			}
		}
	}
	else
	if(DrawMode.Mode==AlignmentLargeDrawAttr::_Point){
		DisplayImageWithAlgorithm::ExeSelectItems(Area);
	}
}

//=========================================================

GUICmdReqAlignmentLargeCheckBitBuff::GUICmdReqAlignmentLargeCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlignmentLargeCheckBitBuff::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentLargeCheckBitBuff	*SendBack=GetSendBack(GUICmdAckAlignmentLargeCheckBitBuff,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
		if(GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer)->HasDataInBitBuff()==true){
			SendBack->HasData=true;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentLargeCheckBitBuff::GUICmdAckAlignmentLargeCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	HasData=false;
}

bool	GUICmdAckAlignmentLargeCheckBitBuff::Load(QIODevice *f)
{
	if(::Load(f,HasData)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentLargeCheckBitBuff::Save(QIODevice *f)
{
	if(::Save(f,HasData)==false)
		return false;
	return true;
}

//=======================================================================
GUICmdSelectItemsAlignmentLarge::GUICmdSelectItemsAlignmentLarge(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	MultiSelect=false;
}
bool	GUICmdSelectItemsAlignmentLarge::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectItemsAlignmentLarge::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectItemsAlignmentLarge::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		AlignmentLargeInPage	*Lp=(AlignmentLargeInPage *)Ap;
		for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)Lp->GetLayerData(Layer);

			CmdSelectItemsAlignmentLarge	RCmd(GetLayersBase());
			RCmd.Area		=Area;
			RCmd.AreaIDList	=AreaIDList;
			Ly->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
}


//=======================================================================
GUICmdCutItemsAlignmentLarge::GUICmdCutItemsAlignmentLarge(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdCutItemsAlignmentLarge::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdCutItemsAlignmentLarge::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(AreaIDList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdCutItemsAlignmentLarge::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		AlignmentLargeInPage	*Lp=(AlignmentLargeInPage *)Ap;
		for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)Lp->GetLayerData(Layer);

			CmdCutItemsAlignmentLarge	RCmd(GetLayersBase());
			RCmd.Area		=Area;
			RCmd.AreaIDList	=AreaIDList;
			Ly->TransmitDirectly(&RCmd);
		}
	}

	SendAck(localPage);
}

//=======================================================================
GUICmdReqAreaOnLocalPoint::GUICmdReqAreaOnLocalPoint(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAreaOnLocalPoint::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}

	return true;
}
bool	GUICmdReqAreaOnLocalPoint::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}

	return true;
}

void	GUICmdReqAreaOnLocalPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaOnLocalPoint	*SendBack=GetSendBack(GUICmdSendAreaOnLocalPoint,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		AlignmentLargeInPage	*Lp=(AlignmentLargeInPage *)Ap;
		for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			int	Layer=L->GetValue();
			AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer	*)Lp->GetLayerData(Layer);
			CmdSelectItemsAlignmentLargeByPoint	Cmd(GetLayersBase());
			Cmd.LocalX	=LocalX;
			Cmd.LocalY	=LocalY;
			Ly->TransmitDirectly(&Cmd);
			SendBack->AreaList	=Cmd.AreaList;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAreaOnLocalPoint::GUICmdSendAreaOnLocalPoint(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAreaOnLocalPoint::Load(QIODevice *f)
{
	if(AreaList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAreaOnLocalPoint::Save(QIODevice *f)
{
	if(AreaList.Save(f)==false)
		return false;
	return true;
}

GUICmdSelectAreaByIDs::GUICmdSelectAreaByIDs(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectAreaByIDs::Load(QIODevice *f)
{
	if(AreaList.Load(f)==false){
		return false;
	}

	return true;
}
bool	GUICmdSelectAreaByIDs::Save(QIODevice *f)
{
	if(AreaList.Save(f)==false){
		return false;
	}

	return true;
}

void	GUICmdSelectAreaByIDs::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		AlignmentLargeInPage	*Lp=(AlignmentLargeInPage *)Ap;
		for(ListAreaIDInfo *c=AreaList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->Layer;
			AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)Lp->GetLayerData(Layer);

			CmdSelectAlignmentAreaByID	RCmd(GetLayersBase());
			RCmd.AreaID		=c->AreaID;
			Ly->TransmitDirectly(&RCmd);
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdSelectAreaByArea::GUICmdSelectAreaByArea(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectAreaByArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectAreaByArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectAreaByArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	if(Phase>=0){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				AlignmentLargeInPage	*Lp=(AlignmentLargeInPage *)Ap;
				for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
					int	Layer=c->GetValue();
					AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)Lp->GetLayerData(Layer);

					CmdSelectAreaByArea	RCmd(GetLayersBase());
					RCmd.Area		=Area;
					RCmd.MultiSelect=MultiSelect;
					Ly->TransmitDirectly(&RCmd);
				}
			}
		}
	}
	else{
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			AlignmentLargeInPage	*Lp=(AlignmentLargeInPage *)Ap;
			for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				int	Layer=c->GetValue();
				AlignmentLargeInLayer	*Ly=(AlignmentLargeInLayer *)Lp->GetLayerData(Layer);

				CmdSelectAreaByArea	RCmd(GetLayersBase());
				RCmd.Area		=Area;
				RCmd.MultiSelect=MultiSelect;
				Ly->TransmitDirectly(&RCmd);
			}
		}
	}
	SendAck(localPage);
}
