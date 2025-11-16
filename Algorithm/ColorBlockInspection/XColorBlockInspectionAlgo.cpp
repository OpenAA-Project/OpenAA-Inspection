#include "ColorBlockFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorBlockInspectionAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XColorBlockInspection.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XColorBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"

#if defined(linux)
#include <x86intrin.h>
#endif // defined(linux)


const	int	MaxResultNGPointInBlock=1000;
const	int	MaxReEntrantCount=30000;


bool    ColorBlockItem::ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthRL ,int BrightWidthRH ,int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
						  ,int BrightWidthGL ,int BrightWidthGH ,int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
						  ,int BrightWidthBL ,int BrightWidthBH ,int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
						  ,WORD &CenterBrightR,WORD &CenterBrightG,WORD &CenterBrightB
						  ,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
							,WORD	RMinNGCountL,WORD RMinNGCountH
							,WORD	GMinNGCountL,WORD GMinNGCountH
							,WORD	BMinNGCountL,WORD BMinNGCountH
							,ThresholdMode NBMode)
{
	const	ColorBlockThreshold	*RThr=GetThresholdR();
	if(RThr->PointMove.ModeEnabled==false){
		return true;
	}
	CenterBrightTargetR=CenterBrightR;
	CenterBrightTargetG=CenterBrightG;
	CenterBrightTargetB=CenterBrightB;
	FlexArea    SubFLines;
    FlexArea    SubFLineEdge;
    FlexArea    SubFLineInside;
    if(SubBlock.GetFirst()!=NULL){
        SubFLines       =GetArea();
        SubFLineEdge    =FLineEdge;
        SubFLineInside  =FLineInside;
        }

    int MinK;
    int	MinL=0x7FFFFFFF;
    int	MinH=0x7FFFFFFF;
    int dx=0;
    int dy=0;
	int SumRL=0;
	int SumRH=0;
	int SumGL=0;
	int SumGH=0;
	int SumBL=0;
	int SumBH=0;

	if(SubBlock.GetFirst()!=NULL){
		L3Remove(mx ,my
                        ,SubFLines
                        ,SubFLineEdge
                        ,SubFLineInside);
		if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
			CalcCenterBright(MasterBuff,0 ,0 ,CenterBrightR,CenterBrightG,CenterBrightB);
		}
	int InsideSumRL=0;
	int InsideSumRH=0;
	int InsideSumGL=0;
	int InsideSumGH=0;
	int InsideSumBL=0;
	int InsideSumBH=0;
	Level3Inside(mx ,my
					,BrightWidthRL ,BrightWidthRH
					,BrightWidthGL ,BrightWidthGH
					,BrightWidthBL ,BrightWidthBH
					,InsideSumRL,InsideSumRH
					,InsideSumGL,InsideSumGH
					,InsideSumBL,InsideSumBH
					,TargetBuff);

	short	Error=0;
	for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
		if(SubBlock.GetFirst()!=NULL){
			L3Remove(mx+W->x ,my+W->y
                                ,SubFLines
                                ,SubFLineEdge
                                ,SubFLineInside);
			if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
				CalcCenterBright(MasterBuff,0 ,0 ,CenterBrightR,CenterBrightG,CenterBrightB);
		}
		int	TmpBrightWidthRL=BrightWidthRL;
		int	TmpBrightWidthRH=BrightWidthRH;
		int	TmpBrightWidthGL=BrightWidthGL;
		int	TmpBrightWidthGH=BrightWidthGH;
		int	TmpBrightWidthBL=BrightWidthBL;
		int	TmpBrightWidthBH=BrightWidthBH;
		if(RThr->PointMove.ModeAdjustable==true){
			EnAverage(mx+W->x ,my+W->y
						,TmpBrightWidthRL,TmpBrightWidthRH
						,TmpBrightWidthGL,TmpBrightWidthGH
						,TmpBrightWidthBL,TmpBrightWidthBH
						,TargetBuff);
		}

		SumRL=0;
		SumRH=0;
		SumGL=0;
		SumGH=0;
		SumBL=0;
		SumBH=0;
		Level3Speedy(mx+W->x ,my+W->y
					,TmpBrightWidthRL ,TmpBrightWidthRH
					,TmpBrightWidthGL ,TmpBrightWidthGH
					,TmpBrightWidthBL ,TmpBrightWidthBH
					,SumRL,SumRH
					,SumGL,SumGH
					,SumBL,SumBH
					,TargetBuff);
		//SumL+=InsideSumL;
		//SumH+=InsideSumH;
		if(SumRL<=OKDotRL && SumRH<=OKDotRH && SumGL<=OKDotGL && SumGH<=OKDotGH && SumBL<=OKDotBL && SumBH<=OKDotBH){
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(W->x,W->y);
			Res->SetResult1(SumRL+SumGL+SumBL);
			Res->SetResult2(SumRH+SumGH+SumBH);
			Res->SetError(1);	//OK
			SetSWayListToTop(ThreadNo,RThr->SelfSearch,W);
			if(SubBlock.GetFirst()!=NULL){
				SetArea(SubFLines);
				FLineEdge   =SubFLineEdge;
				FLineInside =SubFLineInside;
			}
			return true;
		}
		if((SumRL+SumGL+SumBL)<=MinL && (SumRH+SumGH+SumBH)<=MinH){
			dx=W->x;
			dy=W->y;
			MinL=SumRL+SumGL+SumBL;
			MinH=SumRH+SumGH+SumBH;
			Error=0;
			if(SumRL>OKDotRL || SumGL>OKDotGL || SumBL>OKDotBL)
				Error |= 0x10;	//?????A?m?f
			if(SumRH>OKDotRH || SumGH>OKDotGH || SumBH>OKDotBH)
				Error |= 0x20;	//?????A?m?f
		}
	}

	int RNumb;
	int Rx[MaxResultNGPointInBlock];
	int Ry[MaxResultNGPointInBlock];

	int	SumL=SumRL+SumGL+SumBL;
	int	SumH=SumRH+SumGH+SumBH;
	if(RThr->PointMove.ModeNGCluster==true){
		int MinSumL=99999999;
		int MinSumH=99999999;
		int	MinDx=0;
		int	MinDy=0;
		ResultPosListContainer	NowList;
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			if(SubBlock.GetFirst()!=NULL){
				L3Remove(mx+W->x ,my+W->y
				        ,SubFLines
					    ,SubFLineEdge
						,SubFLineInside);
				if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
					CalcCenterBright(MasterBuff,0 ,0 ,CenterBrightR,CenterBrightG,CenterBrightB);
			}
			NowList.RemoveAll();
			short	iError=0;
			if(CheckOnNG(mx,my,W->x,W->y
						,BrightWidthRL,BrightWidthRH ,OKDotRL ,OKDotRH ,OKLengthRL ,OKLengthRH
						,BrightWidthGL,BrightWidthGH ,OKDotGL ,OKDotGH ,OKLengthGL ,OKLengthGH
						,BrightWidthBL,BrightWidthBH ,OKDotBL ,OKDotBH ,OKLengthBL ,OKLengthBH
						,SumL,SumH
						,NowList
						,iError
						,MasterBuff ,TargetBuff
						,RMinNGCountL,RMinNGCountH
						,GMinNGCountL,GMinNGCountH
						,BMinNGCountL,BMinNGCountH
						,NBMode)==true){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(W->x,W->y);
				Res->SetResult1(SumL);
				Res->SetResult2(SumH);
				Res->SetError(1);	//OK
				if(SubBlock.GetFirst()!=NULL){
					SetArea(SubFLines);
					FLineEdge   =SubFLineEdge;
					FLineInside =SubFLineInside;
				}
				return true;
			}
			if((MinSumL+MinSumH)>(SumL+SumH)){
				MinSumL=SumL;
				MinSumH=SumH;
				MinDx=W->x;
				MinDy=W->y;
				Res->MovePosList(NowList);
				Error=iError;
			}
		}
		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(MinDx,MinDy);
		Res->SetResult1(SumL);
		Res->SetResult2(SumH);
		Res->SetError(2 | Error);	//NG
		return false;
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new ResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1(SumL);
	r->SetResult2(SumH);
	r->result =0x30;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(SumL);
	Res->SetResult2(SumH);
	Res->SetError(2 | Error);	//NG

	if(SubBlock.GetFirst()!=NULL){
		SetArea(SubFLines);
		FLineEdge   =SubFLineEdge;
		FLineInside =SubFLineInside;
	}
    return false;

}

int	LimitX(int d,int m){	return (d>=m)?d:m;	}

