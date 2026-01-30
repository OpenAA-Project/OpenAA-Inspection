/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include "XAreaColorConverterPacket.h"
#include "XGeneralFunc.h"
#include "XAreaColorConverter.h"


//=====================================================================================
GUICmdSendAddManualAreaColorConverter::GUICmdSendAddManualAreaColorConverter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualAreaColorConverter::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,SelectedLibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualAreaColorConverter::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,SelectedLibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualAreaColorConverter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AreaColorConverterBase *BBase=(AreaColorConverterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaColorConverter");
	if(BBase!=NULL){
		CmdAddAreaColorConverterItemPacket	Cmd(this);
		Cmd.Area			=Area;
		Cmd.LayerList		=LayerList;
		Cmd.LocalPage		=localPage;
		Cmd.SelectedLibID	=SelectedLibID;
		BBase->TransmitDirectly(&Cmd);
	}

	SendAck(localPage);
}

//===========================================================================
bool	AreaColorConverterListForPacket::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
bool	AreaColorConverterListForPacket::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

//===========================================================================
GUICmdReqAreaColorConverterList::GUICmdReqAreaColorConverterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAreaColorConverterList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAreaColorConverterList	*SendBack=GetSendBack(GUICmdSendAreaColorConverterList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeAreaColorConverterList(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAreaColorConverterList::GUICmdSendAreaColorConverterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdSendAreaColorConverterList::MakeAreaColorConverterList(int localPage)
{
	AlgorithmBase	*AreaColorConverterBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AreaColorConverter");
	if(AreaColorConverterBase==NULL)
		return;
	ItemListInfo.RemoveAll();

	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AreaColorConverterBase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *Item=PData->GetFirstData();Item!=NULL;Item=Item->GetNext()){
			AreaColorConverterListForPacket	*r=new AreaColorConverterListForPacket();
			r->Data.Page=GetLayersBase()->GetGlobalPageFromLocal(localPage);
			r->Data.ItemID	=Item->GetID();
			r->Data.LibID	=Item->GetLibID();
			Item->GetXY(r->Data.x1,r->Data.y1,r->Data.x2,r->Data.y2);
			ItemListInfo.AppendList(r);
		}
	}
}
bool	GUICmdSendAreaColorConverterList::Load(QIODevice *f)
{
	if(ItemListInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAreaColorConverterList::Save(QIODevice *f)
{
	if(ItemListInfo.Save(f)==false)
		return false;
	return true;
}