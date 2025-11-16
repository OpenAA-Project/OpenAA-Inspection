/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\MatchShiftRotation\XMatchShiftRotationItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XMatchShiftRotation.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XImageProcess.h"


void	FlexAreaImageListCoeffAngle::MakeRoughSum(int Sep)
{
	RoughSumA=RoughSumA2=0;
	RoughNumb=0;
	/*
	for(int i=0;i<DataLen;i+=Sep){
		RoughSumA+=Data[i];
		RoughSumA2+=Data[i]*Data[i];
		RoughNumb++;
		
	}
	*/
	if(CoefDim!=NULL){
		delete	[]CoefDim;
	}
	BYTE	*d=Data;
	CoefDim	=new struct	CoefDimStruct[GetFLineLen()];
	CoefDimNumb=0;
	int	Sep2=Sep/2;
	for(int i=0;i<GetFLineLen();i++){
		int x1  =GetFLineLeftX(i);
	    int Numb=GetFLineNumb(i);
		int	y	=GetFLineAbsY(i);
		if((y%Sep)==0){
			CoefDim[CoefDimNumb].AbsY=y;
			CoefDim[CoefDimNumb].SepX=Sep;
			CoefDim[CoefDimNumb].Numb=0;
			CoefDim[CoefDimNumb].Src=NULL;
			for(int t=0;t<Numb;t++,d++){
				int	x=x1+t;
				if((x%Sep)==0){
					if(CoefDim[CoefDimNumb].Src==NULL){
						CoefDim[CoefDimNumb].Src=d;
						CoefDim[CoefDimNumb].LeftX=x;
					}
					CoefDim[CoefDimNumb].Numb++;
				}
			}
			if(CoefDim[CoefDimNumb].Numb>0){
				CoefDimNumb++;
			}
		}
		else if((y%Sep)==Sep2){
			CoefDim[CoefDimNumb].AbsY=y;
			CoefDim[CoefDimNumb].SepX=Sep;
			CoefDim[CoefDimNumb].Numb=0;
			CoefDim[CoefDimNumb].Src=NULL;
			for(int t=0;t<Numb;t++,d++){
				int	x=x1+t;
				if((x%Sep)==Sep2){
					if(CoefDim[CoefDimNumb].Src==NULL){
						CoefDim[CoefDimNumb].Src=d;
						CoefDim[CoefDimNumb].LeftX=x;
					}
					CoefDim[CoefDimNumb].Numb++;
				}
			}
			if(CoefDim[CoefDimNumb].Numb>0){
				CoefDimNumb++;
			}
		}
		else{
			d+=Numb;
		}
	}

	for(int i=0;i<CoefDimNumb;i++){
		BYTE	*s=CoefDim[i].Src;
		for(int j=0;j<CoefDim[i].Numb;j++){
			RoughSumA+=*s;
			RoughSumA2+=*s**s;
			RoughNumb++;
			s+=CoefDim[i].SepX;
		}
	}
	AvrRoughS=RoughSumA/RoughNumb;
}
double	FlexAreaImageListCoeffAngle::CalcCoeffRough(int dx ,int dy ,ImageBuffer &Buffer)
{
	if(0<=(GetMinX()+dx) && 0<=(GetMinY()+dy) && (GetMaxX()+dx)<Buffer.GetWidth() && (GetMaxY()+dy)<Buffer.GetHeight()){

		unsigned	int		SumB=0;
		double	SumB2=0;
		double	SumAB=0;

		struct	CoefDimStruct	*R=CoefDim;
		for(int i=0;i<CoefDimNumb;i++,R++){
			BYTE	*s=R->Src;
			int		y=R->AbsY+dy;
			BYTE	*d=Buffer.GetY(y) + R->LeftX+dx;
			int	n=CoefDim[i].Numb;
			int	SepX=CoefDim[i].SepX;
			unsigned	int		S2Sum=0;
			unsigned	int		SDSum=0;
			for(int j=0;j<n;j++){
				SumB+=*d;
				S2Sum+=*d**d;
				SDSum+=*s**d;
				s+=SepX;
				d+=SepX;
			}
			SumB2+=S2Sum;
			SumAB+=SDSum;
		}


		//int	NN=(int)(d-Data);

		//if(SDCount==0 || NN==0){
		//	return 0;
		//}
		double	AvrD=((double)SumB)/((double)RoughNumb);

		double	D=(RoughSumA2-RoughNumb*AvrRoughS*AvrRoughS)*(SumB2-RoughNumb*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=SumAB-RoughNumb*AvrRoughS*AvrD;
		return K/D;
	}
	else{
		BYTE	*d=Data;
		int		_SumA=0;
		double	_SumA2=0;
		int		_SumB=0;
		double	_SumB2=0;
		double	_SumAB=0;
		int		_SDCount=0;
		for(int i=0;i<GetFLineLen();i++){
			int x1  =GetFLineLeftX(i);
	        int Numb=GetFLineNumb(i);
			int	y	=GetFLineAbsY(i);
			if(0<=(y+dy) && (y+dy)<Buffer.GetHeight()){
				BYTE	*s=Buffer.GetY(y+dy);
				int		S2SumA=0;
				int		S2SumB=0;
				int		SDSum=0;
				for(int j=0;j<Numb;j++){
					int	x=x1+j+dx;
					if(0<=x && x<Buffer.GetWidth()){
						BYTE	k=s[x];
						int	c=*d;
						_SumA+=c;
						_SumB+=k;
						S2SumA+=c*c;
						S2SumB+=k*k;
						SDSum+=k*c;
						_SDCount++;
					}
					d++;
				}
				_SumA2+=S2SumA;
				_SumB2+=S2SumB;
				_SumAB+=SDSum;
			}
			else{
				d+=Numb;
			}
		}

		if(_SDCount==0){
			return 0;
		}
		double	AvrS=_SumA/_SDCount;
		double	AvrD=_SumB/_SDCount;

		double	D=(_SumA2-_SDCount*AvrS*AvrS)*(_SumB2-_SDCount*AvrD*AvrD);
		if(D<=0){
			return 0;
		}
		D=sqrt(D);
		double	K=_SumAB-_SDCount*AvrS*AvrD;
		return K/D;
	}
}


MatchShiftRotationThreshold::MatchShiftRotationThreshold(MatchShiftRotationItem *parent)
:AlgorithmThreshold(parent)
{
	SearchLittleInItem		=2;
	MatchingRate	=0.8;
	TargetLayer		=0;
}
MatchShiftRotationThreshold::~MatchShiftRotationThreshold(void)
{
}

void	MatchShiftRotationThreshold::RegistHist(void)
{
	RegistInt	("Shift-X"	,Hist_MatchShiftRotationShiftX		);
	RegistInt	("Shift-Y"	,Hist_MatchShiftRotationShiftY		);
	RegistInt	("Angle"	,Hist_MatchShiftRotationRotation	);
	RegistInt	("Rate"		,Hist_MatchShiftRotationRate		);
}

void	MatchShiftRotationThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MatchShiftRotationThreshold *s=(const MatchShiftRotationThreshold *)&src;
	SearchLittleInItem	=s->SearchLittleInItem;
	TargetLayer			=s->TargetLayer;
	MatchingRate		=s->MatchingRate;
}
bool	MatchShiftRotationThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MatchShiftRotationThreshold *s=(const MatchShiftRotationThreshold *)&src;
	if(SearchLittleInItem	!=s->SearchLittleInItem	)	return false;
	if(TargetLayer			!=s->TargetLayer		)	return false;
	if(MatchingRate			!=s->MatchingRate		)	return false;
	return true;
}
void	MatchShiftRotationThreshold::FromLibrary(AlgorithmLibrary *src)
{
	SearchLittleInItem		=((MatchShiftRotationLibrary *)src)->SearchLittleInItem;
	if(src->GetAdaptedGenLayers().GetCount()==0 || src->GetAdaptedGenLayers().GetFirst()->GetValue()==0)
		TargetLayer	=0;
	else{
		TargetLayer	=	src->GetAdaptedGenLayers().GetFirst()->GetValue();
	}
	MatchingRate	=((MatchShiftRotationLibrary *)src)->MatchingRate;
}

