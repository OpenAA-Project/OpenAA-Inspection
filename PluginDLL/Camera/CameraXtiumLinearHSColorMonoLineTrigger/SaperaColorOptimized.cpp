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

#include "saperaCtrlColor.h"
#include "featureCtrl.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "CameraXtiumLinearHSColorMonoLineTrigger.h"


bool saperaCtrlColor::getImageInside(ImageBuffer *Buff[],ImageBuffer *TRBuff[])
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	BuffWidth=_Buffers->GetWidth();
	int width	= min(Buff[0]->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
	int height	= min(Buff[0]->GetHeight(),_Buffers->GetHeight());	//CONST_MAX_HEIGHT;
	int	width12	=2048;
	int	width22	=width-width12;

	int	W4=height/4;

	void	*SrcAddress;
	_Buffers->GetAddress(&SrcAddress);

	int		*MatrixRX	=Parent->MatrixRX;
	int		*MatrixGX	=Parent->MatrixGX;
	int		*MatrixBX	=Parent->MatrixBX;
	int		dyR			=Parent->Setting.OffsetYRed;
	int		dyG			=Parent->Setting.OffsetYGreen;
	int		dyB			=Parent->Setting.OffsetYBlue;
	int		dxR			=Parent->Setting.OffsetXRed;
	int		dxG			=Parent->Setting.OffsetXGreen;
	int		dxB			=Parent->Setting.OffsetXBlue;

	double	GainRedL	=Parent->Setting.GainRedL	+Parent->Setting.AddedGainR;
	double	GainGreenL	=Parent->Setting.GainGreenL	+Parent->Setting.AddedGainG;
	double	GainBlueL	=Parent->Setting.GainBlueL	+Parent->Setting.AddedGainB;
	int		OffsetRedL	=Parent->Setting.OffsetRedL	;
	int		OffsetGreenL=Parent->Setting.OffsetGreenL;
	int		OffsetBlueL	=Parent->Setting.OffsetBlueL	;			 			
	double	GainRedR	=Parent->Setting.GainRedR	+Parent->Setting.AddedGainR;
	double	GainGreenR	=Parent->Setting.GainGreenR	+Parent->Setting.AddedGainG;
	double	GainBlueR	=Parent->Setting.GainBlueR	+Parent->Setting.AddedGainB;
	int		OffsetRedR	=Parent->Setting.OffsetRedR	;
	int		OffsetGreenR=Parent->Setting.OffsetGreenR;
	int		OffsetBlueR	=Parent->Setting.OffsetBlueR	;
	bool	LeftRight	=Parent->Setting.LeftRight;

	BYTE	*GainOffsetTableRL	=Parent->GainOffsetTableRL;
	BYTE	*GainOffsetTableGL	=Parent->GainOffsetTableGL;
	BYTE	*GainOffsetTableBL	=Parent->GainOffsetTableBL;
	BYTE	*GainOffsetTableRR	=Parent->GainOffsetTableRR;
	BYTE	*GainOffsetTableGR	=Parent->GainOffsetTableGR;
	BYTE	*GainOffsetTableBR	=Parent->GainOffsetTableBR;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff[0]!=NULL){
		if(Parent->Setting.MultipleRed==1.0 && Parent->Setting.MultipleGreen==1.0 && Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(dxR,dxG),dxB);
			dxR=dxR+StartX;
			dxG=dxG+StartX;
			dxB=dxB+StartX;
			int	MaxDx=max(max(dxR,dxG),dxB);
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

					pB+=dxB;
					pG+=dxG;
					pR+=dxR;

					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pB++ = (*s	   )*GainBlueL	+OffsetBlueL	;		// blue
							*pG++ = (*(s+1))*GainGreenL	+OffsetGreenL	;		// green
							*pR++ = (*(s+2))*GainRedL	+OffsetRedL		;		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB++ = (*s	   )*GainBlueR	+OffsetBlueR	;		// blue
							*pG++ = (*(s+1))*GainGreenR	+OffsetGreenR	;		// green
							*pR++ = (*(s+2))*GainRedR	+OffsetRedR		;		// red
							s+=4;				// mono
						}
					}
					else{
						pB+=width12+width22-1;
						pG+=width12+width22-1;
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pB-- = (*s	   )*GainBlueL	+OffsetBlueL	;		// blue
							*pG-- = (*(s+1))*GainGreenL	+OffsetGreenL	;		// green
							*pR-- = (*(s+2))*GainRedL	+OffsetRedL		;		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB-- = (*s	   )*GainBlueR	+OffsetBlueR	;		// blue
							*pG-- = (*(s+1))*GainGreenR	+OffsetGreenR	;		// green
							*pR-- = (*(s+2))*GainRedR	+OffsetRedR		;		// red
							s+=4;				// mono
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					int	*tG=MatrixGX;
					int	*tB=MatrixBX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							BYTE	b=s[*tB++];
							BYTE	g=s[*tG++];
							BYTE	r=s[*tR++];
							*pB++ = b;
							*pG++ = g;
							*pR++ = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
					else{
						pB+=width-1;
						pG+=width-1;
						pR+=width-1;
						for (int j=0; j< width; j++) {
							BYTE	b=s[*tB++];
							BYTE	g=s[*tG++];
							BYTE	r=s[*tR++];
							*pB-- = b;
							*pG-- = g;
							*pR-- = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
				}
			//}
		}
		TRBuff[0]->TranspositionXY(* Buff[0]);
		TRBuff[1]->TranspositionXY(* Buff[1]);
		TRBuff[2]->TranspositionXY(* Buff[2]);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0 && Parent->Setting.MultipleGreen==1.0 && Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(dxR,dxG),dxB);
			dxR=dxR+StartX;
			dxG=dxG+StartX;
			dxB=dxB+StartX;
			int	MaxDx=max(max(dxR,dxG),dxB);
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

					pB+=dxB;
					pG+=dxG;
					pR+=dxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pB++ = GainOffsetTableBL[*s	];		// blue
							*pG++ = GainOffsetTableGL[*(s+1)];		// green
							*pR++ = GainOffsetTableRL[*(s+2)];		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB++ = GainOffsetTableBR[*s	];		// blue
							*pG++ = GainOffsetTableGR[*(s+1)];		// green
							*pR++ = GainOffsetTableRR[*(s+2)];		// red
							s+=4;				// mono
						}
					}
					else{
						pB+=width12+width22-1;
						pG+=width12+width22-1;
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pB-- = GainOffsetTableBL[*s	];		// blue
							*pG-- = GainOffsetTableGL[*(s+1)];		// green
							*pR-- = GainOffsetTableRL[*(s+2)];		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB-- = GainOffsetTableBR[*s	];		// blue
							*pG-- = GainOffsetTableGR[*(s+1)];		// green
							*pR-- = GainOffsetTableRR[*(s+2)];		// red
							s+=4;				// mono
						}
					}
				}
			}		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

					int	*tR=MatrixRX;
					int	*tG=MatrixGX;
					int	*tB=MatrixBX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pB++ = s[*tB++];
							*pG++ = s[*tG++];
							*pR++ = s[*tR++];
						}
					}
					else{
						pB+=width-1;
						pG+=width-1;
						pR+=width-1;
						for (int j=0; j< width; j++) {
							*pB-- = s[*tB++];
							*pG-- = s[*tG++];
							*pR-- = s[*tR++];
						}
					}
				}
			}
		}
	}

	return r;
}


