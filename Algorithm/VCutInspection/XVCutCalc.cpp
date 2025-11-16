/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VCutInspection\XVCutCalc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XVCutInspection.h"
#include "VCutInspection.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XBitImageProcessor.h"
#include "XDisplayBitImage.h"
#include "omp.h"
#include <QColor>
#include "XVCutInspection.h"
#include "XAnyData.h"
#define	_USE_MATH_DEFINES
#include <math.h>


void	VCutBand::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	//_CrtCheckMemory();

	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)Parent->GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(Parent);
	if(BList!=NULL){
		delete	[]BList;
	}
	BList=new double[WLen];

	ImageBuffer *ImageList[1000];
	Parent->GetMasterBuffList(ImageList);
	MakeBList(ImageList ,0 ,0);

	CalcFromBList();

	int	x1=Px;
	int	y1=Py;
	int	x2=Px+Ux*WLen;
	int	y2=Py+Uy*WLen;
	int	x3=Px+Ux*WLen+Vx*StackedLen;
	int	y3=Py+Uy*WLen+Vy*StackedLen;
	int	x4=Px+Vx*StackedLen;
	int	y4=Py+Vy*StackedLen;

	ResImageX1=min(min(x1,x2),min(x3,x4));
	ResImageY1=min(min(y1,y2),min(y3,y4));
	ResImageX2=max(max(x1,x2),max(x3,x4));
	ResImageY2=max(max(y1,y2),max(y3,y4));

	int	XLen=ResImageX2-ResImageX1+1;
	int	YLen=ResImageY2-ResImageY1+1;
	ResultBitImage.Alloc((XLen+7)/8 ,YLen);
}

void	VCutBand::MakeBList(ImageBuffer *ImageList[] ,int mx ,int my)
{
	int	LayerNumb=Parent->GetLayerNumb();
	double	LLL=1.0/(double)LayerNumb;
	for(int i=0;i<WLen;i++){
		BList[i]=0;
		for(int j=0;j<StackedLen;j++){
			int	Kx=Px+mx+Ux*i+Vx*j;
			int	Ky=Py+my+Uy*i+Vy*j;
			double	d=1;
			if(0<=Kx && Kx<GetDotPerLine() && 0<=Ky && Ky<GetMaxLines()){
				for(int L=0;L<LayerNumb;L++){
					d*=*(ImageList[L]->GetY(Ky)+Kx);
				}
			}
			BList[i]+=pow(d,LLL);
		}
		BList[i]/=StackedLen;
	}
}

bool	VCutBand::CalcFromBList(void)
{
	int	LowB=255;
	int	HighB=0;
	for(int i=0;i<WLen;i++){
		if(BList[i]<LowB)
			LowB=BList[i];
		if(BList[i]>HighB)
			HighB=BList[i];
	}

	MidAvr=(LowB+HighB)/2;
	double	LAdd=0;
	int		LN=0;
	double	HAdd=0;
	int		HN=0;
	for(int i=0;i<WLen;i++){
		if(BList[i]<MidAvr){
			LAdd+=BList[i];
			LN++;
		}
		else{
			HAdd+=BList[i];
			HN++;
		}
	}
	ResultDifference=0;
	if(LN>0 && HN>1){
		int	LAvr=LAdd/LN;
		int	HAvr=HAdd/HN;
		ResultDifference=HAvr-LAvr;
		if(ResultDifference>Parent->GetThresholdR(NULL)->ThresholdLevel){
			return true;
		}
	}
	else{
		ResultDifference=0;
	}
	return false;
}

ResultPosList	*VCutBand::ExecuteProcessing(int kx,int ky)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX-kx;
		my=AVector->ShiftY-ky;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx+kx;
		V.PosYOnTarget=cy+ky;
		V.ShiftX=0;
		V.ShiftY=0;
		Parent->GetAlignmentForProcessing(V);
		mx=V.ShiftX-kx;
		my=V.ShiftY-ky;
	}
	ResMx=mx+kx;
	ResMy=my+ky;

	ImageBuffer *ImageList[1000];
	Parent->GetTargetBuffList(ImageList);

	MakeBList(ImageList ,mx+kx ,my+ky);

	if(CalcFromBList()==true){
		//OK
		if(ResultDifference>1.0){
			for(int i=0;i<WLen;i++){
				if(BList[i]>MidAvr){
					ResultU1=i;
					break;
				}
			}
			for(int i=WLen-1;i>=0;i--){
				if(BList[i]>MidAvr){
					ResultU2=i;
					break;
				}
			}
			VCutInspectionInPage	*PPage=(VCutInspectionInPage *)Parent->GetParent();
			VCutInspectionBase		*PBase=(VCutInspectionBase *)PPage->GetParentBase();
			ResultU1-=PBase->ExpandPixelForResult;
			if(ResultU1<0){
				ResultU1=0;
			}
			ResultU2+=PBase->ExpandPixelForResult;
			if(ResultU2>=WLen){
				ResultU2=WLen-1;
			}
			ResultBitImage.ClearAll();
			for(int v=0;v<=StackedLen;v++){
				for(int u=ResultU1;u<=ResultU2;u++){
					int	X=Px+Vx*v+Ux*u-ResImageX1;
					int Y=Py+Vy*v+Uy*u-ResImageY1;
					ResultBitImage.SetBit(X,Y);
				}
			}
		}
		MakeDynamicMask(mx+kx ,my+ky);
		return NULL;
	}
	int	cx,cy;
	GetCenter(cx,cy);
	ResultPosList	*p=new ResultPosList(cx ,cy ,mx ,my);
	p->result=0x10001;
	p->SetResult1(ResultDifference);
	ResultBitImage.ClearAll();

	MakeDynamicMask(mx+kx ,my+ky);

	return p;
}


