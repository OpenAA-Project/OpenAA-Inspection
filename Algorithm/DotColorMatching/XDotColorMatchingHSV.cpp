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

int	DotColorMatchingItem::ExecuteProcessingHSV(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int &NGSize
								, int dx,int dy
								, int& ResultX, int& ResultY
								, bool EnableClusterize)
{
	if(CurrentMasterPattern->HSVMaster==NULL){
		return 1;
	}
	if(SubBlock.GetCount()!=0){
		return ExecuteProcessingHSV2(Res
								, ImageTargetList
								, NGSize
								, dx,dy
								, ResultX, ResultY
								, EnableClusterize);
	}
	int	Mx,My;
	//GetAlignmentShift(Mx,My);
	Mx=ResultDx+dx;
	My=ResultDy+dy;
	DotColorMatchingInPage	*PPage=(DotColorMatchingInPage	*)GetParentInPage();

	const	DotColorMatchingThreshold	*Thr=GetThresholdR();
	int	MapXPoint	=CurrentMasterPattern->GetMinX()-8;
	int	MapYPoint	=CurrentMasterPattern->GetMinY()-8;
	int	DotPerLine	=CurrentMasterPattern->DotPerLine;
	int	MaxLines	=CurrentMasterPattern->MaxLines;

	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int		MCx=CurrentMasterPattern->XLen/2;
	int		MCy=CurrentMasterPattern->YLen/2;
	NGSize	=0;

	DotColorMatchingInPage::HSVTableClass	*HSVTablePoint=PPage->HSVTablePoint;

	int	N=CurrentMasterPattern->GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y =CurrentMasterPattern->GetFLineAbsY(i);
		if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
			int	X1=CurrentMasterPattern->GetFLineLeftX(i);
			int	Numb=CurrentMasterPattern->GetFLineNumb(i);
			int	CMapY=Y -MasterCy+MCy;
			int	CMapX=X1-MasterCx+MCx;
			BYTE	*sR=ImageTargetList[0]->GetY(Y+My);
			BYTE	*sG=ImageTargetList[1]->GetY(Y+My);
			BYTE	*sB=ImageTargetList[2]->GetY(Y+My);

			int	x1=max(0,-X1+MapXPoint);
			int	x2=min(Numb,DotPerLine-X1+MapXPoint);
			struct HSVValue	*HSV_YTable=CurrentMasterPattern->HSVMaster[CMapY];
			CMapX+=x1;
			for(int xn=x1;xn<x2;xn++,CMapX++){
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine){
					BYTE	r=sR[X1+Mx+xn];
					BYTE	g=sG[X1+Mx+xn];
					BYTE	b=sB[X1+Mx+xn];
					double	Th,Ts ,Tv;
					::RGB2HSV(Th,Ts ,Tv ,r ,g ,b);

					int	cMPH=HSV_YTable[CMapX].H;
					int	cMPS=HSV_YTable[CMapX].S;
					int	cMPV=HSV_YTable[CMapX].V;
					
					int	MHL=HSVTablePoint->HSV_HLTable[cMPH][Thr->HsvPHL][Thr->HsvDHL];
					int	MHH=HSVTablePoint->HSV_HHTable[cMPH][Thr->HsvPHH][Thr->HsvDHH];
					int	MSL=HSVTablePoint->HSV_SVLTable[cMPS][Thr->HsvPSL][Thr->HsvDSL];
					int	MSH=HSVTablePoint->HSV_SVHTable[cMPS][Thr->HsvPSH][Thr->HsvDSH];
					int	MVL=HSVTablePoint->HSV_SVLTable[cMPV][Thr->HsvPVL][Thr->HsvDVL];
					int	MVH=HSVTablePoint->HSV_SVHTable[cMPV][Thr->HsvPVH][Thr->HsvDVH];


					if(((MHL<=MHH && (Th<MHL || MHH<Th)) || (MHL>MHH && (Th<MHL && MHH<Th)))
					|| (Ts<MSL || MSH<Ts)
					|| (Tv<MVL || MVH<Tv)){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
						NGSize++;
					}
				}
			}
		}
	}

	if(Thr->Clusterize==false 
	&& NGSize<Thr->HsvOKDot){
		Res->SetAlignedXY(Mx,My);
		if(EnableClusterize==true){
			ResultDx=Mx;
			ResultDy=My;
		}
		ResultCode=1;
		Res->SetResult1(NGSize);
		Res->SetResult2(NGSize);
		Res->SetError(1);
					//OK
		return 1;
	}
	else{
		if(Thr->Clusterize==true){
			BYTE	DummyMap[100000];
			BYTE	**TmpMap=MakeMatrixBuff(MapXByte,MapYLen,DummyMap,sizeof(DummyMap));
			ThinArea(Map,TmpMap,MapXByte,MapYLen);
			FatAreaN(Map,TmpMap,MapXByte,MapYLen,2);
			DeleteMatrixBuff(TmpMap,DummyMap,MapYLen);

			PureFlexAreaListContainer FPack;
			PickupFlexArea(Map,MapXByte,MapXByte<<3,MapYLen,FPack);

			int64	NGCount=0;
			int64	NGDots=0;
			ResultPosListContainer	NowList;

			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
				{				
					int64	Dots=p->GetPatternByte();
					if(Dots>Thr->HsvOKDot){
						if(EnableClusterize==true){
							int	Cx,Cy;
							p->MoveToNoClip(MapXPoint,MapYPoint);
							p->GetCenter(Cx,Cy);
							ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
							r->result =0x10000+0x600;	//HSV-NG-Dot
							r->SetResult1(Dots);
							r->SetResult2(0);
							r->NGShape.SuckFrom(*p);
							r->NGSize=Dots;
							NowList.AppendList(r);
						}
						NGCount++;
						NGDots+=Dots;
					}
					double	Len=hypot(p->GetWidth(),p->GetHeight());
					if(Len>Thr->HsvOKLength){
						if(EnableClusterize==true){
							int	Cx,Cy;
							p->MoveToNoClip(MapXPoint,MapYPoint);
							p->GetCenter(Cx,Cy);
							ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
							r->result =0x10000+0x700;	//HSV-NG-Length
							r->SetResult1(Len);
							r->SetResult2(0);
							r->NGShape.SuckFrom(*p);
							r->NGSize=Dots;
							NowList.AppendList(r);
						}
						NGCount++;
						NGDots+=Dots;
					}
				}
			}
			if(EnableClusterize==true){
				Res->MovePosList(NowList);
				Res->SetItemSearchedXY(0,0);
			}
			if(NGCount>0){
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=5;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetError(5);
				return 2;				//NG
			}
			else{
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetError(1);
				return 1;				//OK
			}
		}
		else{
			int64	NGCount=::GetBitCount((const BYTE **)Map,MapXByte,MapYLen);
			if(NGCount>Thr->HsvOKDot){
				if(EnableClusterize==true){
					int	Cx,Cy;
					GetCenter(Cx,Cy);
					ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
					r->SetResultCode (0x10000+0x600);	//HSV-NG-Dot
					r->SetResult1(NGCount);
					r->NGSize=NGCount;
					ResultPosListContainer	NowList;
					NowList.AppendList(r);
					Res->MovePosList(NowList);
					Res->SetItemSearchedXY(0,0);
				}
				
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=5;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				Res->SetError(5);
				return 2;			//NG
			}
			else{
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				Res->SetError(1);
				return 1;			//OK
			}
		}
	}
}


