#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGerberApertureMacro.h"
#include "swap.h"
#include <QColor>
#include "XCrossObj.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <omp.h>

void	DrawPolygon(double *PosX,double *PosY,int PosCount
					,double ImagePosX ,double ImagePosY 
					,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
					,const QRgb &Col
					,ApertureHole &Hole);
void	MakeImagePolygon(double *PosX,double *PosY,int PosCount
					,double ImagePosX ,double ImagePosY 
					,BYTE **Image ,int XByte ,int YLen
					,bool PosiImage
					,double ZoomRateX,double ZoomRateY
					,ApertureHole &Hole);
bool IsInside(double lX, double lY, double *plX, double *plY ,int nNum);
double	GetCircleAreaSize(double Cx,double Cy ,double R
						, double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);
double	GetRectangleAreaSize(double MinX,double MinY,double MaxX,double MaxY	//Rectangle
						, double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2);

ApertureHole::ApertureHole(void)
{
	HoleType=_ApertureHole_None;
	HSize=0;
	WSize=0;
}

bool	ApertureHole::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	BYTE	d=(BYTE)HoleType;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,HSize)==false)
		return false;
	if(::Save(f,WSize)==false)
		return false;
	return true;
}
bool	ApertureHole::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	HoleType=(__HoleType)d;
	if(::Load(f,HSize)==false)
		return false;
	if(::Load(f,WSize)==false)
		return false;
	return true;
}

ApertureHole	&ApertureHole::operator=(ApertureHole &src)
{
	HoleType=src.HoleType;
	HSize	=src.HSize;
	WSize	=src.WSize;
	return *this;
}

void	ApertureHole::Draw(double ImagePosX ,double ImagePosY 
							,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
							,const QRgb &Col,double Angle)
{
	if(HoleType==_ApertureHole_Circle){
		double	Rx=(WSize*ZoomRateX)*0.5;
		double	Ry=(WSize*ZoomRateY)*0.5;
		if(0<=(ImagePosY+Ry) && (ImagePosY-Ry)<pnt.height() && 0<=(ImagePosX+Rx) && (ImagePosX-Rx)<pnt.width()){
			if(Rx<=1.5 && Ry<=1.5){
				if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
					BYTE	*d=pnt.scanLine((int)ImagePosY);
					int	X=ImagePosX;
					if(pnt.depth()==32){
						*((QRgb *)&d[X<<2])=Col;
					}
					else if(pnt.depth()==8){
						d[X]=(BYTE)Col;
					}
				}
			}
			else{
				int	Ryi=Ry;
				for(int y=-Ryi;y<=Ryi;y++){
					double	wy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-wy*wy));
					int	Y=ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						int	X1=ImagePosX-m;
						int	X2=ImagePosX+m;
						BYTE	*d=pnt.scanLine(Y);
						X1=max(X1,0);
						X2=min(X2,pnt.width()-1);
						if(pnt.depth()==32){
							for(int X=X1;X<=X2;X++){
								*((QRgb *)&d[X<<2])=Col;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
	else if(HoleType==_ApertureHole_Rectangle){
		double	Rx=(WSize*ZoomRateX)*0.5;
		double	Ry=(HSize*ZoomRateY)*0.5;
		if(0<=(ImagePosY+Ry) && (ImagePosY-Ry)<pnt.height() && 0<=(ImagePosX+Rx) && (ImagePosX-Rx)<pnt.width()){
			if(Rx<=1.5 || Ry<=1.5){
				if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
					BYTE	*d=pnt.scanLine((int)ImagePosY);
					int	X=ImagePosX;
					if(pnt.depth()==32){
						*((QRgb *)&d[X<<2])=Col;
					}
					else if(pnt.depth()==8){
						d[X]=(BYTE)Col;
					}
				}
			}
			else{
				if(Angle==0.0){
					int	Rix=Rx;
					int	Riy=Ry;
					for(int y=-Riy;y<=Riy;y++){
						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX-Rix;
							int	X2=ImagePosX+Rix;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								for(int X=X1;X<=X2;X++){
									*((QRgb *)&d[X<<2])=Col;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
				else{
					double	PosX[5];
					double	PosY[5];
					double	CosS=cos(Angle);
					double	SinS=sin(Angle);
					PosX[0]=-Rx*CosS - Ry*SinS;
					PosY[0]= Rx*SinS - Ry*CosS;
					PosX[1]= Rx*CosS - Ry*SinS;
					PosY[1]=-Rx*SinS - Ry*CosS;
					PosX[2]= Rx*CosS + Ry*SinS;
					PosY[2]=-Rx*SinS + Ry*CosS;
					PosX[3]=-Rx*CosS + Ry*SinS;
					PosY[3]= Rx*SinS + Ry*CosS;
					PosX[4]=PosX[0];
					PosY[4]=PosY[0];
					//DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRate ,Col);
				}
			}
		}
	}
}
void	ApertureHole::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,BYTE **Image ,int XByte ,int YLen
								,double Angle
								,bool PosiImage)
{
	int	XLen=XByte<<3;
	if(HoleType==_ApertureHole_Circle){
		double	Rx=WSize*ZoomRateX*0.5;
		double	Ry=WSize*ZoomRateY*0.5;
		if(Rx<1.0)
			Rx=1.0;
		if(Ry<1.0)
			Ry=1.0;
		int	Ryi=Ry;
		for(int y=-Ryi;y<=Ryi;y++){
			double	wy=Rx*y/Ry;
			int	m=sqrt((double)(Rx*Rx-wy*wy));
			int	Y=ImagePosY+y;
			if(0<=Y && Y<YLen){
				int	X1=ImagePosX-m;
				int	X2=ImagePosX+m;
				BYTE	*d=Image[Y];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
			}
		}
	}
	else if(HoleType==_ApertureHole_Rectangle){
		double	Rx=WSize*ZoomRateX*0.5;
		double	Ry=HSize*ZoomRateY*0.5;
		if(Rx<1.0)
			Rx=1.0;
		if(Ry<1.0)
			Ry=1.0;
		if(Angle==0.0){
			int	Rix=Rx;
			int	Riy=Ry;
			for(int y=-Riy;y<=Riy;y++){
				int	Y=ImagePosY+y;
				if(0<=Y && Y<YLen){
					int	X1=ImagePosX-Rix;
					int	X2=ImagePosX+Rix;
					BYTE	*d=Image[Y];
					X1=max(X1,0);
					X2=min(X2,XLen-1);
					if(PosiImage==true){
						for(int X=X1;X<=X2;X++){
							SetBmpBitOnY0(d,X);
						}
					}
					else{
						for(int X=X1;X<=X2;X++){
							SetBmpBitOnY1(d,X);
						}
					}
				}
			}
		}
		else{
			double	PosX[5];
			double	PosY[5];
			double	CosS=cos(Angle);
			double	SinS=sin(Angle);
			PosX[0]=-Rx*CosS - Ry*SinS;
			PosY[0]= Rx*SinS - Ry*CosS;
			PosX[1]= Rx*CosS - Ry*SinS;
			PosY[1]=-Rx*SinS - Ry*CosS;
			PosX[2]= Rx*CosS + Ry*SinS;
			PosY[2]=-Rx*SinS + Ry*CosS;
			PosX[3]=-Rx*CosS + Ry*SinS;
			PosY[3]= Rx*SinS + Ry*CosS;
			PosX[4]=PosX[0];
			PosY[4]=PosY[0];
			//MakeImagePolygon(PosX,PosY,5
			//				,ImagePosX ,ImagePosY 
			//				,Image ,XByte ,YLen
			//				,PosiImage);
		}
	}
}

void	DrawPolygon(double *PosX,double *PosY,int PosCount
					,double ImagePosX ,double ImagePosY 
					,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
					,const QRgb &Col
					,ApertureHole &Hole)
{
	if(PosCount==0)
		return;
	double	MinY=PosY[0];
	double	MaxY=PosY[0];
	for(int i=1;i<PosCount;i++){
		MinY=min(MinY,PosY[i]);
		MaxY=max(MaxY,PosY[i]);
	}
	int	iMinY=MinY;
	int	iMaxY=MaxY;
	int	YNumb=iMaxY-iMinY+1;
	if(Hole.HoleType==ApertureHole::_ApertureHole_None){
		#pragma omp parallel
		{
			#pragma omp for
			//for(int y=iMinY;y<=iMaxY;y++){
			for(int t=0;t<YNumb;t++){
				int	y=t+iMinY;
				double	X[1000];
				int	Y=y+ImagePosY;
				if(0<=Y && Y<pnt.height()){
					int	N=0;
					for(int i=0;i<PosCount-1;i++){
						if(GetCrossHalfInnerPoint(PosX[i],PosY[i],PosX[i+1],PosY[i+1],y,X[N])==true)
							N++;
					}
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						MinX=min(MinX,X[i]);
						MaxX=max(MaxX,X[i]);
					}
					int	X1=ImagePosX+MinX;
					int	X2=ImagePosX+MaxX;
					BYTE	*d=pnt.scanLine(Y);
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					if(pnt.depth()==32){
						QRgb	*dp=((QRgb *)&d[X1<<2]);
						for(int X=X1;X<=X2;X++){
							*dp=Col;
							dp++;
						}
					}
					else if(pnt.depth()==8){
						for(int X=X1;X<=X2;X++){
							d[X]=(BYTE)Col;
						}
					}
				}
			}
		}
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
		double	HoleRx=(Hole.GetWidth() *ZoomRateX)*0.5;
		double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;
		int	HoleRyi=HoleRy;
		#pragma omp parallel
		{
			#pragma omp for
			//for(int y=iMinY;y<=iMaxY;y++){
			for(int t=0;t<YNumb;t++){
				int	y=t+iMinY;
				double	X[1000];
				int	Y=y+ImagePosY;
					
				if(0<=Y && Y<pnt.height()){
					int	N=0;
					for(int i=0;i<PosCount-1;i++){
						if(GetCrossHalfInnerPoint(PosX[i],PosY[i],PosX[i+1],PosY[i+1],y,X[N])==true)
							N++;
					}
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						MinX=min(MinX,X[i]);
						MaxX=max(MaxX,X[i]);
					}
					int	X1=ImagePosX+MinX;
					int	X2=ImagePosX+MaxX;
					BYTE	*d=pnt.scanLine(Y);
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
				
					if(-HoleRyi<=y && y<=HoleRyi){
						double	wy=HoleRx*y/HoleRy;
						int	hm=sqrt((double)(HoleRx*HoleRx-wy*wy));

						int	X1h=ImagePosX-hm;
						int	X2h=ImagePosX+hm;
						X1h=min(X1h,pnt.width()-1);
						X2h=max(X2h,0);

						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X1;X<=X1h;X++){
								*dp=Col;
								dp++;
							}
							dp=((QRgb *)&d[X2h<<2]);
							for(int X=X2h;X<=X2;X++){
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X1h;X++){
								d[X]=(BYTE)Col;
							}
							for(int X=X2h;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					else{
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X1;X<=X2;X++){
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
		}
	}
}

void	MakeImagePolygon(double *PosX,double *PosY,int PosCount
					,double ImagePosX ,double ImagePosY 
					,BYTE **Image ,int XByte ,int YLen
					,bool PosiImage
					,double ZoomRateX,double ZoomRateY
					,ApertureHole &Hole)
{
	if(PosCount==0)
		return;
	double	MinY=PosY[0];
	double	MaxY=PosY[0];
	for(int i=1;i<PosCount;i++){
		MinY=min(MinY,PosY[i]);
		MaxY=max(MaxY,PosY[i]);
	}
	int	iMinY=MinY;
	int	iMaxY=MaxY;
	int	XLen=XByte<<3;
	int	NLen=iMaxY-iMinY+1;
	if(Hole.HoleType==ApertureHole::_ApertureHole_None){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<NLen;i++){
				int	y=iMinY+i;
			//for(int y=iMinY;y<=iMaxY;y++){
				double	X[200];
				int	Y=y+ImagePosY;
				if(0<=Y && Y<YLen){
					int	N=0;
					for(int i=0;i<PosCount-1;i++){
						if(GetCrossHalfInnerPoint(PosX[i],PosY[i],PosX[i+1],PosY[i+1],y,X[N])==true)
							N++;
					}
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						MinX=min(MinX,X[i]);
						MaxX=max(MaxX,X[i]);
					}
					int	X1=ImagePosX+MinX;
					int	X2=ImagePosX+MaxX;
					BYTE	*d=Image[Y];
					X1=max(X1,0);
					X2=min(X2,XLen-1);
					if(PosiImage==true){
						for(int X=X1;X<=X2;X++){
							SetBmpBitOnY1(d,X);
						}
					}
					else{
						for(int X=X1;X<=X2;X++){
							SetBmpBitOnY0(d,X);
						}
					}
				}
			}
		}
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
		double	HoleRx=(Hole.GetWidth ()*ZoomRateX)*0.5;
		double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;
		int	HoleRyi=HoleRy;
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<NLen;i++){
				int	y=iMinY+i;
			//for(int y=iMinY;y<=iMaxY;y++){
				double	X[200];
				int	Y=y+ImagePosY;
				if(0<=Y && Y<YLen){
					int	N=0;
					for(int i=0;i<PosCount-1;i++){
						if(GetCrossHalfInnerPoint(PosX[i],PosY[i],PosX[i+1],PosY[i+1],y,X[N])==true)
							N++;
					}
					if(N==0)
						continue;
					double	MinX=X[0];
					double	MaxX=X[0];
					for(int i=1;i<N;i++){
						MinX=min(MinX,X[i]);
						MaxX=max(MaxX,X[i]);
					}
					int	X1=ImagePosX+MinX;
					int	X2=ImagePosX+MaxX;
					BYTE	*d=Image[Y];
					X1=max(X1,0);
					X2=min(X2,XLen-1);
					if(-HoleRyi<=y && y<=HoleRyi){
						double	wy=HoleRx*y/HoleRy;
						int	hm=sqrt((double)(HoleRx*HoleRx-wy*wy));

						int	X1h=ImagePosX-hm;
						int	X2h=ImagePosX+hm;
						X1h=min(X1h,XLen-1);
						X2h=max(X2h,0);

						if(PosiImage==true){
							for(int X=X1;X<=X1h;X++){
								SetBmpBitOnY1(d,X);
							}
							for(int X=X2h;X<=X2;X++){
								SetBmpBitOnY1(d,X);
							}
						}
						else{
							for(int X=X1;X<=X1h;X++){
								SetBmpBitOnY0(d,X);
							}
							for(int X=X2h;X<=X2;X++){
								SetBmpBitOnY0(d,X);
							}
						}
					}
					else{
						if(PosiImage==true){
							for(int X=X1;X<=X2;X++){
								SetBmpBitOnY1(d,X);
							}
						}
						else{
							for(int X=X1;X<=X2;X++){
								SetBmpBitOnY0(d,X);
							}
						}
					}

				}
			}
		}
	}
}

bool	IsInclude(double PosX[],double PosY[] ,int PosCount, FlexArea *b)
{
	if(PosCount==0)
		return false;
	double	MinX=PosX[0];
	double	MinY=PosY[0];
	double	MaxX=PosX[0];
	double	MaxY=PosY[0];
	for(int i=1;i<PosCount;i++){
		MinX=min(MinX,PosX[i]);
		MinY=min(MinY,PosY[i]);
		MaxX=max(MaxX,PosX[i]);
		MaxY=max(MaxY,PosY[i]);
	}
	if(::CheckOverlapRectRect((double)b->GetMinX(),(double)b->GetMinY(),(double)b->GetMaxX(),(double)b->GetMaxY()
							,MinX,MinY,MaxX,MaxY)==false)
		return false;

	for(int i=0;i<b->GetFLineLen();i++){
		int	Y=b->GetFLineAbsY(i);
		int	N=0;
		double	X[200];
		for(int j=0;j<PosCount-1;j++){
			if(GetCrossHalfInnerPoint(PosX[j],PosY[j],PosX[j+1],PosY[j+1],Y,X[N])==true)
				N++;
		}
		if(N==0)
			continue;
		
		double	sMinX=X[0];
		double	sMaxX=X[0];
		for(int j=1;j<N;j++){
			sMinX=min(sMinX,X[j]);
			sMaxX=max(sMaxX,X[j]);
		}
		int	X1=b->GetFLineLeftX(i);
		int	X2=X1+b->GetFLineNumb(i);
		if((sMinX<=X1 && X1<=sMaxX) || (sMinX<=X2 && X2<=sMaxX)
		|| (X1<=sMinX && sMinX<=X2) || (X1<=sMaxX && sMaxX<=X2)){
			return true;
		}
	}
	return false;
}


//============================================================

GerberDCodeBase::GerberDCodeBase(void)
{
	DCode=-1;
	Parent=NULL;
}

bool	GerberDCodeBase::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,DCode)==false)
		return false;
	if(Hole.Save(f)==false)
		return false;
	return true;
}

