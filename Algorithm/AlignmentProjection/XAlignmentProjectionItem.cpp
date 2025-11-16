/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentProjection\AlignmentProjectionItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentProjection.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XImageProcess.h"

static	int TransZone=4;
static	int InOutZone=8;
static	int MemTransZone=50;
static	int MemInOutZone=100;

AlignmentProjectionThreshold::AlignmentProjectionThreshold(AlignmentProjectionItem *parent)
:AlgorithmThreshold(parent)
{
	PeakCount		=2;
	Angle			=0;
	PeakIsolation	=30;
	UsageLayer		=0;
	AbandonRateL	=0.1;
	AbandonRateH	=0.2;
}
AlignmentProjectionThreshold::~AlignmentProjectionThreshold(void)
{
}

void	AlignmentProjectionThreshold::RegistHist(void)
{
	RegistInt			("Shift-X"		,Hist_AlighmentProjectionShiftX);
	RegistInt			("Shift-Y"		,Hist_AlighmentProjectionShiftY);
}

void	AlignmentProjectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const	AlignmentProjectionThreshold	*s=(const AlignmentProjectionThreshold *)&src;
	PeakCount		=s->PeakCount	;
	Angle			=s->Angle		;
	PeakIsolation	=s->PeakIsolation	;
	UsageLayer		=s->UsageLayer;
	AbandonRateL	=s->AbandonRateL;
	AbandonRateH	=s->AbandonRateH;
}
bool	AlignmentProjectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const	AlignmentProjectionThreshold	*s=(const AlignmentProjectionThreshold *)&src;
	if(PeakCount	==s->PeakCount
	&& Angle		==s->Angle 
	&& PeakIsolation==s->PeakIsolation
	&& UsageLayer	==s->UsageLayer 
	&& AbandonRateL	==s->AbandonRateL 
	&& AbandonRateH	==s->AbandonRateH)
		return true;
	return false;
}
bool	AlignmentProjectionThreshold::Save(QIODevice *file)
{
	int32	Ver=3;
	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,PeakCount)==false)
		return false;
	if(::Save(file,Angle)==false)
		return false;
	if(::Save(file,PeakIsolation)==false)
		return false;
	if(::Save(file,UsageLayer)==false)
		return false;
	if(::Save(file,AbandonRateL)==false)
		return false;
	if(::Save(file,AbandonRateH)==false)
		return false;
	return true;
}
bool	AlignmentProjectionThreshold::Load(QIODevice *file)
{
	int32	Ver;
	if(::Load(file,Ver)==false)
		return false;

	if(::Load(file,PeakCount)==false)
		return false;
	if(::Load(file,Angle)==false)
		return false;
	if(Ver>=3){
		if(::Load(file,PeakIsolation)==false)
			return false;
	}
	if(::Load(file,UsageLayer)==false)
		return false;
	if(Ver>=2){
		if(::Load(file,AbandonRateL)==false)
			return false;
		if(::Load(file,AbandonRateH)==false)
			return false;
	}
	return true;
}

//---------------------------------------------------------------------------------------


AlignmentProjectionItem::AlignmentProjectionItem(void)
{
    ResultDx	=0;
    ResultDy	=0;
	MapPixelsCount	=NULL;
	MasterMapDim	=NULL;
	TargetMapDim	=NULL;
	MapDimCount	=0;
	MasterPeak	=NULL;
	TargetPeak	=NULL;
}

AlignmentProjectionItem::~AlignmentProjectionItem(void)
{
	if(MapPixelsCount!=NULL){
		delete	[]MapPixelsCount;
	}
	if(MasterMapDim!=NULL){
		delete	[]MasterMapDim;
	}
	if(TargetMapDim!=NULL){
		delete	[]TargetMapDim;
	}
	if(MasterPeak!=NULL){
		delete	[]MasterPeak;
	}
	if(TargetPeak!=NULL){
		delete	[]TargetPeak;
	}
	MapPixelsCount	=NULL;
	MasterMapDim	=NULL;
	TargetMapDim	=NULL;
	MapDimCount	=0;
	MasterPeak	=NULL;
	TargetPeak	=NULL;

}

