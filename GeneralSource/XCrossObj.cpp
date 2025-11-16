/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCrossObj.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#include "XTypeDef.h"
#include <QtGui>
#include <QPointF>
#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "swap.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "NList.h"
#include "XBsearch.h"

double	RegulateAngle(double sita)
//	角度を正規化する
//	０～２πにする
{
	while(sita<0.0){
		sita+=2.0*M_PI;
	}
	while(sita>=2.0*M_PI){
		sita-=2.0*M_PI;
	}
	return(sita);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    dx
//    dy
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
double  GetSita(int dx ,int dy)
/*	(x1,y1) - (x2,y2) の線分の角度を得る	finish debug
	中心を(x1,y1) とする

	リターンはラジアン単位
	０～２πが返る
	*/
{
	double	D;
	double	rt;

	if(dx==0 && dy==0)	return(0.0);
	D=hypot(dx,dy);
	if(dx>=0 && dy>=0){
		if(dx<dy){
			rt=acos((double)dx/(double)D);
			}
		else{
			rt=asin((double)dy/(double)D);
			}
		}
	else if(dx<0 && dy>=0){
		if(-dx<dy){
			rt=acos((double)dx/(double)D);
			}
		else{
			rt=M_PI - asin((double)dy/(double)D);
			}
		}
	else if(dx<0 && dy<0){
		if(dx>dy){
			rt=2.0*M_PI - acos((double)dx/(double)D);
			}
		else{
			rt=M_PI - asin((double)dy/(double)D);
			}
		}
	else{
		if(dx<-dy){
			rt=2.0*M_PI - acos((double)dx/(double)D);
			}
		else{
			rt=2.0*M_PI + asin((double)dy/(double)D);
			}
		}
	return(rt);
}

double  GetSita(double dx ,double dy)
/*	(x1,y1) - (x2,y2) の線分の角度を得る	finish debug
	中心を(x1,y1) とする

	リターンはラジアン単位
	０～２πが返る
	*/
{
	double	D;
	double	rt;

	if(dx==0.0 && dy==0.0)	return(0.0);
	D=hypot(dx,dy);
	if(dx>=0 && dy>=0){
		if(dx>=dy){
			rt=acos(dx/D);
			}
		else{
			rt=asin(dy/D);
			}
		}
	else if(dx<0 && dy>=0){
		if(-dx>=dy){
			rt=acos(dx/D);
			}
		else{
			rt=M_PI - asin(dy/D);
			}
		}
	else if(dx<0 && dy<0){
		if(dx<=dy){
			rt=2.0*M_PI - acos(dx/D);
			}
		else{
			rt=M_PI - asin(dy/D);
			}
		}
	else{
		if(dx>=-dy){
			rt=2.0*M_PI - acos(dx/D);
			}
		else{
			rt=2.0*M_PI + asin(dy/D);
			}
		}
	return(rt);
}
double	GetMiddleAngle(double StartAngle ,double EndAngle)
{
	StartAngle	=RegulateAngle(StartAngle);
	EndAngle	=RegulateAngle(EndAngle);
	if(StartAngle<=EndAngle)
		return RegulateAngle((StartAngle+EndAngle)/2.0);
	else{
		double	t=(StartAngle-2.0*M_PI+EndAngle)/2.0;
		return RegulateAngle(t);
	}
}

bool	IsInsideAngle(double a ,double StartAngle ,double EndAngle)
{
	if(StartAngle<=EndAngle){
		if(StartAngle<=a && a<=EndAngle)
			return true;
	}
	if(StartAngle>=EndAngle){
		if(StartAngle<=a || a<=EndAngle)
			return true;
	}
	return false;
}
double  DiffSita(double s1 ,double s2)
{
    s1=RegulateAngle(s1);
    s2=RegulateAngle(s2);

    double  s=fabs(s1-s2);
	if(s>M_PI){
        s=2.0*M_PI-s;
	}
    return(s);
}

int RInt(double d)
//四捨五入
{
	if(d>=0){
		double	p;
		if(modf(d,&p)<0.5){
			return (int)p;
		}
		else{
			return ((int)p)+1;
		}
	}
	else{
		double	p;
		if(modf(-d,&p)<0.5){
			return -(int)p;
		}
		else{
			return -((int)p)-1;
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    ax1
//    ay1
//    ax2
//    ay2
//    bx1
//    by1
//    bx2
//    by2
//    X
//    Y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    GetCrossInnerPoint(long ax1,long ay1,long ax2,long ay2,long bx1,long by1,long bx2,long by2 , long &X ,long &Y)
/*      ２線分の交点を求める    これは、端点内に交点が存在しないとき、FALSE が返る
							finish debug
	(ax1,ay1) - (ax2,ay2) に線分１の端点
	(bx1,by1) - (bx2,by2) に線分２の端点を入れる
	(X,Y) に交点座標が返る

	正常に交点が求められたとき、TRUE が返る
	FALSE が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		少なくとも一方が線分をなしていないとき
		２線分が重なるとき        */
{
	long    Dax,Day,Dbx,Dby;
	double  Dx,Dy;

	Dax= ax2-ax1;
	Day= ay2-ay1;
	Dbx= bx2-bx1;
	Dby= by2-by1;

	Dx = (double)Dbx*(double)Day - (double)Dax*(double)Dby;
	if(Dx==0L)       return(false);

	if(ax1==ax2){
		X=ax1;
	}
	else if(bx1==bx2){
		X=bx1;
	}
	else{
		X = ax1 + (long)( ( ((double)Dby*(double)(ax1-bx1) - (double)Dbx*(double)(ay1-by1))*(double)Dax +Dx/2)/Dx);
	}

	if(ax1<ax2){
		if(X<ax1 || ax2<X){      return(false);		}
		}
	else{
		if(X<ax2 || ax1<X){      return(false);		}
		}
	if(bx1<bx2){
		if(X<bx1 || bx2<X){      return(false);		}
		}
	else{
		if(X<bx2 || bx1<X){      return(false);		}
		}

	//Dy = (double)Dby*(double)Dax - (double)Day*(double)Dbx;
	Dy=-Dx;
	if(Dy==0L){
		return(false);
	}

	if(ay1==ay2){            Y=ay1;	}
	else if(by1==by2){       Y=by1;	}
	else{    Y = ay1 + (long)( ( ((double)Dbx*(double)(ay1-by1) - (double)Dby*(double)(ax1-bx1))*(double)Day +Dy/2)/Dy);	}

	if(ay1<ay2){
		if(Y<ay1 || ay2<Y){      return(false);		}
		}
	else{
		if(Y<ay2 || ay1<Y){      return(false);		}
		}
	if(by1<by2){
		if(Y<by1 || by2<Y){      return(false);		}
		}
	else{
		if(Y<by2 || by1<Y){      return(false);		}
		}
	return(true);
}

bool    GetCrossInnerPoint(double ax1,double ay1,double ax2,double ay2,double bx1,double by1,double bx2,double by2 , double &X ,double &Y)
{
	double  Dax,Day,Dbx,Dby;
	double  Dx,Dy;

	Dax= ax2-ax1;
	Day= ay2-ay1;
	Dbx= bx2-bx1;
	Dby= by2-by1;

	Dx = Dbx*Day - Dax*Dby;
	if(fabs(Dx)<0.00001){       return false;	}

	if(ax1==ax2)            X=ax1;
	else if(bx1==bx2)       X=bx1;
	else    X = ax1 + ( ( (Dby*(ax1-bx1) - Dbx*(ay1-by1))*Dax)/Dx);

	if(ax1<ax2){
		if(X<ax1 || ax2<X){      return false;		}
		}
	else{
		if(X<ax2 || ax1<X){      return false;		}
		}
	if(bx1<bx2){
		if(X<bx1 || bx2<X){      return false;		}
		}
	else{
		if(X<bx2 || bx1<X){      return false;		}
		}

	Dy=-Dx;
	if(fabs(Dy)<0.0001){		return false;		}

	if(ay1==ay2){            Y=ay1;		}
	else if(by1==by2){       Y=by1;		}
	else{    Y = ay1 + ( ( (Dbx*(ay1-by1) - Dby*(ax1-bx1))*Day)/Dy);		}

	if(ay1<ay2){
		if(Y<ay1 || ay2<Y){      return false;		}
		}
	else{
		if(Y<ay2 || ay1<Y){      return false;		}
		}
	if(by1<by2){
		if(Y<by1 || by2<Y){      return false;		}
		}
	else{
		if(Y<by2 || by1<Y){      return false;		}
		}
	return true;
}

bool    GetCrossPoint(double ax1,double ay1,double ax2,double ay2,double bx1,double by1,double bx2,double by2 , double &X ,double &Y)
{
	double  Dax,Day,Dbx,Dby;
	double  Dx,Dy;

	Dax= ax2-ax1;
	Day= ay2-ay1;
	Dbx= bx2-bx1;
	Dby= by2-by1;

	Dx = Dbx*Day - Dax*Dby;
	if(fabs(Dx)<0.00001){       return false;	}

	if(ax1==ax2)            X=ax1;
	else if(bx1==bx2)       X=bx1;
	else    X = ax1 + ( ( (Dby*(ax1-bx1) - Dbx*(ay1-by1))*Dax)/Dx);

	Dy=-Dx;
	if(fabs(Dy)<0.0001){		return false;		}

	if(ay1==ay2){            Y=ay1;		}
	else if(by1==by2){       Y=by1;		}
	else{    Y = ay1 + ( ( (Dbx*(ay1-by1) - Dby*(ax1-bx1))*Day)/Dy);		}

	return true;
}
bool    GetCrossInnerPointWithoutEdge(double ax1,double ay1,double ax2,double ay2,double bx1,double by1,double bx2,double by2 , double &X ,double &Y)
{
	double  Dax,Day,Dbx,Dby;
	double  Dx,Dy;

	Dax= ax2-ax1;
	Day= ay2-ay1;
	Dbx= bx2-bx1;
	Dby= by2-by1;

	Dx = Dbx*Day - Dax*Dby;
	if(fabs(Dx)<0.00001){       return false;	}

	if(ax1==ax2)            X=ax1;
	else if(bx1==bx2)       X=bx1;
	else    X = ax1 + ( ( (Dby*(ax1-bx1) - Dbx*(ay1-by1))*Dax)/Dx);

	if(ax1<ax2){
		if(X<ax1 || ax2<X){      return false;		}
		}
	else{
		if(X<ax2 || ax1<X){      return false;		}
		}
	if(bx1<bx2){
		if(X<bx1 || bx2<X){      return false;		}
		}
	else{
		if(X<bx2 || bx1<X){      return false;		}
		}

	Dy=-Dx;
	if(fabs(Dy)<0.0001){		return false;		}

	if(ay1==ay2){            Y=ay1;		}
	else if(by1==by2){       Y=by1;		}
	else{    Y = ay1 + ( ( (Dbx*(ay1-by1) - Dby*(ax1-bx1))*Day)/Dy);		}

	if(ay1<ay2){
		if(Y<ay1 || ay2<Y){      return false;		}
		}
	else{
		if(Y<ay2 || ay1<Y){      return false;		}
		}
	if(by1<by2){
		if(Y<by1 || by2<Y){      return false;		}
		}
	else{
		if(Y<by2 || by1<Y){      return false;		}
		}
	if(fabs(X-ax1)<0.00001 && fabs(Y-ay1)<0.00001)	return false;
	if(fabs(X-ax2)<0.00001 && fabs(Y-ay2)<0.00001)	return false;
	if(fabs(X-bx1)<0.00001 && fabs(Y-by1)<0.00001)	return false;
	if(fabs(X-bx2)<0.00001 && fabs(Y-by2)<0.00001)	return false;

	return true;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    ax1
//    ay1
//    ax2
//    ay2
//    by
//    X
//    Y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    GetCrossHalfInnerPoint(long ax1,long ay1,long ax2,long ay2,long by , long &X)
/*      ２線分の交点を求める    これは、端点内に交点が存在しないとき、FALSE が返る
							finish debug
	(ax1,ay1) - (ax2,ay2) に線分１の端点
	(by) に水平ラインのX座標
	X に交点座標が返る

	正常に交点が求められたとき、TRUE が返る
	FALSE が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		線分をなしていないとき
        線分が直線に含まれるとき
        */
{
	double  Dx;

	if(ay1==ay2){
        return(false);
	}

    if((ay1<ay2 && (by<ay1 || ay2<by))
		|| (ay1>ay2 && (by<ay2 || ay1<by))){
        return(false);
	}

    Dx=((double)((by-ay1)*(ax1-ax2)+ax1*(ay1-ay2)))/(double)(ay1-ay2);
    if((ax1<=ax2 && ax1<=Dx && Dx<=ax2)
    || (ax1>=ax2 && ax2<=Dx && Dx<=ax1)){
        X=Dx;
        return(true);
        }
    return(false);
}

bool    GetCrossHalfInnerPoint(double ax1,double ay1,double ax2,double ay2,double by , double &X)
/*      ２線分の交点を求める    これは、端点内に交点が存在しないとき、FALSE が返る
							finish debug
	(ax1,ay1) - (ax2,ay2) に線分１の端点
	(by) に水平ラインのY座標
	X に交点座標が返る

	正常に交点が求められたとき、TRUE が返る
	FALSE が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		線分をなしていないとき
        線分が直線に含まれるとき
        */
{
	double  Dx;
	double	Delta=0.00000001;

	if(ay1==ay2){
        return(false);
	}

    if((ay1<ay2 && (by<ay1 || ay2<by))
		|| (ay1>ay2 && (by<ay2 || ay1<by))){
        return(false);
	}

    Dx=((double)((by-ay1)*(ax1-ax2)+ax1*(ay1-ay2)))/(double)(ay1-ay2);
    if((ax1<=ax2 && ax1<=(Dx+Delta) && Dx<=(ax2+Delta))
    || (ax1>=ax2 && ax2<=(Dx+Delta) && Dx<=(ax1+Delta))){
        X=Dx;
        return(true);
        }
    return(false);
}


bool    GetCrossHalfInnerPointX(long ax1,long ay1,long ax2,long ay2,long bx , long &Y)
/*      ２線分の交点を求める    これは、端点内に交点が存在しないとき、FALSE が返る
							finish debug
	(ax1,ay1) - (ax2,ay2) に線分１の端点
	(bx) に垂直ラインのY座標
	Y に交点座標が返る

	正常に交点が求められたとき、TRUE が返る
	FALSE が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		線分をなしていないとき
        線分が直線に含まれるとき
        */
{
	double  Dy;

	if(ay1==ay2){
        return(false);
	}

    if((ax1<ax2 && (bx<ax1 || ax2<bx))
		|| (ax1>ax2 && (bx<ax2 || ax1<bx))){
        return(false);
	}

    Dy=((double)((bx-ax1)*(ay1-ay2)+ay1*(ax1-ax2)))/(double)(ax1-ax2);
    if((ay1<=ay2 && ay1<=Dy && Dy<=ay2)
    || (ay1>=ay2 && ay2<=Dy && Dy<=ay1)){
        Y=Dy;
        return(true);
        }
    return(false);
}

bool    GetCrossHalfInnerPointX(double ax1,double ay1,double ax2,double ay2,double bx , double &Y)
/*      ２線分の交点を求める    これは、端点内に交点が存在しないとき、FALSE が返る
							finish debug
	(ax1,ay1) - (ax2,ay2) に線分１の端点
	(bx) に垂直ラインのY座標
	Y に交点座標が返る

	正常に交点が求められたとき、TRUE が返る
	FALSE が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		線分をなしていないとき
        線分が直線に含まれるとき
        */
{
	double  Dy;
	double	Delta=0.00000001;

	if(ax1==ax2){
        return(false);
	}

    if((ax1<ax2 && (bx<ax1 || ax2<bx))
		|| (ax1>ax2 && (bx<ax2 || ax1<bx))){
        return(false);
	}

    Dy=((double)((bx-ax1)*(ay1-ay2)+ay1*(ax1-ax2)))/(double)(ax1-ax2);
    if((ay1<=ay2 && ay1<=(Dy+Delta) && Dy<=(ay2+Delta))
    || (ay1>=ay2 && ay2<=(Dy+Delta) && Dy<=(ay1+Delta))){
        Y=Dy;
        return(true);
        }
    return(false);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    rx1
//    ry1
//    rx2
//    ry2
//    px1
//    py1
//    px2
//    py2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    CheckOverlapRectLine(long rx1, long ry1, long rx2, long ry2
			    ,long px1, long py1, long px2, long py2)
/*      内部を含む矩形と線分が１部分でもオーバーラップしているか調べる
						finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に線分の端点を入れる

	オーバーラップしているとき、TRUE が返る
	*/
{
	long    x1 ,y1 ,x2 ,y2;
	long    X,Y;

	x1 = min(rx1,rx2);
	y1 = min(ry1,ry2);
	x2 = max(rx1,rx2);
	y2 = max(ry1,ry2);

	if( (px1<x1 && px2<x1)
	 || (py1<y1 && py2<y1)
	 || (x2<px1 && x2<px2)
	 || (y2<py1 && y2<py2)){
		 return(false);
	}

	if( (x1<=px1 && px1<=x2 && y1<=py1 && py1<=y2)
		|| (x1<=px2 && px2<=x2 && y1<=py2 && py2<=y2)){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x1,y1,x1,y2 , X ,Y)==true){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x1,y1,x2,y1 , X ,Y)==true){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x2,y1,x2,y2 , X ,Y)==true){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x1,y2,x2,y2 , X ,Y)==true){
		return(true);
	}
	return(false);
}
bool    CheckOverlapRectLine(int rx1, int ry1, int rx2, int ry2		//Box
							,int px1, int py1, int px2, int py2)	//Line
{
	return CheckOverlapRectLine	((long)rx1, (long)ry1, (long)rx2, (long)ry2
								,(long)px1, (long)py1, (long)px2, (long)py2);
}
bool    CheckOverlapRectLine(double rx1, double ry1, double rx2, double ry2		//Box
							,double px1, double py1, double px2, double py2)	//Line
{
	double    x1 ,y1 ,x2 ,y2;
	double    X,Y;

	x1 = min(rx1,rx2);
	y1 = min(ry1,ry2);
	x2 = max(rx1,rx2);
	y2 = max(ry1,ry2);

	if( (px1<x1 && px2<x1)
	 || (py1<y1 && py2<y1)
	 || (x2<px1 && x2<px2)
	 || (y2<py1 && y2<py2)){
		 return(false);
	}

	if( (x1<=px1 && px1<=x2 && y1<=py1 && py1<=y2)
	 || (x1<=px2 && px2<=x2 && y1<=py2 && py2<=y2)){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x1,y1,x1,y2 , X ,Y)==true){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x1,y1,x2,y1 , X ,Y)==true){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x2,y1,x2,y2 , X ,Y)==true){
		return(true);
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,x1,y2,x2,y2 , X ,Y)==true){
		return(true);
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    rx1
//    ry1
//    rx2
//    ry2
//    px1
//    py1
//    px2
//    py2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool CheckOverlapRectRect(long rx1, long ry1, long rx2, long ry2
			    ,long px1, long py1, long px2, long py2)
