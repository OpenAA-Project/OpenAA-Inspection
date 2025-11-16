/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterItemLineEmphasize.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaFilter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaFilterPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>


AreaFilterThresholdLargeEnflat::AreaFilterThresholdLargeEnflat(AreaFilterItemLineLargeEnflat *parent)
:AlgorithmThreshold(parent)
{
	BlockSize		=20;
	MoveByAlignment	=true;
	SkipDot			=0;
	GeneratedBrightness	=50;
	AdoptedRate		=30;
}

void	AreaFilterThresholdLargeEnflat::CopyFrom(const AlgorithmThreshold &src)
{
	AreaFilterThresholdLargeEnflat	*s=(AreaFilterThresholdLargeEnflat *)&src;
	BlockSize		=s->BlockSize;
	MoveByAlignment	=s->MoveByAlignment;
	SkipDot			=s->SkipDot;
	GeneratedBrightness	=s->GeneratedBrightness;
	AdoptedRate		=s->AdoptedRate;
}
bool	AreaFilterThresholdLargeEnflat::IsEqual(const AlgorithmThreshold &src)	const 
{
	AreaFilterThresholdLargeEnflat	*s=(AreaFilterThresholdLargeEnflat *)&src;
	if(BlockSize			!=s->BlockSize			)	return false;
	if(MoveByAlignment		!=s->MoveByAlignment	)	return false;
	if(SkipDot				!=s->SkipDot			)	return false;
	if(GeneratedBrightness	!=s->GeneratedBrightness)	return false;
	if(AdoptedRate			!=s->AdoptedRate		)	return false;
	return true;
}
bool	AreaFilterThresholdLargeEnflat::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,BlockSize)==false)
		return false;
	if(::Save(f,MoveByAlignment)==false)
		return false;
	if(::Save(f,SkipDot)==false)
		return false;
	if(::Save(f,GeneratedBrightness)==false)
		return false;
	if(::Save(f,AdoptedRate)==false)
		return false;
	return true;
}
bool	AreaFilterThresholdLargeEnflat::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,BlockSize)==false)
		return false;
	if(::Load(f,MoveByAlignment)==false)
		return false;
	if(::Load(f,SkipDot)==false)
		return false;
	if(::Load(f,GeneratedBrightness)==false)
		return false;
	if(::Load(f,AdoptedRate)==false)
		return false;
	return true;
}

void AreaFilterThresholdLargeEnflat::FromLibrary(AlgorithmLibrary *src)
{
	BlockSize		=((AreaFilterLibrary *)src)->BlockSize;
	MoveByAlignment	=((AreaFilterLibrary *)src)->MoveByAlignment;
	SkipDot			=((AreaFilterLibrary *)src)->SkipDot;
	GeneratedBrightness	=((AreaFilterLibrary *)src)->GeneratedBrightness;
	AdoptedRate		=((AreaFilterLibrary *)src)->AdoptedRate;
}

void AreaFilterThresholdLargeEnflat::ToLibrary(AlgorithmLibrary *dest)
{
	((AreaFilterLibrary *)dest)->BlockSize		=BlockSize;
	((AreaFilterLibrary *)dest)->MoveByAlignment=MoveByAlignment;
	((AreaFilterLibrary *)dest)->SkipDot		=SkipDot;
	((AreaFilterLibrary *)dest)->GeneratedBrightness=GeneratedBrightness;
	((AreaFilterLibrary *)dest)->AdoptedRate	=AdoptedRate;
}

AreaFilterItemLineLargeEnflat::AreaFilterItemLineLargeEnflat(void)
{
	AVector		=NULL;
	MasterBrightness=0;
	TmpBuff		=NULL;
	XLen		=0;
	YLen		=0;
}
AreaFilterItemLineLargeEnflat::~AreaFilterItemLineLargeEnflat(void)
{
	if(TmpBuff!=NULL){
		DeleteMatrixBuff(TmpBuff,YLen);
		TmpBuff=NULL;
	}
}

AlgorithmItemPLI	&AreaFilterItemLineLargeEnflat::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}
bool    AreaFilterItemLineLargeEnflat::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaFilterItemLineLargeEnflat::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}