void	AlignmentProjectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentProjectionDrawAttr	*a=dynamic_cast<AlignmentProjectionDrawAttr *>(Attr);
	if(a!=NULL){
		QRgb	TransCol=qRgba(180,220,0,128);
		if(GetActive()==true){
			GetArea().Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
		}
		else if(GetSelected()==true){
			GetArea().Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
		}
		else{
			QColor	NCol=Attr->NormalColor.rgba();
			NCol.setAlpha(((AlignmentProjectionBase *)GetParentBase())->AlphaLevel);
			GetArea().Draw(0,0 ,&pnt ,NCol.rgba()	,ZoomRate ,movx ,movy);
		}
	}
	else{
		GetArea().Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
	}

	AlignmentProjectionBase	*ABase=(AlignmentProjectionBase *)GetParentBase();
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();

	if(MasterPeak!=NULL && (ABase->DrawOnlyTopPage==false || (ABase->DrawOnlyTopPage==true && GetLayersBase()->GetDrawturn(0)->GetPage()==GetPage()))){
		QPainter	PData(&pnt);
		PData.setPen(Qt::green);
		for(int i=0;i<RThr->PeakCount;i++){
			double	t=MasterPeak[i];
			int	px=MasterCx+t*SCos;
			int	py=MasterCy+t*SSin;
			double	m1;
			double	m2;
			if(fabs(SSin)>fabs(SCos)){
				m1=px/SSin;
				m2=(px-GetDotPerLine())/SSin;
			}
			else{
				m1=-py/SCos;
				m2=-(py-GetMaxLines())/SCos;
			}
			int	X1,Y1;
			int	X2,Y2;
			int	Lm=min(m1,m2);
			int	Hm=max(m1,m2);
			for(int m=Lm;m<=Hm;m++){
				int	X=px-m*SSin;
				int	Y=py+m*SCos;
				if(GetArea().IsInclude(X,Y)==true){
					X1=X;
					Y1=Y;
					break;
				}
			}
			for(int m=Hm;m>=Lm;m--){
				int	X=px-m*SSin;
				int	Y=py+m*SCos;
				if(GetArea().IsInclude(X,Y)==true){
					X2=X;
					Y2=Y;
					break;
				}
			}

			int	x1=(X1+movx)*ZoomRate;
			int	y1=(Y1+movy)*ZoomRate;
			int	x2=(X2+movx)*ZoomRate;
			int	y2=(Y2+movy)*ZoomRate;
			PData.drawLine(x1,y1,x2,y2);
		}
	}
}

