/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XWaveEdit.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
