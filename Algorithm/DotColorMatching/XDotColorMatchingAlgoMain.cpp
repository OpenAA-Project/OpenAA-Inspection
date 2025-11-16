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

inline	int	ClippingL(int d)	{	return (d<0)?0:d;		}
inline	int	ClippingH(int d)	{	return (d>=255)?255:d;	}
bool	MakeFootPoint3D( int x1,int y1,int z1
						,int x2,int y2,int z2
						,int X ,int Y, int Z
						,double &mx ,double &my ,double &mz);

static	int	DbgX,DbgY,DbgCode=0;

void	DotColorMatchingItem::CalcInside1(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
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

			if(EnableM2T==true){
				BYTE	BrightWidthRL=ClippingL(cMPLR-BrightWidthTableRL[cMPR]+CDiffRL);
				BYTE	BrightWidthRH=ClippingH(cMPHR+BrightWidthTableRH[cMPR]+CDiffRH);
				BYTE	BrightWidthGL=ClippingL(cMPLG-BrightWidthTableGL[cMPG]+CDiffGL);
				BYTE	BrightWidthGH=ClippingH(cMPHG+BrightWidthTableGH[cMPG]+CDiffGH);
				BYTE	BrightWidthBL=ClippingL(cMPLB-BrightWidthTableBL[cMPB]+CDiffBL);
				BYTE	BrightWidthBH=ClippingH(cMPHB+BrightWidthTableBH[cMPB]+CDiffBH);

				{
					//Len==0
					{
						pTPR=&rTPR[tX];
						BYTE	kR=*pTPR;
						if(kR<BrightWidthRL || BrightWidthRH<kR)
							goto	NextN1;
					}
					{
						pTPG=&rTPG[tX];
						BYTE	kG=*pTPG;
						if(kG<BrightWidthGL || BrightWidthGH<kG)
							goto	NextN1;
					}
					{
						pTPB=&rTPB[tX];
						BYTE	kB=*pTPB;
						if(kB<BrightWidthBL || BrightWidthBH<kB)
							goto	NextN1;
					}
					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){

						if(TRTBuff[0]->IsNull()==true){
							int	tYey=tY-Len;
							int	tXex=tX+ex;
							for(ey=-Len;ey<Len;ey++,tYey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TPR=TBuff[0]->GetYWithoutDepended(tYey);
									BYTE	kR=TPR[tXex];
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									TPG=TBuff[1]->GetYWithoutDepended(tYey);
									BYTE	kG=TPG[tXex];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									TPB=TBuff[2]->GetYWithoutDepended(tYey);
									BYTE	kB=TPB[tXex];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}

									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						int	tYey=tY+Len;
						int	tXex=tX+ex;
						for(ey=Len;ey>-Len;ey--,tYey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tYey);
								BYTE	kR=TPR[tXex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tYey);
								BYTE	kG=TPG[tXex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tYey);
								BYTE	kB=TPB[tXex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						int	tYey=tY-Len;
						int	tXex=tX+ex;
						for(ey=-Len;ey<Len;ey++,tYey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tYey);
								BYTE	kR=TPR[tXex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tYey);
								BYTE	kG=TPG[tXex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tYey);
								BYTE	kB=TPB[tXex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						int	tYey=tY+Len;
						int	tXex=tX+ex;
						for(ey=Len;ey>-Len;ey--,tYey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tYey);
								BYTE	kR=TPR[tXex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tYey);
								BYTE	kG=TPG[tXex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tYey);
								BYTE	kB=TPB[tXex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
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
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(kRL<(BrightWidthRL+cMPLR) || (BrightWidthRH+cMPHR)<kRH){
							goto	NextT1;
						}
						if(kGL<(BrightWidthGL+cMPLG) || (BrightWidthGH+cMPHG)<kGH){
							goto	NextT1;
						}
						if(kBL<(BrightWidthBL+cMPLB) || (BrightWidthBH+cMPHB)<kBH){
							goto	NextT1;
						}
						//BYTE	rMLR=cMPLR;
						//BYTE	rMLG=cMPLG;
						//BYTE	rMLB=cMPLB;
						//BYTE	rMHR=cMPHR;
						//BYTE	rMHG=cMPHG;
						//BYTE	rMHB=cMPHB;
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							int	UY=DefY+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									if(UX<0){
										h -=UX;
									}
									int	exLen=Len+Len+1;
									if((UX+exLen)>=R->XLen){
										exLen=R->XLen-UX;
									}
									for(;h<exLen;h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										//if(0<=(UX+h) && (UX+h)<R->XLen){									
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										//}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){									
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrightWidthRL+BrHL->BrLow[0];
										BYTE	MPLG=BrightWidthGL+BrHL->BrLow[1];
										BYTE	MPLB=BrightWidthBL+BrHL->BrLow[2];
										BYTE	MPHR=BrightWidthRH+BrHL->BrHigh[0];
										BYTE	MPHG=BrightWidthGH+BrHL->BrHigh[1];
										BYTE	MPHB=BrightWidthBH+BrHL->BrHigh[2];
										//for(ex=-Len;ex<=Len;ex++,h++){
											if(MPLR<=kRL && kRH<=MPHR 
											&& MPLG<=kGL && kGH<=MPHG 
											&& MPLB<=kBL && kBH<=MPHB){
												goto	OkNext2;
											}
										//}
									}
								}
							}
						}
						ex=Len;
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								//int	DefY=Y-MasterCy+MCy;
								int	MaxEy=min(Len,R->YLen-DefY);
								for(ey=max(-Len,-DefY);ey<MaxEy;ey++){
									int	UY=DefY+ey;
									//if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
										}
									//}
								}
							}
						}
						ey=Len;
						{
							int	UY=DefY+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									if(UX<0){
										h -=UX;
									}
									int	exLen=Len+Len+1;
									if((UX+exLen)>=R->XLen){
										exLen=R->XLen-UX;
									}
									for(;h<exLen;h++){
									//for(ex=-Len+1;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										//if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										//}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrightWidthRL+BrHL->BrLow[0];
										BYTE	MPLG=BrightWidthGL+BrHL->BrLow[1];
										BYTE	MPLB=BrightWidthBL+BrHL->BrLow[2];
										BYTE	MPHR=BrightWidthRH+BrHL->BrHigh[0];
										BYTE	MPHG=BrightWidthGH+BrHL->BrHigh[1];
										BYTE	MPHB=BrightWidthBH+BrHL->BrHigh[2];
										//for(ex=-Len+1;ex<=Len;ex++,h++){
											if(MPLR<=kRL && kRH<=MPHR 
											&& MPLG<=kGL && kGH<=MPHG 
											&& MPLB<=kBL && kBH<=MPHB){
												goto	OkNext2;
											}
										//}
									}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								//int	DefY=Y-MasterCy+MCy;
								int	MaxEy=min(Len,R->YLen-DefY);
								int	MinEy=max(-Len,-DefY);
								for(ey=MaxEy;ey<MaxEy;ey--){
									int	UY=DefY+ey;
								//for(ey=Len;ey>-Len;ey--){
								//	int	UY=Y-MasterCy+MCy+ey;
								//	if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
										}
									//}
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
							int	UY=DefY+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								if(BrHL_Y!=NULL){
									if(UX<0){
										h -=UX;
									}
									int	exLen=Len+Len+1;
									if((UX+exLen)>=R->XLen){
										exLen=R->XLen-UX;
									}
									for(;h<exLen;h++){
									//for(ex=-Len;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										//if(0<=(UX+h) && (UX+h)<R->XLen){
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										//}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrightWidthRL+BrHL->BrLow[0];
										BYTE	MPLG=BrightWidthGL+BrHL->BrLow[1];
										BYTE	MPLB=BrightWidthBL+BrHL->BrLow[2];
										BYTE	MPHR=BrightWidthRH+BrHL->BrHigh[0];
										BYTE	MPHG=BrightWidthGH+BrHL->BrHigh[1];
										BYTE	MPHB=BrightWidthBH+BrHL->BrHigh[2];
										//for(ex=-Len;ex<=Len;ex++,h++){
											if((MPLR)<=kRL && kRH<=(MPHR) 
											&& (MPLG)<=kGL && kGH<=(MPHG) 
											&& (MPLB)<=kBL && kBH<=(MPHB)){
												goto	OkNext2;
											}
										//}
									}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								//int	DefY=Y-MasterCy+MCy;
								int	MaxEy=min(Len,R->YLen-DefY);
								for(ey=max(-Len,-DefY);ey<MaxEy;ey++){
									int	UY=DefY+ey;
								//for(ey=-Len;ey<Len;ey++){
								//	int	UY=Y-MasterCy+MCy+ey;
								//	if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];

										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
										}
									//}
								}
							}
						}
						ey=Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							int	UY=DefY+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								if(BrHL_Y!=NULL){
									if(UX<0){
										h -=UX;
									}
									int	exLen=Len+Len+1;
									if((UX+exLen)>=R->XLen){
										exLen=R->XLen-UX;
									}
									for(;h<exLen;h++){
									//for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPLR=BrightWidthRL+BrHL->BrLow[0];
										BYTE	MPLG=BrightWidthGL+BrHL->BrLow[1];
										BYTE	MPLB=BrightWidthBL+BrHL->BrLow[2];
										BYTE	MPHR=BrightWidthRH+BrHL->BrHigh[0];
										BYTE	MPHG=BrightWidthGH+BrHL->BrHigh[1];
										BYTE	MPHB=BrightWidthBH+BrHL->BrHigh[2];
										//for(ex=-Len+1;ex<=Len;ex++,h++){
											if((MPLR)<=kRL && kRH<=(MPHR)
											&& (MPLG)<=kGL && kGH<=(MPHG)
											&& (MPLB)<=kBL && kBH<=(MPHB)){
												goto	OkNext2;
											}
										//}
									}
								}
							}
						}
						ex=-Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								//int	DefY=Y-MasterCy+MCy;
								int	MaxEy=min(Len,R->YLen-DefY);
								int	MinEy=max(-Len,-DefY);
								for(ey=MaxEy;ey>MaxEy;ey--){
									int	UY=DefY+ey;
								//for(ey=Len;ey>-Len;ey--){
								//	int	UY=Y-MasterCy+MCy+ey;
								//	if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];

										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
										}
									//}
								}
							}
						}
					}
					if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MapYLen){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					}
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}

