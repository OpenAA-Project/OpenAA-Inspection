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
#include "CameraXtiumPx8MonoLineTrigger.h"



bool saperaCtrl::getImage(ImageBuffer *Buff,ImageBuffer *TRBuff)
{
	MutexSwapImage.lock();
	//Buff->Swap(ImageStack[CurrentRTop]);
	int		MaxLines=GetMaxLines();
	int		DotPerLine=GetDotPerLine();

#if defined(HalfMode)
	int		MaxLines2=MaxLines/2-1;
	int		DotPerLine2=DotPerLine/2-1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<MaxLines2;y++){
			BYTE	*d=Buff->GetY(2*y);
			BYTE	*s1=ImageStack[CurrentRTop].GetY(y);
			BYTE	*s2=ImageStack[CurrentRTop].GetY(y+1);
			for(int x=0;x<DotPerLine2;x++){
				*d=s1[x];
				*(d+1)=(s1[x]+s1[x+1])>>1;
				d+=2;
			}
			d=Buff->GetY(2*y+1);
			for(int x=0;x<DotPerLine2;x++){
				*d=(s1[x]+s2[x])>>1;
				*(d+1)=(s1[x]+s2[x]+s1[x+1]+s2[x+1])>>2;
				d+=2;
			}
		}
		#pragma omp for
		for(int y=0;y<MaxLines;y++){
			BYTE	*d=Buff->GetY(y);
			for(int x=0;x<DotPerLine-1;x++){
				*d=Clipping((*d)+(*(d+1)),0,255);
				d++;
			}
		}
	}
#else
	Buff->Swap(ImageStack[CurrentRTop]);
#endif

	if(GetParamGlobal()->AllocateTargetTRBuff==true){
		TRBuff->Swap(TRImageStack[CurrentRTop]);
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

bool saperaCtrl::getImageInside(ImageBuffer *Buff,ImageBuffer *TRBuff
							,void	*SrcAddress
							,int	BuffWidth
							,int width
							,int height)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	width12	=4096;
	int	width22	=width-width12;

	int	W4=height/4;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff!=NULL){
		if(Parent->Setting.MultipleRed==1.0){
			int		StartX=-dxR;
			dxR=dxR+StartX;

			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
					pR+=dxR;

					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pR++ = (*s)*GainRedL	+OffsetRedL		;		// red
							s++;				// mono
						}
						for (int j=0; j< width22; j++) {
							*pR++ = (*s)*GainRedR	+OffsetRedR		;		// red
							s+=4;				// mono
						}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pR-- = (*s)*GainRedL	+OffsetRedL		;		// red
							s++;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pR-- = (*s)*GainRedR	+OffsetRedR		;		// red
							s++;				// mono
						}
					}
				}
			//}
		}
		else{
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							BYTE	r=s[*tR++];
							*pR++ = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							BYTE	r=s[*tR++];
							*pR-- = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
				}
			//}
		}
		TRBuff->TranspositionXY(*Buff);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0){
			int		StartX=-dxR;
			dxR=dxR+StartX;

			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			#pragma omp parallel
			{
				#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
					pR+=dxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pR++ = GainOffsetTableRL[*s];		// red
							s++;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pR++ = GainOffsetTableRR[*s];		// red
							s++;				// mono
						}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pR-- = GainOffsetTableRL[*s];		// red
							s++;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pR-- = GainOffsetTableRR[*s];		// red
							s++;				// mono
						}
					}
				}
			}		
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;
					int	*tR=MatrixRX;

					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pR++ = s[*tR++];
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							*pR-- = s[*tR++];
						}
					}
				}
			}
		}
	}

	return r;
}


bool saperaCtrl::getImageInsideBasic(ImageBuffer *Buff,ImageBuffer *TRBuff
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;

	int	width12	=4096;
	int	width22	=width-width12;
	int	W4=height/4;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff!=NULL){
		if(Parent->Setting.MultipleRed==1.0){
			int		StartX=-dxR;
			dxR=dxR+StartX;

			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
					pR+=dxR;

					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pR++ = (*s)		;		// red
							s++;				// mono
						}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width; j++) {
							*pR-- = (*s)		;		// red
							s++;				// mono
						}
					}
				}
			//}
		}
		else{
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							BYTE	r=s[*tR++];
							*pR++ = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							BYTE	r=s[*tR++];
							*pR-- = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
				}
			//}
		}
		TRBuff->TranspositionXY(*Buff);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0){
			int		StartX=-dxR;
			dxR=dxR+StartX;

			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			#pragma omp parallel
			{
				#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
					pR+=dxR;
					if(LeftRight==false){
						memcpy(pR,s,width);
						//for (int j=0; j< width; j++) {
						//	*pR++ = *s;		// red
						//	s++;				// mono
						//}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width; j++) {
							*pR-- = *s;		// red
							s++;				// mono
						}
					}
				}
			}		
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;
					int	*tR=MatrixRX;

					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pR++ = s[*tR++];
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							*pR-- = s[*tR++];
						}
					}
				}
			}
		}
	}

	return r;
}

