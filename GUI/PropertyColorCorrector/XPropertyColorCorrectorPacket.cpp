/*
 * Copyright (C) 2025
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

#include "XPropertyColorCorrectorPacket.h"
#include "XColorCorrector.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdSendAddManualColorCorrector::GUICmdSendAddManualColorCorrector(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualColorCorrector::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;

	int32	d;
	if(::Load(f,d)==false)
		return false;
	VType=(ColorCorrectorType)d;

	return true;
}
bool	GUICmdSendAddManualColorCorrector::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;

	int32	d=(int32)VType;
	if(::Save(f,d)==false)
		return false;

	return true;
}

void	GUICmdSendAddManualColorCorrector::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageRoot	*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdAddByteColorCorrectorItemPacket	Cmd(GetLayersBase());
			Cmd.Buff		=BItem;
			Cmd.Area		=Area;
			Cmd.VType		=VType;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}




GUICmdReqGridList::GUICmdReqGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqGridList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	int32	d;
	if(::Load(f,d)==false)	return false;
	VType=(ColorCorrectorType)d;
	return true;
}
bool	GUICmdReqGridList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	int32	d=(int32)VType;
	if(::Save(f,d)==false)	return false;
	return true;
}
void	GUICmdReqGridList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckGridList	*SendBack=GetSendBack(GUICmdAckGridList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*PData=Ph->GetPageData(localPage);
			if(PData!=NULL){
				CmdReqGridList	Cmd(GetLayersBase());
				Cmd.VType = VType;
				Cmd.ListData = &SendBack->ListData;
				PData->TransmitDirectly(&Cmd);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckGridList::GUICmdAckGridList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckGridList::Load(QIODevice *f)
{
	if(ListData.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckGridList::Save(QIODevice *f)
{
	if(ListData.Save(f)==false)	return false;
	return true;
}

//==============================================================================================
GUICmdReqColorCorrectorItemData::GUICmdReqColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqColorCorrectorItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	GUICmdReqColorCorrectorItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	return true;
}
void	GUICmdReqColorCorrectorItemData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorCorrectorItemData	*SendBack=GetSendBack(GUICmdAckColorCorrectorItemData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*PData=Ph->GetPageData(localPage);
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				ColorCorrectorThresholdBase	*RThr=static_cast<ColorCorrectorThresholdBase *>(a->GetThresholdBaseWritable(GetLayersBase()));
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				RThr->Save(&Buff);
				SendBack->Area		=a->GetArea();
				SendBack->BItem		=Buff.buffer();
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorCorrectorItemData::GUICmdAckColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckColorCorrectorItemData::Load(QIODevice *f)
{
	if(::Load(f,BItem	)==false)	return false;
	if(Area.Load(f)==false)			return false;
	return true;
}
bool	GUICmdAckColorCorrectorItemData::Save(QIODevice *f)
{
	if(::Save(f,BItem	)==false)	return false;
	if(Area.Save(f)==false)			return false;
	return true;
}

	
GUICmdSetColorCorrectorItemData::GUICmdSetColorCorrectorItemData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetColorCorrectorItemData::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,BItem	)==false)	return false;
	return true;
}
bool	GUICmdSetColorCorrectorItemData::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,BItem	)==false)	return false;
	return true;
}
void	GUICmdSetColorCorrectorItemData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*PData=Ph->GetPageData(localPage);
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				ColorCorrectorThresholdBase	*WThr=static_cast<ColorCorrectorThresholdBase *>(a->GetThresholdBaseWritable(GetLayersBase()));
				QBuffer	Buff(&BItem);
				Buff.open(QIODevice::ReadWrite);
				WThr->Load(&Buff);
			}
		}
	}
}
GUICmdDeleteColorCorrectorItem::GUICmdDeleteColorCorrectorItem(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdDeleteColorCorrectorItem::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}
bool	GUICmdDeleteColorCorrectorItem::Save(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	return true;
}

void	GUICmdDeleteColorCorrectorItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorCorrector");
	if(BBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=BBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			AlgorithmInPageRoot	*PData=Ph->GetPageData(localPage);
			if(PData!=NULL){
				AlgorithmItemRoot *a=PData->SearchIDItem(ItemID);
				//PData->RemoveItem(a);
				AlgorithmItemPointerListContainer	AList;
				AList.Add(a);
				PData->RemoveItems(AList);
			}
		}
	}
}