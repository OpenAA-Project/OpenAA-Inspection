#include "BlockFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XBlockLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XBlockInspection.h"
#include "NGTypeDialog.h"
#include "XCrossObj.h"
#include "XCriticalFunc.h"

static	int	DbgX=2450;
static	int	DbgY=2585;
static	int	DbgNumer=0;

BlockLibNGTypeItem::BlockLibNGTypeItem(LayersBase *base)
	:LibNGTypeItem(base)
{
	MinColor=0;
	MaxColor=255;
	MinSize=0;
	MaxSize=9999;
	MinRoundRate=0;
	MaxRoundRate=100;
}

bool	BlockLibNGTypeItem::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MinColor)==false)
		return false;
	if(::Save(f,MaxColor)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,MaxSize)==false)
		return false;
	if(::Save(f,MinRoundRate)==false)
		return false;
	if(::Save(f,MaxRoundRate)==false)
		return false;
	return true;
}
bool	BlockLibNGTypeItem::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,MinColor)==false)
		return false;
	if(::Load(f,MaxColor)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,MaxSize)==false)
		return false;
	if(::Load(f,MinRoundRate)==false)
		return false;
	if(::Load(f,MaxRoundRate)==false)
		return false;
	return true;
}

bool	BlockLibNGTypeItem::ShowSetting(void)
{
	NGTypeDialog	D(GetLayersBase(),this);
	D.exec();
	return true;
}

//============================================================

BlockLibrary::BlockLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupL				=0;
	PickupH				=0;
    MinBlockSize		=0;
    MaxBlockSize		=1000000;
    MinBlockDots		=0;
    MaxBlockDots		=2000000000;
    LimitBlockSize		=400;
	RegularBrightness	=-1;
	GenFollowLine.Gen_Left	=true;
	GenFollowLine.Gen_Top	=true;
	GenFollowLine.Gen_Right	=true;
	GenFollowLine.Gen_Bottom=true;
	FollowLineLength	=3;
	GenerationMode.Transparent			=false;		//?d?!???€??E??E?e?u???b?N
	GenerationMode.LeftPickup			=false;
	GenerationMode.OverlappedGen		=true;
	GenerationMode.PlusHalfDotIsolation	=false;
	GenerationMode.BindSmallBlock		=false;
	GenerationMode.LockFirst			=false;
	GenerationCategory	=_AutoSetting_PAD;

	NoiseSize		=0;
	NoiseSizePinHole=0;
    SpaceToOutline	=0;
	OutlineGeneration=10000;
    Priority		=0;

//????C?f?[?^
	NBrightWidthL	=0;
	NBrightWidthH	=0;
	NOKDotL			=0;
	NOKDotH			=0;
	NMaxNGDotL		=99999999;
	NMaxNGDotH		=99999999;
	NOKLengthL		=0;
	NOKLengthH		=0;
	BBrightWidthL	=0;
	BBrightWidthH	=0;
	BOKDotL			=0;
	BOKDotH			=0;
	BMaxNGDotL		=99999999;
	BMaxNGDotH		=99999999;
	BOKLengthL		=0;
	BOKLengthH		=0;

	DiffBrightWidthL	=255;
	DiffBrightWidthH	=255;
	ExpandForGenMask	=0;

	NMinNGCountL	=0;
	NMinNGCountH	=0;
	BMinNGCountL	=0;
	BMinNGCountH	=0;
	NConnectLen		=0;
	BConnectLen		=0;

	PointMove.ModeEnabled				=true;
	PointMove.ModeAdjustable			=true;
	PointMove.ModeAbsoluteBright		=false;
	PointMove.ModeCommonMovable			=false;
	PointMove.ModeNGCluster				=true;
	PointMove.ModeDiffer				=false;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeOnlyMatching			=false;
	PointMove.ModeWhiteMask				=false;
	PointMove.ModeBlackMask				=false;
	PointMove.ModeInvertLogic			=false;
	PointMove.ModeMatchPosition			=false;
	PointMove.ModeSearchDetail			=false;
	PointMove.ModeDynamicMask			=false;
	PointMove.ModeBindBWBroad			=false;
	PointMove.ModeBindBWNarrow			=false;
	PointMove.ModeAdoptBiggest			=false;
	PointMove.ModeUseMasterImage		=false;
	PointMove.ModePermitInverted		=true;
	PointMove.ModeMatchPositionBW		=false;
	PointMove.ModeOppositeRange			=false;
	PointMove.ModeUseGlobalLine			=true;	//Follow outline
    CommonMoveDot	=0;

    AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    AdjustWhite		=20;    //?P?x?a?3?I?a?A??
    SelfSearch		=4;     //?c?E?T?o?h?b?g??
	FollowLineLayer	=-1;
}
BlockLibrary::~BlockLibrary(void)
{
	SubtractBlock.RemoveAll();
}

bool	BlockLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=BlockInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(SubtractBlock.Save(f)==false)
		return false;

	if(::Save(f,PickupL)==false)
		return false;
	if(::Save(f,PickupH)==false)
		return false;
    if(::Save(f,MinBlockSize)==false)
		return false;
    if(::Save(f,MaxBlockSize)==false)
		return false;
    if(::Save(f,MinBlockDots)==false)
		return false;
    if(::Save(f,MaxBlockDots)==false)
		return false;
    if(::Save(f,LimitBlockSize)==false)
		return false;
    if(::Save(f,RegularBrightness)==false)
		return false;
    if(::Save(f,FollowLineLength)==false)
		return false;
 	if(f->write((const char *)&GenFollowLine,sizeof(GenFollowLine))!=sizeof(GenFollowLine))
		return false;

	if(f->write((const char *)&GenerationMode,sizeof(GenerationMode))!=sizeof(GenerationMode))
		return false;
	if(f->write((const char *)&GenerationCategory,sizeof(GenerationCategory))!=sizeof(GenerationCategory))
		return false;
	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
    if(::Save(f,SpaceToOutline)==false)
		return false;
	if(::Save(f,OutlineGeneration)==false)
		return false;
    if(::Save(f,Priority)==false)
		return false;

