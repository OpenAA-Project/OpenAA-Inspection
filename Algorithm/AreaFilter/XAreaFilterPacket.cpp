/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XAreaFilterPacket.h"
#include "XGeneralFunc.h"
#include "XAreaFilter.h"

//=====================================================================================
GUICmdSendAddManualAreaFilter::GUICmdSendAddManualAreaFilter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualAreaFilter::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,SelectedLibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualAreaFilter::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,SelectedLibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualAreaFilter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AreaFilterBase *BBase=(AreaFilterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaFilter");
	if(BBase!=NULL){
		CmdAddAreaFilterItemPacket	Cmd(this);
		Cmd.Area			=Area;
		Cmd.LayerList		=LayerList;
		Cmd.LocalPage		=localPage;
		Cmd.SelectedLibID	=SelectedLibID;
		BBase->TransmitDirectly(&Cmd);
	}

	SendAck(localPage);
}

//===========================================================================
bool	AreaFilterListForPacket::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	AreaFilterListForPacket::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

//===========================================================================
GUICmdReqAreaFilterList::GUICmdReqAreaFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAreaFilterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaFilterList	*SendBack=GetSendBack(GUICmdSendAreaFilterList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaFilterList(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAreaFilterList::GUICmdSendAreaFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendAreaFilterList::MakeAreaFilterList(int localPage)
{
	AlgorithmBase	*AreaFilterBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AreaFilter");
	if(AreaFilterBase==NULL)
		return;
	ItemListInfo.RemoveAll();

	AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(AreaFilterBase->GetPageData(localPage));
	if(PData!=NULL){
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			AlgorithmInLayerPLI *L=PData->GetLayerDataPLI(Layer);
			for(AlgorithmItemPLI *Item=L->GetFirstData();Item!=NULL;Item=Item->GetNext()){
				AreaFilterListForPacket	*r=new AreaFilterListForPacket();
				r->Data.Page=GetLayersBase()->GetGlobalPageFromLocal(localPage);
				r->Data.Layer	=Layer;
				r->Data.ItemID	=Item->GetID();
				r->Data.LibID	=Item->GetLibID();
				Item->GetXY(r->Data.x1,r->Data.y1,r->Data.x2,r->Data.y2);
				ItemListInfo.AppendList(r);
			}
		}
	}
}
bool	GUICmdSendAreaFilterList::Load(QIODevice *f)
{
	if(ItemListInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAreaFilterList::Save(QIODevice *f)
{
	if(ItemListInfo.Save(f)==false)
		return false;
	return true;
}
