#include "XTypeDef.h"
#include <cmath>
#include "XPointer.h"
#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XImageProcess.h"
#include "swap.h"
#include "XCrossObj.h"
#include <math.h>
#include "XInterpolation.h"

static	double	InterpolateEllipseTest(ImageBuffer &Img
							,double Cx,double Cy
							,double Rx,double Ry);

void	InterpolateEllipse(ImageBuffer &Img , FlexArea &CircleArea
							,double &Cx,double &Cy
							,double &Rx,double &Ry
							,double Precision)
{
	CircleArea.GetCenter(Cx,Cy);
	Rx=CircleArea.GetWidth()/2.0;
	Ry=CircleArea.GetHeight()/2.0;

	double	D0,D1;

	double	dCx=1.0;
	double	dCy=1.0;
	double	dRx=1.0;
	double	dRy=1.0;
	double	LastDCx=0;
	double	LastDCy=0;
	double	LastDRx=0;
	double	LastDRy=0;
	double	A=0.1;

	do{
		D0=InterpolateEllipseTest(Img
								,Cx,Cy
								,Rx,Ry);
		D1=InterpolateEllipseTest(Img
								,Cx,Cy
								,Rx+dRx,Ry);
		Rx+=A*(D1-D0)*dRx;
		if(LastDRx>0 && (D1-D0)>0 && LastDRx>(D1-D0)){
			dRx/=2.0;
		}
		LastDRx=D1-D0;

		D1=InterpolateEllipseTest(Img
								,Cx,Cy
								,Rx,Ry+dRy);
		Ry+=A*(D1-D0)*dRy;
		if(LastDRy>0 && (D1-D0)>0 && LastDRy>(D1-D0)){
			dRy/=2.0;
		}
		LastDRy=D1-D0;

		D1=InterpolateEllipseTest(Img
								,Cx+dCx,Cy
								,Rx,Ry);
		Cx+=A*(D1-D0)*dCx;
		if(LastDCx>0 && (D1-D0)>0 && LastDCx>(D1-D0)){
			dCx/=2.0;
		}
		LastDCx=D1-D0;

		D1=InterpolateEllipseTest(Img
								,Cx,Cy+dCy
								,Rx,Ry);
		Cy+=A*(D1-D0)*dCy;
		if(LastDCy>0 && (D1-D0)>0 && LastDCy>(D1-D0)){
			dCy/=2.0;
		}
		LastDCy=D1-D0;
	}while(dCx>Precision || dCy>Precision || dRx>Precision || dRy>Precision);
}

static	double	InterpolateEllipseTest(ImageBuffer &Img
							,double Cx,double Cy
							,double Rx,double Ry)
{
	double	Ret=0;
	int	Count=0;

	for(int x=-Rx;x<=Rx;x++){
		double	X=x+Cx;
		double	y=sqrt(1-x*x/(Rx*Rx));
		double	Y=y+Cy;
		double	Dx=x*Ry/Ry;
		double	Dy=y*Rx/Ry;
		double	H=hypot(Dx,Dy);
		Dx/=H;
		Dy/=H;
		double	X1=X-Dx/2;
		double	Y1=Y-Dy/2;
		double	X2=X+Dx/2;
		double	Y2=Y+Dy/2;

		double	D1=Img.GetInterpolatedBrightness(X1,Y1);
		double	D2=Img.GetInterpolatedBrightness(X2,Y2);
		Ret+=(D2-D1)*(D2-D1);
		Count++;

		Y=-y+Cy;
		Dx=x*Ry/Ry;
		Dy=y*Rx/Ry;
		Dx/=H;
		Dy/=H;
		X1=X-Dx/2;
		Y1=Y-Dy/2;
		X2=X+Dx/2;
		Y2=Y+Dy/2;

		D1=Img.GetInterpolatedBrightness(X1,Y1);
		D2=Img.GetInterpolatedBrightness(X2,Y2);
		Ret+=(D2-D1)*(D2-D1);
		Count++;
	}
	if(Count==0)
		return 0;
	return Ret/Count;
}