//????C?f?[?^

	if(::Save(f,NBrightWidthL)==false)
		return false;
	if(::Save(f,NBrightWidthH)==false)
		return false;
	if(::Save(f,NOKDotL)==false)
		return false;
	if(::Save(f,NOKDotH)==false)
		return false;
	if(::Save(f,NOKLengthL)==false)
		return false;
	if(::Save(f,NOKLengthH)==false)
		return false;
	if(::Save(f,BBrightWidthL)==false)
		return false;
	if(::Save(f,BBrightWidthH)==false)
		return false;
	if(::Save(f,BOKDotL)==false)
		return false;
	if(::Save(f,BOKDotH)==false)
		return false;
	if(::Save(f,BOKLengthL)==false)
		return false;
	if(::Save(f,BOKLengthH)==false)
		return false;

	if(f->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;
    if(::Save(f,SelfSearch)==false)
		return false;
    if(::Save(f,CommonMoveDot)==false)
		return false;

    if(::Save(f,NMinNGCountL)==false)
		return false;
    if(::Save(f,NMinNGCountH)==false)
		return false;
    if(::Save(f,BMinNGCountL)==false)
		return false;
    if(::Save(f,BMinNGCountH)==false)
		return false;
	if(::Save(f,NConnectLen)==false)
		return false;
	if(::Save(f,BConnectLen)==false)
		return false;

	if(::Save(f,NMaxNGDotL)==false)
		return false;
	if(::Save(f,NMaxNGDotH)==false)
		return false;
	if(::Save(f,BMaxNGDotL)==false)
		return false;
	if(::Save(f,BMaxNGDotH)==false)
		return false;

	if(::Save(f,DiffBrightWidthL)==false)
		return false;
	if(::Save(f,DiffBrightWidthH)==false)
		return false;

	if(::Save(f,ExpandForGenMask)==false)
		return false;
	if(::Save(f,FollowLineLayer)==false)
		return false;

	return true;
}
bool	BlockLibrary::LoadBlob(QIODevice *f)
{
	int64	CurrentPos=f->pos();

	if(LoadBlobNew(f)==true){
		return true;
	}
	f->seek(CurrentPos);
	if(LoadBlobOld(f)==true){
		return true;
	}
	return false;
}

bool	BlockLibrary::LoadBlobNew(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(SubtractBlock.Load(f)==false)
		return false;

	if(::Load(f,PickupL)==false)
		return false;
	if(::Load(f,PickupH)==false)
		return false;
    if(::Load(f,MinBlockSize)==false)
		return false;
    if(::Load(f,MaxBlockSize)==false)
		return false;
    if(::Load(f,MinBlockDots)==false)
		return false;
    if(::Load(f,MaxBlockDots)==false)
		return false;
    if(::Load(f,LimitBlockSize)==false)
		return false;
	if(Ver>=10018){
		if(::Load(f,RegularBrightness)==false)
			return false;
	}
	else{
		RegularBrightness=-1;
	}
	if(Ver>=10027){
		if(::Load(f,FollowLineLength)==false)
			return false;
	}
	else{
		FollowLineLength=3;
	}
	if(Ver>=10028){
		if(f->read((char *)&GenFollowLine,sizeof(GenFollowLine))!=sizeof(GenFollowLine))
			return false;
	}
	else{
		GenFollowLine.Gen_Left	=true;
		GenFollowLine.Gen_Top	=true;
		GenFollowLine.Gen_Right	=true;
		GenFollowLine.Gen_Bottom=true;
	}
	if(f->read((char *)&GenerationMode,sizeof(GenerationMode))!=sizeof(GenerationMode))
		return false;
	if(f->read((char *)&GenerationCategory,sizeof(GenerationCategory))!=sizeof(GenerationCategory))
		return false;
	if(::Load(f,NoiseSize)==false)
		return false;
	NoiseSizePinHole=NoiseSize;
	if(Ver>=10006){
		if(::Load(f,NoiseSizePinHole)==false)
			return false;
	}
    if(::Load(f,SpaceToOutline)==false)
		return false;
	if(Ver>=10007){
		if(::Load(f,OutlineGeneration)==false)
			return false;
	}
    if(::Load(f,Priority)==false)
		return false;

//????C?f?[?^

	if(::Load(f,NBrightWidthL)==false)
		return false;
	if(::Load(f,NBrightWidthH)==false)
		return false;
	if(::Load(f,NOKDotL)==false)
		return false;
	if(::Load(f,NOKDotH)==false)
		return false;
	if(Ver>=10003){
		if(::Load(f,NOKLengthL)==false)
			return false;
		if(::Load(f,NOKLengthH)==false)
			return false;
	}
	if(::Load(f,BBrightWidthL)==false)
		return false;
	if(::Load(f,BBrightWidthH)==false)
		return false;
	if(::Load(f,BOKDotL)==false)
		return false;
	if(::Load(f,BOKDotH)==false)
		return false;
	if(Ver>=10003){
		if(::Load(f,BOKLengthL)==false)
			return false;
		if(::Load(f,BOKLengthH)==false)
			return false;
	}

	if(Ver<=10014){
		struct{
			bool	ModeEnabled:1;
			bool	ModeAdjustable:1;
			bool	ModeAbsoluteBright:1;
			bool	ModeCommonMovable:1;
			bool	ModeNGCluster:1;
			bool	ModeDiffer:1;
			bool	ModeCenterBrightFromParts:1;
			bool	ModeOnlyMatching:1;
			bool    ModeWhiteMask:1;
			bool    ModeBlackMask:1;
			bool	ModeInvertLogic:1;
			bool	ModeMatchPosition:1;
			bool	ModeSearchDetail:1;
			bool	ModeDynamicMask:1;
			bool	ModeBindBWBroad:1;
			bool	ModeBindBWNarrow:1;
		}TmpPointMove;
		if(f->read((char *)&TmpPointMove,sizeof(TmpPointMove))!=sizeof(TmpPointMove))
			return false;
		PointMove.ModeEnabled			=TmpPointMove.ModeEnabled;
		PointMove.ModeAdjustable		=TmpPointMove.ModeAdjustable;
		PointMove.ModeAbsoluteBright	=TmpPointMove.ModeAbsoluteBright;
		PointMove.ModeCommonMovable		=TmpPointMove.ModeCommonMovable;
		PointMove.ModeNGCluster			=TmpPointMove.ModeNGCluster;
		PointMove.ModeDiffer			=TmpPointMove.ModeDiffer;
		PointMove.ModeCenterBrightFromParts	=TmpPointMove.ModeCenterBrightFromParts;
		PointMove.ModeOnlyMatching		=TmpPointMove.ModeOnlyMatching;
		PointMove.ModeWhiteMask			=TmpPointMove.ModeWhiteMask;
		PointMove.ModeBlackMask			=TmpPointMove.ModeBlackMask;
		PointMove.ModeInvertLogic		=TmpPointMove.ModeInvertLogic;
		PointMove.ModeMatchPosition		=TmpPointMove.ModeMatchPosition;
		PointMove.ModeMatchPositionBW	=false;
		PointMove.ModeSearchDetail		=TmpPointMove.ModeSearchDetail;
		PointMove.ModeDynamicMask		=TmpPointMove.ModeDynamicMask;
		PointMove.ModeBindBWBroad		=TmpPointMove.ModeBindBWBroad;
		PointMove.ModeBindBWNarrow		=TmpPointMove.ModeBindBWNarrow;
		PointMove.ModeOppositeRange		=false;
		PointMove.ModeUseGlobalLine		=false;
	}
	else{
		if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
			return false;
	}

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;
    if(::Load(f,SelfSearch)==false)
		return false;
    if(::Load(f,CommonMoveDot)==false)
		return false;

	if(Ver>=10004){
	    if(::Load(f,NMinNGCountL)==false)
			return false;
	    if(::Load(f,NMinNGCountH)==false)
			return false;
	    if(::Load(f,BMinNGCountL)==false)
			return false;
	    if(::Load(f,BMinNGCountH)==false)
			return false;
	}
	if(Ver>=10005){
		if(::Load(f,NConnectLen)==false)
			return false;
		if(::Load(f,BConnectLen)==false)
			return false;
	}
	if(Ver<10008){
		PointMove.ModeInvertLogic=false;
		PointMove.ModeMatchPosition		=false;
		PointMove.ModeMatchPositionBW	=false;
		GenerationMode.PlusHalfDotIsolation=false;
	}
	if(Ver<10020){
		GenerationMode.BindSmallBlock	=false;
	}
	if(Ver>=10010){
		if(::Load(f,NMaxNGDotL)==false)
			return false;
		if(::Load(f,NMaxNGDotH)==false)
			return false;
		if(::Load(f,BMaxNGDotL)==false)
			return false;
		if(::Load(f,BMaxNGDotH)==false)
			return false;
	}
	if(Ver<10011){
		PointMove.ModeSearchDetail=false;
	}
	if(Ver<10012){
		PointMove.ModeDynamicMask=false;
	}
	if(Ver<10013){
		PointMove.ModeBindBWBroad	=false;
		PointMove.ModeBindBWNarrow	=false;
	}
	if(Ver<10015){
		PointMove.ModeAdoptBiggest	=false;
	}
	if(Ver<10017){
		PointMove.ModeUseMasterImage=false;
	}
	if(Ver>=10014){
		if(::Load(f,DiffBrightWidthL)==false)
			return false;
		if(::Load(f,DiffBrightWidthH)==false)
			return false;
	}
	if(Ver>=10026){
		if(::Load(f,ExpandForGenMask)==false)
			return false;
	}
	if(Ver>=10029){
		if(::Load(f,FollowLineLayer)==false)
			return false;
	}
	else{
		FollowLineLayer=-1;
	}
	if(Ver<10023){
		PointMove.ModeMatchPositionBW	=false;
	}
	if(Ver<10024){
		PointMove.ModeOppositeRange		=false;
	}
	if(Ver<10025){
		PointMove.ModeUseGlobalLine		=true;
	}
	return true;
}

