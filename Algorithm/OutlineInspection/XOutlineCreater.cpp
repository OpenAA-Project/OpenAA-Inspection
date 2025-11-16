/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XOutlineInspect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"

#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XPSpline.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XMaskingFromGeneral.h"
#include "XOutlineInspect.h"
#include "XOutlineAlgoPacket.h"
#include "XBitImageProcessor.h"

extern	char	*sRoot;
extern	char	*sName;

static	int	DebugX=3494;
static	int	DebugY=2296;
static	int	DebugPP=0;

class	XYClassForOutline : public XYClass
{
public:
	double	Vx,Vy;	//?P?E?@?u?x?N?g??
	double	dx1,dy1;	//?s?e?u?u?O?I?u?u?x?N?g???i?P?E?x?N?g???j
	double	dx2,dy2;	//?i?T?u?u?O?I?u?u?x?N?g???i?P?E?x?N?g???j
	double	Rad;		//?O?a?I?J??a?p	???u?A???e?I?R

	XYClassForOutline(void)
	{
		Vx=Vy=0.0;
		dx1=dy1=0.0;
		dx2=dy2=0.0;
		Rad=0.0;
	}

	XYClassForOutline	&operator=(XYClassForOutline &src)
	{
		XYClass::operator=(*((XYClass *)&src));
		Vx=src.Vx;
		Vy=src.Vy;
		dx1=src.dx1;
		dy1=src.dy1;
		dx2=src.dx2;
		dy2=src.dy2;
		Rad=src.Rad;
		return *this;
	}
};


bool	OutlineInLayer::CreateBlocks(int LibID)
{
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}
	//OutlineInspectLibrary	*ALib=(OutlineInspectLibrary *)GetLibraryContainer()->CreateNew();
	AlgorithmLibraryLevelContainer	ALibC(GetLibraryContainer());
	if(GetLibraryContainer()->GetLibrary(LibID ,ALibC)==false){
		return false;
	}
	OutlineInspectLibrary	*ALib=(OutlineInspectLibrary *)ALibC.GetLibrary(LibID);
	if(ALib==NULL){
		return false;
	}

	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE	**BMap		=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear(BMap ,0 ,XByte ,YLen);
		
	ConstMapBuffer MaskMap;
	if(ALib->GetAdaptedPickLayers().IsEmpty()==false){
		AlgorithmInPagePLI	*LPg=(AlgorithmInPagePLI*)GetParentInPage();
		AlgorithmInLayerPLI	*LL=(AlgorithmInLayerPLI *)LPg->GetLayerData(ALib->GetAdaptedPickLayers().GetFirst()->GetValue());
		LL->GetReflectionMap(_Reflection_Mask,MaskMap,ALib);
	}
	else{
		GetReflectionMap(_Reflection_Mask,MaskMap,ALib);
	}	
	BYTE	**CutlineBitmap=GetCutLineMaskBitmap();

	bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibID);
	bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,ALib,NULL);
	if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
		Pickup(ALib,BMap ,XByte ,YLen,MaskMap.GetBitMap());
	
		PureFlexAreaListContainer ResPack;
		WashAreas(ALib ,BMap ,XByte ,YLen ,ResPack);

		int	ClusterID=0;
		for(PureFlexAreaList *a=ResPack.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(DebugX,DebugY)==true){
				DebugPP++;
			}
			CreateBlockItem(ALib,a,MaskMap.GetBitMap(),CutlineBitmap,ClusterID);
			ClusterID++;
		}

	}
	if(CutlineBitmap!=NULL){
		DeleteMatrixBuff(CutlineBitmap,GetMaxLines());
	}
	DeleteMatrixBuff(BMap,YLen);
	return true;
}