bool saperaCtrlColor::getImageInsideBasic(ImageBuffer *Buff[],ImageBuffer *TRBuff[])
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	BuffWidth=_Buffers->GetWidth();
	int width	= min(Buff[0]->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
	int height	= min(Buff[0]->GetHeight(),_Buffers->GetHeight());	//CONST_MAX_HEIGHT;
	int	width12	=2048;
	int	width22	=width-width12;

	int	W4=height/4;

	void	*SrcAddress;
	_Buffers->GetAddress(&SrcAddress);

	int		*MatrixRX	=Parent->MatrixRX;
	int		*MatrixGX	=Parent->MatrixGX;
	int		*MatrixBX	=Parent->MatrixBX;
	int		dyR			=Parent->Setting.OffsetYRed;
	int		dyG			=Parent->Setting.OffsetYGreen;
	int		dyB			=Parent->Setting.OffsetYBlue;
	int		dxR			=Parent->Setting.OffsetXRed;
	int		dxG			=Parent->Setting.OffsetXGreen;
	int		dxB			=Parent->Setting.OffsetXBlue;

	double	GainRedL	=Parent->Setting.GainRedL	+Parent->Setting.AddedGainR;
	double	GainGreenL	=Parent->Setting.GainGreenL	+Parent->Setting.AddedGainG;
	double	GainBlueL	=Parent->Setting.GainBlueL	+Parent->Setting.AddedGainB;
	int		OffsetRedL	=Parent->Setting.OffsetRedL	;
	int		OffsetGreenL=Parent->Setting.OffsetGreenL;
	int		OffsetBlueL	=Parent->Setting.OffsetBlueL	;			 			
	double	GainRedR	=Parent->Setting.GainRedR	+Parent->Setting.AddedGainR;
	double	GainGreenR	=Parent->Setting.GainGreenR	+Parent->Setting.AddedGainG;
	double	GainBlueR	=Parent->Setting.GainBlueR	+Parent->Setting.AddedGainB;
	int		OffsetRedR	=Parent->Setting.OffsetRedR	;
	int		OffsetGreenR=Parent->Setting.OffsetGreenR;
	int		OffsetBlueR	=Parent->Setting.OffsetBlueR	;
	bool	LeftRight	=Parent->Setting.LeftRight;

	BYTE	*GainOffsetTableRL	=Parent->GainOffsetTableRL;
	BYTE	*GainOffsetTableGL	=Parent->GainOffsetTableGL;
	BYTE	*GainOffsetTableBL	=Parent->GainOffsetTableBL;
	BYTE	*GainOffsetTableRR	=Parent->GainOffsetTableRR;
	BYTE	*GainOffsetTableGR	=Parent->GainOffsetTableGR;
	BYTE	*GainOffsetTableBR	=Parent->GainOffsetTableBR;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff[0]!=NULL){
		if(Parent->Setting.MultipleRed==1.0 && Parent->Setting.MultipleGreen==1.0 && Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(dxR,dxG),dxB);
			dxR=dxR+StartX;
			dxG=dxG+StartX;
			dxB=dxB+StartX;
			int	MaxDx=max(max(dxR,dxG),dxB);
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

					pB+=dxB;
					pG+=dxG;
					pR+=dxR;

					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pB++ = (*s	   );		// blue
							*pG++ = (*(s+1));		// green
							*pR++ = (*(s+2));		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB++ = (*s	   );		// blue
							*pG++ = (*(s+1));		// green
							*pR++ = (*(s+2));		// red
							s+=4;				// mono
						}
					}
					else{
						pB+=width12+width22-1;
						pG+=width12+width22-1;
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pB-- = (*s	   );		// blue
							*pG-- = (*(s+1));		// green
							*pR-- = (*(s+2));		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB-- = (*s	   );		// blue
							*pG-- = (*(s+1));		// green
							*pR-- = (*(s+2));		// red
							s+=4;				// mono
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					int	*tG=MatrixGX;
					int	*tB=MatrixBX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							BYTE	b=s[*tB++];
							BYTE	g=s[*tG++];
							BYTE	r=s[*tR++];
							*pB++ = b;
							*pG++ = g;
							*pR++ = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
					else{
						pB+=width-1;
						pG+=width-1;
						pR+=width-1;
						for (int j=0; j< width; j++) {
							BYTE	b=s[*tB++];
							BYTE	g=s[*tG++];
							BYTE	r=s[*tR++];
							*pB-- = b;
							*pG-- = g;
							*pR-- = r;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
				}
			//}
		}
		TRBuff[0]->TranspositionXY(* Buff[0]);
		TRBuff[1]->TranspositionXY(* Buff[1]);
		TRBuff[2]->TranspositionXY(* Buff[2]);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0 && Parent->Setting.MultipleGreen==1.0 && Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(dxR,dxG),dxB);
			dxR=dxR+StartX;
			dxG=dxG+StartX;
			dxB=dxB+StartX;
			int	MaxDx=max(max(dxR,dxG),dxB);
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

					pB+=dxB;
					pG+=dxG;
					pR+=dxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pB++ = *s	;		// blue
							*pG++ = *(s+1);		// green
							*pR++ = *(s+2);		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB++ = *s	;		// blue
							*pG++ = *(s+1);		// green
							*pR++ = *(s+2);		// red
							s+=4;				// mono
						}
					}
					else{
						pB+=width12+width22-1;
						pG+=width12+width22-1;
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pB-- = *s	;		// blue
							*pG-- = *(s+1);		// green
							*pR-- = *(s+2);		// red
							s+=4;				// mono
						}

						for (int j=0; j< width22; j++) {
							*pB-- = *s	;		// blue
							*pG-- = *(s+1);		// green
							*pR-- = *(s+2);		// red
							s+=4;				// mono
						}
					}
				}
			}		}
		else{
			#pragma omp parallel
			{
				#pragma omp for
				for (int y=0; y< height; y++) {
					// ruglas64のRGBバッファポインタを得る
					int	yR=Clipping(y+dyR,0,height-1);
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

					int	*tR=MatrixRX;
					int	*tG=MatrixGX;
					int	*tB=MatrixBX;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							*pB = s[*tB];
							*pG = s[*tG];
							*pR = s[*tR];
							tB++;
							tG++;
							tR++;
							pB++;
							pG++;
							pR++;
						}
					}
					else{
						pB+=width-1;
						pG+=width-1;
						pR+=width-1;
						for (int j=0; j< width; j++) {
							*pB = s[*tB];
							*pG = s[*tG];
							*pR = s[*tR];
							tB++;
							tG++;
							tR++;
							pB--;
							pG--;
							pR--;
						}
					}
				}
			}
		}
	}

	return r;
}

