/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\PropertyAlignmentPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentPacket.h"
#include "XGeneralFunc.h"
#include "XAlignment.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"

bool	AlignmentAreaList::Load(QIODevice *f)
{
	if(::Load(f,Number)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,XSize)==false)
		return false;
	if(::Load(f,YSize)==false)
		return false;
	return true;
}
bool	AlignmentAreaList::Save(QIODevice *f)
{
	if(::Save(f,Number)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,XSize)==false)
		return false;
	if(::Save(f,YSize)==false)
		return false;
	return true;
}

AlignmentAreaList	&AlignmentAreaList::operator=(AlignmentAreaList &src)
{
	Number		=src.Number;
	AreaID		=src.AreaID;
	AreaName	=src.AreaName;
	Layer		=src.Layer;
	GlobalPage	=src.GlobalPage;
	XSize		=src.XSize;
	YSize		=src.YSize;
	return *this;
}

bool	AlignmentAreaListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentAreaList *p=new AlignmentAreaList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentAreaListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentAreaList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentAreaListPack	&AlignmentAreaListPack::operator=(AlignmentAreaListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentAreaListPack	&AlignmentAreaListPack::operator+=(AlignmentAreaListPack &src)
{
	for(AlignmentAreaList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentAreaList *q=new AlignmentAreaList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}


//==============================================================================
bool	AlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,Layer)==false)
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
	if(::Load(f,AlignmentOnOutline)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,Threshold)==false)
		return false;
	return true;
}
bool	AlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,Layer)==false)
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
	if(::Save(f,AlignmentOnOutline)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,Threshold)==false)
		return false;
	return true;
}

AlignmentPointList	&AlignmentPointList::operator=(AlignmentPointList &src)
{
	ID			=src.ID;
	AreaID		=src.AreaID;
	ItemID		=src.ItemID;
	GroupNumber	=src.GroupNumber;
	Layer		=src.Layer;
	Page		=src.Page;
	Cx			=src.Cx;
	Cy			=src.Cy;
	XSize		=src.XSize;
	YSize		=src.YSize;
	AlignmentOnOutline	=src.AlignmentOnOutline;
	SearchDot	=src.SearchDot;
	Threshold	=src.Threshold;
	return *this;
}

bool	AlignmentPointListPack::Load(QIODevice *f)
{
	RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		AlignmentPointList *p=new AlignmentPointList();
		if(p->Load(f)==false)
			return false;
		AppendList(p);
	}
	return true;
}
bool	AlignmentPointListPack::Save(QIODevice *f)
{
	int	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlignmentPointList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

AlignmentPointListPack	&AlignmentPointListPack::operator=(AlignmentPointListPack &src)
{
	RemoveAll();
	return operator+=(src);
}
AlignmentPointListPack	&AlignmentPointListPack::operator+=(AlignmentPointListPack &src)
{
	for(AlignmentPointList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		AlignmentPointList *q=new AlignmentPointList();
		*q=*p;
		AppendList(q);
	}
	return *this;
}

//==============================================================================================

GUICmdReqAlignmentAreaList::GUICmdReqAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentAreaList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqAlignmentAreaList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqAlignmentAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentAreaList	*SendBack=GetSendBack(GUICmdSendAlignmentAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaList(localPage ,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentAreaList::GUICmdSendAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentAreaList::MakeAreaList(int localPage,LayersBase *PBase)
{
	//int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	Area.RemoveAll();
	AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		for(int layer=0;layer<AlignBase->GetLayerNumb(localPage);layer++){
			AlgorithmInLayerRoot *PLayer=PData->GetLayerData(layer);
			AlignmentInLayer *AlignLayer=dynamic_cast<AlignmentInLayer *>(PLayer);
			if(AlignLayer!=NULL){
				int	N=0;
				for(XAlignmentArea *a=AlignLayer->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
					AlignmentAreaList	*L=new AlignmentAreaList();
					L->Number		=N;
					L->AreaID		=a->AreaID;
					L->AreaName		=a->AreaName;
					L->Layer		=layer;
					L->GlobalPage	=PBase->GetGlobalPageFromLocal(localPage);
					L->XSize		=a->Area.GetWidth();
					L->YSize		=a->Area.GetHeight();
					Area.AppendList(L);
				}
			}
		}
	}
}
bool	GUICmdSendAlignmentAreaList::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentAreaList::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================
GUICmdReqAlignmentPointList::GUICmdReqAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentPointList	*SendBack=GetSendBack(GUICmdSendAlignmentPointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakePointList(GetLayersBase(),Layer ,Number);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentPointList::GUICmdSendAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentPointList::MakePointList(LayersBase *PBase ,int Layer ,int Number)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	Points.RemoveAll();
	AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(AlignBase->GetPageData(LocalPage));
	if(PData!=NULL){
		AlgorithmInLayerRoot *PLayer=PData->GetLayerData(Layer);
		AlignmentInLayer *AlignLayer=dynamic_cast<AlignmentInLayer *>(PLayer);
		if(AlignLayer!=NULL){
			int	N=0;
			for(XAlignmentArea *a=AlignLayer->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
				if(N==Number){
					int	K=0;
					for(XAlignmentPointer *p=a->GPack.GetFirst();p!=NULL;p=p->GetNext(),K++){
						AlignmentPointList	*L=new AlignmentPointList();
						L->ID	=K;
						L->AreaID	=a->AreaID;
						L->ItemID	=p->Point->GetID();
						L->GroupNumber	=p->Point->GroupNumber;
						L->Layer	=Layer;
						L->Page		=GetGlobalPage();
						p->Point->GetCenter(L->Cx,L->Cy);
						L->XSize	=p->Point->GetArea().GetWidth();
						L->YSize	=p->Point->GetArea().GetHeight();
						L->SearchDot=p->Point->GetThresholdR()->MoveDot;
						L->AlignmentOnOutline	=p->Point->GetAlignmentOnOutline();
						L->Threshold	=p->Point->GetThresholdR()->Threshold;
						Points.AppendList(L);
						//return;
					}
				}
			}
		}
	}
}
bool	GUICmdSendAlignmentPointList::Load(QIODevice *f)
{
	if(Points.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentPointList::Save(QIODevice *f)
{
	if(Points.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAlignmentPointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


//==============================================================================
GUICmdReqAlignmentPutArea::GUICmdReqAlignmentPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPutArea::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
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
	Priority=(XAlignmentArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqAlignmentPutArea::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
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

void	GUICmdReqAlignmentPutArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=dynamic_cast<AlignmentInLayer *>(AL);
	if(AInL==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(localPage));
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ImageControlTools" ,/**/"AlignmentTools");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
		}
	AddAlignmentAreaPacket	DPacket(this);
	DPacket.Number		=AInL->Areas.GetNumber();
	DPacket.Area		=Area;
	DPacket.AreaName	=AreaName;
	DPacket.Layer		=Layer;
	DPacket.LimitedLib	=LimitedLib;
	DPacket.Page		=localPage;
	DPacket.Priority	=Priority;
	AInL->TransmitDirectly(&DPacket);

	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(EmitterRoot,EmitterName,Ret,10);
	if(N!=NULL){
		CmdAddArea	Cmd(this);
		Ret[0]->TransmitDirectly(&Cmd);
	}
}

//==============================================================================

GUICmdReqAlignmentPutPoint::GUICmdReqAlignmentPutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPutPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,MoveDot)==false)
		return false;
    if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,AlignmentOnOutline)==false)
		return false;
	if(PointArea.Read(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPutPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,MoveDot)==false)
		return false;
    if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,AlignmentOnOutline)==false)
		return false;
	if(PointArea.Write(f)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPutPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=dynamic_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddAlignmentPointPacket	DPacket(this);
	DPacket.Area				=PointArea;
	DPacket.AreaID				=AreaID;
	DPacket.MoveDot				=MoveDot;		
    DPacket.Threshold			=Threshold;
	DPacket.AlignmentOnOutline	=AlignmentOnOutline;	//—ÖŠs‚ÅˆÊ’u‡‚í‚¹‚·‚é‚Æ‚«true
	AInL->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqAlignmentModifyPoint::GUICmdReqAlignmentModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentModifyPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,MoveDot)==false)
		return false;
    if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,AlignmentOnOutline)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentModifyPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,MoveDot)==false)
		return false;
    if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,AlignmentOnOutline)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentModifyPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=dynamic_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;
	ModifyAlignmentPointPacket	DPacket(this);
	DPacket.AreaID				=AreaID;
	DPacket.ItemID				=ItemID;
	DPacket.MoveDot				=MoveDot;		
    DPacket.Threshold			=Threshold;
	DPacket.AlignmentOnOutline	=AlignmentOnOutline;	//—ÖŠs‚ÅˆÊ’u‡‚í‚¹‚·‚é‚Æ‚«true
	AInL->TransmitDirectly(&DPacket);
}
//==============================================================================

