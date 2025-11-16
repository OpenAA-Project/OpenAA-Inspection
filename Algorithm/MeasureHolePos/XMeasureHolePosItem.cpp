/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureHolePos\XMeasureHolePos.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureHolePos.h"
#include "omp.h"

MeasureHolePosItemBase::MeasureHolePosItemBase(void)
{
	AVector=NULL;

	ResultHeightDiff=0.0;
	ResultWidthDiff	=0.0;
	ResultPosXDiff	=0.0;
	ResultPosYDiff	=0.0;
	RxTop	=0.0;
	RyTop	=0.0;
	RxLeft	=0.0;
	RyLeft	=0.0;
	RxRight	=0.0;
	RyRight	=0.0;
	RxBottom=0.0;
	RyBottom=0.0;

	AvrTopI		=0.0;
	AvrTopO		=0.0;
	AvrLeftI	=0.0;
	AvrLeftO	=0.0;
	AvrRightI	=0.0;
	AvrRightO	=0.0;
	AvrBottomI	=0.0;
	AvrBottomO	=0.0;

	AMx=AMy		=0;
	MasterDiameterX=MasterDiameterY=0;
	MasterPosX	=0;
	MasterPosY	=0;
}

AlgorithmItemPI	&MeasureHolePosItemBase::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	const MeasureHolePosItemBase	*s=dynamic_cast<const MeasureHolePosItemBase *>(&src);
	if(s!=NULL){
		AreaEdgeTop		=s->AreaEdgeTop;
		AreaEdgeLeft	=s->AreaEdgeLeft;
		AreaEdgeRight	=s->AreaEdgeRight;
		AreaEdgeBottom	=s->AreaEdgeBottom;

		MasterDiameterX	=s->MasterDiameterX;
		MasterDiameterY	=s->MasterDiameterY;
		MasterPosX		=s->MasterPosX;
		MasterPosY		=s->MasterPosY;

		AreaTopI	=s->AreaTopI;
		AreaTopO	=s->AreaTopO;
		AvrTopI		=s->AvrTopI;
		AvrTopO		=s->AvrTopO;

		AreaLeftI	=s->AreaLeftI;
		AreaLeftO	=s->AreaLeftO;
		AvrLeftI	=s->AvrLeftI;
		AvrLeftO	=s->AvrLeftO;

		AreaRightI	=s->AreaRightI;
		AreaRightO	=s->AreaRightO;
		AvrRightI	=s->AvrRightI;
		AvrRightO	=s->AvrRightO;

		AreaBottomI	=s->AreaBottomI;
		AreaBottomO	=s->AreaBottomO;
		AvrBottomI	=s->AvrBottomI;
		AvrBottomO	=s->AvrBottomO;

		AMx			=s->AMx;
		AMy			=s->AMy;
	}
	return *this;
}

bool    MeasureHolePosItemBase::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(::Save(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	if(::Save(f,MasterDiameterX)==false)
		return false;
	if(::Save(f,MasterDiameterY)==false)
		return false;
	if(::Save(f,MasterPosX)==false)
		return false;
	if(::Save(f,MasterPosY)==false)
		return false;
	//if(::Save(f,ItemName)==false)
	//	return false;

	return true;
}

bool    MeasureHolePosItemBase::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	if(::Load(f,MasterDiameterX)==false)
		return false;
	if(::Load(f,MasterDiameterY)==false)
		return false;
	if(::Load(f,MasterPosX)==false)
		return false;
	if(::Load(f,MasterPosY)==false)
		return false;

	if(Ver==2){
		QString	tItemName;
		if(::Load(f,tItemName)==false)
			return false;
		SetItemName(tItemName);
	}

	return true;
}
ExeResult	MeasureHolePosItemBase::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

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
	const MeasureHolePosThreshold	*RThr=GetThresholdR();

	if(RThr->CalcMode==0){
		ImageBuffer *ImageListMaster[10];
		int	MasterNumb=GetMasterBuffList(ImageListMaster);
		ImageBuffer *ImageListTarget[10];
		int	TargetNumb=GetTargetBuffList(ImageListTarget);
		CalcCoefOne(AreaEdgeTop, mx ,my ,RxTop ,RyTop ,ImageListTarget
					,AreaTopI,AvrTopI
					,AreaTopO,AvrTopO);
		CalcCoefOne(AreaEdgeLeft, mx ,my ,RxLeft ,RyLeft,ImageListTarget
					,AreaLeftI,AvrLeftI
					,AreaLeftO,AvrLeftO);
		CalcCoefOne(AreaEdgeRight, mx ,my ,RxRight ,RyRight,ImageListTarget
					,AreaRightI,AvrRightI
					,AreaRightO,AvrRightO);
		CalcCoefOne(AreaEdgeBottom, mx ,my ,RxBottom ,RyBottom,ImageListTarget
					,AreaBottomI,AvrBottomI
					,AreaBottomO,AvrBottomO);

		ResultHeightDiff=RyBottom - RyTop;
		ResultWidthDiff	=RxRight - RxLeft;
		ResultPosXDiff	=(RxRight + RxLeft)/2.0;
		ResultPosYDiff	=(RyBottom+ RyTop )/2.0;

		Res->SetAlignedXY(mx,my);
		AMx=mx;
		AMy=my;
		Res->SetItemSearchedXY(ResultPosXDiff,ResultPosYDiff);
		Res->SetResult1(0);
		Res->SetResult2(0);
		if(ResultHeightDiff>RThr->DiaPrecision){
			Res->SetError(2);	//NG
		}
		if(ResultWidthDiff>RThr->DiaPrecision){
			Res->SetError(2);	//NG
		}
		if(ResultPosXDiff>RThr->PosPrecision){
			Res->SetError(2);	//NG
		}
		if(ResultPosYDiff>RThr->PosPrecision){
			Res->SetError(2);	//NG
		}
	}
	else if(RThr->CalcMode==1){
		ImageBuffer *ImageListTarget[10];
		int	TargetNumb=GetTargetBuffList(ImageListTarget);
		ExecuteProcessingPrecise(Res,ImageListTarget,TargetNumb);
	}
	SetCalcDone(true);
	return _ER_true;
}

