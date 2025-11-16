/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1Processor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XEulerRingL1.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingL1Library.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XCriticalFunc.h"

//=====================================================================================

EulerRingL1HistogramListReq::EulerRingL1HistogramListReq(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;
}
bool	EulerRingL1HistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	EulerRingL1HistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


EulerRingL1HistogramListSend::EulerRingL1HistogramListSend(void)
{
	GlobalPage=-1;
	Layer		=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));
	CenterBright		=0;
	CenterTargetBright	=0;
}
void	EulerRingL1HistogramListSend::ConstructList(EulerRingL1HistogramListReq *reqPacket ,EulerRingL1Base *Base)
{
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(BlockItemID);
				
			EulerRingL1Item	*Item=dynamic_cast<EulerRingL1Item*>(item);
			bool	BuiltList=false;
			if(item->IsOriginParts()==true && Item->GetThresholdR(Ap->GetLayersBase())->PointMove.ModeCenterBrightFromParts==true){
				PieceClass	*Pc=NULL;
				Pc=Base->GetLayersBase()->GetPieceStock()->SearchOnly(item->GetPartsID());
				if(Pc!=NULL){
					QString DLLRoot ,DLLName;
					Base->GetAlgorithmRootName(DLLRoot ,DLLName);
					AlgorithmItemRoot	*PItem=Pc->GetAlgorithmItem(DLLRoot,DLLName,Layer ,item->GetPartsItemID());
					if(PItem->GetDataInLayer()->GetMasterBuff().IsNull()==false)
						PItem->GetArea().MakeBrightList(ListMaster ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetMasterBuff(),0 ,0);
					else if(PItem->GetDataInLayer()->GetTargetBuff().IsNull()==false)
						PItem->GetArea().MakeBrightList(ListMaster ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetTargetBuff(),0 ,0);
					BuiltList=true;
				}
			}
			if(BuiltList==false){
				if(Item->GetMasterBuff().IsNull()==false)
					item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
				else if(Item->GetTargetBuff().IsNull()==false)
					item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
			}
			
			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				if(Rp!=NULL){
					ResultInLayerPLI	&rLayer=Rp->GetLayerData(Item->GetParent()->GetLayer());
					ResultInItemPLI		*rItem=rLayer.FindResultInItem(Item->GetID());
					if(rItem!=NULL){
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
					}
					else
						item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
				}	
				CenterBright		=Item->CenterBright;
				CenterTargetBright	=Item->CenterTargetBright;
			}
		}
	}
}

bool	EulerRingL1HistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(f->write((const char *)ListMaster,sizeof(ListMaster))!=sizeof(ListMaster))
		return false;
	if(f->write((const char *)ListTarget,sizeof(ListTarget))!=sizeof(ListTarget))
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,CenterTargetBright)==false)
		return false;
	return true;
}
bool	EulerRingL1HistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(f->read((char *)ListMaster,sizeof(ListMaster))!=sizeof(ListMaster))
		return false;
	if(f->read((char *)ListTarget,sizeof(ListTarget))!=sizeof(ListTarget))
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,CenterTargetBright)==false)
		return false;
	return true;
}

EulerRingL1ThresholdReq::EulerRingL1ThresholdReq(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Layer		=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	EulerRingL1ThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	EulerRingL1ThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
EulerRingL1ThresholdSend::EulerRingL1ThresholdSend(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;

	CenterBright		=0;
	CenterTargetBright	=0;

	DarkWidth			=0;		//For ring brightness
	LightWidth			=0;
	MinHoleDiameter		=0;
	MaxHoleDiameter		=0;
	MaxShiftHole		=0;
	ConnectLen			=0;	
	ExpandForDynamicMask=0;

    AdjustBlack			=0;	//For ring brightness
    AdjustWhite			=0;
	SearchDot			=0;
	HoleBrightnessAsReference	=0;

	AbsBrightWidthL		=0;
	AbsBrightWidthH		=0;
	BrightWidthL		=0;
	BrightWidthH		=0;
}

void	EulerRingL1ThresholdSend::ConstructList(EulerRingL1ThresholdReq *reqPacket,EulerRingL1Base *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(BlockItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				EulerRingL1Item	*BItem=(EulerRingL1Item *)item;
				const EulerRingL1Threshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				CenterBright	=BItem->CenterBright;
				BrightWidthL	=RThr->DarkWidth;
				BrightWidthH	=RThr->LightWidth;

				int	TmpBrightWidthL=BrightWidthL;
				int	TmpBrightWidthH=BrightWidthH;
				if(RThr->PointMove.ModeAbsoluteBright==true){
					AbsBrightWidthL=TmpBrightWidthL;
					AbsBrightWidthH=TmpBrightWidthH;
				}
				else{
					AbsBrightWidthL=CenterBright-TmpBrightWidthL;
					AbsBrightWidthH=CenterBright+TmpBrightWidthH;
				}

				CenterTargetBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),dx,dy);

				int	D=CenterTargetBright-CenterBright;
				if(D<0){
					if(-D> RThr->AdjustBlack){
						D=-RThr->AdjustBlack;
					}
				}
				else if(D>0){
					if(D> RThr->AdjustWhite){
						D=RThr->AdjustWhite;
					}
				}
				AbsBrightWidthL=(CenterBright+D)-RThr->DarkWidth;
				AbsBrightWidthH=(CenterBright+D)+RThr->LightWidth;

				DarkWidth				=RThr->DarkWidth;		//For ring brightness
				LightWidth				=RThr->LightWidth;
				MinHoleDiameter			=RThr->MinHoleDiameter;
				MaxHoleDiameter			=RThr->MaxHoleDiameter;
				MaxShiftHole			=RThr->MaxShiftHole;
				ConnectLen				=RThr->ConnectLen;		//‚m‚fÚ‘±‹——£
				ExpandForDynamicMask	=RThr->ExpandForDynamicMask;

				AdjustBlack				=RThr->AdjustBlack;	//For ring brightness
				AdjustWhite				=RThr->AdjustWhite; 
				SearchDot				=RThr->SearchDot; 
				HoleBrightnessAsReference=RThr->HoleBrightnessAsReference;
			}
		}
	}
}

