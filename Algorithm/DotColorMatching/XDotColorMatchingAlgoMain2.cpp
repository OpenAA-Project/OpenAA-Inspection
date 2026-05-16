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

#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"
#include "XCriticalFunc.h"


bool	MakeFootPoint3D( int x1,int y1,int z1
						,int x2,int y2,int z2
						,int X ,int Y, int Z
						,double &mx ,double &my ,double &mz);
extern int	DbgX,DbgY,DbgCode;
void	DotColorMatchingItem::CalcInside1WithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
									,ImageBufferFast *TBuff[] ,ImageBuffer *TRTBuff[]
									,int mx ,int my
									,int Skip ,int SelfSearch 
									//,int CDiffR ,int CDiffG ,int CDiffB 
									,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2
									,DWORD StartMilisec,int MaxInspectMilisec)
{
	RotationPattern	*R=CurrentMasterPattern;	//&MasterPattern[CurrentRotationPatternNo];
	FlexArea	&FA=*R;
	int	N=FA.GetFLineLen();

	bool	EnableM2T=Thr->EnableM2T;
	bool	EnableT2M=Thr->EnableT2M;
	NGCount1=0;
	NGCount2=0;
	DotColorMatchingInPage	*AP=(DotColorMatchingInPage *)GetParentInPage();
	DotColorMatchingBase *ABase=((DotColorMatchingBase *)GetParentBase());


	BMatrix	&MBuff0=R->BuffByMaster[0].Map[0];
	BMatrix	&MBuff1=R->BuffByMaster[0].Map[1];
	BMatrix	&MBuff2=R->BuffByMaster[0].Map[2];

	//BYTE	**MHigh0=R->BrightnessHigh[0];
	//BYTE	**MHigh1=R->BrightnessHigh[1];
	//BYTE	**MHigh2=R->BrightnessHigh[2];
	//BYTE	**MLow0=R->BrightnessLow[0];
	//BYTE	**MLow1=R->BrightnessLow[1];
	//BYTE	**MLow2=R->BrightnessLow[2];
	int		MCx=CurrentMasterPattern->XLen/2;
	int		MCy=CurrentMasterPattern->YLen/2;

	double	Mult=1.0;
	if(OutlineArea==true){
		Mult=ABase->LevelDownRateNearOutline;
	}
	int	ThresholdRL=Clipping((int)(MThr->BrightWidthRL*Mult-MThr->BrightWidthRL*Thr->AddedBrightness*0.2),0,255);
	int	ThresholdRH=Clipping((int)(MThr->BrightWidthRH*Mult-MThr->BrightWidthRH*Thr->AddedBrightness*0.2),0,255);
	int	ThresholdGL=Clipping((int)(MThr->BrightWidthGL*Mult-MThr->BrightWidthGL*Thr->AddedBrightness*0.2),0,255);
	int	ThresholdGH=Clipping((int)(MThr->BrightWidthGH*Mult-MThr->BrightWidthGH*Thr->AddedBrightness*0.2),0,255);
	int	ThresholdBL=Clipping((int)(MThr->BrightWidthBL*Mult-MThr->BrightWidthBL*Thr->AddedBrightness*0.2),0,255);
	int	ThresholdBH=Clipping((int)(MThr->BrightWidthBH*Mult-MThr->BrightWidthBH*Thr->AddedBrightness*0.2),0,255);

	__TableType	*CompBrightWidthTableRL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->RThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdRL];
	__TableType	*CompBrightWidthTableRH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->RThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdRH];
	__TableType	*CompBrightWidthTableGL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->GThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdGL];
	__TableType	*CompBrightWidthTableGH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->GThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdGH];
	__TableType	*CompBrightWidthTableBL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->BThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdBL];
	__TableType	*CompBrightWidthTableBH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->BThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdBH];
	
	__TableType	*FlatBrightWidthTableRL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->RThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdRL];
	__TableType	*FlatBrightWidthTableRH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->RThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdRH];
	__TableType	*FlatBrightWidthTableGL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->GThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdGL];
	__TableType	*FlatBrightWidthTableGH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->GThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdGH];
	__TableType	*FlatBrightWidthTableBL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->BThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdBL];
	__TableType	*FlatBrightWidthTableBH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->BThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdBH];


	__TableType	*BrightWidthTableRL;
	__TableType	*BrightWidthTableRH;
	__TableType	*BrightWidthTableGL;
	__TableType	*BrightWidthTableGH;
	__TableType	*BrightWidthTableBL;
	__TableType	*BrightWidthTableBH;

	int	DotPerLine	=R->DotPerLine;
	int	MaxLines	=R->MaxLines;

	for(int i=0;i<N;i++){
		int	Y	=FA.GetFLineAbsY(i);
		int	X1	=FA.GetFLineLeftX(i);
		int	Numb=FA.GetFLineNumb(i);
		int	CMapY=Y-MasterCy+MCy;
		BYTE	*rMPR=MBuff0[CMapY];
		BYTE	*rMPG=MBuff1[CMapY];
		BYTE	*rMPB=MBuff2[CMapY];

		BYTE	CR=(rMPR==NULL)?MBuff0.GetConstantBrightness(CMapY):0;
		BYTE	CG=(rMPG==NULL)?MBuff1.GetConstantBrightness(CMapY):0;
		BYTE	CB=(rMPB==NULL)?MBuff2.GetConstantBrightness(CMapY):0;

		int	DefY=Y-MasterCy+MCy;

		//BYTE	*rMPLR=MLow0 [CMapY];
		//BYTE	*rMPLG=MLow1 [CMapY];
		//BYTE	*rMPLB=MLow2 [CMapY];
		//BYTE	*rMPHR=MHigh0[CMapY];
		//BYTE	*rMPHG=MHigh1[CMapY];
		//BYTE	*rMPHB=MHigh2[CMapY];
		struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL[CMapY];
		BYTE	*TPR;
		BYTE	*TPG;
		BYTE	*TPB;
		BYTE	*pTPR;
		BYTE	*pTPG;
		BYTE	*pTPB;
		int	tY=Y+my;
		if((tY-SelfSearch)<0 || MaxLines<=(tY+SelfSearch))
			continue;
		if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
			return;
		}
		BYTE	*rTPR=TBuff[0]->GetYWithoutDepended(tY);
		BYTE	*rTPG=TBuff[1]->GetYWithoutDepended(tY);
		BYTE	*rTPB=TBuff[2]->GetYWithoutDepended(tY);

		BYTE	*FlatTypeMapY=R->FlatTypeMap[CMapY];

		BYTE	*VarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetY(Y):NULL;
		BYTE	*VarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetY(Y):NULL;
		BYTE	*VarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetY(Y):NULL;

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		BYTE	CMapXMask=0x80>>(CMapX&0x07);
		BYTE	*pFlatTypeMapY=&FlatTypeMapY[CMapX>>3];
		BYTE	FlatTypeMapYValue=*pFlatTypeMapY;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){
			//if(tY==DbgY && (tX)==DbgX)
			//	DbgCode++;

			//int	CMapX=X1+xn-MasterCx+MCx;
			//if(GetBmpBitOnY(FlatTypeMapY,CMapX)==0){
			if(CMapXMask==0){
				CMapXMask=0x80;
				pFlatTypeMapY++;
				FlatTypeMapYValue=*pFlatTypeMapY;
			}
			if((FlatTypeMapYValue & CMapXMask)==0){
				BrightWidthTableRL=CompBrightWidthTableRL;
				BrightWidthTableRH=CompBrightWidthTableRH;
				BrightWidthTableGL=CompBrightWidthTableGL;
				BrightWidthTableGH=CompBrightWidthTableGH;
				BrightWidthTableBL=CompBrightWidthTableBL;
				BrightWidthTableBH=CompBrightWidthTableBH;
			}
			else{
				BrightWidthTableRL=FlatBrightWidthTableRL;
				BrightWidthTableRH=FlatBrightWidthTableRH;
				BrightWidthTableGL=FlatBrightWidthTableGL;
				BrightWidthTableGH=FlatBrightWidthTableGH;
				BrightWidthTableBL=FlatBrightWidthTableBL;
				BrightWidthTableBH=FlatBrightWidthTableBH;
			}
			CMapXMask>>=1;

			int	cMPR=(rMPR!=NULL)?rMPR[CMapX]:CR;
			int	cMPG=(rMPG!=NULL)?rMPG[CMapX]:CG;
			int	cMPB=(rMPB!=NULL)?rMPB[CMapX]:CB;
			const struct	BMatrixBrightHL::BrightHLStruct	*B	=(BrHL!=NULL)?&BrHL[CMapX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(CMapY);

			int	cMPLR=B->BrLow[0];
			int	cMPLG=B->BrLow[1];
			int	cMPLB=B->BrLow[2];
			int	cMPHR=B->BrHigh[0];
			int	cMPHG=B->BrHigh[1];
			int	cMPHB=B->BrHigh[2];

			int	VarietyR=0;
			int	VarietyG=0;
			int	VarietyB=0;
			if(VarietyMapR!=NULL)
				VarietyR=VarietyMapR[X1+xn]*Thr->VarietySigma;
			if(VarietyMapG!=NULL)
				VarietyG=VarietyMapG[X1+xn]*Thr->VarietySigma;
			if(VarietyMapB!=NULL)
				VarietyB=VarietyMapB[X1+xn]*Thr->VarietySigma;

			if(EnableM2T==true){
				BYTE	BrightWidthRL=ClippingL(cMPLR-BrightWidthTableRL[cMPR]+CDiffRL-VarietyR);
				BYTE	BrightWidthRH=ClippingH(cMPHR+BrightWidthTableRH[cMPR]+CDiffRH+VarietyR);
				BYTE	BrightWidthGL=ClippingL(cMPLG-BrightWidthTableGL[cMPG]+CDiffGL-VarietyG);
				BYTE	BrightWidthGH=ClippingH(cMPHG+BrightWidthTableGH[cMPG]+CDiffGH+VarietyG);
				BYTE	BrightWidthBL=ClippingL(cMPLB-BrightWidthTableBL[cMPB]+CDiffBL-VarietyB);
				BYTE	BrightWidthBH=ClippingH(cMPHB+BrightWidthTableBH[cMPB]+CDiffBH+VarietyB);

				bool isMatchedM2T = [&]() -> bool {
					//Len==0
					BYTE	kR=rTPR[tX];
					BYTE	kG=rTPG[tX];
					BYTE	kB=rTPB[tX];
					if(BrightWidthRL<=kR && kR<=BrightWidthRH && 
					   BrightWidthGL<=kG && kG<=BrightWidthGH && 
					   BrightWidthBL<=kB && kB<=BrightWidthBH){
						return true;
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
							TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
							TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
							TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
							pTPR=&TPR[tX-Len];
							pTPG=&TPG[tX-Len];
							pTPB=&TPB[tX-Len];
							for(ex=-Len;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
								//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
									BYTE	kR=*pTPR;
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									BYTE	kG=*pTPG;
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									BYTE	kB=*pTPB;
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						//}
						ex=Len;
						//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){

							if(TRTBuff[0]->IsNull()==true){
								for(ey=-Len;ey<Len;ey++){
									//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
										TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
										BYTE	kR=TPR[tX+ex];
										if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
										
										TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
										BYTE	kG=TPG[tX+ex];
										if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
										
										TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
										BYTE	kB=TPB[tX+ex];
										if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
										
										return true;
								//}
								}
							}
							else{
								TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
								TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
								TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
								for(ey=-Len;ey<Len;ey++){
									//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
										BYTE	kR=TPR[tY+ey];
										if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
										
										BYTE	kG=TPG[tY+ey];
										if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
										
										BYTE	kB=TPB[tY+ey];
										if(kB<BrightWidthBL || BrightWidthBH<kB) continue;

										return true;
								//}
								}
							}
						//}
						ey=-Len;
						TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
						TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
						TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
						//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
							//for(ex=Len;ex>-Len;ex--,pTP--){
							pTPR=&TPR[tX-Len+1];
							pTPG=&TPG[tX-Len+1];
							pTPB=&TPB[tX-Len+1];
							for(ex=-Len+1;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
								BYTE	kR=*pTPR;
								if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
								
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
								
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
								
								return true;
							}
						//}
						ex=-Len;
						//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
						if(TRTBuff[0]->IsNull()==true){
							for(ey=Len;ey>-Len;ey--){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
									BYTE	kR=TPR[tX+ex];
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=Len;ey>-Len;ey--){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									BYTE	kR=TPR[tY+ey];
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						}
					}
					for(int	Len=0;Len<=SelfSearch;Len++){
						if((Len%Skip)==0)
							continue;
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
							TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
							TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
							TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
							pTPR=&TPR[tX-Len];
							pTPG=&TPG[tX-Len];
							pTPB=&TPB[tX-Len];
							for(ex=-Len;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
								//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
									BYTE	kR=*pTPR;
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									BYTE	kG=*pTPG;
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									BYTE	kB=*pTPB;
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						//}
						ex=Len;
						//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
						if(TRTBuff[0]->IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
									BYTE	kR=TPR[tX+ex];
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									BYTE	kR=TPR[tY+ey];
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						}
						ey=-Len;
						TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
						TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
						TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
						//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
							//for(ex=Len;ex>-Len;ex--){
							pTPR=&TPR[tX-Len+1];
							pTPG=&TPG[tX-Len+1];
							pTPB=&TPB[tX-Len+1];
							for(ex=-Len+1;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
								BYTE	kR=*pTPR;
								if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
								
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
								
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
								
								return true;
							}
						//}
						ex=-Len;
						//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
						if(TRTBuff[0]->IsNull()==true){
							for(ey=Len;ey>-Len;ey--){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
									BYTE	kR=TPR[tX+ex];
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=Len;ey>-Len;ey--){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									BYTE	kR=TPR[tY+ey];
									if(kR<BrightWidthRL || BrightWidthRH<kR) continue;
									
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG) continue;
									
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB) continue;
									
									return true;
								//}
							}
						}
					}
					
					return false;
				}();

				if(!isMatchedM2T){
					if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					}
					NGCount1++;
					continue;
				}
			}

			if(EnableT2M==true){
				//if(0<=tY && tY<GetMaxLines() && 0<=(X1+xn+mx) && (X1+xn+mx)<GetDotPerLine()){

					int	cTPR=rTPR[tX];
					int	cTPG=rTPG[tX];
					int	cTPB=rTPB[tX];
					//TP=TBuff.GetYWithoutDepended(tY);
					int	BrightWidthRL=-BrightWidthTableRL[cTPR];
					int	BrightWidthRH= BrightWidthTableRH[cTPR];
					int	BrightWidthGL=-BrightWidthTableGL[cTPG];
					int	BrightWidthGH= BrightWidthTableGH[cTPG];
					int	BrightWidthBL=-BrightWidthTableBL[cTPB];
					int	BrightWidthBH= BrightWidthTableBH[cTPB];
					int	kRL=cTPR-CDiffRL;
					int	kGL=cTPG-CDiffGL;
					int	kBL=cTPB-CDiffBL;
					int	kRH=cTPR-CDiffRH;
					int	kGH=cTPG-CDiffGH;
					int	kBH=cTPB-CDiffBH;

					bool isMatchedT2M = [&]() -> bool {
						//Len==0
						if((BrightWidthRL+cMPLR)<=kRL && kRH<=(BrightWidthRH+cMPHR) && 
						   (BrightWidthGL+cMPLG)<=kGL && kGH<=(BrightWidthGH+cMPHG) && 
						   (BrightWidthBL+cMPLB)<=kBL && kBH<=(BrightWidthBH+cMPHB)){
							return true;
						}

						for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
							int	ex,ey;
							ey=-Len;
							//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
							{
								BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
								BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
								BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;

								int	UY=DefY+ey;
								int	UX=X1+xn-MasterCx+MCx-Len;
								if(0<UY && UY<R->YLen){
									const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
									int	h=0;
									if(BrHL_Y!=NULL){
										for(ex=-Len;ex<=Len;ex++,h++){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if(0<=(UX+h) && (UX+h)<R->XLen){
												
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
												&& (BrightWidthBL+MPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
									else{
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
												
										for(ex=-Len;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
												&& (BrightWidthBL+MPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
								}
							}
							ex=Len;
							{
								int	masterx=X1+xn+ex;
								int	UX=X1+xn-MasterCx+MCx+ex;
								if(0<=(UX) && (UX)<R->XLen){
									for(ey=-Len;ey<Len;ey++){
										int	UY=DefY+ey;
										if(0<UY && UY<R->YLen){
											const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											
											BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
											&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
											&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
												return true;
											}
										}
									}
								}
							}
							ey=Len;
							{
								BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
								BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
								BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
								int	UY=Y-MasterCy+MCy+ey;
								int	UX=X1+xn-MasterCx+MCx-Len+1;
								if(0<UY && UY<R->YLen){
									const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
									int	h=0;
									if(BrHL_Y!=NULL){
										for(ex=-Len+1;ex<=Len;ex++,h++){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if(0<=(UX+h) && (UX+h)<R->XLen){
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
												&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
									else{
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										for(ex=-Len+1;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
												&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
								}
							}
							ex=Len;
							//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
							{
								int	masterx=X1+xn+ex;
								int	UX=X1+xn-MasterCx+MCx+ex;
								if(0<=(UX) && (UX)<R->XLen){
									for(ey=Len;ey>-Len;ey--){
										//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
										int	UY=Y-MasterCy+MCy+ey;
										if(0<UY && UY<R->YLen){
											const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

											BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR)
											&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG)
											&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
												return true;
											}
										}
									}
								}
							}
						}
						for(int	Len=0;Len<=SelfSearch;Len++){
							if((Len%Skip)==0)
								continue;
							int	ex,ey;
							ey=-Len;
							//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
							{
								int	UY=Y-MasterCy+MCy+ey;
								int	UX=X1+xn-MasterCx+MCx-Len;
								if(0<UY && UY<R->YLen){
									BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
									BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
									BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
									const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

									int	h=0;
									if(BrHL_Y!=NULL){
										for(ex=-Len;ex<=Len;ex++,h++){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

												BYTE	MPLR=BrHL->BrLow[0];
												BYTE	MPLG=BrHL->BrLow[1];
												BYTE	MPLB=BrHL->BrLow[2];
												BYTE	MPHR=BrHL->BrHigh[0];
												BYTE	MPHG=BrHL->BrHigh[1];
												BYTE	MPHB=BrHL->BrHigh[2];
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
												&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
									else{
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										for(ex=-Len;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
												&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
								}
							}
							ex=Len;
							//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
							{
								int	masterx=X1+xn+ex;
								int	UX=X1+xn-MasterCx+MCx+ex;
								if(0<=(UX) && (UX)<R->XLen){
									for(ey=-Len;ey<Len;ey++){
										//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
										int	UY=Y-MasterCy+MCy+ey;
										if(0<UY && UY<R->YLen){
											const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

											BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];

											if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR)
											&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG)
											&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
												return true;
											}
										}
									}
								}
							}
							ey=Len;
							//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
							{
								int	UY=Y-MasterCy+MCy+ey;
								int	UX=X1+xn-MasterCx+MCx-Len+1;
								if(0<UY && UY<R->YLen){
									BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
									BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
									BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
									const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

									int	h=0;
									if(BrHL_Y!=NULL){
										for(ex=-Len+1;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

												const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
												BYTE	MPLR=BrHL->BrLow[0];
												BYTE	MPLG=BrHL->BrLow[1];
												BYTE	MPLB=BrHL->BrLow[2];
												BYTE	MPHR=BrHL->BrHigh[0];
												BYTE	MPHG=BrHL->BrHigh[1];
												BYTE	MPHB=BrHL->BrHigh[2];
												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR)
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG)
												&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
									else{
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										for(ex=-Len+1;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

												if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR)
												&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG)
												&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
													return true;
												}
											}
										}
									}
								}
							}
							ex=-Len;
							//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
							{
								int	masterx=X1+xn+ex;
								int	UX=X1+xn-MasterCx+MCx+ex;
								if(0<=(UX) && (UX)<R->XLen){
									for(ey=Len;ey>-Len;ey--){
										//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
										int	UY=Y-MasterCy+MCy+ey;
										if(0<UY && UY<R->YLen){
											const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

											BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
											BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];

											if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR)
											&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG)
											&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
												return true;
											}
										}
									}
								}
							}
						}
						return false;
					}();

					if(!isMatchedT2M){
						if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MapYLen){ // ¦MapYLen‚ª–¢’è‹`‚Ìê‡‚ÍMaxLines‚È‚Ç‚É“K‹XC³‚µ‚Ä‚­‚¾‚³‚¢
							SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
						}
						NGCount2++;
					}
				//}
			}
		}
	}
}

