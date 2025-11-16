/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ThinMetal\XThinMetal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "ThinMetalFormResource.h"
#include "XThinMetal.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XThinMetalLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"
#include "XAlignmentCommon.h"
#include "XAlgorithmDLL.h"
#include "XDisplaySimPanel.h"
#include "XThinMetalAlgoPacket.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


unsigned short	Mult256Table[256][256];
const	int		SepNumb=10;


ThinMetalHistogramListReq::ThinMetalHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	ThinMetalItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	ThinMetalHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThinMetalItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ThinMetalHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ThinMetalItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


ThinMetalHistogramListSend::ThinMetalHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	ThinMetalItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));
	CenterBright		=0;
	CenterTargetBright	=0;
}
void	ThinMetalHistogramListSend::ConstructList(ThinMetalHistogramListReq *reqPacket ,ThinMetalBase *Base)
{
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ThinMetalItemID	=reqPacket->ThinMetalItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ThinMetalItemID);
			if(item!=NULL){
				ThinMetalItem	*Item=dynamic_cast<ThinMetalItem*>(item);
				bool	BuiltList=false;
				if(BuiltList==false){
					item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
				}
			
				ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
				if(DRes!=NULL){
					ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
					ResultBasePhase	*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
					ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
					if(Rp!=NULL){
						ResultInLayerPLI	&rLayer=Rp->GetLayerData(Item->GetParent()->GetLayer());
						ResultInItemPLI		*rItem=rLayer.FindResultInItem(Item->GetID());
						if(rItem!=NULL){
							int	sx,sy;
							rItem->GetTotalShifted(sx,sy);
							item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
						}
						else{
							item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
						}
					}
				}
				CenterBright		=Item->CenterBright;
				CenterTargetBright	=Item->CenterTargetBright;
			}
		}
	}
}

bool	ThinMetalHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThinMetalItemID)==false)
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
bool	ThinMetalHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ThinMetalItemID)==false)
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
ThinMetalThresholdReq::ThinMetalThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	ThinMetalItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	ThinMetalThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThinMetalItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ThinMetalThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ThinMetalItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

ThinMetalThresholdSend::ThinMetalThresholdSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	ThinMetalItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;

	CenterBright		=0;
	CenterTargetBright	=0;
	AbsBrightWidthL		=0;
	AbsBrightWidthH		=0;
	ShrinkDot			=0;
	EnlargeDot			=0;
}

void	ThinMetalThresholdSend::ConstructList(ThinMetalThresholdReq *reqPacket,ThinMetalBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ThinMetalItemID	=reqPacket->ThinMetalItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerRoot	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ThinMetalItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				ThinMetalItem	*BItem=(ThinMetalItem *)item;
				if(BItem->CenterBright==0){
					//BItem->CenterBright=BItem->CalcCenterBright(BItem->GetMasterBuff(),0,0);
					BItem->CenterTargetBright=BItem->CenterBright;
				}
				CenterBright	=BItem->CenterBright;
				const ThinMetalThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				AbsBrightWidthL	=RThr->BrightWidthL;
				AbsBrightWidthH	=RThr->BrightWidthH;

				//CenterTargetBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),dx,dy);
			}
		}
	}
}

bool	ThinMetalThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThinMetalItemID)==false)
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

	if(::Save(f,AbsBrightWidthL)==false)
		return false;
	if(::Save(f,AbsBrightWidthH)==false)
		return false;
	if(::Save(f,ShrinkDot)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	return true;
}
bool	ThinMetalThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ThinMetalItemID)==false)
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

	if(::Load(f,AbsBrightWidthL)==false)
		return false;
	if(::Load(f,AbsBrightWidthH)==false)
		return false;
	if(::Load(f,ShrinkDot)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;

	return true;
}

ThinMetalReqTryThreshold::ThinMetalReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	ThinMetalItemID=-1;
}
bool	ThinMetalReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThinMetalItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	ThinMetalReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ThinMetalItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

ThinMetalSendTryThreshold::ThinMetalSendTryThreshold(void)
{
	NGDotInDark	=0;
	NGDotInBright	=0;
	Error			=0;
	Result	=new ResultInItemPLI();
}
ThinMetalSendTryThreshold::~ThinMetalSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}


