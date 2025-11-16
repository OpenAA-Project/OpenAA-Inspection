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



#ifndef XIMAGEPROCESS_H
#define XIMAGEPROCESS_H

#include <QtGui>
#include "XTypeDef.h"
#include "XFlexArea.h"

class	ImageBuffer;

void    FatArea(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot ,FlexArea *ForceZone=NULL
				,bool EnableThread=true);

void    ThinArea(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot ,FlexArea *ForceZone=NULL
				,bool EnableThread=true);

void    FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot 
				,int Numb
				,FlexArea *ForceZone=NULL
				,bool EnableThread=true);

void    ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone=NULL
				,bool EnableThread=true);

void    FatAreaInACrossShape(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot);

void    ThinAreaInACrossShape(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot);

void    Binarize(BYTE **bmpdata
				,int xbyte ,int YLenDot ,ImageBuffer &Src
				,int LBright ,int HBright
				,int XSep=1 ,int YSep=1);

void    FatAreaRectangle(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte, int YLenDot
				,int minx ,int miny ,int maxx ,int maxy);

void    ThinAreaRectangle(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot
				,int minx ,int miny ,int maxx ,int maxy);

void    AndArea(BYTE **Dest
				,BYTE **Src
				,int xbyte ,int YLenDot);

void    BitmapClusterSized(BYTE **bmpdata ,int xbyte ,int YLen 
						   ,int XYMaxSize ,int XYMinSize ,int AreaMaxSize ,int AreaMinSize
						   ,int DotPerLine, int MaxLines 
						   ,int ClusterMaxSize=99999999
						   ,void (*FoundOneCluster)(BYTE **MapData,int xbyte,int ylen,int minX,int minY,int maxX,int maxY,void *anydata)=NULL 
						   ,void *anydata=NULL);

void    BitmapClusterSized(BYTE **bmpdata ,int xbyte ,int YLen 
						   ,uchar   **tmpdata ,uchar   **tmpdata2 
						   ,int XYMaxSize ,int XYMinSize ,int AreaMaxSize ,int AreaMinSize
						   ,int DotPerLine, int MaxLines
						   ,int ClusterMaxSize=99999999
						   ,void (*FoundOneCluster)(BYTE **MapData,int xbyte,int ylen,int minX,int minY,int maxX,int maxY,void *anydata)=NULL
						   ,void *anydata=NULL);

int		GetBmpMode(int X,int Y,int xlen,int ylen ,uchar **bmpdata ,int xbyte);
//  矩形領域にビットが全くないとき０
//  矩形領域が全てビットで覆われているとき  ２
//  矩形領域にビットが散在するとき          １

#pragma	pack(push,1)
struct  PickupStruct
{
    uchar   **TBuff;
    uchar   **SBuff;
    int     XLen;
    int     YLen;
    int     MinX;
    int     MaxX;
    int     MinY;
    int     MaxY;
    int     xbyte;
    int     x;
    int     y;
    int     py1;
    int     plen;
    int     DotCount;
	int		NestLevel;
	int		MaxBlockXY;
};
#pragma	pack(pop)

void	AutoRegPutPick(struct PickupStruct &PData,int xbyte,int x,int y);

bool	PickupFlexArea(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1,bool Multithread=true);
bool	PickupFlexArea(		 BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1,bool Multithread=true);
bool	PickupFlexAreaFast(		 BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1);

bool	PickupFlexArea(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack 
					,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
					,int MaxAreaCount=-1,bool Multithread=true);
bool	PickupFlexArea(		 BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack 
					,int AreaX1 ,int AreaY1 ,int AreaX2 ,int AreaY2
					,int MaxAreaCount=-1,bool Multithread=true);
//	Destroy Bmp
//	true if all transport
bool	PickupFlexAreaWhole(const BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1,bool Multithread=true);

bool	PickupFlexOneArea(BYTE **Bmp ,int XByte ,int XLen,int YLen 
						,int LocalX ,int LocalY
						,FlexArea &FArea);

//Small area
bool	PickupFlexArea_s(BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1,bool Multithread=true);
//	Destroy Bmp
//	true if all transport
bool	PickupFlexAreaWhole_s(BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1,bool Multithread=true);

bool	PickupFlexOneArea_s(BYTE **Bmp ,int XByte ,int XLen,int YLen 
						,int LocalX ,int LocalY
						,FlexArea &FArea);

void    FatArea(BYTE **Dest
				,BYTE **Src
				,int xbyte, int XLenDot ,int YLenDot ,int Length);
void    ThinArea(BYTE **Dest
				,BYTE **Src
				,int xbyte, int XLenDot ,int YLenDot ,int Length);

void	ReductionImage(BYTE **DestBmp ,int DestXLen,int DestYLen
					  ,BYTE **SrcBmp  ,int SrcXLen ,int SrcYLen
					  ,int Rate);


#endif
