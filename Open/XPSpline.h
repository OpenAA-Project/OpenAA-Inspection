/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */




#ifndef XPSplineH
#define XPSplineH

#include "XTypeDef.h"
#include <QtGui>

#define	_USE_MATH_DEFINES
#include <math.h>

#define MinSplineData   0.000000001

class   XSplineBase
{
  protected:
    int Count;
    double  *x;
    double  *y;
    double  *p;
    double  *a;
    double  *b;

  public:
    XSplineBase(void);
    XSplineBase(XSplineBase &src);
    XSplineBase &operator=(XSplineBase &src);
    ~XSplineBase(void);

    void    Initial(void);
    bool  SetPoints(int count ,double X[] ,double Y[]);
    bool  SetPoints(int count ,QPoint Dot[]);

    void  CalcSpline(double t ,double &px, double &py);   //0<=t<=1.0
    void  CalcSplineV(double t ,double &onPx,double &onPy
                                         ,double &Vx  ,double &Vy);   //0<=t<=1.0
    double FindNearPoint(int OutX,int OutY
                                  ,double &px, double &py);
    void  PalLine(double px, double py
                            ,double &ma,double &mb,double &mc);
    int   GetCrossYList(double Y ,double t[] ,double x[]);
    int   GetCrossXList(double X ,double t[] ,double y[]);
    bool  IsTopY(double t);   //Y�����̋ɓ_���ۂ��𒲂ׂ�

  protected:
    virtual bool  CalcSetPoints(void)=0;
    double  spline1(double t, double m[], double z[]);
    bool     FindYPointInner(double Y ,double startt ,double mint ,double maxt
                                                ,double &t ,double &x);
    bool     FindXPointInner(double X ,double startt ,double mint ,double maxt
                                                ,double &rett ,double &y);
    double  FindNearPointInner(int OutX,int OutY
                                  ,double &px, double &py
                                  ,double t ,double mint ,double maxt
                                  ,double &kt);
};

class   XCloseSpline : public XSplineBase
{
  public:
    XCloseSpline(void){}
    ~XCloseSpline(void){}

    //bool __fastcall CheckInner(int OutX,int OutY);

  private:
    bool CalcSetPoints(void);
    bool maketable(double m[], double z[]);
};

class   XOpenSpline : public XSplineBase
{
  public:
    XOpenSpline(void){}
    ~XOpenSpline(void){}

    //bool __fastcall CheckInner(int OutX,int OutY);

  private:
    bool CalcSetPoints(void);
    bool maketable(double m[], double z[]);
};


#endif