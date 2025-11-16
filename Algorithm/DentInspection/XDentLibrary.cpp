/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Dent\XDentLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XDentLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include <QBuffer>
#include "XDentInspection.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


DentLibrary::DentLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupRL		=0;
	PickupRH		=255;
	PickupGL		=0;
	PickupGH		=255;
	PickupBL		=0;
	PickupBH		=255;
    MinDentSize		=0;
    MaxDentSize		=1000000;
    MinDentDots		=0;
    MaxDentDots		=2000000000;
    LimitDentSize	=400;
	NoiseSize		=0;
	NoiseSizePinHole=0;
    SpaceToOutline	=0;
	
	Difference		=100;
	BandWidth		=20;
	MinNGSize		=100;
	MaxNGSize		=3000;
	IgnoreAroundHole=30;
	BaseWaveLength	=50;
	MaxDiffCoef		=15;
	LinesForAverage	=5;
}

bool	DentLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=4;

	if(::Save(f,Ver)==false)
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
    if(::Save(f,MinDentSize)==false)
		return false;
    if(::Save(f,MaxDentSize)==false)
		return false;
    if(::Save(f,MinDentDots)==false)
		return false;
    if(::Save(f,MaxDentDots)==false)
		return false;
    if(::Save(f,LimitDentSize)==false)
		return false;
	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
    if(::Save(f,SpaceToOutline)==false)
		return false;
    if(::Save(f,IgnoreAroundHole)==false)
		return false;

	if(::Save(f,Difference)==false)
		return false;
	if(::Save(f,BandWidth)==false)
		return false;
	if(::Save(f,MinNGSize)==false)
		return false;
	if(::Save(f,MaxNGSize)==false)
		return false;

	if(::Save(f,BaseWaveLength)==false)
		return false;
	if(::Save(f,MaxDiffCoef)==false)
		return false;
	if(::Save(f,LinesForAverage)==false)
		return false;

	return true;
}
bool	DentLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
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
    if(::Load(f,MinDentSize)==false)
		return false;
    if(::Load(f,MaxDentSize)==false)
		return false;
    if(::Load(f,MinDentDots)==false)
		return false;
    if(::Load(f,MaxDentDots)==false)
		return false;
    if(::Load(f,LimitDentSize)==false)
		return false;
	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,NoiseSizePinHole)==false)
		return false;
    if(::Load(f,SpaceToOutline)==false)
		return false;
	if(Ver>=4){
	    if(::Load(f,IgnoreAroundHole)==false)
			return false;
	}

	if(::Load(f,Difference)==false)
		return false;
	if(::Load(f,BandWidth)==false)
		return false;
	if(::Load(f,MinNGSize)==false)
		return false;
	if(::Load(f,MaxNGSize)==false)
		return false;

	if(::Load(f,BaseWaveLength)==false)
		return false;
	if(::Load(f,MaxDiffCoef)==false)
		return false;
	if(::Load(f,LinesForAverage)==false)
		return false;

	return true;
}