bool saperaCtrlColor::getPartialImageInside(int Index ,ImageBuffer *Buff[],ImageBuffer *TRBuff[]
									,int StartLine , int EndLine
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	width12	=2048;
	int	width22	=width-width12;

	int	W4=height/4;

	int		YN=EndLine-StartLine;
	int		idxR=dxR;
	int		idxG=dxG;
	int		idxB=dxB;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff[0]!=NULL){
		if(Parent->Setting.MultipleRed==1.0 && Parent->Setting.MultipleGreen==1.0 && Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(idxR,idxG),idxB);
			idxR=idxR+StartX;
			idxG=idxG+StartX;
			idxB=idxB+StartX;
			int	MaxDx=max(max(idxR,idxG),idxB);
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

					pB+=idxB;
					pG+=idxG;
					pR+=idxR;
					int	LdxB=idxB;
					int	LdxG=idxG;
					int	LdxR=idxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pB++ =TRBuff[2]->GetYWithoutDepended(LdxB)[yB]	= (*s	 )*GainBlueL +OffsetBlueL	;		// blue
							*pG++ =TRBuff[1]->GetYWithoutDepended(LdxG)[yG]	= (*(s+1))*GainGreenL+OffsetGreenL	;		// green
							*pR++ =TRBuff[0]->GetYWithoutDepended(LdxR)[yR]	= (*(s+2))*GainRedL	 +OffsetRedL	;		// red
							s+=4;				// mono
							LdxB++;
							LdxG++;
							LdxR++;
						}

						int	RdxB=width12+idxB;
						int	RdxG=width12+idxG;
						int	RdxR=width12+idxR;
						for (int j=0; j< width22; j++) {
							*pB++ =TRBuff[2]->GetYWithoutDepended(RdxB)[yB]	= (*s	 )*GainBlueR +OffsetBlueR	;		// blue
							*pG++ =TRBuff[1]->GetYWithoutDepended(RdxG)[yG]	= (*(s+1))*GainGreenR+OffsetGreenR	;		// green
							*pR++ =TRBuff[0]->GetYWithoutDepended(RdxR)[yR]	= (*(s+2))*GainRedR	 +OffsetRedR	;		// red
							s+=4;				// mono
							RdxB++;
							RdxG++;
							RdxR++;
						}
					}
					else{
						pB+=width12+width22-1;
						pG+=width12+width22-1;
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pB-- =TRBuff[2]->GetYWithoutDepended(LdxB)[yB]	= (*s	 )*GainBlueL +OffsetBlueL	;		// blue
							*pG-- =TRBuff[1]->GetYWithoutDepended(LdxG)[yG]	= (*(s+1))*GainGreenL+OffsetGreenL	;		// green
							*pR-- =TRBuff[0]->GetYWithoutDepended(LdxR)[yR]	= (*(s+2))*GainRedL	 +OffsetRedL	;		// red
							s+=4;				// mono
							LdxB++;
							LdxG++;
							LdxR++;
						}

						int	RdxB=width12+idxB;
						int	RdxG=width12+idxG;
						int	RdxR=width12+idxR;
						for (int j=0; j< width22; j++) {
							*pB-- =TRBuff[2]->GetYWithoutDepended(RdxB)[yB]	= (*s	 )*GainBlueR +OffsetBlueR	;		// blue
							*pG-- =TRBuff[1]->GetYWithoutDepended(RdxG)[yG]	= (*(s+1))*GainGreenR+OffsetGreenR	;		// green
							*pR-- =TRBuff[0]->GetYWithoutDepended(RdxR)[yR]	= (*(s+2))*GainRedR	 +OffsetRedR	;		// red
							s+=4;				// mono
							RdxB++;
							RdxG++;
							RdxR++;
						}
					}
				}
			}
		}
		else{
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					int	*tG=MatrixGX;
					int	*tB=MatrixBX;
					//int	*tRTR=MatrixRXTR;
					//int	*tGTR=MatrixGXTR;
					//int	*tBTR=MatrixBXTR;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							int	xG=*tG;
							int	xB=*tB;
							tR++;
							tG++;
							tB++;
							*pB++ = TRBuff[2]->GetYWithoutDepended(j)[yB]	=s[xB];
							*pG++ = TRBuff[1]->GetYWithoutDepended(j)[yG]	=s[xG];
							*pR++ = TRBuff[0]->GetYWithoutDepended(j)[yR]	=s[xR];
							//tRTR++;
							//tGTR++;
							//tBTR++;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
					else{
						pB+=width-1;
						pG+=width-1;
						pR+=width-1;
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							int	xG=*tG;
							int	xB=*tB;
							tR++;
							tG++;
							tB++;
							*pB-- = TRBuff[2]->GetYWithoutDepended(j)[yB]	=s[xB];
							*pG-- = TRBuff[1]->GetYWithoutDepended(j)[yG]	=s[xG];
							*pR-- = TRBuff[0]->GetYWithoutDepended(j)[yR]	=s[xR];
							//tRTR++;
							//tGTR++;
							//tBTR++;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
				}
			//}
		}
		TRBuff[0]->SetFlagCaptured(true);
		TRBuff[1]->SetFlagCaptured(true);
		TRBuff[2]->SetFlagCaptured(true);
		//TRBuff[0]->TranspositionXY(* Buff[0]);
		//TRBuff[1]->TranspositionXY(* Buff[1]);
		//TRBuff[2]->TranspositionXY(* Buff[2]);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0 
		&& Parent->Setting.MultipleGreen==1.0
		&& Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(idxR,idxG),idxB);
			idxR=idxR+StartX;
			idxG=idxG+StartX;
			idxB=idxB+StartX;
			int	MaxDx=max(max(idxR,idxG),idxB);
			if(StartX>=0){
				width	=min(BuffWidth-StartX-MaxDx,width);
				width12	-=StartX;
				if(width12<0)
					width12=0;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				if(width12<0)
					width12=0;
				width22	=width-width12;
			}
			if(Parent->DupLineMode==false){
				if(YN<1024){
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+dyR,0,height-1);
						int	yG=Clipping(y+dyG,0,height-1);
						int	yB=Clipping(y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

						BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

						pB+=idxB;
						pG+=idxG;
						pR+=idxR;
						if(LeftRight==false){
							for (int j=0; j< width12; j++) {
								*pB++ = GainOffsetTableBL[*s	];		// blue
								*pG++ = GainOffsetTableGL[*(s+1)];		// green
								*pR++ = GainOffsetTableRL[*(s+2)];		// red
								s+=4;				// mono
							}

							for (int j=0; j< width22; j++) {
								*pB++ = GainOffsetTableBR[*s	];		// blue
								*pG++ = GainOffsetTableGR[*(s+1)];		// green
								*pR++ = GainOffsetTableRR[*(s+2)];		// red
								s+=4;				// mono
							}
						}
						else{
							pB+=width12+width22-1;
							pG+=width12+width22-1;
							pR+=width12+width22-1;
							for (int j=0; j< width12; j++) {
								*pB-- = GainOffsetTableBL[*s	];		// blue
								*pG-- = GainOffsetTableGL[*(s+1)];		// green
								*pR-- = GainOffsetTableRL[*(s+2)];		// red
								s+=4;				// mono
							}

							for (int j=0; j< width22; j++) {
								*pB-- = GainOffsetTableBR[*s	];		// blue
								*pG-- = GainOffsetTableGR[*(s+1)];		// green
								*pR-- = GainOffsetTableRR[*(s+2)];		// red
								s+=4;				// mono
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
							int	yG=Clipping(y+dyG,0,height-1);
							int	yB=Clipping(y+dyB,0,height-1);
							BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
							BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
							BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

							BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

							pB+=idxB;
							pG+=idxG;
							pR+=idxR;
							if(LeftRight==false){
								for (int j=0; j< width12; j++) {
									*pB++ = GainOffsetTableBL[*s	];		// blue
									*pG++ = GainOffsetTableGL[*(s+1)];		// green
									*pR++ = GainOffsetTableRL[*(s+2)];		// red
									s+=4;				// mono
								}

								for (int j=0; j< width22; j++) {
									*pB++ = GainOffsetTableBR[*s	];		// blue
									*pG++ = GainOffsetTableGR[*(s+1)];		// green
									*pR++ = GainOffsetTableRR[*(s+2)];		// red
									s+=4;				// mono
								}
							}
							else{
								pB+=width12+width22-1;
								pG+=width12+width22-1;
								pR+=width12+width22-1;
								for (int j=0; j< width12; j++) {
									*pB-- = GainOffsetTableBL[*s	];		// blue
									*pG-- = GainOffsetTableGL[*(s+1)];		// green
									*pR-- = GainOffsetTableRL[*(s+2)];		// red
									s+=4;				// mono
								}

								for (int j=0; j< width22; j++) {
									*pB-- = GainOffsetTableBR[*s	];		// blue
									*pG-- = GainOffsetTableGR[*(s+1)];		// green
									*pR-- = GainOffsetTableRR[*(s+2)];		// red
									s+=4;				// mono
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
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);


						BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

						pB+=idxB;
						pG+=idxG;
						pR+=idxR;
						if(LeftRight==false){
							for (int j=0; j< width12; j++) {
								*pB++ = GainOffsetTableBL[*s	];		// blue
								*pG++ = GainOffsetTableGL[*(s+1)];		// green
								*pR++ = GainOffsetTableRL[*(s+2)];		// red
								s+=4;				// mono
							}

							for (int j=0; j< width22; j++) {
								*pB++ = GainOffsetTableBR[*s	];		// blue
								*pG++ = GainOffsetTableGR[*(s+1)];		// green
								*pR++ = GainOffsetTableRR[*(s+2)];		// red
								s+=4;				// mono
							}
						}
						else{
							pB+=width12+width22-1;
							pG+=width12+width22-1;
							pR+=width12+width22-1;
							for (int j=0; j< width12; j++) {
								*pB-- = GainOffsetTableBL[*s	];		// blue
								*pG-- = GainOffsetTableGL[*(s+1)];		// green
								*pR-- = GainOffsetTableRL[*(s+2)];		// red
								s+=4;				// mono
							}

							for (int j=0; j< width22; j++) {
								*pB-- = GainOffsetTableBR[*s	];		// blue
								*pG-- = GainOffsetTableGR[*(s+1)];		// green
								*pR-- = GainOffsetTableRR[*(s+2)];		// red
								s+=4;				// mono
							}
						}
					}
					#pragma omp for
					for (int i=0; i< YN; i++) {
						int	y=StartLine+i;
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						if(yR-2>=0 && yG-2>=0 && yB-2>=0){
							BYTE *pRa= Buff[0]->GetYWithoutDepended(yR-2);
							BYTE *pGa= Buff[1]->GetYWithoutDepended(yG-2);
							BYTE *pBa= Buff[2]->GetYWithoutDepended(yB-2);
							BYTE *pR = Buff[0]->GetYWithoutDepended(yR-1);
							BYTE *pG = Buff[1]->GetYWithoutDepended(yG-1);
							BYTE *pB = Buff[2]->GetYWithoutDepended(yB-1);
							BYTE *pRb= Buff[0]->GetYWithoutDepended(yR);
							BYTE *pGb= Buff[1]->GetYWithoutDepended(yG);
							BYTE *pBb= Buff[2]->GetYWithoutDepended(yB);

							for (int j=0; j< width; j++) {
								pR[j]=(pRa[j]+pRb[j])>>1;
								pG[j]=(pGa[j]+pGb[j])>>1;
								pB[j]=(pBa[j]+pBb[j])>>1;
							}
						}
					}
				}
			}
		}
		else{
			if(Parent->DupLineMode==false){
				#pragma omp parallel
				{
					#pragma omp for
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+dyR,0,height-1);
						int	yG=Clipping(y+dyG,0,height-1);
						int	yB=Clipping(y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

						BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

						/*
						for (int j=0; j< width; j++) {
							*pB++ = *s++;		// blue
							*pG++ = *s++;		// green
							*pR++ = *s++;		// red
							s++;				// mono
						}
						*/
						int	*tR=MatrixRX;
						int	*tG=MatrixGX;
						int	*tB=MatrixBX;
						if(LeftRight==false){
							for (int j=0; j< width; j++) {
								*pB = Clipping((int)(s[*tB]*GainBlueL	+OffsetBlueL	),0,255);		// blue;
								*pG = Clipping((int)(s[*tG]*GainGreenL	+OffsetGreenL	),0,255);		// green;
								*pR = Clipping((int)(s[*tR]*GainRedL	+OffsetRedL		),0,255);		// red;
								tB++;
								tG++;
								tR++;
								pB++;
								pG++;
								pR++;
							}
						}
						else{
							pB+=width-1;
							pG+=width-1;
							pR+=width-1;
							for (int j=0; j< width; j++) {
								*pB = Clipping((int)(s[*tB]*GainBlueL	+OffsetBlueL	),0,255);		// blue;
								*pG = Clipping((int)(s[*tG]*GainGreenL	+OffsetGreenL	),0,255);		// green;
								*pR = Clipping((int)(s[*tR]*GainRedL	+OffsetRedL		),0,255);		// red;
								tB++;
								tG++;
								tR++;
								pB--;
								pG--;
								pR--;
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
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

						BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

						/*
						for (int j=0; j< width; j++) {
							*pB++ = *s++;		// blue
							*pG++ = *s++;		// green
							*pR++ = *s++;		// red
							s++;				// mono
						}
						*/
						int	*tR=MatrixRX;
						int	*tG=MatrixGX;
						int	*tB=MatrixBX;
						if(LeftRight==false){
							for (int j=0; j< width; j++) {
								*pB = Clipping((int)(s[*tB]*GainBlueL	+OffsetBlueL	),0,255);		// blue;
								*pG = Clipping((int)(s[*tG]*GainGreenL	+OffsetGreenL	),0,255);		// green;
								*pR = Clipping((int)(s[*tR]*GainRedL	+OffsetRedL		),0,255);		// red;
								tB++;
								tG++;
								tR++;
								pB++;
								pG++;
								pR++;
							}
						}
						else{
							pB+=width-1;
							pG+=width-1;
							pR+=width-1;
							for (int j=0; j< width; j++) {
								*pB = Clipping((int)(s[*tB]*GainBlueL	+OffsetBlueL	),0,255);		// blue;
								*pG = Clipping((int)(s[*tG]*GainGreenL	+OffsetGreenL	),0,255);		// green;
								*pR = Clipping((int)(s[*tR]*GainRedL	+OffsetRedL		),0,255);		// red;
								tB++;
								tG++;
								tR++;
								pB--;
								pG--;
								pR--;
							}
						}
					}
					#pragma omp for
					for (int i=0; i< YN; i++) {
						int	y=StartLine+i;
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						if(yR-2>=0 && yG-2>=0 && yB-2>=0){
							BYTE *pRa= Buff[0]->GetYWithoutDepended(yR-2);
							BYTE *pGa= Buff[1]->GetYWithoutDepended(yG-2);
							BYTE *pBa= Buff[2]->GetYWithoutDepended(yB-2);
							BYTE *pR = Buff[0]->GetYWithoutDepended(yR-1);
							BYTE *pG = Buff[1]->GetYWithoutDepended(yG-1);
							BYTE *pB = Buff[2]->GetYWithoutDepended(yB-1);
							BYTE *pRb= Buff[0]->GetYWithoutDepended(yR);
							BYTE *pGb= Buff[1]->GetYWithoutDepended(yG);
							BYTE *pBb= Buff[2]->GetYWithoutDepended(yB);

							for (int j=0; j< width; j++) {
								pR[j]=(pRa[j]+pRb[j])>>1;
								pG[j]=(pGa[j]+pGb[j])>>1;
								pB[j]=(pBa[j]+pBb[j])>>1;
							}
						}
					}
				}
			}
		}
	}

	return r;
}

