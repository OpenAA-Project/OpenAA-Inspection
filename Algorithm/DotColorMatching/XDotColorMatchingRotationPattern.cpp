/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotColorMatchingInspection\XDotColorMatching.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatchingAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XLearningRegist.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//====================================================================================================

FlexAreaCoef::FlexAreaCoef(const FlexArea &f)
{
	FlexArea::operator=(f);
}
int	FlexAreaCoefContainer::GetMinX(void)
{
	int	MinX=99999999;
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		MinX=min(MinX,a->GetMinX());
	}
	return MinX;
}
int	FlexAreaCoefContainer::GetMinY(void)
{
	int	MinY=99999999;
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		MinY=min(MinY,a->GetMinY());
	}
	return MinY;
}
int	FlexAreaCoefContainer::GetMaxX(void)
{
	int	MaxX=-99999999;
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		MaxX=max(MaxX,a->GetMaxX());
	}
	return MaxX;
}
int	FlexAreaCoefContainer::GetMaxY(void)
{
	int	MaxY=-99999999;
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		MaxY=max(MaxY,a->GetMaxY());
	}
	return MaxY;
}

void     FlexAreaCoefContainer::MakeBitData(BYTE **data ,int XDotLen ,int YDotLen ,bool EnableThread)
{
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeBitData(data ,XDotLen ,YDotLen ,EnableThread);
	}
}

void     FlexAreaCoefContainer::MakeBitData(BYTE **data 
                                    ,int dx ,int dy
                                    ,int XDotLen, int YDotLen)
{
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeBitData(data 
                       ,dx ,dy
                       ,XDotLen, YDotLen);
	}
}

int		 FlexAreaCoefContainer::GetPatternByte(void)
{
	int	AreaDot=0;
	for(FlexAreaCoef *a=GetFirst();a!=NULL;a=a->GetNext()){
		AreaDot+=a->GetPatternByte();
	}
	return AreaDot;
}

RotationPattern::RotationPattern(void)
{
	Parent	=NULL;
	Angle	=0;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	Mergin	=3;
	FlatAreaWidth=0;
	ComplexPattern			=false;
	FlatPattern				=false;
	DivIsClosedToOutline	=false;

	FlatTypeMap		=NULL;
	VLine			=NULL;
	CountVLine		=0;
	HLine			=NULL;
	CountHLine		=0;
	FlatVar			=0;
	HSVMaster		=NULL;
	SubtractionMap	=NULL;
}
RotationPattern::~RotationPattern(void)
{
	if(FlatTypeMap!=NULL){
		DeleteMatrixBuff(FlatTypeMap,YLen);
		FlatTypeMap=NULL;
	}
	if(HSVMaster!=NULL){
		delete	[]HSVMaster[0];
		delete	[]HSVMaster;
		HSVMaster=NULL;
	}
	if(SubtractionMap!=NULL){
		DeleteMatrixBuff(SubtractionMap,YLen);
		SubtractionMap=NULL;
	}
}
static	int	RRDbgID=0;
static	int	RRDbg=0;
double	MakeAve(FlexArea &Area,BMatrix &Map,int XLen,int YLen,int &AddedA,int &AddedAA);

