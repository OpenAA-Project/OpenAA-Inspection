/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\PropertyAlignmentLargePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentLargePacket.h"
#include "XGeneralFunc.h"
#include "XAlignmentLarge.h"
#include "ImageControlTools.h"
//#include "XGUI.h"
#include "XDisplayImagePacket.h"

bool	AlignmentLargeAreaList::Load(QIODevice *f)
{
	if(::Load(f,Number)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,XSize)==false)
		return false;
	if(::Load(f,YSize)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Priority=(XAlignmentLargeArea::_EnumPriority)d;

	return true;
}
bool	AlignmentLargeAreaList::Save(QIODevice *f)
{
	if(::Save(f,Number)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,XSize)==false)
		return false;
	if(::Save(f,YSize)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	BYTE	d=(BYTE)Priority;
	if(::Save(f,d)==false)
		return false;
	return true;
}

AlignmentLargeAreaList	&AlignmentLargeAreaList::operator=(AlignmentLargeAreaList &src)
{
	Number		=src.Number;
	AreaID		=src.AreaID;
	AreaName	=src.AreaName;
	GlobalPage	=src.GlobalPage;
	XSize		=src.XSize;
	YSize		=src.YSize;
	LimitedLib	=src.LimitedLib;
	Priority	=src.Priority;
	return *this;
}

bool	AlignmentLargeAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentLargeAreaList *p=new AlignmentLargeAreaList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentLargeAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentLargeAreaList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentLargeAreaListPack	&AlignmentLargeAreaListPack::operator=(AlignmentLargeAreaListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentLargeAreaListPack	&AlignmentLargeAreaListPack::operator+=(AlignmentLargeAreaListPack &src)
{
	for(AlignmentLargeAreaList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentLargeAreaList *q=new AlignmentLargeAreaList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}


//==============================================================================
bool	AlignmentLargePointList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GroupID)==false)
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
	if(::Load(f,MoveDotX)==false)
		return false;
	if(::Load(f,MoveDotY)==false)
		return false;
	if(::Load(f,MoveDotX2)==false)
		return false;
	if(::Load(f,MoveDotY2)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	return true;
}
bool	AlignmentLargePointList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GroupID)==false)
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
	if(::Save(f,MoveDotX)==false)
		return false;
	if(::Save(f,MoveDotY)==false)
		return false;
	if(::Save(f,MoveDotX2)==false)
		return false;
	if(::Save(f,MoveDotY2)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	return true;
}

AlignmentLargePointList	&AlignmentLargePointList::operator=(AlignmentLargePointList &src)
{
	ID			=src.ID;
	AreaID		=src.AreaID;
	ItemID		=src.ItemID;
	GroupID		=src.GroupID;
	Page		=src.Page;
	Cx			=src.Cx;
	Cy			=src.Cy;
	XSize		=src.XSize;
	YSize		=src.YSize;
	MoveDotX	=src.MoveDotX;
	MoveDotY	=src.MoveDotY;
	MoveDotX2	=src.MoveDotX2;
	MoveDotY2	=src.MoveDotY2;
	UsageGlobal	=src.UsageGlobal;
	return *this;
}

