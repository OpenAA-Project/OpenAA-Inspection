/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XCrossObj.h
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#ifndef XCrossObjH
#define XCrossObjH
//---------------------------------------------------------------------------
#include <QPoint>
#include "XTypeDef.h"

double	RegulateAngle(double sita);

double  GetSita(int dx ,int dy);
double  GetSita(double dx ,double dy);
double  DiffSita(double s1 ,double s2);
double	GetMiddleAngle(double StartAngle ,double EndAngle);
bool	IsInsideAngle(double a ,double StartAngle ,double EndAngle);
int RInt(double d);	//四捨五入

bool    CheckOverlapRectLine(int rx1, int ry1, int rx2, int ry2		//Box
							,int px1, int py1, int px2, int py2);	//Line
bool    CheckOverlapRectLine(long rx1, long ry1, long rx2, long ry2		//Box
							,long px1, long py1, long px2, long py2);	//Line
bool    CheckOverlapRectLine(double rx1, double ry1, double rx2, double ry2		//Box
							,double px1, double py1, double px2, double py2);	//Line

bool    CheckOverlapRectRect(long rx1, long ry1, long rx2, long ry2
							,long px1, long py1, long px2, long py2);
/*      内部を含む矩形と内部を含む矩形が１部分でもオーバーラップしているか調べる
					finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に矩形座標を入れる

	オーバーラップしているとき、TRUE が返る
	一方が他方を完全に包含しているとき、TRUE が返る
	*/
bool    CheckOverlapRectRect(int rx1, int ry1, int rx2, int ry2
							,int px1, int py1, int px2, int py2);
bool    CheckOverlapRectRect(double rx1, double ry1, double rx2, double ry2
							,double px1, double py1, double px2, double py2);

bool    CheckOverlapRectRectFast(long rx1, long ry1, long rx2, long ry2
			    ,long px1, long py1, long px2, long py2);
/*      内部を含む矩形と内部を含む矩形が１部分でもオーバーラップしているか調べる
					finish debug

	(rx1,ry1)-(rx2,ry2) に矩形座標を入れる
	(px1,py1)-(px2,py2) に矩形座標を入れる

	オーバーラップしているとき、TRUE が返る
	一方が他方を完全に包含しているとき、TRUE が返る
	*/
double slopi(double x ,double y);
int slopi(short x ,short y);
int slopi(int x ,int y);
bool    GetCrossInnerPoint(long ax1,long ay1,long ax2,long ay2,long bx1,long by1,long bx2,long by2 , long &X ,long &Y);
bool    GetCrossInnerPoint(double ax1,double ay1,double ax2,double ay2,double bx1,double by1,double bx2,double by2 , double &X ,double &Y);
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
bool    GetCrossInnerPointWithoutEdge(double ax1,double ay1,double ax2,double ay2,double bx1,double by1,double bx2,double by2 , double &X ,double &Y);
bool    GetCrossPoint(double ax1,double ay1,double ax2,double ay2,double bx1,double by1,double bx2,double by2 , double &X ,double &Y);

bool    GetCrossHalfInnerPoint(long ax1,long ay1,long ax2,long ay2,long by , long &X);
bool    GetCrossHalfInnerPoint(double ax1,double ay1,double ax2,double ay2,double by , double &X);
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

bool    GetCrossHalfInnerPointX(long ax1,long ay1,long ax2,long ay2,long bx , long &Y);
bool    GetCrossHalfInnerPointX(double ax1,double ay1,double ax2,double ay2,double bx , double &Y);
/*      ２線分の交点を求める    これは、端点内に交点が存在しないとき、FALSE が返る
							finish debug
	(ax1,ay1) - (ax2,ay2) に線分１の端点
	(bx) に垂直ラインのX座標
	Y に交点座標が返る

	正常に交点が求められたとき、TRUE が返る
	FALSE が返る条件
		２直線が交点を持たないとき
		交点が、線分の範囲内にないとき
		線分をなしていないとき
        線分が直線に含まれるとき
        */

//double GetLengthLine2Point(long ax1,long ay1,long ax2,long ay2
//			  ,long x  ,long y);

double GetLengthLine2Point(int ax1,int ay1,int ax2,int ay2
			  ,int x  ,int y);
double GetLengthLine2Point(double ax1,double ay1,double ax2,double ay2
			  ,double x  ,double y);
//bool    GetLinePointFoot(long x1,long y1,long x2,long y2
//			,long px ,long py ,long &X ,long &Y);

bool    GetLinePointFoot(int  x1,int y1,int x2,int y2
			,int px ,int py ,int &X ,int &Y);
bool    GetLinePointFoot(double  x1,double y1,double x2,double y2
			,double px ,double py ,double &X ,double &Y);
bool    GetLinePointFoot(double  A,double B,double C
			,double px ,double py ,double &X ,double &Y);
bool    GetLimitlessLinePointFoot(double x1,double y1,double x2,double y2
			,double px ,double py ,double &X ,double &Y);
double	GetLengthLimitlessLine2Point(double ax1,double ay1,double ax2,double ay2
			  ,double x  ,double y);
bool	ExtendLine(double x1,double y1,double x2,double y2 ,double AddedLen
				  ,double &X1,double &Y1,double &X2,double &Y2);

