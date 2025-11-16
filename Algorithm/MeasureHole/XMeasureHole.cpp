/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureHole\XMeasureHole.cpp
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
#include "XMeasureHole.h"
#include "omp.h"

MeasureHoleLibrary::MeasureHoleLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	MinDiameter=0;		//micron size
	MaxDiameter=10000;	//micron size
	NoiseSize=2;
	SearchDot=10;
}

MeasureHoleLibrary::~MeasureHoleLibrary(void)
{
}

bool	MeasureHoleLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(CupperColor.Save(f)==false)
		return false;
	if(::Save(f,MinDiameter)==false)
		return(false);
	if(::Save(f,MaxDiameter)==false)
		return(false);
	if(::Save(f,NoiseSize)==false)
		return(false);
	if(::Save(f,SearchDot)==false)
		return(false);

	return true;
}
bool	MeasureHoleLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(CupperColor.Load(f)==false)
		return false;
	if(::Load(f,MinDiameter)==false)
		return(false);
	if(::Load(f,MaxDiameter)==false)
		return(false);
	if(::Load(f,NoiseSize)==false)
		return(false);
	if(::Load(f,SearchDot)==false)
		return(false);

	return true;
}

MeasureHoleLibrary	&MeasureHoleLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((MeasureHoleLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================

MeasureHoleLibraryContainer::MeasureHoleLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

MeasureHoleLibraryContainer::~MeasureHoleLibraryContainer(void)
{
}

//==============================================================================
MeasureHoleThreshold::MeasureHoleThreshold(MeasureHoleItem *parent)
:AlgorithmThreshold(parent)
{
	MinDiameter=0;
	MaxDiameter=10000;
	NoiseSize=2;
	SearchDot=10;
}

void	MeasureHoleThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MeasureHoleThreshold *s=(const MeasureHoleThreshold *)&src;
    CupperColor	=s->CupperColor;
	MinDiameter	=s->MinDiameter;
	MaxDiameter	=s->MaxDiameter;
	NoiseSize	=s->NoiseSize;
	SearchDot	=s->SearchDot;
}
bool	MeasureHoleThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MeasureHoleThreshold *s=(const MeasureHoleThreshold *)&src;
    if(CupperColor	!=s->CupperColor)	return false;
	if(MinDiameter	!=s->MinDiameter)	return false;
	if(MaxDiameter	!=s->MaxDiameter)	return false;
	if(NoiseSize	!=s->NoiseSize)	return false;
	if(SearchDot	!=s->SearchDot)	return false;
	return true;
}
bool	MeasureHoleThreshold::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(CupperColor.Save(f)==false)
		return false;
	if(::Save(f,MinDiameter)==false)
		return(false);
	if(::Save(f,MaxDiameter)==false)
		return(false);
	if(::Save(f,NoiseSize)==false)
		return(false);
	if(::Save(f,SearchDot)==false)
		return(false);

	return(true);
}
bool	MeasureHoleThreshold::Load(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(CupperColor.Load(f)==false)
		return false;
	if(::Load(f,MinDiameter)==false)
		return(false);
	if(::Load(f,MaxDiameter)==false)
		return(false);
	if(::Load(f,NoiseSize)==false)
		return(false);
	if(::Load(f,SearchDot)==false)
		return(false);
	
	return(true);
}

EllipseXYList::EllipseXYList(void)
{
	Cx=0;
	Cy=0;
	RadiusX=0;
	RadiusY=0;
}

bool	EllipseXYList::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,RadiusX)==false)
		return false;
	if(::Save(f,RadiusY)==false)
		return false;
	return true;
}
bool	EllipseXYList::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,RadiusX)==false)
		return false;
	if(::Load(f,RadiusY)==false)
		return false;
	return true;
}

bool	ResultMeasureHoleOnItem::Save(QIODevice *f)
{
	int32	N=List.GetNumber();

	if(::Load(f,N)==false)
		return false;
	for(EllipseXYList *L=List.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false)
			return false;
	}
	return true;
}
bool	ResultMeasureHoleOnItem::Load(QIODevice *f)
{
	int32	N;

	List.RemoveAll();
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		EllipseXYList *L=new EllipseXYList();
		if(L->Load(f)==false)
			return false;
		List.AppendList(L);
	}
	return true;
}