bool	GerberDCodeBase::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,DCode)==false)
		return false;
	if(Hole.Load(f)==false)
		return false;
	return true;
}

//================================================================

GerberDCodeCircle::GerberDCodeCircle(GerberDCodeContainer *parent)
{
	Parent=parent;
	HSize	=0.0;
	WSize	=0.0;
}

bool	GerberDCodeCircle::Save(QIODevice *f)
{
	if(GerberDCodeBase::Save(f)==false)
		return false;

	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,HSize)==false)
		return false;
	if(::Save(f,WSize)==false)
		return false;
	return true;
}

bool	GerberDCodeCircle::Load(QIODevice *f)
{
	if(GerberDCodeBase::Load(f)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,HSize)==false)
		return false;
	if(::Load(f,WSize)==false)
		return false;
	return true;
}
void	GerberDCodeCircle::Draw(double ImagePosX ,double ImagePosY 
								,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
								,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=(WSize*ZoomRateX)*0.5;
	double	Ry=(WSize*ZoomRateY)*0.5;
	if(-Ry<=ImagePosY && (ImagePosY-Ry)<pnt.height() && -Rx<=ImagePosX && (ImagePosX-Rx)<pnt.width()){
		if(Rx<=1.5 && Ry<=1.5){
			if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
				BYTE	*d=pnt.scanLine((int)ImagePosY);
				int	X=ImagePosX;
				if(pnt.depth()==32){
					*((QRgb *)&d[X<<2])=Col;
				}
				else if(pnt.depth()==8){
					d[X]=(BYTE)Col;
				}
			}
		}
		else{
			int	Ryi=Ry;
			if(Hole.HoleType==ApertureHole::_ApertureHole_None){
				for(int y=0;y<Ryi;y++){
					double	wy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-wy*wy));
					int	X1=ImagePosX-m;
					int	X2=ImagePosX+m;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					int	Y=ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X1;X<=X2;X++){
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
					Y=ImagePosY-y;
					if(0<=Y && Y<pnt.height()){
						BYTE	*d=pnt.scanLine(Y);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X1;X<=X2;X++){
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
			else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
				double	HoleRx=(Hole.GetWidth ()*ZoomRateX)*0.5;
				double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;
				int	HoleRyi=HoleRy;
				for(int y=0;y<Ryi;y++){
					double	gy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-gy*gy));
					if(y<=HoleRyi){
						double	wy=HoleRx*y/HoleRy;
						int	hm=sqrt((double)(HoleRx*HoleRx-wy*wy));

						int	X1=ImagePosX-m;
						int	X1h=ImagePosX-hm;
						int	X2h=ImagePosX+hm;
						int	X2=ImagePosX+m;
						X1=max(X1,0);
						X1h=min(X1h,pnt.width()-1);
						X2h=max(X2h,0);
						X2=min(X2,pnt.width()-1);

						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X1h;X++){
									*dp=Col;
									dp++;
								}
								dp=((QRgb *)&d[X2h<<2]);
								for(int X=X2h;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X1h;X++){
									d[X]=(BYTE)Col;
								}
								for(int X=X2h;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY-y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X1h;X++){
									*dp=Col;
									dp++;
								}
								dp=((QRgb *)&d[X2h<<2]);
								for(int X=X2h;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X1h;X++){
									d[X]=(BYTE)Col;
								}
								for(int X=X2h;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
					else{
						int	X1=ImagePosX-m;
						int	X2=ImagePosX+m;
						X1=max(X1,0);
						X2=min(X2,pnt.width()-1);

						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY-y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
			}
			else if(Hole.HoleType==ApertureHole::_ApertureHole_Rectangle){
				double	HoleW=(Hole.GetWidth ()*ZoomRateX)*0.5;
				double	HoleH=(Hole.GetHeight()*ZoomRateY)*0.5;
				int	HoleHi=HoleH;
				for(int y=0;y<Ryi;y++){
					double	gy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-gy*gy));
					if(y<=HoleHi){

						int	X1=ImagePosX-m;
						int	X1h=ImagePosX-HoleW;
						int	X2h=ImagePosX+HoleW;
						int	X2=ImagePosX+m;
						X1=max(X1,0);
						X1h=min(X1h,pnt.width()-1);
						X2h=max(X2h,0);
						X2=min(X2,pnt.width()-1);

						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X1h;X++){
									*dp=Col;
									dp++;
								}
								dp=((QRgb *)&d[X2h<<2]);
								for(int X=X2h;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X1h;X++){
									d[X]=(BYTE)Col;
								}
								for(int X=X2h;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY-y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X1h;X++){
									*dp=Col;
									dp++;
								}
								dp=((QRgb *)&d[X2h<<2]);
								for(int X=X2h;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X1h;X++){
									d[X]=(BYTE)Col;
								}
								for(int X=X2h;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
					else{
						int	X1=ImagePosX-m;
						int	X2=ImagePosX+m;
						X1=max(X1,0);
						X2=min(X2,pnt.width()-1);

						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY-y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
			}
		}
		//Hole.Draw(ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRate ,qRgb(0,0,0),Angle);
	}
}
void	GerberDCodeCircle::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,BYTE **Image ,int XByte ,int YLen
									,double Angle,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=WSize*ZoomRateY*0.5;
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	int	Ryi=Ry;
	int	XLen=XByte<<3;
	int	N=Ryi*2+1;
	if(Hole.HoleType==ApertureHole::_ApertureHole_None){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
			//for(int y=-Ri;y<=Ri;y++){
				int	y=-Ryi+i;
				int	Y=ImagePosY+y;
				if(0<=Y && Y<YLen){
					double	wy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-wy*wy));
					int	X1=ImagePosX-m;
					int	X2=ImagePosX+m;
					BYTE	*d=Image[Y];
					X1=max(X1,0);
					X2=min(X2,XLen-1);
					if(PosiImage==true){
						for(int X=X1;X<=X2;X++){
							SetBmpBitOnY1(d,X);
						}
					}
					else{
						for(int X=X1;X<=X2;X++){
							SetBmpBitOnY0(d,X);
						}
					}
				}
			}
		}
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
		double	HoleRx=(Hole.GetWidth ()*ZoomRateX)*0.5;
		double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;
		int	HoleRyi=HoleRy;
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				int	y=-Ryi+i;
				int	Y=ImagePosY+y;
				if(0<=Y && Y<YLen){
					double	gy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-gy*gy));
					int	X1=ImagePosX-m;
					int	X2=ImagePosX+m;
					BYTE	*d=Image[Y];
					X1=max(X1,0);
					X2=min(X2,XLen-1);
					if(-HoleRyi<=y && y<=HoleRyi){
						double	wy=HoleRx*y/HoleRy;
						int	hm=sqrt((double)(HoleRx*HoleRx-wy*wy));

						int	X1h=ImagePosX-hm;
						int	X2h=ImagePosX+hm;
						X1h=min(X1h,XLen-1);
						X2h=max(X2h,0);

						if(PosiImage==true){
							for(int X=X1;X<=X1h;X++){
								SetBmpBitOnY1(d,X);
							}
							for(int X=X2h;X<=X2;X++){
								SetBmpBitOnY1(d,X);
							}
						}
						else{
							for(int X=X1;X<=X1h;X++){
								SetBmpBitOnY0(d,X);
							}
							for(int X=X2h;X<=X2;X++){
								SetBmpBitOnY0(d,X);
							}
						}
					}
					else{
						if(PosiImage==true){
							for(int X=X1;X<=X2;X++){
								SetBmpBitOnY1(d,X);
							}
						}
						else{
							for(int X=X1;X<=X2;X++){
								SetBmpBitOnY0(d,X);
							}
						}
					}
				}
			}
		}
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Rectangle){
		double	HoleW=(Hole.GetWidth ()*ZoomRateX)*0.5;
		double	HoleH=(Hole.GetHeight()*ZoomRateX)*0.5;
		int	HoleHi=HoleH;
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				int	y=-Ryi+i;
				int	Y=ImagePosY+y;
				if(0<=Y && Y<YLen){
					double	gy=Rx*y/Ry;
					int	m=sqrt((double)(Rx*Rx-gy*gy));
					int	X1=ImagePosX-m;
					int	X2=ImagePosX+m;
					BYTE	*d=Image[Y];
					X1=max(X1,0);
					X2=min(X2,XLen-1);
					if(-HoleHi<=y && y<=HoleHi){
						int	X1h=ImagePosX-HoleW;
						int	X2h=ImagePosX+HoleW;
						X1h=min(X1h,XLen-1);
						X2h=max(X2h,0);

						if(PosiImage==true){
							for(int X=X1;X<=X1h;X++){
								SetBmpBitOnY1(d,X);
							}
							for(int X=X2h;X<=X2;X++){
								SetBmpBitOnY1(d,X);
							}
						}
						else{
							for(int X=X1;X<=X1h;X++){
								SetBmpBitOnY0(d,X);
							}
							for(int X=X2h;X<=X2;X++){
								SetBmpBitOnY0(d,X);
							}
						}
					}
					else{
						if(PosiImage==true){
							for(int X=X1;X<=X2;X++){
								SetBmpBitOnY1(d,X);
							}
						}
						else{
							for(int X=X1;X<=X2;X++){
								SetBmpBitOnY0(d,X);
							}
						}
					}
				}
			}
		}
	}
	//Hole.MakeImage(ImagePosX ,ImagePosY ,ZoomRate
	//								,Image ,XByte ,YLen ,Angle
	//								,PosiImage);
}

