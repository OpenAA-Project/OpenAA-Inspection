/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EulerRingL1Resource.h"
#include "XEulerRingL1.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingL1Library.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XEulerRingL1AlgoPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "XPropertyEulerRingL1Common.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================
EulerRingL1Threshold::EulerRingL1Threshold(EulerRingL1Item *parent)
:AlgorithmThreshold(parent)
{
	PointMove.ModeEnabled				=true;
	PointMove.ModeAbsoluteBright		=false;
	PointMove.ModeMakeDynamicMask		=true;
	PointMove.ModeEnableHoleCheck		=true;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeEnableOpenRingCheck	=true;
	PointMove.ModeEnableInRound			=true;

	DarkWidth				=0;		//For ring brightness
	LightWidth				=0;
	MinHoleDiameter			=10;
	MaxHoleDiameter			=20;
	MaxShiftHole			=10;
	ConnectLen				=0;
	ExpandForDynamicMask	=0;

    AdjustBlack				=20;
    AdjustWhite				=20;
	SearchDot				=0;
	HoleBrightnessAsReference	=-1;
}

void	EulerRingL1Threshold::RegistHist(void)
{
	static	bool	InitialStr	=false;

	static	QString	StrHoleDiameter			;
	static	QString	StrHoleShift			;
	static	QString	StrHoleCenterBrightness	;
	static	QString	StrRingCenterBrightness	;
	static	QString	StrRingLowBrightness	;
	static	QString	StrRingHighBrightness	;

	if(InitialStr==false){
		StrHoleDiameter			="Hole Diameter";
		StrHoleShift			="Hole shift distance";
		StrHoleCenterBrightness	="Hole center brightness";
		StrRingCenterBrightness	="Ring center brightness";
		StrRingLowBrightness	="Ring Low brightness";
		StrRingHighBrightness	="Ring High brightness";
		InitialStr=true;
	}

	RegistDouble		(StrHoleDiameter		,Hist_EulerRingL1_HoleDiameter			);
	RegistDouble		(StrHoleShift			,Hist_EulerRingL1_HoleShift				);
	RegistInt			(StrHoleCenterBrightness,Hist_EulerRingL1_HoleCenterBrightness	);
	RegistInt			(StrRingCenterBrightness,Hist_EulerRingL1_RingCenterBrightness	);
	RegistInt			(StrRingLowBrightness	,Hist_EulerRingL1_RingLowBrightness		);
	RegistInt			(StrRingHighBrightness	,Hist_EulerRingL1_RingHighBrightness	);

}
void	EulerRingL1Threshold::CopyFrom(const AlgorithmThreshold &src)
{
	const EulerRingL1Threshold *s=(const EulerRingL1Threshold *)&src;
    AdjustBlack					=s->AdjustBlack;
    AdjustWhite					=s->AdjustWhite;
	SearchDot					=s->SearchDot;
	HoleBrightnessAsReference	=s->HoleBrightnessAsReference;

	PointMove					=s->PointMove;
	DarkWidth					=s->DarkWidth;
	LightWidth					=s->LightWidth;
	MinHoleDiameter				=s->MinHoleDiameter;
	MaxHoleDiameter				=s->MaxHoleDiameter;
	MaxShiftHole				=s->MaxShiftHole;
	ConnectLen					=s->ConnectLen;
	ExpandForDynamicMask		=s->ExpandForDynamicMask;
}
bool	EulerRingL1Threshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const EulerRingL1Threshold *s=(const EulerRingL1Threshold *)&src;
    if(AdjustBlack							!=s->AdjustBlack				)	return false;
    if(AdjustWhite							!=s->AdjustWhite				)	return false;
	if(SearchDot							!=s->SearchDot					)	return false;
	if(HoleBrightnessAsReference			!=s->HoleBrightnessAsReference	)	return false;
	if(PointMove.ModeEnabled				!=s->PointMove.ModeEnabled					)	return false;
	if(PointMove.ModeAbsoluteBright			!=s->PointMove.ModeAbsoluteBright			)	return false;
	if(PointMove.ModeMakeDynamicMask		!=s->PointMove.ModeMakeDynamicMask			)	return false;
	if(PointMove.ModeEnableHoleCheck		!=s->PointMove.ModeEnableHoleCheck			)	return false;
	if(PointMove.ModeCenterBrightFromParts	!=s->PointMove.ModeCenterBrightFromParts	)	return false;
	if(PointMove.ModeEnableOpenRingCheck	!=s->PointMove.ModeEnableOpenRingCheck		)	return false;
	if(PointMove.ModeEnableInRound			!=s->PointMove.ModeEnableInRound			)	return false;
	if(PointMove.Dummy						!=s->PointMove.Dummy						)	return false;
	if(DarkWidth							!=s->DarkWidth					)	return false;
	if(LightWidth							!=s->LightWidth					)	return false;
	if(MinHoleDiameter						!=s->MinHoleDiameter			)	return false;
	if(MaxHoleDiameter						!=s->MaxHoleDiameter			)	return false;
	if(MaxShiftHole							!=s->MaxShiftHole				)	return false;
	if(ConnectLen							!=s->ConnectLen					)	return false;
	if(ExpandForDynamicMask					!=s->ExpandForDynamicMask		)	return false;
	return true;
}
bool	EulerRingL1Threshold::Save(QIODevice *f)
{
	WORD	Ver=EulerRingL1Version;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,DarkWidth)==false)
		return false;
	if(::Save(f,LightWidth)==false)
		return false;
	if(::Save(f,MinHoleDiameter)==false)
		return false;
	if(::Save(f,MaxHoleDiameter)==false)
		return false;
	if(::Save(f,MaxShiftHole)==false)
		return false;
	if(::Save(f,ConnectLen)==false)
		return false;
	if(::Save(f,ExpandForDynamicMask)==false)
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;

	if(f->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;

    if(::Save(f,SearchDot)==false)
		return false;
    if(::Save(f,HoleBrightnessAsReference)==false)
		return false;
	return true;
}