bool    ColorBlockItem::ExecuteProcessingInnerWithoutSubtract(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthRL ,int BrightWidthRH ,int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
						  ,int BrightWidthGL ,int BrightWidthGH ,int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
						  ,int BrightWidthBL ,int BrightWidthBH ,int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
						  ,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
							,WORD	RMinNGCountL,WORD RMinNGCountH
							,WORD	GMinNGCountL,WORD GMinNGCountH
							,WORD	BMinNGCountL,WORD BMinNGCountH
							,ThresholdMode NBMode)
{
	const	ColorBlockThreshold	*RThr=GetThresholdR();
	if(RThr->PointMove.ModeEnabled==false){
		return true;
	}
	CenterBrightTargetR=CenterBrightR;
	CenterBrightTargetG=CenterBrightG;
	CenterBrightTargetB=CenterBrightB;
    int MinK;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
    int	MinL=0x7FFFFFFF;
    int	MinH=0x7FFFFFFF;
    int dx=0;
    int dy=0;
	int SumRL=0;
	int SumRH=0;
	int SumGL=0;
	int SumGH=0;
	int SumBL=0;
	int SumBH=0;
	short	Error=0;
	int	NarrowBlockW=12;

	int InsideSumRL=0;
	int InsideSumRH=0;
	int InsideSumGL=0;
	int InsideSumGH=0;
	int InsideSumBL=0;
	int InsideSumBH=0;
	Level3Inside(mx ,my
					,BrightWidthRL ,BrightWidthRH
					,BrightWidthGL ,BrightWidthGH
					,BrightWidthBL ,BrightWidthBH
					,InsideSumRL,InsideSumRH
					,InsideSumGL,InsideSumGH
					,InsideSumBL,InsideSumBH
					,TargetBuff);

	if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			int	TmpBrightWidthRL=BrightWidthRL;
			int	TmpBrightWidthRH=BrightWidthRH;
			int	TmpBrightWidthGL=BrightWidthGL;
			int	TmpBrightWidthGH=BrightWidthGH;
			int	TmpBrightWidthBL=BrightWidthBL;
			int	TmpBrightWidthBH=BrightWidthBH;
			if(RThr->PointMove.ModeAdjustable==true){
				EnAverage(mx+W->x ,my+W->y
						,TmpBrightWidthRL,TmpBrightWidthRH
						,TmpBrightWidthGL,TmpBrightWidthGH
						,TmpBrightWidthBL,TmpBrightWidthBH
						,TargetBuff);
			}

			SumRL=InsideSumRL;
			SumRH=InsideSumRH;
			SumGL=InsideSumGL;
			SumGH=InsideSumGH;
			SumBL=InsideSumBL;
			SumBH=InsideSumBH;
			Level3OnlyEdge(mx+W->x ,my+W->y
					,TmpBrightWidthRL ,TmpBrightWidthRH
					,TmpBrightWidthGL ,TmpBrightWidthGH
					,TmpBrightWidthBL ,TmpBrightWidthBH
					,SumRL,SumRH
					,SumGL,SumGH
					,SumBL,SumBH
					,TargetBuff);
			//SumL+=InsideSumL;
			//SumH+=InsideSumH;
			if(SumRL<=OKDotRL && SumRH<=OKDotRH && SumGL<=OKDotGL && SumGH<=OKDotGH && SumBL<=OKDotBL && SumBH<=OKDotBH){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(W->x,W->y);
				Res->SetResult1(SumRL+SumGL+SumBL);
				Res->SetResult2(SumRH+SumGH+SumBH);
				Res->SetError(1);	//OK
				SetSWayListToTop(ThreadNo,RThr->SelfSearch,W);
				return true;
			}
			if((SumRL*SumRL+SumGL*SumGL+SumBL*SumBL+SumRH*SumRH+SumGH*SumGH+SumBH*SumBH)<=(((int64)MinL2)+((int64)MinH2))){
				dx=W->x;
				dy=W->y;
				MinL2=SumRL*SumRL+SumGL*SumGL+SumBL*SumBL;
				MinH2=SumRH*SumRH+SumGH*SumGH+SumBH*SumBH;
				MinL=SumRL+SumGL+SumBL;
				MinH=SumRH+SumGH+SumBH;
				Error=0;
				if(SumRL>OKDotRL || SumGL>OKDotGL || SumBL>OKDotBL)
					Error |= 0x10;	//?????A?m?f
				if(SumRH>OKDotRH || SumGH>OKDotGH || SumBH>OKDotBH)
					Error |= 0x20;	//?????A?m?f
			}
		}
	}
	else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			for(int t=-1;t<=1;t++){
				int	TmpBrightWidthRL=BrightWidthRL;
				int	TmpBrightWidthRH=BrightWidthRH;
				int	TmpBrightWidthGL=BrightWidthGL;
				int	TmpBrightWidthGH=BrightWidthGH;
				int	TmpBrightWidthBL=BrightWidthBL;
				int	TmpBrightWidthBH=BrightWidthBH;
				if(RThr->PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my+W->y+t
						,TmpBrightWidthRL,TmpBrightWidthRH
						,TmpBrightWidthGL,TmpBrightWidthGH
						,TmpBrightWidthBL,TmpBrightWidthBH
						,TargetBuff);
				}
	
				SumRL=0;
				SumRH=0;
				SumGL=0;
				SumGH=0;
				SumBL=0;
				SumBH=0;
				Level3Speedy(mx+W->x ,my+W->y+t
					,TmpBrightWidthRL ,TmpBrightWidthRH
					,TmpBrightWidthGL ,TmpBrightWidthGH
					,TmpBrightWidthBL ,TmpBrightWidthBH
					,SumRL,SumRH
					,SumGL,SumGH
					,SumBL,SumBH
					,TargetBuff);

				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(SumRL<=OKDotRL && SumRH<=OKDotRH && SumGL<=OKDotGL && SumGH<=OKDotGH && SumBL<=OKDotBL && SumBH<=OKDotBH){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,W->y+t);
					Res->SetResult1(SumRL+SumGL+SumBL);
					Res->SetResult2(SumRH+SumGH+SumBH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,RThr->SelfSearch,W);
					return true;
				}
				if((SumRL*SumRL+SumGL*SumGL+SumBL*SumBL+SumRH*SumRH+SumGH*SumGH+SumBH*SumBH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=W->y+t;
					MinL2=SumRL*SumRL+SumGL*SumGL+SumBL*SumBL;
					MinH2=SumRH*SumRH+SumGH*SumGH+SumBH*SumBH;
					MinL=SumRL+SumGL+SumBL;
					MinH=SumRH+SumGH+SumBH;
					Error=0;
					if(SumRL>OKDotRL || SumGL>OKDotGL || SumBL>OKDotBL)
						Error |= 0x10;	//?????A?m?f
					if(SumRH>OKDotRH || SumGH>OKDotGH || SumBH>OKDotBH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
	}
	else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			for(int t=-1;t<=1;t++){
				int	TmpBrightWidthRL=BrightWidthRL;
				int	TmpBrightWidthRH=BrightWidthRH;
				int	TmpBrightWidthGL=BrightWidthGL;
				int	TmpBrightWidthGH=BrightWidthGH;
				int	TmpBrightWidthBL=BrightWidthBL;
				int	TmpBrightWidthBH=BrightWidthBH;
				if(RThr->PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x+t ,my+W->y
						,TmpBrightWidthRL,TmpBrightWidthRH
						,TmpBrightWidthGL,TmpBrightWidthGH
						,TmpBrightWidthBL,TmpBrightWidthBH
						,TargetBuff);
				}
	
				SumRL=0;
				SumRH=0;
				SumGL=0;
				SumGH=0;
				SumBL=0;
				SumBH=0;
				Level3Speedy(mx+W->x+t ,my+W->y
					,TmpBrightWidthRL ,TmpBrightWidthRH
					,TmpBrightWidthGL ,TmpBrightWidthGH
					,TmpBrightWidthBL ,TmpBrightWidthBH
					,SumRL,SumRH
					,SumGL,SumGH
					,SumBL,SumBH
					,TargetBuff);

				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(SumRL<=OKDotRL && SumRH<=OKDotRH && SumGL<=OKDotGL && SumGH<=OKDotGH && SumBL<=OKDotBL && SumBH<=OKDotBH){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x+t,W->y);
					Res->SetResult1(SumRL+SumGL+SumBL);
					Res->SetResult2(SumRH+SumGH+SumBH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,RThr->SelfSearch,W);
					return true;
				}
				if((SumRL*SumRL+SumGL*SumGL+SumBL*SumBL+SumRH*SumRH+SumGH*SumGH+SumBH*SumBH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x+t;
					dy=W->y;
					MinL2=SumRL*SumRL+SumGL*SumGL+SumBL*SumBL;
					MinH2=SumRH*SumRH+SumGH*SumGH+SumBH*SumBH;
					MinL=SumRL+SumGL+SumBL;
					MinH=SumRH+SumGH+SumBH;
					Error=0;
					if(SumRL>OKDotRL || SumGL>OKDotGL || SumBL>OKDotBL)
						Error |= 0x10;	//?????A?m?f
					if(SumRH>OKDotRH || SumGH>OKDotGH || SumBH>OKDotBH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
	}
	else{
		for(XYClass *W=GetSWayListFirst(ThreadNo,RThr->SelfSearch);W!=NULL;W=W->GetNext()){
			for(int t=-1;t<=1;t++){
				for(int s=-1;s<=1;s++){
					int	TmpBrightWidthRL=BrightWidthRL;
					int	TmpBrightWidthRH=BrightWidthRH;
					int	TmpBrightWidthGL=BrightWidthGL;
					int	TmpBrightWidthGH=BrightWidthGH;
					int	TmpBrightWidthBL=BrightWidthBL;
					int	TmpBrightWidthBH=BrightWidthBH;
					if(RThr->PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my+W->y+s
							,TmpBrightWidthRL,TmpBrightWidthRH
							,TmpBrightWidthGL,TmpBrightWidthGH
							,TmpBrightWidthBL,TmpBrightWidthBH
							,TargetBuff);
					}
	
					SumRL=0;
					SumRH=0;
					SumGL=0;
					SumGH=0;
					SumBL=0;
					SumBH=0;
					Level3Speedy(mx+W->x+t ,my+W->y+s
						,TmpBrightWidthRL ,TmpBrightWidthRH
						,TmpBrightWidthGL ,TmpBrightWidthGH
						,TmpBrightWidthBL ,TmpBrightWidthBH
						,SumRL,SumRH
						,SumGL,SumGH
						,SumBL,SumBH
						,TargetBuff);

					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(SumRL<=OKDotRL && SumRH<=OKDotRH && SumGL<=OKDotGL && SumGH<=OKDotGH && SumBL<=OKDotBL && SumBH<=OKDotBH){
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,W->y+s);
						Res->SetResult1(SumRL+SumGL+SumBL);
						Res->SetResult2(SumRH+SumGH+SumBH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,RThr->SelfSearch,W);
						return true;
					}
					if((SumRL*SumRL+SumGL*SumGL+SumBL*SumBL+SumRH*SumRH+SumGH*SumGH+SumBH*SumBH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=W->y+s;
						MinL2=SumRL*SumRL+SumGL*SumGL+SumBL*SumBL;
						MinH2=SumRH*SumRH+SumGH*SumGH+SumBH*SumBH;
						MinL=SumRL+SumGL+SumBL;
						MinH=SumRH+SumGH+SumBH;
						Error=0;
						if(SumRL>OKDotRL || SumGL>OKDotGL || SumBL>OKDotBL)
							Error |= 0x10;	//?????A?m?f
						if(SumRH>OKDotRH || SumGH>OKDotGH || SumBH>OKDotBH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
	}

	int RNumb;
	int Rx[MaxResultNGPointInBlock];
	int Ry[MaxResultNGPointInBlock];
	int	SumL=SumRL+SumGL+SumBL;
	int	SumH=SumRH+SumGH+SumBH;

	if(RThr->PointMove.ModeNGCluster==true){
		if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			ResultPosListContainer	NowList;
			short	iError=0;
			if(CheckOnNGAll(mx,my,dx,dy
						,BrightWidthRL,BrightWidthRH ,OKDotRL ,OKDotRH ,OKLengthRL ,OKLengthRH
						,BrightWidthGL,BrightWidthGH ,OKDotGL ,OKDotGH ,OKLengthGL ,OKLengthGH
						,BrightWidthBL,BrightWidthBH ,OKDotBL ,OKDotBH ,OKLengthBL ,OKLengthBH
						,SumL,SumH
						,NowList
						,iError
						,MasterBuff ,TargetBuff
						,RMinNGCountL,RMinNGCountH
						,GMinNGCountL,GMinNGCountH
						,BMinNGCountL,BMinNGCountH
						,NBMode)==true){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(dx,dy);
				Res->SetResult1(SumL);
				Res->SetResult2(SumH);
				Res->SetError(1);	//OK
				return true;
			}
			Res->MovePosList(NowList);

			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(dx,dy);
			Res->SetResult1(SumL);
			Res->SetResult2(SumH);
			Res->SetError(2 | iError);	//NG
			return false;
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			for(int t=-1;t<=1;t++){
				ResultPosListContainer	MinList;
				short	iError=0;
				if(CheckOnNG(mx,my,dx,dy+t
						,BrightWidthRL,BrightWidthRH ,OKDotRL ,OKDotRH ,OKLengthRL ,OKLengthRH
						,BrightWidthGL,BrightWidthGH ,OKDotGL ,OKDotGH ,OKLengthGL ,OKLengthGH
						,BrightWidthBL,BrightWidthBH ,OKDotBL ,OKDotBH ,OKLengthBL ,OKLengthBH
						,SumL,SumH
						,MinList
						,iError
						,MasterBuff ,TargetBuff
						,RMinNGCountL,RMinNGCountH
						,GMinNGCountL,GMinNGCountH
						,BMinNGCountL,BMinNGCountH
						,NBMode)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy+t);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
					MinDx=dx;
					MinDy=dy+t;
					MinSumL=SumL;
					MinSumH=SumH;
					MinSumL2=SumL*SumL;
					MinSumH2=SumH*SumH;
					NowList.Move(MinList);
					Error	=iError;
				}
			}
			Res->MovePosList(NowList);
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(MinDx,MinDy);
			Res->SetResult1(MinSumL);
			Res->SetResult2(MinSumH);
			Res->SetError(2 | Error);	//NG
			return false;
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			for(int t=-1;t<=1;t++){
				ResultPosListContainer	MinList;
				short	iError=0;
				if(CheckOnNG(mx,my,dx+t,dy
						,BrightWidthRL,BrightWidthRH ,OKDotRL ,OKDotRH ,OKLengthRL ,OKLengthRH
						,BrightWidthGL,BrightWidthGH ,OKDotGL ,OKDotGH ,OKLengthGL ,OKLengthGH
						,BrightWidthBL,BrightWidthBH ,OKDotBL ,OKDotBH ,OKLengthBL ,OKLengthBH
						,SumL,SumH
						,MinList
						,iError
						,MasterBuff ,TargetBuff
						,RMinNGCountL,RMinNGCountH
						,GMinNGCountL,GMinNGCountH
						,BMinNGCountL,BMinNGCountH
						,NBMode)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx+t,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
					MinDx=dx;
					MinDy=dy+t;
					MinSumL=SumL;
					MinSumH=SumH;
					MinSumL2=SumL*SumL;
					MinSumH2=SumH*SumH;
					NowList.Move(MinList);
					Error	=iError;
				}
			}
			Res->MovePosList(NowList);
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(MinDx,MinDy);
			Res->SetResult1(MinSumL);
			Res->SetResult2(MinSumH);
			Res->SetError(2 | Error);	//NG
			return false;
		}
		else{
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			for(int t=-1;t<=1;t++){
				for(int s=-1;s<=1;s++){
					ResultPosListContainer	MinList;
					short	iError=0;
					if(CheckOnNG(mx,my,dx+t,dy+s
								,BrightWidthRL,BrightWidthRH ,OKDotRL ,OKDotRH ,OKLengthRL ,OKLengthRH
								,BrightWidthGL,BrightWidthGH ,OKDotGL ,OKDotGH ,OKLengthGL ,OKLengthGH
								,BrightWidthBL,BrightWidthBH ,OKDotBL ,OKDotBH ,OKLengthBL ,OKLengthBH
								,SumL,SumH
								,MinList
								,iError
								,MasterBuff ,TargetBuff
								,RMinNGCountL,RMinNGCountH
								,GMinNGCountL,GMinNGCountH
								,BMinNGCountL,BMinNGCountH
								,NBMode)==true){
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(dx+t,dy+s);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						return true;
					}				
					if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
						MinDx=dx;
						MinDy=dy+t;
						MinSumL=SumL;
						MinSumH=SumH;
						MinSumL2=SumL*SumL;
						MinSumH2=SumH*SumH;
						NowList.Move(MinList);
						Error	=iError;
					}
				}
			}
			Res->MovePosList(NowList);
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(MinDx,MinDy);
			Res->SetResult1(MinSumL);
			Res->SetResult2(MinSumH);
			Res->SetError(2 | Error);	//NG
			return false;
		}
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new ResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1(SumL);
	r->SetResult2(SumH);
	r->result =0x30;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(MinL);
	Res->SetResult2(MinH);
	Res->SetError(2 | Error);	//NG

    return false;

}

bool    ColorBlockItem::L3Remove(int mx ,int my
                           ,FlexArea &SubFLines
                           ,FlexArea &SubFLineEdge
                           ,FlexArea &SubFLineInside)
{
    SetArea(SubFLines);
    FLineEdge   =SubFLineEdge;
    FLineInside =SubFLineInside;

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
	return true;
}

void	ColorBlockItem::Level3Inside(int mx ,int my
					,int BrightWidthRL ,int BrightWidthRH
					,int BrightWidthGL ,int BrightWidthGH
					,int BrightWidthBL ,int BrightWidthBH
					,int &InsideSumRL,int &InsideSumRH
					,int &InsideSumGL,int &InsideSumGH
					,int &InsideSumBL,int &InsideSumBH
					,ImageBuffer *TargetBuff[])
{
    if(BrightWidthRL<0)    BrightWidthRL=0;
    if(BrightWidthRH>255)  BrightWidthRH=255;
	const	ColorBlockThreshold	*RThr=GetThresholdR();

    if(RThr->PointMove.ModeWhiteMask==true)
        BrightWidthRH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        BrightWidthRL=0;

    if(BrightWidthGL<0)    BrightWidthGL=0;
    if(BrightWidthGH>255)  BrightWidthGH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        BrightWidthGH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        BrightWidthGL=0;

    if(BrightWidthBL<0)    BrightWidthBL=0;
    if(BrightWidthBH>255)  BrightWidthBH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        BrightWidthBH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        BrightWidthBL=0;

	for(int i=0;i<FLineInside.GetFLineLen();i++){
		int	y =FLineInside.GetFLineAbsY  (i)+my;
		int	x1=FLineInside.GetFLineLeftX (i)+mx;
		int	x2=FLineInside.GetFLineRightX(i)+mx;
		BYTE	*srcR=TargetBuff[0]->GetY(y);
		BYTE	*srcG=TargetBuff[1]->GetY(y);
		BYTE	*srcB=TargetBuff[2]->GetY(y);
		for(int x=x1;x<x2;x++){
			int	r=srcR[x];
			if(r<BrightWidthRL)
				InsideSumRL++;
			if(BrightWidthRH<r)
				InsideSumRH++;

			int	g=srcG[x];
			if(g<BrightWidthGL)
				InsideSumGL++;
			if(BrightWidthGH<g)
				InsideSumGH++;

			int	b=srcB[x];
			if(b<BrightWidthBL)
				InsideSumBL++;
			if(BrightWidthBH<b)
				InsideSumBH++;
		}
	}
}

void	ColorBlockItem::EnAverage(int mx,int my
						,int &TmpBrightWidthLR,int &TmpBrightWidthHR
						,int &TmpBrightWidthLG,int &TmpBrightWidthHG
						,int &TmpBrightWidthLB,int &TmpBrightWidthHB
						,ImageBuffer *TargetBuff[])
{
	WORD	Dr,Dg,Db;
	CalcCenterBright(TargetBuff,mx,my ,Dr,Dg,Db);
	int	DifColR=Dr-CenterBrightR;
	int	DifColG=Dg-CenterBrightG;
	int	DifColB=Db-CenterBrightB;
	const	ColorBlockThreshold	*RThr=GetThresholdR();

	if(DifColR>RThr->InsR.AdjustWhite)
		DifColR=RThr->InsR.AdjustWhite;
	if(-DifColR>RThr->InsR.AdjustBlack)
		DifColR=-((int)RThr->InsR.AdjustBlack);
	TmpBrightWidthLR+=DifColR;
	TmpBrightWidthHR+=DifColR;

	if(DifColG>RThr->InsG.AdjustWhite)
		DifColG=RThr->InsG.AdjustWhite;
	if(-DifColG>RThr->InsG.AdjustBlack)
		DifColG=-((int)RThr->InsG.AdjustBlack);
	TmpBrightWidthLG+=DifColG;
	TmpBrightWidthHG+=DifColG;

	if(DifColB>RThr->InsB.AdjustWhite)
		DifColB=RThr->InsB.AdjustWhite;
	if(-DifColB>RThr->InsB.AdjustBlack)
		DifColB=-((int)RThr->InsB.AdjustBlack);
	TmpBrightWidthLB+=DifColB;
	TmpBrightWidthHB+=DifColB;

	CenterBrightTargetR=CenterBrightR+DifColB;
	CenterBrightTargetG=CenterBrightG+DifColB;
	CenterBrightTargetB=CenterBrightB+DifColB;
}

void	ColorBlockItem::EnAverage(int mx,int my
						,WORD &TmpBrightWidthLR,WORD &TmpBrightWidthHR
						,WORD &TmpBrightWidthLG,WORD &TmpBrightWidthHG
						,WORD &TmpBrightWidthLB,WORD &TmpBrightWidthHB
						,ImageBuffer *TargetBuff[])
{
	int iTmpBrightWidthLR=TmpBrightWidthLR;
	int iTmpBrightWidthHR=TmpBrightWidthHR;
	int iTmpBrightWidthLG=TmpBrightWidthLG;
	int iTmpBrightWidthHG=TmpBrightWidthHG;
	int iTmpBrightWidthLB=TmpBrightWidthLB;
	int iTmpBrightWidthHB=TmpBrightWidthHB;
	EnAverage(mx,my
			,iTmpBrightWidthLR,iTmpBrightWidthHR
			,iTmpBrightWidthLG,iTmpBrightWidthHG
			,iTmpBrightWidthLB,iTmpBrightWidthHB
			,TargetBuff);

	TmpBrightWidthLR=iTmpBrightWidthLR;
	TmpBrightWidthHR=iTmpBrightWidthHR;
	TmpBrightWidthLG=iTmpBrightWidthLG;
	TmpBrightWidthHG=iTmpBrightWidthHG;
	TmpBrightWidthLB=iTmpBrightWidthLB;
	TmpBrightWidthHB=iTmpBrightWidthHB;
}


void	ColorBlockItem::Level3Speedy(int mx,int my
					,int TmpBrightWidthRL ,int TmpBrightWidthRH
					,int TmpBrightWidthGL ,int TmpBrightWidthGH
					,int TmpBrightWidthBL ,int TmpBrightWidthBH
					,int &SumRL,int &SumRH
					,int &SumGL,int &SumGH
					,int &SumBL,int &SumBH
					,ImageBuffer *TargetBuff[])
{
    if(TmpBrightWidthRL<0)    TmpBrightWidthRL=0;
    if(TmpBrightWidthRH>255)  TmpBrightWidthRH=255;
	const	ColorBlockThreshold	*RThr=GetThresholdR();
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthRH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthRL=0;

    if(TmpBrightWidthGL<0)    TmpBrightWidthGL=0;
    if(TmpBrightWidthGH>255)  TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthGL=0;

    if(TmpBrightWidthBL<0)    TmpBrightWidthBL=0;
    if(TmpBrightWidthBH>255)  TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthBL=0;

	FlexArea	*A=&GetArea();
	for(int i=0;i<A->GetFLineLen();i++){
		int	y =A->GetFLineAbsY  (i)+my;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		BYTE	*srcR=TargetBuff[0]->GetY(y);
		BYTE	*srcG=TargetBuff[1]->GetY(y);
		BYTE	*srcB=TargetBuff[2]->GetY(y);
		for(int x=x1;x<x2;x++){
			int	r=srcR[x];
			if(r<TmpBrightWidthRL)
				SumRL++;
			if(TmpBrightWidthRH<r)
				SumRH++;

			int	g=srcG[x];
			if(g<TmpBrightWidthGL)
				SumGL++;
			if(TmpBrightWidthGH<g)
				SumGH++;

			int	b=srcB[x];
			if(b<TmpBrightWidthBL)
				SumBL++;
			if(TmpBrightWidthBH<b)
				SumBH++;
		}
	}
}
void	ColorBlockItem::Level3OnlyEdge(int mx,int my
					,int TmpBrightWidthRL ,int TmpBrightWidthRH
					,int TmpBrightWidthGL ,int TmpBrightWidthGH
					,int TmpBrightWidthBL ,int TmpBrightWidthBH
					,int &SumRL,int &SumRH
					,int &SumGL,int &SumGH
					,int &SumBL,int &SumBH
					,ImageBuffer *TargetBuff[])
{
    if(TmpBrightWidthRL<0)    TmpBrightWidthRL=0;
    if(TmpBrightWidthRH>255)  TmpBrightWidthRH=255;
	const	ColorBlockThreshold	*RThr=GetThresholdR();

    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthRH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthRL=0;

    if(TmpBrightWidthGL<0)    TmpBrightWidthGL=0;
    if(TmpBrightWidthGH>255)  TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthGL=0;

    if(TmpBrightWidthBL<0)    TmpBrightWidthBL=0;
    if(TmpBrightWidthBH>255)  TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthBL=0;

	FlexArea	*A=&FLineEdge;
	for(int i=0;i<A->GetFLineLen();i++){
		int	y =A->GetFLineAbsY  (i)+my;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		BYTE	*srcR=TargetBuff[0]->GetY(y);
		BYTE	*srcG=TargetBuff[1]->GetY(y);
		BYTE	*srcB=TargetBuff[2]->GetY(y);
		for(int x=x1;x<x2;x++){
			int	r=srcR[x];
			if(r<TmpBrightWidthRL)
				SumRL++;
			if(TmpBrightWidthRH<r)
				SumRH++;

			int	g=srcG[x];
			if(g<TmpBrightWidthGL)
				SumGL++;
			if(TmpBrightWidthGH<g)
				SumGH++;

			int	b=srcB[x];
			if(b<TmpBrightWidthBL)
				SumBL++;
			if(TmpBrightWidthBH<b)
				SumBH++;
		}
	}
}
struct AnalyzeNGHoleClass
{
    BYTE			*NGBmp;
    int             NGBmpX;
    int             NGBmpY;
    int             LLevel;
    int             HLevel;
    int             NGNumb;
    ImageBuffer     *TopBuff;
    ImageBuffer     *MasterBuff;
    ImageBuffer     *LoadedBuff;
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

void  ColorBlockItem::SearchAnalyzeNGHole(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData==NULL){
		return;
	}
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY()){
        return;
	}
	if(LData->NGNumb>=MaxReEntrantCount){
		return;
	}
    BYTE *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0){
        return;
	}

    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    if((y+LData->dy)<0 || (y+LData->dy)>=LData->MaxLines
    || (x+LData->dx)<0 || (x+LData->dx)>=LData->DotPerLine){
        return;
	}

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

void  ColorBlockItem::SearchAnalyzeNGHoleL(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData==NULL){
		return;
	}
	if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY()){
        return;
	}
	if(LData->NGNumb>=MaxReEntrantCount){
		return;
	}
    BYTE *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0){
        return;
	}
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    if((y+LData->dy)<0 || (y+LData->dy)>=LData->MaxLines
    || (x+LData->dx)<0 || (x+LData->dx)>=LData->DotPerLine){
        return;
	}

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
void  ColorBlockItem::SearchAnalyzeNGHoleH(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData==NULL){
		return;
	}
    if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY()){
        return;
	}
	if(LData->NGNumb>=MaxReEntrantCount){
		return;
	}
    BYTE *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0){
        return;
	}
    (*BB) &=~(0x80>>((x-LData->FLines->GetMinX())&7));

    if((y+LData->dy)<0 || (y+LData->dy)>=LData->MaxLines
    || (x+LData->dx)<0 || (x+LData->dx)>=LData->DotPerLine){
        return;
	}

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
void  ColorBlockItem::SearchAnalyzeNGHole2L(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData==NULL){
		return;
	}
	if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY()){
        return;
	}
	if(LData->NGNumb>=MaxReEntrantCount){
		return;
	}
    BYTE    *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0){
        return;
	}
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
void  ColorBlockItem::SearchAnalyzeNGHole2(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData==NULL){
		return;
	}
	if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY()){
        return;
	}
	if(LData->NGNumb>=MaxReEntrantCount){
		return;
	}
    BYTE    *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0){
        return;
	}
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
void  ColorBlockItem::SearchAnalyzeNGHole2H(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData==NULL){
		return;
	}
	if(x<LData->FLines->GetMinX() || x>=LData->FLines->GetMaxX()
    || y<LData->FLines->GetMinY() || y>=LData->FLines->GetMaxY()){
        return;
	}
	if(LData->NGNumb>=MaxReEntrantCount){
		return;
	}
    BYTE    *BB=B+((x-LData->FLines->GetMinX())>>3);
    if(((*BB)&(0x80>>((x-LData->FLines->GetMinX())&7)))==0){
        return;
	}
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