ExeResult	MeasureHolePosItemBase::ExecuteProcessingPrecise(ResultInItemRoot *Res,ImageBuffer *ImageList[],int ImageNumb)
{
	const MeasureHolePosThreshold	*RThr=GetThresholdR();
	int	Step1=2;
	double	MaxD=0;
	double	MaxdRx,MaxdRy;
	double	MaxdCx,MaxdCy;

	int	MinRx=PreciseMasterRx-RThr->SearchDot;
	if(MinRx<3){
		MinRx=3;
	}
	MinRx=PreciseMasterRx-MinRx;
	int	MinRy=PreciseMasterRy-RThr->SearchDot;
	if(MinRy<3){
		MinRy=3;
	}
	MinRy=PreciseMasterRy-MinRy;

	for(int dRy=-MinRy;dRy<=RThr->SearchDot;dRy+=Step1){
		for(int dRx=-MinRx;dRx<=RThr->SearchDot;dRx+=Step1){
			for(int dCy=-RThr->SearchDot;dCy<=RThr->SearchDot;dCy+=Step1){
				for(int dCx=-RThr->SearchDot;dCx<=RThr->SearchDot;dCx+=Step1){
					double	D=PreciseCalc(PreciseMasterCx+dCx,PreciseMasterCy+dCy
										, PreciseMasterRx+dRx,PreciseMasterRy+dRy
										, RThr->BandWidth
										, ImageList,ImageNumb);
					if(MaxD<D){
						MaxD=D;
						MaxdRx=dRx;
						MaxdRy=dRy;
						MaxdCx=dCx;
						MaxdCy=dCy;
					}
				}
			}
		}
	}
	MaxD=0;
	double	sMaxdRx,sMaxdRy;
	double	sMaxdCx,sMaxdCy;
	for(int dRy=-Step1;dRy<=Step1;dRy++){
		for(int dRx=-Step1;dRx<=Step1;dRx++){
			for(int dCy=-Step1;dCy<=Step1;dCy++){
				for(int dCx=-Step1;dCx<=Step1;dCx++){
					double	D=PreciseCalc(PreciseMasterCx+MaxdCx+dCx,PreciseMasterCy+MaxdCy+dCy
										, PreciseMasterRx+MaxdRx+dRx,PreciseMasterRy+MaxdRy+dRy
										, RThr->BandWidth
										, ImageList,ImageNumb);
					if(MaxD<D){
						MaxD=D;
						sMaxdRx=dRx;
						sMaxdRy=dRy;
						sMaxdCx=dCx;
						sMaxdCy=dCy;
					}
				}
			}
		}
	}
	MaxD=0;
	MaxdCx+=sMaxdCx;
	MaxdCy+=sMaxdCy;
	MaxdRx+=sMaxdRx;
	MaxdRy+=sMaxdRy;
	double	FloatStep=0.1;
	for(double dRy=-1;dRy<=1;dRy+=FloatStep){
		for(double dRx=-1;dRx<=1;dRx+=FloatStep){
			for(double dCy=-1;dCy<=1;dCy+=FloatStep){
				for(double dCx=-1;dCx<=1;dCx+=FloatStep){
					double	D=PreciseCalc(PreciseMasterCx+MaxdCx+dCx,PreciseMasterCy+MaxdCy+dCy
										, PreciseMasterRx+MaxdRx+dRx,PreciseMasterRy+MaxdRy+dRy
										, RThr->BandWidth
										, ImageList,ImageNumb);
					if(MaxD<D){
						MaxD=D;
						sMaxdRx=dRx;
						sMaxdRy=dRy;
						sMaxdCx=dCx;
						sMaxdCy=dCy;
					}
				}
			}
		}
	}
	PreciseTargetCx=PreciseMasterCx+MaxdCx+sMaxdCx;
	PreciseTargetCy=PreciseMasterCy+MaxdCy+sMaxdCy;
	PreciseTargetRx=PreciseMasterRx+MaxdRx+sMaxdRx;
	PreciseTargetRy=PreciseMasterRy+MaxdRy+sMaxdRy;

	SetCalcDone(true);
	return _ER_true;
}
double	MeasureHolePosItemBase::PreciseCalc( double Cx,double Cy ,double Rx, double Ry
											,int BandWidth
											,ImageBuffer *ImageList[],int ImageNumb)
{
	int	MinX=floor(Cx-Rx)-BandWidth;
	int	MaxX=ceil (Cx+Rx)+BandWidth;
	int	MinY=floor(Cy-Ry)-BandWidth;
	int	MaxY=ceil (Cy+Ry)+BandWidth;

	if(MinX<0)
		MinX=0;
	if(MinY<0)
		MinY=0;
	if(MaxX>=GetDotPerLine()){
		MaxX=GetDotPerLine()-1;
	}
	if(MaxY>=GetMaxLines()){
		MaxY=GetMaxLines()-1;
	}
	double	NRx2=1.0/(Rx*Rx);
	double	NRy2=1.0/(Ry*Ry);
	double	ORx2=1.0/((Rx+BandWidth)*(Rx+BandWidth));
	double	ORy2=1.0/((Ry+BandWidth)*(Ry+BandWidth));
	double	IRx2=1.0/((Rx-BandWidth)*(Rx-BandWidth));
	double	IRy2=1.0/((Ry-BandWidth)*(Ry-BandWidth));

	double	AddedO[4];
	double	AddedI[4];
	double	AddedO2[4];
	double	AddedI2[4];
	double	AreaO[4];
	double	AreaI[4];

	for(int i=0;i<4;i++){
		AddedO[i]=0;
		AddedI[i]=0;
		AddedO2[i]=0;
		AddedI2[i]=0;
		AreaO[i]=0;
		AreaI[i]=0;
	}

	for(int y=MinY;y<=MaxY;y++){
		BYTE	*p=ImageList[0]->GetY(y);
		for(int x=MinX;x<=MaxX;x++){
			double	x2=(x-Cx)*(x-Cx);
			double	y2=(y-Cy)*(y-Cy);
			double	L =x2*NRx2+y2*NRy2;
			double	LO=x2*ORx2+y2*ORy2;
			double	LI=x2*IRx2+y2*IRy2;
			if(L<=1.0 && LI>=1.0){
				double	s=GetSita(x-Cx,y-Cy);
				if(s<=M_PI/4.0 || 7*M_PI/4.0<=s){
					AreaI[0]+=1.0;
					AddedI[0]+=p[x];
					AddedI2[0]+=p[x]*p[x];
				}
				else
				if(s<=3.0*M_PI/4.0){
					AreaI[1]+=1.0;
					AddedI[1]+=p[x];
					AddedI2[1]+=p[x]*p[x];
				}
				else
				if(s<=5.0*M_PI/4.0){
					AreaI[2]+=1.0;
					AddedI[2]+=p[x];
					AddedI2[2]+=p[x]*p[x];
				}
				else
				if(s<=7.0*M_PI/4.0){
					AreaI[3]+=1.0;
					AddedI[3]+=p[x];
					AddedI2[3]+=p[x]*p[x];
				}
			}
			else
			if (L>=1.0 && LO<=1.0) {
				double	s=GetSita(x-Cx,y-Cy);
				if(s<=M_PI/4.0 || 7*M_PI/4.0<=s){
					AreaO[0]+=1.0;
					AddedO[0]+=p[x];
					AddedO2[0]+=p[x]*p[x];
				}
				else
				if(s<=3.0*M_PI/4.0){
					AreaO[1]+=1.0;
					AddedO[1]+=p[x];
					AddedO2[1]+=p[x]*p[x];
				}
				else
				if(s<=5.0*M_PI/4.0){
					AreaO[2]+=1.0;
					AddedO[2]+=p[x];
					AddedO2[2]+=p[x]*p[x];
				}
				else
				if(s<=7.0*M_PI/4.0){
					AreaO[3]+=1.0;
					AddedO[3]+=p[x];
					AddedO2[3]+=p[x]*p[x];
				}
			}
		}
	}
	double	Dif=0;
	int		DifNumb=0;
	for(int i=0;i<4;i++){
		if(AreaO[i]>0 && AreaI[i]>0){
			double	AvrI=AddedI[i]/AreaI[i];
			double	AvrO=AddedO[i]/AreaO[i];
			double	VarI=(AddedI2[i]-AvrI*AvrI*AreaI[i])/AreaI[i];
			//double	VarO=(AddedO2[i]-AvrO*AvrO*AreaO[i])/AreaO[i];

			Dif+=AvrI*AvrI*AvrI/AvrO/sqrt(VarI);
			DifNumb++;
		}
	}
	if(DifNumb>0){
		return Dif/DifNumb;
	}
	return 0;
}