//====================================================================================================

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

				{
					//Len==0
					{
						pTPR=&rTPR[tX];
						BYTE	kR=*pTPR;
						if(kR<BrightWidthRL || BrightWidthRH<kR)
							goto	NextN1;
					}
					{
						pTPG=&rTPG[tX];
						BYTE	kG=*pTPG;
						if(kG<BrightWidthGL || BrightWidthGH<kG)
							goto	NextN1;
					}
					{
						pTPB=&rTPB[tX];
						BYTE	kB=*pTPB;
						if(kB<BrightWidthBL || BrightWidthBH<kB)
							goto	NextN1;
					}
					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}

									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
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
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(kRL<(BrightWidthRL+cMPLR) || (BrightWidthRH+cMPHR)<kRH){
							goto	NextT1;
						}
						if(kGL<(BrightWidthGL+cMPLG) || (BrightWidthGH+cMPHG)<kGH){
							goto	NextT1;
						}
						if(kBL<(BrightWidthBL+cMPLB) || (BrightWidthBH+cMPHB)<kBH){
							goto	NextT1;
						}
						//BYTE	rMLR=cMPLR;
						//BYTE	rMLG=cMPLG;
						//BYTE	rMLB=cMPLB;
						//BYTE	rMHR=cMPHR;
						//BYTE	rMHG=cMPHG;
						//BYTE	rMHB=cMPHB;
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
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
												goto	OkNext2;
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
												goto	OkNext2;
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
											goto	OkNext2;
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
												goto	OkNext2;
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
												goto	OkNext2;
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
											goto	OkNext2;
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
												goto	OkNext2;
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
												goto	OkNext2;
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
											goto	OkNext2;
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
												goto	OkNext2;
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
												goto	OkNext2;
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
											goto	OkNext2;
										}
									}
								}
							}
						}
					}
					if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MapYLen){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					}
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}

//====================================================================================================

void	DotColorMatchingItem::CalcInsideSubtract(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
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

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){

			//if(tY==DbgY && (tX)==DbgX)
			//	DbgCode++;

			//int	CMapX=X1+xn-MasterCx+MCx;
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

			for(SubtractItem *s=SubBlock.GetFirst();s!=NULL;s=s->GetNext()){
				DotColorMatchingItem	*SItem=(DotColorMatchingItem *)s->IndexAfterEdit;
				//SItemの開始座標
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
								goto	MaskedEnd1;
							}
						}
					}
				}
			}

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

			if(EnableM2T==true){
				BYTE	BrightWidthRL=ClippingL(cMPLR-BrightWidthTableRL[cMPR]+CDiffRL);
				BYTE	BrightWidthRH=ClippingH(cMPHR+BrightWidthTableRH[cMPR]+CDiffRH);
				BYTE	BrightWidthGL=ClippingL(cMPLG-BrightWidthTableGL[cMPG]+CDiffGL);
				BYTE	BrightWidthGH=ClippingH(cMPHG+BrightWidthTableGH[cMPG]+CDiffGH);
				BYTE	BrightWidthBL=ClippingL(cMPLB-BrightWidthTableBL[cMPB]+CDiffBL);
				BYTE	BrightWidthBH=ClippingH(cMPHB+BrightWidthTableBH[cMPB]+CDiffBH);

				{
					//Len==0
					{
						pTPR=&rTPR[tX];
						BYTE	kR=*pTPR;
						if(kR<BrightWidthRL || BrightWidthRH<kR)
							goto	NextN1;
					}
					{
						pTPG=&rTPG[tX];
						BYTE	kG=*pTPG;
						if(kG<BrightWidthGL || BrightWidthGH<kG)
							goto	NextN1;
					}
					{
						pTPB=&rTPB[tX];
						BYTE	kB=*pTPB;
						if(kB<BrightWidthBL || BrightWidthBH<kB)
							goto	NextN1;
					}
					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}

									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}

OkNext:;
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
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(kRL<(BrightWidthRL+cMPLR) || (BrightWidthRH+cMPHR)<kRH){
							goto	NextT1;
						}
						if(kGL<(BrightWidthGL+cMPLG) || (BrightWidthGH+cMPHG)<kGH){
							goto	NextT1;
						}
						if(kBL<(BrightWidthBL+cMPLB) || (BrightWidthBH+cMPHB)<kBH){
							goto	NextT1;
						}
						//BYTE	rMLR=cMPLR;
						//BYTE	rMLG=cMPLG;
						//BYTE	rMLB=cMPLB;
						//BYTE	rMHR=cMPHR;
						//BYTE	rMHG=cMPHG;
						//BYTE	rMHB=cMPHB;
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										//for(ex=-Len;ex<=Len;ex++,h++){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									//}
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

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
										}
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
										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									//for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									//}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];
										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
										if(0<=(UX+h) && (UX+h)<R->XLen){
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									//for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR) 
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG) 
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									//}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=-Len;ey<Len;ey++){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];

										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									//for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											BYTE	MPLR=BrHL->BrLow[0];
											BYTE	MPLG=BrHL->BrLow[1];
											BYTE	MPLB=BrHL->BrLow[2];
											BYTE	MPHR=BrHL->BrHigh[0];
											BYTE	MPHG=BrHL->BrHigh[1];
											BYTE	MPHB=BrHL->BrHigh[2];
											if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
											&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
											&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
												goto	OkNext2;
											}
										}
									//}
								}
							}
						}
						ex=-Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPLR=BrHL->BrLow[0];
										BYTE	MPLG=BrHL->BrLow[1];
										BYTE	MPLB=BrHL->BrLow[2];
										BYTE	MPHR=BrHL->BrHigh[0];
										BYTE	MPHG=BrHL->BrHigh[1];
										BYTE	MPHB=BrHL->BrHigh[2];

										if((BrightWidthRL+MPLR)<=kRL && kRH<=(BrightWidthRH+MPHR)
										&& (BrightWidthGL+MPLG)<=kGL && kGH<=(BrightWidthGH+MPHG)
										&& (BrightWidthBL+MPLB)<=kBL && kBH<=(BrightWidthBH+MPHB)){
											goto	OkNext2;
										}
									}
								}
							}
						}
					}
					if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MapYLen){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					}
				//}
				NGCount2++;
			}
