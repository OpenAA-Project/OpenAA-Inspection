/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticBlock\XStatisticBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StatisticBlockResource.h"
#include "XStatisticBlock.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XStatisticBlockLibrary.h"
#include "XPropertyStatisticBlockPacket.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XDynamicMaskingPICommon.h"
#include "XCriticalFunc.h"

StatisticBlockHistogramListReq::StatisticBlockHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	StatisticBlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	StatisticBlockHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StatisticBlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	StatisticBlockHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StatisticBlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


StatisticBlockHistogramListSend::StatisticBlockHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	StatisticBlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));
}
void	StatisticBlockHistogramListSend::ConstructList(StatisticBlockHistogramListReq *reqPacket ,StatisticBlockBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	StatisticBlockItemID	=reqPacket->StatisticBlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemPLI	*item	=(AlgorithmItemPLI *)L->SearchIDItem(StatisticBlockItemID);
			if(item!=NULL){
				bool	BuiltList=false;
				if(item->IsOriginParts()==true){
					PieceClass	*Pc=NULL;
					Pc=Base->GetLayersBase()->GetPieceStock()->SearchOnly(item->GetPartsID());
					if(Pc!=NULL){
						AlgorithmItemRoot	*PItem=Pc->GetAlgorithmItem(/**/"Basic",/**/"StatisticBlock",Layer ,item->GetPartsItemID());
						PItem->GetArea().MakeBrightList(ListMaster ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetMasterBuff(),0 ,0);
						BuiltList=true;
					}
				}
				if(BuiltList==false){
					item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),item->GetMasterBuff(),0 ,0);
				}
			
				ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
				if(DRes!=NULL){
					ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
					ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
					ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
					if(Rp!=NULL){
						ResultInLayerPLI	&rLayer=Rp->GetLayerData(item->GetParent()->GetLayer());
						ResultInItemPLI		*rItem=rLayer.FindResultInItem(item->GetID());
						if(rItem!=NULL){
							int	sx,sy;
							rItem->GetTotalShifted(sx,sy);
							item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),item->GetTargetBuff(),sx ,sy);
						}
						else
							item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),item->GetTargetBuff(),0 ,0);
					}
				}
			}
		}
	}
}

bool	StatisticBlockHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StatisticBlockItemID)==false)
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
	return true;
}
bool	StatisticBlockHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StatisticBlockItemID)==false)
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
	return true;
}
StatisticBlockThresholdReq::StatisticBlockThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	StatisticBlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	StatisticBlockThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StatisticBlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	StatisticBlockThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StatisticBlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

StatisticBlockThresholdSend::StatisticBlockThresholdSend(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	StatisticBlockItemID=-1;
	Mastered	=true;
	Dx			=0;
	Dy			=0;

	Avr			=0;
	Sigma		=0;
	BrightWidthL=0;
	BrightWidthH=0;
}

void	StatisticBlockThresholdSend::ConstructList(StatisticBlockThresholdReq *reqPacket,StatisticBlockBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	StatisticBlockItemID	=reqPacket->StatisticBlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(StatisticBlockItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				StatisticBlockItem	*BItem=(StatisticBlockItem *)item;

				AlgorithmInPageRoot	*LPI=Ap->GetAlgorithm(/**/"Basic" ,/**/"DynamicMaskingPI");
				if(LPI!=NULL){
					BYTE	**DynamicMaskMap=L->GetDataInPage()->GetDynamicMaskingMap();
					int	DynamicMaskMapXByte	=L->GetDataInPage()->GetDynamicMaskMapXByte();
					int	DynamicMaskMapYLen	=L->GetDataInPage()->GetDynamicMaskMapYLen();
					BItem->CalcAvrSigma(dx,dy
										,DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen);
				}
				else{
					BItem->CalcAvrSigma(dx,dy,NULL,0,0);
				}
				Avr		=BItem->Avr;
				Sigma	=BItem->Sigma;
				const StatisticBlockThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				BrightWidthL=RThr->BrightWidthL;		//?A???P?x??
				BrightWidthH=RThr->BrightWidthH;		//?????P?x??
			}
		}
	}
}

bool	StatisticBlockThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StatisticBlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,Avr)==false)
		return false;
	if(::Save(f,Sigma)==false)
		return false;
	if(::Save(f,BrightWidthL)==false)
		return false;
	if(::Save(f,BrightWidthH)==false)
		return false;
	return true;
}
bool	StatisticBlockThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StatisticBlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,Avr)==false)
		return false;
	if(::Load(f,Sigma)==false)
		return false;
	if(::Load(f,BrightWidthL)==false)
		return false;
	if(::Load(f,BrightWidthH)==false)
		return false;
	return true;
}

StatisticBlockReqTryThreshold::StatisticBlockReqTryThreshold(void) 
{
	GlobalPage=-1;
	Layer=-1;
	StatisticBlockItemID=-1;
}
bool	StatisticBlockReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StatisticBlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	StatisticBlockReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StatisticBlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

StatisticBlockSendTryThreshold::StatisticBlockSendTryThreshold(void)
{
	NGDotInDark	=0;
	NGDotInBright	=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
}

