/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockInspectionAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "BlockFormResource.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"
#include <omp.h>
#include "immintrin.h"

const	int	MaxResultNGPointInBlock	=1000;
const	int	MaxReEntrantCount		=30000;
const	bool	MoreThreadInBlock=false;

WORD	CalcCenterBright(unsigned int BrightTable[256]);
void	IncreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my);
void	DecreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my);
void	MakeBrightList(FlexArea &A,int DotPerLine ,int MaxLines ,unsigned int BrightTable[256],ImageBuffer &IBuff,int Dx,int Dy
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
void	IncreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
void	DecreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

WORD	CalcCenterBright(unsigned short BrightTable[256]);
void	IncreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my);
void	DecreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my);
void	MakeBrightList(FlexArea &A,int DotPerLine ,int MaxLines ,unsigned short BrightTable[256],ImageBuffer &IBuff,int Dx,int Dy
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
void	IncreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
void	DecreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

bool    BlockItem::ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeEnabled==false){
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

    int	MinL=0x7FFFFFFF;
    int	MinH=0x7FFFFFFF;
    int dx=0;
    int dy=0;
	int SumL=0;
	int SumH=0;
	short	Error=0;
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	if(GetFromRental()==true){
		SelfSearch +=BBase->MoreSearchForRental;
	}

	if(SubBlock.GetFirst()!=NULL){
		L3Remove(mx ,my
                        ,SubFLines
                        ,SubFLineEdge
                        ,SubFLineInside);
		}
	int InsideSumL=0;
	int InsideSumH=0;
	Level3Inside(mx ,my
					,BrightWidthL ,BrightWidthH
					,InsideSumL,InsideSumH);

	for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
		if(SubBlock.GetFirst()!=NULL){
			L3Remove(mx+W->x ,my+W->y
                                ,SubFLines
                                ,SubFLineEdge
                                ,SubFLineInside);
		}
		int	TmpBrightWidthL=BrightWidthL;
		int	TmpBrightWidthH=BrightWidthH;
		if(RThr->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx+W->x ,my+W->y
						,TmpBrightWidthL,TmpBrightWidthH);
		}

		SumL=0;
		SumH=0;
		Level3Speedy(mx+W->x ,my+W->y
					,TmpBrightWidthL ,TmpBrightWidthH
					,SumL,SumH);
		//SumL+=InsideSumL;
		//SumH+=InsideSumH;
		if(((((SumL<=OKDotL || MaxNGDotL<=SumL) && (SumH<=OKDotH || MaxNGDotH<=SumH)) && BindBW==false)
		 || (((SumL+SumH)<=OKDotL || MaxNGDotL<=(SumL+SumH)) && BindBW==true))
		&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)==false){
			ResultBrightWidthL=TmpBrightWidthL;
			ResultBrightWidthH=TmpBrightWidthH;
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(W->x,W->y);
			Res->SetResult1(SumL);
			Res->SetResult2(SumH);
			Res->SetError(1);	//OK
			SetSWayListToTop(ThreadNo,SelfSearch,W);
			if(SubBlock.GetFirst()!=NULL){
				SetArea(SubFLines);
				FLineEdge   =SubFLineEdge;
				FLineInside =SubFLineInside;
			}
			return true;
		}
		if(BindBW==false && (SumL<=MinL && SumH<=MinH)){
			dx=W->x;
			dy=W->y;
			MinL=SumL;
			MinH=SumH;

			Error=0;
			if(SumL>OKDotL)
				Error |= 0x10;	//?????A?m?f
			if(SumH>OKDotH)
				Error |= 0x20;	//?????A?m?f
		}
		else if(BindBW==true && ((SumL+SumH)<=MinL)){
			dx=W->x;
			dy=W->y;
			MinL=SumL;
			MinH=SumH;

			Error=0;
			if(SumL>OKDotL)
				Error |= 0x10;	//?????A?m?f
			if(SumH>OKDotH)
				Error |= 0x20;	//?????A?m?f
		}
	}

	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		int MinSumL=99999999;
		int MinSumH=99999999;
		int	MinDx=0;
		int	MinDy=0;
		ResultPosListContainer	NowList;
		for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
			if(SubBlock.GetFirst()!=NULL){
				L3Remove(mx+W->x ,my+W->y
				        ,SubFLines
					    ,SubFLineEdge
						,SubFLineInside);
			}
			NowList.RemoveAll();
			short	iError=0;
			if(CheckOnNG(mx,my,W->x,W->y
						,BrightWidthL ,BrightWidthH
						,ResultBrightWidthL ,ResultBrightWidthH
						,OKDotL ,OKDotH
						,MaxNGDotL ,MaxNGDotH
						,SumL,SumH
						,NowList
						,OKLengthL ,OKLengthH
						,MinNGCountL,MinNGCountH,ConnectLen
						,Error
						,NBMode,BindBW
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
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
		Res->SetResult1(MinSumL);
		Res->SetResult2(MinSumH);
		Res->SetError(2 | Error);	//NG
		return false;
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new BlockResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1((DWORD)SumL);
	r->SetResult2((DWORD)SumH);
	r->result =0x30;
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(SumL);
	Res->SetResult2(SumH);
	Res->SetError(2);	//NG

	if(SubBlock.GetFirst()!=NULL){
		SetArea(SubFLines);
		FLineEdge   =SubFLineEdge;
		FLineInside =SubFLineInside;
	}
    return false;

}

struct	TmpStruct
{
	ResultInItemRoot *Res;
	BlockItem::ThresholdMode	NBMode;
	unsigned int	*BrightTable;
	bool			BindBW;
	int				OKDotL,OKDotH;
	int				mx,my;
    int				*MinL;
    int				*MinH;
    int				MinL2;
    int				MinH2;
	int				*dx;
	int				*dy;
	unsigned int	*MinBrightTable;
	int				*MinMx;
	int				*MinMy;
	BYTE			**DynamicMaskMap;
	int				DynamicMaskMapXByte;
	int				DynamicMaskMapYLen;
	int				ResultBrightWidthL;
	int				ResultBrightWidthH;
};

struct	TmpStruct_s
{
	ResultInItemRoot *Res;
	BlockItem::ThresholdMode	NBMode;
	unsigned short	*BrightTable;
	bool			BindBW;
	int				OKDotL,OKDotH;
	int				mx,my;
    int				*MinL;
    int				*MinH;
    int				MinL2;
    int				MinH2;
	int				*dx;
	int				*dy;
	unsigned short	*MinBrightTable;
	int				*MinMx;
	int				*MinMy;
	BYTE			**DynamicMaskMap;
	int				DynamicMaskMapXByte;
	int				DynamicMaskMapYLen;
	int				ResultBrightWidthL;
	int				ResultBrightWidthH;
};
unsigned int		CalcTableAddL(unsigned int BrightTable[] ,int BrightWidthL);
unsigned int		CalcTableAddH(unsigned int BrightTable[] ,int BrightWidthH);
unsigned int		CalcTableRange(unsigned int BrightTable[] ,int BrightWidthL,int BrightWidthH);

unsigned int		CalcTableAddL(unsigned short BrightTable[] ,int BrightWidthL);
unsigned int		CalcTableAddH(unsigned short BrightTable[] ,int BrightWidthH);
unsigned int		CalcTableRange(unsigned short BrightTable[] ,int BrightWidthL,int BrightWidthH);


bool	BlockItem::JudgeDir4(struct	TmpStruct &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeBlackMask==true)
		BrightWidthL=0;
	if(Thres->ThreshouldBag.PointMove.ModeWhiteMask==true)
		BrightWidthH=255;

	int	SumL;
	int	SumH;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false){
		SumL=CalcTableAddL(SData.BrightTable ,BrightWidthL);
		SumH=CalcTableAddH(SData.BrightTable ,BrightWidthH);
	}
	else{
		SumL=CalcTableRange(SData.BrightTable ,BrightWidthL ,BrightWidthH);
		SumH=SumL;
	}

	short	Error=0;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(((SData.BindBW==false && SumL<=SData.OKDotL && SumH<=SData.OKDotH) ||  (SData.BindBW==true && (SumL+SumH)<=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}

			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==true){
		if(((SData.BindBW==false && (SumL>=SData.OKDotL || SumH>=SData.OKDotH)) ||  (SData.BindBW==true && (SumL+SumH)>=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}

			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==true && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(SumL<=SData.OKDotL && SumH<=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else{
		if(SumL>=SData.OKDotL || SumH>=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	if((SumL*SumL+SumH*SumH)<=(((int64)SData.MinL2)+((int64)SData.MinH2))){
		*SData.dx=dx;
		*SData.dy=dy;
		SData.MinL2=SumL*SumL;
		SData.MinH2=SumH*SumH;
		*SData.MinL=SumL;
		*SData.MinH=SumH;

		Error=0;
		if(SumL>SData.OKDotL)
			Error |= 0x10;	//?????A?m?f
		if(SumH>SData.OKDotH)
			Error |= 0x20;	//?????A?m?f
		memcpy(SData.MinBrightTable,SData.BrightTable,sizeof(unsigned int)*256);
		*SData.MinMx=dx;
		*SData.MinMy=dy;
	}
	return false;
}
bool	BlockItem::JudgeDir4S(struct	TmpStruct &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeBlackMask==true)
		BrightWidthL=0;
	if(Thres->ThreshouldBag.PointMove.ModeWhiteMask==true)
		BrightWidthH=255;

	int	SumL;
	int	SumH;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false){
		SumL=CalcTableAddL(SData.BrightTable ,BrightWidthL);
		SumH=CalcTableAddH(SData.BrightTable ,BrightWidthH);
	}
	else{
		SumL=CalcTableRange(SData.BrightTable ,BrightWidthL ,BrightWidthH);
		SumH=SumL;
	}

	short	Error=0;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(((SData.BindBW==false && SumL<=SData.OKDotL && SumH<=SData.OKDotH) ||  (SData.BindBW==true && (SumL+SumH)<=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==true){
		if(((SData.BindBW==false && (SumL>=SData.OKDotL || SumH>=SData.OKDotH)) ||  (SData.BindBW==true && (SumL+SumH)>=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==true && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(SumL<=SData.OKDotL && SumH<=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else{
		if(SumL>=SData.OKDotL || SumH>=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	if((SumL*SumL+SumH*SumH)<=(((int64)SData.MinL2)+((int64)SData.MinH2))){
		*SData.dx=dx+*SData.MinMx;
		*SData.dy=dy+*SData.MinMy;
		SData.MinL2=SumL*SumL;
		SData.MinH2=SumH*SumH;
		*SData.MinL=SumL;
		*SData.MinH=SumH;

		Error=0;
		if(SumL>SData.OKDotL)
			Error |= 0x10;	//?????A?m?f
		if(SumH>SData.OKDotH)
			Error |= 0x20;	//?????A?m?f
		memcpy(SData.MinBrightTable,SData.BrightTable,sizeof(unsigned int)*256);
	}
	return false;
}

bool	BlockItem::JudgeDir4(struct	TmpStruct_s &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeBlackMask==true)
		BrightWidthL=0;
	if(Thres->ThreshouldBag.PointMove.ModeWhiteMask==true)
		BrightWidthH=255;

	int	SumL;
	int	SumH;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false){
		SumL=CalcTableAddL(SData.BrightTable ,BrightWidthL);
		SumH=CalcTableAddH(SData.BrightTable ,BrightWidthH);
	}
	else{
		SumL=CalcTableRange(SData.BrightTable ,BrightWidthL ,BrightWidthH);
		SumH=SumL;
	}

	short	Error=0;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(((SData.BindBW==false && SumL<=SData.OKDotL && SumH<=SData.OKDotH) ||  (SData.BindBW==true && (SumL+SumH)<=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}

			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==true){
		if(((SData.BindBW==false && (SumL>=SData.OKDotL || SumH>=SData.OKDotH)) ||  (SData.BindBW==true && (SumL+SumH)>=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}

			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==true && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(SumL<=SData.OKDotL && SumH<=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else{
		if(SumL>=SData.OKDotL || SumH>=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	if((SumL*SumL+SumH*SumH)<=(((int64)SData.MinL2)+((int64)SData.MinH2))){
		*SData.dx=dx;
		*SData.dy=dy;
		SData.MinL2=SumL*SumL;
		SData.MinH2=SumH*SumH;
		*SData.MinL=SumL;
		*SData.MinH=SumH;

		Error=0;
		if(SumL>SData.OKDotL)
			Error |= 0x10;	//?????A?m?f
		if(SumH>SData.OKDotH)
			Error |= 0x20;	//?????A?m?f
		memcpy(SData.MinBrightTable,SData.BrightTable,sizeof(unsigned short)*256);
		*SData.MinMx=dx;
		*SData.MinMy=dy;
	}
	return false;
}
bool	BlockItem::JudgeDir4S(struct	TmpStruct_s &SData,int BrightWidthL ,int BrightWidthH,int dx,int dy)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeBlackMask==true)
		BrightWidthL=0;
	if(Thres->ThreshouldBag.PointMove.ModeWhiteMask==true)
		BrightWidthH=255;

	int	SumL;
	int	SumH;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false){
		SumL=CalcTableAddL(SData.BrightTable ,BrightWidthL);
		SumH=CalcTableAddH(SData.BrightTable ,BrightWidthH);
	}
	else{
		SumL=CalcTableRange(SData.BrightTable ,BrightWidthL ,BrightWidthH);
		SumH=SumL;
	}

	short	Error=0;
	if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(((SData.BindBW==false && SumL<=SData.OKDotL && SumH<=SData.OKDotH) ||  (SData.BindBW==true && (SumL+SumH)<=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
			}
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==false && Thres->ThreshouldBag.PointMove.ModeInvertLogic==true){
		if(((SData.BindBW==false && (SumL>=SData.OKDotL || SumH>=SData.OKDotH)) ||  (SData.BindBW==true && (SumL+SumH)>=SData.OKDotL))){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
				MakeNGPointForInvertLogic(SData.mx+dx ,SData.my+dy
						,BrightWidthL,BrightWidthH
						,SData.Res,SData.NBMode
						,NULL,0,0);
				SData.Res->SetError(2);	//NG
			}
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else if(Thres->ThreshouldBag.PointMove.ModeOppositeRange==true && Thres->ThreshouldBag.PointMove.ModeInvertLogic==false){
		if(SumL<=SData.OKDotL && SumH<=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	else{
		if(SumL>=SData.OKDotL || SumH>=SData.OKDotH){
			SData.ResultBrightWidthL	=BrightWidthL;
			SData.ResultBrightWidthH	=BrightWidthH;
			SData.Res->SetAlignedXY(SData.mx,SData.my);
			SData.Res->SetItemSearchedXY(dx,dy);
			SData.Res->SetResult1(SumL);
			SData.Res->SetResult2(SumH);
			SData.Res->SetError(1);	//OK
			*SData.dx+=*SData.MinMx;
			*SData.dy+=*SData.MinMy;
			return true;
		}
	}
	if((SumL*SumL+SumH*SumH)<=(((int64)SData.MinL2)+((int64)SData.MinH2))){
		*SData.dx=dx+*SData.MinMx;
		*SData.dy=dy+*SData.MinMy;
		SData.MinL2=SumL*SumL;
		SData.MinH2=SumH*SumH;
		*SData.MinL=SumL;
		*SData.MinH=SumH;

		Error=0;
		if(SumL>SData.OKDotL)
			Error |= 0x10;	//?????A?m?f
		if(SumH>SData.OKDotH)
			Error |= 0x20;	//?????A?m?f
		memcpy(SData.MinBrightTable,SData.BrightTable,sizeof(unsigned short)*256);
	}
	return false;
}

bool	IsInsideArea(FlexArea &Area,int mx,int my,int SelfSearch,int DotPerLine ,int MaxLines)
{
	int	x1=Area.GetMinX()+mx-SelfSearch;
	int	y1=Area.GetMinY()+my-SelfSearch;
	int	x2=Area.GetMaxX()+mx+SelfSearch;
	int	y2=Area.GetMaxY()+my+SelfSearch;
	if(0<=x1 && x2<DotPerLine && 0<=y1 && y2<MaxLines)
		return true;
	return false;
}


bool    BlockItem::ExecuteProcessingInnerWithoutSubtractCalcA(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode ,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    MinL=0x7FFFFFFF;
    MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
	int SumL=0;
	int SumH=0;

	int	NarrowBlockW=12;
	int InsideSumL=0;
	int InsideSumH=0;
	int	SelfSearch=Thres->ThreshouldBag.SelfSearch;
	if(GetFromRental()==true){
		BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
		SelfSearch +=BBase->MoreSearchForRental;
	}

    dx=0;
    dy=0;
	short	Error=0;
	if(ConnectLen==0 && Thres->ThreshouldBag.PointMove.ModeAdoptBiggest==false){
		
		int	sTmpBrightWidthL=BrightWidthL;
		int	sTmpBrightWidthH=BrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,InsideSumL,InsideSumH);
		if(InsideSumL>OKDotL || InsideSumH>OKDotH){
			return false;
		}
		
		if(IsModeDir4()==true && IsInsideArea(GetArea(),mx,my,SelfSearch+1,GetDotPerLine(),GetMaxLines())==true){
			if((DynamicMaskMap==NULL || (Thres->ThreshouldBag.PointMove.ModeDynamicMask==false) 
			|| IsOnDynamicMasking(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx,my,SelfSearch)==false)){

				unsigned int	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned int	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=NULL;
				SData.DynamicMaskMapXByte	=0;
				SData.DynamicMaskMapYLen	=0;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				int	CurrentX=mx;
				int	CurrentY=my;

				A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
				memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					SelfSearch=SkipSearchDot;
					for(int L=0;L<=Thres->ThreshouldBag.SelfSearch;L+=SkipSearchDot){
						if(L!=0){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx;
							CurrentY=my-L;
						}
						int	tTmpBrightWidthL=BrightWidthL;
						int	tTmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
						}
						if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
						for(int x=SkipSearchDot;x<=L;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=-L+SkipSearchDot;y<=L;y+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=L-SkipSearchDot;x>=-L;x-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+x;
							CurrentY=my+L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=L-SkipSearchDot;y>=-L;y-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx-L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=-L+SkipSearchDot;x<=0;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
					}			
				}
				memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
				CurrentX=mx+MinMx;
				CurrentY=my+MinMy;

				for(int L=0;L<=SelfSearch;L++){
					if(L!=0){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
					}
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int x=1;x<=L;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=-L+1;y<=L;y++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=L-1;x>=-L;x--){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=L-1;y>=-L;y--){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=-L+1;x<=0;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
			else{
				unsigned int	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned int	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=DynamicMaskMap;
				SData.DynamicMaskMapXByte	=DynamicMaskMapXByte;
				SData.DynamicMaskMapYLen	=DynamicMaskMapYLen;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				int	CurrentX=mx;
				int	CurrentY=my;

				MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					SelfSearch=SkipSearchDot;
					for(int L=0;L<=Thres->ThreshouldBag.SelfSearch;L+=SkipSearchDot){
						if(L!=0){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx;
							CurrentY=my-L;
						}
						int	tTmpBrightWidthL=BrightWidthL;
						int	tTmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
						}
						if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
						for(int x=SkipSearchDot;x<=L;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=-L+SkipSearchDot;y<=L;y+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=L-SkipSearchDot;x>=-L;x-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+x;
							CurrentY=my+L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=L-SkipSearchDot;y>=-L;y-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx-L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=-L+SkipSearchDot;x<=0;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
					}			
				}
				memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
				CurrentX=mx+MinMx;
				CurrentY=my+MinMy;

				for(int L=0;L<=SelfSearch;L++){
					if(L!=0){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
					}
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int x=1;x<=L;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=-L+1;y<=L;y++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=L-1;x>=-L;x--){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=L-1;y>=-L;y--){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=-L+1;x<=0;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx+W->x ,my+W->y
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) ||  (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,W->y);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}

					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=W->y;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x ,my+W->y+t
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x ,my+W->y+t
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x,W->y+t);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x;
						dy=W->y+t;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x+t ,my+W->y
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,W->y);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=W->y;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else{
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					for(int s=-1;s<=1;s++){
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(mx+W->x+t ,my+W->y+s
										,TmpBrightWidthL,TmpBrightWidthH
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
		
						SumL=0;
						SumH=0;
						Level3Speedy(mx+W->x+t ,my+W->y+s
									,TmpBrightWidthL ,TmpBrightWidthH
									,SumL,SumH);
						//SumL+=InsideSumL;
						//SumH+=InsideSumH;
						if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
						&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
							ResultBrightWidthL=TmpBrightWidthL;
							ResultBrightWidthH=TmpBrightWidthH;
							Res->SetAlignedXY(mx,my);
							Res->SetItemSearchedXY(W->x+t,W->y+s);
							Res->SetResult1(SumL);
							Res->SetResult2(SumH);
							Res->SetError(1);	//OK
							SetSWayListToTop(ThreadNo,SelfSearch,W);
							if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
								MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							}
							return true;
						}
						if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
							dx=W->x+t;
							dy=W->y+s;
							MinL2=SumL*SumL;
							MinH2=SumH*SumH;
							MinL=SumL;
							MinH=SumH;
							Error=0;
							if(SumL>OKDotL)
								Error |= 0x10;	//?????A?m?f
							if(SumH>OKDotH)
								Error |= 0x20;	//?????A?m?f
						}
					}
				}
			}
		}
	}
	return false;
}

bool    BlockItem::ExecuteProcessingInnerWithoutSubtractCalcA_s(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode ,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    MinL=0x7FFFFFFF;
    MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
	int SumL=0;
	int SumH=0;

	int	NarrowBlockW=12;
	int InsideSumL=0;
	int InsideSumH=0;
	int	SelfSearch=Thres->ThreshouldBag.SelfSearch;
	if(GetFromRental()==true){
		BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
		SelfSearch +=BBase->MoreSearchForRental;
	}

    dx=0;
    dy=0;
	short	Error=0;
	if(ConnectLen==0 && Thres->ThreshouldBag.PointMove.ModeAdoptBiggest==false){
		
		int	sTmpBrightWidthL=BrightWidthL;
		int	sTmpBrightWidthH=BrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,InsideSumL,InsideSumH);
		if(InsideSumL>OKDotL || InsideSumH>OKDotH){
			return false;
		}
		
		if(IsModeDir4()==true && IsInsideArea(GetArea(),mx,my,SelfSearch+1,GetDotPerLine(),GetMaxLines())==true){
			if((DynamicMaskMap==NULL || (Thres->ThreshouldBag.PointMove.ModeDynamicMask==false) 
			|| IsOnDynamicMasking(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx,my,SelfSearch)==false)){

				unsigned short	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned short	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct_s	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=NULL;
				SData.DynamicMaskMapXByte	=0;
				SData.DynamicMaskMapYLen	=0;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				int	CurrentX=mx;
				int	CurrentY=my;

				A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
				memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					SelfSearch=SkipSearchDot;
					for(int L=0;L<=Thres->ThreshouldBag.SelfSearch;L+=SkipSearchDot){
						if(L!=0){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx;
							CurrentY=my-L;
						}
						int	tTmpBrightWidthL=BrightWidthL;
						int	tTmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
						}
						if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
						for(int x=SkipSearchDot;x<=L;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=-L+SkipSearchDot;y<=L;y+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=L-SkipSearchDot;x>=-L;x-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+x;
							CurrentY=my+L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=L-SkipSearchDot;y>=-L;y-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx-L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=-L+SkipSearchDot;x<=0;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
					}			
				}
				memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
				CurrentX=mx+MinMx;
				CurrentY=my+MinMy;

				for(int L=0;L<=SelfSearch;L++){
					if(L!=0){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
					}
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int x=1;x<=L;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=-L+1;y<=L;y++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=L-1;x>=-L;x--){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=L-1;y>=-L;y--){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=-L+1;x<=0;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
			else{
				unsigned short	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned short	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct_s	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=DynamicMaskMap;
				SData.DynamicMaskMapXByte	=DynamicMaskMapXByte;
				SData.DynamicMaskMapYLen	=DynamicMaskMapYLen;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				int	CurrentX=mx;
				int	CurrentY=my;

				MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					SelfSearch=SkipSearchDot;
					for(int L=0;L<=Thres->ThreshouldBag.SelfSearch;L+=SkipSearchDot){
						if(L!=0){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx;
							CurrentY=my-L;
						}
						int	tTmpBrightWidthL=BrightWidthL;
						int	tTmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
						}
						if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
						for(int x=SkipSearchDot;x<=L;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=-L+SkipSearchDot;y<=L;y+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=L-SkipSearchDot;x>=-L;x-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+x;
							CurrentY=my+L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int y=L-SkipSearchDot;y>=-L;y-=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx-L;
							CurrentY=my+y;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
						for(int x=-L+SkipSearchDot;x<=0;x+=SkipSearchDot){
							IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							CurrentX=mx+x;
							CurrentY=my-L;
							int	TmpBrightWidthL=BrightWidthL;
							int	TmpBrightWidthH=BrightWidthH;
							if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
								EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
							}
							if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
								ResultBrightWidthL=SData.ResultBrightWidthL;
								ResultBrightWidthH=SData.ResultBrightWidthH;
								return true;
							}
						}
					}			
				}
				memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
				CurrentX=mx+MinMx;
				CurrentY=my+MinMy;

				for(int L=0;L<=SelfSearch;L++){
					if(L!=0){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
					}
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-L)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int x=1;x<=L;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=-L+1;y<=L;y++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=L-1;x>=-L;x--){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int y=L-1;y>=-L;y--){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy+y;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,y)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					for(int x=-L+1;x<=0;x++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx+x;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,x,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx+W->x ,my+W->y
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) ||  (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,W->y);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}

					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=W->y;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x ,my+W->y+t
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x ,my+W->y+t
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x,W->y+t);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
					return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x;
						dy=W->y+t;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x+t ,my+W->y
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,W->y);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=W->y;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else{
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					for(int s=-1;s<=1;s++){
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(mx+W->x+t ,my+W->y+s
										,TmpBrightWidthL,TmpBrightWidthH
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
		
						SumL=0;
						SumH=0;
						Level3Speedy(mx+W->x+t ,my+W->y+s
									,TmpBrightWidthL ,TmpBrightWidthH
									,SumL,SumH);
						//SumL+=InsideSumL;
						//SumH+=InsideSumH;
						if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
						&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
							ResultBrightWidthL=TmpBrightWidthL;
							ResultBrightWidthH=TmpBrightWidthH;
							Res->SetAlignedXY(mx,my);
							Res->SetItemSearchedXY(W->x+t,W->y+s);
							Res->SetResult1(SumL);
							Res->SetResult2(SumH);
							Res->SetError(1);	//OK
							SetSWayListToTop(ThreadNo,SelfSearch,W);
							if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
								MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
							}
							return true;
						}
						if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
							dx=W->x+t;
							dy=W->y+s;
							MinL2=SumL*SumL;
							MinH2=SumH*SumH;
							MinL=SumL;
							MinH=SumH;
							Error=0;
							if(SumL>OKDotL)
								Error |= 0x10;	//?????A?m?f
							if(SumH>OKDotH)
								Error |= 0x20;	//?????A?m?f
						}
					}
				}
			}
		}
	}
	return false;
}

double	GetDifferencialSum2(FlexArea &Area ,ImageBuffer &Src,int dx,int dy,ImageBuffer &Dst,int Isolation
							,int L ,double Mul)
{
	double	SumS=0;
	int		SDCount=0;

	int	NLen=Area.GetFLineLen();
	#pragma omp parallel for reduction(+:SDCount,SumS)
	for(int i=0;i<NLen;i++){
		int SrcX1=Area.GetFLineLeftX (i);
		int SrcX2=Area.GetFLineRightX(i);
		int SrcY =Area.GetFLineAbsY	(i);
		if((SrcY%Isolation)!=0)
			continue;

		int DstX1=SrcX1+dx;
		int DstX2=SrcX2+dx;
		int	DstY =SrcY +dy;

		if(SrcY<0 || SrcY>=Src.GetHeight()	|| DstY<0 || DstY>=Dst.GetHeight()){
			continue;
		}
		if(SrcX2<0 || SrcX1>=Src.GetWidth()	|| DstX2<0 || DstX1>=Dst.GetWidth()){
			continue;
		}
		if(SrcX1<0){
			SrcX1=0;
		}
		if(DstX1<0){
			SrcX1-=DstX1;
			DstX1=0;
		}
		if(SrcX2>Src.GetWidth()){
			SrcX2=Src.GetWidth();
		}
		if(DstX2>Dst.GetWidth()){
			DstX2=Dst.GetWidth();
		}

		BYTE	*s=Src.GetY(SrcY);
		BYTE	*d=Dst.GetY(DstY);
		int	xs,xd;
		for(xs=SrcX1,xd=DstX1;xs<SrcX2 && xd<DstX2;xs+=Isolation,xd+=Isolation){
			int	m=s[xs] - (d[xd]+L)*Mul;
			SumS	+=sqrt((double)m);
			SDCount++;
		}
	}
	if(SDCount==0){
		return 0.0;
	}
	return SumS/SDCount;
}

void	MakeDiffMap(FlexArea &Area,int dx ,int dy, int L,double Mul
				,BYTE **VMap,int LeftX,int TopY,int W,int H
				,ImageBuffer &Src,ImageBuffer &Dst
				,int BrightWidth ,int DiffBrightWidth ,bool Plus)
{
	int	NLen=Area.GetFLineLen();
	#pragma omp parallel for
	for(int i=0;i<NLen;i++){
		int SrcX1=Area.GetFLineLeftX (i);
		int SrcX2=Area.GetFLineRightX(i);
		int SrcY =Area.GetFLineAbsY	(i);

		int DstX1=SrcX1+dx;
		int DstX2=SrcX2+dx;
		int	DstY =SrcY +dy;

		if(SrcY<0 || SrcY>=Src.GetHeight()	|| DstY<0 || DstY>=Dst.GetHeight()){
			continue;
		}
		if(SrcX2<0 || SrcX1>=Src.GetWidth()	|| DstX2<0 || DstX1>=Dst.GetWidth()){
			continue;
		}
		if(SrcX1<0){
			SrcX1=0;
		}
		if(DstX1<0){
			SrcX1-=DstX1;
			DstX1=0;
		}
		if(SrcX2>Src.GetWidth()){
			SrcX2=Src.GetWidth();
		}
		if(DstX2>Dst.GetWidth()){
			DstX2=Dst.GetWidth();
		}

		BYTE	*s=Src.GetY(SrcY);
		BYTE	*d=Dst.GetY(DstY);
		BYTE	*p=VMap[SrcY-TopY];
		int	xs,xd;
		for(xs=SrcX1,xd=DstX1;xs<SrcX2 && xd<DstX2;xs++,xd++){
			int	m=(d[xd]+L)*Mul -s[xs];
			if(Plus==true && m>BrightWidth && d[xd]>DiffBrightWidth){
				SetBmpBitOnY1(p,(xs-LeftX));
			}
			if(Plus==false && (-m)>BrightWidth && d[xd]<DiffBrightWidth){
				SetBmpBitOnY1(p,(xs-LeftX));
			}
		}
	}
}

bool	BlockItem::ExecuteProcessingInnerDiffer(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,WORD	DiffBrightWidthL,WORD DiffBrightWidthH
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	int	Isolation=min(W/20,H/20);
	if(Isolation==0)
		Isolation=1;
	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	for(int dy=-RThr->ThreshouldBag.SelfSearch;dy<=RThr->ThreshouldBag.SelfSearch;dy++){
		for(int dx=-RThr->ThreshouldBag.SelfSearch;dx<=RThr->ThreshouldBag.SelfSearch;dx++){
			double	D=GetArea().GetCoeff(GetMasterBuff(),mx+dx,my+dy,GetTargetBuff(),Isolation);
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}

	double	MinDD=9999999999.0;
	int		MinL=0;
	double	MinMul=1.0;
	for(int	L=-RThr->ThreshouldBag.AdjustBlack;L<=RThr->ThreshouldBag.AdjustWhite;L++){
		//for(double Mul=0.7;Mul<=1.3;Mul+=0.02){
			double Mul=1.0;
			double	D=GetDifferencialSum2(GetArea(),GetMasterBuff(),mx+MaxDx,my+MaxDy,GetTargetBuff(),Isolation
										,L,Mul);
			if(MinDD>D){
				MinDD=D;
				MinL=L;
				MinMul=Mul;
			}
		//}
	}
	FlexArea	*fa=&GetArea();
    //int starty =fa->GetFLineAbsY(0);

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

    uchar   BackBuffV[10000];
	BYTE   *pMapV=NULL;

	if(LByte>sizeof(BackBuffV))
	    pMapV=new BYTE[LByte];
	else
		pMapV=BackBuffV;

	uchar   *VPointer[5000];
	uchar   **VDim;
	if(Ly<sizeof(VPointer)/sizeof(VPointer[0])){
		VDim=VPointer;
	}
	else{
		VDim=new uchar *[Ly];
	}
	BYTE   *pL=pMapV;
	for(int y=0;y<Ly;y++,pL+=Lx){
		VDim[y]=pL;
	}
	bool	DrawResultDetail=GetLayersBase()->GetParamGlobal()->DrawResultDetail;
	ResultPosListContainer PosList;
	short Error=0;

	int	iSumH=0;
	memset(pMapV,0,LByte);
	MakeDiffMap(GetArea(),MaxDx+mx ,MaxDy+my,MinL,MinMul
				,VDim,fa->GetMinX(),fa->GetMinY(),W,H
				,GetMasterBuff(),GetTargetBuff()
				,BrightWidthH,DiffBrightWidthH,true);
	BYTE **bitoperation=NULL;
	if(ConnectLen!=0){
		bitoperation=MakeMatrixBuff(Lx,Ly);
	}
	if(ConnectLen>0){
		for(int i=0;i<ConnectLen-1;i++){
			FatArea(VDim,bitoperation,Lx, Ly);
		}
	}
	else if(ConnectLen<0){
		for(int i=0;i<(-ConnectLen)-1;i++){
			ThinArea(VDim,bitoperation,Lx, Ly);
		}
	}
	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		PureFlexAreaListContainer FPack;
		if(RThr->CalculatedInfo.ModeSmallCalc==true)
			PickupFlexArea_s(VDim,Lx,W,Ly,FPack,-1,MoreThreadInBlock);
		else
			PickupFlexArea(VDim,Lx,W,Ly,FPack,-1,MoreThreadInBlock);

		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
			int	SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			PureFlexAreaList *NextP=p->GetNext();
			if(SumH>OKDotH && SumH<MaxNGDotH && NGLen>OKLengthH){
				iSumH+=SumH;
				FPack.RemoveList(p);
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				//if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap)==false){
				int	Cx,Cy;
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new BlockResultPosList(Cx,Cy ,MaxDx,MaxDy);
				r->result =0x30000;	//?????ANG
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				r->SetResult1((DWORD)SumH);
				r->SetResult2((DWORD)NGLen);
				LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
				if(LNGType!=NULL){
					BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
					if(BL!=NULL){
						r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
					}
				}
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				Error |= 0x20;
				delete	p;
			}
			else if(DrawResultDetail==true){
				FPack.RemoveList(p);
				int	Cx,Cy;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new BlockResultPosList(Cx,Cy ,MaxDx,MaxDy);
				r->SetResult1((DWORD)SumH);
				r->SetResult2((DWORD)NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumH>OKDotH){
					r->result =0x130;	//?????A?P?x?I?m?f?C??E?3?I?n?j
				}
				else if(NGLen>OKLengthH){
					r->result =0x120;	//?????A?P?x?I?m?f?C?E?I?I?n?j
				}
				else{
					r->result =0x110;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
				delete	p;
			}
			p=NextP;
		}
	}
	else{
		int	SumH=::GetBitCount((const BYTE **)VDim,Lx,Ly);
		if(SumH>OKDotH && SumH<MaxNGDotH){
			iSumH=SumH;
			int	Cx,Cy;
			GetCenter(Cx,Cy);
			ResultPosList	*r=new BlockResultPosList(Cx,Cy ,MaxDx,MaxDy);
			r->result =0x30000;	//?????ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1((DWORD)SumH);
			r->SetResult2((DWORD)0);
			PosList.AppendList(r);
			Error |= 0x20;
		}
	}
	int	iSumL=0;
	memset(pMapV,0,LByte);
	MakeDiffMap(GetArea(),MaxDx+mx ,MaxDy+my,MinL,MinMul
				,VDim,fa->GetMinX(),fa->GetMinY(),W,H
				,GetMasterBuff(),GetTargetBuff()
				,BrightWidthL,DiffBrightWidthL,false);
	if(ConnectLen>0){
		for(int i=0;i<ConnectLen-1;i++){
			FatArea(VDim,bitoperation,Lx, Ly);
		}
	}
	else if(ConnectLen<0){
		for(int i=0;i<(-ConnectLen)-1;i++){
			ThinArea(VDim,bitoperation,Lx, Ly);
		}
	}
	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		PureFlexAreaListContainer FPack;
		if(RThr->CalculatedInfo.ModeSmallCalc==true)
			PickupFlexArea_s(VDim,Lx,W,Ly,FPack,-1,MoreThreadInBlock);
		else
			PickupFlexArea(VDim,Lx,W,Ly,FPack,-1,MoreThreadInBlock);
		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
			int	SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			PureFlexAreaList *NextP=p->GetNext();
			if(SumL>OKDotL && SumL<MaxNGDotL && NGLen>OKLengthL){
				iSumL=+SumL;
				FPack.RemoveList(p);
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				//if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap)==false){
				int	Cx,Cy;
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new BlockResultPosList(Cx,Cy ,MaxDx,MaxDy);
				r->result =0x20000;	//?????ANG
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				r->SetResult1((DWORD)SumL);
				r->SetResult2((DWORD)NGLen);
				LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
				if(LNGType!=NULL){
					BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
					if(BL!=NULL){
						r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
					}
				}
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				Error |= 0x10;
				delete	p;
			}
			else if(DrawResultDetail==true){
				FPack.RemoveList(p);
				int	Cx,Cy;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new BlockResultPosList(Cx,Cy ,MaxDx,MaxDy);
				r->SetResult1((DWORD)SumL);
				r->SetResult2((DWORD)NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumL>OKDotL){
					r->result =0x30;	//?????A?P?x?I?m?f?C??E?3?I?n?j
				}
				else if(NGLen>OKLengthH){
					r->result =0x20;	//?????A?P?x?I?m?f?C?E?I?I?n?j
				}
				else{
					r->result =0x10;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
				delete	p;
			}
			p=NextP;
		}
	}
	else{
		int	SumL=::GetBitCount((const BYTE **)VDim,Lx,Ly);
		if(SumL>OKDotL && SumL<MaxNGDotL){
			iSumL=+SumL;
			int	Cx,Cy;
			GetCenter(Cx,Cy);
			ResultPosList	*r=new BlockResultPosList(Cx,Cy ,MaxDx,MaxDy);
			r->result =0x20000;	//?????ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1((DWORD)SumL);
			r->SetResult2((DWORD)0);
			PosList.AppendList(r);
			Error |= 0x10;
		}
	}
	Res->MovePosList(PosList);		

	if(VDim!=VPointer)
		delete	[]VDim;
	if(pMapV!=BackBuffV)
		delete	[]pMapV;
	if(bitoperation!=NULL){
		DeleteMatrixBuff(bitoperation,Ly);
	}

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(MaxDx,MaxDy);
	Res->SetResult1(iSumL);
	Res->SetResult2(iSumH);
	if(Error!=0){
		Res->SetError(2 | Error);	//NG
		return false;
	}
	Res->SetError(1);	//OK
	return true;
}

bool    BlockItem::ExecuteProcessingInnerWithoutSubtractCalcAFixX(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    MinL=0x7FFFFFFF;
    MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
	int SumL=0;
	int SumH=0;

	int	NarrowBlockW=12;
	int InsideSumL=0;
	int InsideSumH=0;
	int	SelfSearch=Thres->ThreshouldBag.SelfSearch;

	if(GetFromRental()==true){
		BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
		SelfSearch +=BBase->MoreSearchForRental;
	}

    dx=0;
    dy=0;
	short	Error=0;
	if(ConnectLen==0 && Thres->ThreshouldBag.PointMove.ModeAdoptBiggest==false){
		int	sTmpBrightWidthL=BrightWidthL;
		int	sTmpBrightWidthH=BrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,InsideSumL,InsideSumH);
		if(InsideSumL>OKDotL || InsideSumH>OKDotH){
			return false;
		}

		if(IsModeDir4()==true && IsInsideArea(GetArea(),mx,my,SelfSearch+1,GetDotPerLine(),GetMaxLines())==true){
			if((DynamicMaskMap==NULL || (Thres->ThreshouldBag.PointMove.ModeDynamicMask==false) 
			|| IsOnDynamicMasking(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx,my,SelfSearch)==false)){

				unsigned int	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned int	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=NULL;
				SData.DynamicMaskMapXByte	=0;
				SData.DynamicMaskMapYLen	=0;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx;
					int	CurrentY=my-SelfSearch;
					MinMy=-SelfSearch;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-SelfSearch)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx;
						CurrentY=my+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;

					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
			else{
				unsigned int	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned int	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=DynamicMaskMap;
				SData.DynamicMaskMapXByte	=DynamicMaskMapXByte;
				SData.DynamicMaskMapYLen	=DynamicMaskMapYLen;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx;
					int	CurrentY=my-SelfSearch;
					MinMy=-SelfSearch;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);

					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-SelfSearch)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx;
						CurrentY=my+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;

					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx ,my+W->y
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(0,W->y);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=0;
					dy=W->y;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx ,my+W->y+t
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx ,my+W->y+t
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(0,W->y+t);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=0;
						dy=W->y+t;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx,my+W->y
							,TmpBrightWidthL,TmpBrightWidthH
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}
	
				SumL=0;
				SumH=0;
				Level3Speedy(mx ,my+W->y
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(0,W->y);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=0;
					dy=W->y;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;
	
					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else{
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int s=-1;s<=1;s++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx ,my+W->y+s
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx ,my+W->y+s
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(0,W->y+s);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=0;
						dy=W->y+s;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
	}
	return false;
}

bool    BlockItem::ExecuteProcessingInnerWithoutSubtractCalcAFixX_s(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    MinL=0x7FFFFFFF;
    MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
	int SumL=0;
	int SumH=0;

	int	NarrowBlockW=12;
	int InsideSumL=0;
	int InsideSumH=0;
	int	SelfSearch=Thres->ThreshouldBag.SelfSearch;

	if(GetFromRental()==true){
		BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
		SelfSearch +=BBase->MoreSearchForRental;
	}

    dx=0;
    dy=0;
	short	Error=0;
	if(ConnectLen==0 && Thres->ThreshouldBag.PointMove.ModeAdoptBiggest==false){
		int	sTmpBrightWidthL=BrightWidthL;
		int	sTmpBrightWidthH=BrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,InsideSumL,InsideSumH);
		if(InsideSumL>OKDotL || InsideSumH>OKDotH){
			return false;
		}

		if(IsModeDir4()==true && IsInsideArea(GetArea(),mx,my,SelfSearch+1,GetDotPerLine(),GetMaxLines())==true){
			if((DynamicMaskMap==NULL || (Thres->ThreshouldBag.PointMove.ModeDynamicMask==false) 
			|| IsOnDynamicMasking(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx,my,SelfSearch)==false)){

				unsigned short	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned short	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct_s	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=NULL;
				SData.DynamicMaskMapXByte	=0;
				SData.DynamicMaskMapYLen	=0;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx;
					int	CurrentY=my-SelfSearch;
					MinMy=-SelfSearch;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-SelfSearch)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx;
						CurrentY=my+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;

					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
			else{
				unsigned short	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned short	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct_s	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=DynamicMaskMap;
				SData.DynamicMaskMapXByte	=DynamicMaskMapXByte;
				SData.DynamicMaskMapYLen	=DynamicMaskMapYLen;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx;
					int	CurrentY=my-SelfSearch;
					MinMy=-SelfSearch;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);

					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,-SelfSearch)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(SkipSearchAreasData->DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx;
						CurrentY=my+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaBottom,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy+L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;

					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaUp,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx;
						CurrentY=my+MinMy-L;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,0,-L)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx ,my+W->y
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(0,W->y);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=0;
					dy=W->y;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx ,my+W->y+t
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx ,my+W->y+t
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(0,W->y+t);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=0;
						dy=W->y+t;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx,my+W->y
							,TmpBrightWidthL,TmpBrightWidthH
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}
	
				SumL=0;
				SumH=0;
				Level3Speedy(mx ,my+W->y
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(0,W->y);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=0;
					dy=W->y;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;
	
					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else{
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int s=-1;s<=1;s++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx ,my+W->y+s
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx ,my+W->y+s
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(0,W->y+s);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=0;
						dy=W->y+s;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
	}
	return false;
}

bool    BlockItem::ExecuteProcessingInnerWithoutSubtractCalcAFixY(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    MinL=0x7FFFFFFF;
    MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
	int SumL=0;
	int SumH=0;

	int	NarrowBlockW=12;
	int InsideSumL=0;
	int InsideSumH=0;
	int	SelfSearch=Thres->ThreshouldBag.SelfSearch;

	if(GetFromRental()==true){
		BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
		SelfSearch +=BBase->MoreSearchForRental;
	}

    dx=0;
    dy=0;
	short	Error=0;
	if(ConnectLen==0 && Thres->ThreshouldBag.PointMove.ModeAdoptBiggest==false){
		int	sTmpBrightWidthL=BrightWidthL;
		int	sTmpBrightWidthH=BrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,InsideSumL,InsideSumH);

		if(IsModeDir4()==true && IsInsideArea(GetArea(),mx,my,SelfSearch+1,GetDotPerLine(),GetMaxLines())==true){
			if((DynamicMaskMap==NULL || (Thres->ThreshouldBag.PointMove.ModeDynamicMask==false) 
			|| IsOnDynamicMasking(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx,my,SelfSearch)==false)){

				unsigned int	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned int	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=NULL;
				SData.DynamicMaskMapXByte	=0;
				SData.DynamicMaskMapYLen	=0;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx-SelfSearch;
					int	CurrentY=my;
					MinMx=-SelfSearch;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,-SelfSearch,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+L;
						CurrentY=my;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
			else{
				unsigned int	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned int	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=DynamicMaskMap;
				SData.DynamicMaskMapXByte	=DynamicMaskMapXByte;
				SData.DynamicMaskMapYLen	=DynamicMaskMapYLen;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx-SelfSearch;
					int	CurrentY=my;
					MinMx=-SelfSearch;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,-SelfSearch,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+L;
						CurrentY=my;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
		}				
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx+W->x ,my
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,0);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=0;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx+W->x ,my
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,0);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=0;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x+t ,my
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,0);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=0;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else{
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
		
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x+t ,my
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,0);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=0;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
	}
	return false;
}

bool    BlockItem::ExecuteProcessingInnerWithoutSubtractCalcAFixY_s(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int &dx ,int &dy
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,int &MinL ,int &MinH
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						  ,int SkipSearchDot)
{
	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	if(Thres->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    MinL=0x7FFFFFFF;
    MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
	int SumL=0;
	int SumH=0;

	int	NarrowBlockW=12;
	int InsideSumL=0;
	int InsideSumH=0;
	int	SelfSearch=Thres->ThreshouldBag.SelfSearch;

	if(GetFromRental()==true){
		BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
		SelfSearch +=BBase->MoreSearchForRental;
	}

    dx=0;
    dy=0;
	short	Error=0;
	if(ConnectLen==0 && Thres->ThreshouldBag.PointMove.ModeAdoptBiggest==false){
		int	sTmpBrightWidthL=BrightWidthL;
		int	sTmpBrightWidthH=BrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx ,my
						,sTmpBrightWidthL,sTmpBrightWidthH
						,InsideSumL,InsideSumH);
		if(InsideSumL>OKDotL || InsideSumH>OKDotH){
			return false;
		}

		if(IsModeDir4()==true && IsInsideArea(GetArea(),mx,my,SelfSearch+1,GetDotPerLine(),GetMaxLines())==true){
			if((DynamicMaskMap==NULL || (Thres->ThreshouldBag.PointMove.ModeDynamicMask==false) 
			|| IsOnDynamicMasking(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx,my,SelfSearch)==false)){

				unsigned short	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned short	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct_s	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=NULL;
				SData.DynamicMaskMapXByte	=0;
				SData.DynamicMaskMapYLen	=0;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx-SelfSearch;
					int	CurrentY=my;
					MinMx=-SelfSearch;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,-SelfSearch,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+L;
						CurrentY=my;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					A->MakeBrightList(BrightTable,GetDotPerLine(),GetMaxLines(),IBuff,CurrentX,CurrentY);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
			else{
				unsigned short	BrightTable[256];
				memset(BrightTable,0,sizeof(BrightTable));
				unsigned short	MinBrightTable[256];
				int	MinMx=0;
				int	MinMy=0;

				struct	TmpStruct_s	SData;
				SData.Res		=Res;	
				SData.NBMode	=NBMode;
				SData.BrightTable	=BrightTable;
				SData.BindBW	=BindBW;
				SData.OKDotL	=OKDotL;
				SData.OKDotH	=OKDotH;
				SData.mx		=mx;
				SData.my		=my;
                SData.MinL		=&MinL;
                SData.MinH		=&MinH;
                SData.MinL2		=MinL2;
                SData.MinH2		=MinH2;
				SData.dx		=&dx;
				SData.dy		=&dy;
				SData.MinMx		=&MinMx;
				SData.MinMy		=&MinMy;
				SData.MinBrightTable=MinBrightTable;
				SData.DynamicMaskMap		=DynamicMaskMap;
				SData.DynamicMaskMapXByte	=DynamicMaskMapXByte;
				SData.DynamicMaskMapYLen	=DynamicMaskMapYLen;

				FlexArea	*A=&GetArea();
				ImageBuffer	&IBuff=GetTargetBuff();
				if(SkipSearchAreasData!=NULL && SkipSearchDot>1){
					int	CurrentX=mx-SelfSearch;
					int	CurrentY=my;
					MinMx=-SelfSearch;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					SelfSearch=SkipSearchDot;

					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4(SData,tTmpBrightWidthL ,tTmpBrightWidthH,-SelfSearch,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=-SelfSearch+SkipSearchDot;L<=SelfSearch;L+=SkipSearchDot){
						IncreaseTable(SkipSearchAreasData->AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(SkipSearchAreasData->DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+L;
						CurrentY=my;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
				else{
					int	CurrentX=mx;
					int	CurrentY=my;
					MakeBrightList(*A,GetDotPerLine(),GetMaxLines(),BrightTable,IBuff,CurrentX,CurrentY
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					memcpy(MinBrightTable,BrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					int	tTmpBrightWidthL=BrightWidthL;
					int	tTmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(BrightTable ,tTmpBrightWidthL,tTmpBrightWidthH);
					}
					if(JudgeDir4S(SData,tTmpBrightWidthL ,tTmpBrightWidthH,0,0)==true){
						ResultBrightWidthL=SData.ResultBrightWidthL;
						ResultBrightWidthH=SData.ResultBrightWidthH;
						return true;
					}
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaRight,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx+L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
					memcpy(BrightTable,MinBrightTable,sizeof(BrightTable));
					CurrentX=mx;
					CurrentY=my;
					for(int L=1;L<=SelfSearch;L++){
						IncreaseTable(AppeLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						DecreaseTable(DisaLeft,BrightTable,IBuff,CurrentX,CurrentY
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						CurrentX=mx+MinMx-L;
						CurrentY=my+MinMy;
						int	TmpBrightWidthL=BrightWidthL;
						int	TmpBrightWidthH=BrightWidthH;
						if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
							EnAverage(BrightTable ,TmpBrightWidthL,TmpBrightWidthH);
						}
						if(JudgeDir4S(SData,TmpBrightWidthL ,TmpBrightWidthH,-L,0)==true){
							ResultBrightWidthL=SData.ResultBrightWidthL;
							ResultBrightWidthH=SData.ResultBrightWidthH;
							return true;
						}
					}
				}
			}
		}				
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx+W->x ,my
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,0);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=0;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
					EnAverage(mx+W->x ,my
								,TmpBrightWidthL,TmpBrightWidthH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}

				SumL=0;
				SumH=0;
				Level3Speedy(mx+W->x ,my
							,TmpBrightWidthL ,TmpBrightWidthH
							,SumL,SumH);
				//SumL+=InsideSumL;
				//SumH+=InsideSumH;
				if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
				&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
					ResultBrightWidthL=TmpBrightWidthL;
					ResultBrightWidthH=TmpBrightWidthH;
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(W->x,0);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					SetSWayListToTop(ThreadNo,SelfSearch,W);
					if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
						MakeNGPointForInvertLogic(mx+W->x ,my+W->y
								,TmpBrightWidthL,TmpBrightWidthH
								,Res,NBMode
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
					dx=W->x;
					dy=0;
					MinL2=SumL*SumL;
					MinH2=SumH*SumH;
					MinL=SumL;
					MinH=SumH;

					Error=0;
					if(SumL>OKDotL)
						Error |= 0x10;	//?????A?m?f
					if(SumH>OKDotH)
						Error |= 0x20;	//?????A?m?f
				}
			}
		}
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
	
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x+t ,my
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,0);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=0;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
	
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
		else{
			for(XYClass *W=GetSWayListFirst(ThreadNo,SelfSearch);W!=NULL;W=W->GetNext()){
				for(int t=-1;t<=1;t++){
					int	TmpBrightWidthL=BrightWidthL;
					int	TmpBrightWidthH=BrightWidthH;
					if(Thres->ThreshouldBag.PointMove.ModeAdjustable==true){
						EnAverage(mx+W->x+t ,my
									,TmpBrightWidthL,TmpBrightWidthH
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
					}
		
					SumL=0;
					SumH=0;
					Level3Speedy(mx+W->x+t ,my
								,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
					//SumL+=InsideSumL;
					//SumH+=InsideSumH;
					if(((BindBW==false && SumL<=OKDotL && SumH<=OKDotH) || (BindBW==true && (SumL+SumH)<=OKDotL))
					&& AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+W->x,my+W->y)){
						ResultBrightWidthL=TmpBrightWidthL;
						ResultBrightWidthH=TmpBrightWidthH;
						Res->SetAlignedXY(mx,my);
						Res->SetItemSearchedXY(W->x+t,0);
						Res->SetResult1(SumL);
						Res->SetResult2(SumH);
						Res->SetError(1);	//OK
						SetSWayListToTop(ThreadNo,SelfSearch,W);
						if(GetInvertLogic()==true && Thres->ThreshouldBag.PointMove.ModeNGCluster==true){
							MakeNGPointForInvertLogic(mx+W->x ,my+W->y
									,TmpBrightWidthL,TmpBrightWidthH
									,Res,NBMode
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
						}
						return true;
					}
					if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
						dx=W->x+t;
						dy=0;
						MinL2=SumL*SumL;
						MinH2=SumH*SumH;
						MinL=SumL;
						MinH=SumH;
						Error=0;
						if(SumL>OKDotL)
							Error |= 0x10;	//?????A?m?f
						if(SumH>OKDotH)
							Error |= 0x20;	//?????A?m?f
					}
				}
			}
		}
	}
	return false;
}

bool    BlockItem::ExecuteProcessingInnerWithoutSubtract(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int dx ,dy;
	int MinL ,MinH;
	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	bool	Ret;
	const	BlockThreshold	*RThr=GetThresholdR();

	if(RThr->CalculatedInfo.ModeSmallCalc==true){
		Ret=ExecuteProcessingInnerWithoutSubtractCalcA_s(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode, BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,BBase->SkipSearchDot);
	}
	else{
		Ret=ExecuteProcessingInnerWithoutSubtractCalcA(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode, BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,BBase->SkipSearchDot);
	}
	if(Ret==true)
		return Ret;
	if(BBase->SkipSearchDot>1){
		if(RThr->CalculatedInfo.ModeSmallCalc==true){
			Ret=ExecuteProcessingInnerWithoutSubtractCalcA_s(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode, BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,1);
		}
		else{
			Ret=ExecuteProcessingInnerWithoutSubtractCalcA(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode, BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,1);
		}
		if(Ret==true)
			return Ret;
	}

	int	NarrowBlockW=12;
	int	RoundBlockW=80;
	short	Error=0;
	int SumL=0;
	int SumH=0;
	int	MulLen[]={	0,1,-1,2,-2	};
	int	SLen=RThr->ThreshouldBag.SelfSearch;

	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			Error=0;
			if(GetArea().GetWidth()>=RoundBlockW && GetArea().GetHeight()>=RoundBlockW){
				ResultPosListContainer	MinNowList;
				for(int i=0;i<5;i++){
					for(int j=0;j<5;j++){
						ResultPosListContainer	NowList;
						int	hx=dx+SLen*MulLen[i]/2;
						int	hy=dy+SLen*MulLen[j]/2;
						if(CheckOnNG(mx,my
							,hx,hy
							,BrightWidthL ,BrightWidthH
							,ResultBrightWidthL ,ResultBrightWidthH
							,OKDotL ,OKDotH
							,MaxNGDotL ,MaxNGDotH
							,SumL,SumH
							,NowList
							,OKLengthL ,OKLengthH
							,MinNGCountL,MinNGCountH,ConnectLen
							,Error
							,NBMode, BindBW
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
								Res->SetAlignedXY(mx,my);
								Res->SetItemSearchedXY(hx,hy);
								Res->SetResult1(SumL);
								Res->SetResult2(SumH);
								Res->SetError(1);	//OK
								return true;
						}
						else{
							if((SumL+SumH)<(MinSumL+MinSumH)){
								MinSumL=SumL;
								MinSumH=SumH;
								MinNowList.Move(NowList);
								MinDx=dx+hx;
								MinDy=dy+hy;
							}
						}
					}
				}
				Res->MovePosList(MinNowList);

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
				for(int i=0;i<5;i++){
					for(int j=0;j<5;j++){
						int	hx=dx+SLen*MulLen[i]/2;
						int	hy=dy+SLen*MulLen[j]/2;
						for(int t=-1;t<=1;t++){
							ResultPosListContainer	MinList;
							short	iError=0;
							if(CheckOnNG(mx,my,hx,hy+t
									,BrightWidthL ,BrightWidthH
									,ResultBrightWidthL ,ResultBrightWidthH
									,OKDotL ,OKDotH
									,MaxNGDotL ,MaxNGDotH
									,SumL,SumH
									,MinList
									,OKLengthL ,OKLengthH
									,MinNGCountL,MinNGCountH,ConnectLen
									,iError
									,NBMode, BindBW
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
								Res->SetAlignedXY(mx,my);
								Res->SetItemSearchedXY(hx,hy+t);
								Res->SetResult1(SumL);
								Res->SetResult2(SumH);
								Res->SetError(1);	//OK
								return true;
							}
							if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
								MinDx=hx;
								MinDy=hy+t;
								MinSumL=SumL;
								MinSumH=SumH;
								MinSumL2=SumL*SumL;
								MinSumH2=SumH*SumH;
								NowList.Move(MinList);
								Error=iError;
							}
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
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					int	hx=dx+SLen*MulLen[i]/2;
					int	hy=dy+SLen*MulLen[j]/2;
					for(int t=-1;t<=1;t++){
						ResultPosListContainer	MinList;
						short	iError=0;
						if(CheckOnNG(mx,my,hx,hy+t
									,BrightWidthL ,BrightWidthH
									,ResultBrightWidthL ,ResultBrightWidthH
									,OKDotL ,OKDotH
									,MaxNGDotL ,MaxNGDotH
									,SumL,SumH
									,MinList
									,OKLengthL ,OKLengthH
									,MinNGCountL,MinNGCountH,ConnectLen
									,iError
									,NBMode, BindBW
									,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
							Res->SetAlignedXY(mx,my);
							Res->SetItemSearchedXY(hx,hy+t);
							Res->SetResult1(SumL);
							Res->SetResult2(SumH);
							Res->SetError(1);	//OK
							return true;
						}
						if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
							MinDx=hx;
							MinDy=hy+t;
							MinSumL=SumL;
							MinSumH=SumH;
							MinSumL2=SumL*SumL;
							MinSumH2=SumH*SumH;
							NowList.Move(MinList);
							Error=iError;
						}
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
		else if(GetArea().GetWidth()<=NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					int	hx=dx+SLen*MulLen[i]/2;
					int	hy=dy+SLen*MulLen[j]/2;
					for(int t=-1;t<=1;t++){
						ResultPosListContainer	MinList;
						short	iError=0;
						if(CheckOnNG(mx,my,hx+t,hy
										,BrightWidthL ,BrightWidthH
										,ResultBrightWidthL ,ResultBrightWidthH
										,OKDotL ,OKDotH
										,MaxNGDotL ,MaxNGDotH
										,SumL,SumH
										,MinList
										,OKLengthL ,OKLengthH
										,MinNGCountL,MinNGCountH,ConnectLen
										,iError
										,NBMode, BindBW
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
							Res->SetAlignedXY(mx,my);
							Res->SetItemSearchedXY(hx+t,hy);
							Res->SetResult1(SumL);
							Res->SetResult2(SumH);
							Res->SetError(1);	//OK
							return true;
						}
						if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
							MinDx=hx;
							MinDy=hy+t;
							MinSumL=SumL;
							MinSumH=SumH;
							MinSumL2=SumL*SumL;
							MinSumH2=SumH*SumH;
							NowList.Move(MinList);
							Error	=iError;
						}
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
		else{
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					int	hx=dx+SLen*MulLen[i]/2;
					int	hy=dy+SLen*MulLen[j]/2;
					for(int t=-1;t<=1;t++){
						for(int s=-1;s<=1;s++){
							ResultPosListContainer	MinList;
							short	iError;
							if(CheckOnNG(mx,my,hx+t,hy+s
											,BrightWidthL ,BrightWidthH
											,ResultBrightWidthL ,ResultBrightWidthH
											,OKDotL ,OKDotH
											,MaxNGDotL ,MaxNGDotH
											,SumL,SumH
											,MinList
											,OKLengthL ,OKLengthH
											,MinNGCountL,MinNGCountH,ConnectLen
											,iError
											,NBMode, BindBW
											,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
								Res->SetAlignedXY(mx,my);
								Res->SetItemSearchedXY(hx+t,hy+s);
								Res->SetResult1(SumL);
								Res->SetResult2(SumH);
								Res->SetError(1);	//OK
								return true;
							}				
							if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
								MinDx=hx+t;
								MinDy=hy+s;
								MinSumL=SumL;
								MinSumH=SumH;
								MinSumL2=SumL*SumL;
								MinSumH2=SumH*SumH;
								NowList.Move(MinList);
								Error	=iError;
							}
						}
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
	ResultPosList	*r=new BlockResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1(SumL);
	r->SetResult2(SumH);
	r->result =0x30+0x10000;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(MinL);
	Res->SetResult2(MinH);
	Res->SetError(2 | Error);	//NG

    return false;

}
bool    BlockItem::ExecuteProcessingInnerWithoutSubtractFixX(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int dx ,dy;
	int MinL ,MinH;
	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	const	BlockThreshold	*RThr=GetThresholdR();
	bool	Ret;
	if(RThr->CalculatedInfo.ModeSmallCalc==true){
		Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixX_s(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,BBase->SkipSearchDot);
	}
	else{
		Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixX(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,BBase->SkipSearchDot);
	}
	if(Ret==true)
		return Ret;

	if(BBase->SkipSearchDot>1){
		if(RThr->CalculatedInfo.ModeSmallCalc==true){
			Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixX_s(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,1);
		}
		else{
			Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixX(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,1);
		}
		if(Ret==true)
			return Ret;
	}
	int	NarrowBlockW=12;
	int	RoundBlockW=80;
	short	Error=0;
	int SumL=0;
	int SumH=0;

	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			ResultPosListContainer	NowList;
			Error=0;
			if(GetArea().GetWidth()>=RoundBlockW && GetArea().GetHeight()>=RoundBlockW){
				if(CheckOnNG(mx,my,dx,dy
							,BrightWidthL ,BrightWidthH
							,ResultBrightWidthL ,ResultBrightWidthH
							,OKDotL ,OKDotH
							,MaxNGDotL ,MaxNGDotH
							,SumL,SumH
							,NowList
							,OKLengthL ,OKLengthH
							,MinNGCountL,MinNGCountH,ConnectLen
							,Error
							,NBMode, BindBW
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}
				else{
					Res->MovePosList(NowList);		

					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(2 | Error);	//NG
					return false;
				}
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
					ResultPosListContainer	MinList;
					short	iError=0;
					if(CheckOnNG(mx,my,dx,dy+t
							,BrightWidthL ,BrightWidthH
							,ResultBrightWidthL ,ResultBrightWidthH
							,OKDotL ,OKDotH
							,MaxNGDotL ,MaxNGDotH
							,SumL,SumH
							,MinList
							,OKLengthL ,OKLengthH
							,MinNGCountL,MinNGCountH,ConnectLen
							,iError
							,NBMode, BindBW
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
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
						Error=iError;
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
							,BrightWidthL ,BrightWidthH
							,ResultBrightWidthL ,ResultBrightWidthH
							,OKDotL ,OKDotH
							,MaxNGDotL ,MaxNGDotH
							,SumL,SumH
							,MinList
							,OKLengthL ,OKLengthH
							,MinNGCountL,MinNGCountH,ConnectLen
							,iError
							,NBMode, BindBW
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
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
					Error=iError;
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

			ResultPosListContainer	MinList;
			short	iError=0;
			if(CheckOnNG(mx,my,dx,dy
							,BrightWidthL ,BrightWidthH
							,ResultBrightWidthL ,ResultBrightWidthH
							,OKDotL ,OKDotH
							,MaxNGDotL ,MaxNGDotH
							,SumL,SumH
							,MinList
							,OKLengthL ,OKLengthH
							,MinNGCountL,MinNGCountH,ConnectLen
							,iError
							,NBMode, BindBW
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(dx,dy);
				Res->SetResult1(SumL);
				Res->SetResult2(SumH);
				Res->SetError(1);	//OK
				return true;
			}
			if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
				MinDx=dx;
				MinDy=dy;
				MinSumL=SumL;
				MinSumH=SumH;
				MinSumL2=SumL*SumL;
				MinSumH2=SumH*SumH;
				NowList.Move(MinList);
				Error	=iError;
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
			for(int s=-1;s<=1;s++){
				ResultPosListContainer	MinList;
				short	iError;
				if(CheckOnNG(mx,my,dx,dy+s
								,BrightWidthL ,BrightWidthH
								,ResultBrightWidthL ,ResultBrightWidthH
								,OKDotL ,OKDotH
								,MaxNGDotL ,MaxNGDotH
								,SumL,SumH
								,MinList
								,OKLengthL ,OKLengthH
								,MinNGCountL,MinNGCountH,ConnectLen
								,iError
								,NBMode, BindBW
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy+s);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}				
				if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
					MinDx=dx;
					MinDy=dy+s;
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
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new BlockResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1(SumL);
	r->SetResult2(SumH);
	r->result =0x30+0x10000;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(MinL);
	Res->SetResult2(MinH);
	Res->SetError(2 | Error);	//NG

    return false;

}
bool    BlockItem::ExecuteProcessingInnerWithoutSubtractFixY(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int dx ,dy;
	int MinL ,MinH;
	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	const	BlockThreshold	*RThr=GetThresholdR();
	bool	Ret;
	if(RThr->CalculatedInfo.ModeSmallCalc==true){
		Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixY_s(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,BBase->SkipSearchDot);
	}
	else{
		Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixY(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,BBase->SkipSearchDot);
	}
	if(Ret==true)
		return Ret;
	if(BBase->SkipSearchDot>1){
		if(RThr->CalculatedInfo.ModeSmallCalc==true){
			Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixY_s(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,1);
		}
		else{
			Ret=ExecuteProcessingInnerWithoutSubtractCalcAFixY(ThreadNo,Res
						  ,mx ,my
						  ,dx ,dy
						  ,BrightWidthL ,BrightWidthH
						  ,ResultBrightWidthL ,ResultBrightWidthH
						  ,OKDotL ,OKDotH
						  ,OKLengthL ,OKLengthH
						  ,MinNGCountL,MinNGCountH,ConnectLen
						  ,MinL ,MinH
						  ,NBMode,BindBW
						  ,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						  ,1);
		}
		if(Ret==true)
			return Ret;
	}
	int	NarrowBlockW=12;
	int	RoundBlockW=80;
	short	Error=0;
	int SumL=0;
	int SumH=0;

	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()>NarrowBlockW){
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			ResultPosListContainer	NowList;
			Error=0;
			if(GetArea().GetWidth()>=RoundBlockW && GetArea().GetHeight()>=RoundBlockW){
				if(CheckOnNG(mx,my,dx,dy
							,BrightWidthL ,BrightWidthH
							,ResultBrightWidthL ,ResultBrightWidthH
							,OKDotL ,OKDotH
							,MaxNGDotL ,MaxNGDotH
							,SumL,SumH
							,NowList
							,OKLengthL ,OKLengthH
							,MinNGCountL,MinNGCountH,ConnectLen
							,Error
							,NBMode, BindBW
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}
				else{
					Res->MovePosList(NowList);		

					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(2 | Error);	//NG
					return false;
				}
			}
			else{
				int MinSumL2=99999999;
				int MinSumH2=99999999;
				MinSumL=99999999;
				MinSumH=99999999;
				MinDx=0;
				MinDy=0;
				ResultPosListContainer	MinList;
				short	iError=0;
				if(CheckOnNG(mx,my,dx,dy
						,BrightWidthL ,BrightWidthH
						,ResultBrightWidthL ,ResultBrightWidthH
						,OKDotL ,OKDotH
						,MaxNGDotL ,MaxNGDotH
						,SumL,SumH
						,MinList
						,OKLengthL ,OKLengthH
						,MinNGCountL,MinNGCountH,ConnectLen
						,iError
						,NBMode, BindBW
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}
				if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
					MinDx=dx;
					MinDy=dy;
					MinSumL=SumL;
					MinSumH=SumH;
					MinSumL2=SumL*SumL;
					MinSumH2=SumH*SumH;
					NowList.Move(MinList);
					Error=iError;
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
		else if(GetArea().GetWidth()>NarrowBlockW && GetArea().GetHeight()<=NarrowBlockW){
			ResultPosListContainer	NowList;
			int MinSumL2=99999999;
			int MinSumH2=99999999;
			int MinSumL=99999999;
			int MinSumH=99999999;
			int	MinDx=0;
			int	MinDy=0;
			ResultPosListContainer	MinList;
			short	iError=0;
			if(CheckOnNG(mx,my,dx,dy
						,BrightWidthL ,BrightWidthH
						,ResultBrightWidthL ,ResultBrightWidthH
						,OKDotL ,OKDotH
						,MaxNGDotL ,MaxNGDotH
						,SumL,SumH
						,MinList
						,OKLengthL ,OKLengthH
						,MinNGCountL,MinNGCountH,ConnectLen
						,iError
						,NBMode, BindBW
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
				Res->SetAlignedXY(mx,my);
				Res->SetItemSearchedXY(dx,dy);
				Res->SetResult1(SumL);
				Res->SetResult2(SumH);
				Res->SetError(1);	//OK
				return true;
			}
			if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
				MinDx=dx;
				MinDy=dy;
				MinSumL=SumL;
				MinSumH=SumH;
				MinSumL2=SumL*SumL;
				MinSumH2=SumH*SumH;
				NowList.Move(MinList);
				Error=iError;
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
								,BrightWidthL ,BrightWidthH
								,ResultBrightWidthL ,ResultBrightWidthH
								,OKDotL ,OKDotH
								,MaxNGDotL ,MaxNGDotH
								,SumL,SumH
								,MinList
								,OKLengthL ,OKLengthH
								,MinNGCountL,MinNGCountH,ConnectLen
								,iError
								,NBMode, BindBW
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
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
				ResultPosListContainer	MinList;
				short	iError;
				if(CheckOnNG(mx,my,dx+t,dy
								,BrightWidthL ,BrightWidthH
								,ResultBrightWidthL ,ResultBrightWidthH
								,OKDotL ,OKDotH
								,MaxNGDotL ,MaxNGDotH
								,SumL,SumH
								,MinList
								,OKLengthL ,OKLengthH
								,MinNGCountL,MinNGCountH,ConnectLen
								,iError
								,NBMode, BindBW
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
					Res->SetAlignedXY(mx,my);
					Res->SetItemSearchedXY(dx+t,dy);
					Res->SetResult1(SumL);
					Res->SetResult2(SumH);
					Res->SetError(1);	//OK
					return true;
				}				
				if((SumL*SumL+SumH*SumH)<=(((int64)MinSumL2)+((int64)MinSumH2))){
					MinDx=dx=t;
					MinDy=dy;
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
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new BlockResultPosList(Cx,Cy ,dx,dy);
	r->SetResult1((DWORD)SumL);
	r->SetResult2((DWORD)SumH);
	r->result =0x30+0x10000;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(dx,dy);
	Res->SetResult1(MinL);
	Res->SetResult2(MinH);
	Res->SetError(2 | Error);	//NG

    return false;

}
bool	BlockItem::ExecuteProcessingInnerNoMove(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my ,int ShiftX ,int ShiftY
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}

    int	MinL=0x7FFFFFFF;
    int	MinH=0x7FFFFFFF;
    int	MinL2=0x7FFFFFFF;
    int	MinH2=0x7FFFFFFF;
    int dx=0;
    int dy=0;
	int SumL=0;
	int SumH=0;

	int InsideSumL=0;
	int InsideSumH=0;
	//int	NarrowBlockW=12;
	//int	SelfSearch=RThr->ThreshouldBag.SelfSearch;

	short	Error=0;
	if(ConnectLen==0){
		int	TmpBrightWidthL=BrightWidthL;
		int	TmpBrightWidthH=BrightWidthH;
		if(RThr->ThreshouldBag.PointMove.ModeAdjustable==true){
			EnAverage(mx+ShiftX ,my+ShiftY
					,TmpBrightWidthL,TmpBrightWidthH
					,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
		}
		Level3Inside(mx+ShiftX ,my+ShiftY
						,TmpBrightWidthL,TmpBrightWidthH
						,InsideSumL,InsideSumH);
		if(InsideSumL>OKDotL || InsideSumH>OKDotH){
			return false;
		}

		SumL=0;
		SumH=0;
		Level3Speedy(mx+ShiftX ,my+ShiftY
					,TmpBrightWidthL ,TmpBrightWidthH
					,SumL,SumH);
		//SumL+=InsideSumL;
		//SumH+=InsideSumH;
		//if(SumL<=OKDotL && SumH<=OKDotH && AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+ShiftX,my+ShiftY)){
		if(((BindBW==false && (SumL<=OKDotL || MaxNGDotL<=SumL) && (SumH<=OKDotH || MaxNGDotH<=SumH)) || (BindBW==true && ((SumL+SumH)<=OKDotL || MaxNGDotL<=(SumL+SumH))))
		&& (RThr->ThreshouldBag.PointMove.ModeDynamicMask==true &&  AboveDMask(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen,mx+ShiftX,my+ShiftY))){
			ResultBrightWidthL	=TmpBrightWidthL;
			ResultBrightWidthH	=TmpBrightWidthH;
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(ShiftX ,ShiftY);
			Res->SetResult1(SumL);
			Res->SetResult2(SumH);
			Res->SetError(1);	//OK
			return true;
		}
		if((SumL*SumL+SumH*SumH)<=(((int64)MinL2)+((int64)MinH2))){
			dx=ShiftX;
			dy=ShiftY;
			MinL2=SumL*SumL;
			MinH2=SumH*SumH;
			MinL=SumL;
			MinH=SumH;

			Error=0;
			if(SumL>OKDotL)
				Error |= 0x10;	//?????A?m?f
			if(SumH>OKDotH)
				Error |= 0x20;	//?????A?m?f
		}
	}

	if(RThr->ThreshouldBag.PointMove.ModeNGCluster==true){
		ResultPosListContainer	NowList;
		Error=0;
		if(CheckOnNG(mx,my,ShiftX,ShiftY
					,BrightWidthL ,BrightWidthH
					,ResultBrightWidthL ,ResultBrightWidthH
					,OKDotL ,OKDotH
					,MaxNGDotL ,MaxNGDotH
					,SumL,SumH
					,NowList
					,OKLengthL ,OKLengthH
					,MinNGCountL,MinNGCountH,ConnectLen
					,Error
					,NBMode,BindBW
					,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
			Res->SetAlignedXY(mx,my);
			Res->SetItemSearchedXY(ShiftX,ShiftY);
			Res->SetResult1(SumL);
			Res->SetResult2(SumH);
			Res->SetError(1);	//OK
			return true;
		}
		Res->MovePosList(NowList);		

		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(ShiftX,ShiftY);
		Res->SetResult1(SumL);
		Res->SetResult2(SumH);
		Res->SetError(2 | Error);	//NG
		return false;
	}

	int	Cx,Cy;
	GetCenter(Cx,Cy);
	ResultPosList	*r=new BlockResultPosList(Cx,Cy ,ShiftX,ShiftY);
	r->SetResult1((DWORD)SumL);
	r->SetResult2((DWORD)SumH);
	r->result =0x30+0x10000;	//?P?x?I?m?f?C??E?3?I?n?j
	r->result +=(NBMode==_ThresholdNarrow)?0:1;
	Res->AddPosList(r);

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(ShiftX,ShiftY);
	Res->SetResult1(MinL);
	Res->SetResult2(MinH);
	Res->SetError(2 | Error);	//NG

    return false;
}

bool	BlockItem::ExecuteProcessingSimpleWithoutSubtract(
						   int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int &ResultBrightWidthL ,int &ResultBrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
						  ,ThresholdMode NBMode,bool BindBW
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeEnabled==false){
		return true;
	}
	int SumL=0;
	int SumH=0;

	if(ConnectLen==0){
		if(DynamicMaskMap==NULL){
			int	TmpBrightWidthL=BrightWidthL;
			int	TmpBrightWidthH=BrightWidthH;
			if(RThr->ThreshouldBag.PointMove.ModeAdjustable==true){
				EnAverage(mx ,my
						,TmpBrightWidthL,TmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			}

			SumL=0;
			SumH=0;
			Level3Speedy(mx,my	,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH);
			//if(SumL<=OKDotL && SumH<=OKDotH){
			if(BindBW==false && ((SumL<=OKDotL || MaxNGDotL<=SumL) && (SumH<=OKDotH || MaxNGDotH<=SumH))){
				return true;
			}
			if(BindBW==true && ((SumL+SumH)<=OKDotL || MaxNGDotL<=(SumL+SumH))){
				return true;
			}
		}
		else{
			int	TmpBrightWidthL=BrightWidthL;
			int	TmpBrightWidthH=BrightWidthH;
			if(RThr->ThreshouldBag.PointMove.ModeAdjustable==true){
				EnAverage(mx ,my
						,TmpBrightWidthL,TmpBrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			}

			SumL=0;
			SumH=0;
			Level3Speedy(mx,my	,TmpBrightWidthL ,TmpBrightWidthH
								,SumL,SumH
								,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
			//if(SumL<=OKDotL && SumH<=OKDotH){
			if(BindBW==false && ((SumL<=OKDotL || MaxNGDotL<=SumL) && (SumH<=OKDotH || MaxNGDotH<=SumH))){
				return true;
			}
			if(BindBW==true && ((SumL+SumH)<=OKDotL || MaxNGDotL<=(SumL+SumH))){
				return true;
			}
		}
	}
	return false;
}

bool	BlockItem::AboveDMask(BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen,int dx,int dy)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeDynamicMask==false){
		return true;
	}
	if(DynamicMaskMap==NULL){
		return true;
	}

	int	x,y;
	GetCenter(x,y);
	int	X=x+dx;
	int	Y=y+dy;
	if(Y<0 || Y>=DynamicMaskMapYLen){
		return false;
	}
	if(X<0 || X>=DynamicMaskMapXByte*8){
		return false;
	}
	if((DynamicMaskMap[Y][X>>3] & (0x80>>(X & 7)))==0){
		return true;
	}
	return false;

}

bool    BlockItem::L3Remove(int mx ,int my
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
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false){
		if(IsOriginParts()==false || RThr->ThreshouldBag.PointMove.ModeCenterBrightFromParts==false)
		    CenterBright=CalcCenterBright(GetMasterBuff(),0 ,0);
	}
	else{
		CenterBright=RThr->ThreshouldBag.RegularCenterBright;
	}
	return true;
}

void	BlockItem::Level3Inside(int mx ,int my
					,int BrightWidthL ,int BrightWidthH
					,int &InsideSumL,int &InsideSumH)
{
    if(BrightWidthL<0)    BrightWidthL=0;
    if(BrightWidthH>255)  BrightWidthH=255;
	const	BlockThreshold	*RThr=GetThresholdR();
    if(RThr->ThreshouldBag.PointMove.ModeWhiteMask==true){
        BrightWidthH=255;
	}
    if(RThr->ThreshouldBag.PointMove.ModeBlackMask==true){
        BrightWidthL=0;
	}

	int	MaxX=GetDotPerLine();
	int	MaxY=GetMaxLines();

	ImageBuffer	&IBuff=GetTargetBuff();
	for(int i=0;i<FLineInside.GetFLineLen();i++){
		int	y =FLineInside.GetFLineAbsY  (i)+my;
		int	x1=FLineInside.GetFLineLeftX (i)+mx;
		int	x2=FLineInside.GetFLineRightX(i)+mx;
		if(y<BLKMergin || (MaxY-BLKMergin)<=y){
			continue;
		}
		BYTE	*src=IBuff.GetY(y);
		int	tx1=max(x1,BLKMergin);
		int	tx2=min(x2,MaxX-BLKMergin);
		for(int x=tx1;x<tx2;x++){
			int	c=src[x];
			if(c<BrightWidthL)
				InsideSumL++;
			if(BrightWidthH<c)
				InsideSumH++;
		}
	}
}

void	BlockItem::EnAverage(int mx,int my
						,int &TmpBrightWidthL,int &TmpBrightWidthH)
{
	int	D=CalcCenterBright(GetTargetBuff(),mx,my);
	int	DifCol=D-CenterBright;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(DifCol>RThr->ThreshouldBag.AdjustWhite)
		DifCol=RThr->ThreshouldBag.AdjustWhite;
	if(-DifCol>RThr->ThreshouldBag.AdjustBlack)
		DifCol=-((int)RThr->ThreshouldBag.AdjustBlack);

	TmpBrightWidthL+=DifCol;
	TmpBrightWidthH+=DifCol;
	CenterTargetBright=D;
}

void	BlockItem::EnAverage(unsigned int BrightTable[256]
						,int &TmpBrightWidthL,int &TmpBrightWidthH)
{
	int	D=::CalcCenterBright(BrightTable);
	int	DifCol=D-CenterBright;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(DifCol>RThr->ThreshouldBag.AdjustWhite)
		DifCol=RThr->ThreshouldBag.AdjustWhite;
	if(-DifCol>RThr->ThreshouldBag.AdjustBlack)
		DifCol=-((int)RThr->ThreshouldBag.AdjustBlack);

	TmpBrightWidthL+=DifCol;
	TmpBrightWidthH+=DifCol;
	CenterTargetBright=D;
}

void	BlockItem::EnAverage(unsigned short BrightTable[256]
						,int &TmpBrightWidthL,int &TmpBrightWidthH)
{
	int	D=::CalcCenterBright(BrightTable);
	int	DifCol=D-CenterBright;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(DifCol>RThr->ThreshouldBag.AdjustWhite)
		DifCol=RThr->ThreshouldBag.AdjustWhite;
	if(-DifCol>RThr->ThreshouldBag.AdjustBlack)
		DifCol=-((int)RThr->ThreshouldBag.AdjustBlack);

	TmpBrightWidthL+=DifCol;
	TmpBrightWidthH+=DifCol;
	CenterTargetBright=D;
}

void	BlockItem::EnAverage(int mx,int my
						,WORD &TmpBrightWidthL,WORD &TmpBrightWidthH)
{
	int	D=CalcCenterBright(GetTargetBuff(),mx,my);
	int	DifCol=D-CenterBright;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(DifCol>RThr->ThreshouldBag.AdjustWhite)
		DifCol=RThr->ThreshouldBag.AdjustWhite;
	if(-DifCol>RThr->ThreshouldBag.AdjustBlack)
		DifCol=-((int)RThr->ThreshouldBag.AdjustBlack);

	int	iTmpBrightWidthL=(int)TmpBrightWidthL+DifCol;
	if(iTmpBrightWidthL<0)
		iTmpBrightWidthL=0;
	int	iTmpBrightWidthH=(int)TmpBrightWidthH+DifCol;
	if(iTmpBrightWidthH<0)
		iTmpBrightWidthH=0;
	TmpBrightWidthH=iTmpBrightWidthH;
	TmpBrightWidthL=iTmpBrightWidthL;
	CenterTargetBright=D;
}

void	BlockItem::EnAverage(int mx,int my
						,int &TmpBrightWidthL,int &TmpBrightWidthH
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int	D=CalcCenterBright(GetTargetBuff(),mx,my
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
	//if(D==0)
	//	D=CenterBright;

	int	DifCol=D-CenterBright;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(DifCol>RThr->ThreshouldBag.AdjustWhite)
		DifCol=RThr->ThreshouldBag.AdjustWhite;
	if(-DifCol>RThr->ThreshouldBag.AdjustBlack)
		DifCol=-((int)RThr->ThreshouldBag.AdjustBlack);

	TmpBrightWidthL+=DifCol;
	TmpBrightWidthH+=DifCol;
	CenterTargetBright=D;
}

void	BlockItem::EnAverage(int mx,int my
						,WORD &TmpBrightWidthL,WORD &TmpBrightWidthH
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int	D=CalcCenterBright(GetTargetBuff(),mx,my
							,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
	//if(D==0)
	//	D=CenterBright;

	int	DifCol=D-CenterBright;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(DifCol>RThr->ThreshouldBag.AdjustWhite)
		DifCol=RThr->ThreshouldBag.AdjustWhite;
	if(-DifCol>RThr->ThreshouldBag.AdjustBlack)
		DifCol=-((int)RThr->ThreshouldBag.AdjustBlack);

	int	iTmpBrightWidthL=(int)TmpBrightWidthL+DifCol;
	if(iTmpBrightWidthL<0)
		iTmpBrightWidthL=0;
	int	iTmpBrightWidthH=(int)TmpBrightWidthH+DifCol;
	if(iTmpBrightWidthH<0)
		iTmpBrightWidthH=0;
	TmpBrightWidthH=iTmpBrightWidthH;
	TmpBrightWidthL=iTmpBrightWidthL;
	CenterTargetBright=D;
}


void	BlockItem::Level3Speedy(int mx,int my
					,int TmpBrightWidthL ,int TmpBrightWidthH
					,int &SumL,int &SumH)
{
    if(TmpBrightWidthL<0)    TmpBrightWidthL=0;
    if(TmpBrightWidthH>255)  TmpBrightWidthH=255;
	const	BlockThreshold	*RThr=GetThresholdR();
    if(RThr->ThreshouldBag.PointMove.ModeWhiteMask==true){
        TmpBrightWidthH=255;
	}
    if(RThr->ThreshouldBag.PointMove.ModeBlackMask==true){
        TmpBrightWidthL=0;
	}

	FlexArea	*A=&GetArea();
	ImageBuffer	&IBuff=GetTargetBuff();
	int	MaxX=GetDotPerLine();
	int	MaxY=GetMaxLines();
	for(int i=0;i<A->GetFLineLen();i++){
		int	y =A->GetFLineAbsY  (i)+my;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		if(y<BLKMergin || (MaxY-BLKMergin)<=y){
			continue;
		}
		BYTE	*src=IBuff.GetY(y);

		int	tx1=max(x1,BLKMergin);
		int	tx2=min(x2,MaxX-BLKMergin);
		for(int x=tx1;x<tx2;x++){
			int	c=src[x];
			if(c<TmpBrightWidthL)
				SumL++;
			if(TmpBrightWidthH<c)
				SumH++;
		}
	}
}

void	BlockItem::Level3Speedy(int mx,int my
					,int TmpBrightWidthL ,int TmpBrightWidthH
					,int &SumL,int &SumH
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
    if(TmpBrightWidthL<0)    TmpBrightWidthL=0;
    if(TmpBrightWidthH>255)  TmpBrightWidthH=255;
	const	BlockThreshold	*RThr=GetThresholdR();
    if(RThr->ThreshouldBag.PointMove.ModeWhiteMask==true){
        TmpBrightWidthH=255;
	}
    if(RThr->ThreshouldBag.PointMove.ModeBlackMask==true){
        TmpBrightWidthL=0;
	}

	FlexArea	*A=&GetArea();
	ImageBuffer	&IBuff=GetTargetBuff();
	int	MaxX=GetDotPerLine();
	int	MaxY=GetMaxLines();
	for(int i=0;i<A->GetFLineLen();i++){
		int	y =A->GetFLineAbsY  (i)+my;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		if(y<BLKMergin || (MaxY-BLKMergin)<=y){
			continue;
		}
		BYTE	*src=IBuff.GetY(y);
		BYTE	*Mask=DynamicMaskMap[y];

		int	tx1=max(x1,BLKMergin);
		int	tx2=min(x2,MaxX-BLKMergin);
		for(int x=tx1;x<tx2;x++){
			if(GetBmpBitOnY(Mask,x)==0){
				int	c=src[x];
				if(c<TmpBrightWidthL)
					SumL++;
				if(TmpBrightWidthH<c)
					SumH++;
			}
		}
	}
}

struct	PureFlexAreaListSortStruct
{
	PureFlexAreaList	*Point;
	double				Dots;
};

static	int	SortFunc(const void *a ,const void *b)
{
	struct	PureFlexAreaListSortStruct	*ta=(struct	PureFlexAreaListSortStruct*)a;
	struct	PureFlexAreaListSortStruct	*tb=(struct	PureFlexAreaListSortStruct*)b;
	double	d=ta->Dots - tb->Dots;
	if(d>0)
		return -1;
	if(d<0)
		return 1;
	return 0;
}

void	Sort(PureFlexAreaListContainer &Pack)
{
	struct	PureFlexAreaListSortStruct	*Point;
	struct	PureFlexAreaListSortStruct	Dim[2000];
	int	N=Pack.GetCount();
	if(N<2000){
		Point=Dim;
	}
	else{
		Point=new struct PureFlexAreaListSortStruct[N];
	}

	for(int i=0;i<N;i++){
		PureFlexAreaList *a=Pack.GetFirst();
		Pack.RemoveList(a);
		Point[i].Point=a;
		Point[i].Dots=a->GetPatternByte();
	}
	QSort(Point,N,sizeof(struct	PureFlexAreaListSortStruct),SortFunc);
	for(int i=0;i<N;i++){
		Pack.AppendList(Point[i].Point);
	}
	if(Point!=Dim){
		delete	[]Point;
	}
}

bool	BlockItem::CheckOnNG(int mx,int my ,int hx ,int hy
				, int BrightWidthL ,int BrightWidthH
				 ,int &ResultBrightWidthL ,int &ResultBrightWidthH
				, int OKDotL ,int OKDotH
				,int MaxNGDotL ,int MaxNGDotH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,WORD	OKLengthL
				,WORD	OKLengthH
				,WORD	MinNGCountL,WORD MinNGCountH,int8 ConnectLen
				,short &Error
				,ThresholdMode NBMode,bool BindBW
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	SumL=0;
	SumH=0;
    int	RNumb=0;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeAdjustable==true){
		EnAverage(mx+hx,my+hy
						,BrightWidthL,BrightWidthH
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
	}
    if(BrightWidthL<0)    BrightWidthL=0;
    if(BrightWidthH>255)  BrightWidthH=255;
    if(RThr->ThreshouldBag.PointMove.ModeWhiteMask==true){
        BrightWidthH=255;
	}
    if(RThr->ThreshouldBag.PointMove.ModeBlackMask==true){
        BrightWidthL=0;
	}

	ResultBrightWidthL	=BrightWidthL;
	ResultBrightWidthH	=BrightWidthH;


    uchar   BackBuffH[20000];
    uchar   BackBuffL[20000];

	FlexArea	*fa=&GetArea();
    int starty =fa->GetFLineAbsY(0);

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

    BYTE   *pMapH=NULL;
    BYTE   *pMapL=NULL;
	if(RThr->ThreshouldBag.PointMove.ModeWhiteMask==false || BindBW==true){
	    if(LByte>sizeof(BackBuffH))
		    pMapH=new BYTE[LByte];
		else
			pMapH=BackBuffH;
		memset(pMapH,0,LByte);
	}
	if(RThr->ThreshouldBag.PointMove.ModeBlackMask==false || BindBW==true){
	    if(LByte>sizeof(BackBuffL))
		    pMapL=new BYTE[LByte];
	    else
		    pMapL=BackBuffL;
		memset(pMapL,0,LByte);
	}

	int LSum,HSum;
    if(RThr->ThreshouldBag.PointMove.ModeDiffer==false){
        CheckOnNGInner1(mx+hx ,my+hy
                        ,BrightWidthL ,BrightWidthH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,LSum,HSum
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
        }
    else{
        CheckOnNGInner2(mx+hx ,my+hy
                        ,BrightWidthL ,BrightWidthH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,LSum,HSum
						,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
        }
	if(BindBW==true && pMapL!=NULL && pMapH!=NULL){
		for(int i=0;i<LByte;i++){
			pMapL[i] |= pMapH[i];
		}
	}

	int iSumL=0;
	int iSumH=0;
	int	HCount=0;
	int	LCount=0;

	bool	DrawResultDetail=GetLayersBase()->GetParamGlobal()->DrawResultDetail;
	uchar   *BackPointer[5000];
	uchar   **BackDim;
	if(Ly<sizeof(BackPointer)/sizeof(BackPointer[0])){
		BackDim=BackPointer;
	}
	else{
		BackDim=new uchar *[Ly];
	}

	BYTE **bitoperation=NULL;
	if(ConnectLen!=0){
		bitoperation=MakeMatrixBuff(Lx,Ly);
	}

	//if((ConnectLen==0 || LSum>OKDotL/2)
	if(RThr->ThreshouldBag.PointMove.ModeBlackMask==false){
	    BYTE   *pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		if(ConnectLen>0){
			for(int i=0;i<ConnectLen-1;i++){
				FatArea(BackDim,bitoperation,Lx, Ly);
			}
		}
		else if(ConnectLen<0){
			for(int i=0;i<(-ConnectLen)-1;i++){
				ThinArea(BackDim,bitoperation,Lx, Ly);
			}
		}


		PureFlexAreaListContainer LFPack;
		if(RThr->CalculatedInfo.ModeSmallCalc==true)
			PickupFlexArea_s(BackDim,Lx,Lx*8,Ly,LFPack,-1,MoreThreadInBlock);
		else
			PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack,-1,MoreThreadInBlock);

		if(RThr->ThreshouldBag.PointMove.ModeAdoptBiggest==true){
			Sort(LFPack);
			PureFlexAreaList *t=LFPack.GetFirst();
			if(t!=NULL){
				LFPack.RemoveList(t);
				LFPack.RemoveAll();
				LFPack.AppendList(t);
			}
		}
		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;){
			SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(((OKDotL<=MaxNGDotL && SumL>OKDotL && SumL<MaxNGDotL)
			|| (OKDotL>MaxNGDotL && (SumL>OKDotL || SumL<MaxNGDotL))) && NGLen>OKLengthL){
				//?m?f?I?e??
				PureFlexAreaList *NextP=p->GetNext();
				LFPack.RemoveList(p);
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				//if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap)==false){
					int	Cx,Cy;
					iSumL+=SumL;
					p->GetCenter(Cx,Cy);
					ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);
					r->result =0x20000;	//?????ANG
					r->result +=(NBMode==_ThresholdNarrow)?0:1;
					r->SetResult1((DWORD)SumL);
					r->SetResult2((DWORD)NGLen);
					LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
					if(LNGType!=NULL){
						BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
						if(BL!=NULL){
							r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
						}
					}
					r->NGShape.SuckFrom(*p);
					PosList.AppendList(r);
					RNumb++;
					Error |= 0x10;	//?????A?m?f
					LCount++;
				//}
				delete	p;
				p=NextP;
			}
			else if(DrawResultDetail==true){
				//?n?j???a?A?P?x?A???o??E???e??
				PureFlexAreaList *NextP=p->GetNext();
				LFPack.RemoveList(p);
				int	Cx,Cy;
				iSumL+=SumL;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);
				r->SetResult1((DWORD)SumL);
				r->SetResult2((DWORD)NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumL>OKDotL){
					r->result =0x30;	//?????A?P?x?I?m?f?C??E?3?I?n?j
				}
				else if(NGLen>OKLengthL){
					r->result =0x20;	//?????A?P?x?I?m?f?C?E?I?I?n?j
				}
				else{
					r->result =0x10;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
				delete	p;
				p=NextP;
			}
			else{
				iSumL+=SumL;
				p=p->GetNext();
			}
		}
	}
	if(BindBW==false
	&& (ConnectLen==0 || HSum>OKDotH/2)
	&& RThr->ThreshouldBag.PointMove.ModeWhiteMask==false){
	    BYTE   *pH=pMapH;
		for(int y=0;y<Ly;y++,pH+=Lx){
			BackDim[y]=pH;
		}
		if(ConnectLen>0){
			for(int i=0;i<ConnectLen-1;i++){
				FatArea(BackDim,bitoperation,Lx, Ly);
			}
		}
		else if(ConnectLen<0){
			for(int i=0;i<(-ConnectLen)-1;i++){
				ThinArea(BackDim,bitoperation,Lx, Ly);
			}
		}

		PureFlexAreaListContainer HFPack;
		if(RThr->CalculatedInfo.ModeSmallCalc==true)
			PickupFlexArea_s(BackDim,Lx,Lx*8,Ly,HFPack,-1,MoreThreadInBlock);
		else
			PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack,-1,MoreThreadInBlock);

		if(RThr->ThreshouldBag.PointMove.ModeAdoptBiggest==true){
			Sort(HFPack);
			PureFlexAreaList *t=HFPack.GetFirst();
			if(t!=NULL){
				HFPack.RemoveList(t);
				HFPack.RemoveAll();
				HFPack.AppendList(t);
			}
		}
		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;){
			SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			//if(SumH>OKDotH && NGLen>OKLengthH){
			if(((OKDotH<=MaxNGDotH && SumH>OKDotH && SumH<MaxNGDotH)
			|| (OKDotH>MaxNGDotH && (SumH>OKDotH || SumH<MaxNGDotH))) && NGLen>OKLengthH){

				PureFlexAreaList *NextP=p->GetNext();
				HFPack.RemoveList(p);
				//?m?f?I?e??
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				//if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap)==false){
					int	Cx,Cy;
					iSumH+=SumH;
					p->GetCenter(Cx,Cy);
					ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);
					r->result =0x30000;	//?????ANG
					r->result +=(NBMode==_ThresholdNarrow)?0:1;
					r->SetResult1((DWORD)SumH);
					r->SetResult2((DWORD)NGLen);
					LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
					if(LNGType!=NULL){
						BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
						if(BL!=NULL){
							r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
						}
					}
					r->NGShape.SuckFrom(*p);
					PosList.AppendList(r);
					RNumb++;
					Error |= 0x20;	//?????A?m?f
					HCount++;
				//}
				delete	p;
				p=NextP;
			}
			else if(DrawResultDetail==true){
				PureFlexAreaList *NextP=p->GetNext();
				HFPack.RemoveList(p);
				//?n?j???a?A?P?x?A???o??E???e??
				int	Cx,Cy;
				iSumH+=SumH;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);
				r->SetResult1((DWORD)SumH);
				r->SetResult2((DWORD)NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumH>OKDotH){
					r->result =0x130;	//?????A?P?x?I?m?f?C?E?I?I?m?f
				}
				else if(NGLen>OKLengthH){
					r->result =0x120;	//?????A?P?x?I?m?f?C??E?3?I?m?f
				}
				else{
					r->result =0x110;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
				r->result +=(NBMode==_ThresholdNarrow)?0:1;
				PosList.AppendList(r);
				delete	p;
				p=NextP;
			}
			else{
				iSumH+=SumH;
				p=p->GetNext();
			}
		}
	}
	if(GetInvertLogic()==true){
	    uchar   BackBuffV[10000];
		BYTE   *pMapV=NULL;

	    if(LByte>sizeof(BackBuffV))
		    pMapV=new BYTE[LByte];
		else
			pMapV=BackBuffV;
		memset(pMapV,0,LByte);

		uchar   *VPointer[5000];
		uchar   **VDim;
		if(Ly<sizeof(VPointer)/sizeof(VPointer[0])){
			VDim=VPointer;
		}
		else{
			VDim=new uchar *[Ly];
		}
		BYTE   *pL=pMapV;
		for(int y=0;y<Ly;y++,pL+=Lx){
			VDim[y]=pL;
		}
		GetArea().MakeBitData(VDim,-fa->GetMinX(),-fa->GetMinY(),Lx*8, Ly);

	    pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		MatrixBuffNotAnd(VDim,(const BYTE **)BackDim ,Lx,Ly);

		PureFlexAreaListContainer LFPack;
		if(RThr->CalculatedInfo.ModeSmallCalc==true)
			PickupFlexArea_s(VDim,Lx,Lx*8,Ly,LFPack,-1,MoreThreadInBlock);
		else
			PickupFlexArea(VDim,Lx,Lx*8,Ly,LFPack,-1,MoreThreadInBlock);
		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;){
			SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());

			PureFlexAreaList *NextP=p->GetNext();
			LFPack.RemoveList(p);
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			//if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap)==false){
			int	Cx,Cy;
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);
			r->result =0x20000;	//?????ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1((DWORD)SumL);
			r->SetResult2((DWORD)NGLen);
			LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
			if(LNGType!=NULL){
				BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
				if(BL!=NULL){
					r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
				}
			}
			r->NGShape.SuckFrom(*p);
			PosList.AppendList(r);
			LCount++;
			
			delete	p;
			p=NextP;
		}

		memset(pMapV,0,LByte);
		GetArea().MakeBitData(VDim,-fa->GetMinX(),-fa->GetMinY(),Lx*8, Ly);
	    pL=pMapH;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		MatrixBuffNotAnd(VDim,(const BYTE **)BackDim ,Lx,Ly);

		PureFlexAreaListContainer HFPack;
		if(RThr->CalculatedInfo.ModeSmallCalc==true)
			PickupFlexArea_s(VDim,Lx,Lx*8,Ly,HFPack,-1,MoreThreadInBlock);
		else
			PickupFlexArea(VDim,Lx,Lx*8,Ly,HFPack,-1,MoreThreadInBlock);

		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;){
			SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			//if(SumH>OKDotH && NGLen>OKLengthH){

			PureFlexAreaList *NextP=p->GetNext();
			HFPack.RemoveList(p);
			p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
			int	Cx,Cy;
			p->GetCenter(Cx,Cy);
			ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);
			r->result =0x30000;	//?????ANG
			r->result +=(NBMode==_ThresholdNarrow)?0:1;
			r->SetResult1((DWORD)SumH);
			r->SetResult2((DWORD)NGLen);
			LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
			if(LNGType!=NULL){
				BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
				if(BL!=NULL){
					r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
				}
			}
			r->NGShape.SuckFrom(*p);
			PosList.AppendList(r);
			HCount++;

			delete	p;
			p=NextP;
		}
		if(VDim!=VPointer)
			delete	[]VDim;
		if(pMapV!=BackBuffV)
			delete	[]pMapV;
	}

	if(BackPointer!=BackDim){
		delete	[]BackDim;
	}
	if(bitoperation!=NULL){
		DeleteMatrixBuff(bitoperation,Ly);
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
					int	NGLen;
					AnalyzeNGHole(mx+hx ,my+hy
								,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
							    ,BrightWidthL ,BrightWidthH
								,pMapL ,Lx ,Ly
								,Cx,Cy
								,OKDotL,SumL
								,NGLen);
	
					if(SumL>OKDotL && NGLen>OKLengthL){
						ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
						r->result1=SumL;
						iSumL+=SumL;
						PosList.AppendList(r);
						RNumb++;
						Error |= 0x10;	//?????A?m?f
						LCount++;
					}
				}
            }
			else if(*qH!=0){
	            for(int k=0;k<8;k++){
		            if(((*qH) & (0x80>>k))==0)
			            continue;
					int	Cx,Cy;
					int	NGLen;
					AnalyzeNGHole(mx+hx ,my+hy
								,fa->GetMinX()+(x<<3)+k ,fa->GetMinY()+y
							    ,BrightWidthL ,BrightWidthH
								,pMapH ,Lx ,Ly
								,Cx,Cy
								,OKDotH,SumH
								,NGLen);
	
					if(SumH>OKDotH && NGLen>OKLengthH){
						ResultPosList	*r=new BlockResultPosList(Cx,Cy ,hx,hy);	//mx+hx ,my+hy);
						r->result2=SumH;
						iSumH+=SumH;
						PosList.AppendList(r);
						RNumb++;
						Error |= 0x20;	//?????A?m?f
						HCount++;
					}
				}
			}
        }
	}
	*/

    if(pMapH!=BackBuffH){
        delete  []pMapH;
	}
    if(pMapL!=BackBuffL){
        delete  []pMapL;
	}

	SumH=iSumH;
	SumL=iSumL;
	if(LCount<=MinNGCountL && HCount<=MinNGCountH){
		return true;
	}
	if(RNumb!=0)
		return false;
	return true;
}


void	BlockItem::MakeNGPointForInvertLogic(int dx ,int dy
						,int LLevel,int HLevel
						,ResultInItemRoot *Res
						,ThresholdMode NBMode
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	ImageBuffer &a=GetTargetBuff();
	ImageBuffer &m=GetMasterBuff();
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	int starty =fa->GetFLineAbsY(0);
    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

	uchar   BackBuffV[35000];
	BYTE   *pMapV=NULL;

	if(LByte>sizeof(BackBuffV))
	    pMapV=new BYTE[LByte];
	else
		pMapV=BackBuffV;
	memset(pMapV,0,LByte);

	uchar   *VPointer[5000];
	uchar   **VDim;
	if(Ly<sizeof(VPointer)/sizeof(VPointer[0])){
		VDim=VPointer;
	}
	else{
		VDim=new uchar *[Ly];
	}
	BYTE   *pL=pMapV;
	for(int y=0;y<Ly;y++,pL+=Lx){
		VDim[y]=pL;
	}
	const	BlockThreshold	*RThr=GetThresholdR();
	int	MBrightWidthL=0;
	int	MBrightWidthH=255;
	if(NBMode==_ThresholdBroad){
		MBrightWidthL=RThr->ThreshouldBag.BBrightWidthL;
		MBrightWidthH=RThr->ThreshouldBag.BBrightWidthH;
	}
	else if(NBMode==_ThresholdNarrow){
		MBrightWidthL=RThr->ThreshouldBag.NBrightWidthL;
		MBrightWidthH=RThr->ThreshouldBag.NBrightWidthH;
	}
	if(m.IsNull()==false){
		if(RThr->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
			MBrightWidthL=CenterBright-MBrightWidthL;
			MBrightWidthH=CenterBright+MBrightWidthH;
		}
	}

	for(int i=0;i<fa->GetFLineLen();i++){
		int Y =fa->GetFLineAbsY(i);
		if(Y+dy<BLKMergin || Y+dy>=(YLen-BLKMergin))
			continue;
		int X   =fa->GetFLineLeftX(i);
		int Numb=fa->GetFLineNumb(i);
		int x1=X;
		int x2=X+Numb;
		X=x1;
		if((X+Numb+dx)<BLKMergin || (X+dx)>=(XLen-BLKMergin))
			continue;
		if((X+dx)<BLKMergin){
			X=BLKMergin-dx;
			x1=max(x1,X);
			x2=min(x2,X+Numb);
			Numb=min(Numb,x2-x1);
		}
		if((X+Numb+dx)>=(XLen-BLKMergin)){
			Numb=(XLen-BLKMergin)-(X+dx);
		}
		if(Numb<=0)
			continue;

		//int px=X-fa->GetMinX();
		int mdy=Y-starty;
		BYTE	*p=a.GetY(dy+Y)+dx+X;
		BYTE	*g=m.GetY(Y)+X;
		BYTE	*qL=&(pMapV[Lx*mdy+((X-fa->GetMinX())>>3)]);
		unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));

		if(DynamicMaskMap==NULL || RThr->ThreshouldBag.PointMove.ModeDynamicMask==false){
			for(int x=0;x<Numb;x+=8){
				int N=8;
				if(x+8>=Numb)
					N=Numb-x;
				for(int k=0;k<N;k++,p++,g++){
					if(qL>&pMapV[LByte])
						break;
					if(qL>=pMapV){
						if((*g<MBrightWidthL || MBrightWidthH<*g) && (LLevel<=*p && *p<=HLevel)){
							*qL|=(BYTE)Mask;
						}
					}
					Mask=_rotr(Mask,1);
					if((Mask &0x80)!=0){
						qL++;
					}
				}
			}
		}
		else{
			BYTE	*DMapP=DynamicMaskMap[Y+dy];
			for(int x=0;x<Numb;x+=8){
				int N=8;
				if(x+8>=Numb)
					N=Numb-x;
				for(int k=0;k<N;k++,p++,g++){
					if(qL>&pMapV[LByte])
						break;
					if(qL>=pMapV){
						int	MapX=X+dx+x+k;
						if((DMapP[MapX>>3] & (0x80>>(MapX &0x07)))==0){
							if((*g<MBrightWidthL || MBrightWidthH<*g) && (LLevel<=*p && *p<=HLevel)){
								*qL|=(BYTE)Mask;
							}
						}
					}
					Mask=_rotr(Mask,1);
					if((Mask &0x80)!=0){
						qL++;
					}
				}
			}
		}
	}
		
	ResultPosListContainer	NowList;
	PureFlexAreaListContainer HFPack;
	if(RThr->CalculatedInfo.ModeSmallCalc==true)
		PickupFlexArea_s(VDim,Lx,Lx*8,Ly,HFPack,-1,MoreThreadInBlock);
	else
		PickupFlexArea(VDim,Lx,Lx*8,Ly,HFPack,-1,MoreThreadInBlock);
	for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;){
		int	SumH	=p->GetPatternByte();
		int	NGLen	=max(p->GetWidth(),p->GetHeight());
			//if(SumH>OKDotH && NGLen>OKLengthH){

		PureFlexAreaList *NextP=p->GetNext();
		HFPack.RemoveList(p);
		p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
		int	Cx,Cy;
		p->GetCenter(Cx,Cy);
		ResultPosList	*r=new BlockResultPosList(Cx,Cy ,0,0);
		r->result =0x30000;	//?????ANG
		r->result +=(NBMode==_ThresholdNarrow)?0:1;
		r->SetResult1((DWORD)SumH);
		r->SetResult2((DWORD)NGLen);
		LibNGTypeInAlgorithm	*LNGType=GetLibNGTypeInAlgorithm();
		if(LNGType!=NULL){
			BlockLibNGTypeItem	*BL=MakeNGType(*p,*LNGType);
			if(BL!=NULL){
				r->NGTypeUniqueCode	=BL->GetTypeUniqueCode();
			}
		}
		r->NGShape.SuckFrom(*p);
		NowList.AppendList(r);
		
		delete	p;
		p=NextP;
	}
	if(VDim!=VPointer)
		delete	[]VDim;
	if(pMapV!=BackBuffV)
		delete	[]pMapV;

	if(NowList.GetFirst()!=NULL){
		Res->AddMovePosList(NowList);	
	}
}


void	BlockItem::CheckOnNGInner2(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,int &LSum,int &HSum
									,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	ImageBuffer &a1=GetMasterBuff();
	ImageBuffer &a2=GetTargetBuff();
	LSum=0;
	HSum=0;
	const	BlockThreshold	*RThr=GetThresholdR();

	for(int i=0;i<fa->GetFLineLen();i++){
		int y =fa->GetFLineAbsY(i);
		if(y<BLKMergin || y>=(YLen-BLKMergin))
			continue;
		if(y+dy<BLKMergin || y+dy>=(YLen-BLKMergin))
			continue;
		int x1=fa->GetFLineLeftX(i);
		int x2=fa->GetFLineLeftX(i)+dx;
		int Numb1=fa->GetFLineNumb(i);
		int Numb2=fa->GetFLineNumb(i);
		if(x1<BLKMergin){
			x2=x2-x1-BLKMergin;
			Numb1=Numb1+x1;
			Numb2=Numb2+x1;
			x1=BLKMergin;
		}
		if(x1+Numb1>=XLen-BLKMergin){
			int d=x1+Numb1 - (XLen-BLKMergin);
			Numb1=Numb1-d;
			Numb2=Numb2-d;
		}
		if(x2<BLKMergin){
			x1=x1-(x2-BLKMergin);
			Numb1=Numb1+x2;
			Numb2=Numb2+x2;
			x2=BLKMergin;
		}
		if(x2+Numb2>=(XLen-BLKMergin)){
			int d=x2+Numb2 - (XLen-BLKMergin);
			Numb1=Numb1-d;
			Numb2=Numb2-d;
		}
		if(Numb1<=0 || Numb2<=0)
			continue;
		int Numb=min(Numb1,Numb2);

		//int px=x1-fa->GetMinX();
		int mdy=y-starty;
		BYTE	*p1=a1.GetY(y)   +x1;
		BYTE	*p2=a2.GetY(y+dy)+x2;
		BYTE	*qL=&pMapL[Lx*mdy+((x1-fa->GetMinX())>>3)];
		BYTE	*qH=&pMapH[Lx*mdy+((x1-fa->GetMinX())>>3)];
		unsigned int	Mask=(0x8080808080808080u>>((x1-fa->GetMinX())&7));

		if(DynamicMaskMap==NULL || RThr->ThreshouldBag.PointMove.ModeDynamicMask==false){
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
							LSum++;
						}
						if(HLevel<d){
							*qH|=(BYTE)Mask;
							HSum++;
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
		else{
			BYTE	*DMapP=DynamicMaskMap[y+dy];
			for(int x=0;x<Numb;x+=8){
				int N=8;
				if(x+8>=Numb)
					N=Numb-x;
				for(int k=0;k<N;k++,p1++,p2++){
					int d=*p2-*p1;
					if(qL>&pMapL[LByte])
						break;
					int	MapX=x1+dx+x+k;
					if((DMapP[MapX>>3] & (0x80>>(MapX &0x07)))!=0){
						if(qL>=pMapL){
							if(d<LLevel){
								*qL|=(BYTE)Mask;
								LSum++;
							}
							if(HLevel<d){
								*qH|=(BYTE)Mask;
								HSum++;
							}
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
}

WORD	BlockItem::CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	if(GetArea().GetWidth()>10 && GetArea().GetHeight()>10){
		int		BTable[256];
		memset(BTable,0,sizeof(BTable));

		int	YSep;
		int	XSep;
		FlexArea	&A=GetArea();
		if(A.GetFLineLen()<20)
			YSep=1;
		else if(A.GetFLineLen()<40)
			YSep=2;
		else if(A.GetFLineLen()<60)
			YSep=3;
		else if(A.GetFLineLen()<100)
			YSep=4;
		else
			YSep=5;

		for(int i=0;i<A.GetFLineLen();i+=YSep){
			int	y =A.GetFLineAbsY  (i)+my;
			if(y<BLKMergin)
				continue;
			if(y>=MaxLines-BLKMergin)
				break;
			int	x1=A.GetFLineLeftX (i)+mx;
			int	x2=A.GetFLineRightX(i)+mx;
			if(x1<BLKMergin)
				x1=BLKMergin;
			if(x2>=DotPerLine-BLKMergin)
				x2=DotPerLine-BLKMergin;
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

			src=IBuff.GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				BTable[*(src+x)]++;
			}
		}
		int	N=0;
		for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
			N+=BTable[i];
		}
		int	DiscardDot=N/4;

		int	LLevel;
		int	HLevel;
		int	D=0;
		for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
			D+=BTable[LLevel];
			if(D>DiscardDot){
				break;
			}
		}
		D=0;
		for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
			D+=BTable[HLevel];
			if(D>DiscardDot){
				break;
			}
		}
		N=0;
		double	DSum=0;
		for(int i=LLevel;i<=HLevel;i++){
			N+=BTable[i];
			DSum+=BTable[i]*i;
		}
		if(N!=0){
			return (WORD)(DSum/N);
		}
		return 0;
	}
	else{
		double	D=0;
		int		DTmp;
		int	N=0;

		FlexArea	*A=&FLineEdge;

		for(int i=0;i<A->GetFLineLen();i++){
			int	y =A->GetFLineAbsY  (i)+my;
			if(y<BLKMergin)
				continue;
			if(y>=MaxLines-BLKMergin)
				break;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			int	DTmp=0;
			if(x1<BLKMergin)
				x1=BLKMergin;
			if(x2>=DotPerLine-BLKMergin)
				x2=DotPerLine-BLKMergin;
			if(x1>x2)
				continue;

			XNumb=x2-x1;

			src=IBuff.GetY(y)+x1;
			for(int x=0;x<XNumb;x++){
				DTmp+=*(src+x);
			}
			N+=XNumb;
			D+=DTmp;
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
			if(y<BLKMergin)
				continue;
			if(y>=MaxLines-BLKMergin)
				break;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			DTmp=0;
			if(x1<BLKMergin)
				x1=BLKMergin;
			if(x2>=DotPerLine-BLKMergin)
				x2=DotPerLine-BLKMergin;
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

			src=IBuff.GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmp+=*(src+x);
			}
			N+=(XNumb+XSep-1)/XSep;
			D+=DTmp;
		}	
		if(N!=0){
			D/=N;
		}
		return (WORD)D;
	}
}

WORD	BlockItem::CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	BYTE	*src;
	int		XNumb;
	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();
	const	BlockThreshold	*RThr=GetThresholdR();

	if(GetArea().GetWidth()>10 && GetArea().GetHeight()>10){
		int		BTable[256];
		memset(BTable,0,sizeof(BTable));

		int	YSep;
		int	XSep;
		FlexArea	&A=GetArea();
		if(A.GetFLineLen()<20)
			YSep=1;
		else if(A.GetFLineLen()<40)
			YSep=2;
		else if(A.GetFLineLen()<60)
			YSep=3;
		else if(A.GetFLineLen()<100)
			YSep=4;
		else
			YSep=5;

		for(int i=0;i<A.GetFLineLen();i+=YSep){
			int	sy=A.GetFLineAbsY  (i);
			int	y =sy+my;
			if(y<BLKMergin)
				continue;
			if(y>=MaxLines-BLKMergin)
				break;
			int	x1=A.GetFLineLeftX (i)+mx;
			int	x2=A.GetFLineRightX(i)+mx;
			if(x1<BLKMergin)
				x1=BLKMergin;
			if(x2>=DotPerLine-BLKMergin)
				x2=DotPerLine-BLKMergin;
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

			src=IBuff.GetY(y)+x1;
			if(DynamicMaskMap!=NULL && RThr->ThreshouldBag.PointMove.ModeDynamicMask==true){
				BYTE	*Mask=DynamicMaskMap[y];
				for(int x=0;x<XNumb;x+=XSep){
					if(GetBmpBitOnY(Mask,x1+x)==0){
						BTable[*(src+x)]++;
					}
				}
			}
			else{
				for(int x=0;x<XNumb;x+=XSep){
					BTable[*(src+x)]++;
				}
			}
		}
		int	N=0;
		for(int i=0;i<sizeof(BTable)/sizeof(BTable[0]);i++){
			N+=BTable[i];
		}
		int	DiscardDot=N/4;

		int	LLevel;
		int	HLevel;
		int	D=0;
		for(LLevel=0;LLevel<sizeof(BTable)/sizeof(BTable[0]);LLevel++){
			D+=BTable[LLevel];
			if(D>DiscardDot){
				break;
			}
		}
		D=0;
		for(HLevel=sizeof(BTable)/sizeof(BTable[0])-1;HLevel>=0;HLevel--){
			D+=BTable[HLevel];
			if(D>DiscardDot){
				break;
			}
		}
		N=0;
		double	DSum=0;
		for(int i=LLevel;i<=HLevel;i++){
			N+=BTable[i];
			DSum+=BTable[i]*i;
		}
		if(N!=0){
			return (WORD)(DSum/N);
		}
		return 0;
	}
	else{
		double	D=0;
		int		DTmp;
		int	N=0;

		FlexArea	*A=&FLineEdge;

		for(int i=0;i<A->GetFLineLen();i++){
			int	y =A->GetFLineAbsY  (i)+my;
			if(y<BLKMergin)
				continue;
			if(y>=MaxLines-BLKMergin)
				break;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			int	DTmp=0;
			if(x1<BLKMergin)
				x1=BLKMergin;
			if(x2>=DotPerLine-BLKMergin)
				x2=DotPerLine-BLKMergin;
			if(x1>x2)
				continue;

			XNumb=x2-x1;

			src=IBuff.GetY(y)+x1;
			for(int x=0;x<XNumb;x++){
				DTmp+=*(src+x);
			}
			N+=XNumb;
			D+=DTmp;
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
			if(y<BLKMergin)
				continue;
			if(y>=MaxLines-BLKMergin)
				break;
			int	x1=A->GetFLineLeftX (i)+mx;
			int	x2=A->GetFLineRightX(i)+mx;
			DTmp=0;
			if(x1<BLKMergin)
				x1=BLKMergin;
			if(x2>=DotPerLine-BLKMergin)
				x2=DotPerLine-BLKMergin;
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

			if(DynamicMaskMap!=NULL && RThr->ThreshouldBag.PointMove.ModeDynamicMask==true){
				BYTE	*Mask=DynamicMaskMap[y];
				src=IBuff.GetY(y)+x1;
				for(int x=0;x<XNumb;x+=XSep){
					if(GetBmpBitOnY(Mask,x1+x)==0){
						DTmp+=*(src+x);
					}
				}
			}
			else{
				src=IBuff.GetY(y)+x1;
				for(int x=0;x<XNumb;x+=XSep){
					DTmp+=*(src+x);
				}
			}
			N+=(XNumb+XSep-1)/XSep;
			D+=DTmp;
		}	
		if(N!=0){
			D/=N;
		}
		return (WORD)D;
	}
}

//==================================================================================
XYClass	*BlockItem::GetSWayListFirst(int ThreadNo,int selfSearch)
{
	BlockInLayer *L=dynamic_cast<BlockInLayer *>(GetParent());
	if(L!=NULL){
		if(L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SWay.GetFirst()==NULL)
			L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SetSearchWay(selfSearch);
		return L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].SWay.GetFirst();
	}
	return NULL;
}
void	BlockItem::SetSWayListToTop(int ThreadNo,int selfSearch,XYClass *w)
{
	BlockInLayer *L=dynamic_cast<BlockInLayer *>(GetParent());
	if(L!=NULL)
		L->SWayListPerCPU[ThreadNo].SWWay[selfSearch].ToTop(w);
}

