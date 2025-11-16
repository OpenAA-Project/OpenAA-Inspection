/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterAreaItemDifferential.cpp
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


AreaFilterThresholdDifferential::AreaFilterThresholdDifferential(AreaFilterItemDifferential *parent)
:AlgorithmThreshold(parent)
{
	BlockSize		=20;
	EmphasizeRate	=1;
	SkipDot			=4;
	MoveByAlignment	=true;
	ShrinkRate		=200;
}

void	AreaFilterThresholdDifferential::CopyFrom(const AlgorithmThreshold &src)
{
	const AreaFilterThresholdDifferential	*s=(const AreaFilterThresholdDifferential *)&src;
	BlockSize		=s->BlockSize;
	EmphasizeRate	=s->EmphasizeRate;
	SkipDot			=s->SkipDot;
	MoveByAlignment	=s->MoveByAlignment;
	ShrinkRate		=s->ShrinkRate;
}
bool	AreaFilterThresholdDifferential::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AreaFilterThresholdDifferential	*s=(const AreaFilterThresholdDifferential *)&src;
	if(BlockSize		!=s->BlockSize		)	return false;
	if(EmphasizeRate	!=s->EmphasizeRate	)	return false;
	if(SkipDot			!=s->SkipDot		)	return false;
	if(MoveByAlignment	!=s->MoveByAlignment)	return false;
	if(ShrinkRate		!=s->ShrinkRate	)		return false;
	return true;
}
bool	AreaFilterThresholdDifferential::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,BlockSize)==false)
		return false;
	if(::Save(f,EmphasizeRate)==false)
		return false;
	if(::Save(f,SkipDot)==false)
		return false;
	if(::Save(f,MoveByAlignment)==false)
		return false;
	if(::Save(f,ShrinkRate)==false)
		return false;
	return true;
}
bool	AreaFilterThresholdDifferential::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,BlockSize)==false)
		return false;
	if(::Load(f,EmphasizeRate)==false)
		return false;
	if(::Load(f,SkipDot)==false)
		return false;
	if(::Load(f,MoveByAlignment)==false)
		return false;
	if(::Load(f,ShrinkRate)==false)
		return false;

	return true;
}

void AreaFilterThresholdDifferential::FromLibrary(AlgorithmLibrary *src)
{
	BlockSize		=((AreaFilterLibrary *)src)->BlockSize;
	EmphasizeRate	=((AreaFilterLibrary *)src)->EmphasizeRate;
	SkipDot			=((AreaFilterLibrary *)src)->SkipDot;
	MoveByAlignment	=((AreaFilterLibrary *)src)->MoveByAlignment;
	ShrinkRate		=((AreaFilterLibrary *)src)->ShrinkRate;
}

void AreaFilterThresholdDifferential::ToLibrary(AlgorithmLibrary *dest)
{
	((AreaFilterLibrary *)dest)->BlockSize		=BlockSize;
	((AreaFilterLibrary *)dest)->EmphasizeRate	=EmphasizeRate;
	((AreaFilterLibrary *)dest)->SkipDot		=SkipDot;
	((AreaFilterLibrary *)dest)->MoveByAlignment=MoveByAlignment;
	((AreaFilterLibrary *)dest)->ShrinkRate		=ShrinkRate;
}

AreaFilterItemDifferential::AreaFilterItemDifferential(void)
{
	AVector		=NULL;
	MasterBrightness=0;
	TmpBuff		=NULL;
	XLen		=0;
	YLen		=0;
	FilterDim	=NULL;
	FilterSize	=0;
}
AreaFilterItemDifferential::~AreaFilterItemDifferential(void)
{
	if(TmpBuff!=NULL){
		DeleteMatrixBuff(TmpBuff,YLen);
		TmpBuff=NULL;
	}
	if(FilterDim!=NULL){
		DeleteMatrixBuff((BYTE **)FilterDim,FilterSize);
		FilterDim=NULL;
	}
}

AlgorithmItemPLI	&AreaFilterItemDifferential::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}
bool    AreaFilterItemDifferential::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaFilterItemDifferential::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}