void	AlignmentProjectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	int	cx,cy;
	GetArea().GetCenter(cx,cy);

	QColor	c=Qt::green;
	c.setAlpha(100);

	GetArea().Draw(0,0,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);

	AlignmentProjectionBase	*ABase=(AlignmentProjectionBase *)GetParentBase();
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	if(MasterPeak!=NULL && TargetPeak!=NULL
	&& (ABase->DrawOnlyTopPage==false || (ABase->DrawOnlyTopPage==true && GetLayersBase()->GetDrawturn(0)->GetPage()==GetPage()))){
		PData.setPen(Qt::green);
		for(int i=0;i<RThr->PeakCount;i++){
			double	t=MasterPeak[i];
			int	px=MasterCx+t*SCos;
			int	py=MasterCy+t*SSin;
			double	m1;
			double	m2;
			if(fabs(SSin)>fabs(SCos)){
				m1=px/SSin;
				m2=(px-GetDotPerLine())/SSin;
			}
			else{
				m1=-py/SCos;
				m2=-(py-GetMaxLines())/SCos;
			}
			int	X1,Y1;
			int	X2,Y2;
			int	Lm=min(m1,m2);
			int	Hm=max(m1,m2);
			for(int m=Lm;m<=Hm;m++){
				int	X=px-m*SSin;
				int	Y=py+m*SCos;
				if(GetArea().IsInclude(X,Y)==true){
					X1=X;
					Y1=Y;
					break;
				}
			}
			for(int m=Hm;m>=Lm;m--){
				int	X=px-m*SSin;
				int	Y=py+m*SCos;
				if(GetArea().IsInclude(X,Y)==true){
					X2=X;
					Y2=Y;
					break;
				}
			}

			int	x1=(X1+MovX)*ZoomRate;
			int	y1=(Y1+MovY)*ZoomRate;
			int	x2=(X2+MovX)*ZoomRate;
			int	y2=(Y2+MovY)*ZoomRate;
			PData.drawLine(x1,y1,x2,y2);
		}
		PData.setPen(Qt::magenta);
		for(int i=0;i<RThr->PeakCount;i++){
			double	t=TargetPeak[i];
			int	px=MasterCx+t*SCos;
			int	py=MasterCy+t*SSin;
			double	m1;
			double	m2;
			if(fabs(SSin)>fabs(SCos)){
				m1=px/SSin;
				m2=(px-GetDotPerLine())/SSin;
			}
			else{
				m1=-py/SCos;
				m2=-(py-GetMaxLines())/SCos;
			}
			int	X1,Y1;
			int	X2,Y2;
			int	Lm=min(m1,m2);
			int	Hm=max(m1,m2);
			for(int m=Lm;m<=Hm;m++){
				int	X=px-m*SSin;
				int	Y=py+m*SCos;
				if(GetArea().IsInclude(X,Y)==true){
					X1=X;
					Y1=Y;
					break;
				}
			}
			for(int m=Hm;m>=Lm;m--){
				int	X=px-m*SSin;
				int	Y=py+m*SCos;
				if(GetArea().IsInclude(X,Y)==true){
					X2=X;
					Y2=Y;
					break;
				}
			}

			int	x1=(X1+MovX)*ZoomRate;
			int	y1=(Y1+MovY)*ZoomRate;
			int	x2=(X2+MovX)*ZoomRate;
			int	y2=(Y2+MovY)*ZoomRate;
			PData.drawLine(x1,y1,x2,y2);
		}
	}
}

void	AlignmentProjectionItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	AlignmentProjectionItem	*ASrc=dynamic_cast<AlignmentProjectionItem *>(src);
	if(ASrc!=NULL){
		ResultDx	=ASrc->ResultDx;
	    ResultDy	=ASrc->ResultDy;
	}
}


AlgorithmItemPI	&AlignmentProjectionItem::operator=(const AlgorithmItemRoot &src)
{
	const	AlignmentProjectionItem	*s=dynamic_cast<const AlignmentProjectionItem *>(&src);
	if(s!=NULL){
		return operator=(*s);
	}
	return *this;
}


AlignmentProjectionItem   &AlignmentProjectionItem::operator=(AlignmentProjectionItem &src)
{
	AlgorithmItemPI::operator=(*((AlgorithmItemPI *)&src));

	SetArea		(src.GetArea());
    ResultDx	=src.ResultDx;
    ResultDy	=src.ResultDy;

	SCos		=src.SCos		;
	SSin		=src.SSin		;
	MasterCx	=src.MasterCx	;
	MasterCy	=src.MasterCy	;
	LMinD		=src.LMinD		;
	LMaxD		=src.LMaxD		;
	MapDimCount	=src.MapDimCount	;

	if(MapPixelsCount!=NULL){
		delete	[]MapPixelsCount;
		MapPixelsCount=NULL;
	}
	if(src.MapPixelsCount!=NULL){
		MapPixelsCount	=new int[MapDimCount];
		for(int i=0;i<MapDimCount;i++){
			MapPixelsCount[i]=src.MapPixelsCount[i];
		}
	}

	if(MasterMapDim!=NULL){
		delete	[]MasterMapDim;
		MasterMapDim=NULL;
	}
	if(src.MasterMapDim!=NULL){
		MasterMapDim	=new double[MapDimCount];
		for(int i=0;i<MapDimCount;i++){
			MasterMapDim[i]=src.MasterMapDim[i];
		}
	}

	if(TargetMapDim!=NULL){
		delete	[]TargetMapDim;
		TargetMapDim=NULL;
	}
	if(src.TargetMapDim!=NULL){
		TargetMapDim	=new double[MapDimCount];
		for(int i=0;i<MapDimCount;i++){
			TargetMapDim[i]=src.TargetMapDim[i];
		}
	}

	if(MasterPeak!=NULL){
		delete	[]MasterPeak;
		MasterPeak=NULL;
	}
	const	AlignmentProjectionThreshold	*RThr=src.GetThresholdR();
	if(src.MasterPeak!=NULL){
		MasterPeak	=new double[RThr->PeakCount];
		for(int i=0;i<RThr->PeakCount;i++){
			MasterPeak[i]=src.MasterPeak[i];
		}
	}

	if(TargetPeak!=NULL){
		delete	[]TargetPeak;
		TargetPeak=NULL;
	}
	if(src.TargetPeak!=NULL){
		TargetPeak	=new double[RThr->PeakCount];
		for(int i=0;i<RThr->PeakCount;i++){
			TargetPeak[i]=src.TargetPeak[i];
		}
	}
	return(*this);
}