bool	ThinMetalSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotInDark	)==false)
		return false;
	if(::Save(f,NGDotInBright	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(Result->Save(f)==false)
		return false;
	return true;
}
bool	ThinMetalSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotInDark	)==false)
		return false;
	if(::Load(f,NGDotInBright	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(Result->Load(f)==false)
		return false;
	return true;
}

void	ThinMetalSendTryThreshold::ConstructList(ThinMetalReqTryThreshold *reqPacket,ThinMetalBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	ThinMetalInPage		*BP=(ThinMetalInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		ThinMetalInLayer	*BL=(ThinMetalInLayer *)BP->GetLayerData(reqPacket->Layer);
		if(BL!=NULL){
			ThinMetalItem		*BI=(ThinMetalItem *)BL->SearchIDItem(reqPacket->ThinMetalItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.CenterBright						=BI->CenterBright;
				reqPacket->Threshold.AVector							=BI->AVector;
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.CopyArea(*BI);
				reqPacket->Threshold.ExecuteProcessing(0,0,Result);
			}
		}
	}
	Result->SetAddedData(NULL,0);

}


//=====================================================================================
void	ThinMetalChangeShift::Reflect(ThinMetalBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ThinMetalItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	ThinMetalChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThinMetalItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ThinMetalChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ThinMetalItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
//=====================================================================================
ThinMetalThreshold::ThinMetalThreshold(ThinMetalItem *parent)
:AlgorithmThreshold(parent)
{
	BrightWidthL	=0;
	BrightWidthH	=0;
	OKDotL			=0;
	OKDotH			=0;
	MaxNGDotL		=99999999;
	MaxNGDotH		=99999999;
	OKLengthL		=0;
	OKLengthH		=0;

	SpaceToOutline	=0;
	ShrinkDot		=1;
	EnlargeDot		=1;
}

void	ThinMetalThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ThinMetalThreshold *s=(const ThinMetalThreshold *)&src;
	BrightWidthL	=s->BrightWidthL;
	BrightWidthH	=s->BrightWidthH;
	OKDotL			=s->OKDotL;
	OKDotH			=s->OKDotH;
	MaxNGDotL		=s->MaxNGDotL;
	MaxNGDotH		=s->MaxNGDotH;
	OKLengthL		=s->OKLengthL;
	OKLengthH		=s->OKLengthH;
	
	SpaceToOutline	=s->SpaceToOutline;
	ShrinkDot		=s->ShrinkDot;
	EnlargeDot		=s->EnlargeDot;
}
bool	ThinMetalThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ThinMetalThreshold *s=(const ThinMetalThreshold *)&src;
	if(BrightWidthL		!=s->BrightWidthL	)	return false;
	if(BrightWidthH		!=s->BrightWidthH	)	return false;
	if(OKDotL			!=s->OKDotL			)	return false;
	if(OKDotH			!=s->OKDotH			)	return false;
	if(MaxNGDotL		!=s->MaxNGDotL		)	return false;
	if(MaxNGDotH		!=s->MaxNGDotH		)	return false;
	if(OKLengthL		!=s->OKLengthL		)	return false;
	if(OKLengthH		!=s->OKLengthH		)	return false;

	if(SpaceToOutline	!=s->SpaceToOutline	)	return false;
	if(ShrinkDot		!=s->ShrinkDot		)	return false;
	if(EnlargeDot		!=s->EnlargeDot		)	return false;
	return true;
}
bool	ThinMetalThreshold::Save(QIODevice *file)
{
	WORD	Ver=ThinMetalVersion;

	if(::Save(file,Ver)==false)
		return false;
	if(::Save(file,BrightWidthL)==false)
		return false;
	if(::Save(file,BrightWidthH)==false)
		return false;
	if(::Save(file,OKDotL)==false)
		return false;
	if(::Save(file,OKDotH)==false)
		return false;
	if(::Save(file,OKLengthL)==false)
		return false;
	if(::Save(file,OKLengthH)==false)
		return false;

	if(::Save(file,SpaceToOutline)==false)
		return false;

	if(::Save(file,MaxNGDotL)==false)
		return false;
	if(::Save(file,MaxNGDotH)==false)
		return false;

	if(::Save(file,ShrinkDot)==false)
		return false;
	if(::Save(file,EnlargeDot)==false)
		return false;

	return true;
}
bool	ThinMetalThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;
	if(::Load(file,BrightWidthL)==false)
		return false;
	if(::Load(file,BrightWidthH)==false)
		return false;
	if(::Load(file,OKDotL)==false)
		return false;
	if(::Load(file,OKDotH)==false)
		return false;
	if(::Load(file,OKLengthL)==false)
		return false;
	if(::Load(file,OKLengthH)==false)
		return false;

	if(::Load(file,SpaceToOutline)==false)
		return false;

	if(::Load(file,MaxNGDotL)==false)
		return false;
	if(::Load(file,MaxNGDotH)==false)
		return false;

	if(::Load(file,ShrinkDot)==false)
		return false;
	if(::Load(file,EnlargeDot)==false)
		return false;

	return true;
}

void	ThinMetalThreshold::FromLibrary(AlgorithmLibrary *src)
{
	ThinMetalLibrary	*LSrc=dynamic_cast<ThinMetalLibrary *>(src);
	if(LSrc==NULL)
		return;
	BrightWidthL	=LSrc->BrightWidthL;
	BrightWidthH	=LSrc->BrightWidthH;
	OKDotL			=LSrc->OKDotL;
	OKDotH			=LSrc->OKDotH;
	MaxNGDotL		=LSrc->MaxNGDotL;
	MaxNGDotH		=LSrc->MaxNGDotH;
	OKLengthL		=LSrc->OKLengthL;
	OKLengthH		=LSrc->OKLengthH;
	
	SpaceToOutline	=LSrc->SpaceToOutline;
	ShrinkDot		=LSrc->ShrinkDot;
	EnlargeDot		=LSrc->EnlargeDot;
}
void	ThinMetalThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	ThinMetalLibrary	*LDst=dynamic_cast<ThinMetalLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->BrightWidthL	=BrightWidthL;
	LDst->BrightWidthH	=BrightWidthH;
	LDst->OKDotL		=OKDotL		;
	LDst->OKDotH		=OKDotH	;
	LDst->MaxNGDotL		=MaxNGDotL;
	LDst->MaxNGDotH		=MaxNGDotH;
	LDst->OKLengthL		=OKLengthL		;
	LDst->OKLengthH		=OKLengthH	;

	LDst->SpaceToOutline=SpaceToOutline;
	LDst->ShrinkDot		=ShrinkDot;
	LDst->EnlargeDot	=EnlargeDot;
}

