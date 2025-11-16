/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XOutlineInspectCalc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"

#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XOutlineInspect.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XPSpline.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XCrossObj.h"
#include "swap.h"

void	OutlineItem::CalcDecision(ResultInItemRoot *Res
								 ,int mx ,int my)
{
	ImageBuffer *MasterImage=&GetMasterBuff();
	ImageBuffer *TargetImage=&GetTargetBuff();

	Res->SetError(0);
	ResultDotSumInside=0;
	ResultDotSumOutside=0;
	ResultPosListContainer	NowList;
	bool	OkNInside;
	bool	OkBInside;
	bool	OkNOutside;
	bool	OkBOutside;
	const OutlineThreshold	*RThr=GetThresholdR();
	int	NNGInsideCount=InsideAlgo.CalcDecision(MasterImage
									,TargetImage
									,mx ,my ,ResultSearchX,ResultSearchY
									,RThr->InsideNOKColor
									,RThr->InsideNTrOKColor
									,RThr->InsideNOKDot
									,ResultDotSumInside ,0x0100
									,NowList,RThr->EffectiveNInside
									,OkNInside
									,MaxNGDotInsideN
									,RThr->AdjustLimitLInside,RThr->AdjustLimitHInside);
	int	NNGOutsideCount=OutsideAlgo.CalcDecision(MasterImage
									,TargetImage
									,mx ,my ,ResultSearchX,ResultSearchY
									,RThr->OutsideNOKColor
									,RThr->OutsideNTrOKColor
									,RThr->OutsideNOKDot
									,ResultDotSumOutside ,0x0200
									,NowList,RThr->EffectiveNOutside
									,OkNOutside
									,MaxNGDotOutsideN
									,RThr->AdjustLimitLOutside,RThr->AdjustLimitHOutside);

	int	BNGInsideCount=InsideAlgo.CalcDecision(MasterImage
									,TargetImage
									,mx ,my ,ResultSearchX,ResultSearchY
									,RThr->InsideBOKColor
									,RThr->InsideBTrOKColor
									,RThr->InsideBOKDot
									,ResultDotSumInside ,0x1100
									,NowList,RThr->EffectiveBInside
									,OkBInside
									,MaxNGDotInsideB
									,RThr->AdjustLimitLInside,RThr->AdjustLimitHInside);
	int	BNGOutsideCount=OutsideAlgo.CalcDecision(MasterImage
									,TargetImage
									,mx ,my ,ResultSearchX,ResultSearchY
									,RThr->OutsideBOKColor
									,RThr->OutsideBTrOKColor
									,RThr->OutsideBOKDot
									,ResultDotSumOutside ,0x1200
									,NowList,RThr->EffectiveBOutside
									,OkBOutside
									,MaxNGDotOutsideB
									,RThr->AdjustLimitLOutside,RThr->AdjustLimitHOutside);

	if(IsCompleteOk( OkNInside ,OkNOutside
					,OkBInside ,OkBOutside)==false){
		int	MinD=99999999;
		int	MinEx=0,MinEy=0;
		int	MinED=99999999;
		int	MinNNGInsideCount	=0	,MinBNGInsideCount=0;
		int	MinNNGOutsideCount	=0	,MinBNGOutsideCount=0;
		int	tMaxNGDotOutsideB=99999999;
		int	tMaxNGDotOutsideN=99999999;
		int	tMaxNGDotInsideB=99999999;
		int	tMaxNGDotInsideN=99999999;

		Res->SetError(0);
		for(int	Len=1;Len<=2 && Len<=RThr->SelfSearch;Len++){
			int	kx,ky;
			ky=-Len;
			for(kx=-Len;kx<Len;kx++){
				ResultPosListContainer	iNowList;
				if(InFunc(kx ,ky ,mx ,my
							,OkNInside
							,OkBInside
							,OkNOutside
							,OkBOutside
							,MinD
							,MinEx
							,MinEy
							,MinED
							,MinNNGInsideCount
							,MinBNGInsideCount
							,MinNNGOutsideCount
							,MinBNGOutsideCount
							,MasterImage
							,TargetImage
							,iNowList)==true){
					goto	Fin;
				}
				if(tMaxNGDotOutsideB+tMaxNGDotOutsideN+tMaxNGDotInsideB+tMaxNGDotInsideN>MaxNGDotOutsideB+MaxNGDotOutsideN+MaxNGDotInsideB+MaxNGDotInsideN){
					tMaxNGDotOutsideB=MaxNGDotOutsideB;
					tMaxNGDotOutsideN=MaxNGDotOutsideN;
					tMaxNGDotInsideB=MaxNGDotInsideB;
					tMaxNGDotInsideN=MaxNGDotInsideN;
					NowList.Move(iNowList);
				}
			}
			kx=Len;
			for(ky=-Len;ky<Len;ky++){
				ResultPosListContainer	iNowList;
				if(InFunc(kx ,ky ,mx ,my
							,OkNInside
							,OkBInside
							,OkNOutside
							,OkBOutside
							,MinD
							,MinEx
							,MinEy
							,MinED
							,MinNNGInsideCount
							,MinBNGInsideCount
							,MinNNGOutsideCount
							,MinBNGOutsideCount
							,MasterImage
							,TargetImage
							,iNowList)==true){
					goto	Fin;
				}
				if(tMaxNGDotOutsideB+tMaxNGDotOutsideN+tMaxNGDotInsideB+tMaxNGDotInsideN>MaxNGDotOutsideB+MaxNGDotOutsideN+MaxNGDotInsideB+MaxNGDotInsideN){
					tMaxNGDotOutsideB=MaxNGDotOutsideB;
					tMaxNGDotOutsideN=MaxNGDotOutsideN;
					tMaxNGDotInsideB=MaxNGDotInsideB;
					tMaxNGDotInsideN=MaxNGDotInsideN;
					NowList.Move(iNowList);
				}
			}
			ky=Len;
			for(kx=Len;kx>-Len;kx--){
				ResultPosListContainer	iNowList;
				if(InFunc(kx ,ky ,mx ,my
							,OkNInside
							,OkBInside
							,OkNOutside
							,OkBOutside
							,MinD
							,MinEx
							,MinEy
							,MinED
							,MinNNGInsideCount
							,MinBNGInsideCount
							,MinNNGOutsideCount
							,MinBNGOutsideCount
							,MasterImage
							,TargetImage
							,iNowList)==true){
					goto	Fin;
				}
				if(tMaxNGDotOutsideB+tMaxNGDotOutsideN+tMaxNGDotInsideB+tMaxNGDotInsideN>MaxNGDotOutsideB+MaxNGDotOutsideN+MaxNGDotInsideB+MaxNGDotInsideN){
					tMaxNGDotOutsideB=MaxNGDotOutsideB;
					tMaxNGDotOutsideN=MaxNGDotOutsideN;
					tMaxNGDotInsideB=MaxNGDotInsideB;
					tMaxNGDotInsideN=MaxNGDotInsideN;
					NowList.Move(iNowList);
				}
			}
			kx=-Len;
			for(ky=Len;ky>-Len;ky--){
				ResultPosListContainer	iNowList;
				if(InFunc(kx ,ky ,mx ,my
							,OkNInside
							,OkBInside
							,OkNOutside
							,OkBOutside
							,MinD
							,MinEx
							,MinEy
							,MinED
							,MinNNGInsideCount
							,MinBNGInsideCount
							,MinNNGOutsideCount
							,MinBNGOutsideCount
							,MasterImage
							,TargetImage
							,iNowList)==true){
					goto	Fin;
				}
				if(tMaxNGDotOutsideB+tMaxNGDotOutsideN+tMaxNGDotInsideB+tMaxNGDotInsideN>MaxNGDotOutsideB+MaxNGDotOutsideN+MaxNGDotInsideB+MaxNGDotInsideN){
					tMaxNGDotOutsideB=MaxNGDotOutsideB;
					tMaxNGDotOutsideN=MaxNGDotOutsideN;
					tMaxNGDotInsideB=MaxNGDotInsideB;
					tMaxNGDotInsideN=MaxNGDotInsideN;
					NowList.Move(iNowList);
				}
			}
		}
		MaxNGDotOutsideB=tMaxNGDotOutsideB;
		MaxNGDotOutsideN=tMaxNGDotOutsideN;
		MaxNGDotInsideB=tMaxNGDotInsideB;
		MaxNGDotInsideN=tMaxNGDotInsideN;
Fin:;
		ResultSearchX+=MinEx;
		ResultSearchY+=MinEy;
		ResultDotSumInside	=MinNNGInsideCount +MinBNGInsideCount;
		ResultDotSumOutside	=MinNNGOutsideCount+MinBNGOutsideCount;

	}

	Res->SetAlignedXY(mx,my);

	if(NNGInsideCount>0x10000)
		NNGInsideCount=0xFFFF;
	if(NNGOutsideCount>0x10000)
		NNGOutsideCount=0xFFFF;
	if(BNGInsideCount>0x10000)
		BNGInsideCount=0xFFFF;
	if(BNGOutsideCount>0x10000)
		BNGOutsideCount=0xFFFF;

	Res->SetResult1((NNGInsideCount<<16) +BNGInsideCount);
	Res->SetResult2((NNGOutsideCount<<16)+BNGOutsideCount);

	Res->SetItemSearchedXY(ResultSearchX,ResultSearchY);
	if(IsTotalOk(OkNInside ,OkNOutside
				,OkBInside ,OkBOutside)==true
	|| NowList.GetFirst()==NULL){
		Res->SetError(1);
	}
	else{
		if(RThr->EffectiveNInside==true && NNGInsideCount!=0){
			Res->MovePosList(NowList);
		}
		else if(RThr->EffectiveNOutside==true && NNGOutsideCount!=0){
			Res->MovePosList(NowList);
		}
		else if(RThr->EffectiveBInside==true && BNGInsideCount!=0){
			Res->MovePosList(NowList);
		}
		else if(RThr->EffectiveBOutside==true && BNGOutsideCount!=0){
			Res->MovePosList(NowList);
		}

		if(RThr->EffectiveNInside==true && NNGInsideCount!=0){
			Res->SetError(Res->GetError() | 0x10);
		}
		if(RThr->EffectiveNOutside==true && NNGOutsideCount!=0){
			Res->SetError(Res->GetError() | 0x20);
		}
		if(RThr->EffectiveBInside==true && BNGInsideCount!=0){
			Res->SetError(Res->GetError() | 0x40);
		}
		if(RThr->EffectiveBOutside==true && BNGOutsideCount!=0){
			Res->SetError(Res->GetError() | 0x80);
		}

		if(NNGInsideCount==0 && NNGOutsideCount==0 && BNGInsideCount==0 && BNGOutsideCount==0){
			Res->SetError(1);
		}
	}
}

