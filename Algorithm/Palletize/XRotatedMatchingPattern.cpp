/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Palletize\XPalletize.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPalletize.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XPalletizeLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//-----------------------------------------------------------------
MatchingLineBase::MatchingLineBase(void)
{
	PosX=PosY=0;
	LineLen=0;
	Data=NULL;
	A=AA=0;
	AvrS=0;
}
MatchingLineBase::~MatchingLineBase(void)
{
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=NULL;
	LineLen=0;
}

void	MatchingLineBase::Initial(void)
{
	A=AA=0;
	AASS=0;
	if(LineLen!=0){
		for(int n=0;n<LineLen;n++){
			int	a=Data[n];
			A+=a;
			AA+=a*a;
		}
		AvrS=((double)A)/(double)LineLen;

		AASS=AA-LineLen*AvrS*AvrS;
		RLineLen=1.0/((double)LineLen);
	}
}
bool	MatchingLineV::SetOnly(double cx, double cy ,double Len)
{
	if(cy-Len/2<0 || cx<0){
		return false;
	}
	PosX=cx;
	PosY=cy-Len/2;
	LineLen=Len;
	return true;
}
bool	MatchingLineV::Set(double cx, double cy ,double Len 
				,ImageBuffer &SourcePattern)
{
	if(cy-Len/2<0 || cx<0){
		return false;
	}
	PosX=cx;
	PosY=cy-Len/2;

	LineLen=Len;
	if(PosY+LineLen>=SourcePattern.GetHeight() || PosX>=SourcePattern.GetWidth())
		return false;

	if(Data!=NULL){
		delete	[]Data;
	}
	Data=new BYTE[LineLen];
	for(int n=0;n<LineLen;n++){
		int	b=SourcePattern.GetYWithoutDepended(PosY+n)[PosX];
		Data[n]=b;
	}
	Initial();
	return true;
}
void	MatchingLineV::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	Pnt.drawLine((PosX+movx)*ZoomRate ,(PosY+movy)*ZoomRate
			    ,(PosX+movx)*ZoomRate ,(PosY+LineLen+movy)*ZoomRate);
}

double	MatchingLineV::GetVar(ImageBuffer &Buff)
{
	double	B,BB;
	B=BB=0.0;
	if(LineLen!=0){
		for(int n=0;n<LineLen;n++){
			int	b=Buff.GetYWithoutDepended(PosY+n)[PosX];
			B+=b;
			BB+=b*b;
		}
		double	AvrB=((double)B)/(double)LineLen;
		double	D=(BB-LineLen*AvrB*AvrB)/LineLen;
		if(D<0){
			return 0;
		}
		return sqrt(D);
	}
	return 0;
}
bool	MatchingLineH::SetOnly(double cx, double cy ,double Len)
{
	if(cx-Len/2<0 || cy<0){
		return false;
	}
	PosX=cx-Len/2;
	PosY=cy;
	LineLen=Len;
	return true;
}
bool	MatchingLineH::Set(double cx, double cy ,double Len 
				,ImageBuffer &SourcePattern)
{
	if(cx-Len/2<0 || cy<0){
		return false;
	}
	PosX=cx-Len/2;
	PosY=cy;

	LineLen=Len;
	if(PosY>=SourcePattern.GetHeight() || PosX+LineLen>=SourcePattern.GetWidth())
		return false;

	if(Data!=NULL){
		delete	[]Data;
	}
	Data=new BYTE[LineLen];
	BYTE	*s=SourcePattern.GetYWithoutDepended(PosY);
	for(int n=0;n<LineLen;n++){
		int	b=s[PosX+n];
		Data[n]=b;
	}
	Initial();
	return true;
}
void	MatchingLineH::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	Pnt.drawLine((PosX+movx)*ZoomRate ,(PosY+movy)*ZoomRate
			    ,(PosX+LineLen+movx)*ZoomRate ,(PosY+movy)*ZoomRate);
}
double	MatchingLineH::GetVar(ImageBuffer &Buff)
{
	double	B,BB;
	B=BB=0.0;
	if(LineLen!=0){
		BYTE	*s=Buff.GetYWithoutDepended(PosY);
		for(int n=0;n<LineLen;n++){
			int	b=s[PosX+n];
			B+=b;
			BB+=b*b;
		}
		double	AvrB=((double)B)/(double)LineLen;
		double	D=(BB-LineLen*AvrB*AvrB)/LineLen;
		if(D<0){
			return 0;
		}
		return sqrt(D);
	}
	return 0;
}