//====================================================================================================

//====================================================================================================


ThinMetalItem::ThinMetalItem(void)
{
	InitialConstructor();
}

void ThinMetalItem::InitialConstructor(void)
{
	CenterBright	=0;
	AVector=NULL;

	ThreshL=ThreshH	=0;
	RepeatableCount	=0;
	CurrentNGCount	=0;
	RegNumber		=0;
	Condition	=_AverageMustBeInside;

	CurrentBrightness	=0;
	ResultOK			=true;
	CenterBright		=0;
	CenterTargetBright	=0;

	MList	=NULL;
	MListNumb=0;
	AllocatedMListNumb	=0;
	LastAreaX1=LastAreaY1=LastAreaX2=LastAreaY2=0;
}
ThinMetalItem::~ThinMetalItem(void)
{
	if(MList!=NULL){
		delete	[]MList;
		MList=NULL;
		AllocatedMListNumb=0;
	}
}

AlgorithmItemPLI	&ThinMetalItem::operator=(const AlgorithmItemRoot &src)
{
	const ThinMetalItem	*s=dynamic_cast<const ThinMetalItem *>(&src);
	if(s!=NULL)
		return AlgorithmItemPLI::operator=(src);
	return *this;
}
ThinMetalItem &ThinMetalItem::operator=(ThinMetalItem &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(src);

	return *this;
}
void	ThinMetalItem::CopyArea(ThinMetalItem &src)
{
	SetArea(src.GetArea());
}