bool	MakeInterpolatedLine(double x[] ,double y[] ,int N
							 ,double &A,double &B,double &C)
/*
	Å¬‚Qæ–@‚Å
	Ax+By+C=0
	‚ð‹‚ß‚é
*/
{
	double	X=0,X2=0,Y=0,Y2=0,XY=0;
	for(int i=0;i<N;i++){
		X	+=x[i];
		Y	+=y[i];
		XY	+=x[i]*y[i];
		X2	+=x[i]*x[i];
		Y2	+=y[i]*y[i];
	}
	double	iA=-N*(X2-Y2)+(X*X-Y*Y);
	double	iB=N*XY-X*Y;
	double	D=4*iB*iB+iA*iA;
	if(D<=0.0){
		return false;
	}
	double	DRoot=sqrt(D);
	double	Cos21=0.5+iA*DRoot/(2*D);
	double	Cos22=0.5-iA*DRoot/(2*D);

	double	MaxM=9.0e100;
	bool	Ret=false;
	for(int i=0;i<4;i++){
		double	CosS;
		switch(i){
			case 0:	if(1.0<Cos21 || Cos21<0){
						continue;
					}
					CosS=sqrt(Cos21);
					break;
			case 1:	if(1.0<Cos21 || Cos21<0){
						continue;
					}
					CosS=-sqrt(Cos21);
					break;
			case 2:	if(1.0<Cos22 || Cos22<0){
						continue;
					}
					CosS=sqrt(Cos22);
					break;
			case 3:	if(1.0<Cos22 || Cos22<0){
						continue;
					}
					CosS=-sqrt(Cos22);
					break;
			default:
					CosS=0;
		}

		double	SinS;
		if(CosS==0.0){
			SinS=1.0;
		}
		else{
			SinS=(-2*iB*CosS*CosS+iB)/(iA*CosS);
		}
		if(-1.0<=SinS && SinS<=1.0){
			double	a=(-X*CosS-Y*SinS)/N;
			double	M=X2*CosS*CosS+Y2*SinS*SinS+N*a*a+2*SinS*CosS*XY+2*a*CosS*X+2*a*SinS*Y;
			if(M<MaxM){
				A=CosS;
				B=SinS;
				C=a;
				MaxM=M;
				Ret=true;
			}
		}
	}
	return Ret;
}

bool	AnalizeInterpolatedLine(double x[] ,double y[] ,int N
								 ,double A,double B,double C
								,double &RetMaxSeparation
								,double &RetVarietySeparatedDistanceFromLine
								,double RetStartPointOnLine[2]
								,double RetEndPointOnLine[2])
{
	double	D=sqrt(A*A+B*B);
	if(D<=0.0 || N<=1){
		return false;
	}
	RetMaxSeparation=0;
	double	SumS=0;
	double	SumSS=0;
	for(int i=0;i<N;i++){
		double	L=fabs(A*x[i]+B*y[i]+C)/D;
		SumS+=L;
		SumSS+=L*L;
		RetMaxSeparation=max(RetMaxSeparation,L);
	}

	double	Avr=SumS/N;
	double	Dv=(SumSS-N*Avr*Avr)/N;
	if(Dv<0)
		return false;

	RetVarietySeparatedDistanceFromLine=sqrt(Dv);

	double	Px,Py;
	GetLinePointFoot(A,B,C,x[0],y[0] ,Px ,Py);
	double	MinT=0;
	double	MaxT=0;
	double	hx=B/D;
	double	hy=-A/D;
	for(int i=1;i<N;i++){
		double	X,Y;
		GetLinePointFoot(A,B,C,x[i],y[i] ,X ,Y);
		double	t=hx*(X-Px)+hy*(Y-Py);
		MinT=min(MinT,t);
		MaxT=max(MaxT,t);
	}
	RetStartPointOnLine[0]	=Px+MinT*hx;
	RetStartPointOnLine[1]	=Py+MinT*hy;
	RetEndPointOnLine[0]	=Px+MaxT*hx;
	RetEndPointOnLine[1]	=Py+MaxT*hy;

	return true;
}
