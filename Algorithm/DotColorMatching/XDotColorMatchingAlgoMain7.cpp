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

void	DotColorMatchingItem::CalcInsideMono(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
									,ImageBufferFast &TBuff ,ImageBuffer &TRTBuff
									,int Layer
									,int mx ,int my
									,int Skip ,int SelfSearch 
									//,int CDiff 
									,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2
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

	BMatrix	&MBuff=R->BuffByMaster[0].Map[Layer];

	int		MCx=MasterPattern[CurrentRotationPatternNo].XLen/2;
	int		MCy=MasterPattern[CurrentRotationPatternNo].YLen/2;

	double	Mult=1.0;
	if(OutlineArea==true){
		Mult=ABase->LevelDownRateNearOutline;
	}
	int	ThresholdL;
	int	ThresholdH;
	if(Layer==0){
		ThresholdL=Clipping((int)(MThr->BrightWidthRL*Mult-MThr->BrightWidthRL*Thr->AddedBrightness*0.2),0,255);
		ThresholdH=Clipping((int)(MThr->BrightWidthRH*Mult-MThr->BrightWidthRH*Thr->AddedBrightness*0.2),0,255);
	}
	else
	if(Layer==1){
		ThresholdL=Clipping((int)(MThr->BrightWidthGL*Mult-MThr->BrightWidthGL*Thr->AddedBrightness*0.2),0,255);
		ThresholdH=Clipping((int)(MThr->BrightWidthGH*Mult-MThr->BrightWidthGH*Thr->AddedBrightness*0.2),0,255);
	}
	else
	if(Layer==2){
		ThresholdL=Clipping((int)(MThr->BrightWidthBL*Mult-MThr->BrightWidthBL*Thr->AddedBrightness*0.2),0,255);
		ThresholdH=Clipping((int)(MThr->BrightWidthBH*Mult-MThr->BrightWidthBH*Thr->AddedBrightness*0.2),0,255);
	}

	__TableType	*CompBrightWidthTableL;
	__TableType	*CompBrightWidthTableH;
	if(Layer==0){
		CompBrightWidthTableL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->RThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		CompBrightWidthTableH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->RThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==1){
		CompBrightWidthTableL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->GThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		CompBrightWidthTableH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->GThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==2){
		CompBrightWidthTableL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->BThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		CompBrightWidthTableH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(MThr->BThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	__TableType	*FlatBrightWidthTableL;
	__TableType	*FlatBrightWidthTableH;
	if(Layer==0){
		FlatBrightWidthTableL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->RThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		FlatBrightWidthTableH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->RThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==1){
		FlatBrightWidthTableL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->GThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		FlatBrightWidthTableH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->GThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==2){
		FlatBrightWidthTableL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->BThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		FlatBrightWidthTableH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(MThr->BThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}

	__TableType	*BrightWidthTableL;
	__TableType	*BrightWidthTableH;

	int	DotPerLine	=R->DotPerLine;
	int	MaxLines	=R->MaxLines;

	for(int i=0;i<N;i++){
		int	Y	=FA.GetFLineAbsY(i);
		int	X1	=FA.GetFLineLeftX(i);
		int	Numb=FA.GetFLineNumb(i);
		int	CMapY=Y-MasterCy+MCy;

		BYTE	*rMP=MBuff[CMapY];
		BYTE	CM=(rMP==NULL)?MBuff.GetConstantBrightness(CMapY):0;

		struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL[CMapY];
		BYTE	*TP;
		BYTE	*pTP;
		int	tY=Y+my;
		if((tY-SelfSearch)<0 || MaxLines<=(tY+SelfSearch))
			continue;
		if(GetComputerMiliSec()-StartMilisec>=MaxInspectMilisec){
			return;
		}
		BYTE	*rTP=TBuff.GetYWithoutDepended(tY);
		BYTE	*FlatTypeMapY=R->FlatTypeMap[CMapY];

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){
			if(tY==DbgY && (tX)==DbgX)
				DbgCode++;

			if(GetBmpBitOnY(FlatTypeMapY,CMapX)==0){
				BrightWidthTableL=CompBrightWidthTableL;
				BrightWidthTableH=CompBrightWidthTableH;
			}
			else{
				BrightWidthTableL=FlatBrightWidthTableL;
				BrightWidthTableH=FlatBrightWidthTableH;
			}

			int	cMP=(rMP!=NULL)?rMP[CMapX]:CM;
			const struct	BMatrixBrightHL::BrightHLStruct	*B	=(BrHL!=NULL)?&BrHL[CMapX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(CMapY);

			int	cMPL=B->BrLow[Layer];
			int	cMPH=B->BrHigh[Layer];

			// ==========================================
			// M2T チェックブロック（ラムダ式による早期リターン化）
			// ==========================================
			if(EnableM2T==true){
				BYTE	BrightWidthL=ClippingL(cMPL-BrightWidthTableL[cMP]+CDiffL);
				BYTE	BrightWidthH=ClippingH(cMPH+BrightWidthTableH[cMP]+CDiffH);

				bool isMatchedM2T = [&]() -> bool {
					//Len==0
					BYTE	k=rTP[tX];
					if(BrightWidthL<=k && k<=BrightWidthH){
						return true;
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k) continue;
							return true;
						}
						
						ex=Len;
						if(TRTBuff.IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
						
						ey=-Len;
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k) continue;
							return true;
						}
						
						ex=-Len;
						if(TRTBuff.IsNull()==true){
							for(ey=Len;ey>-Len;ey--){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=Len;ey>-Len;ey--){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
					}
					
					for(int	Len=0;Len<=SelfSearch;Len++){
						if((Len%Skip)==0)
							continue;
						int	ex,ey;
						ey=-Len;
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k) continue;
							return true;
						}
						
						ex=Len;
						if(TRTBuff.IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
						
						ey=-Len;
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k) continue;
							return true;
						}
						
						ex=-Len;
						if(TRTBuff.IsNull()==true){
							for(ey=Len;ey>-Len;ey--){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=Len;ey>-Len;ey--){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k) continue;
								return true;
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

			// ==========================================
			// T2M チェックブロック（ラムダ式による早期リターン化）
			// ==========================================
			if(EnableT2M==true){
				int	cTP=rTP[tX];
				int	BrightWidthL=-BrightWidthTableL[cTP];
				int	BrightWidthH= BrightWidthTableH[cTP];
				int	kL=cTP-CDiffL;
				int	kH=cTP-CDiffH;

				bool isMatchedT2M = [&]() -> bool {
					//Len==0
					if((BrightWidthL+cMPL)<=kL && kH<=(BrightWidthH+cMPH)){
						return true;
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if(0<=(UX+h) && (UX+h)<R->XLen){										
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){										
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
						ex=Len;
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=-Len;ey<Len;ey++){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
						ey=Len;
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
						ex=-Len;
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPL=BrHL->BrLow[Layer];
											BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
						ex=Len;
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=-Len;ey<Len;ey++){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
						ey=Len;
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPL=BrHL->BrLow[Layer];
											BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
						ex=-Len;
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)) return true;
									}
								}
							}
						}
					}
					
					return false;
				}();

				if(!isMatchedT2M){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					NGCount2++;
				}
			}
		}
	}
}