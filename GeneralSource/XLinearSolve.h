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



//---------------------------------------------------------------------------

#ifndef XLinearSolveH
#define XLinearSolveH
//---------------------------------------------------------------------------
#include "XTypeDef.h"

class   LinearSolveSquare   //�ŏ��Q���덷�̒��������߂�
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
    �����Aa,b�����߂�   */

#endif
 