/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\XStatisticBlockAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XStatisticBlock.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XStatisticBlockLibrary.h"
#include "XPropertyStatisticBlockPacket.h"
#include "XDisplayBitImage.h"
#include <stdlib.h>
#include "swap.h"

#if defined(linux)
#include <x86intrin.h>
#endif // defined(linux)

const	int	MaxResultNGPointInBlock	=1000;
const	int	MaxReEntrantCount		=30000;


bool    StatisticBlockItem::ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,double BrightWidthL ,double BrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	ResultPosListContainer	NowList;
	short	Error=0;
	int	SumL=0;
	int	SumH=0;

	CalcAvrSigma(mx,my,
		DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);

	if(CheckOnNG(mx,my
					,BrightWidthL ,BrightWidthH
					,OKDotL ,OKDotH
					,SumL,SumH
					,NowList
					,OKLengthL ,OKLengthH
					,Error
					,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen)==true){
		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(0,0);
		Res->SetResult1(SumL);
		Res->SetResult2(SumH);
		Res->SetError(1);	//OK
		return true;
	}
	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(0,0);
	Res->SetResult1(SumL);
	Res->SetResult2(SumH);
	Res->MovePosList(NowList);
	Res->SetError(2 | Error);	//NG
	return false;

}


struct AnalyzeNGHoleClass
{
    BYTE			*NGBmp;
    int             NGBmpX;
    int             NGBmpY;
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
	int				FLinesMinX;
	int				FLinesMaxX;
	int				FLinesMinY;
	int				FLinesMaxY;
	int				AMinX;
	int				AMinY;
	int				AMaxX;
	int				AMaxY;
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

void  StatisticBlockItem::SearchAnalyzeNGHole(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B)
{
	if(LData->NGNumb>=MaxReEntrantCount)
		return;
    BYTE *BB=B+((x-LData->FLinesMinX)>>3);
    if(((*BB)&(0x80>>((x-LData->FLinesMinX)&7)))==0)
        return;
    (*BB) &=~(0x80>>((x-LData->FLinesMinX)&7));

	if(LData->AMinX>x)
		LData->AMinX=x;
	if(LData->AMinY>y)
		LData->AMinY=y;
	if(LData->AMaxX<x)
		LData->AMaxX=x;
	if(LData->AMaxY<y)
		LData->AMaxY=y;

	LData->AddX+=x;
	LData->AddY+=y;
	LData->NGNumb++;
	if(y>LData->FLinesMinY && (y+LData->dy)>0){
		if(x>LData->FLinesMinX && (x+LData->dx)>0)
			SearchAnalyzeNGHole(LData,x-1 ,y-1 ,B-LData->NGBmpX );
		SearchAnalyzeNGHole(LData,x   ,y-1 ,B-LData->NGBmpX );
		if((x+1)<LData->FLinesMaxX && (x+1+LData->dx)<LData->DotPerLine)
			SearchAnalyzeNGHole(LData,x+1 ,y-1 ,B-LData->NGBmpX );
	}
	if(x>LData->FLinesMinX && (x+LData->dx)>0)
		SearchAnalyzeNGHole(LData,x-1 ,y   ,B               );
	if((x+1)<LData->FLinesMaxX && (x+1+LData->dx)<LData->DotPerLine)
		SearchAnalyzeNGHole(LData,x+1 ,y   ,B               );

	if((y+1)<LData->FLinesMaxY && (y+1+LData->dy)<LData->MaxLines){
		if(x>LData->FLinesMinX && (x+LData->dx)>0)
			SearchAnalyzeNGHole(LData,x-1 ,y+1 ,B+LData->NGBmpX );
		SearchAnalyzeNGHole(LData,x   ,y+1 ,B+LData->NGBmpX );
		if((x+1)<LData->FLinesMaxX && (x+1+LData->dx)<LData->DotPerLine)
			SearchAnalyzeNGHole(LData,x+1 ,y+1 ,B+LData->NGBmpX );
	}
}


int  StatisticBlockItem::AnalyzeNGHole(int dx ,int dy,int x ,int y
							, BYTE *NGBmp ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot ,int &Sum
							,int &NGLen)
{
	Sum=0;
	const StatisticBlockThreshold	*RThr=GetThresholdR();
    if(RThr->PointMove.ModeEnabled==false)
        return(65535);
	struct AnalyzeNGHoleClass   LData;
    
	LData.NGNumb=0;
	LData.TopBuff=&GetTargetBuff();
    LData.dx=dx;
    LData.dy=dy;
    LData.DotPerLine=GetDotPerLine();
    LData.MaxLines	=GetMaxLines() ;
    LData.NGBmp=NGBmp;
    LData.NGBmpX=NGBmpX;
    LData.NGBmpY=NGBmpY;
    LData.AddX=0;
    LData.AddY=0;
    LData.FLines=&GetArea();
	LData.FLinesMinX=LData.FLines->GetMinX();
	LData.FLinesMaxX=LData.FLines->GetMaxX();
	LData.FLinesMinY=LData.FLines->GetMinY();
	LData.FLinesMaxY=LData.FLines->GetMaxY();
	LData.AMinX=99999999;
	LData.AMinY=99999999;
	LData.AMaxX=-99999999;
	LData.AMaxY=-99999999;

	if(x<LData.FLinesMinX || x>=LData.FLinesMaxX
	|| y<LData.FLinesMinY || y>=LData.FLinesMaxY
	|| (y+dy)<0 || (y+dy)>=LData.MaxLines
	|| (x+dx)<0 || (x+dx)>=LData.DotPerLine)
		return(0);

	SearchAnalyzeNGHole(&LData,x,y ,&NGBmp[(y-GetArea().GetMinY())*NGBmpX]);
    if(LData.NGNumb>OKDot){
        Cx=LData.AddX/LData.NGNumb;
        Cy=LData.AddY/LData.NGNumb;
		Sum=LData.NGNumb;
        }
	NGLen=hypot(LData.AMaxX-LData.AMinX ,LData.AMaxY-LData.AMinY);
    return(LData.NGNumb);
}

void	StatisticBlockItem::CalcAvrSigma(int mx, int my
										 ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	Avr=0.0;
	Sigma=0.0;
	int	ExcludedL=((StatisticBlockBase *)GetParentBase())->ExcludedL;
	int	ExcludedH=((StatisticBlockBase *)GetParentBase())->ExcludedH;

	ImageBuffer	&IBuff=GetTargetBuff();
	int	CountTable[256];
	memset(CountTable,0,sizeof(CountTable));

	FlexArea	*fa=&GetArea();
	int	FLineLen=fa->GetFLineLen();
	if(FLineLen==0)
		return;

	if(DynamicMaskMap==NULL){
		for(int i=0;i<FLineLen;i++){
			int	y =fa->GetFLineAbsY  (i)+my;
			int	x1=fa->GetFLineLeftX (i)+mx;
			int	x2=fa->GetFLineRightX(i)+mx;
			BYTE	*src=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				CountTable[src[x]]++;
			}
		}
	}
	else{
		for(int i=0;i<FLineLen;i++){
			int	y =fa->GetFLineAbsY  (i)+my;
			int	x1=fa->GetFLineLeftX (i)+mx;
			int	x2=fa->GetFLineRightX(i)+mx;
			BYTE	*src=IBuff.GetY(y);
			BYTE	*mask=DynamicMaskMap[y];
			for(int x=x1;x<x2;x++){
				if((mask[x>>3] & (0x80>>(x&7)))==0){
					CountTable[src[x]]++;
				}
			}
		}
	}

