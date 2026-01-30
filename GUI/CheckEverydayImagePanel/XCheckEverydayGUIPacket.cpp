/*
 * Copyright (C) 2020
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

#include "CheckEverydayImagePanelResource.h"
#include "XCheckEverydayGUIPacket.h"
#include "XGeneralFunc.h"
#include "XCheckEverydayCommon.h"

GUICmdReqAddManualLight::GUICmdReqAddManualLight(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	BrightnessLow	=0;
	BrightnessHigh	=255;
}
bool	GUICmdReqAddManualLight::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,BrightnessLow)==false)
		return false;
	if(::Load(f,BrightnessHigh)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqAddManualLight::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,BrightnessLow)==false)
		return false;
	if(::Save(f,BrightnessHigh)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqAddManualLight::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PBase=BBase->GetPageData(localPage);
		AddCheckEverydayAreaLightPacket	Cmd(this);
		Cmd.ItemName		=ItemName;
		Cmd.BrightnessLow	=BrightnessLow;
		Cmd.BrightnessHigh	=BrightnessHigh;
		Cmd.Area			=Area;
		Cmd.LayerList		=LayerList;
		PBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}


GUICmdReqAddManualFocus::GUICmdReqAddManualFocus(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	FocusLow=0;
}
bool	GUICmdReqAddManualFocus::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,FocusLow)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdReqAddManualFocus::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,FocusLow)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	return true;
}


void	GUICmdReqAddManualFocus::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PBase=BBase->GetPageData(localPage);
		AddCheckEverydayAreaFocusPacket	Cmd(this);
		Cmd.ItemName	=ItemName;
		Cmd.FocusLow	=FocusLow;
		Cmd.Area		=Area;
		Cmd.LayerList	=LayerList;
		PBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
	
GUICmdReqModifyManualLight::GUICmdReqModifyManualLight(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	BrightnessLow	=0;
	BrightnessHigh	=255;
	Layer			=0;
	ItemID			=0;
}
bool	GUICmdReqModifyManualLight::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,BrightnessLow)==false)
		return false;
	if(::Load(f,BrightnessHigh)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqModifyManualLight::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,BrightnessLow)==false)
		return false;
	if(::Save(f,BrightnessHigh)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqModifyManualLight::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PBase=BBase->GetPageData(localPage);
		ModifyCheckEverydayAreaLightPacket	Cmd(this);
		Cmd.ItemName		=ItemName;
		Cmd.BrightnessLow	=BrightnessLow;
		Cmd.BrightnessHigh	=BrightnessHigh;
		Cmd.Layer			=Layer;
		Cmd.ItemID			=ItemID;
		PBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

	
GUICmdReqModifyManualFocus::GUICmdReqModifyManualFocus(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	FocusLow	=0;
	Layer			=0;
	ItemID			=0;
}
bool	GUICmdReqModifyManualFocus::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,FocusLow)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqModifyManualFocus::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,FocusLow)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqModifyManualFocus::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PBase=BBase->GetPageData(localPage);
		ModifyCheckEverydayAreaFocusPacket	Cmd(this);
		Cmd.ItemName	=ItemName;
		Cmd.FocusLow	=FocusLow;
		Cmd.Layer		=Layer;
		Cmd.ItemID		=ItemID;
		PBase->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
//------------------------------------------------------------------------------------------------------


GUICmdReqInfo::GUICmdReqInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckInfo	*SendBack=GetSendBack(GUICmdAckInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Make(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckInfo::GUICmdAckInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdAckInfo::Make(int localPage)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
	if(BBase!=NULL){
		AlgorithmInPageRoot		*PBase=BBase->GetPageData(localPage);
		ReqCheckEverydayInfo	Cmd(GetLayersBase());
		Cmd.pInfoLight=&InfoLight;
		Cmd.pInfoFocus=&InfoFocus;
		PBase->TransmitDirectly(&Cmd);
	}
}

bool	GUICmdAckInfo::Load(QIODevice *f)
{
	if(InfoLight.Load(f)==false)
		return false;
	if(InfoFocus.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckInfo::Save(QIODevice *f)
{
	if(InfoLight.Save(f)==false)
		return false;
	if(InfoFocus.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