void    AlignmentProjectionItem::MoveTo(int dx ,int dy)
{
	GetArea()	.MoveToNoClip(dx,dy);
	MasterCx+=dx;
	MasterCy+=dy;
}

ImageBuffer	&AlignmentProjectionItem::GetMasterBuffForMakeArea(void)
{
	DataInLayer	*Dy=GetDataInLayer();
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	if(GetParamGlobal()->AllocBitBuffer==true && ((AlignmentProjectionBase *)GetParentBase())->UseBitBuff==true && Dy->HasDataInBitBuff()==true){
		ImagePointerContainer ImageList;
		GetBitBuffList(ImageList);
		ImageBuffer	*Ret=ImageList[RThr->UsageLayer];
		if(Ret->IsNull()==false)
			return *Ret;
	}
	ImagePointerContainer ImageList;
	GetMasterBuffList(ImageList);
	return *ImageList[RThr->UsageLayer];
}

void    AlignmentProjectionItem::Clear(void)
{
    ResultDx=0;
    ResultDy=0;
}
bool    AlignmentProjectionItem::Save(QIODevice *file)
{
	WORD	Ver=2;
	if(AlgorithmItemPI::Save(file)==false)
		return(false);

	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,SCos		)==false)
		return false;
	if(::Save(file,SSin		)==false)
		return false;
	if(::Save(file,MasterCx	)==false)
		return false;
	if(::Save(file,MasterCy	)==false)
		return false;
	if(::Save(file,LMinD	)==false)
		return false;	
	if(::Save(file,LMaxD	)==false)
		return false;	
	if(::Save(file,MapDimCount	)==false)
		return false;

	if(MapDimCount!=0){
		if(file->write((const char *)MapPixelsCount,sizeof(int)*MapDimCount)!=sizeof(int)*MapDimCount)
			return false;
		if(file->write((const char *)MasterMapDim,sizeof(double)*MapDimCount)!=sizeof(double)*MapDimCount)
			return false;
		if(file->write((const char *)TargetMapDim,sizeof(double)*MapDimCount)!=sizeof(double)*MapDimCount)
			return false;
		if(file->write((const char *)MasterPeak,sizeof(double)*GetThresholdR()->PeakCount)!=sizeof(double)*GetThresholdR()->PeakCount)
			return false;
		if(file->write((const char *)TargetPeak,sizeof(double)*GetThresholdR()->PeakCount)!=sizeof(double)*GetThresholdR()->PeakCount)
			return false;
	}
	return(true);
}
bool    AlignmentProjectionItem::Load(QIODevice *file,LayersBase *LBase)
{
	WORD	Ver;

	if(AlgorithmItemPI::Load(file,LBase)==false)
		return(false);

	if(::Load(file,Ver)==false)
		return false;
	if(Ver>=2){
		if(::Load(file,SCos		)==false)
			return false;
		if(::Load(file,SSin		)==false)
			return false;
		if(::Load(file,MasterCx	)==false)
			return false;
		if(::Load(file,MasterCy	)==false)
			return false;
		if(::Load(file,LMinD	)==false)
			return false;	
		if(::Load(file,LMaxD	)==false)
			return false;	
		if(::Load(file,MapDimCount	)==false)
			return false;

		if(MapPixelsCount!=NULL){
			delete	[]MapPixelsCount;
			MapPixelsCount=NULL;
		}
		if(MasterMapDim!=NULL){
			delete	[]MasterMapDim;
			MasterMapDim=NULL;
		}
		if(TargetMapDim!=NULL){
			delete	[]TargetMapDim;
			TargetMapDim=NULL;
		}
		if(MasterPeak!=NULL){
			delete	[]MasterPeak;
			MasterPeak=NULL;
		}
		if(TargetPeak!=NULL){
			delete	[]TargetPeak;
			TargetPeak=NULL;
		}
		if(MapDimCount!=0){
			MapPixelsCount=new int[MapDimCount];
			MasterMapDim=new double[MapDimCount];
			TargetMapDim=new double[MapDimCount];
			const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
			MasterPeak	=new double[RThr->PeakCount];
			TargetPeak	=new double[RThr->PeakCount];

			if(file->read((char *)MapPixelsCount,sizeof(int)*MapDimCount)!=sizeof(int)*MapDimCount)
				return false;
			if(file->read((char *)MasterMapDim,sizeof(double)*MapDimCount)!=sizeof(double)*MapDimCount)
				return false;
			if(file->read((char *)TargetMapDim,sizeof(double)*MapDimCount)!=sizeof(double)*MapDimCount)
				return false;
			if(file->read((char *)MasterPeak,sizeof(double)*RThr->PeakCount)!=sizeof(double)*RThr->PeakCount)
				return false;
			if(file->read((char *)TargetPeak,sizeof(double)*RThr->PeakCount)!=sizeof(double)*RThr->PeakCount)
				return false;
		}
	}
	return(true);
}