/*      内部を含む矩形と内部を含む矩形が１部分でもオーバーラップしているか調べる
					finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に矩形座標を入れる

	オーバーラップしているとき、TRUE が返る
	一方が他方を完全に包含しているとき、TRUE が返る
	*/
{
	long    x1 ,y1 ,x2 ,y2;
	long    ax1 ,ay1 ,ax2 ,ay2;

	x1 = min(rx1,rx2);
	y1 = min(ry1,ry2);
	x2 = max(rx1,rx2);
	y2 = max(ry1,ry2);      //座標を正規化する

	if( (px1<x1 && px2<x1)
	 || (py1<y1 && py2<y1)
	 || (x2<px1 && x2<px2)
	 || (y2<py1 && y2<py2)){
		 return(false);
	}

	if( x1<=px1 && px1<=x2 && y1<=py1 && py1<=y2){
		return(true);
	}
	if( x1<=px1 && px1<=x2 && y1<=py2 && py2<=y2){
		return(true);
	}
	if( x1<=px2 && px2<=x2 && y1<=py1 && py1<=y2){
		return(true);
	}
	if( x1<=px2 && px2<=x2 && y1<=py2 && py2<=y2){
		return(true);
	}

	ax1 = min(px1,px2);
	ay1 = min(py1,py2);
	ax2 = max(px1,px2);
	ay2 = max(py1,py2);

	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}

	if(x1<=ax1 && ax2<=x2 && ay1<=y1 && y2<=ay2){
        return(true);
	}
	if(ax1<=x1 && x2<=ax2 && y1<=ay1 && ay2<=y2){
        return(true);
	}
	return(false);
}
bool CheckOverlapRectRect(int rx1, int ry1, int rx2, int ry2
			    ,int px1, int py1, int px2, int py2)
/*      内部を含む矩形と内部を含む矩形が１部分でもオーバーラップしているか調べる
					finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に矩形座標を入れる

	オーバーラップしているとき、TRUE が返る
	一方が他方を完全に包含しているとき、TRUE が返る
	*/
{
	int    x1 ,y1 ,x2 ,y2;
	int    ax1 ,ay1 ,ax2 ,ay2;

	x1 = min(rx1,rx2);
	y1 = min(ry1,ry2);
	x2 = max(rx1,rx2);
	y2 = max(ry1,ry2);      //座標を正規化する

	if( (px1<x1 && px2<x1)
	 || (py1<y1 && py2<y1)
	 || (x2<px1 && x2<px2)
	 || (y2<py1 && y2<py2)){
		 return(false);
	}

	if( x1<=px1 && px1<=x2 && y1<=py1 && py1<=y2){
		return(true);
	}
	if( x1<=px1 && px1<=x2 && y1<=py2 && py2<=y2){
		return(true);
	}
	if( x1<=px2 && px2<=x2 && y1<=py1 && py1<=y2){
		return(true);
	}
	if( x1<=px2 && px2<=x2 && y1<=py2 && py2<=y2){
		return(true);
	}

	ax1 = min(px1,px2);
	ay1 = min(py1,py2);
	ax2 = max(px1,px2);
	ay2 = max(py1,py2);

	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}

	if(x1<=ax1 && ax2<=x2 && ay1<=y1 && y2<=ay2){
        return(true);
	}
	if(ax1<=x1 && x2<=ax2 && y1<=ay1 && ay2<=y2){
        return(true);
	}
	return(false);
}



bool CheckOverlapRectRect(double rx1, double ry1, double rx2, double ry2
						 ,double px1, double py1, double px2, double py2)
/*      内部を含む矩形と内部を含む矩形が１部分でもオーバーラップしているか調べる
					finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に矩形座標を入れる

	オーバーラップしているとき、TRUE が返る
	一方が他方を完全に包含しているとき、TRUE が返る
	*/
{
	double    x1 ,y1 ,x2 ,y2;
	double    ax1 ,ay1 ,ax2 ,ay2;

	x1 = min(rx1,rx2);
	y1 = min(ry1,ry2);
	x2 = max(rx1,rx2);
	y2 = max(ry1,ry2);      //座標を正規化する

	if( (px1<x1 && px2<x1)
	 || (py1<y1 && py2<y1)
	 || (x2<px1 && x2<px2)
	 || (y2<py1 && y2<py2)){
		 return(false);
	}

	if( x1<=px1 && px1<=x2 && y1<=py1 && py1<=y2){
		return(true);
	}
	if( x1<=px1 && px1<=x2 && y1<=py2 && py2<=y2){
		return(true);
	}
	if( x1<=px2 && px2<=x2 && y1<=py1 && py1<=y2){
		return(true);
	}
	if( x1<=px2 && px2<=x2 && y1<=py2 && py2<=y2){
		return(true);
	}

	ax1 = min(px1,px2);
	ay1 = min(py1,py2);
	ax2 = max(px1,px2);
	ay2 = max(py1,py2);

	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx1 && rx1<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry1 && ry1<=ay2){
		return(true);
	}
	if( ax1<=rx2 && rx2<=ax2 && ay1<=ry2 && ry2<=ay2){
		return(true);
	}

	if(x1<=ax1 && ax2<=x2 && ay1<=y1 && y2<=ay2){
        return(true);
	}
	if(ax1<=x1 && x2<=ax2 && y1<=ay1 && ay2<=y2){
        return(true);
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    rx1
//    ry1
//    rx2
//    ry2
//    px1
//    py1
//    px2
//    py2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool CheckOverlapRectRectFast(long rx1, long ry1, long rx2, long ry2
				 		     ,long px1, long py1, long px2, long py2)