bool	OutlineItem::InFunc(int kx ,int ky ,int mx ,int my
							,bool	&OkNInside
							,bool	&OkBInside
							,bool	&OkNOutside
							,bool	&OkBOutside
							,int	&MinD
							,int	&MinEx
							,int	&MinEy
							,int	&MinED
							,int	&MinNNGInsideCount
							,int	&MinBNGInsideCount
							,int	&MinNNGOutsideCount
							,int	&MinBNGOutsideCount
							,ImageBuffer *MasterImage
							,ImageBuffer *TargetImage
							,ResultPosListContainer	&NGList)
{
	NGList.RemoveAll();
	const OutlineThreshold	*RThr=GetThresholdR();
	int	iResultDotSumInside=0;
	int	iResultDotSumOutside=0;
	int	iNNGInsideCount=InsideAlgo.CalcDecision(MasterImage,TargetImage
								 ,mx ,my ,ResultSearchX+kx,ResultSearchY+ky
								 ,RThr->InsideNOKColor
								 ,RThr->InsideNTrOKColor
								 ,RThr->InsideNOKDot
								 ,iResultDotSumInside ,0x0100
								 ,NGList,RThr->EffectiveNInside
								 ,OkNInside
								 ,MaxNGDotInsideN
								 ,RThr->AdjustLimitLInside,RThr->AdjustLimitHInside);

	int	iNNGOutsideCount=OutsideAlgo.CalcDecision(MasterImage,TargetImage
								 ,mx ,my ,ResultSearchX+kx,ResultSearchY+ky
								 ,RThr->OutsideNOKColor
								 ,RThr->OutsideNTrOKColor
								 ,RThr->OutsideNOKDot
								 ,iResultDotSumOutside ,0x0200
								 ,NGList,RThr->EffectiveNOutside
								 ,OkNOutside
								 ,MaxNGDotOutsideN
								 ,RThr->AdjustLimitLOutside,RThr->AdjustLimitHOutside);

	int	iBNGInsideCount=InsideAlgo.CalcDecision(MasterImage,TargetImage
								 ,mx ,my ,ResultSearchX+kx,ResultSearchY+ky
								 ,RThr->InsideBOKColor
								 ,RThr->InsideBTrOKColor
								 ,RThr->InsideBOKDot
								 ,iResultDotSumInside ,0x1100
								 ,NGList,RThr->EffectiveBInside
								 ,OkBInside
								 ,MaxNGDotInsideB
								 ,RThr->AdjustLimitLInside,RThr->AdjustLimitHInside);

	int	iBNGOutsideCount=OutsideAlgo.CalcDecision(MasterImage,TargetImage
								 ,mx ,my ,ResultSearchX+kx,ResultSearchY+ky
								 ,RThr->OutsideBOKColor
								 ,RThr->OutsideBTrOKColor
								 ,RThr->OutsideBOKDot
								 ,iResultDotSumOutside ,0x1200
								 ,NGList,RThr->EffectiveBOutside
								 ,OkBOutside
								 ,MaxNGDotOutsideB
								 ,RThr->AdjustLimitLOutside,RThr->AdjustLimitHOutside);

	if(IsCompleteOk(OkNInside ,OkNOutside
				,OkBInside ,OkBOutside)==true){
		MinNNGInsideCount	=iNNGInsideCount;
		MinNNGOutsideCount	=iNNGOutsideCount;
		MinBNGInsideCount	=iBNGInsideCount;
		MinBNGOutsideCount	=iBNGOutsideCount;
		MinEx=kx;
		MinEy=ky;
		return true;
	}
	/*
	if(IsUpdated(iNNGInsideCount ,iNNGOutsideCount,iBNGInsideCount ,iBNGOutsideCount)==true){
		if(iNNGInsideCount+iNNGOutsideCount+iBNGInsideCount+iBNGOutsideCount<MinD){
			MinD=iNNGInsideCount+iNNGOutsideCount+iBNGInsideCount+iBNGOutsideCount;
			NowList.Move(MinList);
			if(RThr->EffectiveNInside==true){
				NNGInsideCount	=iNNGInsideCount;
			}
			else{
				NNGInsideCount	=0;
			}
			if(RThr->EffectiveNOutside==true){
				NNGOutsideCount	=iNNGOutsideCount;
			}
			else{
				NNGOutsideCount	=0;
			}
			if(RThr->EffectiveBInside==true){
				BNGInsideCount	=iBNGInsideCount;
			}
			else{
				BNGInsideCount	=0;
			}
			if(RThr->EffectiveBOutside==true){
				BNGOutsideCount	=iBNGOutsideCount;
			}
			else{
				BNGOutsideCount	=0;
			}
		}
	}
	*/
	int	D=iNNGInsideCount+iNNGOutsideCount+iBNGInsideCount+iBNGOutsideCount;
	if(D<MinED){
		MinED=D;
		MinEx=kx;
		MinEy=ky;
		MinNNGInsideCount	=iNNGInsideCount;
		MinBNGInsideCount	=iBNGInsideCount;
		MinNNGOutsideCount	=iNNGOutsideCount;
		MinBNGOutsideCount	=iBNGOutsideCount;
	}
	else if(D==MinED){
		if(hypot(MinEx,MinEy)>hypot(kx,ky)){
			MinEx=kx;
			MinEy=ky;
			MinNNGInsideCount	=iNNGInsideCount;
			MinBNGInsideCount	=iBNGInsideCount;
			MinNNGOutsideCount	=iNNGOutsideCount;
			MinBNGOutsideCount	=iBNGOutsideCount;
		}
	}
	return false;
}
bool	OutlineItem::IsUpdated(int iNNGInsideCount ,int iNNGOutsideCount
							  ,int iBNGInsideCount ,int iBNGOutsideCount)
{
	const OutlineThreshold	*RThr=GetThresholdR();
	
	if(RThr->EffectiveNInside==false && iNNGInsideCount!=0){
		return false;
	}
	if(RThr->EffectiveNOutside==false && iNNGOutsideCount!=0){
		return false;
	}
	if(RThr->EffectiveBInside==false && iBNGInsideCount!=0){
		return false;
	}
	if(RThr->EffectiveBOutside==false && iBNGOutsideCount!=0){
		return false;
	}
	return true;
}

