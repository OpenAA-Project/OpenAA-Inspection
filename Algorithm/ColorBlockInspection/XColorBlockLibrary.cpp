/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ColorBlockFormResource.h"

#include "XColorBlockLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XColorBlockInspection.h"
#include "NGTypeDialog.h"

ColorBlockLibNGTypeItem::ColorBlockLibNGTypeItem(LayersBase *base)
	:LibNGTypeItem(base)
{
	MinColorR=0;
	MaxColorR=255;
	MinColorG=0;
	MaxColorG=255;
	MinColorB=0;
	MaxColorB=255;
	MinSize=0;
	MaxSize=9999;
	MinRoundRate=0;
	MaxRoundRate=100;
}

bool	ColorBlockLibNGTypeItem::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MinColorR)==false)
		return false;
	if(::Save(f,MaxColorR)==false)
		return false;
	if(::Save(f,MinColorG)==false)
		return false;
	if(::Save(f,MaxColorG)==false)
		return false;
	if(::Save(f,MinColorB)==false)
		return false;
	if(::Save(f,MaxColorB)==false)
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
bool	ColorBlockLibNGTypeItem::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,MinColorR)==false)
		return false;
	if(::Load(f,MaxColorR)==false)
		return false;
	if(::Load(f,MinColorG)==false)
		return false;
	if(::Load(f,MaxColorG)==false)
		return false;
	if(::Load(f,MinColorB)==false)
		return false;
	if(::Load(f,MaxColorB)==false)
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

bool	ColorBlockLibNGTypeItem::ShowSetting(void)
{
	NGTypeDialog	D(GetLayersBase(),this);
	D.exec();
	return true;
}

//============================================================

ColorBlockLibrary::InspectionData::InspectionData(void)
{
//????C?f?[?^
	NBrightWidthL	=0;
	NBrightWidthH	=0;
	NOKDotL			=0;
	NOKDotH			=0;
	BBrightWidthL	=0;
	BBrightWidthH	=0;
	BOKDotL			=0;
	BOKDotH			=0;

	NMinNGCountL	=0;
	NMinNGCountH	=0;
	BMinNGCountL	=0;
	BMinNGCountH	=0;

	BOKLengthL		=0;
	BOKLengthH		=0;
	NOKLengthL		=0;
	NOKLengthH		=0;

    AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    AdjustWhite		=20;    //?P?x?a?3?I?a?A??
}
ColorBlockLibrary::InspectionData	&ColorBlockLibrary::InspectionData::operator=(InspectionData &src)
{
	NBrightWidthL	=src.NBrightWidthL;
	NBrightWidthH	=src.NBrightWidthH;
	NOKDotL			=src.NOKDotL;
	NOKDotH			=src.NOKDotH;
	BBrightWidthL	=src.BBrightWidthL;
	BBrightWidthH	=src.BBrightWidthH;
	BOKDotL			=src.BOKDotL;
	BOKDotH			=src.BOKDotH;

    AdjustBlack		=src.AdjustBlack;    //?P?x?a?3?I?o?A??
    AdjustWhite		=src.AdjustWhite;    //?P?x?a?3?I?a?A??

	NMinNGCountL	=src.NMinNGCountL;
	NMinNGCountH	=src.NMinNGCountH;
	BMinNGCountL	=src.BMinNGCountL;
	BMinNGCountH	=src.BMinNGCountH;

	BOKLengthL		=src.BOKLengthL;
	BOKLengthH		=src.BOKLengthH;
	NOKLengthL		=src.NOKLengthL;
	NOKLengthH		=src.NOKLengthH;

	return *this;
}
bool	ColorBlockLibrary::InspectionData::Save(QIODevice *f)
{
	WORD	Ver=ColorBlockInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,NBrightWidthL)==false)
		return false;
	if(::Save(f,NBrightWidthH)==false)
		return false;
	if(::Save(f,NOKDotL)==false)
		return false;
	if(::Save(f,NOKDotH)==false)
		return false;
	if(::Save(f,BBrightWidthL)==false)
		return false;
	if(::Save(f,BBrightWidthH)==false)
		return false;
	if(::Save(f,BOKDotL)==false)
		return false;
	if(::Save(f,BOKDotH)==false)
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;

    if(::Save(f,NMinNGCountL)==false)
		return false;
    if(::Save(f,NMinNGCountH)==false)
		return false;
    if(::Save(f,BMinNGCountL)==false)
		return false;
    if(::Save(f,BMinNGCountH)==false)
		return false;

	if(::Save(f,BOKLengthL)==false)
		return false;
	if(::Save(f,BOKLengthH)==false)
		return false;
	if(::Save(f,NOKLengthL)==false)
		return false;
	if(::Save(f,NOKLengthH)==false)
		return false;

	return true;
}
bool	ColorBlockLibrary::InspectionData::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

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

	if(::Load(f,AdjustBlack)==false)
		return false;
	if(::Load(f,AdjustWhite)==false)
		return false;

	if(Ver>=10002){
	    if(::Load(f,NMinNGCountL)==false)
			return false;
	    if(::Load(f,NMinNGCountH)==false)
			return false;
	    if(::Load(f,BMinNGCountL)==false)
			return false;
	    if(::Load(f,BMinNGCountH)==false)
			return false;
	}
	if(Ver>=10003){
		if(::Load(f,BOKLengthL)==false)
			return false;
		if(::Load(f,BOKLengthH)==false)
			return false;
		if(::Load(f,NOKLengthL)==false)
			return false;
		if(::Load(f,NOKLengthH)==false)
			return false;
	}
	return true;
}