/*      内部を含む矩形と内部を含む矩形が１部分でもオーバーラップしているか調べる
					finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に矩形座標を入れる

	オーバーラップしているとき、TRUE が返る
	一方が他方を完全に包含しているとき、TRUE が返る
	*/
{
	if( (px1<rx1 && px2<rx1)
	 || (py1<ry1 && py2<ry1)
	 || (rx2<px1 && rx2<px2)
	 || (ry2<py1 && ry2<py2)){
		 return(false);
	}

	if(rx1<=px1 && px1<=rx2 && ry1<=py1 && py1<=ry2){
		return(true);
	}
	if(rx1<=px1 && px1<=rx2 && ry1<=py2 && py2<=ry2){
		return(true);
	}
	if(rx1<=px2 && px2<=rx2 && ry1<=py1 && py1<=ry2){
		return(true);
	}
	if(rx1<=px2 && px2<=rx2 && ry1<=py2 && py2<=ry2){
		return(true);
	}

	if(px1<=rx1 && rx1<=px2 && py1<=ry1 && ry1<=py2){
		return(true);
	}
	if(px1<=rx1 && rx1<=px2 && py1<=ry2 && ry2<=py2){
		return(true);
	}
	if(px1<=rx2 && rx2<=px2 && py1<=ry1 && ry1<=py2){
		return(true);
	}
	if(px1<=rx2 && rx2<=px2 && py1<=ry2 && ry2<=py2){
		return(true);
	}

	if(rx1<=px1 && px2<=rx2 && py1<=ry1 && ry2<=py2){
        return(true);
	}
	if(px1<=rx1 && rx2<=px2 && ry1<=py1 && py2<=ry2){
        return(true);
	}
	return(false);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x
//    y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
double slopi(double x ,double y)
{
	int     i;
	double  t;

	x=fabs(x);      y=fabs(y);
	if(x<y){        t=x;    x=y;    y=t;    }
	if(y==0){
		return(x);
	}
	for(i=0;i<3;i++){
		t=y/x;
		t*=t;
		t/=4+t;
		x+=2*x*t;
		y*=t;
		}
	return(x);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x
//    y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int slopi(short x ,short y)
{
	int     t;
	unsigned long   L;

	x=(short)((x>0)?x:-x);
	y=(short)((y>0)?y:-y);
	if(x<y){        t=x;    x=y;    y=(short)t;    }
	if(y==0){
		return(x);
	}
	if(x==y){
		x++;
	}

	do{
		L=(((unsigned long)y<<16L) +((unsigned long)x>>1))/((unsigned long)x);
		L=L*L;
		L=L/(0x40000L+((L+32767L)>>16L));
		x=(short)(((long)x*(0x10000L+(L<<1)))>>16L);
		y=(short)(((unsigned long)y*L+32767L)>>16);
		}while(y>0);

	return(x+1);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x
//    y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int slopi(int x ,int y)
{
	int     t;
	unsigned long   L;

	x=(x>0)?x:-x;
	y=(y>0)?y:-y;
	if(x<y){        t=x;    x=y;    y=t;    }
	if(y==0){
		return(x);
	}
	if(x==y){
		x++;
	}

	do{
		L=(((unsigned long)y<<16L) +((unsigned long)x>>1))/((unsigned long)x);
		L=L*L;
		L=L/(0x40000L+((L+32767L)>>16L));
		x=(int)(((long)x*(0x10000L+(L<<1)))>>16L);
		y=((unsigned long)y*L+32767L)>>16;
	}while(y>0);

	return(x+1);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    ax1
//    ay1
//    ax2
//    ay2
//    x
//    y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
//double GetLengthLine2Point(long ax1,long ay1,long ax2,long ay2
//			  ,long x  ,long y)

double GetLengthLine2Point(int ax1,int ay1,int ax2,int ay2
			  ,int x  ,int y)


/*      線分と点の距離を求める          finish debug

	(ax1,ay1) - (ax2,ay2) に線分の端点
	(x,y) に点座標を入れる
	*/
{
	double  len1,len2;
	//	long    X,Y;
	int X,Y;
	if(ax1==ax2){
		if(ay1<ay2){
			if(ay1<=y && y<=ay2){
				return(abs(x-ax1));
			}
			else if(y<ay1){
				return(hypot(ax1-x ,ay1-y));
			}
			else{
				return(hypot(ax2-x ,ay2-y));
			}
		}
		else{
			if(ay2<=y && y<=ay1){
				return(abs(x-ax1));
			}
			else if(y<ay2){
				return(hypot(ax2-x ,ay2-y));
			}
			else{
				return(hypot(ax1-x ,ay1-y));
			}
		}
	}
	else if(ay1==ay2){
		if(ax1<ax2){
			if(ax1<=x && x<=ax2){
				return(abs(y-ay1));
			}
			else if(x<ax1){
				return(hypot(ax1-x ,ay1-y));
			}
			else{
				return(hypot(ax2-x ,ay2-y));
			}
		}
		else{
			if(ax2<=x && x<=ax1){
				return(abs(y-ay1));
			}
			else if(x<ax2){
				return(hypot(ax2-x ,ay2-y));
			}
			else{
				return(hypot(ax1-x ,ay1-y));
			}
		}
	}
	len1 = hypot(ax1-x ,ay1-y);
	if((len2 = hypot(ax2-x ,ay2-y))<len1){
		len1=len2;
	}
	if(GetLinePointFoot(ax1,ay1,ax2,ay2,x,y ,X ,Y)==true){
		if((len2 = hypot(X-x ,Y-y))<len1){
			len1=len2;
		}
	}
	return(len1);
}

bool	ExtendLine(double x1,double y1,double x2,double y2 ,double AddedLen
				  ,double &X1,double &Y1,double &X2,double &Y2)
{
	double	Dx=x2-x1;
	double	Dy=y2-y1;
	double	L=hypot(Dx,Dy);
	if(L==0){
		X1=x1;
		Y1=y1;
		X2=x2;
		Y2=y2;
		return false;
	}
	double	Cx=(x1+x2)/2.0;
	double	Cy=(y1+y2)/2.0;
	X1=Cx+Dx*(1.0+AddedLen/L)/2.0;
	X2=Cx-Dx*(1.0+AddedLen/L)/2.0;
	Y1=Cy+Dy*(1.0+AddedLen/L)/2.0;
	Y2=Cy-Dy*(1.0+AddedLen/L)/2.0;
	return true;
}


double GetLengthLine2Point(double ax1,double ay1,double ax2,double ay2
			  ,double x  ,double y)


/*      線分と点の距離を求める          finish debug

	(ax1,ay1) - (ax2,ay2) に線分の端点
	(x,y) に点座標を入れる
	*/
{
	double  len1,len2;
	//	long    X,Y;
	double	X,Y;
	if(ax1==ax2){
		if(ay1<ay2){
			if(ay1<=y && y<=ay2){
				return(abs(x-ax1));
			}
			else if(y<ay1){
				return(hypot(ax1-x ,ay1-y));
			}
			else{
				return(hypot(ax2-x ,ay2-y));
			}
		}
		else{
			if(ay2<=y && y<=ay1){
				return(abs(x-ax1));
			}
			else if(y<ay2){
				return(hypot(ax2-x ,ay2-y));
			}
			else{
				return(hypot(ax1-x ,ay1-y));
			}
		}
	}
	else if(ay1==ay2){
		if(ax1<ax2){
			if(ax1<=x && x<=ax2){
				return(abs(y-ay1));
			}
			else if(x<ax1){
				return(hypot(ax1-x ,ay1-y));
			}
			else{
				return(hypot(ax2-x ,ay2-y));
			}
		}
		else{
			if(ax2<=x && x<=ax1){
				return(abs(y-ay1));
			}
			else if(x<ax2){
				return(hypot(ax2-x ,ay2-y));
			}
			else{
				return(hypot(ax1-x ,ay1-y));
			}
		}
	}
	len1 = hypot(ax1-x ,ay1-y);
	if((len2 = hypot(ax2-x ,ay2-y))<len1){
		len1=len2;
	}
	if(GetLinePointFoot(ax1,ay1,ax2,ay2,x,y ,X ,Y)==true){
		if((len2 = hypot(X-x ,Y-y))<len1){
			len1=len2;
		}
	}
	return(len1);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    x1
//    y1
//    x2
//    y2
//    px
//    py
//    X
//    Y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
//bool    GetLinePointFoot(long x1,long y1,long x2,long y2
//		,long px ,long py ,long &X ,long &Y)

bool    GetLinePointFoot(int x1,int y1,int x2,int y2
			,int px ,int py ,int &X ,int &Y)


/*      点から下ろした線分への足の座標を求める  finish debug

	(ax1,ay1) - (ax2,ay2) に線分の端点
	(px ,py)に点座標        を入れる

	(X ,Y) に足の座標を入れる

	線分の足座標が線分上にないとき、FALSE が返る
*/
{
	double  T = (double)(x1-x2)*(double)(x1-x2) + (double)(y1-y2)*(double)(y1-y2);
	if(T==0){
		return(false);
	}
	double  t = ((double)(px-x2)*(double)(x1-x2) + (double)(py-y2)*(double)(y1-y2))/T;
	if(t<0 || 1<t){
		return(false);
	}
	X=(long)(t*(double)(x1-x2)) + x2;
	Y=(long)(t*(double)(y1-y2)) + y2;
	return(true);
}

bool    GetLinePointFoot(double x1,double y1,double x2,double y2
			,double px ,double py ,double &X ,double &Y)


/*      点から下ろした線分への足の座標を求める  finish debug

	(ax1,ay1) - (ax2,ay2) に線分の端点
	(px ,py)に点座標        を入れる

	(X ,Y) に足の座標を入れる

	線分の足座標が線分上にないとき、FALSE が返る
*/
{
	double  T = (double)(x1-x2)*(double)(x1-x2) + (double)(y1-y2)*(double)(y1-y2);
	if(fabs(T)<0.000000001){
		return(false);
	}
	double  t = ((double)(px-x2)*(double)(x1-x2) + (double)(py-y2)*(double)(y1-y2))/T;
	if(t<0 || 1<t){
		return(false);
	}
	X=(double)(t*(double)(x1-x2)) + x2;
	Y=(double)(t*(double)(y1-y2)) + y2;
	return(true);
}
bool    GetLinePointFoot(double  A,double B,double C
						,double px ,double py ,double &X ,double &Y)
{
	double	D=A*A+B*B;
	if(D==0.0)
		return false;
	X=(B*B*px-A*(B*py+C))/D;
	Y=(A*A*py-B*(A*px+C))/D;
	return true;
}

bool    GetLimitlessLinePointFoot(double x1,double y1,double x2,double y2
			,double px ,double py ,double &X ,double &Y)


/*      点から下ろした直線への足の座標を求める  finish debug

	(ax1,ay1) - (ax2,ay2) に線分の端点
	(px ,py)に点座標        を入れる

	(X ,Y) に足の座標を入れる
*/
{
	double  T = (double)(x1-x2)*(double)(x1-x2) + (double)(y1-y2)*(double)(y1-y2);
	if(T==0){
		return(false);
	}
	double  t = ((double)(px-x2)*(double)(x1-x2) + (double)(py-y2)*(double)(y1-y2))/T;
	X=(double)(t*(double)(x1-x2)) + x2;
	Y=(double)(t*(double)(y1-y2)) + y2;
	return(true);
}
double	GetLengthLimitlessLine2Point(double ax1,double ay1,double ax2,double ay2
			  ,double x  ,double y)
{
	double	X ,Y;
	if(GetLimitlessLinePointFoot(ax1,ay1,ax2,ay2
								,x ,y ,X ,Y)==false){
		return 0.0;
	}
	return hypot(X-x,Y-y);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    PP
//    PQ
//    m
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
static	bool    Get3LevelResolveInner(double PP[3][2] ,double PQ[3][2] ,double m[6]);
bool    Get3LevelResolve(double PP[3][2] ,double PQ[3][2] ,double m[6])
{
	if(Get3LevelResolveInner(PP,PQ ,m)==true)
		return true;
	swap(PP[0][0],PP[2][0]);
	swap(PP[0][1],PP[2][1]);
	swap(PQ[0][0],PQ[2][0]);
	swap(PQ[0][1],PQ[2][1]);
	if(Get3LevelResolveInner(PP,PQ ,m)==true)
		return true;
	return false;
}
static	bool    Get3LevelResolveInner(double PP[3][2] ,double PQ[3][2] ,double m[6])
{
    double  d=(PP[0][0]-PP[1][0])*(PP[1][1]-PP[2][1])
            - (PP[1][0]-PP[2][0])*(PP[0][1]-PP[1][1]);
    double  w1=(PP[1][1]-PP[2][1])*(PQ[0][0]-PQ[1][0])
              -(PP[0][1]-PP[1][1])*(PQ[1][0]-PQ[2][0]);
	if(fabs(d)<0.00001){
        return(false);
	}
    m[0]=w1/d;
    double  q1=(PP[0][1]-PP[1][1]);
	if(fabs(q1)<0.00001){
        return(false);
	}
    m[1]=((PQ[0][0]-PQ[1][0])-m[0]*(PP[0][0]-PP[1][0]))/q1;

    m[2]=PQ[0][0]-m[0]*PP[0][0] - m[1]*PP[0][1];

    double  w2=(PP[1][1]-PP[2][1])*(PQ[0][1]-PQ[1][1])
              -(PP[0][1]-PP[1][1])*(PQ[1][1]-PQ[2][1]);

    m[3]=w2/d;
    m[4]=((PQ[0][1]-PQ[1][1])-m[3]*(PP[0][0]-PP[1][0]))/q1;
    m[5]=PQ[0][1]-m[3]*PP[0][0] - m[4]*PP[0][1];

    return(true);
}



/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    px1
//    py1
//    px2
//    py2
//    pd
//    D
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    GetBarCorner(long px1,long py1,long px2,long py2,long pd
		 ,long D[4][2])
/*	バーの４隅の座標を得る		finish debug

	(px1,py1)-(px2,py2) に線分端点、pd にバーの太さを入れる
	(D[0][0],D[0][1])-(D[1][0],D[1][1])は線分に沿った線になる
	(D[2][0],D[2][1])-(D[3][0],D[3][1])は線分に沿った線になる
	*/
{
	long	dx,dy;
	double	L = hypot(px1-px2,py1-py2);

	if(L<0.00001){
        return;
	}
	dx=(long)((double)pd*(double)(py1-py2)/L)>>1;
	dy=(long)((double)pd*(double)(px1-px2)/L)>>1;

	D[0][0]=px1+dx;
	D[0][1]=py1-dy;
	D[1][0]=px2+dx;
	D[1][1]=py2-dy;

	D[2][0]=px2-dx;
	D[2][1]=py2+dy;
	D[3][0]=px1-dx;
	D[3][1]=py1+dy;

}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    a
//    b
//    cx
//    cy
//    Dx
//    Dy
//    s
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
double  EllipseCalcFunc(double a ,double b ,double cx, double cy
                        ,double Dx, double Dy
                        ,double s)
{
    double  sins=sin(s);
    double  coss=cos(s);

    return((b*b-a*a)*sins*coss+b*(cy-Dy)*coss-a*(cx-Dx)*sins);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    a
//    b
//    cx
//    cy
//    Dx
//    Dy
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
double  EllipseCalcSita(double a ,double b ,double cx, double cy
                        ,double Dx, double Dy)
{
    double  s=0;
    for(int n=0;n<100;n++){
        double  e=EllipseCalcFunc(a ,b ,cx, cy ,Dx, Dy ,s);
        s-=e/(a*a+b*b);
		if(fabs(e)<0.5){
            break;
		}
    }
    return(s);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    a
//    b
//    cx
//    cy
//    Dx
//    Dy
//    X
//    Y
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    EllipseCalcNearestPoint(double a ,double b ,double cx, double cy
                        ,double Dx, double Dy
                        ,double &X, double &Y)
/*  楕円外の点から楕円に下ろした最短距離の楕円状の点を求める    */
{
    double  s=EllipseCalcSita(a ,b ,cx, cy
                        ,Dx, Dy);
    X=a*cos(s)+cx;
    Y=b*sin(s)+cy;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    cx
//    cy
//    r
//    Point
//    PointNumb
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool CalcCircle(double &cx ,double &cy, double &r
                                    ,int Point[][2] ,int PointNumb)
{
    double  Ex3=0.0;
    double  Ey3=0.0;
    double  Ex2=0.0;
    double  Ey2=0.0;
    double  Ex =0.0;
    double  Ey =0.0;
    double  Exy=0.0;
    double  Ex2y=0.0;
    double  Exy2=0.0;

    for(int i=0;i<PointNumb;i++){
        Ex3 +=(double)Point[i][0]*(double)Point[i][0]*(double)Point[i][0];
        Ey3 +=(double)Point[i][1]*(double)Point[i][1]*(double)Point[i][1];
        Ex2 +=(double)Point[i][0]*(double)Point[i][0];
        Ey2 +=(double)Point[i][1]*(double)Point[i][1];
        Ex  +=(double)Point[i][0];
        Ey  +=(double)Point[i][1];
        Exy +=(double)Point[i][0]*(double)Point[i][1];
        Ex2y+=(double)Point[i][0]*(double)Point[i][0]*(double)Point[i][1];
        Exy2+=(double)Point[i][0]*(double)Point[i][1]*(double)Point[i][1];
        }
    double  n=PointNumb;
	if(n==0){
        return(false);
	}
    double  M=2.0*((Ex2-Ex*Ex/n)*(Ey2-Ey*Ey/n)-(Exy-Ex*Ey/n)*(Exy-Ex*Ey/n));
    double  L=(Ex3+Exy2-Ex*(Ex2+Ey2)/n)*(Ey2-Ey*Ey/n)
             -(Ey3+Ex2y-Ey*(Ex2+Ey2)/n)*(Exy-Ex*Ey/n);
	if(fabs(M)<0.001){
        return(false);
	}
    cx=L/M;

    M=2.0*(Exy-Ex*Ey/n);
    L=Ex3+Exy2-Ex*(Ex2+Ey2)/n-2.0*(Ex2-Ex*Ex/n)*cx;
    if(fabs(M)<0.001){
        M=2.0*(Ey2-Ey*Ey/n);
        L=Ey3+Ex2y-Ey*(Ex2+Ey2)/n-2.0*(Exy-Ex*Ey/n)*cx;
        if(fabs(M)<0.001){
            return(false);
        }
    }
    cy=L/M;

    r=sqrt(cx*cx+cy*cy+(-2.0*(Ex*cx+Ey*cy)+Ex2+Ey2)/n);
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    coss1
//    sins1
//    c1
//    coss2
//    sins2
//    c2
//    Point
//    PointNumb
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool CalcLine(double &coss1 ,double &sins1, double &c1
             ,double &coss2 ,double &sins2, double &c2
             ,int Point[][2] ,int PointNumb)
{
    double  X2=0.0;
    double  Y2=0.0;
    double  X1=0.0;
    double  Y1=0.0;
    double  Z =0.0;

    for(int i=0;i<PointNumb;i++){
        X2 +=(double)Point[i][0]*(double)Point[i][0];
        Y2 +=(double)Point[i][1]*(double)Point[i][1];
        X1 +=(double)Point[i][0];
        Y1 +=(double)Point[i][1];
        Z  +=(double)Point[i][0]*(double)Point[i][1];
        }

    double  n=PointNumb;
    double  S=-X2+Y2+(X1*X1-Y1*Y1)/n;
    double  T=Z-2*X1*Y1/n;

    double  w=sqrt(S*S+T*T);
	if(w<0.0001){
        return(false);
	}
    sins1= sqrt((w-S)/(2.0*w));
    coss1=-sqrt((w+S)/(2.0*w));
    c1=-((X1*coss1+Y1*sins1)/n);

    sins2=-coss1;
    coss2= sins1;
    c2=-((X1*coss2+Y1*sins2)/n);
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    a
//    b
//    s
//    y
//    x1
//    x2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int RotEllipseYCut(double a ,double b ,double s
                  ,double y ,double &x1 ,double &x2)
{
    double  coss=cos(s);
    double  sins=sin(s);

    return(RotEllipseYCut(a ,b ,coss,sins
                              ,y ,x1 ,x2));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    a
//    b
//    coss
//    sins
//    y
//    x1
//    x2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int RotEllipseYCut(double a ,double b ,double coss,double sins
                  ,double y ,double &x1 ,double &x2)
{
    double  A=b*b*coss*coss+a*a*sins*sins;
    double  B=(a*a-b*b)*y*sins*coss;
    double  C=y*y*(a*a*coss*coss+b*b*sins*sins)-a*a*b*b;

	if(fabs(A)<0.000000001){
        return(0);
	}
    double  D=B*B-A*C;
	if(D<0){
        return(0);
	}
    if(fabs(D/A)<0.00001){
        x1=x2=-B/A;
        return(1);
        }
    double  M=sqrt(D);
    x1=(-B+M)/A;
    x2=(-B-M)/A;

    return(2);
}

double	GetAreaDot(int Px1,int Py1
				,  int Px2,int Py2
				,  int Px3,int Py3)
/*	３点で結ぶ三角形の面積を計算する	*/
{
	int	vx=Px2-Px1;
	int	vy=Py2-Py1;
	int	ux=Px3-Px1;
	int	uy=Py3-Py1;

	double	U=hypot(ux,uy);
	double	t=(ux*vx+uy*vy)/(U*U);
	double	wx=vx-t*ux;
	double	wy=vy-t*uy;
	double	W=hypot(wx,wy);
	return U*W*0.5;
}
double	GetAreaDot(double Px1,double Py1
				,  double Px2,double Py2
				,  double Px3,double Py3)
/*	３点で結ぶ三角形の面積を計算する	*/
{
	double	vx=Px2-Px1;
	double	vy=Py2-Py1;
	double	ux=Px3-Px1;
	double	uy=Py3-Py1;

	double	U=hypot(ux,uy);
	double	t=(ux*vx+uy*vy)/(U*U);
	double	wx=vx-t*ux;
	double	wy=vy-t*uy;
	double	W=hypot(wx,wy);
	return U*W/2.0;
}




int		GetCrossCircleLine(double cx ,double cy, double r
						 ,double x1		,double y1	,double x2	, double y2
						 ,double &sx1	,double &sy1,double &sx2, double &sy2)
{
	double	Dx=x2-x1;
	double	Dy=y2-y1;

	double	a=Dx*Dx+Dy*Dy;
	double	b=Dx*(x1-cx)+Dy*(y1-cy);
	double	c=x1*(x1-2*cx)+y1*(y1-2*cy)+cx*cx+cy*cy-r*r;
	double	D=b*b-a*c;
	if(D<0)
		return 0;
	if(D==0.0){
		double	t=(-b)/a;
		if(0<=t && t<=1.0){
			sx1=Dx*t+x1;
			sy1=Dy*t+y1;
			return 1;
		}
		return 0;
	}

	D=sqrt(D);
	double	t1=(-b+D)/a;
	double	t2=(-b-D)/a;

	if(0<=t1 && t1<=1.0){
		sx1=Dx*t1+x1;
		sy1=Dy*t1+y1;
		if(0<=t2 && t2<=1.0){
			sx2=Dx*t2+x1;
			sy2=Dy*t2+y1;
			return 2;
		}
		return 1;
	}
	if(0<=t2 && t2<=1.0){
		sx1=Dx*t2+x1;
		sy1=Dy*t2+y1;
		return 1;
	}
	return 0;
}

int		GetCrossCircleCircle(double cx1 ,double cy1, double r1
							,double cx2 ,double cy2, double r2
							,double &sx1,double &sy1 ,double &sx2, double &sy2)
{
	double	cx12	=cx1-cx2;
	double	cy12	=cy1-cy2;
	double	M=cx1*cx1-cx2*cx2 +cy1*cy1-cy2*cy2 - (r1*r1-r2*r2);
	double	K=cx1*cx1-cx2*cx2 - (cy1-cy2)*(cy1-cy2)- (r1*r1-r2*r2);

	double	A=cx12*cx12+cy12*cy12;
	if(A<=0)
		return 0;
	double	B=2*cy12*cy12*cx1 + K*cx12;
	double	C=cy12*cy12*cx1*cx1+K*K/4-cy12*cy12*r1*r1;

	double	D=B*B-4*A*C;
	if(D<0)
		return 0;
	double	E=sqrt(D);
	sx1= (B+E)/(2*A);
	if(cy12!=0.0)
		sy1=(M-2*cx12*sx1)/(2*cy12);
	else{
		sy1=cy1;
	}
	if(E==0.0)
		return 1;
	sx2= (B-E)/(2*A);
	if(cy12!=0.0)
		sy2=(M-2*cx12*sx2)/(2*cy12);
	else
		sy2=cy2;
	return 2;
}

int		CrossLineArc(double x1 ,double y1 ,double x2, double y2
					,double cx ,double cy ,double r ,double startangle ,double endangle
					,double &X1,double &Y1,double &X2,double &Y2
					,double &Angle1,double &Angle2)
{
	double	sx1,sy1 ,sx2, sy2;
	int	n=GetCrossCircleLine(cx ,cy, r
						,x1,y1 ,x2, y2
						,sx1,sy1 ,sx2, sy2);
	if(n==0)
		return 0;
	if(n==1){
		double	s=GetSita(sx1-cx,sy1-cy);
		if((startangle<=endangle && startangle<=s && s<=endangle)
		|| (startangle>endangle && (startangle<=s || s<=endangle))){ 
			X1=sx1;
			Y1=sy1;
			Angle1=s;
			return 1;
		}
		return 0;
	}
	if(n==2){
		double	s1=GetSita(sx1-cx,sy1-cy);
		if((startangle<=endangle && startangle<=s1 && s1<=endangle)
		|| (startangle>endangle && (startangle<=s1 || s1<=endangle))){ 
			X1=sx1;
			Y1=sy1;
			Angle1=s1;

			double	s2=GetSita(sx2-cx,sy2-cy);
			if((startangle<=endangle && startangle<=s2 && s2<=endangle)
			|| (startangle>endangle && (startangle<=s2 || s2<=endangle))){ 
				X2=sx2;
				Y2=sy2;
				Angle2=s2;
				return 2;
			}
			return 1;
		}
		double	s2=GetSita(sx2-cx,sy2-cy);
		if((startangle<=endangle && startangle<=s2 && s2<=endangle)
		|| (startangle>endangle && (startangle<=s2 || s2<=endangle))){ 
			X1=sx2;
			Y1=sy2;
			Angle1=s2;
			return 1;
		}
		return 0;
	}
	return 0;
}
int		CrossArcArc( double cx1 ,double cy1 ,double r1 ,double startangle1 ,double endangle1
					,double cx2 ,double cy2 ,double r2 ,double startangle2 ,double endangle2
					,double &AngleA1,double &AngleA2
					,double &AngleB1,double &AngleB2)
{
	double	sx1,sy1 ,sx2, sy2;
	int	n=GetCrossCircleCircle(cx1 ,cy1, r1
							  ,cx2 ,cy2, r2
								,sx1,sy1 ,sx2, sy2);
	if(n==1){
		double	s1=GetSita(sx1-cx1,sy1-cy1);
		double	s2=GetSita(sx1-cx2,sy1-cy2);

		if(((startangle1<=endangle1 && startangle1<=s1 && s1<=endangle1)
		 || (startangle1>endangle1 && (startangle1<=s1 || s1<=endangle1)))
		&& ((startangle2<=endangle2 && startangle2<=s2 && s2<=endangle2)
		 || (startangle2>endangle2 && (startangle2<=s2 || s2<=endangle2))) ){ 
			AngleA1=s1;
			AngleB1=s2;
			return 1;
		}
		return 0;
	}
	if(n==2){
		double	s1=GetSita(sx1-cx1,sy1-cy1);
		double	s2=GetSita(sx1-cx2,sy1-cy2);
		double	t1=GetSita(sx2-cx1,sy2-cy1);
		double	t2=GetSita(sx2-cx2,sy2-cy2);

		if(((startangle1<=endangle1 && startangle1<=s1 && s1<=endangle1)
		 || (startangle1>endangle1 && (startangle1<=s1 || s1<=endangle1)))
		&& ((startangle2<=endangle2 && startangle2<=s2 && s2<=endangle2)
		 || (startangle2>endangle2 && (startangle2<=s2 || s2<=endangle2))) ){ 
			AngleA1=s1;
			AngleB1=s2;

			if(((startangle1<=endangle1 && startangle1<=t1 && t1<=endangle1)
			 || (startangle1>endangle1 && (startangle1<=t1 || t1<=endangle1)))
			&& ((startangle2<=endangle2 && startangle2<=t2 && t2<=endangle2)
			 || (startangle2>endangle2 && (startangle2<=t2 || t2<=endangle2))) ){ 
				AngleA2=t1;
				AngleB2=t2;
				return 2;
			}
			return 1;
		}
		if(((startangle1<=endangle1 && startangle1<=t1 && t1<=endangle1)
		 || (startangle1>endangle1 && (startangle1<=t1 || t1<=endangle1)))
		&& ((startangle2<=endangle2 && startangle2<=t2 && t2<=endangle2)
		 || (startangle2>endangle2 && (startangle2<=t2 || t2<=endangle2))) ){ 
			AngleA1=t1;
			AngleB1=t2;
			return 1;
		}
		return 0;
	}
	return 0;
}
bool    CheckOverlapRectArc(double rx1, double ry1, double rx2, double ry2							//Box
							,double cx ,double cy ,double r,double startangle ,double endangle)		//Arc
{
	double X1,Y1,X2,Y2;
	double Angle1, Angle2;

	int	n1=CrossLineArc(rx1,ry1,rx1,ry2
					,cx ,cy ,r,startangle ,endangle
					,X1,Y1,X2,Y2
					,Angle1,Angle2);
	if(n1>0)
		return true;
	int	n2=CrossLineArc(rx1,ry2,rx2,ry2
					,cx ,cy ,r,startangle ,endangle
					,X1,Y1,X2,Y2
					,Angle1,Angle2);
	if(n2>0)
		return true;
	int	n3=CrossLineArc(rx2,ry2,rx2,ry1
					,cx ,cy ,r,startangle ,endangle
					,X1,Y1,X2,Y2
					,Angle1,Angle2);
	if(n3>0)
		return true;
	int	n4=CrossLineArc(rx2,ry1,rx1,ry1
					,cx ,cy ,r,startangle ,endangle
					,X1,Y1,X2,Y2
					,Angle1,Angle2);
	if(n4>0)
		return true;
	double	Px=cx+r*cos(startangle);
	double	Py=cy+r*sin(startangle);

	if(rx1>rx2)
		swap(rx1,rx2);
	if(ry1>ry2)
		swap(ry1,ry2);
	if(rx1<=Px && Px<=rx2 && ry1<=Py && Py<=ry2)
		return true;
	return false;
}

double GetLengthArc2Point(double cx ,double cy ,double r,double startangle ,double endangle
						,double x  ,double y)
{
	double	s=GetSita(x-cx,y-cy);
	if((startangle<endangle && startangle<=s && s<=endangle)
	|| (startangle>endangle && (startangle<=s || s<=endangle))){
		return fabs(hypot(x-cx,y-cy)-r);
	}
	double	x1=cx+r*cos(startangle);
	double	y1=cy+r*sin(startangle);
	double	x2=cx+r*cos(endangle);
	double	y2=cy+r*sin(endangle);
	double	L1=hypot(x-x1,y-y1);
	double	L2=hypot(x-x2,y-y2);
	return min(L1,L2);
}

bool	CheckInsidePolygon  (double Points[][2],int PointNumb
							,double x, double y)
{
	int	PNumb=0;
	int	MNumb=0;

	for(int i=0;i<PointNumb;i++){
		int	j=i+1;
		if(j>=PointNumb)
			j-=PointNumb;
		double	ax=Points[j][0] - Points[i][0];
		double	ay=Points[j][1] - Points[i][1];
		double	bx=x - Points[i][0];
		double	by=y - Points[i][1];
		double	D=ax*by-ay*bx;
		if(D>=0)
			PNumb++;
		else
			MNumb++;
	}
	if(PNumb==0 || MNumb==0)
		return true;
	return false;
}


inline	bool	IsInside(QPoint &p, int x1 ,int y1 ,int x2 ,int y2)
{
	if(x1<=p.x() && p.x()<x2 && y1<=p.y() && p.y()<y2)
		return true;
	return false;
}
inline	bool	IsInside(QPointF &p, double x1 ,double y1 ,double x2 ,double y2)
{
	if(x1<=p.x() && p.x()<x2 && y1<=p.y() && p.y()<y2)
		return true;
	return false;
}
inline	bool	IsInside(int px, int py, int x1 ,int y1 ,int x2 ,int y2)
{
	if(x1<=px && px<x2 && y1<=py && py<y2)
		return true;
	return false;
}
inline	bool	IsInside(double px, double py, double x1 ,double y1 ,double x2 ,double y2)
{
	if(x1<=px && px<x2 && y1<=py && py<y2)
		return true;
	return false;
}
int		CrossRectLine(int px1,int py1, int px2, int py2		//Line
					 ,int rx1,int ry1 ,int rx2, int ry2		//Rectangle
					 ,int P[2][2])
{
	int		N=0;
	long	X ,Y;
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx1,ry1,rx2,ry1 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx2,ry1,rx2,ry2 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx2,ry2,rx1,ry2 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx1,ry2,rx1,ry1 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	return N;
}
int		CrossRectLine(double px1,double py1, double px2, double py2		//Line
					 ,double rx1,double ry1 ,double rx2, double ry2		//Rectangle
					 ,double P[2][2])
{
	int		N=0;
	double	X ,Y;
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx1,ry1,rx2,ry1 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx2,ry1,rx2,ry2 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx2,ry2,rx1,ry2 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	if(GetCrossInnerPoint(px1,py1,px2,py2,rx1,ry2,rx1,ry1 , X,Y)==true){
		P[N][0]=X;
		P[N][1]=Y;
		N++;
	}
	return N;
}

static	int	SortCrossPointFunc(const void *a ,const void *b)
{
	int	pa=*(int *)a;
	int	pb=*(int *)b;
	return pa-pb;
}

static	int	SortCrossPointFuncF(const void *a ,const void *b)
{
	double	pa=*(double *)a;
	double	pb=*(double *)b;
	double	d=pa-pb;
	if(d<0)
		return -1;
	if(d>0)
		return 1;
	return 0;
}

static	int	SortDoubleFunc(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;

	if(*pa>*pb)
		return 1;
	if(*pa<*pb)
		return -1;
	return 0;
}
const double	DeltaDouble=1;
bool	IsIncludeYDim(QPoint Source[], int SourcePointNumb ,int X ,int Y);
bool	IsIncludeYDim(QPointF Source[], int SourcePointNumb ,double X ,double Y);

bool	IsInside(QPoint Source[], int SourcePointNumb ,int X,int Y)
{
	if(SourcePointNumb==0)
		return false;

	double	XDim[1000000];
	int		XDimNumb=0;
	double	CurrentX=Source[0].x();
	double	CurrentY=Source[0].y();

	for(int i=1;i<SourcePointNumb;i++){
		if(CurrentY<Source[i].y() && CurrentY<=Y && Y<=Source[i].y()){
			if(CurrentY!=Y){
				double	tX;
				if(GetCrossHalfInnerPoint(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , Y , tX )==true){
					XDim[XDimNumb]=tX;
					XDimNumb++;
				}
			}
			else{
				if(Source[i-1].y()<Y){
					XDim[XDimNumb]=Source[i].x();
					XDimNumb++;
				}
			}
		}
		else if(CurrentY>Source[i].y() && Source[i].y()<=Y && Y<=CurrentY){
			if(CurrentY!=Y){
				double	tX;
				if(GetCrossHalfInnerPoint(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , Y , tX )==true){
					XDim[XDimNumb]=tX;
					XDimNumb++;
				}
			}
			else{
				int	j=i-1;
				if(j<0){
					j=SourcePointNumb-1;
				}
				if(Source[j].y()>Y){
					XDim[XDimNumb]=Source[i].x();
					XDimNumb++;
				}
			}
		}
		else if(Source[i].y()==Source[i+1].y() && Source[i].y()==Y){
			XDim[XDimNumb]=Source[i].x();
			XDimNumb++;
		}

		CurrentX=Source[i].x();
		CurrentY=Source[i].y();
	}

	QSort(XDim,XDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<XDimNumb-1;){
		double	d=XDim[k+1]-XDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(XDimNumb-1);m++){
				XDim[m]=XDim[m+1];
			}
			XDimNumb--;
		}
		else{
			k++;
		}
	}
	if((XDimNumb&1)!=0)
		return false;
	if(XDimNumb==0)
		return false;

	for(int k=0;k<XDimNumb;k+=2){
		double	Lx1=XDim[k];
		double	Lx2=XDim[k+1];
		if(Lx1<=X && X<=Lx2){
			return true;
		}
	}
	return IsIncludeYDim(Source,SourcePointNumb,X,Y);
	
	//return false;
}

bool	IsIncludeYDim(QPoint Source[], int SourcePointNumb ,int X ,int Y)
{
	if(SourcePointNumb==0)
		return false;

	double	YDim[1000000];
	int		YDimNumb=0;
	double	CurrentX=Source[0].x();
	double	CurrentY=Source[0].y();

	for(int i=1;i<SourcePointNumb;i++){
		if(CurrentX<Source[i].x() && CurrentX<=X && X<=Source[i].x()){
			if(CurrentX!=X){
				double	tY;
				if(GetCrossHalfInnerPointX(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , X , tY )==true){
					YDim[YDimNumb]=tY;
					YDimNumb++;
				}
			}
			else{
				if(Source[i-1].x()<X){
					YDim[YDimNumb]=Source[i].y();
					YDimNumb++;
				}
			}
		}
		else if(CurrentX>Source[i].x() && Source[i].x()<=X && X<=CurrentX){
			if(CurrentX!=X){
				double	tY;
				if(GetCrossHalfInnerPointX(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , X , tY )==true){
					YDim[YDimNumb]=tY;
					YDimNumb++;
				}
			}
			else{
				int	j=i-1;
				if(j<0){
					j=SourcePointNumb-1;
				}
				if(Source[j].x()>X){
					YDim[YDimNumb]=Source[i].y();
					YDimNumb++;
				}
			}
		}
		else if(Source[i].x()==Source[i+1].x() && Source[i].x()==X){
			YDim[YDimNumb]=Source[i].y();
			YDimNumb++;
		}
		

		CurrentX=Source[i].x();
		CurrentY=Source[i].y();
	}

	QSort(YDim,YDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<YDimNumb-1;){
		double	d=YDim[k+1]-YDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(YDimNumb-1);m++){
				YDim[m]=YDim[m+1];
			}
			YDimNumb--;
		}
		else{
			k++;
		}
	}
	if((YDimNumb&1)!=0)
		return false;
	if(YDimNumb==0)
		return false;

	for(int k=0;k<YDimNumb;k+=2){
		double	Ly1=YDim[k];
		double	Ly2=YDim[k+1];
		if(Ly1<=Y && Y<=Ly2){
			return true;
		}
	}
	
	return false;
}

bool	IsInside(QPointF Source[], int SourcePointNumb ,double X,double Y)
{
	if(SourcePointNumb==0)
		return false;

	double	XDim[1000000];
	int		XDimNumb=0;
	double	CurrentX=Source[0].x();
	double	CurrentY=Source[0].y();

	for(int i=1;i<SourcePointNumb;i++){
		if(CurrentY<Source[i].y() && CurrentY<=Y && Y<=Source[i].y()){
			if(CurrentY!=Y){
				double	tX;
				if(GetCrossHalfInnerPoint(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , Y , tX )==true){
					XDim[XDimNumb]=tX;
					XDimNumb++;
				}
			}
			else{
				if(Source[i-1].y()<Y){
					XDim[XDimNumb]=Source[i].x();
					XDimNumb++;
				}
			}
		}
		else if(CurrentY>Source[i].y() && Source[i].y()<=Y && Y<=CurrentY){
			if(CurrentY!=Y){
				double	tX;
				if(GetCrossHalfInnerPoint(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , Y , tX )==true){
					XDim[XDimNumb]=tX;
					XDimNumb++;
				}
			}
			else{
				int	j=i-1;
				if(j<0){
					j=SourcePointNumb-1;
				}
				if(Source[j].y()>Y){
					XDim[XDimNumb]=Source[i].x();
					XDimNumb++;
				}
			}
		}
		else if(Source[i].y()==Source[i+1].y() && Source[i].y()==Y){
			XDim[XDimNumb]=Source[i].x();
			XDimNumb++;
		}

		CurrentX=Source[i].x();
		CurrentY=Source[i].y();
	}

	QSort(XDim,XDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<XDimNumb-1;){
		double	d=XDim[k+1]-XDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(XDimNumb-1);m++){
				XDim[m]=XDim[m+1];
			}
			XDimNumb--;
		}
		else{
			k++;
		}
	}
	if((XDimNumb&1)!=0)
		return false;
	if(XDimNumb==0)
		return false;

	for(int k=0;k<XDimNumb;k+=2){
		double	Lx1=XDim[k];
		double	Lx2=XDim[k+1];
		if(Lx1<=X && X<=Lx2){
			return true;
		}
	}
	return IsIncludeYDim(Source,SourcePointNumb,X,Y);
	
	//return false;
}

bool	IsIncludeYDim(QPointF Source[], int SourcePointNumb ,double X ,double Y)
{
	if(SourcePointNumb==0)
		return false;

	double	YDim[1000000];
	int		YDimNumb=0;
	double	CurrentX=Source[0].x();
	double	CurrentY=Source[0].y();

	for(int i=1;i<SourcePointNumb;i++){
		if(CurrentX<Source[i].x() && CurrentX<=X && X<=Source[i].x()){
			if(CurrentX!=X){
				double	tY;
				if(GetCrossHalfInnerPointX(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , X , tY )==true){
					YDim[YDimNumb]=tY;
					YDimNumb++;
				}
			}
			else{
				if(Source[i-1].x()<X){
					YDim[YDimNumb]=Source[i].y();
					YDimNumb++;
				}
			}
		}
		else if(CurrentX>Source[i].x() && Source[i].x()<=X && X<=CurrentX){
			if(CurrentX!=X){
				double	tY;
				if(GetCrossHalfInnerPointX(CurrentX,CurrentY
										, Source[i].x(),Source[i].y() , X , tY )==true){
					YDim[YDimNumb]=tY;
					YDimNumb++;
				}
			}
			else{
				int	j=i-1;
				if(j<0){
					j=SourcePointNumb-1;
				}
				if(Source[j].x()>X){
					YDim[YDimNumb]=Source[i].y();
					YDimNumb++;
				}
			}
		}
		else if(Source[i].x()==Source[i+1].x() && Source[i].x()==X){
			YDim[YDimNumb]=Source[i].y();
			YDimNumb++;
		}
		

		CurrentX=Source[i].x();
		CurrentY=Source[i].y();
	}

	QSort(YDim,YDimNumb,sizeof(double),SortDoubleFunc);
	for(int k=0;k<YDimNumb-1;){
		double	d=YDim[k+1]-YDim[k];
		if(d<DeltaDouble){
			for(int m=k+1;m<(YDimNumb-1);m++){
				YDim[m]=YDim[m+1];
			}
			YDimNumb--;
		}
		else{
			k++;
		}
	}
	if((YDimNumb&1)!=0)
		return false;
	if(YDimNumb==0)
		return false;

	for(int k=0;k<YDimNumb;k+=2){
		double	Ly1=YDim[k];
		double	Ly2=YDim[k+1];
		if(Ly1<=Y && Y<=Ly2){
			return true;
		}
	}
	
	return false;
}
int		ClipPolygon(QPoint Source[], int SourcePointNumb ,QPoint *Dest[] ,int DestPointNumb[] ,int MaxDicCount
				,int x1 ,int y1 ,int x2 ,int y2
				,bool &RetClipped)
				//Buggy
{
	struct	InsideLine
	{
		int	x1,y1,x2,y2;
		bool	Inside;
	};
	struct	InsideLine	*LineDim=new struct	InsideLine[SourcePointNumb*3];
	int		LineDimNumb=0;
	int		CrossedPointTop   [100];
	int		CrossedPointTopNumb=0;
	int		CrossedPointLeft  [100];
	int		CrossedPointLeftNumb=0;
	int		CrossedPointRight [100];
	int		CrossedPointRightNumb=0;
	int		CrossedPointBottom[100];
	int		CrossedPointBottomNumb=0;

	for(int i=0;i<SourcePointNumb;i++){
		int	j=i+1;
		if(j>=SourcePointNumb)
			j=0;
		int	P[2][2];
		int	N=CrossRectLine(Source[i].x(),Source[i].y(), Source[j].x(), Source[j].y()
			 ,x1,y1 ,x2, y2
			 ,P);
		if(N==0){
			if(Source[i].x()!=Source[j].x() || Source[i].y()!=Source[j].y()){
				LineDim[LineDimNumb].x1=Source[i].x();
				LineDim[LineDimNumb].y1=Source[i].y();
				LineDim[LineDimNumb].x2=Source[j].x();
				LineDim[LineDimNumb].y2=Source[j].y();
				LineDimNumb++;
			}
		}
		else if(N==1){
			if(Source[i].x()!=P[0][0] || Source[i].y()!=P[0][1]){
				LineDim[LineDimNumb].x1=Source[i].x();
				LineDim[LineDimNumb].y1=Source[i].y();
				LineDim[LineDimNumb].x2=P[0][0];
				LineDim[LineDimNumb].y2=P[0][1];
				LineDimNumb++;
			}
			if(Source[j].x()!=P[0][0] || Source[j].y()!=P[0][1]){
				LineDim[LineDimNumb].x1=P[0][0];
				LineDim[LineDimNumb].y1=P[0][1];
				LineDim[LineDimNumb].x2=Source[j].x();
				LineDim[LineDimNumb].y2=Source[j].y();
				LineDimNumb++;
			}
			if(P[0][1]==y1){
				CrossedPointTop[CrossedPointTopNumb]=P[0][0];
				CrossedPointTopNumb++;
			}
			else if(P[0][1]==y2){
				CrossedPointBottom[CrossedPointBottomNumb]=P[0][0];
				CrossedPointBottomNumb++;
			}
			else if(P[0][0]==x1){
				CrossedPointLeft[CrossedPointLeftNumb]=P[0][1];
				CrossedPointLeftNumb++;
			}
			else if(P[0][0]==x2){
				CrossedPointRight[CrossedPointRightNumb]=P[0][1];
				CrossedPointRightNumb++;
			}
		}
		else if(N==2){
			if(hypot(Source[i].x()-P[0][0] ,Source[i].y()-P[0][1])>hypot(Source[i].x()-P[1][0] ,Source[i].y()-P[1][1])){
				swap(P[0][0],P[1][0]);
				swap(P[0][1],P[1][1]);
			}
			if(Source[i].x()!=P[0][0] || Source[i].y()!=P[0][1]){
				LineDim[LineDimNumb].x1=Source[i].x();
				LineDim[LineDimNumb].y1=Source[i].y();
				LineDim[LineDimNumb].x2=P[0][0];
				LineDim[LineDimNumb].y2=P[0][1];
				LineDimNumb++;
			}
			if(P[0][0]!=P[1][0] || P[0][1]!=P[1][1]){
				LineDim[LineDimNumb].x1=P[0][0];
				LineDim[LineDimNumb].y1=P[0][1];
				LineDim[LineDimNumb].x2=P[1][0];
				LineDim[LineDimNumb].y2=P[1][1];
				LineDimNumb++;
			}
			if(Source[j].x()!=P[1][0] || Source[j].y()!=P[1][1]){
				LineDim[LineDimNumb].x1=P[1][0];
				LineDim[LineDimNumb].y1=P[1][1];
				LineDim[LineDimNumb].x2=Source[j].x();
				LineDim[LineDimNumb].y2=Source[j].y();
				LineDimNumb++;
			}
			if(P[0][1]==y1){
				CrossedPointTop[CrossedPointTopNumb]=P[0][0];
				CrossedPointTopNumb++;
			}
			else if(P[0][1]==y2){
				CrossedPointBottom[CrossedPointBottomNumb]=P[0][0];
				CrossedPointBottomNumb++;
			}
			else if(P[0][0]==x1){
				CrossedPointLeft[CrossedPointLeftNumb]=P[0][1];
				CrossedPointLeftNumb++;
			}
			else if(P[0][0]==x2){
				CrossedPointRight[CrossedPointRightNumb]=P[0][1];
				CrossedPointRightNumb++;
			}
			if(P[1][1]==y1){
				CrossedPointTop[CrossedPointTopNumb]=P[1][0];
				CrossedPointTopNumb++;
			}
			else if(P[1][1]==y2){
				CrossedPointBottom[CrossedPointBottomNumb]=P[1][0];
				CrossedPointBottomNumb++;
			}
			else if(P[1][0]==x1){
				CrossedPointLeft[CrossedPointLeftNumb]=P[1][1];
				CrossedPointLeftNumb++;
			}
			else if(P[1][0]==x2){
				CrossedPointRight[CrossedPointRightNumb]=P[1][1];
				CrossedPointRightNumb++;
			}
		}
	}
	for(int i=0;i<LineDimNumb;i++){
		LineDim[i].Inside=IsInside((LineDim[i].x1+LineDim[i].x2)/2, (LineDim[i].y1+LineDim[i].y2)/2, x1 ,y1 ,x2 ,y2);
	}
				
	CrossedPointTop[CrossedPointTopNumb]=x1;
	CrossedPointTopNumb++;
	CrossedPointTop[CrossedPointTopNumb]=x2;
	CrossedPointTopNumb++;
	CrossedPointBottom[CrossedPointBottomNumb]=x1;
	CrossedPointBottomNumb++;
	CrossedPointBottom[CrossedPointBottomNumb]=x2;
	CrossedPointBottomNumb++;
	CrossedPointLeft[CrossedPointLeftNumb]=y1;
	CrossedPointLeftNumb++;
	CrossedPointLeft[CrossedPointLeftNumb]=y2;
	CrossedPointLeftNumb++;
	CrossedPointRight[CrossedPointRightNumb]=y1;
	CrossedPointRightNumb++;
	CrossedPointRight[CrossedPointRightNumb]=y2;
	CrossedPointRightNumb++;

	QSort(CrossedPointTop	,CrossedPointTopNumb	,sizeof(CrossedPointTop	  [0]),SortCrossPointFunc);
	QSort(CrossedPointBottom,CrossedPointBottomNumb	,sizeof(CrossedPointBottom[0]),SortCrossPointFunc);
	QSort(CrossedPointLeft	,CrossedPointLeftNumb	,sizeof(CrossedPointLeft  [0]),SortCrossPointFunc);
	QSort(CrossedPointRight	,CrossedPointRightNumb	,sizeof(CrossedPointRight [0]),SortCrossPointFunc);

	
	DestPointNumb[0]=0;
	int	Index=0;
	for(int	RetNumb=0;;RetNumb++){
		for(Index=0;Index<LineDimNumb;Index++){
			if(LineDim[Index].Inside==true){
				break;
			}
		}
		if(RetNumb+1>=MaxDicCount){
			delete	[]LineDim;
			return -1;
		}
		DestPointNumb[RetNumb]=0;
		if(Index>=LineDimNumb){
			if(RetNumb==0 && DestPointNumb[RetNumb]==0){
				if(IsInside(Source, SourcePointNumb ,x1, y1)==true){
					Dest[0][0].setX(x1);
					Dest[0][0].setY(y1);
					Dest[0][1].setX(x2);
					Dest[0][1].setY(y1);
					Dest[0][2].setX(x2);
					Dest[0][2].setY(y2);
					Dest[0][3].setX(x1);
					Dest[0][3].setY(y2);
					DestPointNumb[RetNumb]=4;
				}
			}
			delete	[]LineDim;
			RetNumb++;
			return RetNumb;
		}
		int	LastX=99999999,LastY=99999999;

		if(DestPointNumb[RetNumb]==0){
			Dest[RetNumb][DestPointNumb[RetNumb]].setX(LineDim[Index].x1);
			Dest[RetNumb][DestPointNumb[RetNumb]].setY(LineDim[Index].y1);
			DestPointNumb[RetNumb]++;
		}
		Dest[RetNumb][DestPointNumb[RetNumb]].setX(LineDim[Index].x2);
		Dest[RetNumb][DestPointNumb[RetNumb]].setY(LineDim[Index].y2);
		LastX=LineDim[Index].x2;
		LastY=LineDim[Index].y2;
		DestPointNumb[RetNumb]++;
		LineDim[Index].Inside=false;

		while((LastX!=Dest[RetNumb][0].x() || LastY!=Dest[RetNumb][0].y()) && Index>=0){
			Index=-1;
			for(int i=0;i<LineDimNumb;i++){
				if(LineDim[i].Inside==true){
					if(LastX==LineDim[i].x1 && LastY==LineDim[i].y1){
						Index=i;
						Dest[RetNumb][DestPointNumb[RetNumb]].setX(LineDim[Index].x2);
						Dest[RetNumb][DestPointNumb[RetNumb]].setY(LineDim[Index].y2);
						LastX=LineDim[Index].x2;
						LastY=LineDim[Index].y2;
						DestPointNumb[RetNumb]++;
						LineDim[Index].Inside=false;
					}
					else if(LastX==LineDim[i].x2 && LastY==LineDim[i].y2){
						Index=i;
						Dest[RetNumb][DestPointNumb[RetNumb]].setX(LineDim[Index].x1);
						Dest[RetNumb][DestPointNumb[RetNumb]].setY(LineDim[Index].y1);
						LastX=LineDim[Index].x1;
						LastY=LineDim[Index].y1;
						DestPointNumb[RetNumb]++;
						LineDim[Index].Inside=false;
					}
				}
			}
			if(Index>=0){
				if(LastX==x1){
					int	*p=(int *)EqualSearch(&LastY,CrossedPointLeft	,CrossedPointLeftNumb	,sizeof(CrossedPointLeft  [0]),SortCrossPointFunc);
					if(p!=NULL){
						int	n=p-CrossedPointLeft;
						if(n+1<CrossedPointLeftNumb && IsInside(Source,SourcePointNumb,x1,(CrossedPointLeft[n]+CrossedPointLeft[n+1])/2)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(x1);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointLeft[n]);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(x1);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointLeft[n+1]);
							DestPointNumb[0]++;
							LastX=x1;
							LastY=CrossedPointLeft[n+1];
						}
						else if(n-1>=0 && IsInside(Source,SourcePointNumb,x1,(CrossedPointLeft[n-1]+CrossedPointLeft[n])/2)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(x1);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointLeft[n]);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(x1);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointLeft[n-1]);
							DestPointNumb[0]++;
							LastX=x1;
							LastY=CrossedPointLeft[n-1];
						}
					}
				}
				if(LastX==x2){
					int	*p=(int *)EqualSearch(&LastY,CrossedPointRight	,CrossedPointRightNumb	,sizeof(CrossedPointRight [0]),SortCrossPointFunc);
					if(p!=NULL){
						int	n=p-CrossedPointRight;
						if(n+1<CrossedPointRightNumb && IsInside(Source,SourcePointNumb,x2,(CrossedPointRight[n]+CrossedPointRight[n+1])/2)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(x2);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointRight[n]);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(x2);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointRight[n+1]);
							DestPointNumb[0]++;
							LastX=x2;
							LastY=CrossedPointRight[n+1];
						}
						else if(n-1>=0 && IsInside(Source,SourcePointNumb,x2,(CrossedPointRight[n-1]+CrossedPointRight[n])/2)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(x2);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointRight[n]);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(x2);
							Dest[RetNumb][DestPointNumb[0]].setY(CrossedPointRight[n-1]);
							DestPointNumb[0]++;
							LastX=x2;
							LastY=CrossedPointRight[n-1];
						}
					}
				}
				if(LastY==y1){
					int	*p=(int *)EqualSearch(&LastX,CrossedPointTop		,CrossedPointTopNumb	,sizeof(CrossedPointTop	  [0]),SortCrossPointFunc);
					if(p!=NULL){
						int	n=p-CrossedPointTop;
						if(n+1<CrossedPointTopNumb && IsInside(Source,SourcePointNumb,(CrossedPointTop[n]+CrossedPointTop[n+1])/2,y1)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointTop[n]);
							Dest[RetNumb][DestPointNumb[0]].setY(y1);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointTop[n+1]);
							Dest[RetNumb][DestPointNumb[0]].setY(y1);
							DestPointNumb[0]++;
							LastX=CrossedPointTop[n+1];
							LastY=y1;
						}
						else if(n-1>=0 && IsInside(Source,SourcePointNumb,(CrossedPointTop[n-1]+CrossedPointTop[n])/2,y1)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointTop[n]);
							Dest[RetNumb][DestPointNumb[0]].setY(y1);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointTop[n-1]);
							Dest[RetNumb][DestPointNumb[0]].setY(y1);
							DestPointNumb[0]++;
							LastX=CrossedPointTop[n-1];
							LastY=y1;
						}
					}
				}
				if(LastY==y2){
					int	*p=(int *)EqualSearch(&LastX,CrossedPointBottom	,CrossedPointBottomNumb	,sizeof(CrossedPointBottom[0]),SortCrossPointFunc);
					if(p!=NULL){
						int	n=p-CrossedPointBottom;
						if(n+1<CrossedPointBottomNumb && IsInside(Source,SourcePointNumb,(CrossedPointBottom[n]+CrossedPointBottom[n+1])/2,y2)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointBottom[n]);
							Dest[RetNumb][DestPointNumb[0]].setY(y2);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointBottom[n+1]);
							Dest[RetNumb][DestPointNumb[0]].setY(y2);
							DestPointNumb[0]++;
							LastX=CrossedPointBottom[n+1];
							LastY=y2;
						}
						else if(n-1>=0 && IsInside(Source,SourcePointNumb,(CrossedPointBottom[n-1]+CrossedPointBottom[n])/2,y2)==true){
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointBottom[n]);
							Dest[RetNumb][DestPointNumb[0]].setY(y2);
							DestPointNumb[0]++;
							Dest[RetNumb][DestPointNumb[0]].setX(CrossedPointBottom[n-1]);
							Dest[RetNumb][DestPointNumb[0]].setY(y2);
							DestPointNumb[0]++;
							LastX=CrossedPointBottom[n-1];
							LastY=y2;
						}
					}
				}
			}
		}
	}
	delete	[]LineDim;
}