AlgorithmItemPI	&MeasureHoleItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	return *this;
}

bool    MeasureHoleItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	return true;
}
bool    MeasureHoleItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	return true;
}

void	MeasureHoleItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
}
void	MeasureHoleItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->GetAddedData()!=NULL){
			PureFlexAreaList	*F=((ResultMeasureHoleOnItem *)Res->GetAddedData())->FPack.GetFirst();

			QRgb c=qRgba ( 200, 0, 200, 100);
			F->DrawAlpha(0 ,0 ,&IData ,c
						,ZoomRate ,MovX ,MovY);

			PData.setPen(Qt::red);
			PData.drawArc((Result.Cx-Result.RadiusX+MovX)*ZoomRate,(Result.Cy-Result.RadiusY+MovY)*ZoomRate
				,Result.RadiusX*2*ZoomRate,Result.RadiusY*2*ZoomRate
				,0,360*16-1);

			int	L=0;
			if(Res->GetError()==2)
				L=(Res->GetResult1()+Res->GetResult2())/2;
			else if(Res->GetError()==3)
				L=Res->GetResult1();
			else if(Res->GetError()==4)
				L=Res->GetResult2();

			if(L!=0){
				PData.drawText((Result.Cx+MovX)*ZoomRate,(Result.Cy+MovY)*ZoomRate,QString::number(L));
			}
		}
	}
}

