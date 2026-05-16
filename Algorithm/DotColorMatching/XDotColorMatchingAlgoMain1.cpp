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

void DotColorMatchingItem::CalcInside1(const DotColorMatchingThreshold *Thr, const DotColorMatchingThreshold::MThreshold *MThr
									, ImageBufferFast *TBuff[], ImageBuffer *TRTBuff[]
									, int mx, int my
									, int Skip, int SelfSearch
									//,int CDiffR ,int CDiffG ,int CDiffB 
									, int NoiseBrightness
									, int MapXPoint, int MapYPoint
									, int &NGCount1
									, int &NGCount2
									, DWORD StartMilisec, int MaxInspectMilisec)
{
	RotationPattern *R = CurrentMasterPattern;
	FlexArea &FA = *R;
	int N = FA.GetFLineLen();

	bool EnableM2T = Thr->EnableM2T;
	bool EnableT2M = Thr->EnableT2M;
	NGCount1 = 0;
	NGCount2 = 0;
	DotColorMatchingInPage *AP = (DotColorMatchingInPage *)GetParentInPage();
	DotColorMatchingBase *ABase = ((DotColorMatchingBase *)GetParentBase());

	BMatrix &MBuff0 = R->BuffByMaster[0].Map[0];
	BMatrix &MBuff1 = R->BuffByMaster[0].Map[1];
	BMatrix &MBuff2 = R->BuffByMaster[0].Map[2];

	int MCx = CurrentMasterPattern->XLen / 2;
	int MCy = CurrentMasterPattern->YLen / 2;

	double Mult = 1.0;
	if (OutlineArea == true) {
		Mult = ABase->LevelDownRateNearOutline;
	}
	int ThresholdRL = Clipping((int)(MThr->BrightWidthRL * Mult - MThr->BrightWidthRL * Thr->AddedBrightness * 0.2), 0, 255);
	int ThresholdRH = Clipping((int)(MThr->BrightWidthRH * Mult - MThr->BrightWidthRH * Thr->AddedBrightness * 0.2), 0, 255);
	int ThresholdGL = Clipping((int)(MThr->BrightWidthGL * Mult - MThr->BrightWidthGL * Thr->AddedBrightness * 0.2), 0, 255);
	int ThresholdGH = Clipping((int)(MThr->BrightWidthGH * Mult - MThr->BrightWidthGH * Thr->AddedBrightness * 0.2), 0, 255);
	int ThresholdBL = Clipping((int)(MThr->BrightWidthBL * Mult - MThr->BrightWidthBL * Thr->AddedBrightness * 0.2), 0, 255);
	int ThresholdBH = Clipping((int)(MThr->BrightWidthBH * Mult - MThr->BrightWidthBH * Thr->AddedBrightness * 0.2), 0, 255);

	__TableType *CompBrightWidthTableRL = AP->BrightWidthTableComp[MaxThreOffset + Clipping(MThr->RThrOffsetL - Thr->AddedOffset * 3, -100, 100)][ThresholdRL];
	__TableType *CompBrightWidthTableRH = AP->BrightWidthTableComp[MaxThreOffset + Clipping(MThr->RThrOffsetH - Thr->AddedOffset * 3, -100, 100)][ThresholdRH];
	__TableType *CompBrightWidthTableGL = AP->BrightWidthTableComp[MaxThreOffset + Clipping(MThr->GThrOffsetL - Thr->AddedOffset * 3, -100, 100)][ThresholdGL];
	__TableType *CompBrightWidthTableGH = AP->BrightWidthTableComp[MaxThreOffset + Clipping(MThr->GThrOffsetH - Thr->AddedOffset * 3, -100, 100)][ThresholdGH];
	__TableType *CompBrightWidthTableBL = AP->BrightWidthTableComp[MaxThreOffset + Clipping(MThr->BThrOffsetL - Thr->AddedOffset * 3, -100, 100)][ThresholdBL];
	__TableType *CompBrightWidthTableBH = AP->BrightWidthTableComp[MaxThreOffset + Clipping(MThr->BThrOffsetH - Thr->AddedOffset * 3, -100, 100)][ThresholdBH];

	__TableType *FlatBrightWidthTableRL = AP->BrightWidthTableFlat[MaxThreOffset + Clipping(MThr->RThrOffsetL - Thr->AddedOffset * 3, -100, 100)][ThresholdRL];
	__TableType *FlatBrightWidthTableRH = AP->BrightWidthTableFlat[MaxThreOffset + Clipping(MThr->RThrOffsetH - Thr->AddedOffset * 3, -100, 100)][ThresholdRH];
	__TableType *FlatBrightWidthTableGL = AP->BrightWidthTableFlat[MaxThreOffset + Clipping(MThr->GThrOffsetL - Thr->AddedOffset * 3, -100, 100)][ThresholdGL];
	__TableType *FlatBrightWidthTableGH = AP->BrightWidthTableFlat[MaxThreOffset + Clipping(MThr->GThrOffsetH - Thr->AddedOffset * 3, -100, 100)][ThresholdGH];
	__TableType *FlatBrightWidthTableBL = AP->BrightWidthTableFlat[MaxThreOffset + Clipping(MThr->BThrOffsetL - Thr->AddedOffset * 3, -100, 100)][ThresholdBL];
	__TableType *FlatBrightWidthTableBH = AP->BrightWidthTableFlat[MaxThreOffset + Clipping(MThr->BThrOffsetH - Thr->AddedOffset * 3, -100, 100)][ThresholdBH];

	__TableType *BrightWidthTableRL;
	__TableType *BrightWidthTableRH;
	__TableType *BrightWidthTableGL;
	__TableType *BrightWidthTableGH;
	__TableType *BrightWidthTableBL;
	__TableType *BrightWidthTableBH;

	int DotPerLine = R->DotPerLine;
	int MaxLines = R->MaxLines;

	for (int i = 0; i < N; i++) {
		int Y = FA.GetFLineAbsY(i);
		int X1 = FA.GetFLineLeftX(i);
		int Numb = FA.GetFLineNumb(i);
		int CMapY = Y - MasterCy + MCy;
		BYTE *rMPR = MBuff0[CMapY];
		BYTE *rMPG = MBuff1[CMapY];
		BYTE *rMPB = MBuff2[CMapY];

		BYTE CR = (rMPR == NULL) ? MBuff0.GetConstantBrightness(CMapY) : 0;
		BYTE CG = (rMPG == NULL) ? MBuff1.GetConstantBrightness(CMapY) : 0;
		BYTE CB = (rMPB == NULL) ? MBuff2.GetConstantBrightness(CMapY) : 0;

		int DefY = Y - MasterCy + MCy;
		struct BMatrixBrightHL::BrightHLStruct *BrHL = R->BuffByMaster[0].BrightHL[CMapY];
		BYTE *TPR;
		BYTE *TPG;
		BYTE *TPB;
		BYTE *pTPR;
		BYTE *pTPG;
		BYTE *pTPB;
		int tY = Y + my;
		
		if ((tY - SelfSearch) < 0 || MaxLines <= (tY + SelfSearch))
			continue;
		if (GetComputerMiliSec() - StartMilisec >= MaxInspectMilisec) {
			return;
		}
		BYTE *rTPR = TBuff[0]->GetYWithoutDepended(tY);
		BYTE *rTPG = TBuff[1]->GetYWithoutDepended(tY);
		BYTE *rTPB = TBuff[2]->GetYWithoutDepended(tY);

		BYTE *FlatTypeMapY = R->FlatTypeMap[CMapY];

		int tX = X1 + mx;
		int CMapX = X1 - MasterCx + MCx;
		BYTE CMapXMask = 0x80 >> (CMapX & 0x07);
		BYTE *pFlatTypeMapY = &FlatTypeMapY[CMapX >> 3];
		BYTE FlatTypeMapYValue = *pFlatTypeMapY;
		
		for (int xn = 0; xn < Numb; xn++, tX++, CMapX++) {
			if (CMapXMask == 0) {
				CMapXMask = 0x80;
				pFlatTypeMapY++;
				FlatTypeMapYValue = *pFlatTypeMapY;
			}
			if ((FlatTypeMapYValue & CMapXMask) == 0) {
				BrightWidthTableRL = CompBrightWidthTableRL;
				BrightWidthTableRH = CompBrightWidthTableRH;
				BrightWidthTableGL = CompBrightWidthTableGL;
				BrightWidthTableGH = CompBrightWidthTableGH;
				BrightWidthTableBL = CompBrightWidthTableBL;
				BrightWidthTableBH = CompBrightWidthTableBH;
			} else {
				BrightWidthTableRL = FlatBrightWidthTableRL;
				BrightWidthTableRH = FlatBrightWidthTableRH;
				BrightWidthTableGL = FlatBrightWidthTableGL;
				BrightWidthTableGH = FlatBrightWidthTableGH;
				BrightWidthTableBL = FlatBrightWidthTableBL;
				BrightWidthTableBH = FlatBrightWidthTableBH;
			}
			CMapXMask >>= 1;

			int cMPR = (rMPR != NULL) ? rMPR[CMapX] : CR;
			int cMPG = (rMPG != NULL) ? rMPG[CMapX] : CG;
			int cMPB = (rMPB != NULL) ? rMPB[CMapX] : CB;
			const struct BMatrixBrightHL::BrightHLStruct *B = (BrHL != NULL) ? &BrHL[CMapX] : R->BuffByMaster[0].BrightHL.GetConstantBrightness(CMapY);

			int cMPLR = B->BrLow[0];
			int cMPLG = B->BrLow[1];
			int cMPLB = B->BrLow[2];
			int cMPHR = B->BrHigh[0];
			int cMPHG = B->BrHigh[1];
			int cMPHB = B->BrHigh[2];

			// ==========================================
			// M2T チェックブロック（ラムダ式による早期リターン化）
			// ==========================================
			if (EnableM2T == true) {
				BYTE BrightWidthRL = ClippingL(cMPLR - BrightWidthTableRL[cMPR] + CDiffRL);
				BYTE BrightWidthRH = ClippingH(cMPHR + BrightWidthTableRH[cMPR] + CDiffRH);
				BYTE BrightWidthGL = ClippingL(cMPLG - BrightWidthTableGL[cMPG] + CDiffGL);
				BYTE BrightWidthGH = ClippingH(cMPHG + BrightWidthTableGH[cMPG] + CDiffGH);
				BYTE BrightWidthBL = ClippingL(cMPLB - BrightWidthTableBL[cMPB] + CDiffBL);
				BYTE BrightWidthBH = ClippingH(cMPHB + BrightWidthTableBH[cMPB] + CDiffBH);

				bool isMatchedM2T = [&]() -> bool {
					// Len==0 のチェック
					BYTE kR = rTPR[tX];
					BYTE kG = rTPG[tX];
					BYTE kB = rTPB[tX];
					if (BrightWidthRL <= kR && kR <= BrightWidthRH &&
						BrightWidthGL <= kG && kG <= BrightWidthGH &&
						BrightWidthBL <= kB && kB <= BrightWidthBH) {
						return true;
					}

					for (int Len = Skip; Len <= SelfSearch; Len += Skip) {
						int ex, ey;
						ey = -Len;
						TPR = TBuff[0]->GetYWithoutDepended(tY + ey);
						TPG = TBuff[1]->GetYWithoutDepended(tY + ey);
						TPB = TBuff[2]->GetYWithoutDepended(tY + ey);
						pTPR = &TPR[tX - Len];
						pTPG = &TPG[tX - Len];
						pTPB = &TPB[tX - Len];
						for (ex = -Len; ex <= Len; ex++, pTPR++, pTPG++, pTPB++) {
							if (*pTPR < BrightWidthRL || BrightWidthRH < *pTPR) continue;
							if (*pTPG < BrightWidthGL || BrightWidthGH < *pTPG) continue;
							if (*pTPB < BrightWidthBL || BrightWidthBH < *pTPB) continue;
							return true;
						}

						ex = Len;
						if (TRTBuff[0]->IsNull() == true) {
							int tYey = tY - Len;
							int tXex = tX + ex;
							for (ey = -Len; ey < Len; ey++, tYey++) {
								TPR = TBuff[0]->GetYWithoutDepended(tYey);
								if (TPR[tXex] < BrightWidthRL || BrightWidthRH < TPR[tXex]) continue;
								TPG = TBuff[1]->GetYWithoutDepended(tYey);
								if (TPG[tXex] < BrightWidthGL || BrightWidthGH < TPG[tXex]) continue;
								TPB = TBuff[2]->GetYWithoutDepended(tYey);
								if (TPB[tXex] < BrightWidthBL || BrightWidthBH < TPB[tXex]) continue;
								return true;
							}
						} else {
							TPR = TRTBuff[0]->GetYWithoutDepended(tX + ex);
							TPG = TRTBuff[1]->GetYWithoutDepended(tX + ex);
							TPB = TRTBuff[2]->GetYWithoutDepended(tX + ex);
							for (ey = -Len; ey < Len; ey++) {
								if (TPR[tY + ey] < BrightWidthRL || BrightWidthRH < TPR[tY + ey]) continue;
								if (TPG[tY + ey] < BrightWidthGL || BrightWidthGH < TPG[tY + ey]) continue;
								if (TPB[tY + ey] < BrightWidthBL || BrightWidthBH < TPB[tY + ey]) continue;
								return true;
							}
						}

						ey = -Len;
						TPR = TBuff[0]->GetYWithoutDepended(tY + ey);
						TPG = TBuff[1]->GetYWithoutDepended(tY + ey);
						TPB = TBuff[2]->GetYWithoutDepended(tY + ey);
						pTPR = &TPR[tX - Len + 1];
						pTPG = &TPG[tX - Len + 1];
						pTPB = &TPB[tX - Len + 1];
						for (ex = -Len + 1; ex <= Len; ex++, pTPR++, pTPG++, pTPB++) {
							if (*pTPR < BrightWidthRL || BrightWidthRH < *pTPR) continue;
							if (*pTPG < BrightWidthGL || BrightWidthGH < *pTPG) continue;
							if (*pTPB < BrightWidthBL || BrightWidthBH < *pTPB) continue;
							return true;
						}

						ex = -Len;
						if (TRTBuff[0]->IsNull() == true) {
							int tYey = tY + Len;
							int tXex = tX + ex;
							for (ey = Len; ey > -Len; ey--, tYey--) {
								TPR = TBuff[0]->GetYWithoutDepended(tYey);
								if (TPR[tXex] < BrightWidthRL || BrightWidthRH < TPR[tXex]) continue;
								TPG = TBuff[1]->GetYWithoutDepended(tYey);
								if (TPG[tXex] < BrightWidthGL || BrightWidthGH < TPG[tXex]) continue;
								TPB = TBuff[2]->GetYWithoutDepended(tYey);
								if (TPB[tXex] < BrightWidthBL || BrightWidthBH < TPB[tXex]) continue;
								return true;
							}
						} else {
							TPR = TRTBuff[0]->GetYWithoutDepended(tX + ex);
							TPG = TRTBuff[1]->GetYWithoutDepended(tX + ex);
							TPB = TRTBuff[2]->GetYWithoutDepended(tX + ex);
							for (ey = Len; ey > -Len; ey--) {
								if (TPR[tY + ey] < BrightWidthRL || BrightWidthRH < TPR[tY + ey]) continue;
								if (TPG[tY + ey] < BrightWidthGL || BrightWidthGH < TPG[tY + ey]) continue;
								if (TPB[tY + ey] < BrightWidthBL || BrightWidthBH < TPB[tY + ey]) continue;
								return true;
							}
						}
					}

					for (int Len = 0; Len <= SelfSearch; Len++) {
						if ((Len % Skip) == 0) continue;
						
						int ex, ey;
						ey = -Len;
						TPR = TBuff[0]->GetYWithoutDepended(tY + ey);
						TPG = TBuff[1]->GetYWithoutDepended(tY + ey);
						TPB = TBuff[2]->GetYWithoutDepended(tY + ey);
						pTPR = &TPR[tX - Len];
						pTPG = &TPG[tX - Len];
						pTPB = &TPB[tX - Len];
						for (ex = -Len; ex <= Len; ex++, pTPR++, pTPG++, pTPB++) {
							if (*pTPR < BrightWidthRL || BrightWidthRH < *pTPR) continue;
							if (*pTPG < BrightWidthGL || BrightWidthGH < *pTPG) continue;
							if (*pTPB < BrightWidthBL || BrightWidthBH < *pTPB) continue;
							return true;
						}

						ex = Len;
						if (TRTBuff[0]->IsNull() == true) {
							int tYey = tY - Len;
							int tXex = tX + ex;
							for (ey = -Len; ey < Len; ey++, tYey++) {
								TPR = TBuff[0]->GetYWithoutDepended(tYey);
								if (TPR[tXex] < BrightWidthRL || BrightWidthRH < TPR[tXex]) continue;
								TPG = TBuff[1]->GetYWithoutDepended(tYey);
								if (TPG[tXex] < BrightWidthGL || BrightWidthGH < TPG[tXex]) continue;
								TPB = TBuff[2]->GetYWithoutDepended(tYey);
								if (TPB[tXex] < BrightWidthBL || BrightWidthBH < TPB[tXex]) continue;
								return true;
							}
						} else {
							TPR = TRTBuff[0]->GetYWithoutDepended(tX + ex);
							TPG = TRTBuff[1]->GetYWithoutDepended(tX + ex);
							TPB = TRTBuff[2]->GetYWithoutDepended(tX + ex);
							for (ey = -Len; ey < Len; ey++) {
								if (TPR[tY + ey] < BrightWidthRL || BrightWidthRH < TPR[tY + ey]) continue;
								if (TPG[tY + ey] < BrightWidthGL || BrightWidthGH < TPG[tY + ey]) continue;
								if (TPB[tY + ey] < BrightWidthBL || BrightWidthBH < TPB[tY + ey]) continue;
								return true;
							}
						}

						ey = -Len;
						TPR = TBuff[0]->GetYWithoutDepended(tY + ey);
						TPG = TBuff[1]->GetYWithoutDepended(tY + ey);
						TPB = TBuff[2]->GetYWithoutDepended(tY + ey);
						pTPR = &TPR[tX - Len + 1];
						pTPG = &TPG[tX - Len + 1];
						pTPB = &TPB[tX - Len + 1];
						for (ex = -Len + 1; ex <= Len; ex++, pTPR++, pTPG++, pTPB++) {
							if (*pTPR < BrightWidthRL || BrightWidthRH < *pTPR) continue;
							if (*pTPG < BrightWidthGL || BrightWidthGH < *pTPG) continue;
							if (*pTPB < BrightWidthBL || BrightWidthBH < *pTPB) continue;
							return true;
						}

						ex = -Len;
						if (TRTBuff[0]->IsNull() == true) {
							int tYey = tY + Len;
							int tXex = tX + ex;
							for (ey = Len; ey > -Len; ey--, tYey--) {
								TPR = TBuff[0]->GetYWithoutDepended(tYey);
								if (TPR[tXex] < BrightWidthRL || BrightWidthRH < TPR[tXex]) continue;
								TPG = TBuff[1]->GetYWithoutDepended(tYey);
								if (TPG[tXex] < BrightWidthGL || BrightWidthGH < TPG[tXex]) continue;
								TPB = TBuff[2]->GetYWithoutDepended(tYey);
								if (TPB[tXex] < BrightWidthBL || BrightWidthBH < TPB[tXex]) continue;
								return true;
							}
						} else {
							TPR = TRTBuff[0]->GetYWithoutDepended(tX + ex);
							TPG = TRTBuff[1]->GetYWithoutDepended(tX + ex);
							TPB = TRTBuff[2]->GetYWithoutDepended(tX + ex);
							for (ey = Len; ey > -Len; ey--) {
								if (TPR[tY + ey] < BrightWidthRL || BrightWidthRH < TPR[tY + ey]) continue;
								if (TPG[tY + ey] < BrightWidthGL || BrightWidthGH < TPG[tY + ey]) continue;
								if (TPB[tY + ey] < BrightWidthBL || BrightWidthBH < TPB[tY + ey]) continue;
								return true;
							}
						}
					}
					
					return false; // 最後まで見つからなかった場合
				}();

				if (!isMatchedM2T) {
					if (0 <= (X1 + xn - MapXPoint) && (X1 + xn - MapXPoint) < DotPerLine && 0 <= (Y - MapYPoint) && (Y - MapYPoint) < MaxLines) {
						SetBmpBit1(Map, X1 + xn - MapXPoint, Y - MapYPoint);
					}
					NGCount1++;
					continue; // M2TでNGの場合は後続のT2Mを行わず次のxnへ
				}
			}

			// ==========================================
			// T2M チェックブロック（ラムダ式による早期リターン化）
			// ==========================================
			if (EnableT2M == true) {
				int cTPR = rTPR[tX];
				int cTPG = rTPG[tX];
				int cTPB = rTPB[tX];
				int BrightWidthRL = -BrightWidthTableRL[cTPR];
				int BrightWidthRH = BrightWidthTableRH[cTPR];
				int BrightWidthGL = -BrightWidthTableGL[cTPG];
				int BrightWidthGH = BrightWidthTableGH[cTPG];
				int BrightWidthBL = -BrightWidthTableBL[cTPB];
				int BrightWidthBH = BrightWidthTableBH[cTPB];
				int kRL = cTPR - CDiffRL;
				int kGL = cTPG - CDiffGL;
				int kBL = cTPB - CDiffBL;
				int kRH = cTPR - CDiffRH;
				int kGH = cTPG - CDiffGH;
				int kBH = cTPB - CDiffBH;

				bool isMatchedT2M = [&]() -> bool {
					// Len==0 のチェック
					if ((BrightWidthRL + cMPLR) <= kRL && kRH <= (BrightWidthRH + cMPHR) &&
						(BrightWidthGL + cMPLG) <= kGL && kGH <= (BrightWidthGH + cMPHG) &&
						(BrightWidthBL + cMPLB) <= kBL && kBH <= (BrightWidthBH + cMPHB)) {
						return true;
					}

					for (int Len = Skip; Len <= SelfSearch; Len += Skip) {
						int ex, ey;
						ey = -Len;
						int UY = DefY + ey;
						int UX = X1 + xn - MasterCx + MCx - Len;
						if (0 < UY && UY < R->YLen) {
							const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
							int h = 0;
							if (BrHL_Y != NULL) {
								if (UX < 0) h -= UX;
								int exLen = Len + Len + 1;
								if ((UX + exLen) >= R->XLen) exLen = R->XLen - UX;
								for (; h < exLen; h++) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = &BrHL_Y[UX + h];
									if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
										(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
										(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
										return true;
									}
								}
							} else {
								if (0 <= (UX + h) && (UX + h) < R->XLen) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
										(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
										(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
										return true;
									}
								}
							}
						}

						ex = Len;
						UX = X1 + xn - MasterCx + MCx + ex;
						if (0 <= UX && UX < R->XLen) {
							int MaxEy = min(Len, R->YLen - DefY);
							for (ey = max(-Len, -DefY); ey < MaxEy; ey++) {
								UY = DefY + ey;
								const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
								const struct BMatrixBrightHL::BrightHLStruct *BrHL = (BrHL_Y != NULL) ? &BrHL_Y[UX] : R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
								if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
									(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
									(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
									return true;
								}
							}
						}

						ey = Len;
						UY = DefY + ey;
						UX = X1 + xn - MasterCx + MCx - Len + 1;
						if (0 < UY && UY < R->YLen) {
							const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
							int h = 0;
							if (BrHL_Y != NULL) {
								if (UX < 0) h -= UX;
								int exLen = Len + Len + 1;
								if ((UX + exLen) >= R->XLen) exLen = R->XLen - UX;
								for (; h < exLen; h++) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = &BrHL_Y[UX + h];
									if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
										(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
										(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
										return true;
									}
								}
							} else {
								if (0 <= (UX + h) && (UX + h) < R->XLen) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
										(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
										(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
										return true;
									}
								}
							}
						}

						ex = Len;
						UX = X1 + xn - MasterCx + MCx + ex;
						if (0 <= UX && UX < R->XLen) {
							int MaxEy = min(Len, R->YLen - DefY);
							for (ey = MaxEy; ey < MaxEy; ey--) { // ※元コードの挙動を再現しています
								UY = DefY + ey;
								const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
								const struct BMatrixBrightHL::BrightHLStruct *BrHL = (BrHL_Y != NULL) ? &BrHL_Y[UX] : R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
								if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
									(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
									(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
									return true;
								}
							}
						}
					}

					for (int Len = 0; Len <= SelfSearch; Len++) {
						if ((Len % Skip) == 0) continue;
						
						int ex, ey;
						ey = -Len;
						int UY = DefY + ey;
						int UX = X1 + xn - MasterCx + MCx - Len;
						if (0 < UY && UY < R->YLen) {
							const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
							int h = 0;
							if (BrHL_Y != NULL) {
								if (UX < 0) h -= UX;
								int exLen = Len + Len + 1;
								if ((UX + exLen) >= R->XLen) exLen = R->XLen - UX;
								for (; h < exLen; h++) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = &BrHL_Y[UX + h];
									if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
										(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
										(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
										return true;
									}
								}
							} else {
								if (0 <= (UX + h) && (UX + h) < R->XLen) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									if ((BrHL->BrLow[0]) <= kRL && kRH <= (BrHL->BrHigh[0]) &&
										(BrHL->BrLow[1]) <= kGL && kGH <= (BrHL->BrHigh[1]) &&
										(BrHL->BrLow[2]) <= kBL && kBH <= (BrHL->BrHigh[2])) {
										return true;
									}
								}
							}
						}

						ex = Len;
						UX = X1 + xn - MasterCx + MCx + ex;
						if (0 <= UX && UX < R->XLen) {
							int MaxEy = min(Len, R->YLen - DefY);
							for (ey = max(-Len, -DefY); ey < MaxEy; ey++) {
								UY = DefY + ey;
								const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
								const struct BMatrixBrightHL::BrightHLStruct *BrHL = (BrHL_Y != NULL) ? &BrHL_Y[UX] : R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
								if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
									(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
									(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
									return true;
								}
							}
						}

						ey = Len;
						UY = DefY + ey;
						UX = X1 + xn - MasterCx + MCx - Len + 1;
						if (0 < UY && UY < R->YLen) {
							const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
							int h = 0;
							if (BrHL_Y != NULL) {
								if (UX < 0) h -= UX;
								int exLen = Len + Len + 1;
								if ((UX + exLen) >= R->XLen) exLen = R->XLen - UX;
								for (; h < exLen; h++) {
									if (0 <= (UX + h) && (UX + h) < R->XLen) {
										const struct BMatrixBrightHL::BrightHLStruct *BrHL = &BrHL_Y[UX + h];
										if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
											(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
											(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
											return true;
										}
									}
								}
							} else {
								if (0 <= (UX + h) && (UX + h) < R->XLen) {
									const struct BMatrixBrightHL::BrightHLStruct *BrHL = R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									if ((BrHL->BrLow[0]) <= kRL && kRH <= (BrHL->BrHigh[0]) &&
										(BrHL->BrLow[1]) <= kGL && kGH <= (BrHL->BrHigh[1]) &&
										(BrHL->BrLow[2]) <= kBL && kBH <= (BrHL->BrHigh[2])) {
										return true;
									}
								}
							}
						}

						ex = -Len;
						UX = X1 + xn - MasterCx + MCx + ex;
						if (0 <= UX && UX < R->XLen) {
							int MaxEy = min(Len, R->YLen - DefY);
							for (ey = MaxEy; ey > MaxEy; ey--) { // ※元コードの挙動を再現しています
								UY = DefY + ey;
								const struct BMatrixBrightHL::BrightHLStruct *BrHL_Y = R->BuffByMaster[0].BrightHL[UY];
								const struct BMatrixBrightHL::BrightHLStruct *BrHL = (BrHL_Y != NULL) ? &BrHL_Y[UX] : R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
								if ((BrightWidthRL + BrHL->BrLow[0]) <= kRL && kRH <= (BrightWidthRH + BrHL->BrHigh[0]) &&
									(BrightWidthGL + BrHL->BrLow[1]) <= kGL && kGH <= (BrightWidthGH + BrHL->BrHigh[1]) &&
									(BrightWidthBL + BrHL->BrLow[2]) <= kBL && kBH <= (BrightWidthBH + BrHL->BrHigh[2])) {
									return true;
								}
							}
						}
					}

					return false; // 最後まで見つからなかった場合
				}();

				if (!isMatchedT2M) {
					if (0 <= (Y - MapYPoint) && (Y - MapYPoint) < MapYLen) {
						SetBmpBit1(Map, X1 + xn - MapXPoint, Y - MapYPoint);
					}
					NGCount2++;
				}
			}
		}
	}
}