GUICmdReqAlignmentPutGroup::GUICmdReqAlignmentPutGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentPutGroup::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(GroupArea.Read(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentPutGroup::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(GroupArea.Write(f)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentPutGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=dynamic_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;
	AddAlignmentGroupPacket	DPacket(this);
	DPacket.Area				=GroupArea;
	DPacket.AreaID				=AreaID;
	DPacket.GroupNumber			=GroupNumber;
	AInL->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqAlignmentAreaInfo::GUICmdReqAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentAreaInfo	*SendBack=GetSendBack(GUICmdSendAlignmentAreaInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage,Layer,AreaID,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentAreaInfo::GUICmdSendAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=-1;
	AreaID=-1;
}

void	GUICmdSendAlignmentAreaInfo::Make(int localPage,int layer,int areaID,LayersBase *Base)
{
	AlgorithmBase	*AlignBase=Base->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(layer));
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=dynamic_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;
	for(XAlignmentArea *a=AInL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==areaID){
			Layer=layer;
			AreaID		=a->AreaID;
			Area		=a->Area;
			AreaName	=a->AreaName;
			LimitedLib	=a->LimitedLib;
			Priority	=a->Priority;
			return;
		}
	}
}
bool	GUICmdSendAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
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
	Priority=(XAlignmentArea::_EnumPriority)D;
	return true;
}
bool	GUICmdSendAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
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

void	GUICmdSendAlignmentAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================

GUICmdReqModifyAlignmentAreaInfo::GUICmdReqModifyAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqModifyAlignmentAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
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
	Priority=(XAlignmentArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqModifyAlignmentAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
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
void	GUICmdReqModifyAlignmentAreaInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentInLayer	*AInL=dynamic_cast<AlignmentInLayer*>(AL);
	if(AInL==NULL)
		return;
	if(DeleteMode==false){
		for(XAlignmentArea *a=AInL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==AreaID){
				a->Area			=Area	;
				a->AreaName		=AreaName;
				a->LimitedLib	=LimitedLib;
				a->Priority		=Priority;
				return;
			}
		}
	}
	else{
		RemoveAlignmentAreaPacket	Cmd(this);
		Cmd.AreaID=AreaID;
		AInL->TransmitDirectly(&Cmd);
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
	if(L!=NULL){
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

