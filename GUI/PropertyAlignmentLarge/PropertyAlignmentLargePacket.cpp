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
//#include "ImageControlTools.h"
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
	if(::Load(f,MasterNo)==false)
		return false;
	if(::Load(f,Layer)==false)
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
	if(::Save(f,MasterNo)==false)
		return false;
	if(::Save(f,Layer)==false)
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
	MasterNo	=src.MasterNo;
	Layer		=src.Layer;
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

//==============================================================================================

GUICmdReqAlignmentLargeAreaList::GUICmdReqAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CurrentLayer=0;
}

bool	GUICmdReqAlignmentLargeAreaList::Load(QIODevice *f)
{
	if(::Load(f,CurrentLayer)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargeAreaList::Save(QIODevice *f)
{
	if(::Save(f,CurrentLayer)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargeAreaList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentLargeAreaList	*SendBack=GetSendBack(GUICmdSendAlignmentLargeAreaList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaList(localPage ,CurrentLayer,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentLargeAreaList::GUICmdSendAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentLargeAreaList::MakeAreaList(int localPage,int CurrentLayer ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	Area.RemoveAll();
	AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		AlgorithmInLayerRoot *PLayer=PData->GetLayerData(CurrentLayer);
		AlignmentLargeInLayer *AlignLayer=dynamic_cast<AlignmentLargeInLayer *>(PLayer);
		if(AlignLayer!=NULL){
			int	N=0;
			for(XAlignmentLargeArea *a=AlignLayer->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
				AlignmentLargeAreaList	*L=new AlignmentLargeAreaList();
				L->Number		=N;
				L->AreaID		=a->AreaID;
				L->AreaName		=a->AreaName;
				L->MasterNo		=a->MasterNo;
				L->Layer		=CurrentLayer;
				L->GlobalPage	=PBase->GetGlobalPageFromLocal(localPage);
				L->XSize		=a->Area.GetWidth();
				L->YSize		=a->Area.GetHeight();
				L->LimitedLib	=a->LimitedLib;
				L->Priority		=a->Priority;
				Area.AppendList(L);
			}
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
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Number)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargePointList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Number)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargePointList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentLargePointList	*SendBack=GetSendBack(GUICmdSendAlignmentLargePointList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakePointList(GetLayersBase(),Layer ,Number);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentLargePointList::GUICmdSendAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlignmentLargePointList::MakePointList(LayersBase *PBase ,int Layer ,int Number)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AlignBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	Points.RemoveAll();
	AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(AlignBase->GetPageData(LocalPage));
	if(PData!=NULL){
		AlgorithmInLayerRoot *PLayer=PData->GetLayerData(Layer);
		AlignmentLargeInLayer *AlignLayer=dynamic_cast<AlignmentLargeInLayer *>(PLayer);
		if(AlignLayer!=NULL){
			int	N=0;
			for(XAlignmentLargeArea *a=AlignLayer->Areas.GetFirst();a!=NULL;a=a->GetNext(),N++){
				if(N==Number){
					int	K=0;
					for(XAlignmentLargePointer *p=a->GPack.GetFirst();p!=NULL;p=p->GetNext(),K++){
						AlignmentLargePointList	*L=new AlignmentLargePointList();
						L->ID	=K;
						L->AreaID		=a->AreaID;
						L->ItemID		=p->Point->GetID();
						L->GroupNumber	=p->Point->GroupNumber;
						L->Layer		=Layer;
						L->Page			=GetGlobalPage();
						p->Point->GetCenter(L->Cx,L->Cy);
						L->XSize			=p->Point->GetArea().GetWidth();
						L->YSize			=p->Point->GetArea().GetHeight();
						L->MoveDotX			=p->Point->GetThresholdR()->MoveDotX;
						L->MoveDotY			=p->Point->GetThresholdR()->MoveDotY;
						L->MoveDotX2		=p->Point->GetThresholdR()->MoveDotX2;
						L->MoveDotY2		=p->Point->GetThresholdR()->MoveDotY2;
						L->SearchAround		=p->Point->GetThresholdR()->SearchAround;
						L->UsageGlobal		=p->Point->GetThresholdR()->UsageGlobal;
						L->JudgeWithBrDif	=p->Point->GetThresholdR()->JudgeWithBrDif;
						L->CharacterMode	=p->Point->GetThresholdR()->CharacterMode;
						L->UseLayer			=p->Point->GetThresholdR()->UseLayer;
						L->ThresholdColor	=p->Point->GetThresholdR()->ThresholdColor;
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
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,MasterNo)==false)
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
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MasterNo)==false)
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
	GUICmdAckAlignmentLargePutArea	*SendBack=GetSendBack(GUICmdAckAlignmentLargePutArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);


	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentLargeInLayer	*AInL=dynamic_cast<AlignmentLargeInLayer *>(AL);
	if(AInL==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(localPage));
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ImageControlTools" ,/**/"AlignmentLargeTools");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
		}
	AddAlignmentLargeAreaPacket	DPacket(this);
	DPacket.Area		=Area;
	DPacket.AreaName	=AreaName;
	DPacket.Layer		=Layer;
	DPacket.MasterNo	=MasterNo;
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
	SendBack->GeneratedAreaID=DPacket.GeneratedAreaID;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentLargePutArea::GUICmdAckAlignmentLargePutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAlignmentLargePutArea::Load(QIODevice *f)
{
	if(::Load(f,GeneratedAreaID)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentLargePutArea::Save(QIODevice *f)
{
	if(::Load(f,GeneratedAreaID)==false)
		return false;
	return true;
}
	
GUICmdReqDelAlignmentArea::GUICmdReqDelAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqDelAlignmentArea::Load(QIODevice *f)
{
	if(::Load(f,AreaName)==false)
		return false;
	return true;
}
bool	GUICmdReqDelAlignmentArea::Save(QIODevice *f)
{
	if(::Save(f,AreaName)==false)
		return false;
	return true;
}

void	GUICmdReqDelAlignmentArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	CmdReqDelAlignmentAreaByName	Cmd(GetLayersBase());
	Cmd.AreaName	=AreaName;
	AP->TransmitDirectly(&Cmd);
}

//==============================================================================

GUICmdReqAlignmentLargePutPoint::GUICmdReqAlignmentLargePutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MultiSelect=false;
}

bool	GUICmdReqAlignmentLargePutPoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(AreaID.Load(f)==false)
		return false;
	if(::Load(f,MoveDotX)==false)
		return false;
	if(::Load(f,MoveDotY)==false)
		return false;
	if(::Load(f,MoveDotX2)==false)
		return false;
	if(::Load(f,MoveDotY2)==false)
		return false;
	if(::Load(f,SearchAround)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	if(PointArea.Read(f)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,MultiSelect)==false)
		return false;
	if(::Load(f,UseBitBuff)==false)
		return false;
	if(::Load(f,JudgeWithBrDif)==false)
		return false;
	if(::Load(f,CharacterMode)==false)
		return false;
	if(::Load(f,UseLayer)==false)
		return false;
	if(::Load(f,ThresholdColor)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentLargePutPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(AreaID.Save(f)==false)
		return false;
	if(::Save(f,MoveDotX)==false)
		return false;
	if(::Save(f,MoveDotY)==false)
		return false;
	if(::Save(f,MoveDotX2)==false)
		return false;
	if(::Save(f,MoveDotY2)==false)
		return false;
	if(::Save(f,SearchAround)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	if(PointArea.Write(f)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,MultiSelect)==false)
		return false;
	if(::Save(f,UseBitBuff)==false)
		return false;
	if(::Save(f,JudgeWithBrDif)==false)
		return false;
	if(::Save(f,CharacterMode)==false)
		return false;
	if(::Save(f,UseLayer)==false)
		return false;
	if(::Save(f,ThresholdColor)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentLargePutPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentLargeInLayer	*AInL=dynamic_cast<AlignmentLargeInLayer*>(AL);
	if(AInL==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AddAlignmentLargePointPacket	DPacket(this);
	DPacket.Area				=PointArea;
	DPacket.AreaID				=AreaID;
	DPacket.MoveDotX			=MoveDotX;
	DPacket.MoveDotY			=MoveDotY;
	DPacket.MoveDotX2			=MoveDotX2;
	DPacket.MoveDotY2			=MoveDotY2;
	DPacket.SearchAround		=SearchAround;
	DPacket.UsageGlobal			=UsageGlobal;
	DPacket.GroupNumber			=GroupNumber;
	DPacket.MultiSelect			=MultiSelect;
	DPacket.UseBitBuff			=UseBitBuff;
	DPacket.JudgeWithBrDif		=JudgeWithBrDif;
	DPacket.CharacterMode		=CharacterMode;
	DPacket.UseLayer		=UseLayer	;
	DPacket.ThresholdColor	=ThresholdColor;
	AInL->TransmitDirectly(&DPacket);
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
	if(::Load(f,Layer)==false)
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
	if(::Load(f,SearchAround)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,JudgeWithBrDif)==false)
		return false;
	if(::Load(f,CharacterMode)==false)
		return false;
	if(::Load(f,UseLayer)==false)
		return false;
	if(::Load(f,ThresholdColor)==false)
		return false;

	return true;
}
bool	GUICmdReqAlignmentLargeModifyPoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
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
	if(::Save(f,SearchAround)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,JudgeWithBrDif)==false)
		return false;
	if(::Save(f,CharacterMode)==false)
		return false;
	if(::Save(f,UseLayer)==false)
		return false;
	if(::Save(f,ThresholdColor)==false)
		return false;

	return true;
}

void	GUICmdReqAlignmentLargeModifyPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentLargeInLayer	*AInL=dynamic_cast<AlignmentLargeInLayer*>(AL);
	if(AInL==NULL)
		return;
	ModifyAlignmentLargePointPacket	DPacket(this);
	DPacket.AreaID			=AreaID;
	DPacket.ItemID			=ItemID;
	DPacket.MoveDotX		=MoveDotX;
	DPacket.MoveDotY		=MoveDotY;
	DPacket.MoveDotX2		=MoveDotX2;
	DPacket.MoveDotY2		=MoveDotY2;
	DPacket.SearchAround	=SearchAround;
	DPacket.GroupNumber		=GroupNumber;
	DPacket.UsageGlobal		=UsageGlobal;
	DPacket.JudgeWithBrDif	=JudgeWithBrDif;
	DPacket.CharacterMode	=CharacterMode;
	DPacket.UseLayer		=UseLayer		;
	DPacket.ThresholdColor	=ThresholdColor	;

	AInL->TransmitDirectly(&DPacket);
}

GUICmdReqAlignmentLargeRemovePoint::GUICmdReqAlignmentLargeRemovePoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignmentLargeRemovePoint::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;

	return true;
}
bool	GUICmdReqAlignmentLargeRemovePoint::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;

	return true;
}

void	GUICmdReqAlignmentLargeRemovePoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentLargeInLayer	*AInL=dynamic_cast<AlignmentLargeInLayer*>(AL);
	if(AInL==NULL)
		return;
	RemoveAlignmentLargePointPacket	DPacket(this);
	DPacket.AreaID			=AreaID;
	DPacket.ItemID			=ItemID;
	AInL->TransmitDirectly(&DPacket);
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
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
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
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
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
	Layer=-1;
	AreaID=-1;
}

void	GUICmdSendAlignmentLargeAreaInfo::Make(int localPage,int layer,int areaID,LayersBase *Base)
{
	AlgorithmBase	*AlignBase=Base->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(layer));
	if(AL==NULL)
		return;
	AlignmentLargeInLayer	*AInL=dynamic_cast<AlignmentLargeInLayer*>(AL);
	if(AInL==NULL)
		return;
	for(XAlignmentLargeArea *a=AInL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
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
bool	GUICmdSendAlignmentLargeAreaInfo::Load(QIODevice *f)
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
	Priority=(XAlignmentLargeArea::_EnumPriority)D;
	return true;
}
bool	GUICmdSendAlignmentLargeAreaInfo::Save(QIODevice *f)
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
	if(::Load(f,MasterNo)==false)
		return false;
	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	Priority=(XAlignmentLargeArea::_EnumPriority)D;
	return true;
}
bool	GUICmdReqModifyAlignmentLargeAreaInfo::Save(QIODevice *f)
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
	if(::Save(f,MasterNo)==false)
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
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(AP->GetLayerData(Layer));
	if(AL==NULL)
		return;
	AlignmentLargeInLayer	*AInL=dynamic_cast<AlignmentLargeInLayer*>(AL);
	if(AInL==NULL)
		return;
	if(DeleteMode==false){
		for(XAlignmentLargeArea *a=AInL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==AreaID){
				a->AreaName		=AreaName;
				a->LimitedLib	=LimitedLib;
				a->Priority		=Priority;
				a->MasterNo		=MasterNo;
				return;
			}
		}
	}
	else{
		RemoveAlignmentLargeAreaPacket	Cmd(this);
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
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlignmentLargeInPage	*AP=dynamic_cast<AlignmentLargeInPage *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AP->ShowingMode=AlignmentLargeInPage::ShowingMode_AlignmentArea;
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
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlignmentLargeInPage	*AP=dynamic_cast<AlignmentLargeInPage *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;
	AP->ShowingMode=AlignmentLargeInPage::ShowingMode_AlignmentItem;
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
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
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
bool	GUICmdClearAllPoints::Load(QIODevice *f)
{
	if(::Load(f,Priority)==false)
		return false;
	return true;
}

bool	GUICmdClearAllPoints::Save(QIODevice *f)
{
	if(::Save(f,Priority)==false)
		return false;
	return true;
}
void	GUICmdClearAllPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdClearAllPoints	DPacket(this);
	DPacket.Priority=Priority;
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
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
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
	if(::Load(f,GeneratePartialAlignment)==false)
		return false;
	if(::Load(f,AlignmntPointSize)==false)
		return false;
	if(::Load(f,AlignmntSearchAreaDotX)==false)
		return false;
	if(::Load(f,AlignmntSearchAreaDotY)==false)
		return false;
	if(::Load(f,AlignmntSearchAreaDot2X)==false)
		return false;
	if(::Load(f,AlignmntSearchAreaDot2Y)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaPriority)==false)
		return false;
	if(::Load(f,LimitedLibType)==false)
		return false;
	if(::Load(f,LimitedLibID)==false)
		return false;
	if(::Load(f,AlignmntJudgeWithBrDif)==false)
		return false;
	return true;
}