void	OutlineInLayer::Pickup(OutlineInspectLibrary *ALib
							   ,BYTE **BMap ,int XByte ,int YLen
							   ,const BYTE **MaskBitmap)
{
	BYTE	**TmpMap	=MakeMatrixBuff(XByte ,YLen);

	ImagePointerContainer tImages;
	GetParentInPage()->GetMasterImages(tImages);
	ImagePointerList *tm=tImages.GetItem(GetLayer());

	if(ALib->GetAdaptedPickLayers().IsEmpty()==true){
		ImagePointerContainer Images;
		for(int L=0;L<GetLayerNumb();L++){
			Images.AppendList(new ImagePointerList(tm->GetImage()));
		}
	
		ALib->PickupColor.MakeBitmap(Images,BMap ,GetDotPerLine() ,YLen);
	}
	else{
		ImageBuffer	*MImage=&GetMasterBuff();
		int AbsThresholdL ,AbsThresholdH;
		ALib->PickupColor.GetMonoColorRange(AbsThresholdL ,AbsThresholdH);
		for(int LLayer=0;LLayer<GetLayerNumb();LLayer++){
			if(ALib->HasPickLayer(LLayer)==true){
				ImagePointerContainer ImagesPointers;
				GetParentInPage()->GetMasterImages(ImagesPointers);
				MImage=ImagesPointers[LLayer];
				break;
			}
		}
		::PickupBitmap(BMap, XByte ,YLen
			,*MImage
			,AbsThresholdL ,AbsThresholdH
			,0,0);
	}

	MatrixBuffAnd(BMap,MaskBitmap,XByte,YLen);

	/*
	for(int i=0;i<2;i++){
		ThinArea(MaskBitmap
				,TmpMap	,XByte ,YLen);
	}
	*/

	for(int i=0;i<ALib->NoiseDot;i++){
		FatArea(BMap
				,TmpMap	,XByte ,YLen);
	}
	for(int i=0;i<2*ALib->NoiseDot;i++){
		ThinArea(BMap
				,TmpMap	,XByte ,YLen);
	}
	for(int i=0;i<ALib->NoiseDot;i++){
		FatArea(BMap
				,TmpMap	,XByte ,YLen);
	}
	DeleteMatrixBuff(TmpMap,YLen);

	int	OmitZoneDot=((OutlineBase *)GetParentBase())->OmitZoneDot;
	int	XLen=XByte*8;
	for(int y=0;y<OmitZoneDot;y++){
		memset(BMap[y],0,XByte);
	}
	for(int y=0;y<OmitZoneDot;y++){
		memset(BMap[YLen-y-1],0,XByte);
	}
	for(int y=OmitZoneDot;y<YLen-OmitZoneDot;y++){
		for(int x=0;x<OmitZoneDot;x++){
			BMap[y][x>>3] &= ~(0x80>>(x&7));
		}
		for(int x=XLen-OmitZoneDot;x<XLen;x++){
			BMap[y][x>>3] &= ~(0x80>>(x&7));
		}
	}
}

void	OutlineInLayer::WashAreas(OutlineInspectLibrary *ALib
							   ,BYTE **BMap ,int XByte ,int YLen
							   ,PureFlexAreaListContainer &ResPack)
{
	PureFlexAreaListContainer FPack;
	PickupFlexArea(BMap ,XByte ,GetDotPerLine(),YLen ,FPack);

	PureFlexAreaList	*a;
	while((a=FPack.GetFirst())!=NULL){
		FPack.RemoveList(a);
		int64	N=a->GetPatternByte();
		if(N<ALib->MinAreaDot || N>ALib->MaxAreaDot){
			delete	a;
			continue;
		}
		int	L=max(a->GetWidth(),a->GetHeight());
		if(L<ALib->MinAreaSize || L>ALib->MaxAreaSize){
			delete	a;
			continue;
		}
		if(N<=ALib->InsideWidth*ALib->InsideWidth*4){
			delete	a;
			continue;
		}
		ResPack.AppendList(a);
	}
}


static	bool	CutOk=false;

