/*
 * Copyright (C) 2023
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

#include "PropertyAlignmentShiftRotationForm.h"
#include "XGeneralFunc.h"
#include "SelectLibFolderDialog.h"
#include "XPacketAlignmentShiftRotation.h"
#include "XDisplayImagePacket.h"
#include "XPropertyAlignmentShiftRotationPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==============================================================================
GUICmdAddAlignmentShiftRotation::GUICmdAddAlignmentShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddAlignmentShiftRotation::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddAlignmentShiftRotation::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddAlignmentShiftRotation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentShiftRotation	*SendBack=GetSendBack(GUICmdSendAlignmentShiftRotation,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageRoot	*AP=AlignBase->GetPageData(localPage);
	if(AP==NULL)
		return;

	AddAlignmentShiftRotationPointPacket	DPacket(GetLayersBase());
	DPacket.LibID		=LibID;
	DPacket.Area		=Area;
	AP->TransmitDirectly(&DPacket);

	SendBack->ItemID		=DPacket.RetItemID;
	
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentShiftRotation::GUICmdSendAlignmentShiftRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlignmentShiftRotation::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;

	return true;
}
bool	GUICmdSendAlignmentShiftRotation::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;

	return true;
}

	
GUICmdReqModifyAlignmentShiftRotation::GUICmdReqModifyAlignmentShiftRotation(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqModifyAlignmentShiftRotation::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqModifyAlignmentShiftRotation::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqModifyAlignmentShiftRotation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================

GUICmdReqAlignmentShiftRotationItemList::GUICmdReqAlignmentShiftRotationItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqAlignmentShiftRotationItemList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	return true;
}

bool	GUICmdReqAlignmentShiftRotationItemList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	return true;
}

void	GUICmdReqAlignmentShiftRotationItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentShiftRotationItemList	*SendBack=GetSendBack(GUICmdSendAlignmentShiftRotationItemList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageInOnePhase	*Ph=AlignBase->GetPageDataPhase(Phase);
	if(Ph==NULL)
		return;
	AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
	if(AP==NULL)
		return;

	CmdReqAlignmentShiftRotationItemtPack	DPacket(GetLayersBase());
	DPacket.Items		=&SendBack->ItemList;
	AP->TransmitDirectly(&DPacket);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentShiftRotationItemList::GUICmdSendAlignmentShiftRotationItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAlignmentShiftRotationItemList::Load(QIODevice *f)
{
	if(ItemList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAlignmentShiftRotationItemList::Save(QIODevice *f)
{
	if(ItemList.Save(f)==false)
		return false;
	return true;
}

//==============================================================================
GUICmdReqAlignmentShiftRotationItemAngleList::GUICmdReqAlignmentShiftRotationItemAngleList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqAlignmentShiftRotationItemAngleList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	return true;
}
bool	GUICmdReqAlignmentShiftRotationItemAngleList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	return true;
}
void	GUICmdReqAlignmentShiftRotationItemAngleList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignmentShiftRotationItemAngleList	*SendBack=GetSendBack(GUICmdSendAlignmentShiftRotationItemAngleList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPageInOnePhase	*Ph=AlignBase->GetPageDataPhase(Phase);
	if(Ph==NULL)
		return;
	AlgorithmInPageRoot	*AP=Ph->GetPageData(localPage);
	if(AP==NULL)
		return;

	CmdReqAlignmentShiftRotationItemAngleList	DPacket(GetLayersBase());
	DPacket.ItemID=ItemID;
	AP->TransmitDirectly(&DPacket);
	SendBack->AngleList=DPacket.AngleList;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlignmentShiftRotationItemAngleList::GUICmdSendAlignmentShiftRotationItemAngleList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAlignmentShiftRotationItemAngleList::Load(QIODevice *f)
{
	if(AngleList.Load(f)==false)	return false;
	return true;
}
bool	GUICmdSendAlignmentShiftRotationItemAngleList::Save(QIODevice *f)
{
	if(AngleList.Save(f)==false)	return false;
	return true;
}