bool	AlignmentLargePointListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentLargePointList *p=new AlignmentLargePointList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentLargePointListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentLargePointList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentLargePointListPack	&AlignmentLargePointListPack::operator=(AlignmentLargePointListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentLargePointListPack	&AlignmentLargePointListPack::operator+=(AlignmentLargePointListPack &src)
{
	for(AlignmentLargePointList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentLargePointList *q=new AlignmentLargePointList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}

//==============================================================================================

GUICmdReqAlignmentLargeAreaList::GUICmdReqAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


void	GUICmdReqAlignmentLargeAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentLargeAreaList	*SendBack=GetSendBack(GUICmdSendAlignmentLargeAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaList(localPage ,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentLargeAreaList::GUICmdSendAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentLargeAreaList::MakeAreaList(int localPage ,LayersBase *PBase)
{
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	Area.RemoveAll();
	AlignmentLargeInPage	*PData=dynamic_cast<AlignmentLargeInPage *>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		int	N=0;
		for(XAlignmentLargeArea *a=PData->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
			AlignmentLargeAreaList	*L=new AlignmentLargeAreaList();
			L->Number		=N;
			L->AreaID		=a->AreaID;
			L->AreaName		=a->AreaName;
			L->GlobalPage	=PBase->GetGlobalPageFromLocal(localPage);
			L->XSize		=a->Area.GetWidth();
			L->YSize		=a->Area.GetHeight();
			L->LimitedLib	=a->LimitedLib;
			L->Priority		=a->Priority;
			Area.AppendList(L);
		}
	}
}
bool	GUICmdSendAlignmentLargeAreaList::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentLargeAreaList::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentLargeAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================
GUICmdReqAlignmentLargePointList::GUICmdReqAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargePointList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargePointList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargePointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentLargePointList	*SendBack=GetSendBack(GUICmdSendAlignmentLargePointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakePointList(GetLayersBase() ,Number);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentLargePointList::GUICmdSendAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentLargePointList::MakePointList(LayersBase *PBase ,int Number)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	Points.RemoveAll();
	AlignmentLargeInPage	*PData=dynamic_cast<AlignmentLargeInPage	*>(AlignBase->GetPageData(LocalPage));
	if(PData!=NULL){
		int	N=0;
		for(XAlignmentLargeArea *a=PData->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
			if(N==Number){
				int	K=0;
				for(XAlignmentLargePointerContainer *g=a->GPack.GetFirst();g!=NULL;g=g->GetNext()){
					for(XAlignmentLargePointer *p=g->NPListPack<XAlignmentLargePointer>::GetFirst();p!=NULL;p=p->GetNext(),K++){
						AlignmentLargePointList	*L=new AlignmentLargePointList();
						L->ID	=K;
						L->AreaID		=a->AreaID;
						L->ItemID		=p->Point->GetID();
						L->GroupID		=p->Point->GetGroupID();
						L->Page			=GetGlobalPage();
						p->Point->GetCenter(L->Cx,L->Cy);
						L->XSize		=p->Point->GetArea().GetWidth();
						L->YSize		=p->Point->GetArea().GetHeight();
						L->MoveDotX		=p->Point->GetThresholdR()->MoveDotX;
						L->MoveDotY		=p->Point->GetThresholdR()->MoveDotY;
						L->MoveDotX2	=p->Point->GetThresholdR()->MoveDotX2;
						L->MoveDotY2	=p->Point->GetThresholdR()->MoveDotY2;
						L->UsageGlobal	=p->Point->GetThresholdR()->UsageGlobal;
						Points.AppendList(L);
						//return;
					}
				}
			}
		}
	}
}
bool	GUICmdSendAlignmentLargePointList::Load(QIODevice *f)
{
	if(Points.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentLargePointList::Save(QIODevice *f)
{
	if(Points.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentLargePointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


//==============================================================================
GUICmdReqAlignmentLargePutArea::GUICmdReqAlignmentLargePutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargePutArea::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(Area.Read(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentLargeArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqAlignmentLargePutArea::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(Area.Write(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	BYTE	D=(BYTE)Priority;
	if(::Save(f,D)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargePutArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ImageControlTools" ,/**/"AlignmentLargeTools");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	AddAlignmentLargeAreaPacket	DPacket(this);
	DPacket.Area		=Area;
	DPacket.AreaName	=AreaName;
	DPacket.LimitedLib	=LimitedLib;
	DPacket.Page		=localPage;
	DPacket.Priority	=Priority;
	AP->TransmitDirectly(&DPacket);

	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(EmitterRoot,EmitterName,Ret,10);
	if(N!=NULL){
		CmdAddArea	Cmd(this);
		Ret[0]->TransmitDirectly(&Cmd);
	}
}

//==============================================================================

GUICmdReqAlignmentLargePutPoint::GUICmdReqAlignmentLargePutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargePutPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,MoveDotX)==false)
		return false;
	if(::Load(f,MoveDotY)==false)
		return false;
	if(::Load(f,MoveDotX2)==false)
		return false;
	if(::Load(f,MoveDotY2)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	if(PointArea.Read(f)==false)
		return false;
	if(::Load(f,GroupID)==false)
		return false;
	if(::Load(f,UseBitBuff)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargePutPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,MoveDotX)==false)
		return false;
	if(::Save(f,MoveDotY)==false)
		return false;
	if(::Save(f,MoveDotX2)==false)
		return false;
	if(::Save(f,MoveDotY2)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	if(PointArea.Write(f)==false)
		return false;
	if(::Save(f,GroupID)==false)
		return false;
	if(::Save(f,UseBitBuff)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargePutPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddAlignmentLargePointPacket	DPacket(this);
	DPacket.Area				=PointArea;
	DPacket.AreaID				=AreaID;
	DPacket.MoveDotX			=MoveDotX;
	DPacket.MoveDotY			=MoveDotY;
	DPacket.MoveDotX2			=MoveDotX2;
	DPacket.MoveDotY2			=MoveDotY2;
	DPacket.UsageGlobal			=UsageGlobal;
	DPacket.GroupID				=GroupID;
	DPacket.UseBitBuff			=UseBitBuff;

	AP->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqAlignmentLargeModifyPoint::GUICmdReqAlignmentLargeModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargeModifyPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,MoveDotX)==false)
		return false;
	if(::Load(f,MoveDotY)==false)
		return false;
	if(::Load(f,MoveDotX2)==false)
		return false;
	if(::Load(f,MoveDotY2)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	if(::Load(f,GroupID)==false)
		return false;

	return true;
}
bool	GUICmdReqAlignmentLargeModifyPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,MoveDotX)==false)
		return false;
	if(::Save(f,MoveDotY)==false)
		return false;
	if(::Save(f,MoveDotX2)==false)
		return false;
	if(::Save(f,MoveDotY2)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	if(::Save(f,GroupID)==false)
		return false;

	return true;
}

void	GUICmdReqAlignmentLargeModifyPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	ModifyAlignmentLargePointPacket	DPacket(this);
	DPacket.AreaID			=AreaID;
	DPacket.ItemID			=ItemID;
	DPacket.MoveDotX		=MoveDotX;
	DPacket.MoveDotY		=MoveDotY;
	DPacket.MoveDotX2		=MoveDotX2;
	DPacket.MoveDotY2		=MoveDotY2;
	DPacket.GroupID			=GroupID;
	DPacket.UsageGlobal		=UsageGlobal;
	AP->TransmitDirectly(&DPacket);
}

//===================================================================================================

GUICmdReqAlignmentLargeMakeGroup::GUICmdReqAlignmentLargeMakeGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlignmentLargeMakeGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	MakeAlignmentLargeGroupPacket	DPacket(this);
	DPacket.Cmd=cmd;
	AP->TransmitDirectly(&DPacket);
}

//===================================================================================================

GUICmdReqAlignmentLargeRemoveGroup::GUICmdReqAlignmentLargeRemoveGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAlignmentLargeRemoveGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	RemoveAlignmentLargeGroupPacket	DPacket(this);
	AP->TransmitDirectly(&DPacket);
}
//==============================================================================

GUICmdReqAlignmentLargeAreaInfo::GUICmdReqAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargeAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargeAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargeAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentLargeAreaInfo	*SendBack=GetSendBack(GUICmdSendAlignmentLargeAreaInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,Layer,AreaID,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentLargeAreaInfo::GUICmdSendAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID=-1;
}

void	GUICmdSendAlignmentLargeAreaInfo::Make(int localPage,int layer,int areaID,LayersBase *Base)
{
	AlgorithmBase	*AlignBase=Base->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlignmentLargeInPage	*AP=dynamic_cast<AlignmentLargeInPage *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	for(XAlignmentLargeArea *a=AP->Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==areaID){
			AreaID		=a->AreaID;
			Area		=a->Area;
			AreaName	=a->AreaName;
			LimitedLib	=a->LimitedLib;
			Priority	=a->Priority;
			return;
		}
	}
}
bool	GUICmdSendAlignmentLargeAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentLargeArea::_EnumPriority)D;
	return true;
}
bool	GUICmdSendAlignmentLargeAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	BYTE	D=(BYTE)Priority;
	if(::Save(f,D)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentLargeAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================

GUICmdReqModifyAlignmentLargeAreaInfo::GUICmdReqModifyAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqModifyAlignmentLargeAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	if(::Load(f,DeleteMode)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentLargeArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqModifyAlignmentLargeAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	if(::Save(f,DeleteMode)==false)
		return false;
	BYTE	D=(BYTE)Priority;
	if(::Save(f,D)==false)
		return false;
	return true;
}
void	GUICmdReqModifyAlignmentLargeAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlignmentLargeInPage	*AP=dynamic_cast<AlignmentLargeInPage *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	if(DeleteMode==false){
		for(XAlignmentLargeArea *a=AP->Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==AreaID){
				a->AreaName		=AreaName;
				a->LimitedLib	=LimitedLib;
				a->Priority		=Priority;
				return;
			}
		}
	}
	else{
		RemoveAlignmentLargeAreaPacket	Cmd(this);
		Cmd.AreaID=AreaID;
		AP->TransmitDirectly(&Cmd);
	}
}

