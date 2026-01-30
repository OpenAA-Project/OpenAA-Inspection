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


#include <cmath>
#include "XTypeDef.h"
#include "XDisplayBitImage.h"
#include <omp.h>

void	DrawBitImage(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col)
{
	//if(movx<0){
	//	movx *=ZoomRate;
	//}
	//if(movy<0){
	//	movy *=ZoomRate;
	//}
	double	IZoomRate=1.0/ZoomRate;
	int64	AddX=(int64)(0x100000000*IZoomRate);
	DWORD	C=(DWORD)Col.rgba();
	int	YNumb=Pnt.height();
	int	XNumb=Pnt.width();
	float	Z=1.0/ZoomRate;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			DWORD	*d=(DWORD *)Pnt.scanLine(y);
			int		ry= -movy+OffsetY+y*Z;
			if((ry<0) || (ry>=YLen)){
				for(int x=0;x<XNumb;x++){
					*d=0;
					d++;
				}
			}
			else{
				int	x=0;
				uint64	mx=0;
				if((OffsetX-movx)<0){
					for(;x<XNumb;x++){
						if((((int)(mx>>32))+OffsetX-movx)>=0){
							break;
						}
						*d=0;
						d++;
						mx+=AddX;
					}
				}
				const BYTE	*s=Src[ry];
				for(;x<XNumb;x++){
					if((mx>>32)+OffsetX-movx>=XLen){
						break;
					}
					int	kx=OffsetX-movx+(mx>>32);
					if((*(s+(kx>>3)) & (0x80>>(kx&7)))!=0){
						*d=C;
					}
					else{
						*d=0;
					}
					d++;
					mx+=AddX;
				}
				for(;x<XNumb;x++){
					*d=0;
					d++;				
				}
			}
		}
	}
}


void	DrawBitImageOr(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col)
{
	double	IZoomRate=1.0/ZoomRate;
	int64	AddX=(int64)(0x100000000*IZoomRate);
	DWORD	C=(DWORD)Col.rgba();
	int	YNumb=Pnt.height();
	int	XNumb=Pnt.width();

	//#pragma omp parallel                             
	//{                                                
	//	#pragma omp for
		for(int y=0;y<YNumb;y++){
			DWORD	*d=(DWORD *)Pnt.scanLine(y);
			int		ry= -movy+OffsetY+y/ZoomRate;
			if((ry<0) || (ry>=YLen)){
				for(int x=0;x<XNumb;x++){
					d++;
				}
			}
			else{
				int	x=0;
				uint64	mx=0;
				if((OffsetX-movx)<0){
					for(;x<XNumb;x++){
						if((((int)(mx>>32))+OffsetX-movx)>=0){
							break;
						}
						d++;
						mx+=AddX;
					}
				}
				const BYTE	*s=Src[ry];
				for(;x<XNumb;x++){
					if((mx>>32)+OffsetX-movx>=XLen){
						break;
					}
					int	kx=OffsetX-movx+(mx>>32);
					if((*(s+(kx>>3)) & (0x80>>(kx&7)))!=0){
						*d = C;
					}
					d++;
					mx+=AddX;
				}
				for(;x<XNumb;x++){
					d++;				
				}
			}
		}
	//}
}