void	MatchShiftRotationThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	((MatchShiftRotationLibrary *)Dest)->SearchLittleInItem		=SearchLittleInItem;
	((MatchShiftRotationLibrary *)Dest)->MatchingRate			=MatchingRate;
}

bool	MatchShiftRotationThreshold::Save(QIODevice *file)
{
	if(::Save(file,SearchLittleInItem)==false)
		return(false);
	if(::Save(file,TargetLayer)==false)
		return(false);
	if(::Save(file,MatchingRate)==false)
		return(false);

	return true;
}
bool	MatchShiftRotationThreshold::Load(QIODevice *file)
{
	if(::Load(file,SearchLittleInItem)==false)
		return(false);
	if(::Load(file,TargetLayer)==false)
		return(false);
	if(::Load(file,MatchingRate)==false)
		return(false);

	return true;
}

//---------------------------------------------------------------------------------------

MatchShiftRotationItem::MatchShiftRotationItem(void)
{
    ResultLittleDx	=0;
    ResultLittleDy	=0;
	AreaID			=0;
	MasterX			=0;
	MasterY			=0;

	StepAngle		=0;
}

MatchShiftRotationItem::~MatchShiftRotationItem(void)
{
}

void	MatchShiftRotationItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	Dx=0;
	int	Dy=0;
	if(Attr->DType==2){
		double Angle;
		GetResultTotalDxy(Dx ,Dy ,Angle);
	}
	MatchShiftRotationDrawAttr	*a=dynamic_cast<MatchShiftRotationDrawAttr *>(Attr);
	if(a!=NULL && (a->ModeDrawItem==true || (a->SelectedArea.GetCount()==0 || a->SelectedArea.IsInclude(AreaID)==true))){
		((MatchShiftRotationInPage *)GetParentInPage())->CurrentSelectedAreaID=a->SelectedArea;
		((MatchShiftRotationInPage *)GetParentInPage())->ModeShowArea		 =a->ModeDrawArea;
		if(IsEffective()==true){
			if(GetActive()==true){
				GetArea().DrawAlpha(Dx,Dy ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
			}
			else if(GetSelected()==true){
				GetArea().DrawAlpha(Dx,Dy ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
			}
			else{
				GetArea().DrawAlpha(Dx,Dy ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
			}
		}
	}
}

void	MatchShiftRotationItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	//int	cx,cy;
	//GetArea().GetCenter(cx,cy);
	if(IsEffective()==false)
		return;
	QColor	c=Qt::green;
	c.setAlpha(100);

	GetArea().Draw(0,0,&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);

	int dx ,dy;
	double Angle;
	GetResultTotalDxy(dx ,dy ,Angle);
	FlexAreaImageListCoeffAngle	*w=GetClosedPattern(Angle);
	if(w==NULL)
		return;

	QColor	ce=Qt::red;
	ce.setAlpha(180);
	w->DrawImage(dx,dy,&IData
				,ZoomRate ,MovX ,MovY
				,true,true,false,128);

	if(ZoomRate>=1.0){
		PData.drawText((MasterX+MovX)*ZoomRate,(MasterY+MovY)*ZoomRate
			,QString(/**/"MasterX=") +QString::number((int)MasterX)
			+QString(/**/",MasterY=")+QString::number((int)MasterY));
		PData.drawText((MasterX+MovX)*ZoomRate,(MasterY+MovY)*ZoomRate+16
			,QString(/**/ "dx=")+QString::number((int)(dx))	
			+QString(/**/",dy=")+QString::number((int)(dy))
			+QString(/**/",a=")+QString::number(Angle,'f',2));
	}
}

void	MatchShiftRotationItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	MatchShiftRotationItem	*ASrc=dynamic_cast<MatchShiftRotationItem *>(src);
	if(ASrc!=NULL){
		ResultLittleDx	=ASrc->ResultLittleDx;
	    ResultLittleDy	=ASrc->ResultLittleDy;
		AreaID			=ASrc->AreaID;
		MasterX			=ASrc->MasterX	+OffsetX;
		MasterY			=ASrc->MasterY	+OffsetY;
		StepAngle		=ASrc->StepAngle;
		Patterns		=ASrc->Patterns;
	}
}