bool	OutlineItem::IsTotalOk(bool iOkNInside ,bool iOkNOutside
							  ,bool iOkBInside ,bool iOkBOutside)
{
	const OutlineThreshold	*RThr=GetThresholdR();

	if(RThr->EffectiveNInside==true && iOkNInside==false){
		return false;
	}
	if(RThr->EffectiveNOutside==true && iOkNOutside==false){
		return false;
	}
	if(RThr->EffectiveBInside==true && iOkBInside==false){
		return false;
	}
	if(RThr->EffectiveBOutside==true && iOkBOutside==false){
		return false;
	}
	return true;
}

bool	OutlineItem::IsCompleteOk(bool iOkNInside ,bool iOkNOutside
							  ,bool iOkBInside ,bool iOkBOutside)
{
	if(iOkNInside==false){
		return false;
	}
	if(iOkNOutside==false){
		return false;
	}
	if(iOkBInside==false){
		return false;
	}
	if(iOkBOutside==false){
		return false;
	}
	return true;
}


bool	OutlineItem::CalcSelf(void)
{
	InsideAlgo	.MoveTo(-MoveXForSelf,-MoveYForSelf);
	OutsideAlgo	.MoveTo(-MoveXForSelf,-MoveYForSelf);
	MatchingArea.MoveToNoClip(-MoveXForSelf,-MoveYForSelf);
	GetArea()	.MoveToNoClip(-MoveXForSelf,-MoveYForSelf);

	MoveXForSelf=0;
	MoveYForSelf=0;
	const OutlineThreshold	*RThr=GetThresholdR();

	if(RThr->MatchSlideOnMaster==false){
		return true;
	}
	ImageBuffer *Image=&GetMasterBuff();

	ResultDotSumInside=0;
	ResultDotSumOutside=0;
	ResultPosListContainer	NowList;
	bool	OkNInside;
	bool	OkBInside;
	bool	OkNOutside;
	bool	OkBOutside;
	int		iResultDotSumInside=0;
	int		iResultDotSumOutside=0;

	int	MinEx=0,MinEy=0;
	int	MinED=99999999;
	int	SelfSearch=3;

	for(int ky=-SelfSearch;ky<=SelfSearch;ky++){
		for(int kx=-SelfSearch;kx<=SelfSearch;kx++){
			ResultPosListContainer	MinList;

			int	iNNGInsideCount=InsideAlgo.CalcDecision(Image,Image
							 ,0,0 ,kx,ky
							 ,RThr->InsideNOKColor
							 ,RThr->InsideNTrOKColor
							 ,RThr->InsideNOKDot
							 ,iResultDotSumInside ,0x0100
							 ,MinList,false
							 ,OkNInside
							 ,MaxNGDotInsideN
							 ,0,0);
			int	iNNGOutsideCount=OutsideAlgo.CalcDecision(Image,Image
							 ,0,0 ,kx,ky
							 ,RThr->OutsideNOKColor
							 ,RThr->OutsideNTrOKColor
							 ,RThr->OutsideNOKDot
							 ,iResultDotSumOutside ,0x0200
							 ,MinList,false
							 ,OkNOutside
							 ,MaxNGDotOutsideN
							 ,0,0);
			int	iBNGInsideCount=InsideAlgo.CalcDecision(Image,Image
							 ,0,0 ,kx,ky
							 ,RThr->InsideBOKColor
							 ,RThr->InsideBTrOKColor
							 ,RThr->InsideBOKDot
							 ,iResultDotSumInside ,0x1100
							 ,MinList,false
							 ,OkBInside
							 ,MaxNGDotInsideB
							 ,0,0);
			int	iBNGOutsideCount=OutsideAlgo.CalcDecision(Image,Image
							 ,0,0 ,kx,ky
							 ,RThr->OutsideBOKColor
							 ,RThr->OutsideBTrOKColor
							 ,RThr->OutsideBOKDot
							 ,iResultDotSumOutside ,0x1200
							 ,MinList,false
							 ,OkBOutside
							 ,MaxNGDotOutsideB
							 ,0,0);
			int	D=iNNGInsideCount+iNNGOutsideCount+iBNGInsideCount+iBNGOutsideCount;
			if(D<MinED
			|| (D==MinED && hypot(kx,ky)<hypot(MinEx,MinEy))){
				MinED=D;
				MinEx=kx;
				MinEy=ky;
			}
		}
	}
	if(MinEx==0 && MinEy==0){
		return true;
	}
	InsideAlgo	.MoveTo(MinEx,MinEy);
	OutsideAlgo	.MoveTo(MinEx,MinEy);
	MatchingArea.MoveToNoClip(MinEx,MinEy);
	GetArea()	.MoveToNoClip(MinEx,MinEy);
	MoveXForSelf=MinEx;
	MoveYForSelf=MinEy;

	return false;
}