void	RotationPattern::MakePatternOnAngle(DotColorMatchingItem *p
											,double angle
											,FlexArea &EdgeArea
											,ImageBuffer *ImageMasterList[]
											,ImageBuffer *ImageMaster2List[]
											,double	SurroundCoef[3]
											,int32 SearchDotForBrightnessRange
											,double ThresholdPickupEdge
											,double ThresholdFlatPattern)
{
	Parent=p;
	Angle	=angle;
	if(Parent->GetID()==RRDbgID)
		RRDbg++;

	DotPerLine	=Parent->GetDotPerLine();
	MaxLines	=Parent->GetMaxLines();

	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)Parent->GetParentBase());
	int	TmpXLen=Parent->GetArea().GetWidth();
	int	TmpYLen=Parent->GetArea().GetHeight();
	int	TmpXByte=(TmpXLen+7)/8;
	BYTE	**TmpMap=MakeMatrixBuff(TmpXByte,TmpYLen);
	MatrixBuffClear(TmpMap,0,TmpXByte,TmpYLen);
	int	X1=Parent->GetArea().GetMinX();
	int	Y1=Parent->GetArea().GetMinY();
	Parent->GetArea().MakeBitData(TmpMap,-X1,-Y1,TmpXLen,TmpYLen);
	double	Cx=TmpXLen/2.0;
	double	Cy=TmpYLen/2.0;

	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	int	TmpDstXLen=max(TmpXLen,TmpYLen)*1.7;
	int	TmpDstYLen=max(TmpXLen,TmpYLen)*1.7;
	int	TmpDstXByte=(TmpDstXLen+7)/8;
	BYTE	**TmpDstMap=MakeMatrixBuff(TmpDstXByte,TmpDstYLen);
	MatrixBuffClear(TmpDstMap,0,TmpDstXByte,TmpDstYLen);
	double	DCx=TmpDstXLen/2.0;
	double	DCy=TmpDstYLen/2.0;
	for(int y=0;y<TmpDstYLen;y++){
		BYTE	*d=TmpDstMap[y];
		double	xY=(y-DCy)*SinS+Cx;
		double	yY=(y-DCy)*CosS+Cy;
		for(int x=0;x<TmpDstXLen;x++){
			int	X= (x-DCx)*CosS+xY;
			int	Y=-(x-DCx)*SinS+yY;
			if(0<=X && X<TmpXLen && 0<=Y && Y<TmpYLen){
				if(GetBmpBit(TmpMap,X,Y)!=0){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
	BuildFromRaster(TmpDstMap ,TmpDstXByte ,TmpDstYLen,0,0);
	int	sCx,sCy;
	GetCenter(sCx,sCy);
	MoveToNoClip(Parent->MasterCx-sCx ,Parent->MasterCy-sCy);
	int	tCx,tCy;
	GetCenter(tCx,tCy);

	if(HSVMaster!=NULL){
		delete	[]HSVMaster[0];
		delete	[]HSVMaster;
		HSVMaster=NULL;
	}

	const	BYTE	**MaskMap=((DotColorMatchingInPage *)(Parent->GetParentInPage()))->EffectiveMap.GetBitMap();
	MatrixBuffClear(TmpDstMap,0,TmpDstXByte,TmpDstYLen);
	for(int y=0;y<TmpDstYLen;y++){
		BYTE	*d=TmpDstMap[y];
		for(int x=0;x<TmpDstXLen;x++){
			int	X= (x-DCx)*CosS+(y-DCy)*SinS+Cx;
			int	Y=-(x-DCx)*SinS+(y-DCy)*CosS+Cy;
			if(0<=X && X<TmpXLen && 0<=Y && Y<TmpYLen){
				if(GetBmpBit(MaskMap,X+X1,Y+Y1)==0){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
	BackGround.BuildFromRaster(TmpDstMap ,TmpDstXByte ,TmpDstYLen,0,0);
	BackGround.MoveToNoClip(Parent->MasterCx-sCx ,Parent->MasterCy-sCy);

	FlexArea	InsideArea;
	InsideArea=*this;
	InsideArea.ThinAreaN(4);
	OutlineArea.Sub(*this,InsideArea);

	if(FlatTypeMap!=NULL){
		DeleteMatrixBuff(FlatTypeMap,YLen);
	}
	Mergin	=max(Parent->GetThresholdR(NULL)->SelfSearch+2,Parent->GetThresholdR(NULL)->ExpandToSubBlock);
	XLen=GetWidth() +Mergin*2;
	YLen=GetHeight()+Mergin*2;
	XByte=(XLen+7)/8;
	BuffByMaster[0].BrightHL.AllocHead(XLen,YLen);

	int	NoiseBrightness	=ABase->NoiseBrightness;

	{
		BYTE	HLMapBuff[200*200*6];
		struct BMatrixBrightHL::BrightHLStruct	**HLMap=(struct BMatrixBrightHL::BrightHLStruct **)
						MakeMatrixBuff(XLen*sizeof(struct BMatrixBrightHL::BrightHLStruct) ,YLen
						,HLMapBuff,sizeof(HLMapBuff));

		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
			ImageBuffer	*Buff=ImageMasterList[Layer];
			BuffByMaster[0].Map[Layer].AllocHead(XLen,YLen);
			//BrightnessLow [Layer]=MakeMatrixBuff(XLen,YLen);
			//BrightnessHigh[Layer]=MakeMatrixBuff(XLen,YLen);
			CopyFrom(BuffByMaster[0].Map[Layer],HLMap,Layer
					,SearchDotForBrightnessRange
					,NoiseBrightness
					,*Buff,CosS,SinS);
		}
		if(Parent->GetLayerNumb()>=3){
			HSVMaster=new struct HSVValue*[YLen];
			struct HSVValue	*tHSV=new struct HSVValue[XLen*YLen];
			for(int y=0;y<YLen;y++){
				HSVMaster[y]=tHSV;
				tHSV+=XLen;
			}
			CopyHSVFrom(HSVMaster
					,ImageMasterList
					,CosS,SinS);
		}
		BuffByMaster[0].BrightHL.Copy(HLMap,XLen,YLen,5);
		DeleteMatrixBuff((BYTE **)HLMap,HLMapBuff,YLen);
	}

	FlatTypeMap	=MakeMatrixBuff(XByte,YLen);

	int	cx=XLen/2;
	int	cy=YLen/2;
	double		A[3];
	double		AA[3];
	int			ACalcNumb[3];
	for(int i=0;i<3;i++){
		A[i]=0;
		AA[i]=0;
		ACalcNumb[i]=0;
		SkipA[i]=0;
		SkipAA[i]=0;
		SkipACalcNumb[i]=0;
	}

	for(int i=0;i<GetFLineLen();i++){
		int	Y =GetFLineAbsY (i)-Parent->MasterCy+cy;
		int	X1=GetFLineLeftX(i)-Parent->MasterCx+cx;
		int	Numb=GetFLineNumb(i);

		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
			BYTE	*s=(BuffByMaster[0].Map[Layer])[Y];
			if(s!=NULL){
				for(int j=0;j<Numb;j++){
					BYTE	c=s[X1+j];
					A [Layer]+=c;
					AA[Layer]+=c*c;
					ACalcNumb[Layer]++;
				}
			}
			else{
				BYTE	Cn=BuffByMaster[0].Map[Layer].GetConstantBrightness(Y);
				A [Layer]+=Cn*Numb;
				AA[Layer]+=Cn*Cn*Numb;
				ACalcNumb[Layer]+=Numb;
			}
		}
	}

	for(int i=0;i<GetFLineLen();i++){
		int	Y =GetFLineAbsY (i)-Parent->MasterCy+cy;
		if((Y&0x01)==0){
			int	X1=GetFLineLeftX(i)-Parent->MasterCx+cx;
			int	Numb=GetFLineNumb(i);

			for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
				BYTE	*s=(BuffByMaster[0].Map[Layer])[Y];
				if(s!=NULL){
					if(Numb<=16){
						for(int j=0;j<Numb;j++){
							BYTE	c=s[X1+j];
							SkipA [Layer]+=c;
							SkipAA[Layer]+=c*c;
							SkipACalcNumb[Layer]++;
						}
					}
					else
					if(Numb<=64){
						for(int j=0;j<Numb;j+=2){
							BYTE	c=s[X1+j];
							SkipA [Layer]+=c;
							SkipAA[Layer]+=c*c;
							SkipACalcNumb[Layer]++;
						}
					}
					else{
						for(int j=0;j<Numb;j+=4){
							BYTE	c=s[X1+j];
							SkipA [Layer]+=c;
							SkipAA[Layer]+=c*c;
							SkipACalcNumb[Layer]++;
						}
					}
				}
				else{
					BYTE	Cn=BuffByMaster[0].Map[Layer].GetConstantBrightness(Y);
					if(Numb<=16){
						SkipA [Layer]+=Cn*Numb;
						SkipAA[Layer]+=Cn*Cn*Numb;
						SkipACalcNumb[Layer]+=Numb;
					}
					else
					if(Numb<=64){
						int	LNumb=Numb/2;
						SkipA [Layer]+=Cn*LNumb;
						SkipAA[Layer]+=Cn*Cn*LNumb;
						SkipACalcNumb[Layer]+=LNumb;
					}
					else{
						int	LNumb=Numb/4;
						SkipA [Layer]+=Cn*LNumb;
						SkipAA[Layer]+=Cn*Cn*LNumb;
						SkipACalcNumb[Layer]+=LNumb;
					}
				}
			}
		}
	}
	if(SkipACalcNumb[0]>5){
		EffectiveSkip=true;
	}
	else{
		EffectiveSkip=false;
	}

	if(Parent->GetThresholdR()->UseMaster2==true
	&& Parent->GetCountOnlyMasterBuff()>=2){
		BYTE	HLMapBuff[200*200*6];
		struct BMatrixBrightHL::BrightHLStruct	**HLMap=(struct BMatrixBrightHL::BrightHLStruct **)
						MakeMatrixBuff(XLen*sizeof(struct BMatrixBrightHL::BrightHLStruct) ,YLen
						,HLMapBuff,sizeof(HLMapBuff));

		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
			ImageBuffer	*Buff=ImageMaster2List[Layer];
			if(Buff!=NULL){
				BuffByMaster[1].Map[Layer].AllocHead(XLen,YLen);
				CopyFrom(BuffByMaster[1].Map[Layer],HLMap,Layer
						,SearchDotForBrightnessRange
						,NoiseBrightness
						,*Buff,CosS,SinS);
			}
		}
		BuffByMaster[1].BrightHL.Copy(HLMap,XLen,YLen,5);
		DeleteMatrixBuff((BYTE **)HLMap,HLMapBuff,YLen);
	}



	/*
		(An-A)^4=(An^2-2AnA+A^2)^2
				=An^4-4An^3A-4AnA^3+2An^2A^2+4An^2A^2+A^4
				=An^4-4An^3A+6An^2A^2-4AnA^3+A^4

	*/

	//Create Div area
	DeleteMatrixBuff(TmpMap,TmpYLen);
	DeleteMatrixBuff(TmpDstMap,TmpDstYLen);


	//double	Avr=((double)A[AdoptLayer])/ACalcNumb[AdoptLayer];
	//double	V=AA[AdoptLayer]-Avr*Avr*ACalcNumb[AdoptLayer];	//V=•ªŽU
	//double	VTh=sqrt(V/ACalcNumb[AdoptLayer])*((DotColorMatchingBase *)Parent->GetParentBase())->ThresholdPickupEdge;
	int		AreaSize=((DotColorMatchingBase *)Parent->GetParentBase())->PatternEdgeWidth;
	int		MaxD=0;
	int		MaxD2=0;
	int		MaxArea=0;
	AdoptLayer=0;
	double	VTh=ThresholdPickupEdge;
	int	SecondAdoptLayer=-1;
	int	DivAreaNumbDim[100];
	double	MaxVAvr=0;
	int		RecommendedLayer=0;
	for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
		DivAreaNumbDim[Layer]=0;
		if(Layer==ABase->ExclusiveLayer)
			continue;
		PureFlexAreaListContainer FPack;
		MakeDivFlexAreas(EdgeArea ,AreaSize ,VTh,ImageMasterList ,FPack,Layer);

		int	TotalDivAreaDot=0;
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			TotalDivAreaDot+=a->GetPatternByte();
		}
		if(TotalDivAreaDot<200){
			continue;
		}
		double	AddedV=0;
		int		VNumb=0;
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			double	DAvr;
			double	V=a->GetVar(Parent->MasterCx-cx,Parent->MasterCy-cy,*ImageMasterList[Layer],DAvr);
			AddedV+=V;
			VNumb++;
		}
		if(VNumb>0){
			double	VAvr=AddedV/VNumb;
			if(VAvr>MaxVAvr){
				MaxVAvr=VAvr;
				RecommendedLayer=Layer;
			}
		}
		/*
		int	n=FPack.GetCount();
		DivAreaNumbDim[Layer]=n;
		if(MaxArea<n){
			MaxArea=n;
			int	D=0;
			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
				D+=p->GetPatternByte();
			}
			MaxD=D;
			SecondAdoptLayer=AdoptLayer;
			AdoptLayer=Layer;
		}
		else if(MaxArea==n){
			int	D=0;
			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
				D+=p->GetPatternByte();
			}
			if(MaxD<D){
				MaxD2=MaxD;
				SecondAdoptLayer=AdoptLayer;
				MaxD=D;
				AdoptLayer=Layer;
			}
			else if(MaxD2<D){
				MaxD2=D;
				SecondAdoptLayer=Layer;
			}
		}
		*/
	}
	AdoptLayer=RecommendedLayer;
	//int	iAdoptLayer=GetAdoptLayer(ImageMasterList);
	//if(DivAreaNumbDim[iAdoptLayer]!=0){
	//	AdoptLayer=iAdoptLayer;
	//}
	MakeDivArea(EdgeArea,AreaSize ,VTh,ImageMasterList);
	//{
	//	int	MaxDivAreaDots=0;
	//	for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
	//		MaxDivAreaDots+=a->GetPatternByte();
	//	}
	//	if(MaxDivAreaDots<200){
	//		int	RecommendedLayer=AdoptLayer;
	//		iAdoptLayer=AdoptLayer;
	//		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
	//			if(iAdoptLayer!=Layer){
	//				AdoptLayer=Layer;
	//				MakeDivArea(EdgeArea,AreaSize ,VTh,ImageMasterList);
	//				int	tDivAreaDots=0;
	//				for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
	//					tDivAreaDots+=a->GetPatternByte();
	//				}
	//				if(MaxDivAreaDots<tDivAreaDots){
	//					RecommendedLayer=Layer;
	//					MaxDivAreaDots=tDivAreaDots;
	//				}
	//			}
	//		}
	//		AdoptLayer=RecommendedLayer;
	//		MakeDivArea(EdgeArea,AreaSize ,VTh,ImageMasterList);
	//	}
	//}

	{
		//if(DivArea.GetCount()==0){
		//	AdoptLayer=GetAdoptLayerMinV(ImageMasterList);
		//}
		FlexArea	DivAreaAll;
		for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
			DivAreaAll+=*a;
		}
		FlatAreaWidth=min(DivAreaAll.GetPatternWidth(),DivAreaAll.GetPatternHeight());
	}



	double	AvrS=A[AdoptLayer]/ACalcNumb[AdoptLayer];
	double	Vs=sqrt(AA[AdoptLayer]/ACalcNumb[AdoptLayer]-AvrS*AvrS);
	if(Vs>ABase->ThresholdComplexPattern || FlatAreaWidth>8){
		ComplexPattern=true;
	}
	else{
		ComplexPattern=false;
	}
	if(Vs<ThresholdFlatPattern
	&& DivArea.GetPatternByte()<50
	&& (GetPatternByte()<200 || IsEveryPartFlat(ThresholdFlatPattern,ImageMasterList[AdoptLayer])==true)){
		FlatVar=Vs;
		FlatPattern=true;
	}
	else{
		FlatPattern=false;
	}

	if(ComplexPattern==false){
		double	AvrS=A[AdoptLayer]/ACalcNumb[AdoptLayer];
		double	Vs=sqrt(AA[AdoptLayer]/ACalcNumb[AdoptLayer]-AvrS*AvrS);
		if(Vs<ThresholdFlatPattern
		&& (GetPatternByte()<200 || IsEveryPartFlat(ThresholdFlatPattern,ImageMasterList[AdoptLayer])==true)){
			FlatVar=Vs;
			FlatPattern=true;
		}
		else{
			FlatPattern=false;
		}
	}
	SetInitial(-Parent->MasterCx+cx,-Parent->MasterCy+cy ,BuffByMaster[0].Map[AdoptLayer]);

	FlexArea	TempArea2=*this;
	//int	EWidth=max(TempArea.GetWidth(),TempArea.GetHeight());
	TempArea2.ThinAreaN(AreaSize*2);
	FlexArea	TempArea=*this;
	TempArea-=TempArea2;
	{
		FlexArea	DivAreaAll;
		for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
			DivAreaAll+=*a;
		}
		if(DivAreaAll.CheckOverlap(&TempArea)==false){
			DivIsClosedToOutline=true;
		}
		else{
			DivIsClosedToOutline=false;
		}
	}

	int	DetailDivXn=4;
	int	DetailDivYn=4;
	int	DetailXLen=(XLen+DetailDivXn-1)/DetailDivXn;
	int	DetailYLen=(YLen+DetailDivYn-1)/DetailDivYn;
	if(DetailXLen<10){
		DetailXLen=XLen;
		DetailDivXn=1;
	}
	if(DetailYLen<10){
		DetailYLen=YLen;
		DetailDivYn=1;
	}
	int	MasterCx=Parent->MasterCx;
	int	MasterCy=Parent->MasterCy;
	int	FACx=XLen/2;
	int	FACy=YLen/2;
	double	DMaxD=0;
	for(int ym=0;ym<DetailDivYn;ym++){
		for(int xm=0;xm<DetailDivXn;xm++){
			FlexArea	TmpA=*this;
			TmpA.MoveToNoClip(-MasterCx+FACx,-MasterCy+FACy);
			TmpA.ClipArea(xm*DetailXLen,ym*DetailYLen,(xm+1)*DetailXLen,(ym+1)*DetailYLen);
			if(ResembleNeighbor(TmpA,ThresholdFlatPattern)==true)
				continue;
			int AddedA,AddedAA;
			double	d=MakeAve(TmpA,BuffByMaster[0].Map[AdoptLayer],XLen,YLen,AddedA,AddedAA);
			if(DMaxD<d){
				DMaxD=d;
				DetailSearchArea.Swap(TmpA);
				DetailA	=AddedA;
				DetailAA=AddedAA;
			}
		}
	}
	if(DMaxD>ABase->ThresholdComplexPattern && DetailSearchArea.IsNull()==false){
		DetailSearchArea.MoveToNoClip(MasterCx-FACx,MasterCy-FACy);
	}
	else{
		DetailSearchArea=*this;
		int AddedA,AddedAA;
		DetailSearchArea.MoveToNoClip(-MasterCx+FACx,-MasterCy+FACy);
		MakeAve(DetailSearchArea,BuffByMaster[0].Map[AdoptLayer] ,XLen,YLen ,AddedA,AddedAA);
		DetailSearchArea.MoveToNoClip(MasterCx-FACx,MasterCy-FACy);
		DetailA=AddedA;
		DetailAA=AddedAA;
	}
	
	for(int y=0;y<YLen;y++){
		BYTE	*d=FlatTypeMap[y];
		for(int x=0;x<XLen;x++){
			/*
			double	FMaxD=0;
			for(int Layer=0;Layer<Parent->GetLayerNumb();Layer++){
				double	D=MakeVDiff(x,y,Map[Layer]);
				if(FMaxD<D){
					FMaxD=D;
				}
			}
			*/
			double	FMaxD=MakeVDiff(x,y,BuffByMaster[0].Map[AdoptLayer]);

			if(FMaxD<=ABase->ThresholdVariation){
				SetBmpBitOnY1(d,x);
			}
			else{
				SetBmpBitOnY0(d,x);
			}
		}
	}
}