bool	StatisticBlockSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotInDark	)==false)
		return false;
	if(::Save(f,NGDotInBright	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	return true;
}
bool	StatisticBlockSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotInDark	)==false)
		return false;
	if(::Load(f,NGDotInBright	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	return true;
}

void	StatisticBlockSendTryThreshold::ConstructList(StatisticBlockReqTryThreshold *reqPacket,StatisticBlockBase *Base)
{
	ResultInItemPLI	Res;
	Res.SetAddedData(this,1,sizeof(this));
	StatisticBlockInPage		*BP=(StatisticBlockInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		StatisticBlockInLayer	*BL=(StatisticBlockInLayer *)BP->GetLayerData(reqPacket->Layer);
		if(BL!=NULL){
			StatisticBlockItem		*BI=(StatisticBlockItem *)BL->SearchIDItem(reqPacket->StatisticBlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.AVector							=BI->AVector;
				reqPacket->Threshold.SetParent(BI->GetParent());
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				BI->Save(&Buff);
				Buff.seek(0);
				reqPacket->Threshold.Load(&Buff,Base->GetLayersBase());
				reqPacket->Threshold.ExecuteProcessing(0,0,&Res);
			}
		}
	}
	Res.SetAddedData(NULL,0);

	ResultMoveDx=Res.GetTotalShiftedX();
	ResultMoveDy=Res.GetTotalShiftedY();
}


//=====================================================================================
void	StatisticBlockChangeShift::Reflect(StatisticBlockBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(StatisticBlockItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	StatisticBlockChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StatisticBlockItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	StatisticBlockChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StatisticBlockItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
//=====================================================================================
StatisticBlockThreshold::StatisticBlockThreshold(StatisticBlockItem *parent)
:AlgorithmThreshold(parent)
{
	BrightWidthL	=1;
	BrightWidthH	=1;
	OKDotL			=0;
	OKDotH			=0;
	OKLengthL		=0;
	OKLengthH		=0;
	PointMove.ModeEnabled				=true;
	PointMove.ModeAbsoluteBright		=false;
	PointMove.ModeNGCluster				=true;
	PointMove.ModeWhiteMask				=false;
	PointMove.ModeBlackMask				=false;
	GeneratedOriginOld	=_FromUnknown;

    AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    AdjustWhite		=20;    //?P?x?a?3?I?a?A??

	UseMorphology		=false;
	MorphologyApplyTo	=MAT_Both;
	EliminateAcnode		=true;
	DilationDotCount	=2;
	ErosionDotCount	=1;
}

void	StatisticBlockThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const StatisticBlockThreshold *s=(const StatisticBlockThreshold *)&src;
	BrightWidthL	=s->BrightWidthL;
	BrightWidthH	=s->BrightWidthH;
	OKDotL			=s->OKDotL;
	OKDotH			=s->OKDotH;
	OKLengthL		=s->OKLengthL;
	OKLengthH		=s->OKLengthH;
	PointMove		=s->PointMove;
	GeneratedOriginOld	=s->GeneratedOriginOld;

    AdjustBlack		=s->AdjustBlack;
    AdjustWhite		=s->AdjustWhite;

	UseMorphology		=s->UseMorphology;
	MorphologyApplyTo	=s->MorphologyApplyTo;
	EliminateAcnode		=s->EliminateAcnode;
	DilationDotCount	=s->DilationDotCount;
	ErosionDotCount		=s->ErosionDotCount;
}
bool	StatisticBlockThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const StatisticBlockThreshold *s=(const StatisticBlockThreshold *)&src;
	if(BrightWidthL			!=s->BrightWidthL		)	return false;
	if(BrightWidthH			!=s->BrightWidthH		)	return false;
	if(OKDotL				!=s->OKDotL				)	return false;
	if(OKDotH				!=s->OKDotH				)	return false;
	if(OKLengthL			!=s->OKLengthL			)	return false;
	if(OKLengthH			!=s->OKLengthH			)	return false;
	if(PointMove.ModeEnabled		!=s->PointMove.ModeEnabled			)	return false;
	if(PointMove.ModeAbsoluteBright	!=s->PointMove.ModeAbsoluteBright	)	return false;
	if(PointMove.ModeNGCluster		!=s->PointMove.ModeNGCluster		)	return false;
	if(PointMove.ModeWhiteMask		!=s->PointMove.ModeWhiteMask		)	return false;
	if(PointMove.ModeBlackMask		!=s->PointMove.ModeBlackMask		)	return false;
	if(GeneratedOriginOld			!=s->GeneratedOriginOld				)	return false;

    if(AdjustBlack			!=s->AdjustBlack		)	return false;
    if(AdjustWhite			!=s->AdjustWhite		)	return false;

	if(UseMorphology		!=s->UseMorphology		)	return false;
	if(MorphologyApplyTo	!=s->MorphologyApplyTo	)	return false;
	if(EliminateAcnode		!=s->EliminateAcnode	)	return false;
	if(DilationDotCount		!=s->DilationDotCount	)	return false;
	if(ErosionDotCount		!=s->ErosionDotCount	)	return false;
	return true;
}
bool	StatisticBlockThreshold::Save(QIODevice *file)
{
	WORD	Ver=StatisticBlockVersion;

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
	if(file->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(file->write((const char *)&GeneratedOriginOld,sizeof(GeneratedOriginOld))!=sizeof(GeneratedOriginOld))
		return false;
	if(::Save(file,AdjustBlack)==false)
		return false;
	if(::Save(file,AdjustWhite)==false)
		return false;

    if(::Save(file,UseMorphology)==false)
		return false;
	int32	MAT = (int32)MorphologyApplyTo;
    if(::Save(file,MAT)==false)
		return false;
    if(::Save(file,EliminateAcnode)==false)
		return false;
    if(::Save(file,DilationDotCount)==false)
		return false;
    if(::Save(file,ErosionDotCount)==false)
		return false;

	return true;
}
bool	StatisticBlockThreshold::Load(QIODevice *file)
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
	if(file->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(file->read((char *)&GeneratedOriginOld,sizeof(GeneratedOriginOld))!=sizeof(GeneratedOriginOld))
		return false;
	if(::Load(file,AdjustBlack)==false)
		return false;
	if(::Load(file,AdjustWhite)==false)
		return false;
	if(Ver>=2){
		if(::Load(file,UseMorphology)==false)
			return false;
		int32	MAT;
		if(::Load(file,MAT)==false)
			return false;
		MorphologyApplyTo = (_MorphologyApplyTo)MAT;
		if(::Load(file,EliminateAcnode)==false)
			return false;
		if(::Load(file,DilationDotCount)==false)
			return false;
		if(::Load(file,ErosionDotCount)==false)
			return false;
	}else{
		UseMorphology = false;
		MorphologyApplyTo = _MorphologyApplyTo::MAT_Both;
		EliminateAcnode = true;
		DilationDotCount = 2;
		ErosionDotCount = 1;
	}
	return true;
}

void	StatisticBlockThreshold::FromLibrary(AlgorithmLibrary *src)
{
	StatisticBlockLibrary	*LSrc=dynamic_cast<StatisticBlockLibrary *>(src);
	if(LSrc==NULL)
		return;
	BrightWidthL	=LSrc->BrightWidthL;
	BrightWidthH	=LSrc->BrightWidthH;
	OKDotL			=LSrc->OKDotL;
	OKDotH			=LSrc->OKDotH;
	OKLengthL		=LSrc->OKLengthL;
	OKLengthH		=LSrc->OKLengthH;

	PointMove.ModeEnabled				=LSrc->PointMove.ModeEnabled;
	PointMove.ModeAbsoluteBright		=LSrc->PointMove.ModeAbsoluteBright;
	PointMove.ModeNGCluster				=LSrc->PointMove.ModeNGCluster;
	PointMove.ModeWhiteMask				=LSrc->PointMove.ModeWhiteMask;
	PointMove.ModeBlackMask				=LSrc->PointMove.ModeBlackMask;
	GetParentItem()->SetOriginType(_OriginType_FromLibrary);

	AdjustBlack							=LSrc->AdjustBlack;
	AdjustWhite							=LSrc->AdjustWhite;

	UseMorphology						=LSrc->UseMorphology;
	MorphologyApplyTo					=(_MorphologyApplyTo)LSrc->MorphologyApplyTo;
	EliminateAcnode						=LSrc->EliminateAcnode;
	DilationDotCount					=LSrc->DilationDotCount;
	ErosionDotCount					=LSrc->ErosionDotCount;
}
void	StatisticBlockThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	StatisticBlockLibrary	*LDst=dynamic_cast<StatisticBlockLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->BrightWidthL	=BrightWidthL;
	LDst->BrightWidthH	=BrightWidthH;
	LDst->OKDotL		=OKDotL		;
	LDst->OKDotH		=OKDotH	;
	LDst->OKLengthL		=OKLengthL		;
	LDst->OKLengthH		=OKLengthH	;

	LDst->PointMove.ModeEnabled			=PointMove.ModeEnabled		;
	LDst->PointMove.ModeAbsoluteBright	=PointMove.ModeAbsoluteBright;
	LDst->PointMove.ModeNGCluster		=PointMove.ModeNGCluster	;
	LDst->PointMove.ModeWhiteMask		=PointMove.ModeWhiteMask		;
	LDst->PointMove.ModeBlackMask		=PointMove.ModeBlackMask		;

	LDst->AdjustBlack					=AdjustBlack		;
	LDst->AdjustWhite					=AdjustWhite		;

	LDst->UseMorphology					=UseMorphology;
	LDst->MorphologyApplyTo				=(StatisticBlockLibrary::_MorphologyApplyTo)MorphologyApplyTo;
	LDst->EliminateAcnode				=EliminateAcnode;
	LDst->DilationDotCount				=DilationDotCount;
	LDst->ErosionDotCount				=ErosionDotCount;
}

//====================================================================================================
StatisticBlockItem::StatisticBlockItem(void) 
{
	AVector=NULL;
	Sigma=0.0;
	Avr=0.0;
	AreaDots	=0;
	DegradeRate=1.0;
}
StatisticBlockItem::StatisticBlockItem(FlexArea &area)
:AlgorithmItemPLI(area)
{
	AVector=NULL;
	Sigma=0.0;
	Avr=0.0;
	AreaDots	=0;
	DegradeRate=1.0;
}

StatisticBlockItem::~StatisticBlockItem(void)
{}
void    StatisticBlockItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPLI::MoveTo(dx,dy);
}

