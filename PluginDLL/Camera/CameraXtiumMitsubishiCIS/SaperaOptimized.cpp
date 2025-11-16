/* //////////////////////////////////////////////////////////////////////////////////////////////////////////
   fileid : saperaCtrl.cpp
  subject : Sapera SDK control functions
////////////////////////////////////////////////////////////////////////////////////////////////////////// */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include "swap.h"

#include "sapClassBasic.h"
#include "conio.h"
#include "XMainSchemeMemory.h"

#include "saperaCtrl.h"
#include "featureCtrl.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "CameraXtiumMitsubishiCIS.h"


bool saperaCtrl::getImageInside(ImageBuffer *Buff[])
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	BuffWidth=_Buffers->GetWidth();
	int width	= min(Buff[0]->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
	int height	= min(Buff[0]->GetHeight(),_Buffers->GetHeight());	//CONST_MAX_HEIGHT;
	int	width12	=4096;
	int	width22	=width-width12;

	int	W4=height/4;

	void	*SrcAddress;
	_Buffers->GetAddress(&SrcAddress);


	#pragma omp parallel
	{
		#pragma omp for
		for (int y=0; y< height; y++) {
			// ruglas64のRGBバッファポインタを得る
			int	yR=Clipping(y,0,height-1);
			int	yG=Clipping(y,0,height-1);
			int	yB=Clipping(y,0,height-1);
			BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
			BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
			BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

			BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

			for (int j=0; j< width; j++) {
				*pB++ = *(s+0);
				*pG++ = *(s+1);
				*pR++ = *(s+2);
				s+=4;
			}
		}
	}

	return r;
}

bool saperaCtrl::getPartialImageInside(int Index ,ImageBuffer *Buff[],ImageBuffer *TRBuff[]
									,int StartLine , int EndLine)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	BuffWidth=_Buffers->GetWidth();
	int width	= min(Buff[0]->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
	int height	= min(Buff[0]->GetHeight(),_Buffers->GetHeight());	//CONST_MAX_HEIGHT;
	int	width12	=4096;
	int	width22	=width-width12;

	int	W4=height/4;

	void	*SrcAddress;
	if(Index>=0){
		_Buffers->GetAddress(Index,&SrcAddress);
	}
	else{
		_Buffers->GetAddress(&SrcAddress);
	}
	int		YN=EndLine-StartLine;

	#pragma omp parallel
	{
		#pragma omp for
		for (int i=0; i< YN; i++) {
			// ruglas64のRGBバッファポインタを得る
			int	y=StartLine+i;
			int	yR=Clipping(y,0,height-1);
			int	yG=Clipping(y,0,height-1);
			int	yB=Clipping(y,0,height-1);
			BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
			BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
			BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

			BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

			for (int j=0; j< width; j++) {
				/*
				*pB++ = *s++;		// blue
				*pG++ = *s++;		// green
				*pR++ = *s++;		// red
				s++;				// mono
				*/
				BYTE	X1=*s;
				BYTE	X2=*(s+1);
				BYTE	X3=*(s+2);
				BYTE	X4=*(s+3);
				*pR++=(X1 & 0x3F) +(X4<<6);
				*pG++=((X1>>6)&0x01) + ((X2&0x1F)<<1) +((X4<<4)&0xC0);
				*pB++=((X2>>5)&0x03) + ((X3&0x0F)<<2) +((X4<<2)&0xC0);
				s+=4;
			}
		}
	}

	return r;
}
