/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlignmentAutoGenerate.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAlignmentLargeResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentLarge.h"
#include "XCrossObj.h"
#include "XPointer.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XImageProcess.h"
#include "XPacketAlignmentLarge.h"
#include "XDataAlgorithmConfirm.h"
#include <omp.h>

bool	XAlignmentLargeArea::GenerateAuto(void)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();

	ConstMapBuffer MaskMap;
	AlgorithmLibrary *Lib=NULL;
	ParentInLayer->GetReflectionMap(_Reflection_Mask,MaskMap,Lib);
	PureFlexAreaListContainer FMaskPack;
	::PickupFlexArea(MaskMap.GetBitMap(),MaskMap.GetXByte(),MaskMap.GetXLen(),MaskMap.GetYLen(),FMaskPack);
	FlexArea	AllMaskArea;
	for(PureFlexAreaList *f=FMaskPack.GetFirst();f!=NULL;f=f->GetNext()){
		AllMaskArea+=*f;
	}

	GenerationAreas.RemoveAll();
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();

	int	Nx=(W+ABase->AutoGenAreaSize-1)/ABase->AutoGenAreaSize;
	int	Ny=(H+ABase->AutoGenAreaSize-1)/ABase->AutoGenAreaSize;

	int	Wn=GetArea().GetWidth()/Nx;
	int	Hn=GetArea().GetHeight()/Ny;

	for(int ky=0;ky<Ny;ky++){
		for(int kx=0;kx<Nx;kx++){
			int	Gx=kx*Wn+GetArea().GetMinX();
			int	Gy=ky*Hn+GetArea().GetMinY();

			if(GetArea().CheckOverlapRectangle(Gx ,Gy ,Gx+Wn,Gy+Hn)==true
			&& AllMaskArea.CheckOverlapRectangle(Gx ,Gy ,Gx+Wn,Gy+Hn)==true){
				FlexArea	GArea;
				GArea.SetRectangle(Gx ,Gy ,Gx+Wn,Gy+Hn);
				FlexArea	OutArea=GArea;
				OutArea-=GetArea();
				if(OutArea.GetPatternByte()<Wn*Hn*0.2){
					int			tLayer;
					FlexArea	tArea;

					RectClass	*s=new RectClass(Gx ,Gy ,Gx+Wn,Gy+Hn);
					GenerationAreas.AppendList(s);

					if(GenerateAuto(GArea,tLayer,tArea,AllMaskArea)==true){
						GenerateAutoAddItem(tLayer ,tArea);
					}
				}
			}
		}
	}
	LNext:;
	for(AlgorithmItemPLI *a=ParentInLayer->GetFirstData();a!=NULL;a=a->GetNext()){
		XAlignmentLarge	*AItem=dynamic_cast<XAlignmentLarge *>(a);
		if(AItem!=NULL && AItem->AreaID==AreaID){
			int	ACx,ACy;
			AItem->GetCenter(ACx,ACy);
			for(AlgorithmItemPLI *b=a->GetNext();b!=NULL;b=b->GetNext()){
				XAlignmentLarge	*BItem=dynamic_cast<XAlignmentLarge *>(b);
				if(BItem!=NULL && BItem->AreaID==AreaID){
					int	BCx,BCy;
					BItem->GetCenter(BCx,BCy);
					double	Distance=hypot(ACx-BCx,ACy-BCy);
					if(Distance<ABase->AutoGenMinDistance){
						ParentInLayer->RemoveItem(BItem);
						goto	LNext;
					}
				}
			}
		}
	}

	return true;
}

struct StructGenerateAuto
{
	int Layer;
	int	x;
	int	xi;
	int	y;
	int	yi;
	double	Var;
};

int	FuncSList(const void *a ,const void *b)
{
	struct	StructGenerateAuto	*pa=(struct	StructGenerateAuto	*)a;
	struct	StructGenerateAuto	*pb=(struct	StructGenerateAuto	*)b;
	if(pa->Var>pb->Var)
		return -1;
	else if(pa->Var<pb->Var)
		return 1;
	return 0;
}