//-----------------------------------------------------------------

void	CoeffLine::Initial(RotatedMatchingPattern *p ,ImageBuffer &IBuff)
{
	Parent=p;
	double	PickupLineVar=Parent->Parent->tGetParentBase()->PickupLineVar;
	int	Len=8;
	int	XDivCount=2;
	int	YDivCount=2;
	int	DivX=GetWidth() /XDivCount;
	int	DivY=GetHeight()/YDivCount;
	if(DivX<Len){
		XDivCount=2;
		DivX=GetWidth() /XDivCount;
		if(DivX<Len){
			XDivCount=1;
			DivX=GetWidth() /XDivCount;
		}
	}
	if(DivY<Len){
		YDivCount=2;
		DivY=GetHeight() /YDivCount;
		if(DivY<Len){
			YDivCount=1;
			DivY=GetHeight() /YDivCount;
		}
	}
	int	tMinX=GetMinX();
	int	tMinY=GetMinY();
	int	Len2=(Len+1)/2;
	for(int xn=0;xn<XDivCount;xn++){
		for(int yn=0;yn<YDivCount;yn++){
			int	x1=xn*DivX+tMinX;
			int	y1=yn*DivY+tMinY;
			int	x2=(xn+1)*DivX+tMinX;
			int	y2=(yn+1)*DivY+tMinY;
			{
				MatchingLineH	*H=new MatchingLineH();
				int	MaxY=-1;
				int	MaxCx=-1;
				double	MaxV=0;
				for(int y=y1;y<y2;y++){
					for(int cx=x1+Len2;cx<x2-Len2;cx++){
						if(IsInclude(cx-Len2-2,y-2)==true && IsInclude(cx+Len2+2,y-2)==true
						&& IsInclude(cx-Len2-2,y+2)==true && IsInclude(cx+Len2+2,y+2)==true){
							H->SetOnly(cx, y ,Len);
							double	D=H->GetVar(IBuff);
							if(D>MaxV){
								MaxV=D;
								MaxY=y;
								MaxCx=cx;
							}
						}
					}
				}
				if(MaxV>PickupLineVar){
					H->Set(MaxCx, MaxY ,Len,IBuff);
					MLines.AppendList(H);
				}
				else{
					delete	H;
				}
			}
			{
				MatchingLineV	*V=new MatchingLineV();
				int	MaxX=-1;
				int	MaxCy=-1;
				double	MaxV=0;
				for(int x=x1;x<x2;x++){
					for(int cy=y1+Len2;cy<y2-Len2;cy++){
						if(IsInclude(x-2,cy-Len2-2)==true && IsInclude(x-2,cy+Len2+2)==true
						&& IsInclude(x+2,cy-Len2-2)==true && IsInclude(x+2,cy+Len2+2)==true){
							V->SetOnly(x, cy ,Len);
							double	D=V->GetVar(IBuff);
							if(D>MaxV){
								MaxV=D;
								MaxX=x;
								MaxCy=cy;
							}
						}
					}
				}
				if(MaxV>PickupLineVar){
					V->Set(MaxX, MaxCy ,Len,IBuff);
					MLines.AppendList(V);
				}
				else{
					delete	V;
				}
			}
		}
	}
}

double	CoeffLine::MatchByLine(int dx,int dy,ImageBuffer &TargetImage,int SearchDot)
{
	double	Ret=1.0;
	for(MatchingLineBase *f=MLines.GetFirst();f!=NULL;f=f->GetNext()){
		double	MaxD=0;
		if(dynamic_cast<MatchingLineV *>(f)!=NULL){
			for(int y=-SearchDot;y<=SearchDot;y++){
				double	D=fabs(f->Match(&TargetImage,dx,dy+y));
				if(D>MaxD){
					MaxD=D;
				}
			}
		}
		else{
			for(int x=-SearchDot;x<=SearchDot;x++){
				double	D=fabs(f->Match(&TargetImage,dx+x,dy));
				if(D>MaxD){
					MaxD=D;
				}
			}
		}
		Ret*=MaxD;
	}
	return Ret;
}