bool	MatchShiftRotationItem::GetResultTotalDxy(int &dx ,int &dy ,double &Angle)
{
	dx=0;
	dy=0;
	Angle=0;
	XMatchShiftRotationArea	*A=GetMatchShiftRotationArea();
	if(A==NULL)
		return false;
	int	Cx,Cy;
	A->Area.GetCenter(Cx,Cy);
	int	ItemCx,ItemCy;
	GetCenter(ItemCx,ItemCy);

	Angle=A->ResultAngle;
	double	CosS=cos(A->ResultAngle);
	double	SinS=sin(A->ResultAngle);

	dx= (ItemCx-Cx)*CosS + (ItemCy-Cy)*SinS +Cx-ItemCx+ A->ResultDx +ResultLittleDx;
	dy=-(ItemCx-Cx)*SinS + (ItemCy-Cy)*CosS +Cy-ItemCy+ A->ResultDy +ResultLittleDy;
	return true;
}
FlexAreaImageListCoeffAngle	*MatchShiftRotationItem::GetClosedPattern(double angle)
{
	for(FlexAreaImageList *f=Patterns.GetFirst();f!=NULL;f=f->GetNext()){
		FlexAreaImageListCoeffAngle	*a=dynamic_cast<FlexAreaImageListCoeffAngle *>(f);
		if(a!=NULL){
			if(a->Angle>angle){
				return a;
			}
		}
	}
	return NULL;
}