MaskedEnd1:;
OkNext2:;
		}
	}
}

//====================================================================================================

void	DotColorMatchingItem::CalcInsideSubtractWithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
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
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){

			//if(tY==DbgY && (tX)==DbgX)
			//	DbgCode++;

			//int	CMapX=X1+xn-MasterCx+MCx;
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

			for(SubtractItem *s=SubBlock.GetFirst();s!=NULL;s=s->GetNext()){
				DotColorMatchingItem	*SItem=(DotColorMatchingItem *)s->IndexAfterEdit;
				//SItemの開始座標
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
								goto	MaskedEnd1;
							}
						}
					}
				}
			}

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

				{
					//Len==0
					{
						pTPR=&rTPR[tX];
						BYTE	kR=*pTPR;
						if(kR<BrightWidthRL || BrightWidthRH<kR)
							goto	NextN1;
					}
					{
						pTPG=&rTPG[tX];
						BYTE	kG=*pTPG;
						if(kG<BrightWidthGL || BrightWidthGH<kG)
							goto	NextN1;
					}
					{
						pTPB=&rTPB[tX];
						BYTE	kB=*pTPB;
						if(kB<BrightWidthBL || BrightWidthBH<kB)
							goto	NextN1;
					}
					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
									if(kR<BrightWidthRL || BrightWidthRH<kR){
										continue;
									}
									BYTE	kG=TPG[tY+ey];
									if(kG<BrightWidthGL || BrightWidthGH<kG){
										continue;
									}
									BYTE	kB=TPB[tY+ey];
									if(kB<BrightWidthBL || BrightWidthBH<kB){
										continue;
									}

									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=*pTPG;
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=*pTPB;
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
							if(kR<BrightWidthRL || BrightWidthRH<kR){
								continue;
							}
							BYTE	kG=*pTPG;
							if(kG<BrightWidthGL || BrightWidthGH<kG){
								continue;
							}
							BYTE	kB=*pTPB;
							if(kB<BrightWidthBL || BrightWidthBH<kB){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if(kR<BrightWidthRL || BrightWidthRH<kR){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if(kG<BrightWidthGL || BrightWidthGH<kG){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if(kB<BrightWidthBL || BrightWidthBH<kB){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}

OkNext:;
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
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(kRL<(BrightWidthRL+cMPLR) || (BrightWidthRH+cMPHR)<kRH){
							goto	NextT1;
						}
						if(kGL<(BrightWidthGL+cMPLG) || (BrightWidthGH+cMPHG)<kGH){
							goto	NextT1;
						}
						if(kBL<(BrightWidthBL+cMPLB) || (BrightWidthBH+cMPHB)<kBH){
							goto	NextT1;
						}
						//BYTE	rMLR=cMPLR;
						//BYTE	rMLG=cMPLG;
						//BYTE	rMLB=cMPLB;
						//BYTE	rMHR=cMPHR;
						//BYTE	rMHG=cMPHG;
						//BYTE	rMHB=cMPHB;
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							BYTE	*tVarietyMapR=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[0].GetYDirectly(Y+ey):NULL;
							BYTE	*tVarietyMapG=(AP->VarietyMap[1].IsValid()==true)?AP->VarietyMap[1].GetYDirectly(Y+ey):NULL;
							BYTE	*tVarietyMapB=(AP->VarietyMap[2].IsValid()==true)?AP->VarietyMap[2].GetYDirectly(Y+ey):NULL;

							int	UY=Y-MasterCy+MCy+ey;
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
												goto	OkNext2;
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
									if(0<=(UX+h) && (UX+h)<R->XLen){
										for(ex=-Len;ex<=Len;ex++,h++){
											int	masterx=X1+xn+ex;											
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
											&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
											&& (BrightWidthBL+MPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
												goto	OkNext2;
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
											goto	OkNext2;
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
												goto	OkNext2;
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
									if(0<=(UX+h) && (UX+h)<R->XLen){
										for(ex=-Len+1;ex<=Len;ex++,h++){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+MPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+MPHR+tVarietyR) 
											&& (BrightWidthGL+MPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+MPHG+tVarietyG) 
											&& (BrightWidthBL+MPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+MPHB+tVarietyB)){
												goto	OkNext2;
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
											goto	OkNext2;
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
												goto	OkNext2;
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
												goto	OkNext2;
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
											goto	OkNext2;
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
												goto	OkNext2;
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
												goto	OkNext2;
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
											goto	OkNext2;
										}
									}
								}
							}
						}
					}
					if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MapYLen){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
					}
				//}
				NGCount2++;
			}
MaskedEnd1:;
OkNext2:;
		}
	}
}

//====================================================================================================