void	GerberDCodeCircle::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,OutlineArea &TransArea ,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	//double	Ry=WSize*ZoomRateY*0.5;
	for(int i=0;i<8;i++){
		double	x1,y1,x2,y2;
		MakeHairline(M_PI/4.0*i,x1,y1,x2,y2, HairlineLength,Rx);
		HairLineList	*H=new HairLineList();
		H->Position.x1	=ImagePosX+x1;
		H->Position.y1	=ImagePosY+y1;
		H->Position.x2	=ImagePosX+x2;
		H->Position.y2	=ImagePosY+y2;
		TransArea.HairLineContaner.AppendList(H);
	}
}
	
void	GerberDCodeCircle::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
										,SparsShape &OutlineShape
										,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)
{
	SparsArc	*a=new SparsArc();
	a->Cx	=ImagePosX;
	a->Cy	=ImagePosY;
	a->R	=WSize*ZoomRateX*0.5;
	a->StartAngle	=0;
	a->EndAngle		=2*M_PI;
	SparsOutline	*t=new SparsOutline();
	t->AppendList(a);
	OutlineShape.AppendList(t);
}

void	GerberDCodeCircle::MakeHairline(double Angle ,double &x1,double &y1,double &x2,double &y2, double HairlineLength ,double Radius)
{
	
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);

	double	px=Radius*CosS;
	double	py=Radius*SinS;
	x1=px-CosS*HairlineLength*0.5;
	y1=py-SinS*HairlineLength*0.5;
	x2=px+CosS*HairlineLength*0.5;
	y2=py+SinS*HairlineLength*0.5;
}