bool	EulerRingL1ThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,CenterTargetBright)==false)
		return false;

	if(::Save(f,DarkWidth)==false)
		return false;
	if(::Save(f,LightWidth)==false)
		return false;
	if(::Save(f,MinHoleDiameter)==false)
		return false;
	if(::Save(f,MaxHoleDiameter)==false)
		return false;
	if(::Save(f,MaxShiftHole)==false)
		return false;
	if(::Save(f,ConnectLen)==false)
		return false;
	if(::Save(f,ExpandForDynamicMask)==false)
		return false;

    if(::Save(f,AdjustBlack)==false)
		return false;
    if(::Save(f,AdjustWhite)==false)
		return false;
    if(::Save(f,SearchDot)==false)
		return false;
    if(::Save(f,HoleBrightnessAsReference)==false)
		return false;

	if(::Save(f,AbsBrightWidthL)==false)
		return false;
	if(::Save(f,AbsBrightWidthH)==false)
		return false;
	if(::Save(f,BrightWidthL)==false)
		return false;
	if(::Save(f,BrightWidthH)==false)
		return false;

	return true;
}
bool	EulerRingL1ThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,CenterTargetBright)==false)
		return false;

	if(::Load(f,DarkWidth)==false)
		return false;
	if(::Load(f,LightWidth)==false)
		return false;
	if(::Load(f,MinHoleDiameter)==false)
		return false;
	if(::Load(f,MaxHoleDiameter)==false)
		return false;
	if(::Load(f,MaxShiftHole)==false)
		return false;
	if(::Load(f,ConnectLen)==false)
		return false;
	if(::Load(f,ExpandForDynamicMask)==false)
		return false;

    if(::Load(f,AdjustBlack)==false)
		return false;
    if(::Load(f,AdjustWhite)==false)
		return false;
    if(::Load(f,SearchDot)==false)
		return false;
    if(::Load(f,HoleBrightnessAsReference)==false)
		return false;

	if(::Load(f,AbsBrightWidthL)==false)
		return false;
	if(::Load(f,AbsBrightWidthH)==false)
		return false;
	if(::Load(f,BrightWidthL)==false)
		return false;
	if(::Load(f,BrightWidthH)==false)
		return false;

	return true;
}

//=====================================================================================================
EulerRingL1ReqTryThreshold::EulerRingL1ReqTryThreshold(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
}
bool	EulerRingL1ReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	EulerRingL1ReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

EulerRingL1SendTryThreshold::EulerRingL1SendTryThreshold(void)
{
	Result	=new ResultInItemPLI();
	MasterHoleDiameter=0;
	HoleDiameter	=0;
	HoleShift		=0;
	Ring			=true;
}
EulerRingL1SendTryThreshold::~EulerRingL1SendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	EulerRingL1SendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,MasterHoleDiameter	)==false)
		return false;
	if(::Save(f,HoleDiameter	)==false)
		return false;
	if(::Save(f,HoleShift	)==false)
		return false;
	if(::Save(f,Ring	)==false)
		return false;
	return true;
}
bool	EulerRingL1SendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,MasterHoleDiameter	)==false)
		return false;
	if(::Load(f,HoleDiameter	)==false)
		return false;
	if(::Load(f,HoleShift	)==false)
		return false;
	if(::Load(f,Ring	)==false)
		return false;
	return true;
}

void	EulerRingL1SendTryThreshold::ConstructList(EulerRingL1ReqTryThreshold *reqPacket,EulerRingL1Base *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	EulerRingL1InPage	*Ap=(EulerRingL1InPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(reqPacket->Layer));
		if(AL!=NULL){
			EulerRingL1Item	*BI=(EulerRingL1Item *)AL->SearchIDItem(reqPacket->BlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.CenterBright						=BI->CenterBright;
				reqPacket->Threshold.CenterTargetBright					=BI->CenterTargetBright;
				reqPacket->Threshold.MasterHoleDiameter					=BI->MasterHoleDiameter;
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.CopyArea(*BI);
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				reqPacket->Threshold.ExecuteInitialAfterEdit (0,0,Result,EInfo);
				reqPacket->Threshold.ExecuteStartByInspection(0,0,Result);
				reqPacket->Threshold.AVector							=BI->AVector;
				reqPacket->Threshold.TestMode=true;
				reqPacket->Threshold.ExecutePreProcessing	 (0,0,Result);

				MasterHoleDiameter	=BI->MasterHoleDiameter;
				HoleDiameter=reqPacket->Threshold.ResultHoleDiameter;
				HoleShift	=reqPacket->Threshold.ResultHoleShift;
			}
		}
	}
	Result->SetAddedData(NULL,0);

	Ring		=Result->GetError();
}


void	EulerRingL1ChangeShift::Reflect(EulerRingL1Base *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(BlockItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	EulerRingL1ChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	EulerRingL1ChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