	double	Sum2=0;
	int		CntNumb=0;
	int	LTop;
	int	HTop;
	int	MinDot=AreaDots*((StatisticBlockBase *)GetParentBase())->MinDotRate;
	int	CurrentDot=0;
	for(LTop=max(0,ExcludedL);LTop<256;LTop++){	//LTopの計算
		CurrentDot+=CountTable[LTop];
		if(CurrentDot>=MinDot)
			break;
	}
	CurrentDot=0;
	for(HTop=min(255,ExcludedH);HTop>0;HTop--){	//HTopの計算
		CurrentDot+=CountTable[HTop];
		if(CurrentDot>=MinDot)
			break;
	}

	for(int i=LTop;i<=HTop;i++){
		CntNumb+=CountTable[i];
		Avr+=i*CountTable[i];
		Sum2+=i*i*CountTable[i];
	}
	if(CntNumb==0)
		return;
	Avr/=CntNumb;
	Sigma=sqrt((Sum2-Avr*Avr*CntNumb)/CntNumb);
}

bool	StatisticBlockItem::CheckOnNG(int mx,int my
				, double BrightWidthL ,double BrightWidthH
				, int OKDotL ,int OKDotH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,WORD	OKLengthL
				,WORD	OKLengthH
				,short &Error
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	SumL=0;
	SumH=0;
    int	RNumb=0;

	ImageBuffer	&IBuff=GetTargetBuff();
	FlexArea	*fa=&GetArea();
	int	FLineLen=fa->GetFLineLen();
	if(FLineLen==0)
		return true;
	int starty =fa->GetFLineAbsY(0);

	const StatisticBlockThreshold	*RThr=GetThresholdR();
	int LLevel	=Avr-Sigma*BrightWidthL*DegradeRate;
    int HLevel	=Avr+Sigma*BrightWidthH*DegradeRate;
	if(LLevel<0)
		LLevel=0;
	if(HLevel>255)
		HLevel=255;
	if(RThr->PointMove.ModeWhiteMask==true)
		HLevel=255;
	if(RThr->PointMove.ModeBlackMask==true)
		LLevel=0;

    uchar   BackBuffH[50000];
    uchar   BackBuffL[50000];

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

	bool UseMorphology = RThr->UseMorphology;
	bool AllocpTempMap2D1 = false;
	BYTE   **pTempMap2D1=NULL, **pTempMap2D2=NULL;
	StatisticBlockThreshold::_MorphologyApplyTo MorphologyApplyTo = RThr->MorphologyApplyTo;

	uchar   TempMap2D2BackBuff[50000];
    uchar   TempMap2D1BackBuff[50000];
	uchar   *TempMap2D2BackPointer[10000];
	uchar   *TempMap2D1BackPointer[10000];
	uchar   **TempMap2D1BackDim=NULL;
	uchar   **TempMap2D2BackDim=NULL;
    uchar   *pTempMap2D2BackBuff=NULL;
    uchar   *pTempMap2D1BackBuff=NULL;
	if(UseMorphology==true){
		// テンポラリな二次元配列を作る -> pTempMap2D1, pTempMap2D2
		if(Ly<sizeof(TempMap2D2BackPointer)/sizeof(TempMap2D2BackPointer[0]) && (Lx*Ly)<sizeof(TempMap2D2BackBuff)){
			pTempMap2D2BackBuff=TempMap2D2BackBuff;
			pTempMap2D2=TempMap2D2BackPointer;
			for(int y=0;y<Ly;y++){
				pTempMap2D2[y]=&pTempMap2D2BackBuff[y*Lx];
			}

			pTempMap2D1BackBuff=TempMap2D1BackBuff;
			pTempMap2D1=TempMap2D1BackPointer;
			for(int y=0;y<Ly;y++){
				pTempMap2D1[y]=&pTempMap2D1BackBuff[y*Lx];
			}
			AllocpTempMap2D1=true;
		}
		else{
			pTempMap2D2 = MakeMatrixBuff(Lx, Ly);

			//const int TemporaryBufferSize=250;
			//uchar   BackBuffH2D[TemporaryBufferSize][TemporaryBufferSize];
	
			//if((Lx>TemporaryBufferSize) || (Ly>TemporaryBufferSize)){
				pTempMap2D1=MakeMatrixBuff(Lx, Ly);
				AllocpTempMap2D1=true;
			//}else{
			//	for(int by=0; by<Ly; by++)
			//		pMapH2D[by]=BackBuffH2D[by];
			//	AllocpTempMapH2D=false;
			//}
		}
	}

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
	int LSum=0;
	int HSum=0;


	int iSumL=0;
	int iSumH=0;

	int	HCount=0;
	int	LCount=0;

	bool	DrawResultDetail=GetLayersBase()->GetParamGlobal()->DrawResultDetail;
	uchar   *BackPointer[10000];
	uchar   **BackDim;
	if(Ly<sizeof(BackPointer)/sizeof(BackPointer[0])){
		BackDim=BackPointer;
	}
	else{
		BackDim=new uchar *[Ly];
	}

	CheckOnNGInner1(mx ,my
                   ,LLevel,HLevel
                   ,pMapL,pMapH
                   ,Lx ,Ly ,LByte,starty
				   ,LSum,HSum
				   ,/*debug*/NULL,DynamicMaskMapXByte,DynamicMaskMapYLen);
	if(LSum>OKDotL && RThr->PointMove.ModeBlackMask==false){
		if( (UseMorphology==true)
			&&((MorphologyApplyTo==StatisticBlockThreshold::_MorphologyApplyTo::MAT_Both)
			  |(MorphologyApplyTo==StatisticBlockThreshold::_MorphologyApplyTo::MAT_DarkSideOnly)
			  )
		  ){
			DilateAndErode(pMapL, pTempMap2D1, pTempMap2D2, Lx, Ly);
		}
	    BYTE   *pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		PureFlexAreaListContainer LFPack;
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack);
		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;){
			SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumL>OKDotL && NGLen>OKLengthL){
				PureFlexAreaList *NextP=p->GetNext();
				LFPack.RemoveList(p);
				//ＮＧの場合
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap,GetDotPerLine(),GetMaxLines())==false){
					int	Cx,Cy;
					iSumL+=SumL;
					p->GetCenter(Cx,Cy);
					ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);
					r->result =0x20000;	//黒側でNG
					r->SetResult1(SumL);
					r->SetResult2(NGLen);
					r->NGShape.SuckFrom(*p);
					PosList.AppendList(r);
					RNumb++;
					Error |= 0x10;	//黒側でＮＧ
					LCount++;
				}
				delete	p;
				p=NextP;
			}
			else if(DrawResultDetail==true){
				PureFlexAreaList *NextP=p->GetNext();
				LFPack.RemoveList(p);
				//ＯＫだが、輝度で抽出した場合
				int	Cx,Cy;
				iSumL+=SumL;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumL>OKDotL){
					r->result =0x30;	//黒側で輝度はＮＧ，長さはＯＫ
				}
				else if(NGLen>OKLengthL){
					r->result =0x20;	//黒側で輝度はＮＧ，面積はＯＫ
				}
				else{
					r->result =0x10;	//黒側で輝度はＮＧ、長さ面積ともＯＫ
				}
				PosList.AppendList(r);
				delete	p;
				p=NextP;
			}
			else{
				p=p->GetNext();
			}
		}
	}

	if(HSum>OKDotH && RThr->PointMove.ModeWhiteMask==false){
		if( (UseMorphology==true)  
			&&((MorphologyApplyTo==StatisticBlockThreshold::_MorphologyApplyTo::MAT_Both)
			  |(MorphologyApplyTo==StatisticBlockThreshold::_MorphologyApplyTo::MAT_LightSideOnly)
			  )
		  ){
			DilateAndErode(pMapH, pTempMap2D1, pTempMap2D2, Lx, Ly);
		}

	    BYTE   *pH=pMapH;
		for(int y=0;y<Ly;y++,pH+=Lx){
			BackDim[y]=pH;
		}

		PureFlexAreaListContainer HFPack;
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack);
		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;){
			SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumH>OKDotH && NGLen>OKLengthH){
				PureFlexAreaList *NextP=p->GetNext();
				HFPack.RemoveList(p);
				//ＮＧの場合
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap,GetDotPerLine(),GetMaxLines())==false){
					int	Cx,Cy;
					iSumH+=SumH;
					p->GetCenter(Cx,Cy);
					ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);
					r->result =0x30000;	//白側でNG
					r->SetResult1(SumH);
					r->SetResult2(NGLen);
					r->NGShape.SuckFrom(*p);
					PosList.AppendList(r);
					RNumb++;
					Error |= 0x20;	//白側でＮＧ
					HCount++;
				}
				delete	p;
				p=NextP;
			}
			else if(DrawResultDetail==true){
				PureFlexAreaList *NextP=p->GetNext();
				HFPack.RemoveList(p);
				//ＯＫだが、輝度で抽出した場合
				int	Cx,Cy;
				iSumH+=SumH;
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new ResultPosList(Cx,Cy ,0,0);
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumH>OKDotH){
					r->result =0x130;	//白側で輝度はＮＧ，面積はＮＧ
				}
				else if(NGLen>OKLengthH){
					r->result =0x120;	//白側で輝度はＮＧ，長さはＮＧ
				}
				else{
					r->result =0x110;	//白側で輝度はＮＧ、長さ面積ともＯＫ
				}
				PosList.AppendList(r);
				delete	p;
				p=NextP;
			}
			else{
				p=p->GetNext();
			}
		}
	}
	if(BackPointer!=BackDim){
		delete	[]BackDim;
	}

    if(pMapH!=BackBuffH)
        delete  []pMapH;
    if(pMapL!=BackBuffL)
        delete  []pMapL;

	if(UseMorphology==true){
		if(AllocpTempMap2D1==true){
			if(pTempMap2D1BackBuff!=TempMap2D1BackBuff){
				DeleteMatrixBuff(pTempMap2D1, Ly);
			}
		}
		if(pTempMap2D2BackBuff!=TempMap2D2BackBuff){
			DeleteMatrixBuff(pTempMap2D2, Ly);
		}
	}

	SumH=iSumH;
	SumL=iSumL;
	if(RNumb!=0)
		return false;
	return true;
}

