/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentBlock\XAlignmentBlockRotated.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlignmentBlock.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
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

void	MatchingLineBase::Initial(bool ModeCalcIncline)
{
	A=AA=0;
	AASS=0;
	if(LineLen!=0){
		if(ModeCalcIncline==true){
			double	pa,pb;
			if(CalcIncline(pa,pb ,Data ,LineLen)==true){
				for(int n=0;n<LineLen;n++){
					Data[n]=Data[n]-(pa*n+pb);
				}
				for(int n=0;n<LineLen;n++){
					int	a=Data[n];
					A+=a;
					AA+=a*a;
				}
			}
		}
		else{
			for(int n=0;n<LineLen;n++){
				int	a=Data[n];
				A+=a;
				AA+=a*a;
			}
		}
		AvrS=((double)A)/(double)LineLen;

		AASS=AA-LineLen*AvrS*AvrS;
		RLineLen=1.0/((double)LineLen);
	}
}
void	MatchingLineBase::MoveTo(int dx ,int dy)
{
	PosX+=dx;
	PosY+=dy;
}

bool	MatchingLineBase::CalcIncline(double &pa,double &pb ,BYTE *D ,int N)
{
	int	An=0;
	int	nAn=0;
		
	for(int n=0;n<N;n++){
		int	a=D[n];
		An +=a;
		nAn+=n*a;
	}

	double	k1=N*(N+1)*(2*N+1)/6;
	double	k2=nAn;
	double	k3=N*(N+1)/2;
	double	k4=An;

	double	M=N*k1-k3*k3;
	if(M==0.0)
		return false;
	pa=(N*k2-k3*k4)/M;
	pb=(k4-k3*pa)/N;

	return true;
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
bool	MatchingLineV::Set(bool ModeCalcIncline,double cx, double cy ,double Len 
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
	Initial(ModeCalcIncline);
	return true;
}
void	MatchingLineV::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	Pnt.drawLine((PosX+movx)*ZoomRate ,(PosY+movy)*ZoomRate
			    ,(PosX+movx)*ZoomRate ,(PosY+LineLen+movy)*ZoomRate);
}

