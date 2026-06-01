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


#include "XPropertyAutoMaskingPIPacket.h"
#include "XGeneralFunc.h"
#include "XAutoMaskingPI.h"

GUICmdAddAutoMaskingPIArea::GUICmdAddAutoMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddAutoMaskingPIArea::Load(QIODevice *f)
{
	if(MaskArea.Load(f)==false)
		return false;
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddAutoMaskingPIArea::Save(QIODevice *f)
{
	if(MaskArea.Save(f)==false)
		return false;
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddAutoMaskingPIArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddAutoMaskingPIAreaPacket	Cmd(this);
	Cmd.Area=MaskArea;
	Cmd.Effective=Effective;
	Cmd.LimitedLib=LimitedLib;
	PData->TransmitDirectly(&Cmd);
}

GUICmdChangeAutoMaskingPIAttr::GUICmdChangeAutoMaskingPIAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdChangeAutoMaskingPIAttr::Load(QIODevice *f)
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
bool	GUICmdChangeAutoMaskingPIAttr::Save(QIODevice *f)
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

void	GUICmdChangeAutoMaskingPIAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(L==NULL)
		return;
	AlgorithmInPageRoot	*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AlgorithmItemRoot	*Item=PData->SearchIDItem(ItemID);
	if(Item==NULL)
		return;
	AutoMaskingPIItem	*M=static_cast<AutoMaskingPIItem *>(Item);

	M->GetThresholdW()->Effective=Effective;
	M->GetThresholdW()->SelAreaID=LimitedLib;
}

//==============================================================================================

GUICmdReqAutoMaskPIList::GUICmdReqAutoMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IneffectiveMode	=false;
	EffectiveMode	=false;
}

bool	GUICmdReqAutoMaskPIList::Load(QIODevice *f)
{
	if(::Load(f,IneffectiveMode)==false)
		return false;
	if(::Load(f,EffectiveMode)==false)
		return false;
	return true;
}
bool	GUICmdReqAutoMaskPIList::Save(QIODevice *f)
{
	if(::Save(f,IneffectiveMode)==false)
		return false;
	if(::Save(f,EffectiveMode)==false)
		return false;
	return true;
}

void	GUICmdReqAutoMaskPIList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAutoMaskPIList	*SendBack=GetSendBack(GUICmdSendAutoMaskPIList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeMaskList(EffectiveMode,IneffectiveMode,localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAutoMaskPIList::GUICmdSendAutoMaskPIList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAutoMaskPIList::MakeMaskList(bool EffectiveMode,bool IneffectiveMode,int localPage ,LayersBase *PBase)
{
	int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*AutoMaskingPIBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(AutoMaskingPIBase==NULL)
		return;
	MaskInfo.RemoveAll();
	for(int phase=0;phase<PBase->GetPhaseNumb();phase++){
		if(PBase->GetPhaseNumb()>1)
			PBase->TF_SetCurrentScanPhaseNumber(phase); // phase function
		AlgorithmInPageRoot	*PData=AutoMaskingPIBase->GetPageData(localPage);
		if(PData==NULL)
			continue;

		CmdSendAutoMaskPIList	Cmd(GetLayersBase());
		Cmd.IneffectiveMode	=IneffectiveMode;
		Cmd.EffectiveMode	=EffectiveMode	;
		Cmd.MaskInfo = &MaskInfo;
		PData->TransmitDirectly(&Cmd);

///////
	}
	if(PBase->GetPhaseNumb()>1)
		PBase->TF_SetCurrentScanPhaseNumber(0);
///////
}
bool	GUICmdSendAutoMaskPIList::Load(QIODevice *f)
{
	if(MaskInfo.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAutoMaskPIList::Save(QIODevice *f)
{
	if(MaskInfo.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAutoMaskPIList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//==============================================================================
GUICmdGenerateAutoMaskPIInSameColor::GUICmdGenerateAutoMaskPIInSameColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGenerateAutoMaskPIInSameColor::Load(QIODevice *f)
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
bool	GUICmdGenerateAutoMaskPIInSameColor::Save(QIODevice *f)
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
void	GUICmdGenerateAutoMaskPIInSameColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AutoMaskingBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(AutoMaskingBase==NULL)
		return;
	AlgorithmInPageRoot	*MaskPIPage=AutoMaskingBase->GetPageData(localPage);
	if(MaskPIPage==NULL)
		return;

	CmdGenerateAutoMaskPIInSameColor	Cmd(this);
	Cmd.RPickupL=RPickupL;
	Cmd.RPickupH=RPickupH;
	Cmd.GPickupL=GPickupL;
	Cmd.GPickupH=GPickupH;
	Cmd.BPickupL=BPickupL;
	Cmd.BPickupH=BPickupH;
	Cmd.Effective=Effective;
	MaskPIPage->TransmitDirectly(&Cmd);
}

//=============================================================================================================
bool	CmdSetAutoMaskingPIShowingState::Load(QIODevice *f)
{
	int	d;
	if(::Load(f,d)==false)
		return false;
	ModeShowingButton=(_ShowingButton)d;
	return true;
}
bool	CmdSetAutoMaskingPIShowingState::Save(QIODevice *f)
{
	int	d=(int)ModeShowingButton;
	if(::Save(f,d)==false)
		return false;
	return true;
}

GUICmdSetAutoMaskingPIShowingState::GUICmdSetAutoMaskingPIShowingState(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,State(Base)
{
}

bool	GUICmdSetAutoMaskingPIShowingState::Load(QIODevice *f)
{
	if(State.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetAutoMaskingPIShowingState::Save(QIODevice *f)
{
	if(State.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetAutoMaskingPIShowingState::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoMaskingPI" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&State);
	}
}