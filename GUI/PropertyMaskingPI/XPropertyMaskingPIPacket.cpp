#include "PropertyMaskingPIResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMaskingPI\XPropertyMaskingPIPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
	MaskingPIInPage	*M=dynamic_cast<MaskingPIInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);
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
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(L->GetPageData(localPage));
	if(PData==NULL)
		return;
	AlgorithmItemPI		*Item=dynamic_cast<AlgorithmItemPI *>(PData->SearchIDItem(ItemID));
	if(Item==NULL)
		return;
	MaskingPIItem	*M=dynamic_cast<MaskingPIItem *>(Item);
	if(M==NULL)
		return;

	M->GetThresholdW()->Effective=Effective;
	M->GetThresholdW()->SelAreaID=LimitedLib;
}

bool	MaskingPIListForPacket::Save(QIODevice *f)
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
bool	MaskingPIListForPacket::Load(QIODevice *f)
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
MaskingPIListForPacket	&MaskingPIListForPacket::operator=(MaskingPIListForPacket &src)
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


bool	MaskingPIListForPacketPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(MaskingPIListForPacket *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
bool	MaskingPIListForPacketPack::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		MaskingPIListForPacket	*c=new MaskingPIListForPacket();
		if(c->Load(f)==false)
			return false;
	}
	return true;
}

MaskingPIListForPacketPack	&MaskingPIListForPacketPack::operator=(MaskingPIListForPacketPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
MaskingPIListForPacketPack	&MaskingPIListForPacketPack::operator+=(MaskingPIListForPacketPack &src)
{
	for(MaskingPIListForPacket *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		MaskingPIListForPacket *d=new MaskingPIListForPacket();
		*d=*c;
		AppendList(d);
	}
	return *this;
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
	//int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GetGlobalPage());
	AlgorithmBase	*MaskingPIBase=PBase->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(MaskingPIBase==NULL)
		return;
	MaskInfo.RemoveAll();

	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(MaskingPIBase->GetPageData(localPage));
	if(PData!=NULL){
		for(AlgorithmItemPI *item=PData->GetFirstData();item!=NULL;item=item->GetNext()){
			MaskingPIItem	*MItem=dynamic_cast<MaskingPIItem *>(item);
			if(MItem!=NULL && ((EffectiveMode==true && MItem->GetThresholdR()->Effective==true) || (IneffectiveMode==true && MItem->GetThresholdR()->Effective==false))){
				MaskingPIListForPacket	*L=new MaskingPIListForPacket();
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
	AlgorithmInPagePI	*MaskPIPage=dynamic_cast<AlgorithmInPagePI *>(MaskingBase->GetPageData(localPage));
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
			AlgorithmInPagePI	*MaskPage = dynamic_cast<AlgorithmInPagePI*>(Ah->GetPageData(localPage));
			if(MaskPage!=NULL) {
				CmdRemoveMaskPIItem	Cmd(GetLayersBase());
				Cmd.ItemID=ItemID;
				MaskPage->TransmitDirectly(&Cmd);
			}
		}
	}
	SendAck(localPage);
}
	
