/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\XStatisticBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XStatisticBlockLibrary.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XStatisticBlock.h"

StatisticBlockLibrary::StatisticBlockLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupL		=0;
	PickupH		=0;
    MinBlockSize=0;
    MaxBlockSize=1000000;
    MinBlockDots=0;
    MaxBlockDots=2000000000;
    LimitBlockSize=400;
	GenerationMode.Transparent	=false;		//重複生成するブロック
	GenerationMode.LeftPickup	=false;
	GenerationMode.OverlappedGen=true;
	GenerationCategory	=_AutoSetting_PAD;

	NoiseSize		=0;
    SpaceToOutline	=0;
    Priority		=0;
	OverlapDot		=5;

//検査データ
	BrightWidthL	=0;
	BrightWidthH	=0;
	OKDotL			=0;
	OKDotH			=0;
	OKLengthL		=0;
	OKLengthH		=0;
	PointMove.ModeEnabled				=true;
	PointMove.ModeAbsoluteBright		=false;
	PointMove.ModeNGCluster				=true;
	PointMove.ModeWhiteMask				=false;
	PointMove.ModeBlackMask				=false;

    AdjustBlack		=20;    //輝度補正の下限幅
    AdjustWhite		=20;    //輝度補正の上限幅

	UseMorphology		=false;
	MorphologyApplyTo	=MAT_Both;
	EliminateAcnode		=true;
	DilationDotCount	=2;
	ErosionDotCount	=1;
}
StatisticBlockLibrary::~StatisticBlockLibrary(void)
{
}

bool	StatisticBlockLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=StatisticBlockVersion;

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

	if(f->write((const char *)&GenerationMode,sizeof(GenerationMode))!=sizeof(GenerationMode))
		return false;
	if(f->write((const char *)&GenerationCategory,sizeof(GenerationCategory))!=sizeof(GenerationCategory))
		return false;
	if(::Save(f,NoiseSize)==false)
		return false;
    if(::Save(f,SpaceToOutline)==false)
		return false;
    if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,OverlapDot)==false)
		return false;

//検査データ

	if(::Save(f,BrightWidthL)==false)
		return false;
	if(::Save(f,BrightWidthH)==false)
		return false;
	if(::Save(f,OKDotL)==false)
		return false;
	if(::Save(f,OKDotH)==false)
		return false;
	if(::Save(f,OKLengthL)==false)
		return false;
	if(::Save(f,OKLengthH)==false)
		return false;

	if(f->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;

    if(::Save(f,UseMorphology)==false)
		return false;
    if(::Save(f,(int32)MorphologyApplyTo)==false)
		return false;
    if(::Save(f,EliminateAcnode)==false)
		return false;
    if(::Save(f,DilationDotCount)==false)
		return false;
    if(::Save(f,ErosionDotCount)==false)
		return false;

	return true;
}
bool	StatisticBlockLibrary::LoadBlob(QIODevice *f)
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

	if(Ver>=3){
		if(::Load(f,OverlapDot)==false)
			return false;
	}
//検査データ

	if(::Load(f,BrightWidthL)==false)
		return false;
	if(::Load(f,BrightWidthH)==false)
		return false;
	if(::Load(f,OKDotL)==false)
		return false;
	if(::Load(f,OKDotH)==false)
		return false;
	if(::Load(f,OKLengthL)==false)
		return false;
	if(::Load(f,OKLengthH)==false)
		return false;

	if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,UseMorphology)==false)
			return false;
		int32	MAT;
		if(::Load(f,MAT)==false)
			return false;
		MorphologyApplyTo = (_MorphologyApplyTo)MAT;
		if(::Load(f,EliminateAcnode)==false)
			return false;
		if(::Load(f,DilationDotCount)==false)
			return false;
		if(::Load(f,ErosionDotCount)==false)
			return false;
	}else{
		UseMorphology = false;
		MorphologyApplyTo = _MorphologyApplyTo::MAT_Both;
		EliminateAcnode = true;
		DilationDotCount = 2;
		ErosionDotCount = 1;
	}

	return true;
}