void	OutlineInLayer::CreateBlockItem(OutlineInspectLibrary *ALib ,FlexArea *Area 
									   ,const BYTE **MaskBitmap 
									   ,BYTE **CutlineBitmap
									   ,int ClusterID)
{
	XYClassCluster XY;
	Area->MakeOutlineDot(XY);

	int XByte	=(GetDotPerLine()+7)/8;
	int YLen	=GetMaxLines();
	BYTE **ShrinkedMaskBitmap	=MakeMatrixBuff(XByte ,YLen);
	BYTE **TmpMap				=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy	(ShrinkedMaskBitmap	,XByte ,YLen
					,MaskBitmap			,XByte ,YLen);
	int	tShrinkDot=(ALib->TransDot+1)/2+ max(ALib->InsideWidth+ALib->InsideTrWidth,ALib->OutsideWidth+ALib->OutsideTrWidth);
	for(int i=0;i<tShrinkDot;i++){
		 ThinArea(ShrinkedMaskBitmap
				,TmpMap
				,XByte ,YLen);
	}
	DeleteMatrixBuff(TmpMap,YLen);

	int	SwayDot=(ALib->TransDot+1)/2+3;
	int	Mx=Area->GetMinX()-12-ALib->OutsideWidth-ALib->TransDot-SwayDot;
	Mx &= 0xFFFFFFF8;	//?W?I?{????a
	int	My=Area->GetMinY()-12-ALib->OutsideWidth-ALib->TransDot-SwayDot;
	Area->MoveToNoClip(-Mx,-My);
	XY.MoveTo(-Mx,-My);

	int	SelfSearch=ALib->SelfSearch;

	for(XYClassArea *DotArea=XY.GetFirst();DotArea!=NULL;DotArea=DotArea->GetNext()){
		
		//?A???E?O?e?U?d?T??E?A?a?a?E??E?e
		XYClassArea	*a=NULL;
		XYClassCluster	HAll;
		XYClass	*TopK;
		for(TopK=DotArea->NPListPack<XYClass>::GetFirst();TopK!=NULL;TopK=TopK->GetNext()){
			if(GetBmpBit(MaskBitmap,TopK->x+Mx,TopK->y+My)==0 
			|| GetBmpBit(CutlineBitmap,TopK->x+Mx,TopK->y+My)!=0){
				break;
			}
		}
		if(TopK==NULL){
			//?O?e?U?a?c?A?c?c?E??P?e?I???X?g?I?A???d?a?a?E??E?e
			TopK=DotArea->NPListPack<XYClass>::GetFirst();
		}
		int	N=DotArea->GetDotCount();
		if(N<25){
			continue;
		}
		for(int i=0;i<N;i++){
			while(GetBmpBit(MaskBitmap,TopK->x+Mx,TopK->y+My)==0 
			   || GetBmpBit(CutlineBitmap,TopK->x+Mx,TopK->y+My)!=0){
				//?}?X?N?c?J?b?g???C???I?A??a?A???I?p?X?E??E?e
				a=NULL;
				TopK=DotArea->GetRingNext(TopK);
				i++;
				if(i>=N){
					goto	PEnd;
				}
			}
			if(a==NULL){
				a=new XYClassArea();
				HAll.AppendList(a);
			}
			XYClass	*PrevK=DotArea->GetRingPrev(TopK);
			if(GetBmpBit(MaskBitmap,PrevK->x+Mx,PrevK->y+My)!=0 
			&& GetBmpBit(CutlineBitmap,PrevK->x+Mx,PrevK->y+My)!=0){
				//?L?o?E?}?X?N?I?I?I?a?A?A?J?b?g???C???E?E?A???A??a?p?X?dSelfSearch/2?a????E??E?e
				for(int j=0;j<(SelfSearch+1)/2;j++){
					if(GetBmpBit(MaskBitmap,PrevK->x+Mx,PrevK->y+My)==0){
						break;
					}
					PrevK=DotArea->GetRingPrev(PrevK);
				}
				while(*PrevK!=*TopK){
					XYClass	*c=new XYClassForOutline();
					*c=*PrevK;
					a->AppendList(c);
					PrevK=DotArea->GetRingNext(PrevK);
				}
			}
			XYClass	*c=new XYClassForOutline();
			*c=*TopK;
			TopK=DotArea->GetRingNext(TopK);
			a->AppendList(c);
		}
PEnd:;				
		for(XYClassArea	*sa=HAll.GetFirst();sa!=NULL;){
			if(sa->GetDotCount()>2*SelfSearch+4){
				sa=sa->GetNext();
			}
			else{
				//?e?p?X?I??E?3?a?Z????A??a?A?i????E?e
				XYClassArea	*SNext=sa->GetNext();
				HAll.RemoveList(sa);
				delete	sa;
				sa=SNext;
			}
		}

		for(XYClassArea	*sa=HAll.GetFirst();sa!=NULL;sa=sa->GetNext()){
			SetVectorForOnePath(sa);

			CalcOnePath(sa,Area
						,Mx,My
						,ALib 
						,MaskBitmap
						,(const BYTE **)ShrinkedMaskBitmap
						,tShrinkDot
						,ClusterID);
		}
	}
	DeleteMatrixBuff(ShrinkedMaskBitmap,YLen);
}