void	MeasureHolePosItemBase::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::MoveTo(GlobalDx,GlobalDy);
		AreaEdgeTop.MoveToNoClip(GlobalDx,GlobalDy);
		AreaEdgeLeft.MoveToNoClip(GlobalDx,GlobalDy);
		AreaEdgeRight.MoveToNoClip(GlobalDx,GlobalDy);
		AreaEdgeBottom.MoveToNoClip(GlobalDx,GlobalDy);

		AreaTopI.MoveToNoClip(GlobalDx,GlobalDy);
		AreaTopO.MoveToNoClip(GlobalDx,GlobalDy);

		AreaLeftI.MoveToNoClip(GlobalDx,GlobalDy);
		AreaLeftO.MoveToNoClip(GlobalDx,GlobalDy);

		AreaRightI.MoveToNoClip(GlobalDx,GlobalDy);
		AreaRightO.MoveToNoClip(GlobalDx,GlobalDy);

		AreaBottomI.MoveToNoClip(GlobalDx,GlobalDy);
		AreaBottomO.MoveToNoClip(GlobalDx,GlobalDy);

		MasterPosX	+=GlobalDx;
		MasterPosY	+=GlobalDy;
	}
}

void	MeasureHolePosItemBase::CalcCoefOne(FlexAreaImageListCoeff &EArea, int mx ,int my ,double &Rx ,double &Ry
											,ImageBuffer *ImageListTarget[]
											,FlexArea &AreaInside ,double MasterColorI
											,FlexArea &AreaOutside ,double MasterColorO)
{
	double	MaxD=0.0;
	int	MaxDx=0;
	int	MaxDy=0;
	double	dMaxDx=0;
	double	dMaxDy=0;
	double	dMaxCI=0;
	double	dMaxCO=0;
	const MeasureHolePosThreshold	*RThr=GetThresholdR();
	if(GetLayerNumb()==1){
		for(int dy=-RThr->SearchDot;dy<=RThr->SearchDot;dy++){
			for(int dx=-RThr->SearchDot;dx<=RThr->SearchDot;dx++){
				double	d=fabs(EArea.CalcCoeff(	 mx+dx
												,my+dy
												,*ImageListTarget[0]));	//‘ŠŒÝ‘ŠŠÖ‚ÌŒvŽZ
				double	ci=AreaInside	.GetAverage(*ImageListTarget[0],mx+dx,my+dy);
				double	co=AreaOutside	.GetAverage(*ImageListTarget[0],mx+dx,my+dy);
				double	M=d*ExpFunc(ci,MasterColorI)*ExpFunc(co,MasterColorO);
				if(M>MaxD){
					MaxDx=dx;
					MaxDy=dy;
					MaxD=M;
					dMaxCI=ci;
					dMaxCO=co;
				}
			}
		}

		MaxD=0.0;
		for(double dy=-0.9;dy<0.999;dy+=0.1){
			for(double dx=-0.9;dx<0.999;dx+=0.1){
				double	d=fabs(EArea.CalcCoeff(	 mx+MaxDx+dx
												,my+MaxDy+dy
												,*ImageListTarget[0]));	//‘ŠŒÝ‘ŠŠÖ‚ÌŒvŽZ
				double	ci=AreaInside	.GetAverage(*ImageListTarget[0],mx+MaxDx+dx,my+MaxDy+dy);
				double	co=AreaOutside	.GetAverage(*ImageListTarget[0],mx+MaxDx+dx,my+MaxDy+dy);
				double	M=d*ExpFunc(ci,MasterColorI)*ExpFunc(co,MasterColorO);
				if(M>MaxD){
					dMaxDx=dx;
					dMaxDy=dy;
					MaxD=M;
					dMaxCI=ci;
					dMaxCO=co;
				}
			}
		}
	}
	Rx=MaxDx+dMaxDx;
	Ry=MaxDy+dMaxDy;
}

