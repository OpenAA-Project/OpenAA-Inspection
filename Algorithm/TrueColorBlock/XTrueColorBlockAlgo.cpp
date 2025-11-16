/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlockAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "XTrueColorBlock.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XTrueColorBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"

const	int	MaxResultNGPointInBlock=1000;
const	int	MaxReEntrantCount=30000;


bool    TrueColorBlockItem::ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,ColorLogic &Brightness
						  ,int Mergin
						  ,int OKDot,int OKLength
						  ,WORD	MinNGCount
						  ,ThresholdMode NBMode)
{
	const TrueColorBlockThreshold	*RThr=GetThresholdR();
	if(RThr->PointMove.ModeEnabled==false){
		return true;
	}
	FlexArea    SubFLines;
    FlexArea    SubFLineEdge;
    FlexArea    SubFLineInside;
    if(SubBlock.GetFirst()!=NULL){
        SubFLines       =GetArea();
        SubFLineEdge    =FLineEdge;
        SubFLineInside  =FLineInside;
        }

    int MinK;
    int	Min=0x7FFFFFFF;
    int dx=0;
    int dy=0;
	int Sum=0;

	if(SubBlock.GetFirst()!=NULL){
		L3Remove(mx ,my
                        ,SubFLines
                        ,SubFLineEdge
                        ,SubFLineInside);
		}
	int InsideSum=0;
	Level3Inside(mx ,my
				,Brightness ,Mergin,InsideSum);

	ColorLogic TmpBrightness;
	if(RThr->PointMove.ModeAdjustable==true
	&& GetArea().GetWidth()>=10 && GetArea().GetHeight()>=10){
		TmpBrightness=Brightness;
		EnAverage(mx ,my
				,TmpBrightness);
	}
	else{
		TmpBrightness=Brightness;
	}

	if(InsideSum<OKDot){
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			if(SubBlock.GetFirst()!=NULL){
				L3Remove(mx+W->x ,my+W->y
				                    ,SubFLines
					                ,SubFLineEdge
						            ,SubFLineInside);
			}
			if(RThr->PointMove.ModeAdjustable==true
			&& (GetArea().GetWidth()<10 || GetArea().GetHeight()<10)){
				TmpBrightness=Brightness;
				EnAverage(mx+W->x ,my+W->y
							,TmpBrightness);
			}

			Sum=InsideSum;
			Level3Speedy(mx+W->x ,my+W->y
						,TmpBrightness ,Mergin,Sum);
			if(Sum<OKDot){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(W->x,W->y);
				Res->SetResult1(Sum);
				Res->SetResult2(0);
				Res->SetError(1);	//OK
				SetSWayListToTop(ThreadNo,GetThresholdW()->SelfSearch,W);
				if(SubBlock.GetFirst()!=NULL){
					SetArea(SubFLines);
					FLineEdge   =SubFLineEdge;
					FLineInside =SubFLineInside;
				}
				return true;
			}
			if(Sum<Min){
				dx=W->x;
				dy=W->y;
				Min=Sum;
			}
		}
	}

	int RNumb;
	int Rx[MaxResultNGPointInBlock];
	int Ry[MaxResultNGPointInBlock];

	if(RThr->PointMove.ModeNGCluster==true){
		int MinSum=99999999;
		int	MinDx=0;
		int	MinDy=0;
		ResultPosListContainer	NowList;
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			if(SubBlock.GetFirst()!=NULL){
				L3Remove(mx+W->x ,my+W->y
				        ,SubFLines
					    ,SubFLineEdge
						,SubFLineInside);
			}
			NowList.RemoveAll();
			if(CheckOnNG(mx,my,W->x,W->y
						,Brightness,Mergin
						,OKDot,OKLength
						,Sum
						,NowList
						,MinNGCount
						,NBMode)==true){

				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(W->x,W->y);
				Res->SetResult1(Sum);
				Res->SetResult2(0);
				Res->SetError(1);	//OK
				if(SubBlock.GetFirst()!=NULL){
					SetArea(SubFLines);
					FLineEdge   =SubFLineEdge;
					FLineInside =SubFLineInside;
				}
				return true;
			}
			if(MinSum>Sum){
				MinSum=Sum;
				MinDx=W->x;
				MinDy=W->y;
				Res->MovePosList(NowList);
			}
		}
		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(MinDx,MinDy);
		Res->SetResult1(Sum);
		Res->SetResult2(0);
		Res->SetError(2);	//NG
		return true;
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new ResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1(Sum);
	r->SetResult2(0);
	r->result =0x30;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(Sum);
	Res->SetResult2(0);
	Res->SetError(2);	//NG

	if(SubBlock.GetFirst()!=NULL){
		SetArea(SubFLines);
		FLineEdge   =SubFLineEdge;
		FLineInside =SubFLineInside;
	}
    return false;

}