bool    Get3LevelResolve(double PP[][2] ,double PQ[][2] ,double m[]);
/*
		double PP[3][2] ,double PQ[3][2] ,double m[6]
*/

void    GetBarCorner(long px1,long py1,long px2,long py2,long pd
			       ,long D[4][2]);
/*	バーの４隅の座標を得る		finish debug

	(px1,py1)-(px2,py2) に線分端点、pd にバーの太さを入れる
	(D[0][0],D[0][1])-(D[1][0],D[1][1])は線分に沿った線になる
	(D[2][0],D[2][1])-(D[3][0],D[3][1])は線分に沿った線になる*/

void    EllipseCalcNearestPoint(double a ,double b ,double cx, double cy
                        ,double Dx, double Dy
                        ,double &X, double &Y);
/*  楕円外の点から楕円に下ろした最短距離の楕円状の点を求める    */

bool CalcCircle(double &cx ,double &cy, double &r
                                    ,int Point[][2] ,int PointNumb);
bool CalcLine(double &coss1 ,double &sins1, double &c1
                        ,double &coss2 ,double &sins2, double &c2
                                    ,int Point[][2] ,int PointNumb);

int RotEllipseYCut(double a ,double b ,double coss,double sins
                              ,double y ,double &x1 ,double &x2);
int RotEllipseYCut(double a ,double b ,double s
                              ,double y ,double &x1 ,double &x2);

double	GetAreaDot(int Px1,int Py1
				,  int Px2,int Py2
				,  int Px3,int Py3);
/*	３点で結ぶ三角形の面積を計算する	*/
double	GetAreaDot(double Px1,double Py1
				,  double Px2,double Py2
				,  double Px3,double Py3);
/*	３点で結ぶ三角形の中にあるかどうかの判定	*/
bool	CheckInsideTriangle (double Px1,double Py1
							,double Px2,double Py2
							,double Px3,double Py3
							,double Px, double Py);

int		GetCrossCircleLine(double cx ,double cy, double r
						,double x1,double y1 ,double x2, double y2
						,double &sx1,double &sy1 ,double &sx2, double &sy2);
int		GetCrossCircleCircle(double cax ,double cay, double ra
							,double cbx ,double cby, double rb
							,double &sx1,double &sy1 ,double &sx2, double &sy2);

int		CrossLineArc(double x1 ,double y1 ,double x2, double y2
					,double cx ,double cy ,double r,double startangle ,double endangle
					,double &X1,double &Y1,double &X2,double &Y2
					,double &Angle1,double &Angle2);
int		CrossArcArc( double cx1 ,double cy1 ,double r1 ,double startangle1 ,double endangle1
					,double cx2 ,double cy2 ,double r2 ,double startangle2 ,double endangle2
					,double &AngleA1,double &AngleA2
					,double &AngleB1,double &AngleB2);
bool    CheckOverlapRectArc(double rx1, double ry1, double rx2, double ry2							//Box
							,double cx ,double cy ,double r,double startangle ,double endangle);	//Arc

double GetLengthArc2Point(double cx ,double cy ,double r,double startangle ,double endangle
						,double x  ,double y);

bool	CheckInsidePolygon  (double Points[][2],int PointNumb	//Convex
							,double x, double y);
inline	bool	CheckInsideRectangle(double x1 ,double y1 ,double x2 ,double y2
							,double x ,double y)	{	return (x1<=x && x<x2 && y1<=y && y<y2)?true:false;		}	

int		CrossRectLine(int px1,int py1, int px2, int py2		//Line
					 ,int rx1,int ry1 ,int rx2, int ry2		//Rectangle
					 ,int P[2][2]);
int		CrossRectLine(double px1,double py1, double px2, double py2		//Line
					 ,double rx1,double ry1 ,double rx2, double ry2		//Rectangle
					 ,double P[2][2]);
int		ClipPolygon(QPoint Source[], int SourcePointNumb ,QPoint *Dest[] ,int DestPointNumb[] ,int MaxDicCount
					,int x1 ,int y1 ,int x2 ,int y2
					,bool &RetClipped);
int		ClipPolygon(QPointF Source[], int SourcePointNumb ,QPointF *Dest[] ,int DestPointNumb[] ,int MaxDicCount
					,double x1 ,double y1 ,double x2 ,double y2
					,bool &RetClipped);

double	GetAreaPolygon(double Points[][2],int PointNumb);
double	GetAreaPolygon(QPointF Points[],int PointNumb);

bool	CalcCircleFrom3Points(int X1, int Y1
							 ,int X2, int Y2
							 ,int X3, int Y3
							 ,double &Cx, double &Cy ,double &R
							 ,double MinDiff=0.000001);
bool	CalcCircleFrom3Points(double X1, double Y1
							 ,double X2, double Y2
							 ,double X3, double Y3
							 ,double &Cx, double &Cy ,double &R
							 ,double MinDiff=0.000001);
double	GetDistanceRect2Rect(double sx1,double sy1,double sx2,double sy2
							,double dx1,double dy1,double dx2,double dy2);
double	GetDistanceRect2Rect(int sx1,int sy1,int sx2,int sy2
							,int dx1,int dy1,int dx2,int dy2);
#endif