void	GerberDCodeCircle::MakeApertureInfo(struct	ApertureInfo &Info)
{

}
void	GerberDCodeCircle::SetApertureInfo(struct	ApertureInfo &Info)
{

}
bool	GerberDCodeCircle::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	if(hypot(PosX,PosY)<=GetWidth()*0.5*ZoomAperture){
		return true;
	}
	return false;
}
bool	GerberDCodeCircle::IsCrossed(FlexArea *b
									, double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	Rx=GetWidth()*0.5*ZoomAperture;
	double	Ry=GetHeight()*0.5*ZoomAperture;
	if(::CheckOverlapRectRect((double)b->GetMinX(),(double)b->GetMinY(),(double)b->GetMaxX(),(double)b->GetMaxY()
							,PosX-Rx ,PosY-Ry ,PosX+Rx ,PosY+Ry)==false)
		return false;
	for(int i=0;i<b->GetFLineLen();i++){
		int	Y=b->GetFLineAbsY(i);
		if(PosY-Ry<=Y && Y<=PosY+Ry){
			int	X1=b->GetFLineLeftX(i);
			int	X2=X1+b->GetFLineNumb(i);
			double	M=sqrt(Ry*Ry-(PosY-Y)*(PosY-Y));
			if((PosX-M<=X1 && X1<=PosX+M) || (PosX-M<=X2 && X2<=PosX+M)
			|| (X1<=PosX-M && PosX-M<=X2) || (X1<=PosX+M && PosX+M<=X2)){
				return true;
			}
		}
	}
	return false;
}
double	GerberDCodeCircle::GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	double	Rx=WSize*ZoomRateX*0.5;
	//double	Ry=WSize*ZoomRateY*0.5;

	if(Hole.HoleType==ApertureHole::_ApertureHole_None){
		return	GetCircleAreaSize(ImagePosX,ImagePosY ,Rx
						, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
		double	HoleRx=(Hole.GetWidth ()*ZoomRateX)*0.5;
		//double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;

		double	HoleArea=GetCircleAreaSize(ImagePosX,ImagePosY ,HoleRx
						, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		double	AArea	=GetCircleAreaSize(ImagePosX,ImagePosY ,Rx
						, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		return AArea-HoleArea;
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Rectangle){
		double	HoleW=(Hole.GetWidth ()*ZoomRateX)*0.5;
		double	HoleH=(Hole.GetHeight()*ZoomRateY)*0.5;

		double	HoleArea=GetRectangleAreaSize(ImagePosX-HoleW,ImagePosY-HoleH ,ImagePosX+HoleW,ImagePosY+HoleH
											, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		double	AArea	=GetCircleAreaSize(ImagePosX,ImagePosY ,Rx
						, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		return AArea-HoleArea;
	}
	else
		return 0;
}


//================================================================

GerberDCodeRectangle::GerberDCodeRectangle(GerberDCodeContainer *parent)
{
	Parent=parent;
	HSize	=0.0;
	WSize	=0.0;
}

bool	GerberDCodeRectangle::Save(QIODevice *f)
{
	if(GerberDCodeBase::Save(f)==false)
		return false;

	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,HSize)==false)
		return false;
	if(::Save(f,WSize)==false)
		return false;
	return true;
}

bool	GerberDCodeRectangle::Load(QIODevice *f)
{
	if(GerberDCodeBase::Load(f)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,HSize)==false)
		return false;
	if(::Load(f,WSize)==false)
		return false;
	return true;
}
void	GerberDCodeRectangle::Draw(double ImagePosX ,double ImagePosY 
									,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
									,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=((WSize*ZoomRateX)*0.5);
	double	Ry=((HSize*ZoomRateY)*0.5);
	if(0<=(ImagePosY+Ry) && (ImagePosY-Ry)<pnt.height() && 0<=(ImagePosX+Rx) && (ImagePosX-Rx)<pnt.width()){
		if(Rx<1.5 || Ry<=1.5){
			if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
				BYTE	*d=pnt.scanLine((int)ImagePosY);
				int	X=ImagePosX;
				if(pnt.depth()==32){
					*((QRgb *)&d[X<<2])=Col;
				}
				else if(pnt.depth()==8){
					d[X]=(BYTE)Col;
				}
			}
		}
		else{
			if(Angle==0){
				int	iRx=Rx;
				int	iRy=Ry;
				int	YNumb=iRy*2+1;
				if(Hole.HoleType==ApertureHole::_ApertureHole_None){
					for(int t=0;t<YNumb;t++){
						int	y=t-iRy;
						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX-iRx;
							int	X2=ImagePosX+iRx;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
				else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
					double	HoleRx=(Hole.GetWidth()*ZoomRateX)*0.5;
					double	HoleRy=(Hole.GetWidth()*ZoomRateY)*0.5;
					int	HoleRyi=HoleRy;
					for(int t=0;t<YNumb;t++){
						int	y=t-iRy;
						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX-iRx;
							int	X2=ImagePosX+iRx;
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							BYTE	*d=pnt.scanLine(Y);

							if(-HoleRyi<=y && y<=HoleRyi){
								double	wy=HoleRx*y/HoleRy;
								int	hm=sqrt((double)(HoleRx*HoleRx-wy*wy));
								int	X1h=ImagePosX-hm;
								int	X2h=ImagePosX+hm;
								X1h=min(X1h,pnt.width()-1);
								X2h=max(X2h,0);

								if(pnt.depth()==32){
									QRgb	*dp=((QRgb *)&d[X1<<2]);
									for(int X=X1;X<=X1h;X++){
										*dp=Col;
										dp++;
									}
									dp=((QRgb *)&d[X2h<<2]);
									for(int X=X2h;X<=X2;X++){
										*dp=Col;
										dp++;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X1h;X++){
										d[X]=(BYTE)Col;
									}
									for(int X=X2h;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}

							}
							else{
								if(pnt.depth()==32){
									QRgb	*dp=((QRgb *)&d[X1<<2]);
									for(int X=X1;X<=X2;X++){
										*dp=Col;
										dp++;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
				}
				else if(Hole.HoleType==ApertureHole::_ApertureHole_Rectangle){
					double	HoleW=(Hole.GetWidth ()*ZoomRateX)*0.5;
					double	HoleH=(Hole.GetHeight()*ZoomRateY)*0.5;
					int	HoleHi=HoleH;
					for(int t=0;t<YNumb;t++){
						int	y=t-iRy;
						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX-iRx;
							int	X2=ImagePosX+iRx;
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							BYTE	*d=pnt.scanLine(Y);

							if(-HoleHi<=y && y<=HoleHi){
								int	X1h=ImagePosX-HoleW;
								int	X2h=ImagePosX+HoleW;
								X1h=min(X1h,pnt.width()-1);
								X2h=max(X2h,0);

								if(pnt.depth()==32){
									QRgb	*dp=((QRgb *)&d[X1<<2]);
									for(int X=X1;X<=X1h;X++){
										*dp=Col;
										dp++;
									}
									dp=((QRgb *)&d[X2h<<2]);
									for(int X=X2h;X<=X2;X++){
										*dp=Col;
										dp++;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X1h;X++){
										d[X]=(BYTE)Col;
									}
									for(int X=X2h;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
							else{
								if(pnt.depth()==32){
									QRgb	*dp=((QRgb *)&d[X1<<2]);
									for(int X=X1;X<=X2;X++){
										*dp=Col;
										dp++;
									}
								}
								else if(pnt.depth()==8){
									for(int X=X1;X<=X2;X++){
										d[X]=(BYTE)Col;
									}
								}
							}
						}
					}
				}
			}
			else{
				double	PosX[5];
				double	PosY[5];
				double	CosS=cos(Angle);
				double	SinS=sin(Angle);
				PosX[0]=-Rx*CosS - Ry*SinS;
				PosY[0]= Rx*SinS - Ry*CosS;
				PosX[1]= Rx*CosS - Ry*SinS;
				PosY[1]=-Rx*SinS - Ry*CosS;
				PosX[2]= Rx*CosS + Ry*SinS;
				PosY[2]=-Rx*SinS + Ry*CosS;
				PosX[3]=-Rx*CosS + Ry*SinS;
				PosY[3]= Rx*SinS + Ry*CosS;
				PosX[4]=PosX[0];
				PosY[4]=PosY[0];
				DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
			}
		}
		//Hole.Draw(ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRate ,qRgb(0,0,0),Angle);
	}
}
void	GerberDCodeRectangle::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,BYTE **Image ,int XByte ,int YLen
									,double Angle,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS;
	PosY[0]= Rx*SinS - Ry*CosS;
	PosX[1]= Rx*CosS - Ry*SinS;
	PosY[1]=-Rx*SinS - Ry*CosS;
	PosX[2]= Rx*CosS + Ry*SinS;
	PosY[2]=-Rx*SinS + Ry*CosS;
	PosX[3]=-Rx*CosS + Ry*SinS;
	PosY[3]= Rx*SinS + Ry*CosS;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);

	//Hole.MakeImage(ImagePosX ,ImagePosY ,ZoomRate
	//				,Image ,XByte ,YLen ,Angle
	//				,PosiImage);
}
	
void	GerberDCodeRectangle::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS;
	PosY[0]= Rx*SinS - Ry*CosS;
	PosX[1]= Rx*CosS - Ry*SinS;
	PosY[1]=-Rx*SinS - Ry*CosS;
	PosX[2]= Rx*CosS + Ry*SinS;
	PosY[2]=-Rx*SinS + Ry*CosS;
	PosX[3]=-Rx*CosS + Ry*SinS;
	PosY[3]= Rx*SinS + Ry*CosS;	

	MakeHairline(PosX[0],PosY[0],PosX[1],PosY[1] ,TransArea,Isolation ,HairlineLength);
	MakeHairline(PosX[1],PosY[1],PosX[2],PosY[2] ,TransArea,Isolation ,HairlineLength);
	MakeHairline(PosX[2],PosY[2],PosX[3],PosY[3] ,TransArea,Isolation ,HairlineLength);
	MakeHairline(PosX[3],PosY[3],PosX[0],PosY[0] ,TransArea,Isolation ,HairlineLength);	
}
	
void	GerberDCodeRectangle::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
										,SparsShape &OutlineShape
										,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS;
	PosY[0]= Rx*SinS - Ry*CosS;
	PosX[1]= Rx*CosS - Ry*SinS;
	PosY[1]=-Rx*SinS - Ry*CosS;
	PosX[2]= Rx*CosS + Ry*SinS;
	PosY[2]=-Rx*SinS + Ry*CosS;
	PosX[3]=-Rx*CosS + Ry*SinS;
	PosY[3]= Rx*SinS + Ry*CosS;	

	SparsOutline	*t=new SparsOutline();
	SparsLine	*a1=new SparsLine();
	a1->X1	=ImagePosX + PosX[0];
	a1->Y1	=ImagePosY + PosY[0];
	a1->X2	=ImagePosX + PosX[1];
	a1->Y2	=ImagePosY + PosY[1];
	t->AppendList(a1);
	SparsLine	*a2=new SparsLine();
	a2->X1	=ImagePosX + PosX[1];
	a2->Y1	=ImagePosY + PosY[1];
	a2->X2	=ImagePosX + PosX[2];
	a2->Y2	=ImagePosY + PosY[2];
	t->AppendList(a2);
	SparsLine	*a3=new SparsLine();
	a3->X1	=ImagePosX + PosX[2];
	a3->Y1	=ImagePosY + PosY[2];
	a3->X2	=ImagePosX + PosX[3];
	a3->Y2	=ImagePosY + PosY[3];
	t->AppendList(a3);
	SparsLine	*a4=new SparsLine();
	a4->X1	=ImagePosX + PosX[3];
	a4->Y1	=ImagePosY + PosY[3];
	a4->X2	=ImagePosX + PosX[0];
	a4->Y2	=ImagePosY + PosY[0];
	t->AppendList(a4);
	OutlineShape.AppendList(t);
}

void	GerberDCodeRectangle::MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
										,OutlineArea &TransArea,double Isolation ,double HairlineLength)
{
	double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
	if(Len<5)
		return;
	double	Dx=(PosX2-PosX1)/Len;
	double	Dy=(PosY2-PosY1)/Len;
	int		N=Len/Isolation;
	if(N<2)
		N=2;
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	for(int i=0;i<LineCount;i++){
		HairLineList	*H=new HairLineList();
		double	Px=PosX1+Dx*(EdgeLen+Isolation*i);
		double	Py=PosY1+Dy*(EdgeLen+Isolation*i);
		H->Position.x1	=Px+HairlineLength*Dy*0.5;
		H->Position.y1	=Py-HairlineLength*Dx*0.5;
		H->Position.x2	=Px-HairlineLength*Dy*0.5;
		H->Position.y2	=Py+HairlineLength*Dx*0.5;
		TransArea.HairLineContaner.AppendList(H);
	}
}

void	GerberDCodeRectangle::MakeApertureInfo(struct	ApertureInfo &Info)
{
}
void	GerberDCodeRectangle::SetApertureInfo(struct	ApertureInfo &Info)
{
}
bool	GerberDCodeRectangle::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	Rx=((WSize*ZoomAperture)*0.5);
	double	Ry=((HSize*ZoomAperture)*0.5);
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	double	Px=PosX*CosS - PosY*SinS;
	double	Py=PosX*SinS + PosY*CosS;
	if(-Rx<=Px && Px<Rx && -Ry<=Py && Py<=Ry){
		return true;
	}
	return false;
}
bool	GerberDCodeRectangle::IsCrossed(FlexArea *b
									, double Cx,double Cy,	double Angle,double ZoomAperture)
{
	double	Rx=((WSize*ZoomAperture)*0.5);
	double	Ry=((HSize*ZoomAperture)*0.5);
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS +Cx;
	PosY[0]= Rx*SinS - Ry*CosS +Cy;
	PosX[1]= Rx*CosS - Ry*SinS +Cx;
	PosY[1]=-Rx*SinS - Ry*CosS +Cy;
	PosX[2]= Rx*CosS + Ry*SinS +Cx;
	PosY[2]=-Rx*SinS + Ry*CosS +Cy;
	PosX[3]=-Rx*CosS + Ry*SinS +Cx;
	PosY[3]= Rx*SinS + Ry*CosS +Cy;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	return ::IsInclude(PosX,PosY,5,b);
}

double	GerberDCodeRectangle::GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	double	ApertureW=WSize*ZoomRateX*0.5;
	double	ApertureH=HSize*ZoomRateY*0.5;

	double	ApertureArea=GetRectangleAreaSize(ImagePosX-ApertureW,ImagePosY-ApertureH ,ImagePosX+ApertureW,ImagePosY+ApertureH
										, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);

	if(Hole.HoleType==ApertureHole::_ApertureHole_None){
		return	ApertureArea;
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
		double	HoleRx=(Hole.GetWidth ()*ZoomRateX)*0.5;
		//double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;
		double	HoleArea=GetCircleAreaSize(ImagePosX,ImagePosY ,HoleRx
						, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		return ApertureArea-HoleArea;
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Rectangle){
		double	HoleW=(Hole.GetWidth ()*ZoomRateX)*0.5;
		double	HoleH=(Hole.GetHeight()*ZoomRateY)*0.5;

		double	HoleArea=GetRectangleAreaSize(ImagePosX-HoleW,ImagePosY-HoleH ,ImagePosX+HoleW,ImagePosY+HoleH
											, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		return ApertureArea-HoleArea;
	}
	else
		return 0;
}

//================================================================

GerberDCodeRectRCorner::GerberDCodeRectRCorner(GerberDCodeContainer *parent)
{
	Parent=parent;
	HSize	=0.0;
	WSize	=0.0;
	Radius	=0;
	Attr.Rounded	=false;
	Attr.TopRight	=true;
	Attr.TopLeft	=true;
	Attr.BottomLeft	=true;
	Attr.BottomRight=true;
}

bool	GerberDCodeRectRCorner::Save(QIODevice *f)
{
	if(GerberDCodeBase::Save(f)==false)
		return false;

	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,HSize)==false)
		return false;
	if(::Save(f,WSize)==false)
		return false;
	if(::Save(f,Radius)==false)
		return false;
	if(f->write((const char *)&Attr,sizeof(Attr))!=sizeof(Attr))
		return false;

	return true;
}

bool	GerberDCodeRectRCorner::Load(QIODevice *f)
{
	if(GerberDCodeBase::Load(f)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,HSize)==false)
		return false;
	if(::Load(f,WSize)==false)
		return false;
	if(::Load(f,Radius)==false)
		return false;
	if(f->read((char *)&Attr,sizeof(Attr))!=sizeof(Attr))
		return false;

	return true;
}
void	GerberDCodeRectRCorner::Draw(double ImagePosX ,double ImagePosY 
									,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
									,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=((WSize*ZoomRateX)*0.5);
	double	Ry=((HSize*ZoomRateY)*0.5);
	if(0<=(ImagePosY+Ry) && (ImagePosY-Ry)<pnt.height() && 0<=(ImagePosX+Rx) && (ImagePosX-Rx)<pnt.width()){
		if(Rx<1.5 || Ry<=1.5){
			if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
				BYTE	*d=pnt.scanLine((int)ImagePosY);
				int	X=ImagePosX;
				if(pnt.depth()==32){
					*((QRgb *)&d[X<<2])=Col;
				}
				else if(pnt.depth()==8){
					d[X]=(BYTE)Col;
				}
			}
		}
		else{
			if(Angle==0){
				int	iRx=Rx;
				int	iRy=Ry;

				int	YNumb=iRy*2+1;
				//#pragma omp parallel
				//{
				//	#pragma omp for
					//for(int y=-iRy;y<=iRy;y++){
					for(int t=0;t<YNumb;t++){
						int	y=t-iRy;
						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX-iRx;
							int	X2=ImagePosX+iRx;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				//}
			}
			else{
				double	PosX[5];
				double	PosY[5];
				double	CosS=cos(Angle);
				double	SinS=sin(Angle);
				PosX[0]=-Rx*CosS - Ry*SinS;
				PosY[0]= Rx*SinS - Ry*CosS;
				PosX[1]= Rx*CosS - Ry*SinS;
				PosY[1]=-Rx*SinS - Ry*CosS;
				PosX[2]= Rx*CosS + Ry*SinS;
				PosY[2]=-Rx*SinS + Ry*CosS;
				PosX[3]=-Rx*CosS + Ry*SinS;
				PosY[3]= Rx*SinS + Ry*CosS;
				PosX[4]=PosX[0];
				PosY[4]=PosY[0];
				DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
			}
		}
		//Hole.Draw(ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRate ,qRgb(0,0,0),Angle);
	}
}
void	GerberDCodeRectRCorner::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,BYTE **Image ,int XByte ,int YLen
									,double Angle,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS;
	PosY[0]= Rx*SinS - Ry*CosS;
	PosX[1]= Rx*CosS - Ry*SinS;
	PosY[1]=-Rx*SinS - Ry*CosS;
	PosX[2]= Rx*CosS + Ry*SinS;
	PosY[2]=-Rx*SinS + Ry*CosS;
	PosX[3]=-Rx*CosS + Ry*SinS;
	PosY[3]= Rx*SinS + Ry*CosS;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);

	//Hole.MakeImage(ImagePosX ,ImagePosY ,ZoomRate
	//				,Image ,XByte ,YLen ,Angle
	//				,PosiImage);
}
	
void	GerberDCodeRectRCorner::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS;
	PosY[0]= Rx*SinS - Ry*CosS;
	PosX[1]= Rx*CosS - Ry*SinS;
	PosY[1]=-Rx*SinS - Ry*CosS;
	PosX[2]= Rx*CosS + Ry*SinS;
	PosY[2]=-Rx*SinS + Ry*CosS;
	PosX[3]=-Rx*CosS + Ry*SinS;
	PosY[3]= Rx*SinS + Ry*CosS;	

	MakeHairline(PosX[0],PosY[0],PosX[1],PosY[1] ,TransArea,Isolation ,HairlineLength);
	MakeHairline(PosX[1],PosY[1],PosX[2],PosY[2] ,TransArea,Isolation ,HairlineLength);
	MakeHairline(PosX[2],PosY[2],PosX[3],PosY[3] ,TransArea,Isolation ,HairlineLength);
	MakeHairline(PosX[3],PosY[3],PosX[0],PosY[0] ,TransArea,Isolation ,HairlineLength);
	
}
	
void	GerberDCodeRectRCorner::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
										,SparsShape &OutlineShape
										,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS;
	PosY[0]= Rx*SinS - Ry*CosS;
	PosX[1]= Rx*CosS - Ry*SinS;
	PosY[1]=-Rx*SinS - Ry*CosS;
	PosX[2]= Rx*CosS + Ry*SinS;
	PosY[2]=-Rx*SinS + Ry*CosS;
	PosX[3]=-Rx*CosS + Ry*SinS;
	PosY[3]= Rx*SinS + Ry*CosS;	

	SparsOutline	*t=new SparsOutline();
	SparsLine	*a1=new SparsLine();
	a1->X1	=ImagePosX + PosX[0];
	a1->Y1	=ImagePosY + PosY[0];
	a1->X2	=ImagePosX + PosX[1];
	a1->Y2	=ImagePosY + PosY[1];
	t->AppendList(a1);
	SparsLine	*a2=new SparsLine();
	a2->X1	=ImagePosX + PosX[1];
	a2->Y1	=ImagePosY + PosY[1];
	a2->X2	=ImagePosX + PosX[2];
	a2->Y2	=ImagePosY + PosY[2];
	t->AppendList(a2);
	SparsLine	*a3=new SparsLine();
	a3->X1	=ImagePosX + PosX[2];
	a3->Y1	=ImagePosY + PosY[2];
	a3->X2	=ImagePosX + PosX[3];
	a3->Y2	=ImagePosY + PosY[3];
	t->AppendList(a3);
	SparsLine	*a4=new SparsLine();
	a4->X1	=ImagePosX + PosX[3];
	a4->Y1	=ImagePosY + PosY[3];
	a4->X2	=ImagePosX + PosX[0];
	a4->Y2	=ImagePosY + PosY[0];
	t->AppendList(a4);
	OutlineShape.AppendList(t);
}