AlgorithmItemPI	&MatchShiftRotationItem::operator=(const AlgorithmItemRoot &src)
{
	const MatchShiftRotationItem	*s=dynamic_cast<const MatchShiftRotationItem *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}


MatchShiftRotationItem   &MatchShiftRotationItem::operator=(MatchShiftRotationItem &src)
{
	AlgorithmItemPI::operator=(*((AlgorithmItemPI *)&src));

	MasterX			=src.MasterX;
	MasterY			=src.MasterY;
	SetArea		(src.GetArea());
    ResultLittleDx	=src.ResultLittleDx;
    ResultLittleDy	=src.ResultLittleDy;
	StepAngle		=src.StepAngle;
	Patterns		=src.Patterns;

	return(*this);
}

struct	MatchBCStruct
{
	int	DDiffAbs;
	int	dx;
	int	dy;
};

void    MatchShiftRotationItem::MoveTo(int dx ,int dy)
{
	GetArea()	.MoveToNoClip(dx,dy);
    Patterns	.MoveToNoClip(dx,dy);

	MasterX	+=dx;
	MasterY	+=dy;
}

bool    MatchShiftRotationItem::Save(QIODevice *file)
{
	WORD	Ver=2;
	if(AlgorithmItemPI::Save(file)==false)
		return(false);

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,AreaID)==false)
		return false;

	return(true);
}
bool    MatchShiftRotationItem::Load(QIODevice *file,LayersBase *LBase)
{
	WORD	Ver;

	if(AlgorithmItemPI::Load(file,LBase)==false)
		return(false);
	if(::Load(file,Ver)==false)
		return false;

	if(::Load(file,AreaID)==false)
		return false;

	return(true);
}

bool	MatchShiftRotationItem::IsAreaEffective(void)
{
	if(GetArea().IsNull()==false)
		return(true);
	return(false);
}


