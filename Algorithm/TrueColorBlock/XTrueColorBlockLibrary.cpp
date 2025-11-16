/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "XTrueColorBlockLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XTrueColorBlock.h"
#include <omp.h>
#include "NGTypeDialog.h"

TrueColorBlockLibNGTypeItem::TrueColorBlockLibNGTypeItem(LayersBase *base ,AlgorithmLibraryContainer *lib)
	:LibNGTypeItem(base),Lib(lib)
{
	MinSize=0;
	MaxSize=9999;
	MinRoundRate=0;
	MaxRoundRate=100;
}

bool	TrueColorBlockLibNGTypeItem::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(ColorZone.Save(f)==false)
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
bool	TrueColorBlockLibNGTypeItem::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(ColorZone.Load(f)==false)
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

bool	TrueColorBlockLibNGTypeItem::ShowSetting(void)
{
	NGTypeDialog	D(Lib->GetLayersBase(),this);
	D.exec();
	return true;
}

//============================================================

TrueColorBlockLibrary::TrueColorBlockLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
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

//????C?f?[?^
	NOKDot			=0;
	NMergin			=10;
	BOKDot			=0;
	BMergin			=10;

	NMinNGCount		=0;
	BMinNGCount		=0;

	BOKLength		=0;
	NOKLength		=0;

	PointMove.ModeEnabled				=true;
	PointMove.ModeAdjustable			=true;
	PointMove.ModeCommonMovable			=false;
	PointMove.ModeNGCluster				=true;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeOnlyMatching			=false;
	PointMove.ModeInvertLogic			=false;

    CommonMoveDot	=0;

    AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    AdjustWhite		=20;    //?P?x?a?3?I?a?A??
    SelfSearch		=4;     //?c?E?T?o?h?b?g??
}
TrueColorBlockLibrary::~TrueColorBlockLibrary(void)
{
	SubtractBlock.RemoveAll();
}

bool	TrueColorBlockLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=TrueColorBlockVersion;

	if(SubtractBlock.Save(f)==false)
		return false;

	if(PickupColor.Save(f)==false)
		return false;

	if(::Save(f,Ver)==false)
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
	if(::Save(f,NMergin)==false)
		return false;
	if(NInsColor.Save(f)==false)
		return false;
	if(::Save(f,NOKDot)==false)
		return false;

	if(::Save(f,BMergin)==false)
		return false;
	if(BInsColor.Save(f)==false)
		return false;
	if(::Save(f,BOKDot)==false)
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

    if(::Save(f,NMinNGCount)==false)
		return false;
    if(::Save(f,BMinNGCount)==false)
		return false;

	if(::Save(f,BOKLength)==false)
		return false;
	if(::Save(f,NOKLength)==false)
		return false;

	return true;
}
bool	TrueColorBlockLibrary::LoadBlob(QIODevice *f)
{
	if(SubtractBlock.Load(f)==false)
		return false;

	if(PickupColor.Load(f)==false)
		return false;

	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(Ver<20000){
		MinBlockSize=Ver;
	}
	else{
		if(::Load(f,MinBlockSize)==false)
			return false;
	}
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
	if(Ver>=20004){
		if(::Load(f,NoiseSizePinHole)==false)
			return false;
	}
    if(::Load(f,SpaceToOutline)==false)
		return false;
    if(::Load(f,Priority)==false)
		return false;

//????C?f?[?^

	if(::Load(f,NMergin)==false)
		return false;
	if(NInsColor.Load(f)==false)
		return false;
	if(::Load(f,NOKDot)==false)
		return false;

	if(::Save(f,BMergin)==false)
		return false;
	if(BInsColor.Load(f)==false)
		return false;
	if(::Load(f,BOKDot)==false)
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

	if(Ver>=20002){
	    if(::Load(f,NMinNGCount)==false)
			return false;
	    if(::Load(f,BMinNGCount)==false)
			return false;
	}
	if(Ver>=20003){
		if(::Load(f,BOKLength)==false)
			return false;
		if(::Load(f,NOKLength)==false)
			return false;
	}

	return true;
}