bool	EulerRingL1Threshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,DarkWidth)==false)
		return false;
	if(::Load(f,LightWidth)==false)
		return false;
	if(::Load(f,MinHoleDiameter)==false)
		return false;
	if(::Load(f,MaxHoleDiameter)==false)
		return false;
	if(::Load(f,MaxShiftHole)==false)
		return false;
	if(::Load(f,ConnectLen)==false)
		return false;
	if(::Load(f,ExpandForDynamicMask)==false)
		return false;

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;

	if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
    if(::Load(f,SearchDot)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,HoleBrightnessAsReference)==false)
			return false;
	}
	return true;
}

void	EulerRingL1Threshold::FromLibrary(AlgorithmLibrary *src)
{
	EulerRingL1Library	*LSrc=dynamic_cast<EulerRingL1Library *>(src);
	if(LSrc==NULL)
		return;
    AdjustBlack					=LSrc->AdjustBlack;
    AdjustWhite					=LSrc->AdjustWhite;
	SearchDot					=LSrc->SearchDot;
	HoleBrightnessAsReference	=LSrc->HoleBrightnessAsReference;

	PointMove.ModeEnabled				=LSrc->PointMove.ModeEnabled;
	PointMove.ModeAbsoluteBright		=LSrc->PointMove.ModeAbsoluteBright;
	PointMove.ModeMakeDynamicMask		=LSrc->PointMove.ModeMakeDynamicMask;
	PointMove.ModeEnableHoleCheck		=LSrc->PointMove.ModeEnableHoleCheck;
	PointMove.ModeCenterBrightFromParts	=LSrc->PointMove.ModeCenterBrightFromParts;
	PointMove.ModeEnableOpenRingCheck	=LSrc->PointMove.ModeEnableOpenRingCheck;
	PointMove.ModeEnableInRound			=LSrc->PointMove.ModeEnableInRound;
	DarkWidth						=LSrc->DarkWidth;
	LightWidth						=LSrc->LightWidth;
	MinHoleDiameter					=LSrc->MinHoleDiameter;
	MaxHoleDiameter					=LSrc->MaxHoleDiameter;
	MaxShiftHole					=LSrc->MaxShiftHole;
	ConnectLen						=LSrc->ConnectLen;
	ExpandForDynamicMask			=LSrc->ExpandForDynamicMask;
}
void	EulerRingL1Threshold::ToLibrary(AlgorithmLibrary *Dest)
{
	EulerRingL1Library	*LDst=dynamic_cast<EulerRingL1Library *>(Dest);
	if(LDst==NULL)
		return;
    LDst->AdjustBlack				=AdjustBlack;
    LDst->AdjustWhite				=AdjustWhite;
	LDst->SearchDot					=SearchDot;
	LDst->HoleBrightnessAsReference	=HoleBrightnessAsReference;

	LDst->PointMove.ModeEnabled				=PointMove.ModeEnabled;
	LDst->PointMove.ModeAbsoluteBright		=PointMove.ModeAbsoluteBright;
	LDst->PointMove.ModeMakeDynamicMask		=PointMove.ModeMakeDynamicMask;
	LDst->PointMove.ModeEnableHoleCheck		=PointMove.ModeEnableHoleCheck;
	LDst->PointMove.ModeCenterBrightFromParts	=PointMove.ModeCenterBrightFromParts;
	LDst->PointMove.ModeEnableOpenRingCheck	=PointMove.ModeEnableOpenRingCheck;
	LDst->PointMove.ModeEnableInRound		=PointMove.ModeEnableInRound;
	LDst->DarkWidth							=DarkWidth;
	LDst->LightWidth						=LightWidth;
	LDst->MinHoleDiameter					=MinHoleDiameter;
	LDst->MaxHoleDiameter					=MaxHoleDiameter;
	LDst->MaxShiftHole						=MaxShiftHole;
	LDst->ConnectLen						=ConnectLen;
	LDst->ExpandForDynamicMask				=ExpandForDynamicMask;
}