double	MatchingLineV::GetVar(bool ModeCalcIncline,ImageBuffer &Buff)
{
	double	B,BB;
	B=BB=0.0;
	if(LineLen!=0){
		BYTE	W[100];
		for(int n=0;n<LineLen;n++){
			W[n]=Buff.GetYWithoutDepended(PosY+n)[PosX];
		}
		if(ModeCalcIncline==true){
			double	pa,pb;
			if(CalcIncline(pa,pb ,W ,LineLen)==true){
				for(int n=0;n<LineLen;n++){
					int	b=W[n]-(pa*n+pb);
					B+=b;
					BB+=b*b;
				}
			}
		}
		else{
			for(int n=0;n<LineLen;n++){
				int	b=W[n];
				B+=b;
				BB+=b*b;
			}
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
double	MatchingLineV::GetSitaBrightness(ImageBuffer &Buff)
{
	if(LineLen!=0){
		BYTE	W[100];
		for(int n=0;n<LineLen;n++){
			W[n]=Buff.GetYWithoutDepended(PosY+n)[PosX];
		}

		int	N=3;
		if(LineLen>=N*2+2){
			int	C=LineLen/2;
			int	L=0;
			for(int i=1;i<=N;i++){
				L+=W[C-i];
			}
			int	H=0;
			for(int i=1;i<=N;i++){
				H+=W[C+i];
			}
			double	Div=((double)(H-L))/((double)N);
			
			return fabs(Div);
		}
	}
	return 0;
}
double	MatchingLineV::Match(bool ModeCalcIncline,ImageBuffer *TBuff,int dx,int dy)
{
	int	TargetPosX=PosX+dx;
	int	TargetPosY=PosY+dy;
	ImageBuffer *D=TBuff;

	if(0<=TargetPosY && (TargetPosY+LineLen)<D->GetHeight()
	&& 0<=TargetPosX &&  TargetPosX			<D->GetWidth()
	&& 0<=PosY && (PosY+LineLen)<D->GetHeight()
	&& 0<=PosX &&  PosX			<D->GetWidth()
	&& LineLen>0){
		unsigned	int	B =0;
		unsigned	int	BB=0;
		unsigned	int	AB=0;
		BYTE	W[100];
		for(int n=0;n<LineLen;n++){
			W[n]=D->GetYWithoutDepended(TargetPosY+n)[TargetPosX];
		}
		if(ModeCalcIncline==true){
			double	pa,pb;
			if(CalcIncline(pa,pb ,W ,LineLen)==true){
				BYTE	*d=W;
				BYTE	*s=Data;
				for(int n=0;n<LineLen;n++,s++,d++){
					BYTE	b=*d-(pa*n+pb);
					B +=b;
					BB+=b*b;
					AB+=(*s)*b;
				}
			}
		}
		else{
			BYTE	*d=W;
			BYTE	*s=Data;
			for(int n=0;n<LineLen;n++,s++,d++){
				BYTE	b=*d;
				B +=b;
				BB+=b*b;
				AB+=(*s)*b;
			}
		}
		double	AvrD=((double)B)*RLineLen;

		double	BBSS=BB-LineLen*AvrD*AvrD;
		double	M=AASS*BBSS;
		if(M<=0){
			return 0;
		}
		double	Rt;
		if(AASS>=BBSS)
			Rt=sqrt(BBSS/AASS);
		else
			Rt=sqrt(AASS/BBSS);
		M=sqrt(M);
		double	K=AB-LineLen*AvrS*AvrD;
		return Rt*K/M;
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
bool	MatchingLineH::Set(bool ModeCalcIncline,double cx, double cy ,double Len 
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
	Initial(ModeCalcIncline);
	return true;
}
void	MatchingLineH::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	Pnt.drawLine((PosX+movx)*ZoomRate ,(PosY+movy)*ZoomRate
			    ,(PosX+LineLen+movx)*ZoomRate ,(PosY+movy)*ZoomRate);
}
double	MatchingLineH::GetVar(bool ModeCalcIncline,ImageBuffer &Buff)
{
	double	B,BB;
	B=BB=0.0;
	if(LineLen!=0){
		BYTE	*s=Buff.GetYWithoutDepended(PosY);
		BYTE	W[100];
		for(int n=0;n<LineLen;n++){
			W[n]=s[PosX+n];
		}
		if(ModeCalcIncline==true){
			double	pa,pb;
			if(CalcIncline(pa,pb ,W ,LineLen)==true){
				for(int n=0;n<LineLen;n++){
					int	b=W[n]-(pa*n+pb);
					B+=b;
					BB+=b*b;
				}
			}
		}
		else{
			for(int n=0;n<LineLen;n++){
				int	b=W[n];
				B+=b;
				BB+=b*b;
			}
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
double	MatchingLineH::GetSitaBrightness(ImageBuffer &Buff)
{
	if(LineLen!=0){
		BYTE	*s=Buff.GetYWithoutDepended(PosY);
		BYTE	W[100];
		for(int n=0;n<LineLen;n++){
			W[n]=s[PosX+n];
		}

		int	N=3;
		if(LineLen>=N*2+2){
			int	C=LineLen/2;
			int	L=0;
			for(int i=1;i<=N;i++){
				L+=W[C-i];
			}
			int	H=0;
			for(int i=1;i<=N;i++){
				H+=W[C+i];
			}
			double	Div=((double)(H-L))/((double)N);
			
			return fabs(Div);
		}
	}
	return 0;
}
double	MatchingLineH::Match(bool ModeCalcIncline,ImageBuffer *TBuff,int dx,int dy)
{
	int	TargetPosX=PosX+dx;
	int	TargetPosY=PosY+dy;
	ImageBuffer *D=TBuff;

	if(0<=TargetPosY &&  TargetPosY			<D->GetHeight()
	&& 0<=TargetPosX && (TargetPosX+LineLen)<D->GetWidth()
	&& 0<=PosY &&  PosY			<D->GetHeight()
	&& 0<=PosX && (PosX+LineLen)<D->GetWidth()
	&& LineLen>0){

		unsigned	int	B =0;
		unsigned	int	BB=0;
		unsigned	int	AB=0;
		BYTE	*d=&D->GetYWithoutDepended(TargetPosY)[TargetPosX];
		BYTE	*s=Data;
		BYTE	W[100];
		for(int n=0;n<LineLen;n++,d++){
			W[n]=*d;
		}
		if(ModeCalcIncline==true){
			double	pa,pb;
			if(CalcIncline(pa,pb ,W ,LineLen)==true){
				for(int n=0;n<LineLen;n++,s++){
					BYTE	b=W[n]-(pa*n+pb);
					B +=b;
					BB+=b*b;
					AB+=(*s)*b;
				}
			}
		}
		else{
			for(int n=0;n<LineLen;n++,s++){
				BYTE	b=W[n];
				B +=b;
				BB+=b*b;
				AB+=(*s)*b;
			}
		}

		double	AvrD=((double)B)*RLineLen;

		double	BBSS=BB-LineLen*AvrD*AvrD;
		double	M=AASS*BBSS;
		if(M<=0){
			return 0;
		}
		double	Rt;
		if(AASS>=BBSS)
			Rt=sqrt(BBSS/AASS);
		else
			Rt=sqrt(AASS/BBSS);
		M=sqrt(M);
		double	K=AB-LineLen*AvrS*AvrD;
		return Rt*K/M;
	}
	return 0;
}

//==============================================================================

RotatedMatchingPattern::RotatedMatchingPattern(AlignmentBlockItem *p ,double radian)
{
	Parent		=p;
	Radian			=radian;
}
RotatedMatchingPattern::~RotatedMatchingPattern(void)
{
}

class TmpLineList : public NPList<TmpLineList>
{
public:
	int		Cx,Cy;
	double	Var;
	int		Layer;

	TmpLineList(void){}

	virtual	int	Compare(TmpLineList &src)	override
	{
		double	d=Var-src.Var;
		if(d>0)
			return -1;
		if(d<0)
			return 1;
		return 0;
	}
};



bool	RotatedMatchingPattern::BuildInitial(bool ModeCalcIncline)
{
	ImageBuffer *ImageList[100];
	Parent->GetMasterBuffList(ImageList);
	int	LineLength	=Parent->GetThresholdR()->LineLength;
	int		DotPerLine	=Parent->GetDotPerLine();
	int		MaxLines	=Parent->GetMaxLines();

	FlexArea	RArea=Parent->GetArea();
	RArea.FatAreaN(LineLength);
	RArea.ClipArea(1 ,1 ,DotPerLine-1 ,MaxLines-1);

	Set(RArea,ImageList
			, Parent->GetLayerNumb());

	double	Cos=cos(Radian);
	double	Sin=sin(Radian);
	double	Cx,Cy;
	Parent->GetCenter(Cx,Cy);
	
	ImagePointerContainer ImageListContainer;
	Parent->GetMasterBuffList(ImageListContainer);
	for(int layer=0;layer<Parent->GetLayerNumb();layer++){
		BYTE	*d=GetData(layer);
		ImageBuffer	*IBuff=ImageListContainer[layer];
		for(int i=0;i<GetFLineLen();i++){
			int	Y	=GetFLineAbsY(i);
			int	X1	=GetFLineLeftX(i);
			int	Numb=GetFLineNumb(i);
			for(int k=0;k<Numb;k++){
				int	X=X1+k;
				int	x= (X-Cx)*Cos+(Y-Cy)*Sin+Cx;
				int	y=-(X-Cx)*Sin+(Y-Cy)*Cos+Cy;
				if(x<0 || DotPerLine<=x
				|| y<0 || MaxLines<=y){
					return false;
				}
				*d=IBuff->GetPixel(x,y);
				d++;
			}
		}
	}

	int	XLen=GetWidth();
	int	YLen=GetHeight();
	ImageBufferListContainer DstCont;
	DstCont.MakeImageBuff(Parent->GetLayerNumb(),0,XLen,YLen);
	ImagePointerContainer	Dst(DstCont);
	CopyToBuffer(Dst ,-GetMinX(),-GetMinY());

	double	MinVar	=Parent->GetThresholdR()->MinVar;
	double	ThreDiv	=Parent->GetThresholdR()->ThreDiv;
	int		NeighborLen=hypot(XLen,YLen)*0.1;
	int		Step=3;
	{
		NPListPack<TmpLineList>	TmpLineListContainer;
		double	tMinVar=MinVar;
		int		NCount=0;
		do{
			for(int Y=LineLength;Y<YLen-LineLength;Y+=Step){
				for(int X=LineLength;X<XLen-LineLength;X+=Step){
					MatchingLineV	V;
					V.SetOnly(X,Y,LineLength);

					double	VMaxVar=0;
					int		VLayer=-1;
					double	LDiv;
					for(int layer=0;layer<Parent->GetLayerNumb();layer++){
						ImageBuffer	*B=DstCont[layer];
						double	D=V.GetVar(ModeCalcIncline,*B);
						if(D>VMaxVar){
							VMaxVar	=D;
							VLayer	=layer;
							LDiv=V.GetSitaBrightness(*B);
						}
					}
					if(VMaxVar>=tMinVar && LDiv>=ThreDiv){
						TmpLineList	*C=new TmpLineList();
						C->Cx=X;
						C->Cy=Y;
						C->Var=VMaxVar;
						C->Layer=VLayer;
						TmpLineListContainer.AppendList(C);
					}
				}
			}
			tMinVar*=0.6;
			NCount++;
			if(NCount>5)
				break;
		}while(TmpLineListContainer.GetCount()==0);

		TmpLineListContainer.Sort();
		for(TmpLineList *s=TmpLineListContainer.GetFirst();s!=NULL;s=s->GetNext()){
			for(TmpLineList *t=s->GetNext();t!=NULL;){
				TmpLineList *NextT=t->GetNext();
				if(hypot(s->Cx-t->Cx,s->Cy-t->Cy)<NeighborLen){
					TmpLineListContainer.RemoveList(t);
					delete	t;
				}
				t=NextT;
			}
		}
		for(TmpLineList *s=TmpLineListContainer.GetFirst();s!=NULL;s=s->GetNext()){
			MatchingLineV	*V=new MatchingLineV;
			ImageBuffer	*B=DstCont[s->Layer];
			V->Layer	=s->Layer;
			V->Set(ModeCalcIncline,s->Cx,s->Cy,LineLength,*B);
			V->MoveTo(GetMinX(),GetMinY());
			MLines.AppendList(V);
		}
	}
	{
		NPListPack<TmpLineList>	TmpLineListContainer;
		double	tMinVar=MinVar;
		int		NCount=0;
		do{
			for(int Y=LineLength;Y<YLen-LineLength;Y+=Step){
				for(int X=LineLength;X<XLen-LineLength;X+=Step){
					MatchingLineH	H;
					H.SetOnly(X,Y,LineLength);

					double	VMaxVar=0;
					int		VLayer=-1;
					for(int layer=0;layer<Parent->GetLayerNumb();layer++){
						ImageBuffer	*B=DstCont[layer];
						double	D=H.GetVar(ModeCalcIncline,*B);
						if(D>VMaxVar){
							VMaxVar=D;
							VLayer=layer;
						}
					}
					if(VMaxVar>=tMinVar){
						TmpLineList	*C=new TmpLineList();
						C->Cx=X;
						C->Cy=Y;
						C->Var=VMaxVar;
						C->Layer=VLayer;
						TmpLineListContainer.AppendList(C);
					}
				}
			}
			tMinVar*=0.6;
			NCount++;
			if(NCount>5)
				break;
		}while(TmpLineListContainer.GetCount()==0);

		TmpLineListContainer.Sort();
		for(TmpLineList *s=TmpLineListContainer.GetFirst();s!=NULL;s=s->GetNext()){
			for(TmpLineList *t=s->GetNext();t!=NULL;){
				TmpLineList *NextT=t->GetNext();
				if(hypot(s->Cx-t->Cx,s->Cy-t->Cy)<NeighborLen){
					TmpLineListContainer.RemoveList(t);
					delete	t;
				}
				t=NextT;
			}
		}
		for(TmpLineList *s=TmpLineListContainer.GetFirst();s!=NULL;s=s->GetNext()){
			MatchingLineH	*H=new MatchingLineH;
			H->Layer	=s->Layer;
			ImageBuffer	*B=DstCont[s->Layer];
			H->Set(ModeCalcIncline,s->Cx,s->Cy,LineLength,*B);
			H->MoveTo(GetMinX(),GetMinY());
			MLines.AppendList(H);
		}
	}

	return true;
}

void	RotatedMatchingPattern::MatchByLine	(bool ModeCalcIncline,int dx,int dy,ImagePointerContainer &TargetImages,int SearchDot)
{
	if(MLines.GetCount()<=2){
		ResultDx=0;
		ResultDy=0;
		Result	=0;
		return;
	}

	int	Step=2;

	double	MaxD=0;
	int		MaxDx,MaxDy;
	for(int dy=-SearchDot;dy<=SearchDot;dy+=Step){
		for(int dx=-SearchDot;dx<=SearchDot;dx+=Step){
			double	DValue=1.0;
			for(MatchingLineBase *s=MLines.GetFirst();s!=NULL;s=s->GetNext()){
				ImageBuffer	*B=TargetImages[s->Layer];

				double	D=s->Match(ModeCalcIncline,B,dx,dy);
				if(D<0)
					D=0;
				DValue+=D*D;
			}
			if(MaxD<DValue){
				MaxD=DValue;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	ResultDx=MaxDx;
	ResultDy=MaxDy;
	for(int dy=-Step;dy<=Step;dy++){
		for(int dx=-Step;dx<=Step;dx++){
			double	DValue=1.0;
			for(MatchingLineBase *s=MLines.GetFirst();s!=NULL;s=s->GetNext()){
				ImageBuffer	*B=TargetImages[s->Layer];
				double	D=s->Match(ModeCalcIncline,B,MaxDx+dx,MaxDy+dy);
				if(D<0)
					D=0;
				DValue+=D*D;
			}
			if(MaxD<DValue){
				MaxD=DValue;
				ResultDx=MaxDx+dx;
				ResultDy=MaxDy+dy;
			}
		}
	}
	Result=MaxD;
}

void	RotatedMatchingPattern::Draw(QImage &IData
									,int MovX ,int MovY ,double ZoomRate)
{

}

void	RotatedMatchingPattern::DrawLine(QImage &IData ,QColor &LineColor
										,int MovX ,int MovY ,double ZoomRate)
{
	QPainter	Pnt(&IData);
	Pnt.setPen(LineColor);
	for(MatchingLineBase *s=MLines.GetFirst();s!=NULL;s=s->GetNext()){
		s->Draw(Pnt,ZoomRate,MovX,MovY);
	}
}