void	ThinMetalItem::CopyThreshold(ThinMetalItem &src)
{
	CenterBright	=src.CenterBright;
	GetThresholdW()->CopyFrom(*((ThinMetalThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	ThinMetalItem::CopyThresholdOnly(ThinMetalItem &src)
{
	GetThresholdW()->CopyFrom(*((ThinMetalThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

bool    ThinMetalItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;
	if(::Save(file,CenterBright)==false)
		return false;
	if(SampleImages.Save(file)==false)
		return false;

	return true;
}
bool    ThinMetalItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	if(::Load(file,CenterBright)==false)
		return false;
	if(GetLoadedVersion()>=2){
		if(SampleImages.Load(file)==false)
			return false;
		for(CoeffImageList *a=SampleImages.GetFirst();a!=NULL;a=a->GetNext()){
			a->CalcAA(SepNumb);
		}
	}
	return true;
}

void	ThinMetalItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			ThinMetalInLayer	*Ly=dynamic_cast<ThinMetalInLayer *>(GetParentInLayer());
			UndoElement<ThinMetalInLayer>	*UPointer=new UndoElement<ThinMetalInLayer>(Ly,&ThinMetalInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ThinMetalItem *src=(ThinMetalItem *)Data;
			CopyThresholdOnly(*src);
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			//CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((ThinMetalItem *)Data)->GetLibID()){
			ThinMetalInLayer	*Ly=dynamic_cast<ThinMetalInLayer *>(GetParentInLayer());
			UndoElement<ThinMetalInLayer>	*UPointer=new UndoElement<ThinMetalInLayer>(Ly,&ThinMetalInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ThinMetalItem *src=(ThinMetalItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
			//CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((ThinMetalItem *)Data)->GetLibID()){
			ThinMetalInLayer	*Ly=dynamic_cast<ThinMetalInLayer *>(GetParentInLayer());
			UndoElement<ThinMetalInLayer>	*UPointer=new UndoElement<ThinMetalInLayer>(Ly,&ThinMetalInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ThinMetalItem *src=(ThinMetalItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}

void	ThinMetalItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	ThinMetalItem	*ASrc=dynamic_cast<ThinMetalItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((ThinMetalBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		CenterBright	=ASrc->CenterBright;
	}
}

ExeResult	ThinMetalItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	
	int	cx,cy;
	//_CrtCheckMemory();

	int	gap=((ThinMetalBase *)GetParentBase())->OmitZoneDot;
	if(GetLayersBase()->GetBootingLevel()>=1){
		gap=5;
	}
	if(GetFromRental()==false){
		GetArea().ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
	}

	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	if(LastAreaX1!=x1 || LastAreaY1!=y1
	|| LastAreaX2!=x2 || LastAreaY2!=y2){
		LastAreaX1=x1;
		LastAreaY1=y1;
		LastAreaX2=x2;
		LastAreaY2=y2;
		ImageBuffer		&IBuff=GetTargetBuff();
		for(CoeffImageList *s=SampleImages.GetFirst();s!=NULL;s=s->GetNext()){
			s->SetImage(IBuff,x1,y1,x2,y2,SepNumb);
		}
	}

	//_CrtCheckMemory();

	return Ret;
}




void	ThinMetalItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ThinMetalDrawAttr	*BAttr=dynamic_cast<ThinMetalDrawAttr *>(Attr);
	if(BAttr!=NULL){
		ThinMetalDrawAttr	TmpAttr(GetLayersBase());
		TmpAttr=*BAttr;
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	ThinMetalItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false){	// && ZoomRate>0.5){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						+QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())+QString(/**/",")+QString::number((int)Res->GetTotalShiftedY())+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
					if(Res->GetError()>=2){
						PData.drawText(kx,ky+24
								,GetNGString(Res->GetError()));
						PData.drawText(kx,ky+40
								,QString(/**/"Matching=")+QString::number(((double)Res->GetResult1())/100.0,'f',1) +QString(/**/"%")
								);
						if(SampleImages[Res->GetResult2()]!=NULL){
							PData.drawText(kx,ky+56
								,SampleImages[Res->GetResult2()]->TargetFileName
								);
						}
					}
				}
			}
		}
	}
}

QString	ThinMetalItem::GetNGString(int judgeNo)
{
	switch(judgeNo){
	case 2:	return /**/"NG1";
	case 3:	return /**/"NG2";
	case 4:	return /**/"NG3";
	case 5:	return /**/"NG4";
	}
	return /**/"";
}

void	ThinMetalItem::StoreTargetImageToSamples(int Judgement,const QString &TargetFolder ,const QString &TargetFileName)
{
	ImageBuffer		&IBuff=GetTargetBuff();
	CoeffImageList	*s=new CoeffImageList();
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	s->SetImage(IBuff,x1,y1,x2,y2,SepNumb);
	s->Judgement=Judgement;
	s->TargetFolder		=TargetFolder;
	s->TargetFileName	=TargetFileName;
	SampleImages.AppendList(s);
}
void	ThinMetalItem::ClearSampleImages(void)
{
	SampleImages.RemoveAll();
}

int	MListFunc(const void *a ,const void *b)
{
	struct	MatchingList	*pa=(struct	MatchingList *)a;
	struct	MatchingList	*pb=(struct	MatchingList *)b;

	double	d=pa->Result - pb->Result;
	if(d<0)
		return 1;
	if(d>0)
		return -1;
	return 0;
}


int		ThinMetalItem::MatchSamples(int mx ,int my ,int swing ,int &Dx ,int &Dy,double &Result ,int &SampleNo)
{
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);

	int		N=(2*swing+1)*(2*swing+1) *SampleImages.GetCount();
	if(N>AllocatedMListNumb || MList==NULL){
		if(MList!=NULL){
			delete	[]MList;
		}
		AllocatedMListNumb=N;
		MList=new struct MatchingList[AllocatedMListNumb];
	}

	int	Index=0;
	for(int dy=-swing;dy<=swing;dy+=3){
		for(int dx=-swing;dx<=swing;dx+=3){
			double	B,BB;
			CalcTargetImage(dx,dy,B,BB,SepNumb);

			for(CoeffImageList *a=SampleImages.GetFirst();a!=NULL;a=a->GetNext()){
				MList[Index].dx=dx;
				MList[Index].dy=dy;
				MList[Index].B =B;
				MList[Index].BB=BB;
				MList[Index].Point=a;
				Index++;
			}
		}
	}
	MListNumb=Index;
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Index;i++){
			double	D=MList[i].Point->GetRoughMatch  (GetTargetBuff()
										,MList[i].dx+mx, MList[i].dy+my ,MList[i].B ,MList[i].BB,SepNumb);
			MList[i].Result=D;
		}
	}
	QSort(MList,Index,sizeof(struct	MatchingList),MListFunc);

	int	NCount=Index/100;
	if(NCount>0){
		if(NCount<50)
			NCount=Index;

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<NCount;i++){
				double	MaxD=0;
				int		MaxDx=0;
				int		MaxDy=0;
				for(int dy=-2;dy<=2;dy++){
					for(int dx=-2;dx<=2;dx++){
						double	B,BB;
						CalcTargetImage(mx+MList[i].dx+dx, my+MList[i].dy+dy,B,BB,SepNumb);
						double	D=MList[i].Point->GetRoughMatch  (GetTargetBuff()
														,mx+MList[i].dx+dx, my+MList[i].dy+dy ,B ,BB,SepNumb);
						#pragma omp critical
						{
							if(D>MaxD){
								MaxD=D;
								MaxDx=dx;
								MaxDy=dy;
							}
						}
					}
				}
				MList[i].dx+=MaxDx;
				MList[i].dy+=MaxDy;
			}
		}

		int	MaxPointIndex=0;
		double	MaxD=0;
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<NCount;i++){
				double	B,BB;
				CalcTargetImage(mx+MList[i].dx, my+MList[i].dy,B,BB,1);
				double	D=MList[i].Point->GetPreciseMatch  (GetTargetBuff()
												,mx+MList[i].dx, my+MList[i].dy ,B ,BB);
				#pragma omp critical
				{
					if(D>MaxD){
						MaxD=D;
						MaxPointIndex=i;
					}
				}
			}
		}
		MListNumb=NCount;

		Dx=MList[MaxPointIndex].dx;
		Dy=MList[MaxPointIndex].dy;
		int	Judgement=MList[MaxPointIndex].Point->Judgement;
		Result	=MaxD;
		SampleNo=0;
		for(CoeffImageList *a=SampleImages.GetFirst();a!=NULL;a=a->GetNext(),SampleNo++){
			if(a==MList[MaxPointIndex].Point)
				break;
		}

		return Judgement;
	}
	return -1;
}