double	MeasureHolePosItemBase::ExpFunc(double c ,double MasterC)
{
	if(MasterC>0.0){
		double	k=(c-MasterC)/MasterC/0.1;	//10%‚Ì•Ï‰»‚Å‚P
		double	p=exp(-(k*k));
		return p;
	}
	double	p=exp(-(c*c));
	return p;
}
double	MeasureHolePosItemBase::GetSemiCoeff(FlexArea &EArea 
										,ImageBuffer &Src 
										,double dx ,double dy 
										,ImageBuffer &Dst)	//‘ŠŒÝ‘ŠŠÖ‚ÌŒvŽZ
{
	double	SumS=0;
	double	SumD=0;
	double	SumSS=0;
	double	SumDD=0;
	double	SumSD=0;
	int		SDCount=0;

	int	DxN=floor(dx);
	double	DxF=dx-DxN;
	int	DyN=floor(dy);
	double	DyF=dx-DyN;

	int	NLen=EArea.GetFLineLen();
	#pragma omp parallel for reduction(+:SDCount,SumS,SumD,SumSS,SumDD,SumSD)
	for(int i=0;i<NLen;i++){
		int SrcX1=EArea.GetFLineLeftX (i);
		int SrcX2=EArea.GetFLineRightX(i);
		int SrcY =EArea.GetFLineAbsY	(i);

		int DstX1=SrcX1+DxN;
		int DstX2=SrcX2+DxN;
		int	DstY =SrcY +DyN;

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
		BYTE	*dL=Dst.GetY(DstY);
		BYTE	*dH=Dst.GetY(DstY+1);
		int	xs,xd;
		int	tSumS=0;
		double	tSumD=0;
		int	tSumSS=0;
		double	tSumDD=0;
		double	tSumSD=0;
		for(xs=SrcX1,xd=DstX1;xs<SrcX2 && xd<DstX2;xs++,xd++){
			tSumS	+=s[xs];
			tSumSS	+=((int)s[xs])*((int)s[xs]);
			int	d1=dL[xd];
			int	d2=dL[xd+1];
			int	d3=dH[xd];
			int	d4=dH[xd+1];
			double	d=(d1*(1.0-DxF)+d2*DxF)*(1.0-DyF)+(d3*(1.0-DxF)+d4*DxF)*DyF;
			tSumD	+=d;
			tSumDD	+=(d*d);
			tSumSD	+=((int)s[xs])*((int)d);
			SDCount++;
		}
		SumS+=tSumS;
		SumD+=tSumD;
		SumSS+=tSumSS;
		SumDD+=tSumDD;
		SumSD+=tSumSD;
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=SumS/SDCount;
	double	AvrD=SumD/SDCount;

	double	D=(SumSS-SDCount*AvrS*AvrS)*(SumDD-SDCount*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=SumSD-SDCount*AvrS*AvrD;
	return K/D;
}

void	MeasureHolePosItemBase::MakeIdeal(FlexAreaImageListCoeff &Area)
{
	int	KLen=Area.GetFLineLen();
	BYTE	*D=Area.GetData();
	double	Rx2=MasterDiameterX*MasterDiameterX/4.0;
	double	Ry2=MasterDiameterY*MasterDiameterY/4.0;
	for(int i=0;i<KLen;i++){
		int	y	=Area.GetFLineAbsY (i);
		int	x1	=Area.GetFLineLeftX(i);
		int	numb=Area.GetFLineNumb (i);
		for(int n=0;n<numb;n++){
			int	x=x1+n;
			double	t=(x-MasterPosX)*(x-MasterPosX)/Rx2
					 +(y-MasterPosY)*(y-MasterPosY)/Ry2;
			if(t<=1){
				*D=0xFF;
			}
			else{
				*D=0;
			}
			D++;
		}
	}
}
void	MeasureHolePosItemBase::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MeasureHolePosInPage	*Pg=dynamic_cast<MeasureHolePosInPage *>(GetParentInPage());
			UndoElement<MeasureHolePosInPage>	*UPointer=new UndoElement<MeasureHolePosInPage>(Pg,&MeasureHolePosInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((MeasureHolePosItemBase *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MeasureHolePosItemBase *)Data)->GetLibID()){
			MeasureHolePosInPage	*Pg=dynamic_cast<MeasureHolePosInPage *>(GetParentInPage());
			UndoElement<MeasureHolePosInPage>	*UPointer=new UndoElement<MeasureHolePosInPage>(Pg,&MeasureHolePosInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((MeasureHolePosItemBase *)Data));
		}
	}
}
void	MeasureHolePosItemBase::CopyThresholdOnly(MeasureHolePosItemBase &src)
{
	GetThresholdW()->CopyFrom(*((MeasureHolePosThreshold *)src.GetThresholdR()));
}

//===========================================================================

MeasureHolePosItem::MeasureHolePosItem(void)
{
}

AlgorithmItemPI	&MeasureHolePosItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureHolePosItemBase::operator=(src);

	const MeasureHolePosItem	*s=dynamic_cast<const MeasureHolePosItem *>(&src);
	if(s!=NULL){
		AreaHole=s->AreaHole;
	}
	return *this;
}

bool    MeasureHolePosItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(MeasureHolePosItemBase::Save(f)==false)
		return false;

	return true;
}
bool    MeasureHolePosItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(MeasureHolePosItemBase::Load(f,LBase)==false)
		return false;

	return true;
}