//=====================================================================================


EulerRingL1InLayer::EulerRingL1InLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLITemplate<EulerRingL1Item,EulerRingL1InPage,EulerRingL1Base>(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte=0;
	PickupBmpYLen=0;

	DimSearcher		=NULL;
	DimSearcherNumb	=0;
}
EulerRingL1InLayer::~EulerRingL1InLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;

	if(DimSearcher!=NULL)
		delete	[]DimSearcher;
	DimSearcher		=NULL;
	DimSearcherNumb	=0;
}
bool		EulerRingL1InLayer::AppendItem(AlgorithmItemRoot *item)
{
	if(item->GetLibID()>=0){
		AlgorithmLibraryLevelContainer	*LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		if(LibP==NULL){
			GetParentBase()->LoadAllManagedCacheLib();
			LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		}
		if(LibP!=NULL){
			if(LibP->HasGenLayer(GetLayer())==true){
				return AlgorithmInLayerPLI::AppendItem(item);
			}
			return false;
		}
	}
	return AlgorithmInLayerPLI::AppendItem(item);
}

bool		EulerRingL1InLayer::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}

bool		EulerRingL1InLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	return AlgorithmInLayerPLI::AppendItemFromLoad(item);
}

bool		EulerRingL1InLayer::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	return AlgorithmInLayerPLI::AppendItem(item,itemID);
}

ExeResult	EulerRingL1InLayer::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInLayerRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{	
	ExeResult	Ret=AlgorithmInLayerPLITemplate<EulerRingL1Item,EulerRingL1InPage,EulerRingL1Base>::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);

	if(DimSearcher==NULL){
		DimSearcherNumb	=tGetParentBase()->MaxRadius;
		DimSearcher	=new EulerRingL1Searcher[DimSearcherNumb];
		for(int r=1;r<DimSearcherNumb;r++){
			DimSearcher[r].ExecuteInitialAfterEdit(r,EInfo);
		}
	}

	return Ret;
}

void	EulerRingL1InLayer::CreatePickupBmpBuff(void)
{
	if(PickupBmp!=NULL && PickupBmpYLen!=GetMaxLines()){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
	}
	if(PickupBmp==NULL){
		PickupBmpYLen=GetMaxLines();
		PickupBmpXByte=(GetDotPerLine()+7)/8;
		PickupBmp=MakeMatrixBuff(PickupBmpXByte ,PickupBmpYLen);
	}
	MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
}

