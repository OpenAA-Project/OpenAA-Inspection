/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XImageProcess.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XIMAGEPROCESS2_H
#define XIMAGEPROCESS2_H

#include <QtGui>
#include "XTypeDef.h"
#include "XFlexArea.h"
#include "XTreeLines.h"

class	ImageBuffer;

bool    MakeHough(BYTE **BmpMap,BYTE **DestMap
				  ,int FreqDots
				  ,int XLen,int YLen
				  ,int HoughResolution=1000);
//ハフ変換で、直線上のドットだけ抽出

void    NarrowizeLine(BYTE **Bmp ,BYTE **Tmp ,int XLen , int YLen);
//	細線化

void	PickupLines(BYTE **BmpMap, int XLen , int YLen
					,TreesContainer &XYCluster);
//	２値化画像を樹状点列へ変換する
//	あらかじめ細線化しておくべき
//	BmpMapは破壊される


#endif
