#include "XGerberApertureMacro.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XCrossObj.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include <float.h>


void	DrawPolygon(double *PosX,double *PosY,int PosCount
					,double ImagePosX ,double ImagePosY 
					,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
					,const QRgb &Col
					,ApertureHole &Hole);
void	MakeImagePolygon(double *PosX,double *PosY,int PosCount
					,double ImagePosX ,double ImagePosY 
					,BYTE **Image ,int XByte ,int YLen
					,bool PosiImage
					,double ZoomRateX ,double ZoomRateY
					,ApertureHole &Hole);
bool IsInside(double lX, double lY, double *plX, double *plY ,int nNum);

class	MacroParser
{
public:
	double	Value;
	int		ParamNumber;
	int		CType;
	/*
		0:double
		1:+
		2:-
		3:*
		4:/
		5:(
		6:)
		7:parameter
	*/
	MacroParser(void){	Value=0.0;	CType=0;	ParamNumber=0;	}
};

int	MakeParser(MacroParser	Parser[] ,QString &Str)
{
	QString	Number="0123456789";
	int	k;
	int	N=Str.count();
	int	Index=0;
	for(int i=0;i<N;){
		QChar	c=Str[i];
		if(c==QChar('+')){
			Parser[Index].CType=1;
			Index++;
			i++;
		}
		else if(c==QChar('-')){
			Parser[Index].CType=2;
			Index++;
			i++;
		}
		else if(c==QChar('*')){
			Parser[Index].CType=3;
			Index++;
			i++;
		}
		else if(c==QChar('/')){
			Parser[Index].CType=4;
			Index++;
			i++;
		}
		else if(c==QChar('(')){
			Parser[Index].CType=5;
			Index++;
			i++;
		}
		else if(c==QChar(')')){
			Parser[Index].CType=6;
			Index++;
			i++;
		}
		else if(c==QChar('$')){
			Parser[Index].CType=7;
			Parser[Index].ParamNumber=0;
			i++;
			if(i>=N)
				return false;
			while((k=Number.indexOf(c))>=0){
				Parser[Index].ParamNumber*=10;
				Parser[Index].ParamNumber+=k;
				i++;
				if(i>=N)
					return -1;
				c=Str[i];
			}
			Index++;
		}
		else if(c==QChar(' ')){
			i++;
		}
		else if(c==QChar('\t')){
			i++;
		}
		else if((k=Number.indexOf(c))>=0){
			Parser[Index].CType=0;
			Parser[Index].Value=0;
			while((k=Number.indexOf(c))>=0){
				Parser[Index].Value*=10.0;
				Parser[Index].Value+=k;
				i++;
				if(i>=N)
					return Index+1;
				c=Str[i];
			}
			if(c==QChar('.')){
				i++;
				if(i>=N)
					return Index+1;
				c=Str[i];
				double	FValue=1.0;
				while((k=Number.indexOf(c))>=0){
					FValue/=10.0;
					Parser[Index].Value+=k*FValue;
					i++;
					if(i>=N)
						return Index+1;
					c=Str[i];
				}
			}
			Index++;
		}
		else if(c==QChar('.')){
			Parser[Index].CType=0;
			Parser[Index].Value=0;
			i++;
			if(i>=N)
				return Index+1;
			double	FValue=1.0;
			c=Str[i];
			while((k=Number.indexOf(c))>=0){
				FValue/=10.0;
				Parser[Index].Value+=k*FValue;
				i++;
				if(i>=N)
					return Index+1;
				c=Str[i];
			}
			Index++;
		}
		else{
			break;
		}
	}
	return Index;
}

double	MacroGerberAperturePrimitiveBase::MakeValue(QString &Str ,DoubleList &Param)
{
	MacroParser	Parser[200];

	Str=Str.trimmed ();

	int	N=MakeParser(Parser ,Str);
	if(N<0)
		return 0.0;
	for(int i=0;i<N;i++){
		if(Parser[i].CType==7){
			Parser[i].Value=Param[Parser[i].ParamNumber];
			Parser[i].CType=0;
		}
	}
	for(;;){
		bool	Flag=false;
		for(int i=0;i<N-2;i++){
			if(Parser[i].CType==0 && Parser[i+1].CType==1 && Parser[i+2].CType==0){
				Parser[i].Value=Parser[i].Value+Parser[i+2].Value;
				for(int j=i+3;j<N;j++){
					Parser[j-2]=Parser[j];
				}
				N-=2;
				Flag=true;
				break;
			}
		}
		if(Flag==false){
			for(int i=0;i<N-2;i++){
				if(Parser[i].CType==0 && Parser[i+1].CType==2 && Parser[i+2].CType==0){
					Parser[i].Value=Parser[i].Value-Parser[i+2].Value;
					for(int j=i+3;j<N;j++){
						Parser[j-2]=Parser[j];
					}
					N-=2;
					Flag=true;
					break;
				}
			}
		}
		if(Flag==false){
			for(int i=0;i<N-2;i++){
				if(Parser[i].CType==0 && Parser[i+1].CType==3 && Parser[i+2].CType==0){
					Parser[i].Value=Parser[i].Value*Parser[i+2].Value;
					for(int j=i+3;j<N;j++){
						Parser[j-2]=Parser[j];
					}
					N-=2;
					Flag=true;
					break;
				}
			}
		}
		if(Flag==false){
			for(int i=0;i<N-2;i++){
				if(Parser[i].CType==0 && Parser[i+1].CType==4 && Parser[i+2].CType==0){
					if(Parser[i+2].Value==0.0){
						return 0.0;
					}
					Parser[i].Value=Parser[i].Value/Parser[i+2].Value;
					for(int j=i+3;j<N;j++){
						Parser[j-2]=Parser[j];
					}
					N-=2;
					Flag=true;
					break;
				}
			}
		}
		if(Flag==false){
			for(int i=0;i<N-2;i++){
				if(Parser[i].CType==5 && Parser[i+1].CType==0 && Parser[i+2].CType==6){
					Parser[i].Value=Parser[i+1].Value;
					Parser[i].CType=0;
					for(int j=i+3;j<N;j++){
						Parser[j-2]=Parser[j];
					}
					N-=2;
					Flag=true;
					break;
				}
			}
		}
		if(Flag==false){
			for(int i=0;i<N-1;i++){
				if(Parser[i].CType==1 && Parser[i+1].CType==0){
					Parser[i].Value=Parser[i+1].Value;
					Parser[i].CType=0;
					for(int j=i+2;j<N;j++){
						Parser[j-1]=Parser[j];
					}
					N--;
					Flag=true;
					break;
				}
			}
		}
		if(Flag==false){
			for(int i=0;i<N-1;i++){
				if(Parser[i].CType==2 && Parser[i+1].CType==0){
					Parser[i].Value=-Parser[i+1].Value;
					Parser[i].CType=0;
					for(int j=i+2;j<N;j++){
						Parser[j-1]=Parser[j];
					}
					N--;
					Flag=true;
					break;
				}
			}
		}
		if(Flag==false){
			if(N==1 && Parser[0].CType==0){
				return Parser[0].Value;
			}
			return 0.0;
		}
	}
}

//=============================================================================

bool	MacroGerberAperturePrimitiveCircle::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	return true;
}
bool	MacroGerberAperturePrimitiveCircle::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveCircle::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveCircle	*c=new InstGerberAperturePrimitiveCircle();
	c->Exposure	=MakeValue(Exposure,Param);
	c->Diameter	=MakeValue(Diameter,Param)*Unit;
	c->CenterX	=MakeValue(CenterX,Param)*Unit;
	c->CenterY	=MakeValue(CenterY,Param)*Unit;
	return c;
}
bool	MacroGerberAperturePrimitiveCircle::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<4)
		return false;
	Exposure=Param[0];
	Diameter=Param[1];
	CenterX	=Param[2];
	CenterY	=Param[3];
	Unit=_Unit;
	return true;
}
	
bool	InstGerberAperturePrimitiveCircle::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveCircle::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveCircle::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	double	R=Diameter/2.0;
	X1=CenterX-R;
	X2=CenterX+R;
	Y1=CenterY-R;
	Y2=CenterY+R;
	return true;
}