void	EulerRingL1InLayer::PickupTest(EulerRingL1Library &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);

	LibData.MakePickupTest(GetPage()
							,GetMasterBuff()
							,MaskMap.GetBitMap()
							,PickupBmp,NULL
							,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
							,((EulerRingL1Base *)GetParentBase())->OmitZoneDot);
}
void	EulerRingL1InLayer::GenerateBlocks(EulerRingL1Library *LibDim[],int LibDimNumb)
{
	CreatePickupBmpBuff();

	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;
	BYTE **GeneratedMap=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(GeneratedMap,0,XByte,GetMaxLines());

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(GetParentBase());
			if(GetParentBase()->GetLibraryContainer()->GetLibrary(L->GetLibID() ,*Lib)==true){
				LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
			}
			else{
				delete	Lib;
				Lib=NULL;
			}
		}
		if(Lib!=NULL){
			EulerRingL1Library	*BLib=dynamic_cast<EulerRingL1Library *>(Lib->GetLibrary());
			L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
		}
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2	 ,GetMaxLines());

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());

	BYTE **tMaskMap	=MakeMatrixBuff(XByte,GetMaxLines());
	GetParentBase()->LoadAllManagedCacheLib();

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());
		ConstMapBuffer MaskMap;
		GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();

		
		MatrixBuffCopy(tMaskMap,XByte,GetMaxLines()
                     , MaskBitmap,XByte,GetMaxLines());
		MatrixBuffNotAnd (tMaskMap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

		int	Layer=GetLayer();
		if(LibDim[i]->GetAdaptedPickLayers().GetCount()>0){
			Layer=LibDim[i]->GetAdaptedPickLayers()[0];
		}
		
		int	ExpandedDotToPad=LibDim[i]->ExpandedDotToPad;
		LibDim[i]->ExpandedDotToPad=0;
		LibDim[i]->MakePickupTest(GetPage()
								,tGetParentInPage()->GetLayerData(Layer)->GetMasterBuff()
								,(const BYTE **)tMaskMap
								,CurrentMap,OcupyMap
								,XByte ,GetDotPerLine(),GetMaxLines()
								,((EulerRingL1Base *)GetParentBase())->OmitZoneDot);

		LibDim[i]->ExpandedDotToPad=ExpandedDotToPad;
		NPListPack<AlgorithmItemPLI>	TmpBlockData;
		LibDim[i]->MakeBlock(GetPage()
			,CurrentMap,LastOcupyMap
			,XByte ,GetDotPerLine(),GetMaxLines()
			,TmpBlockData
			,ExpandedDotToPad);

		AlgorithmItemPLI	*q;
		while((q=TmpBlockData.GetFirst())!=NULL){
			TmpBlockData.RemoveList(q);
			AppendItem(q);
		}
		MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(CurrentMap	 ,GetMaxLines());
	DeleteMatrixBuff(OcupyMap	 ,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap,GetMaxLines());
	DeleteMatrixBuff(GeneratedMap,GetMaxLines());
	DeleteMatrixBuff(tMaskMap	 ,GetMaxLines());
}
void	EulerRingL1InLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedEulerRingL1FromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedEulerRingL1FromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		EulerRingL1Item	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			EulerRingL1Item	*B=(EulerRingL1Item *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
		return;
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				EulerRingL1Item	*B=(EulerRingL1Item *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestEulerRingL1Packet	*CmdClearTestEulerRingL1PacketVar=dynamic_cast<CmdClearTestEulerRingL1Packet *>(packet);
	if(CmdClearTestEulerRingL1PacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}
	CmdEulerRingL1InfoListPacket	*CmdEulerRingL1InfoListPacketVar=dynamic_cast<CmdEulerRingL1InfoListPacket *>(packet);
	if(CmdEulerRingL1InfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			EulerRingL1InfoList	*a;
			for(a=CmdEulerRingL1InfoListPacketVar->EulerRingL1Infos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->EulerRingL1Count.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new EulerRingL1InfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					a->EulerRingL1Count.Add(0);
				}
				IntClass	*d=a->EulerRingL1Count.GetItem(GetLayer());
				if(d!=NULL){
					d->SetValue(d->GetValue()+1);
				}
				CmdEulerRingL1InfoListPacketVar->EulerRingL1Infos->AppendList(a);
			}
		}
		return;
	}
	CmdGetEulerRingL1FromList	*CmdGetEulerRingL1FromListVar=dynamic_cast<CmdGetEulerRingL1FromList *>(packet);
	if(CmdGetEulerRingL1FromListVar!=NULL){
		EulerRingL1Item *Item=(EulerRingL1Item *)SearchIDItem(CmdGetEulerRingL1FromListVar->CurrentItem.GetFirst()->ID);
		CmdGetEulerRingL1FromListVar->EulerRingL1InfoOnMouse=Item;
		return;
	}
	CmdCreateEulerRingL1Item	*CmdCreateEulerRingL1ItemVar=dynamic_cast<CmdCreateEulerRingL1Item *>(packet);
	if(CmdCreateEulerRingL1ItemVar!=NULL){
		CmdCreateEulerRingL1ItemVar->EulerRingL1=(EulerRingL1Item *)CreateItem(0);
		return;
	}
	CmdAddByteEulerRingL1ItemPacket	*AddBItem=dynamic_cast<CmdAddByteEulerRingL1ItemPacket *>(packet);
	if(AddBItem!=NULL){
		QBuffer	MBuff(&AddBItem->Buff);
		EulerRingL1Item	*Item=new EulerRingL1Item();
		MBuff.open(QIODevice::ReadWrite);
		Item->Load(&MBuff,GetLayersBase());
		Item->SetArea(AddBItem->Area);
		Item->SetManualCreated(true);
		GetParentBase()->ClearManagedCacheLib();
		if(AppendItem(Item)==false){
			delete	Item;
		}
		return;
	}
	CmdRemoveAllOriginalEulerRingL1Items	*CmdRemoveAllOriginalEulerRingL1ItemsVar=dynamic_cast<CmdRemoveAllOriginalEulerRingL1Items *>(packet);
	if(CmdRemoveAllOriginalEulerRingL1ItemsVar!=NULL){
		AlgorithmItemPointerListContainer Items;
		EnumOriginTypeItems((OriginType)CmdRemoveAllOriginalEulerRingL1ItemsVar->GeneratedOrigin,Items);
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
			AlgorithmItemPointerList *NextP=a->GetNext();
			if(a->GetItem()->GetEditLocked()==true){
				Items.RemoveList(a);
				delete	a;
			}
			a=NextP;
		}
		RemoveItems(Items);
		return;
	}
	ChangeEulerRingL1sThresholdCommon	*ChangeEulerRingL1sThresholdCommonVar=dynamic_cast<ChangeEulerRingL1sThresholdCommon *>(packet);
	if(ChangeEulerRingL1sThresholdCommonVar!=NULL){
		SetThresholdEulerRingL1Info	ThresholdInfo;
		QBuffer	Buff(&ChangeEulerRingL1sThresholdCommonVar->InfosData);
		Buff.open(QIODevice::ReadWrite);
		if(ThresholdInfo.Load(&Buff)==true){
			for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
				if(ChangeEulerRingL1sThresholdCommonVar->BlockLibID==L->GetLibID()){
					EulerRingL1Item	*B=(EulerRingL1Item *)L;
					B->SetThresholdFromCommon(&ThresholdInfo);
				}
			}
		}
		return;
	}
}