TrueColorBlockLibrary	&TrueColorBlockLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((TrueColorBlockLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	TrueColorBlockLibrary::MakePickupTest(ImagePointerContainer &ImageBuff
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

	MatrixBuffClear(BmpPoint ,0,XByte ,YLen);
	int	YNumb;
	int	XNumb;
	if(GetLayerNumb(Page)>=3){
		ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=ImageBuff.GetItem(1)->GetImage();
		ImageBuffer	*BBuff=ImageBuff.GetItem(2)->GetImage();
		YNumb=min(min(min(YLen,RBuff->GetHeight()),GBuff->GetHeight()),BBuff->GetHeight());
		XNumb=min(min(min(XLen,RBuff->GetWidth()) ,GBuff->GetWidth()) ,BBuff->GetWidth());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=RBuff->GetY(y);
				BYTE	*srcG=GBuff->GetY(y);
				BYTE	*srcB=BBuff->GetY(y);
				BYTE	*dest=BmpPoint[y];
				BYTE	cR,cG,cB;
				for(int x=0;x<XNumb;x++,srcR++,srcG++,srcB++){
					cR=*srcR;
					cG=*srcG;
					cB=*srcB;
					if(PickupColor.Calc(cR,cG,cB,1)==true){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)==2){
		ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
		ImageBuffer	*GBuff=ImageBuff.GetItem(1)->GetImage();
		YNumb=min(min(YLen,RBuff->GetHeight()),GBuff->GetHeight());
		XNumb=min(min(XLen,RBuff->GetWidth()) ,GBuff->GetWidth());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=RBuff->GetY(y);
				BYTE	*srcG=GBuff->GetY(y);
				BYTE	*dest=BmpPoint[y];
				BYTE	cR,cG;
				for(int x=0;x<XNumb;x++,srcR++,srcG++){
					cR=*srcR;
					cG=*srcG;
					if(PickupColor.Calc(cR,cG,cG,1)==true){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else if(GetLayerNumb(Page)==1){
		ImageBuffer	*RBuff=ImageBuff.GetItem(0)->GetImage();
		YNumb=min(YLen,RBuff->GetHeight());
		XNumb=min(XLen,RBuff->GetWidth());
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YNumb;y++){
				BYTE	*srcR=RBuff->GetY(y);
				BYTE	*dest=BmpPoint[y];
				BYTE	cR;
				for(int x=0;x<XNumb;x++,srcR++){
					cR=*srcR;
					if(PickupColor.Calc(cR,cR,cR,1)==true){
						dest[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	else
		return;
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
		GetLayersBase()->FatAreaN (BmpPoint,TmpData ,XByte, YLen,SpaceToOutline);
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
			int	DotN=a->GetPatternByte();
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

struct	TrueColorBlockFoundOneClusterClass
{
	PureFlexAreaListContainer	*L3List;
	BYTE	**CurrentPattern;
	BYTE	SelfSearchDot;
	int		DotPerLine;
	int		MaxLines;
};

static	void TrueColorBlockFoundOneCluster(BYTE **MapData,int xbyte,int YLenen
								  ,int minX,int minY,int maxX,int maxY
								  ,void *anydata)
{
	struct	TrueColorBlockFoundOneClusterClass	*L=(struct TrueColorBlockFoundOneClusterClass *)anydata;
	PureFlexAreaList	*a=new PureFlexAreaList();
	minX-=L->SelfSearchDot+1;
	if(minX<0)
		minX=0;
	minY-=L->SelfSearchDot+1;
	if(minY<0)
		minY=0;
	maxX+=L->SelfSearchDot+1;
	if(maxX>=L->DotPerLine)
		maxX=L->DotPerLine-1;
	maxY+=L->SelfSearchDot+1;
	if(maxY>=L->MaxLines)
		maxY=L->MaxLines-1;

    int rminx=minX&0xFFFFFF8;
    int rminy=minY;
    int rmaxx=(maxX+7)&0xFFFFFF8;
	if(rmaxx>=L->DotPerLine)
		rmaxx=L->DotPerLine-1;
    int rmaxy=maxY;
    int xlen=rmaxx-rminx;
    int ylen=rmaxy-rminy+1;
    int kxbyte=xlen>>3;
    if(kxbyte+(rminx>>3)>xbyte)
        kxbyte=xbyte-(rminx>>3);
    if(kxbyte<=0)
        return;
    BYTE    **kbuff	 =MakeMatrixBuff(kxbyte,ylen);
    BYTE    **tmpbuff=MakeMatrixBuff(kxbyte,ylen);
    for(int y=0;y<ylen;y++){
        memcpy(kbuff[y],&MapData[y+rminy][(rminx>>3)],kxbyte);
        }
	::FatAreaN(kbuff
				,tmpbuff
				,kxbyte, ylen
				,L->SelfSearchDot);

    for(int y=0;y<ylen;y++){
		BYTE	*Dst=kbuff[y];
		BYTE	*Src=&L->CurrentPattern[y+rminy][(rminx>>3)];
		for(int x=0;x<kxbyte;x++,Dst++,Src++){
			*Dst &= *Src;
        }
	}
    a->BuildFromRaster(kbuff ,kxbyte,ylen,rminx,rminy);
	L->L3List->AppendList(a);
    DeleteMatrixBuff(kbuff	,ylen);
    DeleteMatrixBuff(tmpbuff,ylen);

}

class	PureFlexAreaListPoint : public NPList<PureFlexAreaListPoint>
{
public:
	PureFlexAreaList	*Point;
	PureFlexAreaListPoint(PureFlexAreaList *p){	Point=p;	}
};

void	TrueColorBlockLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			 ,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &BlockList)
{
	GetLayersBase()->SetMaxProcessing(5);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         , (const BYTE **)CurrentMap,XByte,YLen);

	PureFlexAreaListContainer	L3List;
	struct	TrueColorBlockFoundOneClusterClass	ClusterizedData;
	ClusterizedData.L3List=&L3List;
	ClusterizedData.CurrentPattern	=CurrentMap;
	ClusterizedData.SelfSearchDot	=SelfSearch;
	ClusterizedData.DotPerLine		=XLen;
	ClusterizedData.MaxLines		=YLen;

	if(GenerationMode.Transparent==false){
		MatrixBuffNotAnd(CurrentMap,(const BYTE **)OcupyMap,XByte,YLen);
	}
	GetLayersBase()->StepProcessing(-1);

	/*
	BitmapClusterSized(CurrentMap,XByte ,YLen 
						   ,MaxBlockSize ,MinBlockSize ,MaxBlockDots ,MinBlockDots
						   ,XLen, YLen
						   ,LimitBlockSize
						   ,TrueColorBlockFoundOneCluster
						   ,&ClusterizedData);

	//??E?3?E?u???b?N?d?1????E?e
	GetLayersBase()->StepProcessing();
	
	const int	DivNumbSmallArea=20;
	NPListPack<PureFlexAreaListPoint>	DivRef[DivNumbSmallArea][DivNumbSmallArea];
	int	XDivDot=(XLen+DivNumbSmallArea-1)/DivNumbSmallArea;
	int	YDivDot=(YLen+DivNumbSmallArea-1)/DivNumbSmallArea;
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		int	Mx1=(a->GetMinX()-1)/XDivDot;
		int	Mx2=(a->GetMaxX()+1)/XDivDot;
		int	My1=(a->GetMinY()-1)/YDivDot;
		int	My2=(a->GetMaxY()+1)/YDivDot;
		Mx1=Clipping(Mx1,0,DivNumbSmallArea-1);
		My1=Clipping(My1,0,DivNumbSmallArea-1);
		Mx2=Clipping(Mx2,0,DivNumbSmallArea-1);
		My2=Clipping(My2,0,DivNumbSmallArea-1);
		for(int ky=My1;ky<=My2;ky++){
			for(int kx=Mx1;kx<=Mx2;kx++){
				DivRef[ky][kx].AppendList(new PureFlexAreaListPoint(a));
			}
		}
	}

	GetLayersBase()->StepProcessing();
	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;){
		PureFlexAreaList *ANext=a->GetNext();
		if(a->GetPatternByte()<10){
			int	Mx1=(a->GetMinX()-1)/XDivDot;
			int	Mx2=(a->GetMaxX()+1)/XDivDot;
			int	My1=(a->GetMinY()-1)/YDivDot;
			int	My2=(a->GetMaxY()+1)/YDivDot;
			Mx1=Clipping(Mx1,0,DivNumbSmallArea-1);
			My1=Clipping(My1,0,DivNumbSmallArea-1);
			Mx2=Clipping(Mx2,0,DivNumbSmallArea-1);
			My2=Clipping(My2,0,DivNumbSmallArea-1);
			for(int ky=My1;ky<=My2;ky++){
				for(int kx=Mx1;kx<=Mx2;kx++){
					for(PureFlexAreaListPoint *b=DivRef[ky][kx].GetFirst();b!=NULL;b=b->GetNext()){
						if(b->Point==a)
							continue;
						if(b->Point->CheckOverlapNeighbor(a)==true){
							b->Point->EatArea(a);
							for(int hy=My1;hy<=My2;hy++){
								for(int hx=Mx1;hx<=Mx2;hx++){
									for(PureFlexAreaListPoint *h=DivRef[hy][hx].GetFirst();h!=NULL;h=h->GetNext()){
										if(h->Point==a){
											DivRef[hy][hx].RemoveList(h);
											break;
										}
									}
									PureFlexAreaListPoint *h;
									for(h=DivRef[hy][hx].GetFirst();h!=NULL;h=h->GetNext()){
										if(h->Point==b->Point)
											break;
									}
									if(h==NULL){
										DivRef[hy][hx].AppendList(new PureFlexAreaListPoint(b->Point));
									}
								}
							}
							L3List.RemoveList(a);
							delete	a;
							goto	CLoop;
						}
					}
				}
			}
		}
CLoop:;
		a=ANext;
	}
	*/

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		GetLayersBase()->StepProcessing(-1);

		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;){
			int	DotN=a->GetPatternByte();
			if((MinBlockDots<=0 && MinBlockSize<=0 && GetDotPerLine(Page)<MaxBlockSize && GetMaxLines(Page)<MaxBlockSize
			&& (2000000000<=MaxBlockDots || GetDotPerLine(Page)*GetMaxLines(Page)<=MaxBlockDots))
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
			GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2,XByte, YLen ,SelfSearch);

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
	GetLayersBase()->StepProcessing(-1);
    DeleteMatrixBuff(TmpData,YLen);

	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		a->ClipArea(0,0,GetDotPerLine(Page),GetMaxLines(Page));
		if(a->GetPatternByte()<5)
			continue;
		TrueColorBlockItem	*v=new TrueColorBlockItem(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}
}

//==============================================================================

TrueColorBlockLibraryContainer::TrueColorBlockLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
TrueColorBlockLibraryContainer::~TrueColorBlockLibraryContainer(void)
{
}