bool    TrueColorBlockItem::ExecuteProcessingInnerWithoutSubtract(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,ColorLogic &Brightness
						  ,int Mergin
						  ,int OKDot,int OKLength
						  ,WORD	MinNGCount
						  ,ThresholdMode NBMode)
{
    int MinK;
    int	Min=0x7FFFFFFF;
    int dx=0;
    int dy=0;
	int Sum=0;
	const TrueColorBlockThreshold	*RThr=GetThresholdR();
	if(RThr->PointMove.ModeEnabled==false){
		return true;
	}

	ColorLogic TmpBrightness;
	if(RThr->PointMove.ModeAdjustable==true
	&& GetArea().GetWidth()>=10 && GetArea().GetHeight()>=10){
		TmpBrightness=Brightness;
		EnAverage(mx ,my
				,TmpBrightness);
	}
	else{
		TmpBrightness=Brightness;
	}

	int InsideSum=0;
	Level3Inside(mx ,my
					,TmpBrightness
					,Mergin
					,InsideSum);

	if(InsideSum<OKDot){
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			ColorLogic iTmpBrightness;
			if(RThr->PointMove.ModeAdjustable==true
			&& (GetArea().GetWidth()<10 || GetArea().GetHeight()<10)){
				ColorLogic iTmpBrightness=Brightness;
				EnAverage(mx+W->x ,my+W->y
							,iTmpBrightness);
			}
			else{
				iTmpBrightness=TmpBrightness;
			}

			Sum=InsideSum;
			Level3Speedy(mx+W->x ,my+W->y
						,iTmpBrightness
						,Mergin
						,Sum);
			if(Sum<OKDot){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(W->x,W->y);
				Res->SetResult1(Sum);
				Res->SetResult2(0);
				Res->SetError(1);	//OK
				SetSWayListToTop(ThreadNo,GetThresholdW()->SelfSearch,W);
				return true;
			}
			if(Sum<Min){
				dx=W->x;
				dy=W->y;
				Min=Sum;
			}
		}
	}

	int RNumb;
	int Rx[MaxResultNGPointInBlock];
	int Ry[MaxResultNGPointInBlock];

	if(RThr->PointMove.ModeNGCluster==true){
		int MinSum=99999999;
		int	MinDx=0;
		int	MinDy=0;
		/*
		ResultPosListContainer	NowList;
		for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
			NowList.RemoveAll();
			if(CheckOnNG(mx,my,W->x,W->y
						,BrightWidthL ,BrightWidthH
						,OKDotL ,OKDotH
						,SumL,SumH
						,NowList)==true){
				Res->Mx=mx;
				Res->Hx=W->x;
				Res->My=my;
				Res->Hy=W->y;
				Res->result1=SumL;
				Res->result2=SumH;
				Res->Error=1;	//OK
				return true;
			}
			if((MinSumL+MinSumH)>(SumL+SumH)){
				MinSumL=SumL;
				MinSumH=SumH;
				MinDx=W->x;
				MinDy=W->y;
				Res->PosList=NowList;
			}
		}
		Res->Mx=mx;
		Res->Hx=MinDx;
		Res->My=my;
		Res->Hy=MinDy;
		Res->result1=SumL;
		Res->result2=SumH;
		Res->Error=2;	//NG
		return false;
		*/
		ResultPosListContainer	NowList;
		if(CheckOnNG(mx,my,dx,dy
						,TmpBrightness
						,Mergin
						,OKDot,OKLength
						,Sum
						,NowList
						,MinNGCount
						,NBMode)==true){
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(dx,dy);
			Res->SetResult1(Sum);
			Res->SetResult2(0);
			Res->SetError(1);	//OK
			return true;
		}
		Res->MovePosList(NowList);		

		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(dx,dy);
		Res->SetResult1(Sum);
		Res->SetResult2(0);
		Res->SetError(2);	//NG
		return false;
	}
	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new ResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1(Sum);
	r->SetResult2(0);
	r->result =0x30;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(Sum);
	Res->SetResult2(0);
	Res->SetError(2);	//NG

    return false;

}