void	RotationPattern::InitializeOnlyByImage (ImageBuffer *ImageMasterList[]
												,ImageBuffer *ImageMaster2List[]
												,FlexArea &EdgeArea
												,int32 SearchDotForBrightnessRange
												,double ThresholdPickupEdge
												,double ThresholdFlatPattern)
{
	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)Parent->GetParentBase());
	//int	TmpXLen=Parent->GetArea().GetWidth();
	//int	TmpYLen=Parent->GetArea().GetHeight();
	//int	TmpXByte=(TmpXLen+7)/8;
	//BYTE	**TmpMap=MakeMatrixBuff(TmpXByte,TmpYLen);
	//MatrixBuffClear(TmpMap,0,TmpXByte,TmpYLen);
	//int	X1=Parent->GetArea().GetMinX();
	//int	Y1=Parent->GetArea().GetMinY();
	//Parent->GetArea().MakeBitData(TmpMap,-X1,-Y1,TmpXLen,TmpYLen);
	//double	Cx=TmpXLen/2.0;
	//double	Cy=TmpYLen/2.0;
	//
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	//int	TmpDstXLen=max(TmpXLen,TmpYLen)*1.7;
	//int	TmpDstYLen=max(TmpXLen,TmpYLen)*1.7;
	//int	TmpDstXByte=(TmpDstXLen+7)/8;
	//BYTE	**TmpDstMap=MakeMatrixBuff(TmpDstXByte,TmpDstYLen);
	//MatrixBuffClear(TmpDstMap,0,TmpDstXByte,TmpDstYLen);
	//double	DCx=TmpDstXLen/2.0;
	//double	DCy=TmpDstYLen/2.0;
	//for(int y=0;y<TmpDstYLen;y++){
	//	BYTE	*d=TmpDstMap[y];
	//	double	xY=(y-DCy)*SinS+Cx;
	//	double	yY=(y-DCy)*CosS+Cy;
	//	for(int x=0;x<TmpDstXLen;x++){
	//		int	X= (x-DCx)*CosS+xY;
	//		int	Y=-(x-DCx)*SinS+yY;
	//		if(0<=X && X<TmpXLen && 0<=Y && Y<TmpYLen){
	//			if(GetBmpBit(TmpMap,X,Y)!=0){
	//				SetBmpBitOnY1(d,x);
	//			}
	//		}
	//	}
	//}
	//BuildFromRaster(TmpDstMap ,TmpDstXByte ,TmpDstYLen,0,0);
	//int	sCx,sCy;
	//GetCenter(sCx,sCy);
	//MoveToNoClip(Parent->MasterCx-sCx ,Parent->MasterCy-sCy);
	int	tCx,tCy;
	GetCenter(tCx,tCy);

	//if(HSVMaster!=NULL){
	//	delete	[]HSVMaster[0];
	//	delete	[]HSVMaster;
	//	HSVMaster=NULL;
	//}

	//const	BYTE	**MaskMap=((DotColorMatchingInPage *)(Parent->GetParentInPage()))->EffectiveMap.GetBitMap();
	//MatrixBuffClear(TmpDstMap,0,TmpDstXByte,TmpDstYLen);
	//for(int y=0;y<TmpDstYLen;y++){
	//	BYTE	*d=TmpDstMap[y];
	//	for(int x=0;x<TmpDstXLen;x++){
	//		int	X= (x-DCx)*CosS+(y-DCy)*SinS+Cx;
	//		int	Y=-(x-DCx)*SinS+(y-DCy)*CosS+Cy;
	//		if(0<=X && X<TmpXLen && 0<=Y && Y<TmpYLen){
	//			if(GetBmpBit(MaskMap,X+X1,Y+Y1)==0){
	//				SetBmpBitOnY1(d,x);
	//			}
	//		}
	//	}
	//}
	//BackGround.BuildFromRaster(TmpDstMap ,TmpDstXByte ,TmpDstYLen,0,0);
	//BackGround.MoveToNoClip(Parent->MasterCx-sCx ,Parent->MasterCy-sCy);

	//FlexArea	InsideArea;
	//InsideArea=*this;
	//InsideArea.ThinAreaN(4);
	//OutlineArea.Sub(*this,InsideArea);
	//
	//if(FlatTypeMap!=NULL){
	//	DeleteMatrixBuff(FlatTypeMap,YLen);
	//}
	//Mergin	=max(Parent->GetThresholdR(NULL)->SelfSearch+2,Parent->GetThresholdR(NULL)->ExpandToSubBlock);
	//XLen=GetWidth() +Mergin*2;
	//YLen=GetHeight()+Mergin*2;
	//XByte=(XLen+7)/8;
	//BuffByMaster[0].BrightHL.AllocHead(XLen,YLen);

	int	NoiseBrightness	=ABase->NoiseBrightness;

	{
		BYTE	HLMapBuff[200*200*6];
		struct BMatrixBrightHL::BrightHLStruct	**HLMap=(struct BMatrixBrightHL::BrightHLStruct **)
						MakeMatrixBuff(XLen*sizeof(struct BMatrixBrightHL::BrightHLStruct) ,YLen
						,HLMapBuff,sizeof(HLMapBuff));

		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
			ImageBuffer	*Buff=ImageMasterList[Layer];
			BuffByMaster[0].Map[Layer].AllocHead(XLen,YLen);

			CopyFrom(BuffByMaster[0].Map[Layer],HLMap,Layer
					,SearchDotForBrightnessRange
					,NoiseBrightness
					,*Buff,CosS,SinS);
		}
		if(Parent->GetLayerNumb()>=3){
			//HSVMaster=new struct HSVValue*[YLen];
			//struct HSVValue	*tHSV=new struct HSVValue[XLen*YLen];
			//for(int y=0;y<YLen;y++){
			//	HSVMaster[y]=tHSV;
			//	tHSV+=XLen;
			//}
			CopyHSVFrom(HSVMaster
					,ImageMasterList
					,CosS,SinS);
		}
		BuffByMaster[0].BrightHL.Copy(HLMap,XLen,YLen,5);
		DeleteMatrixBuff((BYTE **)HLMap,HLMapBuff,YLen);
	}

	FlatTypeMap	=MakeMatrixBuff(XByte,YLen);

	int	cx=XLen/2;
	int	cy=YLen/2;
	double		A[3];
	double		AA[3];
	int			ACalcNumb[3];
	for(int i=0;i<3;i++){
		A[i]=0;
		AA[i]=0;
		ACalcNumb[i]=0;
		SkipA[i]=0;
		SkipAA[i]=0;
		SkipACalcNumb[i]=0;
	}

	for(int i=0;i<GetFLineLen();i++){
		int	Y =GetFLineAbsY (i)-Parent->MasterCy+cy;
		int	X1=GetFLineLeftX(i)-Parent->MasterCx+cx;
		int	Numb=GetFLineNumb(i);

		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
			BYTE	*s=(BuffByMaster[0].Map[Layer])[Y];
			if(s!=NULL){
				for(int j=0;j<Numb;j++){
					BYTE	c=s[X1+j];
					A [Layer]+=c;
					AA[Layer]+=c*c;
					ACalcNumb[Layer]++;
				}
			}
			else{
				BYTE	Cn=BuffByMaster[0].Map[Layer].GetConstantBrightness(Y);
				A [Layer]+=Cn*Numb;
				AA[Layer]+=Cn*Cn*Numb;
				ACalcNumb[Layer]+=Numb;
			}
		}
	}

	for(int i=0;i<GetFLineLen();i++){
		int	Y =GetFLineAbsY (i)-Parent->MasterCy+cy;
		if((Y&0x01)==0){
			int	X1=GetFLineLeftX(i)-Parent->MasterCx+cx;
			int	Numb=GetFLineNumb(i);

			for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
				BYTE	*s=(BuffByMaster[0].Map[Layer])[Y];
				if(s!=NULL){
					if(Numb<=16){
						for(int j=0;j<Numb;j++){
							BYTE	c=s[X1+j];
							SkipA [Layer]+=c;
							SkipAA[Layer]+=c*c;
							SkipACalcNumb[Layer]++;
						}
					}
					else
					if(Numb<=64){
						for(int j=0;j<Numb;j+=2){
							BYTE	c=s[X1+j];
							SkipA [Layer]+=c;
							SkipAA[Layer]+=c*c;
							SkipACalcNumb[Layer]++;
						}
					}
					else{
						for(int j=0;j<Numb;j+=4){
							BYTE	c=s[X1+j];
							SkipA [Layer]+=c;
							SkipAA[Layer]+=c*c;
							SkipACalcNumb[Layer]++;
						}
					}
				}
				else{
					BYTE	Cn=BuffByMaster[0].Map[Layer].GetConstantBrightness(Y);
					if(Numb<=16){
						SkipA [Layer]+=Cn*Numb;
						SkipAA[Layer]+=Cn*Cn*Numb;
						SkipACalcNumb[Layer]+=Numb;
					}
					else
					if(Numb<=64){
						int	LNumb=Numb/2;
						SkipA [Layer]+=Cn*LNumb;
						SkipAA[Layer]+=Cn*Cn*LNumb;
						SkipACalcNumb[Layer]+=LNumb;
					}
					else{
						int	LNumb=Numb/4;
						SkipA [Layer]+=Cn*LNumb;
						SkipAA[Layer]+=Cn*Cn*LNumb;
						SkipACalcNumb[Layer]+=LNumb;
					}
				}
			}
		}
	}
	if(SkipACalcNumb[0]>5){
		EffectiveSkip=true;
	}
	else{
		EffectiveSkip=false;
	}

	if(Parent->GetThresholdR()->UseMaster2==true
	&& Parent->GetCountOnlyMasterBuff()>=2){
		BYTE	HLMapBuff[200*200*6];
		struct BMatrixBrightHL::BrightHLStruct	**HLMap=(struct BMatrixBrightHL::BrightHLStruct **)
						MakeMatrixBuff(XLen*sizeof(struct BMatrixBrightHL::BrightHLStruct) ,YLen
						,HLMapBuff,sizeof(HLMapBuff));

		for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
			ImageBuffer	*Buff=ImageMaster2List[Layer];
			if(Buff!=NULL){
				BuffByMaster[1].Map[Layer].AllocHead(XLen,YLen);
				CopyFrom(BuffByMaster[1].Map[Layer],HLMap,Layer
						,SearchDotForBrightnessRange
						,NoiseBrightness
						,*Buff,CosS,SinS);
			}
		}
		BuffByMaster[1].BrightHL.Copy(HLMap,XLen,YLen,5);
		DeleteMatrixBuff((BYTE **)HLMap,HLMapBuff,YLen);
	}



	/*
		(An-A)^4=(An^2-2AnA+A^2)^2
				=An^4-4An^3A-4AnA^3+2An^2A^2+4An^2A^2+A^4
				=An^4-4An^3A+6An^2A^2-4AnA^3+A^4

	*/

	//Create Div area
	//DeleteMatrixBuff(TmpMap,TmpYLen);
	//DeleteMatrixBuff(TmpDstMap,TmpDstYLen);


	//double	Avr=((double)A[AdoptLayer])/ACalcNumb[AdoptLayer];
	//double	V=AA[AdoptLayer]-Avr*Avr*ACalcNumb[AdoptLayer];	//V=•ªŽU
	//double	VTh=sqrt(V/ACalcNumb[AdoptLayer])*((DotColorMatchingBase *)Parent->GetParentBase())->ThresholdPickupEdge;
	int		AreaSize=((DotColorMatchingBase *)Parent->GetParentBase())->PatternEdgeWidth;
	int		MaxD=0;
	int		MaxD2=0;
	int		MaxArea=0;
	AdoptLayer=0;
	double	VTh=ThresholdPickupEdge;
	int	SecondAdoptLayer=-1;
	int	DivAreaNumbDim[100];
	double	MaxVAvr=0;
	int		RecommendedLayer=0;
	for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
		DivAreaNumbDim[Layer]=0;
		if(Layer==ABase->ExclusiveLayer)
			continue;
		PureFlexAreaListContainer FPack;
		MakeDivFlexAreas(EdgeArea ,AreaSize ,VTh,ImageMasterList ,FPack,Layer);

		int	TotalDivAreaDot=0;
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			TotalDivAreaDot+=a->GetPatternByte();
		}
		if(TotalDivAreaDot<200){
			continue;
		}
		double	AddedV=0;
		int		VNumb=0;
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			double	DAvr;
			double	V=a->GetVar(Parent->MasterCx-cx,Parent->MasterCy-cy,*ImageMasterList[Layer],DAvr);
			AddedV+=V;
			VNumb++;
		}
		if(VNumb>0){
			double	VAvr=AddedV/VNumb;
			if(VAvr>MaxVAvr){
				MaxVAvr=VAvr;
				RecommendedLayer=Layer;
			}
		}
	}
	AdoptLayer=RecommendedLayer;

	MakeDivArea(EdgeArea,AreaSize ,VTh,ImageMasterList);


	{
		FlexArea	DivAreaAll;
		for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
			DivAreaAll+=*a;
		}
		FlatAreaWidth=min(DivAreaAll.GetPatternWidth(),DivAreaAll.GetPatternHeight());
	}


	double	AvrS=A[AdoptLayer]/ACalcNumb[AdoptLayer];
	double	Vs=sqrt(AA[AdoptLayer]/ACalcNumb[AdoptLayer]-AvrS*AvrS);
	if(Vs>ABase->ThresholdComplexPattern || FlatAreaWidth>8){
		ComplexPattern=true;
	}
	else{
		ComplexPattern=false;
	}
	if(Vs<ThresholdFlatPattern
	&& DivArea.GetPatternByte()<50
	&& (GetPatternByte()<200 || IsEveryPartFlat(ThresholdFlatPattern,ImageMasterList[AdoptLayer])==true)){
		FlatVar=Vs;
		FlatPattern=true;
	}
	else{
		FlatPattern=false;
	}

	if(ComplexPattern==false){
		double	AvrS=A[AdoptLayer]/ACalcNumb[AdoptLayer];
		double	Vs=sqrt(AA[AdoptLayer]/ACalcNumb[AdoptLayer]-AvrS*AvrS);
		if(Vs<ThresholdFlatPattern
		&& (GetPatternByte()<200 || IsEveryPartFlat(ThresholdFlatPattern,ImageMasterList[AdoptLayer])==true)){
			FlatVar=Vs;
			FlatPattern=true;
		}
		else{
			FlatPattern=false;
		}
	}
	SetInitial(-Parent->MasterCx+cx,-Parent->MasterCy+cy ,BuffByMaster[0].Map[AdoptLayer]);

	FlexArea	TempArea2=*this;
	//int	EWidth=max(TempArea.GetWidth(),TempArea.GetHeight());
	TempArea2.ThinAreaN(AreaSize*2);
	FlexArea	TempArea=*this;
	TempArea-=TempArea2;
	{
		FlexArea	DivAreaAll;
		for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
			DivAreaAll+=*a;
		}
		if(DivAreaAll.CheckOverlap(&TempArea)==false){
			DivIsClosedToOutline=true;
		}
		else{
			DivIsClosedToOutline=false;
		}
	}

	int	DetailDivXn=4;
	int	DetailDivYn=4;
	int	DetailXLen=(XLen+DetailDivXn-1)/DetailDivXn;
	int	DetailYLen=(YLen+DetailDivYn-1)/DetailDivYn;
	if(DetailXLen<10){
		DetailXLen=XLen;
		DetailDivXn=1;
	}
	if(DetailYLen<10){
		DetailYLen=YLen;
		DetailDivYn=1;
	}
	int	MasterCx=Parent->MasterCx;
	int	MasterCy=Parent->MasterCy;
	int	FACx=XLen/2;
	int	FACy=YLen/2;
	double	DMaxD=0;
	for(int ym=0;ym<DetailDivYn;ym++){
		for(int xm=0;xm<DetailDivXn;xm++){
			FlexArea	TmpA=*this;
			TmpA.MoveToNoClip(-MasterCx+FACx,-MasterCy+FACy);
			TmpA.ClipArea(xm*DetailXLen,ym*DetailYLen,(xm+1)*DetailXLen,(ym+1)*DetailYLen);
			if(ResembleNeighbor(TmpA,ThresholdFlatPattern)==true)
				continue;
			int AddedA,AddedAA;
			double	d=MakeAve(TmpA,BuffByMaster[0].Map[AdoptLayer],XLen,YLen,AddedA,AddedAA);
			if(DMaxD<d){
				DMaxD=d;
				DetailSearchArea.Swap(TmpA);
				DetailA	=AddedA;
				DetailAA=AddedAA;
			}
		}
	}
	if(DMaxD>ABase->ThresholdComplexPattern && DetailSearchArea.IsNull()==false){
		DetailSearchArea.MoveToNoClip(MasterCx-FACx,MasterCy-FACy);
	}
	else{
		DetailSearchArea=*this;
		int AddedA,AddedAA;
		DetailSearchArea.MoveToNoClip(-MasterCx+FACx,-MasterCy+FACy);
		MakeAve(DetailSearchArea,BuffByMaster[0].Map[AdoptLayer] ,XLen,YLen ,AddedA,AddedAA);
		DetailSearchArea.MoveToNoClip(MasterCx-FACx,MasterCy-FACy);
		DetailA=AddedA;
		DetailAA=AddedAA;
	}
	
	for(int y=0;y<YLen;y++){
		BYTE	*d=FlatTypeMap[y];
		for(int x=0;x<XLen;x++){
			double	FMaxD=MakeVDiff(x,y,BuffByMaster[0].Map[AdoptLayer]);

			if(FMaxD<=ABase->ThresholdVariation){
				SetBmpBitOnY1(d,x);
			}
			else{
				SetBmpBitOnY0(d,x);
			}
		}
	}
}

