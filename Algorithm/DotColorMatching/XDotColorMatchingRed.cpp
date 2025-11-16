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
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatchingAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XLearningRegist.h"

void	DotColorMatchingItem::GetDetectRedRange(BYTE r,BYTE g,BYTE b
												,short &RedRL,short &RedRH
												,short &RedGL,short &RedGH
												,short &RedBL,short &RedBH)
{
	const	DotColorMatchingThreshold	*Th=GetThresholdR();
	int		RedGBMerginRate	=Th->RedGBMerginRate*256/100;
	int		RedHighRate		=Th->RedHighRate*256/100;

	RedRL=Th->RedMinBrightness;
	RedGL=((g-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
	RedBL=((b-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
	RedGH=((g+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
	RedBH=((b+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
	RedRH=((g+b)*RedHighRate)>>9;
}

int	DotColorMatchingItem::ExecuteProcessingRed(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int &NGSize
								, int& ResultX, int& ResultY
								, int OffsetX ,int OffsetY)
{
	int	Mx,My;
	GetAlignmentShift(Mx,My);
	Mx+=OffsetX;
	My+=OffsetY;

	const	DotColorMatchingThreshold	*Th=GetThresholdR();
	int	MapXPoint	=CurrentMasterPattern->GetMinX()-8;
	int	MapYPoint	=CurrentMasterPattern->GetMinY()-8;
	int	DotPerLine	=CurrentMasterPattern->DotPerLine;
	int	MaxLines	=CurrentMasterPattern->MaxLines;

	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int		MCx=CurrentMasterPattern->XLen/2;
	int		MCy=CurrentMasterPattern->YLen/2;
	NGSize	=0;
	int		RedGBMerginRate	=Th->RedGBMerginRate*256/100;
	int		RedHighRate		=Th->RedHighRate*256/100;

	int	N=CurrentMasterPattern->GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y =CurrentMasterPattern->GetFLineAbsY(i);
		int	X1=CurrentMasterPattern->GetFLineLeftX(i);
		int	Numb=CurrentMasterPattern->GetFLineNumb(i);
		int	CMapY=Y -MasterCy+MCy;
		int	CMapX=X1-MasterCx+MCx;
		int	tY=Y+My;
		if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines && 0<=tY && tY<ImageTargetList[0]->GetHeight()){
			BYTE	*sR=ImageTargetList[0]->GetY(tY);
			BYTE	*sG=ImageTargetList[1]->GetY(tY);
			BYTE	*sB=ImageTargetList[2]->GetY(tY);

			int	x1=max(0,-X1+MapXPoint);
			int	x2=min(Numb,DotPerLine-X1+MapXPoint);

			CMapX+=x1;
			for(int xn=x1;xn<x2;xn++,CMapX++){
				BYTE	r=sR[X1+Mx+xn];
				if(r>=Th->RedMinBrightness){
					BYTE	g=sG[X1+Mx+xn];
					BYTE	b=sB[X1+Mx+xn];
					int	gL=((g-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
					int	bL=((b-Th->RedGBMerginOffset)*(256-RedGBMerginRate))>>8;
					if(gL<=b  || bL<=g){
						int	gH=((g+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
						int	bH=((b+Th->RedGBMerginOffset)*(256+RedGBMerginRate))>>8;
						if((gL<=b && b<gH) || (bL<=g && g<=bH)){
							int	rL=((g+b)*RedHighRate)>>9;
							if(r>=rL){
								if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine){
									SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
									NGSize++;
								}
							}
						}
					}
				}
			}
		}
	}
	if(Th->Clusterize==false 
	&& NGSize<Th->RedOKDot){
		Res->SetAlignedXY(Mx,My);
		ResultDx=Mx;
		ResultDy=My;
		ResultCode=1;
		Res->SetResult1(NGSize);
		Res->SetError(1);
					//OK
		return 1;
	}
	else{
		if(Th->Clusterize==true){
			PureFlexAreaListContainer FPack;
			if(Th->RedShrink!=0){
				BYTE	TmpBuff[10000];
				BYTE	**TmpMap=MakeMatrixBuff(MapXByte,MapYLen,TmpBuff,sizeof(TmpBuff));
				GetLayersBase()->ThinAreaN(Map,TmpMap,MapXByte,MapYLen,Th->RedShrink);
				DeleteMatrixBuff(TmpMap,TmpBuff,MapYLen);
			}
			PickupFlexArea(Map,MapXByte,MapXByte<<3,MapYLen,FPack);

			int64	NGCount=0;
			int64	NGDots=0;
			ResultPosListContainer	NowList;

			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
				{				
					int64	Dots=p->GetPatternByte();
					if(Dots>Th->RedOKDot){
						int	Cx,Cy;
						p->MoveToNoClip(MapXPoint,MapYPoint);
						p->GetCenter(Cx,Cy);
						ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
						r->result =0x10000+0x500;	//Red-NG
						r->SetResult1(Dots);
						r->SetResult2(0);
						r->NGShape.SuckFrom(*p);
						r->NGSize=Dots;
						NowList.AppendList(r);
						NGCount++;
						NGDots+=Dots;
					}
				}
			}
			Res->MovePosList(NowList);
			Res->SetItemSearchedXY(0,0);
			if(NGCount>0){
				Res->SetAlignedXY(Mx,My);
				ResultDx=Mx;
				ResultDy=My;
				ResultCode=5;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetError(5);
				return 2;				//NG
			}
			else{
				Res->SetAlignedXY(Mx,My);
				ResultDx=Mx;
				ResultDy=My;
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetError(1);
				return 1;				//OK
			}
		}
		else{
			int64	NGCount=::GetBitCount((const BYTE **)Map,MapXByte,MapYLen);
			if(NGCount>Th->RedOKDot){
				int	Cx,Cy;
				GetCenter(Cx,Cy);
				ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
				r->SetResultCode (0x10000+0x500);	//Red-NG
				r->SetResult1(NGCount);
				r->NGSize=NGCount;
				ResultPosListContainer	NowList;
				NowList.AppendList(r);
				Res->MovePosList(NowList);
				Res->SetItemSearchedXY(0,0);
				
				Res->SetAlignedXY(Mx,My);
				ResultDx=Mx;
				ResultDy=My;
				ResultCode=5;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				Res->SetError(5);
				return 2;			//NG
			}
			else{
				Res->SetAlignedXY(Mx,My);
				ResultDx=Mx;
				ResultDy=My;
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				Res->SetError(1);
				return 1;			//OK
			}
		}
	}
}