AlgorithmItemPLI	&StatisticBlockItem::operator=(const AlgorithmItemRoot &src)
{
	const StatisticBlockItem	*s=dynamic_cast<const StatisticBlockItem *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}
StatisticBlockItem &StatisticBlockItem::operator=(StatisticBlockItem &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(src);
	return *this;
}

void	StatisticBlockItem::CopyThreshold(StatisticBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((StatisticBlockThreshold *)src.GetThresholdR()));
}

void	StatisticBlockItem::CopyThresholdOnly(StatisticBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((StatisticBlockThreshold *)src.GetThresholdR()));
}

bool    StatisticBlockItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;
	return true;
}
bool    StatisticBlockItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	return true;
}

void	StatisticBlockItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			CopyThresholdOnly(*((StatisticBlockItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((StatisticBlockItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((StatisticBlockItem *)Data));
		}
	}
}


int		StatisticBlockItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}

void	StatisticBlockItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);

	int	OmitZoneDot=((StatisticBlockBase *)GetParentBase())->OmitZoneDot;
	GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
}


ExeResult	StatisticBlockItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	
	AreaDots=GetArea().GetPatternByte();
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	if(((StatisticBlockBase *)GetParentBase())->SideDegradeRate<1.0){
		double	s=acos(((StatisticBlockBase *)GetParentBase())->SideDegradeRate);
		DegradeRate=cos(s*abs(cx-GetDotPerLine()/2)/(GetDotPerLine()/2));
	}
	else
		DegradeRate=1.0;

	return Ret;
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	StatisticBlockItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID && GetParent()->GetLayer()==DbgLayer)
		DbgNumer++;

	WORD	OKLengthL;
	WORD	OKLengthH;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	StatisticBlockInLayer	*P=(StatisticBlockInLayer *)GetParentInLayer();

	const StatisticBlockThreshold	*RThr=GetThresholdR();
	short	Error=0;
	if(ExecuteProcessingInner(ThreadNo,Res
							  ,mx ,my
							  ,RThr->BrightWidthL	,RThr->BrightWidthH
							  ,RThr->OKDotL			,RThr->OKDotH
							  ,RThr->OKLengthL		,RThr->OKLengthH
							  ,P->DynamicMaskMap	,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
		Error = 0x02 | (Res->GetError()&0xF0);		//?m?f?-?÷
		Res->SetError(2 | (Res->GetError()&0xF0));
		FinishCalc();
		return _ER_true;
	}
	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			StatisticBlockSendTryThreshold	*Q=dynamic_cast<StatisticBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->NGDotInDark		=Res->GetResult1();
				Q->NGDotInBright	=Res->GetResult2();
			}
		}
	}
	Res->SetError(Error);
	FinishCalc();
	return _ER_true;
}