bool saperaCtrlColor::getPartialImageInsideBasic(int Index ,ImageBuffer *Buff[],ImageBuffer *TRBuff[]
									,int StartLine , int EndLine
									,void	*SrcAddress
									,int	BuffWidth
									,int width
									,int height)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	width12	=2048;
	int	width22	=width-width12;
	int	W4=height/4;

	int		YN=EndLine-StartLine;
	int		idxR=dxR;
	int		idxG=dxG;
	int		idxB=dxB;

	if(GetParamGlobal()->AllocateTargetTRBuff==true && TRBuff[0]!=NULL){
		if(Parent->Setting.MultipleRed==1.0 && Parent->Setting.MultipleGreen==1.0 && Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(idxR,idxG),idxB);
			idxR=idxR+StartX;
			idxG=idxG+StartX;
			idxB=idxB+StartX;
			int	MaxDx=max(max(idxR,idxG),idxB);
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
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

					pB+=idxB;
					pG+=idxG;
					pR+=idxR;
					int	LdxB=idxB;
					int	LdxG=idxG;
					int	LdxR=idxR;
					if(LeftRight==false){
						for (int j=0; j< width12; j++) {
							*pB++ =TRBuff[2]->GetYWithoutDepended(LdxB)[yB]	= (*s	 );		// blue
							*pG++ =TRBuff[1]->GetYWithoutDepended(LdxG)[yG]	= (*(s+1));		// green
							*pR++ =TRBuff[0]->GetYWithoutDepended(LdxR)[yR]	= (*(s+2));		// red
							s+=4;				// mono
							LdxB++;
							LdxG++;
							LdxR++;
						}

						int	RdxB=width12+idxB;
						int	RdxG=width12+idxG;
						int	RdxR=width12+idxR;
						for (int j=0; j< width22; j++) {
							*pB++ =TRBuff[2]->GetYWithoutDepended(RdxB)[yB]	= (*s	 );		// blue
							*pG++ =TRBuff[1]->GetYWithoutDepended(RdxG)[yG]	= (*(s+1));		// green
							*pR++ =TRBuff[0]->GetYWithoutDepended(RdxR)[yR]	= (*(s+2));		// red
							s+=4;				// mono
							RdxB++;
							RdxG++;
							RdxR++;
						}
					}
					else{
						pB+=width12+width22-1;
						pG+=width12+width22-1;
						pR+=width12+width22-1;
						for (int j=0; j< width12; j++) {
							*pB-- =TRBuff[2]->GetYWithoutDepended(LdxB)[yB]	= (*s	 );		// blue
							*pG-- =TRBuff[1]->GetYWithoutDepended(LdxG)[yG]	= (*(s+1));		// green
							*pR-- =TRBuff[0]->GetYWithoutDepended(LdxR)[yR]	= (*(s+2));		// red
							s+=4;				// mono
							LdxB++;
							LdxG++;
							LdxR++;
						}

						int	RdxB=width12+idxB;
						int	RdxG=width12+idxG;
						int	RdxR=width12+idxR;
						for (int j=0; j< width22; j++) {
							*pB-- =TRBuff[2]->GetYWithoutDepended(RdxB)[yB]	= (*s	 );		// blue
							*pG-- =TRBuff[1]->GetYWithoutDepended(RdxG)[yG]	= (*(s+1));		// green
							*pR-- =TRBuff[0]->GetYWithoutDepended(RdxR)[yR]	= (*(s+2));		// red
							s+=4;				// mono
							RdxB++;
							RdxG++;
							RdxR++;
						}
					}
				}
			}
		}
		else{
			//#pragma omp parallel
			//{
			//	#pragma omp for
				for (int i=0; i< YN; i++) {
					// ruglas64のRGBバッファポインタを得る
					int	y=StartLine+i;
					int	yR=Clipping(y+dyR,0,height-1);
					int	yG=Clipping(y+dyG,0,height-1);
					int	yB=Clipping(y+dyB,0,height-1);
					BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
					BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
					BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

					BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

					/*
					for (int j=0; j< width; j++) {
						*pB++ = *s++;		// blue
						*pG++ = *s++;		// green
						*pR++ = *s++;		// red
						s++;				// mono
					}
					*/
					int	*tR=MatrixRX;
					int	*tG=MatrixGX;
					int	*tB=MatrixBX;
					//int	*tRTR=MatrixRXTR;
					//int	*tGTR=MatrixGXTR;
					//int	*tBTR=MatrixBXTR;
					if(LeftRight==false){
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							int	xG=*tG;
							int	xB=*tB;
							tR++;
							tG++;
							tB++;
							*pB++ = TRBuff[2]->GetYWithoutDepended(j)[yB]	=s[xB];
							*pG++ = TRBuff[1]->GetYWithoutDepended(j)[yG]	=s[xG];
							*pR++ = TRBuff[0]->GetYWithoutDepended(j)[yR]	=s[xR];
							//tRTR++;
							//tGTR++;
							//tBTR++;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
					else{
						pB+=width-1;
						pG+=width-1;
						pR+=width-1;
						for (int j=0; j< width; j++) {
							int	xR=*tR;
							int	xG=*tG;
							int	xB=*tB;
							tR++;
							tG++;
							tB++;
							*pB-- = TRBuff[2]->GetYWithoutDepended(j)[yB]	=s[xB];
							*pG-- = TRBuff[1]->GetYWithoutDepended(j)[yG]	=s[xG];
							*pR-- = TRBuff[0]->GetYWithoutDepended(j)[yR]	=s[xR];
							//tRTR++;
							//tGTR++;
							//tBTR++;
							//TRBuff[0]->GetY(j)[yR]=r;
							//TRBuff[1]->GetY(j)[yG]=g;
							//TRBuff[2]->GetY(j)[yB]=b;
						}
					}
				}
			//}
		}
		TRBuff[0]->SetFlagCaptured(true);
		TRBuff[1]->SetFlagCaptured(true);
		TRBuff[2]->SetFlagCaptured(true);
		//TRBuff[0]->TranspositionXY(* Buff[0]);
		//TRBuff[1]->TranspositionXY(* Buff[1]);
		//TRBuff[2]->TranspositionXY(* Buff[2]);
	}
	else{
		if(Parent->Setting.MultipleRed==1.0 
		&& Parent->Setting.MultipleGreen==1.0
		&& Parent->Setting.MultipleBlue==1.0){
			int		StartX=-min(min(idxR,idxG),idxB);
			idxR=idxR+StartX;
			idxG=idxG+StartX;
			idxB=idxB+StartX;
			int	MaxDx=max(max(idxR,idxG),idxB);
			if(StartX>=0){
				width	=min(BuffWidth-StartX-MaxDx,width);
				width12	-=StartX;
				if(width12<0)
					width12=0;
				width22	=width-width12;
			}
			else{
				width	=width+StartX-MaxDx;
				StartX=0;
				width12	-=StartX;
				if(width12<0)
					width12=0;
				width22	=width-width12;
			}
			if(Parent->DupLineMode==false){
				if(YN<1024){
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+dyR,0,height-1);
						int	yG=Clipping(y+dyG,0,height-1);
						int	yB=Clipping(y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

						BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

						pB+=idxB;
						pG+=idxG;
						pR+=idxR;
						if(LeftRight==false){
							for (int j=0; j< width; j++) {
								*pB++ = *s	;		// blue
								*pG++ = *(s+1);		// green
								*pR++ = *(s+2);		// red
								s+=4;				// mono
							}
						}
						else{
							pB+=width12+width22-1;
							pG+=width12+width22-1;
							pR+=width12+width22-1;
							for (int j=0; j< width; j++) {
								*pB-- = *s	;		// blue
								*pG-- = *(s+1);		// green
								*pR-- = *(s+2);		// red
								s+=4;				// mono
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
							int	yG=Clipping(y+dyG,0,height-1);
							int	yB=Clipping(y+dyB,0,height-1);
							BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
							BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
							BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

							BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

							pB+=idxB;
							pG+=idxG;
							pR+=idxR;
							if(LeftRight==false){
								for (int j=0; j< width; j++) {
									*pB++ = *s	;		// blue
									*pG++ = *(s+1);		// green
									*pR++ = *(s+2);		// red
									s+=4;				// mono
								}
							}
							else{
								pB+=width12+width22-1;
								pG+=width12+width22-1;
								pR+=width12+width22-1;
								for (int j=0; j< width; j++) {
									*pB-- = *s	;		// blue
									*pG-- = *(s+1);		// green
									*pR-- = *(s+2);		// red
									s+=4;				// mono
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
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);


						BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

						pB+=idxB;
						pG+=idxG;
						pR+=idxR;
						if(LeftRight==false){
							for (int j=0; j< width; j++) {
								*pB++ = *s	;		// blue
								*pG++ = *(s+1);		// green
								*pR++ = *(s+2);		// red
								s+=4;				// mono
							}
						}
						else{
							pB+=width12+width22-1;
							pG+=width12+width22-1;
							pR+=width12+width22-1;
							for (int j=0; j< width; j++) {
								*pB-- = *s	;		// blue
								*pG-- = *(s+1);		// green
								*pR-- = *(s+2);		// red
								s+=4;				// mono
							}
						}
					}
					#pragma omp for
					for (int i=0; i< YN; i++) {
						int	y=StartLine+i;
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						if(yR-2>=0 && yG-2>=0 && yB-2>=0){
							BYTE *pRa= Buff[0]->GetYWithoutDepended(yR-2);
							BYTE *pGa= Buff[1]->GetYWithoutDepended(yG-2);
							BYTE *pBa= Buff[2]->GetYWithoutDepended(yB-2);
							BYTE *pR = Buff[0]->GetYWithoutDepended(yR-1);
							BYTE *pG = Buff[1]->GetYWithoutDepended(yG-1);
							BYTE *pB = Buff[2]->GetYWithoutDepended(yB-1);
							BYTE *pRb= Buff[0]->GetYWithoutDepended(yR);
							BYTE *pGb= Buff[1]->GetYWithoutDepended(yG);
							BYTE *pBb= Buff[2]->GetYWithoutDepended(yB);

							for (int j=0; j< width; j++) {
								pR[j]=(pRa[j]+pRb[j])>>1;
								pG[j]=(pGa[j]+pGb[j])>>1;
								pB[j]=(pBa[j]+pBb[j])>>1;
							}
						}
					}
				}
			}
		}
		else{
			if(Parent->DupLineMode==false){
				//#pragma omp parallel
				//{
				//	#pragma omp for
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+dyR,0,height-1);
						int	yG=Clipping(y+dyG,0,height-1);
						int	yB=Clipping(y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

						BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

						/*
						for (int j=0; j< width; j++) {
							*pB++ = *s++;		// blue
							*pG++ = *s++;		// green
							*pR++ = *s++;		// red
							s++;				// mono
						}
						*/
						int	*tR=MatrixRX;
						int	*tG=MatrixGX;
						int	*tB=MatrixBX;
						if(LeftRight==false){
							for (int j=0; j< width; j++) {
								*pB = s[*tB];
								*pG = s[*tG];
								*pR = s[*tR];
								tB++;
								tG++;
								tR++;
								pB++;
								pG++;
								pR++;
							}
						}
						else{
							pB+=width-1;
							pG+=width-1;
							pR+=width-1;
							for (int j=0; j< width; j++) {
								*pB = s[*tB];
								*pG = s[*tG];
								*pR = s[*tR];
								tB++;
								tG++;
								tR++;
								pB--;
								pG--;
								pR--;
							}
						}
					}
				//}
			}
			else{
				#pragma omp parallel
				{
					#pragma omp for
					for (int i=0; i< YN; i++) {
						// ruglas64のRGBバッファポインタを得る
						int	y=StartLine+i;
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						BYTE *pR = Buff[0]->GetYWithoutDepended(yR);
						BYTE *pG = Buff[1]->GetYWithoutDepended(yG);
						BYTE *pB = Buff[2]->GetYWithoutDepended(yB);

						BYTE	*s=((BYTE *)SrcAddress)+y*BuffWidth*4;

						/*
						for (int j=0; j< width; j++) {
							*pB++ = *s++;		// blue
							*pG++ = *s++;		// green
							*pR++ = *s++;		// red
							s++;				// mono
						}
						*/
						int	*tR=MatrixRX;
						int	*tG=MatrixGX;
						int	*tB=MatrixBX;
						if(LeftRight==false){
							for (int j=0; j< width; j++) {
								*pB = s[*tB];
								*pG = s[*tG];
								*pR = s[*tR];
								tB++;
								tG++;
								tR++;
								pB++;
								pG++;
								pR++;
							}
						}
						else{
							pB+=width-1;
							pG+=width-1;
							pR+=width-1;
							for (int j=0; j< width; j++) {
								*pB = s[*tB];
								*pG = s[*tG];
								*pR = s[*tR];
								tB++;
								tG++;
								tR++;
								pB--;
								pG--;
								pR--;
							}
						}
					}
					#pragma omp for
					for (int i=0; i< YN; i++) {
						int	y=StartLine+i;
						int	yR=Clipping(y+y+dyR,0,height-1);
						int	yG=Clipping(y+y+dyG,0,height-1);
						int	yB=Clipping(y+y+dyB,0,height-1);
						if(yR-2>=0 && yG-2>=0 && yB-2>=0){
							BYTE *pRa= Buff[0]->GetYWithoutDepended(yR-2);
							BYTE *pGa= Buff[1]->GetYWithoutDepended(yG-2);
							BYTE *pBa= Buff[2]->GetYWithoutDepended(yB-2);
							BYTE *pR = Buff[0]->GetYWithoutDepended(yR-1);
							BYTE *pG = Buff[1]->GetYWithoutDepended(yG-1);
							BYTE *pB = Buff[2]->GetYWithoutDepended(yB-1);
							BYTE *pRb= Buff[0]->GetYWithoutDepended(yR);
							BYTE *pGb= Buff[1]->GetYWithoutDepended(yG);
							BYTE *pBb= Buff[2]->GetYWithoutDepended(yB);

							for (int j=0; j< width; j++) {
								pR[j]=(pRa[j]+pRb[j])>>1;
								pG[j]=(pGa[j]+pGb[j])>>1;
								pB[j]=(pBa[j]+pBb[j])>>1;
							}
						}
					}
				}
			}
		}
	}

	return r;
}