ColorBlockLibrary::ColorBlockLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupRL		=0;
	PickupRH		=0;
	PickupGL		=0;
	PickupGH		=0;
	PickupBL		=0;
	PickupBH		=0;
    MinBlockSize=0;
    MaxBlockSize=1000000;
    MinBlockDots=0;
    MaxBlockDots=2000000000;
    LimitBlockSize=400;
	GenerationMode.Transparent	=false;		//?d?!???€??E??E?e?u???b?N
	GenerationMode.LeftPickup	=false;
	GenerationMode.OverlappedGen=true;
	GenerationCategory	=_AutoSetting_PAD;

	NoiseSize		=0;
	NoiseSizePinHole=0;
    SpaceToOutline	=0;
    Priority		=0;

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

    CommonMoveDot	=0;
    SelfSearch		=4;     //?c?E?T?o?h?b?g??
}
ColorBlockLibrary::~ColorBlockLibrary(void)
{
	SubtractBlock.RemoveAll();
}

bool	ColorBlockLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=ColorBlockInspectionVersion;
	if(::Save(f,Ver)==false)
		return false;

	if(SubtractBlock.Save(f)==false)
		return false;

	if(::Save(f,PickupRL)==false)
		return false;
	if(::Save(f,PickupRH)==false)
		return false;
	if(::Save(f,PickupGL)==false)
		return false;
	if(::Save(f,PickupGH)==false)
		return false;
	if(::Save(f,PickupBL)==false)
		return false;
	if(::Save(f,PickupBH)==false)
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
    if(::Save(f,Priority)==false)
		return false;

//????C?f?[?^
	if(InsR.Save(f)==false)
		return false;
	if(InsG.Save(f)==false)
		return false;
	if(InsB.Save(f)==false)
		return false;

	if(f->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
    if(::Save(f,SelfSearch)==false)
		return false;
    if(::Save(f,CommonMoveDot)==false)
		return false;
	return true;
}
bool	ColorBlockLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver<10001)
		return false;

	if(SubtractBlock.Load(f)==false)
		return false;

	if(::Load(f,PickupRL)==false)
		return false;
	if(::Load(f,PickupRH)==false)
		return false;
	if(::Load(f,PickupGL)==false)
		return false;
	if(::Load(f,PickupGH)==false)
		return false;
	if(::Load(f,PickupBL)==false)
		return false;
	if(::Load(f,PickupBH)==false)
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
	NoiseSizePinHole=NoiseSize;
	if(Ver>=10004){
		if(::Load(f,NoiseSizePinHole)==false)
			return false;
	}
    if(::Load(f,SpaceToOutline)==false)
		return false;
    if(::Load(f,Priority)==false)
		return false;

//????C?f?[?^
	if(InsR.Load(f)==false)
		return false;
	if(InsG.Load(f)==false)
		return false;
	if(InsB.Load(f)==false)
		return false;

	if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
    if(::Load(f,SelfSearch)==false)
		return false;
    if(::Load(f,CommonMoveDot)==false)
		return false;
	return true;
}

ColorBlockLibrary	&ColorBlockLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((ColorBlockLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);

	PointMove		=((const ColorBlockLibrary *)&src)->PointMove;
    SelfSearch		=((const ColorBlockLibrary *)&src)->SelfSearch;     //?c?E?T?o?h?b?g??
    CommonMoveDot	=((const ColorBlockLibrary *)&src)->CommonMoveDot;

	return *this;
}

