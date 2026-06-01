/*
 * Copyright (C) 2017
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

#include "PropertyFrameDefResource.h"
#include"XPropertyFrameDefPacket.h"
#include "XFrameDef.h"
#include "XGeneralFunc.h"

GUICmdAddFrameAreaManual::GUICmdAddFrameAreaManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdAddFrameAreaManual::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,FrameNumber)==false)
		return false;
	if(::Load(f,Original)==false)
		return false;
	return true;
}

bool	GUICmdAddFrameAreaManual::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,FrameNumber)==false)
		return false;
	if(::Save(f,Original)==false)
		return false;
	return true;
}

void	GUICmdAddFrameAreaManual::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	if(PPage!=NULL){
		CmdAlgoCreateFrameDefManual	Da(GetLayersBase());
		Da.Area			=Area;
		Da.GroupNumber	=GroupNumber;
		Da.FrameNumber	=FrameNumber;
		Da.Original		=Original;
		PPage->TransmitDirectly(&Da);
	}
	SendAck(localPage);
}

//==========================================================================================
GUICmdReqFrameContainer::GUICmdReqFrameContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqFrameContainer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckFrameContainer	*SendBack=GetSendBack(GUICmdAckFrameContainer,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	if(PPage!=NULL){
		CmdAckFrameContainer	Da(GetLayersBase());
		Da.ItemContainer	=&SendBack->ItemContainer;
		PPage->TransmitDirectly(&Da);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

	
GUICmdAckFrameContainer::GUICmdAckFrameContainer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckFrameContainer::Load(QIODevice *f)
{
	if(ItemContainer.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckFrameContainer::Save(QIODevice *f)
{
	if(ItemContainer.Save(f)==false)
		return false;
	return true;
}

//==========================================================================================
GUICmdReqMaxFrameNumber::GUICmdReqMaxFrameNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	GroupNumber=-1;
}
bool	GUICmdReqMaxFrameNumber::Load(QIODevice *f)
{
	if(::Load(f,GroupNumber)==false)
		return false;
	return true;
}
bool	GUICmdReqMaxFrameNumber::Save(QIODevice *f)
{
	if(::Save(f,GroupNumber)==false)
		return false;
	return true;
}

void	GUICmdReqMaxFrameNumber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMaxFrameNumber	*SendBack=GetSendBack(GUICmdAckMaxFrameNumber,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	if(PPage!=NULL){
		CmdAckMaxFrameNumber	Da(GetLayersBase());
		Da.GroupNumber	=GroupNumber;
		PPage->TransmitDirectly(&Da);
		SendBack->FrameNumber	=Da.FrameNumber;
		SendBack->OriginExists	=Da.OriginExists;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMaxFrameNumber::GUICmdAckMaxFrameNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	FrameNumber=-1;
}
bool	GUICmdAckMaxFrameNumber::Load(QIODevice *f)
{
	if(::Load(f,FrameNumber)==false)
		return false;
	if(::Load(f,OriginExists)==false)
		return false;
	return true;
}
bool	GUICmdAckMaxFrameNumber::Save(QIODevice *f)
{
	if(::Save(f,FrameNumber)==false)
		return false;
	if(::Save(f,OriginExists)==false)
		return false;
	return true;
}

//==========================================================================================

GUICmdSetItemNumber::GUICmdSetItemNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ItemID		=-1;
	GroupNumber	=-1;
	FrameNumber	=-1;
	Original	=false;
}
bool	GUICmdSetItemNumber::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,FrameNumber)==false)
		return false;
	if(::Load(f,Original)==false)
		return false;
	return true;
}
bool	GUICmdSetItemNumber::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,FrameNumber)==false)
		return false;
	if(::Save(f,Original)==false)
		return false;
	return true;
}

void	GUICmdSetItemNumber::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"FrameDef");
	if(PBase==NULL)
		return;
	AlgorithmInPageRoot	*PPage=PBase->GetPageData(localPage);
	if(PPage!=NULL){
		CmdSetItemNumber	Da(GetLayersBase());
		Da.ItemID		=ItemID;
		Da.GroupNumber	=GroupNumber;
		Da.FrameNumber	=FrameNumber;
		Da.Original		=Original;
		PPage->TransmitDirectly(&Da);
	}
}