int  ColorBlockItem::AnalyzeNGHole(int dx ,int dy,int x ,int y
							, int LLevel ,int HLevel
							, BYTE *NGBmp ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot ,int &Sum
							,ImageBuffer &MasterBuff,ImageBuffer &TargetBuff)
{
	Sum=0;
	struct AnalyzeNGHoleClass   LData;
	const	ColorBlockThreshold	*RThr=GetThresholdR();

    if(RThr->PointMove.ModeDiffer==false){
        LData.NGNumb=0;
		LData.TopBuff=&TargetBuff;
        LData.dx=dx;
        LData.dy=dy;
        LData.DotPerLine=GetDotPerLine();
        LData.MaxLines	=GetMaxLines() ;
        LData.LLevel=LLevel;
        LData.HLevel=HLevel;
        LData.NGBmp=NGBmp;
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
        return(LData.NGNumb);
        }
    else{
        LData.NGNumb=0;
        LData.TopBuff=NULL;
        LData.MasterBuff=&MasterBuff;
        LData.LoadedBuff=&TargetBuff;

        LData.dx=dx;
        LData.dy=dy;
        LData.LLevel=LLevel;
        LData.HLevel=HLevel;
        LData.NGBmp=NGBmp;
        LData.NGBmpX=NGBmpX;
        LData.NGBmpY=NGBmpY;
        LData.AddX=0;
        LData.AddY=0;
        LData.FLines=&GetArea();
        SearchAnalyzeNGHole2(&LData,x,y,&NGBmp[(y-GetArea().GetMinY())*NGBmpX]);
        if(LData.NGNumb>OKDot){
            Cx=LData.AddX/LData.NGNumb;
            Cy=LData.AddY/LData.NGNumb;
			Sum=LData.NGNumb;
		}
	}
	return(LData.NGNumb);        
}


