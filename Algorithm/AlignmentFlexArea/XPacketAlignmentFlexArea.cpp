/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentFlexArea\XPacketAlignmentFlexArea.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#define	_USE_MATH_DEFINES
#include "XPacketAlignmentFlexArea.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlignmentFlexArea.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool	AlignmentFlexAreaShiftList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CalcDone)==false)
		return false;
	if(::Save(f,ShiftX)==false)
		return false;
	if(::Save(f,ShiftY)==false)
		return false;
	if(::Save(f,MasterX)==false)
		return false;
	if(::Save(f,MasterY)==false)
		return false;
	return true;
}

bool	AlignmentFlexAreaShiftList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CalcDone)==false)
		return false;
	if(::Load(f,ShiftX)==false)
		return false;
	if(::Load(f,ShiftY)==false)
		return false;
	if(::Load(f,MasterX)==false)
		return false;
	if(::Load(f,MasterY)==false)
		return false;
	return true;
}


//==================================================================================

bool	ReqAlignmentFlexAreaAreaListPack::LayerExists(int page)
{
	for(ReqAlignmentFlexAreaAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GlobalPage==page)
			return true;
	}
	return false;
}

bool	ReqAlignmentFlexAreaAreaListPack::ExistsAreaID(int areaID)
{
	for(ReqAlignmentFlexAreaAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==areaID)
			return true;
	}
	return false;
}
bool	ReqAlignmentFlexAreaAreaListPack::Exists(int page ,int areaID)
{
	for(ReqAlignmentFlexAreaAreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GlobalPage==page && a->AreaID==areaID)
			return true;
	}
	return false;
}


//==================================================================================

SlaveCommReqAlignmentFlexAreaPoint::SlaveCommReqAlignmentFlexAreaPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
	AreaID	=0;
	Layer	=0;
}

