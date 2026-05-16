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

void	DotColorMatchingItem::CalcInside2WithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
									,ImageBufferFast *TBuff[] ,ImageBuffer *TRTBuff[]
									,int mx ,int my
									,int Skip ,int SelfSearch 
									//,int CDiffR ,int CDiffG ,int CDiffB 
									,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2
									,int &GrayDotsM
									,int &GrayDotsT
									,DWORD StartMilisec,int MaxInspectMilisec)
{
	RotationPattern	*R=&MasterPattern[CurrentRotationPatternNo];
	FlexArea	&FA=*R;
	int	N=FA.GetFLineLen();
	bool	EnableM2T=Thr->EnableM2T;
	bool	EnableT2M=Thr->EnableT2M;
	NGCount1=0;
	NGCount2=0;
	DotColorMatchingInPage	*AP=(DotColorMatchingInPage *)GetParentInPage();
	DotColorMatchingBase *ABase=((DotColorMatchingBase *)GetParentBase());


	BMatrix	&MBuffA0=R->BuffByMaster[0].Map[0];
	BMatrix	&MBuffA1=R->BuffByMaster[0].Map[1];
	BMatrix	&MBuffA2=R->BuffByMaster[0].Map[2];

	BMatrix	&MBuffB0=R->BuffByMaster[1].Map[0];
	BMatrix	&MBuffB1=R->BuffByMaster[1].Map[1];
	BMatrix	&MBuffB2=R->BuffByMaster[1].Map[2];

	int		MCx=MasterPattern[CurrentRotationPatternNo].XLen/2;
	int		MCy=MasterPattern[CurrentRotationPatternNo].YLen/2;

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
	GrayDotsM	=0;
	GrayDotsT	=0;

	for(int i=0;i<N;i++){
		int	Y	=FA.GetFLineAbsY(i);
		int	X1	=FA.GetFLineLeftX(i);
		int	Numb=FA.GetFLineNumb(i);
		int	CMapY=Y-MasterCy+MCy;
		BYTE	*rAMPR=MBuffA0[CMapY];
		BYTE	*rAMPG=MBuffA1[CMapY];
		BYTE	*rAMPB=MBuffA2[CMapY];
		BYTE	*rBMPR=MBuffB0[CMapY];
		BYTE	*rBMPG=MBuffB1[CMapY];
		BYTE	*rBMPB=MBuffB2[CMapY];

		BYTE	ACR=(rAMPR==NULL)?MBuffA0.GetConstantBrightness(CMapY):0;
		BYTE	ACG=(rAMPG==NULL)?MBuffA1.GetConstantBrightness(CMapY):0;
		BYTE	ACB=(rAMPB==NULL)?MBuffA2.GetConstantBrightness(CMapY):0;
		BYTE	BCR=(rBMPR==NULL)?MBuffB0.GetConstantBrightness(CMapY):0;
		BYTE	BCG=(rBMPG==NULL)?MBuffB1.GetConstantBrightness(CMapY):0;
		BYTE	BCB=(rBMPB==NULL)?MBuffB2.GetConstantBrightness(CMapY):0;

		if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
			return;
		}
		struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=R->BuffByMaster[0].BrightHL[CMapY];
		struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=R->BuffByMaster[1].BrightHL[CMapY];
		BYTE	*TPR;
		BYTE	*TPG;
		BYTE	*TPB;
		BYTE	*pTPR;
		BYTE	*pTPG;
		BYTE	*pTPB;
		int	tY=Y+my;
		if((tY-SelfSearch)<0 || MaxLines<=(tY+SelfSearch))
			continue;


		BYTE	*rTPR=TBuff[0]->GetYWithoutDepended(tY);
		BYTE	*rTPG=TBuff[1]->GetYWithoutDepended(tY);
		BYTE	*rTPB=TBuff[2]->GetYWithoutDepended(tY);

		BYTE	*FlatTypeMapY=R->FlatTypeMap[CMapY];

		BYTE	*VarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetY(Y):NULL;
		BYTE	*VarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetY(Y):NULL;
		BYTE	*VarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetY(Y):NULL;

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){
			if(tY==DbgY && (tX)==DbgX)
				DbgCode++;

			if(GetBmpBitOnY(FlatTypeMapY,CMapX)==0){
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

			// ==========================================
			// Subtract (マスク) チェックブロック
			// ==========================================
			bool isMasked = false;
			for(SubtractItem *s=SubBlock.GetFirst();s!=NULL;s=s->GetNext()){
				DotColorMatchingItem	*SItem=(DotColorMatchingItem *)s->IndexAfterEdit;
				if(SItem->CurrentMasterPattern!=NULL){
					int	Sy=SItem->CurrentMasterPattern->GetMinY();
					int	YMergin=(SItem->CurrentMasterPattern->YLen-SItem->CurrentMasterPattern->GetHeight())/2;
					int	sy=(Y+my)-(Sy+SItem->ResultDy)+YMergin;
					if(0<=sy && sy<SItem->CurrentMasterPattern->YLen){
						int	Sx=SItem->CurrentMasterPattern->GetMinX();
						int	XMergin=(SItem->CurrentMasterPattern->XLen-SItem->CurrentMasterPattern->GetWidth())/2;
						int	sx=(X1+mx+xn)-(Sx+SItem->ResultDx)+XMergin;
						if(0<=sx && sx<SItem->CurrentMasterPattern->XLen){
							if(GetBmpBit(SItem->CurrentMasterPattern->SubtractionMap,sx,sy)!=0){
								isMasked = true;
								break;
							}
						}
					}
				}
			}

			if (isMasked) continue;

			int	cAMPR=(rAMPR!=NULL)?rAMPR[CMapX]:ACR;
			int	cAMPG=(rAMPG!=NULL)?rAMPG[CMapX]:ACG;
			int	cAMPB=(rAMPB!=NULL)?rAMPB[CMapX]:ACB;
			int	cBMPR=(rBMPR!=NULL)?rBMPR[CMapX]:BCR;
			int	cBMPG=(rBMPG!=NULL)?rBMPG[CMapX]:BCG;
			int	cBMPB=(rBMPB!=NULL)?rBMPB[CMapX]:BCB;
			const struct	BMatrixBrightHL::BrightHLStruct	*AB	=(BrAHL!=NULL)?&BrAHL[CMapX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(CMapY);
			const struct	BMatrixBrightHL::BrightHLStruct	*BB	=(BrBHL!=NULL)?&BrBHL[CMapX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(CMapY);

			int	cAMPLR=AB->BrLow[0];
			int	cAMPLG=AB->BrLow[1];
			int	cAMPLB=AB->BrLow[2];
			int	cAMPHR=AB->BrHigh[0];
			int	cAMPHG=AB->BrHigh[1];
			int	cAMPHB=AB->BrHigh[2];
			int	cBMPLR=BB->BrLow[0];
			int	cBMPLG=BB->BrLow[1];
			int	cBMPLB=BB->BrLow[2];
			int	cBMPHR=BB->BrHigh[0];
			int	cBMPHG=BB->BrHigh[1];
			int	cBMPHB=BB->BrHigh[2];

			int	VarietyR=0;
			int	VarietyG=0;
			int	VarietyB=0;
			if(VarietyMapR!=NULL)
				VarietyR=VarietyMapR[X1+xn]*Thr->VarietySigma;
			if(VarietyMapG!=NULL)
				VarietyG=VarietyMapG[X1+xn]*Thr->VarietySigma;
			if(VarietyMapB!=NULL)
				VarietyB=VarietyMapB[X1+xn]*Thr->VarietySigma;

			// ==========================================
			// M2T チェックブロック（ラムダ式による早期リターン化）
			// ==========================================
			if(EnableM2T==true){
				BYTE	ABrightWidthRL=ClippingL(cAMPLR-BrightWidthTableRL[cAMPR]+CDiffRL-VarietyR);
				BYTE	ABrightWidthRH=ClippingH(cAMPHR+BrightWidthTableRH[cAMPR]+CDiffRH+VarietyR);
				BYTE	ABrightWidthGL=ClippingL(cAMPLG-BrightWidthTableGL[cAMPG]+CDiffGL-VarietyG);
				BYTE	ABrightWidthGH=ClippingH(cAMPHG+BrightWidthTableGH[cAMPG]+CDiffGH+VarietyG);
				BYTE	ABrightWidthBL=ClippingL(cAMPLB-BrightWidthTableBL[cAMPB]+CDiffBL-VarietyB);
				BYTE	ABrightWidthBH=ClippingH(cAMPHB+BrightWidthTableBH[cAMPB]+CDiffBH+VarietyB);
				BYTE	BBrightWidthRL=ClippingL(cBMPLR-BrightWidthTableRL[cBMPR]+CDiffRL-VarietyR);
				BYTE	BBrightWidthRH=ClippingH(cBMPHR+BrightWidthTableRH[cBMPR]+CDiffRH+VarietyR);
				BYTE	BBrightWidthGL=ClippingL(cBMPLG-BrightWidthTableGL[cBMPG]+CDiffGL-VarietyG);
				BYTE	BBrightWidthGH=ClippingH(cBMPHG+BrightWidthTableGH[cBMPG]+CDiffGH+VarietyG);
				BYTE	BBrightWidthBL=ClippingL(cBMPLB-BrightWidthTableBL[cBMPB]+CDiffBL-VarietyB);
				BYTE	BBrightWidthBH=ClippingH(cBMPHB+BrightWidthTableBH[cBMPB]+CDiffBH+VarietyB);

				bool isMatchedM2T = [&]() -> bool {
					//Len==0
					BYTE	kR=rTPR[tX];
					BYTE	kG=rTPG[tX];
					BYTE	kB=rTPB[tX];
					bool len0_ok = true;
					if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) len0_ok = false;
					else if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) len0_ok = false;
					else if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) len0_ok = false;
					if(len0_ok) return true;

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
						TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
						TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
						pTPR=&TPR[tX-Len];
						pTPG=&TPG[tX-Len];
						pTPB=&TPB[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
							BYTE	kR=*pTPR;
							if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
							return true;
						}

						ex=Len;
						if(TRTBuff[0]->IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								BYTE	kR=TPR[tY+ey];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}

						ey=-Len;
						TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
						TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
						TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
						pTPR=&TPR[tX-Len+1];
						pTPG=&TPG[tX-Len+1];
						pTPB=&TPB[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
							BYTE	kR=*pTPR;
							if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
							return true;
						}

						ex=-Len;
						if(TRTBuff[0]->IsNull()==true){
							for(ey=Len;ey>-Len;ey--){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=Len;ey>-Len;ey--){
								BYTE	kR=TPR[tY+ey];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}
					}

					for(int	Len=0;Len<=SelfSearch;Len++){
						if((Len%Skip)==0) continue;
						int	ex,ey;
						ey=-Len;
						TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
						TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
						TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
						pTPR=&TPR[tX-Len];
						pTPG=&TPG[tX-Len];
						pTPB=&TPB[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
							BYTE	kR=*pTPR;
							if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
							return true;
						}

						ex=Len;
						if(TRTBuff[0]->IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								BYTE	kR=TPR[tY+ey];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}

						ey=-Len;
						TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
						TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
						TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
						pTPR=&TPR[tX-Len+1];
						pTPG=&TPG[tX-Len+1];
						pTPB=&TPB[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTPR++,pTPG++,pTPB++){
							BYTE	kR=*pTPR;
							if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
							return true;
						}

						ex=-Len;
						if(TRTBuff[0]->IsNull()==true){
							for(ey=Len;ey>-Len;ey--){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}
						else{
							TPR=TRTBuff[0]->GetYWithoutDepended(tX+ex);
							TPG=TRTBuff[1]->GetYWithoutDepended(tX+ex);
							TPB=TRTBuff[2]->GetYWithoutDepended(tX+ex);
							for(ey=Len;ey>-Len;ey--){
								BYTE	kR=TPR[tY+ey];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR) && (kR<BBrightWidthRL || BBrightWidthRH<kR)) continue;
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG) && (kG<BBrightWidthGL || BBrightWidthGH<kG)) continue;
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB) && (kB<BBrightWidthBL || BBrightWidthBH<kB)) continue;
								return true;
							}
						}
					}

					// GrayDotsM 判定
					double hx, hy, hz;
					if(MakeFootPoint3D(cAMPR, cAMPG, cAMPB, cBMPR, cBMPG, cBMPB, kR, kG, kB, hx, hy, hz)==true && 
					   MakeFootPoint3D(cAMPR, cAMPG, cAMPB, cBMPR, cBMPG, cBMPB, kR, kG, kB, hx, hy, hz)==true){
						BYTE cMPR=(BYTE)Clipping(hx,0.0,255.0);
						BYTE cMPG=(BYTE)Clipping(hy,0.0,255.0);
						BYTE cMPB=(BYTE)Clipping(hz,0.0,255.0);
						BYTE HBrightWidthRL=ClippingL(cMPR-BrightWidthTableRL[cMPR]+CDiffRL-VarietyR);
						BYTE HBrightWidthRH=ClippingH(cMPR+BrightWidthTableRH[cMPR]+CDiffRH+VarietyR);
						BYTE HBrightWidthGL=ClippingL(cMPG-BrightWidthTableGL[cMPG]+CDiffGL-VarietyG);
						BYTE HBrightWidthGH=ClippingH(cMPG+BrightWidthTableGH[cMPG]+CDiffGH+VarietyG);
						BYTE HBrightWidthBL=ClippingL(cMPB-BrightWidthTableBL[cMPB]+CDiffBL-VarietyB);
						BYTE HBrightWidthBH=ClippingH(cMPB+BrightWidthTableBH[cMPB]+CDiffBH+VarietyB);

						if(HBrightWidthRL<=kR && kR<=HBrightWidthRH &&
						   HBrightWidthGL<=kG && kG<=HBrightWidthGH &&
						   HBrightWidthBL<=kB && kB<=HBrightWidthBH){
							GrayDotsM++;
							return true;
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

			// ==========================================
			// T2M チェックブロック（ラムダ式による早期リターン化）
			// ==========================================
			if(EnableT2M==true){
				int	cTPR=rTPR[tX];
				int	cTPG=rTPG[tX];
				int	cTPB=rTPB[tX];
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
					bool len0_ok = true;
					if((kRL<(BrightWidthRL+cAMPLR) || (BrightWidthRH+cAMPHR)<kRH) && (kRL<(BrightWidthRL+cBMPLR) || (BrightWidthRH+cBMPHR)<kRH)) len0_ok = false;
					else if((kGL<(BrightWidthGL+cAMPLG) || (BrightWidthGH+cAMPHG)<kGH) && (kGL<(BrightWidthGL+cBMPLG) || (BrightWidthGH+cBMPHG)<kGH)) len0_ok = false;
					else if((kBL<(BrightWidthBL+cAMPLB) || (BrightWidthBH+cAMPHB)<kBH) && (kBL<(BrightWidthBL+cBMPLB) || (BrightWidthBH+cBMPHB)<kBH)) len0_ok = false;
					if(len0_ok) return true;

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						{
							BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
							BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
							BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;

							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=&BrAHL_Y[UX+h];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=&BrBHL_Y[UX+h];
										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
								else{
									for(ex=-Len;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX+h]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
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
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

										BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];
										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=&BrAHL_Y[UX+h];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=&BrBHL_Y[UX+h];
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										for(ex=-Len+1;ex<=Len;ex++,h++){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											BYTE	AMPLR=BrAHL->BrLow[0];
											BYTE	AMPLG=BrAHL->BrLow[1];
											BYTE	AMPLB=BrAHL->BrLow[2];
											BYTE	AMPHR=BrAHL->BrHigh[0];
											BYTE	AMPHG=BrAHL->BrHigh[1];
											BYTE	AMPHB=BrAHL->BrHigh[2];
											BYTE	BMPLR=BrBHL->BrLow[0];
											BYTE	BMPLG=BrBHL->BrLow[1];
											BYTE	BMPLB=BrBHL->BrLow[2];
											BYTE	BMPHR=BrBHL->BrHigh[0];
											BYTE	BMPHG=BrBHL->BrHigh[1];
											BYTE	BMPHB=BrBHL->BrHigh[2];
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
								else{
									for(ex=-Len+1;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX+h]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
							}
						}
						ex=-Len;
						{
							int	masterx=X1+xn+ex;
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

										BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];

										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
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
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
								BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
								BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];

								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=&BrAHL_Y[UX+h];
											const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=&BrBHL_Y[UX+h];
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											BYTE	AMPLR=BrAHL->BrLow[0];
											BYTE	AMPLG=BrAHL->BrLow[1];
											BYTE	AMPLB=BrAHL->BrLow[2];
											BYTE	AMPHR=BrAHL->BrHigh[0];
											BYTE	AMPHG=BrAHL->BrHigh[1];
											BYTE	AMPHB=BrAHL->BrHigh[2];
											BYTE	BMPLR=BrBHL->BrLow[0];
											BYTE	BMPLG=BrBHL->BrLow[1];
											BYTE	BMPLB=BrBHL->BrLow[2];
											BYTE	BMPHR=BrBHL->BrHigh[0];
											BYTE	BMPHG=BrBHL->BrHigh[1];
											BYTE	BMPHB=BrBHL->BrHigh[2];
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
										for(ex=-Len;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
												BYTE	AMPLR=BrAHL->BrLow[0];
												BYTE	AMPLG=BrAHL->BrLow[1];
												BYTE	AMPLB=BrAHL->BrLow[2];
												BYTE	AMPHR=BrAHL->BrHigh[0];
												BYTE	AMPHG=BrAHL->BrHigh[1];
												BYTE	AMPHB=BrAHL->BrHigh[2];
												BYTE	BMPLR=BrBHL->BrLow[0];
												BYTE	BMPLG=BrBHL->BrLow[1];
												BYTE	BMPLB=BrBHL->BrLow[2];
												BYTE	BMPHR=BrBHL->BrHigh[0];
												BYTE	BMPHG=BrBHL->BrHigh[1];
												BYTE	BMPHB=BrBHL->BrHigh[2];
												if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
												if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
											}
										}
									}
								}
								else{
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX+h]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											BYTE	AMPLR=BrAHL->BrLow[0];
											BYTE	AMPLG=BrAHL->BrLow[1];
											BYTE	AMPLB=BrAHL->BrLow[2];
											BYTE	AMPHR=BrAHL->BrHigh[0];
											BYTE	AMPHG=BrAHL->BrHigh[1];
											BYTE	AMPHB=BrAHL->BrHigh[2];
											BYTE	BMPLR=BrBHL->BrLow[0];
											BYTE	BMPLG=BrBHL->BrLow[1];
											BYTE	BMPLB=BrBHL->BrLow[2];
											BYTE	BMPHR=BrBHL->BrHigh[0];
											BYTE	BMPHG=BrBHL->BrHigh[1];
											BYTE	BMPHB=BrBHL->BrHigh[2];
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
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
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

										BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];

										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=&BrAHL_Y[UX+h];
											const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=&BrBHL_Y[UX+h];
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											BYTE	AMPLR=BrAHL->BrLow[0];
											BYTE	AMPLG=BrAHL->BrLow[1];
											BYTE	AMPLB=BrAHL->BrLow[2];
											BYTE	AMPHR=BrAHL->BrHigh[0];
											BYTE	AMPHG=BrAHL->BrHigh[1];
											BYTE	AMPHB=BrAHL->BrHigh[2];
											BYTE	BMPLR=BrBHL->BrLow[0];
											BYTE	BMPLG=BrBHL->BrLow[1];
											BYTE	BMPLB=BrBHL->BrLow[2];
											BYTE	BMPHR=BrBHL->BrHigh[0];
											BYTE	BMPHG=BrBHL->BrHigh[1];
											BYTE	BMPHB=BrBHL->BrHigh[2];
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
										for(ex=-Len+1;ex<=Len;ex++,h++){
											if(0<=(UX+h) && (UX+h)<R->XLen){
												int	masterx=X1+xn+ex;
												BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
												BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
												BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
												BYTE	AMPLR=BrAHL->BrLow[0];
												BYTE	AMPLG=BrAHL->BrLow[1];
												BYTE	AMPLB=BrAHL->BrLow[2];
												BYTE	AMPHR=BrAHL->BrHigh[0];
												BYTE	AMPHG=BrAHL->BrHigh[1];
												BYTE	AMPHB=BrAHL->BrHigh[2];
												BYTE	BMPLR=BrBHL->BrLow[0];
												BYTE	BMPLG=BrBHL->BrLow[1];
												BYTE	BMPLB=BrBHL->BrLow[2];
												BYTE	BMPHR=BrBHL->BrHigh[0];
												BYTE	BMPHG=BrBHL->BrHigh[1];
												BYTE	BMPHB=BrBHL->BrHigh[2];
												if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
												if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
											}
										}
									}
								}
								else{
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX+h]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											BYTE	AMPLR=BrAHL->BrLow[0];
											BYTE	AMPLG=BrAHL->BrLow[1];
											BYTE	AMPLB=BrAHL->BrLow[2];
											BYTE	AMPHR=BrAHL->BrHigh[0];
											BYTE	AMPHG=BrAHL->BrHigh[1];
											BYTE	AMPHB=BrAHL->BrHigh[2];
											BYTE	BMPLR=BrBHL->BrLow[0];
											BYTE	BMPLG=BrBHL->BrLow[1];
											BYTE	BMPLB=BrBHL->BrLow[2];
											BYTE	BMPHR=BrBHL->BrHigh[0];
											BYTE	BMPHG=BrBHL->BrHigh[1];
											BYTE	BMPHB=BrBHL->BrHigh[2];
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
										}
									}
								}
							}
						}
						ex=-Len;
						{
							int	masterx=X1+xn+ex;
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

										BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
										BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

										BYTE	AMPLR=BrAHL->BrLow[0];
										BYTE	AMPLG=BrAHL->BrLow[1];
										BYTE	AMPLB=BrAHL->BrLow[2];
										BYTE	AMPHR=BrAHL->BrHigh[0];
										BYTE	AMPHG=BrAHL->BrHigh[1];
										BYTE	AMPHB=BrAHL->BrHigh[2];
										BYTE	BMPLR=BrBHL->BrLow[0];
										BYTE	BMPLG=BrBHL->BrLow[1];
										BYTE	BMPLB=BrBHL->BrLow[2];
										BYTE	BMPHR=BrBHL->BrHigh[0];
										BYTE	BMPHG=BrBHL->BrHigh[1];
										BYTE	BMPHB=BrBHL->BrHigh[2];

										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) && (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) && (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)) return true;
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) && (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) && (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)) return true;
									}
								}
							}
						}
					}

					// GrayDotsT 判定
					double hxL, hyL, hzL;
					double hxH, hyH, hzH;
					if(MakeFootPoint3D(cAMPR, cAMPG, cAMPB, cBMPR, cBMPG, cBMPB, kRL, kGL, kBL, hxL, hyL, hzL)==true && 
					   MakeFootPoint3D(cAMPR, cAMPG, cAMPB, cBMPR, cBMPG, cBMPB, kRH, kGH, kBH, hxH, hyH, hzH)==true){
						BYTE cMPRL=(BYTE)Clipping(hxL,0.0,255.0);
						BYTE cMPGL=(BYTE)Clipping(hyL,0.0,255.0);
						BYTE cMPBL=(BYTE)Clipping(hzL,0.0,255.0);
						BYTE cMPRH=(BYTE)Clipping(hxH,0.0,255.0);
						BYTE cMPGH=(BYTE)Clipping(hyH,0.0,255.0);
						BYTE cMPBH=(BYTE)Clipping(hzH,0.0,255.0);
						BYTE HBrightWidthRL=ClippingL(cMPRL-BrightWidthTableRL[cMPRL]+CDiffRL-VarietyR);
						BYTE HBrightWidthRH=ClippingH(cMPRH+BrightWidthTableRH[cMPRH]+CDiffRH+VarietyR);
						BYTE HBrightWidthGL=ClippingL(cMPGL-BrightWidthTableGL[cMPGL]+CDiffGL-VarietyG);
						BYTE HBrightWidthGH=ClippingH(cMPGH+BrightWidthTableGH[cMPGH]+CDiffGH+VarietyG);
						BYTE HBrightWidthBL=ClippingL(cMPBL-BrightWidthTableBL[cMPBL]+CDiffBL-VarietyB);
						BYTE HBrightWidthBH=ClippingH(cMPBH+BrightWidthTableBH[cMPBH]+CDiffBH+VarietyB);

						if(HBrightWidthRL<=kRL && kRH<=HBrightWidthRH &&
						   HBrightWidthGL<=kGL && kGH<=HBrightWidthGH &&
						   HBrightWidthBL<=kBL && kBH<=HBrightWidthBH){
							GrayDotsT++;
							return true;
						}
					}

					return false;
				}();

				if(!isMatchedT2M){
					if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MapYLen){ // MapYLenの定義がある前提
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					}
					NGCount2++;
				}
			}
		}
	}
}