bool	BlockLibrary::LoadBlobOld(QIODevice *f)
{
	if(SubtractBlock.Load(f)==false)
		return false;
	if(::Load(f,PickupL)==false)
		return false;
	if(::Load(f,PickupH)==false)
		return false;
    if(::Load(f,MinBlockSize)==false)
		return false;
    if(::Load(f,MaxBlockSize)==false)
		return false;
    if(::Load(f,MinBlockDots)==false)
		return false;
    if(::Load(f,MaxBlockDots)==false)
		return false;
    if(::Load(f,LimitBlockSize)==false)
		return false;

	if(f->read((char *)&GenerationMode,sizeof(GenerationMode))!=sizeof(GenerationMode))
		return false;
	if(f->read((char *)&GenerationCategory,sizeof(GenerationCategory))!=sizeof(GenerationCategory))
		return false;
	if(::Load(f,NoiseSize)==false)
		return false;
    if(::Load(f,SpaceToOutline)==false)
		return false;
    if(::Load(f,Priority)==false)
		return false;

//????C?f?[?^

	if(::Load(f,NBrightWidthL)==false)
		return false;
	if(::Load(f,NBrightWidthH)==false)
		return false;
	if(::Load(f,NOKDotL)==false)
		return false;
	if(::Load(f,NOKDotH)==false)
		return false;
	if(::Load(f,BBrightWidthL)==false)
		return false;
	if(::Load(f,BBrightWidthH)==false)
		return false;
	if(::Load(f,BOKDotL)==false)
		return false;
	if(::Load(f,BOKDotH)==false)
		return false;

	if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;
    if(::Load(f,SelfSearch)==false)
		return false;
    if(::Load(f,CommonMoveDot)==false)
		return false;
	PointMove.ModeInvertLogic		=false;
	PointMove.ModeMatchPosition		=false;
	PointMove.ModeMatchPositionBW	=false;
	PointMove.ModeSearchDetail		=false;
	PointMove.ModeDynamicMask		=false;
	PointMove.ModeBindBWBroad		=false;
	PointMove.ModeBindBWNarrow		=false;
	PointMove.ModeAdoptBiggest		=false;
	PointMove.ModeUseMasterImage	=false;
	PointMove.ModePermitInverted	=true;
	PointMove.ModeOppositeRange		=false;
	PointMove.ModeUseGlobalLine		=true;
	FollowLineLayer=-1;
	return true;
}