class	QPointFList : public NPList<QPointFList>
{
public:
	QPointF	*Point;
	int		PointNumb;

	QPointFList(void)	{	Point=NULL;	PointNumb=0;	}
	~QPointFList(void)	{	delete	[]Point;	}
};

struct	EndLinePointF
{
	double	X,Y;
	QPointFList	*f;
	bool	DirNormal;
};

int	SortEndLinePointF(const void *a ,const void *b)
{
	struct	EndLinePointF	*pa=(struct	EndLinePointF *)a;
	struct	EndLinePointF	*pb=(struct	EndLinePointF *)b;

	double	dx=pa->X - pb->X;
	double	dy=pa->Y - pb->Y;

	if(dx>0)
		return 1;
	if(dx<0)
		return -1;

	if(dy>0)
		return 1;
	if(dy<0)
		return -1;

	return 0;
}
void	MakeClosedInClipArea(QPointF Source[], int SourcePointNumb
						,NPListPack<QPointFList> &PointPack
						,struct	EndLinePointF EndPoints[],int EndPointNumb
						,const QPointF &P1 , const QPointF &P2);

int		ClipPolygon(QPointF *Dest[] ,int DestPointNumb[] ,int MaxDicCount
				,double x1 ,double y1 ,double x2 ,double y2
				,NPListPack<QPointFList> &PointPack
				,int RetNumb);