bool	ColorBlockItem::CheckOnNG(int mx,int my ,int hx ,int hy
				,int TmpBrightWidthRL,int TmpBrightWidthRH , int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
				,int TmpBrightWidthGL,int TmpBrightWidthGH , int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
				,int TmpBrightWidthBL,int TmpBrightWidthBH , int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,short &Error
				,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
				,WORD RMinNGCountL,WORD RMinNGCountH
				,WORD GMinNGCountL,WORD GMinNGCountH
				,WORD BMinNGCountL,WORD BMinNGCountH
				,ThresholdMode NBMode)
{
	int	MaxNGInBlock=-1;
	SumL=0;
	SumH=0;
    int	RNumb=0;
	const	ColorBlockThreshold	*RThr=GetThresholdR();

	if(RThr->PointMove.ModeAdjustable==true){
		EnAverage(mx,my
				,TmpBrightWidthRL,TmpBrightWidthRH
				,TmpBrightWidthGL,TmpBrightWidthGH
				,TmpBrightWidthBL,TmpBrightWidthBH
				,TargetBuff);
	}
    if(TmpBrightWidthRL<0)    TmpBrightWidthRL=0;
    if(TmpBrightWidthRH>255)  TmpBrightWidthRH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthRH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthRL=0;

    if(TmpBrightWidthGL<0)    TmpBrightWidthGL=0;
    if(TmpBrightWidthGH>255)  TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthGL=0;

    if(TmpBrightWidthBL<0)    TmpBrightWidthBL=0;
    if(TmpBrightWidthBH>255)  TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthBL=0;

    int LLevel; //=((ThS-ThA+127+ThOffset)>>8)+BrightOffset;
    int HLevel; //=((ThS+ThA+127+ThOffset)>>8)+BrightOffset;
    uchar   BackBuffH[10000];
    uchar   BackBuffL[10000];

	FlexArea	*fa=&GetArea();
    int starty =fa->GetFLineAbsY(0);

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

    BYTE   *pMapH;
    BYTE   *pMapL;
    if(LByte>sizeof(BackBuffH))
        pMapH=new BYTE[LByte];
    else
        pMapH=BackBuffH;

    if(LByte>sizeof(BackBuffL))
        pMapL=new BYTE[LByte];
    else
        pMapL=BackBuffL;

	memset(pMapH,0,LByte);
	memset(pMapL,0,LByte);

    if(RThr->PointMove.ModeDiffer==false){
        CheckOnNGInner1(mx+hx ,my+hy
						,TmpBrightWidthRL,TmpBrightWidthRH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,*TargetBuff[0]);
        }
    else{
        CheckOnNGInner2(mx+hx ,my+hy
						,TmpBrightWidthRL,TmpBrightWidthRH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,*MasterBuff[0] ,*TargetBuff[0]);
        }

	int iSumL=0;
	int iSumH=0;
	int	RHCount=0;
	int	RLCount=0;
	int	GHCount=0;
	int	GLCount=0;
	int	BHCount=0;
	int	BLCount=0;

	bool	DrawResultDetail=GetLayersBase()->GetParamGlobal()->DrawResultDetail;
	uchar   *BackPointer[10000];
	uchar   **BackDim;
	if(Ly<sizeof(BackPointer)/sizeof(BackPointer[0])){
		BackDim=BackPointer;
	}
	else{
		BackDim=new uchar *[Ly];
	}

    BYTE   *pL=pMapL;
    for(int y=0;y<Ly;y++,pL+=Lx){
		BackDim[y]=pL;
	}
	PureFlexAreaListContainer LFPack;
	PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack,MaxNGInBlock,false);
	for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;p=p->GetNext()){
		SumL	=p->GetPatternByte();
		int	NGLen	=max(p->GetWidth(),p->GetHeight());
		if(SumL>OKDotRL && NGLen>OKLengthRL){
			//?m?f?I?e??
			int	Cx,Cy;
			iSumL+=SumL;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->result =0x20000;	//?????q?ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1(SumL);
			r->SetResult2(NGLen);
			LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
			if(LNGType!=NULL){
				ColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
				if(BL!=NULL){
					r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
				}
			}
			r->NGShape.SuckFrom(*p);
			PosList.AppendList(r);
			RNumb++;
			Error |= 0x10;	//?????A?m?f
			RLCount++;
		}
		else if(DrawResultDetail==true){
			//?n?j???a?A?P?x?A???o??E???e??
			int	Cx,Cy;
			iSumL+=SumL;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->SetResult1(SumL);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			if(SumL>OKDotRL){
				r->result =0x30;	//?????q?A?P?x?I?m?f?C??E?3?I?n?j
			}
			else if(NGLen>OKLengthRL){
				r->result =0x20;	//?????q?A?P?x?I?m?f?C?E?I?I?n?j
			}
			else{
				r->result =0x10;	//?????q?A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
			}
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			PosList.AppendList(r);
		}
	}
    BYTE   *pH=pMapH;
    for(int y=0;y<Ly;y++,pH+=Lx){
		BackDim[y]=pH;
	}
	PureFlexAreaListContainer HFPack;
	PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack,MaxNGInBlock,false);
	for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;p=p->GetNext()){
		SumH	=p->GetPatternByte();
		int	NGLen	=max(p->GetWidth(),p->GetHeight());
		if(SumH>OKDotRH && NGLen>OKLengthRH){
			//?m?f?I?e??
			int	Cx,Cy;
			iSumH+=SumH;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->result =0x30000;	//?????q?ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1(SumH);
			r->SetResult2(NGLen);
			LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
			if(LNGType!=NULL){
				ColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
				if(BL!=NULL){
					r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
				}
			}
			r->NGShape.SuckFrom(*p);
			PosList.AppendList(r);
			RNumb++;
			Error |= 0x20;	//?????A?m?f
			RHCount++;
		}
		else if(DrawResultDetail==true){
			//?n?j???a?A?P?x?A???o??E???e??
			int	Cx,Cy;
			iSumH+=SumH;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->SetResult1(SumH);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			if(SumH>OKDotRH){
				r->result =0x130;	//?????q?A?P?x?I?m?f?C?E?I?I?m?f
			}
			else if(NGLen>OKLengthRH){
				r->result =0x120;	//?????q?A?P?x?I?m?f?C??E?3?I?m?f
			}
			else{
				r->result =0x110;	//?????q?A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
			}
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			PosList.AppendList(r);
		}
	}
	if(RNumb==0){
		memset(pMapH,0,LByte);
		memset(pMapL,0,LByte);

	    if(RThr->PointMove.ModeDiffer==false){
		    CheckOnNGInner1(mx+hx ,my+hy
							,TmpBrightWidthGL,TmpBrightWidthGH
				            ,pMapL,pMapH
					        ,Lx ,Ly ,LByte,starty
							,*TargetBuff[1]);
	    }
		else{
			CheckOnNGInner2(mx+hx ,my+hy
							,TmpBrightWidthGL,TmpBrightWidthGH
					        ,pMapL,pMapH
						    ,Lx ,Ly ,LByte,starty
							,*MasterBuff[1] ,*TargetBuff[1]);
	    }

		iSumL=0;
		iSumH=0;
		HFPack.RemoveAll();
		LFPack.RemoveAll();
	    pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack,MaxNGInBlock,false);
		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;p=p->GetNext()){
			SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumL>OKDotGL && NGLen>OKLengthGL){
				//?m?f?I?e??
				int	Cx,Cy;
				iSumL+=SumL;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->result =0x120000;	//?????f?ANG
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
				if(LNGType!=NULL){
					ColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
					if(BL!=NULL){
						r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
					}
				}
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				RNumb++;
				Error |= 0x10;	//?????A?m?f
				GLCount++;
			}
			else if(DrawResultDetail==true){
				//?n?j???a?A?P?x?A???o??E???e??
				int	Cx,Cy;
				iSumL+=SumL;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				r->NGShape=*p;
				if(SumL>OKDotGL){
					r->result =0x1030;	//?????f?A?P?x?I?m?f?C??E?3?I?n?j
				}
				else if(NGLen>OKLengthGL){
					r->result =0x1020;	//?????f?A?P?x?I?m?f?C?E?I?I?n?j
				}
				else{
					r->result =0x1010;	//?????f?A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
			}
		}
		pH=pMapH;
	    for(int y=0;y<Ly;y++,pH+=Lx){
			BackDim[y]=pH;
		}
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack,MaxNGInBlock,false);
		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;p=p->GetNext()){
			SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumH>OKDotGH && NGLen>OKLengthGH){
				//?m?f?I?e??
				int	Cx,Cy;
				iSumH+=SumH;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->result =0x130000;	//?????f?ANG
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
				LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
				if(LNGType!=NULL){
					ColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
					if(BL!=NULL){
						r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
					}
				}
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				RNumb++;
				Error |= 0x20;	//?????A?m?f
				GHCount++;
			}
			else if(DrawResultDetail==true){
				//?n?j???a?A?P?x?A???o??E???e??
				int	Cx,Cy;
				iSumH+=SumH;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
				r->NGShape=*p;
				if(SumH>OKDotGH){
					r->result =0x1130;	//?????f?A?P?x?I?m?f?C?E?I?I?m?f
				}
				else if(NGLen>OKLengthGH){
					r->result =0x1120;	//?????f?A?P?x?I?m?f?C??E?3?I?m?f
				}
				else{
					r->result =0x1110;	//?????f?A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
			}
		}
	}
	if(RNumb==0){
		memset(pMapH,0,LByte);
		memset(pMapL,0,LByte);

	    if(RThr->PointMove.ModeDiffer==false){
		    CheckOnNGInner1(mx+hx ,my+hy
							,TmpBrightWidthBL,TmpBrightWidthBH
				            ,pMapL,pMapH
					        ,Lx ,Ly ,LByte,starty
							,*TargetBuff[2]);
	    }
		else{
			CheckOnNGInner2(mx+hx ,my+hy
							,TmpBrightWidthBL,TmpBrightWidthBH
					        ,pMapL,pMapH
						    ,Lx ,Ly ,LByte,starty
							,*MasterBuff[2] ,*TargetBuff[2]);
	    }

		iSumL=0;
		iSumH=0;
		HFPack.RemoveAll();
		LFPack.RemoveAll();
	    pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack,MaxNGInBlock,false);
		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;p=p->GetNext()){
			SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumL>OKDotBL && NGLen>OKLengthBL){
				//?m?f?I?e??
				int	Cx,Cy;
				iSumL+=SumL;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->result =0x220000;	//?????a?ANG
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
				if(LNGType!=NULL){
					ColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
					if(BL!=NULL){
						r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
					}
				}
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				RNumb++;
				Error |= 0x10;	//?????A?m?f
				BLCount++;
			}
			else if(DrawResultDetail==true){
				//?n?j???a?A?P?x?A???o??E???e??
				int	Cx,Cy;
				iSumL+=SumL;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				r->NGShape=*p;
				if(SumL>OKDotBL){
					r->result =0x2030;	//?????a?A?P?x?I?m?f?C??E?3?I?n?j
				}
				else if(NGLen>OKLengthBL){
					r->result =0x2020;	//?????a?A?P?x?I?m?f?C?E?I?I?n?j
				}
				else{
					r->result =0x2010;	//?????a?A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
			}
		}
		pH=pMapH;
	    for(int y=0;y<Ly;y++,pH+=Lx){
			BackDim[y]=pH;
		}
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack,MaxNGInBlock,false);
		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;p=p->GetNext()){
			SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumH>OKDotBH && NGLen>OKLengthBH){
				//?m?f?I?e??
				int	Cx,Cy;
				iSumH+=SumH;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->result =0x230000;	//?????a?ANG
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
				LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
				if(LNGType!=NULL){
					ColorBlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
					if(BL!=NULL){
						r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
					}
				}
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				RNumb++;
				Error |= 0x20;	//?????A?m?f
				BHCount++;
			}
			else if(DrawResultDetail==true){
				//?n?j???a?A?P?x?A???o??E???e??
				int	Cx,Cy;
				iSumH+=SumH;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
				r->NGShape=*p;
				if(SumH>OKDotBH){
					r->result =0x2130;	//?????a?A?P?x?I?m?f?C?E?I?I?m?f
				}
				else if(NGLen>OKLengthBH){
					r->result =0x2120;	//?????a?A?P?x?I?m?f?C??E?3?I?m?f
				}
				else{
					r->result =0x2110;	//?????a?A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
			}
		}
	}
	if(BackPointer!=BackDim){
		delete	[]BackDim;
	}




	/*
    BYTE   *pL=pMapL;
    BYTE   *pH=pMapH;
    for(int y=0;y<Ly;y++,pL+=Lx,pH+=Lx){
        BYTE   *qL=pL;
        BYTE   *qH=pH;
        for(int x=0;x<Lx;x++,qL++,qH++){
			if(*qL!=0){
	            for(int k=0;k<8;k++){
		            if(((*qL) & (0x80>>k))==0)
			            continue;
					int	Cx,Cy;
					AnalyzeNGHole(mx+hx ,my+hy
								,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
							    ,TmpBrightWidthRL ,TmpBrightWidthRH
								,pMapL ,Lx ,Ly
								,Cx,Cy
								,OKDotRL,SumL
								,*MasterBuff[0],*TargetBuff[0]);
	
					if(SumL>OKDotRL){
						ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
						r->result1=SumL;
						iSumL+=SumL;
						PosList.AppendList(r);
						RNumb++;
						Error |= 0x10;	//?????A?m?f
						RLCount++;
					}
				}
            }
			else if(*qH!=0){
	            for(int k=0;k<8;k++){
		            if(((*qH) & (0x80>>k))==0)
			            continue;
					int	Cx,Cy;
					AnalyzeNGHole(mx+hx ,my+hy
								,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
							    ,TmpBrightWidthRL ,TmpBrightWidthRH
								,pMapH ,Lx ,Ly
								,Cx,Cy
								,OKDotRH,SumH
								,*MasterBuff[0],*TargetBuff[0]);

					if(SumH>OKDotRH){
						ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
						r->result2=SumH;
						iSumH+=SumH;
						PosList.AppendList(r);
						RNumb++;
						Error |= 0x20;	//?????A?m?f
						RHCount++;
					}
				}
			}
        }
	}
	if(RNumb==0){
		memset(pMapH,0,LByte);
		memset(pMapL,0,LByte);

	    if(RThr->PointMove.ModeDiffer==false){
		    CheckOnNGInner1(mx+hx ,my+hy
							,TmpBrightWidthGL,TmpBrightWidthGH
				            ,pMapL,pMapH
					        ,Lx ,Ly ,LByte,starty
							,*TargetBuff[1]);
	        }
		else{
			CheckOnNGInner2(mx+hx ,my+hy
							,TmpBrightWidthGL,TmpBrightWidthGH
					        ,pMapL,pMapH
						    ,Lx ,Ly ,LByte,starty
							,*MasterBuff[1] ,*TargetBuff[1]);
	        }

		iSumL=0;
		iSumH=0;
		pL=pMapL;
		pH=pMapH;
		for(int y=0;y<Ly;y++,pL+=Lx,pH+=Lx){
			BYTE   *qL=pL;
	        BYTE   *qH=pH;
		    for(int x=0;x<Lx;x++,qL++,qH++){
				if(*qL!=0){
				    for(int k=0;k<8;k++){
					    if(((*qL) & (0x80>>k))==0)
						    continue;
						int	Cx,Cy;
						AnalyzeNGHole(mx+hx ,my+hy
									,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
								    ,TmpBrightWidthGL ,TmpBrightWidthGH
									,pMapL ,Lx ,Ly
									,Cx,Cy
									,OKDotGL,SumL
									,*MasterBuff[1],*TargetBuff[1]);
	
						if(SumL>OKDotGL){
							ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
							r->result1=SumL;
							iSumL+=SumL;
							PosList.AppendList(r);
							RNumb++;
							Error |= 0x10;	//?????A?m?f
							GLCount++;
						}
					}
			    }
				else if(*qH!=0){
					for(int k=0;k<8;k++){
						if(((*qH) & (0x80>>k))==0)
							continue;
						int	Cx,Cy;
						AnalyzeNGHole(mx+hx ,my+hy
									,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
								    ,TmpBrightWidthGL ,TmpBrightWidthGH
									,pMapH ,Lx ,Ly
									,Cx,Cy
									,OKDotGH,SumH
									,*MasterBuff[1],*TargetBuff[1]);

						if(SumH>OKDotGH){
							ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
							r->result2=SumH;
							iSumH+=SumH;
							PosList.AppendList(r);
							RNumb++;
							Error |= 0x20;	//?????A?m?f
							GHCount++;
						}
					}
				}
			}
        }
	}
	if(RNumb==0){
		memset(pMapH,0,LByte);
		memset(pMapL,0,LByte);

	    if(RThr->PointMove.ModeDiffer==false){
		    CheckOnNGInner1(mx+hx ,my+hy
							,TmpBrightWidthBL,TmpBrightWidthBH
				            ,pMapL,pMapH
					        ,Lx ,Ly ,LByte,starty
							,*TargetBuff[2]);
	        }
		else{
			CheckOnNGInner2(mx+hx ,my+hy
							,TmpBrightWidthBL,TmpBrightWidthBH
					        ,pMapL,pMapH
						    ,Lx ,Ly ,LByte,starty
							,*MasterBuff[2] ,*TargetBuff[2]);
	        }

		iSumL=0;
		iSumH=0;
		pL=pMapL;
		pH=pMapH;
		for(int y=0;y<Ly;y++,pL+=Lx,pH+=Lx){
			BYTE   *qL=pL;
	        BYTE   *qH=pH;
		    for(int x=0;x<Lx;x++,qL++,qH++){
				if(*qL!=0){
				    for(int k=0;k<8;k++){
					    if(((*qL) & (0x80>>k))==0)
						    continue;
						int	Cx,Cy;
						AnalyzeNGHole(mx+hx ,my+hy
									,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
								    ,TmpBrightWidthBL ,TmpBrightWidthBH
									,pMapL ,Lx ,Ly
									,Cx,Cy
									,OKDotBL,SumL
									,*MasterBuff[2],*TargetBuff[2]);
	
						if(SumL>OKDotBL){
							ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
							r->result1=SumL;
							iSumL+=SumL;
							PosList.AppendList(r);
							RNumb++;
							Error |= 0x10;	//?????A?m?f
							BLCount++;
						}
					}
			    }
				else if(*qH!=0){
					for(int k=0;k<8;k++){
						if(((*qH) & (0x80>>k))==0)
							continue;
						int	Cx,Cy;
						AnalyzeNGHole(mx+hx ,my+hy
									,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
								    ,TmpBrightWidthBL ,TmpBrightWidthBH
									,pMapH ,Lx ,Ly
									,Cx,Cy
									,OKDotBH,SumH
									,*MasterBuff[2],*TargetBuff[2]);

						if(SumH>OKDotBH){
							ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
							r->result2=SumH;
							iSumH+=SumH;
							PosList.AppendList(r);
							RNumb++;
							Error |= 0x20;	//?????A?m?f
							BHCount++;
						}
					}
				}
			}
        }
	}
	*/

    if(pMapH!=BackBuffH)
        delete  []pMapH;
    if(pMapL!=BackBuffL)
        delete  []pMapL;

	SumH=iSumH;
	SumL=iSumL;
	if(RLCount<RMinNGCountL && RHCount<RMinNGCountH
	&& GLCount<GMinNGCountL && GHCount<GMinNGCountH
	&& BLCount<BMinNGCountL && BHCount<BMinNGCountH){
		return true;
	}
	if(RNumb!=0)
		return false;

	return true;
}