void	GerberDCodeRectRCorner::MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
										,OutlineArea &TransArea,double Isolation ,double HairlineLength)
{
	double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
	if(Len<5)
		return;
	double	Dx=(PosX2-PosX1)/Len;
	double	Dy=(PosY2-PosY1)/Len;
	int		N=Len/Isolation;
	if(N<2)
		N=2;
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	for(int i=0;i<LineCount;i++){
		HairLineList	*H=new HairLineList();
		double	Px=PosX1+Dx*(EdgeLen+Isolation*i);
		double	Py=PosY1+Dy*(EdgeLen+Isolation*i);
		H->Position.x1	=Px+HairlineLength*Dy*0.5;
		H->Position.y1	=Py-HairlineLength*Dx*0.5;
		H->Position.x2	=Px-HairlineLength*Dy*0.5;
		H->Position.y2	=Py+HairlineLength*Dx*0.5;
		TransArea.HairLineContaner.AppendList(H);
	}
}

void	GerberDCodeRectRCorner::MakeApertureInfo(struct	ApertureInfo &Info)
{
}
void	GerberDCodeRectRCorner::SetApertureInfo(struct	ApertureInfo &Info)
{
}
bool	GerberDCodeRectRCorner::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	Rx=((WSize*ZoomAperture)*0.5);
	double	Ry=((HSize*ZoomAperture)*0.5);
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	double	Px=PosX*CosS - PosY*SinS;
	double	Py=PosX*SinS + PosY*CosS;
	if(-Rx<=Px && Px<Rx && -Ry<=Py && Py<=Ry){
		return true;
	}
	return false;
}
bool	GerberDCodeRectRCorner::IsCrossed(FlexArea *b
									, double Cx,double Cy,	double Angle,double ZoomAperture)
{
	double	Rx=((WSize*ZoomAperture)*0.5);
	double	Ry=((HSize*ZoomAperture)*0.5);
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	PosX[0]=-Rx*CosS - Ry*SinS +Cx;
	PosY[0]= Rx*SinS - Ry*CosS +Cy;
	PosX[1]= Rx*CosS - Ry*SinS +Cx;
	PosY[1]=-Rx*SinS - Ry*CosS +Cy;
	PosX[2]= Rx*CosS + Ry*SinS +Cx;
	PosY[2]=-Rx*SinS + Ry*CosS +Cy;
	PosX[3]=-Rx*CosS + Ry*SinS +Cx;
	PosY[3]= Rx*SinS + Ry*CosS +Cy;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	return ::IsInclude(PosX,PosY,5,b);
}

double	GerberDCodeRectRCorner::GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	double	ApertureW=WSize*ZoomRateX*0.5;
	double	ApertureH=HSize*ZoomRateY*0.5;

	double	ApertureArea=GetRectangleAreaSize(ImagePosX-ApertureW,ImagePosY-ApertureH ,ImagePosX+ApertureW,ImagePosY+ApertureH
										, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);

	double	CornerOutside=Radius*Radius*4-M_PI*Radius*Radius/4;

	if((Attr.Rounded==true || Attr.TopLeft==true) && CheckInsideRectangle(ClipX1 ,ClipY1 ,ClipX2 ,ClipY2
																		,ImagePosX-ApertureW ,ImagePosY-ApertureH)==true){
		ApertureArea-=CornerOutside;
	}
	if((Attr.Rounded==true || Attr.TopRight==true) && CheckInsideRectangle(ClipX1 ,ClipY1 ,ClipX2 ,ClipY2
																		,ImagePosX+ApertureW ,ImagePosY-ApertureH)==true){
		ApertureArea-=CornerOutside;
	}
	if((Attr.Rounded==true || Attr.BottomLeft==true) && CheckInsideRectangle(ClipX1 ,ClipY1 ,ClipX2 ,ClipY2
																		,ImagePosX-ApertureW ,ImagePosY+ApertureH)==true){
		ApertureArea-=CornerOutside;
	}
	if((Attr.Rounded==true || Attr.BottomRight==true) && CheckInsideRectangle(ClipX1 ,ClipY1 ,ClipX2 ,ClipY2
																		,ImagePosX+ApertureW ,ImagePosY+ApertureH)==true){
		ApertureArea-=CornerOutside;
	}

	if(Hole.HoleType==ApertureHole::_ApertureHole_None){
		return	ApertureArea;
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Circle){
		double	HoleRx=(Hole.GetWidth ()*ZoomRateX)*0.5;
		//double	HoleRy=(Hole.GetHeight()*ZoomRateY)*0.5;
		double	HoleArea=GetCircleAreaSize(ImagePosX,ImagePosY ,HoleRx
						, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		return ApertureArea-HoleArea;
	}
	else if(Hole.HoleType==ApertureHole::_ApertureHole_Rectangle){
		double	HoleW=(Hole.GetWidth ()*ZoomRateX)*0.5;
		double	HoleH=(Hole.GetHeight()*ZoomRateY)*0.5;

		double	HoleArea=GetRectangleAreaSize(ImagePosX-HoleW,ImagePosY-HoleH ,ImagePosX+HoleW,ImagePosY+HoleH
											, ClipX1 ,ClipY1 ,ClipX2 ,ClipY2);
		return ApertureArea-HoleArea;
	}
	else
		return 0;
}

//================================================================

GerberDCodeObround::GerberDCodeObround(GerberDCodeContainer *parent)
{
	Parent=parent;
	HSize	=0.0;
	WSize	=0.0;
}

bool	GerberDCodeObround::Save(QIODevice *f)
{
	if(GerberDCodeBase::Save(f)==false)
		return false;

	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,HSize)==false)
		return false;
	if(::Save(f,WSize)==false)
		return false;
	return true;
}