int		ClipDbg=0;
int		ClipDbgN=288;
int		ClipDbgCounter=0;

int		ClipPolygon(QPointF Source[], int SourcePointNumb ,QPointF *Dest[] ,int DestPointNumb[] ,int MaxDicCount
				,double x1 ,double y1 ,double x2 ,double y2
				,bool &RetClipped)
{
	struct	InsideLine
	{
		double	x1,y1,x2,y2;
		bool	Inside;
	};
	struct	InsideLine	*LineDim=new struct	InsideLine[SourcePointNumb*3];
	int			LineDimNumb=0;
	double		CrossedPointTop   [100];
	int			CrossedPointTopNumb=0;
	double		CrossedPointLeft  [100];
	int			CrossedPointLeftNumb=0;
	double		CrossedPointRight [100];
	int			CrossedPointRightNumb=0;
	double		CrossedPointBottom[100];
	int			CrossedPointBottomNumb=0;

	for(int i=0;i<SourcePointNumb;i++){
		int	j=i+1;
		if(j>=SourcePointNumb)
			j=0;
		double	P[2][2];
		int	N=CrossRectLine(Source[i].x(),Source[i].y(), Source[j].x(), Source[j].y()
			 ,x1,y1 ,x2, y2
			 ,P);
		if(N==0){
			if(Source[i].x()!=Source[j].x() || Source[i].y()!=Source[j].y()){
				LineDim[LineDimNumb].x1=Source[i].x();
				LineDim[LineDimNumb].y1=Source[i].y();
				LineDim[LineDimNumb].x2=Source[j].x();
				LineDim[LineDimNumb].y2=Source[j].y();
				LineDimNumb++;
			}
		}
		else if(N==1){
			if(Source[i].x()!=P[0][0] || Source[i].y()!=P[0][1]){
				LineDim[LineDimNumb].x1=Source[i].x();
				LineDim[LineDimNumb].y1=Source[i].y();
				LineDim[LineDimNumb].x2=P[0][0];
				LineDim[LineDimNumb].y2=P[0][1];
				LineDimNumb++;
			}
			if(Source[j].x()!=P[0][0] || Source[j].y()!=P[0][1]){
				LineDim[LineDimNumb].x1=P[0][0];
				LineDim[LineDimNumb].y1=P[0][1];
				LineDim[LineDimNumb].x2=Source[j].x();
				LineDim[LineDimNumb].y2=Source[j].y();
				LineDimNumb++;
			}
			if(P[0][1]==y1){
				CrossedPointTop[CrossedPointTopNumb]=P[0][0];
				CrossedPointTopNumb++;
			}
			else if(P[0][1]==y2){
				CrossedPointBottom[CrossedPointBottomNumb]=P[0][0];
				CrossedPointBottomNumb++;
			}
			else if(P[0][0]==x1){
				CrossedPointLeft[CrossedPointLeftNumb]=P[0][1];
				CrossedPointLeftNumb++;
			}
			else if(P[0][0]==x2){
				CrossedPointRight[CrossedPointRightNumb]=P[0][1];
				CrossedPointRightNumb++;
			}
		}
		else if(N==2){
			if(hypot(Source[i].x()-P[0][0] ,Source[i].y()-P[0][1])>hypot(Source[i].x()-P[1][0] ,Source[i].y()-P[1][1])){
				swap(P[0][0],P[1][0]);
				swap(P[0][1],P[1][1]);
			}
			if(Source[i].x()!=P[0][0] || Source[i].y()!=P[0][1]){
				LineDim[LineDimNumb].x1=Source[i].x();
				LineDim[LineDimNumb].y1=Source[i].y();
				LineDim[LineDimNumb].x2=P[0][0];
				LineDim[LineDimNumb].y2=P[0][1];
				LineDimNumb++;
			}
			if(P[0][0]!=P[1][0] || P[0][1]!=P[1][1]){
				LineDim[LineDimNumb].x1=P[0][0];
				LineDim[LineDimNumb].y1=P[0][1];
				LineDim[LineDimNumb].x2=P[1][0];
				LineDim[LineDimNumb].y2=P[1][1];
				LineDimNumb++;
			}
			if(Source[j].x()!=P[1][0] || Source[j].y()!=P[1][1]){
				LineDim[LineDimNumb].x1=P[1][0];
				LineDim[LineDimNumb].y1=P[1][1];
				LineDim[LineDimNumb].x2=Source[j].x();
				LineDim[LineDimNumb].y2=Source[j].y();
				LineDimNumb++;
			}
			if(P[0][1]==y1){
				CrossedPointTop[CrossedPointTopNumb]=P[0][0];
				CrossedPointTopNumb++;
			}
			else if(P[0][1]==y2){
				CrossedPointBottom[CrossedPointBottomNumb]=P[0][0];
				CrossedPointBottomNumb++;
			}
			else if(P[0][0]==x1){
				CrossedPointLeft[CrossedPointLeftNumb]=P[0][1];
				CrossedPointLeftNumb++;
			}
			else if(P[0][0]==x2){
				CrossedPointRight[CrossedPointRightNumb]=P[0][1];
				CrossedPointRightNumb++;
			}
			if(P[1][1]==y1){
				CrossedPointTop[CrossedPointTopNumb]=P[1][0];
				CrossedPointTopNumb++;
			}
			else if(P[1][1]==y2){
				CrossedPointBottom[CrossedPointBottomNumb]=P[1][0];
				CrossedPointBottomNumb++;
			}
			else if(P[1][0]==x1){
				CrossedPointLeft[CrossedPointLeftNumb]=P[1][1];
				CrossedPointLeftNumb++;
			}
			else if(P[1][0]==x2){
				CrossedPointRight[CrossedPointRightNumb]=P[1][1];
				CrossedPointRightNumb++;
			}
		}
	}
	RetClipped=false;
	for(int i=0;i<LineDimNumb;i++){
		LineDim[i].Inside=IsInside((LineDim[i].x1+LineDim[i].x2)/2, (LineDim[i].y1+LineDim[i].y2)/2, x1 ,y1 ,x2 ,y2);
		if(LineDim[i].Inside==false){
			RetClipped=true;
		}
	}

	if(ClipDbgN==ClipDbgCounter)
		ClipDbg++;
	NPListPack<QPointFList>	PointPack;

	for(int i=0;i<LineDimNumb;i++){
		if(LineDim[i].Inside==false)
			continue;
		int	StartI=i;
		if(StartI==0){
			for(int j=LineDimNumb-1;j>0;j--){
				if(LineDim[j].Inside==false){
					break;
				}
				StartI=j;
			}
		}
		LineDim[StartI].Inside=false;
		int	EndI=StartI;
		int	N=1;
		for(int j=0;j<LineDimNumb;j++){
			if(EndI>=LineDimNumb){
				EndI=0;
			}
			int	k=EndI+1;
			if(k>=LineDimNumb){
				k=0;
			}
			if(LineDim[k].Inside==false){
				break;
			}
			EndI=k;
			LineDim[EndI].Inside=false;
			N++;
		}

		QPointFList	*f=new QPointFList();
		f->PointNumb	=0;
		f->Point=new QPointF[2*N+3];
		double	LastX=-99999999.9;
		double	LastY=-99999999.9;
		for(int j=0;j<LineDimNumb;j++){
			int	k=StartI+j;
			while(k>=LineDimNumb){
				k-=LineDimNumb;
			}
			if(LastX!=LineDim[k].x1 || LastY!=LineDim[k].y1){
				f->Point[f->PointNumb].setX(LineDim[k].x1);
				f->Point[f->PointNumb].setY(LineDim[k].y1);
				f->PointNumb++;
			}
			f->Point[f->PointNumb].setX(LineDim[k].x2);
			f->Point[f->PointNumb].setY(LineDim[k].y2);
			LastX=LineDim[k].x2;
			LastY=LineDim[k].y2;
			f->PointNumb++;
			if(k==EndI){
				break;
			}
		}
		PointPack.AppendList(f);
	}

	int RetNumb=ClipPolygon(Dest ,DestPointNumb ,MaxDicCount
				,x1 ,y1 ,x2 ,y2
				,PointPack
				,0);

	struct	EndLinePointF	EndPoints[1000];
	int						EndPointNumb;

	//Top side
	EndPointNumb=0;
	for(QPointFList *f=PointPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->Point[0].y()==y1){
			EndPoints[EndPointNumb].X=f->Point[0].x();
			EndPoints[EndPointNumb].Y=f->Point[0].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=true;
			EndPointNumb++;
		}
		if(f->Point[f->PointNumb-1].y()==y1){
			EndPoints[EndPointNumb].X=f->Point[f->PointNumb-1].x();
			EndPoints[EndPointNumb].Y=f->Point[f->PointNumb-1].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=false;
			EndPointNumb++;
		}
	}
	MakeClosedInClipArea(Source, SourcePointNumb
						,PointPack
						,EndPoints,EndPointNumb
						,QPointF(x1,y1),QPointF(x1,y1));

	RetNumb=ClipPolygon(Dest ,DestPointNumb ,MaxDicCount
				,x1 ,y1 ,x2 ,y2
				,PointPack
				,RetNumb);

	//Right side
	EndPointNumb=0;
	for(QPointFList *f=PointPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->Point[0].x()==x2){
			EndPoints[EndPointNumb].X=f->Point[0].x();
			EndPoints[EndPointNumb].Y=f->Point[0].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=true;
			EndPointNumb++;
		}
		if(f->Point[f->PointNumb-1].x()==x2){
			EndPoints[EndPointNumb].X=f->Point[f->PointNumb-1].x();
			EndPoints[EndPointNumb].Y=f->Point[f->PointNumb-1].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=false;
			EndPointNumb++;
		}
	}
	MakeClosedInClipArea(Source, SourcePointNumb
						,PointPack
						,EndPoints,EndPointNumb
						,QPointF(x2,y1),QPointF(x2,y2));

	RetNumb=ClipPolygon(Dest ,DestPointNumb ,MaxDicCount
				,x1 ,y1 ,x2 ,y2
				,PointPack
				,RetNumb);

	//bottom side
	EndPointNumb=0;
	for(QPointFList *f=PointPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->Point[0].y()==y2){
			EndPoints[EndPointNumb].X=f->Point[0].x();
			EndPoints[EndPointNumb].Y=f->Point[0].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=true;
			EndPointNumb++;
		}
		if(f->Point[f->PointNumb-1].y()==y2){
			EndPoints[EndPointNumb].X=f->Point[f->PointNumb-1].x();
			EndPoints[EndPointNumb].Y=f->Point[f->PointNumb-1].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=false;
			EndPointNumb++;
		}
	}
	MakeClosedInClipArea(Source, SourcePointNumb
						,PointPack
						,EndPoints,EndPointNumb
						,QPointF(x1,y2),QPointF(x2,y2));

	RetNumb=ClipPolygon(Dest ,DestPointNumb ,MaxDicCount
				,x1 ,y1 ,x2 ,y2
				,PointPack
				,RetNumb);

	//left side
	EndPointNumb=0;
	for(QPointFList *f=PointPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->Point[0].x()==x1){
			EndPoints[EndPointNumb].X=f->Point[0].x();
			EndPoints[EndPointNumb].Y=f->Point[0].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=true;
			EndPointNumb++;
		}
		if(f->Point[f->PointNumb-1].x()==x1){
			EndPoints[EndPointNumb].X=f->Point[f->PointNumb-1].x();
			EndPoints[EndPointNumb].Y=f->Point[f->PointNumb-1].y();
			EndPoints[EndPointNumb].f=f;
			EndPoints[EndPointNumb].DirNormal=false;
			EndPointNumb++;
		}
	}
	MakeClosedInClipArea(Source, SourcePointNumb
						,PointPack
						,EndPoints,EndPointNumb
						,QPointF(x1,y1),QPointF(x1,y2));

	RetNumb=ClipPolygon(Dest ,DestPointNumb ,MaxDicCount
				,x1 ,y1 ,x2 ,y2
				,PointPack
				,RetNumb);

	ClipDbgCounter++;
	delete	[]LineDim;
	return RetNumb;
}