void	StatisticBlockItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	StatisticBlockDrawAttr	*BAttr=dynamic_cast<StatisticBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		StatisticBlockDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		//QColor	BuffColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	TmpAttr.NormalColor=BAttr->BlockColor0;	break;
			case 1:	TmpAttr.NormalColor=BAttr->BlockColor1;	break;
			case 2:	TmpAttr.NormalColor=BAttr->BlockColor2;	break;
			case 3:	TmpAttr.NormalColor=BAttr->BlockColor3;	break;
			case 4:	TmpAttr.NormalColor=BAttr->BlockColor4;	break;
			case 5:	TmpAttr.NormalColor=BAttr->BlockColor5;	break;
			case 6:	TmpAttr.NormalColor=BAttr->BlockColor6;	break;
			case 7:	TmpAttr.NormalColor=BAttr->BlockColor7;	break;
		}
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	StatisticBlockItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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
						+QString(/**/" Sft(")+QString::number(Res->GetTotalShiftedX())+QString(/**/",")+QString::number(Res->GetTotalShiftedY())+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
					if(Res->GetError()==2){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"L=")+QString::number(Res->GetResult1())
							,&rect);
					}
				}
			}
		}
	}
}

//===========================================================================================

StatisticBlockInLayer::StatisticBlockInLayer(AlgorithmInPageRoot *parent):AlgorithmInLayerPLI(parent)
{
	PickupBmp=NULL;
	PickupBmpYLen	=0;
	PickupBmpXByte	=0;
	DynamicMaskMap	=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;

	int	ThreadNumb;
	#pragma omp parallel                             
	{             
		ThreadNumb=omp_get_num_threads();
	}
}
StatisticBlockInLayer::~StatisticBlockInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}
void	StatisticBlockInLayer::CreatePickupBmpBuff(void)
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

ExeResult	StatisticBlockInLayer::ExecuteProcessing(int ExeID ,ResultInLayerRoot *Res)
{
	DynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	DynamicMaskMapXByte	=GetDataInPage()->GetDynamicMaskMapXByte();
	DynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	return AlgorithmInLayerPLI::ExecuteProcessing(ExeID ,Res);
}


