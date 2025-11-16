/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XVIAInspectionAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "VIAFormResource.h"
#include "XViaInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XViaInspectionLibrary.h"
#include <stdlib.h>
#include "swap.h"
#include <omp.h>

#if defined(linux)
#include <x86intrin.h>
#endif // defined(linux)

const	int	MaxResultNGPointInVIA	=1000;
const	int	MaxReEntrantCount		=30000;
const	int	BLKMergin	=4;

static	int	DbgID=7036;
static	int	DbgLayer=1;
static	int	DbgNumer=0;

ExeResult	VIAItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	if(GetID()==DbgID && GetParent()->GetLayer()==DbgLayer)
		DbgNumer++;
	const VIAThreshold	*RThr=GetThresholdR();
	int	BrightWidthL=RThr->BrightWidthL;
	int	BrightWidthH=RThr->BrightWidthH;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	WORD	OKLengthL	=RThr->OKLengthL;
	WORD	OKLengthH	=RThr->OKLengthH;

	VIAInLayer	*P=(VIAInLayer *)GetParentInLayer();
	CenterBright=CalcCenterBright(GetTargetBuff(),mx,my);

	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			VIASendTryThreshold	*Q=dynamic_cast<VIASendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->Error=0;
			}
		}
	}

	short	Error=1;
	int		SumL,SumH;
	ResultPosListContainer PosList;
	if(CheckOnNG(mx,my
				, RThr->BrightWidthL,RThr->BrightWidthH
				, RThr->OKDotL		,RThr->OKDotH
				, RThr->MaxNGDotL	,RThr->MaxNGDotH
				,SumL,SumH
				,PosList
				,RThr->OKLengthL	,RThr->OKLengthH
				,RThr->ShrinkDot	,RThr->EnlargeDot
				,Error)==true){
		GetThresholdW()->AddHist(Hist_VIAInspection_CenterBright,CenterBright);
		Res->MovePosList(PosList);
		Res->SetAlignedXY(mx,my);
		Res->SetResult1(SumL);
		Res->SetResult2(SumH);
		Res->SetError(1);	//OK
	}
	else{
		GetThresholdW()->AddHist(Hist_VIAInspection_CenterBright,CenterBright);
		Res->MovePosList(PosList);
		Res->SetAlignedXY(mx,my);
		Res->SetResult1(SumL);
		Res->SetResult2(SumH);
		Res->SetError(2 | Error);	//NG
	}
							
	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			VIASendTryThreshold	*Q=dynamic_cast<VIASendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->NGDotInDark		=Res->GetResult1();
				Q->NGDotInBright	=Res->GetResult2();
				Q->Error			=Res->GetError();
			}
		}
	}
	FinishCalc();
	return _ER_true;
}