ExeResult	MeasureHoleItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	return _ER_true;
}
ExeResult	MeasureHoleItem::ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	const MeasureHoleThreshold	*RThr=GetThresholdR();
	int	XLen=GetArea().GetWidth()+16+RThr->NoiseSize*4;
	int	YLen=GetArea().GetHeight()+8+RThr->NoiseSize*4;
	int	XTop=GetArea().GetMinX()-8	-RThr->NoiseSize*2;
	int	YTop=GetArea().GetMinY()-4	-RThr->NoiseSize*2;

	MeasureHoleBase	*BBase=(MeasureHoleBase *)GetParentBase();
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

	BYTE	**SBmp=MakeMatrixBuff(XByte,YLen);
	BYTE	**SBmp2=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(SBmp,0,XByte,YLen);

	ColorLogic	&CLogic=GetThresholdW()->CupperColor;
	ImageBuffer *ImageList[10];

	GetTargetBuffList(ImageList);

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
	//if(_CrtCheckMemory()==false)
	//	return false;
	MatrixBuffNot	(SBmp ,XByte ,YLen);
	//if(_CrtCheckMemory()==false)
	//	return false;

	GetLayersBase()->FatAreaN(SBmp
				,SBmp2
				,XByte, YLen
				,RThr->NoiseSize);
	GetLayersBase()->ThinAreaN(SBmp
				,SBmp2
				,XByte, YLen
				,RThr->NoiseSize*2);
	GetLayersBase()->FatAreaN(SBmp
				,SBmp2
				,XByte, YLen
				,RThr->NoiseSize);

	//if(_CrtCheckMemory()==false)
	//	return false;
	
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
	if(Res->GetAddedData()==NULL){
		Res->SetAddedData(new ResultMeasureHoleOnItem(),ResultMeasureHoleOnItemType);
	}
	else{
		Res->GetAddedData()->Clear();
	}
	Res->SetError(0);

	if(MaxF!=NULL){
		FPack.RemoveList(MaxF);
		double Cx ,Cy;
		MaxF->GetCenter(Cx ,Cy);
		Cx+=XTop;
		Cy+=YTop;
		double	Rx,Ry;
		Rx=Ry=sqrt(MaxN/M_PI);
		MaxF->MoveToNoClip(XTop,YTop);
		((ResultMeasureHoleOnItem *)Res->GetAddedData())->FPack.AppendList(MaxF);

		double	MaxK;
		double	iRx=0.0;
		double	iRy=0.0;
		double	iCx=0.0;
		double	iCy=0.0;

		int	S=RThr->SearchDot;
		if(S>=Rx*0.7)
			S=Rx*0.7-1;
		if(S>=Ry*0.7)
			S=Ry*0.7-1;

		if(S>=10){
			MaxK=0;
			for(int icy=-S;icy<=S;icy+=2){
				for(int icx=-S;icx<=S;icx+=2){
					for(int iry=-S;iry<=S;iry+=2){
						for(int irx=-S;irx<=S;irx+=2){
							double	K=GetDivSum(Cx+icx,Cy+icy,Rx+irx,Ry+iry,ImageList);
							if(K>MaxK){
								MaxK=K;
								iRx=irx;
								iRy=iry;
								iCx=icx;
								iCy=icy;
							}
						}
					}
				}
			}
			Cx+=iCx;
			Cy+=iCy;
			Rx+=iRx;
			Ry+=iRy;

			MaxK=0;
			for(double icy=-2;icy<=2;icy+=0.5){
				for(double icx=-2;icx<=2;icx+=0.5){
					for(double iry=-2;iry<=2;iry+=0.5){
						for(double irx=-1;irx<=1;irx+=0.5){
							double	K=GetDivSum(Cx+icx,Cy+icy,Rx+irx,Ry+iry,ImageList);
							if(K>MaxK){
								MaxK=K;
								iRx=irx;
								iRy=iry;
								iCx=icx;
								iCy=icy;
							}
						}
					}
				}
			}
			Cx+=iCx;
			Cy+=iCy;
			Rx+=iRx;
			Ry+=iRy;

			MaxK=0;
			for(double icy=-0.5;icy<=0.5;icy+=0.1){
				for(double icx=-0.5;icx<=0.5;icx+=0.1){
					for(double iry=-0.5;iry<=0.5;iry+=0.1){
						for(double irx=-1;irx<=1;irx+=0.1){
							double	K=GetDivSum(Cx+icx,Cy+icy,Rx+irx,Ry+iry,ImageList);
							if(K>MaxK){
								MaxK=K;
								iRx=irx;
								iRy=iry;
								iCx=icx;
								iCy=icy;
							}
						}
					}
				}
			}
			Cx+=iCx;
			Cy+=iCy;
			Rx+=iRx;
			Ry+=iRy;
		}
		else{
			MaxK=0;
			for(int icy=-S;icy<=S;icy++){
				for(int icx=-S;icx<=S;icx++){
					for(int iry=-S;iry<=S;iry++){
						for(int irx=-S;irx<=S;irx++){
							double	K=GetDivSum(Cx+icx,Cy+icy,Rx+irx,Ry+iry,ImageList);
							if(K>MaxK){
								MaxK=K;
								iRx=irx;
								iRy=iry;
								iCx=icx;
								iCy=icy;
							}
						}
					}
				}
			}
			Cx+=iCx;
			Cy+=iCy;
			Rx+=iRx;
			Ry+=iRy;

			MaxK=0;
			for(double icy=-1;icy<=1;icy+=0.2){
				for(double icx=-1;icx<=1;icx+=0.2){
					for(double iry=-1;iry<=1;iry+=0.2){
						for(double irx=-1;irx<=1;irx+=0.2){
							double	K=GetDivSum(Cx+icx,Cy+icy,Rx+irx,Ry+iry,ImageList);
							if(K>MaxK){
								MaxK=K;
								iRx=irx;
								iRy=iry;
								iCx=icx;
								iCy=icy;
							}
						}
					}
				}
			}
			Cx+=iCx;
			Cy+=iCy;
			Rx+=iRx;
			Ry+=iRy;

			MaxK=0;
			for(double icy=-0.2;icy<=0.2;icy+=0.1){
				for(double icx=-0.2;icx<=0.2;icx+=0.1){
					for(double iry=-0.2;iry<=0.2;iry+=0.1){
						for(double irx=-0.2;irx<=0.2;irx+=0.1){
							double	K=GetDivSum(Cx+icx,Cy+icy,Rx+irx,Ry+iry,ImageList);
							if(K>MaxK){
								MaxK=K;
								iRx=irx;
								iRy=iry;
								iCx=icx;
								iCy=icy;
							}
						}
					}
				}
			}
			Cx+=iCx;
			Cy+=iCy;
			Rx+=iRx;
			Ry+=iRy;
		}

		Result.Cx=Cx;
		Result.Cy=Cy;
		Result.RadiusX=Rx;
		Result.RadiusY=Ry;

		int W=(2.0*Rx*GetParamGlobal()->ResolutionXNano)/1000.0 *BBase->Gain+ BBase->Offset;
		int H=(2.0*Ry*GetParamGlobal()->ResolutionYNano)/1000.0 *BBase->Gain+ BBase->Offset;
		Res->SetResult1(W);
		Res->SetResult2(H);
		if((W<GetThresholdW()->MinDiameter || GetThresholdW()->MaxDiameter<W) && (H<GetThresholdW()->MinDiameter || GetThresholdW()->MaxDiameter<H)){
			Res->SetError(2);
		}
		else if(W<GetThresholdW()->MinDiameter || GetThresholdW()->MaxDiameter<W){
			Res->SetError(3);
		}
		else if(H<GetThresholdW()->MinDiameter || GetThresholdW()->MaxDiameter<H){
			Res->SetError(4);
		}
		else{
			Res->SetError(1);
		}
	}

	DeleteMatrixBuff(SBmp,YLen);
	DeleteMatrixBuff(SBmp2,YLen);

	return _ER_true;
}