DentLibrary	&DentLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((DentLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	DentLibrary::MakePickupTest(ImageBuffer *IBuff[]
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

	int	YNumb=min(YLen,IBuff[0]->GetHeight());
	int	XNumb=min(XLen,IBuff[0]->GetWidth());
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*srcR=IBuff[0]->GetY(y);
			BYTE	*srcG=IBuff[1]->GetY(y);
			BYTE	*srcB=IBuff[2]->GetY(y);
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
	GetLayersBase()->ThinAreaN(BmpPoint,TmpData ,XByte, YLen ,SpaceToOutline);

	if(0<MinDentDots || 0<MinDentSize || MaxDentSize<GetDotPerLine(Page) || MaxDentSize<GetMaxLines(Page)
	|| MaxDentDots<2000000000 || MaxDentDots<GetDotPerLine(Page)*GetMaxLines(Page)){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(BmpPoint,XByte,XLen,YLen ,FPack);
		MatrixBuffClear(BmpPoint ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int	DotN=a->GetPatternByte();
			if(MinDentDots<=DotN && DotN<=MaxDentDots && MinDentSize<=a->GetWidth() && a->GetWidth()<=MaxDentSize && MinDentSize<=a->GetHeight() && a->GetHeight()<=MaxDentSize){
				a->MakeBitData(BmpPoint,XLen ,YLen);
			}
		}
	}
	/*
	MatrixBuffNotCopy(TmpData					,XByte,YLen
					, (const BYTE **)BmpPoint	,XByte,YLen);
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpData,XByte,XLen,YLen ,FPack);
	int64	MaxD=0;
	PureFlexAreaList *MaxF=NULL;
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(MaxD<a->GetPatternByte()){
			MaxF=a;
			MaxD=a->GetPatternByte();
		}
	}
	if(MaxF!=NULL){
		FPack.RemoveList(MaxF);
		delete	MaxF;
		MatrixBuffClear(TmpData ,0 ,XByte ,YLen);
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			a->MakeBitData(TmpData,XLen ,YLen);
		}
		GetLayersBase()->FatAreaN (TmpData,TmpData2 ,XByte, YLen,IgnoreAroundHole);
		MatrixBuffNotAnd(BmpPoint ,(const BYTE **)TmpData ,XLen ,YLen);
	}
	*/

	GetLayersBase()->StepProcessing(-1);
	if(OcupyMap!=NULL){
		MatrixBuffCopy(OcupyMap					,XByte,YLen
		             , (const BYTE **)BmpPoint	,XByte,YLen);

		GetLayersBase()->FatAreaN(OcupyMap,TmpData ,XByte, YLen,SpaceToOutline);
	}


	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData2,YLen);
	DeleteMatrixBuff(TmpData,YLen);
}


class	PureFlexAreaListPoint : public NPList<PureFlexAreaListPoint>
{
public:
	PureFlexAreaList	*Point;
	PureFlexAreaListPoint(PureFlexAreaList *p){	Point=p;	}
};


void	DentLibrary::MakeDent(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &DentList)
{
	GetLayersBase()->SetMaxProcessing(6);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	PureFlexAreaListContainer	L3List;

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

	GetLayersBase()->StepProcessing(-1);

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
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
				if(LimitDentSize==0 || (h->GetWidth()<LimitDentSize && h->GetHeight()<LimitDentSize)){
					Piece.AppendList(h);
					h=NULL;
				}
				else{
					h->ChopRect(Piece ,LimitDentSize);
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

	GetLayersBase()->StepProcessing(-1);

	int	MSearch=6;
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		int	XLen=a->GetWidth()+MSearch*2+2+16;
		int	XByte=(XLen+7)/8;
		int	YLen=a->GetHeight()+MSearch*2+2;
		BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
		BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
		MatrixBuffClear(TmpBuff,0,XByte,YLen);
		int	dx=-a->GetMinX()+MSearch+8;
		int	dy=-a->GetMinY()+MSearch;
		int	dx2=a->GetMinX();
		int	dy2=a->GetMinY();
		a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
		FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,MSearch );
		
		for(int y=0;y<YLen;y++){
			if(y-dy<0)
				continue;
			if(y-dy>=GetMaxLines(Page))
				break;
			BYTE	*YPoint	=TmpBuff[y];
			BYTE	*YSrc	=TmpData[y-dy];
			int	sx=-dx;
			if(sx+XLen>GetDotPerLine(Page))
				XLen=GetDotPerLine(Page)-sx;
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
		int	W=a->GetPatternWidth();
		bool	Changed;
		do{
			Changed=false;
			int N=a->GetFLineLen();
			for(int i=0;i<N-2;i++){
				int	Numb1=a->GetFLineNumb(i);
				int	Numb2=a->GetFLineNumb(i+2);
				if(Numb1<W*0.75 && Numb2<W*0.75){
					int	SMinY=a->GetFLineAbsY(i)-IgnoreAroundHole;
					int	Index1=i;
					for(int j=0;j<N;j++){
						if(a->GetFLineAbsY(j)>=SMinY){
							Index1=j;
							break;
						}
					}
					int	Index2=i+1;
					for(int j=i+1;j<N;j++){
						int	Numb3=a->GetFLineNumb(j);
						if(Numb3>W*0.75){
							Index2=j;
							int	SMaxY=a->GetFLineAbsY(j)+IgnoreAroundHole;
							for(int k=N-1;k>=j;k--){
								if(a->GetFLineAbsY(k)<=SMaxY){
									Index2=k;
									break;
								}
							}
							break;
						}
					}
					int	NewN=N-(Index2-Index1);
					struct  FlexLine    *FL=new struct  FlexLine[NewN];
					memcpy(FL,a->GetFLinePoint(),Index1*sizeof(struct  FlexLine));
					memcpy(&FL[Index1],&a->GetFLinePoint()[Index2],(NewN-Index1)*sizeof(struct  FlexLine));
					a->SetFLine(FL,NewN);
					Changed=true;
					break;
				}
			}
		}while(Changed==true);

		DeleteMatrixBuff(TmpBuff,YLen);
		DeleteMatrixBuff(TmpBuff2,YLen);
	}		

	GetLayersBase()->StepProcessing(-1);

	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
		if(a->GetPatternByte()<5)
			continue;
		DentItem	*v=new DentItem(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		DentList.AppendList(v);
	}
}

//==============================================================================
DentLibraryContainer::DentLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