ExeResult	AreaFilterItemLineLargeEnflat::ExecuteInitialAfterEdit(int ExeID 
																	,int ThresdNo
																	, ResultInItemRoot *Res
																	,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	MasterBrightness	=GetArea().GetAverage(GetMasterBuff(),0,0);
	if(MasterBrightness==0)
		MasterBrightness=GetThresholdR()->GeneratedBrightness;

	if(TmpBuff!=NULL){
		DeleteMatrixBuff(TmpBuff,YLen);
		TmpBuff=NULL;
	}
	XLen=min(GetDotPerLine(),GetArea().GetWidth());
	YLen=min(GetMaxLines(),GetArea().GetHeight());

	TmpBuff	=MakeMatrixBuff(XLen,YLen);
	BuffX	=GetArea().GetMinX();
	BuffY	=GetArea().GetMinY();
	MatrixBuffClear	(TmpBuff ,MasterBrightness ,XLen ,YLen);

	return _ER_true;
}

ExeResult	AreaFilterItemLineLargeEnflat::ExecutePreProcessing       (int ExeID ,int ThreadNo, ResultInItemRoot *Res)
{
	int	mx=0;
	int	my=0;
	if(GetThresholdR()->MoveByAlignment==true){
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
	}

	int	BlockSize	=GetThresholdR()->BlockSize;
	int	SkipDot		=GetThresholdR()->SkipDot;
	if(SkipDot==0)
		SkipDot=1;
	int	R=BlockSize/2;
	ClippedArea=GetArea();
	int	MaxX=GetDotPerLine()-R-abs(mx)+BlockSize;
	int	DiffX=0;
	if(MaxX>=GetDotPerLine()){
		DiffX=MaxX-GetDotPerLine()+1;
	}
	int	MaxY=GetMaxLines()-R-abs(my)+BlockSize;
	int	DiffY=0;
	if(MaxY>=GetMaxLines()){
		DiffY=MaxY-GetMaxLines()+1;
	}
	ClippedArea.ClipArea(R+abs(mx),R+abs(my),GetDotPerLine()-R-abs(mx)-DiffX,GetMaxLines()-R-abs(my)-DiffY);
	ImageBuffer	&TBuff=GetTargetBuff();
	int	HopCount=BlockSize/SkipDot;
	int	TotalCount=HopCount*HopCount;
	int	N=ClippedArea.GetFLineLen();
	omp_set_nested(0);
	if(TotalCount<256){
		#pragma omp parallel   num_threads(8)                          
		{                                                
			#pragma omp for 
			for(int i=0;i<N;i++){
				BYTE	BTable[256];
				int	Y	=ClippedArea.GetFLineAbsY(i)+my;
				int	X1	=ClippedArea.GetFLineLeftX(i)+mx;
				int	Numb=ClippedArea.GetFLineNumb(i);

				BYTE	*d=TBuff.GetY(Y);
				BYTE	*tP=TmpBuff[Y-BuffY];
				for(int j=0;j<Numb;j++){
					int	X=X1+j;
					memset(BTable,0,sizeof(BTable));
					BYTE	MinC=255;
					BYTE	MaxC=0;
					for(int ny=0;ny<BlockSize;ny+=SkipDot){
						BYTE	*s=&TBuff.GetY(Y-R+ny)[X-R];
						for(int k=0;k<HopCount;k++){
							BYTE	c=*s;
							s+=SkipDot;
							BTable[c]++;
							if(MinC>c)
								MinC=c;
							if(MaxC<c)
								MaxC=c;
						}
					}
					int	Col=MakeAverage(MinC,MaxC,BTable,TotalCount);
					tP[X-BuffX]=Clipping(MasterBrightness+d[X]-Col,0,255);
				}
			}
		}
	}
	else if(TotalCount<65535){
		#pragma omp parallel    num_threads(8)                           
		{                                                
			#pragma omp for
			for(int i=0;i<N;i++){
				WORD	BTable[256];
				int	Y	=ClippedArea.GetFLineAbsY(i)+my;
				int	X1	=ClippedArea.GetFLineLeftX(i)+mx;
				int	Numb=ClippedArea.GetFLineNumb(i);

				BYTE	*d=TBuff.GetY(Y);
				BYTE	*tP=TmpBuff[Y-BuffY];
				for(int j=0;j<Numb;j++){
					int	X=X1+j;
					memset(BTable,0,sizeof(BTable));
					BYTE	MinC=255;
					BYTE	MaxC=0;
					for(int ny=0;ny<BlockSize;ny+=SkipDot){
						BYTE	*s=&TBuff.GetY(Y-R+ny)[X-R];
						for(int k=0;k<HopCount;k++){
							BYTE	c=*s;
							s+=SkipDot;
							BTable[c]++;
							if(MinC>c)
								MinC=c;
							if(MaxC<c)
								MaxC=c;
						}
					}
					int	Col=MakeAverage(MinC,MaxC,BTable,TotalCount);
					tP[X-BuffX]=Clipping(MasterBrightness+d[X]-Col,0,255);
				}
			}
		}
	}
	else{
		#pragma omp parallel    num_threads(8)                           
		{                                                
			#pragma omp for
			for(int i=0;i<N;i++){
				int	BTable[256];
				int	Y	=ClippedArea.GetFLineAbsY(i)+my;
				int	X1	=ClippedArea.GetFLineLeftX(i)+mx;
				int	Numb=ClippedArea.GetFLineNumb(i);

				BYTE	*d=TBuff.GetY(Y);
				BYTE	*tP=TmpBuff[Y-BuffY];
				for(int j=0;j<Numb;j++){
					int	X=X1+j;
					memset(BTable,0,sizeof(BTable));
					BYTE	MinC=255;
					BYTE	MaxC=0;
					for(int ny=0;ny<BlockSize;ny+=SkipDot){
						BYTE	*s=&TBuff.GetY(Y-R+ny)[X-R];
						for(int k=0;k<HopCount;k++){
							BYTE	c=*s;
							s+=SkipDot;
							BTable[c]++;
							if(MinC>c)
								MinC=c;
							if(MaxC<c)
								MaxC=c;
						}
					}
					int	Col=MakeAverage(MinC,MaxC,BTable,TotalCount);
					tP[X-BuffX]=Clipping(MasterBrightness+d[X]-Col,0,255);
				}
			}
		}
	}
	omp_set_nested(1);
	for(int y=0;y<YLen && y<TBuff.GetHeight();y++){
		BYTE	*d=&TBuff.GetY(BuffY+y)[BuffX];
		memcpy(d,TmpBuff[y],XLen);
	}

	return _ER_true;
}