BlockLibrary	&BlockLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((BlockLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	MakeHalfDotOff(BYTE **BmpPoint,int XByte, int YLen)
{
	for(int y=YLen-2;y>=0;y--){
		BYTE	*d=BmpPoint[y+1];
		BYTE	*s=BmpPoint[y];

		d[0] &= s[0]>>1;
		for(int x=1;x<XByte;x++){
			d[x] &= (s[x-1]<<7) | (s[x]>>1);
		}
	}
}

void	MakeHalfDotOn(BYTE **BmpPoint,int XByte, int YLen)
{
	for(int y=0;y<YLen-1;y++){
		BYTE	*d=BmpPoint[y];
		BYTE	*s=BmpPoint[y+1];

		d[XByte-1] |= s[XByte-1]<<1;
		for(int x=0;x<XByte-1;x++){
			d[x] |= (s[x+1]>>7) | (s[x]<<1);
		}
	}
}

void	BlockLibrary::MakePickupTest(int localpage
									 ,ImageBuffer &IBuff 
									 ,const BYTE **MaskBitmap ,const BYTE **LastOcupyMap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;

	//GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(localpage);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	int	YNumb=min(YLen,IBuff.GetHeight());
	int	XNumb=min(XLen,IBuff.GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*src=IBuff.GetY(y);
			BYTE	*dest=BmpPoint[y];
			int		c;
			for(int x=0;x<XNumb;x++,src++){
				c=*src;
				if(PickupL<=c && c<=PickupH){
					dest[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
	GetLayersBase()->StepProcessing(localpage);

	if(MaskBitmap!=NULL){
		if(GenerationMode.Transparent==false){
			MatrixBuffNotAnd (BmpPoint,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines(localpage));
		}
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(localpage);

	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(	 TmpData2				,XByte ,YLen
					,(const BYTE **)BmpPoint,XByte ,YLen);

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSize);
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSize);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);

	for(int y=0;y<OmitZoneDot;y++){
		memset(BmpPoint[y],0,XByte);
	}
	for(int y=0;y<OmitZoneDot;y++){
		memset(BmpPoint[YLen-y-1],0,XByte);
	}
	for(int y=OmitZoneDot;y<YLen-OmitZoneDot;y++){
		for(int x=0;x<OmitZoneDot;x++){
			BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
		}
		for(int x=XLen-OmitZoneDot;x<XLen;x++){
			BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
		}
	}
	DWORD	tm=GetComputerMiliSec();
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSizePinHole);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSizePinHole);

	DWORD	smm=GetComputerMiliSec()-tm;

	if(MaskBitmap!=NULL){
		if(GenerationMode.Transparent==false){
			MatrixBuffNotAnd (BmpPoint,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines(localpage));
		}
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	
	GetLayersBase()->StepProcessing(localpage);
	//BitmapClusterSized(BmpPoint,XByte ,YLen 
	//					,TmpData,TmpData2
	//					   ,MaxBlockSize ,MinBlockSize ,MaxBlockDots ,MinBlockDots
	//					   ,XLen, YLen);

	GetLayersBase()->StepProcessing(localpage);
	if(GenerationCategory==_AutoSetting_OTHERMASK
	|| GenerationCategory==_AutoSetting_SURROUND){
		GetLayersBase()->FatAreaN(BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);
	}
	else{
		GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);
		if(GenerationMode.PlusHalfDotIsolation==true){
			MakeHalfDotOff(BmpPoint,XByte, YLen);
		}
	}
	if(OutlineGeneration<1000){
		if(GenerationCategory==_AutoSetting_OTHERMASK
		|| GenerationCategory==_AutoSetting_SURROUND){
			MatrixBuffCopy(TmpData					,XByte,YLen
			             , (const BYTE **)BmpPoint	,XByte,YLen);

			GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,OutlineGeneration);
			
			MatrixBuffXor(BmpPoint,(const BYTE **)TmpData,XByte,YNumb);

			if(MaskBitmap!=NULL){
				MatrixBuffCopy(TmpData					,XByte,YLen
				             , (const BYTE **)MaskBitmap,XByte,YLen);
				GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,(OutlineGeneration+SpaceToOutline+1));

				MatrixBuffAnd(BmpPoint,(const BYTE **)TmpData,XByte,YNumb);
			}
			int	tmpOmitZoneDot=OmitZoneDot+OutlineGeneration+SpaceToOutline+1;
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(BmpPoint[y],0,XByte);
			}
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(BmpPoint[YLen-y-1],0,XByte);
			}
			for(int y=tmpOmitZoneDot;y<YLen-tmpOmitZoneDot;y++){
				for(int x=0;x<tmpOmitZoneDot;x++){
					BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
				}
				for(int x=XLen-tmpOmitZoneDot;x<XLen;x++){
					BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
				}	
			}
		}		
		else{
			MatrixBuffCopy(TmpData					,XByte,YLen
			             , (const BYTE **)BmpPoint	,XByte,YLen);
			GetLayersBase()->ThinAreaN(TmpData,TmpData2 ,XByte, YLen,OutlineGeneration);
			MatrixBuffXor(BmpPoint,(const BYTE **)TmpData,XByte,YNumb);

			if(MaskBitmap!=NULL){
				MatrixBuffCopy(TmpData					,XByte,YLen
				             , (const BYTE **)MaskBitmap,XByte,YLen);
				GetLayersBase()->ThinAreaN(TmpData,TmpData2 ,XByte, YLen,(OutlineGeneration+SpaceToOutline+1));
				MatrixBuffAnd(BmpPoint,(const BYTE **)TmpData,XByte,YNumb);
			}
			int	tmpOmitZoneDot=OmitZoneDot+OutlineGeneration+SpaceToOutline+1;
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(BmpPoint[y],0,XByte);
			}
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(BmpPoint[YLen-y-1],0,XByte);
			}
			for(int y=tmpOmitZoneDot;y<YLen-tmpOmitZoneDot;y++){
				for(int x=0;x<tmpOmitZoneDot;x++){
					BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
				}
				for(int x=XLen-tmpOmitZoneDot;x<XLen;x++){
					BmpPoint[y][x>>3] &= ~(0x80>>(x&7));
				}	
			}
		}
	}

	DeleteMatrixBuff(TmpData2,YLen);

	if(0<MinBlockDots || 0<MinBlockSize || MaxBlockSize<GetDotPerLine(localpage) || MaxBlockSize<GetMaxLines(localpage)
	|| MaxBlockDots<2000000000 || MaxBlockDots<GetDotPerLine(localpage)*GetMaxLines(localpage)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	DotN=a->GetPatternByte();
			if((((int64)MinBlockDots)<=DotN && (MaxBlockDots<0 || DotN<=((int64)MaxBlockDots))) 
			&& MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}

	GetLayersBase()->StepProcessing(localpage);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);

		if(GenerationCategory==_AutoSetting_OTHERMASK
			|| GenerationCategory==_AutoSetting_SURROUND){
		}
		else{
			if(GenerationMode.PlusHalfDotIsolation==true){
				MakeHalfDotOn(OcupyMap,XByte, YLen);
			}
			GetLayersBase()->FatAreaN(OcupyMap,TmpData ,XByte, YLen,SpaceToOutline);
		}
	}

	DeleteMatrixBuff(TmpData,YLen);
	GetLayersBase()->StepProcessing(localpage);
}



class	PureFlexAreaListPoint : public NPList<PureFlexAreaListPoint>
{
public:
	PureFlexAreaList	*Point;
	PureFlexAreaListPoint(PureFlexAreaList *p){	Point=p;	}
};