bool    TrueColorBlockItem::L3Remove(int mx ,int my
                           ,FlexArea &SubFLines
                           ,FlexArea &SubFLineEdge
                           ,FlexArea &SubFLineInside)
{
    SetArea(SubFLines);
    FLineEdge   =SubFLineEdge;
    FLineInside =SubFLineInside;
	const TrueColorBlockThreshold	*RThr=GetThresholdR();

    for(SubtractItem *sb=SubBlock.GetFirst();sb!=NULL;sb=sb->GetNext()){
		/*
        GetArea().Sub(sb->IndexAfterEdit->GetFLineSubtract()
					, sb->IndexAfterEdit->GetCurrentResult()->GetItemSearchedX()-mx
					, sb->IndexAfterEdit->GetCurrentResult()->GetItemSearchedY()-my);
        FLineInside.Sub(sb->IndexAfterEdit->GetFLineSubtract()
					, sb->IndexAfterEdit->GetCurrentResult()->GetItemSearchedX()-mx
					, sb->IndexAfterEdit->GetCurrentResult()->GetItemSearchedY()-my);
        FLineEdge.Sub(sb->IndexAfterEdit->GetFLineSubtract()
					, sb->IndexAfterEdit->GetCurrentResult()->GetItemSearchedX()-mx
					, sb->IndexAfterEdit->GetCurrentResult()->GetItemSearchedY()-my);
		*/
        }
	if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
	    CenterBright=CalcCenterBright(GetMasterBuff(),0 ,0);
	return true;
}

void	TrueColorBlockItem::Level3Inside(int mx ,int my
					,ColorLogic &Brightness
					,int Mergin
					,int &InsideSum)
{
	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer	*[GetLayerNumb()];
	else
		ImagePoint=ImageList;

	GetTargetBuffList(ImagePoint);

	if(Ln>=3){
		for(int i=0;i<FLineInside.GetFLineLen();i++){
			int	y =FLineInside.GetFLineAbsY  (i)+my;
			int	x1=FLineInside.GetFLineLeftX (i)+mx;
			int	x2=FLineInside.GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			BYTE	*srcG=ImagePoint[1]->GetY(y);
			BYTE	*srcB=ImagePoint[2]->GetY(y);
			int	XN8=(x2-x1)>>3;
			int	x=x1;
			for(int j=0;j<XN8;j++){
				BYTE	M=~Brightness.Calc8(&srcR[x],&srcG[x],&srcB[x],Mergin);
				for(BYTE mask=1;mask!=0;mask<<=1){
					if((M & mask)!=0){
						InsideSum++;
					}
				}
				x+=8;
			}
			for(;x<x2;x++){
				if(Brightness.Calc(srcR[x],srcG[x],srcB[x],Mergin)==false){
					InsideSum++;
				}
			}
			/*
			for(int x=x1;x<x2;x++){
				if(Brightness.Calc(srcR[x],srcG[x],srcB[x],Mergin)==false){
					InsideSum++;
				}
			}
			*/
		}
	}
	else if(Ln==2){
		for(int i=0;i<FLineInside.GetFLineLen();i++){
			int	y =FLineInside.GetFLineAbsY  (i)+my;
			int	x1=FLineInside.GetFLineLeftX (i)+mx;
			int	x2=FLineInside.GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			BYTE	*srcG=ImagePoint[1]->GetY(y);
			for(int x=x1;x<x2;x++){
				if(Brightness.Calc(srcR[x],srcG[x],srcG[x],Mergin)==false){
					InsideSum++;
				}
			}
		}
	}
	else if(Ln==1){
		for(int i=0;i<FLineInside.GetFLineLen();i++){
			int	y =FLineInside.GetFLineAbsY  (i)+my;
			int	x1=FLineInside.GetFLineLeftX (i)+mx;
			int	x2=FLineInside.GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			for(int x=x1;x<x2;x++){
				if(Brightness.Calc(srcR[x],srcR[x],srcR[x],Mergin)==false){
					InsideSum++;
				}
			}
		}
	}

	if(ImagePoint!=ImageList)
		delete	[]ImagePoint;
}

double	TrueColorBlockItem::EnAverage(int mx,int my
						,ColorLogic &TmpBrightness)
{
	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0])){
		ImagePoint=new ImageBuffer	*[GetLayerNumb()];
	}
	else{
		ImagePoint=ImageList;
	}
	GetTargetBuffList(ImagePoint);

	QRgb	D=CalcCenterBright(ImagePoint,mx,my);
	if(ImagePoint!=ImageList){
		delete	[]ImagePoint;
	}

	double	Vc	=GetRGBBrightness(CenterBright);
	double	Vd	=GetRGBBrightness(D);
	const TrueColorBlockThreshold	*RThr=GetThresholdR();
	double	kDifCol=Vd-Vc;
	if(kDifCol>RThr->AdjustWhite)
		kDifCol=RThr->AdjustWhite;
	if(-kDifCol>RThr->AdjustBlack)
		kDifCol=-((int)RThr->AdjustBlack);

	double	Vk=Vc+kDifCol;
	if(Vc>0.0){
		double	m=Vk/Vc;
		TmpBrightness.Multiply(m);
		return m;
	}
	return 1.0;
}