void	StatisticBlockInLayer::PickupTest(StatisticBlockLibrary &LibData)
{
	CreatePickupBmpBuff();

	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);
	LibData.MakePickupTest(GetMasterBuff()
		,MaskMap.GetBitMap()
		,PickupBmp,NULL
		,GetPage()
		,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
		,((StatisticBlockBase *)GetParentBase())->OmitZoneDot);
}

void	StatisticBlockInLayer::GenerateStatisticBlocks(StatisticBlockLibrary *LibDim[],int LibDimNumb)
{
	CreatePickupBmpBuff();
	CommonMoveIDList.RemoveAll();
	//Data.RemoveAll();
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;
	BYTE **GeneratedMap=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(GeneratedMap,0,XByte,GetMaxLines());

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
		if(Lib!=NULL){
			StatisticBlockLibrary	*BLib=(StatisticBlockLibrary *)Lib;
			int	BSpaceToOutline;
			if(BLib->GenerationCategory==StatisticBlockLibrary::_AutoSetting_OTHERMASK
				|| BLib->GenerationCategory==StatisticBlockLibrary::_AutoSetting_SURROUND){
				BSpaceToOutline=0;
			}
			else{
				BSpaceToOutline=BLib->SpaceToOutline;
			}
			L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			
			MatrixBuffOrBlock(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines()
							 ,(L->GetArea().GetMinX()-BSpaceToOutline)>>3,L->GetArea().GetMinY()-BSpaceToOutline
							 ,(L->GetArea().GetMaxX()+BSpaceToOutline+7)>>3,L->GetArea().GetMaxY()+BSpaceToOutline);	
		}
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2	 ,GetMaxLines());

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBuffer MaskMap;
		GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();
		MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

		LibDim[i]->MakePickupTest(GetMasterBuff()
			,MaskBitmap
			,CurrentMap,OcupyMap
			,GetPage()
			,XByte ,GetDotPerLine(),GetMaxLines()
			,((StatisticBlockBase *)GetParentBase())->OmitZoneDot);
		if(LibDim[i]->GenerationMode.LeftPickup==false){
			NPListPack<AlgorithmItemPLI>	TmpBlockData;
			LibDim[i]->MakeBlock(
				 CurrentMap,LastOcupyMap
				 ,GetPage()
				,XByte ,GetDotPerLine(),GetMaxLines()
				,TmpBlockData);
			AlgorithmItemPLI	*q;
			while((q=TmpBlockData.GetFirst())!=NULL){
				TmpBlockData.RemoveList(q);
				AppendItem(q);
			}
		}
		MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
		//if(MaskBitmap!=NULL)
		//	DeleteMatrixBuff(MaskBitmap,GetMaxLines());
	}
	DeleteMatrixBuff(CurrentMap	 ,GetMaxLines());
	DeleteMatrixBuff(OcupyMap	 ,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap,GetMaxLines());
	DeleteMatrixBuff(GeneratedMap,GetMaxLines());
}
bool	StatisticBlockInLayer::Save(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Save(f)==false)
		return false;
	return true;
}
bool	StatisticBlockInLayer::Load(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Load(f)==false)
		return false;
	return true;
}


void	StatisticBlockInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedStatisticBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedStatisticBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		StatisticBlockItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			StatisticBlockItem	*B=(StatisticBlockItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				StatisticBlockItem	*B=(StatisticBlockItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
	}
	CmdClearTestStatisticBlockPacket	*CmdClearTestStatisticBlockPacketVar=dynamic_cast<CmdClearTestStatisticBlockPacket *>(packet);
	if(CmdClearTestStatisticBlockPacketVar!=NULL){
		if(PickupBmp!=NULL)
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
	}
	CmdStatisticBlockInfoListPacket	*CmdStatisticBlockInfoListPacketVar=dynamic_cast<CmdStatisticBlockInfoListPacket *>(packet);
	if(CmdStatisticBlockInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			StatisticBlockInfoList	*a;
			for(a=CmdStatisticBlockInfoListPacketVar->StatisticBlockInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->StatisticBlockCount.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new StatisticBlockInfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					if(layer==GetLayer())
						a->StatisticBlockCount.Add(1);
					else
						a->StatisticBlockCount.Add(0);
				}
				CmdStatisticBlockInfoListPacketVar->StatisticBlockInfos->AppendList(a);
			}
		}
	}
	CmdGetStatisticBlockFromList	*CmdGetStatisticBlockFromListVar=dynamic_cast<CmdGetStatisticBlockFromList *>(packet);
	if(CmdGetStatisticBlockFromListVar!=NULL){
		StatisticBlockItem *Item=(StatisticBlockItem *)SearchIDItem(CmdGetStatisticBlockFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetStatisticBlockFromListVar->StatisticBlockInfoOnMouse=Item;
	}
	CmdCreateStatisticBlockItem	*CmdCreateStatisticBlockItemVar=dynamic_cast<CmdCreateStatisticBlockItem *>(packet);
	if(CmdCreateStatisticBlockItemVar!=NULL){
		CmdCreateStatisticBlockItemVar->StatisticBlock=(StatisticBlockItem *)CreateItem(0);
	}
}

