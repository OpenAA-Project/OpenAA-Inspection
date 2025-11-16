#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "XBitImageProcessor.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XFlatInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XUndo.h"
#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspectionAlgoPacket.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"


void	FlatInspectionItem::GetDetectRedRange(BYTE r,BYTE g,BYTE b
												,short &RedRL,short &RedRH
												,short &RedGL,short &RedGH
												,short &RedBL,short &RedBH)
{
	const	FlatInspectionThreshold	*Th=GetThresholdR();
	int		RedGBMerginRate	=Th->RedGBMerginRate*256/100;
	int		RedHighRate		=Th->RedHighRate*256/100;

	RedRL=Th->RedMinBrightness;
	RedGL=((g-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
	RedBL=((b-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
	RedGH=((g+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
	RedBH=((b+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
	RedRH=((g+b)*RedHighRate)>>9;
}

int	FlatInspectionItem::ExecuteProcessingRed(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, FlexArea &MapArea
								, int OffsetX ,int OffsetY)
{
	const	FlatInspectionThreshold	*Th=GetThresholdR();

	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();

	MatrixBuffClear	(NGMapN ,0 ,NGMapXByte ,NGMapYLen);

	int		RedGBMerginRate	=Th->RedGBMerginRate*256/100;
	int		RedHighRate		=Th->RedHighRate*256/100;

	int	N=MapArea.GetFLineLen();
	for(int i=0;i<N;i++){
		int	y =MapArea.GetFLineAbsY(i);
		int	x1=MapArea.GetFLineLeftX(i);
		int	Numb=MapArea.GetFLineNumb(i);
		int	Y=y+OffsetY;
		if(0<=Y && Y<MaxLines){
			int	X1=x1+OffsetX;
			int	X2=x1+Numb+OffsetX;
			BYTE	*sR=ImageTargetList[0]->GetY(Y);
			BYTE	*sG=ImageTargetList[1]->GetY(Y);
			BYTE	*sB=ImageTargetList[2]->GetY(Y);

			X1=max(0,X1);
			X2=min(X2,DotPerLine);
			BYTE	*m=NGMapRed[y-NGMapOffsetY];
			for(int X=X1;X<X2;X++){
				BYTE	r=sR[X];
				if(r>=Th->RedMinBrightness){
					BYTE	g=sG[X];
					BYTE	b=sB[X];
					int	gL=((g-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
					int	bL=((b-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
					if(gL<=b  || bL<=g){
						int	gH=((g+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
						int	bH=((b+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
						if((gL<=b && b<gH) || (bL<=g && g<=bH)){
							int	rL=((g+b)*RedHighRate)>>9;
							if(r>=rL){
								SetBmpBitOnY1(m,X-NGMapOffsetX);
							}
						}
					}
				}
			}
		}
	}
	PureFlexAreaListContainer FPack;
	PickupFlexArea(NGMapRed ,NGMapXByte ,NGMapXLen,NGMapYLen ,FPack);

	int64	NGCount=0;
	int64	NGDots=0;
	ResultPosListContainer	NowList;

	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		{				
			int64	Dots=p->GetPatternByte();
			if(Dots>Th->RedOKDot){
				int	Cx,Cy;
				p->MoveToNoClip(NGMapOffsetX+OffsetX,NGMapOffsetY+OffsetY);
				p->GetCenter(Cx,Cy);
				FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
				r->result =0x10500;	//Red-NG
				r->SetResult1(Dots);
				r->SetResult2(0);
				r->NGShape.SuckFrom(*p);
				r->NGSize=Dots;
				NowList.AppendList(r);
				NGCount++;
				NGDots+=Dots;
			}
		}
	}
	return NGCount;
	Res->AddMovePosList(NowList);
	Res->SetItemSearchedXY(0,0);
	if(NGCount>0){
		Res->SetAlignedXY(OffsetX,OffsetY);
		Res->SetResult1(NGCount);
		Res->SetResult2(NGDots);
		Res->SetError(5);
	}
	return NGCount;
}


int	FlatInspectionItem::ExecuteProcessingRed(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int OffsetX ,int OffsetY)
{
	const	FlatInspectionThreshold	*Th=GetThresholdR();

	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	FlatInspectionInPage	*Ap=tGetParentInPage();

	MatrixBuffClear	(NGMapN ,0 ,NGMapXByte ,NGMapYLen);

	int		RedGBMerginRate	=Th->RedGBMerginRate*256/100;
	int		RedHighRate		=Th->RedHighRate*256/100;
	int	W=GetArea().GetWidth();
	int	X1=ResultMinX;
	int	X2=X1+W;

	for(int	Y=ResultY1;Y<ResultY2;Y++){
		BYTE	*sR=ImageTargetList[0]->GetY(Y);
		BYTE	*sG=ImageTargetList[1]->GetY(Y);
		BYTE	*sB=ImageTargetList[2]->GetY(Y);
		BYTE	*mp=Ap->MaskMap[Y];
		BYTE	*m=NGMapRed[Y-NGMapOffsetY];
		for(int X=X1;X<X2;X++){
			if(GetBmpBitOnY(mp,X)!=0){
				BYTE	r=sR[X];
				if(r>=Th->RedMinBrightness){
					BYTE	g=sG[X];
					BYTE	b=sB[X];
					int	gL=((g-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
					int	bL=((b-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
					if(gL<=b  || bL<=g){
						int	gH=((g+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
						int	bH=((b+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
						if((gL<=b && b<gH) || (bL<=g && g<=bH)){
							int	rL=((g+b)*RedHighRate)>>9;
							if(r>=rL){
								SetBmpBitOnY1(m,X-NGMapOffsetX);
							}
						}
					}
				}
			}
		}
	}
	PureFlexAreaListContainer FPack;
	PickupFlexArea(NGMapRed ,NGMapXByte ,NGMapXLen,NGMapYLen ,FPack);

	int64	NGCount=0;
	int64	NGDots=0;
	ResultPosListContainer	NowList;

	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		{				
			int64	Dots=p->GetPatternByte();
			if(Dots>Th->RedOKDot){
				int	Cx,Cy;
				p->MoveToNoClip(NGMapOffsetX+OffsetX,NGMapOffsetY+OffsetY);
				p->GetCenter(Cx,Cy);
				FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
				r->result =0x10000+0x500;	//Red-NG
				r->SetResult1(Dots);
				r->SetResult2(0);
				r->NGShape.SuckFrom(*p);
				r->NGSize=Dots;
				NowList.AppendList(r);
				NGCount++;
				NGDots+=Dots;
			}
		}
	}
	return NGCount;
	Res->AddMovePosList(NowList);
	Res->SetItemSearchedXY(0,0);
	if(NGCount>0){
		Res->SetAlignedXY(OffsetX,OffsetY);
		Res->SetResult1(NGCount);
		Res->SetResult2(NGDots);
		Res->SetError(5);
	}
	return NGCount;
}