int	AreaFilterItemLineLargeEnflat::MakeAverage(int	MinC,int MaxC ,BYTE BTable[256],int TotalCount)
{
	int	s=TotalCount*(1.0-GetThresholdR()->AdoptedRate/100.0)/2;
	int	L;
	int	LNumb=0;
	for(L=MinC;L<MaxC;L++){
		LNumb+=BTable[L];
		if(LNumb>=s){
			break;
		}
	}
	int	H;
	int	HNumb=0;
	for(H=MaxC;H>=MinC;H--){
		HNumb+=BTable[H];
		if(HNumb>=s){
			break;
		}
	}
	double	D=0;
	int	Numb=0;
	for(int i=L;i<=H;i++){
		Numb+=BTable[i];
		D+=((double)i)*BTable[i];
	}
	return D/Numb;
}

int	AreaFilterItemLineLargeEnflat::MakeAverage(int	MinC,int MaxC ,WORD BTable[256],int TotalCount)
{
	int	s=TotalCount*(1.0-GetThresholdR()->AdoptedRate/100.0)/2;
	int	L;
	int	LNumb=0;
	for(L=MinC;L<MaxC;L++){
		LNumb+=BTable[L];
		if(LNumb>=s){
			break;
		}
	}
	int	H;
	int	HNumb=0;
	for(H=MaxC;H>=MinC;H--){
		HNumb+=BTable[H];
		if(HNumb>=s){
			break;
		}
	}
	double	D=0;
	int	Numb=0;
	for(int i=L;i<=H;i++){
		Numb+=BTable[i];
		D+=((double)i)*BTable[i];
	}
	return D/Numb;
}

int	AreaFilterItemLineLargeEnflat::MakeAverage(int	MinC,int MaxC ,int BTable[256],int TotalCount)
{
	int	s=TotalCount*(1.0-GetThresholdR()->AdoptedRate/100.0)/2;
	int	L;
	int	LNumb=0;
	for(L=MinC;L<MaxC;L++){
		LNumb+=BTable[L];
		if(LNumb>=s){
			break;
		}
	}
	int	H;
	int	HNumb=0;
	for(H=MaxC;H>=MinC;H--){
		HNumb+=BTable[H];
		if(HNumb>=s){
			break;
		}
	}
	double	D=0;
	int	Numb=0;
	for(int i=L;i<=H;i++){
		Numb+=BTable[i];
		D+=((double)i)*BTable[i];
	}
	return D/Numb;
}
void	AreaFilterItemLineLargeEnflat::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AreaFilterItem::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
}