ExeResult	MeasureHolePosItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	int	EdgeWidth=10;
	const MeasureHolePosThreshold	*RThr=GetThresholdR();
	int	XLen=GetArea().GetWidth()+16+RThr->NoiseSize*4+EdgeWidth*2;
	int	YLen=GetArea().GetHeight()+8+RThr->NoiseSize*4+EdgeWidth*2;
	int	XTop=GetArea().GetMinX()-8	-RThr->NoiseSize*2-EdgeWidth;
	int	YTop=GetArea().GetMinY()-4	-RThr->NoiseSize*2-EdgeWidth;

	MeasureHolePosBase	*BBase=(MeasureHolePosBase *)GetParentBase();
	if(XTop<0){
		XLen+=XTop;
		XTop=0;
	}
	if(YTop<0){
		YLen+=YTop;
		YTop=0;
	}
	if(XTop+XLen>GetDotPerLine()){
		XLen=GetDotPerLine()-XTop;
	}
	if(YTop+YLen>GetMaxLines()){
		YLen=GetMaxLines()-YTop;
	}
	int	XByte=(XLen+7)/8;

	BYTE	**SBmp	=MakeMatrixBuff(XByte,YLen);
	BYTE	**SBmp2	=MakeMatrixBuff(XByte,YLen);
	BYTE	**SBmp3	=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(SBmp,0,XByte,YLen);

	ColorLogic	&CLogic=GetThresholdW()->HoleColor;
	ImageBuffer *ImageList[10];

	GetMasterBuffList(ImageList);

	if(GetLayerNumb()==1){
		for(int y=0;y<YLen;y++){
			BYTE	*s0=ImageList[0]->GetY(YTop+y);
			BYTE	*d=SBmp[y];
			for(int x=0;x<XLen;x++){
				if(CLogic.Calc(*(s0+XTop+x),*(s0+XTop+x),*(s0+XTop+x),0)==true){
					d[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
	else if(GetLayerNumb()==2){
		for(int y=0;y<YLen;y++){
			BYTE	*s0=ImageList[0]->GetY(YTop+y);
			BYTE	*s1=ImageList[1]->GetY(YTop+y);
			BYTE	*d=SBmp[y];
			for(int x=0;x<XLen;x++){
				if(CLogic.Calc(*(s0+XTop+x),*(s1+XTop+x),*(s1+XTop+x),0)==true){
					d[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
	else if(GetLayerNumb()>=3){
		for(int y=0;y<YLen;y++){
			BYTE	*s0=ImageList[0]->GetY(YTop+y);
			BYTE	*s1=ImageList[1]->GetY(YTop+y);
			BYTE	*s2=ImageList[2]->GetY(YTop+y);
			BYTE	*d=SBmp[y];
			for(int x=0;x<XLen;x++){
				if(CLogic.Calc(*(s0+XTop+x),*(s1+XTop+x),*(s2+XTop+x),0)==true){
					d[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}

	//MatrixBuffNot	(SBmp ,XByte ,YLen);

	GetLayersBase()->FatAreaN (SBmp
				,SBmp2
				,XByte, YLen
				,RThr->NoiseSize);
	GetLayersBase()->ThinAreaN(SBmp
				,SBmp2
				,XByte, YLen
				,RThr->NoiseSize*2);
	GetLayersBase()->FatAreaN (SBmp
				,SBmp2
				,XByte, YLen
				,RThr->NoiseSize);
	
	PureFlexAreaListContainer FPack;
	PickupFlexArea(SBmp ,XByte ,XLen,YLen ,FPack);

	PureFlexAreaList *MaxF=NULL;
	int64	MaxN=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		int64	n=f->GetPatternByte();
		if(n>MaxN){
			MaxN=n;
			MaxF=f;
		}
	}

	AreaHole		.Clear();
	AreaEdgeTop		.Clear();
	AreaEdgeLeft	.Clear();
	AreaEdgeRight	.Clear();
	AreaEdgeBottom	.Clear();

	if(MaxF!=NULL){
		AreaHole=*MaxF;
		AreaHole.MoveToNoClip(XTop,YTop);

		int	cx,cy;
		AreaHole.GetCenter(cx,cy);
		AreaHole.GetCenter(MasterPosX,MasterPosY);
		MasterDiameterX=sqrt(AreaHole.GetPatternByte()*4/M_PI);
		MasterDiameterY=MasterDiameterX;

		AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
		if(AVector!=NULL)
			AVector->Set(this);

		MatrixBuffClear(SBmp,0,XByte,YLen);
		MaxF->MakeBitData(SBmp,XLen,YLen);
		MatrixBuffCopy	(SBmp2,XByte,YLen
						,(const BYTE **)SBmp ,XByte,YLen);

		GetLayersBase()->FatAreaN (SBmp
					,SBmp3
					,XByte, YLen
					,EdgeWidth);
		GetLayersBase()->ThinAreaN(SBmp2
					,SBmp3
					,XByte, YLen
					,EdgeWidth);

		MatrixBuffXor	(SBmp,(const BYTE **)SBmp2,XByte, YLen);


		int	Cx=XLen/2;
		int	Cy=YLen/2;

		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y>=y1 && Y>=y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeBottom=*((FlexArea *)t);
				AreaEdgeBottom.MoveToNoClip(XTop,YTop);
			}
		}
		catch(...){}

		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=1.0/sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y<y1 && Y>=y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeRight=*t;
				AreaEdgeRight.MoveToNoClip(XTop,YTop);
			}
		}

		catch(...){}
		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y<y1 && Y<y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeTop=*t;
				AreaEdgeTop.MoveToNoClip(XTop,YTop);
			}
		}
		catch(...){}

		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=1.0/sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y>=y1 && Y<y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeLeft=*t;
				AreaEdgeLeft.MoveToNoClip(XTop,YTop);
			}
		}
		catch(...){}
	}
	DeleteMatrixBuff(SBmp,YLen);
	DeleteMatrixBuff(SBmp2,YLen);
	DeleteMatrixBuff(SBmp3,YLen);
	
	return _ER_true;
}

double	MeasureHolePosItem::GetTParam(double x1 ,double y1 ,double x2 ,double y2)
/*
	a*x+b*y+c=0
	a*a+b*b=1
	a*x1+b*y1+c=0
	a*x2+b*y2+c=0
	a(x2-x1)+b(y2-y1)=0;
*/
{
	double	Cx,Cy;
	AreaHole.GetCenter(Cx,Cy);
	double	dx=x2-x1;
	double	dy=y2-y1;
	double	L=hypot(dx,dy);
	double	a=-dy/L;
	double	b=dx/L;
	double	c=-a*x1-b*y1;
	return a*Cx+b*Cy+c;
}

void	MeasureHolePosItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		MeasureHolePosItemBase::ExecuteMove(GlobalDx,GlobalDy,AllItems);
		AreaHole.MoveToNoClip(GlobalDx,GlobalDy);
	}
}

void	MeasureHolePosItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MeasureHolePosDrawAttr	*BAttr=dynamic_cast<MeasureHolePosDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->DMode==MeasureHolePosDrawAttr::__Mode_Area)
			AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		else if(BAttr->DMode==MeasureHolePosDrawAttr::__Mode_Hole)
			AlgorithmItemPI::DrawArea(AreaHole,pnt, movx ,movy ,ZoomRate ,BAttr);
		else if(BAttr->DMode==MeasureHolePosDrawAttr::__Mode_Edge){
			AlgorithmItemPI::DrawArea(AreaEdgeTop	,pnt, movx ,movy ,ZoomRate ,BAttr);
			AlgorithmItemPI::DrawArea(AreaEdgeLeft	,pnt, movx ,movy ,ZoomRate ,BAttr);
			AlgorithmItemPI::DrawArea(AreaEdgeRight	,pnt, movx ,movy ,ZoomRate ,BAttr);
			AlgorithmItemPI::DrawArea(AreaEdgeBottom,pnt, movx ,movy ,ZoomRate ,BAttr);

			AreaEdgeTop		.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
			AreaEdgeLeft	.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
			AreaEdgeRight	.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
			AreaEdgeBottom	.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	MeasureHolePosItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			AreaHole.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(ZoomRate>1.0){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/" HDiff(")+QString::number(ResultHeightDiff,'g',2)+QString(/**/")")
						,&rect);
					PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/" WDiff(")+QString::number(ResultWidthDiff,'g',2)+QString(/**/")")
						,&rect);
					PData.drawText(kx,ky+32,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/" XPos(")+QString::number(ResultPosXDiff,'g',2)+QString(/**/")")
						,&rect);
					PData.drawText(kx,ky+48,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/" YPos(")+QString::number(ResultPosYDiff,'g',2)+QString(/**/")")
						,&rect);
					
				}
			}
		}
	}
}

double	MeasureHolePosItem::GetIsolation(double x ,double y)
{
	double	D=hypot(x-MasterPosX,y-MasterPosY);
	if(D<MasterDiameterX/2){
		return 0;
	}
	return D;
}
double	MeasureHolePosItem::GetDrawParam(double x ,double y)
{
	return 0;
}

void	MeasureHolePosItem::GetDrawPoint(double Param ,double &x ,double &y)
{
	x=MasterPosX;
	y=MasterPosY;
}

void	MeasureHolePosItem::GetShiftVector(double &sx, double &sy)
{
	sx=ResultPosXDiff;
	sy=ResultPosYDiff;
}

void	MeasureHolePosItem::GetCenterPoint(double &cx, double &cy)
{
	cx=MasterPosX;
	cy=MasterPosY;
}

void	MeasureHolePosItem::Move(double dx ,double dy)
{
	ExecuteMove(dx,dy,true);
}


//===========================================================================

MeasureHolePosVectorItem::MeasureHolePosVectorItem(void)
{
}

AlgorithmItemPI	&MeasureHolePosVectorItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureHolePosItemBase::operator=(src);

	const MeasureHolePosItem	*s=dynamic_cast<const MeasureHolePosItem *>(&src);
	if(s!=NULL){
	}
	return *this;
}