void	OutlineItem::AlgoCalcStruct::CutArea(FlexArea &localArea)
{
	FlexArea	A=Area;
	A.Sub(Area, localArea);
	Area=A;

	FlexArea	B=TrArea;
	B.Sub(TrArea, localArea);
	TrArea=B;
}

int	OutlineItem::AlgoCalcStruct::CalcDecision(ImageBuffer *MasterImageList
											, ImageBuffer *TargetImageList
								,int mx ,int my ,int hx ,int hy
								,const RelativeThresholdColorBox &OKColor 
								,const RelativeThresholdColorBox &TrOKColor 
								,int OKDotCount
								,int &Sum ,WORD Mode
								,ResultPosListContainer &PosList ,bool EnabledResult
								,bool &Ok
								,int &MaxNGDot
								,int AdjustLimitL ,int AdjustLimitH)
{
	int	MinX=min(Area.GetMinX(),TrArea.GetMinX());
	int	MinY=min(Area.GetMinY(),TrArea.GetMinY());
	int	NGDotCount=0;
	ExecuteStartByInspection();
	const OutlineThreshold	*RThr=Parent->GetThresholdR(GetLayersBase());

	if(MasterImageList->IsNull()==false && TargetImageList->IsNull()==false){
		if(RThr->DiffMode==false){
			int	dL,dH;
			if(RThr->AbsMode==false){
				double	Col=Area.GetAverage(*TargetImageList,mx+hx ,my+hy);
				int	d=Col-CenterColorOnMaster;
				if(d>=0 && d>=AdjustLimitH){
					Col=CenterColorOnMaster+AdjustLimitH;
				}
				else if(d<0 && (-d)>AdjustLimitL){
					Col=CenterColorOnMaster-AdjustLimitL;
				}
				if(Col<0)
					Col=0;
				if(Col>255)
					Col=255;
				OKColor.GetMonoRange((int)Col,dL,dH);
				if(RThr->AdjustMode==true){
					if(CenterColorOnMaster!=0){
						/*
						double	Mul=Col/((double)CenterColorOnMaster);
						dL=(int)(dL*Mul);
						dH=(int)(dH*Mul);
						*/
						int	dD=Col-CenterColorOnMaster;
						dL+=dD;
						dH+=dD;
					}
				}
			}
			else{
				OKColor.GetRelMonoRange(dL,dH);
			}

			int	LCount=Area.GetFLineLen();
			for(int i=0;i<LCount;i++){
				int	Y	=Area.GetFLineAbsY(i);
				int	x1	=Area.GetFLineLeftX(i);
				int	Numb=Area.GetFLineNumb(i);
				BYTE	*R=TargetImageList->GetY(Y+my+hy)+x1+mx+hx;
				BYTE	*Dest=BMap[Y-MinY];
				int		x;
				int	k=x1-MinX;
				for(int x=0;x<Numb;x++){
					if(*R<dL || dH<*R){
						Dest[k>>3] |= 0x80>>(k&7);
						NGDotCount++;
					}
					k++;
					R++;
				}
			}

			if(RThr->AbsMode==false){
				double	Col=TrArea.GetAverage(*TargetImageList,mx+hx ,my+hy);
				int	d=Col-TrCenterColorOnMaster;
				if(d>=0 && d>=AdjustLimitH){
					Col=TrCenterColorOnMaster+AdjustLimitH;
				}
				else if(d<0 && (-d)>AdjustLimitL){
					Col=TrCenterColorOnMaster-AdjustLimitL;
				}
				if(Col<0)
					Col=0;
				if(Col>255)
					Col=255;
				TrOKColor.GetMonoRange((int)Col,dL,dH);
				if(RThr->AdjustMode==true){
					if(CenterColorOnMaster!=0){
						/*
						double	Mul=Col/((double)CenterColorOnMaster);
						dL=(int)(dL*Mul);
						dH=(int)(dH*Mul);
						*/
						int	dD=Col-TrCenterColorOnMaster;
						dL+=dD;
						dH+=dD;
					}
				}
			}
			else{
				TrOKColor.GetRelMonoRange(dL,dH);
			}

			LCount=TrArea.GetFLineLen();
			for(int i=0;i<LCount;i++){
				int	Y	=TrArea.GetFLineAbsY(i);
				int	x1	=TrArea.GetFLineLeftX(i);
				int	Numb=TrArea.GetFLineNumb(i);
				BYTE	*R=TargetImageList->GetY(Y+my+hy)+x1+mx+hx;
				BYTE	*Dest=BMap[Y-MinY];
				int		x;
				int	k=x1-MinX;
				for(int x=0;x<Numb;x++){
					if(*R<dL || dH<*R){
						Dest[k>>3] |= 0x80>>(k&7);
						NGDotCount++;
					}
					k++;
					R++;
				}
			}
		}
		else{
			int	dL,dH;
			OKColor.GetRelMonoRange(dL,dH);

			int	LCount=Area.GetFLineLen();
			for(int i=0;i<LCount;i++){
				int	Y	=Area.GetFLineAbsY(i);
				int	x1	=Area.GetFLineLeftX(i);
				int	Numb=Area.GetFLineNumb(i);
				BYTE	*R=TargetImageList->GetY(Y+my+hy)+x1+mx+hx;
				BYTE	*M=MasterImageList->GetY(Y)+x1;
				BYTE	*Dest=BMap[Y-MinY];
				int		x;
				int	k=x1-MinX;
				for(int x=0;x<Numb;x++){
					int	h=*R-*M;
					if((h<0 && dL<-h) || (h>=0 && dH<h)){
						Dest[k>>3] |= 0x80>>(k&7);
						NGDotCount++;
					}
					k++;
					R++;
					M++;
				}
			}

			TrOKColor.GetRelMonoRange(dL,dH);
			LCount=TrArea.GetFLineLen();
			for(int i=0;i<LCount;i++){
				int	Y	=TrArea.GetFLineAbsY(i);
				int	x1	=TrArea.GetFLineLeftX(i);
				int	Numb=TrArea.GetFLineNumb(i);
				BYTE	*R=TargetImageList->GetY(Y+my+hy)+x1+mx+hx;
				BYTE	*M=MasterImageList->GetY(Y)+x1;
				BYTE	*Dest=BMap[Y-MinY];
				int		x;
				int	k=x1-MinX;
				for(int x=0;x<Numb;x++){
					int	h=*R-*M;
					if((h<0 && dL<-h) || (h>=0 && dH<h)){
						Dest[k>>3] |= 0x80>>(k&7);
						NGDotCount++;
					}
					k++;
					R++;
					M++;
				}
			}
		}
		//}
		Ok=true;
		int	NGPointCount=0;
		MaxNGDot=0;
		if(NGDotCount>OKDotCount){
			PureFlexAreaListContainer FPack;
			PickupFlexArea(BMap ,XByte ,XByte*8,YLen ,FPack);
			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
				int64	iSum	=p->GetPatternByte();
				if(iSum>MaxNGDot){
					MaxNGDot=iSum;
				}
				if(iSum>OKDotCount){
					//?m?f?I?e??
					PureFlexAreaList *NextP=p->GetNext();
					FPack.RemoveList(p);
					Sum+=iSum;
					if(EnabledResult==true){
						p->MoveToNoClip(MinX,MinY);
		
						int	Cx,Cy;
						p->GetCenter(Cx,Cy);
						ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
						r->result =0x10000+Mode;
						r->result1=iSum;
						r->result2=0;
						LibNGTypeInAlgorithm	*LNGType=GetParent()->GetLibNGTypeInAlgorithm();
						if(LNGType!=NULL){
							OutlineInspectLibNGTypeItem	*BL=GetParent()->MakeNGType(*p,*LNGType);
							if(BL!=NULL){
								r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
							}
						}
						r->NGShape.SuckFrom(*p);
						PosList.AppendList(r);
					}
					NGPointCount++;
					delete	p;
					p=NextP;
					Ok=false;
				}
				else{
					p=p->GetNext();
				}
			}
		}
		return NGPointCount;
	}
	return 0;
}