bool	VIAItem::CheckOnNG(int mx,int my
				, int BrightWidthL ,int BrightWidthH
				, int OKDotL ,int OKDotH
				,int MaxNGDotL ,int MaxNGDotH
				,int &SumL,int &SumH
				,ResultPosListContainer &PosList
				,WORD	OKLengthL
				,WORD	OKLengthH
				,WORD	ShrinkDot,WORD EnlargeDot
				,short &Error)
{
	SumL=0;
	SumH=0;
    int	RNumb=0;

	if(BrightWidthL<0)    BrightWidthL=0;
    if(BrightWidthH>255)  BrightWidthH=255;
    
    int LLevel; //=((ThS-ThA+127+ThOffset)>>8)+BrightOffset;
    int HLevel; //=((ThS+ThA+127+ThOffset)>>8)+BrightOffset;
    uchar   BackBuffH[50000];
    uchar   BackBuffL[50000];

	FlexArea	*fa=&GetArea();
    int starty =fa->GetFLineAbsY(0);

    int Lx=(fa->GetWidth()+1+7)>>3;
    int Ly=fa->GetHeight()+1;
    int LByte=Lx*Ly;

    BYTE   *pMapH=NULL;
    BYTE   *pMapL=NULL;

    if(LByte>sizeof(BackBuffH))
	    pMapH=new BYTE[LByte];
	else
		pMapH=BackBuffH;
	memset(pMapH,0,LByte);

	if(LByte>sizeof(BackBuffL))
	    pMapL=new BYTE[LByte];
	else
	    pMapL=BackBuffL;
	memset(pMapL,0,LByte);

	int	LSum,HSum;
    CheckOnNGInner1(mx ,my
                        ,BrightWidthL ,BrightWidthH
                        ,pMapL,pMapH
                        ,Lx ,Ly ,LByte,starty
						,LSum,HSum);

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

	BYTE **bitoperation=bitoperation=MakeMatrixBuff(Lx,Ly);

	try{
		BYTE   *pL=pMapL;
		for(int y=0;y<Ly;y++,pL+=Lx){
			BackDim[y]=pL;
		}
		for(int i=0;i<ShrinkDot;i++){
			ThinArea(BackDim,bitoperation,Lx, Ly);
		}
		for(int i=0;i<EnlargeDot;i++){
			FatArea(BackDim,bitoperation,Lx, Ly);
		}


		PureFlexAreaListContainer LFPack;
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,LFPack);
		for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;){
			SumL	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			if(SumL>OKDotL && SumL<MaxNGDotL && NGLen>OKLengthL){
				PureFlexAreaList *NextP=p->GetNext();
				LFPack.RemoveList(p);
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
					
				int	Cx,Cy;
				iSumL+=SumL;
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new VIAResultPosList(Cx,Cy ,0,0);
				r->result =0x20000;	//?????ANG
				if(SumL>OKDotL){
					r->result |=0x01;
				}
				if(NGLen>OKLengthL){
					r->result |=0x02;
				}
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				r->NGShape.SuckFrom(*p);
				PosList.AppendList(r);
				RNumb++;
				Error |= 0x10;	//?????A?m?f
				LCount++;

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
				ResultPosList	*r=new VIAResultPosList(Cx,Cy ,0,0);
				r->SetResult1(SumL);
				r->SetResult2(NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumL>OKDotL &&  NGLen>OKLengthL){
					r->result =0x30;	//?????A?P?x?I?m?f?C??E?3?I?n?j
				}
				else if(NGLen>OKLengthL){
					r->result =0x20;	//?????A?P?x?I?m?f?C?E?I?I?n?j
				}
				else{
					r->result =0x10;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
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
	catch(...){}

	try{
	    BYTE   *pH=pMapH;
		for(int y=0;y<Ly;y++,pH+=Lx){
			BackDim[y]=pH;
		}
		for(int i=0;i<ShrinkDot;i++){
			ThinArea(BackDim,bitoperation,Lx, Ly);
		}
		for(int i=0;i<EnlargeDot;i++){
			FatArea(BackDim,bitoperation,Lx, Ly);
		}

		PureFlexAreaListContainer HFPack;
		PickupFlexArea(BackDim,Lx,Lx*8,Ly,HFPack);
		for(PureFlexAreaList *p=HFPack.GetFirst();p!=NULL;){
			SumH	=p->GetPatternByte();
			int	NGLen	=max(p->GetWidth(),p->GetHeight());
			//if(SumH>OKDotH && NGLen>OKLengthH){
			if(SumH>OKDotH && SumH<MaxNGDotH && NGLen>OKLengthH){

				PureFlexAreaList *NextP=p->GetNext();
				HFPack.RemoveList(p);
				//?m?f?I?e??
				p->MoveToNoClip(fa->GetMinX(),fa->GetMinY());
				//if(DynamicMaskMap==NULL || p->CheckOverlapBit(DynamicMaskMap)==false){
				int	Cx,Cy;
				iSumH+=SumH;
				p->GetCenter(Cx,Cy);
				ResultPosList	*r=new VIAResultPosList(Cx,Cy ,0,0);
				r->result =0x30000;	//?????ANG
				if(SumH>OKDotH){
					r->result |=0x04;
				}
				if(NGLen>OKLengthH){
					r->result |=0x08;
				}
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
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
				ResultPosList	*r=new VIAResultPosList(Cx,Cy ,0,0);
				r->SetResult1(SumH);
				r->SetResult2(NGLen);
				r->NGShape.SuckFrom(*p);
				if(SumH>OKDotH && NGLen>OKLengthH){
					r->result =0x130;	//?????A?P?x?I?m?f?C?E?I?I?m?f
				}
				else if(NGLen>OKLengthH){
					r->result =0x120;	//?????A?P?x?I?m?f?C??E?3?I?m?f
				}
				else{
					r->result =0x110;	//?????A?P?x?I?m?f?A??E?3?E?I?A?a?n?j
				}
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
	catch(...){}

	if(BackPointer!=BackDim){
		delete	[]BackDim;
	}
	if(bitoperation!=NULL){
		DeleteMatrixBuff(bitoperation,Ly);
	}


    if(pMapH!=BackBuffH)
        delete  []pMapH;
    if(pMapL!=BackBuffL)
        delete  []pMapL;

	SumH=iSumH;
	SumL=iSumL;

	if(RNumb!=0)
		return false;

	return true;
}

void	VIAItem::CheckOnNGInner1(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,int &LSum,int &HSum)
{
	ImageBuffer &a=GetTargetBuff();
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	LSum=0;
	HSum=0;

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


WORD	VIAItem::CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my)
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

		FlexArea	*A=&GetArea();

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

		D/=N;
		return (WORD)D;
	}
}