bool	GerberDCodeObround::Load(QIODevice *f)
{
	if(GerberDCodeBase::Load(f)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,HSize)==false)
		return false;
	if(::Load(f,WSize)==false)
		return false;
	return true;
}
void	GerberDCodeObround::Draw(double ImagePosX ,double ImagePosY 
								,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
								,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=(WSize*ZoomRateX)*0.5;
	double	Ry=(HSize*ZoomRateY)*0.5;
	double	L=hypot(Rx,Ry);
	if(0<=(ImagePosY+L) && (ImagePosY-L)<pnt.height() && 0<=(ImagePosX+L) && (ImagePosX-L)<pnt.width()){
		if(Rx<1.5 || Ry<=1.5){
			if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
				BYTE	*d=pnt.scanLine((int)ImagePosY);
				int	X=ImagePosX;
				if(pnt.depth()==32){
					*((QRgb *)&d[X<<2])=Col;
				}
				else if(pnt.depth()==8){
					d[X]=(BYTE)Col;
				}
			}
		}
		else{
			int	Rix=Rx;
			int	Riy=Ry;
			if(Rx>=Ry){
				if(Angle==0.0){
					for(int y=-Riy;y<=Riy;y++){
						int	Y=ImagePosY+y;
						if(0<=Y && Y<pnt.height()){
							int	m=sqrt((double)(Ry*Ry-y*y));
							int	X1=ImagePosX-Rx+Ry-m;
							int	X2=ImagePosX+Rx-Ry+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
								
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
				else{
					double	PosX[5];
					double	PosY[5];
					double	CosS=cos(Angle);
					double	SinS=sin(Angle);
					double	Mx=Rx-Ry;
					double	My=Ry;
					if(Mx<0)
						Mx=0;

					PosX[0]=-Mx*CosS - My*SinS;
					PosY[0]= Mx*SinS - My*CosS;
					PosX[1]= Mx*CosS - My*SinS;
					PosY[1]=-Mx*SinS - My*CosS;
					PosX[2]= Mx*CosS + My*SinS;
					PosY[2]=-Mx*SinS + My*CosS;
					PosX[3]=-Mx*CosS + My*SinS;
					PosY[3]= Mx*SinS + My*CosS;
					PosX[4]=PosX[0];
					PosY[4]=PosY[0];
					DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
					double	S1X=(PosX[1]+PosX[2])/2.0;
					double	S1Y=(PosY[1]+PosY[2])/2.0;
					double	S2X=(PosX[3]+PosX[4])/2.0;
					double	S2Y=(PosY[3]+PosY[4])/2.0;
					for(int y=-Riy;y<Riy;y++){
						int	Y=ImagePosY+S1Y+y;
						if(0<=Y && Y<pnt.height()){
							int	m=sqrt((double)(Ry*Ry-y*y));
							int	X1=ImagePosX+S1X-m;
							int	X2=ImagePosX+S1X+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
					for(int y=-Riy;y<=Riy;y++){
						int	Y=ImagePosY+S2Y+y;
						if(0<=Y && Y<pnt.height()){
							int	m=sqrt((double)(Ry*Ry-y*y));
							int	X1=ImagePosX+S2X-m;
							int	X2=ImagePosX+S2X+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
			}
			else{
				if(Angle==0.0){
					int	Ri=Rix;
					int	Y1=ImagePosY-Ry+Rx;
					int	Y2=ImagePosY+Ry-Rx;
					for(int y=0;y<=Ri;y++){
						int	m=sqrt((double)(Rx*Rx-y*y));
						int	X1=ImagePosX-m;
						int	X2=ImagePosX+m;
						X1=max(X1,0);
						X2=min(X2,pnt.width()-1);
								
						int	Y=Y1-y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=Y2+y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
					int	X1=ImagePosX-Ri;
					int	X2=ImagePosX+Ri;
					X1=max(X1,0);
					X2=min(X2,pnt.width()-1);
					for(int y=Y1;y<=Y2;y++){
						int	Y=y;
						if(0<=Y && Y<pnt.height()){
							BYTE	*d=pnt.scanLine(Y);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
				else{
					double	PosX[5];
					double	PosY[5];
					double	CosS=cos(Angle);
					double	SinS=sin(Angle);
					double	Mx=Rx;
					double	My=Ry-Rx;
					if(My<0)
						My=0;

					PosX[0]=-Mx*CosS - My*SinS;
					PosY[0]= Mx*SinS - My*CosS;
					PosX[1]= Mx*CosS - My*SinS;
					PosY[1]=-Mx*SinS - My*CosS;
					PosX[2]= Mx*CosS + My*SinS;
					PosY[2]=-Mx*SinS + My*CosS;
					PosX[3]=-Mx*CosS + My*SinS;
					PosY[3]= Mx*SinS + My*CosS;
					PosX[4]=PosX[0];
					PosY[4]=PosY[0];
					DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
					double	S1X=(PosX[0]+PosX[1])/2.0;
					double	S1Y=(PosY[0]+PosY[1])/2.0;
					double	S2X=(PosX[2]+PosX[3])/2.0;
					double	S2Y=(PosY[2]+PosY[3])/2.0;

					for(int y=0;y<Rix;y++){
						int	Y=ImagePosY+S1Y+y;
						int	m=sqrt((double)(Rx*Rx-y*y));
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX+S1X-m;
							int	X2=ImagePosX+S1X+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY+S1Y-y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX+S1X-m;
							int	X2=ImagePosX+S1X+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY+S2Y+y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX+S2X-m;
							int	X2=ImagePosX+S2X+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
						Y=ImagePosY+S2Y-y;
						if(0<=Y && Y<pnt.height()){
							int	X1=ImagePosX+S2X-m;
							int	X2=ImagePosX+S2X+m;
							BYTE	*d=pnt.scanLine(Y);
							X1=max(X1,0);
							X2=min(X2,pnt.width()-1);
							if(pnt.depth()==32){
								QRgb	*dp=((QRgb *)&d[X1<<2]);
								for(int X=X1;X<=X2;X++){
									//*((QRgb *)&d[X<<2])=Col;
									*dp=Col;
									dp++;
								}
							}
							else if(pnt.depth()==8){
								for(int X=X1;X<=X2;X++){
									d[X]=(BYTE)Col;
								}
							}
						}
					}
				}
			}
		}
		Hole.Draw(ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,qRgb(0,0,0),Angle);
	}
}

void	GerberDCodeObround::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,BYTE **Image ,int XByte ,int YLen
									,double Angle,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	int	XLen=XByte<<3;
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;
	int	Rix=Rx;
	int	Riy=Ry;

	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);

	if(Rx>=Ry){
		double	Mx=Rx-Ry;
		double	My=Ry;
		if(Mx<0)
			Mx=0;

		PosX[0]=-Mx*CosS - My*SinS;
		PosY[0]= Mx*SinS - My*CosS;
		PosX[1]= Mx*CosS - My*SinS;
		PosY[1]=-Mx*SinS - My*CosS;
		PosX[2]= Mx*CosS + My*SinS;
		PosY[2]=-Mx*SinS + My*CosS;
		PosX[3]=-Mx*CosS + My*SinS;
		PosY[3]= Mx*SinS + My*CosS;
		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);

		double	S1X=(PosX[1]+PosX[2])/2.0;
		double	S1Y=(PosY[1]+PosY[2])/2.0;
		double	S2X=(PosX[3]+PosX[4])/2.0;
		double	S2Y=(PosY[3]+PosY[4])/2.0;
		for(int y=-Riy;y<Riy;y++){
			int	m=sqrt((double)(Ry*Ry-y*y));
			int	Y1=ImagePosY+S1Y+y;
			if(0<=Y1 && Y1<YLen){
				int	X1=ImagePosX+S1X-m;
				int	X2=ImagePosX+S1X+m;
				BYTE	*d=Image[Y1];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
			int	Y2=ImagePosY+S2Y+y;
			if(0<=Y2 && Y2<YLen){
				int	X1=ImagePosX+S2X-m;
				int	X2=ImagePosX+S2X+m;
				BYTE	*d=Image[Y2];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
		}
	}
	else{
		double	Mx=Rx;
		double	My=Ry-Rx;
		if(My<0)
			My=0;

		PosX[0]=-Mx*CosS - My*SinS;
		PosY[0]= Mx*SinS - My*CosS;
		PosX[1]= Mx*CosS - My*SinS;
		PosY[1]=-Mx*SinS - My*CosS;
		PosX[2]= Mx*CosS + My*SinS;
		PosY[2]=-Mx*SinS + My*CosS;
		PosX[3]=-Mx*CosS + My*SinS;
		PosY[3]= Mx*SinS + My*CosS;
		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);

		double	S1X=(PosX[0]+PosX[1])/2.0;
		double	S1Y=(PosY[0]+PosY[1])/2.0;
		double	S2X=(PosX[2]+PosX[3])/2.0;
		double	S2Y=(PosY[2]+PosY[3])/2.0;
		for(int y=-Rix;y<Rix;y++){
			int	m=sqrt((double)(Rx*Rx-y*y));
			int	Y1=ImagePosY+S1Y+y;
			if(0<=Y1 && Y1<YLen){
				int	X1=ImagePosX+S1X-m;
				int	X2=ImagePosX+S1X+m;
				BYTE	*d=Image[Y1];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
			int	Y2=ImagePosY+S2Y+y;
			if(0<=Y2 && Y2<YLen){
				int	X1=ImagePosX+S2X-m;
				int	X2=ImagePosX+S2X+m;
				BYTE	*d=Image[Y2];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
		}
	}
	//Hole.MakeImage(ImagePosX ,ImagePosY ,ZoomRate
	//				,Image ,XByte ,YLen ,Angle
	//				,PosiImage);
}
	
void	GerberDCodeObround::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
					,OutlineArea &TransArea,double Isolation ,double HairlineLength
					,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
					,bool PosiImage)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;

	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);

	if(Rx>=Ry){
		double	Mx=Rx-Ry;
		double	My=Ry;

		PosX[0]=-Mx*CosS - My*SinS;
		PosY[0]= Mx*SinS - My*CosS;
		PosX[1]= Mx*CosS - My*SinS;
		PosY[1]=-Mx*SinS - My*CosS;
		PosX[2]= Mx*CosS + My*SinS;
		PosY[2]=-Mx*SinS + My*CosS;
		PosX[3]=-Mx*CosS + My*SinS;
		PosY[3]= Mx*SinS + My*CosS;

		MakeHairline(PosX[0],PosY[0],PosX[1],PosY[1] ,TransArea,Isolation ,HairlineLength);

		double	Radius=hypot(PosX[2]-PosX[1],PosY[2]-PosY[1])/2.0;
		double	S1X=(PosX[1]+PosX[2])/2.0;
		double	S1Y=(PosY[1]+PosY[2])/2.0;
		double	S1=GetSita(PosX[0]-PosX[1],PosY[0]-PosY[1]);
		for(int i=0;i<8;i++){
			double	x1,y1,x2,y2;
			double	c=RegulateAngle(M_PI/4*i+Angle+M_PI/4);
			double	df=DiffSita(S1,c);
			if(df>50.0/360.0*2*M_PI){
				MakeHairline(c,x1,y1,x2,y2, HairlineLength ,Radius);
				HairLineList	*H=new HairLineList();
				H->Position.x1=x1+S1X;
				H->Position.y1=y1+S1Y;
				H->Position.x2=x2+S1X;
				H->Position.y2=y2+S1Y;
				TransArea.HairLineContaner.AppendList(H);
			}
		}
		MakeHairline(PosX[2],PosY[2],PosX[3],PosY[3] ,TransArea,Isolation ,HairlineLength);
		double	S2X=(PosX[3]+PosX[0])/2.0;
		double	S2Y=(PosY[3]+PosY[0])/2.0;
		double	S2=GetSita(PosX[2]-PosX[3],PosY[2]-PosY[3]);
		for(int i=0;i<8;i++){
			double	x1,y1,x2,y2;
			double	c=RegulateAngle(M_PI/4*i+Angle+M_PI/4);
			double	df=DiffSita(S2,c);
			if(df>50.0/360.0*2*M_PI){
				MakeHairline(c,x1,y1,x2,y2, HairlineLength ,Radius);
				HairLineList	*H=new HairLineList();
				H->Position.x1=x1+S2X;
				H->Position.y1=y1+S2Y;
				H->Position.x2=x2+S2X;
				H->Position.y2=y2+S2Y;
				TransArea.HairLineContaner.AppendList(H);
			}
		}
	}
	else{
		double	Mx=Rx;
		double	My=Ry-Rx;

		PosX[0]=-Mx*CosS - My*SinS;
		PosY[0]= Mx*SinS - My*CosS;
		PosX[1]= Mx*CosS - My*SinS;
		PosY[1]=-Mx*SinS - My*CosS;
		PosX[2]= Mx*CosS + My*SinS;
		PosY[2]=-Mx*SinS + My*CosS;
		PosX[3]=-Mx*CosS + My*SinS;
		PosY[3]= Mx*SinS + My*CosS;

		MakeHairline(PosX[1],PosY[1],PosX[2],PosY[2] ,TransArea,Isolation ,HairlineLength);

		double	Radius=hypot(PosX[1]-PosX[0],PosY[1]-PosY[0])/2.0;
		double	S1X=(PosX[0]+PosX[1])/2.0;
		double	S1Y=(PosY[0]+PosY[1])/2.0;
		double	S1=GetSita(PosX[1]-PosX[2],PosY[1]-PosY[2]);
		for(int i=0;i<8;i++){
			double	x1,y1,x2,y2;
			double	c=RegulateAngle(M_PI/4*i+Angle+M_PI/4);
			double	df=DiffSita(S1,c);
			if(df>50.0/360.0*2*M_PI){
				MakeHairline(c,x1,y1,x2,y2, HairlineLength ,Radius);
				HairLineList	*H=new HairLineList();
				H->Position.x1=x1+S1X;
				H->Position.y1=y1+S1Y;
				H->Position.x2=x2+S1X;
				H->Position.y2=y2+S1Y;
				TransArea.HairLineContaner.AppendList(H);
			}
		}
		MakeHairline(PosX[3],PosY[3],PosX[0],PosY[0] ,TransArea,Isolation ,HairlineLength);
		double	S2X=(PosX[2]+PosX[3])/2.0;
		double	S2Y=(PosY[2]+PosY[3])/2.0;
		double	S2=GetSita(PosX[3]-PosX[0],PosY[3]-PosY[0]);
		for(int i=0;i<8;i++){
			double	x1,y1,x2,y2;
			double	c=RegulateAngle(M_PI/4*i+Angle+M_PI/4);
			double	df=DiffSita(S2,c);
			if(df>50.0/360.0*2*M_PI){
				MakeHairline(c,x1,y1,x2,y2, HairlineLength ,Radius);
				HairLineList	*H=new HairLineList();
				H->Position.x1=x1+S2X;
				H->Position.y1=y1+S2Y;
				H->Position.x2=x2+S2X;
				H->Position.y2=y2+S2Y;
				TransArea.HairLineContaner.AppendList(H);
			}
		}
	}
}
void	GerberDCodeObround::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
										,SparsShape &OutlineShape
										,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)
{
	double	Rx=WSize*ZoomRateX*0.5;
	double	Ry=HSize*ZoomRateY*0.5;

	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	SparsOutline	*t=new SparsOutline();

	if(Rx>=Ry){
		double	Mx=Rx-Ry;
		double	My=Ry;

		PosX[0]=-Mx*CosS - My*SinS;
		PosY[0]= Mx*SinS - My*CosS;
		PosX[1]= Mx*CosS - My*SinS;
		PosY[1]=-Mx*SinS - My*CosS;
		PosX[2]= Mx*CosS + My*SinS;
		PosY[2]=-Mx*SinS + My*CosS;
		PosX[3]=-Mx*CosS + My*SinS;
		PosY[3]= Mx*SinS + My*CosS;

		SparsLine	*a1=new SparsLine();
		a1->X1	= ImagePosX + PosX[0];
		a1->Y1	= ImagePosY + PosY[0];
		a1->X2	= ImagePosX + PosX[1];
		a1->Y2	= ImagePosY + PosY[1];
		t->AppendList(a1);

		double	Radius=hypot(PosX[2]-PosX[1],PosY[2]-PosY[1])/2.0;
		double	S1X=(PosX[1]+PosX[2])/2.0;
		double	S1Y=(PosY[1]+PosY[2])/2.0;
		double	S1=GetSita(PosX[1]-S1X,PosY[1]-S1Y);
		double	dx=PosX[1]-PosX[0];
		double	dy=PosY[1]-PosY[0];
		double	L=hypot(dx,dy);
		if(L<=0.0)
			return;
		dx/=L;
		dy/=L;
		double	hx=S1X+dx*Radius;
		double	hy=S1Y+dy*Radius;
		double	SC=RegulateAngle(GetSita(hx-S1X,hy-S1Y));
		double	S2=RegulateAngle(S1+M_PI);

		bool	Dir;
		if(S1<=S2){
			if(S1<=SC && SC<=S2){
				Dir=true;
			}
			else{
				Dir=false;
			}
		}
		else{
			if(S1<=SC || SC<=S2){
				Dir=true;
			}
			else{
				Dir=false;
			}
		}
		SparsArc	*a2=new SparsArc();
		a2->Cx	= ImagePosX + S1X;
		a2->Cy	= ImagePosY + S1Y;
		a2->R	=Radius;
		if(Dir==true){
			a2->StartAngle	=S1;
			a2->EndAngle	=S2;
		}
		else{
			a2->StartAngle	=S2;
			a2->EndAngle	=S1;
		}
		t->AppendList(a2);

		SparsLine	*a3=new SparsLine();
		a3->X1	= ImagePosX + PosX[2];
		a3->Y1	= ImagePosY + PosY[2];
		a3->X2	= ImagePosX + PosX[3];
		a3->Y2	= ImagePosY + PosY[3];
		t->AppendList(a3);

		double	S2X=(PosX[3]+PosX[0])/2.0;
		double	S2Y=(PosY[3]+PosY[0])/2.0;
		SparsArc	*a4=new SparsArc();
		a4->Cx	= ImagePosX + S2X;
		a4->Cy	= ImagePosY + S2Y;
		a4->R	=Radius;
		if(Dir==true){
			a4->StartAngle	=S2;
			a4->EndAngle	=S1;
		}
		else{
			a4->StartAngle	=S1;
			a4->EndAngle	=S2;
		}
		t->AppendList(a4);
	}
	else{
		double	Mx=Rx;
		double	My=Ry-Rx;

		PosX[0]=-Mx*CosS - My*SinS;
		PosY[0]= Mx*SinS - My*CosS;
		PosX[1]= Mx*CosS - My*SinS;
		PosY[1]=-Mx*SinS - My*CosS;
		PosX[2]= Mx*CosS + My*SinS;
		PosY[2]=-Mx*SinS + My*CosS;
		PosX[3]=-Mx*CosS + My*SinS;
		PosY[3]= Mx*SinS + My*CosS;

		SparsLine	*a1=new SparsLine();
		a1->X1	= ImagePosX + PosX[1];
		a1->Y1	= ImagePosY + PosY[1];
		a1->X2	= ImagePosX + PosX[2];
		a1->Y2	= ImagePosY + PosY[2];
		t->AppendList(a1);

		double	Radius=hypot(PosX[3]-PosX[2],PosY[3]-PosY[2])/2.0;
		double	S1X=(PosX[3]+PosX[2])/2.0;
		double	S1Y=(PosY[3]+PosY[2])/2.0;
		double	S1=GetSita(PosX[2]-S1X,PosY[2]-S1Y);
		double	dx=PosX[2]-PosX[1];
		double	dy=PosY[2]-PosY[1];
		double	L=hypot(dx,dy);
		if(L<=0.0)
			return;
		dx/=L;
		dy/=L;
		double	hx=S1X+dx*Radius;
		double	hy=S1Y+dy*Radius;
		double	SC=RegulateAngle(GetSita(hx-S1X,hy-S1Y));
		double	S2=RegulateAngle(S1+M_PI);

		bool	Dir;
		if(S1<=S2){
			if(S1<=SC && SC<=S2){
				Dir=true;
			}
			else{
				Dir=false;
			}
		}
		else{
			if(S1<=SC || SC<=S2){
				Dir=true;
			}
			else{
				Dir=false;
			}
		}
		SparsArc	*a2=new SparsArc();
		a2->Cx	= ImagePosX + S1X;
		a2->Cy	= ImagePosY + S1Y;
		a2->R	=Radius;
		if(Dir==true){
			a2->StartAngle	=S1;
			a2->EndAngle	=S2;
		}
		else{
			a2->StartAngle	=S2;
			a2->EndAngle	=S1;
		}
		t->AppendList(a2);

		SparsLine	*a3=new SparsLine();
		a3->X1	= ImagePosX + PosX[3];
		a3->Y1	= ImagePosY + PosY[3];
		a3->X2	= ImagePosX + PosX[0];
		a3->Y2	= ImagePosY + PosY[0];
		t->AppendList(a3);

		double	S2X=(PosX[1]+PosX[0])/2.0;
		double	S2Y=(PosY[1]+PosY[0])/2.0;
		SparsArc	*a4=new SparsArc();
		a4->Cx	= ImagePosX + S2X;
		a4->Cy	= ImagePosY + S2Y;
		a4->R	=Radius;
		if(Dir==true){
			a4->StartAngle	=S2;
			a4->EndAngle	=S1;
		}
		else{
			a4->StartAngle	=S1;
			a4->EndAngle	=S2;
		}
		t->AppendList(a4);
	}
	OutlineShape.AppendList(t);
}
void	GerberDCodeObround::MakeHairline(double Angle ,double &x1,double &y1,double &x2,double &y2, double HairlineLength ,double Radius)
{
	
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);

	double	px=Radius*CosS;
	double	py=Radius*SinS;
	x1=px-CosS*HairlineLength*0.5;
	y1=py-SinS*HairlineLength*0.5;
	x2=px+CosS*HairlineLength*0.5;
	y2=py+SinS*HairlineLength*0.5;
}

void	GerberDCodeObround::MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
										,OutlineArea &TransArea,double Isolation ,double HairlineLength)
{
	double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
	if(Len<5)
		return;
	double	Dx=(PosX2-PosX1)/Len;
	double	Dy=(PosY2-PosY1)/Len;
	int		N=Len/Isolation;
	if(N<2)
		N=2;
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	for(int i=0;i<LineCount;i++){
		HairLineList	*H=new HairLineList();
		double	Px=PosX1+Dx*(EdgeLen+Isolation*i);
		double	Py=PosY1+Dy*(EdgeLen+Isolation*i);
		H->Position.x1	=Px+HairlineLength*Dy*0.5;
		H->Position.y1	=Py-HairlineLength*Dx*0.5;
		H->Position.x2	=Px-HairlineLength*Dy*0.5;
		H->Position.y2	=Py+HairlineLength*Dx*0.5;
		TransArea.HairLineContaner.AppendList(H);
	}
}

void	GerberDCodeObround::MakeApertureInfo(struct	ApertureInfo &Info)
{
}
void	GerberDCodeObround::SetApertureInfo(struct	ApertureInfo &Info)
{
}
bool	GerberDCodeObround::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	Rx=(WSize*ZoomAperture)*0.5;
	double	Ry=(HSize*ZoomAperture)*0.5;
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	if(Rx>=Ry){
		double	Mx=Rx-Ry;
		double	My=Ry;
		if(Mx<0)
			Mx=0;
		double	CosS=cos(Angle);
		double	SinS=sin(Angle);
		double	Px=PosX*CosS - PosY*SinS;
		double	Py=PosX*SinS + PosY*CosS;
		if(-Mx<=Px && Px<Mx && -My<=Py && Py<=My){
			return true;
		}
		if(Px<0){
			if(hypot(Px+Mx,PosY)<=Ry)
				return true;
		}
		else if(Px>=0){
			if(hypot(Px-Mx,PosY)<=Ry)
				return true;
		}
	}
	else{
		double	Mx=Rx;
		double	My=Ry-Rx;
		if(My<0)
			My=0;
		double	CosS=cos(Angle);
		double	SinS=sin(Angle);
		double	Px=PosX*CosS - PosY*SinS;
		double	Py=PosX*SinS + PosY*CosS;
		if(-Mx<=Px && Px<Mx && -My<=Py && Py<=My){
			return true;
		}
		if(Px<0){
			if(hypot(Px+Mx,PosY)<=Rx)
				return true;
		}
		else if(Px>=0){
			if(hypot(Px-Mx,PosY)<=Rx)
				return true;
		}
	}
	return false;
}
bool	GerberDCodeObround::IsCrossed(FlexArea *b
									, double Cx,double Cy,	double Angle,double ZoomAperture)
{
	double	Rx=WSize*ZoomAperture*0.5;
	double	Ry=HSize*ZoomAperture*0.5;
	//int	Rix=Rx;
	//int	Riy=Ry;

	double	PosX[5];
	double	PosY[5];
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	if(Rx>=Ry){
		double	Mx=Rx-Ry;
		double	My=Ry;
		if(Mx<0)
			Mx=0;

		PosX[0]=-Mx*CosS - My*SinS +Cx;
		PosY[0]= Mx*SinS - My*CosS +Cy;
		PosX[1]= Mx*CosS - My*SinS +Cx;
		PosY[1]=-Mx*SinS - My*CosS +Cy;
		PosX[2]= Mx*CosS + My*SinS +Cx;
		PosY[2]=-Mx*SinS + My*CosS +Cy;
		PosX[3]=-Mx*CosS + My*SinS +Cx;
		PosY[3]= Mx*SinS + My*CosS +Cy;
		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		if(::IsInclude(PosX,PosY,5,b)==true)
			return true;

		/*	Write later
		double	S1X=(PosX[1]+PosX[2])/2.0;
		double	S1Y=(PosY[1]+PosY[2])/2.0;
		double	S2X=(PosX[3]+PosX[4])/2.0;
		double	S2Y=(PosY[3]+PosY[4])/2.0;
		for(int y=-Riy;y<Riy;y++){
			int	m=sqrt((double)(Ry*Ry-y*y));
			int	Y1=ImagePosY-S1Y+y;
			if(0<=Y1 && Y1<YLen){
				int	X1=ImagePosX+S1X-m;
				int	X2=ImagePosX+S1X+m;
				BYTE	*d=Image[Y1];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
			int	Y2=ImagePosY+S2Y+y;
			if(0<=Y2 && Y2<YLen){
				int	X1=ImagePosX+S2X-m;
				int	X2=ImagePosX+S2X+m;
				BYTE	*d=Image[Y2];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
		}
		*/
	}
	else{
		double	Mx=Rx;
		double	My=Ry-Rx;
		if(My<0)
			My=0;

		PosX[0]=-Mx*CosS - My*SinS +Cx;
		PosY[0]= Mx*SinS - My*CosS +Cy;
		PosX[1]= Mx*CosS - My*SinS +Cx;
		PosY[1]=-Mx*SinS - My*CosS +Cy;
		PosX[2]= Mx*CosS + My*SinS +Cx;
		PosY[2]=-Mx*SinS + My*CosS +Cy;
		PosX[3]=-Mx*CosS + My*SinS +Cx;
		PosY[3]= Mx*SinS + My*CosS +Cy;
		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		if(::IsInclude(PosX,PosY,5,b)==true)
			return true;

		/*	Write later
		double	S1X=(PosX[1]+PosX[2])/2.0;
		double	S1Y=(PosY[1]+PosY[2])/2.0;
		double	S2X=(PosX[3]+PosX[4])/2.0;
		double	S2Y=(PosY[3]+PosY[4])/2.0;
		for(int y=-Rix;y<Rix;y++){
			int	m=sqrt((double)(Ry*Ry-y*y));
			int	Y1=ImagePosY-S1Y+y;
			if(0<=Y1 && Y1<YLen){
				int	X1=ImagePosX+S1X-m;
				int	X2=ImagePosX+S1X+m;
				BYTE	*d=Image[Y1];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
			int	Y2=ImagePosY+S2Y+y;
			if(0<=Y2 && Y2<YLen){
				int	X1=ImagePosX+S2X-m;
				int	X2=ImagePosX+S2X+m;
				BYTE	*d=Image[Y2];
				X1=max(X1,0);
				X2=min(X2,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
		}
		*/
	}
	return false;
}
double	GerberDCodeObround::GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	return 0;
}

//================================================================

GerberDCodePolygon::GerberDCodePolygon(GerberDCodeContainer *parent)
{
	Parent=parent;
	Diameter	=0;
	Sides		=0;
}

bool	GerberDCodePolygon::Save(QIODevice *f)
{
	if(GerberDCodeBase::Save(f)==false)
		return false;

	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,Sides)==false)
		return false;
	return true;
}

bool	GerberDCodePolygon::Load(QIODevice *f)
{
	if(GerberDCodeBase::Load(f)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,Sides)==false)
		return false;
	return true;
}