bool	ColorBlockItem::CheckOnNGAll(int mx,int my ,int hx ,int hy
				,int TmpBrightWidthRL,int TmpBrightWidthRH , int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
				,int TmpBrightWidthGL,int TmpBrightWidthGH , int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
				,int TmpBrightWidthBL,int TmpBrightWidthBH , int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,short &Error
				,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
				,WORD RMinNGCountL,WORD RMinNGCountH
				,WORD GMinNGCountL,WORD GMinNGCountH
				,WORD BMinNGCountL,WORD BMinNGCountH
				,ThresholdMode NBMode)
{
	int	MaxNGInBlock=-1;
	SumL=0;
	SumH=0;
    int	RNumb=0;
	const	ColorBlockThreshold	*RThr=GetThresholdR();

	if(RThr->PointMove.ModeAdjustable==true){
		EnAverage(mx,my
				,TmpBrightWidthRL,TmpBrightWidthRH
				,TmpBrightWidthGL,TmpBrightWidthGH
				,TmpBrightWidthBL,TmpBrightWidthBH
				,TargetBuff);
	}
    if(TmpBrightWidthRL<0)    TmpBrightWidthRL=0;
    if(TmpBrightWidthRH>255)  TmpBrightWidthRH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthRH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthRL=0;

    if(TmpBrightWidthGL<0)    TmpBrightWidthGL=0;
    if(TmpBrightWidthGH>255)  TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthGH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthGL=0;

    if(TmpBrightWidthBL<0)    TmpBrightWidthBL=0;
    if(TmpBrightWidthBH>255)  TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeWhiteMask==true)
        TmpBrightWidthBH=255;
    if(RThr->PointMove.ModeBlackMask==true)
        TmpBrightWidthBL=0;

    int LLevel; //=((ThS-ThA+127+ThOffset)>>8)+BrightOffset;
    int HLevel; //=((ThS+ThA+127+ThOffset)>>8)+BrightOffset;
    uchar   BackBuffH[10000];
    uchar   BackBuffL[10000];

	FlexArea	*fa=&GetArea();
    int starty =fa->GetFLineAbsY(0);

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

    BYTE   *pMapH;
    BYTE   *pMapL;
    if(LByte>sizeof(BackBuffH))
        pMapH=new BYTE[LByte];
    else
        pMapH=BackBuffH;

    if(LByte>sizeof(BackBuffL))
        pMapL=new BYTE[LByte];
    else
        pMapL=BackBuffL;

	memset(pMapH,0,LByte);
	memset(pMapL,0,LByte);

    if(RThr->PointMove.ModeDiffer==false){
        CheckOnNGInner1All(mx+hx ,my+hy
						,TmpBrightWidthRL,TmpBrightWidthRH
						,TmpBrightWidthGL,TmpBrightWidthGH
						,TmpBrightWidthBL,TmpBrightWidthBH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,TargetBuff);
        }
    else{
        CheckOnNGInner2All(mx+hx ,my+hy
						,TmpBrightWidthRL,TmpBrightWidthRH
						,TmpBrightWidthGL,TmpBrightWidthGH
						,TmpBrightWidthBL,TmpBrightWidthBH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,MasterBuff ,TargetBuff);
        }

	int iSumL=0;
	int iSumH=0;
	int	RHCount=0;
	int	RLCount=0;
	int	GHCount=0;
	int	GLCount=0;
	int	BHCount=0;
	int	BLCount=0;

	bool	DrawResultDetail=GetLayersBase()->GetParamGlobal()->DrawResultDetail;
	uchar   *BackPointer[10000];
	uchar   **BackDim;
	if(Ly<sizeof(BackPointer)/sizeof(BackPointer[0])){
		BackDim=BackPointer;
	}
	else{
		BackDim=new uchar *[Ly];
	}

    BYTE   *pL=pMapL;
    for(int y=0;y<Ly;y++,pL+=Lx){
		BackDim[y]=pL;
	}
	PureFlexAreaListContainer LFPack;
	PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack,MaxNGInBlock,false);
	for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;p=p->GetNext()){
		SumL	=p->GetPatternByte();
		int	NGLen	=max(p->GetWidth(),p->GetHeight());
		if(SumL>OKDotRL && NGLen>OKLengthRL){
			//?m?f?I?e??
			int	Cx,Cy;
			iSumL+=SumL;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->result =0x40000;	//?????ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1(SumL);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			PosList.AppendList(r);
			RNumb++;
			Error |= 0x10;	//?????A?m?f
			RLCount++;
		}
		else if(DrawResultDetail==true){
			//?n?j???a?A?P?x?A???o??E???e??
			int	Cx,Cy;
			iSumL+=SumL;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->SetResult1(SumL);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			if(SumL>OKDotRL){
				r->result =0x60;	//?????A?P?x?I?m?f?C??E?3?I?n?j
			}
			else if(NGLen>OKLengthRL){
				r->result =0x50;	//?????A?P?x?I?m?f?C?E?I?I?n?j
			}
			else{
				r->result =0x40;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
			}
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			PosList.AppendList(r);
		}
	}
    BYTE   *pH=pMapH;
    for(int y=0;y<Ly;y++,pH+=Lx){
		BackDim[y]=pH;
	}
	PureFlexAreaListContainer HFPack;
	PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack,MaxNGInBlock,false);
	for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;p=p->GetNext()){
		SumH	=p->GetPatternByte();
		int	NGLen	=max(p->GetWidth(),p->GetHeight());
		if(SumH>OKDotRH && NGLen>OKLengthRH){
			//?m?f?I?e??
			int	Cx,Cy;
			iSumH+=SumH;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->result =0x50000;	//?????ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1(SumH);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			PosList.AppendList(r);
			RNumb++;
			Error |= 0x20;	//?????A?m?f
			RHCount++;
		}
		else if(DrawResultDetail==true){
			//?n?j???a?A?P?x?A???o??E???e??
			int	Cx,Cy;
			iSumH+=SumH;
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new ResultPosList(Cx,Cy ,hx,hy);
			r->SetResult1(SumH);
			r->SetResult2(NGLen);
			r->NGShape=*p;
			if(SumH>OKDotRH){
				r->result =0x160;	//?????A?P?x?I?m?f?C?E?I?I?m?f
			}
			else if(NGLen>OKLengthRH){
				r->result =0x150;	//?????A?P?x?I?m?f?C??E?3?I?m?f
			}
			else{
				r->result =0x140;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
			}
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			PosList.AppendList(r);
		}
	}

    if(pMapH!=BackBuffH)
        delete  []pMapH;
    if(pMapL!=BackBuffL)
        delete  []pMapL;

	SumH=iSumH;
	SumL=iSumL;
	if(RLCount<RMinNGCountL && RHCount<RMinNGCountH
	&& GLCount<GMinNGCountL && GHCount<GMinNGCountH
	&& BLCount<BMinNGCountL && BHCount<BMinNGCountH){
		return true;
	}
	if(RNumb!=0)
		return false;

	return true;
}