StatisticBlockLibrary	&StatisticBlockLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((StatisticBlockLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

void	StatisticBlockLibrary::MakePickupTest(ImageBuffer &IBuff 
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
	GetLayersBase()->StepProcessing(-1);

	if(MaskBitmap!=NULL){
		MatrixBuffAnd	(BmpPoint,MaskBitmap,XByte,YNumb);
	}
	GetLayersBase()->StepProcessing(-1);

	for(int i=0;i<NoiseSize;i++)
		ThinArea(BmpPoint,TmpData ,XByte, YLen);
	for(int i=0;i<NoiseSize;i++)
		FatArea(BmpPoint,TmpData ,XByte, YLen);

	GetLayersBase()->StepProcessing(-1);
	if(GenerationCategory==_AutoSetting_OTHERMASK
		|| GenerationCategory==_AutoSetting_SURROUND){
		for(int i=0;i<SpaceToOutline;i++)
			FatArea(BmpPoint,TmpData ,XByte, YLen);
	}
	else{
		for(int i=0;i<SpaceToOutline;i++)
			ThinArea(BmpPoint,TmpData ,XByte, YLen);
	}

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

	GetLayersBase()->StepProcessing(-1);
	//BitmapClusterSized(BmpPoint,XByte ,YLen 
	//					,TmpData,TmpData2
	//					   ,MaxBlockSize ,MinBlockSize ,MaxBlockDots ,MinBlockDots
	//					   ,XLen, YLen);
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
			for(int i=0;i<SpaceToOutline;i++)
				FatArea(OcupyMap,TmpData ,XByte, YLen);
		}
	}

	/*
	FatArea(TmpData ,BmpPoint
				,XByte, XLen,YLen,15);
	MatrixBuffCopy(BmpPoint,XByte,YLen
		          , TmpData,XByte,YLen);
	*/

	GetLayersBase()->StepProcessing(-1);
	DeleteMatrixBuff(TmpData,YLen);
}

struct	BlockFoundOneClusterClass
{
	PureFlexAreaListContainer	*L3List;
	BYTE	**CurrentPattern;
	BYTE	SelfSearchDot;
	int		DotPerLine;
	int		MaxLines;
};

static	void BlockFoundOneCluster(BYTE **MapData,int xbyte,int YLenen
								  ,int minX,int minY,int maxX,int maxY
								  ,void *anydata)
{
	struct	BlockFoundOneClusterClass	*L=(struct	BlockFoundOneClusterClass *)anydata;
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
	for(int i=0;i<L->SelfSearchDot;i++){
		FatArea(kbuff
				,tmpbuff
				,kxbyte, ylen);
	}
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


void	StatisticBlockLibrary::MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList)
{
	GetLayersBase()->AddMaxProcessing(-1,6);
	GetLayersBase()->StepProcessing(-1);

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy(TmpData					,XByte,YLen
		         ,(const BYTE **)CurrentMap	,XByte,YLen);

	PureFlexAreaListContainer	L3List;
	struct	BlockFoundOneClusterClass	ClusterizedData;
	ClusterizedData.L3List=&L3List;
	ClusterizedData.CurrentPattern	=CurrentMap;
	ClusterizedData.SelfSearchDot	=5;
	ClusterizedData.DotPerLine		=XLen;
	ClusterizedData.MaxLines		=YLen;

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
	GetLayersBase()->StepProcessing(-1);

	try{
		PureFlexAreaListContainer FPack;
		PickupFlexArea(CurrentMap,XByte,XLen,YLen ,FPack);
		GetLayersBase()->StepProcessing(-1);

		PureFlexAreaList *a;
		for(a=FPack.GetFirst();a!=NULL;){
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
	}	
	catch(...){}


	GetLayersBase()->StepProcessing(-1);

	if(GenerationMode.OverlappedGen==true){
		for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
			int	XLen=a->GetWidth()+OverlapDot*2+2;
			int	XByte=(XLen+7)/8;
			int	YLen=a->GetHeight()+OverlapDot*2+2;
			BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
			BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
			MatrixBuffClear(TmpBuff,0,XByte,YLen);
			int	dx=-a->GetMinX()+OverlapDot;
			int	dy=-a->GetMinY()+OverlapDot;
			int	dx2=a->GetMinX();
			int	dy2=a->GetMinY();
			a->MakeBitData(TmpBuff,dx,dy,XLen,YLen);
			for(int i=0;i<OverlapDot;i++){
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
					if(sx<0)
						continue;
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

	for(PureFlexAreaList *a=L3List.GetFirst();a!=NULL;a=a->GetNext()){
		a->Regulate();
		if(a->GetPatternByte()<5)
			continue;
		StatisticBlockItem	*v=new StatisticBlockItem(*a);

		v->CopyThresholdFromLibrary(GetParentLevelContainer());
		v->SetLibID(GetLibID());
		BlockList.AppendList(v);
	}
}

//==============================================================================

StatisticBlockLibraryContainer::StatisticBlockLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
StatisticBlockLibraryContainer::~StatisticBlockLibraryContainer(void)
{
}