void	TrueColorBlockItem::Level3Speedy(int mx,int my
					,ColorLogic &TmpBrightness
					,int Mergin
					,int &Sum)
{
	FlexArea	*A=&FLineEdge;

	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer	*[GetLayerNumb()];
	else
		ImagePoint=ImageList;
	GetTargetBuffList(ImagePoint);

	if(Ln>=3){
		for(int i=0;i<A->GetFLineLen();i++){
			int	y =A->GetFLineAbsY  (i)+my;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			BYTE	*srcG=ImagePoint[1]->GetY(y);
			BYTE	*srcB=ImagePoint[2]->GetY(y);
			/*
			int	XN8=(x2-x1)>>3;
			int	x=x1;
			for(int j=0;j<XN8;j++){
				BYTE	M=~TmpBrightness.Calc8(&srcR[x],&srcG[x],&srcB[x],Mergin);
				for(BYTE mask=1;mask!=0;mask<<=1){
					if((M & mask)!=0){
						Sum++;
					}
				}
				x+=8;
			}
			for(;x<x2;x++){
				if(TmpBrightness.Calc(srcR[x],srcG[x],srcB[x],Mergin)==false){
					Sum++;
				}
			}
			*/
			
			for(int x=x1;x<x2;x++){
				if(TmpBrightness.Calc(srcR[x],srcG[x],srcB[x],Mergin)==false){
					Sum++;
				}
			}
			
		}
	}
	else if(Ln==2){
		for(int i=0;i<A->GetFLineLen();i++){
			int	y =A->GetFLineAbsY  (i)+my;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			BYTE	*srcG=ImagePoint[1]->GetY(y);
			for(int x=x1;x<x2;x++){
				if(TmpBrightness.Calc(srcR[x],srcG[x],srcG[x],Mergin)==false){
					Sum++;
				}
			}
		}
	}
	else if(Ln==1){
		for(int i=0;i<A->GetFLineLen();i++){
			int	y =A->GetFLineAbsY  (i)+my;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			for(int x=x1;x<x2;x++){
				if(TmpBrightness.Calc(srcR[x],srcR[x],srcR[x],Mergin)==false){
					Sum++;
				}
			}
		}
	}
	if(ImagePoint!=ImageList)
		delete	[]ImagePoint;
}
struct AnalyzeNGHoleClass
{
    BYTE			*NGBmp;
    int             NGBmpX;
    int             NGBmpY;
    ColorLogic		*Level;
    int             NGNumb;
    ImageBuffer     **TopBuffList;
	ImageBuffer     **MasterBuffList;
	ImageBuffer     **LoadedBuffList;
	int				LayerNumb;
    int             dx;
    int             dy;
    int             AddX;
    int             AddY;
    int             AddOffset;
	int				DotPerLine;
	int				MaxLines;
    FlexArea        *FLines;
};
static	int AnalyzeNGHoleFunc(const void *a ,const void *b)
{
    if(((struct FlexLine *)a)->_GetAbsY()<((struct FlexLine *)b)->_GetAbsY())
        return(-1);
    if(((struct FlexLine *)a)->_GetAbsY()>((struct FlexLine *)b)->_GetAbsY())
        return(1);
    if(((struct FlexLine *)a)->_GetLeftX()<=((struct FlexLine *)b)->_GetLeftX()
    && ((struct FlexLine *)a)->_GetRightX()>((struct FlexLine *)b)->_GetLeftX())
        return(0);
    if(((struct FlexLine *)b)->_GetLeftX()<=((struct FlexLine *)a)->_GetLeftX()
    && ((struct FlexLine *)b)->_GetRightX()>((struct FlexLine *)a)->_GetLeftX())
        return(0);

    if(((struct FlexLine *)a)->_GetLeftX()<((struct FlexLine *)b)->_GetLeftX())
        return(-1);
    return(1);
}

