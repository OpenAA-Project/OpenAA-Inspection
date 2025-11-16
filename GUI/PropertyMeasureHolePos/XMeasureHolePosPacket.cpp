#include "CreateManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHolePos\XMeasureHolePosPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XMeasureHolePosPacket.h"
#include "XMeasureHolePos.h"


//======================================================================

GUICmdSendAddManualMeasureHolePos::GUICmdSendAddManualMeasureHolePos(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Vector=NULL;
}
GUICmdSendAddManualMeasureHolePos::~GUICmdSendAddManualMeasureHolePos(void)
{
	if(Vector!=NULL){
		delete	Vector;
		Vector=NULL;
	}
}
bool	GUICmdSendAddManualMeasureHolePos::Load(QIODevice *f)
{
	int		VectorID;
	if(::Load(f,VectorID)==false)
		return false;
	Vector	=VectorLineBase::Create(VectorID);
	if(Vector->Load(f)==false)
		return false;

	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualMeasureHolePos::Save(QIODevice *f)
{
	int	VectorID=Vector->GetID();
	if(::Save(f,VectorID)==false)
		return false;
	if(Vector->Save(f)==false)
		return false;

	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualMeasureHolePos::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureHolePosBase *BBase=(MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(BBase!=NULL){
		CmdAddByteMeasureHolePosItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.Vector		=Vector;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

CmdReqMeasureHolePosColorMap::CmdReqMeasureHolePosColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdReqMeasureHolePosColorMap::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	CmdReqMeasureHolePosColorMap::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	CmdReqMeasureHolePosColorMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAckMeasureHolePosColorMap	*SendBack=GetSendBack(CmdAckMeasureHolePosColorMap,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ImagePointerContainer Images;
	GetLayersBase()->GetPageData(localPage)->GetTargetImages(Images);
	RGBStock	PickupSamples;
	Area.CreateRGBStock(Images, PickupSamples);
		
	ColorSphere	*b=new ColorSphere();
	b->Create(PickupSamples);
	SendBack->Color.AddBase(b);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

CmdAckMeasureHolePosColorMap::CmdAckMeasureHolePosColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdAckMeasureHolePosColorMap::Load(QIODevice *f)
{
	if(Color.Load(f)==false)
		return false;
	return true;
}
bool	CmdAckMeasureHolePosColorMap::Save(QIODevice *f)
{
	if(Color.Save(f)==false)
		return false;
	return true;
}

void	CmdAckMeasureHolePosColorMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


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
	MeasureHolePosBase *BBase=(MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;

	MakeListPacket	Cmd(GetLayersBase());
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

//==============================================================================================================

GUICmdReqItemThreshold::GUICmdReqItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID=0;
}

bool	GUICmdReqItemThreshold::Load(QIODevice *f)	
{	
	if(::Load(f,ItemID)==false)
		return false;
	return true;	
}

bool	GUICmdReqItemThreshold::Save(QIODevice *f)	
{	
	if(::Save(f,ItemID)==false)
		return false;
	return true;	
}
	
void	GUICmdReqItemThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemThreshold	*SendBack=GetSendBack(GUICmdSendItemThreshold,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	MeasureHolePosBase *BBase=(MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;
	AlgorithmItemRoot	*a=PData->SearchIDItem(ItemID);
	if(a!=NULL){
		MeasureHolePosItemBase	*ai=dynamic_cast<MeasureHolePosItemBase *>(a);
		if(ai!=NULL){
			SendBack->ItemName=ai->GetItemName();
			CmdCreateThresholdPacket	PCmd(GetLayersBase());
			BBase->TransmitDirectly(&PCmd);
			SendBack->Thre	=PCmd.Thre;
			SendBack->Thre->CopyFrom(*ai->GetThresholdW());
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendItemThreshold::GUICmdSendItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Thre=NULL;
}
GUICmdSendItemThreshold::~GUICmdSendItemThreshold(void)
{
	if(Thre!=NULL){
		delete	Thre;
		Thre=NULL;
	}
}


bool	GUICmdSendItemThreshold::Load(QIODevice *f)
{
	if(Thre!=NULL){
		MeasureHolePosBase *BBase=(MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
		if(BBase==NULL)
			return false;
		CmdCreateThresholdPacket	PCmd(GetLayersBase());
		BBase->TransmitDirectly(&PCmd);
		Thre	=PCmd.Thre;
	}
	if(Thre->Load(f)==false)
		return false;

	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	GUICmdSendItemThreshold::Save(QIODevice *f)
{
	if(Thre->Save(f)==false)
		return false;

	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

GUICmdSetItemThreshold::GUICmdSetItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Thre=NULL;
}
GUICmdSetItemThreshold::~GUICmdSetItemThreshold(void)
{
	if(Thre!=NULL){
		delete	Thre;
		Thre=NULL;
	}
}

bool	GUICmdSetItemThreshold::Load(QIODevice *f)
{
	if(Thre!=NULL){
		MeasureHolePosBase *BBase=(MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
		if(BBase==NULL)
			return false;
		CmdCreateThresholdPacket	PCmd(GetLayersBase());
		BBase->TransmitDirectly(&PCmd);
		Thre	=PCmd.Thre;
	}
	if(Thre->Load(f)==false)
		return false;

	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}
bool	GUICmdSetItemThreshold::Save(QIODevice *f)
{
	if(Thre->Save(f)==false)
		return false;

	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

void	GUICmdSetItemThreshold::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureHolePosBase *BBase=(MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
	if(BBase==NULL)
		return;
	AlgorithmInPageRoot		*PData=BBase->GetPageData(localPage);
	if(PData==NULL)
		return;
	AlgorithmItemRoot	*a=PData->SearchIDItem(ItemID);
	if(a!=NULL){
		MeasureHolePosItemBase	*ai=dynamic_cast<MeasureHolePosItemBase *>(a);
		if(ai!=NULL){
			ai->SetItemName(ItemName);
			ai->GetThresholdW()->CopyFrom(*Thre);
		}
	}
}



