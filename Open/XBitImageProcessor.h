/*
 * Copyright (C) 2025
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