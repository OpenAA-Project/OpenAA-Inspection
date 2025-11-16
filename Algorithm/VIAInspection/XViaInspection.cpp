#include "XVIAInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VIAInspection\XVIAInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "VIAFormResource.h"
#include "XViaInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XViaInspectionLibrary.h"
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
#include "XVIAAlgoPacket.h"
#include "ChangeCreateVIAForm.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

VIAHistogramListReq::VIAHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	VIAItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	VIAHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,VIAItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	VIAHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,VIAItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


VIAHistogramListSend::VIAHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	VIAItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));
	CenterBright		=0;
	CenterTargetBright	=0;
}
void	VIAHistogramListSend::ConstructList(VIAHistogramListReq *reqPacket ,VIABase *Base)
{
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	VIAItemID	=reqPacket->VIAItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(VIAItemID);
			if(item!=NULL){
				VIAItem	*Item=dynamic_cast<VIAItem*>(item);
				bool	BuiltList=false;
				if(BuiltList==false){
					item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
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

bool	VIAHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,VIAItemID)==false)
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
bool	VIAHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,VIAItemID)==false)
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
VIAThresholdReq::VIAThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	VIAItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	VIAThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,VIAItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	VIAThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,VIAItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

VIAThresholdSend::VIAThresholdSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	VIAItemID=-1;
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

void	VIAThresholdSend::ConstructList(VIAThresholdReq *reqPacket,VIABase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	VIAItemID	=reqPacket->VIAItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerRoot	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(VIAItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				VIAItem	*BItem=(VIAItem *)item;
				if(BItem->CenterBright==0){
					BItem->CenterBright=BItem->CalcCenterBright(BItem->GetMasterBuff(),0,0);
					BItem->CenterTargetBright=BItem->CenterBright;
				}
				const VIAThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				CenterBright	=BItem->CenterBright;
				AbsBrightWidthL	=RThr->BrightWidthL;
				AbsBrightWidthH	=RThr->BrightWidthH;

				CenterTargetBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),dx,dy);
			}
		}
	}
}

bool	VIAThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,VIAItemID)==false)
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
bool	VIAThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,VIAItemID)==false)
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

VIAReqTryThreshold::VIAReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	VIAItemID=-1;
}
bool	VIAReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,VIAItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	VIAReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,VIAItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

VIASendTryThreshold::VIASendTryThreshold(void)
{
	NGDotInDark	=0;
	NGDotInBright	=0;
	Error			=0;
	Result	=new ResultInItemPLI();
}
VIASendTryThreshold::~VIASendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}


bool	VIASendTryThreshold::Save(QIODevice *f)
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
bool	VIASendTryThreshold::Load(QIODevice *f)
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

