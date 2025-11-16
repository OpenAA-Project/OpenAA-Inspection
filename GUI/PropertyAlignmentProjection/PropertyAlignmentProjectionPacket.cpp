/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentProjection\PropertyAlignmentProjectionPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentProjectionPacket.h"
#include "XGeneralFunc.h"
#include "XAlignmentProjection.h"
#include "ImageControlTools.h"
//#include "XGUI.h"
#include "XDisplayImagePacket.h"

//==============================================================================
bool	AlignmentProjectionPointList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,XSize)==false)
		return false;
	if(::Load(f,YSize)==false)
		return false;
	if(::Load(f,PeakCount)==false)
		return false;
	return true;
}
bool	AlignmentProjectionPointList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,XSize)==false)
		return false;
	if(::Save(f,YSize)==false)
		return false;
	if(::Save(f,PeakCount)==false)
		return false;
	return true;
}

AlignmentProjectionPointList	&AlignmentProjectionPointList::operator=(AlignmentProjectionPointList &src)
{
	ItemID		=src.ItemID;
	Phase		=src.Phase;
	Page		=src.Page;
	Cx			=src.Cx;
	Cy			=src.Cy;
	XSize		=src.XSize;
	YSize		=src.YSize;
	PeakCount	=src.PeakCount;
	return *this;
}

bool	AlignmentProjectionPointListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentProjectionPointList *p=new AlignmentProjectionPointList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentProjectionPointListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentProjectionPointList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentProjectionPointListPack	&AlignmentProjectionPointListPack::operator=(AlignmentProjectionPointListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentProjectionPointListPack	&AlignmentProjectionPointListPack::operator+=(AlignmentProjectionPointListPack &src)
{
	for(AlignmentProjectionPointList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentProjectionPointList *q=new AlignmentProjectionPointList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}

//==============================================================================
GUICmdReqAlignmentProjectionPoint::GUICmdReqAlignmentProjectionPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentProjectionPoint::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentProjectionPoint::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentProjectionPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentProjectionPoint	*SendBack=GetSendBack(GUICmdSendAlignmentProjectionPoint,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentProjection");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	ReqAlignmentProjectionPointPacket	DPacket(GetLayersBase());
	DPacket.ItemID		=ItemID;
	AP->TransmitDirectly(&DPacket);

	SendBack->ItemName		=DPacket.ItemName;
	SendBack->PeakCount		=DPacket.PeakCount;
	SendBack->Angle			=DPacket.Angle;
	SendBack->UsageLayer	=DPacket.UsageLayer;
	SendBack->AbandonRateL	=DPacket.AbandonRateL;
	SendBack->AbandonRateH	=DPacket.AbandonRateH;
	
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentProjectionPoint::GUICmdSendAlignmentProjectionPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlignmentProjectionPoint::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,PeakCount)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,PeakIsolation)==false)
		return false;
	if(::Load(f,UsageLayer)==false)
		return false;
	if(::Load(f,AbandonRateL)==false)
		return false;
	if(::Load(f,AbandonRateH)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentProjectionPoint::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,PeakCount)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,PeakIsolation)==false)
		return false;
	if(::Save(f,UsageLayer)==false)
		return false;
	if(::Save(f,AbandonRateL)==false)
		return false;
	if(::Save(f,AbandonRateH)==false)
		return false;
	return true;
}
//==============================================================================
GUICmdReqAlignmentProjectionPointListPack::GUICmdReqAlignmentProjectionPointListPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentProjectionPointListPack::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;

	return true;
}
bool	GUICmdReqAlignmentProjectionPointListPack::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;

	return true;
}

void	GUICmdReqAlignmentProjectionPointListPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentProjectionPointListPack	*SendBack=GetSendBack(GUICmdSendAlignmentProjectionPointListPack,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentProjection");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageInOnePhase	*Ph=AlignBase->GetPageDataPhase(Phase);
	if(Ph==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(Ph->GetPageData(localPage));
	if(AP==NULL)
		return;

	for(AlgorithmItemPI	*a=AP->GetFirstData();a!=NULL;a=a->GetNext()){
		AlignmentProjectionPointList	*L=new AlignmentProjectionPointList();
		AlignmentProjectionItem	*Item=dynamic_cast<AlignmentProjectionItem *>(a);
		if(Item!=NULL){
			L->ItemID	=Item->GetID();
			L->Phase	=Phase;
			L->Page		=GetLayersBase()->GetGlobalPageFromLocal(localPage);
			Item->GetCenter(L->Cx,L->Cy);
			L->XSize	=Item->GetArea().GetWidth();
			L->YSize	=Item->GetArea().GetHeight();
			L->PeakCount=Item->GetThresholdR()->PeakCount;
			SendBack->List.AppendList(L);
		}
	}
	
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentProjectionPointListPack::GUICmdSendAlignmentProjectionPointListPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlignmentProjectionPointListPack::Load(QIODevice *f)
{
	if(List.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentProjectionPointListPack::Save(QIODevice *f)
{
	if(List.Save(f)==false)
		return false;
	return true;
}

//==============================================================================

GUICmdReqAlignmentProjectionPutPoint::GUICmdReqAlignmentProjectionPutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentProjectionPutPoint::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,PeakCount)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,UsageLayer)==false)
		return false;
	if(::Load(f,AbandonRateL)==false)
		return false;
	if(::Load(f,AbandonRateH)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentProjectionPutPoint::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,PeakCount)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,UsageLayer)==false)
		return false;
	if(::Save(f,AbandonRateL)==false)
		return false;
	if(::Save(f,AbandonRateH)==false)
		return false;

	return true;
}

void	GUICmdReqAlignmentProjectionPutPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentProjection");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddAlignmentProjectionPointPacket	DPacket(this);
	DPacket.Area		=Area;
	DPacket.ItemName	=ItemName;
	DPacket.PeakCount	=PeakCount;
	DPacket.Angle		=Angle;
	DPacket.UsageLayer	=UsageLayer;
	DPacket.AbandonRateL=AbandonRateL;
	DPacket.AbandonRateH=AbandonRateH;

	AP->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqAlignmentProjectionModifyPoint::GUICmdReqAlignmentProjectionModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentProjectionModifyPoint::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,PeakCount)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,UsageLayer)==false)
		return false;
	if(::Load(f,AbandonRateL)==false)
		return false;
	if(::Load(f,AbandonRateH)==false)
		return false;

	return true;
}
bool	GUICmdReqAlignmentProjectionModifyPoint::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,PeakCount)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,UsageLayer)==false)
		return false;
	if(::Save(f,AbandonRateL)==false)
		return false;
	if(::Save(f,AbandonRateH)==false)
		return false;

	return true;
}

void	GUICmdReqAlignmentProjectionModifyPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentProjection");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	ModifyAlignmentProjectionPointPacket	DPacket(this);
	DPacket.ItemID		=ItemID;
	DPacket.ItemName	=ItemName;
	DPacket.PeakCount	=PeakCount;
	DPacket.Angle		=Angle;
	DPacket.UsageLayer	=UsageLayer;
	DPacket.AbandonRateL=AbandonRateL;
	DPacket.AbandonRateH=AbandonRateH;

	AP->TransmitDirectly(&DPacket);
}
