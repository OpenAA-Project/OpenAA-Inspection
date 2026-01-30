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

#include "XForHalcon.h"

XForHalcon::XForHalcon()
{
}

XForHalcon::~XForHalcon()
{
}

void XForHalcon::CreateImage(ImageBuffer *Buff[],int LayerNumb)
{
	int iDotPerLine	=Buff[0]->MaxX;
	int iMaxLines	=Buff[0]->MaxY;
	if(LayerNumb==1){
		unsigned char *image=new unsigned char[iDotPerLine*iMaxLines];
		for(int Y=0;Y<iMaxLines;Y++){
			BYTE *pBuff=Buff[0]->GetY(Y);
			for(int X=0;X<iDotPerLine;X++)
				image[Y*iDotPerLine+X]=pBuff[X];
		}
		ExeHalcon.Hgen_image1(iDotPerLine,iMaxLines,image);
	}
	else if(LayerNumb==3){
		unsigned char *image[3];
		for(int L=0;L<LayerNumb;L++){
			image[L]=new unsigned char[iDotPerLine*iMaxLines];
			for(int Y=0;Y<iMaxLines;Y++){
				BYTE *pBuff=Buff[L]->GetY(Y);
				for(int X=0;X<iDotPerLine;X++)
					image[L][Y*iDotPerLine+X]=pBuff[X];
			}
		}
		ExeHalcon.Hgen_image3(iDotPerLine,iMaxLines,image[0],image[1],image[2]);
	}
}