void	InstGerberAperturePrimitiveCircle::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if((Exposure==1 && PosiImage==false) || (Exposure==0 && PosiImage==true))
		Col=NegaColor.rgba();

	double	Rx=(Diameter*ZoomRateX)*0.5;
	double	Ry=(Diameter*ZoomRateY)*0.5;

	double	s=Angle;
	s=RegulateAngle(s);
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	RCx=( CenterX*CosS + CenterY*SinS);
	double	RCy=(-CenterX*SinS + CenterY*CosS);

	double	Px=RCx*ZoomRateX;
	double	Py=RCy*ZoomRateY;
	if(ModeMirrorX==true)
		Px=-Px;
	if(ModeMirrorY==true)
		Py=-Py;
	if((Py-Ry)<=ImagePosY && (Py+ImagePosY-Ry)<pnt.height() && (Px-Rx)<=ImagePosX && (Px+ImagePosX-Rx)<pnt.width()){
		if(Rx<=1.5 && Ry<=1.5){
			if(0<=(Py+ImagePosY) && (Py+ImagePosY)<pnt.height() && 0<=(Px+ImagePosX) && (Px+ImagePosX)<pnt.width()){
				BYTE	*d=pnt.scanLine((int)(Py+ImagePosY));
				int	X=Px+ImagePosX;
				if(pnt.depth()==32){
					*((QRgb *)&d[X<<2])=Col;
				}
				else if(pnt.depth()==8){
					d[X]=(BYTE)Col;
				}
			}
		}
		else{
			int	Rxi=Rx;
			int	Ryi=Ry;
			int	YNumb=Ryi+Ryi+1;
			//#pragma omp parallel
			//{
			//	#pragma omp for
				//for(int y=-Ri;y<=Ri;y++){
				for(int t=0;t<YNumb;t++){
					int	y=t-Ryi;
					int	Y=Py+ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						double	wy=y*Rx/Ry;
						int	m=sqrt((double)(Rx*Rx-wy*wy));
						int	X1=Px+ImagePosX-m;
						int	X2=Px+ImagePosX+m;
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
				//}
			}
		}
	}
}
void	InstGerberAperturePrimitiveCircle::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	if(Exposure==0)
		return;
	double	Rx=Diameter*ZoomRateX*0.5;
	double	Ry=Diameter*ZoomRateY*0.5;
	if(Rx<1.0)
		Rx=1.0;
	if(Ry<1.0)
		Ry=1.0;
	int	Rxi=Rx;
	int	Ryi=Ry;
	double	s=Angle;
	s=RegulateAngle(s);
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	RCx=( CenterX*CosS + CenterY*SinS);
	double	RCy=(-CenterX*SinS + CenterY*CosS);

	double	Px=RCx*ZoomRateX;
	double	Py=RCy*ZoomRateY;
	if(ModeMirrorX==true)
		Px=-Px;
	if(ModeMirrorY==true)
		Py=-Py;
	int	XLen=XByte<<3;
	int	N=Ryi*2+1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<N;i++){
		//for(int y=-Ri;y<=Ri;y++){
			int	y=-Ryi+i;
			int	Y=Py+ImagePosY+y;
			if(0<=Y && Y<YLen){
				double	wy=y*Rx/Ry;
				int	m=sqrt((double)(Rx*Rx-wy*wy));
				int	X1=Px+ImagePosX-m;
				int	X2=Px+ImagePosX+m;
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
bool	InstGerberAperturePrimitiveCircle::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	if(hypot(PosX-CenterX,PosY-CenterY)<=Diameter*0.5*ZoomAperture){
		return true;
	}
	return false;
}
//=============================================================================

bool	MacroGerberAperturePrimitiveLineVector::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,LineWidth)==false)
		return false;
	if(::Save(f,StartX)==false)
		return false;
	if(::Save(f,StartY)==false)
		return false;
	if(::Save(f,EndX)==false)
		return false;
	if(::Save(f,EndY)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	MacroGerberAperturePrimitiveLineVector::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,LineWidth)==false)
		return false;
	if(::Load(f,StartX)==false)
		return false;
	if(::Load(f,StartY)==false)
		return false;
	if(::Load(f,EndX)==false)
		return false;
	if(::Load(f,EndY)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveLineVector::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveLineVector	*c=new InstGerberAperturePrimitiveLineVector();
	c->Exposure	=MakeValue(Exposure,Param);
	c->LineWidth=MakeValue(LineWidth,Param)*Unit;
	c->StartX	=MakeValue(StartX,Param)*Unit;
	c->StartY	=MakeValue(StartY,Param)*Unit;
	c->EndX		=MakeValue(EndX,Param)*Unit;
	c->EndY		=MakeValue(EndY,Param)*Unit;
	c->Rotation	=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitiveLineVector::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<7)
		return false;
	Exposure	=Param[0];
	LineWidth	=Param[1];
	StartX		=Param[2];
	StartY		=Param[3];
	EndX		=Param[4];
	EndY		=Param[5];
	Rotation	=Param[6];
	Unit		=_Unit;
	return true;
}
bool	InstGerberAperturePrimitiveLineVector::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,LineWidth)==false)
		return false;
	if(::Save(f,StartX)==false)
		return false;
	if(::Save(f,StartY)==false)
		return false;
	if(::Save(f,EndX)==false)
		return false;
	if(::Save(f,EndY)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	InstGerberAperturePrimitiveLineVector::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,LineWidth)==false)
		return false;
	if(::Load(f,StartX)==false)
		return false;
	if(::Load(f,StartY)==false)
		return false;
	if(::Load(f,EndX)==false)
		return false;
	if(::Load(f,EndY)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveLineVector::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	double	Lx=EndX-StartX;
	double	Ly=EndY-StartY;
	double	L=hypot(Lx,Ly);
	if(L==0.0)
		return false;
	double	W=LineWidth/2.0;
	double	Vx=-Ly/L*W;
	double	Vy= Lx/L*W;
	double	x1=StartX+Vx;
	double	y1=StartY+Vy;
	double	x2=EndX+Vx;
	double	y2=EndY+Vy;
	double	x3=EndX-Vx;
	double	y3=EndY-Vy;
	double	x4=StartX-Vx;
	double	y4=StartY-Vy;
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	Mx1= x1*CosS + y1*SinS;
	double	My1=-x1*SinS + y1*CosS;
	double	Mx2= x2*CosS + y2*SinS;
	double	My2=-x2*SinS + y2*CosS;
	double	Mx3= x3*CosS + y3*SinS;
	double	My3=-x3*SinS + y3*CosS;
	double	Mx4= x4*CosS + y4*SinS;
	double	My4=-x4*SinS + y4*CosS;
	X1=min(min(Mx1,Mx2),min(Mx3,Mx4));
	Y1=min(min(My1,My2),min(My3,My4));
	X2=max(max(Mx1,Mx2),max(Mx3,Mx4));
	Y2=max(max(My1,My2),max(My3,My4));
	return true;
}
void	InstGerberAperturePrimitiveLineVector::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if((Exposure==1 && PosiImage==false) || (Exposure==0 && PosiImage==true))
		Col=NegaColor.rgba();

	double	RL=((hypot((EndX-StartX)*ZoomRateX,(EndY-StartY)*ZoomRateY))*0.5);
	double	RW=((LineWidth*ZoomRateX)*0.5);

	if(RL<1.5 || RW<=1.5){
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
		double	tStartX	=(ModeMirrorX==false)?StartX:-StartX;
		double	tStartY	=(ModeMirrorY==false)?StartY:-StartY;
		double	tEndX	=(ModeMirrorX==false)?EndX:-EndX;
		double	tEndY	=(ModeMirrorY==false)?EndY:-EndY;
	
		double	Lx=tEndX-tStartX;
		double	Ly=tEndY-tStartY;
		double	L=hypot(Lx,Ly);
		if(L==0.0)
			return;
		double	s=Rotation+Angle;
		s=RegulateAngle(s);
		double	W=LineWidth/2.0;
		double	Vx=-Ly/L*W;
		double	Vy= Lx/L*W;
		double	x1=tStartX+Vx;
		double	y1=tStartY+Vy;
		double	x2=tEndX+Vx;
		double	y2=tEndY+Vy;
		double	x3=tEndX-Vx;
		double	y3=tEndY-Vy;
		double	x4=tStartX-Vx;
		double	y4=tStartY-Vy;
		double	CosS=cos(s);
		double	SinS=sin(s);
		double	PosX[5];
		double	PosY[5];
		PosX[0]=( x1*CosS + y1*SinS)*ZoomRateX;
		PosY[0]=(-x1*SinS + y1*CosS)*ZoomRateY;
		PosX[1]=( x2*CosS + y2*SinS)*ZoomRateX;
		PosY[1]=(-x2*SinS + y2*CosS)*ZoomRateY;
		PosX[2]=( x3*CosS + y3*SinS)*ZoomRateX;
		PosY[2]=(-x3*SinS + y3*CosS)*ZoomRateY;
		PosX[3]=( x4*CosS + y4*SinS)*ZoomRateX;
		PosY[3]=(-x4*SinS + y4*CosS)*ZoomRateY;

		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
	}
}
void	InstGerberAperturePrimitiveLineVector::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	if(Exposure==0)
		return;
	double	tStartX	=(ModeMirrorX==false)?StartX:-StartX;
	double	tStartY	=(ModeMirrorY==false)?StartY:-StartY;
	double	tEndX	=(ModeMirrorX==false)?EndX:-EndX;
	double	tEndY	=(ModeMirrorY==false)?EndY:-EndY;
	
	double	Lx=tEndX-tStartX;
	double	Ly=tEndY-tStartY;
	double	L=hypot(Lx,Ly);
	if(L==0.0)
		return;
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	W=LineWidth/2.0;
	double	Vx=-Ly/L*W;
	double	Vy= Lx/L*W;
	double	x1=tStartX+Vx;
	double	y1=tStartY+Vy;
	double	x2=tEndX+Vx;
	double	y2=tEndY+Vy;
	double	x3=tEndX-Vx;
	double	y3=tEndY-Vy;
	double	x4=tStartX-Vx;
	double	y4=tStartY-Vy;
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	PosX[5];
	double	PosY[5];
	PosX[0]=( x1*CosS + y1*SinS)*ZoomRateX;
	PosY[0]=(-x1*SinS + y1*CosS)*ZoomRateY;
	PosX[1]=( x2*CosS + y2*SinS)*ZoomRateX;
	PosY[1]=(-x2*SinS + y2*CosS)*ZoomRateY;
	PosX[2]=( x3*CosS + y3*SinS)*ZoomRateX;
	PosY[2]=(-x3*SinS + y3*CosS)*ZoomRateY;
	PosX[3]=( x4*CosS + y4*SinS)*ZoomRateX;
	PosY[3]=(-x4*SinS + y4*CosS)*ZoomRateY;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);
}
bool	InstGerberAperturePrimitiveLineVector::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	Lx=EndX-StartX;
	double	Ly=EndY-StartY;
	double	L=hypot(Lx,Ly);
	if(L==0.0)
		return false;
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	W=LineWidth/2.0;
	double	Vx=-Ly/L*W;
	double	Vy= Lx/L*W;
	double	x1=StartX+Vx;
	double	y1=StartY+Vy;
	double	x2=EndX+Vx;
	double	y2=EndY+Vy;
	double	x3=EndX-Vx;
	double	y3=EndY-Vy;
	double	x4=StartX-Vx;
	double	y4=StartY-Vy;
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	gPosX[5];
	double	gPosY[5];
	gPosX[0]=( x1*CosS + y1*SinS)*ZoomAperture;
	gPosY[0]=(-x1*SinS + y1*CosS)*ZoomAperture;
	gPosX[1]=( x2*CosS + y2*SinS)*ZoomAperture;
	gPosY[1]=(-x2*SinS + y2*CosS)*ZoomAperture;
	gPosX[2]=( x3*CosS + y3*SinS)*ZoomAperture;
	gPosY[2]=(-x3*SinS + y3*CosS)*ZoomAperture;
	gPosX[3]=( x4*CosS + y4*SinS)*ZoomAperture;
	gPosY[3]=(-x4*SinS + y4*CosS)*ZoomAperture;
	gPosX[4]=gPosX[0];
	gPosY[4]=gPosY[0];

	return IsInside(PosX, PosY, gPosX, gPosY ,4);
}
//=============================================================================