int		ClipPolygon(QPointF *Dest[] ,int DestPointNumb[] ,int MaxDicCount
				,double x1 ,double y1 ,double x2 ,double y2
				,NPListPack<QPointFList> &PointPack
				,int RetNumb)
{
	for(QPointFList *f=PointPack.GetFirst();f!=NULL;){
		QPointFList *NextF=f->GetNext();
		if(  (f->Point[0].y()!=y1 && f->Point[f->PointNumb-1].y()!=y1
		   && f->Point[0].y()!=y2 && f->Point[f->PointNumb-1].y()!=y2
		   && f->Point[0].x()!=x1 && f->Point[f->PointNumb-1].x()!=x1
		   && f->Point[0].x()!=x2 && f->Point[f->PointNumb-1].x()!=x2)
		||  (f->Point[0].y()==y1 && f->Point[f->PointNumb-1].y()==y1)
		||  (f->Point[0].y()==y2 && f->Point[f->PointNumb-1].y()==y2)
		||  (f->Point[0].x()==x1 && f->Point[f->PointNumb-1].x()==x1)
		||  (f->Point[0].x()==x2 && f->Point[f->PointNumb-1].x()==x2) ){
			PointPack.RemoveList(f);
			if(RetNumb<MaxDicCount){
				Dest[RetNumb]=f->Point;
				DestPointNumb[RetNumb]=f->PointNumb;
				f->Point=NULL;
				f->PointNumb=0;
				RetNumb++;
			}
			delete	f;
		}
		f=NextF;
	}
	return RetNumb;
}


