/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XBitImageProcessor.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XBITIMAGEPROCESSOR_H)
#define	XBITIMAGEPROCESSOR_H

#include "XMainSchemeMemory.h"
#include "XFlexArea.h"


void	PickupBitmapWithAverage(BYTE **BmpImage , int XByte ,int YLen
								,ImageBuffer &SrcImage
								,int BlockWidth ,int BlockHeight
								,int RelThresholdL ,int RelThresholdH
								,int EnsmallSize ,int EnlargeSize
								,int Sep=4);

void	PickupBitmap(BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH
					,int EnsmallSize ,int EnlargeSize);

void	PickupBitmap(FlexArea &Area,int dx ,int dy
					 ,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH
					,int EnsmallSize ,int EnlargeSize);

void	PickupBitmapWithTmp(FlexArea &Area ,int dx ,int dy
					,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH
					,int EnsmallSize ,int EnlargeSize
					,BYTE	**tmp);

void	PickupBitmapWithTmpMulti(FlexArea &Area ,int dx ,int dy
					,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer *SrcImage[] ,int ImageNumb
					,int AbsThresholdL[] ,int AbsThresholdH[]
					,int EnsmallSize ,int EnlargeSize
					,BYTE	**tmp);

void	DrawBitRectangle(BYTE **BmpImage , int XByte ,int YLen
						 ,int x1, int y1, int x2, int y2);

void    CopyBlocyBitBuff(BYTE **dst			,int dstXByte ,int dstYLen
						,const BYTE **src	,int srcXByte ,int srcYLen
						,int OffsetX ,int OffsetY);

void	ClearBitInRect(BYTE **BitMapDim , int XByte ,int YLen
						 ,int x1, int y1, int x2, int y2);

#endif