void	OutlineInLayer::SetVectorForOnePath(XYClassArea *sa)
{
	int	RewindCount=3;
	for(XYClass	*a=sa->NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		XYClass	*b=a;
		for(int i=0;i<RewindCount;i++){
			b=b->GetPrev();
			if(b==NULL){
				goto	PNext;
			}
		}
		XYClass	*c=a;
		for(int i=0;i<RewindCount;i++){
			c=c->GetNext();
			if(c==NULL){
				goto	PNext;
			}
		}
		XYClassForOutline	*m=(XYClassForOutline *)a;
		int	hx1=b->x - a->x;
		int	hy1=b->y - a->y;
		if(hx1==0 && hy1==0){
			goto	PNext;
		}
		double	h1=hypot(hx1,hy1);
		m->dx1=hx1/h1;
		m->dy1=hy1/h1;

		int	hx2=c->x - a->x;
		int	hy2=c->y - a->y;
		if(hx2==0 && hy2==0){
			goto	PNext;
		}
		double	h2=hypot(hx2,hy2);
		m->dx2=hx2/h2;
		m->dy2=hy2/h2;

		double	rx=m->dx2-m->dx1;
		double	ry=m->dy2-m->dy1;
		double	r=hypot(rx,ry);

		m->Vx=-ry/r;
		m->Vy= rx/r;

		double	g1=GetSita(hx1,hy1);
		double	g2=GetSita(hx2,hy2);
		m->Rad=DiffSita(g1,g2);
PNext:;
	}
}

class	CalcInfoClass
{
public:
	int		XLen,YLen;
	int		XByte;
	BYTE	**OutMap;
	BYTE	**InMap;
	BYTE	**OutTrMap;
	BYTE	**InTrMap;
	BYTE	**AreaMap;
	BYTE	**TmpMap;
	BYTE	**MatchingMap;
	BYTE	**LineMap;
	BYTE	**LineMap2;

	BYTE	**FatAreaMap;
	BYTE	**ThinAreaMap;
	BYTE	**TestAreaMap;
	BYTE	**FatTrAreaMap;
	BYTE	**ThinTrAreaMap;

	int MaxXLen ,MaxYLen;

	CalcInfoClass(void);
	~CalcInfoClass(void);

	void	Initial(int xlen ,int ylen
					,FlexArea *Area
					,OutlineInspectLibrary *ALib
					,int _MaxXLen ,int _MaxYLen);
	void	Release(void);

	void	CreateItemFromChopped(XYClassArea *Path
								,int Mx,int My
								 ,OutlineInspectLibrary *ALib
								 ,const BYTE **MaskBitmap
								 ,OutlineItem *Item);
};

CalcInfoClass::CalcInfoClass(void)
{
	OutMap			=NULL;
	InMap			=NULL;
	OutTrMap		=NULL;
	InTrMap			=NULL;
	AreaMap			=NULL;
	TmpMap			=NULL;
	MatchingMap		=NULL;
	LineMap			=NULL;
	LineMap2		=NULL;

	FatAreaMap		=NULL;
	ThinAreaMap		=NULL;
	TestAreaMap		=NULL;
	FatTrAreaMap	=NULL;
	ThinTrAreaMap	=NULL;
}

CalcInfoClass::~CalcInfoClass(void)
{
	Release();
}

