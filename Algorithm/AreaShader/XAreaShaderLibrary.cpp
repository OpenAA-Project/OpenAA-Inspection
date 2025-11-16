/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaShader\XAreaShader.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaShader.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaShaderPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>

AreaShaderLibrary::AreaShaderLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupColorL=0;
	PickupColorH=255;

	MaxDot=90000;
	MinDot=20;
	ShrinkDot=3;
	Priority=100;
	MaxSize	=500;
	MinSize	=50;
	GenerateOverlap	=true;

	CellSize=50;
	AdoptRate=80;	//Ì—p—¦
	Fixed	=false;
	Average	=0;
	Sigma	=0;
	PreProcessingMode=true;
}

AreaShaderLibrary::~AreaShaderLibrary(void)
{
}

bool	AreaShaderLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=5;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MaxDot)==false)
		return false;
	if(::Save(f,MinDot)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,PickupColorL)==false)
		return false;
	if(::Save(f,PickupColorH)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,MaxSize)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,GenerateOverlap)==false)
		return false;

	if(::Save(f,CellSize)==false)
		return false;
	if(::Save(f,AdoptRate)==false)
		return false;
	if(::Save(f,Fixed)==false)
		return false;
	if(::Save(f,Average)==false)
		return false;
	if(::Save(f,Sigma)==false)
		return false;
	if(::Save(f,PreProcessingMode)==false)
		return false;
	return true;
}
bool	AreaShaderLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=3){
		if(::Load(f,MaxDot)==false)
			return false;
		if(::Load(f,MinDot)==false)
			return false;
		if(::Load(f,ShrinkDot)==false)
			return false;
		if(::Load(f,PickupColorL)==false)
			return false;
		if(::Load(f,PickupColorH)==false)
			return false;
		if(::Load(f,Priority)==false)
			return false;
		if(::Load(f,MaxSize)==false)
			return false;
		if(::Load(f,MinSize)==false)
			return false;
		if(Ver>=4){
			if(::Save(f,GenerateOverlap)==false)
				return false;
		}
	}

	if(::Load(f,CellSize)==false)
		return false;
	if(::Load(f,AdoptRate)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,Fixed)==false)
			return false;
		if(::Load(f,Average)==false)
			return false;
		if(::Load(f,Sigma)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,PreProcessingMode)==false)
			return false;
	}
	return true;
}
AreaShaderLibrary	&AreaShaderLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AreaShaderLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


void	AreaShaderLibrary::MakePickupTest(ImageBuffer *MasterImage
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;

	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	int	YNumb=min(YLen,MasterImage->GetHeight());
	int	XNumb=min(XLen,MasterImage->GetWidth());

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*src=MasterImage->GetY(y);
			BYTE	*dest=BmpPoint[y];
			int		c;
			for(int x=0;x<XNumb;x++,src++){
				c=*src;
				if(PickupColorL<=c && c<=PickupColorH){
					dest[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
	GetLayersBase()->StepProcessing(-1);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(	 TmpData2				,XByte ,YLen
					,(const BYTE **)BmpPoint,XByte ,YLen);

	for(int i=0;i<1;i++)
		ThinArea(BmpPoint,TmpData ,XByte, YLen);
	for(int i=0;i<1;i++)
		FatArea(BmpPoint,TmpData ,XByte, YLen);

	MatrixBuffAnd	(BmpPoint,(const BYTE **)TmpData2,XByte,YLen);
	DeleteMatrixBuff(TmpData2,YLen);

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

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	
	GetLayersBase()->StepProcessing(-1);
	//BitmapClusterSized(BmpPoint,XByte ,YLen 
	//					,TmpData,TmpData2
	//					   ,MaxBlockSize ,MinBlockSize ,MaxBlockDots ,MinBlockDots
	//					   ,XLen, YLen);

	GetLayersBase()->StepProcessing(-1);

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,ShrinkDot);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
	MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		int	DotN=a->GetPatternByte();
		int	W=a->GetWidth();
		int	H=a->GetHeight();
		int	MinLen=min(W,H);
		int	MaxLen=max(W,H);
		if(MinDot<=DotN && DotN<=MaxDot && MinSize<=MinLen && MaxLen<MaxSize){
			a->MakeBitData(BmpPoint,XLen ,YLen);
		}
	}

	GetLayersBase()->FatAreaN(BmpPoint,TmpData ,XByte, YLen,ShrinkDot);

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);
	}

	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}

void	AreaShaderLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList)
{
	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	for(int i=0;i<ShrinkDot;i++){
		ThinArea(CurrentMap,TmpData ,XByte, YLen);
	}

	PureFlexAreaListContainer FPack;
	PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
		PureFlexAreaList *NextA=a->GetNext();
		int	DotN=a->GetPatternByte();
		if(DotN<MinDot || MaxDot<DotN){
			FPack.RemoveList(a);
			delete	a;
		}
		a=NextA;
	}

	PureFlexAreaList *a;
	while((a=FPack.GetFirst())!=NULL){
		FPack.RemoveList(a);
		AreaShaderItem	*v=new AreaShaderItem();
		v->SetArea(*a);
		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}
	DeleteMatrixBuff(TmpData,YLen);
}