double	GerberDCodePolygon::GetWidth(void)
{
	return Diameter;
}
double	GerberDCodePolygon::GetHeight(void)
{
	return Diameter;
}

void	GerberDCodePolygon::SetWidth(double w)
{
	Diameter	=w;
}

void	GerberDCodePolygon::SetHeight(double h)
{
}


void	GerberDCodePolygon::Draw(double ImagePosX ,double ImagePosY 
								,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
								,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=((Diameter*ZoomRateX)*0.5);
	if(Rx<1.0)
		Rx=1.0;
	double	Ry=((Diameter*ZoomRateY)*0.5);
	if(Ry<1.0)
		Ry=1.0;
	if(0<=(ImagePosY+Ry) && (ImagePosY-Ry)<pnt.height() && 0<=(ImagePosX+Rx) && (ImagePosX-Rx)<pnt.width()){
		if(Rx<1.5 && Ry<1.5){
			if(0<=ImagePosY && ImagePosY<pnt.height() && 0<=ImagePosX && ImagePosX<pnt.width()){
				BYTE	*d=pnt.scanLine((int)ImagePosY);
				int	X=ImagePosX;
				if(pnt.depth()==32){
					*((QRgb *)&d[X<<2])=Col;
				}
				else if(pnt.depth()==8){
					d[X]=(BYTE)Col;
				}
			}
		}
		else{
			double	PosX[500];
			double	PosY[500];
			double	RotateAngle=2*M_PI/Sides;
			for(int i=0;i<Sides;i++){
				double	CosS=cos(RotateAngle*i+Angle);
				double	SinS=sin(RotateAngle*i+Angle);
				PosX[i]= Rx*CosS + Ry*SinS;
				PosY[i]=-Rx*SinS + Ry*CosS;
			}
			PosX[Sides]=PosX[0];
			PosY[Sides]=PosY[0];
			DrawPolygon(PosX,PosY,Sides+1,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);

			Hole.Draw(ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,qRgb(0,0,0),Angle);
		}
	}
}
void	GerberDCodePolygon::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,BYTE **Image ,int XByte ,int YLen
									,double Angle,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	double	Rx=(Diameter*ZoomRateX*0.5);
	if(Rx<1.0)
		Rx=1.0;
	double	Ry=(Diameter*ZoomRateY*0.5);
	if(Ry<1.0)
		Ry=1.0;

	double	PosX[1000];
	double	PosY[1000];
	double	RotateAngle=2*M_PI/Sides;
	for(int i=0;i<Sides;i++){
		double	CosS=cos(RotateAngle*i+Angle);
		double	SinS=sin(RotateAngle*i+Angle);
		PosX[i]=ImagePosX+Rx*CosS + Ry*SinS;
		PosY[i]=ImagePosY-Rx*SinS + Ry*CosS;
	}
	PosX[Sides]=PosX[0];
	PosY[Sides]=PosY[0];
	MakeImagePolygon(PosX,PosY,Sides+1,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);

	//Hole.MakeImage(ImagePosX ,ImagePosY ,ZoomRate
	//				,Image ,XByte ,YLen ,Angle
	//				,PosiImage);
}
	