bool	MacroGerberAperturePrimitiveLineCenter::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	MacroGerberAperturePrimitiveLineCenter::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,Height)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveLineCenter::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveLineCenter	*c=new InstGerberAperturePrimitiveLineCenter();
	c->Exposure	=MakeValue(Exposure,Param);
	c->Width	=MakeValue(Width,Param)*Unit;
	c->Height	=MakeValue(Height,Param)*Unit;
	c->CenterX	=MakeValue(CenterX,Param)*Unit;
	c->CenterY	=MakeValue(CenterY,Param)*Unit;
	c->Rotation	=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitiveLineCenter::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<6)
		return false;
	Exposure	=Param[0];
	Width		=Param[1];
	Height		=Param[2];
	CenterX		=Param[3];
	CenterY		=Param[4];
	Rotation	=Param[5];
	Unit		=_Unit;
	return true;
}
bool	InstGerberAperturePrimitiveLineCenter::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}
	
bool	InstGerberAperturePrimitiveLineCenter::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,Height)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveLineCenter::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	double	W=Width/2.0;
	double	H=Height/2.0;
	double	x1=CenterX-W;
	double	y1=CenterY-H;
	double	x2=CenterX+W;
	double	y2=CenterY-H;
	double	x3=CenterX+W;
	double	y3=CenterY+H;
	double	x4=CenterX-W;
	double	y4=CenterY+H;
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	Mx1= x1*CosS + y1*SinS;
	double	My1=-x1*SinS + y1*CosS;
	double	Mx2= x2*CosS + y2*SinS;
	double	My2=-x2*SinS + y2*CosS;
	double	Mx3= x3*CosS + y3*SinS;
	double	My3=-x3*SinS + y3*CosS;
	double	Mx4= x4*CosS + y4*SinS;
	double	My4=-x4*SinS + y4*CosS;
	X1=min(min(Mx1,Mx2),min(Mx3,Mx4));
	Y1=min(min(My1,My2),min(My3,My4));
	X2=max(max(Mx1,Mx2),max(Mx3,Mx4));
	Y2=max(max(My1,My2),max(My3,My4));
	return true;
}
void	InstGerberAperturePrimitiveLineCenter::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if((Exposure==1 && PosiImage==false) || (Exposure==0 && PosiImage==true))
		Col=NegaColor.rgba();

	double	Rx=((Width*ZoomRateX)*0.5);
	double	Ry=((Height*ZoomRateY)*0.5);

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
		double	tCenterX=CenterX;
		double	tCenterY=CenterY;
		if(ModeMirrorX==true)
			tCenterX=-tCenterX;
		if(ModeMirrorY==true)
			tCenterY=-tCenterY;
		double	s=Rotation+Angle;
		s=RegulateAngle(s);
		double	W=Width/2.0;
		double	H=Height/2.0;
		double	x1=tCenterX-W;
		double	y1=tCenterY-H;
		double	x2=tCenterX+W;
		double	y2=tCenterY-H;
		double	x3=tCenterX+W;
		double	y3=tCenterY+H;
		double	x4=tCenterX-W;
		double	y4=tCenterY+H;
		double	CosS=cos(s);
		double	SinS=sin(s);
		double	PosX[5];
		double	PosY[5];
		PosX[0]=( x1*CosS + y1*SinS)*ZoomRateX;
		PosY[0]=(-x1*SinS + y1*CosS)*ZoomRateY;
		PosX[1]=( x2*CosS + y2*SinS)*ZoomRateX;
		PosY[1]=(-x2*SinS + y2*CosS)*ZoomRateY;
		PosX[2]=( x3*CosS + y3*SinS)*ZoomRateX;
		PosY[2]=(-x3*SinS + y3*CosS)*ZoomRateY;
		PosX[3]=( x4*CosS + y4*SinS)*ZoomRateX;
		PosY[3]=(-x4*SinS + y4*CosS)*ZoomRateY;
		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
	}
}
void	InstGerberAperturePrimitiveLineCenter::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	if(Exposure==0)
		return;
	double	tCenterX=CenterX;
	double	tCenterY=CenterY;
	if(ModeMirrorX==true)
		tCenterX=-tCenterX;
	if(ModeMirrorY==true)
		tCenterY=-tCenterY;
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	W=Width/2.0;
	double	H=Height/2.0;
	double	x1=tCenterX-W;
	double	y1=tCenterY-H;
	double	x2=tCenterX+W;
	double	y2=tCenterY-H;
	double	x3=tCenterX+W;
	double	y3=tCenterY+H;
	double	x4=tCenterX-W;
	double	y4=tCenterY+H;
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	PosX[5];
	double	PosY[5];
	PosX[0]=( x1*CosS + y1*SinS)*ZoomRateX;
	PosY[0]=(-x1*SinS + y1*CosS)*ZoomRateY;
	PosX[1]=( x2*CosS + y2*SinS)*ZoomRateX;
	PosY[1]=(-x2*SinS + y2*CosS)*ZoomRateY;
	PosX[2]=( x3*CosS + y3*SinS)*ZoomRateX;
	PosY[2]=(-x3*SinS + y3*CosS)*ZoomRateY;
	PosX[3]=( x4*CosS + y4*SinS)*ZoomRateX;
	PosY[3]=(-x4*SinS + y4*CosS)*ZoomRateY;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);
}
bool	InstGerberAperturePrimitiveLineCenter::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	W=Width/2.0;
	double	H=Height/2.0;
	double	x1=CenterX-W;
	double	y1=CenterY-H;
	double	x2=CenterX+W;
	double	y2=CenterY-H;
	double	x3=CenterX+W;
	double	y3=CenterY+H;
	double	x4=CenterX-W;
	double	y4=CenterY+H;
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	gPosX[5];
	double	gPosY[5];
	gPosX[0]=( x1*CosS + y1*SinS)*ZoomAperture;
	gPosY[0]=(-x1*SinS + y1*CosS)*ZoomAperture;
	gPosX[1]=( x2*CosS + y2*SinS)*ZoomAperture;
	gPosY[1]=(-x2*SinS + y2*CosS)*ZoomAperture;
	gPosX[2]=( x3*CosS + y3*SinS)*ZoomAperture;
	gPosY[2]=(-x3*SinS + y3*CosS)*ZoomAperture;
	gPosX[3]=( x4*CosS + y4*SinS)*ZoomAperture;
	gPosY[3]=(-x4*SinS + y4*CosS)*ZoomAperture;
	gPosX[4]=gPosX[0];
	gPosY[4]=gPosY[0];

	return IsInside(PosX, PosY, gPosX, gPosY ,4);
}
//=============================================================================

	
bool	MacroGerberAperturePrimitiveLineLowerLeft::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	if(::Save(f,StartX)==false)
		return false;
	if(::Save(f,StartY)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	MacroGerberAperturePrimitiveLineLowerLeft::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,Height)==false)
		return false;
	if(::Load(f,StartX)==false)
		return false;
	if(::Load(f,StartY)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveLineLowerLeft::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveLineLowerLeft	*c=new InstGerberAperturePrimitiveLineLowerLeft();
	c->Exposure	=MakeValue(Exposure,Param);
	c->Width	=MakeValue(Width,Param)*Unit;
	c->Height	=MakeValue(Height,Param)*Unit;
	c->StartX	=MakeValue(StartX,Param)*Unit;
	c->StartY	=MakeValue(StartY,Param)*Unit;
	c->Rotation	=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitiveLineLowerLeft::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<6)
		return false;
	Exposure	=Param[0];
	Width		=Param[1];
	Height		=Param[2];
	StartX		=Param[3];
	StartY		=Param[4];
	Rotation	=Param[5];
	Unit		=_Unit;
	return true;
}
bool	InstGerberAperturePrimitiveLineLowerLeft::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	if(::Save(f,StartX)==false)
		return false;
	if(::Save(f,StartY)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	InstGerberAperturePrimitiveLineLowerLeft::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,Height)==false)
		return false;
	if(::Load(f,StartX)==false)
		return false;
	if(::Load(f,StartY)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveLineLowerLeft::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	double	x1=StartX;
	double	y1=StartY;
	double	x2=StartX+Width;
	double	y2=StartY;
	double	x3=StartX+Width;
	double	y3=StartY+Height;
	double	x4=StartX;
	double	y4=StartY+Height;
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	Mx1= x1*CosS + y1*SinS;
	double	My1=-x1*SinS + y1*CosS;
	double	Mx2= x2*CosS + y2*SinS;
	double	My2=-x2*SinS + y2*CosS;
	double	Mx3= x3*CosS + y3*SinS;
	double	My3=-x3*SinS + y3*CosS;
	double	Mx4= x4*CosS + y4*SinS;
	double	My4=-x4*SinS + y4*CosS;
	X1=min(min(Mx1,Mx2),min(Mx3,Mx4));
	Y1=min(min(My1,My2),min(My3,My4));
	X2=max(max(Mx1,Mx2),max(Mx3,Mx4));
	Y2=max(max(My1,My2),max(My3,My4));
	return true;
}
void	InstGerberAperturePrimitiveLineLowerLeft::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if((Exposure==1 && PosiImage==false) || (Exposure==0 && PosiImage==true))
		Col=NegaColor.rgba();

	double	Rx=((Width*ZoomRateX)*0.5);
	double	Ry=((Height*ZoomRateY)*0.5);
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
		double	tStartX	=(ModeMirrorX==false)?StartX:-StartX;
		double	tStartY	=(ModeMirrorY==false)?StartY:-StartY;
		double	tWidth	=(ModeMirrorX==false)?Width:-Width;
		double	tHeight	=(ModeMirrorY==false)?Height:-Height;
	
		double	s=Rotation+Angle;
		s=RegulateAngle(s);

		double	x1=tStartX;
		double	y1=tStartY;
		double	x2=tStartX+tWidth;
		double	y2=tStartY;
		double	x3=tStartX+tWidth;
		double	y3=tStartY+tHeight;
		double	x4=tStartX;
		double	y4=tStartY+tHeight;
		double	CosS=cos(s);
		double	SinS=sin(s);
		double	PosX[5];
		double	PosY[5];
		PosX[0]=( x1*CosS + y1*SinS)*ZoomRateX;
		PosY[0]=(-x1*SinS + y1*CosS)*ZoomRateY;
		PosX[1]=( x2*CosS + y2*SinS)*ZoomRateX;
		PosY[1]=(-x2*SinS + y2*CosS)*ZoomRateY;
		PosX[2]=( x3*CosS + y3*SinS)*ZoomRateX;
		PosY[2]=(-x3*SinS + y3*CosS)*ZoomRateY;
		PosX[3]=( x4*CosS + y4*SinS)*ZoomRateX;
		PosY[3]=(-x4*SinS + y4*CosS)*ZoomRateY;
		PosX[4]=PosX[0];
		PosY[4]=PosY[0];
		DrawPolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
	}
}
void	InstGerberAperturePrimitiveLineLowerLeft::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	if(Exposure==0)
		return;
	double	tStartX	=(ModeMirrorX==false)?StartX:-StartX;
	double	tStartY	=(ModeMirrorY==false)?StartY:-StartY;
	double	tWidth	=(ModeMirrorX==false)?Width:-Width;
	double	tHeight	=(ModeMirrorY==false)?Height:-Height;
	
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	x1=tStartX;
	double	y1=tStartY;
	double	x2=tStartX+tWidth;
	double	y2=tStartY;
	double	x3=tStartX+tWidth;
	double	y3=tStartY+tHeight;
	double	x4=tStartX;
	double	y4=tStartY+tHeight;
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	PosX[5];
	double	PosY[5];
	PosX[0]=( x1*CosS + y1*SinS)*ZoomRateX;
	PosY[0]=(-x1*SinS + y1*CosS)*ZoomRateY;
	PosX[1]=( x2*CosS + y2*SinS)*ZoomRateX;
	PosY[1]=(-x2*SinS + y2*CosS)*ZoomRateY;
	PosX[2]=( x3*CosS + y3*SinS)*ZoomRateX;
	PosY[2]=(-x3*SinS + y3*CosS)*ZoomRateY;
	PosX[3]=( x4*CosS + y4*SinS)*ZoomRateX;
	PosY[3]=(-x4*SinS + y4*CosS)*ZoomRateY;
	PosX[4]=PosX[0];
	PosY[4]=PosY[0];
	MakeImagePolygon(PosX,PosY,5,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);
}
bool	InstGerberAperturePrimitiveLineLowerLeft::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	x1=StartX;
	double	y1=StartY;
	double	x2=StartX+Width;
	double	y2=StartY;
	double	x3=StartX+Width;
	double	y3=StartY+Height;
	double	x4=StartX;
	double	y4=StartY+Height;
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	gPosX[5];
	double	gPosY[5];
	gPosX[0]=( x1*CosS + y1*SinS)*ZoomAperture;
	gPosY[0]=(-x1*SinS + y1*CosS)*ZoomAperture;
	gPosX[1]=( x2*CosS + y2*SinS)*ZoomAperture;
	gPosY[1]=(-x2*SinS + y2*CosS)*ZoomAperture;
	gPosX[2]=( x3*CosS + y3*SinS)*ZoomAperture;
	gPosY[2]=(-x3*SinS + y3*CosS)*ZoomAperture;
	gPosX[3]=( x4*CosS + y4*SinS)*ZoomAperture;
	gPosY[3]=(-x4*SinS + y4*CosS)*ZoomAperture;
	gPosX[4]=gPosX[0];
	gPosY[4]=gPosY[0];

	return IsInside(PosX, PosY, gPosX, gPosY ,4);
}
//=============================================================================