bool	GUICmdAutoCreatePoint::Save(QIODevice *f)
{
	if(::Save(f,GeneratePartialAlignment)==false)
		return false;
	if(::Save(f,AlignmntPointSize)==false)
		return false;
	if(::Save(f,AlignmntSearchAreaDotX)==false)
		return false;
	if(::Save(f,AlignmntSearchAreaDotY)==false)
		return false;
	if(::Save(f,AlignmntSearchAreaDot2X)==false)
		return false;
	if(::Save(f,AlignmntSearchAreaDot2Y)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaPriority)==false)
		return false;
	if(::Save(f,LimitedLibType)==false)
		return false;
	if(::Save(f,LimitedLibID)==false)
		return false;
	if(::Save(f,AlignmntJudgeWithBrDif)==false)
		return false;
	return true;
}

void	GUICmdAutoCreatePoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdAutoCreatePoint	DPacket(this);
	DPacket.GeneratePartialAlignment=GeneratePartialAlignment;
	DPacket.AlignmntPointSize		=AlignmntPointSize;
	DPacket.AlignmntSearchAreaDotX	=AlignmntSearchAreaDotX;
	DPacket.AlignmntSearchAreaDotY	=AlignmntSearchAreaDotY;
	DPacket.AlignmntSearchAreaDot2X	=AlignmntSearchAreaDot2X;
	DPacket.AlignmntSearchAreaDot2Y	=AlignmntSearchAreaDot2Y;
	DPacket.Layer					=Layer;
	DPacket.AreaPriority			=AreaPriority;
	DPacket.LimitedLibType			=LimitedLibType;
	DPacket.LimitedLibID			=LimitedLibID;
	DPacket.AlignmntJudgeWithBrDif	=AlignmntJudgeWithBrDif;
	AP->TransmitDirectly(&DPacket);
}

