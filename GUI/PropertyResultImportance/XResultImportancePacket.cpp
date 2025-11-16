/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyResultImportance\XResultImportancePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XResultImportancePacket.h"
#include "XGeneralFunc.h"
#include<QBuffer>
#include "XResultImportance.h"

bool	ResultImportanceList::Load(QIODevice *f)
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
	if(::Load(f,ImportanceLevel)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}

bool	ResultImportanceList::Save(QIODevice *f)
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
	if(::Save(f,ImportanceLevel)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

ResultImportanceListForPacketPack	&ResultImportanceListForPacketPack::operator+=(ResultImportanceListForPacketPack &src)
{
	for(ResultImportanceList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		ResultImportanceList *d=new ResultImportanceList();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		c->Save(&Buff);
		Buff.seek(0);
		d->Load(&Buff);
		AppendList(d);
	}
	return *this;
}
bool	ResultImportanceListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		ResultImportanceList *c=new ResultImportanceList();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
bool	ResultImportanceListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(ResultImportanceList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}

//===========================================================================

GUICmdAddResultImportanceArea::GUICmdAddResultImportanceArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ImportanceLevel=100;
}
bool	GUICmdAddResultImportanceArea::Load(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Load(f,ImportanceLevel)==false)
		return false;

	return true;
}
bool	GUICmdAddResultImportanceArea::Save(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Save(f,ImportanceLevel)==false)
		return false;

	return true;
}

void	GUICmdAddResultImportanceArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultImportance");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	CmdAddResultImportanceItemPacket	Cmd(GetLayersBase());
	Cmd.Area	=Area;
	Cmd.ImportanceLevel	=ImportanceLevel;

	PData->TransmitDirectly(&Cmd);
}

//===========================================================================

GUICmdReqResultImportanceList::GUICmdReqResultImportanceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqResultImportanceList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendResultImportanceList	*SendBack=GetSendBack(GUICmdSendResultImportanceList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeResultImportanceList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//===========================================================================
GUICmdSendResultImportanceList::GUICmdSendResultImportanceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendResultImportanceList::Load(QIODevice *f)
{
	if(ResultImportanceInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendResultImportanceList::Save(QIODevice *f)
{
	if(ResultImportanceInfo.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendResultImportanceList::MakeResultImportanceList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultImportance");
	if(ABase==NULL)
		return;
	ResultImportanceInfo.RemoveAll();

	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(ABase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			ResultImportanceItem	*MItem=dynamic_cast<ResultImportanceItem *>(item);
			if(MItem!=NULL){
				ResultImportanceList	*L=new ResultImportanceList();
				L->Page=PBase->GetGlobalPageFromLocal(localPage);
				int x1 ,y1 ,x2 ,y2;
				MItem->GetXY(x1 ,y1 ,x2 ,y2);
				L->x1=x1;
				L->y1=y1;
				L->x2=x2;
				L->y2=y2;
				L->ImportanceLevel	=MItem->ImportanceLevel;
				L->ItemID			=item->GetID();

				ResultImportanceInfo.AppendList(L);				
			}
		}
	}
}
void	GUICmdSendResultImportanceList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{}

//===========================================================================
GUICmdChangeResultImportanceLevel::GUICmdChangeResultImportanceLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeResultImportanceLevel::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ImportanceLevel)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdChangeResultImportanceLevel::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ImportanceLevel)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
void	GUICmdChangeResultImportanceLevel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultImportance");
	if(ABase==NULL)
		return;
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(ABase->GetPageData(localPage));
	if(PData!=NULL){
		AlgorithmItemRoot *item=PData->SearchIDItem(ItemID);
		if(item!=NULL){
			ResultImportanceItem	*MItem=dynamic_cast<ResultImportanceItem *>(item);
			if(MItem!=NULL){
				MItem->ImportanceLevel=ImportanceLevel;
			}
		}
	}
}

//===========================================================================

GUICmdSelectResultImportance::GUICmdSelectResultImportance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectResultImportance::Load(QIODevice *f)
{
	if(ImportanceLevels.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectResultImportance::Save(QIODevice *f)
{
	if(ImportanceLevels.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectResultImportance::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ResultImportance");
	if(ABase==NULL)
		return;

	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(ABase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			ResultImportanceItem	*MItem=dynamic_cast<ResultImportanceItem *>(item);
			if(MItem!=NULL){
				if(ImportanceLevels.IsInclude(MItem->ImportanceLevel)==true){
					MItem->SetSelected(true);
				}
				else{
					MItem->SetSelected(false);
				}
			}
		}
	}

}
