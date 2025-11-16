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
#include "CameraXtiumSpectral.h"


bool saperaCtrl::getImage(ImageBuffer *Buff[],ImageBuffer *TRBuff[])
{
	MutexSwapImage.lock();
	//Buff->Swap(ImageStack[CurrentRTop]);
	int		MaxLines=GetMaxLines();
	int		DotPerLine=GetDotPerLine();

	ImageBufferList*s=ImageStack[CurrentRTop].GetFirst();
	for(int layer=0;layer<GetLayersBase()->GetMaxLayerNumb();layer++,s=s->GetNext()){
		Buff[layer]->Swap(*s);
	}

	MutexSwapImage.unlock();
	CurrentRTop++;
	if(CurrentRTop>=CamStackNumb){
		CurrentRTop=0;
	}
	MutexStackImage.lock();
	StackedNumb--;
	MutexStackImage.unlock();

	return true;
}

bool saperaCtrl::getPartialImageInside(int Index 
									,ImageBufferListContainer *Buff,ImageBufferListContainer *TRBuff
									,int StartLine , int EndLine)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	BuffWidth=_Buffers->GetWidth();
	//int width	= min(Buff->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
	//int height	= min(Buff->GetHeight(),_Buffers->GetHeight());	//CONST_MAX_HEIGHT;

	void	*SrcAddress;
	if(Index>=0){
		_Buffers->GetAddress(Index,&SrcAddress);
	}
	else{
		_Buffers->GetAddress(&SrcAddress);
	}

	int	BindedPixels=Parent->Setting.BindedPixels;
	int	StartPos	=Parent->Setting.StartPos;
	int	RefStart	=Parent->Setting.RefStart;

	int		YN=EndLine-StartLine;
	int		LayerNumb=min(GetLayersBase()->GetMaxLayerNumb(),(int)Buff->GetCount());
	int		height	= GetMaxLines();
	int		RDotPerLine=GetDotPerLine();

	//OpenMP is slow
	//#pragma omp parallel
	//{
	//	#pragma omp for

		for (int i=0; i< YN; i++) {
			// ruglas64のRGBバッファポインタを得る
			int	y=StartLine+i;
			int	RYLine	=y/RDotPerLine;
			int	RStartX	=y%RDotPerLine;

			if(0<=RYLine && RYLine<height){
				ImageBufferList	*d=Buff->GetFirst();
				BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth);
				for(int layer=0;layer<LayerNumb;layer++,d=d->GetNext()){
					BYTE *p = &d->GetYWithoutDepended(RYLine)[RStartX];

					s+=StartPos;
					*p=*s;
					for(int k=1;k<BindedPixels;k++){
						s++;
						*p+=*s;
					}
				}
			}
		}
	//}

	return r;
}

