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
#include "CameraXtiumPx8Repeat.h"

bool saperaCtrl::getImage(ImageBuffer *Buff[],ImageBuffer *TRBuff[])
{
	//int	YLen=GetMaxLines();
	//int	DotPerLine=GetDotPerLine();
	//LockGetImage.lock();
	//for(int y=0;y<YLen;y++){
	//	int	RPoint=(CurrentRPoint+y) % ImageStack[0].GetHeight();
	//
	//	memcpy(Buff[0]->GetYWithoutDepended(y),ImageStack[0].GetY(RPoint),DotPerLine);
	//	memcpy(Buff[1]->GetYWithoutDepended(y),ImageStack[1].GetY(RPoint),DotPerLine);
	//	memcpy(Buff[2]->GetYWithoutDepended(y),ImageStack[2].GetY(RPoint),DotPerLine);
	//}
	//LockGetImage.unlock();
	//
	//CurrentRPoint=(CurrentRPoint+YLen) % ImageStack[0].GetHeight();
	//
	//MutexStackedLineCount.lock();
	//StackedLineCount-=YLen;
	//MutexStackedLineCount.unlock();

	if(Parent->Setting.VerticalBinning==2){
		int	YLen=GetMaxLines();
		int	DotPerLine=GetDotPerLine();
		for(int y=0;y<YLen;y+=2){
			memcpy(Buff[0]->GetYWithoutDepended(y+1),Buff[0]->GetYWithoutDepended(y),DotPerLine);
			memcpy(Buff[1]->GetYWithoutDepended(y+1),Buff[1]->GetYWithoutDepended(y),DotPerLine);
			memcpy(Buff[2]->GetYWithoutDepended(y+1),Buff[2]->GetYWithoutDepended(y),DotPerLine);
		}
	}
	if(Parent->Setting.VerticalBinning==4){
		int	YLen=GetMaxLines();
		int	DotPerLine=GetDotPerLine();

		int	N=(YLen-4)/4;
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<N;i++){
			//for(int y=0;y<YLen-4;y+=4){
				int	y=i<<2;
				//for(int m=0;m<3;m++){
				//	BYTE	*SrcR1=Buff[m]->GetYWithoutDepended(y);
				//	BYTE	*Dst1R=Buff[m]->GetYWithoutDepended(y+1);
				//	BYTE	*Dst2R=Buff[m]->GetYWithoutDepended(y+2);
				//	BYTE	*Dst3R=Buff[m]->GetYWithoutDepended(y+3);
				//	BYTE	*SrcR2=Buff[m]->GetYWithoutDepended(y+4);
				//	for(int x=0;x<DotPerLine;x++){
				//		*Dst1R=((*SrcR1)*3+(*SrcR2))>>2;
				//		*Dst2R=((*SrcR1)+(*SrcR2))>>1;
				//		*Dst3R=((*SrcR1)+(*SrcR2)*3)>>2;
				//		SrcR1++;
				//		SrcR2++;
				//		Dst1R++;
				//		Dst2R++;
				//		Dst3R++;
				//	}
				//}
				BYTE	*SrcR1=Buff[0]->GetYWithoutDepended(y);
				BYTE	*Dst1R=Buff[0]->GetYWithoutDepended(y+1);
				BYTE	*Dst2R=Buff[0]->GetYWithoutDepended(y+2);
				BYTE	*Dst3R=Buff[0]->GetYWithoutDepended(y+3);
				BYTE	*SrcR2=Buff[0]->GetYWithoutDepended(y+4);
				BYTE	*SrcG1=Buff[1]->GetYWithoutDepended(y);
				BYTE	*Dst1G=Buff[1]->GetYWithoutDepended(y+1);
				BYTE	*Dst2G=Buff[1]->GetYWithoutDepended(y+2);
				BYTE	*Dst3G=Buff[1]->GetYWithoutDepended(y+3);
				BYTE	*SrcG2=Buff[1]->GetYWithoutDepended(y+4);
				BYTE	*SrcB1=Buff[2]->GetYWithoutDepended(y);
				BYTE	*Dst1B=Buff[2]->GetYWithoutDepended(y+1);
				BYTE	*Dst2B=Buff[2]->GetYWithoutDepended(y+2);
				BYTE	*Dst3B=Buff[2]->GetYWithoutDepended(y+3);
				BYTE	*SrcB2=Buff[2]->GetYWithoutDepended(y+4);
				for(int x=0;x<DotPerLine;x++){
					unsigned short	tR=*SrcR1;
					unsigned short	tG=*SrcG1;
					unsigned short	tB=*SrcB1;

					unsigned short	mR=*SrcR2;
					unsigned short	mG=*SrcG2;
					unsigned short	mB=*SrcB2;

					*Dst1R=((tR<<1)+tR+mR)>>2;
					*Dst1G=((tG<<1)+tG+mG)>>2;
					*Dst1B=((tB<<1)+tB+mB)>>2;
					*Dst2R=(tR+mR)>>1;
					*Dst2G=(tG+mG)>>1;
					*Dst2B=(tB+mB)>>1;
					*Dst3R=(tR+(mR<<1)+mR)>>2;
					*Dst3G=(tG+(mG<<1)+mG)>>2;
					*Dst3B=(tB+(mB<<1)+mB)>>2;
					SrcR1++;
					SrcR2++;
					Dst1R++;
					Dst2R++;
					Dst3R++;
					SrcG1++;
					SrcG2++;
					Dst1G++;
					Dst2G++;
					Dst3G++;
					SrcB1++;
					SrcB2++;
					Dst1B++;
					Dst2B++;
					Dst3B++;
				}
			}
		}
	}
	StateInPage[CurrentRPage]=2;
	CurrentRPage++;

	return true;
}