int	DotColorMatchingItem::ExecuteProcessingHSV2(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int &NGSize
								, int dx,int dy
								, int& ResultX, int& ResultY
								, bool EnableClusterize)
{
	if(CurrentMasterPattern->HSVMaster==NULL){
		return 1;
	}
	int	Mx,My;
	//GetAlignmentShift(Mx,My);
	Mx=ResultDx+dx;
	My=ResultDy+dy;
	DotColorMatchingInPage	*PPage=(DotColorMatchingInPage	*)GetParentInPage();
	DotColorMatchingInPage::HSVTableClass	*HSVTablePoint=PPage->HSVTablePoint;

	const	DotColorMatchingThreshold	*Thr=GetThresholdR();
	int	MapXPoint	=CurrentMasterPattern->GetMinX()-8;
	int	MapYPoint	=CurrentMasterPattern->GetMinY()-8;
	int	DotPerLine	=CurrentMasterPattern->DotPerLine;
	int	MaxLines	=CurrentMasterPattern->MaxLines;

	MatrixBuffClear(Map		,0,MapXByte,MapYLen);
	int		MCx=CurrentMasterPattern->XLen/2;
	int		MCy=CurrentMasterPattern->YLen/2;
	NGSize	=0;

	int	N=CurrentMasterPattern->GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y =CurrentMasterPattern->GetFLineAbsY(i);
		if(0<=(Y-MapYPoint) && (Y-MapYPoint)<MaxLines){
			int	X1=CurrentMasterPattern->GetFLineLeftX(i);
			int	Numb=CurrentMasterPattern->GetFLineNumb(i);
			int	CMapY=Y -MasterCy+MCy;
			int	CMapX=X1-MasterCx+MCx;
			BYTE	*sR=ImageTargetList[0]->GetY(Y+My);
			BYTE	*sG=ImageTargetList[1]->GetY(Y+My);
			BYTE	*sB=ImageTargetList[2]->GetY(Y+My);

			int	x1=max(0,-X1+MapXPoint);
			int	x2=min(Numb,DotPerLine-X1+MapXPoint);
			struct HSVValue	*HSV_YTable=CurrentMasterPattern->HSVMaster[CMapY];
			CMapX+=x1;
			for(int xn=x1;xn<x2;xn++,CMapX++){
				if(0<=(X1+xn-MapXPoint) && (X1+xn-MapXPoint)<DotPerLine){

					for(SubtractItem *s=SubBlock.GetFirst();s!=NULL;s=s->GetNext()){
						DotColorMatchingItem	*SItem=(DotColorMatchingItem *)s->IndexAfterEdit;
						//SItem‚ÌŠJŽnÀ•W
						int	Sy=SItem->CurrentMasterPattern->GetMinY();
						int	YMergin=(SItem->CurrentMasterPattern->YLen-SItem->CurrentMasterPattern->GetHeight())/2;
						int	sy=(Y+My)-(Sy+SItem->ResultDy)+YMergin;
						if(0<=sy && sy<SItem->CurrentMasterPattern->YLen){
							int	Sx=SItem->CurrentMasterPattern->GetMinX();
							int	XMergin=(SItem->CurrentMasterPattern->XLen-SItem->CurrentMasterPattern->GetWidth())/2;
							int	sx=(X1+Mx+xn)-(Sx+SItem->ResultDx)+XMergin;
							if(0<=sx && sx<SItem->CurrentMasterPattern->XLen){
								if(GetBmpBit(SItem->CurrentMasterPattern->SubtractionMap,sx,sy)!=0){
									goto	MaskedEnd1;
								}
							}
						}
					}

					BYTE	r=sR[X1+Mx+xn];
					BYTE	g=sG[X1+Mx+xn];
					BYTE	b=sB[X1+Mx+xn];
					double	Th,Ts ,Tv;
					::RGB2HSV(Th,Ts ,Tv ,r ,g ,b);

					int	cMPH=HSV_YTable[CMapX].H;
					int	cMPS=HSV_YTable[CMapX].S;
					int	cMPV=HSV_YTable[CMapX].V;
					
					int	MHL=HSVTablePoint->HSV_HLTable[cMPH][Thr->HsvPHL][Thr->HsvDHL];
					int	MHH=HSVTablePoint->HSV_HHTable[cMPH][Thr->HsvPHH][Thr->HsvDHH];
					int	MSL=HSVTablePoint->HSV_SVLTable[cMPS][Thr->HsvPSL][Thr->HsvDSL];
					int	MSH=HSVTablePoint->HSV_SVHTable[cMPS][Thr->HsvPSH][Thr->HsvDSH];
					int	MVL=HSVTablePoint->HSV_SVLTable[cMPV][Thr->HsvPVL][Thr->HsvDVL];
					int	MVH=HSVTablePoint->HSV_SVHTable[cMPV][Thr->HsvPVH][Thr->HsvDVH];


					if(((MHL<=MHH && (Th<MHL || MHH<Th)) || (MHL>MHH && (Th<MHL && MHH<Th)))
					|| (Ts<MSL || MSH<Ts)
					|| (Tv<MVL || MVH<Tv)){
						SetBmpBit1(Map,X1+xn-MapXPoint,Y-MapYPoint);
						NGSize++;
					}
				}
				MaskedEnd1:;
			}
		}
	}

	if(Thr->Clusterize==false 
	&& NGSize<Thr->HsvOKDot){
		Res->SetAlignedXY(Mx,My);
		if(EnableClusterize==true){
			ResultDx=Mx;
			ResultDy=My;
		}
		ResultCode=1;
		Res->SetResult1(NGSize);
		Res->SetResult2(NGSize);
		Res->SetError(1);
					//OK
		return 1;
	}
	else{
		if(Thr->Clusterize==true){
			BYTE	DummyMap[100000];
			BYTE	**TmpMap=MakeMatrixBuff(MapXByte,MapYLen,DummyMap,sizeof(DummyMap));
			ThinArea(Map,TmpMap,MapXByte,MapYLen);
			FatAreaN(Map,TmpMap,MapXByte,MapYLen,2);
			DeleteMatrixBuff(TmpMap,DummyMap,MapYLen);

			PureFlexAreaListContainer FPack;
			PickupFlexArea(Map,MapXByte,MapXByte<<3,MapYLen,FPack);

			int64	NGCount=0;
			int64	NGDots=0;
			ResultPosListContainer	NowList;

			for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
				{				
					int64	Dots=p->GetPatternByte();
					if(Dots>Thr->HsvOKDot){
						if(EnableClusterize==true){
							int	Cx,Cy;
							p->MoveToNoClip(MapXPoint,MapYPoint);
							p->GetCenter(Cx,Cy);
							ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
							r->result =0x10000+0x600;	//HSV-NG-Dot
							r->SetResult1(Dots);
							r->SetResult2(0);
							r->NGShape.SuckFrom(*p);
							r->NGSize=Dots;
							NowList.AppendList(r);
						}
						NGCount++;
						NGDots+=Dots;
					}
					double	Len=hypot(p->GetWidth(),p->GetHeight());
					if(Len>Thr->HsvOKLength){
						if(EnableClusterize==true){
							int	Cx,Cy;
							p->MoveToNoClip(MapXPoint,MapYPoint);
							p->GetCenter(Cx,Cy);
							ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
							r->result =0x10000+0x700;	//HSV-NG-Length
							r->SetResult1(Len);
							r->SetResult2(0);
							r->NGShape.SuckFrom(*p);
							r->NGSize=Dots;
							NowList.AppendList(r);
						}
						NGCount++;
						NGDots+=Dots;
					}
				}
			}
			if(EnableClusterize==true){
				Res->MovePosList(NowList);
				Res->SetItemSearchedXY(0,0);
			}
			if(NGCount>0){
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=5;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetError(5);
				return 2;				//NG
			}
			else{
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGDots);
				Res->SetError(1);
				return 1;				//OK
			}
		}
		else{
			int64	NGCount=::GetBitCount((const BYTE **)Map,MapXByte,MapYLen);
			if(NGCount>Thr->HsvOKDot){
				if(EnableClusterize==true){
					int	Cx,Cy;
					GetCenter(Cx,Cy);
					ResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
					r->SetResultCode(0x10000+0x600);	//HSV-NG-Dot
					r->SetResult1(NGCount);
					r->NGSize=NGCount;
					ResultPosListContainer	NowList;
					NowList.AppendList(r);
					Res->MovePosList(NowList);
					Res->SetItemSearchedXY(0,0);
				}
				
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=5;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				Res->SetError(5);
				return 2;			//NG
			}
			else{
				Res->SetAlignedXY(Mx,My);
				if(EnableClusterize==true){
					ResultDx=Mx;
					ResultDy=My;
				}
				ResultCode=1;
				Res->SetResult1(NGCount);
				Res->SetResult2(NGCount);
				Res->SetError(1);
				return 1;			//OK
			}
		}
	}
}