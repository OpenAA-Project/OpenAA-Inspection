/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Aklgorithm\ProjectedInspection\XProjectedInspectionLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XProjectedInspectionLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XProjectedInspection.h"
#include "XCriticalFunc.h"
#include <omp.h>

//============================================================

ProjectedInspectionLibrary::ProjectedInspectionLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupL				=0;
	PickupH				=255;
    MinBlockSize		=0;
    MaxBlockSize		=99999999;
    MinBlockDots		=0;
    MaxBlockDots		=999999999;
    LimitBlockSize		=200;
	NoiseSize			=0;			//孤立点削除
	NoiseSizePinHole	=0;	//ピンホール削除
	Priority			=0;

	Angle=90;
	ExcludeDynamicMask	=true;
	TransitWidth		=4;
	OKWidthDiffereceL	=5;
	OKWidthDiffereceH	=5;
	UseAbsolute			=true;
	CircleMode			=false;
	EvenLength			=99999999;
	PartialSwingAngle	=25.0*2*M_PI/360;
}
ProjectedInspectionLibrary::~ProjectedInspectionLibrary(void)
{
}

bool	ProjectedInspectionLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=ProjectedInspectionVersion;

	if(::Save(f,Ver)==false)
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
	if(::Save(f,NoiseSize)==false)
		return false;
	if(::Save(f,NoiseSizePinHole)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;

	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,ExcludeDynamicMask)==false)
		return false;
    if(::Save(f,TransitWidth)==false)
		return false;
    if(::Save(f,OKWidthDiffereceL)==false)
		return false;
    if(::Save(f,OKWidthDiffereceH)==false)
		return false;
    if(::Save(f,UseAbsolute)==false)
		return false;
    if(::Save(f,CircleMode)==false)
		return false;
    if(::Save(f,EvenLength)==false)
		return false;
    if(::Save(f,PartialSwingAngle)==false)
		return false;

	return true;
}
bool	ProjectedInspectionLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
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
	if(::Load(f,NoiseSize)==false)
		return false;
	if(::Load(f,NoiseSizePinHole)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;

	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,ExcludeDynamicMask)==false)
		return false;
    if(::Load(f,TransitWidth)==false)
		return false;
     if(::Load(f,OKWidthDiffereceL)==false)
		return false;
    if(::Load(f,OKWidthDiffereceH)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,UseAbsolute)==false)
			return false;
	}
    if(::Load(f,CircleMode)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,EvenLength)==false)
			return false;
	}
	if(Ver>=4){
		if(::Save(f,PartialSwingAngle)==false)
			return false;
	}

	return true;
}


ProjectedInspectionLibrary	&ProjectedInspectionLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((ProjectedInspectionLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


void	ProjectedInspectionLibrary::MakePickupTest(int localpage
									 ,ImageBuffer &IBuff 
									 ,const BYTE **MaskBitmap ,const BYTE **LastOcupyMap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int Page
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
		MatrixBuffNotAnd (BmpPoint,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines(Page));
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
		MatrixBuffNotAnd (BmpPoint,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines(Page));
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	
	GetLayersBase()->StepProcessing(localpage);
	//BitmapClusterSized(BmpPoint,XByte ,YLen 
	//					,TmpData,TmpData2
	//					   ,MaxBlockSize ,MinBlockSize ,MaxBlockDots ,MinBlockDots
	//					   ,XLen, YLen);

	GetLayersBase()->StepProcessing(localpage);

	DeleteMatrixBuff(TmpData2,YLen);

	if(0<MinBlockDots || 0<MinBlockSize || MaxBlockSize<GetDotPerLine(Page) || MaxBlockSize<GetMaxLines(Page)
	|| MaxBlockDots<2000000000 || MaxBlockDots<GetDotPerLine(Page)*GetMaxLines(Page)){
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


void	ProjectedInspectionLibrary::MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList)
{
	//GetLayersBase()->SetMaxProcessing(7);
	GetLayersBase()->StepProcessing(localpage);

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
	
	GetLayersBase()->StepProcessing(localpage);

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		GetLayersBase()->StepProcessing(localpage);

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

	DeleteMatrixBuff(TmpData,YLen);

	GetLayersBase()->StepProcessing(localpage);

	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
		if(a->GetPatternByte()<5)
			continue;
		ProjectedInspectionItem	*v=new ProjectedInspectionItem();
		v->SetArea(*a);
		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}

	GetLayersBase()->StepProcessing(localpage);
}

//==============================================================================

ProjectedInspectionLibraryContainer::ProjectedInspectionLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
ProjectedInspectionLibraryContainer::~ProjectedInspectionLibraryContainer(void)
{
}