bool    MeasureHolePosVectorItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(MeasureHolePosItemBase::Save(f)==false)
		return false;

	return true;
}
bool    MeasureHolePosVectorItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(MeasureHolePosItemBase::Load(f,LBase)==false)
		return false;

	return true;
}

ExeResult	MeasureHolePosVectorItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	int	EdgeWidth=10;
	VectorLineEllipse	*V=(VectorLineEllipse *)GetVector();

	if(V!=NULL){
		double	Rx,Ry;
		V->GetEllipse(MasterPosX,MasterPosY,Rx ,Ry);
		MasterDiameterX=Rx*2.0;
		MasterDiameterY=Ry*2.0;

		ExecuteInitialAfterEditInner(EInfo);

		ImageBuffer *ImageListMaster[10];
		GetMasterBuffList(ImageListMaster);

		double RxTop ,RyTop;
		CalcCoefOne(AreaEdgeTop, 0 ,0 ,RxTop ,RyTop ,ImageListMaster
				,AreaTopI,AvrTopI
				,AreaTopO,AvrTopO);

		double RxLeft ,RyLeft;
		CalcCoefOne(AreaEdgeLeft, 0,0 ,RxLeft ,RyLeft,ImageListMaster
				,AreaLeftI,AvrLeftI
				,AreaLeftO,AvrLeftO);

		double RxRight ,RyRight;
		CalcCoefOne(AreaEdgeRight, 0 ,0 ,RxRight ,RyRight,ImageListMaster
				,AreaRightI,AvrRightI
				,AreaRightO,AvrRightO);

		double RxBottom ,RyBottom;
		CalcCoefOne(AreaEdgeBottom, 0,0 ,RxBottom ,RyBottom,ImageListMaster
				,AreaBottomI,AvrBottomI
				,AreaBottomO,AvrBottomO);

		double	Ay1=MasterPosY-MasterDiameterY+RyTop;
		double	Ax1=MasterPosX-MasterDiameterX+RxLeft;
		double	Ay2=MasterPosY+MasterDiameterY+RyBottom;
		double	Ax2=MasterPosX+MasterDiameterX+RxRight;

		MasterPosX=(Ax1+Ax2)/2.0;
		MasterPosY=(Ay1+Ay2)/2.0;
		MasterDiameterX	=Ax2-MasterPosX;
		MasterDiameterY	=Ay2-MasterPosY;

		ExecuteInitialAfterEditInner(EInfo);
	}

	GetCenter(PreciseMasterCx,PreciseMasterCy);
	int	Hx1,Hy1,Hx2,Hy2;
	GetXY(Hx1,Hy1,Hx2,Hy2);
	PreciseMasterRx=(Hx2-Hx1)/2;
	PreciseMasterRy=(Hy2-Hy1)/2;

	ImageBuffer *ImageListMaster[10];
	int	ImageNumb=GetMasterBuffList(ImageListMaster);
	ExecuteProcessingPrecise(Res,ImageListMaster,ImageNumb);
	
	PreciseMasterCx=PreciseTargetCx;
	PreciseMasterCy=PreciseTargetCy;
	PreciseMasterRx=PreciseTargetRx;
	PreciseMasterRy=PreciseTargetRy;

	return _ER_true;
}

