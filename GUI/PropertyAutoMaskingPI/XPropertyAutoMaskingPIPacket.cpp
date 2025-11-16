/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoMaskingPI\XPropertyAutoMaskingPIPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
	AutoMaskingPIInPage	*M=dynamic_cast<AutoMaskingPIInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);
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
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(L->GetPageData(localPage));
	if(PData==NULL)
		return;
	AlgorithmItemPI		*Item=dynamic_cast<AlgorithmItemPI *>(PData->SearchIDItem(ItemID));
	if(Item==NULL)
		return;
	AutoMaskingPIItem	*M=dynamic_cast<AutoMaskingPIItem *>(Item);
	if(M==NULL)
		return;

	M->GetThresholdW()->Effective=Effective;
	M->GetThresholdW()->SelAreaID=LimitedLib;
}

bool	AutoMaskingPIListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,Effective)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}
bool	AutoMaskingPIListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,Effective)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
AutoMaskingPIListForPacket	&AutoMaskingPIListForPacket::operator=(AutoMaskingPIListForPacket &src)
{
	ItemID	=src.ItemID;
	Page	=src.Page;
	x1		=src.x1;
	y1		=src.y1;
	x2		=src.x2;
	y2		=src.y2;
	Effective	=src.Effective;
	LimitedLib	=src.LimitedLib;
	return *this;
}


bool	AutoMaskingPIListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AutoMaskingPIListForPacket *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
bool	AutoMaskingPIListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		AutoMaskingPIListForPacket	*c=new AutoMaskingPIListForPacket();
		if(c->Load(f)==false)
			return false;
	}
	return true;
}

AutoMaskingPIListForPacketPack	&AutoMaskingPIListForPacketPack::operator=(AutoMaskingPIListForPacketPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
AutoMaskingPIListForPacketPack	&AutoMaskingPIListForPacketPack::operator+=(AutoMaskingPIListForPacketPack &src)
{
	for(AutoMaskingPIListForPacket *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		AutoMaskingPIListForPacket *d=new AutoMaskingPIListForPacket();
		*d=*c;
		AppendList(d);
	}
	return *this;
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
		AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AutoMaskingPIBase->GetPageData(localPage));
		if(PData==NULL)
			continue;
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			AutoMaskingPIItem	*MItem=dynamic_cast<AutoMaskingPIItem *>(item);
			if(MItem!=NULL && ((EffectiveMode==true && MItem->GetThresholdR()->Effective==true) || (IneffectiveMode==true && MItem->GetThresholdR()->Effective==false))){
				AutoMaskingPIListForPacket	*L=new AutoMaskingPIListForPacket();
				L->Page=PBase->GetGlobalPageFromLocal(localPage);
				L->Effective=MItem->GetThresholdR()->Effective;
				int x1 ,y1 ,x2 ,y2;
				MItem->GetXY(x1 ,y1 ,x2 ,y2);
				L->ItemID=MItem->GetID();
				L->x1=x1;
				L->y1=y1;
				L->x2=x2;
				L->y2=y2;
				L->LimitedLib=*((AlgorithmLibraryListContainer *)&MItem->GetThresholdR()->SelAreaID);
				MaskInfo.AppendList(L);				
			}
		}
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
	AlgorithmInPagePI	*MaskPIPage=dynamic_cast<AlgorithmInPagePI *>(AutoMaskingBase->GetPageData(localPage));
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