double	MeasureHoleItem::GetDivSum(double Cx,double Cy,double Rx,double Ry
									,ImageBuffer *ImageList[])
{
	int	N=(Rx+Ry)/2;
	double	RetSum=0;
	if(N>36)
		N=36;
	if(N<8)
		N=8;
	for(int i=0;i<N;i++){
		double	s=2*M_PI/N*i;
		double	SinS=sin(s);
		double	CosS=cos(s);
		double	K=sqrt(Rx*Rx*SinS*SinS+Ry*Ry*CosS*CosS);
		double	Qx=Ry*CosS/K;
		double	Qy=Rx*SinS/K;

		double	Hx1=Cx+Rx*CosS+Qx*1.5;
		double	Hy1=Cy+Ry*SinS+Qy*1.5;
		double	Hx2=Cx+Rx*CosS-Qx*1.5;
		double	Hy2=Cy+Ry*SinS-Qy*1.5;

		double	R1=0.0,G1=0.0,B1=0.0;
		double	R2=0.0,G2=0.0,B2=0.0;

		int	iHx1=floor(Hx1);
		int	iHy1=floor(Hy1);
		double	fHx1=Hx1-iHx1;
		double	fHy1=Hy1-iHy1;

		double	L111=fHx1*fHx1+fHy1*fHy1;
		double	L101=(1-fHx1)*(1-fHx1)+fHy1*fHy1;
		double	L110=fHx1*fHx1+(1-fHy1)*(1-fHy1);
		double	L100=(1-fHx1)*(1-fHx1)+(1-fHy1)*(1-fHy1);

		double	LN1=L100+L101+L110+L111;

		int	iHx2=floor(Hx2);
		int	iHy2=floor(Hy2);
		double	fHx2=Hx2-iHx2;
		double	fHy2=Hy2-iHy2;

		double	L211=fHx2*fHx2+fHy2*fHy2;
		double	L201=(1-fHx2)*(1-fHx2)+fHy2*fHy2;
		double	L210=fHx2*fHx2+(1-fHy2)*(1-fHy2);
		double	L200=(1-fHx2)*(1-fHx2)+(1-fHy2)*(1-fHy2);

		double	LN2=L200+L201+L210+L211;

		if(GetLayerNumb()==1){
			BYTE	s100=*(ImageList[0]->GetY(iHy1)+iHx1);
			BYTE	s110=*(ImageList[0]->GetY(iHy1)+iHx1+1);
			BYTE	s101=*(ImageList[0]->GetY(iHy1+1)+iHx1);
			BYTE	s111=*(ImageList[0]->GetY(iHy1+1)+iHx1+1);

			R1=(s100*L100+s110*L110+s101*L101+s111*L111)/LN1;
			G1=B1=R1;

			BYTE	s200=*(ImageList[0]->GetY(iHy2)+iHx2);
			BYTE	s210=*(ImageList[0]->GetY(iHy2)+iHx2+1);
			BYTE	s201=*(ImageList[0]->GetY(iHy2+1)+iHx2);
			BYTE	s211=*(ImageList[0]->GetY(iHy2+1)+iHx2+1);

			R2=(s200*L200+s210*L210+s201*L201+s211*L211)/LN2;
			G2=B2=R2;
		}
		else if(GetLayerNumb()==2){
			BYTE	r100=*(ImageList[0]->GetY(iHy1)+iHx1);
			BYTE	r110=*(ImageList[0]->GetY(iHy1)+iHx1+1);
			BYTE	r101=*(ImageList[0]->GetY(iHy1+1)+iHx1);
			BYTE	r111=*(ImageList[0]->GetY(iHy1+1)+iHx1+1);
			R1=(r100*L100+r110*L110+r101*L101+r111*L111)/LN1;

			BYTE	g100=*(ImageList[1]->GetY(iHy1)+iHx1);
			BYTE	g110=*(ImageList[1]->GetY(iHy1)+iHx1+1);
			BYTE	g101=*(ImageList[1]->GetY(iHy1+1)+iHx1);
			BYTE	g111=*(ImageList[1]->GetY(iHy1+1)+iHx1+1);
			G1=(g100*L100+g110*L110+g101*L101+g111*L111)/LN1;
			B1=G1;

			BYTE	r200=*(ImageList[0]->GetY(iHy2)+iHx2);
			BYTE	r210=*(ImageList[0]->GetY(iHy2)+iHx2+1);
			BYTE	r201=*(ImageList[0]->GetY(iHy2+1)+iHx2);
			BYTE	r211=*(ImageList[0]->GetY(iHy2+1)+iHx2+1);
			R2=(r200*L200+r210*L210+r201*L201+r211*L211)/LN2;

			BYTE	g200=*(ImageList[1]->GetY(iHy2)+iHx2);
			BYTE	g210=*(ImageList[1]->GetY(iHy2)+iHx2+1);
			BYTE	g201=*(ImageList[1]->GetY(iHy2+1)+iHx2);
			BYTE	g211=*(ImageList[1]->GetY(iHy2+1)+iHx2+1);
			G2=(g200*L200+g210*L210+g201*L201+g211*L211)/LN2;
			B2=G2;
		}
		else if(GetLayerNumb()>=3){
			BYTE	r100=*(ImageList[0]->GetY(iHy1)+iHx1);
			BYTE	r110=*(ImageList[0]->GetY(iHy1)+iHx1+1);
			BYTE	r101=*(ImageList[0]->GetY(iHy1+1)+iHx1);
			BYTE	r111=*(ImageList[0]->GetY(iHy1+1)+iHx1+1);
			R1=(r100*L100+r110*L110+r101*L101+r111*L111)/LN1;

			BYTE	g100=*(ImageList[1]->GetY(iHy1)+iHx1);
			BYTE	g110=*(ImageList[1]->GetY(iHy1)+iHx1+1);
			BYTE	g101=*(ImageList[1]->GetY(iHy1+1)+iHx1);
			BYTE	g111=*(ImageList[1]->GetY(iHy1+1)+iHx1+1);
			G1=(g100*L100+g110*L110+g101*L101+g111*L111)/LN1;

			BYTE	b100=*(ImageList[2]->GetY(iHy1)+iHx1);
			BYTE	b110=*(ImageList[2]->GetY(iHy1)+iHx1+1);
			BYTE	b101=*(ImageList[2]->GetY(iHy1+1)+iHx1);
			BYTE	b111=*(ImageList[2]->GetY(iHy1+1)+iHx1+1);
			B1=(b100*L100+b110*L110+b101*L101+b111*L111)/LN1;

			BYTE	r200=*(ImageList[0]->GetY(iHy2)+iHx2);
			BYTE	r210=*(ImageList[0]->GetY(iHy2)+iHx2+1);
			BYTE	r201=*(ImageList[0]->GetY(iHy2+1)+iHx2);
			BYTE	r211=*(ImageList[0]->GetY(iHy2+1)+iHx2+1);
			R2=(r200*L200+r210*L210+r201*L201+r211*L211)/LN2;

			BYTE	g200=*(ImageList[1]->GetY(iHy2)+iHx2);
			BYTE	g210=*(ImageList[1]->GetY(iHy2)+iHx2+1);
			BYTE	g201=*(ImageList[1]->GetY(iHy2+1)+iHx2);
			BYTE	g211=*(ImageList[1]->GetY(iHy2+1)+iHx2+1);
			G2=(g200*L200+g210*L210+g201*L201+g211*L211)/LN2;

			BYTE	b200=*(ImageList[2]->GetY(iHy2)+iHx2);
			BYTE	b210=*(ImageList[2]->GetY(iHy2)+iHx2+1);
			BYTE	b201=*(ImageList[2]->GetY(iHy2+1)+iHx2);
			BYTE	b211=*(ImageList[2]->GetY(iHy2+1)+iHx2+1);
			B2=(b200*L200+b210*L210+b201*L201+b211*L211)/LN2;
		}
		
		RetSum+=(R1-R2)*(R1-R2)+(G1-G2)*(R1-R2)+(B1-B2)*(B1-B2);
	}
	return RetSum;
}