bool	CoeffLine::GoodForRough(void)
{
	if(MLines.GetCount()==0)
		return false;
	int	HCount=0;
	int	VCount=0;
	for(MatchingLineBase *f=MLines.GetFirst();f!=NULL;f=f->GetNext()){
		if(dynamic_cast<MatchingLineV *>(f)!=NULL){
			VCount++;
		}
		else{
			HCount++;
		}
	}
	if(VCount==0 || HCount==0){
		return false;
	}
	return true;
}

//==============================================================================

RotatedMatchingPattern::RotatedMatchingPattern(PalletizeItem *p ,double radian ,double zoomsize)
{
	Parent		=p;
	XYPiece		=NULL;
	XCount=YCount=0;
	PickedAreaInPatternXLen=0;
	PickedAreaInPatternYLen=0;
	Radian			=radian;
	ZoomSize		=zoomsize;
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		RoughPiece[i]	=NULL;
	}
}
RotatedMatchingPattern::~RotatedMatchingPattern(void)
{
	if(XYPiece!=NULL){
		for(int yn=0;yn<YCount;yn++){
			delete	[]XYPiece[yn];
			XYPiece[yn]=NULL;
		}
		delete	[]XYPiece;
		XYPiece=NULL;
	}
	XCount=YCount=0;
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		RoughPiece[i]	=NULL;
	}
}

