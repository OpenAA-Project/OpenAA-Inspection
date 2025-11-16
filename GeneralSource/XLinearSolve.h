/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLinearSolve.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XLinearSolveH
#define XLinearSolveH
//---------------------------------------------------------------------------
#include "XTypeDef.h"

class   LinearSolveSquare   //ç≈è¨ÇQèÊåÎç∑ÇÃíºê¸ÇãÅÇﬂÇÈ
{
    double  Sx2;
    double  Sy2;
    double  Sx;
    double  Sy;
    double  Sxy;
    int     Numb;

  public:  
    LinearSolveSquare(void);

    void    AddXY(double x ,double y);
    bool    GetABC(double &a ,double &b ,double &c);
};

bool    Solve2DLinear(double x1 ,double y1 ,double t1
                     ,double x2 ,double y2 ,double t2
                     ,double &a ,double &b);
/*
    a*x1 + b*y1 =t1
    a*x2 + b*y2 =t2
    Ç©ÇÁÅAa,bÇãÅÇﬂÇÈ   */

#endif
 