//===========================================

void	MeasureHoleInPage::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
}
void	MeasureHoleInPage::GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen)
{
}


void	MeasureHoleInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMeasureHoleAreaPacket	*AddMArea=dynamic_cast<AddMeasureHoleAreaPacket *>(packet);
	if(AddMArea!=NULL){
		MeasureHoleItem	*MData=(MeasureHoleItem *)CreateItem();
		MData->GetThresholdW()->CupperColor	=AddMArea->CupperColor;
		MData->SetArea(AddMArea->MaskArea);
		MData->SetManualCreated(true);
		AppendItem(MData);
	}
	/*
	CmdCreateMaskingPIBitmapWithLibPacket	*BmpWithLibPacket=dynamic_cast<CmdCreateMaskingPIBitmapWithLibPacket *>(packet);
	if(BmpWithLibPacket!=NULL){
		BYTE **Dst=MakeMatrixBuff(BmpWithLibPacket->XByte ,BmpWithLibPacket->YLen);
		GetItemBitmap(BmpWithLibPacket->LibType ,BmpWithLibPacket->LibID
					 ,Dst,BmpWithLibPacket->XByte<<3 ,BmpWithLibPacket->YLen);
		BmpWithLibPacket->BmpMap=Dst;
		return;
	}
	*/
}