void  TrueColorBlockItem::SearchAnalyzeNGHole(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY())
        return;
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    if((y+LData->dy)<0 || (y+LData->dy)>=LData->MaxLines
    || (x+LData->dx)<0 || (x+LData->dx)>=LData->DotPerLine)
        return;

	LData->AddX+=x;
	LData->AddY+=y;
	LData->NGNumb++;
	SearchAnalyzeNGHole(LData,x-1 ,y-1 ,B-LData->NGBmpX );
	SearchAnalyzeNGHole(LData,x   ,y-1 ,B-LData->NGBmpX );
	SearchAnalyzeNGHole(LData,x+1 ,y-1 ,B-LData->NGBmpX );
	SearchAnalyzeNGHole(LData,x-1 ,y   ,B               );
	SearchAnalyzeNGHole(LData,x+1 ,y   ,B               );
	SearchAnalyzeNGHole(LData,x-1 ,y+1 ,B+LData->NGBmpX );
	SearchAnalyzeNGHole(LData,x   ,y+1 ,B+LData->NGBmpX );
	SearchAnalyzeNGHole(LData,x+1 ,y+1 ,B+LData->NGBmpX );
}

void  TrueColorBlockItem::SearchAnalyzeNGHoleL(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY())
        return;
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    if((y+LData->dy)<0 || (y+LData->dy)>=LData->MaxLines
    || (x+LData->dx)<0 || (x+LData->dx)>=LData->DotPerLine)
        return;

    //BYTE    C=LData->TopBuff->GetY(y+LData->dy)[x+LData->dx];
	//if(C<LData->LLevel){
		LData->AddX+=x;
		LData->AddY+=y;
		LData->NGNumb++;
		SearchAnalyzeNGHoleL(LData,x-1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHoleL(LData,x   ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHoleL(LData,x+1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHoleL(LData,x-1 ,y   ,B               );
		SearchAnalyzeNGHoleL(LData,x+1 ,y   ,B               );
		SearchAnalyzeNGHoleL(LData,x-1 ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHoleL(LData,x   ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHoleL(LData,x+1 ,y+1 ,B+LData->NGBmpX );
	//}
}
void  TrueColorBlockItem::SearchAnalyzeNGHoleH(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY())
        return;
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    if((y+LData->dy)<0 || (y+LData->dy)>=LData->MaxLines
    || (x+LData->dx)<0 || (x+LData->dx)>=LData->DotPerLine)
        return;

    //BYTE    C=LData->TopBuff->GetY(y+LData->dy)[x+LData->dx];
	//if(LData->HLevel<C){
		LData->AddX+=x;
		LData->AddY+=y;
		LData->NGNumb++;
		SearchAnalyzeNGHoleH(LData,x-1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHoleH(LData,x   ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHoleH(LData,x+1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHoleH(LData,x-1 ,y   ,B               );
		SearchAnalyzeNGHoleH(LData,x+1 ,y   ,B               );
		SearchAnalyzeNGHoleH(LData,x-1 ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHoleH(LData,x   ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHoleH(LData,x+1 ,y+1 ,B+LData->NGBmpX );
	//}
}
void  TrueColorBlockItem::SearchAnalyzeNGHole2L(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY())
        return;
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE    *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    //int d= LData->LoadedBuff->GetY(y+LData->dy)[x+LData->dx]
    //      -LData->MasterBuff->GetY(y)[x]
    //      -LData->AddOffset;
	//if(d<LData->LLevel){
		LData->AddX+=x;
		LData->AddY+=y;
		LData->NGNumb++;
		SearchAnalyzeNGHole2L(LData,x-1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2L(LData,x   ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2L(LData,x+1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2L(LData,x-1 ,y   ,B);
		SearchAnalyzeNGHole2L(LData,x+1 ,y   ,B);
		SearchAnalyzeNGHole2L(LData,x-1 ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole2L(LData,x   ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole2L(LData,x+1 ,y+1 ,B+LData->NGBmpX );
	//}
}
void  TrueColorBlockItem::SearchAnalyzeNGHole2(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY())
        return;
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE    *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    //int d= LData->LoadedBuff->GetY(y+LData->dy)[x+LData->dx]
    //      -LData->MasterBuff->GetY(y)[x]
    //      -LData->AddOffset;
	//if(d<LData->LLevel){
		LData->AddX+=x;
		LData->AddY+=y;
		LData->NGNumb++;
		SearchAnalyzeNGHole2(LData,x-1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2(LData,x   ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2(LData,x+1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2(LData,x-1 ,y   ,B);
		SearchAnalyzeNGHole2(LData,x+1 ,y   ,B);
		SearchAnalyzeNGHole2(LData,x-1 ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole2(LData,x   ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole2(LData,x+1 ,y+1 ,B+LData->NGBmpX );
	//}
}
void  TrueColorBlockItem::SearchAnalyzeNGHole2H(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY())
        return;
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE    *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    //int d= LData->LoadedBuff->GetY(y+LData->dy)[x+LData->dx]
    //      -LData->MasterBuff->GetY(y)[x]
    //      -LData->AddOffset;
	//if(LData->HLevel<d){
		LData->AddX+=x;
		LData->AddY+=y;
		LData->NGNumb++;
		SearchAnalyzeNGHole2H(LData,x-1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2H(LData,x   ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2H(LData,x+1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole2H(LData,x-1 ,y   ,B);
		SearchAnalyzeNGHole2H(LData,x+1 ,y   ,B);
		SearchAnalyzeNGHole2H(LData,x-1 ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole2H(LData,x   ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole2H(LData,x+1 ,y+1 ,B+LData->NGBmpX );
	//}
}

int  TrueColorBlockItem::AnalyzeNGHole(int dx ,int dy,int x ,int y
							, ColorLogic &Level
							, BYTE *NGBmp ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot ,int &Sum)
{
	Sum=0;
	struct AnalyzeNGHoleClass   LData;

	ImageBuffer	*ImageListTarget[100];
	ImageBuffer	**ImagePointTarget;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageListTarget)/sizeof(ImageListTarget[0]))
		ImagePointTarget=new ImageBuffer	*[GetLayerNumb()];
	else
		ImagePointTarget=ImageListTarget;
	GetTargetBuffList(ImagePointTarget);

    LData.NGNumb=0;
	LData.TopBuffList=ImagePointTarget;
	LData.LayerNumb=GetLayerNumb();
    LData.dx=dx;
    LData.dy=dy;
    LData.DotPerLine=GetDotPerLine();
    LData.MaxLines	=GetMaxLines() ;
	LData.Level=&Level;
	LData.NGBmp =NGBmp;
	LData.NGBmpX=NGBmpX;
	LData.NGBmpY=NGBmpY;
	LData.AddX=0;
	LData.AddY=0;
	LData.FLines=&GetArea();

	SearchAnalyzeNGHole(&LData,x,y ,&NGBmp[(y-GetArea().GetMinY())*NGBmpX]);
	if(LData.NGNumb>OKDot){
		Cx=LData.AddX/LData.NGNumb;
		Cy=LData.AddY/LData.NGNumb;
		Sum=LData.NGNumb;
	}
	if(ImagePointTarget!=ImageListTarget)
		delete	[]ImagePointTarget;

	return(LData.NGNumb);        
}


bool	TrueColorBlockItem::CheckOnNG(int mx,int my ,int hx ,int hy
				, ColorLogic &Brightness
				,int Mergin
				, int OKDot ,int OKLength
				,int &Sum
				,NPListPack<ResultPosList> &PosList
				,WORD MinNGCount
				,ThresholdMode NBMode)
{
	Sum=0;
    int	RNumb=0;
	const TrueColorBlockThreshold	*RThr=GetThresholdR();
	if(RThr->PointMove.ModeAdjustable==true){
		EnAverage(mx,my
				,Brightness);
	}
    uchar   BackBuff[50000];

	FlexArea	*fa=&GetArea();
    int starty =fa->GetFLineAbsY(0);

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

    BYTE   *pMap;
    if(LByte>sizeof(BackBuff))
        pMap=new BYTE[LByte];
    else
        pMap=BackBuff;

	memset(pMap,0,LByte);

	CheckOnNGInner1(mx+hx ,my+hy
                    ,Brightness
					,Mergin
                    ,pMap
                    ,Lx ,Ly ,LByte,starty);

	int iSum=0;
	int	NGCount=0;

	bool	DrawResultDetail=GetLayersBase()->GetParamGlobal()->DrawResultDetail;
	uchar   *BackPointer[10000];
	uchar   **BackDim;
	if(Ly<sizeof(BackPointer)/sizeof(BackPointer[0])){
		BackDim=BackPointer;
	}
	else{
		BackDim=new uchar *[Ly];
	}

    BYTE   *pL=pMap;
    for(int y=0;y<Ly;y++,pL+=Lx){
		BackDim[y]=pL;
	}
	PureFlexAreaListContainer LFPack;
	PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack);
	for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;){
		Sum	=p->GetPatternByte();
		int	NGLen	=max(p->GetWidth(),p->GetHeight());
		if(Sum>OKDot && NGLen>OKLength){
			//?m?f?I?e??
			PureFlexAreaList *NextP=p->GetNext();
			LFPack.RemoveList(p);
			int	Cx,Cy;
			iSum+=Sum;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->result =0x20000;	//NG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1(Sum);
			r->SetResult2(NGLen);
			LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
			if(LNGType!=NULL){
				TrueColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
				if(BL!=NULL){
					r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
				}
			}
			r->NGShape.SuckFrom(*p);
			PosList.AppendList(r);
			RNumb++;
			NGCount++;
			delete	p;
			p=NextP;
		}
		else if(DrawResultDetail==true){
			//?n?j???a?A?P?x?A???o??E???e??
			PureFlexAreaList *NextP=p->GetNext();
			LFPack.RemoveList(p);
			int	Cx,Cy;
			iSum+=Sum;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->SetResult1(Sum);
			r->SetResult2(NGLen);
			if(Sum>OKDot){
				r->result =0x30;	//?P?x?I?m?f?C??E?3?I?n?j
			}
			else if(NGLen>OKLength){
				r->result =0x20;	//?P?x?I?m?f?C?E?I?I?n?j
			}
			else{
				r->result =0x10;	//?P?x?I?m?f?A??E?3?E?I?A?a?n?j
			}
			r->result +=(NBMode==_ThresholdNarrow)?0:1;

			LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
			if(LNGType!=NULL){
				TrueColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
				if(BL!=NULL){
					r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
				}
			}
			r->NGShape.SuckFrom(*p);
			PosList.AppendList(r);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}


    if(pMap!=BackBuff)
        delete  []pMap;

	Sum=iSum;
	if(NGCount<MinNGCount)
		return true;

	if(RNumb!=0)
		return false;

	return true;
}

void	TrueColorBlockItem::CheckOnNGInner1(int dx ,int dy
                                    ,ColorLogic &Level
									,int Mergin
                                    ,BYTE *pMap
                                    ,int Lx ,int Ly ,int LByte,int starty)
{
	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer	*[GetLayerNumb()];
	else
		ImagePoint=ImageList;
	GetTargetBuffList(ImagePoint);

	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();

	for(int i=0;i<fa->GetFLineLen();i++){
		int Y =fa->GetFLineAbsY(i);
		if(Y+dy<0 || Y+dy>=YLen)
			continue;
		int X   =fa->GetFLineLeftX(i);
		int Numb=fa->GetFLineNumb(i);
		int x1=X;
		int x2=X+Numb;
		if(x2<0 || x1>=(XLen-1) || x1>x2)
			continue;
		if(x1<0)
			x1=0;
		if(x2>=XLen-1)
			x2=XLen-1;
		Numb=x2-x1;
		X=x1;
		if((dx+X)<0 || (dx+X)>=XLen)
			continue;
		if(Numb<=0)
			continue;

		int px=X-fa->GetMinX();
		int mdy=Y-starty;
		BYTE	*p0=ImagePoint[0]->GetY(dy+Y)+dx+X;
		BYTE	*p1=ImagePoint[1]->GetY(dy+Y)+dx+X;
		BYTE	*p2=ImagePoint[2]->GetY(dy+Y)+dx+X;

		BYTE	*q=&(pMap[Lx*mdy+((X-fa->GetMinX())>>3)]);

		/*
		unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));
		for(int x=0;x<Numb;x+=8){
			int N=8;
			if(x+8>=Numb)
				N=Numb-x;
			for(int k=0;k<N;k++,p0++,p1++,p2++){
				if(q>&pMap[LByte])
					break;
				if(q>=pMap){
					if(Level.Calc(*p0,*p1,*p2,Mergin)==false){
						*q|=(BYTE)Mask;
					}
				}
				Mask=_rotr(Mask,1);
				if((Mask &0x80)!=0){
					q++;
				}
			}
		}
		*/

		int	Numb8=Numb>>3;
		int	Shift=(X-fa->GetMinX())&7;
		int	x=0;
		for(int j=0;j<Numb8;j++){
			BYTE	m=~(Level.Calc8(p0,p1,p2,Mergin));
			p0+=8;
			p1+=8;
			p2+=8;
			*q |= m>>Shift;
			q++;
			if(Shift!=0){
				*q |= m<<(8-Shift);
			}
			x+=8;
		}
		for(;x<Numb;x++){
			if(Level.Calc(*p0,*p1,*p2,Mergin)==false){
				*q|=(0x80>>(x&7));
			}
			if((x&7)==7){
				q++;
			}
			p0++;
			p1++;
			p2++;
		}
	}
	if(ImagePoint!=ImageList)
		delete	[]ImagePoint;
}


QRgb	TrueColorBlockItem::CalcCenterBright(ImageBuffer *ImageList[] ,int mx ,int my)
{
	int	N=0;
	double	DR=0;
	double	DG=0;
	double	DB=0;
	BYTE	*srcR;
	BYTE	*srcG;
	BYTE	*srcB;
	int		XNumb;
	int		DTmpR;
	int		DTmpG;
	int		DTmpB;

	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	FlexArea	*A=&FLineEdge;
	int		Ln=GetLayerNumb();

	for(int i=0;i<A->GetFLineLen();i++){
		int	y =A->GetFLineAbsY  (i)+my;
		if(y<0)
			continue;
		if(y>=MaxLines)
			break;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		if(x1<0)
			x1=0;
		if(x2>=DotPerLine)
			x2=DotPerLine;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(Ln>=3){
			DTmpR=DTmpG=DTmpB=0;
			srcR=ImageList[0]->GetY(y)+x1;
			srcG=ImageList[1]->GetY(y)+x1;
			srcB=ImageList[2]->GetY(y)+x1;
			for(int x=0;x<XNumb;x++){
				DTmpR+=*(srcR+x);
				DTmpG+=*(srcG+x);
				DTmpB+=*(srcB+x);
			}
			DR+=DTmpR;
			DG+=DTmpG;
			DB+=DTmpB;
		}
		else if(Ln==2){
			DTmpR=DTmpG=0;
			srcR=ImageList[0]->GetY(y)+x1;
			srcG=ImageList[1]->GetY(y)+x1;
			for(int x=0;x<XNumb;x++){
				DTmpR+=*(srcR+x);
				DTmpG+=*(srcG+x);
			}
			DR+=DTmpR;
			DG+=DTmpG;
		}
		else if(Ln==1){
			DTmpR=0;
			srcR=ImageList[0]->GetY(y)+x1;
			for(int x=0;x<XNumb;x++){
				DTmpR+=*(srcR+x);
			}
			DR+=DTmpR;
		}
		N+=XNumb;
	}

	int	YSep;
	int	XSep;
	A=&FLineInside;
	if(A->GetFLineLen()<20)
		YSep=1;
	else if(A->GetFLineLen()<40)
		YSep=2;
	else if(A->GetFLineLen()<60)
		YSep=3;
	else if(A->GetFLineLen()<100)
		YSep=4;
	else
		YSep=5;

	for(int i=0;i<A->GetFLineLen();i+=YSep){
		int	y =A->GetFLineAbsY  (i)+my;
		if(y<0)
			continue;
		if(y>=MaxLines)
			break;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		if(x1<0)
			x1=0;
		if(x2>=DotPerLine)
			x2=DotPerLine;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(XNumb<20)
			XSep=1;
		else if(XNumb<40)
			XSep=2;
		else if(XNumb<60)
			XSep=3;
		else if(XNumb<100)
			XSep=4;
		else
			XSep=5;

		if(Ln>=3){
			DTmpR=DTmpG=DTmpB=0;
			srcR=ImageList[0]->GetY(y)+x1;
			srcG=ImageList[1]->GetY(y)+x1;
			srcB=ImageList[2]->GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmpR+=*(srcR+x);
				DTmpG+=*(srcG+x);
				DTmpB+=*(srcB+x);
			}
			DR+=DTmpR;
			DG+=DTmpG;
			DB+=DTmpB;
		}
		else if(Ln==2){
			DTmpR=DTmpG=0;
			srcR=ImageList[0]->GetY(y)+x1;
			srcG=ImageList[1]->GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmpR+=*(srcR+x);
				DTmpG+=*(srcG+x);
			}
			DR+=DTmpR;
			DG+=DTmpG;
		}
		else if(Ln==1){
			DTmpR=0;
			srcR=ImageList[0]->GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmpR+=*(srcR+x);
			}
			DR+=DTmpR;
		}
		N+=(XNumb+XSep-1)/XSep;
	}
	if(N!=0){
		DR/=N;
		DG/=N;
		DB/=N;
	}
	return qRgb((int)DR,(int)DG,(int)DB);
}

//==================================================================================
XYClass	*TrueColorBlockItem::GetSWayListFirst(int ThreadNo,int selfSearch)
{
	TrueColorBlockInPage *L=dynamic_cast<TrueColorBlockInPage *>(GetParent());
	if(L!=NULL){
		if(L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SWay.GetFirst()==NULL)
			L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SetSearchWay(selfSearch);
		return L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SWay.GetFirst();
	}
	return NULL;
}
void	TrueColorBlockItem::SetSWayListToTop(int ThreadNo,int selfSearch,XYClass *w)
{
	TrueColorBlockInPage *L=dynamic_cast<TrueColorBlockInPage *>(GetParent());
	if(L!=NULL)
		L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].ToTop(w);
}