void	StatisticBlockItem::DilateAndErode(BYTE *pMap
    	                                   ,BYTE **pTempMap2D1, BYTE **pTempMap2D2
    	                                   ,int Lx, int Ly)
{
	for(int by=0, idx=0; by<Ly; by++)
		for(int bx=0; bx<Lx; bx++, idx++)
			pTempMap2D1[by][bx] = pMap[idx];
	const StatisticBlockThreshold	*RThr=GetThresholdR();
	// モフォロジー
	bool EliminateAcnode  = RThr->EliminateAcnode;
	int	DilationDotCount  = RThr->DilationDotCount;
	int	ErosionDotCount   = RThr->ErosionDotCount;

	if(EliminateAcnode==true)		//孤立点の除去
		ThinAreaInACrossShape(pTempMap2D1, pTempMap2D2, Lx, Ly);
	for(int i=0; i<DilationDotCount; i++)	//膨張
		FatAreaInACrossShape(pTempMap2D1, pTempMap2D2, Lx, Ly);
	for(int i=0; i<ErosionDotCount; i++)	//収縮
		ThinAreaInACrossShape(pTempMap2D1, pTempMap2D2, Lx, Ly);

	for(int by=0, idx=0; by<Ly; by++)
		for(int bx=0; bx<Lx; bx++, idx++)
			pMap[idx] = pTempMap2D1[by][bx];
}