void	ColorBlockLibrary::MakePickupTest(ImageBuffer &IBuffR ,ImageBuffer &IBuffG ,ImageBuffer &IBuffB
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int Page
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;
	GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);

	int	YNumb=min(min(min(YLen,IBuffR.GetHeight()),IBuffG.GetHeight()),IBuffB.GetHeight());
	int	XNumb=min(min(min(XLen,IBuffR.GetWidth()) ,IBuffG.GetWidth()) ,IBuffB.GetWidth() );
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*srcR=IBuffR.GetY(y);
			BYTE	*srcG=IBuffG.GetY(y);
			BYTE	*srcB=IBuffB.GetY(y);
			BYTE	*dest=BmpPoint[y];
			int		cR,cG,cB;
			for(int x=0;x<XNumb;x++,srcR++,srcG++,srcB++){
				cR=*srcR;
				cG=*srcG;
				cB=*srcB;
				if(PickupRL<=cR && cR<=PickupRH && PickupGL<=cG && cG<=PickupGH && PickupBL<=cB && cB<=PickupBH){
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

	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSize);
	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSize);

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

	GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,NoiseSizePinHole);
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,NoiseSizePinHole);
	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);
	if(GenerationCategory==_AutoSetting_OTHERMASK
		|| GenerationCategory==_AutoSetting_SURROUND){
		GetLayersBase()->FatAreaN(BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);
	}
	else{
		GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);
	}

	GetLayersBase()->StepProcessing(-1);
	if(0<MinBlockDots || 0<MinBlockSize || MaxBlockSize<GetDotPerLine(Page) || MaxBlockSize<GetMaxLines(Page)
	|| MaxBlockDots<2000000000 || MaxBlockDots<GetDotPerLine(Page)*GetMaxLines(Page)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	DotN=a->GetPatternByte();
			if(MinBlockDots<=DotN && DotN<=MaxBlockDots && MinBlockSize<=a->GetWidth() && a->GetWidth()<=MaxBlockSize && MinBlockSize<=a->GetHeight() && a->GetHeight()<=MaxBlockSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);

		if(GenerationCategory==_AutoSetting_OTHERMASK
			|| GenerationCategory==_AutoSetting_SURROUND){
			//for(int i=0;i<SpaceToOutline;i++)
			//	ThinArea(OcupyMap,TmpData ,XByte, YLen);
		}
		else{
			GetLayersBase()->FatAreaN(OcupyMap,TmpData ,XByte, YLen,SpaceToOutline);
		}
	}
	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}


class	PureFlexAreaListPoint : public NPList<PureFlexAreaListPoint>
{
public:
	PureFlexAreaList	*Point;
	PureFlexAreaListPoint(PureFlexAreaList *p){	Point=p;	}
};


void	ColorBlockLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &BlockList
			,int SelfSearch)
{
	GetLayersBase()->SetMaxProcessing(5);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	PureFlexAreaListContainer	L3List;

	if(GenerationMode.Transparent==false){
		MatrixBuffNotAnd(CurrentMap,(const BYTE **)OcupyMap,XByte,YLen);
	}
	GetLayersBase()->StepProcessing(-1);

	//??E?3?E?u???b?N?d?1????E?e	
	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		GetLayersBase()->StepProcessing(-1);

		/*
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
			int64	DotN=a->GetPatternByte();
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
	
		GetLayersBase()->StepProcessing(-1);
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

		/*
		while((a=FPack.GetFirst())!=NULL){
			if(LimitBlockSize==0 || (a->GetWidth()<LimitBlockSize && a->GetHeight()<LimitBlockSize)){
				FPack.RemoveList(a);
				L3List.AppendList(a);
			}
			else{
				FPack.RemoveList(a);
				PureFlexAreaListContainer Piece;
				a->ChopRect(Piece ,LimitBlockSize);
				PureFlexAreaList *b;
				while((b=Piece.GetFirst())!=NULL){
					Piece.RemoveList(b);
					L3List.AppendList(b);
				}
				delete	a;
			}
		}
		*/
	}	
	catch(...){}

	if(GenerationMode.OverlappedGen==true){
		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
			int	XLen=a->GetWidth()+SelfSearch*2+2+16;
			int	XByte=(XLen+7)/8;
			int	YLen=a->GetHeight()+SelfSearch*2+2;
			BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
			BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffClear(TmpBuff,0,XByte,YLen);
			int	dx=-a->GetMinX()+SelfSearch+8;
			int	dy=-a->GetMinY()+SelfSearch;
			int	dx2=a->GetMinX();
			int	dy2=a->GetMinY();
			a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
			for(int i=0;i<SelfSearch;i++){
				FatArea(TmpBuff,TmpBuff2,XByte, YLen );
			}
			for(int y=0;y<YLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetLayersBase()->GetMaxLines(Page))
					break;
				BYTE	*YPoint	=TmpBuff[y];
				BYTE	*YSrc	=TmpData[y-dy];
				int	sx=-dx;
				if(sx+XLen>GetLayersBase()->GetDotPerLine(Page))
					XLen=GetLayersBase()->GetDotPerLine(Page)-sx;
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
			a->BuildFromRaster(TmpBuff,XByte,YLen ,-dx ,-dy);
			DeleteMatrixBuff(TmpBuff,YLen);
			DeleteMatrixBuff(TmpBuff2,YLen);
		}
	}		
    DeleteMatrixBuff(TmpData,YLen);
	GetLayersBase()->StepProcessing(-1);

	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
		if(a->GetPatternByte()<5)
			continue;
		ColorBlockItem	*v=new ColorBlockItem(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}
}

//==============================================================================

ColorBlockLibraryContainer::ColorBlockLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
ColorBlockLibraryContainer::~ColorBlockLibraryContainer(void)
{
}