void	CalcInfoClass::Initial(int xlen ,int ylen
							   ,FlexArea *Area,OutlineInspectLibrary *ALib
							   ,int _MaxXLen ,int _MaxYLen)
{
	XLen=xlen;
	YLen=ylen;
	XByte=(XLen+7)/8;
	MaxXLen	=_MaxXLen;
	MaxYLen	=_MaxYLen;

	OutMap		=MakeMatrixBuff(XByte,YLen);
	InMap		=MakeMatrixBuff(XByte,YLen);
	OutTrMap	=MakeMatrixBuff(XByte,YLen);
	InTrMap		=MakeMatrixBuff(XByte,YLen);
	AreaMap		=MakeMatrixBuff(XByte,YLen);
	TmpMap		=MakeMatrixBuff(XByte,YLen);
	MatchingMap	=MakeMatrixBuff(XByte,YLen);
	LineMap		=MakeMatrixBuff(XByte,YLen);
	LineMap2	=MakeMatrixBuff(XByte,YLen);

	FatAreaMap	=MakeMatrixBuff(XByte,YLen);
	ThinAreaMap	=MakeMatrixBuff(XByte,YLen);
	TestAreaMap	=MakeMatrixBuff(XByte,YLen);
	FatTrAreaMap=MakeMatrixBuff(XByte,YLen);
	ThinTrAreaMap=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear(AreaMap ,0 ,XByte ,YLen);
	Area->MakeBitData(AreaMap,MaxXLen,MaxYLen);
	MatrixBuffCopy(FatAreaMap			,XByte,YLen
				, (const BYTE **)AreaMap,XByte,YLen);
	MatrixBuffCopy(ThinAreaMap			,XByte,YLen
				, (const BYTE **)AreaMap,XByte,YLen);
	MatrixBuffCopy(TestAreaMap			,XByte,YLen
				, (const BYTE **)AreaMap,XByte,YLen);
	for(int j=0;j<(ALib->TransDot+1)/2;j++){
		FatArea(FatAreaMap
				,TmpMap	,XByte ,YLen);
	}
	for(int j=0;j<(ALib->TransDot+1)/2+1;j++){
		FatArea(TestAreaMap
				,TmpMap	,XByte ,YLen);
	}
	for(int j=0;j<ALib->TransDot/2;j++){
		ThinArea(ThinAreaMap
				,TmpMap	,XByte ,YLen);
	}
	MatrixBuffCopy(FatTrAreaMap				,XByte,YLen
				, (const BYTE **)FatAreaMap	,XByte,YLen);
	MatrixBuffCopy(ThinTrAreaMap			,XByte,YLen
				, (const BYTE **)ThinAreaMap,XByte,YLen);
	for(int j=0;j<ALib->OutsideTrWidth;j++){
		FatArea(FatTrAreaMap
				,TmpMap	,XByte ,YLen);
	}
	for(int j=0;j<ALib->InsideTrWidth;j++){
		ThinArea(ThinTrAreaMap
				,TmpMap	,XByte ,YLen);
	}
}

void	CalcInfoClass::Release(void)
{
	if(OutMap!=NULL){
		DeleteMatrixBuff(OutMap,YLen);
	}
	if(InMap!=NULL){
		DeleteMatrixBuff(InMap,YLen);
	}
	if(OutTrMap!=NULL){
		DeleteMatrixBuff(OutTrMap,YLen);
	}
	if(InTrMap!=NULL){
		DeleteMatrixBuff(InTrMap,YLen);
	}
	if(AreaMap!=NULL){
		DeleteMatrixBuff(AreaMap,YLen);
	}
	if(FatAreaMap!=NULL){
		DeleteMatrixBuff(FatAreaMap,YLen);
	}
	if(ThinAreaMap!=NULL){
		DeleteMatrixBuff(ThinAreaMap,YLen);
	}
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,YLen);
	}
	if(MatchingMap!=NULL){
		DeleteMatrixBuff(MatchingMap,YLen);
	}
	if(LineMap!=NULL){
		DeleteMatrixBuff(LineMap,YLen);
	}
	if(LineMap2!=NULL){
		DeleteMatrixBuff(LineMap2,YLen);
	}
	if(TestAreaMap!=NULL){
		DeleteMatrixBuff(TestAreaMap,YLen);
	}
}