//==============================================================================

GUICmdReqHeadAlignment::GUICmdReqHeadAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqHeadAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHeadAlignment	*SendBack=GetSendBack(GUICmdAckHeadAlignment,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlignmentLargeBase	*AlignBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;

	SendBack->HeadData.UseHeadAlignment		=AlignBase->UseHeadAlignment		;
	SendBack->HeadData.MaxHeadAlignmentX	=AlignBase->MaxHeadAlignmentX	 	;
	SendBack->HeadData.MaxHeadAlignmentY	=AlignBase->MaxHeadAlignmentY	 	;
	SendBack->HeadData.SkipHeadAlignmentX	=AlignBase->SkipHeadAlignmentX		; 
	SendBack->HeadData.SkipHeadAlignmentY	=AlignBase->SkipHeadAlignmentY		; 
	SendBack->HeadData.HeadAlignmentDifColor=AlignBase->HeadAlignmentDifColor	;
	SendBack->HeadData.HeadAlignmentMinSize	=AlignBase->HeadAlignmentMinSize 	;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckHeadAlignment::GUICmdAckHeadAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckHeadAlignment::Load(QIODevice *f)
{
	if(f->read((char *)&HeadData,sizeof(HeadData))!=sizeof(HeadData))	return false;

	return true;
}
bool	GUICmdAckHeadAlignment::Save(QIODevice *f)
{
	if(f->write((const char *)&HeadData,sizeof(HeadData))!=sizeof(HeadData))	return false;

	return true;
}
GUICmdSetHeadAlignment::GUICmdSetHeadAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetHeadAlignment::Load(QIODevice *f)
{
	if(f->read((char *)&HeadData,sizeof(HeadData))!=sizeof(HeadData))	return false;

	return true;
}
bool	GUICmdSetHeadAlignment::Save(QIODevice *f)
{
	if(f->write((const char *)&HeadData,sizeof(HeadData))!=sizeof(HeadData))	return false;

	return true;
}
void	GUICmdSetHeadAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckHeadAlignment	*SendBack=GetSendBack(GUICmdAckHeadAlignment,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlignmentLargeBase	*AlignBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;

	AlignBase->UseHeadAlignment		=HeadData.UseHeadAlignment	;
	AlignBase->MaxHeadAlignmentX	=HeadData.MaxHeadAlignmentX	;
	AlignBase->MaxHeadAlignmentY	=HeadData.MaxHeadAlignmentY	;
	AlignBase->SkipHeadAlignmentX	=HeadData.SkipHeadAlignmentX; 
	AlignBase->SkipHeadAlignmentY	=HeadData.SkipHeadAlignmentY; 
	AlignBase->HeadAlignmentDifColor=HeadData.HeadAlignmentDifColor	;
	AlignBase->HeadAlignmentMinSize =HeadData.HeadAlignmentMinSize	;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//==============================================================================
GUICmdSetAlignmentData::GUICmdSetAlignmentData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetAlignmentData::Load(QIODevice *f)
{
	if(::Load(f,AlignData)==false)	return false;
	return true;
}
bool	GUICmdSetAlignmentData::Save(QIODevice *f)
{
	if(::Save(f,AlignData)==false)	return false;
	return true;
}
void	GUICmdSetAlignmentData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdSetAlignmentData	DPacket(this);
	DPacket.AlignData	=AlignData;
	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================

GUICmdDeleteAreaExceptGlobal::GUICmdDeleteAreaExceptGlobal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdDeleteAreaExceptGlobal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdDeleteAreaExceptGlobal	DPacket(this);
	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================

GUICmdDeleteItemsExceptGlobal::GUICmdDeleteItemsExceptGlobal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdDeleteItemsExceptGlobal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdDeleteItemsExceptGlobal	DPacket(this);
	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}
//==============================================================================
GUICmdGenerateAuto::GUICmdGenerateAuto(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdGenerateAuto::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)	return false;
	if(::Load(f,Layer)==false)	return false;
	return true;
}
bool	GUICmdGenerateAuto::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)	return false;
	if(::Save(f,Layer)==false)	return false;
	return true;
}
void	GUICmdGenerateAuto::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePLI	*AP=dynamic_cast<AlgorithmInPagePLI *>(AlignBase->GetPageData(localPage));
	if(AP==NULL)
		return;

	CmdGenerateAuto	DPacket(this);
	DPacket.AreaID	=AreaID;
	DPacket.Layer	=Layer;
	AP->TransmitDirectly(&DPacket);
	SendAck(localPage);
}

//==============================================================================

GUICmdReqMakeAreaFromMask::GUICmdReqMakeAreaFromMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMakeAreaFromMask::Load(QIODevice *f)
{
	if(AreaPriority.Load(f)==false)	return false;
	return true;
}
bool	GUICmdReqMakeAreaFromMask::Save(QIODevice *f)
{
	if(AreaPriority.Save(f)==false)	return false;
	return true;
}

void	GUICmdReqMakeAreaFromMask::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(Ab!=NULL){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(localPage);
				if(Ap!=NULL){
					for(int layer=0;layer<GetLayerNumb(localPage);layer++){
						AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(layer);
						if(AL!=NULL){
							CmdReqMakeAreaFromMask	Cmd(GetLayersBase());
							Cmd.AreaPriority=AreaPriority;
							AL->TransmitDirectly(&Cmd);
						}
					}
				}
			}
		}
	}
}