bool	MacroGerberAperturePrimitiveOutline::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Count)==false)
		return false;
	int	iCount=Count.toInt();
	for(int i=0;i<iCount && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		if(::Save(f,PointX[i])==false)
			return false;
		if(::Save(f,PointY[i])==false)
			return false;
	}
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}
bool	MacroGerberAperturePrimitiveOutline::Load(QIODevice *f)	
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Count)==false)
		return false;
	int	iCount=Count.toInt();
	for(int i=0;i<PointCount_MacroGerberAperturePrimitiveOutline && i<iCount;i++){
		if(::Load(f,PointX[i])==false)
			return false;
		if(::Load(f,PointY[i])==false)
			return false;
	}
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveOutline::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveOutline	*c=new InstGerberAperturePrimitiveOutline();
	c->Exposure	=MakeValue(Exposure,Param);
	c->Count	=MakeValue(Count,Param);
	for(int i=0;i<c->Count;i++){
		c->PointX[i]	=MakeValue(PointX[i],Param)*Unit;
		c->PointY[i]	=MakeValue(PointY[i],Param)*Unit;
	}
	c->Rotation	=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitiveOutline::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<9)
		return false;
	int	LCount=(Param.count()-3)/2;
	Exposure	=Param[0];
	Count		=Param[1];
	for(int i=0;i<LCount;i++){
		PointX[i]	=Param[2*i+2];
		PointY[i]	=Param[2*i+3];
	}
	Rotation	=Param[2*LCount+2];
	Unit		=_Unit;
	return true;
}
bool	InstGerberAperturePrimitiveOutline::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Count)==false)
		return false;
	for(int i=0;i<PointCount_MacroGerberAperturePrimitiveOutline && i<Count;i++){
		if(::Save(f,PointX[i])==false)
			return false;
		if(::Save(f,PointY[i])==false)
			return false;
	}
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveOutline::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Count)==false)
		return false;
	for(int i=0;i<PointCount_MacroGerberAperturePrimitiveOutline && i<Count;i++){
		if(::Load(f,PointX[i])==false)
			return false;
		if(::Load(f,PointY[i])==false)
			return false;
	}
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveOutline::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	if(Count<=0){
		return false;
	}
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	for(int i=0;i<Count;i++){
		double	Mx= PointX[i]*CosS + PointY[i]*SinS;
		double	My=-PointX[i]*SinS + PointY[i]*CosS;
		X1=min(X1,Mx);
		Y1=min(Y1,My);
		X2=max(X2,Mx);
		Y2=max(Y2,My);
	}
	return true;
}
void	InstGerberAperturePrimitiveOutline::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if((Exposure==1 && PosiImage==false) || (Exposure==0 && PosiImage==true))
		Col=NegaColor.rgba();

	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	PosX[PointCount_MacroGerberAperturePrimitiveOutline+1];
	double	PosY[PointCount_MacroGerberAperturePrimitiveOutline+1];
	for(int i=0;i<Count && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		double	tPx	=(ModeMirrorX==false)?PointX[i]:-PointX[i];
		double	tPy	=(ModeMirrorY==false)?PointY[i]:-PointY[i];
		PosX[i]=( tPx*CosS + tPy*SinS)*ZoomRateX;
		PosY[i]=(-tPx*SinS + tPy*CosS)*ZoomRateY;
	}
	PosX[Count]=PosX[0];
	PosY[Count]=PosY[0];
	DrawPolygon(PosX,PosY,Count+1,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY,Col,Hole);
}
void	InstGerberAperturePrimitiveOutline::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	if(Exposure==0)
		return;
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	PosX[PointCount_MacroGerberAperturePrimitiveOutline+1];
	double	PosY[PointCount_MacroGerberAperturePrimitiveOutline+1];
	for(int i=0;i<Count && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		double	tPx	=(ModeMirrorX==false)?PointX[i]:-PointX[i];
		double	tPy	=(ModeMirrorY==false)?PointY[i]:-PointY[i];
		PosX[i]=( tPx*CosS + tPy*SinS)*ZoomRateX;
		PosY[i]=(-tPx*SinS + tPy*CosS)*ZoomRateY;
	}
	PosX[Count]=PosX[0];
	PosY[Count]=PosY[0];
	MakeImagePolygon(PosX,PosY,Count+1,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);
}
bool	InstGerberAperturePrimitiveOutline::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	gPosX[PointCount_MacroGerberAperturePrimitiveOutline+1];
	double	gPosY[PointCount_MacroGerberAperturePrimitiveOutline+1];
	for(int i=0;i<Count && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		gPosX[i]=( PointX[i]*CosS + PointY[i]*SinS)*ZoomAperture;
		gPosY[i]=(-PointX[i]*SinS + PointY[i]*CosS)*ZoomAperture;
	}
	gPosX[Count]=gPosX[0];
	gPosY[Count]=gPosY[0];

	return IsInside(PosX, PosY, gPosX, gPosY ,Count);
}
//=============================================================================

