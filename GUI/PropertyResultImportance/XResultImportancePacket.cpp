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


#include "XResultImportancePacket.h"
#include "XGeneralFunc.h"
#include<QBuffer>
#include "XResultImportance.h"

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

	AlgorithmInPageRoot	*PData=ABase->GetPageData(localPage);
	if(PData!=NULL){
		CmdMakeResultImportanceList	Cmd(GetLayersBase());
		Cmd.ResultImportanceInfo = &ResultImportanceInfo;
		PData->TransmitDirectly(&Cmd);
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
	AlgorithmInPageRoot	*PData=ABase->GetPageData(localPage);
	if(PData!=NULL){
		AlgorithmItemRoot *item=PData->SearchIDItem(ItemID);
		if(item!=NULL){
			ResultImportanceItem	*MItem=static_cast<ResultImportanceItem *>(item);
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

	AlgorithmInPageRoot	*PData=ABase->GetPageData(localPage);
	if(PData!=NULL){
		CmdSelectResultImportance	Cmd(GetLayersBase());
		Cmd.ImportanceLevels = &ImportanceLevels;
		PData->TransmitDirectly(&Cmd);
	}
}