void	DotColorMatchingItem::CalcInside2(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
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

	//BYTE	**MHigh0=R->BrightnessHigh[0];
	//BYTE	**MHigh1=R->BrightnessHigh[1];
	//BYTE	**MHigh2=R->BrightnessHigh[2];
	//BYTE	**MLow0=R->BrightnessLow[0];
	//BYTE	**MLow1=R->BrightnessLow[1];
	//BYTE	**MLow2=R->BrightnessLow[2];
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

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){
			if(tY==DbgY && (tX)==DbgX)
				DbgCode++;

			//int	CMapX=X1+xn-MasterCx+MCx;
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

			if(EnableM2T==true){
				BYTE	ABrightWidthRL=ClippingL(cAMPLR-BrightWidthTableRL[cAMPR]+CDiffRL);
				BYTE	ABrightWidthRH=ClippingH(cAMPHR+BrightWidthTableRH[cAMPR]+CDiffRH);
				BYTE	ABrightWidthGL=ClippingL(cAMPLG-BrightWidthTableGL[cAMPG]+CDiffGL);
				BYTE	ABrightWidthGH=ClippingH(cAMPHG+BrightWidthTableGH[cAMPG]+CDiffGH);
				BYTE	ABrightWidthBL=ClippingL(cAMPLB-BrightWidthTableBL[cAMPB]+CDiffBL);
				BYTE	ABrightWidthBH=ClippingH(cAMPHB+BrightWidthTableBH[cAMPB]+CDiffBH);
				BYTE	BBrightWidthRL=ClippingL(cBMPLR-BrightWidthTableRL[cBMPR]+CDiffRL);
				BYTE	BBrightWidthRH=ClippingH(cBMPHR+BrightWidthTableRH[cBMPR]+CDiffRH);
				BYTE	BBrightWidthGL=ClippingL(cBMPLG-BrightWidthTableGL[cBMPG]+CDiffGL);
				BYTE	BBrightWidthGH=ClippingH(cBMPHG+BrightWidthTableGH[cBMPG]+CDiffGH);
				BYTE	BBrightWidthBL=ClippingL(cBMPLB-BrightWidthTableBL[cBMPB]+CDiffBL);
				BYTE	BBrightWidthBH=ClippingH(cBMPHB+BrightWidthTableBH[cBMPB]+CDiffBH);

				{
					//Len==0
					{
						pTPR=&rTPR[tX];
						BYTE	kR=*pTPR;
						if((kR<ABrightWidthRL || ABrightWidthRH<kR)
						&& (kR<BBrightWidthRL || BBrightWidthRH<kR))
							goto	NextN1;
					}
					{
						pTPG=&rTPG[tX];
						BYTE	kG=*pTPG;
						if((kG<ABrightWidthGL || ABrightWidthGH<kG)
						&& (kG<BBrightWidthGL || BBrightWidthGH<kG))
							goto	NextN1;
					}
					{
						pTPB=&rTPB[tX];
						BYTE	kB=*pTPB;
						if((kB<ABrightWidthBL || ABrightWidthBH<kB)
						&& (kB<BBrightWidthBL || BBrightWidthBH<kB))
							goto	NextN1;
					}
					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=*pTPG;
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=*pTPB;
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
									if((kR<ABrightWidthRL || ABrightWidthRH<kR)
									&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
										continue;
									}
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if((kG<ABrightWidthGL || ABrightWidthGH<kG)
									&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
										continue;
									}
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if((kB<ABrightWidthBL || ABrightWidthBH<kB)
									&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
									if((kR<ABrightWidthRL || ABrightWidthRH<kR)
									&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
										continue;
									}
									BYTE	kG=TPG[tY+ey];
									if((kG<ABrightWidthGL || ABrightWidthGH<kG)
									&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
										continue;
									}
									BYTE	kB=TPB[tY+ey];
									if((kB<ABrightWidthBL || ABrightWidthBH<kB)
									&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
										continue;
									}

									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
							if((kR<ABrightWidthRL || ABrightWidthRH<kR)
							&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
								continue;
							}
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG)
							&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
								continue;
							}
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB)
							&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=*pTPG;
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=*pTPB;
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
							if((kR<ABrightWidthRL || ABrightWidthRH<kR)
							&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
								continue;
							}
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG)
							&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
								continue;
							}
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB)
							&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					TPR=TBuff[0]->GetYWithoutDepended(tY);
					TPG=TBuff[1]->GetYWithoutDepended(tY);
					TPB=TBuff[2]->GetYWithoutDepended(tY);
					BYTE	kR=TPR[tX];
					BYTE	kG=TPG[tX];
					BYTE	kB=TPB[tX];
					double hx ,hy ,hz;
					if(MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kR ,kG, kB
										,hx ,hy ,hz)==true
					&& MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kR ,kG, kB
										,hx ,hy ,hz)==true){
						BYTE	cMPR=(BYTE)Clipping(hx,0.0,255.0);
						BYTE	cMPG=(BYTE)Clipping(hy,0.0,255.0);
						BYTE	cMPB=(BYTE)Clipping(hz,0.0,255.0);
						BYTE	HBrightWidthRL=ClippingL(cMPR-BrightWidthTableRL[cMPR]+CDiffRL);
						BYTE	HBrightWidthRH=ClippingH(cMPR+BrightWidthTableRH[cMPR]+CDiffRH);
						BYTE	HBrightWidthGL=ClippingL(cMPG-BrightWidthTableGL[cMPG]+CDiffGL);
						BYTE	HBrightWidthGH=ClippingH(cMPG+BrightWidthTableGH[cMPG]+CDiffGH);
						BYTE	HBrightWidthBL=ClippingL(cMPB-BrightWidthTableBL[cMPB]+CDiffBL);
						BYTE	HBrightWidthBH=ClippingH(cMPB+BrightWidthTableBH[cMPB]+CDiffBH);

						if(HBrightWidthRL<=kR && kR<=HBrightWidthRH
						&& HBrightWidthGL<=kG && kG<=HBrightWidthGH
						&& HBrightWidthBL<=kB && kB<=HBrightWidthBH){
							GrayDotsM++;
							goto	OkNext;
						}
					}					
					
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
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
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if((kRL<(BrightWidthRL+cAMPLR) || (BrightWidthRH+cAMPHR)<kRH)
						&& (kRL<(BrightWidthRL+cBMPLR) || (BrightWidthRH+cBMPHR)<kRH)){
							goto	NextT1;
						}
						if((kGL<(BrightWidthGL+cAMPLG) || (BrightWidthGH+cAMPHG)<kGH)
						&& (kGL<(BrightWidthGL+cBMPLG) || (BrightWidthGH+cBMPHG)<kGH)){
							goto	NextT1;
						}
						if((kBL<(BrightWidthBL+cAMPLB) || (BrightWidthBH+cAMPHB)<kBH)
						&& (kBL<(BrightWidthBL+cBMPLB) || (BrightWidthBH+cBMPHB)<kBH)){
							goto	NextT1;
						}
						//BYTE	rMLR=cMPLR;
						//BYTE	rMLG=cMPLG;
						//BYTE	rMLB=cMPLB;
						//BYTE	rMHR=cMPHR;
						//BYTE	rMHG=cMPHG;
						//BYTE	rMHB=cMPHB;
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									for(ex=-Len;ex<=Len;ex++,h++){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
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
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

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
										if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
										&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
										&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
										&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
										&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
											goto	OkNext2;
										}
									}
								}
							}
						}
						ey=Len;
						{
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else
								if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									if(0<=(UX+h) && (UX+h)<R->XLen){
									//for(ex=-Len+1;ex<=Len;ex++,h++){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									//}
								}
								else{
									for(ex=-Len+1;ex<=Len;ex++,h++){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

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
										if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR)
										&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG)
										&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR)
										&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG)
										&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];

								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									//for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									//}
								}
								else{
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR) 
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG) 
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR) 
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG) 
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=-Len;ey<Len;ey++){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

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

										if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR)
										&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG)
										&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR)
										&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG)
										&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];

								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR)
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG)
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR)
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG)
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
									//for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR)
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG)
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR)
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG)
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									//}
								}
								else{
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
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
											if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR)
											&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG)
											&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR)
											&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG)
											&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
												goto	OkNext2;
											}
										}
									}
								}
							}
						}
						ex=-Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrAHL=(BrAHL_Y!=NULL)?&BrAHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										const struct	BMatrixBrightHL::BrightHLStruct	*BrBHL=(BrBHL_Y!=NULL)?&BrBHL_Y[UX]:R->BuffByMaster[1].BrightHL.GetConstantBrightness(UY);

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

										if((BrightWidthRL+AMPLR)<=kRL && kRH<=(BrightWidthRH+AMPHR)
										&& (BrightWidthGL+AMPLG)<=kGL && kGH<=(BrightWidthGH+AMPHG)
										&& (BrightWidthBL+AMPLB)<=kBL && kBH<=(BrightWidthBH+AMPHB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR)<=kRL && kRH<=(BrightWidthRH+BMPHR)
										&& (BrightWidthGL+BMPLG)<=kGL && kGH<=(BrightWidthGH+BMPHG)
										&& (BrightWidthBL+BMPLB)<=kBL && kBH<=(BrightWidthBH+BMPHB)){
											goto	OkNext2;
										}
									}
								}
							}
						}
					}

					double hxL ,hyL ,hzL;
					double hxH ,hyH ,hzH;
					if(MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kRL ,kGL, kBL
										,hxL ,hyL ,hzL)==true
					&& MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kRH ,kGH, kBH
										,hxH ,hyH ,hzH)==true){
						BYTE	cMPRL=(BYTE)Clipping(hxL,0.0,255.0);
						BYTE	cMPGL=(BYTE)Clipping(hyL,0.0,255.0);
						BYTE	cMPBL=(BYTE)Clipping(hzL,0.0,255.0);
						BYTE	cMPRH=(BYTE)Clipping(hxH,0.0,255.0);
						BYTE	cMPGH=(BYTE)Clipping(hyH,0.0,255.0);
						BYTE	cMPBH=(BYTE)Clipping(hzH,0.0,255.0);
						BYTE	HBrightWidthRL=ClippingL(cMPRL-BrightWidthTableRL[cMPRL]+CDiffRL);
						BYTE	HBrightWidthRH=ClippingH(cMPRH+BrightWidthTableRH[cMPRH]+CDiffRH);
						BYTE	HBrightWidthGL=ClippingL(cMPGL-BrightWidthTableGL[cMPGL]+CDiffGL);
						BYTE	HBrightWidthGH=ClippingH(cMPGH+BrightWidthTableGH[cMPGH]+CDiffGH);
						BYTE	HBrightWidthBL=ClippingL(cMPBL-BrightWidthTableBL[cMPBL]+CDiffBL);
						BYTE	HBrightWidthBH=ClippingH(cMPBH+BrightWidthTableBH[cMPBH]+CDiffBH);

						if(HBrightWidthRL<=kRL && kRH<=HBrightWidthRH
						&& HBrightWidthGL<=kGL && kGH<=HBrightWidthGH
						&& HBrightWidthBL<=kBL && kBH<=HBrightWidthBH){
							GrayDotsT++;
							goto	OkNext2;
						}
					}					

					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}


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

	//BYTE	**MHigh0=R->BrightnessHigh[0];
	//BYTE	**MHigh1=R->BrightnessHigh[1];
	//BYTE	**MHigh2=R->BrightnessHigh[2];
	//BYTE	**MLow0=R->BrightnessLow[0];
	//BYTE	**MLow1=R->BrightnessLow[1];
	//BYTE	**MLow2=R->BrightnessLow[2];
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

			//int	CMapX=X1+xn-MasterCx+MCx;
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

				{
					//Len==0
					{
						pTPR=&rTPR[tX];
						BYTE	kR=*pTPR;
						if((kR<ABrightWidthRL || ABrightWidthRH<kR)
						&& (kR<BBrightWidthRL || BBrightWidthRH<kR))
							goto	NextN1;
					}
					{
						pTPG=&rTPG[tX];
						BYTE	kG=*pTPG;
						if((kG<ABrightWidthGL || ABrightWidthGH<kG)
						&& (kG<BBrightWidthGL || BBrightWidthGH<kG))
							goto	NextN1;
					}
					{
						pTPB=&rTPB[tX];
						BYTE	kB=*pTPB;
						if((kB<ABrightWidthBL || ABrightWidthBH<kB)
						&& (kB<BBrightWidthBL || BBrightWidthBH<kB))
							goto	NextN1;
					}
					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=*pTPG;
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=*pTPB;
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
									if((kR<ABrightWidthRL || ABrightWidthRH<kR)
									&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
										continue;
									}
									TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
									BYTE	kG=TPG[tX+ex];
									if((kG<ABrightWidthGL || ABrightWidthGH<kG)
									&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
										continue;
									}
									TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
									BYTE	kB=TPB[tX+ex];
									if((kB<ABrightWidthBL || ABrightWidthBH<kB)
									&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
									if((kR<ABrightWidthRL || ABrightWidthRH<kR)
									&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
										continue;
									}
									BYTE	kG=TPG[tY+ey];
									if((kG<ABrightWidthGL || ABrightWidthGH<kG)
									&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
										continue;
									}
									BYTE	kB=TPB[tY+ey];
									if((kB<ABrightWidthBL || ABrightWidthBH<kB)
									&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
										continue;
									}

									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
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
							if((kR<ABrightWidthRL || ABrightWidthRH<kR)
							&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
								continue;
							}
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG)
							&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
								continue;
							}
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB)
							&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=*pTPG;
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=*pTPB;
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
							if((kR<ABrightWidthRL || ABrightWidthRH<kR)
							&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
								continue;
							}
							BYTE	kG=*pTPG;
							if((kG<ABrightWidthGL || ABrightWidthGH<kG)
							&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
								continue;
							}
							BYTE	kB=*pTPB;
							if((kB<ABrightWidthBL || ABrightWidthBH<kB)
							&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff[0]->IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TPR=TBuff[0]->GetYWithoutDepended(tY+ey);
								BYTE	kR=TPR[tX+ex];
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								TPG=TBuff[1]->GetYWithoutDepended(tY+ey);
								BYTE	kG=TPG[tX+ex];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								TPB=TBuff[2]->GetYWithoutDepended(tY+ey);
								BYTE	kB=TPB[tX+ex];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
								if((kR<ABrightWidthRL || ABrightWidthRH<kR)
								&& (kR<BBrightWidthRL || BBrightWidthRH<kR)){
									continue;
								}
								BYTE	kG=TPG[tY+ey];
								if((kG<ABrightWidthGL || ABrightWidthGH<kG)
								&& (kG<BBrightWidthGL || BBrightWidthGH<kG)){
									continue;
								}
								BYTE	kB=TPB[tY+ey];
								if((kB<ABrightWidthBL || ABrightWidthBH<kB)
								&& (kB<BBrightWidthBL || BBrightWidthBH<kB)){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					TPR=TBuff[0]->GetYWithoutDepended(tY);
					TPG=TBuff[1]->GetYWithoutDepended(tY);
					TPB=TBuff[2]->GetYWithoutDepended(tY);
					BYTE	kR=TPR[tX];
					BYTE	kG=TPG[tX];
					BYTE	kB=TPB[tX];
					double hx ,hy ,hz;
					if(MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kR ,kG, kB
										,hx ,hy ,hz)==true){
						BYTE	cMPR=(BYTE)Clipping(hx,0.0,255.0);
						BYTE	cMPG=(BYTE)Clipping(hy,0.0,255.0);
						BYTE	cMPB=(BYTE)Clipping(hz,0.0,255.0);
						BYTE	HBrightWidthRL=ClippingL(cMPR-BrightWidthTableRL[cMPR]+CDiffRL-VarietyR);
						BYTE	HBrightWidthRH=ClippingH(cMPR+BrightWidthTableRH[cMPR]+CDiffRH+VarietyR);
						BYTE	HBrightWidthGL=ClippingL(cMPG-BrightWidthTableGL[cMPG]+CDiffGL-VarietyG);
						BYTE	HBrightWidthGH=ClippingH(cMPG+BrightWidthTableGH[cMPG]+CDiffGH+VarietyG);
						BYTE	HBrightWidthBL=ClippingL(cMPB-BrightWidthTableBL[cMPB]+CDiffBL-VarietyB);
						BYTE	HBrightWidthBH=ClippingH(cMPB+BrightWidthTableBH[cMPB]+CDiffBH+VarietyB);

						if(HBrightWidthRL<=kR && kR<=HBrightWidthRH
						&& HBrightWidthGL<=kG && kG<=HBrightWidthGH
						&& HBrightWidthBL<=kB && kB<=HBrightWidthBH){
							GrayDotsM++;
							goto	OkNext;
						}
					}					
					
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
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
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if((kRL<(BrightWidthRL+cAMPLR) || (BrightWidthRH+cAMPHR)<kRH)
						&& (kRL<(BrightWidthRL+cBMPLR) || (BrightWidthRH+cBMPHR)<kRH)){
							goto	NextT1;
						}
						if((kGL<(BrightWidthGL+cAMPLG) || (BrightWidthGH+cAMPHG)<kGH)
						&& (kGL<(BrightWidthGL+cBMPLG) || (BrightWidthGH+cBMPHG)<kGH)){
							goto	NextT1;
						}
						if((kBL<(BrightWidthBL+cAMPLB) || (BrightWidthBH+cAMPHB)<kBH)
						&& (kBL<(BrightWidthBL+cBMPLB) || (BrightWidthBH+cBMPHB)<kBH)){
							goto	NextT1;
						}
						//BYTE	rMLR=cMPLR;
						//BYTE	rMLG=cMPLG;
						//BYTE	rMLB=cMPLB;
						//BYTE	rMHR=cMPHR;
						//BYTE	rMHG=cMPHG;
						//BYTE	rMHB=cMPHB;
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
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
									for(ex=-Len;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										if(0<=(UX+h) && (UX+h)<R->XLen){
											
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else {
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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyR)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
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
										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
										&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
										&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
										&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
										&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
											goto	OkNext2;
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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
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
									for(ex=-Len+1;ex<=Len;ex++,h++){
										int	masterx=X1+xn+ex;
										BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
										BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
										BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
										if(0<=(UX+h) && (UX+h)<R->XLen){
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
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
										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR)
										&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG)
										&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR)
										&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG)
										&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];

								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
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
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR) 
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG) 
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR) 
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG) 
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
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

										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR)
										&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG)
										&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR)
										&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG)
										&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrAHL_Y=R->BuffByMaster[0].BrightHL[UY];
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrBHL_Y=R->BuffByMaster[1].BrightHL[UY];

								int	h=0;
								if(BrAHL_Y!=NULL && BrBHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR)
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG)
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR)
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG)
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else if(BrAHL_Y==NULL && BrBHL_Y==NULL){
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
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR)
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG)
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR)
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG)
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											int	masterx=X1+xn+ex;
											BYTE	tVarietyR=(tVarietyMapR!=NULL)?tVarietyMapR[masterx]:0;
											BYTE	tVarietyG=(tVarietyMapG!=NULL)?tVarietyMapG[masterx]:0;
											BYTE	tVarietyB=(tVarietyMapB!=NULL)?tVarietyMapB[masterx]:0;

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
											if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR)
											&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG)
											&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
												goto	OkNext2;
											}
											if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR)
											&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG)
											&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
												goto	OkNext2;
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

										if((BrightWidthRL+AMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+AMPHR+tVarietyR)
										&& (BrightWidthGL+AMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+AMPHG+tVarietyG)
										&& (BrightWidthBL+AMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+AMPHB+tVarietyB)){
											goto	OkNext2;
										}
										if((BrightWidthRL+BMPLR-tVarietyR)<=kRL && kRH<=(BrightWidthRH+BMPHR+tVarietyR)
										&& (BrightWidthGL+BMPLG-tVarietyG)<=kGL && kGH<=(BrightWidthGH+BMPHG+tVarietyG)
										&& (BrightWidthBL+BMPLB-tVarietyB)<=kBL && kBH<=(BrightWidthBH+BMPHB+tVarietyB)){
											goto	OkNext2;
										}
									}
								}
							}
						}
					}

					double hxL ,hyL ,hzL;
					double hxH ,hyH ,hzH;
					if(MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kRL ,kGL, kBL
										,hxL ,hyL ,hzL)==true
					&& MakeFootPoint3D(  cAMPR,cAMPG,cAMPB
										,cBMPR,cBMPG,cBMPB
										,kRH ,kGH, kBH
										,hxH ,hyH ,hzH)==true){
						BYTE	cMPRL=(BYTE)Clipping(hxL,0.0,255.0);
						BYTE	cMPGL=(BYTE)Clipping(hyL,0.0,255.0);
						BYTE	cMPBL=(BYTE)Clipping(hzL,0.0,255.0);
						BYTE	cMPRH=(BYTE)Clipping(hxH,0.0,255.0);
						BYTE	cMPGH=(BYTE)Clipping(hyH,0.0,255.0);
						BYTE	cMPBH=(BYTE)Clipping(hzH,0.0,255.0);
						BYTE	HBrightWidthRL=ClippingL(cMPRL-BrightWidthTableRL[cMPRL]+CDiffRL-VarietyR);
						BYTE	HBrightWidthRH=ClippingH(cMPRH+BrightWidthTableRH[cMPRH]+CDiffRH+VarietyR);
						BYTE	HBrightWidthGL=ClippingL(cMPGL-BrightWidthTableGL[cMPGL]+CDiffGL-VarietyG);
						BYTE	HBrightWidthGH=ClippingH(cMPGH+BrightWidthTableGH[cMPGH]+CDiffGH+VarietyG);
						BYTE	HBrightWidthBL=ClippingL(cMPBL-BrightWidthTableBL[cMPBL]+CDiffBL-VarietyB);
						BYTE	HBrightWidthBH=ClippingH(cMPBH+BrightWidthTableBH[cMPBH]+CDiffBH+VarietyB);

						if(HBrightWidthRL<=kRL && kRH<=HBrightWidthRH
						&& HBrightWidthGL<=kGL && kGH<=HBrightWidthGH
						&& HBrightWidthBL<=kBL && kBH<=HBrightWidthBH){
							GrayDotsT++;
							goto	OkNext2;
						}
					}					

					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}


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

			//int	CMapX=X1+xn-MasterCx+MCx;
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

			if(EnableM2T==true){
				BYTE	BrightWidthL=ClippingL(cMPL-BrightWidthTableL[cMP]+CDiffL);
				BYTE	BrightWidthH=ClippingH(cMPH+BrightWidthTableH[cMP]+CDiffH);

				{
					//Len==0
					{
						pTP=&rTP[tX];
						BYTE	k=*pTP;
						if(k<BrightWidthL || BrightWidthH<k)
							goto	NextN1;
					}

					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
				}

				for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
					int	ex,ey;
					ey=-Len;
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							goto	OkNext;
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){

						if(TRTBuff.IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TP=TBuff.GetYWithoutDepended(tY+ey);
									BYTE	k=TP[tX+ex];
									if(k<BrightWidthL || BrightWidthH<k){
										continue;
									}
									goto	OkNext;
							//}
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									BYTE	k=TP[tY+ey];
									if(k<BrightWidthL || BrightWidthH<k){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
							//}
							}
						}
					//}
					ey=-Len;
					TP=TBuff.GetYWithoutDepended(tY+ey);
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						//for(ex=Len;ex>-Len;ex--,pTP--){
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
								BYTE	k=*pTP;
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=-Len;ey<Len;ey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=-Len;ey<Len;ey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					ey=-Len;
					TP=TBuff.GetYWithoutDepended(tY+ey);
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						//for(ex=Len;ex>-Len;ex--){
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
			if(EnableT2M==true){
				//if(0<=tY && tY<GetMaxLines() && 0<=(X1+xn+mx) && (X1+xn+mx)<GetDotPerLine()){

					int	cTP=rTP[tX];
					//TP=TBuff.GetYWithoutDepended(tY);
					int	BrightWidthL=-BrightWidthTableL[cTP];
					int	BrightWidthH= BrightWidthTableH[cTP];
					int	kL=cTP-CDiffL;
					int	kH=cTP-CDiffH;
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(kL<(BrightWidthL+cMPL) || (BrightWidthH+cMPH)<kH){
							goto	NextT1;
						}
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
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
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){										
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										//for(ex=-Len;ex<=Len;ex++,h++){
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									//}
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
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
											goto	OkNext2;
										}
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
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									if(0<=(UX+h) && (UX+h)<R->XLen){
										//for(ex=-Len+1;ex<=Len;ex++,h++){
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									//}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPL=BrHL->BrLow[Layer];
											BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									//for(ex=-Len;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											BYTE	MPL=BrHL->BrLow[Layer];
											BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									//}
								}
							}
						}
						ex=Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=-Len;ey<Len;ey++){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
											goto	OkNext2;
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
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								if(BrHL_Y!=NULL){
									for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=&BrHL_Y[UX+h];
											BYTE	MPL=BrHL->BrLow[Layer];
											BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									}
								}
								else{
									//for(ex=-Len+1;ex<=Len;ex++,h++){
										if(0<=(UX+h) && (UX+h)<R->XLen){
											const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
											BYTE	MPL=BrHL->BrLow[Layer];
											BYTE	MPH=BrHL->BrHigh[Layer];
											if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
												goto	OkNext2;
											}
										}
									//}
								}
							}
						}
						ex=-Len;
						//if(0<=(X1+xn+ex) && (X1+xn+ex)<GetDotPerLine()){
						{
							int	UX=X1+xn-MasterCx+MCx+ex;
							if(0<=(UX) && (UX)<R->XLen){
								for(ey=Len;ey>-Len;ey--){
									//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
									int	UY=Y-MasterCy+MCy+ey;
									if(0<UY && UY<R->YLen){
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL)<=kL && kH<=(BrightWidthH+MPH)){
											
											goto	OkNext2;
										}
									}
								}
							}
						}
					}
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}