bool	RotatedMatchingPattern::BuildInitial(FlexAreaImage &ItemArea)
{
	PickedAreaInPattern=ItemArea;
	PickedAreaInPattern.Multiply(ZoomSize);
	int	sW=PickedAreaInPattern.GetWidth();
	int	sH=PickedAreaInPattern.GetHeight();
	double	cx=sW/2.0;
	double	cy=sH/2.0;
	PickedAreaInPattern.Rotate(Radian*180/M_PI,cx,cy);

	ImageBuffer Src;
	Src.Set(0,0,ItemArea.GetWidth(),ItemArea.GetHeight());
	ItemArea.CopyToBuffer(Src);

	double	CosS=cos(Radian);
	double	SinS=sin(Radian);
	double	Z=1.0/ZoomSize;

	FlexAreaImage	DstAreaImage;
	DstAreaImage=PickedAreaInPattern;
	BYTE	*p=DstAreaImage.GetData();
	int		ErrorCount=0;
	for(int i=0;i<DstAreaImage.GetFLineLen();i++){
		int	y=DstAreaImage.GetFLineAbsY(i);
		int	x1=DstAreaImage.GetFLineLeftX(i);
		int	numb=DstAreaImage.GetFLineNumb(i);
		for(int n=0;n<numb;n++){
			int	x=x1+n;
			int	X=((x-cx)*CosS-(y-cy)*SinS)+cx;
			int	Y=((x-cx)*SinS+(y-cy)*CosS)+cy;
			X*=Z;
			Y*=Z;
			if(0<=X && X<Src.GetWidth() && 0<=Y && Y<Src.GetHeight()){
				BYTE	c=Src.GetPixel(X,Y);
				*p=c;
			}
			else{
				ErrorCount++;
			}
			p++;
		}
	}
	int	tMinX=DstAreaImage.GetMinX();
	int	tMinY=DstAreaImage.GetMinY();
	DstAreaImage.MoveToNoClip(-tMinX,-tMinY);

	ImageBuffer TmpBuff;
	TmpBuff.Set(0,0,DstAreaImage.GetWidth(),DstAreaImage.GetHeight());
	DstAreaImage.CopyToBuffer(TmpBuff);
	//QImage	Img=TmpBuff.MakeImage();
	//Img.save("tmppng.png","PNG");

	int	DW=DstAreaImage.GetWidth();
	int	DH=DstAreaImage.GetHeight();
	XCount=DW/Parent->GetThresholdR()->PieceSize;
	YCount=DH/Parent->GetThresholdR()->PieceSize;
	if(XCount==0)
		XCount=1;
	if(YCount==0)
		YCount=1;

	int	DPieceW=DW/XCount;
	int	DPieceH=DH/YCount;

	if(XYPiece!=NULL){
		for(int yn=0;yn<YCount;yn++){
			delete	[]XYPiece[yn];
			XYPiece[yn]=NULL;
		}
		delete	[]XYPiece;
		XYPiece=NULL;
	}
	XYPiece=new CoeffLine*[YCount];
	for(int yn=0;yn<YCount;yn++){
		XYPiece[yn]=new CoeffLine[XCount];
	}
	for(int yn=0;yn<YCount;yn++){
		for(int xn=0;xn<XCount;xn++){
			(XYPiece[yn])[xn].Copy(DstAreaImage 
								   ,DPieceW*xn,DPieceH*yn,DPieceW*(xn+1),DPieceH*(yn+1));
			(XYPiece[yn])[xn].Initial(this,TmpBuff);
			(XYPiece[yn])[xn].MakeSum();
		}
	}
	double	ThresholdV=Parent->GetThresholdR()->ThresholdV;
	for(int yn=0;yn<YCount;yn++){
		for(int xn=0;xn<XCount;xn++){
			if((XYPiece[yn])[xn].GetV()<ThresholdV){
				(XYPiece[yn])[xn].Clear();
			}
		}
	}
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		RoughPiece[i]	=NULL;
	}
	for(int i=0;i<6;i++){
		for(int xn=0;xn<=i && xn<XCount;xn++){
			for(int yn=i-xn;yn<=i && yn<YCount;yn++){
				int	tx1=xn;
				int	ty1=yn;
				int	tx2=XCount-xn-1;
				int	ty2=YCount-yn-1;
				if(RoughPiece[0]==NULL){
					CoeffLine	*f=&(XYPiece[ty1])[tx1];
					if(f->GoodForRough()==true){
						RoughPiece[0]=f;
					}
				}
				if(RoughPiece[1]==NULL){
					CoeffLine	*f=&(XYPiece[ty1])[tx2];
					if(f->GoodForRough()==true){
						RoughPiece[1]=f;
					}
				}
				if(RoughPiece[2]==NULL){
					CoeffLine	*f=&(XYPiece[ty2])[tx1];
					if(f->GoodForRough()==true){
						RoughPiece[2]=f;
					}
				}
				if(RoughPiece[3]==NULL){
					CoeffLine	*f=&(XYPiece[ty2])[tx2];
					if(f->GoodForRough()==true){
						RoughPiece[3]=f;
					}
				}
			}
		}
	}

	return true;
}

