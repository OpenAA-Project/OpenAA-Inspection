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


#include "PropertyAlignmentBlockPacket.h"
#include "XAlignmentBlock.h"
#include "XGeneralFunc.h"
#include "XAlignmentBlockCommon.h"
//#include "XGUI.h"

//=====================================================================================
GUICmdSendAddManualAlignmentBlock::GUICmdSendAddManualAlignmentBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualAlignmentBlock::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualAlignmentBlock::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualAlignmentBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
	if(BBase!=NULL){
		AlgorithmInPageRoot	*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdAddAlignmentBlockItemPacket	Cmd(this);
			Cmd.Area		=Area;
			Cmd.LibID		=LibID;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}


GUICmdAutoGenerateAlignmentBlock::GUICmdAutoGenerateAlignmentBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAutoGenerateAlignmentBlock::Load(QIODevice *f)
{	
	if(::Load(f,LibID)==false)
		return false;

	return true;
}
bool	GUICmdAutoGenerateAlignmentBlock::Save(QIODevice *f)
{	
	if(::Save(f,LibID)==false)
		return false;

	return true;
}

void	GUICmdAutoGenerateAlignmentBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
	if(BBase!=NULL){
		AlgorithmInPageRoot	*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdAutoGenerateAlignmentBlock	Cmd(this);
			Cmd.LibID	=LibID	;
			PData->TransmitDirectly(&Cmd);
		}
	}
}


//=============================================================================================


GUICmdReqAlignmentBlockItemList::GUICmdReqAlignmentBlockItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqAlignmentBlockItemList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentBlockItemList	*SendBack=GetSendBack(GUICmdAckAlignmentBlockItemList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->Items.RemoveAll();
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
	if(BBase!=NULL){
		AlgorithmInPageRoot	*PData=BBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdMakeAlignmentBlockItemList	Cmd(GetLayersBase());
			Cmd.Items = &SendBack->Items;
			PData->TransmitDirectly(&Cmd);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlignmentBlockItemList::GUICmdAckAlignmentBlockItemList(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAlignmentBlockItemList::Load(QIODevice *f)
{
	if(Items.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckAlignmentBlockItemList::Save(QIODevice *f)
{
	if(Items.Save(f)==false)	return false;
	return true;
}