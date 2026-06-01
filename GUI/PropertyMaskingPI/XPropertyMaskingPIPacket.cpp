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

#include "PropertyMaskingPIResource.h"

#include "XPropertyMaskingPIPacket.h"
#include "XGeneralFunc.h"
#include "XMaskingPI.h"

GUICmdAddMaskingPIArea::GUICmdAddMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddMaskingPIArea::Load(QIODevice *f)
{
	if(MaskArea.Load(f)==false)
		return false;
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddMaskingPIArea::Save(QIODevice *f)
{
	if(MaskArea.Save(f)==false)
		return false;
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddMaskingPIArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddMaskingPIAreaPacket	Cmd(this);
	Cmd.Area=MaskArea;
	Cmd.Effective=Effective;
	Cmd.LimitedLib=LimitedLib;
	PData->TransmitDirectly(&Cmd);
}

GUICmdChangeMaskingPIAttr::GUICmdChangeMaskingPIAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdChangeMaskingPIAttr::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdChangeMaskingPIAttr::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

void	GUICmdChangeMaskingPIAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(L==NULL)
		return;
	AlgorithmInPageRoot	*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AlgorithmItemRoot	*Item=PData->SearchIDItem(ItemID);
	if(Item==NULL)
		return;
	MaskingPIItem	*M=static_cast<MaskingPIItem *>(Item);
	if(M==NULL)
		return;

	M->GetThresholdW()->Effective=Effective;
	M->GetThresholdW()->SelAreaID=LimitedLib;
}

//==============================================================================================

GUICmdReqMaskPIList::GUICmdReqMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IneffectiveMode	=false;
	EffectiveMode	=false;
}

bool	GUICmdReqMaskPIList::Load(QIODevice *f)
{
	if(::Load(f,IneffectiveMode)==false)
		return false;
	if(::Load(f,EffectiveMode)==false)
		return false;
	return true;
}
bool	GUICmdReqMaskPIList::Save(QIODevice *f)
{
	if(::Save(f,IneffectiveMode)==false)
		return false;
	if(::Save(f,EffectiveMode)==false)
		return false;
	return true;
}

void	GUICmdReqMaskPIList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendMaskPIList	*SendBack=GetSendBack(GUICmdSendMaskPIList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeMaskList(EffectiveMode,IneffectiveMode,localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendMaskPIList::GUICmdSendMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendMaskPIList::MakeMaskList(bool EffectiveMode,bool IneffectiveMode,int localPage ,LayersBase *PBase)
{
	AlgorithmBase	*MaskingPIBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(MaskingPIBase==NULL)
		return;
	MaskInfo.RemoveAll();

	AlgorithmInPageRoot	*PData=MaskingPIBase->GetPageData(localPage);
	if(PData!=NULL){
		CmdMakeMaskPIList	Cmd(GetLayersBase());
		Cmd.EffectiveMode = EffectiveMode;
		Cmd.IneffectiveMode = IneffectiveMode;
		Cmd.MaskInfo = &MaskInfo;
		PData->TransmitDirectly(&Cmd);
	}
}
bool	GUICmdSendMaskPIList::Load(QIODevice *f)
{
	if(MaskInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendMaskPIList::Save(QIODevice *f)
{
	if(MaskInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendMaskPIList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================
GUICmdGenerateMaskPIInSameColor::GUICmdGenerateMaskPIInSameColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGenerateMaskPIInSameColor::Load(QIODevice *f)
{
	if(::Load(f,RPickupL)==false)
		return false;
	if(::Load(f,RPickupH)==false)
		return false;
	if(::Load(f,GPickupL)==false)
		return false;
	if(::Load(f,GPickupH)==false)
		return false;
	if(::Load(f,BPickupL)==false)
		return false;
	if(::Load(f,BPickupH)==false)
		return false;
	if(::Load(f,Effective)==false)
		return false;
	return true;
}
bool	GUICmdGenerateMaskPIInSameColor::Save(QIODevice *f)
{
	if(::Save(f,RPickupL)==false)
		return false;
	if(::Save(f,RPickupH)==false)
		return false;
	if(::Save(f,GPickupL)==false)
		return false;
	if(::Save(f,GPickupH)==false)
		return false;
	if(::Save(f,BPickupL)==false)
		return false;
	if(::Save(f,BPickupH)==false)
		return false;
	if(::Save(f,Effective)==false)
		return false;
	return true;
}
void	GUICmdGenerateMaskPIInSameColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*MaskingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(MaskingBase==NULL)
		return;
	AlgorithmInPageRoot	*MaskPIPage=MaskingBase->GetPageData(localPage);
	if(MaskPIPage==NULL)
		return;

	CmdGenerateMaskPIInSameColor	Cmd(this);
	Cmd.RPickupL=RPickupL;
	Cmd.RPickupH=RPickupH;
	Cmd.GPickupL=GPickupL;
	Cmd.GPickupH=GPickupH;
	Cmd.BPickupL=BPickupL;
	Cmd.BPickupH=BPickupH;
	Cmd.Effective=Effective;
	MaskPIPage->TransmitDirectly(&Cmd);
}

//========================================================

GUICmdReqRemoveMaskPI::GUICmdReqRemoveMaskPI(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdReqRemoveMaskPI::Load(QIODevice *f)
{
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,Phase	)==false)	return false;
	return true;
}
bool	GUICmdReqRemoveMaskPI::Save(QIODevice *f)
{
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,Phase	)==false)	return false;
	return true;
}

void	GUICmdReqRemoveMaskPI::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*MaskingBase = GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if (MaskingBase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=MaskingBase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*MaskPage = Ah->GetPageData(localPage);
			if(MaskPage!=NULL) {
				CmdRemoveMaskPIItem	Cmd(GetLayersBase());
				Cmd.ItemID=ItemID;
				MaskPage->TransmitDirectly(&Cmd);
			}
		}
	}
	SendAck(localPage);
}
	