ExeResult	MatchShiftRotationItem::ExecuteInitialAfterEdit	(int ExeID 
															,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();

	for(XMatchShiftRotationArea *a=((MatchShiftRotationInPage *)GetParentInPage())->Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==AreaID){
			ParentArea=a;
			break;
		}
	}

	double	Cx,Cy;
	GetCenter(Cx,Cy);
	Patterns.RemoveAll();
	ImagePointerContainer ImageList;
	GetMasterBuffList(ImageList);
	ImageBuffer	*MasterBuff=NULL;
	const MatchShiftRotationThreshold	*RThr=GetThresholdR();
	if(0<=RThr->TargetLayer && RThr->TargetLayer<GetLayerNumb()){
		MasterBuff=ImageList[RThr->TargetLayer];
	}
	else{
		MasterBuff=ImageList[0];
	}

	int	XLen=hypot(W,H)+16;
	int	YLen=XLen;
	double	XLenCenter=XLen/2.0;
	double	YLenCenter=YLen/2.0;

	int	XByte=(XLen+7)/8;
	BYTE	**BMap =MakeMatrixBuff(XByte,YLen);
	BYTE	**DMap =MakeMatrixBuff(XByte,YLen);
	ImageBuffer	DBuffer(0,XLen,YLen);

	MatrixBuffClear	(BMap ,0 ,XByte,YLen);
	FlexArea	A=GetArea();
	A.MoveToNoClip(-Cx+XLenCenter,-Cy+YLenCenter);
	A.MakeBitData(BMap,XLen,YLen);

	StepAngle=atan(2.0/XLen);
	int	SearchAngle=ParentArea->SearchAngle;
	int	N=ceil(2*M_PI/StepAngle);
	int	N2=(N+1)/2;
	//int	OffX=A.GetWidth()/2;
	//int	OffY=A.GetHeight()/2;
	for(int i=-N2;i<=N2;i++){
		double	a=i*StepAngle;
		if(fabs(a)*180.0/M_PI<SearchAngle){
			double	CosS=cos(a);
			double	SinS=sin(a);
			MatrixBuffClear	(DMap ,0 ,XByte,YLen);
			for(int y=0;y<YLen;y++){
				for(int x=0;x<XLen;x++){
					int	X= (x-XLenCenter)*CosS-(y-YLenCenter)*SinS+XLenCenter;
					int	Y= (x-XLenCenter)*SinS+(y-YLenCenter)*CosS+YLenCenter;
					if(0<=X && X<XLen && 0<=Y && Y<YLen){
						if(GetBmpBit(BMap,X,Y)!=0)
							SetBmpBit1(DMap,x,y);
						else
							SetBmpBit0(DMap,x,y);
					}
					int	Px=X-XLenCenter+Cx;
					int	Py=Y-YLenCenter+Cy;
					if(0<=Px && Px<GetDotPerLine() && 0<=Py && Py<GetMaxLines()){
						DBuffer.GetY(y)[x]=MasterBuff->GetY(Py)[Px];
					}
				}
			}
			PureFlexAreaListContainer FPack;
			PickupFlexArea(DMap ,XByte ,XLen,YLen ,FPack);
			PureFlexAreaList	*f=FPack.GetFirst();
			if(f!=NULL){
				FlexAreaImageListCoeffAngle	*t=new FlexAreaImageListCoeffAngle();
				t->Angle=a;
				t->Set(*f,DBuffer);
				t->MoveToNoClip(Cx-XLenCenter,Cy-YLenCenter);
				Patterns.AppendList(t);
			}
		}
	}
	MatchShiftRotationBase *PBase=(MatchShiftRotationBase *)GetParentBase();
	for(FlexAreaImageList *f=Patterns.GetFirst();f!=NULL;f=f->GetNext()){
		FlexAreaImageListCoeffAngle	*a=dynamic_cast<FlexAreaImageListCoeffAngle *>(f);
		if(a!=NULL){
			//a->SetAndCalc(*MasterBuff);
			a->MakeSum();
			a->MakeRoughSum(PBase->RoughSeparationIsolation);
		}
	}

	return Ret;
}

ExeResult	MatchShiftRotationItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	return _ER_true;
}

double	MatchShiftRotationItem::Calc(int dx, int dy ,double angle,int &SearchedDx ,int &SearchedDy,int step)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	ImageBuffer	*TargetBuff=NULL;
	const MatchShiftRotationThreshold	*RThr=GetThresholdR();
	if(0<=RThr->TargetLayer && RThr->TargetLayer<GetLayerNumb()){
		TargetBuff=ImageList[RThr->TargetLayer];
	}
	else{
		TargetBuff=ImageList[0];
	}
	FlexAreaImageListCoeffAngle	*a=GetClosedPattern(angle);
	if(a!=NULL){
		double	MaxD=0;
		int		MaxHx=0;
		int		MaxHy=0;

		for(int hy=-RThr->SearchLittleInItem;hy<=RThr->SearchLittleInItem;hy+=step){
			for(int hx=-RThr->SearchLittleInItem;hx<=RThr->SearchLittleInItem;hx+=step){
				double	d=a->CalcCoeff(dx+hx,dy+hy,*TargetBuff);
				if(d>MaxD){
					MaxD=d;
					MaxHx=hx;
					MaxHy=hy;
				}
			}
		}
		SearchedDx=MaxHx;
		SearchedDy=MaxHy;
		return MaxD;
	}
	return 0;
}

