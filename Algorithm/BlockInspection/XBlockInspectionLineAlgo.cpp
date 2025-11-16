/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockInspectionAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "BlockFormResource.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"
#include <omp.h>
#include "immintrin.h"

static	int	ShiftDimFunc(const void *a,const void *b)
{
	struct BlockShiftList::BlockShiftInfo	*pa=(struct BlockShiftList::BlockShiftInfo	*)a;
	struct BlockShiftList::BlockShiftInfo	*pb=(struct BlockShiftList::BlockShiftInfo	*)b;
	if(pa->MatchResult>pb->MatchResult)
		return -1;
	if(pa->MatchResult<pb->MatchResult)
		return 1;
	return 0;
}

bool	BlockItem::ExeMatchLinePosition(int mx,int my,BlockShiftList &BlockShiftListData,bool &FixXDir,bool &FixYDir)
{
	if(FollowLineData==NULL)
		return false;
	const	BlockThreshold	*RThr=GetThresholdR();
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
	int	MaxBlockShiftCount	=((BlockBase *)GetParentBase())->MaxBlockShiftCount;

	int	LftCount=0;
	int	TopCount=0;
	int	RgtCount=0;
	int	BtmCount=0;

	if(FollowLineData->LftMatchLine0.IsEffective()==true){
		LftCount++;
	}
	if(FollowLineData->LftMatchLine1.IsEffective()==true){
		LftCount++;
	}
	if(FollowLineData->LftMatchLine2.IsEffective()==true){
		LftCount++;
	}
	if(FollowLineData->TopMatchLine0.IsEffective()==true){
		TopCount++;
	}
	if(FollowLineData->TopMatchLine1.IsEffective()==true){
		TopCount++;
	}
	if(FollowLineData->TopMatchLine2.IsEffective()==true){
		TopCount++;
	}

	if(FollowLineData->RgtMatchLine0.IsEffective()==true){
		RgtCount++;
	}
	if(FollowLineData->RgtMatchLine1.IsEffective()==true){
		RgtCount++;
	}
	if(FollowLineData->RgtMatchLine2.IsEffective()==true){
		RgtCount++;
	}
	if(FollowLineData->BtmMatchLine0.IsEffective()==true){
		BtmCount++;
	}
	if(FollowLineData->BtmMatchLine1.IsEffective()==true){
		BtmCount++;
	}
	if(FollowLineData->BtmMatchLine2.IsEffective()==true){
		BtmCount++;
	}
	/*
	if((LftCount==0 && TopCount==0 && RgtCount==0 && BtmCount>=0)
	|| (LftCount==0 && TopCount==0 && RgtCount>=0 && BtmCount==0)
	|| (LftCount==0 && TopCount>=0 && RgtCount==0 && BtmCount==0)
	|| (LftCount>=0 && TopCount==0 && RgtCount==0 && BtmCount==0)){
		return false;
	}
	*/
	if(LftCount==0 && RgtCount==0)
		FixXDir=false;
	else
		FixXDir=true;
	if(TopCount==0 && BtmCount==0)
		FixYDir=false;
	else
		FixYDir=true;

	ImageBuffer *DBuff=NULL;
	if(RThr->ThreshouldBag.FollowLineLayer<0){
		DBuff=&GetTargetBuff();
	}
	else{
		int	Layer=min(RThr->ThreshouldBag.FollowLineLayer,Parent->GetLayerNumb()-1);
		DataInLayer	*DL=Parent->GetDataInPage()->GetLayerData(Layer);
		DBuff=&DL->GetTargetBuff();
	}

	struct BlockShiftList::BlockShiftInfo	*ShiftDim=new struct BlockShiftList::BlockShiftInfo[4*(SelfSearch+1)*SelfSearch+1+8*20];
	int		ShiftDimNumb=0;
	if(SelfSearch==0){
		ShiftDim[ShiftDimNumb].ShiftX=0;
		ShiftDim[ShiftDimNumb].ShiftY=0;
		ShiftDimNumb++;
	}
	else if(SelfSearch<4){
		if(LftCount>0 && TopCount==0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount>0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount>0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount==0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount==0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}	
		else{
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
	}
	else if(SelfSearch<10){
		if(LftCount>0 && TopCount==0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,2
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount>0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,2
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,2
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount>0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,2
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount==0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount==0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}	
		else{
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,2
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
	}
	else{
		if(LftCount>0 && TopCount==0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1	//3
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount>0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1	//3
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1	//3
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount>0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1	//3
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount==0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1	//3
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount==0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2);
		}
		else if(LftCount==0 && TopCount==0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}
		else if(LftCount>0 && TopCount==0 && RgtCount>0 && BtmCount==0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2);
		}
		else if(LftCount==0 && TopCount>0 && RgtCount==0 && BtmCount>0){
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
		}	
		else{
			ShiftDimNumb=ExeMatchLineSwing(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
			if(ShiftDimNumb<MaxCountOfBlockShiftList){
				ShiftDimNumb=ExeMatchLineChooseBetter(*DBuff,mx,my ,1
							,ShiftDim
							,FollowLineData->LftMatchLine0,FollowLineData->LftMatchLine1,FollowLineData->LftMatchLine2
							,FollowLineData->RgtMatchLine0,FollowLineData->RgtMatchLine1,FollowLineData->RgtMatchLine2
							,FollowLineData->TopMatchLine0,FollowLineData->TopMatchLine1,FollowLineData->TopMatchLine2
							,FollowLineData->BtmMatchLine0,FollowLineData->BtmMatchLine1,FollowLineData->BtmMatchLine2);
			}
		}
	}
	QSort(ShiftDim,ShiftDimNumb,sizeof(ShiftDim[0]),ShiftDimFunc);
	if(FixXDir==true && FixYDir==true){
		BlockShiftListData.CurrentNumb=0;
		for(int i=0;BlockShiftListData.CurrentNumb<BlockShiftListData.DimNumb 
				&& i<ShiftDimNumb 
				&& BlockShiftListData.CurrentNumb<MaxBlockShiftCount
			;i++){
			BlockShiftListData.Dim[BlockShiftListData.CurrentNumb]=ShiftDim[i];
			BlockShiftListData.CurrentNumb++;
		}
	}
	else if(FixXDir==true && FixYDir==false){
		BlockShiftListData.CurrentNumb=0;
		for(int i=0;BlockShiftListData.CurrentNumb<BlockShiftListData.DimNumb 
				&& i<ShiftDimNumb
				&& BlockShiftListData.CurrentNumb<MaxBlockShiftCount
			;i++){
			int	t;
			for(t=0;t<BlockShiftListData.CurrentNumb;t++){
				if(BlockShiftListData.Dim[t].ShiftX==ShiftDim[i].ShiftX)
					break;
			}
			if(t>=BlockShiftListData.CurrentNumb){
				BlockShiftListData.Dim[BlockShiftListData.CurrentNumb]=ShiftDim[i];
				BlockShiftListData.CurrentNumb++;
			}
		}
	}
	else if(FixXDir==false && FixYDir==true){
		BlockShiftListData.CurrentNumb=0;
		for(int i=0;BlockShiftListData.CurrentNumb<BlockShiftListData.DimNumb 
				&& i<ShiftDimNumb
				&& BlockShiftListData.CurrentNumb<MaxBlockShiftCount
			;i++){
			int	t;
			for(t=0;t<BlockShiftListData.CurrentNumb;t++){
				if(BlockShiftListData.Dim[t].ShiftY==ShiftDim[i].ShiftY)
					break;
			}
			if(t>=BlockShiftListData.CurrentNumb){
				BlockShiftListData.Dim[BlockShiftListData.CurrentNumb]=ShiftDim[i];
				BlockShiftListData.CurrentNumb++;
			}
		}
	}
	delete	[]ShiftDim;
	return true;
}

static	double	CalcMatchBW(double data
					,bool ModePermitInverted
					,bool ModeMatchPosition ,bool ModeMatchPositionBW)
{
	if(ModeMatchPosition==true && ModeMatchPositionBW==false){
		if(ModePermitInverted==true)
			return fabs(data);
		else
			return data;
	}
	if(ModeMatchPosition==false && ModeMatchPositionBW==true)
		return data;
	if(ModeMatchPosition==true && ModeMatchPositionBW==true)
		return data;
	return data;
}


int	BlockItem::ExeMatchLineSwing(ImageBuffer &DBuff
									,int mx,int my ,int Sep
									,struct BlockShiftList::BlockShiftInfo	*ShiftDim
									,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
									,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
	int	HCount=0;
	int	VCount=0;
	if(HLine0.IsEffective()==true){
		HCount++;
	}
	if(HLine1.IsEffective()==true){
		HCount++;
	}
	if(HLine2.IsEffective()==true){
		HCount++;
	}
	if(VLine0.IsEffective()==true){
		VCount++;
	}
	if(VLine1.IsEffective()==true){
		VCount++;
	}
	if(VLine2.IsEffective()==true){
		VCount++;
	}
	int	ShiftNumb=0;
	for(int kx=-SelfSearch;kx<=SelfSearch;kx+=Sep){
		for(int ky=-SelfSearch;ky<=SelfSearch;ky+=Sep){
			double	DH[3];
			double	DV[3];
			int		HN=0;
			int		VN=0;
			bool	Plus=true;
			if(HLine0.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine0.Match(DBuff,mx+kx,my+ky)
								  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine1.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine1.Match(DBuff,mx+kx,my+ky)
								  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine2.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine2.Match(DBuff,mx+kx,my+ky)
								  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(VLine0.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine0.Match(DBuff,mx+kx,my+ky)
								  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine1.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine1.Match(DBuff,mx+kx,my+ky)
								  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine2.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine2.Match(DBuff,mx+kx,my+ky)
								  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
								  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(Plus==true){
				int	N=HN+VN;
				double	D=1.0;
				if(HCount==1)
					D*=DH[0]*DH[0]*DH[0];
				else if(HCount==2)
					D*=DH[0]*DH[0]*DH[1]*DH[1];
				else if(HCount==3)
					D*=DH[0]*DH[1]*DH[2];
				if(VCount==1)
					D*=DV[0]*DV[0]*DV[0];
				else if(VCount==2)
					D*=DV[0]*DV[0]*DV[1]*DV[1];
				else if(VCount==3)
					D*=DV[0]*DV[1]*DV[2];
							
				if(N>0){
					ShiftDim[ShiftNumb].ShiftX=kx;
					ShiftDim[ShiftNumb].ShiftY=ky;
					ShiftDim[ShiftNumb].MatchResult=D;
					ShiftNumb++;
				}
			}
		}
	}
	if(Sep>1){
		QSort(ShiftDim,ShiftNumb,sizeof(ShiftDim[0]),ShiftDimFunc);
		int	tShiftNumb=ShiftNumb;
		for(int t=0;t<MaxCountOfBlockShiftList && t<tShiftNumb;t++){
			int	Bx=ShiftDim[t].ShiftX;
			int	By=ShiftDim[t].ShiftY;
			for(int kx=-(Sep-1);kx<=(Sep-1);kx++){
				for(int ky=-(Sep-1);ky<=(Sep-1);ky++){
					if(kx==0 && ky==0)
						continue;
					double	DH[3];
					double	DV[3];
					int		HN=0;
					int		VN=0;
					bool	Plus=true;
					if(HLine0.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine0.Match(DBuff,mx+Bx+kx,my+By+ky)
									  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
									  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine1.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine1.Match(DBuff,mx+Bx+kx,my+By+ky)
									  ,RThr->ThreshouldBag.PointMove.ModePermitInverted
									  ,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									  ,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine2.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine2.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(VLine0.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine0.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine1.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine1.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine2.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine2.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(Plus==true){
						int	N=HN+VN;
						double	D=1.0;
						if(HCount==1)
							D*=DH[0]*DH[0]*DH[0];
						else if(HCount==2)
							D*=DH[0]*DH[0]*DH[1]*DH[1];
						else if(HCount==3)
							D*=DH[0]*DH[1]*DH[2];
						if(VCount==1)
							D*=DV[0]*DV[0]*DV[0];
						else if(VCount==2)
							D*=DV[0]*DV[0]*DV[1]*DV[1];
						else if(VCount==3)
							D*=DV[0]*DV[1]*DV[2];
									
						if(N>0){
							ShiftDim[ShiftNumb].ShiftX=kx+Bx;
							ShiftDim[ShiftNumb].ShiftY=ky+By;
							ShiftDim[ShiftNumb].MatchResult=D;
							ShiftNumb++;
						}
					}
				}
			}
		}
	}
	return ShiftNumb;
}


int	BlockItem::ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
								,HLineInBlock &HLine3 ,HLineInBlock &HLine4 ,HLineInBlock &HLine5)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
	int	HCount=0;
	if(HLine0.IsEffective()==true){
		HCount++;
	}
	if(HLine1.IsEffective()==true){
		HCount++;
	}
	if(HLine2.IsEffective()==true){
		HCount++;
	}
	if(HLine3.IsEffective()==true){
		HCount++;
	}
	if(HLine4.IsEffective()==true){
		HCount++;
	}
	if(HLine5.IsEffective()==true){
		HCount++;
	}

	int	ShiftNumb=0;
	for(int kx=-SelfSearch;kx<=SelfSearch;kx+=Sep){
		for(int ky=-SelfSearch;ky<=SelfSearch;ky+=Sep){
			double	DH[6];
			int		HN=0;
			bool	Plus=true;
			if(HLine0.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine0.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine1.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine1.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine2.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine2.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine3.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine3.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine4.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine4.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(HLine5.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine5.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					Plus=false;
				HN++;
			}
			if(Plus==true){
				int	N=HN;
				double	D=1.0;
				/*
				if(HCount==1)
					D=DH[0]*DH[0]*DH[0];
				else if(HCount==2)
					D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1];
				else if(HCount==3)
					D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2];
				else if(HCount==4)
					D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2]+DH[3]*DH[3]*DH[3];
				else if(HCount==5)
					D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2]+DH[3]*DH[3]*DH[3]+DH[4]*DH[4]*DH[4];
				else if(HCount==6)
					D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2]+DH[3]*DH[3]*DH[3]+DH[4]*DH[4]*DH[4]+DH[5]*DH[5]*DH[5];
				*/
				if(HCount==1)
					D=DH[0]*DH[0]*DH[0];
				else if(HCount==2)
					D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1];
				else if(HCount==3)
					D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2];
				else if(HCount==4)
					D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2]*DH[3]*DH[3]*DH[3];
				else if(HCount==5)
					D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2]*DH[3]*DH[3]*DH[3]*DH[4]*DH[4]*DH[4];
				else if(HCount==6)
					D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2]*DH[3]*DH[3]*DH[3]*DH[4]*DH[4]*DH[4]*DH[5]*DH[5]*DH[5];

				if(N>0){
					ShiftDim[ShiftNumb].ShiftX=kx;
					ShiftDim[ShiftNumb].ShiftY=ky;
					ShiftDim[ShiftNumb].MatchResult=D;
					ShiftNumb++;
				}
			}
		}
	}
	if(Sep>1){
		QSort(ShiftDim,ShiftNumb,sizeof(ShiftDim[0]),ShiftDimFunc);
		int	tShiftNumb=ShiftNumb;
		for(int t=0;t<MaxCountOfBlockShiftList && t<tShiftNumb;t++){
			int	Bx=ShiftDim[t].ShiftX;
			int	By=ShiftDim[t].ShiftY;
			for(int kx=-(Sep-1);kx<=(Sep-1);kx++){
				for(int ky=-(Sep-1);ky<=(Sep-1);ky++){
					if(kx==0 && ky==0)
						continue;
					double	DH[6];
					int		HN=0;
					bool	Plus=true;
					if(HLine0.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine0.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine1.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine1.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine2.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine2.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine3.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine3.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine4.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine4.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}
					if(HLine5.IsEffective()==true){
						DH[HN]=CalcMatchBW(HLine5.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DH[HN]<0)
							Plus=false;
						HN++;
					}

					if(Plus==true){
						int	N=HN;
						double	D=1.0;
						/*
						if(HCount==1)
							D=DH[0]*DH[0]*DH[0];
						else if(HCount==2)
							D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1];
						else if(HCount==3)
							D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2];
						else if(HCount==4)
							D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2]+DH[3]*DH[3]*DH[3];
						else if(HCount==5)
							D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2]+DH[3]*DH[3]*DH[3]+DH[4]*DH[4]*DH[4];
						else if(HCount==6)
							D=DH[0]*DH[0]*DH[0]+DH[1]*DH[1]*DH[1]+DH[2]*DH[2]*DH[2]+DH[3]*DH[3]*DH[3]+DH[4]*DH[4]*DH[4]+DH[5]*DH[5]*DH[5];
						*/
						if(HCount==1)
							D=DH[0]*DH[0]*DH[0];
						else if(HCount==2)
							D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1];
						else if(HCount==3)
							D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2];
						else if(HCount==4)
							D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2]*DH[3]*DH[3]*DH[3];
						else if(HCount==5)
							D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2]*DH[3]*DH[3]*DH[3]*DH[4]*DH[4]*DH[4];
						else if(HCount==6)
							D=DH[0]*DH[0]*DH[0]*DH[1]*DH[1]*DH[1]*DH[2]*DH[2]*DH[2]*DH[3]*DH[3]*DH[3]*DH[4]*DH[4]*DH[4]*DH[5]*DH[5]*DH[5];

						if(N>0){
							ShiftDim[ShiftNumb].ShiftX=kx+Bx;
							ShiftDim[ShiftNumb].ShiftY=ky+By;
							ShiftDim[ShiftNumb].MatchResult=D;
							ShiftNumb++;
						}
					}
				}
			}
		}
	}
	return ShiftNumb;
}