double    AlignmentProjectionItem::GetLinePointFoot(double Cx,double Cy ,double px ,double py ,double &X ,double &Y)


/*      点から下ろした直線への足の座標を求める

	直線	SSin*(x-Cx)-SCos*(y-Cy)=0
	(px ,py)に点座標        を入れる

	(X ,Y) に足の座標を入れる
*/
{
	double	t=(px-Cx)*SCos+(py-Cy)*SSin;

	X=t*SCos+Cx;
	Y=t*SSin+Cy;

	return t;
}

ExeResult	AlignmentProjectionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	SCos	=cos(RThr->Angle*2*M_PI/360.0);
	SSin	=sin(RThr->Angle*2*M_PI/360.0);

	if(MapPixelsCount!=NULL){
		delete	[]MapPixelsCount;
	}
	if(MasterMapDim!=NULL){
		delete	[]MasterMapDim;
	}
	if(TargetMapDim!=NULL){
		delete	[]TargetMapDim;
	}
	GetArea().GetCenter(MasterCx,MasterCy);	//(Cx,Cy)を通る傾きAngleの直線	SSin*(x-Cx)-SCos*(y-Cy)=0
	double	MinD=99999999;
	double	MaxD=-99999999;
	int	N=GetArea().GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y=GetArea().GetFLineAbsY(i);
		int	X1=GetArea().GetFLineLeftX(i);
		int	X2=GetArea().GetFLineRightX(i);
		for(int X=X1;X<X2;X++){
			double mX ,mY;
			double	t=GetLinePointFoot(MasterCx,MasterCy ,X ,Y ,mX ,mY);
			if(t<MinD){
				MinD=t;
			}
			if(MaxD<t){
				MaxD=t;
			}
		}
	}
	LMinD=floor(MinD);
	LMaxD=ceil(MaxD);

	MapDimCount	=LMaxD-LMinD;

	MapPixelsCount	=new int	[MapDimCount];
	MasterMapDim	=new double[MapDimCount];
	TargetMapDim	=new double[MapDimCount];

	if(MasterPeak!=NULL){
		delete	[]MasterPeak;
	}
	if(TargetPeak!=NULL){
		delete	[]TargetPeak;
	}

	MasterPeak=new double[RThr->PeakCount];
	TargetPeak=new double[RThr->PeakCount];

	for(int i=0;i<MapDimCount;i++){
		MasterMapDim[i]=0.0;
		TargetMapDim[i]=0.0;
		MapPixelsCount[i]=0;
	}
	for(int i=0;i<RThr->PeakCount;i++){
		MasterPeak[i]=0;
		TargetPeak[i]=0;
	}
	ImagePointerContainer ImageList;
	GetMasterBuffList	(ImageList);
	ImageBuffer	*MasterImage=ImageList[RThr->UsageLayer];

	MakeMapPeak(*MasterImage ,MasterMapDim ,MasterPeak);


	return Ret;
}

