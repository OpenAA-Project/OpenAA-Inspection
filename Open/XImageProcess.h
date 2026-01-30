/*
 * Copyright (C) 2026
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
//  ���`�̈��Ƀr�b�g���S���Ȃ��Ƃ��O
//  ���`�̈悪�S�ăr�b�g�ŕ������Ă����Ƃ�  �Q
//  ���`�̈��Ƀr�b�g���U�݂����Ƃ�          �P

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
bool	PickupFlexAreaFast(	 BYTE **Bmp ,int XByte ,int XLen,int YLen ,PureFlexAreaListContainer &FPack ,int MaxAreaCount=-1);

int		PickupFlexAreaFastDim(BYTE **Bmp ,int XByte ,int XLen,int YLen ,FlexAreaFastDimPack &RetFPackDim ,int MinDotCount=0 ,bool Multithread=true);

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