void	BlockLibrary::MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList)
{
	//GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(localpage);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	PureFlexAreaListContainer	L3List;

	if(GenerationMode.Transparent==false){
		int	XNumbInt =XByte/sizeof(unsigned int);
		int	XNumbLeft=XByte%sizeof(unsigned int);
		for(int y=0;y<YLen;y++){
			unsigned int	*Src=(unsigned int *)OcupyMap[y];
			unsigned int	*Dst=(unsigned int *)CurrentMap[y];
			for(int x=0;x<XNumbInt;x++,Src++,Dst++){
				*Dst &= ~*Src;
			}
			BYTE	*S=(BYTE *)Src;
			BYTE	*D=(BYTE *)Dst;
			for(int x=0;x<XNumbLeft;x++,S++,D++){
				*D &= ~*S;
			}
		}
	}
	GetLayersBase()->StepProcessing(localpage);

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		GetLayersBase()->StepProcessing(localpage);

		/*
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
			int	DotN=a->GetPatternByte();
			if((MinBlockDots<=0 && MinBlockSize<=0 && GetDotPerLine()<MaxBlockSize && GetMaxLines()<MaxBlockSize
			&& (2000000000<=MaxBlockDots || GetDotPerLine()*GetMaxLines()<=MaxBlockDots))
			|| (MinBlockDots<=DotN && DotN<=MaxBlockDots && MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize)){
				a=a->GetNext();
			}
			else{
				PureFlexAreaList *NextA=a->GetNext();
				FPack.RemoveList(a);
				delete	a;
				a=NextA;
			}
		}
		*/

		GetLayersBase()->StepProcessing(localpage);
		PureFlexAreaList *a;

		int	N=FPack.GetCount();
		PureFlexAreaList **PureFlexAreaPointerDim=new PureFlexAreaList *[N];
		int	i=0;
		while((a=FPack.GetFirst())!=NULL){
			FPack.RemoveList(a);
			PureFlexAreaPointerDim[i]=a;
			i++;
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int k=0;k<N;k++){
				PureFlexAreaList *h=PureFlexAreaPointerDim[k];

				PureFlexAreaListContainer Piece;
				if(LimitBlockSize==0 || (h->GetWidth()<LimitBlockSize && h->GetHeight()<LimitBlockSize)){
					Piece.AppendList(h);
					h=NULL;
				}
				else{
					h->ChopRect(Piece ,LimitBlockSize);
				}
				PureFlexAreaList *b;
				while((b=Piece.GetFirst())!=NULL){
					Piece.RemoveList(b);
					#pragma omp critical
					{
						L3List.AppendList(b);
					}
				}
				if(h!=NULL){
					delete	h;
				}
			}
		}
		delete	[]PureFlexAreaPointerDim;
	}	
	catch(...){}

	GetLayersBase()->StepProcessing(localpage);

	if(GenerationMode.OverlappedGen==true){
		PureFlexAreaListContainer	L3Other;
		PureFlexAreaList *a;
		int	OverlappedLen=SelfSearch;	//SelfSearch+CommonMoveDot
		BYTE	SavBuffBuff [10000];
		BYTE	TmpImageBuff [10000];
		BYTE	TmpImageBuff2[10000];
		while((a=L3List.GetFirst())!=NULL){
			L3List.RemoveList(a);
			
			int	XLen=a->GetWidth()+OverlappedLen*2+2+16;
			int	XByte=(XLen+7)/8;
			int	YLen=a->GetHeight()+OverlappedLen*2+2;
			BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen,TmpImageBuff,sizeof(TmpImageBuff));
			BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen,TmpImageBuff2,sizeof(TmpImageBuff2));
			MatrixBuffClear(TmpBuff,0,XByte,YLen);
			int	dx=-a->GetMinX()+OverlappedLen+8;
			int	dy=-a->GetMinY()+OverlappedLen;

			a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);

			BYTE	**SavBuff =MakeMatrixBuff(XByte ,YLen,SavBuffBuff,sizeof(SavBuffBuff));
			MatrixBuffCopy(SavBuff		  ,XByte,YLen
					     , (const BYTE **)TmpBuff,XByte,YLen);

			GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,OverlappedLen);

			for(int y=0;y<YLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetMaxLines(localpage))
					break;
				BYTE	*YPoint	=TmpBuff[y];
				BYTE	*YSrc	=TmpData[y-dy];
				int	sx=-dx;
				if(sx+XLen>GetDotPerLine(localpage))
					XLen=GetDotPerLine(localpage)-sx;
				for(int x=0;x<XLen;x++,sx++){
					if(sx<0){
						YPoint[x>>3] &= ~(0x80>>(x&7));
						continue;
					}
					if((YPoint[x>>3]&(0x80>>(x&7)))!=0){
						if((YSrc[sx>>3]&(0x80>>(sx&7)))==0)
							YPoint[x>>3] &= ~(0x80>>(x&7));
					}
				}
			}
			PureFlexAreaListContainer PFPack;
			::PickupFlexArea(TmpBuff,XByte ,XLen,YLen ,PFPack);

			for(PureFlexAreaList *t=PFPack.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->CheckOverlapBit(SavBuff,XLen,YLen)==true){
					PureFlexAreaList	*K=new PureFlexAreaList();
					*((FlexArea *)K)=*((FlexArea *)t);
					K->MoveToNoClip(-dx,-dy);
					L3Other.AppendList(K);
				}
			}
			delete	a;
			//a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
			if((BYTE	**)TmpImageBuff!=TmpBuff){
				DeleteMatrixBuff(TmpBuff,YLen);
			}
			if((BYTE	**)TmpImageBuff2!=TmpBuff2){
				DeleteMatrixBuff(TmpBuff2,YLen);
			}
			if((BYTE	**)SavBuffBuff!=SavBuff){
				DeleteMatrixBuff(SavBuff,YLen);
			}
		}
		L3List.Move(L3Other);
	}
	DeleteMatrixBuff(TmpData,YLen);

	GetLayersBase()->StepProcessing(localpage);

	if(GenerationMode.BindSmallBlock==true){
		int	MinAreaDot=LimitBlockSize*LimitBlockSize*0.75;
		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;){
			if(a->GetPatternByte()<MinAreaDot){
				int	Cx,Cy;
				a->GetCenter(Cx,Cy);
				int	mx1,my1,mx2,my2;
				a->GetXY(mx1,my1,mx2,my2);
				double	MinL=99999999;
				PureFlexAreaList *m=NULL;
				for(PureFlexAreaList *b=L3List.GetFirst();b!=NULL;b=b->GetNext()){
					if(a!=b){
						int	nx1,ny1,nx2,ny2;
						b->GetXY(nx1,ny1,nx2,ny2);
						if(CheckOverlapRectRect(mx1-1,my1-1,mx2+1,my2+1 ,nx1,ny1,nx2,ny2)==true){
							int	Qx,Qy;
							b->GetCenter(Qx,Qy);
							
							double	L=hypot(Cx-Qx,Cy-Qy);
							if(L<MinL){
								m=b;
								MinL=L;
							}
						}
					}
				}
				if(m!=NULL){
					L3List.RemoveList(m);
					*a+=*m;
				}
				else{
					a=a->GetNext();
				}
			}
			else{
				a=a->GetNext();
			}
		}
	}
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(localpage),GetMaxLines(localpage));
		if(a->GetPatternByte()<5)
			continue;
		BlockItem	*v=new BlockItem(*a);
		if(GenerationMode.LockFirst==true){
			v->SetEditLocked(true);
		}
		if(RegularBrightness>=0){
			v->CenterBright=RegularBrightness;
		}
		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}


	GetLayersBase()->StepProcessing(localpage);
}

