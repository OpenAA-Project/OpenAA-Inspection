/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAffin.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XAffinH
#define XAffinH
//---------------------------------------------------------------------------
bool    GetAffin(int x1,int y1
                ,int x2,int y2          //マスター画像上のアライメント基準位置
                ,double cx, double cy   //回転中心
                ,int X1 ,int Y1
                ,int X2 ,int Y2     //探索した結果のアラインメント位置
                ,double &ResultPx,double &ResultPy  //平行移動量
                ,double &ResultS                    //回転量（ラジアン）
                ,double &ResultAlpha);              //拡大率

bool	GetAffinDecompose(double m[6] 
						,double &A ,double &B, double &Tx ,double &Ty ,double &S ,double &R);

#endif