void	MakeClosedInClipArea(QPointF Source[], int SourcePointNumb
						,NPListPack<QPointFList> &PointPack
						,struct	EndLinePointF EndPoints[],int EndPointNumb
						,const QPointF &P1 ,const QPointF &P2)
{
	if(EndPointNumb>0){

		QSort(EndPoints	,EndPointNumb	,sizeof(EndPoints[0]),SortEndLinePointF);
		int tEndPointNumb=EndPointNumb;

		if(P1!=EndPoints[0].f->Point[0] && P1!=EndPoints[0].f->Point[EndPoints[0].f->PointNumb-1]
		&& P1!=EndPoints[EndPointNumb-1].f->Point[0] && P1!=EndPoints[EndPointNumb-1].f->Point[EndPoints[0].f->PointNumb-1]){
			EndPoints[tEndPointNumb].X=P1.x();
			EndPoints[tEndPointNumb].Y=P1.y();
			EndPoints[tEndPointNumb].f=NULL;
			EndPoints[tEndPointNumb].DirNormal=true;
			tEndPointNumb++;
		}
		if(P2!=EndPoints[0].f->Point[0] && P2!=EndPoints[0].f->Point[EndPoints[0].f->PointNumb-1]
		&& P2!=EndPoints[EndPointNumb-1].f->Point[0] && P2!=EndPoints[EndPointNumb-1].f->Point[EndPoints[0].f->PointNumb-1]){
			EndPoints[tEndPointNumb].X=P2.x();
			EndPoints[tEndPointNumb].Y=P2.y();
			EndPoints[tEndPointNumb].f=NULL;
			EndPoints[tEndPointNumb].DirNormal=true;
			tEndPointNumb++;
		}
		EndPointNumb=tEndPointNumb;
		QSort(EndPoints	,EndPointNumb	,sizeof(EndPoints[0]),SortEndLinePointF);
		for(int i=0;i<EndPointNumb-1;i++){
			double X=(EndPoints[i].X+EndPoints[i+1].X)/2.0;
			double Y=(EndPoints[i].Y+EndPoints[i+1].Y)/2.0;
			if(IsInside(Source, SourcePointNumb ,X,Y)==true){
				if(EndPoints[i].f!=NULL && EndPoints[i+1].f!=NULL){
					int	PointNumb=EndPoints[i].f->PointNumb+EndPoints[i+1].f->PointNumb;
					QPointF	*Point	=new QPointF[PointNumb];
					PointNumb=0;
					if(EndPoints[i].DirNormal==true){
						for(int j=EndPoints[i].f->PointNumb-1;j>=0;j--){
							Point[PointNumb]=EndPoints[i].f->Point[j];
							PointNumb++;
						}
					}
					else{
						for(int j=0;j<EndPoints[i].f->PointNumb;j++){
							Point[PointNumb]=EndPoints[i].f->Point[j];
							PointNumb++;
						}
					}
					if(EndPoints[i+1].DirNormal==true){
						for(int j=0;j<EndPoints[i+1].f->PointNumb;j++){
							Point[PointNumb]=EndPoints[i+1].f->Point[j];
							PointNumb++;
						}
					}
					else{
						for(int j=EndPoints[i+1].f->PointNumb-1;j>=0;j--){
							Point[PointNumb]=EndPoints[i+1].f->Point[j];
							PointNumb++;
						}
					}
					delete	[]EndPoints[i].f->Point;
					EndPoints[i].f->Point=Point;
					EndPoints[i].f->PointNumb=PointNumb;

					for(QPointFList *f=PointPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f==EndPoints[i+1].f){
							PointPack.RemoveList(f);
							delete	f;
							break;
						}
					}
				}
				else if(EndPoints[i].f==NULL && EndPoints[i+1].f!=NULL){
					int	PointNumb=EndPoints[i+1].f->PointNumb+1;
					QPointF	*Point	=new QPointF[PointNumb];
					PointNumb=0;
					if(EndPoints[i+1].DirNormal==true){
						Point[PointNumb]=QPointF(EndPoints[i].X,EndPoints[i].Y);
						PointNumb++;
						for(int j=0;j<EndPoints[i+1].f->PointNumb;j++){
							Point[PointNumb]=EndPoints[i+1].f->Point[j];
							PointNumb++;
						}
					}
					else{
						for(int j=0;j<EndPoints[i+1].f->PointNumb;j++){
							Point[PointNumb]=EndPoints[i+1].f->Point[j];
							PointNumb++;
						}
						Point[PointNumb]=QPointF(EndPoints[i].X,EndPoints[i].Y);
						PointNumb++;
					}
					delete	[]EndPoints[i+1].f->Point;
					EndPoints[i+1].f->Point=Point;
					EndPoints[i+1].f->PointNumb=PointNumb;
				}
				else if(EndPoints[i].f!=NULL && EndPoints[i+1].f==NULL){
					int	PointNumb=EndPoints[i].f->PointNumb+1;
					QPointF	*Point	=new QPointF[PointNumb];
					PointNumb=0;
					if(EndPoints[i+1].DirNormal==true){
						Point[PointNumb]=QPointF(EndPoints[i+1].X,EndPoints[i+1].Y);
						PointNumb++;
						for(int j=0;j<EndPoints[i].f->PointNumb;j++){
							Point[PointNumb]=EndPoints[i].f->Point[j];
							PointNumb++;
						}
					}
					else{
						for(int j=0;j<EndPoints[i].f->PointNumb;j++){
							Point[PointNumb]=EndPoints[i].f->Point[j];
							PointNumb++;
						}
						Point[PointNumb]=QPointF(EndPoints[i+1].X,EndPoints[i+1].Y);
						PointNumb++;
					}
					delete	[]EndPoints[i].f->Point;
					EndPoints[i].f->Point=Point;
					EndPoints[i].f->PointNumb=PointNumb;
				}
				i++;
			}
		}
	}
}