ExeResult	AreaFilterItemDifferential::ExecuteInitialAfterEdit(int ExeID ,int ThresdNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}

	if(TmpBuff!=NULL){
		DeleteMatrixBuff(TmpBuff,YLen);
		TmpBuff=NULL;
	}
	int	ShrinkRate=GetThresholdR()->ShrinkRate;
	if(ShrinkRate<=0)
		ShrinkRate=1;
	XLen=GetArea().GetWidth();
	YLen=GetArea().GetHeight()+1;
	XLen=(min(GetDotPerLine(),GetArea().GetWidth())+ShrinkRate-1)/ShrinkRate;
	YLen=(min(GetMaxLines(),GetArea().GetHeight()+1)+ShrinkRate-1)/ShrinkRate;

	TmpBuff	=MakeMatrixBuff(XLen,YLen);
	BuffX	=GetArea().GetMinX();
	BuffY	=GetArea().GetMinY();
	MatrixBuffClear	(TmpBuff ,MasterBrightness ,XLen ,YLen);

	if(FilterDim!=NULL){
		DeleteMatrixBuff((BYTE **)FilterDim,FilterSize);
		FilterDim=NULL;
	}
	FilterSize=GetThresholdR()->BlockSize;
	if((FilterSize &1)==0)
		FilterSize |=1;
	FilterDim	=(int **)MakeMatrixBuff(FilterSize*sizeof(int),FilterSize);
	int	FilterR=FilterSize/2;
	double	Sigma=FilterR;
	double	Sum=0;
	for(int y=0;y<FilterSize;y++){
		for(int x=0;x<FilterSize;x++){
			double	r=hypot(x-FilterR,y-FilterR);
			double	e=exp(-(r-FilterR)*(r-FilterR)/(2*Sigma*Sigma))/(sqrt(2.0)*Sigma);
			FilterDim[y][x]=e*65536.0;
			if(x!=FilterR && y!=FilterR){
				Sum+=FilterDim[y][x];
			}
		}
	}
	FilterDim[FilterR][FilterR]=-Sum;

	return _ER_true;
}

ExeResult	AreaFilterItemDifferential::ExecuteStartByInspection	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AreaFilterItem::ExecuteStartByInspection(ExeID ,ThreadNo,Res);
	MatrixBuffClear	(TmpBuff ,0 ,XLen ,YLen);
	return _ER_true;
}

ExeResult	AreaFilterItemDifferential::ExecutePreProcessing       (int ExeID ,int ThreadNo, ResultInItemRoot *Res)
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
	int	R=FilterSize/2;
	int	ShrinkRate	=GetThresholdR()->ShrinkRate;
	if(ShrinkRate<=0)
		ShrinkRate=1;
	ClippedArea=GetArea();
	if(GetThresholdR()->MoveByAlignment==true){
		ClippedArea.MoveToClip(mx,my,R,R,GetDotPerLine()-R,GetMaxLines()-R);
	}
	else{
		ClippedArea.ClipArea(R,R,GetDotPerLine()-R,GetMaxLines()-R);
	}
	ImageBuffer	&TBuff=GetTargetBuff();
	int	TopY	=ClippedArea.GetMinY();
	int	LeftX	=ClippedArea.GetMinX();
	int	N=ClippedArea.GetFLineLen();
	int	FilterR=FilterSize/2;
	omp_set_nested(0);
	
	#pragma omp parallel    num_threads(8)                           
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			int	Y	=ClippedArea.GetFLineAbsY(i);
			if(((Y-TopY)%ShrinkRate)!=0)
				continue;
			int	DestY=(Y-TopY)/ShrinkRate;

			int	X1	=ClippedArea.GetFLineLeftX(i);
			int	DestX=(X1-LeftX)/ShrinkRate;
			
			int	X=DestX*ShrinkRate;
			if(X<X1)
				X+=ShrinkRate;
			int	X2=ClippedArea.GetFLineRightX(i);
			
			for(;X<X2;X+=ShrinkRate,DestX++){
				int	D=0;
				int	sy=Y;
				int	ey=0;
				for(int yn=-FilterR;yn<=FilterR;yn++,sy+=ShrinkRate,ey++){
					int	sx=X;
					BYTE	*s=TBuff.GetY(sy);
					int		*F=FilterDim[ey];
					int		ex=0;
					for(int xn=-FilterR;xn<=FilterR;xn++,sx+=ShrinkRate,ex++){
						D+=F[ex]*s[sx];
					}
				}
				TmpBuff[DestY][DestX]=Clipping(D/65536.0,0.0,255.0);
			}
		}
	}
	omp_set_nested(1);
	for(int y=0;y<YLen && y<TBuff.GetHeight();y++){
		BYTE	*d=&TBuff.GetY(TopY+y)[LeftX];
		int	DestY=(y-TopY)/ShrinkRate;
		int	xn=0;
		for(int x=0;x<XLen;x+=ShrinkRate,xn++){
			int	X=LeftX+x;
			BYTE	D=TmpBuff[DestY][xn];
			for(int i=0;i<ShrinkRate;i++){
				d[X+i]=D;
			}
		}
	}

	return _ER_true;
}

void	AreaFilterItemDifferential::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AreaFilterItem::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
}