void	EulerRingL1InLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	EulerRingL1DrawAttr	*BAttr=dynamic_cast<EulerRingL1DrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==EulerRingL1DrawAttr::_LibTest){
			if(PickupBmp!=NULL){
				EulerRingL1Base	*BBase=dynamic_cast<EulerRingL1Base *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==EulerRingL1DrawAttr::_CreatedBlock){
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	EulerRingL1InLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		EulerRingL1Item	*BI=(EulerRingL1Item *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

bool	EulerRingL1InLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}

void	EulerRingL1InLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		EulerRingL1Item	*a=dynamic_cast<EulerRingL1Item *>(k);
		if(a!=NULL){
			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}
	}
}


//===========================================================================================
EulerRingL1InPage::EulerRingL1InPage(AlgorithmBase *parent)
	:AlgorithmInPagePLITemplate<EulerRingL1Item,EulerRingL1InLayer,EulerRingL1Base>(parent)
{
}
EulerRingL1InPage::~EulerRingL1InPage(void)
{
}

ExeResult	EulerRingL1InPage::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInPageRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePLI::ExecuteInitialAfterEdit( ExeID ,Res,EInfo);
	return Ret;
}

ExeResult	EulerRingL1InPage::ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePLI::ExecutePreAlignment(ExeID ,Res);
}