void	BlockLibrary::MakeBlockOnly(int localpage
			,BYTE **CurrentMap,const BYTE **MaskMap ,BYTE **DriftMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList
			,int OmitZoneDot)
{
	GetLayersBase()->AddMaxProcessing(localpage,5);
	GetLayersBase()->StepProcessing(localpage);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	if(GenerationCategory==_AutoSetting_OTHERMASK
	|| GenerationCategory==_AutoSetting_SURROUND){
		GetLayersBase()->FatAreaN(CurrentMap,TmpData ,XByte, YLen,SpaceToOutline);
	}
	else{
		int	MinLeave=1;
		if(SpaceToOutline<=MinLeave){
			GetLayersBase()->ThinAreaN(CurrentMap,TmpData ,XByte, YLen ,SpaceToOutline);
		}
		else{
			int	Step1=SpaceToOutline-MinLeave;

			GetLayersBase()->ThinAreaN(CurrentMap,TmpData ,XByte, YLen,Step1);
	
			BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
			BYTE	**TmpData3=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffCopy(TmpData2					,XByte,YLen
			             , (const BYTE **)CurrentMap,XByte,YLen);

			GetLayersBase()->ThinAreaN(TmpData2,TmpData ,XByte, YLen,MinLeave);

			MatrixBuffCopy(TmpData3					,XByte,YLen
			             , (const BYTE **)TmpData2,XByte,YLen);
			ThinArea(TmpData2,TmpData ,XByte, YLen);

			GetLayersBase()->FatAreaN(TmpData2,TmpData ,XByte, YLen,(MinLeave+1));

			MatrixBuffNotAnd(CurrentMap,(const BYTE **)TmpData2,XByte,YLen);
			MatrixBuffOr	(CurrentMap,(const BYTE **)TmpData3,XByte,YLen);

			DeleteMatrixBuff(TmpData2,YLen);
			DeleteMatrixBuff(TmpData3,YLen);
		}
		if(GenerationMode.PlusHalfDotIsolation==true){
			MakeHalfDotOff(CurrentMap,XByte, YLen);
		}
	}

	if(OutlineGeneration<1000){
		if(GenerationCategory==_AutoSetting_OTHERMASK
		|| GenerationCategory==_AutoSetting_SURROUND){
			BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);

			MatrixBuffCopy(TmpData					,XByte,YLen
			             , (const BYTE **)CurrentMap,XByte,YLen);

			GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,OutlineGeneration);
			
			MatrixBuffXor(CurrentMap,(const BYTE **)TmpData,XByte,YLen);

			if(MaskMap!=NULL){
				MatrixBuffCopy(TmpData	,XByte,YLen
				             , MaskMap	,XByte,YLen);

				GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,(OutlineGeneration+SpaceToOutline+1));

				MatrixBuffAnd(CurrentMap,(const BYTE **)TmpData,XByte,YLen);
			}
			int	tmpOmitZoneDot=OmitZoneDot+OutlineGeneration+SpaceToOutline+1;
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(CurrentMap[y],0,XByte);
			}
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(CurrentMap[YLen-y-1],0,XByte);
			}
			for(int y=tmpOmitZoneDot;y<YLen-tmpOmitZoneDot;y++){
				for(int x=0;x<tmpOmitZoneDot;x++){
					CurrentMap[y][x>>3] &= ~(0x80>>(x&7));
				}
				for(int x=XLen-tmpOmitZoneDot;x<XLen;x++){
					CurrentMap[y][x>>3] &= ~(0x80>>(x&7));
				}	
			}
			DeleteMatrixBuff(TmpData2,YLen);
		}		
		else{
			BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);

			MatrixBuffCopy(TmpData					,XByte,YLen
			             , (const BYTE **)CurrentMap,XByte,YLen);
			GetLayersBase()->ThinAreaN(TmpData,TmpData2 ,XByte, YLen ,OutlineGeneration);
			MatrixBuffXor(CurrentMap,(const BYTE **)TmpData,XByte,YLen);

			if(MaskMap!=NULL){
				MatrixBuffCopy(TmpData	,XByte,YLen
				             , MaskMap	,XByte,YLen);
				GetLayersBase()->ThinAreaN(TmpData,TmpData2 ,XByte, YLen ,(OutlineGeneration+SpaceToOutline+1));
				MatrixBuffAnd(CurrentMap,(const BYTE **)TmpData,XByte,YLen);
			}
			int	tmpOmitZoneDot=OmitZoneDot+OutlineGeneration+SpaceToOutline+1;
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(CurrentMap[y],0,XByte);
			}
			for(int y=0;y<tmpOmitZoneDot;y++){
				memset(CurrentMap[YLen-y-1],0,XByte);
			}
			for(int y=tmpOmitZoneDot;y<YLen-tmpOmitZoneDot;y++){
				for(int x=0;x<tmpOmitZoneDot;x++){
					CurrentMap[y][x>>3] &= ~(0x80>>(x&7));
				}
				for(int x=XLen-tmpOmitZoneDot;x<XLen;x++){
					CurrentMap[y][x>>3] &= ~(0x80>>(x&7));
				}	
			}
			DeleteMatrixBuff(TmpData2,YLen);
		}
	}

	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);
	PureFlexAreaListContainer	L3List;
	PureFlexAreaListContainer	FPackDrift;
	try{
		if(DriftMap!=NULL)
			MatrixBuffAnd	(DriftMap,(const BYTE **)CurrentMap ,XByte,YLen);
		PureFlexAreaListContainer FPack1;
		if(DriftMap!=NULL)
			PickupFlexArea(DriftMap,XByte,XLen,YLen ,FPack1);

		if(DriftMap!=NULL)
			MatrixBuffNotAnd(CurrentMap ,(const BYTE **)DriftMap ,XByte,YLen);
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);

		GetLayersBase()->StepProcessing(localpage);
		PureFlexAreaList *a;

		{
			int	N=FPack.GetCount();
			PureFlexAreaList **PureFlexAreaPointerDim=new PureFlexAreaList *[N];
			int	i=0;
			while((a=FPack.GetFirst())!=NULL){
				FPack.RemoveList(a);
				int64	DotN=a->GetPatternByte();
				if((((int64)MinBlockDots)<=DotN && (MaxBlockDots<0 || DotN<=((int64)MaxBlockDots))) 
				&& MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize){
					PureFlexAreaPointerDim[i]=a;
					i++;
				}
				else{
					delete	a;
				}
			}
			N=i;

			#pragma omp parallel
			{
				#pragma omp for
				for(int k=0;k<N;k++){
					PureFlexAreaList *h=PureFlexAreaPointerDim[k];

					PureFlexAreaListContainer Piece;
					if(LimitBlockSize==0 || (h->GetWidth()<LimitBlockSize && h->GetHeight()<LimitBlockSize)){
						Piece.AppendList(h);
						h=NULL;
					}
					else{
						h->ChopRect(Piece ,LimitBlockSize);
					}
					PureFlexAreaList *b;
					while((b=Piece.GetFirst())!=NULL){
						Piece.RemoveList(b);
						#pragma omp critical
						{
							L3List.AppendList(b);
						}
					}
					if(h!=NULL){
						delete	h;
					}
				}
			}
			delete	[]PureFlexAreaPointerDim;
		}
		{
			int	N=FPack1.GetCount();
			PureFlexAreaList **PureFlexAreaPointerDim=new PureFlexAreaList *[N];
			int	i=0;
			while((a=FPack1.GetFirst())!=NULL){
				FPack1.RemoveList(a);
				int64	DotN=a->GetPatternByte();
				if(((int64)MinBlockDots)<=DotN && (MaxBlockDots<0 || DotN<=((int64)MaxBlockDots))
				&& MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize){
					PureFlexAreaPointerDim[i]=a;
					i++;
				}
				else{
					delete	a;
				}
			}
			N=i;

			#pragma omp parallel
			{
				#pragma omp for
				for(int k=0;k<N;k++){
					PureFlexAreaList *h=PureFlexAreaPointerDim[k];

					PureFlexAreaListContainer Piece;
					if(LimitBlockSize==0 || (h->GetWidth()<LimitBlockSize && h->GetHeight()<LimitBlockSize)){
						Piece.AppendList(h);
						h=NULL;
					}
					else{
						h->ChopRect(Piece ,LimitBlockSize);
					}
					PureFlexAreaList *b;
					while((b=Piece.GetFirst())!=NULL){
						Piece.RemoveList(b);
						#pragma omp critical
						{
							FPackDrift.AppendList(b);
						}
					}
					if(h!=NULL){
						delete	h;
					}
				}
			}
			delete	[]PureFlexAreaPointerDim;
		}
	}	
	catch(...){}

	GetLayersBase()->StepProcessing(localpage);

	int	OverlappedLen=SelfSearch;	//SelfSearch+CommonMoveDot
	if(GenerationMode.OverlappedGen==true){
		PureFlexAreaListContainer	L3Other;
		PureFlexAreaList *a;
		while((a=L3List.GetFirst())!=NULL){
			L3List.RemoveList(a);

			int	XLen=a->GetWidth()+OverlappedLen*2+2+16;
			int	XByte=(XLen+7)/8;
			int	YLen=a->GetHeight()+OverlappedLen*2+2;
			BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
			BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffClear(TmpBuff,0,XByte,YLen);
			int	dx=-a->GetMinX()+OverlappedLen+8;
			int	dy=-a->GetMinY()+OverlappedLen;

			a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
			BYTE	**SavBuff =MakeMatrixBuff(XByte ,YLen);
			MatrixBuffCopy(SavBuff		  ,XByte,YLen
					     , (const BYTE **)TmpBuff,XByte,YLen);

			GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,OverlappedLen);
			
			for(int y=0;y<YLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetMaxLines(localpage))
					break;
				BYTE	*YPoint	=TmpBuff[y];
				BYTE	*YSrc	=CurrentMap[y-dy];
				int	sx=-dx;
				if(sx+XLen>GetDotPerLine(localpage))
					XLen=GetDotPerLine(localpage)-sx;
				for(int x=0;x<XLen;x++,sx++){
					if(sx<0){
						YPoint[x>>3] &= ~(0x80>>(x&7));
						continue;
					}
					if((YPoint[x>>3]&(0x80>>(x&7)))!=0){
						if((YSrc[sx>>3]&(0x80>>(sx&7)))==0)
							YPoint[x>>3] &= ~(0x80>>(x&7));
					}
				}
			}
			PureFlexAreaListContainer PFPack;
			::PickupFlexArea(TmpBuff,XByte ,XLen,YLen ,PFPack);

			for(PureFlexAreaList *t=PFPack.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->CheckOverlapBit(SavBuff,XLen,YLen)==true){
					PureFlexAreaList	*K=new PureFlexAreaList();
					*((FlexArea *)K)=*((FlexArea *)t);
					K->MoveToNoClip(-dx,-dy);
					L3Other.AppendList(K);
				}
			}
			delete	a;
			//a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
			DeleteMatrixBuff(TmpBuff,YLen);
			DeleteMatrixBuff(TmpBuff2,YLen);
			DeleteMatrixBuff(SavBuff,YLen);
		}
		L3List.Move(L3Other);
	}		
	if(GenerationMode.OverlappedGen==true){
		PureFlexAreaListContainer	L3Other;

		BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
		MatrixBuffCopy	(TmpData			, XByte , YLen
					,(const BYTE **)DriftMap, XByte , YLen);
		GetLayersBase()->FatAreaN(TmpData,TmpData2 ,XByte, YLen,SelfSearch);
		MatrixBuffCopy	(TmpData2			, XByte , YLen
					,(const BYTE **)DriftMap, XByte , YLen);
		MatrixBuffOr	(TmpData2 ,(const BYTE **)CurrentMap ,XByte , YLen);
		MatrixBuffAnd	(TmpData  ,(const BYTE **)TmpData2   ,XByte , YLen);
		DeleteMatrixBuff(TmpData2,YLen);

		PureFlexAreaList *a;
		bool	Dbg=false;
		while((a=FPackDrift.GetFirst())!=NULL){
			FPackDrift.RemoveList(a);
			int	XMergin=16;
			int	YMergin=8;

			int	XLen=a->GetWidth()+OverlappedLen*2+2+XMergin*2;
			int	XByte=(XLen+7)/8;
			int	YLen=a->GetHeight()+OverlappedLen*2+2+YMergin*2;
			BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
			BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffClear(TmpBuff,0,XByte,YLen);
			int	dx=-a->GetMinX()+OverlappedLen+XMergin;
			int	dy=-a->GetMinY()+OverlappedLen+YMergin;

			a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
			BYTE	**SavBuff =MakeMatrixBuff(XByte ,YLen);
			MatrixBuffCopy(SavBuff		  ,XByte,YLen
					     , (const BYTE **)TmpBuff,XByte,YLen);
			GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,OverlappedLen);
			
			for(int y=0;y<YLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetMaxLines(localpage))
					break;
				BYTE	*YPoint	=TmpBuff[y];
				BYTE	*YSrc	=TmpData[y-dy];
				int	sx=-dx;
				if(sx+XLen>GetDotPerLine(localpage))
					XLen=GetDotPerLine(localpage)-sx;
				for(int x=0;x<XLen;x++,sx++){
					if(sx<0){
						YPoint[x>>3] &= ~(0x80>>(x&7));
						continue;
					}
					if((YPoint[x>>3]&(0x80>>(x&7)))!=0){
						if((YSrc[sx>>3]&(0x80>>(sx&7)))==0)
							YPoint[x>>3] &= ~(0x80>>(x&7));
					}
				}
			}
			for(int y=0;y<YMergin;y++){
				BYTE	*d1=TmpBuff[y];
				memset(d1,0,XByte);
				BYTE	*d2=TmpBuff[YLen-y-1];
				memset(d2,0,XByte);
			}
			for(int x=0;x<XMergin;x++){
				for(int y=YMergin;y<YLen-YMergin;y++){
					BYTE	*d=TmpBuff[y];
					SetBmpBitOnY0(d,x);
					SetBmpBitOnY0(d,XLen-x-1);
				}
			}

			PureFlexAreaListContainer PFPack;
			::PickupFlexArea(TmpBuff,XByte ,XLen,YLen ,PFPack);

			for(PureFlexAreaList *t=PFPack.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->CheckOverlapBit(SavBuff,XLen,YLen)==true){
					PureFlexAreaList	*K=new PureFlexAreaList();
					*((FlexArea *)K)=*((FlexArea *)t);
					K->MoveToNoClip(-dx,-dy);
					if(K->IsInclude(3474,12636)==true)
						Dbg=true;
					L3Other.AppendList(K);
				}
			}
			delete	a;
			//a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
			DeleteMatrixBuff(TmpBuff,YLen);
			DeleteMatrixBuff(TmpBuff2,YLen);
			DeleteMatrixBuff(SavBuff,YLen);
		}
		FPackDrift.Move(L3Other);
	}		
	DeleteMatrixBuff(TmpData,YLen);
	GetLayersBase()->StepProcessing(localpage);

	if(GenerationMode.BindSmallBlock==true){
		int	MinAreaDot=LimitBlockSize*LimitBlockSize*0.75;
		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;){
			if(a->GetPatternByte()<MinAreaDot){
				int	Cx,Cy;
				a->GetCenter(Cx,Cy);
				int	mx1,my1,mx2,my2;
				a->GetXY(mx1,my1,mx2,my2);
				double	MinL=99999999;
				PureFlexAreaList *m=NULL;
				for(PureFlexAreaList *b=L3List.GetFirst();b!=NULL;b=b->GetNext()){
					if(a!=b){
						int	nx1,ny1,nx2,ny2;
						b->GetXY(nx1,ny1,nx2,ny2);
						if(CheckOverlapRectRect(mx1-1,my1-1,mx2+1,my2+1 ,nx1,ny1,nx2,ny2)==true){
							int	Qx,Qy;
							b->GetCenter(Qx,Qy);
							
							double	L=hypot(Cx-Qx,Cy-Qy);
							if(L<MinL){
								m=b;
								MinL=L;
							}
						}
					}
				}
				if(m!=NULL){
					L3List.RemoveList(m);
					*a+=*m;
				}
				else{
					a=a->GetNext();
				}
			}
			else{
				a=a->GetNext();
			}
		}
		for(PureFlexAreaList *a=FPackDrift.GetFirst();a!=NULL;){
			if(a->GetPatternByte()<MinAreaDot){
				int	Cx,Cy;
				a->GetCenter(Cx,Cy);
				int	mx1,my1,mx2,my2;
				a->GetXY(mx1,my1,mx2,my2);
				double	MinL=99999999;
				PureFlexAreaList *m=NULL;
				for(PureFlexAreaList *b=FPackDrift.GetFirst();b!=NULL;b=b->GetNext()){
					if(a!=b){
						int	nx1,ny1,nx2,ny2;
						b->GetXY(nx1,ny1,nx2,ny2);
						if(CheckOverlapRectRect(mx1-1,my1-1,mx2+1,my2+1 ,nx1,ny1,nx2,ny2)==true){
							int	Qx,Qy;
							b->GetCenter(Qx,Qy);
							
							double	L=hypot(Cx-Qx,Cy-Qy);
							if(L<MinL){
								m=b;
								MinL=L;
							}
						}
					}
				}
				if(m!=NULL){
					FPackDrift.RemoveList(m);
					*a+=*m;
				}
				else{
					a=a->GetNext();
				}
			}
			else{
				a=a->GetNext();
			}
		}
	}
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(localpage),GetMaxLines(localpage));
		if(a->GetPatternByte()<5)
			continue;

		BlockItem	*v=new BlockItem(a);
		if(GenerationMode.LockFirst==true){
			v->SetEditLocked(true);
		}
		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		if(RegularBrightness>=0){
			v->CenterBright=RegularBrightness;
		}
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}
	for(PureFlexAreaList *a=FPackDrift.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(localpage),GetMaxLines(localpage));
		if(a->GetPatternByte()<5)
			continue;

		BlockItem	*v=new BlockItem(a);
		if(GenerationMode.LockFirst==true){
			v->SetEditLocked(true);
		}
		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		if(RegularBrightness>=0){
			v->CenterBright=RegularBrightness;
		}
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}
	GetLayersBase()->StepProcessing(localpage);
}

//==============================================================================

BlockLibraryContainer::BlockLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
BlockLibraryContainer::~BlockLibraryContainer(void)
{
}


