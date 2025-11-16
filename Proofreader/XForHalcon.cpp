/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\XForHalcon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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