bool	XAlignmentLargeArea::GenerateAuto(FlexArea &GArea,int &RetLayer ,FlexArea &RetArea,FlexArea &AllMaskArea)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	int	AutoGenItemSize			=ABase->AutoGenItemSize;
	int	AutoGenSelfSearchArea	=ABase->AutoGenSelfSearchArea;

	int	dx=AutoGenItemSize/4;
	int	dy=AutoGenItemSize/4;
	int	W=GArea.GetWidth();
	int	H=GArea.GetHeight();

	int	N=0;
	for(int Layer=0;Layer<ParentInLayer->GetLayerNumb();Layer++){
		for(int x=0;x<W;x+=dx){
			for(int y=0;y<H;y+=dy){
				N++;
			}
		}
	}
	struct StructGenerateAuto	*SList=new struct StructGenerateAuto[N];
	int	K=0;
	for(int Layer=0;Layer<ParentInLayer->GetLayerNumb();Layer++){
		int	xi=0;
		for(int x=0;x<W;x+=dx,xi++){
			int	yi=0;
			for(int y=0;y<H;y+=dy,yi++){
				SList[K].Layer=Layer;
				SList[K].x=x;
				SList[K].y=y;
				SList[K].xi=xi;
				SList[K].yi=yi;
				K++;
			}
		}
	}

	DataInPage	*Dp=GetDataInPage();

	#pragma omp parallel
	{                                               
		#pragma omp for
		for(int i=0;i<N;i++){
			SList[i].Var=0;
			FlexArea	ItemArea;
			int	ax1=SList[i].x+GArea.GetMinX();
			int	ay1=SList[i].y+GArea.GetMinY();
			int	ax2=SList[i].x+GArea.GetMinX()+AutoGenItemSize;
			int	ay2=SList[i].y+GArea.GetMinY()+AutoGenItemSize;
			if(AllMaskArea.CheckOverlapRectangle(ax1,ay1,ax2,ay2)==true){
				ItemArea.SetRectangle(ax1,ay1,ax2,ay2);
				FlexArea	A=ItemArea;
				A-=GetArea();
				if(A.GetPatternByte()==0){
					double Avr;
					double Var;
					DataInLayer	*Ly=Dp->GetLayerData(SList[i].Layer);
					ImageBuffer	&IBuff=Ly->GetMasterBuff();
					if(ItemArea.CalcAvrVar(0,0,IBuff,Avr ,Var,1.0,1.0)==true){
						SList[i].Var=Var;
					}
				}
			}
		}
	}
	QSort(SList,N,sizeof(SList[0]),FuncSList);
	int	NN=N/20;
	int	MAutoGenItemSize=AutoGenItemSize/4;
	double	NeighborMatch=ABase->AutoGenNeighborMatch;
	for(int i=0;i<NN;i++){
		if(sqrt(SList[i].Var)<ABase->AutoGenMinVar){
			SList[i].Var=0;
		}
		else{
			for(int j=i+1;j<NN;j++){
				if(SList[i].Layer==SList[j].Layer
				&& SList[j].Var>0
				&& abs(SList[i].xi-SList[j].yi)<=1
				&& abs(SList[i].yi-SList[j].yi)<=1){
					DataInLayer	*Ly=Dp->GetLayerData(SList[i].Layer);
					ImageBuffer	&IBuff=Ly->GetMasterBuff();
					FlexAreaImageListCoeff	ItemArea;
					ItemArea.SetRectangle(SList[i].x+GArea.GetMinX(),SList[i].y+GArea.GetMinY()
										 ,SList[i].x+GArea.GetMinX()+AutoGenItemSize,SList[i].y+GArea.GetMinY()+AutoGenItemSize);
					FlexArea	A=ItemArea;
					A-=GetArea();
					if(A.GetPatternByte()!=0){
						continue;
					}
					ItemArea.Set(IBuff);
					double	MaxD=0;
					for(int qx=-MAutoGenItemSize;qx<=MAutoGenItemSize;qx++){
						for(int qy=-MAutoGenItemSize;qy<=MAutoGenItemSize;qy++){
							int	dx=SList[j].x-SList[i].x+qx;
							int	dy=SList[j].y-SList[i].y+qy;
							if(-3<=dx && dx<=3 && -3<=dy && dy<=3){
								continue;
							}
							double	D=ItemArea.CalcCoeff(dx,dy,IBuff);
							if(MaxD<D){
								MaxD=D;
							}
						}
					}
					if(MaxD>NeighborMatch){
						SList[j].Var=0;
						SList[i].Var=0;
					}
				}
			}
		}
	}
	QSort(SList,NN,sizeof(SList[0]),FuncSList);
	int	Nr=0;
	for(int i=0;i<NN;i++){
		if(SList[i].Var>0){
			Nr++;
		}
	}

	double	MaxMk=0;
	FlexArea	FittableArea;
	int			FittableLayer=-1;
	struct StructGenerateAuto	*SelfSearchList=new struct StructGenerateAuto[(2*AutoGenSelfSearchArea+1)*(2*AutoGenSelfSearchArea+1)];
	int	Kn=0;	
	for(int qx=-AutoGenSelfSearchArea;qx<=AutoGenSelfSearchArea;qx++){
		for(int qy=-AutoGenSelfSearchArea;qy<=AutoGenSelfSearchArea;qy++){
			if(-3<=qx && qx<=3 && -3<=qy && qy<=3){
				continue;
			}
			SelfSearchList[Kn].x=qx;
			SelfSearchList[Kn].y=qy;
			Kn++;
		}
	}

	for(int i=0;i<Nr;i++){
		DataInLayer	*Ly=Dp->GetLayerData(SList[i].Layer);
		ImageBuffer	&IBuff=Ly->GetMasterBuff();
		FlexAreaImageListCoeff	ItemArea;
		ItemArea.SetRectangle(SList[i].x+GArea.GetMinX()
							 ,SList[i].y+GArea.GetMinY()
							 ,SList[i].x+GArea.GetMinX()+AutoGenItemSize
							 ,SList[i].y+GArea.GetMinY()+AutoGenItemSize);
		FlexArea	A=ItemArea;
		A-=GetArea();
		if(A.GetPatternByte()!=0){
			continue;
		}
		ItemArea.Set(IBuff);
		double Var=SList[i].Var;
		double	MaxD=0;
		#pragma omp parallel
		{                                               
			#pragma omp for
			for(int j=0;j<Kn;j++){
				double	D=ItemArea.CalcCoeff(SelfSearchList[j].x
											,SelfSearchList[j].y
											,IBuff);
				SelfSearchList[j].Var=D;
			}
		}
		for(int j=0;j<Kn;j++){
			if(SelfSearchList[j].Var>MaxD){
				MaxD=SelfSearchList[j].Var;
			}
		}
		if(MaxD<NeighborMatch){
			double	M=1.0+fabs(MaxD);
			double	Mk=Var/M;
			if(MaxMk<Mk){
				MaxMk=Mk;
				FittableArea	=ItemArea;
				FittableLayer	=SList[i].Layer;
			}
		}
	}
	delete	[]SList;
	delete	[]SelfSearchList;

	if(FittableLayer>=0){
		RetLayer=FittableLayer;
		RetArea	=FittableArea;
		return true;
	}
	return false;
}