bool saperaCtrl::RemoveLineNoise(int x1, int XLen ,ImageBuffer *Buff
								,int StartLine , int EndLine)
{
	int	CDim[100000];
	int	iStartLine;
	if(StartLine!=0)
		iStartLine=StartLine-1;
	else
		iStartLine=StartLine;
	for(int y=iStartLine;y<EndLine;y++){
		BYTE	*s=Buff->GetY(y);
		CDim[y]=0;
		for(int xi=0;xi<XLen;xi++){
			CDim[y]+=s[x1+xi];
		}
	}
	for(int y=iStartLine;y<EndLine-1;y++){
		if(abs(CDim[y]-CDim[y+2])<XLen*3
		&& abs(CDim[y+1]-CDim[y])>XLen*10){
			BYTE	*s1=Buff->GetY(y);
			BYTE	*d =Buff->GetY(y+1);
			BYTE	*s2=Buff->GetY(y+2);
			for(int xi=0;xi<XLen;xi++){
				d[x1+xi]=(s1[x1+xi]+s2[x1+xi])/2;
			}
		}
	}
	return true;
}


bool saperaCtrl::RemoveVerticalStripe(ImageBuffer *Buff)
{
	int	StartX	=1024;
	int	EndX	=7168;
	int	YBand	=30;
	double	AvrDim[20];
	int	YLen=Buff->GetHeight();
	int		N=0;

	for(int x=StartX;x<EndX;x+=1024,N++){
		int	D=0;
		for(int y=2;y<2+YBand;y++){
			BYTE	*s=Buff->GetY(y);
			for(int i=0;i<1024;i++){
				D+=s[x+i];
			}
		}
		AvrDim[N]=D/(1024*YBand);
	}
	for(int i=1;i<N;i++){
		if(AvrDim[i-1]>(AvrDim[i]+10)){
			int	X=i*1024+StartX;
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<YLen;y++){
					BYTE	*d=Buff->GetY(y);
					for(int t=0;t<1024;t++){
						d[X+t]=Clipping((int)(d[X+t]*1.05+10),0,255);
					}
				}
			}
		}
		else
		if(AvrDim[i-1]>(AvrDim[i]+5)){
			int	X=i*1024+StartX;
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<YLen;y++){
					BYTE	*d=Buff->GetY(y);
					for(int t=0;t<1024;t++){
						d[X+t]=Clipping((int)(d[X+t]*1.02+5),0,255);
					}
				}
			}
		}
	}
	return true;
}

bool saperaCtrl::getPartialImageInside(int Index ,ImageBuffer *Buff,ImageBuffer *TRBuff
									,int StartLine , int EndLine
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	width12	=4096;
	int	width22	=width-width12;

	int	W4=height/4;

	int		YN=EndLine-StartLine;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff!=NULL){
		if(Parent->Setting.MultipleRed==1.0){
			int		StartX=-dxR;
			dxR=dxR+StartX;
			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			//OpenMP is slow
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);

					pR+=dxR;

					int	LdxR=dxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pR++ =TRBuff->GetYWithoutDepended(LdxR)[yR]	= (*s)*GainRedL	 +OffsetRedL	;		// red
							s++;				// mono
							LdxR++;
						}
						int	RdxR=width12+dxR;
						for (int j=0; j< width22; j++) {
							*pR++ =TRBuff->GetYWithoutDepended(RdxR)[yR]	= (*s)*GainRedR	 +OffsetRedR	;		// red
							s++;				// mono
							RdxR++;
						}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pR-- =TRBuff->GetYWithoutDepended(LdxR)[yR]	= (*s)*GainRedL	 +OffsetRedL	;		// red
							s++;				// mono
							LdxR++;
						}

						int	RdxR=width12+dxR;
						for (int j=0; j< width22; j++) {
							*pR-- =TRBuff->GetYWithoutDepended(RdxR)[yR]	= (*s)*GainRedR	 +OffsetRedR	;		// red
							s++;				// mono
							RdxR++;
						}
					}
				}
			//}
		}
		else{
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;

					int	*tR=MatrixRX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							tR++;
							*pR++ = TRBuff->GetYWithoutDepended(j)[yR]	=s[xR];
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							tR++;
							*pR-- = TRBuff->GetYWithoutDepended(j)[yR]	=s[xR];
						}
					}
				}
			//}
		}
		TRBuff->SetFlagCaptured(true);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0 ){
			int		StartX=-dxR;
			dxR=dxR+StartX;
			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			#pragma omp parallel
			{
				#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
					pR+=dxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pR++ = GainOffsetTableRL[*s];		// red
							s++;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pR++ = GainOffsetTableRR[*s];		// red
							s++;				// mono
						}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pR-- = GainOffsetTableRL[*s];		// red
							s++;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pR-- = GainOffsetTableRR[*s];		// red
							s++;				// mono
						}
					}
				}
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pR++ = s[*tR++];
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							*pR-- = s[*tR++];
						}
					}
				}
			}
		}
	}

	return r;
}