//===========================================
MeasureHoleBase::MeasureHoleBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	Offset	=0;
	Gain	=1.0;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,"Color for Mask");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");

	SetParam(&Offset	, /**/"Seting" ,/**/"Offset"	,"Offset from measured diameter to result");
	SetParam(&Gain		, /**/"Seting" ,/**/"Gain"		,"Multplied-gain from measured diameter to result");
}

AlgorithmDrawAttr	*MeasureHoleBase::CreateDrawAttr(void)
{
	return new MeasureHoleDrawAttr();
}

void	MeasureHoleBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempMeasureHoleItemPacket	*CreateMeasureHoleItem=dynamic_cast<CmdCreateTempMeasureHoleItemPacket *>(packet);
	if(CreateMeasureHoleItem!=NULL){
		CreateMeasureHoleItem->Point=new MeasureHoleItem();
		return;
	}
	CmdCreateTempMeasureHoleLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempMeasureHoleLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdGetMeasureHoleLibraryListPacket	*AListPacket=dynamic_cast<CmdGetMeasureHoleLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdLoadMeasureHoleLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadMeasureHoleLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdAddByteMeasureHoleItemPacket	*AddBItem=dynamic_cast<CmdAddByteMeasureHoleItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			MeasureHoleItem	*Item=new MeasureHoleItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);
		}
	}
	CmdCreateByteArrayFromMeasureHoleItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromMeasureHoleItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdInsertMeasureHoleLibraryPacket	*BInsLib=dynamic_cast<CmdInsertMeasureHoleLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(MeasureHoleVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateMeasureHoleLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateMeasureHoleLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(MeasureHoleVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
}

//bool	MeasureHoleBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
//{
	/*
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(DForm);
	D.exec();
	if(DForm->RetOK==false)
		return false;
	DynamicMaskingPIItem	Item(NULL);
	Item.GetThresholdW()->Effective=DForm->Effective;
	Item.GetThresholdW()->SelAreaID=DForm->Libs.SelectedList;
	QBuffer	Buff(&templateData);
	Buff.open(QIODevice::ReadWrite);
	if(Item.Save(&Buff)==false)
		return false;
	*/
//	return true;
//}