//==============================================================================

GUICmdSetActiveAreas::GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetActiveAreas::Load(QIODevice *f)
{
	if(ActiveAreas.Load(f)==false){
		return false;
	}
	if(::Load(f,InstForm)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetActiveAreas::Save(QIODevice *f)
{
	if(ActiveAreas.Save(f)==false){
		return false;
	}
	if(::Save(f,InstForm)==false){
		return false;
	}
	return true;
}

void	GUICmdSetActiveAreas::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstForm);
	if(L!=NULL && localPage==0){
		CmdSetActiveAreas	Cmd(this);
		Cmd.ActiveAreas=ActiveAreas;
		L->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//==============================================================================

GUICmdClickAreaButton::GUICmdClickAreaButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdClickAreaButton::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClickAreaButton::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	GUICmdClickAreaButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstName);
	if(L!=NULL){
		L->TransmitDirectly(this);
	}
}

//==============================================================================

GUICmdClickPointButton::GUICmdClickPointButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdClickPointButton::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClickPointButton::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	GUICmdClickPointButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstName);
	if(L!=NULL){
		L->TransmitDirectly(this);
	}
}

//==============================================================================

GUICmdClickGroupButton::GUICmdClickGroupButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdClickGroupButton::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClickGroupButton::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	return true;
}

