/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyShiftMark\XShiftMarkPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XShiftMark.h"
#include "XPropertyShiftMarkPacket.h"

//==============================================================================================================
GUICmdReqItemList::GUICmdReqItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemList	*SendBack=GetSendBack(GUICmdSendItemList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->MakeList(localPage,GetLayersBase());

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendItemList::GUICmdSendItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendItemList::MakeList(int localPage ,LayersBase *PBase)
{
	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;

	MakeShiftMarkListPacket	Cmd(GetLayersBase());
	Cmd.ListInfo=&ListInfo;
	PData->TransmitDirectly(&Cmd);
}
	
bool	GUICmdSendItemList::Load(QIODevice *f)
{
	if(ListInfo.Load(f)==false)
		return false;
	return true;
}
	
bool	GUICmdSendItemList::Save(QIODevice *f)
{
	if(ListInfo.Save(f)==false)
		return false;
	return true;
}

//======================================================================

GUICmdSendAddManualShiftMark::GUICmdSendAddManualShiftMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Vector			=NULL;
	SelectedLibID	=-1;
}

GUICmdSendAddManualShiftMark::~GUICmdSendAddManualShiftMark(void)
{
	if(Vector!=NULL){
		delete	Vector;
		Vector=NULL;
	}
}

bool	GUICmdSendAddManualShiftMark::Load(QIODevice *f)
{
	if(::Load(f,BItem)==false)
		return false;
	int		VectorID;
	if(::Load(f,VectorID)==false)
		return false;

	Vector	=VectorLineBase::Create(VectorID);
	if(Vector->Load(f)==false)
		return false;

	if(::Load(f,SelectedLibID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	return true;
}
bool	GUICmdSendAddManualShiftMark::Save(QIODevice *f)
{
	if(::Save(f,BItem)==false)
		return false;

	int	VectorID=Vector->GetID();
	if(::Save(f,VectorID)==false)
		return false;

	if(Vector->Save(f)==false)
		return false;

	if(::Save(f,SelectedLibID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	return true;
}

void	GUICmdSendAddManualShiftMark::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdAddByteShiftMarkItemPacket	Cmd(this);
			Cmd.Buff			=BItem;
			if(Vector!=NULL){
				Cmd.Vector			=Vector->CreateDup();
			}
			Cmd.LocalPage		=localPage;
			Cmd.SelectedLibID	=SelectedLibID;
			Cmd.ItemName		=ItemName;

			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}


//======================================================================

GUICmdSendAddEdgeMark::GUICmdSendAddEdgeMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddEdgeMark::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,ModeAddEdge)==false)
		return false;
	if(::Load(f,ModeAddMark)==false)
		return false;
	return true;
}
bool	GUICmdSendAddEdgeMark::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,ModeAddEdge)==false)
		return false;
	if(::Save(f,ModeAddMark)==false)
		return false;
	return true;
}

void	GUICmdSendAddEdgeMark::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdSendAddEdgeMark	Cmd(this);
			Cmd.ItemID	=ItemID;
			Cmd.Area	=Area;
			Cmd.ModeAddEdge	=ModeAddEdge;
			Cmd.ModeAddMark	=ModeAddMark;

			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}

//======================================================================