void	AlignmentProjectionItem::MakeMapPeak(ImageBuffer &IBuff ,double *MapDim ,double *Peak)
{
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	for(int i=0;i<MapDimCount;i++){
		MapPixelsCount[i]=0;
	}
	int	N=GetArea().GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y=GetArea().GetFLineAbsY(i);
		int	X1=GetArea().GetFLineLeftX(i);
		int	X2=GetArea().GetFLineRightX(i);
		for(int X=X1;X<X2;X++){
			double mX ,mY;
			double	t=GetLinePointFoot(MasterCx,MasterCy ,X ,Y ,mX ,mY);
			int	d=t-LMinD;
			if(0<=d && d<MapDimCount){
				MapPixelsCount[d]++;
				MapDim[d]+=IBuff.GetY(Y)[X];
			}
		}
	}
	for(int i=0;i<MapDimCount;i++){
		if(MapPixelsCount[i]!=0){
			MapDim[i]=MapDim[i]/MapPixelsCount[i];
		}
	}
	double	LastCenter=MapDim[0];
	for(int i=1;i<MapDimCount-1;i++){
		double	CCenter=MapDim[i];
		MapDim[i]=(LastCenter+CCenter+MapDim[i+1])/3.0;
		LastCenter=CCenter;
	}

	int	BTable[256];
	for(int i=0;i<256;i++){
		BTable[i]=0;
	}
	for(int i=0;i<MapDimCount;i++){
		int	n=MapDim[i];
		BTable[n]++;
	}
	int	LCount=MapDimCount*RThr->AbandonRateL;
	int	HCount=MapDimCount*RThr->AbandonRateH;
	int	LLevel;
	int	HLevel;
	int	n=0;
	for(LLevel=0;LLevel<256;LLevel++){
		if(n+BTable[LLevel]>LCount){
			break;
		}
		n+=BTable[LLevel];
	}
	n=0;
	for(HLevel=255;HLevel>=0;HLevel--){
		if(n+BTable[HLevel]>HCount){
			break;
		}
		n+=BTable[HLevel];
	}
	LLevel--;
	HLevel+=2;

	bool	EnabledDim[10000];
	for(int i=0;i<MapDimCount;i++){
		EnabledDim[i]=true;
	}
	for(int	PeakN=0;PeakN<RThr->PeakCount;PeakN++){
		double	TopP=-99999999;
		int		Index=-1;
		for(int i=1;i<MapDimCount-1;i++){
			bool	FlagNear=false;
			for(int LastPeak=0;LastPeak<PeakN;LastPeak++){
				int	p=Peak[LastPeak]-LMinD;
				int	D=p-i;
				if(abs(D)<RThr->PeakIsolation){
					FlagNear=true;
					break;
				}
			}
			if(FlagNear==false){
				if(EnabledDim[i]==true){
					if(MapDim[i]>TopP){
						TopP=MapDim[i];
						Index=i;
					}
				}
			}
		}
		Peak[PeakN]=Index+LMinD;
		int	iL;
		for(iL=Index;iL>=0 && iL>=Index-4;iL--){
			EnabledDim[iL]=false;
		}
		for(;iL>=0 && MapDim[iL]>HLevel;iL--){
			EnabledDim[iL]=false;
		}

		int	iH;
		for(iH=Index+1;iH<MapDimCount && iH<=Index+4;iH++){
			EnabledDim[iH]=false;
		}
		for(;iH<MapDimCount && MapDim[iH]>HLevel;iH++){
			EnabledDim[iH]=false;
		}
	}
}