void	VIASendTryThreshold::ConstructList(VIAReqTryThreshold *reqPacket,VIABase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	VIAInPage		*BP=(VIAInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		VIAInLayer	*BL=(VIAInLayer *)BP->GetLayerData(reqPacket->Layer);
		if(BL!=NULL){
			VIAItem		*BI=(VIAItem *)BL->SearchIDItem(reqPacket->VIAItemID);
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


void	VIAResultPosList::DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData 
									,int MovX ,int MovY ,double ZoomRate 
									,int MinimumRadius,QRgb Col
									,int CircleWidth,bool DrawBlueNGMark)
{
	int	R=ZoomRate;
	if(R<MinimumRadius){
		R=MinimumRadius;
	}
	int	R2=R+R;
	int	x1=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate-R;
	int y1=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate-R;
	int	x2=x1+R2;
	int	y2=y1+R2;
	if(0<=x2 && x1<IData.width() && 0<=y2 && y1<IData.height()){
		PData.setPen(QColor(Col));
		if(ImportanceLevel<100){
			PData.drawEllipse(x1-4,y1-4,R2+4,R2+4);
			PData.drawEllipse(x1-2,y1-2,R2+2,R2+2);
			PData.drawEllipse(x1,y1,R2,R2);
		}
		else{
			PData.drawEllipse(x1,y1,R2,R2);
		}
	}
}

//=====================================================================================
void	VIAChangeShift::Reflect(VIABase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(VIAItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	VIAChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,VIAItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	VIAChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,VIAItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
//=====================================================================================
VIAThreshold::VIAThreshold(VIAItem *parent)
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

void	VIAThreshold::RegistHist(void)
{
	RegistBoundaryChar	(/**/"Center Bright difference"	,Hist_VIAInspection_CenterBright,-120,120);
	RegistInt			(/**/"Broad Light NG size"		,Hist_VIAInspection_LightNGSize);
	RegistInt			(/**/"Broad Dark NG size"		,Hist_VIAInspection_DarkNGSize);
}

void	VIAThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const VIAThreshold *s=(const VIAThreshold *)&src;
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
bool	VIAThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const VIAThreshold *s=(const VIAThreshold *)&src;
	if(BrightWidthL		!=s->BrightWidthL	)	return false;
	if(BrightWidthH		!=s->BrightWidthH	)	return false;
	if(OKDotL			!=s->OKDotL			)	return false;
	if(OKDotH			!=s->OKDotH			)	return false;
	if(MaxNGDotL		!=s->MaxNGDotL		)	return false;
	if(MaxNGDotH		!=s->MaxNGDotH		)	return false;
	if(OKLengthL		!=s->OKLengthL		)	return false;
	if(OKLengthH		!=s->OKLengthH		)	return false;

	if(SpaceToOutline	!=s->SpaceToOutline)	return false;
	if(ShrinkDot		!=s->ShrinkDot		)	return false;
	if(EnlargeDot		!=s->EnlargeDot		)	return false;
	return true;
}
bool	VIAThreshold::Save(QIODevice *file)
{
	WORD	Ver=VIAInspectionVersion;

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
bool	VIAThreshold::Load(QIODevice *file)
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

void	VIAThreshold::FromLibrary(AlgorithmLibrary *src)
{
	VIALibrary	*LSrc=dynamic_cast<VIALibrary *>(src);
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
void	VIAThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	VIALibrary	*LDst=dynamic_cast<VIALibrary *>(Dest);
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
VIAItem::VIAItem(void)
{
	InitialConstructor();
}
VIAItem::VIAItem(FlexArea &area)
:AlgorithmItemPLI(area)
{
	InitialConstructor();
}

void VIAItem::InitialConstructor(void)
{
	CenterBright	=0;
	AVector=NULL;
}

VIAItem::~VIAItem(void)
{}

AlgorithmItemPLI	&VIAItem::operator=(const AlgorithmItemRoot &src)
{
	const VIAItem	*s=dynamic_cast<const VIAItem *>(&src);
	if(s!=NULL)
		return AlgorithmItemPLI::operator=(src);
	return *this;
}
VIAItem &VIAItem::operator=(VIAItem &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(src);

	return *this;
}

void	VIAItem::CopyThreshold(VIAItem &src)
{
	CenterBright	=src.CenterBright;
	GetThresholdW()->CopyFrom(*((VIAThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	VIAItem::CopyThresholdOnly(VIAItem &src)
{
	GetThresholdW()->CopyFrom(*((VIAThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

bool    VIAItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;
	if(::Save(file,CenterBright)==false)
		return false;
	return true;
}
bool    VIAItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	if(::Load(file,CenterBright)==false)
		return false;
	return true;
}

void	VIAItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			VIAInLayer	*Ly=dynamic_cast<VIAInLayer *>(GetParentInLayer());
			UndoElement<VIAInLayer>	*UPointer=new UndoElement<VIAInLayer>(Ly,&VIAInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			VIAItem *src=(VIAItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
			CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((VIAItem *)Data)->GetLibID()){
			VIAInLayer	*Ly=dynamic_cast<VIAInLayer *>(GetParentInLayer());
			UndoElement<VIAInLayer>	*UPointer=new UndoElement<VIAInLayer>(Ly,&VIAInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			VIAItem *src=(VIAItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
			CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
		}
	}

}
void	VIAItem::CopyArea(VIAItem &src)
{
	SetArea(src.GetArea());
}


int		VIAItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}

void	VIAItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	VIAItem	*ASrc=dynamic_cast<VIAItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((VIABase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		CenterBright	=ASrc->CenterBright;
	}
}

ExeResult	VIAItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
											,ResultInItemRoot *Res
											,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	
	int	cx,cy;
	//_CrtCheckMemory();

	int	gap=((VIABase *)GetParentBase())->OmitZoneDot;
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


	//_CrtCheckMemory();

	return Ret;
}




void	VIAItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	VIADrawAttr	*BAttr=dynamic_cast<VIADrawAttr *>(Attr);
	if(BAttr!=NULL){
		VIADrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		//QColor	BuffColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	TmpAttr.NormalColor=BAttr->VIAColor0;	break;
			case 1:	TmpAttr.NormalColor=BAttr->VIAColor1;	break;
			case 2:	TmpAttr.NormalColor=BAttr->VIAColor2;	break;
			case 3:	TmpAttr.NormalColor=BAttr->VIAColor3;	break;
			case 4:	TmpAttr.NormalColor=BAttr->VIAColor4;	break;
			case 5:	TmpAttr.NormalColor=BAttr->VIAColor5;	break;
			case 6:	TmpAttr.NormalColor=BAttr->VIAColor6;	break;
			case 7:	TmpAttr.NormalColor=BAttr->VIAColor7;	break;
		}
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	VIAItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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
			if(Res->IsOk()==false && ZoomRate>1.0){
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
					if(Res->GetError()==2){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"N: L=")+QString::number(Res->GetResult1()) +QString(/**/" H=")+QString::number(Res->GetResult2())
							,&rect);
					}
					else if(Res->GetError()==3){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"B: L=")+QString::number(Res->GetResult1()) +QString(/**/" H=")+QString::number(Res->GetResult2())
							,&rect);
					}
				}
			}
		}
	}
}

//===========================================================================================

VIAInLayer::VIAInLayer(AlgorithmInPageRoot *parent):AlgorithmInLayerPLI(parent)
{
	PickupBmp		=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
}

VIAInLayer::~VIAInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}
void	VIAInLayer::CreatePickupBmpBuff(void)
{
	if(PickupBmp!=NULL && PickupBmpYLen!=GetMaxLines()){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
	}
	if(PickupBmp==NULL){
		PickupBmpYLen=GetMaxLines();
		PickupBmpXByte=(GetDotPerLine()+7)/8;
		PickupBmp=MakeMatrixBuff(PickupBmpXByte ,PickupBmpYLen);
	}
	MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
}

bool	VIAInLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfVIA	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfVIA	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
void	VIAInLayer::PickupTest(VIALibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;	
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);

	bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibData.GetLibID());
	bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&LibData,NULL);
	if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
		LibData.MakePickupTest(GetMasterBuff()
			,MaskMap.GetBitMap()
			,PickupBmp,NULL
			,GetPage()
			,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
			,((VIABase *)GetParentBase())->OmitZoneDot);
	}
}