void	OutlineInLayer::CalcOnePath(XYClassArea *Path,FlexArea *Area 
								   ,int Mx,int My
								   ,OutlineInspectLibrary *ALib
								   ,const BYTE **MaskBitmap
								   ,const BYTE **ShrinkedMaskBitmap
								   ,int tShrinkDot
								   ,int ClusterID)
//?}?X?N???e????I?J?b?g???C???A?a?O?c?e???_?n?I????
{
	int	SwayDot=(ALib->TransDot+1)/2+3;
	int	XLen=Area->GetMaxX()+12+ALib->OutsideWidth+ALib->TransDot+SwayDot;
	int	YLen=Area->GetMaxY()+12+ALib->OutsideWidth+ALib->TransDot+SwayDot;
	CalcInfoClass	CInfo;
	CInfo.Initial(XLen,YLen ,Area,ALib
				,GetDotPerLine(),GetMaxLines());

	int	DivCount=(Path->GetDotCount()+ALib->ChoppedLength/2)/ALib->ChoppedLength;
	if(DivCount==0){
		return;
	}
	int	SelfSearch=ALib->SelfSearch;
	int	DivLen=(Path->GetDotCount()+ALib->ChoppedLength/2)/DivCount;
	XYClass	*k=Path->NPListPack<XYClass>::GetFirst();
	for(int i=0;i<DivCount;i++){
		XYClassArea	AreaDot;
		if(i!=0){
			//?!?n?I?a???u?a?n?_?A?E????A??a?ASelfSearch?h?b?g?a?s?e
			XYClass	*t=k;
			for(int j=0;j<SelfSearch;j++){
				if(t->GetPrev()==NULL){
					break;
				}
				t=t->GetPrev();
			}
			while(*t!=*k){
				XYClassForOutline	*c=new XYClassForOutline();
				*c=*((XYClassForOutline *)t);
				AreaDot.AppendList(c);
				t=t->GetNext();
			}
		}
		for(int j=0;j<DivLen;j++){
			XYClassForOutline	*c=new XYClassForOutline();
			*c=*((XYClassForOutline *)k);
			AreaDot.AppendList(c);
			k=k->GetNext();
			if(k==NULL){
				break;
			}
		}

		if(k!=NULL){
			//?!?n?I?a???u?a?I?_?A?E????A??a?ASelfSearch?h?b?g?a?i?T
			XYClass	*t=k;
			for(int j=0;j<SelfSearch;j++){
				XYClassForOutline	*c=new XYClassForOutline();
				*c=*((XYClassForOutline *)t);
				AreaDot.AppendList(c);
				t=t->GetNext();
				if(t==NULL){
					break;
				}
			}
		}
		if(ChoppedAreaIsEnabled(&AreaDot,Mx,My,ShrinkedMaskBitmap,tShrinkDot)==true){
			CalcOneChopped(&AreaDot,Area
							,Mx,My
							,ALib,MaskBitmap,ClusterID
							,CInfo);
		}
	}
}

bool	OutlineInLayer::ChoppedAreaIsEnabled(XYClassArea *Path ,int Mx,int My
											 ,const BYTE **MaskBitmap
											 ,int tShrinkDot)
{
	int	OmitZoneDot=((OutlineBase *)GetParentBase())->OmitZoneDot+tShrinkDot;

	for(XYClass	*k=Path->NPListPack<XYClass>::GetFirst();k!=NULL;k=k->GetNext()){
		int	X=Mx+k->x;
		int	Y=My+k->y;
		if(GetBmpBit(MaskBitmap,X,Y)==0){
			return false;
		}
		if(X<=OmitZoneDot || GetDotPerLine()-OmitZoneDot<=X
		|| Y<=OmitZoneDot || GetMaxLines()-OmitZoneDot<=Y){
			return false;
		}
	}
	return true;
}