void	ThinMetalItem::CalcTargetImage(int dx,int dy,double &B,double &BB,int Sep)
{
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	B=0;
	BB=0;
	for(int y=y1;y<y2;y+=Sep){
		BYTE	*s=GetTargetBuff().GetY(y+dy);
		int	iB=0;
		int	iBB=0;
		for(int x=x1;x<x2;x+=Sep){
			iB+=s[x+dx];
			iBB+=s[x+dx]*s[x+dx];
		}
		B+=iB;
		BB+=iBB;
	}
}

void	ThinMetalItem::DeleteSamples(IntList &Numbers)
{
	CoeffImageList	**Dim=new CoeffImageList *[Numbers.GetCount()];
	int	N=0;
	for(IntClass *d=Numbers.GetFirst();d!=NULL;d=d->GetNext(),N++){
		Dim[N]=SampleImages.GetItem(d->GetValue());
	}
	for(int i=0;i<N;i++){
		if(Dim[i]!=NULL){
			SampleImages.RemoveList(Dim[i]);
		}
	}
	for(int i=0;i<N;i++){
		delete	Dim[i];
	}
	delete	[]Dim;
}
//===========================================================================================

ThinMetalInLayer::ThinMetalInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLITemplate<ThinMetalItem,ThinMetalInPage,ThinMetalBase>(parent)
{
}

AlgorithmItemRoot	*ThinMetalInLayer::CreateItem(int ItemClassType)
{	
	if(ItemClassType==0){
		ThinMetalItem	*a=new ThinMetalItem();	
		a->SetParent(this);
		return a;
	}
	else{
		return NULL;
	}
}
bool	ThinMetalInLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfThinMetal	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfThinMetal	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}



void	ThinMetalInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedThinMetalFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedThinMetalFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		ThinMetalItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ThinMetalItem	*B=(ThinMetalItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
		return;
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				ThinMetalItem	*B=(ThinMetalItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestThinMetalPacket	*CmdClearTestThinMetalPacketVar=dynamic_cast<CmdClearTestThinMetalPacket *>(packet);
	if(CmdClearTestThinMetalPacketVar!=NULL){
		return;
	}
	CmdThinMetalInfoListPacket	*CmdThinMetalInfoListPacketVar=dynamic_cast<CmdThinMetalInfoListPacket *>(packet);
	if(CmdThinMetalInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ThinMetalInfoList	*a=new ThinMetalInfoList();
			a->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			a->Layer		=GetLayer();
			a->ItemID		=L->GetID();
			a->LibID		=L->GetLibID();
			L->GetXY(a->x1,a->y1,a->x2,a->y2);
			CmdThinMetalInfoListPacketVar->ThinMetalInfos->AppendList(a);
		}
		return;
	}
	CmdGetThinMetalFromList	*CmdGetThinMetalFromListVar=dynamic_cast<CmdGetThinMetalFromList *>(packet);
	if(CmdGetThinMetalFromListVar!=NULL){
		ThinMetalItem *Item=(ThinMetalItem *)SearchIDItem(CmdGetThinMetalFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetThinMetalFromListVar->ThinMetalInfoOnMouse=Item;
		return;
	}
	CmdCreateThinMetalItem	*CmdCreateThinMetalItemVar=dynamic_cast<CmdCreateThinMetalItem *>(packet);
	if(CmdCreateThinMetalItemVar!=NULL){
		CmdCreateThinMetalItemVar->ThinMetal=(ThinMetalItem *)CreateItem(0);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		ThinMetalItem *Item=(ThinMetalItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);
			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
		}
		return;
	}
	CmdReqStoreThinMetal	*CmdReqStoreThinMetalVar=dynamic_cast<CmdReqStoreThinMetal *>(packet);
	if(CmdReqStoreThinMetalVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ThinMetalItem	*Item=dynamic_cast<ThinMetalItem *>(L);
			if(Item!=NULL && (Item->GetItemName()==CmdReqStoreThinMetalVar->JudgeStr || CmdReqStoreThinMetalVar->Judgement==1 || Item->GetItemName().isEmpty()==true)){
				Item->StoreTargetImageToSamples(CmdReqStoreThinMetalVar->Judgement
												,CmdReqStoreThinMetalVar->TargetFolder
												,CmdReqStoreThinMetalVar->TargetFileName);
			}
		}
		return;
	}
	CmdReqStoreThinMetalStart	*CmdReqStoreThinMetalStartVar=dynamic_cast<CmdReqStoreThinMetalStart *>(packet);
	if(CmdReqStoreThinMetalStartVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ThinMetalItem	*Item=dynamic_cast<ThinMetalItem *>(L);
			if(Item!=NULL){
				Item->ClearSampleImages();
			}
		}
		return;
	}
	CmdReqStoreThinMetalEnd	*CmdReqStoreThinMetalEndVar=dynamic_cast<CmdReqStoreThinMetalEnd *>(packet);
	if(CmdReqStoreThinMetalEndVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ThinMetalItem	*Item=dynamic_cast<ThinMetalItem *>(L);
			if(Item!=NULL){
				Item->FinalizeSampleImages();
			}
		}
		return;
	}
	CmdReqSampleList	*CmdReqSampleListVar=dynamic_cast<CmdReqSampleList *>(packet);
	if(CmdReqSampleListVar!=NULL){
		AlgorithmItemRoot	*h=SearchIDItem(CmdReqSampleListVar->ItemID);
		if(h!=NULL){
			ThinMetalItem	*Item=dynamic_cast<ThinMetalItem *>(h);
			if(Item!=NULL){
				for(CoeffImageList *a=Item->SampleImages.GetFirst();a!=NULL;a=a->GetNext()){
					CmdReqSampleListVar->Judgement->Add(a->Judgement);
				}
			}
		}
		return;
	}
	CmdReqSampleDetail	*CmdReqSampleDetailVar=dynamic_cast<CmdReqSampleDetail *>(packet);
	if(CmdReqSampleDetailVar!=NULL){
		AlgorithmItemRoot	*h=SearchIDItem(CmdReqSampleDetailVar->ItemID);
		if(h!=NULL){
			ThinMetalItem	*Item=dynamic_cast<ThinMetalItem *>(h);
			if(Item!=NULL){
				CmdReqSampleDetailVar->Point=Item->SampleImages.GetItem(CmdReqSampleDetailVar->Number);
			}
		}
		return;
	}
	CmdReqDeleteSample	*CmdReqDeleteSampleVar=dynamic_cast<CmdReqDeleteSample *>(packet);
	if(CmdReqDeleteSampleVar!=NULL){
		AlgorithmItemRoot	*h=SearchIDItem(CmdReqDeleteSampleVar->ItemID);
		if(h!=NULL){
			ThinMetalItem	*Item=dynamic_cast<ThinMetalItem *>(h);
			if(Item!=NULL){
				Item->DeleteSamples(CmdReqDeleteSampleVar->Numbers);
			}
		}
		return;
	}
}

