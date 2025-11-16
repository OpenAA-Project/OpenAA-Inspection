#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\XPropertyDynamicMaskingPIPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyDynamicMaskingPIPacket.h"
#include "XGeneralFunc.h"
#include "XDynamicMaskingPI.h"

GUICmdAddDynamicMaskingPIArea::GUICmdAddDynamicMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AbsLR=AbsHR=0;
	AbsLG=AbsHG=0;
	AbsLB=AbsHB=0;
	OpeType=DynamicMaskingPIThreshold::_PickupMask;
	DrawColR=0;
	DrawColG=0;
	DrawColB=0;
	MinSize	=0;

	AbsLR2=AbsHR2=0;
	AbsLG2=AbsHG2=0;
	AbsLB2=AbsHB2=0;
	DrawColR2=0;
	DrawColG2=0;
	DrawColB2=0;
	Layer	=0;
	ParentItemID	=0;
}

bool	GUICmdAddDynamicMaskingPIArea::Load(QIODevice *f)
{
	if(MaskArea.Load(f)==false)
		return false;
	if(::Load(f,AbsLR)==false)
		return false;
	if(::Load(f,AbsHR)==false)
		return false;
	if(::Load(f,AbsLG)==false)
		return false;
	if(::Load(f,AbsHG)==false)
		return false;
	if(::Load(f,AbsLB)==false)
		return false;
	if(::Load(f,AbsHB)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;	
	if(::Load(f,BlockWidth)==false)
		return false;
	if(::Load(f,BlockHeight)==false)
		return false;	

	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	OpeType=(DynamicMaskingPIThreshold::OperationType)D;

	if(::Load(f,DrawColR)==false)
		return false;
	if(::Load(f,DrawColG)==false)
		return false;
	if(::Load(f,DrawColB)==false)
		return false;

	if(::Load(f,AbsHR2)==false)
		return false;
	if(::Load(f,AbsLG2)==false)
		return false;
	if(::Load(f,AbsHG2)==false)
		return false;
	if(::Load(f,AbsLB2)==false)
		return false;
	if(::Load(f,AbsHB2)==false)
		return false;
	if(::Load(f,EnlargeDot2)==false)
		return false;
	if(::Load(f,EnsmallDot2)==false)
		return false;	
	if(::Load(f,DrawColR2)==false)
		return false;
	if(::Load(f,DrawColG2)==false)
		return false;
	if(::Load(f,DrawColB2)==false)
		return false;
	if(::Load(f,Mergin)==false)
		return false;
	if(MaskingColor.Load(f)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,ParentItemID)==false)
		return false;

	if(AdaptedPickupLayers.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAddDynamicMaskingPIArea::Save(QIODevice *f)
{
	if(MaskArea.Save(f)==false)
		return false;

	if(::Save(f,AbsLR)==false)
		return false;
	if(::Save(f,AbsHR)==false)
		return false;
	if(::Save(f,AbsLG)==false)
		return false;
	if(::Save(f,AbsHG)==false)
		return false;
	if(::Save(f,AbsLB)==false)
		return false;
	if(::Save(f,AbsHB)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	if(::Save(f,BlockWidth)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;	

	BYTE	D=(BYTE)OpeType;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,DrawColR)==false)
		return false;
	if(::Save(f,DrawColG)==false)
		return false;
	if(::Save(f,DrawColB)==false)
		return false;

	if(::Save(f,AbsLR2)==false)
		return false;
	if(::Save(f,AbsHR2)==false)
		return false;
	if(::Save(f,AbsLG2)==false)
		return false;
	if(::Save(f,AbsHG2)==false)
		return false;
	if(::Save(f,AbsLB2)==false)
		return false;
	if(::Save(f,AbsHB2)==false)
		return false;
	if(::Save(f,EnlargeDot2)==false)
		return false;
	if(::Save(f,EnsmallDot2)==false)
		return false;
	if(::Save(f,DrawColR2)==false)
		return false;
	if(::Save(f,DrawColG2)==false)
		return false;
	if(::Save(f,DrawColB2)==false)
		return false;
	if(::Save(f,Mergin)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,ParentItemID)==false)
		return false;

	if(AdaptedPickupLayers.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAddDynamicMaskingPIArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DynamicMaskingPI");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddDynamicMaskingPIAreaPacket	Cmd(this);
	Cmd.MaskArea	=MaskArea;

	Cmd.AbsLR		=AbsLR;
	Cmd.AbsHR		=AbsHR;
	Cmd.AbsLG		=AbsLG;
	Cmd.AbsHG		=AbsHG;
	Cmd.AbsLB		=AbsLB;
	Cmd.AbsHB		=AbsHB;
	Cmd.EnlargeDot	=EnlargeDot;
	Cmd.EnsmallDot	=EnsmallDot;
	Cmd.BlockWidth	=BlockWidth;
	Cmd.BlockHeight	=BlockHeight;
	Cmd.OpeType		=OpeType;
	Cmd.DrawColR	=DrawColR;
	Cmd.DrawColG	=DrawColG;
	Cmd.DrawColB	=DrawColB;
	Cmd.MinSize		=MinSize;

	Cmd.AbsLR2		=AbsLR2;
	Cmd.AbsHR2		=AbsHR2;
	Cmd.AbsLG2		=AbsLG2;
	Cmd.AbsHG2		=AbsHG2;
	Cmd.AbsLB2		=AbsLB2;
	Cmd.AbsHB2		=AbsHB2;
	Cmd.EnlargeDot2	=EnlargeDot2;
	Cmd.EnsmallDot2	=EnsmallDot2;
	Cmd.DrawColR2	=DrawColR2;
	Cmd.DrawColG2	=DrawColG2;
	Cmd.DrawColB2	=DrawColB2;
	Cmd.Mergin		=Mergin;
	Cmd.MaskingColor=MaskingColor;
	Cmd.Layer		=Layer;
	Cmd.ParentItemID=ParentItemID;
	Cmd.AdaptedPickupLayers	=AdaptedPickupLayers;

	DynamicMaskingPIInPage	*M=dynamic_cast<DynamicMaskingPIInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//========================================================================================

GUICmdModDynamicMaskingPIArea::GUICmdModDynamicMaskingPIArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AbsLR=AbsHR=0;
	AbsLG=AbsHG=0;
	AbsLB=AbsHB=0;
	OpeType=DynamicMaskingPIThreshold::_PickupMask;
	DrawColR=0;
	DrawColG=0;
	DrawColB=0;
	MinSize	=0;

	AbsLR2=AbsHR2=0;
	AbsLG2=AbsHG2=0;
	AbsLB2=AbsHB2=0;
	DrawColR2=0;
	DrawColG2=0;
	DrawColB2=0;
	Layer	=0;
}

bool	GUICmdModDynamicMaskingPIArea::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,AbsLR)==false)
		return false;
	if(::Load(f,AbsHR)==false)
		return false;
	if(::Load(f,AbsLG)==false)
		return false;
	if(::Load(f,AbsHG)==false)
		return false;
	if(::Load(f,AbsLB)==false)
		return false;
	if(::Load(f,AbsHB)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;	
	if(::Load(f,BlockWidth)==false)
		return false;
	if(::Load(f,BlockHeight)==false)
		return false;	

	BYTE	D;
	if(::Load(f,D)==false)
		return false;
	OpeType=(DynamicMaskingPIThreshold::OperationType)D;

	if(::Load(f,DrawColR)==false)
		return false;
	if(::Load(f,DrawColG)==false)
		return false;
	if(::Load(f,DrawColB)==false)
		return false;

	if(::Load(f,AbsHR2)==false)
		return false;
	if(::Load(f,AbsLG2)==false)
		return false;
	if(::Load(f,AbsHG2)==false)
		return false;
	if(::Load(f,AbsLB2)==false)
		return false;
	if(::Load(f,AbsHB2)==false)
		return false;
	if(::Load(f,EnlargeDot2)==false)
		return false;
	if(::Load(f,EnsmallDot2)==false)
		return false;	
	if(::Load(f,DrawColR2)==false)
		return false;
	if(::Load(f,DrawColG2)==false)
		return false;
	if(::Load(f,DrawColB2)==false)
		return false;
	if(::Load(f,Mergin)==false)
		return false;
	if(MaskingColor.Load(f)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(AdaptedPickupLayers.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdModDynamicMaskingPIArea::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;

	if(::Save(f,AbsLR)==false)
		return false;
	if(::Save(f,AbsHR)==false)
		return false;
	if(::Save(f,AbsLG)==false)
		return false;
	if(::Save(f,AbsHG)==false)
		return false;
	if(::Save(f,AbsLB)==false)
		return false;
	if(::Save(f,AbsHB)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	if(::Save(f,BlockWidth)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;	

	BYTE	D=(BYTE)OpeType;
	if(::Save(f,D)==false)
		return false;
	if(::Save(f,DrawColR)==false)
		return false;
	if(::Save(f,DrawColG)==false)
		return false;
	if(::Save(f,DrawColB)==false)
		return false;

	if(::Save(f,AbsLR2)==false)
		return false;
	if(::Save(f,AbsHR2)==false)
		return false;
	if(::Save(f,AbsLG2)==false)
		return false;
	if(::Save(f,AbsHG2)==false)
		return false;
	if(::Save(f,AbsLB2)==false)
		return false;
	if(::Save(f,AbsHB2)==false)
		return false;
	if(::Save(f,EnlargeDot2)==false)
		return false;
	if(::Save(f,EnsmallDot2)==false)
		return false;
	if(::Save(f,DrawColR2)==false)
		return false;
	if(::Save(f,DrawColG2)==false)
		return false;
	if(::Save(f,DrawColB2)==false)
		return false;
	if(::Save(f,Mergin)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(AdaptedPickupLayers.Save(f)==false)
		return false;
	return true;
}

void	GUICmdModDynamicMaskingPIArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DynamicMaskingPI");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	ModDynamicMaskingPIAreaPacket	Cmd(this);
	Cmd.ID	=ID;

	Cmd.AbsLR		=AbsLR;
	Cmd.AbsHR		=AbsHR;
	Cmd.AbsLG		=AbsLG;
	Cmd.AbsHG		=AbsHG;
	Cmd.AbsLB		=AbsLB;
	Cmd.AbsHB		=AbsHB;
	Cmd.EnlargeDot	=EnlargeDot;
	Cmd.EnsmallDot	=EnsmallDot;
	Cmd.BlockWidth	=BlockWidth;
	Cmd.BlockHeight	=BlockHeight;
	Cmd.OpeType		=OpeType;
	Cmd.DrawColR	=DrawColR;
	Cmd.DrawColG	=DrawColG;
	Cmd.DrawColB	=DrawColB;
	Cmd.MinSize		=MinSize;

	Cmd.AbsLR2		=AbsLR2;
	Cmd.AbsHR2		=AbsHR2;
	Cmd.AbsLG2		=AbsLG2;
	Cmd.AbsHG2		=AbsHG2;
	Cmd.AbsLB2		=AbsLB2;
	Cmd.AbsHB2		=AbsHB2;
	Cmd.EnlargeDot2	=EnlargeDot2;
	Cmd.EnsmallDot2	=EnsmallDot2;
	Cmd.DrawColR2	=DrawColR2;
	Cmd.DrawColG2	=DrawColG2;
	Cmd.DrawColB2	=DrawColB2;
	Cmd.Mergin		=Mergin;
	Cmd.MaskingColor=MaskingColor;
	Cmd.Layer		=Layer;
	Cmd.AdaptedPickupLayers	=AdaptedPickupLayers;

	DynamicMaskingPIInPage	*M=dynamic_cast<DynamicMaskingPIInPage *>(PData);
	if(M!=NULL)
		M->TransmitDirectly(&Cmd);

	SendAck(localPage);
}

//========================================================================================
GUICmdReqDMaskingPIAreaInfoList::GUICmdReqDMaskingPIAreaInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqDMaskingPIAreaInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDMaskingPIAreaInfoList	*SendBack=GetSendBack(GUICmdAckDMaskingPIAreaInfoList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"DynamicMaskingPI");
	if(L==NULL)
		return;
	CmdReqDMaskingPIAreaInfoList	Cmd(this);
	Cmd.List=&SendBack->Data;

	L->GetPageData(localPage)->TransmitDirectly(&Cmd);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckDMaskingPIAreaInfoList::GUICmdAckDMaskingPIAreaInfoList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckDMaskingPIAreaInfoList::Load(QIODevice *f)
{
	if(Data.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckDMaskingPIAreaInfoList::Save(QIODevice *f)
{
	if(Data.Save(f)==false)
		return false;
	return true;
}

void	GUICmdAckDMaskingPIAreaInfoList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