GUICmdReqItemThreshold::GUICmdReqItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqItemThreshold::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	return true;
}
bool	GUICmdReqItemThreshold::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	return true;
}
void	GUICmdReqItemThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemThreshold	*SendBack=GetSendBack(GUICmdAckItemThreshold,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			ShiftMarkItem	*Item=dynamic_cast<ShiftMarkItem *>(PData->SearchIDItem(ItemID));
			if(Item!=NULL){
				const	ShiftMarkThreshold	*RThr=Item->GetThresholdR();
				if(RThr!=NULL){
					SendBack	->ItemName			=Item->GetItemName();
					SendBack	->SearchDotEdge		=RThr->SearchDotEdge;
					SendBack	->SearchDotMarkMin	=RThr->SearchDotMarkMin;
					SendBack	->SearchDotMarkMax	=RThr->SearchDotMarkMax;
					SendBack	->NGByLosingMark	=RThr->NGByLosingMark;
					SendBack	->ThresholdLost		=RThr->ThresholdLost;
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckItemThreshold::GUICmdAckItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemThreshold::Load(QIODevice *f)
{
	if(::Load(f,ItemName		)==false)	return false;
	if(::Load(f,SearchDotEdge	)==false)	return false;
	if(::Load(f,SearchDotMarkMin)==false)	return false;
	if(::Load(f,SearchDotMarkMax)==false)	return false;
	if(::Load(f,NGByLosingMark	)==false)	return false;
	if(::Load(f,ThresholdLost	)==false)	return false;
	return true;
}
bool	GUICmdAckItemThreshold::Save(QIODevice *f)
{
	if(::Save(f,ItemName		)==false)	return false;
	if(::Save(f,SearchDotEdge	)==false)	return false;
	if(::Save(f,SearchDotMarkMin)==false)	return false;
	if(::Save(f,SearchDotMarkMax)==false)	return false;
	if(::Save(f,NGByLosingMark	)==false)	return false;
	if(::Save(f,ThresholdLost	)==false)	return false;
	return true;
}


GUICmdSetItemThreshold::GUICmdSetItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetItemThreshold::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)			return false;
	if(::Load(f,ItemID	)==false)			return false;
	if(::Load(f,ItemName		)==false)	return false;
	if(::Load(f,SearchDotEdge	)==false)	return false;
	if(::Load(f,SearchDotMarkMin)==false)	return false;
	if(::Load(f,SearchDotMarkMax)==false)	return false;
	if(::Load(f,NGByLosingMark	)==false)	return false;
	if(::Load(f,ThresholdLost	)==false)	return false;
	return true;
}
bool	GUICmdSetItemThreshold::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)			return false;
	if(::Save(f,ItemID)==false)			return false;
	if(::Save(f,ItemName		)==false)	return false;
	if(::Save(f,SearchDotEdge	)==false)	return false;
	if(::Save(f,SearchDotMarkMin)==false)	return false;
	if(::Save(f,SearchDotMarkMax)==false)	return false;
	if(::Save(f,NGByLosingMark	)==false)	return false;
	if(::Save(f,ThresholdLost	)==false)	return false;
	return true;
}

void	GUICmdSetItemThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			ShiftMarkItem	*Item=dynamic_cast<ShiftMarkItem *>(PData->SearchIDItem(ItemID));
			if(Item!=NULL){
				Item->SetItemName(ItemName);
				ShiftMarkThreshold	*WThr=Item->GetThresholdW();
				if(WThr!=NULL){
					WThr->SearchDotEdge		=SearchDotEdge	;
					WThr->SearchDotMarkMin	=SearchDotMarkMin	;
					WThr->SearchDotMarkMax	=SearchDotMarkMax	;
					WThr->NGByLosingMark	=NGByLosingMark	;
					WThr->ThresholdLost		=ThresholdLost	;
				}
			}
		}
	}
}

GUICmdChangeDirection::GUICmdChangeDirection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdChangeDirection::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	return true;
}
bool	GUICmdChangeDirection::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	return true;
}

void	GUICmdChangeDirection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			ShiftMarkItem	*Item=dynamic_cast<ShiftMarkItem *>(PData->SearchIDItem(ItemID));
			if(Item!=NULL){
				VectorLineBase	*L=Item->GetVector();
				if(L!=NULL){
					VectorItemBase	*p1=L->GetFirstItem();
					VectorItemBase	*p2=L->GetLastItem();
					L->RemoveItem(p1);
					L->RemoveItem(p2);
					L->AppendItemBase(p2);
					L->AppendItemBase(p1);
				}
			}
		}
	}
}

//======================================================================

GUICmdReqRotationPoint::GUICmdReqRotationPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRotationPoint::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	return true;
}
bool	GUICmdReqRotationPoint::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	return true;
}

void	GUICmdReqRotationPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRotationPoint	*SendBack=GetSendBack(GUICmdAckRotationPoint,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ShiftMarkBase *BBase=(ShiftMarkBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ShiftMark");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=BBase->GetPageDataPhase(Phase);
		AlgorithmInPageRoot			*PData=Ah->GetPageData(localPage);
		if(PData!=NULL){
			ShiftMarkItem	*Item=dynamic_cast<ShiftMarkItem *>(PData->SearchIDItem(ItemID));
			if(Item!=NULL){
				SendBack	->EdgeArea	=Item->EdgeArea;
				SendBack	->MarkArea	=Item->MarkArea;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRotationPoint::GUICmdAckRotationPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRotationPoint::Load(QIODevice *f)
{
	if(EdgeArea.Load(f)==false)		return false;
	if(MarkArea.Load(f)==false)		return false;
	return true;
}
bool	GUICmdAckRotationPoint::Save(QIODevice *f)
{
	if(EdgeArea.Save(f)==false)		return false;
	if(MarkArea.Save(f)==false)		return false;
	return true;
}