void	MeasureHolePosVectorItem::ExecuteInitialAfterEditInner(ExecuteInitialAfterEditInfo &EInfo)
{
	int	EdgeWidth=10;

	AreaEdgeTop		.Clear();
	AreaEdgeLeft	.Clear();
	AreaEdgeRight	.Clear();
	AreaEdgeBottom	.Clear();
	const MeasureHolePosThreshold	*RThr=GetThresholdR();
	int	XLen=ceil(MasterDiameterX)+16+RThr->NoiseSize*4+EdgeWidth*2;
	int	YLen=ceil(MasterDiameterY)+ 8+RThr->NoiseSize*4+EdgeWidth*2;
	int	XTop=floor(MasterPosX-MasterDiameterX/2.0)-8	-RThr->NoiseSize*2-EdgeWidth;
	int	YTop=floor(MasterPosY-MasterDiameterY/2.0)-4	-RThr->NoiseSize*2-EdgeWidth;
	int	XByte=(XLen+7)/8;

	BYTE	**SBmp	=MakeMatrixBuff(XByte,YLen);
	BYTE	**SBmp2	=MakeMatrixBuff(XByte,YLen);
	BYTE	**SBmp3	=MakeMatrixBuff(XByte,YLen);
	BYTE	**SBmp4	=MakeMatrixBuff(XByte,YLen);
	BYTE	**HoleBmp	=MakeMatrixBuff(XByte,YLen);

	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterPosX,MasterPosY);
	if(AVector!=NULL)
		AVector->Set(this);

	MatrixBuffClear(SBmp,0,XByte,YLen);

	FlexArea	Hole;
		Hole.SetEllipse(MasterPosX-XTop,MasterPosY-YTop,MasterDiameterX/2.0,MasterDiameterY/2.0);

		Hole.MakeBitData(SBmp,XLen,YLen);
		MatrixBuffCopy	(HoleBmp,XByte,YLen
						,(const BYTE **)SBmp ,XByte,YLen);
		MatrixBuffCopy	(SBmp2,XByte,YLen
						,(const BYTE **)SBmp ,XByte,YLen);

		GetLayersBase()->FatAreaN (SBmp
					,SBmp3
					,XByte, YLen
					,EdgeWidth);
		GetLayersBase()->ThinAreaN(SBmp2
					,SBmp3
					,XByte, YLen
					,EdgeWidth);

		MatrixBuffXor	(SBmp,(const BYTE **)SBmp2,XByte, YLen);

		int	Cx=XLen/2;
		int	Cy=YLen/2;

		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y>=y1 && Y>=y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeBottom=*t;
				AreaEdgeBottom.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffCopy	(SBmp4,XByte,YLen
							,(const BYTE **)SBmp2 ,XByte,YLen);
			MatrixBuffAnd	(SBmp2,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp2
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackInside;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackInside);
			t=FPackInside.GetFirst();
			if(t!=NULL){
				AreaBottomI=*t;
				AreaBottomI.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffNotAnd(SBmp4,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp4
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackOutside;
			PickupFlexArea(SBmp4 ,XByte ,XLen,YLen ,FPackOutside);
			t=FPackOutside.GetFirst();
			if(t!=NULL){
				AreaBottomO=*t;
				AreaBottomO.MoveToNoClip(XTop,YTop);
			}
		}
		catch(...){}

		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=1.0/sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y<y1 && Y>=y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeRight=*t;
				AreaEdgeRight.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffCopy	(SBmp4,XByte,YLen
							,(const BYTE **)SBmp2 ,XByte,YLen);
			MatrixBuffAnd	(SBmp2,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp2
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackInside;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackInside);
			t=FPackInside.GetFirst();
			if(t!=NULL){
				AreaRightI=*t;
				AreaRightI.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffNotAnd(SBmp4,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp4
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackOutside;
			PickupFlexArea(SBmp4 ,XByte ,XLen,YLen ,FPackOutside);
			t=FPackOutside.GetFirst();
			if(t!=NULL){
				AreaRightO=*t;
				AreaRightO.MoveToNoClip(XTop,YTop);
			}
		}

		catch(...){}
		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y<y1 && Y<y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeTop=*t;
				AreaEdgeTop.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffCopy	(SBmp4,XByte,YLen
							,(const BYTE **)SBmp2 ,XByte,YLen);
			MatrixBuffAnd	(SBmp2,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp2
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackInside;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackInside);
			t=FPackInside.GetFirst();
			if(t!=NULL){
				AreaTopI=*t;
				AreaTopI.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffNotAnd(SBmp4,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp4
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackOutside;
			PickupFlexArea(SBmp4 ,XByte ,XLen,YLen ,FPackOutside);
			t=FPackOutside.GetFirst();
			if(t!=NULL){
				AreaTopO=*t;
				AreaTopO.MoveToNoClip(XTop,YTop);
			}
		}
		catch(...){}

		try{
			MatrixBuffCopy	(SBmp2,XByte,YLen
							,(const BYTE **)SBmp ,XByte,YLen);
			double	k=1.0/sqrt(3.0);
			for(int y=0;y<YLen;y++){
				BYTE	*s=SBmp2[y];
				for(int x=0;x<XLen;x++){
					if(GetBmpBitOnY(s,x)!=0){
						int	X=x-Cx;
						int	Y=y-Cy;
						int	y1=X*k;
						int	y2=-X*k;
						if(Y>=y1 && Y<y2){
						}
						else{
							SetBmpBitOnY0(s,x);
						}
					}
				}
			}
			PureFlexAreaListContainer FPackEdge;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackEdge);
			PureFlexAreaList	*t=FPackEdge.GetFirst();
			if(t!=NULL){
				AreaEdgeLeft=*t;
				AreaEdgeLeft.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffCopy	(SBmp4,XByte,YLen
							,(const BYTE **)SBmp2 ,XByte,YLen);
			MatrixBuffAnd	(SBmp2,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp2
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackInside;
			PickupFlexArea(SBmp2 ,XByte ,XLen,YLen ,FPackInside);
			t=FPackInside.GetFirst();
			if(t!=NULL){
				AreaLeftI=*t;
				AreaLeftI.MoveToNoClip(XTop,YTop);
			}

			MatrixBuffNotAnd(SBmp4,(const BYTE **)HoleBmp,XByte, YLen);
			ThinArea(SBmp4
					,SBmp3
					,XByte, YLen);
			PureFlexAreaListContainer FPackOutside;
			PickupFlexArea(SBmp4 ,XByte ,XLen,YLen ,FPackOutside);
			t=FPackOutside.GetFirst();
			if(t!=NULL){
				AreaLeftO=*t;
				AreaLeftO.MoveToNoClip(XTop,YTop);
			}
		}
		catch(...){}

		ImageBuffer *ImageListMaster[10];
		GetMasterBuffList(ImageListMaster);

		AreaEdgeTop.SetAndCalc(*ImageListMaster[0]);
		AreaEdgeLeft.SetAndCalc(*ImageListMaster[0]);
		AreaEdgeRight.SetAndCalc(*ImageListMaster[0]);
		AreaEdgeBottom.SetAndCalc(*ImageListMaster[0]);

		MakeIdeal(AreaEdgeTop);
		MakeIdeal(AreaEdgeLeft);
		MakeIdeal(AreaEdgeRight);
		MakeIdeal(AreaEdgeBottom);

		AreaEdgeTop.MakeSum();
		AreaEdgeLeft.MakeSum();
		AreaEdgeRight.MakeSum();
		AreaEdgeBottom.MakeSum();

		DeleteMatrixBuff(SBmp,YLen);
		DeleteMatrixBuff(SBmp2,YLen);
		DeleteMatrixBuff(SBmp3,YLen);
		DeleteMatrixBuff(SBmp4,YLen);
		DeleteMatrixBuff(HoleBmp,YLen);

		AvrTopI		=AreaTopI.GetAverage(*ImageListMaster[0],0,0);
		AvrTopO		=AreaTopO.GetAverage(*ImageListMaster[0],0,0);
		AvrLeftI	=AreaLeftI.GetAverage(*ImageListMaster[0],0,0);
		AvrLeftO	=AreaLeftO.GetAverage(*ImageListMaster[0],0,0);
		AvrRightI	=AreaRightI.GetAverage(*ImageListMaster[0],0,0);
		AvrRightO	=AreaRightO.GetAverage(*ImageListMaster[0],0,0);
		AvrBottomI	=AreaBottomI.GetAverage(*ImageListMaster[0],0,0);
		AvrBottomO	=AreaBottomO.GetAverage(*ImageListMaster[0],0,0);

}
void	MeasureHolePosVectorItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		MeasureHolePosItemBase::ExecuteMove(GlobalDx,GlobalDy,AllItems);
	}
}

void	MeasureHolePosVectorItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);

	MeasureHolePosBase	*ABase=(MeasureHolePosBase *)GetParentBase();
	const MeasureHolePosThreshold	*RThr=GetThresholdR();
	QPainter	PData(&pnt);

	if(RThr->CalcMode==0){
		MeasureHolePosDrawAttr	*BAttr=dynamic_cast<MeasureHolePosDrawAttr *>(Attr);
		if(BAttr!=NULL){
			AlgorithmItemPI::DrawArea(AreaEdgeTop	,pnt, movx ,movy ,ZoomRate ,BAttr);
			AlgorithmItemPI::DrawArea(AreaEdgeLeft	,pnt, movx ,movy ,ZoomRate ,BAttr);
			AlgorithmItemPI::DrawArea(AreaEdgeRight	,pnt, movx ,movy ,ZoomRate ,BAttr);
			AlgorithmItemPI::DrawArea(AreaEdgeBottom,pnt, movx ,movy ,ZoomRate ,BAttr);

			AreaEdgeTop		.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
			AreaEdgeLeft	.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
			AreaEdgeRight	.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
			AreaEdgeBottom	.DrawImage(0,0,&pnt,ZoomRate,movx,movy,true,false,false,128);
		}
		else{
			AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}

		QColor	c=Qt::green;
		c.setAlpha(100);
		QPen	Pen(c);
		Pen.setWidth(ABase->ResultLineWidth);
		PData.setPen(Pen);

		PData.drawArc (  (MasterPosX-MasterDiameterX/2.0+movx)*ZoomRate
						,(MasterPosY-MasterDiameterY/2.0+movy)*ZoomRate
						, MasterDiameterX*ZoomRate
						, MasterDiameterY*ZoomRate
						,0
						,16*360-1);
	}
	else
	if(RThr->CalcMode==1){
		QColor	c=Qt::green;
		c.setAlpha(100);
		QPen	Pen(c);
		Pen.setWidth(ABase->ResultLineWidth);
		PData.setPen(Pen);

		PData.drawArc (  (PreciseMasterCx-PreciseMasterRx+movx)*ZoomRate
						,(PreciseMasterCy-PreciseMasterRy+movy)*ZoomRate
						, PreciseMasterRx*2*ZoomRate
						, PreciseMasterRy*2*ZoomRate
						,0
						,16*360-1);
	}
}