void	StatisticBlockInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	StatisticBlockDrawAttr	*BAttr=dynamic_cast<StatisticBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==CmdStatisticBlockDrawModePacket::_LibTest){
			if(PickupBmp!=NULL){
				StatisticBlockBase	*BBase=dynamic_cast<StatisticBlockBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==CmdStatisticBlockDrawModePacket::_CreatedBlock){
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

//===========================================================================================

void	StatisticBlockInPage::PickupTest(IntList &LayerList ,StatisticBlockLibrary &LibData)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerPLI	*AL=GetLayerDataPLI(L->GetValue());
			StatisticBlockInLayer	*BI=dynamic_cast<StatisticBlockInLayer *>(AL);
			if(BI!=NULL){
				BI->PickupTest(LibData);
			}
		}
	}
}
void	StatisticBlockInPage::GenerateStatisticBlocks(IntList &LayerList, StatisticBlockLibrary *LibDim[],int LibDimNumb)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerPLI	*AL=GetLayerDataPLI(L->GetValue());
			StatisticBlockInLayer	*BI=dynamic_cast<StatisticBlockInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateStatisticBlocks(LibDim,LibDimNumb);
			}
		}
	}
}
void	StatisticBlockInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedStatisticBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedStatisticBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(IntClass *L=ModifyItemFromBA->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}	
	CmdClearTestStatisticBlockPacket	*CmdClearTestStatisticBlockPacketVar=dynamic_cast<CmdClearTestStatisticBlockPacket *>(packet);
	if(CmdClearTestStatisticBlockPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdClearTestStatisticBlockPacketVar);
		}
	}
	CmdStatisticBlockInfoListPacket	*CmdStatisticBlockInfoListPacketVar=dynamic_cast<CmdStatisticBlockInfoListPacket *>(packet);
	if(CmdStatisticBlockInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdStatisticBlockInfoListPacketVar);
		}
	}
	CmdGetStatisticBlockFromList	*CmdGetStatisticBlockFromListVar=dynamic_cast<CmdGetStatisticBlockFromList *>(packet);
	if(CmdGetStatisticBlockFromListVar!=NULL){
		if(CmdGetStatisticBlockFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetStatisticBlockFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
	}
	CmdCreateStatisticBlockItem	*CmdCreateStatisticBlockItemVar=dynamic_cast<CmdCreateStatisticBlockItem *>(packet);
	if(CmdCreateStatisticBlockItemVar!=NULL){
		AlgorithmInLayerRoot	*p=GetLayerData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

//===========================================================================================
StatisticBlockBase::StatisticBlockBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	ColorBlockNormal	=Qt::darkGreen;
	ColorBlockSelected	=Qt::green;
	ColorBlockActive	=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;
	MinDotRate	=0.001;
	SideDegradeRate=0.7;
	ExcludedL=20;
	ExcludedH=220;

	SetParam(&ColorPickup		, /**/"Color" ,/**/"ColorPickup"		,LangSolver.GetString(XStatisticBlock_LS,LID_1)/*"Color for Image to Pickup-Test "*/);
	SetParam(&ColorBlockNormal	, /**/"Color" ,/**/"ColorBlockNormal"	,LangSolver.GetString(XStatisticBlock_LS,LID_3)/*"Color for Block"*/);
	SetParam(&ColorBlockSelected, /**/"Color" ,/**/"ColorBlockSelected"	,LangSolver.GetString(XStatisticBlock_LS,LID_5)/*"Color for Selected Block"*/);
	SetParam(&ColorBlockActive	, /**/"Color" ,/**/"ColorBlockActive"	,LangSolver.GetString(XStatisticBlock_LS,LID_7)/*"Color for Active Block"*/);

	SetParam(&BlockColor0	, /**/"BlockColor" ,/**/"BlockColor0"	,LangSolver.GetString(XStatisticBlock_LS,LID_9)/*"Block Color 0"*/);
	SetParam(&BlockColor1	, /**/"BlockColor" ,/**/"BlockColor1"	,LangSolver.GetString(XStatisticBlock_LS,LID_11)/*"Block Color 1"*/);
	SetParam(&BlockColor2	, /**/"BlockColor" ,/**/"BlockColor2"	,LangSolver.GetString(XStatisticBlock_LS,LID_13)/*"Block Color 2"*/);
	SetParam(&BlockColor3	, /**/"BlockColor" ,/**/"BlockColor3"	,LangSolver.GetString(XStatisticBlock_LS,LID_15)/*"Block Color 3"*/);
	SetParam(&BlockColor4	, /**/"BlockColor" ,/**/"BlockColor4"	,LangSolver.GetString(XStatisticBlock_LS,LID_17)/*"Block Color 4"*/);
	SetParam(&BlockColor5	, /**/"BlockColor" ,/**/"BlockColor5"	,LangSolver.GetString(XStatisticBlock_LS,LID_19)/*"Block Color 5"*/);
	SetParam(&BlockColor6	, /**/"BlockColor" ,/**/"BlockColor6"	,LangSolver.GetString(XStatisticBlock_LS,LID_21)/*"Block Color 6"*/);
	SetParam(&BlockColor7	, /**/"BlockColor" ,/**/"BlockColor7"	,LangSolver.GetString(XStatisticBlock_LS,LID_23)/*"Block Color 7"*/);

	SetParam(&OmitZoneDot	, /**/"Setting"		,/**/"OmitZoneDot"	,LangSolver.GetString(XStatisticBlock_LS,LID_25)/*"Omit zone dot in block generation"*/);
	SetParam(&MinDotRate	, /**/"Setting"		,/**/"MinDotRate"	,LangSolver.GetString(XStatisticBlock_LS,LID_27)/*"Cut off in less dot of this rate"*/);
	SetParam(&SideDegradeRate,/**/"Setting"		,/**/"SideDegradeRate",LangSolver.GetString(XStatisticBlock_LS,LID_29)/*"Degrade rate on side"*/);
	SetParam(&ExcludedL		, /**/"Setting"		,/**/"ExcludedL",LangSolver.GetString(XStatisticBlock_LS,LID_34)/*"Excluded low side brightness"*/);
	SetParam(&ExcludedH		, /**/"Setting"		,/**/"ExcludedH",LangSolver.GetString(XStatisticBlock_LS,LID_35)/*"Excluded high side brightness"*/);
}

AlgorithmDrawAttr	*StatisticBlockBase::CreateDrawAttr(void)
{
	return new StatisticBlockDrawAttr();
}

void	StatisticBlockBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStatisticBlockLibraryListPacket	*AListPacket=dynamic_cast<CmdGetStatisticBlockLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetStatisticBlockLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetStatisticBlockLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertStatisticBlockLibraryPacket	*BInsLib=dynamic_cast<CmdInsertStatisticBlockLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(StatisticBlockVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateStatisticBlockLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateStatisticBlockLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(StatisticBlockVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadStatisticBlockLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadStatisticBlockLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempStatisticBlockLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempStatisticBlockLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdDeleteStatisticBlockLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteStatisticBlockLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestStatisticBlockPacket	*BPickLib=dynamic_cast<CmdPickupTestStatisticBlockPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		StatisticBlockInPage	*Bp=dynamic_cast<StatisticBlockInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(BPickLib->LayerList,*(StatisticBlockLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateStatisticBlockPacket	*BGenerated=dynamic_cast<CmdGenerateStatisticBlockPacket *>(packet);
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
				StatisticBlockLibrary	*L1=dynamic_cast<StatisticBlockLibrary *>(LibDim[i  ]->GetLibrary());
				StatisticBlockLibrary	*L2=dynamic_cast<StatisticBlockLibrary *>(LibDim[i+1]->GetLibrary());
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
		StatisticBlockLibrary	**DDim=new StatisticBlockLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<StatisticBlockLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			StatisticBlockInPage	*Bp=dynamic_cast<StatisticBlockInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateStatisticBlocks(BGenerated->LayerList,DDim,N);		
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
	CmdCreateTempStatisticBlockItemPacket	*CreateStatisticBlockItem=dynamic_cast<CmdCreateTempStatisticBlockItemPacket *>(packet);
	if(CreateStatisticBlockItem!=NULL){
		CreateStatisticBlockItem->Point=new StatisticBlockItem();
		return;
	}
	CmdCreateByteArrayFromStatisticBlockItemPacket	*BAFromStatisticBlockItem=dynamic_cast<CmdCreateByteArrayFromStatisticBlockItemPacket *>(packet);
	if(BAFromStatisticBlockItem!=NULL){
		QBuffer	Buff(&BAFromStatisticBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromStatisticBlockItem->Point->Save(&Buff);
	}
	CmdAddByteStatisticBlockItemPacket	*AddBItem=dynamic_cast<CmdAddByteStatisticBlockItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePLI		*PData=dynamic_cast<AlgorithmInPagePLI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			for(IntClass *L=AddBItem->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
				StatisticBlockInLayer	*BL=dynamic_cast<StatisticBlockInLayer *>(PData->GetLayerData(L->GetValue()));
				if(BL!=NULL){
					QBuffer	MBuff(&AddBItem->Buff);
					StatisticBlockItem	*Item=new StatisticBlockItem();
					MBuff.open(QIODevice::ReadWrite);
					Item->Load(&MBuff,GetLayersBase());
					Item->SetArea(AddBItem->Area);
					Item->SetManualCreated(true);
					BL->AppendItem(Item);
				}
			}
		}
	}
	CmdLoadStatisticBlockItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadStatisticBlockItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedStatisticBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedStatisticBlockFromByteArray *>(packet);
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
	CmdClearTestStatisticBlockPacket	*CmdClearTestStatisticBlockPacketVar=dynamic_cast<CmdClearTestStatisticBlockPacket *>(packet);
	if(CmdClearTestStatisticBlockPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestStatisticBlockPacketVar);
		}
	}
	CmdStatisticBlockInfoListPacket	*CmdStatisticBlockInfoListPacketVar=dynamic_cast<CmdStatisticBlockInfoListPacket *>(packet);
	if(CmdStatisticBlockInfoListPacketVar!=NULL){
		GetPageData(CmdStatisticBlockInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetStatisticBlockFromList	*CmdGetStatisticBlockFromListVar=dynamic_cast<CmdGetStatisticBlockFromList *>(packet);
	if(CmdGetStatisticBlockFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetStatisticBlockFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateStatisticBlockItem	*CmdCreateStatisticBlockItemVar=dynamic_cast<CmdCreateStatisticBlockItem *>(packet);
	if(CmdCreateStatisticBlockItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

bool	StatisticBlockBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==StatisticBlockHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==StatisticBlockHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==StatisticBlockReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==StatisticBlockReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==StatisticBlockReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==StatisticBlockSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==StatisticBlockReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*StatisticBlockBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==StatisticBlockHistogramListSendCommand){
		StatisticBlockHistogramListSend	*pSend=new StatisticBlockHistogramListSend();
		if(reqData!=NULL){
			StatisticBlockHistogramListReq	*req=(StatisticBlockHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==StatisticBlockHistogramListReqCommand){
		return new StatisticBlockHistogramListReq();
	}
	else if(Command==StatisticBlockReqThresholdReqCommand){
		return new StatisticBlockThresholdReq();
	}
	else if(Command==StatisticBlockReqThresholdSendCommand){
		StatisticBlockThresholdSend	*pSend=new StatisticBlockThresholdSend();
		if(reqData!=NULL){
			StatisticBlockThresholdReq	*req=(StatisticBlockThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==StatisticBlockReqTryThresholdCommand){
		return new StatisticBlockReqTryThreshold();
	}
	else if(Command==StatisticBlockSendTryThresholdCommand){
		StatisticBlockSendTryThreshold	*pSend=new StatisticBlockSendTryThreshold();
		if(reqData!=NULL){
			StatisticBlockReqTryThreshold	*req=(StatisticBlockReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==StatisticBlockReqChangeShiftCommand){
		return new StatisticBlockChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	StatisticBlockBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==StatisticBlockHistogramListSendCommand){
		StatisticBlockHistogramListSend	*p=(StatisticBlockHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==StatisticBlockHistogramListReqCommand){
		StatisticBlockHistogramListReq	*p=(StatisticBlockHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==StatisticBlockReqThresholdReqCommand){
		StatisticBlockThresholdReq	*p=(StatisticBlockThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==StatisticBlockReqThresholdSendCommand){
		StatisticBlockThresholdSend	*p=(StatisticBlockThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==StatisticBlockReqTryThresholdCommand){
		StatisticBlockReqTryThreshold	*p=(StatisticBlockReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==StatisticBlockSendTryThresholdCommand){
		StatisticBlockSendTryThreshold	*p=(StatisticBlockSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==StatisticBlockReqChangeShiftCommand){
		StatisticBlockChangeShift	*p=(StatisticBlockChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	StatisticBlockBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==StatisticBlockHistogramListSendCommand){
		StatisticBlockHistogramListSend	*p=(StatisticBlockHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==StatisticBlockHistogramListReqCommand){
		StatisticBlockHistogramListReq	*p=(StatisticBlockHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==StatisticBlockReqThresholdReqCommand){
		StatisticBlockThresholdReq	*p=(StatisticBlockThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==StatisticBlockReqThresholdSendCommand){
		StatisticBlockThresholdSend	*p=(StatisticBlockThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==StatisticBlockReqTryThresholdCommand){
		StatisticBlockReqTryThreshold	*p=(StatisticBlockReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==StatisticBlockSendTryThresholdCommand){
		StatisticBlockSendTryThreshold	*p=(StatisticBlockSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==StatisticBlockReqChangeShiftCommand){
		StatisticBlockChangeShift	*p=(StatisticBlockChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	StatisticBlockBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==StatisticBlockHistogramListSendCommand){
		StatisticBlockHistogramListSend	*p=(StatisticBlockHistogramListSend *)data;
		return true;
	}
	else if(Command==StatisticBlockHistogramListReqCommand){
		StatisticBlockHistogramListReq	*p=(StatisticBlockHistogramListReq *)data;
		return true;
	}
	else if(Command==StatisticBlockReqThresholdReqCommand){
		StatisticBlockThresholdReq	*p=(StatisticBlockThresholdReq *)data;
		return true;
	}
	else if(Command==StatisticBlockReqThresholdSendCommand){
		StatisticBlockThresholdSend	*p=(StatisticBlockThresholdSend *)data;
		return true;
	}
	else if(Command==StatisticBlockReqTryThresholdCommand){
		StatisticBlockReqTryThreshold	*p=(StatisticBlockReqTryThreshold *)data;
		return true;
	}
	else if(Command==StatisticBlockSendTryThresholdCommand){
		StatisticBlockSendTryThreshold	*p=(StatisticBlockSendTryThreshold *)data;
		return true;
	}
	else if(Command==StatisticBlockReqChangeShiftCommand){
		StatisticBlockChangeShift	*p=(StatisticBlockChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	StatisticBlockBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	ChangeCreateStatisticBlockForm	Q(this);
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultStatisticBlock.Save(&Buff)==false)
			return false;
	}
	return ret;
	*/
	return true;
}


//===========================================================================================