int	BlockItem::ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2
								,VLineInBlock &VLine3 ,VLineInBlock &VLine4 ,VLineInBlock &VLine5)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
	int	VCount=0;

	if(VLine0.IsEffective()==true){
		VCount++;
	}
	if(VLine1.IsEffective()==true){
		VCount++;
	}
	if(VLine2.IsEffective()==true){
		VCount++;
	}
	if(VLine3.IsEffective()==true){
		VCount++;
	}
	if(VLine4.IsEffective()==true){
		VCount++;
	}
	if(VLine5.IsEffective()==true){
		VCount++;
	}

	int	ShiftNumb=0;
	for(int kx=-SelfSearch;kx<=SelfSearch;kx+=Sep){
		for(int ky=-SelfSearch;ky<=SelfSearch;ky+=Sep){
			double	DV[6];
			int		VN=0;
			bool	Plus=true;
			if(VLine0.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine0.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine1.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine1.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine2.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine2.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine3.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine3.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine4.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine4.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(VLine5.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine5.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					Plus=false;
				VN++;
			}
			if(Plus==true){
				int	N=VN;
				double	D=1.0;
				/*
				if(VCount==1)
					D=DV[0]*DV[0]*DV[0];
				else if(VCount==2)
					D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1];
				else if(VCount==3)
					D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2];
				else if(VCount==4)
					D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2]+DV[3]*DV[3]*DV[3];
				else if(VCount==5)
					D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2]+DV[3]*DV[3]*DV[3]+DV[4]*DV[4]*DV[4];
				else if(VCount==6)
					D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2]+DV[3]*DV[3]*DV[3]+DV[4]*DV[4]*DV[4]+DV[5]*DV[5]*DV[5];
				*/
				if(VCount==1)
					D=DV[0]*DV[0]*DV[0];
				else if(VCount==2)
					D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1];
				else if(VCount==3)
					D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2];
				else if(VCount==4)
					D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2]*DV[3]*DV[3]*DV[3];
				else if(VCount==5)
					D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2]*DV[3]*DV[3]*DV[3]*DV[4]*DV[4]*DV[4];
				else if(VCount==6)
					D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2]*DV[3]*DV[3]*DV[3]*DV[4]*DV[4]*DV[4]*DV[5]*DV[5]*DV[5];

				if(N>0){
					ShiftDim[ShiftNumb].ShiftX=kx;
					ShiftDim[ShiftNumb].ShiftY=ky;
					ShiftDim[ShiftNumb].MatchResult=D;
					ShiftNumb++;
				}
			}
		}
	}
	if(Sep>1){
		QSort(ShiftDim,ShiftNumb,sizeof(ShiftDim[0]),ShiftDimFunc);
		int	tShiftNumb=ShiftNumb;
		for(int t=0;t<MaxCountOfBlockShiftList && t<tShiftNumb;t++){
			int	Bx=ShiftDim[t].ShiftX;
			int	By=ShiftDim[t].ShiftY;
			for(int kx=-(Sep-1);kx<=(Sep-1);kx++){
				for(int ky=-(Sep-1);ky<=(Sep-1);ky++){
					if(kx==0 && ky==0)
						continue;
					double	DV[6];
					int		VN=0;
					bool	Plus=true;
					if(VLine0.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine0.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine1.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine1.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine2.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine2.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine3.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine3.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine4.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine4.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(VLine5.IsEffective()==true){
						DV[VN]=CalcMatchBW(VLine5.Match(DBuff,mx+Bx+kx,my+By+ky)
										,RThr->ThreshouldBag.PointMove.ModePermitInverted
										,RThr->ThreshouldBag.PointMove.ModeMatchPosition
										,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DV[VN]<0)
							Plus=false;
						VN++;
					}
					if(Plus==true){
						int	N=VN;
						double	D=1.0;
						/*
						if(VCount==1)
							D=DV[0]*DV[0]*DV[0];
						else if(VCount==2)
							D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1];
						else if(VCount==3)
							D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2];
						else if(VCount==4)
							D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2]+DV[3]*DV[3]*DV[3];
						else if(VCount==5)
							D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2]+DV[3]*DV[3]*DV[3]+DV[4]*DV[4]*DV[4];
						else if(VCount==6)
							D=DV[0]*DV[0]*DV[0]+DV[1]*DV[1]*DV[1]+DV[2]*DV[2]*DV[2]+DV[3]*DV[3]*DV[3]+DV[4]*DV[4]*DV[4]+DV[5]*DV[5]*DV[5];					
						*/
						if(VCount==1)
							D=DV[0]*DV[0]*DV[0];
						else if(VCount==2)
							D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1];
						else if(VCount==3)
							D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2];
						else if(VCount==4)
							D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2]*DV[3]*DV[3]*DV[3];
						else if(VCount==5)
							D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2]*DV[3]*DV[3]*DV[3]*DV[4]*DV[4]*DV[4];
						else if(VCount==6)
							D=DV[0]*DV[0]*DV[0]*DV[1]*DV[1]*DV[1]*DV[2]*DV[2]*DV[2]*DV[3]*DV[3]*DV[3]*DV[4]*DV[4]*DV[4]*DV[5]*DV[5]*DV[5];
					
						if(N>0){
							ShiftDim[ShiftNumb].ShiftX=kx+Bx;
							ShiftDim[ShiftNumb].ShiftY=ky+By;
							ShiftDim[ShiftNumb].MatchResult=D;
							ShiftNumb++;
						}
					}
				}
			}
		}
	}
	return ShiftNumb;
}

