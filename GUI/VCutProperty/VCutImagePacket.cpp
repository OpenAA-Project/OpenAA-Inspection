/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyVCutProperty\VCutImagePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "VCutImagePacket.h"
#include "XGeneralFunc.h"
#include<QBuffer>

bool	VCutInspectionList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ThresholdShift)==false)
		return false;
	if(::Load(f,ThresholdLevel)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	return true;
}

bool	VCutInspectionList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ThresholdShift)==false)
		return false;
	if(::Save(f,ThresholdLevel)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	return true;
}

VCutInspectionListForPacketPack	&VCutInspectionListForPacketPack::operator+=(VCutInspectionListForPacketPack &src)
{
	for(VCutInspectionList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		VCutInspectionList *d=new VCutInspectionList();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		c->Save(&Buff);
		Buff.seek(0);
		d->Load(&Buff);
		AppendList(d);
	}
	return *this;
}
bool	VCutInspectionListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		VCutInspectionList *c=new VCutInspectionList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
bool	VCutInspectionListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(VCutInspectionList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}

//===========================================================================

GUICmdAddVCutInspectionArea::GUICmdAddVCutInspectionArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Vector=NULL;
}
bool	GUICmdAddVCutInspectionArea::Load(QIODevice *f)
{
	int	VectorId;
	if(::Load(f,VectorId)==false){
		return false;
	}
	if(Vector!=NULL){
		delete	Vector;
	}
	Vector=VectorLineBase::Create(VectorId);

	if(Vector->Load(f)==false){
		return false;
	}
	if(::Load(f,ThresholdShift)==false)
		return false;
	if(::Load(f,ThresholdLevel)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdAddVCutInspectionArea::Save(QIODevice *f)
{
	int	VectorId=Vector->GetID();
	if(::Save(f,VectorId)==false){
		return false;
	}

	if(Vector->Save(f)==false){
		return false;
	}
	if(::Save(f,ThresholdShift)==false)
		return false;
	if(::Save(f,ThresholdLevel)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdAddVCutInspectionArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"PCB" ,/**/"VCutInspection");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(localPage);

	if(PData==NULL)
		return;
	AddVCutInspectionAreaPacket	Cmd(this);
	Cmd.Vector	=Vector;
	Cmd.ThresholdShift	=ThresholdShift;
	Cmd.ThresholdLevel	=ThresholdLevel;
	Cmd.ThresholdLength	=ThresholdLength;
	Cmd.LibID			=LibID;

	VCutInspectionInPage	*M=dynamic_cast<VCutInspectionInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);
}

//===========================================================================

GUICmdReqVCutInspectionList::GUICmdReqVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqVCutInspectionList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendVCutInspectionList	*SendBack=GetSendBack(GUICmdSendVCutInspectionList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeVCutList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//===========================================================================
GUICmdSendVCutInspectionList::GUICmdSendVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendVCutInspectionList::Load(QIODevice *f)
{
	if(VCutInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendVCutInspectionList::Save(QIODevice *f)
{
	if(VCutInfo.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendVCutInspectionList::MakeVCutList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"PCB" ,/**/"VCutInspection");
	if(ABase==NULL)
		return;
	VCutInfo.RemoveAll();
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(ABase->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(LocalPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			VCutInspectionItem	*MItem=dynamic_cast<VCutInspectionItem *>(item);
			if(MItem!=NULL){
				VCutInspectionList	*L=new VCutInspectionList();
				L->Page=PBase->GetGlobalPageFromLocal(localPage);
				MItem->GetVector()->GetXY(L->x1,L->y1,L->x2,L->y2);
				L->ThresholdLength	=MItem->GetThresholdR()->ThresholdLength;
				L->ThresholdLevel	=MItem->GetThresholdR()->ThresholdLevel;
				L->ThresholdShift	=MItem->GetThresholdR()->ThresholdShift;
				VCutInfo.AppendList(L);				
			}
		}
	}
}
void	GUICmdSendVCutInspectionList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{}
