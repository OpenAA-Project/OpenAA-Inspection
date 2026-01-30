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

#include "XGeneralFunc.h"
#include "XPropertyRepeatControlPacket.h"
#include "XDataInLayer.h"

GUICmdSendAddManualRepeatControl::GUICmdSendAddManualRepeatControl(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualRepeatControl::Load(QIODevice *f)
{
	if(::Load(f,RepeatCount		)==false)	return false;
	if(::Load(f,MeshSize		)==false)	return false;
	if(::Load(f,SequenceOffset	)==false)	return false;
	if(::Load(f,GatherAllPhase	)==false)	return false;
	if(Area.Load(f)==false)	return false;
	return true;
}
bool	GUICmdSendAddManualRepeatControl::Save(QIODevice *f)
{
	if(::Save(f,RepeatCount		)==false)	return false;
	if(::Save(f,MeshSize		)==false)	return false;
	if(::Save(f,SequenceOffset	)==false)	return false;
	if(::Save(f,GatherAllPhase	)==false)	return false;
	if(Area.Save(f)==false)	return false;
	return true;
}

void	GUICmdSendAddManualRepeatControl::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RepeatControlBase *RBBase=(RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
	if(RBBase!=NULL){
		RepeatControlInPage	*PData=dynamic_cast<RepeatControlInPage	*>(RBBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddRepeatControlItemPacket	Cmd(GetLayersBase());
			Cmd.RepeatCount		=RepeatCount	;
			Cmd.MeshSize		=MeshSize		;
			Cmd.SequenceOffset	=SequenceOffset	;
			Cmd.GatherAllPhase	=GatherAllPhase	;
			Cmd.Area			=Area			;
			PData->TransmitDirectly(&Cmd);
		}
	}
}

GUICmdSendModifyRepeatControl::GUICmdSendModifyRepeatControl(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendModifyRepeatControl::Load(QIODevice *f)
{
	if(Index.Load(f)==false)	return false;
	if(::Load(f,RepeatCount		)==false)	return false;
	if(::Load(f,MeshSize		)==false)	return false;
	if(::Load(f,SequenceOffset	)==false)	return false;
	if(::Load(f,GatherAllPhase	)==false)	return false;
	return true;
}
bool	GUICmdSendModifyRepeatControl::Save(QIODevice *f)
{
	if(Index.Save(f)==false)	return false;
	if(::Save(f,RepeatCount		)==false)	return false;
	if(::Save(f,MeshSize		)==false)	return false;
	if(::Save(f,SequenceOffset	)==false)	return false;
	if(::Save(f,GatherAllPhase	)==false)	return false;
	return true;
}

void	GUICmdSendModifyRepeatControl::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	RepeatControlBase *RBBase=(RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(Index.Data.Phase);
		if(Ph!=NULL){
			RepeatControlInPage	*PData=dynamic_cast<RepeatControlInPage	*>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				CmdModifyRepeatControlItemPacket	Cmd(GetLayersBase());
				Cmd.RepeatCount		=RepeatCount	;
				Cmd.MeshSize		=MeshSize		;
				Cmd.SequenceOffset	=SequenceOffset	;
				Cmd.GatherAllPhase	=GatherAllPhase	;
				Cmd.ItemID			=Index.Data.ItemID	;
				PData->TransmitDirectly(&Cmd);
			}
		}
	}
}
	
//=================================================================

GUICmdReqRepeatControlInfoList::GUICmdReqRepeatControlInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRepeatControlInfoList::Load(QIODevice *f)
{
	if(::Load(f,Phase		)==false)	return false;
	return true;
}
bool	GUICmdReqRepeatControlInfoList::Save(QIODevice *f)
{
	if(::Save(f,Phase		)==false)	return false;
	return true;
}
void	GUICmdReqRepeatControlInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckRepeatControlInfoList	*SendBack=GetSendBack(GUICmdAckRepeatControlInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	RepeatControlBase *RBBase=(RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			RepeatControlInPage	*PData=dynamic_cast<RepeatControlInPage	*>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				CmdReqRepeatControlInfoList	Cmd(GetLayersBase());
				PData->TransmitDirectly(&Cmd);
				SendBack->RepeatControlInfos=Cmd.RepeatControlInfos;
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckRepeatControlInfoList::GUICmdAckRepeatControlInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckRepeatControlInfoList::Load(QIODevice *f)
{
	if(RepeatControlInfos.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckRepeatControlInfoList::Save(QIODevice *f)
{
	if(RepeatControlInfos.Save(f)==false)	return false;
	return true;
}

//=================================================================

GUICmdCreateWholeRepeatControl::GUICmdCreateWholeRepeatControl(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCreateWholeRepeatControl::Load(QIODevice *f)
{
	if(::Load(f,Phase		)==false)	return false;
	if(::Load(f,RepeatCount	)==false)	return false;
	return true;
}
bool	GUICmdCreateWholeRepeatControl::Save(QIODevice *f)
{
	if(::Save(f,Phase		)==false)	return false;
	if(::Save(f,RepeatCount	)==false)	return false;
	return true;
}

void	GUICmdCreateWholeRepeatControl::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	RepeatControlBase *RBBase=(RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
	if(RBBase!=NULL){
		AlgorithmInPageInOnePhase	*Ph=RBBase->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			RepeatControlInPage	*PData=dynamic_cast<RepeatControlInPage	*>(Ph->GetPageData(localPage));
			if(PData!=NULL){
				CmdCreateWholeRepeatControl	Cmd(GetLayersBase());
				Cmd.RepeatCount		=RepeatCount	;
				PData->TransmitDirectly(&Cmd);
			}
		}
	}
}