int	BlockItem::ExeMatchLineSwing(ImageBuffer &DBuff
								,int mx,int my ,int Sep
								,struct BlockShiftList::BlockShiftInfo	*ShiftDim
								,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
								,HLineInBlock &HLine3 ,HLineInBlock &HLine4 ,HLineInBlock &HLine5
								,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2
								,VLineInBlock &VLine3 ,VLineInBlock &VLine4 ,VLineInBlock &VLine5)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;

	int	ShiftNumb=0;
	for(int kx=-SelfSearch;kx<=SelfSearch;kx+=Sep){
		for(int ky=-SelfSearch;ky<=SelfSearch;ky+=Sep){
			double	DHL[3];
			double	DHR[3];
			double	DVT[3];
			double	DVB[3];
			int		HNL=0;
			int		HNR=0;
			int		VNT=0;
			int		VNB=0;
			bool	Plus=true;
			if(HLine0.IsEffective()==true){
				DHL[HNL]=CalcMatchBW(HLine0.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
				if(DHL[HNL]<0)
					Plus=false;
				HNL++;
			}
			if(HLine1.IsEffective()==true){
				DHL[HNL]=CalcMatchBW(HLine1.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DHL[HNL]<0)
					Plus=false;
				HNL++;
			}
			if(HLine2.IsEffective()==true){
				DHL[HNL]=CalcMatchBW(HLine2.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DHL[HNL]<0)
					Plus=false;
				HNL++;
			}
			if(HLine3.IsEffective()==true){
				DHR[HNR]=CalcMatchBW(HLine3.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
				if(DHR[HNR]<0)
					Plus=false;
				HNR++;
			}
			if(HLine4.IsEffective()==true){
				DHR[HNR]=CalcMatchBW(HLine4.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DHR[HNR]<0)
					Plus=false;
				HNR++;
			}
			if(HLine5.IsEffective()==true){
				DHR[HNR]=CalcMatchBW(HLine5.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DHR[HNR]<0)
					Plus=false;
				HNR++;
			}
			if(VLine0.IsEffective()==true){
				DVT[VNT]=CalcMatchBW(VLine0.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DVT[VNT]<0)
					Plus=false;
				VNT++;
			}
			if(VLine1.IsEffective()==true){
				DVT[VNT]=CalcMatchBW(VLine1.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DVT[VNT]<0)
					Plus=false;
				VNT++;
			}
			if(VLine2.IsEffective()==true){
				DVT[VNT]=CalcMatchBW(VLine2.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DVT[VNT]<0)
					Plus=false;
				VNT++;
			}
			if(VLine3.IsEffective()==true){
				DVB[VNB]=CalcMatchBW(VLine3.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DVB[VNB]<0)
					Plus=false;
				VNB++;
			}
			if(VLine4.IsEffective()==true){
				DVB[VNB]=CalcMatchBW(VLine4.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DVB[VNB]<0)
					Plus=false;
				VNB++;
			}
			if(VLine5.IsEffective()==true){
				DVB[VNB]=CalcMatchBW(VLine5.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DVB[VNB]<0)
					Plus=false;
				VNB++;
			}
			if(Plus==true){
				int	N=HNL+HNR+VNT+VNB;
				double	D=1.0;

				if(HNL==1)
					D*=DHL[0]*DHL[0]*DHL[0]*DHL[0]*DHL[0]*DHL[0];
				else if(HNL==2)
					D*=DHL[0]*DHL[1]*DHL[0]*DHL[1]*DHL[0]*DHL[1];
				else if(HNL==3)
					D*=DHL[0]*DHL[1]*DHL[2]*DHL[0]*DHL[1]*DHL[2];

				if(HNR==1)
					D*=DHR[0]*DHR[0]*DHR[0]*DHR[0]*DHR[0]*DHR[0];
				else if(HNR==2)
					D*=DHR[0]*DHR[1]*DHR[0]*DHR[1]*DHR[0]*DHR[1];
				else if(HNR==3)
					D*=DHR[0]*DHR[1]*DHR[2]*DHR[0]*DHR[1]*DHR[2];

				if(VNT==1)
					D*=DVT[0]*DVT[0]*DVT[0]*DVT[0]*DVT[0]*DVT[0];
				else if(VNT==2)
					D*=DVT[0]*DVT[1]*DVT[0]*DVT[1]*DVT[0]*DVT[1];
				else if(VNT==3)
					D*=DVT[0]*DVT[1]*DVT[2]*DVT[0]*DVT[1]*DVT[2];

				if(VNB==1)
					D*=DVB[0]*DVB[0]*DVB[0]*DVB[0]*DVB[0]*DVB[0];
				else if(VNB==2)
					D*=DVB[0]*DVB[1]*DVB[0]*DVB[1]*DVB[0]*DVB[1];
				else if(VNB==3)
					D*=DVB[0]*DVB[1]*DVB[2]*DVB[0]*DVB[1]*DVB[2];
							
				if(N>0){
					ShiftDim[ShiftNumb].ShiftX=kx;
					ShiftDim[ShiftNumb].ShiftY=ky;
					ShiftDim[ShiftNumb].MatchResult=D;
					ShiftNumb++;
				}
			}
		}
	}
	if(Sep>1){
		QSort(ShiftDim,ShiftNumb,sizeof(ShiftDim[0]),ShiftDimFunc);
		int	tShiftNumb=ShiftNumb;
		for(int t=0;t<MaxCountOfBlockShiftList && t<tShiftNumb;t++){
			int	Bx=ShiftDim[t].ShiftX;
			int	By=ShiftDim[t].ShiftY;
			for(int kx=-(Sep-1);kx<=(Sep-1);kx++){
				for(int ky=-(Sep-1);ky<=(Sep-1);ky++){
					if(kx==0 && ky==0)
						continue;

					double	DHL[3];
					double	DHR[3];
					double	DVT[3];
					double	DVB[3];
					int		HNL=0;
					int		HNR=0;
					int		VNT=0;
					int		VNB=0;
					bool	Plus=true;
					if(HLine0.IsEffective()==true){
						DHL[HNL]=CalcMatchBW(HLine0.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
						if(DHL[HNL]<0)
							Plus=false;
						HNL++;
					}
					if(HLine1.IsEffective()==true){
						DHL[HNL]=CalcMatchBW(HLine1.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DHL[HNL]<0)
							Plus=false;
						HNL++;
					}
					if(HLine2.IsEffective()==true){
						DHL[HNL]=CalcMatchBW(HLine2.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DHL[HNL]<0)
							Plus=false;
						HNL++;
					}
					if(HLine3.IsEffective()==true){
						DHR[HNR]=CalcMatchBW(HLine3.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
						if(DHR[HNR]<0)
							Plus=false;
						HNR++;
					}
					if(HLine4.IsEffective()==true){
						DHR[HNR]=CalcMatchBW(HLine4.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DHR[HNR]<0)
							Plus=false;
						HNR++;
					}
					if(HLine5.IsEffective()==true){
						DHR[HNR]=CalcMatchBW(HLine5.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DHR[HNR]<0)
							Plus=false;
						HNR++;
					}
					if(VLine0.IsEffective()==true){
						DVT[VNT]=CalcMatchBW(VLine0.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DVT[VNT]<0)
							Plus=false;
						VNT++;
					}
					if(VLine1.IsEffective()==true){
						DVT[VNT]=CalcMatchBW(VLine1.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DVT[VNT]<0)
							Plus=false;
						VNT++;
					}
					if(VLine2.IsEffective()==true){
						DVT[VNT]=CalcMatchBW(VLine2.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DVT[VNT]<0)
							Plus=false;
						VNT++;
					}
					if(VLine3.IsEffective()==true){
						DVB[VNB]=CalcMatchBW(VLine3.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DVB[VNB]<0)
							Plus=false;
						VNB++;
					}
					if(VLine4.IsEffective()==true){
						DVB[VNB]=CalcMatchBW(VLine4.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DVB[VNB]<0)
							Plus=false;
						VNB++;
					}
					if(VLine5.IsEffective()==true){
						DVB[VNB]=CalcMatchBW(VLine5.Match(DBuff,mx+Bx+kx,my+By+ky)
											,RThr->ThreshouldBag.PointMove.ModePermitInverted
											,RThr->ThreshouldBag.PointMove.ModeMatchPosition
											,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

						if(DVB[VNB]<0)
							Plus=false;
						VNB++;
					}
					if(Plus==true){
						int	N=HNL+HNR+VNT+VNB;
						double	D=1.0;

						if(HNL==1)
							D*=DHL[0]*DHL[0]*DHL[0]*DHL[0]*DHL[0]*DHL[0];
						else if(HNL==2)
							D*=DHL[0]*DHL[1]*DHL[0]*DHL[1]*DHL[0]*DHL[1];
						else if(HNL==3)
							D*=DHL[0]*DHL[1]*DHL[2]*DHL[0]*DHL[1]*DHL[2];

						if(HNR==1)
							D*=DHR[0]*DHR[0]*DHR[0]*DHR[0]*DHR[0]*DHR[0];
						else if(HNR==2)
							D*=DHR[0]*DHR[1]*DHR[0]*DHR[1]*DHR[0]*DHR[1];
						else if(HNR==3)
							D*=DHR[0]*DHR[1]*DHR[2]*DHR[0]*DHR[1]*DHR[2];

						if(VNT==1)
							D*=DVT[0]*DVT[0]*DVT[0]*DVT[0]*DVT[0]*DVT[0];
						else if(VNT==2)
							D*=DVT[0]*DVT[1]*DVT[0]*DVT[1]*DVT[0]*DVT[1];
						else if(VNT==3)
							D*=DVT[0]*DVT[1]*DVT[2]*DVT[0]*DVT[1]*DVT[2];

						if(VNB==1)
							D*=DVB[0]*DVB[0]*DVB[0]*DVB[0]*DVB[0]*DVB[0];
						else if(VNB==2)
							D*=DVB[0]*DVB[1]*DVB[0]*DVB[1]*DVB[0]*DVB[1];
						else if(VNB==3)
							D*=DVB[0]*DVB[1]*DVB[2]*DVB[0]*DVB[1]*DVB[2];

						if(N>0){
							ShiftDim[ShiftNumb].ShiftX=kx+Bx;
							ShiftDim[ShiftNumb].ShiftY=ky+By;
							ShiftDim[ShiftNumb].MatchResult=D;
							ShiftNumb++;
						}
					}
				}
			}
		}
	}
	return ShiftNumb;
}
int	BlockItem::ExeMatchLineChooseBetter(ImageBuffer &DBuff
									,int mx,int my ,int Sep
									,struct BlockShiftList::BlockShiftInfo	*ShiftDim
									,HLineInBlock &HLine0 ,HLineInBlock &HLine1 ,HLineInBlock &HLine2
									,HLineInBlock &HLine3 ,HLineInBlock &HLine4 ,HLineInBlock &HLine5
									,VLineInBlock &VLine0 ,VLineInBlock &VLine1 ,VLineInBlock &VLine2
									,VLineInBlock &VLine3 ,VLineInBlock &VLine4 ,VLineInBlock &VLine5)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
	int	HCount=0;
	int	VCount=0;
	if(HLine0.IsEffective()==true){
		HCount++;
	}
	if(HLine1.IsEffective()==true){
		HCount++;
	}
	if(HLine2.IsEffective()==true){
		HCount++;
	}
	if(HLine3.IsEffective()==true){
		HCount++;
	}
	if(HLine4.IsEffective()==true){
		HCount++;
	}
	if(HLine5.IsEffective()==true){
		HCount++;
	}
	if(VLine0.IsEffective()==true){
		VCount++;
	}
	if(VLine1.IsEffective()==true){
		VCount++;
	}
	if(VLine2.IsEffective()==true){
		VCount++;
	}
	if(VLine3.IsEffective()==true){
		VCount++;
	}
	if(VLine4.IsEffective()==true){
		VCount++;
	}
	if(VLine5.IsEffective()==true){
		VCount++;
	}

	int	ShiftNumb=0;
	for(int kx=-SelfSearch;kx<=SelfSearch;kx+=Sep){
		for(int ky=-SelfSearch;ky<=SelfSearch;ky+=Sep){
			double	DH[6];
			double	DV[6];
			int		HN=0;
			int		VN=0;
			bool	PlusR=true;
			bool	PlusT=true;
			bool	PlusL=true;
			bool	PlusB=true;
			if(HLine0.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine0.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
				if(DH[HN]<0)
					PlusT=false;
				HN++;
			}
			if(HLine1.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine1.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					PlusT=false;
				HN++;
			}
			if(HLine2.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine2.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					PlusT=false;
				HN++;
			}
			if(HLine3.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine3.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);
				if(DH[HN]<0)
					PlusB=false;
				HN++;
			}
			if(HLine4.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine4.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					PlusB=false;
				HN++;
			}
			if(HLine5.IsEffective()==true){
				DH[HN]=CalcMatchBW(HLine5.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DH[HN]<0)
					PlusB=false;
				HN++;
			}
			if(VLine0.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine0.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					PlusL=false;
				VN++;
			}
			if(VLine1.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine1.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					PlusL=false;
				VN++;
			}
			if(VLine2.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine2.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					PlusL=false;
				VN++;
			}
			if(VLine3.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine3.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					PlusR=false;
				VN++;
			}
			if(VLine4.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine4.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					PlusR=false;
				VN++;
			}
			if(VLine5.IsEffective()==true){
				DV[VN]=CalcMatchBW(VLine5.Match(DBuff,mx+kx,my+ky)
									,RThr->ThreshouldBag.PointMove.ModePermitInverted
									,RThr->ThreshouldBag.PointMove.ModeMatchPosition
									,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

				if(DV[VN]<0)
					PlusR=false;
				VN++;
			}
			if((PlusT==true && PlusL==true)
			|| (PlusT==true && PlusR==true)
			|| (PlusB==true && PlusL==true)
			|| (PlusB==true && PlusR==true)){
				int	N=HN+VN;
				double	D=1.0;
				if(HCount==1)
					D*=DH[0]*DH[0]*DH[0]*DH[0]*DH[0]*DH[0];
				else if(HCount==2)
					D*=DH[0]*DH[1]*DH[1]*DH[0]*DH[0]*DH[1];
				else if(HCount==3)
					D*=DH[0]*DH[1]*DH[2]*DH[0]*DH[1]*DH[2];
				else if(HCount==4)
					D*=DH[0]*DH[1]*DH[2]*DH[3]*DH[0]*DH[1]*DH[2]*DH[3];
				else if(HCount==5)
					D*=DH[0]*DH[1]*DH[2]*DH[3]*DH[4]*DH[0]*DH[1]*DH[2]*DH[3]*DH[4];
				else if(HCount==6)
					D*=DH[0]*DH[1]*DH[2]*DH[3]*DH[4]*DH[5];
				if(VCount==1)
					D*=DV[0]*DV[0]*DV[0]*DV[0]*DV[0]*DV[0];
				else if(VCount==2)
					D*=DV[0]*DV[1]*DV[1]*DV[0]*DV[0]*DV[1];
				else if(VCount==3)
					D*=DV[0]*DV[1]*DV[2]*DV[0]*DV[1]*DV[2];
				else if(VCount==4)
					D*=DV[0]*DV[1]*DV[2]*DV[3]*DV[0]*DV[1]*DV[2]*DV[3];
				else if(VCount==5)
					D*=DV[0]*DV[1]*DV[2]*DV[3]*DV[4]*DV[0]*DV[1]*DV[2]*DV[3]*DV[4];
				else if(VCount==6)
					D*=DV[0]*DV[1]*DV[2]*DV[3]*DV[4]*DV[5];

				if(N>0){
					ShiftDim[ShiftNumb].ShiftX=kx;
					ShiftDim[ShiftNumb].ShiftY=ky;
					ShiftDim[ShiftNumb].MatchResult=D;
					ShiftNumb++;
				}
			}
		}
	}
	return ShiftNumb;
}

double	BlockItem::CalcMatchLinePosition(double mx,double my)
{
	double	DH[6];
	double	DV[6];
	int		HN=0;
	int		VN=0;
	bool	Plus=true;
	const	BlockThreshold	*RThr=GetThresholdR();
	ImageBuffer &DBuff=GetTargetBuff();
	if(FollowLineData->LftMatchLine0.IsEffective()==true){
		DH[HN]=CalcMatchBW(FollowLineData->LftMatchLine0.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DH[HN]<0)
			Plus=false;
		HN++;
	}
	if(FollowLineData->LftMatchLine1.IsEffective()==true){
		DH[HN]=CalcMatchBW(FollowLineData->LftMatchLine1.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DH[HN]<0)
			Plus=false;
		HN++;
	}
	if(FollowLineData->LftMatchLine2.IsEffective()==true){
		DH[HN]=CalcMatchBW(FollowLineData->LftMatchLine2.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DH[HN]<0)
			Plus=false;
		HN++;
	}
	if(FollowLineData->RgtMatchLine0.IsEffective()==true){
		DH[HN]=CalcMatchBW(FollowLineData->RgtMatchLine0.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DH[HN]<0)
			Plus=false;
		HN++;
	}
	if(FollowLineData->RgtMatchLine1.IsEffective()==true){
		DH[HN]=CalcMatchBW(FollowLineData->RgtMatchLine1.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DH[HN]<0)
			Plus=false;
		HN++;
	}				
	if(FollowLineData->RgtMatchLine2.IsEffective()==true){
		DH[HN]=CalcMatchBW(FollowLineData->RgtMatchLine2.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DH[HN]<0)
			Plus=false;
		HN++;
	}
	if(FollowLineData->TopMatchLine0.IsEffective()==true){
		DV[VN]=CalcMatchBW(FollowLineData->TopMatchLine0.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DV[VN]<0)
			Plus=false;
		VN++;
	}
	if(FollowLineData->TopMatchLine1.IsEffective()==true){
		DV[VN]=CalcMatchBW(FollowLineData->TopMatchLine1.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DV[VN]<0)
			Plus=false;
		VN++;
	}
	if(FollowLineData->TopMatchLine2.IsEffective()==true){
		DV[VN]=CalcMatchBW(FollowLineData->TopMatchLine2.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DV[VN]<0)
			Plus=false;
		VN++;
	}
	if(FollowLineData->BtmMatchLine0.IsEffective()==true){
		DV[VN]=CalcMatchBW(FollowLineData->BtmMatchLine0.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DV[VN]<0)
			Plus=false;
		VN++;
	}
	if(FollowLineData->BtmMatchLine1.IsEffective()==true){
		DV[VN]=CalcMatchBW(FollowLineData->BtmMatchLine1.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DV[VN]<0)
			Plus=false;
		VN++;
	}
	if(FollowLineData->BtmMatchLine2.IsEffective()==true){
		DV[VN]=CalcMatchBW(FollowLineData->BtmMatchLine2.Match(DBuff,mx,my)
						,RThr->ThreshouldBag.PointMove.ModePermitInverted
						,RThr->ThreshouldBag.PointMove.ModeMatchPosition
						,RThr->ThreshouldBag.PointMove.ModeMatchPositionBW);

		if(DV[VN]<0)
			Plus=false;
		VN++;
	}
	if(Plus==true){
		double	D=1.0;
		if(HN==1)
			D*=DH[0]*DH[0]*DH[0]*DH[0]*DH[0]*DH[0];
		else if(HN==2)
			D*=DH[0]*DH[1]*DH[1]*DH[0]*DH[0]*DH[1];
		else if(HN==3)
			D*=DH[0]*DH[1]*DH[2]*DH[0]*DH[1]*DH[2];
		else if(HN==4)
			D*=pow(DH[0]*DH[1]*DH[2]*DH[3],1.5);
		else if(HN==5)
			D*=pow(DH[0]*DH[1]*DH[2]*DH[3]*DH[4],1.2);
		else if(HN==6)
			D*=DH[0]*DH[1]*DH[2]*DH[3]*DH[4]*DH[5];
		if(VN==1)
			D*=DV[0]*DV[0]*DV[0]*DV[0]*DV[0]*DV[0];
		else if(VN==2)
			D*=DV[0]*DV[1]*DV[1]*DV[0]*DV[0]*DV[1];
		else if(VN==3)
			D*=DV[0]*DV[1]*DV[2]*DV[0]*DV[1]*DV[2];
		else if(VN==4)
			D*=pow(DV[0]*DV[1]*DV[2]*DV[3],1.5);
		else if(VN==5)
			D*=pow(DV[0]*DV[1]*DV[2]*DV[3]*DV[4],1.2);
		else if(VN==6)
			D*=DV[0]*DV[1]*DV[2]*DV[3]*DV[4]*DV[5];
		return D;
	}
	return 0;
}