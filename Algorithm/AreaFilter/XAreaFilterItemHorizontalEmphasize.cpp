/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterAreaItemHorizontalEmphasize.cpp
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


AreaFilterThresholdHorizontalEmphasize::AreaFilterThresholdHorizontalEmphasize(AreaFilterItemHorizontalEmphasize *parent)
:AlgorithmThreshold(parent)
{
	BlockSize		=20;
	EmphasizeRate	=1;
	SkipDot			=4;
	MoveByAlignment	=true;
	BlockHeight		=200;
}

void	AreaFilterThresholdHorizontalEmphasize::CopyFrom(const AlgorithmThreshold &src)
{
	const AreaFilterThresholdHorizontalEmphasize	*s=(const AreaFilterThresholdHorizontalEmphasize *)&src;
	BlockSize		=s->BlockSize;
	EmphasizeRate	=s->EmphasizeRate;
	SkipDot			=s->SkipDot;
	MoveByAlignment	=s->MoveByAlignment;
	BlockHeight		=s->BlockHeight;
}
bool	AreaFilterThresholdHorizontalEmphasize::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AreaFilterThresholdHorizontalEmphasize	*s=(const AreaFilterThresholdHorizontalEmphasize *)&src;
	if(BlockSize		!=s->BlockSize		)	return false;
	if(EmphasizeRate	!=s->EmphasizeRate	)	return false;
	if(SkipDot			!=s->SkipDot		)	return false;
	if(MoveByAlignment	!=s->MoveByAlignment)	return false;
	if(BlockHeight		!=s->BlockHeight	)	return false;
	return true;
}
bool	AreaFilterThresholdHorizontalEmphasize::Save(QIODevice *f)
{
	WORD	Ver=2;

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
	if(::Save(f,BlockHeight)==false)
		return false;
	return true;
}
bool	AreaFilterThresholdHorizontalEmphasize::Load(QIODevice *f)
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
	BlockHeight=BlockSize;
	if(Ver>=2){
		if(::Load(f,BlockHeight)==false)
			return false;
	}

	return true;
}

void AreaFilterThresholdHorizontalEmphasize::FromLibrary(AlgorithmLibrary *src)
{
	BlockSize		=((AreaFilterLibrary *)src)->BlockSize;
	EmphasizeRate	=((AreaFilterLibrary *)src)->EmphasizeRate;
	SkipDot			=((AreaFilterLibrary *)src)->SkipDot;
	MoveByAlignment	=((AreaFilterLibrary *)src)->MoveByAlignment;
	BlockHeight		=((AreaFilterLibrary *)src)->BlockHeight;
}

void AreaFilterThresholdHorizontalEmphasize::ToLibrary(AlgorithmLibrary *dest)
{
	((AreaFilterLibrary *)dest)->BlockSize		=BlockSize;
	((AreaFilterLibrary *)dest)->EmphasizeRate	=EmphasizeRate;
	((AreaFilterLibrary *)dest)->SkipDot		=SkipDot;
	((AreaFilterLibrary *)dest)->MoveByAlignment=MoveByAlignment;
	((AreaFilterLibrary *)dest)->BlockHeight	=BlockHeight;
}

AreaFilterItemHorizontalEmphasize::AreaFilterItemHorizontalEmphasize(void)
{
	AVector		=NULL;
	MasterBrightness=0;
	TmpBuff		=NULL;
	XLen		=0;
	YLen		=0;
}
AreaFilterItemHorizontalEmphasize::~AreaFilterItemHorizontalEmphasize(void)
{
	if(TmpBuff!=NULL){
		DeleteMatrixBuff(TmpBuff,YLen);
		TmpBuff=NULL;
	}
}

AlgorithmItemPLI	&AreaFilterItemHorizontalEmphasize::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}
bool    AreaFilterItemHorizontalEmphasize::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaFilterItemHorizontalEmphasize::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}


ExeResult	AreaFilterItemHorizontalEmphasize::ExecuteInitialAfterEdit(int ExeID 
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

	if(TmpBuff!=NULL){
		DeleteMatrixBuff(TmpBuff,YLen);
		TmpBuff=NULL;
	}
	XLen=GetArea().GetWidth();
	YLen=GetArea().GetHeight()+1;
	XLen=min(GetDotPerLine(),GetArea().GetWidth());
	YLen=min(GetMaxLines(),GetArea().GetHeight()+1);

	TmpBuff	=MakeMatrixBuff(XLen,YLen);
	BuffX	=GetArea().GetMinX();
	BuffY	=GetArea().GetMinY();
	MatrixBuffClear	(TmpBuff ,MasterBrightness ,XLen ,YLen);

	return _ER_true;
}

ExeResult	AreaFilterItemHorizontalEmphasize::ExecutePreProcessing       (int ExeID ,int ThreadNo, ResultInItemRoot *Res)
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
	int	R=BlockSize/2;
	ClippedArea=GetArea();
	ClippedArea.ClipArea(R+abs(mx),R+abs(my),GetDotPerLine()-R-abs(mx),GetMaxLines()-R-abs(my));
	ImageBuffer	&TBuff=GetTargetBuff();
	int		XCount		=BlockSize/SkipDot;
	double	OverlapRate	=0.25;
	int		BlockHeight	=GetThresholdR()->BlockHeight;
	int		YStep		=GetThresholdR()->BlockHeight*OverlapRate;
	int		YEffectiveLines=BlockSize-YStep-YStep;
	int		TopY=ClippedArea.GetMinY();
	int	N=ClippedArea.GetFLineLen();
	omp_set_nested(0);
	
	#pragma omp parallel    num_threads(8)                           
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			int		BTable[5000];
			int	Y	=ClippedArea.GetFLineAbsY(i)+my;
			int	X1	=ClippedArea.GetFLineLeftX(i)+mx;
			int	Numb=ClippedArea.GetFLineNumb(i);
			
			int	qy=Y-TopY;
			if((qy%YEffectiveLines)!=0)
				continue;

			for(int j=0;j<Numb;j+=SkipDot){
				int	X=X1+j;
				int	DotCount=0;
				for(int yn=0;yn<BlockHeight;yn++){
					int	HY=Y+yn-YStep;
					if(0<=HY && HY<GetMaxLines()){
						BYTE	*s=&TBuff.GetY(HY)[X-R];
						BTable[yn]=*s;
						s+=SkipDot;
						for(int xn=1;xn<XCount;xn++){
							BTable[yn]+=*s;
							s+=SkipDot;
						}
						DotCount+=XCount;
					}
					else{
						BTable[yn]=0;
					}
				}
				double	Avr=0;
				for(int k=0;k<BlockHeight;k++){
					Avr+=BTable[k];
				}
				Avr/=DotCount;

				int	MaxYn=min(BlockHeight-YStep,YLen-(Y-YStep));
				int	MaxXn=min(SkipDot,Numb-j);
				for(int yn=YStep;yn<MaxYn;yn++){
					BYTE	*tP=TmpBuff[Y-YStep+yn-BuffY];
					BYTE	*d=TBuff.GetY(Y-YStep+yn);
					int	AddedD=(((double)BTable[yn])/((double)XCount)-Avr)*GetThresholdR()->EmphasizeRate/100.0;

					for(int xn=0;xn<MaxXn;xn++){
						tP[X-BuffX+xn]=Clipping((int)(d[X+xn] + AddedD),0,255);
					}
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

void	AreaFilterItemHorizontalEmphasize::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AreaFilterItem::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
}

