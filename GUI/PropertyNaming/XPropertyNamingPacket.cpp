/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\XPropertyNamingPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyNamingPacket.h"
#include "XGeneralFunc.h"
#include "XNaming.h"

GUICmdAddNamingArea::GUICmdAddNamingArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddNamingArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Row)==false)
		return false;
	if(::Load(f,Column)==false)
		return false;
	return true;
}
bool	GUICmdAddNamingArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	return true;
}

void	GUICmdAddNamingArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddNamingAreaPacket	Cmd(this);
	Cmd.Area	=Area;
	Cmd.AreaName=AreaName;
	Cmd.Row		=Row;
	Cmd.Column	=Column;
	NamingInPage	*M=dynamic_cast<NamingInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);

	SendAck(localPage);
}


GUICmdChangeNamingAttr::GUICmdChangeNamingAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeNamingAttr::Load(QIODevice *f)
{
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Row)==false)
		return false;
	if(::Load(f,Column)==false)
		return false;
	return true;
}
bool	GUICmdChangeNamingAttr::Save(QIODevice *f)
{
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	return true;
}

void	GUICmdChangeNamingAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//====================================================================
GUICmdReqSelectedNamingItems::GUICmdReqSelectedNamingItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedNamingItems::Load(QIODevice *f)
{	
	return true;	
}
bool	GUICmdReqSelectedNamingItems::Save(QIODevice *f)
{	
	return true;	
}

void	GUICmdReqSelectedNamingItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedNamingItems	*SendBack=GetSendBack(GUICmdSendSelectedNamingItems,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeSelectedNamingList(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendSelectedNamingItems::GUICmdSendSelectedNamingItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSelectedNamingItems::Load(QIODevice *f)
{
	if(Stocker.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendSelectedNamingItems::Save(QIODevice *f)
{
	if(Stocker.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendSelectedNamingItems::MakeSelectedNamingList(int localPage)
{
	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;

	ReqBuildItemPointerNaming	RCmd(GetLayersBase());
	RCmd.Stocker=&Stocker;
	NamingInPage	*PData=dynamic_cast<NamingInPage *>(NamingBase->GetPageData(localPage));
	if(PData!=NULL){
		PData->TransmitDirectly(&RCmd);
	}
}

void	GUICmdSendSelectedNamingItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


GUICmdSetSelectedNamingItems::GUICmdSetSelectedNamingItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetSelectedNamingItems::Load(QIODevice *f)
{
	if(Stocker.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetSelectedNamingItems::Save(QIODevice *f)
{
	if(Stocker.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetSelectedNamingItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;

	NamingInPage	*PData=dynamic_cast<NamingInPage *>(NamingBase->GetPageData(localPage));
	if(PData!=NULL){
		ReqSetItemPointerNaming	RCmd(this);
		RCmd.Stocker=&Stocker;
		PData->TransmitDirectly(&RCmd);
		//PData->SetItemPointer(Stocker);
	}
	SendAck(localPage);

}
//====================================================================
bool	NamingListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
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
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	if(::Save(f,Row)==false)
		return false;
	return true;
}
bool	NamingListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
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
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Column)==false)
		return false;
	if(::Load(f,Row)==false)
		return false;
	return true;
}
NamingListForPacket	&NamingListForPacket::operator=(NamingListForPacket &src)
{
	ItemID	=src.ItemID;
	Page	=src.Page;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	AreaName=src.AreaName;
	Column	=src.Column;
	Row		=src.Row;
	return *this;
}


bool	NamingListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(NamingListForPacket *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
bool	NamingListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		NamingListForPacket	*c=new NamingListForPacket();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}

NamingListForPacketPack	&NamingListForPacketPack::operator=(NamingListForPacketPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
NamingListForPacketPack	&NamingListForPacketPack::operator+=(NamingListForPacketPack &src)
{
	for(NamingListForPacket *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		NamingListForPacket *d=new NamingListForPacket();
		*d=*c;
		AppendList(d);
	}
	return *this;
}

//==============================================================================================

GUICmdReqNamingList::GUICmdReqNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqNamingList::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqNamingList::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqNamingList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNamingList	*SendBack=GetSendBack(GUICmdSendNamingList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeNamingList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendNamingList::GUICmdSendNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendNamingList::MakeNamingList(int localPage ,LayersBase *PBase)
{
	AlgorithmBase	*NamingBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;
	NamingInfo.RemoveAll();

	NamingInPage	*PData=dynamic_cast<NamingInPage *>(NamingBase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			NamingItem	*MItem=dynamic_cast<NamingItem *>(item);
			if(MItem!=NULL){
				NamingListForPacket	*L=new NamingListForPacket();
				L->Page=PBase->GetGlobalPageFromLocal(localPage);
				int x1 ,y1 ,x2 ,y2;
				MItem->GetXY(x1 ,y1 ,x2 ,y2);
				L->ItemID=MItem->GetID();
				L->x1=x1;
				L->y1=y1;
				L->x2=x2;
				L->y2=y2;
				L->AreaName	=MItem->GetItemName();
				L->Row		=MItem->Row;
				L->Column	=MItem->Column;
				NamingInfo.AppendList(L);
			}
		}
	}
}
bool	GUICmdSendNamingList::Load(QIODevice *f)
{
	if(NamingInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNamingList::Save(QIODevice *f)
{
	if(NamingInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendNamingList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================

GUICmdReqSetGroup::GUICmdReqSetGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSetGroup::Load(QIODevice *f)
{
	if(::Load(f,GroupString)==false)
		return false;
	if(::Load(f,GroupID)==false)
		return false;
	return true;
}

bool	GUICmdReqSetGroup::Save(QIODevice *f)
{
	if(::Save(f,GroupString)==false)
		return false;
	if(::Save(f,GroupID)==false)
		return false;
	return true;
}

void	GUICmdReqSetGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;

	SetGroupCmd	SGCmd(GetLayersBase());
	SGCmd.GroupString=GroupString;
	SGCmd.GroupID	=GroupID;
	NamingBase->TransmitDirectly(&SGCmd);

	//ReqMaxGroupID	ReqIDMessage(GetLayersBase());
	//NamingBase->TransmitDirectly(&ReqIDMessage);

	NamingInPage	*PData=dynamic_cast<NamingInPage *>(NamingBase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			NamingItem	*MItem=dynamic_cast<NamingItem *>(item);
			if(MItem!=NULL){
				if(MItem->GetSelected()==true){
					MItem->GroupID=GroupID;
				}
			}
		}
	}
}

//==============================================================================

GUICmdReqClearGroup::GUICmdReqClearGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqClearGroup::Load(QIODevice *f)
{
	if(::Load(f,GroupID)==false)
		return false;
	return true;
}

bool	GUICmdReqClearGroup::Save(QIODevice *f)
{
	if(::Load(f,GroupID)==false)
		return false;
	return true;
}


void	GUICmdReqClearGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;

	ClearGroupCmd	SGCmd(GetLayersBase());
	SGCmd.GroupID	=GroupID;
	NamingBase->TransmitDirectly(&SGCmd);

	//ReqMaxGroupID	ReqIDMessage(GetLayersBase());
	//NamingBase->TransmitDirectly(&ReqIDMessage);

	NamingInPage	*PData=dynamic_cast<NamingInPage *>(NamingBase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			NamingItem	*MItem=dynamic_cast<NamingItem *>(item);
			if(MItem!=NULL){
				if(MItem->GroupID==GroupID){
					MItem->GroupID=-1;
				}
			}
		}
	}
}

//==============================================================================

GUICmdReqNamingGroupList::GUICmdReqNamingGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqNamingGroupList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNamingGroupList	*SendBack=GetSendBack(GUICmdSendNamingGroupList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;
	ReqGroupData	SGCmd(GetLayersBase());
	NamingBase->TransmitDirectly(&SGCmd);

	SendBack->GroupData	=*SGCmd.GroupPointer;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendNamingGroupList::GUICmdSendNamingGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendNamingGroupList::Load(QIODevice *f)
{
	if(GroupData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNamingGroupList::Save(QIODevice *f)
{
	if(GroupData.Save(f)==false)
		return false;
	return true;
}


//==============================================================================

GUICmdReqGenerateIndex::GUICmdReqGenerateIndex(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqGenerateIndex::Load(QIODevice *f)
{
	return true;
}

bool	GUICmdReqGenerateIndex::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqGenerateIndex::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*NamingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Naming");
	if(NamingBase==NULL)
		return;

	NamingInPage	*PData=dynamic_cast<NamingInPage *>(NamingBase->GetPageData(localPage));
	if(PData!=NULL){
		ReqGenerateIndex	SGCmd(GetLayersBase());
		PData->TransmitDirectly(&SGCmd);
	}
}