bool	MacroGerberAperturePrimitivePolygon::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Count)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	MacroGerberAperturePrimitivePolygon::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Count)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitivePolygon::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitivePolygon	*c=new InstGerberAperturePrimitivePolygon();
	c->Exposure	=MakeValue(Exposure,Param);
	c->Count	=MakeValue(Count,Param);
	c->CenterX	=MakeValue(CenterX,Param)*Unit;
	c->CenterY	=MakeValue(CenterY,Param)*Unit;
	c->Diameter	=MakeValue(Diameter,Param)*Unit;
	c->Rotation	=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitivePolygon::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<6)
		return false;
	Exposure	=Param[0];
	Count		=Param[1];
	CenterX		=Param[2];
	CenterY		=Param[3];
	Diameter	=Param[4];
	Rotation	=Param[5];
	Unit		=_Unit;
	return true;
}
bool	InstGerberAperturePrimitivePolygon::Save(QIODevice *f)
{
	if(::Save(f,Exposure)==false)
		return false;
	if(::Save(f,Count)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitivePolygon::Load(QIODevice *f)
{
	if(::Load(f,Exposure)==false)
		return false;
	if(::Load(f,Count)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitivePolygon::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	if(Count<=0)
		return false;
	double	r=2.0*M_PI/Count;
	double	s=r/2.0;
	double	CosP=cos(s);
	double	SinP=sin(s);
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	W=Diameter/2.0/CosP;
	for(int i=0;i<Count;i++){
		double	Px=CenterX+W*cos(s+r*i);
		double	Py=CenterY+W*sin(s+r*i);
		double	Mx= Px*CosS + Py*SinS;
		double	My=-Px*SinS + Py*CosS;
		X1=min(X1,Mx);
		Y1=min(Y1,My);
		X2=max(X2,Mx);
		Y2=max(Y2,My);
	}
	return true;
}
void	InstGerberAperturePrimitivePolygon::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if((Exposure==1 && PosiImage==false) || (Exposure==0 && PosiImage==true))
		Col=NegaColor.rgba();

	if(Count==0)
		return;
	double	r=2.0*M_PI/Count;
	double	s=r/2.0;
	double	CosP=cos(s);
	double	SinP=sin(s);
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	W=Diameter/2.0/CosP;
	double	PosX[PointCount_MacroGerberAperturePrimitiveOutline+1];
	double	PosY[PointCount_MacroGerberAperturePrimitiveOutline+1];
	for(int i=0;i<Count && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		double	Px=CenterX+W*cos(s+r*i);
		double	Py=CenterY+W*sin(s+r*i);
		PosX[i]=( Px*CosS + Py*SinS)*ZoomRateX;
		PosY[i]=(-Px*SinS + Py*CosS)*ZoomRateY;
	}
	PosX[Count]=PosX[0];
	PosY[Count]=PosY[0];
	DrawPolygon(PosX,PosY,Count+1,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
}
void	InstGerberAperturePrimitivePolygon::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	if(Exposure==0)
		return;
	if(Count==0)
		return;
	double	r=2.0*M_PI/Count;
	double	s=r/2.0;
	double	CosP=cos(s);
	double	SinP=sin(s);
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	W=Diameter/2.0/CosP;
	double	PosX[PointCount_MacroGerberAperturePrimitiveOutline+1];
	double	PosY[PointCount_MacroGerberAperturePrimitiveOutline+1];
	for(int i=0;i<Count && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		double	Px=CenterX+W*cos(s+r*i);
		double	Py=CenterY+W*sin(s+r*i);
		PosX[i]=( Px*CosS + Py*SinS)*ZoomRateX;
		PosY[i]=(-Px*SinS + Py*CosS)*ZoomRateY;
	}
	PosX[Count]=PosX[0];
	PosY[Count]=PosY[0];
	MakeImagePolygon(PosX,PosY,Count+1,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);
}
bool	InstGerberAperturePrimitivePolygon::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	if(Count==0)
		return false;
	double	r=2.0*M_PI/Count;
	double	s=r/2.0;
	double	CosP=cos(s);
	double	SinP=sin(s);
	double	CosS=cos(Rotation);
	double	SinS=sin(Rotation);
	double	W=Diameter/2.0/CosP;
	double	gPosX[PointCount_MacroGerberAperturePrimitiveOutline+1];
	double	gPosY[PointCount_MacroGerberAperturePrimitiveOutline+1];
	for(int i=0;i<Count && i<PointCount_MacroGerberAperturePrimitiveOutline;i++){
		double	Px=CenterX+W*cos(s+r*i);
		double	Py=CenterY+W*sin(s+r*i);
		gPosX[i]=( Px*CosS + Py*SinS)*ZoomAperture;
		gPosY[i]=(-Px*SinS + Py*CosS)*ZoomAperture;
	}
	gPosX[Count]=gPosX[0];
	gPosY[Count]=gPosY[0];

	return IsInside(PosX, PosY, gPosX, gPosY ,4);
}
//=============================================================================

bool	MacroGerberAperturePrimitiveMoire::Save(QIODevice *f)
{
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,LineWidth)==false)
		return false;
	if(::Save(f,LineIsolation)==false)
		return false;
	if(::Save(f,LineCount)==false)
		return false;
	if(::Save(f,CrossLineWidth)==false)
		return false;
	if(::Save(f,CrossLineLength)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	MacroGerberAperturePrimitiveMoire::Load(QIODevice *f)
{
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,LineWidth)==false)
		return false;
	if(::Load(f,LineIsolation)==false)
		return false;
	if(::Load(f,LineCount)==false)
		return false;
	if(::Load(f,CrossLineWidth)==false)
		return false;
	if(::Load(f,CrossLineLength)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveMoire::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveMoire	*c=new InstGerberAperturePrimitiveMoire();
	c->CenterX			=MakeValue(CenterX,Param)*Unit;
	c->CenterY			=MakeValue(CenterY,Param)*Unit;
	c->Diameter			=MakeValue(Diameter,Param)*Unit;
	c->LineWidth		=MakeValue(LineWidth,Param)*Unit;
	c->LineIsolation	=MakeValue(LineIsolation,Param)*Unit;
	c->LineCount		=MakeValue(LineCount,Param);
	c->CrossLineWidth	=MakeValue(CrossLineWidth,Param)*Unit;
	c->CrossLineLength	=MakeValue(CrossLineLength,Param)*Unit;
	c->Rotation			=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitiveMoire::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<9)
		return false;
	CenterX			=Param[0];
	CenterY			=Param[1];
	Diameter		=Param[2];
	LineWidth		=Param[3];
	LineIsolation	=Param[4];
	LineCount		=Param[5];
	CrossLineWidth	=Param[6];
	CrossLineLength	=Param[7];
	Rotation		=Param[8];
	Unit			=_Unit;
	return true;
}
bool	InstGerberAperturePrimitiveMoire::Save(QIODevice *f)
{
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Diameter)==false)
		return false;
	if(::Save(f,LineWidth)==false)
		return false;
	if(::Save(f,LineIsolation)==false)
		return false;
	if(::Save(f,LineCount)==false)
		return false;
	if(::Save(f,CrossLineWidth)==false)
		return false;
	if(::Save(f,CrossLineLength)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	InstGerberAperturePrimitiveMoire::Load(QIODevice *f)
{
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Diameter)==false)
		return false;
	if(::Load(f,LineWidth)==false)
		return false;
	if(::Load(f,LineIsolation)==false)
		return false;
	if(::Load(f,LineCount)==false)
		return false;
	if(::Load(f,CrossLineWidth)==false)
		return false;
	if(::Load(f,CrossLineLength)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveMoire::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	double	W=Diameter/2.0;
	X1=CenterX-W;
	Y1=CenterY-W;
	X2=CenterX+W;
	Y2=CenterY+W;
	return true;
}
void	InstGerberAperturePrimitiveMoire::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=(Diameter*ZoomRateX)*0.5;
	double	Ry=(Diameter*ZoomRateY)*0.5;
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
			for(int n=0;n<LineCount;n++){
				double	Rn=(Diameter*0.5-(LineWidth+LineIsolation)*n)*ZoomRateY;
				double	Rm=(Diameter*0.5-(LineWidth+LineIsolation)*n-LineWidth)*ZoomRateY;
				int	Ryi=Rn;

				for(int y=-Ryi;y<-Ryi+LineWidth;y++){
					int	Y=ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						double	wy=ZoomRateX*y/ZoomRateY;
						int	m=sqrt((double)(Rn*Rn-wy*wy));
						int	X1=ImagePosX-m;
						int	X2=ImagePosX+m;
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
				for(int y=-Ryi+LineWidth;y<Ryi-LineWidth;y++){
					int	Y=ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						double	wy=ZoomRateX*y/ZoomRateY;
						int	m1=sqrt((double)(Rn*Rn-wy*wy));
						int	m2=sqrt((double)(Rm*Rm-wy*wy));
						int	X1 =ImagePosX-m1;
						int	X11=ImagePosX-m2;
						int	X21=ImagePosX+m2;
						int	X2 =ImagePosX+m1;
						BYTE	*d=pnt.scanLine(Y);
						X1 =max(X1 ,0);
						X11=min(X11,pnt.width()-1);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X1;X<=X11;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X11;X++){
								d[X]=(BYTE)Col;
							}
						}
						X21=max(X21,0);
						X2 =min(X2 ,pnt.width()-1);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X21;X<=X2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X21;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
				for(int y=Ryi-LineWidth;y<Ryi;y++){
					int	Y=ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						double	wy=ZoomRateX*y/ZoomRateY;
						int	m=sqrt((double)(Rn*Rn-wy*wy));
						int	X1=ImagePosX-m;
						int	X2=ImagePosX+m;
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
		double	PosX[12];
		double	PosY[12];
		PosX[0]=-CrossLineWidth*0.5;
		PosY[0]=-CrossLineLength*0.5;
		PosX[1]=-CrossLineWidth*0.5;
		PosY[1]=-CrossLineWidth*0.5;
		PosX[2]=-CrossLineLength*0.5;
		PosY[2]=-CrossLineWidth*0.5;
		PosX[3]=-CrossLineLength*0.5;
		PosY[3]= CrossLineWidth*0.5;
		PosX[4]=-CrossLineWidth*0.5;
		PosY[4]= CrossLineWidth*0.5;
		PosX[5]=-CrossLineWidth*0.5;
		PosY[5]= CrossLineLength*0.5;
		PosX[6]= CrossLineWidth*0.5;
		PosY[6]= CrossLineLength*0.5;
		PosX[7]= CrossLineWidth*0.5;
		PosY[7]= CrossLineWidth*0.5;
		PosX[8]= CrossLineLength*0.5;
		PosY[8]= CrossLineWidth*0.5;
		PosX[9]= CrossLineLength*0.5;
		PosY[9]=-CrossLineWidth*0.5;
		PosX[10]= CrossLineWidth*0.5;
		PosY[10]=-CrossLineWidth*0.5;
		PosX[11]= CrossLineWidth*0.5;
		PosY[11]=-CrossLineLength*0.5;

		double	s=Rotation+Angle;
		s=RegulateAngle(s);
		double	CosS=cos(s);
		double	SinS=sin(s);
		double	gPosX[13];
		double	gPosY[13];
		for(int i=0;i<12;i++){
			gPosX[i]=( PosX[i]*CosS + PosY[i]*SinS)*ZoomRateX;
			gPosY[i]=(-PosX[i]*SinS + PosY[i]*CosS)*ZoomRateY;
		}
		gPosX[12]=gPosX[0];
		gPosY[12]=gPosY[0];
		DrawPolygon(gPosX,gPosY,13,ImagePosX ,ImagePosY ,pnt, movx ,movy ,ZoomRateX ,ZoomRateY ,Col,Hole);
	}
}
void	InstGerberAperturePrimitiveMoire::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	int	XLen=XByte<<3;
	for(int n=0;n<LineCount;n++){
		double	Rn=(Diameter*0.5-(LineWidth+LineIsolation)*n)*ZoomRateY;
		double	Rm=(Diameter*0.5-(LineWidth+LineIsolation)*n-LineWidth)*ZoomRateY;
		int	Ryi=Rn;

		for(int y=-Ryi;y<-Ryi+LineWidth;y++){
			int	Y=ImagePosY+y;
			if(0<=Y && Y<YLen){
				double	wy=ZoomRateX*y/ZoomRateY;
				int	m=sqrt((double)(Rn*Rn-wy*wy));
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
		for(int y=-Ryi+LineWidth;y<Ryi-LineWidth;y++){
			int	Y=ImagePosY+y;
			if(0<=Y && Y<YLen){
				double	wy=ZoomRateX*y/ZoomRateY;
				int	m1=sqrt((double)(Rn*Rn-wy*wy));
				int	m2=sqrt((double)(Rm*Rm-wy*wy));
				int	X1 =ImagePosX-m1;
				int	X11=ImagePosX-m2;
				int	X21=ImagePosX+m2;
				int	X2 =ImagePosX+m1;
				BYTE	*d=Image[Y];
				X1 =max(X1 ,0);
				X11=min(X11,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X11;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X11;X++){
						SetBmpBitOnY0(d,X);
					}
				}
				X21=max(X21,0);
				X2 =min(X2 ,XLen-1);
				if(PosiImage==true){
					for(int X=X21;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X21;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
		}
		for(int y=Ryi-LineWidth;y<Ryi;y++){
			int	Y=ImagePosY+y;
			if(0<=Y && Y<YLen){
				double	wy=ZoomRateX*y/ZoomRateY;
				int	m=sqrt((double)(Rn*Rn-wy*wy));
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

	double	PosX[12];
	double	PosY[12];
	PosX[0]=-CrossLineWidth*0.5;
	PosY[0]=-CrossLineLength*0.5;
	PosX[1]=-CrossLineWidth*0.5;
	PosY[1]=-CrossLineWidth*0.5;
	PosX[2]=-CrossLineLength*0.5;
	PosY[2]=-CrossLineWidth*0.5;
	PosX[3]=-CrossLineLength*0.5;
	PosY[3]= CrossLineWidth*0.5;
	PosX[4]=-CrossLineWidth*0.5;
	PosY[4]= CrossLineWidth*0.5;
	PosX[5]=-CrossLineWidth*0.5;
	PosY[5]= CrossLineLength*0.5;
	PosX[6]= CrossLineWidth*0.5;
	PosY[6]= CrossLineLength*0.5;
	PosX[7]= CrossLineWidth*0.5;
	PosY[7]= CrossLineWidth*0.5;
	PosX[8]= CrossLineLength*0.5;
	PosY[8]= CrossLineWidth*0.5;
	PosX[9]= CrossLineLength*0.5;
	PosY[9]=-CrossLineWidth*0.5;
	PosX[10]= CrossLineWidth*0.5;
	PosY[10]=-CrossLineWidth*0.5;
	PosX[11]= CrossLineWidth*0.5;
	PosY[11]=-CrossLineLength*0.5;

	double	s=Rotation+Angle;
	s=RegulateAngle(s);
	double	CosS=cos(s);
	double	SinS=sin(s);
	double	gPosX[13];
	double	gPosY[13];
	for(int i=0;i<12;i++){
		gPosX[i]=( PosX[i]*CosS + PosY[i]*SinS)*ZoomRateX;
		gPosY[i]=(-PosX[i]*SinS + PosY[i]*CosS)*ZoomRateY;
	}
	gPosX[12]=gPosX[0];
	gPosY[12]=gPosY[0];
	MakeImagePolygon(gPosX,gPosY,13,ImagePosX ,ImagePosY ,Image ,XByte ,YLen,PosiImage,ZoomRateX,ZoomRateY,Hole);
}

bool	InstGerberAperturePrimitiveMoire::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	if(hypot(PosX-CenterX,PosY-CenterY)<=Diameter*0.5*ZoomAperture){
		return true;
	}
	return false;
}
//=============================================================================

bool	MacroGerberAperturePrimitiveThermal::Save(QIODevice *f)
{
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,DiameterOut)==false)
		return false;
	if(::Save(f,DiameterIn)==false)
		return false;
	if(::Save(f,CrossLineWidth)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}

bool	MacroGerberAperturePrimitiveThermal::Load(QIODevice *f)
{
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,DiameterOut)==false)
		return false;
	if(::Load(f,DiameterIn)==false)
		return false;
	if(::Load(f,CrossLineWidth)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
InstGerberAperturePrimitiveBase	*MacroGerberAperturePrimitiveThermal::MakeInst(DoubleList &Param)
{
	InstGerberAperturePrimitiveThermal	*c=new InstGerberAperturePrimitiveThermal();
	c->CenterX			=MakeValue(CenterX,Param)*Unit;
	c->CenterY			=MakeValue(CenterY,Param)*Unit;
	c->DiameterOut		=MakeValue(DiameterOut,Param)*Unit;
	c->DiameterIn		=MakeValue(DiameterIn,Param)*Unit;
	c->CrossLineWidth	=MakeValue(CrossLineWidth,Param)*Unit;
	c->Rotation			=MakeValue(Rotation,Param)*2*M_PI/360.0;
	return c;
}
bool	MacroGerberAperturePrimitiveThermal::SetParam(QStringList &Param ,double _Unit)
{
	if(Param.count()<6)
		return false;
	CenterX			=Param[0];
	CenterY			=Param[1];
	DiameterOut		=Param[2];
	DiameterIn		=Param[3];
	CrossLineWidth	=Param[4];
	Rotation		=Param[5];
	Unit			=_Unit;
	return true;
}
bool	InstGerberAperturePrimitiveThermal::Save(QIODevice *f)
{
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,DiameterOut)==false)
		return false;
	if(::Save(f,DiameterIn)==false)
		return false;
	if(::Save(f,CrossLineWidth)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveThermal::Load(QIODevice *f)
{
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,DiameterOut)==false)
		return false;
	if(::Load(f,DiameterIn)==false)
		return false;
	if(::Load(f,CrossLineWidth)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;
	return true;
}
bool	InstGerberAperturePrimitiveThermal::GetXY(double &X1, double &Y1 ,double &X2 ,double &Y2)
{
	double	W=DiameterOut/2.0;
	X1=CenterX-W;
	Y1=CenterY-W;
	X2=CenterX+W;
	Y2=CenterY+W;
	return true;
}
void	InstGerberAperturePrimitiveThermal::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	if(PosiImage==false)
		Col=NegaColor.rgba();

	double	Rx=(DiameterOut*ZoomRateX)*0.5;
	double	Ry=(DiameterOut*ZoomRateY)*0.5;
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
			double	Rn=DiameterOut*ZoomRateY*0.5;
			double	Rm=DiameterIn *ZoomRateY*0.5;
			double	Gap=CrossLineWidth*ZoomRateX*0.5;
			int	Ryo=Rn;
			int	Ryi=Rm;
			int	g=Gap;
			for(int y=-Ryo;y<-Ryi;y++){
				int	Y=ImagePosY+y;
				if(0<=Y && Y<pnt.height()){
					double	wy=ZoomRateX*y/ZoomRateY;
					int	m=sqrt((double)(Rn*Rn-wy*wy));
					int	X1=ImagePosX-m;
					int	X2=ImagePosX-g;
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
					int	X3=ImagePosX+g;
					int	X4=ImagePosX+m;
					X3=max(X3,0);
					X4=min(X4,pnt.width()-1);
					if(pnt.depth()==32){
						QRgb	*dp=((QRgb *)&d[X1<<2]);
						for(int X=X3;X<=X4;X++){
							//*((QRgb *)&d[X<<2])=Col;
							*dp=Col;
							dp++;
						}
					}
					else if(pnt.depth()==8){
						for(int X=X3;X<=X4;X++){
							d[X]=(BYTE)Col;
						}
					}
				}
			}
			for(int y=-Ryi;y<Ryi;y++){
				if(y<=-g || g<=y){
					int	Y=ImagePosY+y;
					if(0<=Y && Y<pnt.height()){
						double	wy=ZoomRateX*y/ZoomRateY;
						int	m1=sqrt((double)(Rn*Rn-wy*wy));
						int	m2=sqrt((double)(Rm*Rm-wy*wy));
						int	X1 =ImagePosX-m1;
						int	X11=ImagePosX-m2;
						int	X21=ImagePosX+m2;
						int	X2 =ImagePosX+m1;
						BYTE	*d=pnt.scanLine(Y);
						X1 =max(X1 ,0);
						X11=min(X11,pnt.width()-1);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X1;X<=X11;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X1;X<=X11;X++){
								d[X]=(BYTE)Col;
							}
						}
						X21=max(X21,0);
						X2 =min(X2 ,pnt.width()-1);
						if(pnt.depth()==32){
							QRgb	*dp=((QRgb *)&d[X1<<2]);
							for(int X=X21;X<=X2;X++){
								//*((QRgb *)&d[X<<2])=Col;
								*dp=Col;
								dp++;
							}
						}
						else if(pnt.depth()==8){
							for(int X=X21;X<=X2;X++){
								d[X]=(BYTE)Col;
							}
						}
					}
				}
			}
			for(int y=Ryi;y<Ryo;y++){
				int	Y=ImagePosY+y;
				if(0<=Y && Y<pnt.height()){
					double	wy=ZoomRateX*y/ZoomRateY;
					int	m=sqrt((double)(Rn*Rn-wy*wy));
					int	X1=ImagePosX-m;
					int	X2=ImagePosX-g;
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
					int	X3=ImagePosX+g;
					int	X4=ImagePosX+m;
					X3=max(X3,0);
					X4=min(X4,pnt.width()-1);
					if(pnt.depth()==32){
						QRgb	*dp=((QRgb *)&d[X1<<2]);
						for(int X=X3;X<=X4;X++){
							//*((QRgb *)&d[X<<2])=Col;
							*dp=Col;
							dp++;
						}
					}
					else if(pnt.depth()==8){
						for(int X=X3;X<=X4;X++){
							d[X]=(BYTE)Col;
						}
					}
				}
			}
		}
	}
}
void	InstGerberAperturePrimitiveThermal::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	int	XLen=XByte<<3;
	double	Rn=DiameterOut*ZoomRateY*0.5;
	double	Rm=DiameterIn *ZoomRateY*0.5;
	double	Gap=CrossLineWidth*ZoomRateX*0.5;
	int	Ryo=Rn;
	int	Ryi=Rm;
	int	g=Gap;
	for(int y=-Ryo;y<-Ryi;y++){
		int	Y=ImagePosY+y;
		if(0<=Y && Y<YLen){
			double	wy=ZoomRateX*y/ZoomRateY;
			int	m=sqrt((double)(Rn*Rn-wy*wy));
			int	X1=ImagePosX-m;
			int	X2=ImagePosX-g;
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
			int	X3=ImagePosX+g;
			int	X4=ImagePosX+m;
			X3=max(X3,0);
			X4=min(X4,XLen-1);
			if(PosiImage==true){
				for(int X=X3;X<=X4;X++){
					SetBmpBitOnY1(d,X);
				}
			}
			else{
				for(int X=X3;X<=X4;X++){
					SetBmpBitOnY0(d,X);
				}
			}
		}
	}
	for(int y=-Ryi;y<Ryi;y++){
		if(y<=-g || g<=y){
			int	Y=ImagePosY+y;
			if(0<=Y && Y<YLen){
				double	wy=ZoomRateX*y/ZoomRateY;
				int	m1=sqrt((double)(Rn*Rn-wy*wy));
				int	m2=sqrt((double)(Rm*Rm-wy*wy));
				int	X1 =ImagePosX-m1;
				int	X11=ImagePosX-m2;
				int	X21=ImagePosX+m2;
				int	X2 =ImagePosX+m1;
				BYTE	*d=Image[Y];
				X1 =max(X1 ,0);
				X11=min(X11,XLen-1);
				if(PosiImage==true){
					for(int X=X1;X<=X11;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X1;X<=X11;X++){
						SetBmpBitOnY0(d,X);
					}
				}
				X21=max(X21,0);
				X2 =min(X2 ,XLen-1);
				if(PosiImage==true){
					for(int X=X21;X<=X2;X++){
						SetBmpBitOnY1(d,X);
					}
				}
				else{
					for(int X=X21;X<=X2;X++){
						SetBmpBitOnY0(d,X);
					}
				}
			}
		}
	}
	for(int y=Ryi;y<=Ryo;y++){
		int	Y=ImagePosY+y;
		if(0<=Y && Y<YLen){
			double	wy=ZoomRateX*y/ZoomRateY;
			int	m=sqrt((double)(Rn*Rn-wy*wy));
			int	X1=ImagePosX-m;
			int	X2=ImagePosX-g;
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
			int	X3=ImagePosX+g;
			int	X4=ImagePosX+m;
			X3=max(X3,0);
			X4=min(X4,XLen-1);
			if(PosiImage==true){
				for(int X=X3;X<=X4;X++){
					SetBmpBitOnY1(d,X);
				}
			}
			else{
				for(int X=X3;X<=X4;X++){
					SetBmpBitOnY0(d,X);
				}
			}
		}
	}
}

