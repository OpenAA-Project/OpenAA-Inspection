/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\RasterInspection\XRasterInspectionLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XRasterInspectionLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include <QBuffer>
#include "XRasterInspection.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


RasterInspectionLibrary::RasterInspectionLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	GenColorDistance=3;
	Priority		=100;
	EnableOverlap	=false;
	LimitSize		=30;
	SearchAreaDot	=3;
	SearchWaveDiv	=5;
	WaveDistance	=20;
	OKDot			=16;
}

bool	RasterInspectionLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}

	if(::Save(f,GenColorDistance)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,EnableOverlap)==false)
		return false;
	if(::Save(f,LimitSize)==false)
		return false;

	if(::Save(f,SearchAreaDot)==false)
		return false;
	if(::Save(f,SearchWaveDiv)==false)
		return false;
	if(::Save(f,WaveDistance)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;
	return true;
}
bool	RasterInspectionLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,GenColorDistance)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,EnableOverlap)==false)
		return false;
	if(::Load(f,LimitSize)==false)
		return false;

	if(::Load(f,SearchAreaDot)==false)
		return false;
	if(::Load(f,SearchWaveDiv)==false)
		return false;
	if(::Load(f,WaveDistance)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;
	return true;
}


RasterInspectionLibrary	&RasterInspectionLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((RasterInspectionLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}
void	RasterInspectionLibrary::MakeRasterInspection(
				ImageBufferListContainer &ImageContainer
				,BYTE **MaskBitmap,BYTE **LastOcupyMap
				,int XByte ,int XLen,int YLen
				,int OmitZoneDot
				,int Page
				,NPListPack<AlgorithmItemPI> &TmpRasterInspectionData)
{
	for(int y=0;y<OmitZoneDot;y++){
		BYTE	*d=MaskBitmap[y];
		memset(d,0,XByte);
	}
	for(int y=0;y<OmitZoneDot;y++){
		BYTE	*d=MaskBitmap[YLen-y-1];
		memset(d,0,XByte);
	}
	for(int y=0;y<YLen;y++){
		BYTE	*d=MaskBitmap[y];
		for(int x=0;x<OmitZoneDot;x++){
			SetBmpBitOnY0(d,x);
			SetBmpBitOnY0(d,XLen-x-1);
		}
	}
	MatrixBuffNotAnd(MaskBitmap ,(const BYTE **)LastOcupyMap ,XByte ,YLen);

	int	MSearch=SearchAreaDot;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(MaskBitmap,XByte,XLen,YLen ,FPack);

	for(PureFlexAreaList *h=FPack.GetFirst();h!=NULL;h=h->GetNext()){
		PureFlexAreaListContainer Piece;
		h->ChopRect(Piece ,LimitSize);
		for(PureFlexAreaList *a=Piece.GetFirst();a!=NULL;a=a->GetNext()){
			int	aXLen=a->GetWidth()+MSearch*2+2+16;
			int	aXByte=(aXLen+7)/8;
			int	aYLen=a->GetHeight()+MSearch*2+2;
			BYTE	**TmpBuff =MakeMatrixBuff(aXByte ,aYLen);
			BYTE	**TmpBuff2=MakeMatrixBuff(aXByte ,aYLen);
			MatrixBuffClear(TmpBuff,0,aXByte,aYLen);
			int	dx=-a->GetMinX()+MSearch+8;
			int	dy=-a->GetMinY()+MSearch;
			int	dx2=a->GetMinX();
			int	dy2=a->GetMinY();
			a->MakeBitData(TmpBuff,dx,dy,aXLen,aYLen);
			FatAreaN(TmpBuff,TmpBuff2,aXByte, aYLen ,MSearch );
			
			for(int y=0;y<aYLen;y++){
				if(y-dy<0)
					continue;
				if(y-dy>=GetMaxLines(Page))
					break;
				BYTE	*YPoint	=TmpBuff[y];
				BYTE	*YSrc	=MaskBitmap[y-dy];
				int	sx=-dx;
				if(sx+aXLen>GetDotPerLine(Page))
					aXLen=GetDotPerLine(Page)-sx;
				for(int x=0;x<aXLen;x++,sx++){
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

			if(EnableOverlap==false){
				int	iGetDotPerLine=GetDotPerLine(Page);
				for(int y=0;y<aYLen;y++){
					if(y-dy<0)
						continue;
					if(y-dy>=GetMaxLines(Page))
						break;
					BYTE	*Src=(BYTE *)LastOcupyMap[y-dy];
					BYTE	*Dst=(BYTE *)TmpBuff[y];
					for(int x=0;x<aXLen;x++){
						int	X=x-dx;
						if(0<=X && X<iGetDotPerLine){
							if(GetBmpBitOnY(Src,X)!=0){
								SetBmpBitOnY0(Dst,x);
							}
						}
					}
				}
			}
			a->BuildFromRaster(TmpBuff,aXByte,aYLen ,-dx ,-dy);

			DeleteMatrixBuff(TmpBuff,aYLen);
			DeleteMatrixBuff(TmpBuff2,aYLen);
		}
		for(PureFlexAreaList *a=Piece.GetFirst();a!=NULL;a=a->GetNext()){
			a->Regulate();
			a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
			if(a->GetPatternByte()<5)
				continue;
			RasterInspectionItem	*v=new RasterInspectionItem();
			v->SetAreaWithImage(*a,ImageContainer);
			v->CopyThresholdFromLibrary(GetParentLevelContainer());
			v->SetLibID(GetLibID());
			TmpRasterInspectionData.AppendList(v);
		}
	}
}

//==============================================================================
RasterInspectionLibraryContainer::RasterInspectionLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