void	VIAInLayer::GenerateVIAs(VIALibrary *LibDim[],int LibDimNumb)
{
	UndoElement<VIAInLayer>	*UPointer=new UndoElement<VIAInLayer>(this,&VIAInLayer::UndoGenerateItems);
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

	CreatePickupBmpBuff();
	//Data.RemoveAll();
	int	DeletedItemCount=0;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetEditLocked()==false){
			DeletedItemCount++;
		}
	}
	::Save(UPointer->GetWritePointer(),DeletedItemCount);

	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			L->Save(UPointer->GetWritePointer());
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(GetLibraryContainer());
			if(GetLibraryContainer()->GetLibrary(L->GetLibID() ,*Lib)==true){
				LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
			}
			else{
				delete	Lib;
				Lib=NULL;
			}
		}
	}

	for(AlgorithmLibraryStockerList *B=LibStocker.GetFirst();B!=NULL;B=B->GetNext()){
		MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		VIALibrary	*BLib=(VIALibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline;
		BSpaceToOutline=BLib->SpaceToOutline;
		if(BSpaceToOutline>0){
			GetLayersBase()->FatAreaN (TempMap,TempMap2 ,XByte,GetMaxLines(),BSpaceToOutline);
		}
		else{
			GetLayersBase()->ThinAreaN(TempMap,TempMap2 ,XByte,GetMaxLines(),-BSpaceToOutline);
		}
		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2		,GetMaxLines());

	BYTE **OcupyMap				=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **OcupyMapSamePriority	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());

	IntList	AddedItemIDList;
	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBuffer MaskMap;
		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			AlgorithmInPagePLI	*LPg=(AlgorithmInPagePLI*)GetParentInPage();
			AlgorithmInLayerPLI	*LL=(AlgorithmInLayerPLI *)LPg->GetLayerData(LibDim[i]->GetAdaptedPickLayers().GetFirst()->GetValue());
			LL->GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		else{
			GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();
		
		MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

		bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibDim[i]->GetLibID());
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,LibDim[i],NULL);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){

			ImageBuffer	*MImage=&GetMasterBuff();
			if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
				for(int LLayer=0;LLayer<GetLayerNumb();LLayer++){
					if(LibDim[i]->HasPickLayer(LLayer)==true){
						ImagePointerContainer ImagesPointers;
						GetParentInPage()->GetMasterImages(ImagesPointers);
						MImage=ImagesPointers[LLayer];
						break;
					}
				}
			}

			LibDim[i]->MakePickupTest(*MImage
				,MaskBitmap
				,CurrentMap,OcupyMap
				,GetPage()
				,XByte ,GetDotPerLine(),GetMaxLines()
				,((VIABase *)GetParentBase())->OmitZoneDot);

			NPListPack<AlgorithmItemPLI>	TmpVIAData;
			LibDim[i]->MakeVIA(
					 CurrentMap,LastOcupyMap
					 ,GetPage()
					,XByte ,GetDotPerLine(),GetMaxLines()
					,TmpVIAData);
			AlgorithmItemPLI	*q;
			while((q=TmpVIAData.GetFirst())!=NULL){
				TmpVIAData.RemoveList(q);
				AppendItem(q);
				AddedItemIDList.Add(q->GetID());
			}
		}
		MatrixBuffOr (OcupyMapSamePriority,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
		if((i+1)<LibDimNumb && LibDim[i]->Priority!=LibDim[i+1]->Priority){
			MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMapSamePriority ,XByte,GetMaxLines());
			MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());
		}
	}
	AddedItemIDList.Save(UPointer->GetWritePointer());

	DeleteMatrixBuff(CurrentMap				,GetMaxLines());
	DeleteMatrixBuff(OcupyMap				,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
	DeleteMatrixBuff(OcupyMapSamePriority	,GetMaxLines());
}

