/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicClassify\XDynamicClassify.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XFlexArea.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XDynamicClassify.h"
#include "XBitImageProcessor.h"
#include "omp.h"

ExeResult	DynamicClassifyItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	InitializeBuffer();

	ImagePointerContainer Images;
	GetMasterBuffList(Images);
	MakeExecuableArea(Images , 0, 0);
	return _ER_true;
}

static	int	DbgID=7036;
static	int	DbgLayer=1;
static	int	DbgNumer=0;

ExeResult	DynamicClassifyItem::ExecutePreProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID)
		DbgNumer++;

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

	ImagePointerContainer Images;
	GetTargetBuffList(Images);
	MakeExecuableArea(Images , mx, my);

	return _ER_true;
}


bool	DynamicClassifyItem::InitializeBuffer(void)
{
	int	DeadZone=12;

	int	W=AlgorithmItemPI::GetArea().GetWidth();
	int	H=AlgorithmItemPI::GetArea().GetHeight();
	const	DynamicClassifyThreshold	*RThr=GetThresholdR();
	int	TmpXLen	=W+RThr->VariableWidth*2+DeadZone*2;
	TmpYLen		=H+RThr->VariableWidth*2+DeadZone*2;
	TmpXByte	=(TmpXLen+7)>>3;
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,TmpYLen);
	}
	if(TmpMap2!=NULL){
		DeleteMatrixBuff(TmpMap2,TmpYLen);
	}
	if(TmpMap3!=NULL){
		DeleteMatrixBuff(TmpMap3,TmpYLen);
	}
	if(TmpMap4!=NULL){
		DeleteMatrixBuff(TmpMap4,TmpYLen);
	}
	TmpMap	=MakeMatrixBuff(TmpXByte,TmpYLen);
	TmpMap2	=MakeMatrixBuff(TmpXByte,TmpYLen);
	TmpMap3	=MakeMatrixBuff(TmpXByte,TmpYLen);
	TmpMap4	=MakeMatrixBuff(TmpXByte,TmpYLen);

	Hx1=AlgorithmItemPI::GetArea().GetMinX()-RThr->VariableWidth-DeadZone;
	Hy1=AlgorithmItemPI::GetArea().GetMinY()-RThr->VariableWidth-DeadZone;
	Hx2=Hx1+TmpXLen;
	Hy2=Hy1+TmpYLen;

	FlexArea	A=AlgorithmItemPI::GetArea();
	A.MoveToClip(-Hx1,-Hy1,0,0,TmpXLen,TmpYLen);
	MatrixBuffClear	(TmpMap ,0 ,TmpXByte,TmpYLen);
	A.MakeBitData(TmpMap,TmpXLen,TmpYLen);
	GetLayersBase()->FatAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->VariableWidth);
    MaxZone.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,Hx1,Hy1);

	MatrixBuffClear	(TmpMap ,0 ,TmpXByte,TmpYLen);
	A.MakeBitData(TmpMap,TmpXLen,TmpYLen);
	GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->VariableWidth);
    MinZone.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,Hx1,Hy1);

	MatrixBuffClear	(TmpMap ,0 ,TmpXByte,TmpYLen);
	A.MakeBitData(TmpMap,TmpXLen,TmpYLen);
	if(RThr->ShrinkDot>0){
		GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->ShrinkDot);
	}
	else{
		GetLayersBase()->FatAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->ShrinkDot);
	}
	CoreArea.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,Hx1,Hy1);
	if(CoreArea.GetPatternByte()<3){
		return false;
	}

	CoreCenterX=-1;
	CoreCenterY=-1;

	MatrixBuffCopy(TmpMap3		,TmpXByte,TmpYLen
		,(const BYTE **)TmpMap	,TmpXByte,TmpYLen);
	for(int slen=10;slen>=0;slen--){
		MatrixBuffCopy(TmpMap			,TmpXByte,TmpYLen
				,(const BYTE **)TmpMap3	,TmpXByte,TmpYLen);
		GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen ,slen);

		int	Cx=TmpXLen/2;
		int	Cy=TmpYLen/2;
		for(int	Len=1;Len<max(TmpXLen,TmpYLen)/2;Len++){
			int	y=-Len;
			int	x;
			for(x=-Len;x<Len;x++){
				if(0<(Cx+x) && (Cx+x)<TmpXLen && 0<(Cy+y) && (Cy+y)<TmpYLen
				&& GetBmpBit(TmpMap,Cx+x,Cy+y)!=0){
					CoreCenterX=Hx1+Cx+x;
					CoreCenterY=Hy1+Cy+y;
					goto	FoundCenter;
				}
			}
			x=Len;
			for(y=-Len;y<Len;y++){
				if(0<(Cx+x) && (Cx+x)<TmpXLen && 0<(Cy+y) && (Cy+y)<TmpYLen
				&& GetBmpBit(TmpMap,Cx+x,Cy+y)!=0){
					CoreCenterX=Hx1+Cx+x;
					CoreCenterY=Hy1+Cy+y;
					goto	FoundCenter;
				}
			}
			y=Len;
			for(x=Len;x>-Len;x--){
				if(0<(Cx+x) && (Cx+x)<TmpXLen && 0<(Cy+y) && (Cy+y)<TmpYLen
				&& GetBmpBit(TmpMap,Cx+x,Cy+y)!=0){
					CoreCenterX=Hx1+Cx+x;
					CoreCenterY=Hy1+Cy+y;
					goto	FoundCenter;
				}
			}
			x=-Len;
			for(y=Len;y>-Len;y--){
				if(0<(Cx+x) && (Cx+x)<TmpXLen && 0<(Cy+y) && (Cy+y)<TmpYLen
				&& GetBmpBit(TmpMap,Cx+x,Cy+y)!=0){
					CoreCenterX=Hx1+Cx+x;
					CoreCenterY=Hy1+Cy+y;
					goto	FoundCenter;
				}
			}
		}
	}