double	RotatedMatchingPattern::Match(int dx ,int dy ,ImageBuffer &TargetImage)
{
	DoubleList	DList;
	int	SearchDotPiece	=Parent->GetThresholdR()->SearchDotPiece;
	for(int yn=0;yn<YCount;yn++){
		for(int xn=0;xn<XCount;xn++){
			CoeffLine	&f=(XYPiece[yn])[xn];
			double	MaxD=0;
			for(int y=-SearchDotPiece;y<=SearchDotPiece;y++){
				for(int x=-SearchDotPiece;x<=SearchDotPiece;x++){
					double	D=fabs(f.CalcCoeff(dx+x,dy+y,TargetImage));
					if(D>MaxD){
						MaxD=D;
					}
				}
			}
			DList.Add(MaxD);
		}
	}
	double	Ret=1.0;
	DList.Sort();
	int		MCount=YCount*XCount*0.2;
	if(MCount<6)
		MCount=6;
	int	i=0;
	for(DoubleClass *d=DList.GetFirst();d!=NULL && i<MCount;d=d->GetNext(),i++){
		Ret*=d->GetValue();
	}
	return Ret;
}
double	RotatedMatchingPattern::MatchByLine(int dx,int dy,ImageBuffer &TargetImage)
{
	DoubleList	DList;
	int	SearchDotPiece	=Parent->GetThresholdR()->SearchDotPiece;
	for(int yn=0;yn<YCount;yn++){
		for(int xn=0;xn<XCount;xn++){
			CoeffLine	&f=(XYPiece[yn])[xn];
			if(f.MLines.GetFirst()!=NULL){
				double	D=fabs(f.MatchByLine(dx,dy,TargetImage,SearchDotPiece));
				DList.Add(D);
			}
		}
	}
	double	Ret=1.0;
	DList.Sort();
	int		MCount=YCount*XCount*0.2;
	if(MCount<6)
		MCount=6;
	int	i=0;
	for(DoubleClass *d=DList.GetFirst();d!=NULL && i<MCount;d=d->GetNext(),i++){
		Ret*=d->GetValue();
	}
	return Ret;
}
double	RotatedMatchingPattern::MatchRoughByLine(int dx,int dy,ImageBuffer &TargetImage)
{
	double	Ret=1.0;
	int	SearchDotPiece	=Parent->GetThresholdR()->SearchDotPiece;
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		CoeffLine	*f=RoughPiece[i];
		if(f!=NULL){
			double	D=fabs(f->MatchByLine(dx,dy,TargetImage,SearchDotPiece));
			Ret*=D;
		}
	}
	return Ret;
}
double	RotatedMatchingPattern::MatchByOneLine(int dx,int dy,ImageBuffer &TargetImage)
{
	//int	SearchDotPiece	=Parent->GetThresholdR()->SearchDotPiece;
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		CoeffLine	*f=RoughPiece[i];
		if(f!=NULL){
			double	D=fabs(f->MatchByLine(dx,dy,TargetImage,1));
			return D;
		}
	}
	return 0;
}

double	RotatedMatchingPattern::MatchRough(int dx ,int dy ,ImageBuffer &TargetImage)
{
	double	Ret=1.0;
	//int	SearchDotPiece	=Parent->GetThresholdR()->SearchDotPiece;
	int	SearchDotPiece	=1;
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		CoeffLine	*f=RoughPiece[i];
		double	MaxD=0;
		for(int y=-SearchDotPiece;y<=SearchDotPiece;y++){
			for(int x=-SearchDotPiece;x<=SearchDotPiece;x++){
				double	D=fabs(f->CalcCoeff(dx+x,dy+y,TargetImage));
				if(D>MaxD){
					MaxD=D;
				}
			}
		}
		Ret*=MaxD;
	}
	return Ret;
}
void	RotatedMatchingPattern::Draw(QImage &IData
									,int MovX ,int MovY ,double ZoomRate)
{
	for(int yn=0;yn<YCount;yn++){
		for(int xn=0;xn<XCount;xn++){
			CoeffLine	&f=(XYPiece[yn])[xn];
			f.DrawImage(0,0 ,&IData
						,ZoomRate ,MovX ,MovY
						,true,true,true
						,0xFF);
		}
	}
	QRgb	Col=qRgba(255,160,0,128);
	for(int i=0;i<sizeof(RoughPiece)/sizeof(RoughPiece[0]);i++){
		if(RoughPiece[i]!=NULL){
			RoughPiece[i]->DrawAlpha(0,0,&IData,Col,ZoomRate,MovX,MovY);
		}
	}

	QPainter	Pnt(&IData);
	Pnt.setPen(Qt::yellow);
	for(int yn=0;yn<YCount;yn++){
		for(int xn=0;xn<XCount;xn++){
			CoeffLine	&f=(XYPiece[yn])[xn];
			for(MatchingLineBase *L=f.MLines.GetFirst();L!=NULL;L=L->GetNext()){
				L->Draw(Pnt,ZoomRate,MovX,MovY);
			}

			//ImageBuffer TmpBuff;
			//TmpBuff.Set(0,0,f.GetWidth(),f.GetHeight());
			//f.CopyToBuffer(TmpBuff);
			//QImage	Img=TmpBuff.MakeImage();
			//QString	FileName=QString("tmppng-")
			//				+QString::number(xn)
			//				+QString("-")
			//				+QString::number(yn)
			//				+QString(".png");
			//Img.save(FileName,"PNG");
		}
	}
}