bool saperaCtrlColor::getPartialImageInsideShrink2(int Index ,ImageBuffer *Buff[],ImageBuffer *TRBuff[]
									,int StartLine , int EndLine)
{
	//int pic = _Buffers->GetBytesPerPixel();

	bool r = false;
	int	BuffWidth=_Buffers->GetWidth();
	int width	= min(Buff[0]->GetWidth() ,BuffWidth);	//CONST_MAX_WIDTH;
	int height	= min(Buff[0]->GetHeight(),(Parent->DupLineMode==false)?_Buffers->GetHeight():_Buffers->GetHeight()*2);	//CONST_MAX_HEIGHT;

	//int	W4=height/4;

	void	*SrcAddress;
	if(Index>=0){
		_Buffers->GetAddress(Index,&SrcAddress);
	}
	else{
		_Buffers->GetAddress(&SrcAddress);
	}

	bool	LeftRight	=Parent->Setting.LeftRight;
	StartLine &=0xFF4FFFFE;
	int		YN=EndLine-StartLine;

	int		StartX=-min(min(dxR,dxG),dxB);
	dxR=dxR+StartX;
	dxG=dxG+StartX;
	dxB=dxB+StartX;
	YN/=2;

	//#pragma omp parallel
	//{
	//	#pragma omp for
		for (int i=0; i< YN; i++) {
			// ruglas64のRGBバッファポインタを得る
			int	y=StartLine+i*2;
			int	yR=Clipping(y+dyR,0,height*2-1);
			int	yG=Clipping(y+dyG,0,height*2-1);
			int	yB=Clipping(y+dyB,0,height*2-1);
			BYTE *pR = Buff[0]->GetYWithoutDepended(yR/2);
			BYTE *pG = Buff[1]->GetYWithoutDepended(yG/2);
			BYTE *pB = Buff[2]->GetYWithoutDepended(yB/2);

			BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;
			s+=4;

			pB+=dxB;
			pG+=dxG;
			pR+=dxR;
			if(Parent->Setting.GainRedL==1.0 
			&& Parent->Setting.GainGreenL==1.0
			&& Parent->Setting.GainBlueL==1.0
			&& Parent->Setting.GainRedR==1.0 
			&& Parent->Setting.GainGreenR==1.0
			&& Parent->Setting.GainBlueR==1.0	){
				if(LeftRight==false){
					for (int j=0; j< width; j++) {
						*pB++ = *s	  ;		// blue
						*pG++ = *(s+1);		// green
						*pR++ = *(s+2);		// red
						s+=8;				// mono
					}
				}
				else{
					pB+=width-1;
					pG+=width-1;
					pR+=width-1;
					for (int j=0; j< width; j++) {
						*pB-- = *s	  ;		// blue
						*pG-- = *(s+1);		// green
						*pR-- = *(s+2);		// red
						s+=8;				// mono
					}
				}
			}
			else{
				if(LeftRight==false){
					//for (int j=0; j< width; j++) {
					//	*pB++ = Clipping(*s	   +*(s+4),0,255);		// blue
					//	*pG++ = Clipping(*(s+1)+*(s+5),0,255);		// green
					//	*pR++ = Clipping(*(s+2)+*(s+6),0,255);		// red
					//	s+=8;				// mono
					//}
					int	j=0;
					for (j=0; j< 2047; j++) {
						*pB++ = Clipping(*s	   +*(s+4),0,255);		// blue
						*pG++ = Clipping(*(s+1)+*(s+5),0,255);		// green
						*pR++ = Clipping(*(s+2)+*(s+6),0,255);		// red
						s+=8;				// mono
					}
						*pB++ = Clipping(*s	   +*(s  ),0,255);		// blue
						*pG++ = Clipping(*(s+1)+*(s+1),0,255);		// green
						*pR++ = Clipping(*(s+2)+*(s+2),0,255);		// red
						s+=8;				// mono
						j++;
					for (; j< width; j++) {
						*pB++ = Clipping(*s	   +*(s+4),0,255);		// blue
						*pG++ = Clipping(*(s+1)+*(s+5),0,255);		// green
						*pR++ = Clipping(*(s+2)+*(s+6),0,255);		// red
						s+=8;				// mono
					}
				}
				else{
					pB+=width-1;
					pG+=width-1;
					pR+=width-1;
					//for (int j=0; j< width; j++) {
					//	*pB-- = Clipping(*s	   +*(s+4),0,255);		// blue
					//	*pG-- = Clipping(*(s+1)+*(s+5),0,255);		// green
					//	*pR-- = Clipping(*(s+2)+*(s+6),0,255);		// red
					//	s+=8;				// mono
					//}
					int	j=0;
					for (j=0; j< 2047; j++) {
						*pB-- = Clipping(*s	   +*(s+4),0,255);		// blue
						*pG-- = Clipping(*(s+1)+*(s+5),0,255);		// green
						*pR-- = Clipping(*(s+2)+*(s+6),0,255);		// red
						s+=8;				// mono
					}
						*pB-- = Clipping(*s	   +*(s+0),0,255);		// blue
						*pG-- = Clipping(*(s+1)+*(s+1),0,255);		// green
						*pR-- = Clipping(*(s+2)+*(s+2),0,255);		// red
						s+=8;				// mono
						j++;
					for (; j< width; j++) {
						*pB-- = Clipping(*s	   +*(s+4),0,255);		// blue
						*pG-- = Clipping(*(s+1)+*(s+5),0,255);		// green
						*pR-- = Clipping(*(s+2)+*(s+6),0,255);		// red
						s+=8;				// mono
					}
				}
			}
		}
	//}

	return r;
}