void	StatisticBlockItem::CheckOnNGInner1(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,int &LSum ,int &HSum
									,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	ImageBuffer &a=GetTargetBuff();
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	LSum=0;
	HSum=0;
	const StatisticBlockThreshold	*RThr=GetThresholdR();
	if(RThr->PointMove.ModeBlackMask==false
	&& RThr->PointMove.ModeWhiteMask==false){
		if(DynamicMaskMap==NULL){
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
							if(*p<LLevel){
								*qL|=(BYTE)Mask;
								LSum++;
							}
							if(HLevel<*p){
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
		}
		else{
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
				BYTE	*mask=DynamicMaskMap[Y+dy];
	
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
						int	tx=X+dx+x+k;
						if((mask[tx>>3]&(0x80>>(tx&7)))==0){
							if(qL>&pMapL[LByte])
								break;
							if(qL>=pMapL){
								if(*p<LLevel){
									*qL|=(BYTE)Mask;
									LSum++;
								}
								if(HLevel<*p){
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
	else if(RThr->PointMove.ModeBlackMask==true
		 && RThr->PointMove.ModeWhiteMask==false){
		if(DynamicMaskMap==NULL){
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
				BYTE	*qH=&(pMapH[Lx*mdy+((X-fa->GetMinX())>>3)]);
				unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));
	
				for(int x=0;x<Numb;x+=8){
					int N=8;
					if(x+8>=Numb)
						N=Numb-x;
					for(int k=0;k<N;k++,p++){
						if(qH>&pMapH[LByte])
							break;
						if(qH>=pMapH){
							if(HLevel<*p){
								*qH|=(BYTE)Mask;
								HSum++;
							}
						}
						Mask=_rotr(Mask,1);
						if((Mask &0x80)!=0){
							qH++;
						}
					}
				}
			}
		}
		else{
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
				BYTE	*mask=DynamicMaskMap[Y+dy];
	
				int px=X-fa->GetMinX();
				int mdy=Y-starty;
				BYTE	*p=a.GetY(dy+Y)+dx+X;
				BYTE	*qH=&(pMapH[Lx*mdy+((X-fa->GetMinX())>>3)]);
				unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));
	
				for(int x=0;x<Numb;x+=8){
					int N=8;
					if(x+8>=Numb)
						N=Numb-x;
					for(int k=0;k<N;k++,p++){
						int	tx=X+dx+x+k;
						if((mask[tx>>3]&(0x80>>(tx&7)))==0){
							if(qH>&pMapH[LByte])
								break;
							if(qH>=pMapH){
								if(HLevel<*p){
									*qH|=(BYTE)Mask;
									HSum++;
								}
							}
						}
						Mask=_rotr(Mask,1);
						if((Mask &0x80)!=0){
							qH++;
						}
					}
				}
			}
		}
	}
	else if(RThr->PointMove.ModeBlackMask==false
		 && RThr->PointMove.ModeWhiteMask==true){
		if(DynamicMaskMap==NULL){
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
				unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));
	
				for(int x=0;x<Numb;x+=8){
					int N=8;
					if(x+8>=Numb)
						N=Numb-x;
					for(int k=0;k<N;k++,p++){
						if(qL>&pMapL[LByte])
							break;
						if(qL>=pMapL){
							if(*p<LLevel){
								*qL|=(BYTE)Mask;
								LSum++;
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
		else{
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
				BYTE	*mask=DynamicMaskMap[Y+dy];
	
				int px=X-fa->GetMinX();
				int mdy=Y-starty;
				BYTE	*p=a.GetY(dy+Y)+dx+X;
				BYTE	*qL=&(pMapL[Lx*mdy+((X-fa->GetMinX())>>3)]);
				unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));
	
				for(int x=0;x<Numb;x+=8){
					int N=8;
					if(x+8>=Numb)
						N=Numb-x;
					for(int k=0;k<N;k++,p++){
						int	tx=X+dx+x+k;
						if((mask[tx>>3]&(0x80>>(tx&7)))==0){
							if(qL>&pMapL[LByte])
								break;
							if(qL>=pMapL){
								if(*p<LLevel){
									*qL|=(BYTE)Mask;
									LSum++;
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
	}
}