void	saperaCtrl::CaptureImage(void)
{
	ImageBuffer *Buff[3];

	//GSleep(10);
	if(GetLayersBase()->IsReadyOK()==true){
		if(0<=CurrentWPage && CurrentWPage<GetPageNumb()){
			GetLayersBase()->GetPageData(CurrentWPage)->GetTargetImages(Buff,GetLayerNumb(CurrentWPage));
			int	iCurrentWPage=CurrentWPage;
			Parent->OutputCurrentPage(CurrentWPage);
			Index=(_Buffers->GetIndex())%GCount;
			//int	YN=_Buffers->GetHeight();
			int	Wn=getPartialImageInside(-1 ,Buff
									,0
									,Parent->Setting.VerticalBinning);
			
			int	N=(GetMaxLines()-OverlapYLen)/8-Wn;
			if(N>0){
				if(0<=CurrentWPage && CurrentWPage<GetPageNumb()){
					GetLayersBase()->GetPageData(CurrentWPage)->GetTargetImages(Buff,GetLayerNumb(CurrentWPage));
					getPartialImageInside(-1 ,Buff
									//,max(N-100,0));
									,max(N,0)
									,Parent->Setting.VerticalBinning);
				}
			}
			if(iCurrentWPage>=0 && iCurrentWPage!=CurrentWPage){

				GetLayersBase()->GetPageData(iCurrentWPage  )->GetTargetImages(    Buff,GetLayerNumb(CurrentWPage));
				int	YLen=GetMaxLines();
				int	DotPerLine=GetDotPerLine();

				if(iCurrentWPage!=0){
					for(int y=0;y<OverlapYLen+OverlapAddedYLen;y++){
						memcpy(Buff[0]->GetYWithoutDepended(y),Parent->BottomArea[0].GetYWithoutDepended(y),DotPerLine);
						memcpy(Buff[1]->GetYWithoutDepended(y),Parent->BottomArea[1].GetYWithoutDepended(y),DotPerLine);
						memcpy(Buff[2]->GetYWithoutDepended(y),Parent->BottomArea[2].GetYWithoutDepended(y),DotPerLine);
					}
				}
				if(iCurrentWPage==0 || iCurrentWPage==1){
					for(int y=0;y<OverlapYLen;y++){
						memcpy(Buff[0]->GetYWithoutDepended(y),Buff[0]->GetYWithoutDepended(OverlapYLen),DotPerLine);
						memcpy(Buff[1]->GetYWithoutDepended(y),Buff[1]->GetYWithoutDepended(OverlapYLen),DotPerLine);
						memcpy(Buff[2]->GetYWithoutDepended(y),Buff[2]->GetYWithoutDepended(OverlapYLen),DotPerLine);
					}
				}
				for(int y=0;y<OverlapYLen+OverlapAddedYLen;y++){
					memcpy(Parent->BottomArea[0].GetYWithoutDepended(y),Buff[0]->GetYWithoutDepended(YLen-OverlapYLen+y-DeadYLine-OverlapAddedYLen),DotPerLine);
					memcpy(Parent->BottomArea[1].GetYWithoutDepended(y),Buff[1]->GetYWithoutDepended(YLen-OverlapYLen+y-DeadYLine-OverlapAddedYLen),DotPerLine);
					memcpy(Parent->BottomArea[2].GetYWithoutDepended(y),Buff[2]->GetYWithoutDepended(YLen-OverlapYLen+y-DeadYLine-OverlapAddedYLen),DotPerLine);
				}
			}
		}
		Parent->OutputCurrentPage(CurrentWPage);
	}
}