void	MeasureHolePosVectorItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			MeasureHolePosBase	*ABase=(MeasureHolePosBase *)GetParentBase();
			const MeasureHolePosThreshold	*RThr=GetThresholdR();
			if(RThr->CalcMode==0){
				{
					QColor	c=Qt::green;
					c.setAlpha(100);
					QPen	Pen(c);
					Pen.setWidth(ABase->ResultLineWidth);
					PData.setPen(Pen);
					PData.drawArc (  (MasterPosX-MasterDiameterX/2.0+MovX)*ZoomRate
									,(MasterPosY-MasterDiameterY/2.0+MovY)*ZoomRate
									, MasterDiameterX*ZoomRate
									, MasterDiameterY*ZoomRate
									,0
									,16*360-1);
				}
				QColor	ce=Qt::red;
				ce.setAlpha(100);
				QPen	Pen(ce);
				Pen.setWidth(ABase->ResultLineWidth);
				PData.setPen(Pen);
				double	ECx=MasterPosX+Res->GetAlignedX()+(RxRight+RxLeft)/2.0;
				double	ECy=MasterPosY+Res->GetAlignedY()+(RyBottom+RyTop)/2.0;
				double	EDx=MasterDiameterX+RxRight-RxLeft;
				double	EDy=MasterDiameterY+RyBottom-RyTop;
				PData.drawArc (  (ECx-EDx/2.0+MovX)*ZoomRate
								,(ECy-EDy/2.0+MovY)*ZoomRate
								, EDx*ZoomRate
								, EDy*ZoomRate
								,0
								,16*360-1);

				if(ZoomRate>1.0){
					PData.setPen(Qt::yellow);
					PData.setBrush(Qt::yellow);
					int	kx=(MasterPosX+MovX)*ZoomRate;
					int	ky=(MasterPosY+MovY)*ZoomRate;
					if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
						QRect	rect(0,0,IData.width(),IData.height());
						PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" HDiff(")+QString::number(ResultHeightDiff,'g',2)+QString(/**/")")
							,&rect);
						PData.drawText(kx,ky+16*1,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" H(")+QString::number(EDy,'f',2)+QString(/**/")")
							,&rect);
						PData.drawText(kx,ky+16*2,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" WDiff(")+QString::number(ResultWidthDiff,'g',2)+QString(/**/")")
							,&rect);
						PData.drawText(kx,ky+16*3,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" W(")+QString::number(EDx,'f',2)+QString(/**/")")
							,&rect);
						PData.drawText(kx,ky+16*4,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" XPos(")+QString::number(ResultPosXDiff,'g',2)+QString(/**/")")
							,&rect);
						PData.drawText(kx,ky+16*5,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" YPos(")+QString::number(ResultPosYDiff,'g',2)+QString(/**/")")
							,&rect);
						
					}
				}
			}
			else
			if(RThr->CalcMode==1){
				QColor	c=Qt::green;
				c.setAlpha(100);
				QPen	Pen(c);
				Pen.setWidth(ABase->ResultLineWidth);
				PData.setPen(Pen);

				PData.drawArc (  (PreciseMasterCx-PreciseMasterRx+MovX)*ZoomRate
								,(PreciseMasterCy-PreciseMasterRy+MovY)*ZoomRate
								, PreciseMasterRx*2*ZoomRate
								, PreciseMasterRy*2*ZoomRate
								,0
								,16*360-1);

				QColor	ce=Qt::red;
				ce.setAlpha(100);
				QPen	PenE(ce);
				PenE.setWidth(ABase->ResultLineWidth);
				PData.setPen(PenE);

				PData.drawArc (  (PreciseTargetCx-PreciseTargetRx+MovX)*ZoomRate
								,(PreciseTargetCy-PreciseTargetRy+MovY)*ZoomRate
								, PreciseTargetRx*2*ZoomRate
								, PreciseTargetRy*2*ZoomRate
								,0
								,16*360-1);

				if(ZoomRate>1.0){
					PData.setPen(Qt::yellow);
					PData.setBrush(Qt::yellow);
					int	kx=(PreciseMasterCx+MovX)*ZoomRate;
					int	ky=(PreciseMasterCy+MovY)*ZoomRate;
					if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
						QRect	rect(0,0,IData.width(),IData.height());
						PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" dx,dy=(")
							+QString::number(PreciseTargetCx-PreciseMasterCx,'f',2)
							+QString(/**/",")
							+QString::number(PreciseTargetCy-PreciseMasterCy,'f',2)
							+QString(/**/")")
							,&rect);
						PData.drawText(kx,ky+16*1,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/" dRx,dRy=(")
							+QString::number(PreciseTargetRx-PreciseMasterRx,'f',2)
							+QString(/**/",")
							+QString::number(PreciseTargetRy-PreciseMasterRy,'f',2)
							+QString(/**/")")
							,&rect);						
					}
				}
			}
		}
	}
}


double	MeasureHolePosVectorItem::GetIsolation(double x ,double y)
{
	double	D=(x-MasterPosX)*(x-MasterPosX)/(MasterDiameterX*MasterDiameterX/4.0)
			 +(y-MasterPosY)*(y-MasterPosY)/(MasterDiameterY*MasterDiameterY/4.0);
	if(D<=1){
		return sqrt(D);
	}
	return 1000;
}
double	MeasureHolePosVectorItem::GetDrawParam(double x ,double y)
{
	return 0;
}
double	MeasureHolePosVectorItem::GetTParam(double x1 ,double y1 ,double x2 ,double y2)
{
	return 0;
}

void	MeasureHolePosVectorItem::GetDrawPoint(double Param ,double &x ,double &y)
{
	x=MasterPosX;
	y=MasterPosY;
}

void	MeasureHolePosVectorItem::GetShiftVector(double &sx, double &sy)
{
	sx=ResultPosXDiff+AMx;
	sy=ResultPosYDiff+AMy;
}

void	MeasureHolePosVectorItem::GetCenterPoint(double &cx, double &cy)
{
	cx=MasterPosX;
	cy=MasterPosY;
}

void	MeasureHolePosVectorItem::Move(double dx ,double dy)
{
	ExecuteMove(dx,dy,true);
}
