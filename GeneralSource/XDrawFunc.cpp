#include "XTypeDef.h"
#include "XDrawFunc.h"
#include "XCrossObj.h"
#define	_USE_MATH_DEFINES
#include <math.h>

void	DrawArrow(double StartX ,double StartY ,double EndX ,double EndY
				 ,QPainter &Pnt ,int movx ,int movy ,double ZoomRate ,int SizeOfArrowMark)
{
	double	X1=(StartX+movx)*ZoomRate;
	double	Y1=(StartY+movy)*ZoomRate;
	double	X2=(EndX+movx)*ZoomRate;
	double	Y2=(EndY+movy)*ZoomRate;

    double	dx=X2-X1;
    double	dy=Y2-Y1;
    double	Len=hypot(dx,dy);
	if(Len<0.0000001)
		return;
	double	px=dx/Len;
	double	py=dy/Len;
	double	vx=py;
	double	vy=-px;

	if(Len<SizeOfArrowMark){
		Len=SizeOfArrowMark;
		X2=X1+px*Len;
		Y2=Y1+py*Len;
	}

    QPoint	P[8];

	double	Cos1=cos(135.0/360.0*2.0*M_PI);
	double	Sin1=sin(135.0/360.0*2.0*M_PI);
	double	Sqrt2=sqrt(2.0);

    P[0].setX(X2);
    P[0].setY(Y2);
	double	Lx=SizeOfArrowMark/2.0*(px*Cos1-py*Sin1)*Sqrt2;
	double	Ly=SizeOfArrowMark/2.0*(px*Sin1+py*Cos1)*Sqrt2;
    P[1].setX(X2+Lx);
    P[1].setY(Y2+Ly);
	Lx+=vx*SizeOfArrowMark/3.0;
	Ly+=vy*SizeOfArrowMark/3.0;
    P[2].setX(X2+Lx);
    P[2].setY(Y2+Ly);
	Lx+=-px*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
	Ly+=-py*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
    P[3].setX(X2+Lx);
    P[3].setY(Y2+Ly);
	Lx+=vx*SizeOfArrowMark/3.0;
	Ly+=vy*SizeOfArrowMark/3.0;
    P[4].setX(X2+Lx);
    P[4].setY(Y2+Ly);
	Lx+=px*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
	Ly+=py*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
    P[5].setX(X2+Lx);
    P[5].setY(Y2+Ly);
	Lx+=vx*SizeOfArrowMark/3.0;
	Ly+=vy*SizeOfArrowMark/3.0;
    P[6].setX(X2+Lx);
    P[6].setY(Y2+Ly);

    P[7]=P[0];

	Pnt.drawPolygon(P,7);

}


void	DrawArrow(double StartX ,double StartY ,double EndX ,double EndY
				 ,QPainter &Pnt ,int movx ,int movy ,double ZoomRate 
				 ,int x1,int y1 ,int x2 ,int y2
				 ,int SizeOfArrowMark)
{
	double	X1=(StartX+movx)*ZoomRate;
	double	Y1=(StartY+movy)*ZoomRate;
	double	X2=(EndX+movx)*ZoomRate;
	double	Y2=(EndY+movy)*ZoomRate;

    double	dx=X2-X1;
    double	dy=Y2-Y1;
    double	Len=hypot(dx,dy);
	if(Len<0.0000001)
		return;
	double	px=dx/Len;
	double	py=dy/Len;
	double	vx=py;
	double	vy=-px;

	if(Len<SizeOfArrowMark){
		Len=SizeOfArrowMark;
		X2=X1+px*Len;
		Y2=Y1+py*Len;
	}

    QPoint	P[8];

	double	Cos1=cos(135.0/360.0*2.0*M_PI);
	double	Sin1=sin(135.0/360.0*2.0*M_PI);
	double	Sqrt2=sqrt(2.0);

    P[0].setX(X2);
    P[0].setY(Y2);
	double	Lx=SizeOfArrowMark/2.0*(px*Cos1-py*Sin1)*Sqrt2;
	double	Ly=SizeOfArrowMark/2.0*(px*Sin1+py*Cos1)*Sqrt2;
    P[1].setX(X2+Lx);
    P[1].setY(Y2+Ly);
	Lx+=vx*SizeOfArrowMark/3.0;
	Ly+=vy*SizeOfArrowMark/3.0;
    P[2].setX(X2+Lx);
    P[2].setY(Y2+Ly);
	Lx+=-px*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
	Ly+=-py*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
    P[3].setX(X2+Lx);
    P[3].setY(Y2+Ly);
	Lx+=vx*SizeOfArrowMark/3.0;
	Ly+=vy*SizeOfArrowMark/3.0;
    P[4].setX(X2+Lx);
    P[4].setY(Y2+Ly);
	Lx+=px*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
	Ly+=py*(SizeOfArrowMark/2.0 + Len-SizeOfArrowMark);
    P[5].setX(X2+Lx);
    P[5].setY(Y2+Ly);
	Lx+=vx*SizeOfArrowMark/3.0;
	Ly+=vy*SizeOfArrowMark/3.0;
    P[6].setX(X2+Lx);
    P[6].setY(Y2+Ly);

    P[7]=P[0];

	QPoint	*Dest[20];
	QPoint	TmpD[2000];
	for(int i=0;i<20;i++){
		Dest[i]=&TmpD[100*i];
	}
	int	DestPointNumb[20];

	bool	Clipped;
	int	N=ClipPolygon(P, 7,Dest ,DestPointNumb,20
				,x1 ,y1 ,x2 ,y2
				,Clipped);

	for(int i=0;i<N;i++){
		Pnt.drawPolygon(Dest[i],DestPointNumb[i]);
	}
}
