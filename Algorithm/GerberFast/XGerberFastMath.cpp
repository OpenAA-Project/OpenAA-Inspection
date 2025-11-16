#include "XGerberAperture.h"
#include "XGerberFast.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include <omp.h>


bool	IsConnrctedFF(double Cx1,double Cy1,double R1
					, double Cx2,double Cy2,double R2)
{
	if(hypot(Cx2-Cx1,Cy2-Cy1)<=(R1+R2))
		return true;
	return false;
}

bool	IsConnrctedFL(double Cx ,double Cy ,double R
					, double X1 ,double Y1 ,double X2 ,double Y2 ,double LW)
{
	double	Len=GetLengthLine2Point(X1,Y1,X2,Y2 ,Cx  ,Cy);
	if(Len<=(R+LW))
		return true;
	return false;
}

bool	IsConnrctedLL(double Xa1 ,double Ya1 ,double Xa2 ,double Ya2 ,double LWa
					, double Xb1 ,double Yb1 ,double Xb2 ,double Yb2 ,double LWb)
{
	double X ,Y;
	if(GetCrossInnerPoint(Xa1 ,Ya1 ,Xa2 ,Ya2
						, Xb1 ,Yb1 ,Xb2 ,Yb2, X ,Y)==true)
		return true;
	double	Len1=GetLengthLine2Point(Xa1,Ya1,Xa2,Ya2 ,Xb1,Yb1);
	double	Len2=GetLengthLine2Point(Xa1,Ya1,Xa2,Ya2 ,Xb2,Yb2);
	double	Len3=GetLengthLine2Point(Xb1,Yb1,Xb2,Yb2 ,Xa1,Ya1);
	double	Len4=GetLengthLine2Point(Xb1,Yb1,Xb2,Yb2 ,Xa2,Ya2);
	double	Len=min(min(Len1,Len2),min(Len3,Len4));
	if(Len<=(LWa+LWb))
		return true;
	return false;
}

bool	IsConnrctedAF(double Cx ,double Cy ,double R ,double S1, double S2 ,double WidthA
					, double Px ,double Py ,double PR )
{
	double	Len=hypot(Cx-Px,Cy-Py);
	if(fabs(Len-R)>(WidthA+PR))
		return false;
	double	s=GetSita(Px-Cx,Py-Cy);
	if(S1<=S2){
		if(S1<=s && s<=S2)
			return true;
	}
	if(S1<=s || s<=S2)
		return true;
	return false;
}
bool	IsConnrctedAL(double Cx ,double Cy ,double R ,double S1, double S2 ,double WidthA
					, double X1 ,double Y1 ,double X2 ,double Y2 ,double LW)
{
	double sx1,sy1 ,sx2, sy2;

	int	N=GetCrossCircleLine(Cx ,Cy, R
						,X1,Y1 ,X2, Y2
						,sx1,sy1 ,sx2, sy2);
	double	sa,sb;
	if(N<=2){
		sa=GetSita(sx1-Cx,sy1-Cy);
		if((S1<=S2 && (S1<=sa && sa<=S2)) || ((S2<S1) && (S1<=sa || sa<=S2))){
			return true;
		}
	}
	if(N==2){
		sb=GetSita(sx2-Cx,sy2-Cy);
		if((S1<=S2 && (S1<=sb && sb<=S2)) || ((S2<S1) && (S1<=sb || sb<=S2))){
			return true;
		}
	}
	double	Len0=GetLengthLine2Point(X1,Y1,X2,Y2 ,Cx,Cy);
	if(fabs(Len0-R)<=(WidthA+LW)){
		double	Hx,Hy;
		double	X,Y;
		if(GetLinePointFoot(X1,Y1,X2,Y2	,Cx,Cy,X ,Y)==true){
			Hx=X;
			Hy=Y;
		}
		else{
			double	Len1=hypot(Cx-X1,Cy-Y1);
			double	Len2=hypot(Cx-X2,Cy-Y2);
			if(Len1<Len2){
				Hx=X1;
				Hy=Y1;
			}
			else{
				Hx=X2;
				Hy=Y2;
			}
		}
		double	sc=GetSita(Hx-Cx,Hy-Cy);
		if((S1<=S2 && (S1<=sc && sc<=S2)) || ((S2<S1) && (S1<=sc || sc<=S2))){
			return true;
		}
	}

	double	Ax1=R*cos(S1)+Cx;
	double	Ay1=R*sin(S1)+Cy;
	double	Len1=GetLengthLine2Point(X1,Y1,X2,Y2 ,Ax1,Ay1);
	if(Len1<=(WidthA+LW))
		return true;

	double	Ax2=R*cos(S2)+Cx;
	double	Ay2=R*sin(S2)+Cy;
	double	Len2=GetLengthLine2Point(X1,Y1,X2,Y2 ,Ax2,Ay2);
	if(Len2<=(WidthA+LW))
		return true;
	return false;
}

bool	IsConnrctedAA(double Cax ,double Cay ,double Ra ,double Sa1, double Sa2 ,double WidthA
					, double Cbx ,double Cby ,double Rb ,double Sb1, double Sb2 ,double WidthB)
{
	//Incomplete

	double	Tx1=Ra*cos(Sa1)+Cax;
	double	Ty1=Ra*sin(Sa1)+Cay;
	if(IsConnrctedAF(Cbx ,Cby ,Rb ,Sb1, Sb2 ,WidthB
					, Tx1,Ty1,WidthA)==true)
		return true;

	double	Tx2=Ra*cos(Sa2)+Cax;
	double	Ty2=Ra*sin(Sa2)+Cay;
	if(IsConnrctedAF(Cbx ,Cby ,Rb ,Sb1, Sb2 ,WidthB
					, Tx2,Ty2,WidthA)==true)
		return true;

	double	Hx1=Rb*cos(Sb1)+Cbx;
	double	Hy1=Rb*sin(Sb1)+Cby;
	if(IsConnrctedAF(Cax ,Cay ,Ra ,Sa1, Sa2 ,WidthA
					, Hx1,Hy1,WidthB)==true)
		return true;

	double	Hx2=Rb*cos(Sb2)+Cbx;
	double	Hy2=Rb*sin(Sb2)+Cby;
	if(IsConnrctedAF(Cax ,Cay ,Ra ,Sa1, Sa2 ,WidthA
					, Hx2,Hy2,WidthB)==true)
		return true;

	return false;
}