void	MakeCoeffData(FlexArea &Area,ImageBuffer &Buff,double &AddedA, double &AddedAA)
{
	int XLen	=Buff.GetWidth();
	int YLen	=Buff.GetHeight();
	int N=Area.GetFLineLen();
	AddedA	=0;
	AddedAA	=0;
	int		Numb=0;
	if(Area.GetPatternByte()<32767){
		int	iAddedA	=0;
		int	iAddedAA=0;
		for(int i=0;i<N;i++){
			int	Y=Area.GetFLineAbsY(i);
			if(Y<0 || YLen<=Y)
				continue;
			int	DestY=Y;
			if(DestY<0 || YLen<=DestY)
				continue;
			int	X1=Area.GetFLineLeftX(i);
			int	numb=Area.GetFLineNumb(i);
			if(X1<0){
				numb+=X1;
				X1=0;
			}
			if(X1+numb>=XLen){
				numb=XLen-X1;
			}
			int	DestX=X1;
			if(DestX<0){
				numb+=DestX;
				X1-=DestX;
				DestX=0;
			}
			if(DestX+numb>=XLen){
				numb=XLen-DestX;
			}
			if(numb<=0)
				continue;
			BYTE	*sp=&Buff.GetY(Y)[X1];

			for(int xn=0;xn<numb;xn++){
				BYTE	s=*sp;
				sp++;
				iAddedA	+=s;
				iAddedAA+=s*s;
			}
			Numb+=numb;
		}
		AddedA	=iAddedA	;
		AddedAA	=iAddedAA	;
	}
	else{
		for(int i=0;i<N;i++){
			int	Y=Area.GetFLineAbsY(i);
			if(Y<0 || YLen<=Y)
				continue;
			int	DestY=Y;
			if(DestY<0 || YLen<=DestY)
				continue;
			int	X1=Area.GetFLineLeftX(i);
			int	numb=Area.GetFLineNumb(i);
			if(X1<0){
				numb+=X1;
				X1=0;
			}
			if(X1+numb>=XLen){
				numb=XLen-X1;
			}
			int	DestX=X1;
			if(DestX<0){
				numb+=DestX;
				X1-=DestX;
				DestX=0;
			}
			if(DestX+numb>=XLen){
				numb=XLen-DestX;
			}
			if(numb<=0)
				continue;
			BYTE	*sp=Buff.GetY(Y);
			int	iAddedA	=0;
			int	iAddedAA=0;

			for(int xn=0;xn<numb;xn++){
				BYTE	s=sp[X1+xn];
				iAddedA	+=s;
				iAddedAA+=s*s;
			}
			Numb+=numb;
			AddedA	+=iAddedA	;
			AddedAA	+=iAddedAA	;
		}
	}
}