double	MatchShiftRotationItem::CalcRough(int dx, int dy ,double angle,int step)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	ImageBuffer	*TargetBuff=NULL;
	const MatchShiftRotationThreshold	*RThr=GetThresholdR();
	if(0<=RThr->TargetLayer && RThr->TargetLayer<GetLayerNumb()){
		TargetBuff=ImageList[RThr->TargetLayer];
	}
	else{
		TargetBuff=ImageList[0];
	}
	FlexAreaImageListCoeffAngle	*a=GetClosedPattern(angle);
	if(a!=NULL){
		double	d=a->CalcCoeffRough(dx,dy,*TargetBuff);
		return d;
		/*
		if(a->Angle>angle){
			double	MaxD=0;
			int		MaxHx=0;
			int		MaxHy=0;

			for(int hy=-RThr->SearchLittleInItem;hy<=RThr->SearchLittleInItem;hy+=step){
				for(int hx=-RThr->SearchLittleInItem;hx<=RThr->SearchLittleInItem;hx+=step){
					double	d=a->CalcCoeffRough(dx+hx,dy+hy,*TargetBuff,RoughIsolation);
					if(d>MaxD){
						MaxD=d;
						MaxHx=hx;
						MaxHy=hy;
					}
				}
			}
			return MaxD;
		}
		*/
	}
	return 0;
}
ExeResult	MatchShiftRotationItem::ExecuteProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(IsProcessDone()==false){
		XMatchShiftRotationArea	*A=GetMatchShiftRotationArea();
		if(A!=NULL){
			const MatchShiftRotationThreshold	*RThr=GetThresholdR();
			Res->SetAlignedXY(A->ResultDx+ResultLittleDx,A->ResultDy+ResultLittleDy);
			Res->SetResult1(MatchingRate);
			Res->SetResult2(0);
			if(MatchingRate>=RThr->MatchingRate){
				Res->SetError(1);	//OK			
			}
			else{
				Res->SetError(2);	//NG
			}

			GetThresholdW()->AddHist(Hist_MatchShiftRotationShiftX		,A->ResultDx+ResultLittleDx);
			GetThresholdW()->AddHist(Hist_MatchShiftRotationShiftY		,A->ResultDy+ResultLittleDy);
			GetThresholdW()->AddHist(Hist_MatchShiftRotationRotation	,A->ResultAngle);
			GetThresholdW()->AddHist(Hist_MatchShiftRotationRate		,MatchingRate);
		}
	}
	SetProcessDone();
	return _ER_true;
}

void	MatchShiftRotationItem::CopyThresholdOnly(MatchShiftRotationItem *src)
{
	const MatchShiftRotationThreshold	*RThr=src->GetThresholdR(GetLayersBase());
	GetThresholdW()->TargetLayer		=RThr->TargetLayer	;
	GetThresholdW()->SearchLittleInItem	=RThr->SearchLittleInItem	;
	GetThresholdW()->MatchingRate		=RThr->MatchingRate	;
}

void	MatchShiftRotationItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MatchShiftRotationInPage	*Pg=dynamic_cast<MatchShiftRotationInPage *>(GetParentInPage());
			UndoElement<MatchShiftRotationInPage>	*UPointer=new UndoElement<MatchShiftRotationInPage>(Pg,&MatchShiftRotationInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MatchShiftRotationItem *src=(MatchShiftRotationItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MatchShiftRotationItem *)Data)->GetLibID()){
			MatchShiftRotationInPage	*Pg=dynamic_cast<MatchShiftRotationInPage *>(GetParentInPage());
			UndoElement<MatchShiftRotationInPage>	*UPointer=new UndoElement<MatchShiftRotationInPage>(Pg,&MatchShiftRotationInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MatchShiftRotationItem *src=(MatchShiftRotationItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((MatchShiftRotationItem *)Data)->GetLibID()){
			MatchShiftRotationInPage	*Pg=dynamic_cast<MatchShiftRotationInPage *>(GetParentInPage());
			UndoElement<MatchShiftRotationInPage>	*UPointer=new UndoElement<MatchShiftRotationInPage>(Pg,&MatchShiftRotationInPage::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MatchShiftRotationItem *src=(MatchShiftRotationItem *)Data;
			SetItemName(src->GetItemName());
		}
	}

}

void	MatchShiftRotationItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	::Save(&Buff,AreaID);
	::Save(&Buff,ParentArea->SearchArea);
	::Save(&Buff,ParentArea->SearchAngle);

	AInd->Something=Buff.buffer();

}