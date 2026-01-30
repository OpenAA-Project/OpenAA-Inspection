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

#ifndef XWaveEditH
#define XWaveEditH
//---------------------------------------------------------------------------
#include<QString>

#include"NList.h"
#include "XIODefine.h"
#include "XTypeDef.h"

class   XWaveEditLeaf;

enum NodeKind{
     __WE_Toggle
    ,__WE_SetH
    ,__WE_SetL
    ,__WE_Let
    ,__WE_Add
    ,__WE_Sub
    ,__WE_Mul
    ,__WE_Div
    ,__WE_Mod
    ,__WE_And
    ,__WE_Or
    ,__WE_Xor
    ,__WE_Neg
    ,__WE_Goto
    ,__WE_EqualGo
    ,__WE_NotEqualGo
    ,__WE_GreaterGo
    ,__WE_GreatEqualGo
    ,__WE_LessGo
    ,__WE_LessEqualGo
    ,__WE_Wait
    ,__WE_MOut
    ,__WE_Return
};



class   XWaveNode : public NPList<XWaveNode>
{
  public:
    NodeKind        Kind;
    XWaveEditLeaf   *ParentLeaf;
    int             StepCount;
    XWaveEditLeaf   *ParentLeaf2;
    XWaveEditLeaf   *ParentLeaf3;
    XWaveEditLeaf   *ParentLeaf4;

    double          DataD;
    int             DataI;
    QString         DataS;
    bool            DataB;

    XWaveNode(void){}
    ~XWaveNode(void){}
};

enum    OpeKind
{
     __IOIn
    ,__IOOut
    ,__VWord
    ,__VString
    ,__VDouble
    ,__VComm
    ,__VBit
};

class   XWaveEditOpe : public NPList<XWaveEditOpe>
{
  public:
    OpeKind Kind;
    int     OpeID;
    NPListPack<XWaveNode>   Node;

    XWaveEditOpe(void){}
    ~XWaveEditOpe(void){}
};


extern  IODefineClass   IORegData;


#endif