void	ColorBlockItem::CheckOnNGInner1(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,ImageBuffer &TargetBuff)
{
	ImageBuffer &a=TargetBuff;
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
		BYTE	*p=a.GetY(dy+Y)+dx+X;
		BYTE	*qL=&(pMapL[Lx*mdy+((X-fa->GetMinX())>>3)]);
		BYTE	*qH=&(pMapH[Lx*mdy+((X-fa->GetMinX())>>3)]);
		unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));

		for(int x=0;x<Numb;x+=8){
			int N=8;
			if(x+8>=Numb)
				N=Numb-x;
			for(int k=0;k<N;k++,p++){
				if(qL>&pMapL[LByte])
					break;
				if(qL>=pMapL){
					if(*p<LLevel)
						*qL|=(BYTE)Mask;
					if(HLevel<*p){
						*qH|=(BYTE)Mask;
					}
				}
				Mask=_rotr(Mask,1);
				if((Mask &0x80)!=0){
					qL++;
					qH++;
				}
			}
		}
	}
}

void	ColorBlockItem::CheckOnNGInner1All(int dx ,int dy
                                    ,int LLevelR ,int HLevelR
                                    ,int LLevelG ,int HLevelG
                                    ,int LLevelB ,int HLevelB
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,ImageBuffer *TargetBuff[])
{
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
		BYTE	*pR=TargetBuff[0]->GetY(dy+Y)+dx+X;
		BYTE	*pG=TargetBuff[1]->GetY(dy+Y)+dx+X;
		BYTE	*pB=TargetBuff[2]->GetY(dy+Y)+dx+X;
		BYTE	*qL=&(pMapL[Lx*mdy+((X-fa->GetMinX())>>3)]);
		BYTE	*qH=&(pMapH[Lx*mdy+((X-fa->GetMinX())>>3)]);
		unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));

		for(int x=0;x<Numb;x+=8){
			int N=8;
			if(x+8>=Numb)
				N=Numb-x;
			for(int k=0;k<N;k++,pR++,pG++,pB++){
				if(qL>&pMapL[LByte])
					break;
				if(qL>=pMapL){
					if(*pR<LLevelR)
						*qL|=(BYTE)Mask;
					if(HLevelR<*pR){
						*qH|=(BYTE)Mask;
					}
					if(*pG<LLevelG)
						*qL|=(BYTE)Mask;
					if(HLevelG<*pG){
						*qH|=(BYTE)Mask;
					}
					if(*pB<LLevelB)
						*qL|=(BYTE)Mask;
					if(HLevelB<*pB){
						*qH|=(BYTE)Mask;
					}
				}
				Mask=_rotr(Mask,1);
				if((Mask &0x80)!=0){
					qL++;
					qH++;
				}
			}
		}
	}
}