bool	XAlignmentLargeArea::GenerateAutoAddItem(int &tLayer ,FlexArea &tArea)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	XAlignmentLarge	*Item=dynamic_cast<XAlignmentLarge *>(ParentInLayer->CreateItem(0));
	Item->AreaID						=AreaID;
	Item->GetThresholdW()->MoveDotX		=ABase->AutoGenMoveDotX ;
	Item->GetThresholdW()->MoveDotY		=ABase->AutoGenMoveDotY ;
	Item->GetThresholdW()->MoveDotX2	=ABase->AutoGenMoveDotX2;
	Item->GetThresholdW()->MoveDotY2	=ABase->AutoGenMoveDotY2;
	Item->GetThresholdW()->SearchAround	=0;
	Item->GroupNumber					=0;
	Item->GetThresholdW()->UsageGlobal	=false;
	Item->GetThresholdW()->JudgeWithBrDif	=true;

	Item->GetThresholdW()->CharacterMode	=false;

	Item->SetArea(tArea);
	Item->SelectedLayer	=tLayer;
	Item->SetManualCreated(false);
	ParentInLayer->AppendItem(Item);

	ImageBuffer	&MBuff=Item->GetMasterBuffForMakeArea();
	Item->GetThresholdW()->CharacterMode	=Item->CheckCharactered(MBuff);
	Item->MakeArea(MBuff);

	if(Item->TransArea.GetPatternByte()==0){
		int	W=Item->GetArea().GetWidth();
		int	H=Item->GetArea().GetHeight();

		int	dx=W/3;
		int	dy=H/3;

		{
			Item->MoveTo(dx,0);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(-dx,0);
			Item->MoveTo(-dx,0);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(dx,0);
		}
		{
			Item->MoveTo(0,dy);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(0,-dy);
			Item->MoveTo(0,-dy);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(0,dy);
		}
		{
			Item->MoveTo(-dx,0);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(dx,0);
			Item->MoveTo(dx,0);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(-dx,0);
		}
		{
			Item->MoveTo(0,-dy);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(0,dy);
			Item->MoveTo(0,dy);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(0,-dy);
		}

		{
			Item->MoveTo(dx,dy);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(-dx,-dy);
			Item->MoveTo(-dx,-dy);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(dx,dy);
		}

		{
			Item->MoveTo(dx,-dy);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(-dx,dy);
			Item->MoveTo(-dx,dy);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(dx,-dy);
		}

		{
			Item->MoveTo(-dx,dy);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(dx,-dy);
			Item->MoveTo(dx,-dy);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(-dx,dy);
		}

		{
			Item->MoveTo(-dx,-dy);
			Item->MakeArea(MBuff);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(dx,dy);
			Item->MoveTo(dx,dy);
			if(Item->TransArea.GetPatternByte()!=0){
				return true;
			}
			Item->MoveTo(-dx,-dy);
		}
		ParentInLayer->RemoveItem(Item);
		delete	Item;
		return false;
	}

	return true;
}