bool	SlaveCommReqAlignmentFlexAreaPoint::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	SlaveCommReqAlignmentFlexAreaPoint::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	SlaveCommReqAlignmentFlexAreaPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckAlignmentFlexAreaPoint	*S
	=(SlaveCommAckAlignmentFlexAreaPoint *)((GetSendBackPacket()==NULL)?new SlaveCommAckAlignmentFlexAreaPoint(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			CmdReqAlignmentFlexAreaPointPacket	Cmd(GetLayersBase());
			Cmd.AreaID		=AreaID;
			Cmd.AreaName	=AreaName;
			Pg->TransmitDirectly(&Cmd);
			S->AlignmentFlexAreaPointData=Cmd.AlignmentFlexAreaPointData;
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}



SlaveCommAckAlignmentFlexAreaPoint::SlaveCommAckAlignmentFlexAreaPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommAckAlignmentFlexAreaPoint::Load(QIODevice *f)
{
	if(AlignmentFlexAreaPointData.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckAlignmentFlexAreaPoint::Save(QIODevice *f)
{
	if(AlignmentFlexAreaPointData.Save(f)==false)
		return false;
	return true;
}

//===================================================================================================
SlaveCommReqAlignmentFlexAreaShift::SlaveCommReqAlignmentFlexAreaShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
	Layer=0;
}
bool	SlaveCommReqAlignmentFlexAreaShift::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(ItemID.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqAlignmentFlexAreaShift::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(ItemID.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqAlignmentFlexAreaShift::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckAlignmentFlexAreaShift	*S
	=(SlaveCommAckAlignmentFlexAreaShift *)((GetSendBackPacket()==NULL)?new SlaveCommAckAlignmentFlexAreaShift(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			CmdReqAlignmentFlexAreaShiftPacket	Cmd(GetLayersBase());
			Cmd.ItemIDPoint		=&ItemID;
			Cmd.ShiftDataPoint	=&S->ShiftData;
			Pg->TransmitDirectly(&Cmd);
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckAlignmentFlexAreaShift::SlaveCommAckAlignmentFlexAreaShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName,typeid(this).name())
{
}
bool	SlaveCommAckAlignmentFlexAreaShift::Load(QIODevice *f)
{
	if(ShiftData.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckAlignmentFlexAreaShift::Save(QIODevice *f)
{
	if(ShiftData.Save(f)==false)
		return false;
	return true;
}

//================================================================================

LibraryEfectivity::LibraryEfectivity(void)
{
	LibID	=0;
	IncludedInMask	=false;
}

bool	LibraryEfectivity::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,IncludedInMask)==false)
		return false;
	return true;
}

bool	LibraryEfectivity::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,IncludedInMask)==false)
		return false;
	return true;
}


bool	LibraryEfectivityContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(LibraryEfectivity *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	LibraryEfectivityContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		LibraryEfectivity	*a=new LibraryEfectivity();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
bool	LibraryEfectivityContainer::IsIncluded(int LibID)
{
	for(LibraryEfectivity *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID){
			return a->IncludedInMask;
		}
	}
	return false;
}

//================================================================================
SlaveCommReqLibraryInMaskOfBlock::SlaveCommReqLibraryInMaskOfBlock(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqLibraryInMaskOfBlock::Load(QIODevice *f)
{
	if(UsedLibraries.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqLibraryInMaskOfBlock::Save(QIODevice *f)
{
	if(UsedLibraries.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqLibraryInMaskOfBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckLibraryInMaskOfBlock	*S
	=(SlaveCommAckLibraryInMaskOfBlock *)((GetSendBackPacket()==NULL)?new SlaveCommAckLibraryInMaskOfBlock(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		for(IntClass *a=UsedLibraries.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibrary *Lib=BBase->GetLibraryContainer()->CreateNew();
			AlgorithmLibraryLevelContainer	SrcLib(BBase);
			SrcLib.SetLibID(a->GetValue());
			SrcLib.Set(Lib);
			S->UsedLibraries.AppendList(new LibraryEfectivity(a->GetValue(),Pg->IncludeLibInReflection(_Reflection_Mask,Lib)));
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckLibraryInMaskOfBlock::SlaveCommAckLibraryInMaskOfBlock(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommAckLibraryInMaskOfBlock::Load(QIODevice *f)
{
	if(UsedLibraries.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckLibraryInMaskOfBlock::Save(QIODevice *f)
{
	if(UsedLibraries.Save(f)==false)
		return false;
	return true;
}

static	int	TestDbg=1;
void	SlaveCommAckLibraryInMaskOfBlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	TestDbg++;
}

//================================================================================

SlaveCommReqSAreaInWholeMatch::SlaveCommReqSAreaInWholeMatch(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	SImageNo=0;
}

bool	SlaveCommReqSAreaInWholeMatch::Load(QIODevice *f)
{
	if(::Load(f,SImageNo)==false)
		return false;
	return true;
}
bool	SlaveCommReqSAreaInWholeMatch::Save(QIODevice *f)
{
	if(::Save(f,SImageNo)==false)
		return false;
	return true;
}
void	SlaveCommReqSAreaInWholeMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckSAreaInWholeMatch	*S
	=(SlaveCommAckSAreaInWholeMatch *)((GetSendBackPacket()==NULL)?new SlaveCommAckSAreaInWholeMatch(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		AlignmentFlexAreaInPage	*Ap=(AlignmentFlexAreaInPage *)Pg;
		if(Ap->WholeMatchData.SImageInfo[SImageNo]!=NULL){
			S->SArea=Ap->WholeMatchData.SImageInfo[SImageNo]->SArea;
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckSAreaInWholeMatch::SlaveCommAckSAreaInWholeMatch(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommAckSAreaInWholeMatch::Load(QIODevice *f)
{
	if(SArea.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckSAreaInWholeMatch::Save(QIODevice *f)
{
	if(SArea.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommAckSAreaInWholeMatch::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	TestDbg++;
}