void	ColorBlockItem::CheckOnNGInner2(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,ImageBuffer &MasterBuff,ImageBuffer &TargetBuff)
{
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	ImageBuffer &a1=MasterBuff;
	ImageBuffer &a2=TargetBuff;

	for(int i=0;i<fa->GetFLineLen();i++){
		int y =fa->GetFLineAbsY(i);
		if(y<0 || y>=YLen)
			continue;
		if(y+dy<0 || y+dy>=YLen)
			continue;
		int x1=fa->GetFLineLeftX(i);
		int x2=fa->GetFLineLeftX(i)+dx;
		int Numb1=fa->GetFLineNumb(i);
		int Numb2=fa->GetFLineNumb(i);
		if(x1<0){
			x2=x2-x1;
			Numb1=Numb1+x1;
			Numb2=Numb2+x1;
			x1=0;
		}
		if(x1+Numb1>=XLen){
			int d=x1+Numb1 - XLen;
			Numb1=Numb1-d;
			Numb2=Numb2-d;
		}
		if(x2<0){
			x1=x1-x2;
			Numb1=Numb1+x2;
			Numb2=Numb2+x2;
			x2=0;
		}
		if(x2+Numb2>=XLen){
			int d=x2+Numb2 - XLen;
			Numb1=Numb1-d;
			Numb2=Numb2-d;
		}
		if(Numb1<=0 || Numb2<=0)
			continue;
		int Numb=min(Numb1,Numb2);

		int px=x1-fa->GetMinX();
		int mdy=y-starty;
		BYTE	*p1=a1.GetY(y)   +x1;
		BYTE	*p2=a2.GetY(y+dy)+x2;
		BYTE	*qL=&pMapL[Lx*mdy+((x1-fa->GetMinX())>>3)];
		BYTE	*qH=&pMapH[Lx*mdy+((x1-fa->GetMinX())>>3)];
		unsigned int	Mask=(0x8080808080808080u>>((x1-fa->GetMinX())&7));

		for(int x=0;x<Numb;x+=8){
			int N=8;
			if(x+8>=Numb)
				N=Numb-x;
			for(int k=0;k<N;k++,p1++,p2++){
				int d=*p2-*p1;
				if(qL>&pMapL[LByte])
					break;
				if(qL>=pMapL){
					if(d<LLevel){
						*qL|=(BYTE)Mask;
					if(HLevel<d)
						*qH|=(BYTE)Mask;
					}
				}
				Mask=_rotr(Mask,1);
				if((Mask &0x80)!=0){
					qL++;
					qH++;
				}
			}
		}
	}
}