void	GUICmdClickGroupButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*L=GetLayersBase()->FindByName(EmitterRoot,EmitterName,InstName);
	if(L!=NULL){
		L->TransmitDirectly(this);
	}
}


//==============================================================================
GUICmdClearAllAreas::GUICmdClearAllAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdClearAllAreas::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdClearAllAreas	DPacket(this);
	AP->TransmitDirectly(&DPacket);
}
//==============================================================================
GUICmdClearAllPoints::GUICmdClearAllPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdClearAllPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdClearAllPoints	DPacket(this);
	AP->TransmitDirectly(&DPacket);
}
//==============================================================================
GUICmdCreateAreaInMask::GUICmdCreateAreaInMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdCreateAreaInMask::Load(QIODevice *f)
{
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,Erosion)==false)
		return false;
	return true;
}

bool	GUICmdCreateAreaInMask::Save(QIODevice *f)
{
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,Erosion)==false)
		return false;
	return true;
}

void	GUICmdCreateAreaInMask::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdCreateAreaInMask	DPacket(this);
	DPacket.Priority	=Priority;
	DPacket.Erosion		=Erosion;

	AP->TransmitDirectly(&DPacket);
}
//==============================================================================
GUICmdAutoCreatePoint::GUICmdAutoCreatePoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAutoCreatePoint::Load(QIODevice *f)
{
	if(::Load(f,AlignmntPointSize)==false)
		return false;
	if(::Load(f,AlignmntSearchAreaDot)==false)
		return false;
	if(::Load(f,AlignmntSearchAreaDot2)==false)
		return false;
	return true;
}

bool	GUICmdAutoCreatePoint::Save(QIODevice *f)
{
	if(::Save(f,AlignmntPointSize)==false)
		return false;
	if(::Save(f,AlignmntSearchAreaDot)==false)
		return false;
	if(::Save(f,AlignmntSearchAreaDot2)==false)
		return false;
	return true;
}

void	GUICmdAutoCreatePoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdAutoCreatePoint	DPacket(this);
	DPacket.AlignmntPointSize		=AlignmntPointSize;
	DPacket.AlignmntSearchAreaDot	=AlignmntSearchAreaDot;
	DPacket.AlignmntSearchAreaDot2	=AlignmntSearchAreaDot2;
	AP->TransmitDirectly(&DPacket);
}
//==============================================================================
GUICmdReqAlignmentLargeAngleList::GUICmdReqAlignmentLargeAngleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargeAngleList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargeAngleList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargeAngleList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentLargeAngleList	*SendBack=GetSendBack(GUICmdAckAlignmentLargeAngleList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*AP=dynamic_cast<AlgorithmInPagePI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqAlignmentLargeAngleList	Cmd(GetLayersBase());
	Cmd.ItemID=ItemID;
	AP->TransmitDirectly(&Cmd);
	SendBack->AngleList=Cmd.AngleList;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentLargeAngleList::GUICmdAckAlignmentLargeAngleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAlignmentLargeAngleList::Load(QIODevice *f)
{
	if(AngleList.Load(f)==false)
		return false;
	return true;
}
	
bool	GUICmdAckAlignmentLargeAngleList::Save(QIODevice *f)
{
	if(AngleList.Save(f)==false)
		return false;
	return true;
}