void saperaCtrlColor::RemoveCenterBlack(ImageBuffer *Buff[])
{
	int	BuffWidth=_Buffers->GetWidth();
	int	BuffWidth2=BuffWidth/2;
	int	YN=_Buffers->GetHeight();
	ImageBuffer *BR=Buff[0];
	ImageBuffer *BG=Buff[1];
	ImageBuffer *BB=Buff[2];

	int	WR	=ceil(BuffWidth2*Parent->Setting.MultipleRed	+Parent->Setting.OffsetXRed		);
	int	WG	=ceil(BuffWidth2*Parent->Setting.MultipleGreen	+Parent->Setting.OffsetXGreen	);
	int	WB	=ceil(BuffWidth2*Parent->Setting.MultipleBlue	+Parent->Setting.OffsetXBlue	);

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YN;y++){
			BYTE	*tR=BR->GetYWithoutDepended(y);
			BYTE	*tG=BG->GetYWithoutDepended(y);
			BYTE	*tB=BB->GetYWithoutDepended(y);
			if(tR[WR-1]!=0 && tR[WR]==0 && tR[WR+1]!=0)
				tR[WR]=(tR[WR-1]+tR[WR+1])>>1;
			if(tG[WG-1]!=0 && tG[WG]==0 && tG[WG+1]!=0)
				tG[WG]=(tG[WG-1]+tG[WG+1])>>1;
			if(tB[WB-1]!=0 && tB[WB]==0 && tB[WB+1]!=0)
				tB[WB]=(tB[WB-1]+tB[WB+1])>>1;
		}
	}
}