bool saperaCtrl::getPartialImageInsideBasic(int Index ,ImageBuffer *Buff,ImageBuffer *TRBuff
									,int StartLine , int EndLine
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;

	int	width12	=4096;
	int	width22	=width-width12;

	int	W4=height/4;
	int		YN=EndLine-StartLine;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff!=NULL){
		if(Parent->Setting.MultipleRed==1.0){
			int		StartX=-dxR;
			dxR=dxR+StartX;
			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}

			//OpenMP is slow
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);

					pR+=dxR;

					int	LdxR=dxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pR++ =TRBuff->GetYWithoutDepended(LdxR)[yR]	= (*s)	;		// red
							s++;				// mono
							LdxR++;
						}
						int	RdxR=width12+dxR;
						for (int j=0; j< width22; j++) {
							*pR++ =TRBuff->GetYWithoutDepended(RdxR)[yR]	= (*s)	;		// red
							s++;				// mono
							RdxR++;
						}
					}
					else{
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pR-- =TRBuff->GetYWithoutDepended(LdxR)[yR]	= (*s)	;		// red
							s++;				// mono
							LdxR++;
						}

						int	RdxR=width12+dxR;
						for (int j=0; j< width22; j++) {
							*pR-- =TRBuff->GetYWithoutDepended(RdxR)[yR]	= (*s)	;		// red
							s++;				// mono
							RdxR++;
						}
					}
				}
			//}
		}
		else{
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;

					int	*tR=MatrixRX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							tR++;
							*pR++ = TRBuff->GetYWithoutDepended(j)[yR]	=s[xR];
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							tR++;
							*pR-- = TRBuff->GetYWithoutDepended(j)[yR]	=s[xR];
						}
					}
				}
			//}
		}
		TRBuff->SetFlagCaptured(true);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0 ){
			int		StartX=-dxR;
			dxR=dxR+StartX;
			int	MaxDx=dxR;
			if(StartX>=0){
				width	=width-StartX-MaxDx;
				width12	-=StartX;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				width22	=width-width12;
			}
			if(YN<1024){
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+dyR,0,height-1);
						BYTE *pR = Buff->GetYWithoutDepended(yR);
						BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
						pR+=dxR;
						if(LeftRight==false){
							memcpy(pR,s,width);
							//for (int j=0; j< width; j++) {
							//	*pR++ = *s;		// red
							//	s++;				// mono
							//}
						}
						else{
							pR+=width12+width22-1;
							for (int j=0; j< width; j++) {
								*pR-- = *s;		// red
								s++;				// mono
							}
						}
					}
			}
			else{
				#pragma omp parallel
				{
					#pragma omp for
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+dyR,0,height-1);
						BYTE *pR = Buff->GetYWithoutDepended(yR);
						BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX);
						pR+=dxR;
						if(LeftRight==false){
							memcpy(pR,s,width);
							//for (int j=0; j< width; j++) {
							//	*pR++ = *s;		// red
							//	s++;				// mono
							//}
						}
						else{
							pR+=width12+width22-1;
							for (int j=0; j< width; j++) {
								*pR-- = *s;		// red
								s++;				// mono
							}
						}
					}
				}
			}
		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					BYTE *pR = Buff->GetYWithoutDepended(yR);
					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth;

					int	*tR=MatrixRX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pR++ = s[*tR++];
						}
					}
					else{
						pR+=width-1;
						for (int j=0; j< width; j++) {
							*pR-- = s[*tR++];
						}
					}
				}
			}
		}
	}

	return r;
}

void		CameraXtiumPx8MonoLineTrigger::ExecuteColorAllocation(ImageBuffer *Buff[],int BufferDimCounts ,BYTE MulColor[3])
{
	int width	= Buff[0]->GetWidth() ;	//CONST_MAX_WIDTH;
	int height	= Buff[0]->GetHeight();	//CONST_MAX_HEIGHT;
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<height;y++){
			BYTE	*s=Buff[0]->GetY(y);
			BYTE	*d1=Buff[1]->GetY(y);
			BYTE	*d2=Buff[2]->GetY(y);
			for(int x=0;x<width;x++){
				BYTE	c=*s;
				*s=(c*MulColor[0])>>8;
				*d1=(c*MulColor[1])>>8;
				*d2=(c*MulColor[2])>>8;
				s++;
				d1++;
				d2++;
			}
		}
	}
}