int saperaCtrl::getPartialImageInside(int Index ,ImageBuffer *Buff[]
									,int DMAStartLine
									,int SkipLine)
{
	//int pic = _Buffers->GetBytesPerPixel();

	int	BuffWidth=_Buffers->GetWidth();
	int DstWidth	= Buff[0]->GetWidth();
	int BuffHeight	= _Buffers->GetHeight();
	int DstHeight	= Buff[0]->GetHeight();
	int	StartX=0;	//Parent->Setting.ImageStart;

	void	*SrcAddress;
	if(Index>=0){
		_Buffers->GetAddress(Index,&SrcAddress);
	}
	else{
		_Buffers->GetAddress(&SrcAddress);
	}
	BYTE	RTable[256];
	BYTE	GTable[256];
	BYTE	BTable[256];
	for(int i=0;i<256;i++){
		RTable[i]=Clipping(((int)Parent->Setting.GainRedL*i	)	,0,255);
		GTable[i]=Clipping(((int)Parent->Setting.GainGreenL*i)	,0,255);
		BTable[i]=Clipping(((int)Parent->Setting.GainBlueL*i)	,0,255);
	}

	int		dyR			=Parent->Setting.OffsetYRed;
	int		dyG			=Parent->Setting.OffsetYGreen;
	int		dyB			=Parent->Setting.OffsetYBlue;

	//bool	LeftRight	=Parent->Setting.LeftRight;

	int		YN=BuffHeight-DMAStartLine;


	if(DstWidth+StartX>BuffWidth){
		DstWidth=BuffWidth-StartX;
	}

	if(SkipLine<=1){
		if(CurrentWPoint+YN+dyR>DstHeight)
			YN=DstHeight-CurrentWPoint-OverlapYLen;
		if(CurrentWPoint+YN+dyG>DstHeight)
			YN=DstHeight-CurrentWPoint-OverlapYLen;
		if(CurrentWPoint+YN+dyB>DstHeight)
			YN=DstHeight-CurrentWPoint-OverlapYLen;

		#pragma omp parallel
		{
			#pragma omp for
			for (int i=0; i< YN; i++) {
				// ruglas64のRGBバッファポインタを得る
				int	y=DMAStartLine+i;
				int	yR=CurrentWPoint+i+dyR;
				int	yG=CurrentWPoint+i+dyG;
				int	yB=CurrentWPoint+i+dyB;
				if(yR<0 || DstHeight<=yR
				|| yG<0 || DstHeight<=yG
				|| yB<0 || DstHeight<=yB){
					continue;
				}
				BYTE *pR = Buff[0]->GetYWithoutDepended(yR+OverlapYLen);
				BYTE *pG = Buff[1]->GetYWithoutDepended(yG+OverlapYLen);
				BYTE *pB = Buff[2]->GetYWithoutDepended(yB+OverlapYLen);

				BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

				for (int j=0; j< DstWidth; j++) {
					*pB++ = BTable[*s	 ];		// blue
					*pG++ = GTable[*(s+1)];		// green
					*pR++ = RTable[*(s+2)];		// red
					s+=4;				// mono
				}
			}
		}
		CurrentWPoint+=YN;
	}
	else if(SkipLine==2){
		if(CurrentWPoint+YN*2+dyR>DstHeight)
			YN=(DstHeight-OverlapYLen-CurrentWPoint)/2;
		if(CurrentWPoint+YN*2+dyG>DstHeight)
			YN=(DstHeight-OverlapYLen-CurrentWPoint)/2;
		if(CurrentWPoint+YN*2+dyB>DstHeight)
			YN=(DstHeight-OverlapYLen-CurrentWPoint)/2;
		#pragma omp parallel
		{
			#pragma omp for
			for (int i=0; i< YN; i++) {
				// ruglas64のRGBバッファポインタを得る
				int	y=DMAStartLine+i;
				int	yR=CurrentWPoint+(i+dyR)*2+OverlapYLen;
				int	yG=CurrentWPoint+(i+dyG)*2+OverlapYLen;
				int	yB=CurrentWPoint+(i+dyB)*2+OverlapYLen;
				if(yR<0 || DstHeight<=yR
				|| yG<0 || DstHeight<=yG
				|| yB<0 || DstHeight<=yB){
					continue;
				}
				BYTE *pR1 = Buff[0]->GetYWithoutDepended(yR);
				BYTE *pG1 = Buff[1]->GetYWithoutDepended(yG);
				BYTE *pB1 = Buff[2]->GetYWithoutDepended(yB);
				//BYTE *pR2 = Buff[0]->GetYWithoutDepended(yR+1);
				//BYTE *pG2 = Buff[1]->GetYWithoutDepended(yG+1);
				//BYTE *pB2 = Buff[2]->GetYWithoutDepended(yB+1);

				BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

				for (int j=0; j< DstWidth; j++) {
					BYTE	tR=*s;
					BYTE	tG=*(s+1);
					BYTE	tB=*(s+2);

					*pB1++ = BTable[tR];		// blue
					*pG1++ = GTable[tG];		// green
					*pR1++ = RTable[tB];		// red
					//*pB2++ = tR;		// blue
					//*pG2++ = tG;		// green
					//*pR2++ = tB;		// red
					s+=4;				
				}
			}
		}
		CurrentWPoint+=YN*2;
	}
	else if(SkipLine==4){
		if(CurrentWPoint+YN*4+dyR>DstHeight)
			YN=(DstHeight-OverlapYLen-CurrentWPoint)/4;
		if(CurrentWPoint+YN*4+dyG>DstHeight)
			YN=(DstHeight-OverlapYLen-CurrentWPoint)/4;
		if(CurrentWPoint+YN*4+dyB>DstHeight)
			YN=(DstHeight-OverlapYLen-CurrentWPoint)/4;

		#pragma omp parallel
		{
			#pragma omp for
			for (int i=0; i< YN; i++) {
				// ruglas64のRGBバッファポインタを得る
				int	y=DMAStartLine+i;
				int	yR=CurrentWPoint+(i+dyR)*4+OverlapYLen;
				int	yG=CurrentWPoint+(i+dyG)*4+OverlapYLen;
				int	yB=CurrentWPoint+(i+dyB)*4+OverlapYLen;
				if(yR<0 || DstHeight<=yR
				|| yG<0 || DstHeight<=yG
				|| yB<0 || DstHeight<=yB){
					continue;
				}
				BYTE *pR1 = Buff[0]->GetYWithoutDepended(yR);
				BYTE *pG1 = Buff[1]->GetYWithoutDepended(yG);
				BYTE *pB1 = Buff[2]->GetYWithoutDepended(yB);
				//BYTE *pR2 = Buff[0]->GetYWithoutDepended(yR+1);
				//BYTE *pG2 = Buff[1]->GetYWithoutDepended(yG+1);
				//BYTE *pB2 = Buff[2]->GetYWithoutDepended(yB+1);

				BYTE	*s=((BYTE *)SrcAddress)+(y*BuffWidth+StartX)*4;

				for (int j=0; j< DstWidth; j++) {
					BYTE	tR=*s;
					BYTE	tG=*(s+1);
					BYTE	tB=*(s+2);

					*pB1++ = BTable[tR];		// blue
					*pG1++ = GTable[tG];		// green
					*pR1++ = RTable[tB];		// red
					//*pB2++ = tR;		// blue
					//*pG2++ = tG;		// green
					//*pR2++ = tB;		// red
					s+=4;				
				}
			}
		}
		CurrentWPoint+=YN*4;
	}
	if(CurrentWPoint>=(DstHeight-OverlapYLen)){
		//if(CurrentWPage+1<Parent->GetReadablePage()){
		if(CurrentWPage==1 && Scan1Counter==0){
			Scan1Counter++;
			CurrentWPoint=0;
		}
		else{
			if(CurrentWPage==0){
				Scan1Counter=0;
			}
			Parent->OutputCurrentPage(CurrentWPage);
			StateInPage[CurrentWPage]=1;
			CurrentWPoint=0;
			CurrentWPage++;
		}
		//else{
		//	CurrentWPoint=0;
		//}
	}
	


		//memset(((BYTE *)SrcAddress),0,EndLine*4);

	return YN;
}