void	ThinMetalInLayer::UndoAppendManualItem(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}

void	ThinMetalInLayer::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		ThinMetalItem	*B=new ThinMetalItem();
		if(B->Load(f,GetLayersBase())==false)
			return;
		RemovedItems.Add(B);
	}
	IntList	AddedItemIDList;
	if(AddedItemIDList.Load(f)==false)
		return;
	for(IntClass *a=AddedItemIDList.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*Item=SearchIDItem(a->GetValue());
		if(Item!=NULL){
			RemoveItem(Item);
			delete	Item;
		}
	}
	for(AlgorithmItemPointerList *item=RemovedItems.GetFirst();item!=NULL;item=item->GetNext()){
		AppendItem(item->GetItem());
	}
}

void	ThinMetalInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		ThinMetalItem	*BI=(ThinMetalItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

void	ThinMetalInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		ThinMetalItem	*BI=(ThinMetalItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

//===========================================================================================
ThinMetalInPage::ThinMetalInPage(AlgorithmBase *parent)
:AlgorithmInPagePLITemplate<ThinMetalItem,ThinMetalInLayer,ThinMetalBase>(parent)
{
}
ThinMetalInPage::~ThinMetalInPage(void)
{
}
void	ThinMetalInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedThinMetalFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedThinMetalFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(IntClass *L=ModifyItemFromBA->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}	
	CmdClearTestThinMetalPacket	*CmdClearTestThinMetalPacketVar=dynamic_cast<CmdClearTestThinMetalPacket *>(packet);
	if(CmdClearTestThinMetalPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdClearTestThinMetalPacketVar);
		}
		return;
	}
	CmdThinMetalInfoListPacket	*CmdThinMetalInfoListPacketVar=dynamic_cast<CmdThinMetalInfoListPacket *>(packet);
	if(CmdThinMetalInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdThinMetalInfoListPacketVar);
		}
		return;
	}
	CmdGetThinMetalFromList	*CmdGetThinMetalFromListVar=dynamic_cast<CmdGetThinMetalFromList *>(packet);
	if(CmdGetThinMetalFromListVar!=NULL){
		if(CmdGetThinMetalFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetThinMetalFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdCreateThinMetalItem	*CmdCreateThinMetalItemVar=dynamic_cast<CmdCreateThinMetalItem *>(packet);
	if(CmdCreateThinMetalItemVar!=NULL){
		AlgorithmInLayerRoot	*p=GetLayerData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdReqStoreThinMetal	*CmdReqStoreThinMetalVar=dynamic_cast<CmdReqStoreThinMetal *>(packet);
	if(CmdReqStoreThinMetalVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqStoreThinMetalStart	*CmdReqStoreThinMetalStartVar=dynamic_cast<CmdReqStoreThinMetalStart *>(packet);
	if(CmdReqStoreThinMetalStartVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqStoreThinMetalEnd	*CmdReqStoreThinMetalEndVar=dynamic_cast<CmdReqStoreThinMetalEnd *>(packet);
	if(CmdReqStoreThinMetalEndVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
}

//===========================================================================================
ThinMetalBase::ThinMetalBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;
	OmitZoneDot	=100;

	SetParam(&ColorArea					, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected				, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive				, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea				, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected			, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel			, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");

	SetParam(&OmitZoneDot	, /**/"Setting"		,/**/"OmitZoneDot"	,"Omit zone dot");

	for(int i=0;i<256;i++){
		for(int j=0;j<256;j++){
			Mult256Table[i][j]=i*j;
		}
	}
}

AlgorithmDrawAttr	*ThinMetalBase::CreateDrawAttr(void)
{
	return new ThinMetalDrawAttr(GetLayersBase());
}

void	ThinMetalBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetThinMetalLibraryListPacket	*AListPacket=dynamic_cast<CmdGetThinMetalLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetThinMetalLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetThinMetalLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertThinMetalLibraryPacket	*BInsLib=dynamic_cast<CmdInsertThinMetalLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(ThinMetalVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateThinMetalLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateThinMetalLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(ThinMetalVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadThinMetalLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadThinMetalLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempThinMetalLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempThinMetalLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearThinMetalLibraryPacket	*CmdClearThinMetalLibraryPacketVar=dynamic_cast<CmdClearThinMetalLibraryPacket *>(packet);
	if(CmdClearThinMetalLibraryPacketVar!=NULL){
		CmdClearThinMetalLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteThinMetalLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteThinMetalLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestThinMetalPacket	*BPickLib=dynamic_cast<CmdPickupTestThinMetalPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		ThinMetalInPage	*Bp=dynamic_cast<ThinMetalInPage *>(p);
		if(Bp==NULL)
			return;
		//Bp->PickupTest(BPickLib->LayerList,*BPickLib->LibPoint);		
		return;
	}
	CmdGenerateThinMetalPacket	*BGenerated=dynamic_cast<CmdGenerateThinMetalPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(Container);
			Container->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				ThinMetalLibrary	*L1=dynamic_cast<ThinMetalLibrary *>(LibDim[i  ]->GetLibrary());
				ThinMetalLibrary	*L2=dynamic_cast<ThinMetalLibrary *>(LibDim[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(Container);
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}

		ThinMetalLibrary	**DDim=new ThinMetalLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<ThinMetalLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			ThinMetalInPage	*Bp=dynamic_cast<ThinMetalInPage *>(p);
			if(Bp!=NULL){
				//Bp->GenerateThinMetals(BGenerated->LayerList,LibDim,N);		
			}
		}
		delete	[]DDim;
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempThinMetalItemPacket	*CreateThinMetalItem=dynamic_cast<CmdCreateTempThinMetalItemPacket *>(packet);
	if(CreateThinMetalItem!=NULL){
		CreateThinMetalItem->Point=new ThinMetalItem();
		return;
	}
	CmdCreateByteArrayFromThinMetalItemPacket	*BAFromThinMetalItem=dynamic_cast<CmdCreateByteArrayFromThinMetalItemPacket *>(packet);
	if(BAFromThinMetalItem!=NULL){
		QBuffer	Buff(&BAFromThinMetalItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromThinMetalItem->Point->Save(&Buff);
	}
	CmdAddByteThinMetalItemPacket	*AddBItem=dynamic_cast<CmdAddByteThinMetalItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePLI		*PData=dynamic_cast<AlgorithmInPagePLI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			for(IntClass *L=AddBItem->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
				ThinMetalInLayer	*BL=dynamic_cast<ThinMetalInLayer *>(PData->GetLayerData(L->GetValue()));
				if(BL!=NULL){
					QBuffer	MBuff(&AddBItem->Buff);
					ThinMetalItem	*Item=new ThinMetalItem();
					MBuff.open(QIODevice::ReadWrite);
					Item->SetParent(BL);
					Item->Load(&MBuff,GetLayersBase());
					Item->SetArea(AddBItem->Area);
					Item->SetManualCreated(true);
					BL->AppendItem(Item);

					UndoElement<ThinMetalInLayer>	*UPointer=new UndoElement<ThinMetalInLayer>(BL,&ThinMetalInLayer::UndoAppendManualItem);
					::Save(UPointer->GetWritePointer(),Item->GetID());
					Item->Save(UPointer->GetWritePointer());
					GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
				}
			}
		}
	}
	CmdLoadThinMetalItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadThinMetalItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedThinMetalFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedThinMetalFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		AlgorithmLibraryLevelContainer	LibData(this);
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
	CmdClearTestThinMetalPacket	*CmdClearTestThinMetalPacketVar=dynamic_cast<CmdClearTestThinMetalPacket *>(packet);
	if(CmdClearTestThinMetalPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestThinMetalPacketVar);
		}
	}
	CmdThinMetalInfoListPacket	*CmdThinMetalInfoListPacketVar=dynamic_cast<CmdThinMetalInfoListPacket *>(packet);
	if(CmdThinMetalInfoListPacketVar!=NULL){
		GetPageData(CmdThinMetalInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetThinMetalFromList	*CmdGetThinMetalFromListVar=dynamic_cast<CmdGetThinMetalFromList *>(packet);
	if(CmdGetThinMetalFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetThinMetalFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateThinMetalItem	*CmdCreateThinMetalItemVar=dynamic_cast<CmdCreateThinMetalItem *>(packet);
	if(CmdCreateThinMetalItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

bool	ThinMetalBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==ThinMetalHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ThinMetalHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ThinMetalReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ThinMetalReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ThinMetalReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ThinMetalSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ThinMetalReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*ThinMetalBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==ThinMetalHistogramListSendCommand){
		ThinMetalHistogramListSend	*pSend=new ThinMetalHistogramListSend();
		if(reqData!=NULL){
			ThinMetalHistogramListReq	*req=(ThinMetalHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ThinMetalHistogramListReqCommand){
		return new ThinMetalHistogramListReq();
	}
	else if(Command==ThinMetalReqThresholdReqCommand){
		return new ThinMetalThresholdReq();
	}
	else if(Command==ThinMetalReqThresholdSendCommand){
		ThinMetalThresholdSend	*pSend=new ThinMetalThresholdSend();
		if(reqData!=NULL){
			ThinMetalThresholdReq	*req=(ThinMetalThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ThinMetalReqTryThresholdCommand){
		return new ThinMetalReqTryThreshold();
	}
	else if(Command==ThinMetalSendTryThresholdCommand){
		ThinMetalSendTryThreshold	*pSend=new ThinMetalSendTryThreshold();
		if(reqData!=NULL){
			ThinMetalReqTryThreshold	*req=(ThinMetalReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ThinMetalReqChangeShiftCommand){
		return new ThinMetalChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	ThinMetalBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==ThinMetalHistogramListSendCommand){
		ThinMetalHistogramListSend	*p=(ThinMetalHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==ThinMetalHistogramListReqCommand){
		ThinMetalHistogramListReq	*p=(ThinMetalHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==ThinMetalReqThresholdReqCommand){
		ThinMetalThresholdReq	*p=(ThinMetalThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==ThinMetalReqThresholdSendCommand){
		ThinMetalThresholdSend	*p=(ThinMetalThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==ThinMetalReqTryThresholdCommand){
		ThinMetalReqTryThreshold	*p=(ThinMetalReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==ThinMetalSendTryThresholdCommand){
		ThinMetalSendTryThreshold	*p=(ThinMetalSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==ThinMetalReqChangeShiftCommand){
		ThinMetalChangeShift	*p=(ThinMetalChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	ThinMetalBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==ThinMetalHistogramListSendCommand){
		ThinMetalHistogramListSend	*p=(ThinMetalHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==ThinMetalHistogramListReqCommand){
		ThinMetalHistogramListReq	*p=(ThinMetalHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==ThinMetalReqThresholdReqCommand){
		ThinMetalThresholdReq	*p=(ThinMetalThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==ThinMetalReqThresholdSendCommand){
		ThinMetalThresholdSend	*p=(ThinMetalThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==ThinMetalReqTryThresholdCommand){
		ThinMetalReqTryThreshold	*p=(ThinMetalReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==ThinMetalSendTryThresholdCommand){
		ThinMetalSendTryThreshold	*p=(ThinMetalSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==ThinMetalReqChangeShiftCommand){
		ThinMetalChangeShift	*p=(ThinMetalChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	ThinMetalBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==ThinMetalHistogramListSendCommand){
		ThinMetalHistogramListSend	*p=(ThinMetalHistogramListSend *)data;
		return true;
	}
	else if(Command==ThinMetalHistogramListReqCommand){
		ThinMetalHistogramListReq	*p=(ThinMetalHistogramListReq *)data;
		return true;
	}
	else if(Command==ThinMetalReqThresholdReqCommand){
		ThinMetalThresholdReq	*p=(ThinMetalThresholdReq *)data;
		return true;
	}
	else if(Command==ThinMetalReqThresholdSendCommand){
		ThinMetalThresholdSend	*p=(ThinMetalThresholdSend *)data;
		return true;
	}
	else if(Command==ThinMetalReqTryThresholdCommand){
		ThinMetalReqTryThreshold	*p=(ThinMetalReqTryThreshold *)data;
		return true;
	}
	else if(Command==ThinMetalSendTryThresholdCommand){
		ThinMetalSendTryThreshold	*p=(ThinMetalSendTryThreshold *)data;
		return true;
	}
	else if(Command==ThinMetalReqChangeShiftCommand){
		ThinMetalChangeShift	*p=(ThinMetalChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	ThinMetalBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	ChangeCreateThinMetalForm	Q(this,GetLayersBase()->GetMainWidget());
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultThinMetal.Save(&Buff)==false)
			return false;
	}
	return ret;
	*/
	return true;
}


//===========================================================================================