double	GetAreaPolygon(double Points[][2],int PointNumb)
{
	if(PointNumb<3)
		return 0;

	double	Area=0;
	for(int i=0;i<PointNumb-1;i++){
		Area+= Points[i][0]*Points[i+1][1] - Points[i][1]*Points[i+1][0];
	}
	Area+= Points[PointNumb-1][0]*Points[0][1] - Points[PointNumb-1][1]*Points[0][0];
	return 0.5*fabs(Area);
}
double	GetAreaPolygon(QPointF Points[],int PointNumb)
{
	if(PointNumb<3)
		return 0;

	double	Area=0;
	for(int i=0;i<PointNumb-1;i++){
		Area+= Points[i].x()*Points[i+1].y() - Points[i].y()*Points[i+1].x();
	}
	Area+= Points[PointNumb-1].x()*Points[0].y() - Points[PointNumb-1].y()*Points[0].x();
	return 0.5*fabs(Area);
}

bool	CheckInsideTriangle (double Px1,double Py1
							,double Px2,double Py2
							,double Px3,double Py3
							,double Px, double Py)
{
	if(Px2==Px1 && Py2==Py1)
		return false;
	if(Px3==Px1 && Py3==Py1)
		return false;

	/*
	V1*t+V2*s+P1=P
	Vx1*t+Vx2*s=Px-Px1
	Vy1*t+Xy2*s=Py-Py1

	Vx1*Vy2*t=(Px-Px1)*Vy2
	Vy1*Vx2*t=(Py-Py1)*Vx2
	t=((Px-Px1)*Vy2-(Py-Py1)*Vx2)/(Vx1*Vy2-Vy1*Vx2)

	Vx2*Vy1*s=(Px-Px1)*Vx1
	Vy2*Vx1*s=(Py-Py1)*Vx1
	s=((Px-Px1)*Vx1-(Py-Py1)*Vx1)/(Vx2*Vy1-Vy2*Vx1)
	 =(-(Px-Px1)*Vx1+(Py-Py1)*Vx1)/(Vy2*Vx1-Vx2*Vy1)
	*/
	{
		double	Vx1=Px2-Px1;
		double	Vy1=Py2-Py1;
		double	Vx2=Px3-Px1;
		double	Vy2=Py3-Py1;
		
		double	D=Vx1*Vy2-Vy1*Vx2;
		if(fabs(D)<0.0000000001)
			return false;
		double	t=( (Px-Px1)*Vy2-(Py-Py1)*Vx2)/D;
		double	s=(-(Px-Px1)*Vx1+(Py-Py1)*Vx1)/D;
		if(t<0 || 1.0<t || s<0 || 1.0<s)
			return false;
	}
	{
		double	Vx1=Px3-Px2;
		double	Vy1=Py3-Py2;
		double	Vx2=Px1-Px2;
		double	Vy2=Py1-Py2;
		
		double	D=Vx1*Vy2-Vy1*Vx2;
		if(fabs(D)<0.0000000001)
			return false;
		double	t=( (Px-Px2)*Vy2-(Py-Py2)*Vx2)/D;
		double	s=(-(Px-Px2)*Vx1+(Py-Py2)*Vx1)/D;
		if(t<0 || 1.0<t || s<0 || 1.0<s)
			return false;
	}
	return true;

}
bool	CalcCircleFrom3Points(int X1, int Y1
							 ,int X2, int Y2
							 ,int X3, int Y3
							 ,double &Cx, double &Cy ,double &R
							 ,double MinDiff)
{
	double	A=(X1-X2);
	double	B=(Y1-Y2);
	double	C=(X2-X3);
	double	D=(Y2-Y3);
	double	E=A*(X1+X2)+B*(Y1+Y2);
	double	F=C*(X2+X3)+D*(Y2+Y3);

	double	M=A*D-B*C;
	if(fabs(M)<=MinDiff){
		return false;
	}
	double	P=0.5/M;
	Cx=(E*D-B*F)*P;
	Cy=(A*F-C*E)*P;
	R=hypot(X1-Cx,Y1-Cy);
	return true;
}

bool	CalcCircleFrom3Points(double X1, double Y1
							 ,double X2, double Y2
							 ,double X3, double Y3
							 ,double &Cx, double &Cy ,double &R
							 ,double MinDiff)
{
	double	A=(X1-X2);
	double	B=(Y1-Y2);
	double	C=(X2-X3);
	double	D=(Y2-Y3);
	double	E=A*(X1+X2)+B*(Y1+Y2);
	double	F=C*(X2+X3)+D*(Y2+Y3);

	double	M=A*D-B*C;
	if(fabs(M)<=MinDiff){
		return false;
	}
	double	P=0.5/M;
	Cx=(E*D-B*F)*P;
	Cy=(A*F-C*E)*P;
	R=hypot(X1-Cx,Y1-Cy);
	return true;
}

double	GetDistanceRect2Rect(double sx1,double sy1,double sx2,double sy2
							,double dx1,double dy1,double dx2,double dy2)
{
	double	d;
	double	MinD=99999999;	
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}

	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}

	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}

	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}
	return MinD;
}

double	GetDistanceRect2Rect(int sx1,int sy1,int sx2,int sy2
							,int dx1,int dy1,int dx2,int dy2)
{
	double	d;
	double	MinD=99999999;	
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy1,sx2,sy1 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}

	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy1,sx2,sy2 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}

	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx2,sy2,sx1,sy2 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}

	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx1,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx2,dy1);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx2,dy2);
	if(d<MinD){
		MinD=d;
	}
	d=GetLengthLine2Point(sx1,sy2,sx1,sy1 ,dx1,dy2);
	if(d<MinD){
		MinD=d;
	}
	return MinD;
}
