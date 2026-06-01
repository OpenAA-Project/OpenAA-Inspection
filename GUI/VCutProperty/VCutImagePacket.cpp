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


#include "VCutImagePacket.h"
#include "XGeneralFunc.h"
#include<QBuffer>


//===========================================================================

GUICmdAddVCutInspectionArea::GUICmdAddVCutInspectionArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Vector=NULL;
}
bool	GUICmdAddVCutInspectionArea::Load(QIODevice *f)
{
	int	VectorId;
	if(::Load(f,VectorId)==false){
		return false;
	}
	if(Vector!=NULL){
		delete	Vector;
	}
	Vector=VectorLineBase::Create(VectorId);

	if(Vector->Load(f)==false){
		return false;
	}
	if(::Load(f,ThresholdShift)==false)
		return false;
	if(::Load(f,ThresholdLevel)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdAddVCutInspectionArea::Save(QIODevice *f)
{
	int	VectorId=Vector->GetID();
	if(::Save(f,VectorId)==false){
		return false;
	}

	if(Vector->Save(f)==false){
		return false;
	}
	if(::Save(f,ThresholdShift)==false)
		return false;
	if(::Save(f,ThresholdLevel)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdAddVCutInspectionArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"PCB" ,/**/"VCutInspection");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(localPage);

	if(PData==NULL)
		return;
	AddVCutInspectionAreaPacket	Cmd(this);
	Cmd.Vector	=Vector;
	Cmd.ThresholdShift	=ThresholdShift;
	Cmd.ThresholdLevel	=ThresholdLevel;
	Cmd.ThresholdLength	=ThresholdLength;
	Cmd.LibID			=LibID;

	PData->TransmitDirectly(&Cmd);
}

//===========================================================================

GUICmdReqVCutInspectionList::GUICmdReqVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqVCutInspectionList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendVCutInspectionList	*SendBack=GetSendBack(GUICmdSendVCutInspectionList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeVCutList(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
//===========================================================================
GUICmdSendVCutInspectionList::GUICmdSendVCutInspectionList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendVCutInspectionList::Load(QIODevice *f)
{
	if(VCutInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendVCutInspectionList::Save(QIODevice *f)
{
	if(VCutInfo.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendVCutInspectionList::MakeVCutList(int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"PCB" ,/**/"VCutInspection");
	if(ABase==NULL)
		return;
	VCutInfo.RemoveAll();
	AlgorithmInPageRoot	*PData=ABase->GetPageDataPhase(GetLayersBase()->GetCurrentPhase())->GetPageData(LocalPage);
	if(PData!=NULL){
		CmdMakeVCutInspectionList	Cmd(GetLayersBase());
		Cmd.VCutInfo = &VCutInfo;
		PData->TransmitDirectly(&Cmd);
	}
}
void	GUICmdSendVCutInspectionList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{}