bool	InstGerberAperturePrimitiveThermal::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	if(hypot(PosX-CenterX,PosY-CenterY)<=DiameterOut*0.5*ZoomAperture){
		return true;
	}
	return false;
}
//============================================================

bool	MacroGerberAperturePrimitiveContainer::Save(QIODevice *f)
{
	int32	Count=GetCount();
	if(::Save(f,Count)==false)
		return false;
	for(MacroGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	C=a->GetClassID();
		if(::Save(f,C)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	MacroGerberAperturePrimitiveContainer::Load(QIODevice *f)
{
	int32	Count;
	if(::Load(f,Count)==false)
		return false;
	RemoveAll();
	for(int i=0;i<Count;i++){
		int32	C;
		if(::Load(f,C)==false)
			return false;
		MacroGerberAperturePrimitiveBase	*a=NULL;
		if(C==1)
			a=new MacroGerberAperturePrimitiveCircle();
		else if(C==2)
			a=new MacroGerberAperturePrimitiveLineVector();
		else if(C==21)
			a=new MacroGerberAperturePrimitiveLineCenter();
		else if(C==22)
			a=new MacroGerberAperturePrimitiveLineLowerLeft();
		else if(C==4)
			a=new MacroGerberAperturePrimitiveOutline();
		else if(C==5)
			a=new MacroGerberAperturePrimitivePolygon();
		else if(C==6)
			a=new MacroGerberAperturePrimitiveMoire();
		else if(C==7)
			a=new MacroGerberAperturePrimitiveThermal();
		if(a!=NULL){
			if(a->Load(f)==false)
				return false;
			AppendList(a);
		}
	}
	return true;
}

bool	MacroGerberAperturePrimitiveContainer::Make(InstGerberAperturePrimitiveContainer &RetContainer , DoubleList &Param)
{
	RetContainer.RemoveAll();
	for(MacroGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		InstGerberAperturePrimitiveBase	*c=a->MakeInst(Param);
		RetContainer.AppendList(c);
	}
	return true;
}
bool	MacroGerberAperturePrimitiveContainer::LoadFromGerber(char Buff[] ,double Unit)
{
	char	*fp=strchr(Buff,'%');
	if(fp!=NULL)
		*fp=0;
	fp=Buff;
	while(*fp!=0){
		while(*fp==' ' || *fp=='\t' || *fp=='\n' || *fp=='\r')
			fp++;
		char	*gp=strchr(fp,'*');
		if(gp==NULL){
			return false;
		}
		*gp=0;
		QString	ParamStr=fp;
		fp=gp+1;
		while(*fp==' ' || *fp=='\t' || *fp=='\n' || *fp=='\r')
			fp++;
		QStringList	List=ParamStr.split(',');
		if(List.count()==0)
			return false;
		bool	ok;
		int	Code=List[0].toInt(&ok);
		if(ok==false)
			return false;
		QStringList	Param;
		for(int i=1;i<List.count();i++){
			Param.append(List[i]);
		}
		MacroGerberAperturePrimitiveBase	*a=NULL;
		if(Code==1)
			a=new MacroGerberAperturePrimitiveCircle();
		else if(Code==2 || Code==20)
			a=new MacroGerberAperturePrimitiveLineVector();
		else if(Code==21)
			a=new MacroGerberAperturePrimitiveLineCenter();
		else if(Code==22)
			a=new MacroGerberAperturePrimitiveLineLowerLeft();
		else if(Code==4)
			a=new MacroGerberAperturePrimitiveOutline();
		else if(Code==5)
			a=new MacroGerberAperturePrimitivePolygon();
		else if(Code==6)
			a=new MacroGerberAperturePrimitiveMoire();
		else if(Code==7)
			a=new MacroGerberAperturePrimitiveThermal();

		if(a==NULL)
			return false;
		if(a->SetParam(Param ,Unit)==false)
			return false;
		AppendList(a);
	}
	return true;
}
	
bool	InstGerberAperturePrimitiveContainer::Save(QIODevice *f)
{
	int32	Count=GetCount();
	if(::Save(f,Count)==false)
		return false;
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		int32	C=a->GetClassID();
		if(::Save(f,C)==false)
			return false;
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	InstGerberAperturePrimitiveContainer::Load(QIODevice *f)
{
	int32	Count;
	if(::Load(f,Count)==false)
		return false;
	RemoveAll();
	for(int i=0;i<Count;i++){
		int32	C;
		if(::Load(f,C)==false)
			return false;
		InstGerberAperturePrimitiveBase	*a=NULL;
		if(C==1)
			a=new InstGerberAperturePrimitiveCircle();
		else if(C==2)
			a=new InstGerberAperturePrimitiveLineVector();
		else if(C==21)
			a=new InstGerberAperturePrimitiveLineCenter();
		else if(C==22)
			a=new InstGerberAperturePrimitiveLineLowerLeft();
		else if(C==4)
			a=new InstGerberAperturePrimitiveOutline();
		else if(C==5)
			a=new InstGerberAperturePrimitivePolygon();
		else if(C==6)
			a=new InstGerberAperturePrimitiveMoire();
		else if(C==7)
			a=new InstGerberAperturePrimitiveThermal();
		if(a!=NULL){
			if(a->Load(f)==false)
				return false;
			AppendList(a);
		}
	}
	return true;
}
//============================================================
GerberApertureMacro::GerberApertureMacro(void)
{
}

bool	GerberApertureMacro::Save(QIODevice *f)
{
	if(::Save(f,MacroName)==false)
		return false;
	if(Primitives.Save(f)==false)
		return false;
	return true;
}
bool	GerberApertureMacro::Load(QIODevice *f)
{
	if(::Load(f,MacroName)==false)
		return false;
	if(Primitives.Load(f)==false)
		return false;
	return true;
}

bool	GerberApertureMacro::LoadFromGerber(char Buff[] ,double Unit)
{
	return Primitives.LoadFromGerber(Buff ,Unit);
}

//============================================================

double	InstGerberAperturePrimitiveContainer::GetWidth(void)
{
	double	MinX=DBL_MAX;
	double	MaxX=-DBL_MAX;
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		double	X1,Y1,X2,Y2;
		if(a->GetXY(X1,Y1,X2,Y2)==true){
			MinX=min(MinX,X1);
			MaxX=max(MaxX,X2);
		}
	}
	return MaxX-MinX;
}

double	InstGerberAperturePrimitiveContainer::GetHeight(void)
{
	double	MinY=DBL_MAX;
	double	MaxY=-DBL_MAX;
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		double	X1,Y1,X2,Y2;
		if(a->GetXY(X1,Y1,X2,Y2)==true){
			MinY=min(MinY,Y1);
			MaxY=max(MaxY,Y2);
		}
	}
	return MaxY-MinY;
}


void	InstGerberAperturePrimitiveContainer::SetWidth(double w)
{
}

void	InstGerberAperturePrimitiveContainer::SetHeight(double h)
{
}

void	InstGerberAperturePrimitiveContainer::Draw(double ImagePosX ,double ImagePosY 
						,QImage &pnt, int movx ,int movy ,double ZoomRateX ,double ZoomRateY
						,QRgb Col,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
						,bool PosiImage
						,ApertureHole &Hole)
{
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(ImagePosX ,ImagePosY 
						,pnt, movx ,movy , ZoomRateX ,ZoomRateY 
						,Col,Angle ,ModeMirrorX ,ModeMirrorY
						,PosiImage
						,Hole);
	}
}

void	InstGerberAperturePrimitiveContainer::MakeImage(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
							,BYTE **Image ,int XByte ,int YLen
							,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
							,bool PosiImage
							,ApertureHole &Hole)
{
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeImage(ImagePosX ,ImagePosY ,ZoomRateX ,ZoomRateY
							,Image ,XByte ,YLen
							,Angle ,ModeMirrorX ,ModeMirrorY
							,PosiImage
							,Hole);
	}
}
	
void	InstGerberAperturePrimitiveContainer::MakeOutline(double ImagePosX ,double ImagePosY ,double ZoomRateX ,double ZoomRateY
								,OutlineArea &TransArea,double Isolation ,double HairlineLength
								,double Angle ,bool ModeMirrorX ,bool ModeMirrorY
								,bool PosiImage)
{
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeOutline(ImagePosX ,ImagePosY ,ZoomRateX ,ZoomRateY
								,TransArea,Isolation ,HairlineLength
								, Angle , ModeMirrorX , ModeMirrorY
								, PosiImage);
	}
}

void	InstGerberAperturePrimitiveContainer::MakeApertureInfo(struct	ApertureInfo &Info)
{
}

void	InstGerberAperturePrimitiveContainer::SetApertureInfo(struct	ApertureInfo &Info)
{
}

bool	InstGerberAperturePrimitiveContainer::IsInclude(double PosX,double PosY,	double Angle,double ZoomAperture)
{
	for(InstGerberAperturePrimitiveBase *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(PosX,PosY,	Angle,ZoomAperture)==true)
			return true;
	}
	return false;
}