void	VIAInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedVIAFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedVIAFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		VIAItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			VIAItem	*B=(VIAItem *)L;
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
				VIAItem	*B=(VIAItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestVIAPacket	*CmdClearTestVIAPacketVar=dynamic_cast<CmdClearTestVIAPacket *>(packet);
	if(CmdClearTestVIAPacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}
	CmdVIAInfoListPacket	*CmdVIAInfoListPacketVar=dynamic_cast<CmdVIAInfoListPacket *>(packet);
	if(CmdVIAInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			VIAInfoList	*a;
			for(a=CmdVIAInfoListPacketVar->VIAInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->VIACount.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new VIAInfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					if(layer==GetLayer())
						a->VIACount.Add(1);
					else
						a->VIACount.Add(0);
				}
				CmdVIAInfoListPacketVar->VIAInfos->AppendList(a);
			}
		}
		return;
	}
	CmdGetVIAFromList	*CmdGetVIAFromListVar=dynamic_cast<CmdGetVIAFromList *>(packet);
	if(CmdGetVIAFromListVar!=NULL){
		VIAItem *Item=(VIAItem *)SearchIDItem(CmdGetVIAFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetVIAFromListVar->VIAInfoOnMouse=Item;
		return;
	}
	CmdCreateVIAItem	*CmdCreateVIAItemVar=dynamic_cast<CmdCreateVIAItem *>(packet);
	if(CmdCreateVIAItemVar!=NULL){
		CmdCreateVIAItemVar->VIA=(VIAItem *)CreateItem(0);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		VIAItem *Item=(VIAItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);
			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
		}
		return;
	}
}