void	CalcInfoClass::CreateItemFromChopped(XYClassArea *Path
											,int Mx,int My
											 ,OutlineInspectLibrary *ALib
											 ,const BYTE **MaskBitmap
											 ,OutlineItem *Item)
{
	MatrixBuffClear(LineMap ,0 ,XByte ,YLen);

	for(XYClass	*k=Path->NPListPack<XYClass>::GetFirst();k!=NULL;k=k->GetNext()){
		SetBmpBit1(LineMap,k->x,k->y);
		XYClassForOutline	*h=((XYClassForOutline *)k);
		if(0<h->Rad && h->Rad<3*M_PI/4){
			for(int y=-2;y<=2;y++){
				for(int x=-2;x<=2;x++){
					SetBmpBit1(LineMap,k->x+x,k->y+y);
				}
			}
			XYClass	*k1=k->GetPrev();
			if(k1!=NULL){
				for(int y=-2;y<=2;y++){
					for(int x=-2;x<=2;x++){
						SetBmpBit1(LineMap,k1->x+x,k1->y+y);
					}
				}
			}
			XYClass	*k2=k->GetNext();
			if(k2!=NULL){
				for(int y=-2;y<=2;y++){
					for(int x=-2;x<=2;x++){
						SetBmpBit1(LineMap,k2->x+x,k2->y+y);
					}
				}
			}
			/*
			for(int i=-2;i<=2;i++){
				SetBmpBit1(LineMap,k->x+(int)(h->Vx*i),(int)(k->y+h->Vy*i));
			}
			XYClass	*k1=k->GetPrev();
			if(k1!=NULL){
				for(int i=-1;i<=1;i++){
					SetBmpBit1(LineMap,k1->x+(int)(h->Vx*i),k1->y+(int)(h->Vy*i));
				}
			}
			XYClass	*k2=k->GetNext();
			if(k2!=NULL){
				for(int i=-1;i<=1;i++){
					SetBmpBit1(LineMap,k2->x+(int)(h->Vx*i),k2->y+(int)(h->Vy*i));
				}
			}
			*/
		}
	}

	MatrixBuffCopy(OutTrMap				,XByte,YLen
				, (const BYTE **)LineMap,XByte,YLen);
	MatrixBuffCopy(InTrMap				,XByte,YLen
				, (const BYTE **)LineMap,XByte,YLen);

	for(int j=0;j<ALib->OutsideTrWidth;j++){
		FatArea(OutTrMap
				,TmpMap	,XByte ,YLen);
	}	
	for(int j=0;j<(ALib->TransDot+1)/2;j++){
		FatArea(OutTrMap
				,TmpMap	,XByte ,YLen);
	}
	MatrixBuffCopy(OutMap					,XByte,YLen
				, (const BYTE **)OutTrMap	,XByte,YLen);
	for(int j=0;j<ALib->OutsideWidth;j++){
		FatArea(OutMap
				,TmpMap	,XByte ,YLen);
	}	
	MatrixBuffNotAnd(OutMap		,(const BYTE **)FatTrAreaMap,XByte,YLen);
	MatrixBuffNotAnd(OutTrMap	,(const BYTE **)FatAreaMap	,XByte,YLen);

	int	MaxXByte=(MaxXLen+7)/8;
	int	Offx=(Mx>>3);
	for(int y=0;y<YLen && (y+My)<MaxYLen;y++){
		BYTE	*D=OutTrMap[y];
		if(y+My<0){
			continue;
		}
		const BYTE	*S=MaskBitmap[y+My]+Offx;
		for(int x=0;x<XByte;x++){
			if(0<=(Offx+x) && (Offx+x)<MaxXByte){
				D[x] &= S[x];
			}
		}
	}

	MatrixBuffNotAnd(OutTrMap,(const BYTE **)LineMap,XByte,YLen);
	Item->OutsideAlgo.TrArea.BuildFromRaster(OutTrMap,XByte,YLen,0,0);

	for(int y=0;y<YLen && (y+My)<MaxYLen;y++){
		BYTE	*D=OutMap[y];
		if(y+My<0){
			continue;
		}
		const BYTE	*S=MaskBitmap[y+My]+Offx;
		for(int x=0;x<XByte;x++){
			if(0<=(Offx+x) && (Offx+x)<MaxXByte){
				D[x] &= S[x];
			}
		}
	}
	Item->OutsideAlgo.Area.BuildFromRaster(OutMap,XByte,YLen,0,0);

	for(int j=0;j<ALib->InsideTrWidth;j++){
		FatArea(InTrMap
				,TmpMap	,XByte ,YLen);
	}
	for(int j=0;j<ALib->TransDot/2;j++){
		FatArea(InTrMap
				,TmpMap	,XByte ,YLen);
	}
	MatrixBuffCopy(InMap				,XByte,YLen
				, (const BYTE **)InTrMap,XByte,YLen);
	for(int j=0;j<ALib->InsideWidth;j++){
		FatArea(InMap
				,TmpMap	,XByte ,YLen);
	}
	MatrixBuffAnd(InMap		,(const BYTE **)ThinTrAreaMap	,XByte,YLen);
	MatrixBuffAnd(InTrMap	,(const BYTE **)ThinAreaMap		,XByte,YLen);

	MatrixBuffCopy(LineMap2				 ,XByte,YLen
				 , (const BYTE **)LineMap,XByte,YLen);
	for(int j=0;j<(ALib->TransDot/2+1);j++){
		FatArea(LineMap2
				,TmpMap	,XByte ,YLen);
	}

	MatrixBuffCopy(MatchingMap			,XByte,YLen
		         , (const BYTE **)OutMap,XByte,YLen);
	MatrixBuffOr(MatchingMap,(const BYTE **)InMap	,XByte,YLen);
	MatrixBuffOr(MatchingMap,(const BYTE **)OutTrMap,XByte,YLen);
	MatrixBuffOr(MatchingMap,(const BYTE **)InTrMap ,XByte,YLen);
	MatrixBuffOr(MatchingMap,(const BYTE **)LineMap2,XByte,YLen);
	Item->MatchingArea.BuildFromRaster(MatchingMap,XByte,YLen,0,0);

	Item->SetArea(Item->MatchingArea);

	MatrixBuffNotAnd(InMap,(const BYTE **)InTrMap		,XByte,YLen);
	MatrixBuffAnd(InTrMap ,(const BYTE **)ThinAreaMap	,XByte,YLen);
	for(int y=0;y<YLen && (y+My)<MaxYLen;y++){
		BYTE	*D=InTrMap[y];
		if(y+My<0){
			continue;
		}		
		const BYTE	*S=MaskBitmap[y+My]+Offx;
		for(int x=0;x<XByte;x++){
			if(0<=(Offx+x) && (Offx+x)<MaxXByte){
				D[x] &= S[x];
			}
		}
	}
	//MatrixBuffNotAnd(InTrMap,LineMap,XByte,YLen);
	Item->InsideAlgo.TrArea.BuildFromRaster(InTrMap,XByte,YLen,0,0);

	for(int y=0;y<YLen && (y+My)<MaxYLen;y++){
		BYTE	*D=InMap[y];
		if(y+My<0){
			continue;
		}		
		const BYTE	*S=MaskBitmap[y+My]+Offx;
		for(int x=0;x<XByte;x++){
			if(0<=(Offx+x) && (Offx+x)<MaxXByte){
				D[x] &= S[x];
			}
		}
	}
	Item->InsideAlgo.Area.BuildFromRaster(InMap,XByte,YLen,0,0);
}


void	OutlineInLayer::CalcOneChopped(XYClassArea *Path,FlexArea *Area 
									,int Mx,int My
									,OutlineInspectLibrary *ALib
									,const BYTE **MaskBitmap
									,int ClusterID
									,CalcInfoClass &CInfo)
//?a???u?I????
{
	OutlineItem	*Item=new OutlineItem();
	
	CInfo.CreateItemFromChopped(Path
								,Mx,My
								,ALib
								,MaskBitmap
								,Item);

	Item->CopyThresholdFromLibrary(ALib->GetParentLevelContainer());
	Item->ClusterID=ClusterID;

	Item->GetArea().MoveToNoClip(Mx,My);
	Item->MatchingArea.MoveToNoClip(Mx,My);
	Item->OutsideAlgo.Area.MoveToNoClip(Mx,My);
	Item->OutsideAlgo.TrArea.MoveToNoClip(Mx,My);
	Item->InsideAlgo.Area.MoveToNoClip(Mx,My);
	Item->InsideAlgo.TrArea.MoveToNoClip(Mx,My);
	Item->SetLibID(ALib->GetLibID());

	AppendItem(Item);
}