void	ColorBlockItem::CheckOnNGInner2All(int dx ,int dy
                                    ,int LLevelR ,int HLevelR
                                    ,int LLevelG ,int HLevelG
                                    ,int LLevelB ,int HLevelB
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,ImageBuffer *MasterBuff[],ImageBuffer *TargetBuff[])
{
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();

	for(int i=0;i<fa->GetFLineLen();i++){
		int y =fa->GetFLineAbsY(i);
		if(y<0 || y>=YLen)
			continue;
		if(y+dy<0 || y+dy>=YLen)
			continue;
		int x1=fa->GetFLineLeftX(i);
		int x2=fa->GetFLineLeftX(i)+dx;
		int Numb1=fa->GetFLineNumb(i);
		int Numb2=fa->GetFLineNumb(i);
		if(x1<0){
			x2=x2-x1;
			Numb1=Numb1+x1;
			Numb2=Numb2+x1;
			x1=0;
		}
		if(x1+Numb1>=XLen){
			int d=x1+Numb1 - XLen;
			Numb1=Numb1-d;
			Numb2=Numb2-d;
		}
		if(x2<0){
			x1=x1-x2;
			Numb1=Numb1+x2;
			Numb2=Numb2+x2;
			x2=0;
		}
		if(x2+Numb2>=XLen){
			int d=x2+Numb2 - XLen;
			Numb1=Numb1-d;
			Numb2=Numb2-d;
		}
		if(Numb1<=0 || Numb2<=0)
			continue;
		int Numb=min(Numb1,Numb2);

		int px=x1-fa->GetMinX();
		int mdy=y-starty;
		BYTE	*p1R=MasterBuff[0]->GetY(y)   +x1;
		BYTE	*p2R=TargetBuff[0]->GetY(y+dy)+x2;
		BYTE	*p1G=MasterBuff[1]->GetY(y)   +x1;
		BYTE	*p2G=TargetBuff[1]->GetY(y+dy)+x2;
		BYTE	*p1B=MasterBuff[2]->GetY(y)   +x1;
		BYTE	*p2B=TargetBuff[2]->GetY(y+dy)+x2;
		BYTE	*qL=&pMapL[Lx*mdy+((x1-fa->GetMinX())>>3)];
		BYTE	*qH=&pMapH[Lx*mdy+((x1-fa->GetMinX())>>3)];
		unsigned int	Mask=(0x8080808080808080u>>((x1-fa->GetMinX())&7));

		for(int x=0;x<Numb;x+=8){
			int N=8;
			if(x+8>=Numb)
				N=Numb-x;
			for(int k=0;k<N;k++,p1R++,p2R++,p1G++,p2G++,p1B++,p2B++){
				int dR=*p2R-*p1R;
				int dG=*p2G-*p1G;
				int dB=*p2B-*p1B;
				if(qL>&pMapL[LByte])
					break;
				if(qL>=pMapL){
					if(dR<LLevelR){
						*qL|=(BYTE)Mask;
					if(HLevelR<dR)
						*qH|=(BYTE)Mask;
					}
					if(dG<LLevelG){
						*qL|=(BYTE)Mask;
					if(HLevelG<dG)
						*qH|=(BYTE)Mask;
					}
					if(dB<LLevelB){
						*qL|=(BYTE)Mask;
					if(HLevelB<dB)
						*qH|=(BYTE)Mask;
					}
				}
				Mask=_rotr(Mask,1);
				if((Mask &0x80)!=0){
					qL++;
					qH++;
				}
			}
		}
	}
}

void	ColorBlockItem::CalcCenterBright(ImageBuffer *IBuff[] ,int mx ,int my 
										 ,WORD  &CenterBrightR,WORD  &CenterBrightG,WORD  &CenterBrightB)
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

		DTmpR=0;
		DTmpG=0;
		DTmpB=0;
		srcR=IBuff[0]->GetY(y)+x1;
		srcG=IBuff[1]->GetY(y)+x1;
		srcB=IBuff[2]->GetY(y)+x1;
		for(int x=0;x<XNumb;x++){
			DTmpR+=*(srcR+x);
			DTmpG+=*(srcG+x);
			DTmpB+=*(srcB+x);
		}
		N+=XNumb;
		DR+=DTmpR;
		DG+=DTmpG;
		DB+=DTmpB;
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

		DTmpR=0;
		DTmpG=0;
		DTmpB=0;
		srcR=IBuff[0]->GetY(y)+x1;
		srcG=IBuff[1]->GetY(y)+x1;
		srcB=IBuff[2]->GetY(y)+x1;
		for(int x=0;x<XNumb;x+=XSep){
			DTmpR+=*(srcR+x);
			DTmpG+=*(srcG+x);
			DTmpB+=*(srcB+x);
		}
		N+=(XNumb+XSep-1)/XSep;
		DR+=DTmpR;
		DG+=DTmpG;
		DB+=DTmpB;
	}
	if(N!=0){
		CenterBrightR=DR/N;
		CenterBrightG=DG/N;
		CenterBrightB=DB/N;
	}
	CenterBrightTargetR=CenterBrightR;
	CenterBrightTargetG=CenterBrightG;
	CenterBrightTargetB=CenterBrightB;
}

//==================================================================================
XYClass	*ColorBlockItem::GetSWayListFirst(int ThreadNo,int selfSearch)
{
	ColorBlockInPage *L=dynamic_cast<ColorBlockInPage *>(GetParent());
	if(L!=NULL){
		if(L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SWay.GetFirst()==NULL)
			L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SetSearchWay(selfSearch);
		return L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SWay.GetFirst();
	}
	return NULL;
}
void	ColorBlockItem::SetSWayListToTop(int ThreadNo,int selfSearch,XYClass *w)
{
	ColorBlockInPage *L=dynamic_cast<ColorBlockInPage *>(GetParent());
	if(L!=NULL)
		L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].ToTop(w);
}