void	EulerRingL1InPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestEulerRingL1Packet	*BPickLib=dynamic_cast<CmdPickupTestEulerRingL1Packet *>(packet);
	if(BPickLib!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			if(BPickLib->LibPoint->GetAdaptedPickLayers().IsInclude(Layer)==true){
				EulerRingL1InLayer	*BL=dynamic_cast<EulerRingL1InLayer *>(GetLayerData(Layer));
				BL->PickupTest(*(EulerRingL1Library *)BPickLib->LibPoint->GetLibrary());
			}
		}
		return;
	}
	CmdGenerateEulerRingL1Packet	*BGenerated=dynamic_cast<CmdGenerateEulerRingL1Packet *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryContainer	*Container=GetParentBase()->GetLibraryContainer();
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
			int	N=0;
			for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext()){
				AlgorithmLibraryLevelContainer	*Lib=new AlgorithmLibraryLevelContainer(Container);
				Container->GetLibrary(L->GetValue(),*Lib);
				if(Lib->GetAdaptedGenLayers().IsInclude(Layer)==true){
					LibDim[N]=Lib;
					N++;
				}
				else{
					delete	Lib;
				}
			}
			if(N>0){
				EulerRingL1Library	**DDim=new EulerRingL1Library*[N];
				for(int i=0;i<N;i++){
					DDim[i]=dynamic_cast<EulerRingL1Library *>(LibDim[i]->GetLibrary());
				}

				EulerRingL1InLayer	*BL=dynamic_cast<EulerRingL1InLayer *>(GetLayerData(Layer));
				if(BL!=NULL){
					BL->GenerateBlocks(DDim,N);		
				}
				delete	[]DDim;
			}
			for(int i=0;i<N;i++){
				delete	LibDim[i];
			}
			delete	[]LibDim;
		}
		return;
	}
	CmdAddByteEulerRingL1ItemPacket	*AddBItem=dynamic_cast<CmdAddByteEulerRingL1ItemPacket *>(packet);
	if(AddBItem!=NULL){
		for(IntClass *c=AddBItem->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}

	CmdEulerRingL1InfoListPacket	*CmdEulerRingL1InfoListPacketVar=dynamic_cast<CmdEulerRingL1InfoListPacket *>(packet);
	if(CmdEulerRingL1InfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdGetEulerRingL1FromList	*CmdGetEulerRingL1FromListVar=dynamic_cast<CmdGetEulerRingL1FromList *>(packet);
	if(CmdGetEulerRingL1FromListVar!=NULL){
		if(CmdGetEulerRingL1FromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetEulerRingL1FromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdClearTestEulerRingL1Packet	*CmdClearTestEulerRingL1PacketVar=dynamic_cast<CmdClearTestEulerRingL1Packet *>(packet);
	if(CmdClearTestEulerRingL1PacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdRemoveAllOriginalEulerRingL1Items	*CmdRemoveAllOriginalEulerRingL1ItemsVar=dynamic_cast<CmdRemoveAllOriginalEulerRingL1Items *>(packet);
	if(CmdRemoveAllOriginalEulerRingL1ItemsVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	ChangeEulerRingL1sThresholdCommon	*ChangeEulerRingL1sThresholdCommonVar=dynamic_cast<ChangeEulerRingL1sThresholdCommon *>(packet);
	if(ChangeEulerRingL1sThresholdCommonVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
}

bool	EulerRingL1InPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	EulerRingL1Base	*ABase=(EulerRingL1Base *)GetParentBase();

	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){

		GetParentBase()->LoadAllManagedCacheLib();
		EulerRingL1Library	*TmpLib=(EulerRingL1Library *)GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			for(int layer=0;layer<GetLayerNumb();layer++){
				NPListPack<AlgorithmItemPLI>	TmpBlockData;
				if(TmpLib->HasGenLayer(layer)==true){
					EulerRingL1InLayer	*BL=(EulerRingL1InLayer*)GetLayerData(layer);
					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					ConstMapBuffer MaskMap;
					BL->GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib);
					bool	LimitedMaskInOtherPage=BL->UseLibraryForMaskingInOtherPage(Info.LibID);
					bool	LimitedMaskInThisPage =BL->IncludeLibInReflection(_Reflection_Mask,TmpLib,NULL);
					if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
						MatrixBuffAnd	(TmpData ,MaskMap.GetBitMap() ,Info.XByte ,Info.YLen);

						if(Info.Something.count()>0){
							QBuffer	tBuff(&Info.Something);
							tBuff.open(QIODevice::ReadOnly);

							int32	AlgoCount;
							if(::Load(&tBuff,AlgoCount)==false){
								DeleteMatrixBuff(TmpData,Info.YLen);
								return false;
							}
							QByteArray	DataArray;
							bool		Found=false;
							for(int i=0;i<AlgoCount;i++){
								QString	AlgoName;
								if(::Load(&tBuff,AlgoName)==false){
									DeleteMatrixBuff(TmpData,Info.YLen);
									return false;
								}
								if(::Load(&tBuff,DataArray)==false){
									DeleteMatrixBuff(TmpData,Info.YLen);
									return false;
								}
								if(AlgoName==/**/"EulerRingL1"){
									Found=true;
									break;
								}
							}
							if(Found==true){
								QBuffer	Buff(&DataArray);
								Buff.open(QIODevice::ReadOnly);

								SetThresholdEulerRingL1Info	ThresholdEulerRingL1InfoData;
								if(ThresholdEulerRingL1InfoData.Load(&Buff)==true){
									//TmpLib->SpaceToOutline	= 0;
									TmpLib->MakeBlockOnly(GetPage(),TmpData,Info.XByte ,Info.XByte*8,Info.YLen,TmpBlockData
														,ABase->RoundRateInHole);
									for(AlgorithmItemPLI *aq=TmpBlockData.GetFirst();aq!=NULL;aq=aq->GetNext()){
										EulerRingL1Item	*BItem=dynamic_cast<EulerRingL1Item *>(aq);
										if(BItem!=NULL){	
											BItem->SetThresholdFromCommon(&ThresholdEulerRingL1InfoData);
										}
									}
								}
							}
						}
						else{
							TmpLib->MakeBlockOnly(GetPage(),TmpData,Info.XByte ,Info.XByte*8,Info.YLen,TmpBlockData
												,ABase->RoundRateInHole);
						}

						AlgorithmItemPLI	*q;
						while((q=TmpBlockData.GetFirst())!=NULL){
							TmpBlockData.RemoveList(q);
							q->SetOrigin(Info.Origin);
							q->SetOriginType(Info.OperationOrigin);
							BL->AppendItem(q);
						}
					}
					DeleteMatrixBuff(TmpData,Info.YLen);
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(int layer=0;layer<GetLayerNumb();layer++){
			EulerRingL1InLayer	*L=(EulerRingL1InLayer *)GetLayerData(layer);
			L->MoveFromPipe(Info);
		}
		return true;
	}

	return false;
}
//===========================================================================================
EulerRingL1Base::EulerRingL1Base(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	EulerRingL1Normal		=Qt::darkGreen;
	EulerRingL1Selected	=Qt::green;
	EulerRingL1Active		=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;
	RoundRateInHole	=0.9;
	MaxRadius		=200;

	SetParam(&ColorPickup			, /**/"Color" ,/**/"ColorPickup"			,LangSolver.GetString(XEulerRingL1_LS,LID_1)/*"Color for Image to Pickup-Test "*/);
	SetParam(&EulerRingL1Normal		, /**/"Color" ,/**/"EulerRingL1Normal"		,LangSolver.GetString(XEulerRingL1_LS,LID_2)/*"Color for Area"*/);
	SetParam(&EulerRingL1Selected	, /**/"Color" ,/**/"EulerRingL1Selected"	,LangSolver.GetString(XEulerRingL1_LS,LID_3)/*"Color for Selected Area"*/);
	SetParam(&EulerRingL1Active		, /**/"Color" ,/**/"EulerRingL1Active"		,LangSolver.GetString(XEulerRingL1_LS,LID_4)/*"Color for Active Area"*/);

	SetParam(&BlockColor0		, /**/"BlockColor" ,/**/"BlockColor0"		,LangSolver.GetString(XEulerRingL1_LS,LID_5)/*"Area Color 0"*/);
	SetParam(&BlockColor1		, /**/"BlockColor" ,/**/"BlockColor1"		,LangSolver.GetString(XEulerRingL1_LS,LID_6)/*"Area Color 1"*/);
	SetParam(&BlockColor2		, /**/"BlockColor" ,/**/"BlockColor2"		,LangSolver.GetString(XEulerRingL1_LS,LID_7)/*"Area Color 2"*/);
	SetParam(&BlockColor3		, /**/"BlockColor" ,/**/"BlockColor3"		,LangSolver.GetString(XEulerRingL1_LS,LID_8)/*"Area Color 3"*/);
	SetParam(&BlockColor4		, /**/"BlockColor" ,/**/"BlockColor4"		,LangSolver.GetString(XEulerRingL1_LS,LID_9)/*"Area Color 4"*/);
	SetParam(&BlockColor5		, /**/"BlockColor" ,/**/"BlockColor5"		,LangSolver.GetString(XEulerRingL1_LS,LID_10)/*"Area Color 5"*/);
	SetParam(&BlockColor6		, /**/"BlockColor" ,/**/"BlockColor6"		,LangSolver.GetString(XEulerRingL1_LS,LID_11)/*"Area Color 6"*/);
	SetParam(&BlockColor7		, /**/"BlockColor" ,/**/"BlockColor7"		,LangSolver.GetString(XEulerRingL1_LS,LID_12)/*"Area Color 7"*/);

	SetParam(&OmitZoneDot		, /**/"Setting"		,/**/"OmitZoneDot"		,LangSolver.GetString(XEulerRingL1_LS,LID_13)/*"Omit zone dot in area generation"*/);
	SetParam(&RoundRateInHole	, /**/"Setting"		,/**/"RoundRateInHole"	,"Round rate to check roundness");
	SetParam(&MaxRadius	, /**/"Setting"				,/**/"MaxRadius"		,"Max radius for search");
}

AlgorithmDrawAttr	*EulerRingL1Base::CreateDrawAttr(void)
{
	return new EulerRingL1DrawAttr();
}

void	EulerRingL1Base::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetEulerRingL1LibraryListPacket	*AListPacket=dynamic_cast<CmdGetEulerRingL1LibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetEulerRingL1LibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetEulerRingL1LibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertEulerRingL1LibraryPacket	*BInsLib=dynamic_cast<CmdInsertEulerRingL1LibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(EulerRingL1Version);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateEulerRingL1LibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateEulerRingL1LibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(EulerRingL1Version);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadEulerRingL1LibraryPacket	*BLoadLib=dynamic_cast<CmdLoadEulerRingL1LibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempEulerRingL1LibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempEulerRingL1LibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearEulerRingL1LibraryPacket	*CmdClearEulerRingL1LibraryPacketVar=dynamic_cast<CmdClearEulerRingL1LibraryPacket *>(packet);
	if(CmdClearEulerRingL1LibraryPacketVar!=NULL){
		CmdClearEulerRingL1LibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteEulerRingL1LibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteEulerRingL1LibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestEulerRingL1Packet	*BPickLib=dynamic_cast<CmdPickupTestEulerRingL1Packet *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		EulerRingL1InPage	*Bp=dynamic_cast<EulerRingL1InPage *>(p);
		if(Bp==NULL)
			return;
		Bp->TransmitDirectly(packet);	
		return;
	}
	CmdGenerateEulerRingL1Packet	*BGenerated=dynamic_cast<CmdGenerateEulerRingL1Packet *>(packet);
	if(BGenerated!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p==NULL)
			return;
		EulerRingL1InPage	*Bp=dynamic_cast<EulerRingL1InPage *>(p);
		if(Bp==NULL)
			return;
		Bp->TransmitDirectly(packet);	
		return;
	}
	CmdCreateTempEulerRingL1ItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempEulerRingL1ItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new EulerRingL1Item();
		return;
	}
	CmdCreateByteArrayFromEulerRingL1ItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromEulerRingL1ItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadEulerRingL1ItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadEulerRingL1ItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedEulerRingL1FromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedEulerRingL1FromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
	CmdClearTestEulerRingL1Packet	*CmdClearTestEulerRingL1PacketVar=dynamic_cast<CmdClearTestEulerRingL1Packet *>(packet);
	if(CmdClearTestEulerRingL1PacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestEulerRingL1PacketVar);
		}
	}
	CmdCreateEulerRingL1Item	*CmdCreateEulerRingL1ItemVar=dynamic_cast<CmdCreateEulerRingL1Item *>(packet);
	if(CmdCreateEulerRingL1ItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

ExeResult	EulerRingL1Base::ExecuteInitialAfterEdit(int ExeID 
													,ResultBaseForAlgorithmRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ColorLogicWithTable::ClearTable();
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}


bool	EulerRingL1Base::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==EulerRingL1HistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingL1HistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingL1ReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingL1ReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingL1ReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingL1SendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==EulerRingL1ReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*EulerRingL1Base::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==EulerRingL1HistogramListSendCommand){
		EulerRingL1HistogramListSend	*pSend=new EulerRingL1HistogramListSend();
		if(reqData!=NULL){
			EulerRingL1HistogramListReq	*req=(EulerRingL1HistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==EulerRingL1HistogramListReqCommand){
		return new EulerRingL1HistogramListReq();
	}
	else if(Command==EulerRingL1ReqThresholdReqCommand){
		return new EulerRingL1ThresholdReq();
	}
	else if(Command==EulerRingL1ReqThresholdSendCommand){
		EulerRingL1ThresholdSend	*pSend=new EulerRingL1ThresholdSend();
		if(reqData!=NULL){
			EulerRingL1ThresholdReq	*req=(EulerRingL1ThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==EulerRingL1ReqTryThresholdCommand){
		return new EulerRingL1ReqTryThreshold();
	}
	else if(Command==EulerRingL1SendTryThresholdCommand){
		EulerRingL1SendTryThreshold	*pSend=new EulerRingL1SendTryThreshold();
		if(reqData!=NULL){
			EulerRingL1ReqTryThreshold	*req=(EulerRingL1ReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==EulerRingL1ReqChangeShiftCommand){
		return new EulerRingL1ChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	EulerRingL1Base::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==EulerRingL1HistogramListSendCommand){
		EulerRingL1HistogramListSend	*p=(EulerRingL1HistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingL1HistogramListReqCommand){
		EulerRingL1HistogramListReq	*p=(EulerRingL1HistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingL1ReqThresholdReqCommand){
		EulerRingL1ThresholdReq	*p=(EulerRingL1ThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingL1ReqThresholdSendCommand){
		EulerRingL1ThresholdSend	*p=(EulerRingL1ThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingL1ReqTryThresholdCommand){
		EulerRingL1ReqTryThreshold	*p=(EulerRingL1ReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==EulerRingL1SendTryThresholdCommand){
		EulerRingL1SendTryThreshold	*p=(EulerRingL1SendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==EulerRingL1ReqChangeShiftCommand){
		EulerRingL1ChangeShift	*p=(EulerRingL1ChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	EulerRingL1Base::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==EulerRingL1HistogramListSendCommand){
		EulerRingL1HistogramListSend	*p=(EulerRingL1HistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingL1HistogramListReqCommand){
		EulerRingL1HistogramListReq	*p=(EulerRingL1HistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingL1ReqThresholdReqCommand){
		EulerRingL1ThresholdReq	*p=(EulerRingL1ThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingL1ReqThresholdSendCommand){
		EulerRingL1ThresholdSend	*p=(EulerRingL1ThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingL1ReqTryThresholdCommand){
		EulerRingL1ReqTryThreshold	*p=(EulerRingL1ReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingL1SendTryThresholdCommand){
		EulerRingL1SendTryThreshold	*p=(EulerRingL1SendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==EulerRingL1ReqChangeShiftCommand){
		EulerRingL1ChangeShift	*p=(EulerRingL1ChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	EulerRingL1Base::GeneralDataReply(int32 Command,void *data)
{
	if(Command==EulerRingL1HistogramListSendCommand){
		EulerRingL1HistogramListSend	*p=(EulerRingL1HistogramListSend *)data;
		return true;
	}
	else if(Command==EulerRingL1HistogramListReqCommand){
		EulerRingL1HistogramListReq	*p=(EulerRingL1HistogramListReq *)data;
		return true;
	}
	else if(Command==EulerRingL1ReqThresholdReqCommand){
		EulerRingL1ThresholdReq	*p=(EulerRingL1ThresholdReq *)data;
		return true;
	}
	else if(Command==EulerRingL1ReqThresholdSendCommand){
		EulerRingL1ThresholdSend	*p=(EulerRingL1ThresholdSend *)data;
		return true;
	}
	else if(Command==EulerRingL1ReqTryThresholdCommand){
		EulerRingL1ReqTryThreshold	*p=(EulerRingL1ReqTryThreshold *)data;
		return true;
	}
	else if(Command==EulerRingL1SendTryThresholdCommand){
		EulerRingL1SendTryThreshold	*p=(EulerRingL1SendTryThreshold *)data;
		return true;
	}
	else if(Command==EulerRingL1ReqChangeShiftCommand){
		EulerRingL1ChangeShift	*p=(EulerRingL1ChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}