FoundCenter:;
	if(CoreCenterX==-1 && CoreCenterY==-1){
		return false;
	}

	ImagePointerContainer ImageList;
	GetMasterBuffList(ImageList);
	int	CenterColorDim[100];
	int	n=0;
	for(ImagePointerList *d=ImageList.GetFirst();d!=NULL;d=d->GetNext()){
		int BrList[256];
		memset(BrList,0,sizeof(BrList));
		CoreArea.MakeBrightList(BrList ,GetDotPerLine(),GetMaxLines(),*d->GetImage());
		CenterColorDim[n]=GetCenterBright(BrList);
		n++;
	}
	if(GetLayerNumb()==1){
		CenterBright=qRgb(CenterColorDim[0],CenterColorDim[0],CenterColorDim[0]);
	}
	else if(GetLayerNumb()==2){
		CenterBright=qRgb(CenterColorDim[0],CenterColorDim[1],CenterColorDim[1]);
	}
	else if(GetLayerNumb()>=3){
		CenterBright=qRgb(CenterColorDim[0],CenterColorDim[1],CenterColorDim[2]);
	}
	return true;
}
void	DynamicClassifyItem::MakeExecuableArea(ImagePointerContainer &Images , int dx, int dy)
{
	const	DynamicClassifyThreshold	*RThr=GetThresholdR();
	ColorLogic	PickupColor=RThr->PickupColor;

	int	CenterColorDim[100];
	int	n=0;
	for(ImagePointerList *d=Images.GetFirst();d!=NULL;d=d->GetNext()){
		int BrList[256];
		memset(BrList,0,sizeof(BrList));
		CoreArea.MakeBrightList(BrList ,GetDotPerLine(),GetMaxLines(),*d->GetImage(),dx,dy);
		CenterColorDim[n]=GetCenterBright(BrList);
		n++;
	}
	MatrixBuffClear	(TmpMap ,0 ,TmpXByte,TmpYLen);
	BareArea.Clear();

	QRgb	CurrentCenterBright;
	if(GetLayerNumb()==1){
		CurrentCenterBright=qRgb(CenterColorDim[0],CenterColorDim[0],CenterColorDim[0]);
	}
	else if(GetLayerNumb()==2){
		CurrentCenterBright=qRgb(CenterColorDim[0],CenterColorDim[1],CenterColorDim[1]);
	}
	else if(GetLayerNumb()>=3){
		int	dR=CenterColorDim[0] - qRed(CenterBright);
		int	dG=CenterColorDim[1] - qGreen(CenterBright);
		int	dB=CenterColorDim[2] - qBlue(CenterBright);
		if(dR<-RThr->AdjustBrightL)
			dR=-RThr->AdjustBrightL;
		if(dR>RThr->AdjustBrightH)
			dR=RThr->AdjustBrightH;
		if(dG<-RThr->AdjustBrightL)
			dG=-RThr->AdjustBrightL;
		if(dG>RThr->AdjustBrightH)
			dG=RThr->AdjustBrightH;
		if(dB<-RThr->AdjustBrightL)
			dB=-RThr->AdjustBrightL;
		if(dB>RThr->AdjustBrightH)
			dB=RThr->AdjustBrightH;

		PickupColor.ShiftColor(dR,dG,dB);

		int	NLen=MaxZone.GetFLineLen();
		for(int i=0;i<NLen;i++){
			int	srcy=MaxZone.GetFLineAbsY(i);
			int	Y	=srcy+dy;
			int	srcx=MaxZone.GetFLineLeftX(i);
			int	X1	=srcx+dx;
			int	Numb=MaxZone.GetFLineNumb(i);
			BYTE	*sR=Images[0]->GetY(Y)+X1;
			BYTE	*sG=Images[1]->GetY(Y)+X1;
			BYTE	*sB=Images[2]->GetY(Y)+X1;
			BYTE	*DestP=TmpMap[srcy-Hy1];
			int	j=0;
			for(j=0;j<Numb-8;j+=8){
				int	x=srcx+j;
				BYTE	d=PickupColor.Calc8(sR,sG,sB,0);
				sR+=8;
				sG+=8;
				sB+=8;
				for(int k=0;k<8;k++){
					if((d&(0x80>>k))!=0){
						SetBmpBitOnY1(DestP,x-Hx1+k);
					}
				}
			}
			for(;j<Numb;j++){
				int	x=srcx+j;
				if(PickupColor.Calc(*sR,*sG,*sB,0)==true){
					SetBmpBitOnY1(DestP,x-Hx1);
				}
				sR++;
				sG++;
				sB++;
			}
		}
	}

	GetLayersBase()->FatAreaN (TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->NoiseDot);
	GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->NoiseDot);
	
	FlexArea	A=MinZone;
	A.MoveToNoClip(-(Hx1+dx),-(Hy1+dy));
	A.MakeBitData(TmpMap,TmpXByte*8,TmpYLen);

	BareArea.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,0,0);

	/*
	bool	Found=false;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpMap,TmpXByte,TmpXByte*8,TmpYLen,FPack,-1,false);
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(CoreCenterX+dx-Hx1,CoreCenterY+dy-Hy1)==true){
			BareArea.SuckFrom(*a);
			Found=true;
			break;
		}
	}
	if(Found==false){
		PureFlexAreaList *Largest=NULL;
		int64			LargestDots=0;
		for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
			int64	dots=a->GetPatternByte();
			if(LargestDots<dots){
				LargestDots=dots;
				Largest=a;
			}
		}
		if(Largest!=NULL){
			BareArea.SuckFrom(*Largest);
		}
	}
	*/
	MatrixBuffClear	(TmpMap ,0 ,TmpXByte,TmpYLen);

	BareArea.MakeBitData(TmpMap,TmpXByte*8,TmpYLen);
	BareArea.MoveToNoClip(Hx1+dx,Hy1+dy);

	MatrixBuffCopy	(TmpMap3		,TmpXByte,TmpYLen
					,(const BYTE **)TmpMap,TmpXByte,TmpYLen);


	if(RThr->ShrinkDot>0){
		GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->ShrinkDot);
	}
	else{
		GetLayersBase()->FatAreaN (TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,RThr->ShrinkDot);
	}
	InsideArea.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,Hx1+dx,Hy1+dy);

	if(RThr->OutlineTWidth>0){
		MatrixBuffCopy	(TmpMap					,TmpXByte,TmpYLen
						,(const BYTE **)TmpMap3	,TmpXByte,TmpYLen);
		MatrixBuffCopy	(TmpMap4				,TmpXByte,TmpYLen
						,(const BYTE **)TmpMap3	,TmpXByte,TmpYLen);
		int	L2=RThr->OutlineTWidth/2;
		GetLayersBase()->FatAreaN (TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,L2);
		GetLayersBase()->ThinAreaN(TmpMap4 ,TmpMap2 ,TmpXByte, TmpYLen,RThr->OutlineTWidth-L2);

		MatrixBuffNotAnd(TmpMap,(const BYTE **)TmpMap4 ,TmpXByte, TmpYLen);
		OutlineTArea.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,Hx1+dx,Hy1+dy);
	}
	if(RThr->OutlineIWidth>0){
		int	Gap=(RThr->OutlineTWidth+1)/2-RThr->OverlapInEachArea;
		if(Gap<0)
			Gap=0;
		MatrixBuffCopy	(TmpMap					,TmpXByte,TmpYLen
						,(const BYTE **)TmpMap3	,TmpXByte,TmpYLen);
		GetLayersBase()->ThinAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,Gap);

		MatrixBuffCopy	(TmpMap4				,TmpXByte,TmpYLen
						,(const BYTE **)TmpMap	,TmpXByte,TmpYLen);
		GetLayersBase()->ThinAreaN(TmpMap4 ,TmpMap2 ,TmpXByte, TmpYLen,RThr->OutlineIWidth);

		MatrixBuffNotAnd(TmpMap,(const BYTE **)TmpMap4 ,TmpXByte, TmpYLen);
		OutlineIArea.BuildFromRaster(TmpMap,TmpXByte,TmpYLen ,Hx1+dx,Hy1+dy);
	}
	if(RThr->OutlineOWidth>0){
		int	Gap=(RThr->OutlineTWidth)/2-RThr->OverlapInEachArea;
		if(Gap<0)
			Gap=0;
		MatrixBuffCopy	(TmpMap					,TmpXByte,TmpYLen
						,(const BYTE **)TmpMap3	,TmpXByte,TmpYLen);
		GetLayersBase()->FatAreaN(TmpMap ,TmpMap2 ,TmpXByte, TmpYLen,Gap);

		MatrixBuffCopy	(TmpMap4				,TmpXByte,TmpYLen
						,(const BYTE **)TmpMap	,TmpXByte,TmpYLen);
		GetLayersBase()->FatAreaN(TmpMap4 ,TmpMap2 ,TmpXByte, TmpYLen,RThr->OutlineOWidth);

		MatrixBuffNotAnd(TmpMap4,(const BYTE **)TmpMap ,TmpXByte, TmpYLen);
		OutlineOArea.BuildFromRaster(TmpMap4,TmpXByte,TmpYLen ,Hx1+dx,Hy1+dy);
	}
}

int		DynamicClassifyItem::GetCenterBright(int BTable[256])
{
	int	N=0;
	int	BTableNumb=256;
	for(int i=0;i<BTableNumb;i++){
		N+=BTable[i];
	}
	int	DiscardDot=N/4;

	int	LLevel;
	int	HLevel;
	int	D=0;
	for(LLevel=0;LLevel<BTableNumb;LLevel++){
		D+=BTable[LLevel];
		if(D>DiscardDot){
			break;
		}
	}
	D=0;
	for(HLevel=BTableNumb-1;HLevel>=0;HLevel--){
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