double	GetImageBufferCoeff(FlexArea &Area
					,ImageBuffer &DstBuff,int dx ,int dy
					,ImageBuffer &SrcBuff
					,double AddedA, double AddedAA)
{
	int XLen	=min(DstBuff.GetWidth() ,SrcBuff.GetWidth());
	int YLen	=min(DstBuff.GetHeight(),SrcBuff.GetHeight());
	int N=Area.GetFLineLen();

	double	AddedB	=0;
	double	AddedBB	=0;
	double	AddedAB	=0;
	int		Numb=0;

	int	MinX=Area.GetMinX();
	int	MinY=Area.GetMinY();
	int	MaxX=Area.GetMaxX();
	int	MaxY=Area.GetMaxY();

	if(0<=(MinX+dx) && (MaxX+dx)<XLen && 0<=(MinY+dy) && (MaxY+dy)<YLen){
		if(Area.GetPatternByte()<32767){
			int	iAddedB	=0;
			int	iAddedBB=0;
			int	iAddedAB=0;
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;
				BYTE	*sp=&SrcBuff.GetYWithoutDepended(Y)[X1];
				BYTE	*dp=&DstBuff.GetYWithoutDepended(DestY)[DestX];
				for(int xn=0;xn<numb;xn++){
					BYTE	s=*sp;
					BYTE	d=*dp;
					sp++;
					dp++;
					iAddedB	+=d;
					iAddedBB+=d*d;
					iAddedAB+=s*d;
				}
				Numb+=numb;
			}
			AddedB	=iAddedB	;
			AddedBB	=iAddedBB	;
			AddedAB	=iAddedAB	;
		}
		else{
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;
				BYTE	*sp=SrcBuff.GetYWithoutDepended(Y);
				BYTE	*dp=DstBuff.GetYWithoutDepended(DestY);	
				int	iAddedB	=0;
				int	iAddedBB=0;
				int	iAddedAB=0;

				for(int xn=0;xn<numb;xn++){
					BYTE	s=sp[X1+xn];
					BYTE	d=dp[DestX+xn];
					iAddedB	+=d;
					iAddedBB+=d*d;
					iAddedAB+=s*d;
				}
				Numb+=numb;
				AddedB	+=iAddedB	;
				AddedBB	+=iAddedBB	;
				AddedAB	+=iAddedAB	;
			}
		}
	}
	else{
		AddedA	=0;
		AddedAA	=0;
		if(Area.GetPatternByte()<32767){
			int	iAddedA	=0;
			int	iAddedAA=0;
			int	iAddedB	=0;
			int	iAddedBB=0;
			int	iAddedAB=0;
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;
				BYTE	*sp=&SrcBuff.GetYWithoutDepended(Y)[X1];
				BYTE	*dp=&DstBuff.GetYWithoutDepended(DestY)[DestX];	
				for(int xn=0;xn<numb;xn++){
					BYTE	s=*sp;
					BYTE	d=*dp;
					sp++;
					dp++;
					iAddedA	+=s;
					iAddedAA+=s*s;
					iAddedB	+=d;
					iAddedBB+=d*d;
					iAddedAB+=s*d;
				}
				Numb+=numb;
			}
			AddedA	=iAddedA	;
			AddedAA	=iAddedAA	;
			AddedB	=iAddedB	;
			AddedBB	=iAddedBB	;
			AddedAB	=iAddedAB	;
		}
		else{
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;
				BYTE	*sp=SrcBuff.GetYWithoutDepended(Y);
				BYTE	*dp=DstBuff.GetYWithoutDepended(DestY);	
				int	iAddedA	=0;
				int	iAddedAA=0;
				int	iAddedB	=0;
				int	iAddedBB=0;
				int	iAddedAB=0;

				for(int xn=0;xn<numb;xn++){
					BYTE	s=sp[X1+xn];
					BYTE	d=dp[DestX+xn];
					iAddedA	+=s;
					iAddedAA+=s*s;
					iAddedB	+=d;
					iAddedBB+=d*d;
					iAddedAB+=s*d;
				}
				Numb+=numb;
				AddedA	+=iAddedA	;
				AddedAA	+=iAddedAA	;
				AddedB	+=iAddedB	;
				AddedBB	+=iAddedBB	;
				AddedAB	+=iAddedAB	;
			}
		}
	}
	if(Numb<5)
		return 0;
	double	AvrA=AddedA/Numb;
	double	AvrB=AddedB/Numb;

	double	Ma=AddedAA-Numb*AvrA*AvrA;
	double	D=Ma*(AddedBB-Numb*AvrB*AvrB);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AddedAB-Numb*AvrA*AvrB;
	return K/D;
}
int	RotationPattern::GetAdoptLayer(ImageBuffer *ImageMasterList[])
{
	double	LMaxD=1.0;
	int		LMaxLayer=0;
	for(int Layer=0;Layer<Parent->GetLayerNumb();Layer++){
		double AddedA, AddedAA;
		MakeCoeffData(*this,*ImageMasterList[Layer],AddedA, AddedAA);
		double DAvr;
		double	V=GetVar(0 ,0 ,*ImageMasterList[Layer] ,DAvr);
		int	dx,dy;
		dy=-10;
		double	MaxD=0;
		int	MaxDx=0;
		int	MaxDy=0;
		for(dx=-10;dx<10;dx+=2){
			//double	D=GetCoeff	(*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer]);
			double	D=GetImageBufferCoeff(*this ,*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer] ,AddedA, AddedAA);
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
		dx=10;
		for(dy=-10;dy<10;dy+=2){
			//double	D=GetCoeff	(*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer]);
			double	D=GetImageBufferCoeff(*this ,*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer] ,AddedA, AddedAA);
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
		dy=10;
		for(dx=10;dx>-10;dx-=2){
			//double	D=GetCoeff	(*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer]);
			double	D=GetImageBufferCoeff(*this ,*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer] ,AddedA, AddedAA);
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
		dx=-10;
		for(dy=10;dy>-10;dy-=2){
			//double	D=GetCoeff	(*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer]);
			double	D=GetImageBufferCoeff(*this ,*ImageMasterList[Layer] ,dx ,dy ,*ImageMasterList[Layer] ,AddedA, AddedAA);
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
		for(dx=-1;dx<=1;dx++){
			for(dy=-1;dy<=1;dy++){
				if(dx==0 && dy==0)
					continue;
				double	D=GetImageBufferCoeff(*this ,*ImageMasterList[Layer] ,MaxDx+dx ,MaxDy+dy ,*ImageMasterList[Layer] ,AddedA, AddedAA);
				if(MaxD<D){
					MaxD=D;
					MaxDx=dx;
					MaxDy=dy;
				}
			}
		}
		if(V>5){
			double	F=log(V+2)/MaxD;
			if(LMaxD<F){
				LMaxD=F;
				LMaxLayer=Layer;
			}
		}
	}
	return LMaxLayer;
}


int	RotationPattern::GetAdoptLayerMinV(ImageBuffer *ImageMasterList[])
{
	FlexArea	TopArea;
	FlexArea	LeftArea;
	FlexArea	RightArea;
	FlexArea	BottomArea;

	TopArea		.SetRectangle(GetMinX(),GetMinY()-10,GetMaxX(),GetMinY());
	LeftArea	.SetRectangle(GetMinX()-10,GetMinY(),GetMinX(),GetMaxY());
	RightArea	.SetRectangle(GetMaxX(),GetMinY(),GetMaxX()+10,GetMaxY());
	BottomArea	.SetRectangle(GetMinX(),GetMaxY(),GetMaxX(),GetMaxY()+10);


	double	LMaxD=1.0;
	int		LMaxLayer=0;
	for(int Layer=0;Layer<Parent->GetLayerNumb();Layer++){
		double DAvr;
		double	V1=TopArea		.GetVar(0 ,0 ,*ImageMasterList[Layer] ,DAvr);
		double	V2=LeftArea		.GetVar(0 ,0 ,*ImageMasterList[Layer] ,DAvr);
		double	V3=RightArea	.GetVar(0 ,0 ,*ImageMasterList[Layer] ,DAvr);
		double	V4=BottomArea	.GetVar(0 ,0 ,*ImageMasterList[Layer] ,DAvr);
		double	V=V1+V2+V3+V4;
		if(LMaxD<V){
			LMaxD=V;
			LMaxLayer=Layer;
		}
	}
	return LMaxLayer;
}



bool	RotationPattern::IsEveryPartFlat(double ThresholdFlat ,ImageBuffer *ImageMasterList)
{
	int	Wi=GetWidth()/4;
	int	Hi=GetHeight()/4;
	double	PA=0;
	double	PAA=0;
	int		Numb=0;
	double	MinD=256;
	double	MaxD=0;
	int	MinArea=Wi*Hi/5;
	for(int yn=0;yn<4;yn++){
		for(int xn=0;xn<4;xn++){
			FlexArea	A;
			A=*this;
			A.ClipArea(GetMinX()+xn*Wi,GetMinY()+yn*Hi ,GetMinX()+(xn+1)*Wi,GetMinY()+(yn+1)*Hi);
			if(A.GetPatternByte()>MinArea){
				double	DAvr;
				double	V=A.GetVar(0,0,*ImageMasterList,DAvr);
				if(V>ThresholdFlat){
					return false;
				}
				MinD=min(MinD,DAvr);
				MaxD=max(MaxD,DAvr);
				PA+=DAvr;
				PAA+=DAvr*DAvr;
				Numb++;
			}
		}
	}
	int	W16=(GetWidth ()+15)/16;
	int	H16=(GetHeight()+15)/16;
	{
		FlexArea	A;
		A=*this;
		A.ClipArea(GetMinX(),GetMinY() ,GetMaxX(),GetMinY()+H16);
		if(A.GetPatternByte()>MinArea){
			double	DAvr;
			double	V=A.GetVar(0,0,*ImageMasterList,DAvr);
			if(V>ThresholdFlat){
				return false;
			}
			MinD=min(MinD,DAvr);
			MaxD=max(MaxD,DAvr);
			PA+=DAvr;
			PAA+=DAvr*DAvr;
			Numb++;
		}
	}
	{
		FlexArea	A;
		A=*this;
		A.ClipArea(GetMinX(),GetMinY() ,GetMinX()+W16,GetMaxY());
		if(A.GetPatternByte()>MinArea){
			double	DAvr;
			double	V=A.GetVar(0,0,*ImageMasterList,DAvr);
			if(V>ThresholdFlat){
				return false;
			}
			MinD=min(MinD,DAvr);
			MaxD=max(MaxD,DAvr);
			PA+=DAvr;
			PAA+=DAvr*DAvr;
			Numb++;
		}
	}
	{
		FlexArea	A;
		A=*this;
		A.ClipArea(GetMaxX()-W16,GetMinY() ,GetMaxX(),GetMaxY());
		if(A.GetPatternByte()>MinArea){
			double	DAvr;
			double	V=A.GetVar(0,0,*ImageMasterList,DAvr);
			if(V>ThresholdFlat){
				return false;
			}
			MinD=min(MinD,DAvr);
			MaxD=max(MaxD,DAvr);
			PA+=DAvr;
			PAA+=DAvr*DAvr;
			Numb++;
		}
	}
	{
		FlexArea	A;
		A=*this;
		A.ClipArea(GetMinX(),GetMaxY()-H16 ,GetMaxX(),GetMaxY());
		if(A.GetPatternByte()>MinArea){
			double	DAvr;
			double	V=A.GetVar(0,0,*ImageMasterList,DAvr);
			if(V>ThresholdFlat){
				return false;
			}
			MinD=min(MinD,DAvr);
			MaxD=max(MaxD,DAvr);
			PA+=DAvr;
			PAA+=DAvr*DAvr;
			Numb++;
		}
	}

	if(Numb==0)
		return true;
	if(MaxD-MinD>ThresholdFlat)
		return false;
	double	Avr=PA/Numb;
	double	M=PAA/Numb-Avr*Avr;
	if(M<0)
		return true;
	M=sqrt(M);
	if(M>ThresholdFlat)
		return false;
	return true;
}

double	RotationPattern::MakeVDiff(int x,int y,BMatrix &map)
{
	DotColorMatchingBase	*BBase=dynamic_cast<DotColorMatchingBase *>(Parent->GetParentBase());
	int SeearchDot=BBase->SearchAreaForVariation;
	int	AddedA	=0;
	int	AddedAA	=0;
	int	Numb	=0;
	int	X1=x-SeearchDot;
	int	XNumb=SeearchDot+SeearchDot+1;
	int	Y1=y-SeearchDot;
	int	YNumb=SeearchDot+SeearchDot+1;
	if(Y1<0){
		YNumb+=Y1;
		Y1=0;
	}
	if(Y1+YNumb>=YLen){
		YNumb=YLen-Y1;
	}
	if(X1<0){
		XNumb+=X1;
		X1=0;
	}
	if(X1+XNumb>=XLen){
		XNumb=XLen-X1;
	}
	if(XNumb<=0 || YNumb<=0)
		return 0.0;

	int	SkipY=1;
	if(YNumb>20)
		SkipY=3;
	else if(YNumb>10)
		SkipY=2;

	for(int yn=0;yn<YNumb;yn+=SkipY){
		BYTE	*L=map[Y1+yn];
		if(L!=NULL){
			BYTE	*dp=&L[X1];
			for(int xn=0;xn<XNumb;xn++){
				BYTE	d=dp[xn];
				AddedA+=d;
				AddedAA+=d*d;
			}
		}
		else{
			BYTE	d=map.GetConstantBrightness(Y1+yn);
			AddedA+=d*XNumb;
			AddedAA+=d*d*XNumb;
		}
		Numb+=XNumb;
	}
	if(Numb<20)
		return 0;
	double	Avr=((double)AddedA)/Numb;
	double	M=((double)AddedAA)/Numb-Avr*Avr;
	return sqrt(M);
}
void	MakeSelfCoeffData(FlexArea &Area,BMatrix &Map,int XLen ,int YLen ,double &AddedA, double &AddedAA)
{
	int N=Area.GetFLineLen();
	AddedA	=0;
	AddedAA	=0;
	int		Numb=0;
	if(Area.GetPatternByte()<32767){
		int	iAddedA	=0;
		int	iAddedAA=0;
		for(int i=0;i<N;i++){
			int	Y=Area.GetFLineAbsY(i);
			if(Y<0 || YLen<=Y)
				continue;
			int	DestY=Y;
			if(DestY<0 || YLen<=DestY)
				continue;
			int	X1=Area.GetFLineLeftX(i);
			int	numb=Area.GetFLineNumb(i);
			if(X1<0){
				numb+=X1;
				X1=0;
			}
			if(X1+numb>=XLen){
				numb=XLen-X1;
			}
			int	DestX=X1;
			if(DestX<0){
				numb+=DestX;
				X1-=DestX;
				DestX=0;
			}
			if(DestX+numb>=XLen){
				numb=XLen-DestX;
			}
			if(numb<=0)
				continue;
			BYTE	*L=Map[Y];
			if(L!=NULL){
				BYTE	*sp=&L[X1];
				for(int xn=0;xn<numb;xn++){
					BYTE	s=*sp++;
					iAddedA	+=s;
					iAddedAA+=s*s;
				}
			}
			else{
				BYTE	s=Map.GetConstantBrightness(Y);
				iAddedA	+=s*numb;
				iAddedAA+=s*s*numb;
			}
			Numb+=numb;
		}
		AddedA	=iAddedA	;
		AddedAA	=iAddedAA	;
	}
	else{
		for(int i=0;i<N;i++){
			int	Y=Area.GetFLineAbsY(i);
			if(Y<0 || YLen<=Y)
				continue;
			int	DestY=Y;
			if(DestY<0 || YLen<=DestY)
				continue;
			int	X1=Area.GetFLineLeftX(i);
			int	numb=Area.GetFLineNumb(i);
			if(X1<0){
				numb+=X1;
				X1=0;
			}
			if(X1+numb>=XLen){
				numb=XLen-X1;
			}
			int	DestX=X1;
			if(DestX<0){
				numb+=DestX;
				X1-=DestX;
				DestX=0;
			}
			if(DestX+numb>=XLen){
				numb=XLen-DestX;
			}
			if(numb<=0)
				continue;
			BYTE	*sp=Map[Y];
			int	iAddedA	=0;
			int	iAddedAA=0;
			if(sp!=NULL){
				for(int xn=0;xn<numb;xn++){
					BYTE	s=sp[X1+xn];
					iAddedA	+=s;
					iAddedAA+=s*s;
				}
			}
			else{
				BYTE	s=Map.GetConstantBrightness(Y);
				iAddedA	+=s*numb;
				iAddedAA+=s*s*numb;
			}
			Numb+=numb;
			AddedA	+=iAddedA	;
			AddedAA	+=iAddedAA	;
		}
	}
}

double	GetSelfCoeff(FlexArea &Area,int dx ,int dy
					,BMatrix &Map,int XLen ,int YLen
					,double AddedA, double AddedAA
					,double &DVar)
{
	int N=Area.GetFLineLen();

	double	AddedB	=0;
	double	AddedBB	=0;
	double	AddedAB	=0;
	int		Numb=0;

	int	MinX=Area.GetMinX();
	int	MinY=Area.GetMinY();
	int	MaxX=Area.GetMaxX();
	int	MaxY=Area.GetMaxY();

	if(0<=(MinX+dx) && (MaxX+dx)<XLen && 0<=(MinY+dy) && (MaxY+dy)<YLen){
		if(Area.GetPatternByte()<32767){
			int	iAddedB	=0;
			int	iAddedBB=0;
			int	iAddedAB=0;
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;
				BYTE	*Ls=Map[Y];
				BYTE	*Ld=Map[DestY];
				if(Ls!=NULL && Ld!=NULL){
					BYTE	*sp=&Ls[X1];
					BYTE	*dp=&Ld[DestX];
					for(int xn=0;xn<numb;xn++){
						BYTE	s=*sp++;
						BYTE	d=*dp++;
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
				}
				else
				if(Ls==NULL && Ld!=NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					BYTE	*dp=&Ld[DestX];
					for(int xn=0;xn<numb;xn++){
						BYTE	d=*dp++;
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
				}
				else
				if(Ls!=NULL && Ld==NULL){
					BYTE	*sp=&Ls[X1];
					BYTE	d=Map.GetConstantBrightness(DestY);
					for(int xn=0;xn<numb;xn++){
						BYTE	s=*sp++;
						iAddedAB+=s*d;
					}
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
				}
				else
				if(Ls==NULL && Ld==NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					BYTE	d=Map.GetConstantBrightness(DestY);
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
					iAddedAB+=s*d*numb;
				}
				Numb+=numb;
			}
			AddedB	=iAddedB	;
			AddedBB	=iAddedBB	;
			AddedAB	=iAddedAB	;
		}
		else{
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;

				int	iAddedB	=0;
				int	iAddedBB=0;
				int	iAddedAB=0;

				BYTE	*sp=Map[Y];
				BYTE	*dp=Map[DestY];
				if(sp!=NULL && dp!=NULL){
					for(int xn=0;xn<numb;xn++){
						BYTE	s=sp[X1+xn];
						BYTE	d=dp[DestX+xn];
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
				}
				else
				if(sp==NULL && dp!=NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					for(int xn=0;xn<numb;xn++){
						BYTE	d=dp[DestX+xn];
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
				}
				else
				if(sp!=NULL && dp==NULL){
					BYTE	d=Map.GetConstantBrightness(DestY);
					for(int xn=0;xn<numb;xn++){
						BYTE	s=sp[X1+xn];
						iAddedAB+=s*d;
					}
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
				}
				else
				if(sp==NULL && dp==NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					BYTE	d=Map.GetConstantBrightness(DestY);
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
					iAddedAB+=s*d*numb;
				}
				Numb+=numb;
				AddedB	+=iAddedB	;
				AddedBB	+=iAddedBB	;
				AddedAB	+=iAddedAB	;
			}
		}
	}
	else{
		AddedA	=0;
		AddedAA	=0;
		if(Area.GetPatternByte()<32767){
			int	iAddedA	=0;
			int	iAddedAA=0;
			int	iAddedB	=0;
			int	iAddedBB=0;
			int	iAddedAB=0;
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;

				BYTE	*Ls=Map[Y];
				BYTE	*Ld=Map[DestY];
				if(Ls!=NULL && Ld!=NULL){
					BYTE	*sp=&Ls[X1];
					BYTE	*dp=&Ld[DestX];
					for(int xn=0;xn<numb;xn++){
						BYTE	s=*sp++;
						BYTE	d=*dp++;
						iAddedA	+=s;
						iAddedAA+=s*s;
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
				}
				else
				if(Ls==NULL && Ld!=NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					BYTE	*dp=&Ld[DestX];
					for(int xn=0;xn<numb;xn++){
						BYTE	d=*dp++;
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
					iAddedA	+=s*numb;
					iAddedAA+=s*s*numb;
				}
				else
				if(Ls!=NULL && Ld==NULL){
					BYTE	*sp=&Ls[X1];
					BYTE	d=Map.GetConstantBrightness(DestY);
					for(int xn=0;xn<numb;xn++){
						BYTE	s=*sp++;
						iAddedA	+=s;
						iAddedAA+=s*s;
						iAddedAB+=s*d;
					}
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
				}
				else
				if(Ls==NULL && Ld==NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					BYTE	d=Map.GetConstantBrightness(DestY);
					iAddedA	+=s*numb;
					iAddedAA+=s*s*numb;
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
					iAddedAB+=s*d*numb;
				}
				Numb+=numb;
			}
			AddedA	=iAddedA	;
			AddedAA	=iAddedAA	;
			AddedB	=iAddedB	;
			AddedBB	=iAddedBB	;
			AddedAB	=iAddedAB	;
		}
		else{
			for(int i=0;i<N;i++){
				int	Y=Area.GetFLineAbsY(i);
				if(Y<0 || YLen<=Y)
					continue;
				int	DestY=Y+dy;
				if(DestY<0 || YLen<=DestY)
					continue;
				int	X1=Area.GetFLineLeftX(i);
				int	numb=Area.GetFLineNumb(i);
				if(X1<0){
					numb+=X1;
					X1=0;
				}
				if(X1+numb>=XLen){
					numb=XLen-X1;
				}
				int	DestX=X1+dx;
				if(DestX<0){
					numb+=DestX;
					X1-=DestX;
					DestX=0;
				}
				if(DestX+numb>=XLen){
					numb=XLen-DestX;
				}
				if(numb<=0)
					continue;

				int	iAddedA	=0;
				int	iAddedAA=0;
				int	iAddedB	=0;
				int	iAddedBB=0;
				int	iAddedAB=0;

				BYTE	*sp=Map[Y];
				BYTE	*dp=Map[DestY];
				if(sp!=NULL && dp!=NULL){
					for(int xn=0;xn<numb;xn++){
						BYTE	s=sp[X1+xn];
						BYTE	d=dp[DestX+xn];
						iAddedA	+=s;
						iAddedAA+=s*s;
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
				}
				else
				if(sp==NULL && dp!=NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					for(int xn=0;xn<numb;xn++){
						BYTE	d=dp[DestX+xn];
						iAddedB	+=d;
						iAddedBB+=d*d;
						iAddedAB+=s*d;
					}
					iAddedA	+=s*numb;
					iAddedAA+=s*s*numb;
				}
				else
				if(sp!=NULL && dp==NULL){
					BYTE	d=Map.GetConstantBrightness(DestY);
					for(int xn=0;xn<numb;xn++){
						BYTE	s=sp[X1+xn];
						iAddedA	+=s;
						iAddedAA+=s*s;
						iAddedAB+=s*d;
					}
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
				}
				else
				if(sp==NULL && dp==NULL){
					BYTE	s=Map.GetConstantBrightness(Y);
					BYTE	d=Map.GetConstantBrightness(DestY);
					iAddedA	+=s*numb;
					iAddedAA+=s*s*numb;
					iAddedB	+=d*numb;
					iAddedBB+=d*d*numb;
					iAddedAB+=s*d*numb;
				}
				Numb+=numb;
				AddedA	+=iAddedA	;
				AddedAA	+=iAddedAA	;
				AddedB	+=iAddedB	;
				AddedBB	+=iAddedBB	;
				AddedAB	+=iAddedAB	;
			}
		}
	}
	if(Numb<5)
		return 0;
	double	AvrA=AddedA/Numb;
	double	AvrB=AddedB/Numb;

	double	Ma=AddedAA-Numb*AvrA*AvrA;
	DVar	=Ma/Numb;
	double	D=Ma*(AddedBB-Numb*AvrB*AvrB);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=AddedAB-Numb*AvrA*AvrB;
	return K/D;
}

bool	RotationPattern::ResembleNeighbor(FlexArea &Area,double ThresholdFlatPattern)
{
	double	DVar=0;
	DotColorMatchingBase	*BBase=dynamic_cast<DotColorMatchingBase *>(Parent->GetParentBase());
	int	SearchAreaX=Parent->GetThresholdR(NULL)->AreaSearchX;
	int	SearchAreaY=Parent->GetThresholdR(NULL)->AreaSearchY;
	double	AddedA	;
	double	AddedAA	;
	MakeSelfCoeffData(Area,BuffByMaster[0].Map[AdoptLayer] ,XLen,YLen,AddedA,AddedAA);

	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	for(int dy=-SearchAreaY;dy<=SearchAreaY;dy+=2){
		for(int dx=-SearchAreaX;dx<=SearchAreaX;dx+=2){
			if(-3<=dx && dx<=3 && -3<=dy && dy<=3)
				continue;
			double	D=GetSelfCoeff(Area,dx ,dy ,BuffByMaster[0].Map[AdoptLayer] ,XLen,YLen,AddedA,AddedAA,DVar);
			if(D>BBase->CoefSelfSearch){
				return true;
			}
			if(D>MaxD){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	for(int dy=-1;dy<=1;dy++){
		for(int dx=-1;dx<=1;dx++){
			if(dx==0 && dy==0)
				continue;
			double	D=GetSelfCoeff(Area,MaxDx+dx ,MaxDy+dy ,BuffByMaster[0].Map[AdoptLayer] ,XLen,YLen,AddedA,AddedAA,DVar);
			if(D>BBase->CoefSelfSearch){
				return true;
			}
		}
	}
	if(DVar<ThresholdFlatPattern){
		return true;
	}
	return false;
}

double	MakeAve(FlexArea &Area,BMatrix &BMap,int XLen,int YLen ,int &AddedA,int &AddedAA)
{
	AddedA=0;
	AddedAA=0;
	int	Numb=0;
	int	N=Area.GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y	=Area.GetFLineAbsY(i);
		if(0<=Y && Y<YLen){
			int	X1	=Area.GetFLineLeftX(i);
			int	numb=Area.GetFLineNumb(i);
			if(X1<0){
				numb+=X1;
				X1=0;
			}
			if(X1+numb>XLen){
				numb=XLen-X1;
			}
			BYTE	*s=BMap[Y];
			if(s!=NULL){
				for(int x=0;x<numb;x++){
					BYTE	k=s[X1+x];
					AddedA	+=k;
					AddedAA	+=k*k;
					Numb++;
				}
			}
			else{
				BYTE	k=BMap.GetConstantBrightness(Y);
				AddedA	+=k*numb;
				AddedAA	+=k*k*numb;
			}
		}
	}
	double	Avr=((double)AddedA)/Numb;
	double	M=((double)AddedAA)/Numb-Avr*Avr;
	return M;
}

void	RotationPattern::MakeDivFlexAreas(FlexArea &EdgeArea ,int AreaSize ,double VTh,ImageBuffer *ImageMasterList[]
									,PureFlexAreaListContainer &FPack
									,int Layer)
{
	int	cx=XLen/2;
	int	cy=YLen/2;
	DivArea.RemoveAll();
	FlexArea	CurrentArea=*this;
	CurrentArea.ThinAreaN(3);

	int	TmpXLen=XLen;
	int	TmpYLen=YLen;
	int	TmpXByte=(TmpXLen+7)/8;

	BYTE	TmpMapDim[10000];
	BYTE	TmpMapDim2[10000];

	BYTE	**TmpMap =MakeMatrixBuff(TmpXByte,TmpYLen,TmpMapDim ,sizeof(TmpMapDim ));
	BYTE	**TmpMap2=MakeMatrixBuff(TmpXByte,TmpYLen,TmpMapDim2,sizeof(TmpMapDim2));
	MatrixBuffClear(TmpMap,0,TmpXByte,TmpYLen);

	for(int i=0;i<CurrentArea.GetFLineLen();i++){
		int	ym=CurrentArea.GetFLineAbsY (i);
		int	Y =ym-Parent->MasterCy+cy;
		int	xm1=CurrentArea.GetFLineLeftX(i);
		int	X1=xm1-Parent->MasterCx+cx;
		int	Numb=CurrentArea.GetFLineNumb(i);
		//BYTE	*s=(Map[AdoptLayer])[Y];
		BYTE	*d=TmpMap[Y];
		for(int j=0;j<Numb;j++){
			if(EdgeArea.IsInclude(xm1+j,ym)==false){
				int	X=X1+j;
				double	v=CalcSmallBlockV(X,Y,BuffByMaster[0].Map[Layer],AreaSize);
				if(v>VTh){
					SetBmpBitOnY1(d,X);
				}
			}
		}
	}
	::FatArea(TmpMap,TmpMap2,TmpXByte,TmpYLen);
	int	MinAreaDots=(AreaSize+2)*(AreaSize+2);
	::PickupFlexArea(TmpMap ,TmpXByte ,TmpXByte*8,TmpYLen ,FPack,-1,false);
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
		PureFlexAreaList *NextF=f->GetNext();
		//if(f->GetPatternByte()<20 || f->GetPatternWidth()<=2 || f->GetPatternHeight()<=2){
		if(f->GetPatternByte()<MinAreaDots){
			FPack.RemoveList(f);
			delete	f;
		}
		f=NextF;
	}
	DeleteMatrixBuff(TmpMap2,TmpMapDim2,TmpYLen);
	DeleteMatrixBuff(TmpMap ,TmpMapDim ,TmpYLen);
}
									

void	RotationPattern::MakeDivArea(FlexArea &EdgeArea ,int AreaSize ,double VTh,ImageBuffer *ImageMasterList[])
{
	int	cx=XLen/2;
	int	cy=YLen/2;
	DivArea.RemoveAll();
	DotColorMatchingBase* ABase = ((DotColorMatchingBase*)Parent->GetParentBase());

	PureFlexAreaListContainer FPack;
	MakeDivFlexAreas(EdgeArea ,AreaSize ,VTh,ImageMasterList ,FPack,AdoptLayer);

	PureFlexAreaList *f;
	int	TotalDot=0;
	while((f=FPack.GetFirst())!=NULL){
		FPack.RemoveList(f);
		f->MoveToNoClip(Parent->MasterCx-cx,Parent->MasterCy-cy);
		f->ClipArea(*this);
		if(f->GetPatternByte()< ABase->MinDivAreaPixels 
		|| max(f->GetWidth(),f->GetHeight())< ABase->MinDivAreaLength){
			delete	f;
		}
		else{
			TotalDot += f->GetPatternByte();
			FlexAreaCoef	*g=new FlexAreaCoef(*f);
			DivArea.AppendList(g);
			delete	f;
		}
	}
	if(TotalDot<ABase->MinTotalDivAreaPixels){
		DivArea.RemoveAll();
	}

	double	DAvr=0;
	int		DAvrNumb=0;
	for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
		double	TmpDAvr;
		a->GetVar(0 ,0,*ImageMasterList[AdoptLayer]
                           ,TmpDAvr);
		DAvr+=TmpDAvr;
		DAvrNumb++;
	}
	if(DAvr<10*DAvrNumb){
		DivArea.RemoveAll();
	}

	for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
		for(int i=0;i<3;i++){
			a->DivA[i]=0;
			a->DivAA[i]=0;
		}
		int	N=a->GetFLineLen();
		for(int i=0;i<N;i++){
			int	Y =a->GetFLineAbsY (i)-Parent->MasterCy+cy;
			//if(N>32 && ((Y&0x01)!=0))
			//	continue;
			int	X1=a->GetFLineLeftX(i)-Parent->MasterCx+cx;
			int	Numb=a->GetFLineNumb(i);

			for(int Layer=0;Layer<3 && Layer<Parent->GetLayerNumb();Layer++){
				BYTE	*s=(BuffByMaster[0].Map[Layer])[Y];
				if(s!=NULL){
					for(int j=0;j<Numb;j++){
						BYTE	c=s[X1+j];
						a->DivA [Layer]+=c;
						a->DivAA[Layer]+=c*c;
					}
				}
				else{
					BYTE	m=BuffByMaster[0].Map[Layer].GetConstantBrightness(Y);
					a->DivA [Layer]+=m*Numb;
					a->DivAA[Layer]+=m*m*Numb;
				}
			}
		}
	}
}

double	RotationPattern::CalcSmallBlockV(int X,int Y,BMatrix &map,int AreaSize)
{
	int	x1=max(X-AreaSize/2,0);
	int	y1=max(Y-AreaSize/2,0);
	int	x2=min(x1+AreaSize,XLen);
	int	y2=min(y1+AreaSize,YLen);

	int	MAddA	=0;
	int	MAddAA	=0;
	int	CalcNumb=0;
	int	XNumb=x2-x1;
	for(int y=y1;y<y2;y++){
		BYTE	*s=(map[y]);
		if(s!=NULL){
			s+=x1;
			//for(int x=x1;x<x2;x++){
			for(int i=0;i<XNumb;i++){
				BYTE	a=s[i];
				MAddA  +=a;
				MAddAA +=a*a;
			}
			CalcNumb+=XNumb;
		}
		else{
			BYTE	a=map.GetConstantBrightness(y);
			int	numb=x2-x1;
			if(numb>0){
				MAddA  +=a*numb;
				MAddAA +=a*a*numb;
				CalcNumb+=numb;
			}
		}
	}
	if(CalcNumb<AreaSize*AreaSize/2)
		return 0;

	double	Avr=((double)MAddA)/CalcNumb;
	double	V=MAddAA-Avr*Avr*CalcNumb;	//V=•ªŽU
	double	S=sqrt(V/CalcNumb);
	return S;
}

void	RotationPattern::CopyFrom(BMatrix &BBMap ,struct BMatrixBrightHL::BrightHLStruct **HLMap ,int layer
								,int SearchDotForBrightnessRange
								,int NoiseBrightness
								, ImageBuffer &Buff
								,double CosS, double SinS)
{
	BYTE	BMapBuff[600*600];
	BYTE	**BMap=MakeMatrixBuff(BBMap.GetWidth(),BBMap.GetHeight()
					,BMapBuff,sizeof(BMapBuff));

	int	HalfNoiseBrightness=(NoiseBrightness>>1);
	int	cx=XLen/2;
	int	cy=YLen/2;
	for(int y=0;y<YLen;y++){
		BYTE	*d=BMap[y];
		struct BMatrixBrightHL::BrightHLStruct *dHL=HLMap[y];
		double	xY=(y-cy)*SinS+Parent->MasterCx;
		double	yY=(y-cy)*CosS+Parent->MasterCy;;
		for(int x=0;x<XLen;x++){
			int	X= (x-cx)*CosS+xY;
			int	Y=-(x-cx)*SinS+yY;
			if(0<=Y && Y<Buff.GetHeight()
			&& 0<=X && X<Buff.GetWidth()){
				BYTE	*s=Buff.GetYWithoutDepended(Y);
				BYTE	tC=s[X];
				d[x]	=tC;

				BYTE	ML=255;
				BYTE	MH=0;
				for(int ty=-SearchDotForBrightnessRange;ty<=SearchDotForBrightnessRange;ty++){
					int	Hy=Y+ty;
					if(0<=Hy && Hy<Buff.GetHeight()){
						BYTE	*hs=Buff.GetY(Hy);
						int	Hx1=X-SearchDotForBrightnessRange;
						int	Hx2=X+SearchDotForBrightnessRange;
						if( Hx1<0)
							Hx1=0;
						if(Buff.GetWidth()<=Hx2)
							Hx2=Buff.GetWidth()-1;
						int	tNumb=Hx2-Hx1+1;
						if(tNumb>0){
							BYTE	*hp=&hs[Hx1];
							for(int k=0;k<tNumb;k++){
								BYTE	c=*hp;
								hp++;
								if(ML>c)
									ML=c;
								else
								if(MH<c)
									MH=c;
							}
						}
					}
				}
				ML=((tC+ML)>>1)+HalfNoiseBrightness;
				MH=((MH+tC)>>1)-HalfNoiseBrightness;
				if(ML>tC)
					ML=tC;
				if(MH<tC)
					MH=tC;

				dHL[x].BrHigh[layer]=MH;
				dHL[x].BrLow[layer] =ML;
			}
			else{
				d[x]=0;
				dHL[x].BrHigh[layer]=255;
				dHL[x].BrLow[layer] =0;
			}
		}
	}
	BBMap.Copy(BMap,BBMap.GetWidth(),BBMap.GetHeight(),5);
	DeleteMatrixBuff(BMap,BMapBuff,BBMap.GetHeight());
}

void	RotationPattern::CopyHSVFrom(struct HSVValue	**tHSVMaster
									,ImageBuffer *ImageMasterList[3]
									,double CosS,double SinS)
{
	int	MaxWidth	=ImageMasterList[0]->GetWidth();
	int	MaxHeight	=ImageMasterList[0]->GetHeight();

	int	cx=XLen/2;
	int	cy=YLen/2;
	for(int y=0;y<YLen;y++){
		double	xY=(y-cy)*SinS+Parent->MasterCx;
		double	yY=(y-cy)*CosS+Parent->MasterCy;;
		for(int x=0;x<XLen;x++){
			int	X= (x-cx)*CosS+xY;
			int	Y=-(x-cx)*SinS+yY;
			if(0<=Y && Y<MaxHeight
			&& 0<=X && X<MaxWidth){
				int	s0=ImageMasterList[0]->GetY(Y)[X];
				int	s1=ImageMasterList[1]->GetY(Y)[X];
				int	s2=ImageMasterList[2]->GetY(Y)[X];

				double	Mh,Ms ,Mv;
				::RGB2HSV(Mh,Ms ,Mv ,s0 ,s1 ,s2);
				tHSVMaster[y][x].H=Mh;
				tHSVMaster[y][x].S=Ms;
				tHSVMaster[y][x].V=Mv;
			}
		}
	}
}
QImage	RotationPattern::MakeImage(void)
{
	QImage	RetImage(XLen,YLen,QImage::Format_ARGB32);
	for(int y=0;y<YLen;y++){
		QRgb	*d=(QRgb *)RetImage.scanLine(y);
		BYTE	*s0=(BuffByMaster[0].Map[0])[y];
		BYTE	*s1=(BuffByMaster[0].Map[1])[y];
		BYTE	*s2=(BuffByMaster[0].Map[2])[y];
		BYTE	c0,c1,c2;
		if(s0==NULL)
			c0=BuffByMaster[0].Map[0].GetConstantBrightness(y);
		if(s1==NULL)
			c1=BuffByMaster[0].Map[1].GetConstantBrightness(y);
		if(s2==NULL)
			c2=BuffByMaster[0].Map[2].GetConstantBrightness(y);
		for(int x=0;x<XLen;x++){
			*d=qRgb( (s0!=NULL)?*(s0++):c0
					,(s1!=NULL)?*(s1++):c1
					,(s2!=NULL)?*(s2++):c2);
			d++;
		}
	}
	//FlexArea	_DivArea=DivArea;
	//_DivArea.MoveToNoClip(-Parent->MasterCx+Cx,-Parent->MasterCy+Cy);
	int	Cx=XLen/2;
	int	Cy=YLen/2;
	QRgb	Col=qRgba(0,192,192,128);
	for(FlexAreaCoef *a=DivArea.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawAlpha(-Parent->MasterCx+Cx,-Parent->MasterCy+Cy
					,&RetImage,Col
					,1.0,0,0);
	}

	QRgb	BackGroundCol=qRgba(0,0,192,128);
	BackGround.DrawAlpha(-Parent->MasterCx+Cx,-Parent->MasterCy+Cy
					,&RetImage,BackGroundCol
					,1.0,0,0);

	if(VLine!=NULL){
		for(int i=0;i<CountVLine;i++){
			VLine[i].Draw(RetImage,-Parent->MasterCx+Cx,-Parent->MasterCy+Cy,1);
		}
	}
	if(HLine!=NULL){
		for(int i=0;i<CountHLine;i++){
			HLine[i].Draw(RetImage,-Parent->MasterCx+Cx,-Parent->MasterCy+Cy,1);
		}
	}

	return RetImage;
}

int	RotationPattern::GetMinDivProjection(void)
{
	int	XByte	=(XLen+7)/8;

	BYTE	PMapDim[10000];

	BYTE	**PMap=MakeMatrixBuff(XByte ,YLen ,PMapDim,sizeof(PMapDim));
	MatrixBuffClear	(PMap ,0,XByte ,YLen);

	int	X1=DivArea.GetMinX();
	int	Y1=DivArea.GetMinY();
	DivArea.MakeBitData(PMap,-X1,-Y1,XLen,YLen);

	int	MinD=99999999;

	for(int i=0;i<360;i++){
		double angle=((double)i)*0.5;
		int	D=GetProjetion(PMap,angle*M_PI/180.0);
		if(MinD>D){
			MinD=D;
		}
	}
	DeleteMatrixBuff(PMap,PMapDim,YLen);
	return MinD;
}

int		RotationPattern::GetProjetion(BYTE **PMap,double angle)
{
	double	CosS=cos(angle);
	double	SinS=sin(angle);
	int	R=max(XLen,YLen)*1.5;
	int	R2=R/2;
	int	Cx=XLen/2;
	int	Cy=YLen/2;
	int	DCounter=0;
	int	Sep;
	if(R<20)
		Sep=1;
	else if(R<50)
		Sep=2;
	else if(R<100)
		Sep=3;
	else
		Sep=4;

	for(int y=-R2;y<=R2;y+=Sep){
		double	yX= y*SinS+Cx;
		double	yY=-y*CosS+Cy;
		for(int x=-R2;x<=R2;x+=Sep){
			int	X= x*CosS+yX;
			int	Y=-x*SinS+yY;
			if(0<=X && X<XLen && 0<=Y && Y<YLen){
				if(GetBmpBit(PMap,X,Y)!=0){
					DCounter++;
					break;
				}
			}
		}
	}
	return DCounter;
}
double	RotationPattern::GetMaxSelfMatch(ImageBuffer *ImageMaster,int dx ,int dy)
{
	return GetCoeff	(*ImageMaster ,dx ,dy ,*ImageMaster,1,false);
}

void	RotationPattern::BuildSubtractionMap(int ExtendedDot)
{
	if(SubtractionMap!=NULL){
		DeleteMatrixBuff(SubtractionMap,YLen);
		SubtractionMap=NULL;
	}
	SubtractionMap	=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear	(SubtractionMap ,0 ,XByte,YLen);
	int	X1=GetMinX();
	int	Y1=GetMinY();
	int	XMergin=(XLen-GetWidth())/2;
	int	YMergin=(YLen-GetHeight())/2;
	//FatAreaN(ExtendedDot);
	MakeBitData(SubtractionMap
                        ,-X1+XMergin,-Y1+YMergin
                        ,XLen,YLen);
	int		tXByte=(XLen+7)/8;
	BYTE	TmpDim[10000];
	BYTE	**TmpBuff=MakeMatrixBuff(tXByte,YLen,TmpDim,sizeof(TmpDim));
	Parent->GetLayersBase()->FatAreaN(SubtractionMap,TmpBuff,tXByte,YLen,ExtendedDot);
	DeleteMatrixBuff(TmpBuff,TmpDim,YLen);
}

void	RotationPattern::ClearSubtractionMap(void)
{
	if(SubtractionMap!=NULL){
		DeleteMatrixBuff(SubtractionMap,YLen);
		SubtractionMap=NULL;
	}
}


double	 FlexAreaCoefXY::GetAverageOptimized(ImageBuffer &Data,int dx ,int dy)	const
{
	int 	N=0;
	double	D=0.0;
	int	YSize=Data.GetHeight();
	int	XSize=Data.GetWidth() ;

	for(int i=0;i<GetFLineLen();i++){
		int x1=GetFLineLeftX (i)+dx;
		int x2=GetFLineRightX(i)+dx;
		int y =GetFLineAbsY  (i)+dy;

		if(y<0 || y>=YSize){
			continue;
		}

		if(x1<0){
			x1=0;
		}
		if(x1>=XSize){
			x1=XSize-1;
		}
		if(x2<0){
			x2=0;
		}
		if(x2>=XSize){
			x2=XSize-1;
		}

		if(x1>x2){
			continue;
		}
		if(x2<=0 || x1>=(XSize-1)){
			continue;
		}

		int Len=x2-x1+1;
		if(Len<=0){
			continue;
		}
		BYTE	*p=Data.GetY(y)+x1;
		int Di=0;
		for(int n=0;n<Len;n++){
		   Di+= *p;
		   p++;
		   }
		D+=Di;
		N+=Len;
		}
	if(N==0){
		return(0);
	}
	return(D/N);
}