void	GerberDCodePolygon::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	double	Rx=(Diameter*ZoomRateX*0.5);
	double	Ry=(Diameter*ZoomRateY*0.5);

	double	PosX[1000];
	double	PosY[1000];
	double	RotateAngle=2*M_PI/Sides;
	for(int i=0;i<Sides;i++){
		double	CosS=cos(RotateAngle*i+Angle);
		double	SinS=sin(RotateAngle*i+Angle);
		PosX[i]=ImagePosX+Rx*CosS + Ry*SinS;
		PosY[i]=ImagePosY-Rx*SinS + Ry*CosS;
	}
	for(int i=0;i<Sides-1;i++){
		MakeHairline(PosX[i],PosY[i],PosX[i+1],PosY[i+1] ,TransArea,Isolation ,HairlineLength);
	}
	MakeHairline(PosX[Sides-1],PosY[Sides-1],PosX[0],PosY[0] ,TransArea,Isolation ,HairlineLength);
}
void	GerberDCodePolygon::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
										,SparsShape &OutlineShape
										,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)
{
	double	Rx=(Diameter*ZoomRateX*0.5);
	double	Ry=(Diameter*ZoomRateY*0.5);

	double	PosX[1000];
	double	PosY[1000];
	double	RotateAngle=2*M_PI/Sides;
	SparsOutline	*t=new SparsOutline();
	for(int i=0;i<Sides;i++){
		double	CosS=cos(RotateAngle*i+Angle);
		double	SinS=sin(RotateAngle*i+Angle);
		PosX[i]=Rx*CosS + Ry*SinS;
		PosY[i]=Rx*SinS + Ry*CosS;
	}

	for(int i=0;i<Sides;i++){
		SparsLine	*a=new SparsLine();
		a->X1	=ImagePosX + PosX[i];
		a->Y1	=ImagePosY + PosY[i];
		a->X2	=ImagePosX + PosX[(i<Sides-1)?i+1:0];
		a->Y2	=ImagePosY + PosY[(i<Sides-1)?i+1:0];
		t->AppendList(a);
	}
	OutlineShape.AppendList(t);
}
void	GerberDCodePolygon::MakeHairline(double PosX1,double PosY1,double PosX2,double PosY2 
										,OutlineArea &TransArea,double Isolation ,double HairlineLength)
{
	double	Len=hypot(PosX2-PosX1 ,PosY2-PosY1);
	if(Len<5)
		return;
	double	Dx=(PosX2-PosX1)/Len;
	double	Dy=(PosY2-PosY1)/Len;
	int		N=Len/Isolation;
	if(N<2)
		N=2;
	int	LineCount=N-1;
	double	EdgeLen=(Len-(LineCount-1)*Isolation)/2;
	for(int i=0;i<LineCount;i++){
		HairLineList	*H=new HairLineList();
		double	Px=PosX1+Dx*(EdgeLen+Isolation*i);
		double	Py=PosY1+Dy*(EdgeLen+Isolation*i);
		H->Position.x1	=Px+HairlineLength*Dy*0.5;
		H->Position.y1	=Py-HairlineLength*Dx*0.5;
		H->Position.x2	=Px-HairlineLength*Dy*0.5;
		H->Position.y2	=Py+HairlineLength*Dx*0.5;
		TransArea.HairLineContaner.AppendList(H);
	}
}
void	GerberDCodePolygon::MakeApertureInfo(struct	ApertureInfo &Info)
{
}
void	GerberDCodePolygon::SetApertureInfo(struct	ApertureInfo &Info)
{
}
bool	GerberDCodePolygon::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	R=((Diameter*ZoomAperture)*0.5);
	if(R<1.0)
		R=1.0;

	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	double	Px=PosX*CosS - PosY*SinS;
	double	Py=PosX*SinS + PosY*CosS;

	double	RotateAngle=2*M_PI/Sides;
	double	X[500];
	double	Y[500];
	for(int i=0;i<Sides;i++){
		double	CosS=cos(RotateAngle*i);
		double	SinS=sin(RotateAngle*i);
		X[i]= R*CosS + R*SinS;
		Y[i]=-R*SinS + R*CosS;
	}
	X[Sides]=X[0];
	Y[Sides]=Y[0];
	if(IsInside(Px, Py, X, Y ,Sides+1)==true)
		return true;
	return false;
}

bool	GerberDCodePolygon::IsCrossed(FlexArea *b
									, double Cx,double Cy,	double Angle,double ZoomAperture)
{
	double	R=((Diameter*ZoomAperture)*0.5);
	if(R<1.0)
		R=1.0;

	//double	CosS=cos(Angle);
	//double	SinS=sin(Angle);

	double	RotateAngle=2*M_PI/Sides;
	double	X[500];
	double	Y[500];
	for(int i=0;i<Sides;i++){
		double	CosS=cos(RotateAngle*i);
		double	SinS=sin(RotateAngle*i);
		X[i]= R*CosS + R*SinS;
		Y[i]=-R*SinS + R*CosS;
	}
	X[Sides]=X[0];
	Y[Sides]=Y[0];
	if(::IsInclude(X,Y,Sides,b)==true)
		return true;
	return false;
}
double	GerberDCodePolygon::GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	return 0;
}

//=============================================================================
GerberDCodeMacro::GerberDCodeMacro(GerberDCodeContainer *parent)
{
	Parent		=parent;
	Macro		=NULL;
}

bool	GerberDCodeMacro::Save(QIODevice *f)
{
	if(GerberDCodeBase::Save(f)==false)
		return false;

	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	QString	MacroName=Macro->MacroName;
	if(::Save(f,MacroName)==false)
		return false;
	if(Param.Save(f)==false)
		return false;
	if(InstMacro.Save(f)==false)
		return false;
	return true;
}
bool	GerberDCodeMacro::Load(QIODevice *f)
{
	if(GerberDCodeBase::Load(f)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	QString	MacroName;
	if(::Load(f,MacroName)==false)
		return false;
	Macro=Parent->FindMacro(MacroName);
	if(Macro==NULL)
		return false;
	if(Param.Load(f)==false)
		return false;
	if(InstMacro.Load(f)==false)
		return false;
	return true;
}
	
double	GerberDCodeMacro::GetWidth(void)
{
	return InstMacro.GetWidth();
}
double	GerberDCodeMacro::GetHeight(void)
{
	return InstMacro.GetHeight();
}
void	GerberDCodeMacro::SetWidth(double w)
{
	InstMacro.SetWidth(w);
}

void	GerberDCodeMacro::SetHeight(double h)
{
	InstMacro.SetHeight(h);
}

void	GerberDCodeMacro::Draw(double ImagePosX ,double ImagePosY 
								,QImage &pnt, int movx ,int movy ,double ZoomRateX,double ZoomRateY
								,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	InstMacro.Draw(ImagePosX ,ImagePosY 
								,pnt, movx ,movy , ZoomRateX, ZoomRateY 
								,Col,Angle ,ModeMirrorX ,ModeMirrorY
								,PosiImage
								,Hole);
}
void	GerberDCodeMacro::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,BYTE **Image ,int XByte ,int YLen
									,double Angle,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
	InstMacro.MakeImage(ImagePosX ,ImagePosY , ZoomRateX, ZoomRateY
									,Image ,XByte ,YLen
									,Angle,ModeMirrorX ,ModeMirrorY
									,PosiImage
									,Hole);
}
	
void	GerberDCodeMacro::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
									,OutlineArea &TransArea,double Isolation ,double HairlineLength
									,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
									,bool PosiImage)
{
}
void	GerberDCodeMacro::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
										,SparsShape &OutlineShape
										,double Angle ,bool ModeMirrorX ,bool ModeMirrorY)
{
}

void	GerberDCodeMacro::MakeApertureInfo(struct	ApertureInfo &Info)
{
}
void	GerberDCodeMacro::SetApertureInfo(struct	ApertureInfo &Info)
{
}
bool	GerberDCodeMacro::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	return InstMacro.IsInclude(PosX,PosY,Angle,ZoomAperture);
}
bool	GerberDCodeMacro::IsCrossed(FlexArea *b
									, double Cx,double Cy,	double Angle,double ZoomAperture)
{
	return false;
}
double	GerberDCodeMacro::GetAreaSize(double ImagePosX ,double ImagePosY ,double ZoomRateX,double ZoomRateY
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,double ClipX1 ,double ClipY1 ,double ClipX2 ,double ClipY2)
{
	return 0;
}

//=============================================================================

bool	GerberDCodeContainer::Save(QIODevice *f)
{
	int32	Ver=100001;
	if(::Save(f,Ver)==false)
		return false;

	int32	MacroNumb=Macros.GetCount();
	if(::Save(f,MacroNumb)==false)
		return false;
	for(GerberApertureMacro *m=Macros.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->Save(f)==false)
			return false;
	}

	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(GerberDCodeBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	ClassType=a->GetItemClassType();
		if(::Save(f,ClassType)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	GerberDCodeContainer::Load(QIODevice *f)
{
	RemoveAll();
	Macros.RemoveAll();
	return LoadWithoutClear(f);
}

bool	GerberDCodeContainer::LoadWithoutClear(QIODevice *f)
{
	int32	Ver=0;
	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=100001){
		int32	MacroNumb;
		if(::Load(f,MacroNumb)==false)
			return false;
		for(int i=0;i<MacroNumb;i++){
			GerberApertureMacro	*m=new GerberApertureMacro();
			if(m->Load(f)==false)
				return false;
			Macros.AppendList(m);
		}

		int32	N;
		if(::Load(f,N)==false)
			return false;
		for(int i=0;i<N;i++){
			int32	ClassType;
			if(::Load(f,ClassType)==false)
				return false;
			GerberDCodeBase	*a;
			switch(ClassType){
				case 1:
					a=new GerberDCodeCircle(this);
					break;
				case 2:
					a=new GerberDCodeRectangle(this);
					break;
				case 3:
					a=new GerberDCodeObround(this);
					break;
				case 4:
					a=new GerberDCodePolygon(this);
					break;
				case 5:
					a=new GerberDCodeMacro(this);
					break;
				default:
					a=NULL;
			}
			if(a!=NULL){
				if(a->Load(f)==false)
					return false;
				AppendList(a);
			}
		}
	}
	else{
		int32	N=Ver;

		//if(::Load(f,N)==false)
		//	return false;
		for(int i=0;i<N;i++){
			int32	ClassType;
			if(::Load(f,ClassType)==false)
				return false;
			GerberDCodeBase	*a;
			switch(ClassType){
				case 1:
					a=new GerberDCodeCircle(this);
					break;
				case 2:
					a=new GerberDCodeRectangle(this);
					break;
				case 3:
					a=new GerberDCodeObround(this);
					break;
				case 4:
					a=new GerberDCodePolygon(this);
					break;
				case 5:
					a=new GerberDCodeMacro(this);
					break;
				default:
					a=NULL;
			}
			if(a!=NULL){
				if(a->Load(f)==false)
					return false;
				AppendList(a);
			}
		}
	}
	return true;
}

GerberDCodeContainer	&GerberDCodeContainer::operator=(GerberDCodeContainer &src)
{
	QBuffer	Buff;

	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

GerberDCodeContainer	&GerberDCodeContainer::operator+=(GerberDCodeContainer &src)
{
	QBuffer	Buff;

	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	LoadWithoutClear(&Buff);
	return *this;
}

GerberDCodeBase	*GerberDCodeContainer::FindDCode(int dcode)
{
	for(GerberDCodeBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->DCode==dcode)
			return a;
	}
	return NULL;
}

GerberApertureMacro	*GerberDCodeContainer::FindMacro(const QString &MacroName)
{
	for(GerberApertureMacro *m=Macros.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->MacroName==MacroName){
			return m;
		}
	}
	return NULL;
}

QString	GerberDCodeContainer::GetApertureName(int ApertureClassID)
{
	switch(ApertureClassID){
	case 1:
		return "Circle";
	case 2:
		return "Rectangle";
	case 12:
		return "RectRCorner";
	case 3:
		return "Obround";
	case 4:
		return "Polygon";
	case 5:
		return "Macro";
	default:
		return "Unknown";
	}
}