void	DotColorMatchingItem::CalcInsideMonoWithVariety(const	DotColorMatchingThreshold	*Thr,const DotColorMatchingThreshold::MThreshold *MThr
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
		BYTE	*VarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetY(Y):NULL;

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){
			if(tY==DbgY && (tX)==DbgX)
				DbgCode++;

			//int	CMapX=X1+xn-MasterCx+MCx;
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

			int	Variety=0;
			if(VarietyMap!=NULL)
				Variety=VarietyMap[X1+xn]*Thr->VarietySigma;

			if(EnableM2T==true){
				BYTE	BrightWidthL=ClippingL(cMPL-BrightWidthTableL[cMP]+CDiffL-Variety);
				BYTE	BrightWidthH=ClippingH(cMPH+BrightWidthTableH[cMP]+CDiffH+Variety);

				{
					//Len==0
					{
						pTP=&rTP[tX];
						BYTE	k=*pTP;
						if(k<BrightWidthL || BrightWidthH<k)
							goto	NextN1;
					}

					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
				}

				for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
					int	ex,ey;
					ey=-Len;
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							goto	OkNext;
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){

						if(TRTBuff.IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TP=TBuff.GetYWithoutDepended(tY+ey);
									BYTE	k=TP[tX+ex];
									if(k<BrightWidthL || BrightWidthH<k){
										continue;
									}
									goto	OkNext;
							//}
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									BYTE	k=TP[tY+ey];
									if(k<BrightWidthL || BrightWidthH<k){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
							//}
							}
						}
					//}
					ey=-Len;
					TP=TBuff.GetYWithoutDepended(tY+ey);
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						//for(ex=Len;ex>-Len;ex--,pTP--){
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
								BYTE	k=*pTP;
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=-Len;ey<Len;ey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=-Len;ey<Len;ey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					ey=-Len;
					TP=TBuff.GetYWithoutDepended(tY+ey);
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						//for(ex=Len;ex>-Len;ex--){
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
			if(EnableT2M==true){
				//if(0<=tY && tY<GetMaxLines() && 0<=(X1+xn+mx) && (X1+xn+mx)<GetDotPerLine()){

					int	cTP=rTP[tX];
					//TP=TBuff.GetYWithoutDepended(tY);
					int	BrightWidthL=-BrightWidthTableL[cTP];
					int	BrightWidthH= BrightWidthTableH[cTP];
					int	kL=cTP-CDiffL;
					int	kH=cTP-CDiffH;
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(kL<(BrightWidthL+cMPL) || (BrightWidthH+cMPH)<kH){
							goto	NextT1;
						}
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;

							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								for(ex=-Len;ex<=Len;ex++,h++){
									int	masterx=X1+xn+ex;
									const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									BYTE	MPL=BrHL->BrLow[Layer];
									BYTE	MPH=BrHL->BrHigh[Layer];
									if(0<=(UX+h) && (UX+h)<R->XLen){
										
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;
										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										
										BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;
	
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
										}
									}
								}
							}
						}
						ey=Len;
						{
							BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								for(ex=-Len+1;ex<=Len;ex++,h++){
									int	masterx=X1+xn+ex;
									const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;
									BYTE	MPL=BrHL->BrLow[Layer];
									BYTE	MPH=BrHL->BrHigh[Layer];
									if(0<=(UX+h) && (UX+h)<R->XLen){
										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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

										BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;
	
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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
								BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								for(ex=-Len;ex<=Len;ex++,h++){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										int	masterx=X1+xn+ex;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;

										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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

										BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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
								BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								for(ex=-Len+1;ex<=Len;ex++,h++){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										int	masterx=X1+xn+ex;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;

										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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

										BYTE	*tVarietyMap=(AP->VarietyMap[0].IsValid()==true)?AP->VarietyMap[Layer].GetYDirectly(Y+ey):NULL;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]*Thr->VarietySigma:0;

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL-tVariety)<=kL && kH<=(BrightWidthH+MPH+tVariety)){
											
											goto	OkNext2;
										}
									}
								}
							}
						}
					}
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}