void	VIAInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	VIADrawAttr	*BAttr=dynamic_cast<VIADrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==VIADrawAttr::_LibTest){
			if(PickupBmp!=NULL){
				VIABase	*BBase=dynamic_cast<VIABase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==VIADrawAttr::_CreatedVIA){
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	VIAInLayer::UndoAppendManualItem(QIODevice *f)
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

void	VIAInLayer::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		VIAItem	*B=new VIAItem();
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

void	VIAInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		VIAItem	*BI=(VIAItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}


//===========================================================================================

void	VIAInPage::PickupTest(IntList &LayerList ,VIALibrary &LibData)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			VIAInLayer	*BI=dynamic_cast<VIAInLayer *>(AL);
			if(BI!=NULL){
				BI->PickupTest(LibData);
			}
		}
	}
}
void	VIAInPage::GenerateVIAs(IntList &LayerList, VIALibrary *LibDim[],int LibDimNumb)
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		VIALibrary *TmpLibDim[1000];
		int	LibN=0;
		for(int i=0;i<LibDimNumb;i++){
			if(LibDim[i]->HasGenLayer(Layer)==true
			|| ((LibDim[i]->GetAdaptedGenLayers().IsEmpty()==true) && LayerList.IsInclude(Layer)==true)){
				TmpLibDim[LibN]=LibDim[i];
				LibN++;
				if(LibN>=1000){
					break;
				}
			}
		}
		if(LibN!=0){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			VIAInLayer	*BI=dynamic_cast<VIAInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateVIAs(TmpLibDim,LibN);
			}
		}
	}
}
void	VIAInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedVIAFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedVIAFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(IntClass *L=ModifyItemFromBA->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}	
	CmdClearTestVIAPacket	*CmdClearTestVIAPacketVar=dynamic_cast<CmdClearTestVIAPacket *>(packet);
	if(CmdClearTestVIAPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdClearTestVIAPacketVar);
		}
		return;
	}
	CmdVIAInfoListPacket	*CmdVIAInfoListPacketVar=dynamic_cast<CmdVIAInfoListPacket *>(packet);
	if(CmdVIAInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdVIAInfoListPacketVar);
		}
		return;
	}
	CmdGetVIAFromList	*CmdGetVIAFromListVar=dynamic_cast<CmdGetVIAFromList *>(packet);
	if(CmdGetVIAFromListVar!=NULL){
		if(CmdGetVIAFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetVIAFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdCreateVIAItem	*CmdCreateVIAItemVar=dynamic_cast<CmdCreateVIAItem *>(packet);
	if(CmdCreateVIAItemVar!=NULL){
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

}

//===========================================================================================
VIABase::VIABase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	ColorVIANormal	=Qt::darkGreen;
	ColorVIASelected	=Qt::green;
	ColorVIAActive	=Qt::red;

	VIAColor0	=Qt::green;
	VIAColor1	=Qt::yellow;
	VIAColor2	=Qt::darkRed;
	VIAColor3	=Qt::cyan;
	VIAColor4	=Qt::magenta;
	VIAColor5	=Qt::darkGreen;
	VIAColor6	=Qt::darkYellow;
	VIAColor7	=Qt::darkCyan;
	OmitZoneDot	=100;
	VarLow		=20;

	SetParam(&ColorPickup		, /**/"Color" ,/**/"ColorPickup"		,LangSolver.GetString(XViaInspection_LS,LID_0)/*"Color for Image to Pickup-Test "*/);
	SetParam(&ColorVIANormal	, /**/"Color" ,/**/"ColorVIANormal"		,LangSolver.GetString(XViaInspection_LS,LID_1)/*"Color for VIA"*/);
	SetParam(&ColorVIASelected	, /**/"Color" ,/**/"ColorVIASelected"	,LangSolver.GetString(XViaInspection_LS,LID_2)/*"Color for Selected VIA"*/);
	SetParam(&ColorVIAActive	, /**/"Color" ,/**/"ColorVIAActive"		,LangSolver.GetString(XViaInspection_LS,LID_3)/*"Color for Active VIA"*/);

	SetParam(&VIAColor0	, /**/"VIAColor" ,/**/"VIAColor0"	,LangSolver.GetString(XViaInspection_LS,LID_4)/*"VIA Color 0"*/);
	SetParam(&VIAColor1	, /**/"VIAColor" ,/**/"VIAColor1"	,LangSolver.GetString(XViaInspection_LS,LID_5)/*"VIA Color 1"*/);
	SetParam(&VIAColor2	, /**/"VIAColor" ,/**/"VIAColor2"	,LangSolver.GetString(XViaInspection_LS,LID_6)/*"VIA Color 2"*/);
	SetParam(&VIAColor3	, /**/"VIAColor" ,/**/"VIAColor3"	,LangSolver.GetString(XViaInspection_LS,LID_7)/*"VIA Color 3"*/);
	SetParam(&VIAColor4	, /**/"VIAColor" ,/**/"VIAColor4"	,LangSolver.GetString(XViaInspection_LS,LID_8)/*"VIA Color 4"*/);
	SetParam(&VIAColor5	, /**/"VIAColor" ,/**/"VIAColor5"	,LangSolver.GetString(XViaInspection_LS,LID_9)/*"VIA Color 5"*/);
	SetParam(&VIAColor6	, /**/"VIAColor" ,/**/"VIAColor6"	,LangSolver.GetString(XViaInspection_LS,LID_10)/*"VIA Color 6"*/);
	SetParam(&VIAColor7	, /**/"VIAColor" ,/**/"VIAColor7"	,LangSolver.GetString(XViaInspection_LS,LID_11)/*"VIA Color 7"*/);

	SetParam(&OmitZoneDot	, /**/"Setting"		,/**/"OmitZoneDot"	,LangSolver.GetString(XViaInspection_LS,LID_12)/*"Omit zone dot in VIA generation"*/);
	SetParam(&VarLow		, /**/"Setting"		,/**/"VarLow"		,LangSolver.GetString(XViaInspection_LS,LID_13)/*"Var limit low for outline chaser"*/);
}

AlgorithmDrawAttr	*VIABase::CreateDrawAttr(void)
{
	return new VIADrawAttr();
}

void	VIABase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetVIALibraryListPacket	*AListPacket=dynamic_cast<CmdGetVIALibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetVIALibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetVIALibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertVIALibraryPacket	*BInsLib=dynamic_cast<CmdInsertVIALibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(VIAInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateVIALibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateVIALibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(VIAInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadVIALibraryPacket	*BLoadLib=dynamic_cast<CmdLoadVIALibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempVIALibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempVIALibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearVIALibraryPacket	*CmdClearVIALibraryPacketVar=dynamic_cast<CmdClearVIALibraryPacket *>(packet);
	if(CmdClearVIALibraryPacketVar!=NULL){
		CmdClearVIALibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteVIALibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteVIALibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestVIAPacket	*BPickLib=dynamic_cast<CmdPickupTestVIAPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		VIAInPage	*Bp=dynamic_cast<VIAInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(BPickLib->LayerList,*(VIALibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateVIAPacket	*BGenerated=dynamic_cast<CmdGenerateVIAPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				VIALibrary	*L1=dynamic_cast<VIALibrary *>(LibDim[i  ]->GetLibrary());
				VIALibrary	*L2=dynamic_cast<VIALibrary *>(LibDim[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(this);
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}
		VIALibrary	**DDim=new VIALibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<VIALibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			VIAInPage	*Bp=dynamic_cast<VIAInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateVIAs(BGenerated->LayerList,DDim,N);		
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
	CmdCreateTempVIAItemPacket	*CreateVIAItem=dynamic_cast<CmdCreateTempVIAItemPacket *>(packet);
	if(CreateVIAItem!=NULL){
		CreateVIAItem->Point=new VIAItem();
		return;
	}
	CmdCreateByteArrayFromVIAItemPacket	*BAFromVIAItem=dynamic_cast<CmdCreateByteArrayFromVIAItemPacket *>(packet);
	if(BAFromVIAItem!=NULL){
		QBuffer	Buff(&BAFromVIAItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromVIAItem->Point->Save(&Buff);
	}
	CmdAddByteVIAItemPacket	*AddBItem=dynamic_cast<CmdAddByteVIAItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePLI		*PData=dynamic_cast<AlgorithmInPagePLI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			for(IntClass *L=AddBItem->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
				VIAInLayer	*BL=dynamic_cast<VIAInLayer *>(PData->GetLayerData(L->GetValue()));
				if(BL!=NULL){
					QBuffer	MBuff(&AddBItem->Buff);
					VIAItem	*Item=new VIAItem();
					MBuff.open(QIODevice::ReadWrite);
					Item->Load(&MBuff,GetLayersBase());
					Item->SetArea(AddBItem->Area);
					Item->SetManualCreated(true);
					BL->AppendItem(Item);

					UndoElement<VIAInLayer>	*UPointer=new UndoElement<VIAInLayer>(BL,&VIAInLayer::UndoAppendManualItem);
					::Save(UPointer->GetWritePointer(),Item->GetID());
					Item->Save(UPointer->GetWritePointer());
					GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
				}
			}
		}
	}
	CmdLoadVIAItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadVIAItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedVIAFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedVIAFromByteArray *>(packet);
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
	CmdClearTestVIAPacket	*CmdClearTestVIAPacketVar=dynamic_cast<CmdClearTestVIAPacket *>(packet);
	if(CmdClearTestVIAPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestVIAPacketVar);
		}
	}
	CmdVIAInfoListPacket	*CmdVIAInfoListPacketVar=dynamic_cast<CmdVIAInfoListPacket *>(packet);
	if(CmdVIAInfoListPacketVar!=NULL){
		GetPageData(CmdVIAInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetVIAFromList	*CmdGetVIAFromListVar=dynamic_cast<CmdGetVIAFromList *>(packet);
	if(CmdGetVIAFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetVIAFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateVIAItem	*CmdCreateVIAItemVar=dynamic_cast<CmdCreateVIAItem *>(packet);
	if(CmdCreateVIAItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

bool	VIABase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==VIAHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==VIAHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==VIAReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==VIAReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==VIAReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==VIASendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==VIAReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*VIABase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==VIAHistogramListSendCommand){
		VIAHistogramListSend	*pSend=new VIAHistogramListSend();
		if(reqData!=NULL){
			VIAHistogramListReq	*req=(VIAHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==VIAHistogramListReqCommand){
		return new VIAHistogramListReq();
	}
	else if(Command==VIAReqThresholdReqCommand){
		return new VIAThresholdReq();
	}
	else if(Command==VIAReqThresholdSendCommand){
		VIAThresholdSend	*pSend=new VIAThresholdSend();
		if(reqData!=NULL){
			VIAThresholdReq	*req=(VIAThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==VIAReqTryThresholdCommand){
		return new VIAReqTryThreshold();
	}
	else if(Command==VIASendTryThresholdCommand){
		VIASendTryThreshold	*pSend=new VIASendTryThreshold();
		if(reqData!=NULL){
			VIAReqTryThreshold	*req=(VIAReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==VIAReqChangeShiftCommand){
		return new VIAChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	VIABase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==VIAHistogramListSendCommand){
		VIAHistogramListSend	*p=(VIAHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==VIAHistogramListReqCommand){
		VIAHistogramListReq	*p=(VIAHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==VIAReqThresholdReqCommand){
		VIAThresholdReq	*p=(VIAThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==VIAReqThresholdSendCommand){
		VIAThresholdSend	*p=(VIAThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==VIAReqTryThresholdCommand){
		VIAReqTryThreshold	*p=(VIAReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==VIASendTryThresholdCommand){
		VIASendTryThreshold	*p=(VIASendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==VIAReqChangeShiftCommand){
		VIAChangeShift	*p=(VIAChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	VIABase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==VIAHistogramListSendCommand){
		VIAHistogramListSend	*p=(VIAHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==VIAHistogramListReqCommand){
		VIAHistogramListReq	*p=(VIAHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==VIAReqThresholdReqCommand){
		VIAThresholdReq	*p=(VIAThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==VIAReqThresholdSendCommand){
		VIAThresholdSend	*p=(VIAThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==VIAReqTryThresholdCommand){
		VIAReqTryThreshold	*p=(VIAReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==VIASendTryThresholdCommand){
		VIASendTryThreshold	*p=(VIASendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==VIAReqChangeShiftCommand){
		VIAChangeShift	*p=(VIAChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	VIABase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==VIAHistogramListSendCommand){
		VIAHistogramListSend	*p=(VIAHistogramListSend *)data;
		return true;
	}
	else if(Command==VIAHistogramListReqCommand){
		VIAHistogramListReq	*p=(VIAHistogramListReq *)data;
		return true;
	}
	else if(Command==VIAReqThresholdReqCommand){
		VIAThresholdReq	*p=(VIAThresholdReq *)data;
		return true;
	}
	else if(Command==VIAReqThresholdSendCommand){
		VIAThresholdSend	*p=(VIAThresholdSend *)data;
		return true;
	}
	else if(Command==VIAReqTryThresholdCommand){
		VIAReqTryThreshold	*p=(VIAReqTryThreshold *)data;
		return true;
	}
	else if(Command==VIASendTryThresholdCommand){
		VIASendTryThreshold	*p=(VIASendTryThreshold *)data;
		return true;
	}
	else if(Command==VIAReqChangeShiftCommand){
		VIAChangeShift	*p=(VIAChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	VIABase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	ChangeCreateVIAForm	Q(this,GetLayersBase()->GetMainWidget());
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultVIA.Save(&Buff)==false)
			return false;
	}
	return ret;
}


//===========================================================================================