ExeResult	AlignmentProjectionItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	for(int i=0;i<MapDimCount;i++){
		TargetMapDim[i]=0.0;
		MapPixelsCount[i]=0;
	}
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	for(int i=0;i<RThr->PeakCount;i++){
		TargetPeak[i]=0;
	}

	ResetProcessDone();
	return _ER_true;
}

ExeResult	AlignmentProjectionItem::ExecuteAlignment	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList	(ImageList);
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	ImageBuffer	*TargetImage=ImageList[RThr->UsageLayer];
	MakeMapPeak(*TargetImage ,TargetMapDim ,TargetPeak);
	SetProcessDone();
	return _ER_true;
}

void	AlignmentProjectionItem::CopyThresholdOnly(AlignmentProjectionItem *src)
{
	const	AlignmentProjectionThreshold	*RThr=src->GetThresholdR(GetLayersBase());
	GetThresholdW()->PeakCount		=RThr->PeakCount	;
	GetThresholdW()->Angle			=RThr->Angle		;
	GetThresholdW()->PeakIsolation	=RThr->PeakIsolation;
	GetThresholdW()->UsageLayer		=RThr->UsageLayer	;
	GetThresholdW()->AbandonRateL	=RThr->AbandonRateL	;
	GetThresholdW()->AbandonRateH	=RThr->AbandonRateH	;
}

void	AlignmentProjectionItem::GetAlignmentProjection(AlignmentPacket2D &AData)
{
	const	AlignmentProjectionThreshold	*RThr=GetThresholdR();
	if(RThr->PeakCount==1){
		double	D=TargetPeak[0]-MasterPeak[0];
		AData.ShiftX=D*SCos;
		AData.ShiftY=D*SSin;
	}
	else
	if(RThr->PeakCount==2 && fabs(MasterPeak[1]-MasterPeak[0])>0){
		
		int	x1=MasterCx+(MasterPeak[0]+LMinD)*SCos;
		int	y1=MasterCy+(MasterPeak[0]+LMinD)*SSin;
		int	x2=MasterCx+(MasterPeak[1]+LMinD)*SCos;
		int	y2=MasterCy+(MasterPeak[1]+LMinD)*SSin;
		
		int	X1=MasterCx+(TargetPeak[0]+LMinD)*SCos;
		int	Y1=MasterCy+(TargetPeak[0]+LMinD)*SSin;
		int	X2=MasterCx+(TargetPeak[1]+LMinD)*SCos;
		int	Y2=MasterCy+(TargetPeak[1]+LMinD)*SSin;

		double	dx=(X2+X1)/2 - (x2+x1)/2;
		double	dy=(Y2+Y1)/2 - (y2+y1)/2;
		double	Z=fabs((TargetPeak[1]-TargetPeak[0])/(MasterPeak[1]-MasterPeak[0]));

		double mX ,mY;
		double    t=GetLinePointFoot(MasterCx,MasterCy,AData.PosXOnTarget,AData.PosYOnTarget,mX,mY);
		double	t2=t*(1.0-Z);
		AData.ShiftX=dx+t2*SCos;
		AData.ShiftY=dy+t2*SSin;
	}
}

void	AlignmentProjectionItem::GetAlignmentByHandle(AlignmentPacket2D &AData ,void *Handle)
{
	GetAlignmentProjection(AData);
}

void	AlignmentProjectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			AlignmentProjectionInPage	*Pg=dynamic_cast<AlignmentProjectionInPage *>(GetParentInPage());
			UndoElement<AlignmentProjectionInPage>	*UPointer=new UndoElement<AlignmentProjectionInPage>(Pg,&AlignmentProjectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AlignmentProjectionItem *src=(AlignmentProjectionItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AlignmentProjectionItem *)Data)->GetLibID()){
			AlignmentProjectionInPage	*Pg=dynamic_cast<AlignmentProjectionInPage *>(GetParentInPage());
			UndoElement<AlignmentProjectionInPage>	*UPointer=new UndoElement<AlignmentProjectionInPage>(Pg,&AlignmentProjectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			AlignmentProjectionItem *src=(AlignmentProjectionItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
}