/*
void	DotColorMatchingItem::CalcInsideMono2(ImageBufferFast &TBuff ,ImageBuffer &TRTBuff
									,int Layer
									,int mx ,int my
									,int Skip ,int SelfSearch ,int CDiff ,int NoiseBrightness
									,int MapXPoint ,int MapYPoint
									,int &NGCount1
									,int &NGCount2)
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
		ThresholdL=Clipping((int)(Thr->BrightWidthRL*Mult-Thr->BrightWidthRL*Thr->AddedBrightness*0.2),0,255);
		ThresholdH=Clipping((int)(Thr->BrightWidthRH*Mult-Thr->BrightWidthRH*Thr->AddedBrightness*0.2),0,255);
	}
	else
	if(Layer==1){
		ThresholdL=Clipping((int)(Thr->BrightWidthGL*Mult-Thr->BrightWidthGL*Thr->AddedBrightness*0.2),0,255);
		ThresholdH=Clipping((int)(Thr->BrightWidthGH*Mult-Thr->BrightWidthGH*Thr->AddedBrightness*0.2),0,255);
	}
	else
	if(Layer==2){
		ThresholdL=Clipping((int)(Thr->BrightWidthBL*Mult-Thr->BrightWidthBL*Thr->AddedBrightness*0.2),0,255);
		ThresholdH=Clipping((int)(Thr->BrightWidthBH*Mult-Thr->BrightWidthBH*Thr->AddedBrightness*0.2),0,255);
	}

	__TableType	*CompBrightWidthTableL;
	__TableType	*CompBrightWidthTableH;
	if(Layer==0){
		CompBrightWidthTableL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(Thr->RThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		CompBrightWidthTableH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(Thr->RThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==1){
		CompBrightWidthTableL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(Thr->GThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		CompBrightWidthTableH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(Thr->GThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==2){
		CompBrightWidthTableL=AP->BrightWidthTableComp[MaxThreOffset+Clipping(Thr->BThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		CompBrightWidthTableH=AP->BrightWidthTableComp[MaxThreOffset+Clipping(Thr->BThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	__TableType	*FlatBrightWidthTableL;
	__TableType	*FlatBrightWidthTableH;
	if(Layer==0){
		FlatBrightWidthTableL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(Thr->RThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		FlatBrightWidthTableH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(Thr->RThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==1){
		FlatBrightWidthTableL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(Thr->GThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		FlatBrightWidthTableH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(Thr->GThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
	}
	else
	if(Layer==2){
		FlatBrightWidthTableL=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(Thr->BThrOffsetL-Thr->AddedOffset*3,-100,100)][ThresholdL];
		FlatBrightWidthTableH=AP->BrightWidthTableFlat[MaxThreOffset+Clipping(Thr->BThrOffsetH-Thr->AddedOffset*3,-100,100)][ThresholdH];
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
		BYTE	*rTP=TBuff.GetYWithoutDepended(tY);
		BYTE	*FlatTypeMapY=R->FlatTypeMap[CMapY];
		BYTE	*VarietyMap=AP->VarietyMap[Layer].GetY(Y);

		int	tX=X1+mx;
		int	CMapX=X1-MasterCx+MCx;
		for(int xn=0;xn<Numb;xn++,tX++,CMapX++){
			if(tY==DbgY && (tX)==DbgX)
				DbgCode++;

			//int	CMapX=X1+xn-MasterCx+MCx;
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

			int	Variety=0;
			if(VarietyMap!=NULL)
				Variety=VarietyMap[X1+xn]*Thr->VarietySigma;

			if(EnableM2T==true){
				BYTE	BrightWidthL=ClippingL(cMPL-BrightWidthTableL[cMP]+CDiff-Variety);
				BYTE	BrightWidthH=ClippingH(cMPH+BrightWidthTableH[cMP]+CDiff+Variety);

				{
					//Len==0
					{
						pTP=&rTP[tX];
						BYTE	k=*pTP;
						if(k<BrightWidthL || BrightWidthH<k)
							goto	NextN1;
					}

					//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
						goto	OkNext;
					NextN1:;
				}

				for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
					int	ex,ey;
					ey=-Len;
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							goto	OkNext;
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){

						if(TRTBuff.IsNull()==true){
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									TP=TBuff.GetYWithoutDepended(tY+ey);
									BYTE	k=TP[tX+ex];
									if(k<BrightWidthL || BrightWidthH<k){
										continue;
									}
									goto	OkNext;
							//}
							}
						}
						else{
							TP=TRTBuff.GetYWithoutDepended(tX+ex);
							for(ey=-Len;ey<Len;ey++){
								//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
									BYTE	k=TP[tY+ey];
									if(k<BrightWidthL || BrightWidthH<k){
										continue;
									}
									//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
										goto	OkNext;
									//}
							//}
							}
						}
					//}
					ey=-Len;
					TP=TBuff.GetYWithoutDepended(tY+ey);
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						//for(ex=Len;ex>-Len;ex--,pTP--){
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
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
						TP=TBuff.GetYWithoutDepended(tY+ey);
						pTP=&TP[tX-Len];
						for(ex=-Len;ex<=Len;ex++,pTP++){
							//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
								BYTE	k=*pTP;
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					//}
					ex=Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=-Len;ey<Len;ey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=-Len;ey<Len;ey++){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					ey=-Len;
					TP=TBuff.GetYWithoutDepended(tY+ey);
					//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
						//for(ex=Len;ex>-Len;ex--){
						pTP=&TP[tX-Len+1];
						for(ex=-Len+1;ex<=Len;ex++,pTP++){
							BYTE	k=*pTP;
							if(k<BrightWidthL || BrightWidthH<k){
								continue;
							}
							//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
								goto	OkNext;
							//}
						}
					//}
					ex=-Len;
					//if(0<=(X1+xn+mx+ex) && (X1+xn+mx+ex)<GetDotPerLine()){
					if(TRTBuff.IsNull()==true){
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								TP=TBuff.GetYWithoutDepended(tY+ey);
								BYTE	k=TP[tX+ex];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
					else{
						TP=TRTBuff.GetYWithoutDepended(tX+ex);
						for(ey=Len;ey>-Len;ey--){
							//if(0<=(Y+my+ey) && (Y+my+ey)<GetMaxLines()){
								BYTE	k=TP[tY+ey];
								if(k<BrightWidthL || BrightWidthH<k){
									continue;
								}
								//if(BrightWidthRL<=kR && kR<=BrightWidthRH && BrightWidthGL<=kG && kG<=BrightWidthGH && BrightWidthBL<=kB && kB<=BrightWidthBH){
									goto	OkNext;
								//}
							//}
						}
					}
				}
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine && 0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				}
				NGCount1++;
				continue;
			}
OkNext:;
			if(EnableT2M==true){
				//if(0<=tY && tY<GetMaxLines() && 0<=(X1+xn+mx) && (X1+xn+mx)<GetDotPerLine()){

					int	cTP=rTP[tX];
					//TP=TBuff.GetYWithoutDepended(tY);
					int	BrightWidthL=-BrightWidthTableL[cTP];
					int	BrightWidthH= BrightWidthTableH[cTP];
					int	k=cTP-CDiff;
					//BYTE	*MPLR;
					//BYTE	*MPLG;
					//BYTE	*MPLB;
					//BYTE	*MPHR;
					//BYTE	*MPHG;
					//BYTE	*MPHB;

					{
						//Len==0

						if(k<(BrightWidthL+cMPL) || (BrightWidthH+cMPH)<k){
							goto	NextT1;
						}
						//if((BrightWidthRL+rMLR)<=kR && kR<=(BrightWidthRH+rMHR) && (BrightWidthGL+rMLG)<=kG && kG<=(BrightWidthGH+rMHG) && (BrightWidthBL+rMLB)<=kB && kB<=(BrightWidthBH+rMHB)){
							goto	OkNext2;
						NextT1:;
						//}
					}

					for(int	Len=Skip;Len<=SelfSearch;Len+=Skip){
						int	ex,ey;
						ey=-Len;
						//if(0<=(Y+ey) && (Y+ey)<GetMaxLines()){
						{
							BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);

							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								for(ex=-Len;ex<=Len;ex++,h++){
									int	masterx=X1+xn+ex;
									const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									BYTE	MPL=BrHL->BrLow[Layer];
									BYTE	MPH=BrHL->BrHigh[Layer];
									if(0<=(UX+h) && (UX+h)<R->XLen){
										
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;
										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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
										const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										
										BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;
	
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
										}
									}
								}
							}
						}
						ey=Len;
						{
							BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
							int	UY=Y-MasterCy+MCy+ey;
							int	UX=X1+xn-MasterCx+MCx-Len+1;
							if(0<UY && UY<R->YLen){
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];
								int	h=0;
								for(ex=-Len+1;ex<=Len;ex++,h++){
									int	masterx=X1+xn+ex;
									const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
									BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;
									BYTE	MPL=BrHL->BrLow[Layer];
									BYTE	MPH=BrHL->BrHigh[Layer];
									if(0<=(UX+h) && (UX+h)<R->XLen){
										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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

										BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;
	
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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
								BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								for(ex=-Len;ex<=Len;ex++,h++){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										int	masterx=X1+xn+ex;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;

										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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

										BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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
								BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
								const	struct	BMatrixBrightHL::BrightHLStruct	*BrHL_Y=R->BuffByMaster[0].BrightHL[UY];

								int	h=0;
								for(ex=-Len+1;ex<=Len;ex++,h++){
									if(0<=(UX+h) && (UX+h)<R->XLen){
										int	masterx=X1+xn+ex;
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;

										const struct	BMatrixBrightHL::BrightHLStruct	*BrHL=(BrHL_Y!=NULL)?&BrHL_Y[UX+h]:R->BuffByMaster[0].BrightHL.GetConstantBrightness(UY);
										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];
										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
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

										BYTE	*tVarietyMap=AP->VarietyMap[Layer].GetYDirectly(Y+ey);
										BYTE	tVariety=(tVarietyMap!=NULL)?tVarietyMap[masterx]:0;

										BYTE	MPL=BrHL->BrLow[Layer];
										BYTE	MPH=BrHL->BrHigh[Layer];

										if((BrightWidthL+MPL-tVariety)<=k && k<=(BrightWidthH+MPH+tVariety)){
											goto	OkNext2;
										}
									}
								}
							}
						}
					}
					SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
				//}
				NGCount2++;
			}
OkNext2:;
		}
	}
}
*/