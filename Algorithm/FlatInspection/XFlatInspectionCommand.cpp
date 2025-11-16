//#include "FlatInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\FlatInspectionInspection\XFlatInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XFlatInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspectionAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

extern	const	char	*sRoot;
extern	const	char	*sName;



FlatInspectionHistogramListReq::FlatInspectionHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	FlatInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	FlatInspectionHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,FlatInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	FlatInspectionHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,FlatInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


FlatInspectionHistogramListSend::FlatInspectionHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	FlatInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMasterR,0,sizeof(ListMasterR));
	memset(ListMasterG,0,sizeof(ListMasterG));
	memset(ListMasterB,0,sizeof(ListMasterB));
	memset(ListTargetR,0,sizeof(ListTargetR));
	memset(ListTargetG,0,sizeof(ListTargetG));
	memset(ListTargetB,0,sizeof(ListTargetB));
	CenterBrightR		=0;
	CenterBrightG		=0;
	CenterBrightB		=0;
	CenterTargetBrightR	=0;
	CenterTargetBrightG	=0;
	CenterTargetBrightB	=0;
}
void	FlatInspectionHistogramListSend::ConstructList(FlatInspectionHistogramListReq *reqPacket ,FlatInspectionBase *Base)
{
	memset(ListMasterR,0,sizeof(ListMasterR));
	memset(ListMasterG,0,sizeof(ListMasterG));
	memset(ListMasterB,0,sizeof(ListMasterB));
	memset(ListTargetR,0,sizeof(ListTargetR));
	memset(ListTargetG,0,sizeof(ListTargetG));
	memset(ListTargetB,0,sizeof(ListTargetB));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	FlatInspectionItemID	=reqPacket->FlatInspectionItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		int	LayerNumb=Ap->GetLayerNumb();
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(FlatInspectionItemID);
		if(item!=NULL){
			FlatInspectionItem	*Item=dynamic_cast<FlatInspectionItem*>(item);
			bool	BuiltList=false;
			if(BuiltList==false){
				ImagePointerContainer ImageList;			
				Item->GetMasterBuffList(ImageList);
				item->GetArea().MakeBrightList(ListMasterR ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[0],0 ,0);
				if(LayerNumb>=2){
					item->GetArea().MakeBrightList(ListMasterG ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[1],0 ,0);
				}
				if(LayerNumb>=3){
					item->GetArea().MakeBrightList(ListMasterB ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[2],0 ,0);
				}
			}
		
			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				ImagePointerContainer ImageList;
				Item->GetTargetBuffList(ImageList);
				if(Rp!=NULL){
					ResultInItemPI		*rItem=Rp->SearchItem(Item->GetID());
					if(rItem!=NULL){
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						item->GetArea().MakeBrightList(ListTargetR ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[0],sx ,sy);
						if(LayerNumb>=2){
							item->GetArea().MakeBrightList(ListTargetG ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[1],sx ,sy);
						}
						if(LayerNumb>=3){
							item->GetArea().MakeBrightList(ListTargetB ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[2],sx ,sy);
						}
					}
					else{
						item->GetArea().MakeBrightList(ListTargetR ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[0],0 ,0);
						if(LayerNumb>=2){
							item->GetArea().MakeBrightList(ListTargetG ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[1],0 ,0);
						}
						if(LayerNumb>=3){
							item->GetArea().MakeBrightList(ListTargetB ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[2],0 ,0);
						}
					}
				}
			}
			CenterBrightR		=Item->CenterBrightR;
			CenterBrightG		=Item->CenterBrightG;
			CenterBrightB		=Item->CenterBrightB;
			CenterTargetBrightR	=Item->CenterTargetBrightR;
			CenterTargetBrightG	=Item->CenterTargetBrightG;
			CenterTargetBrightB	=Item->CenterTargetBrightB;
		}
	}
}

bool	FlatInspectionHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,FlatInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(f->write((const char *)ListMasterR,sizeof(ListMasterR))!=sizeof(ListMasterR))
		return false;
	if(f->write((const char *)ListMasterG,sizeof(ListMasterG))!=sizeof(ListMasterG))
		return false;
	if(f->write((const char *)ListMasterB,sizeof(ListMasterB))!=sizeof(ListMasterB))
		return false;
	if(f->write((const char *)ListTargetR,sizeof(ListTargetR))!=sizeof(ListTargetR))
		return false;
	if(f->write((const char *)ListTargetG,sizeof(ListTargetG))!=sizeof(ListTargetG))
		return false;
	if(f->write((const char *)ListTargetB,sizeof(ListTargetB))!=sizeof(ListTargetB))
		return false;
	if(::Save(f,CenterBrightR)==false)
		return false;
	if(::Save(f,CenterBrightG)==false)
		return false;
	if(::Save(f,CenterBrightB)==false)
		return false;
	if(::Save(f,CenterTargetBrightR)==false)
		return false;
	if(::Save(f,CenterTargetBrightG)==false)
		return false;
	if(::Save(f,CenterTargetBrightB)==false)
		return false;
	return true;
}
bool	FlatInspectionHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,FlatInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(f->read((char *)ListMasterR,sizeof(ListMasterR))!=sizeof(ListMasterR))
		return false;
	if(f->read((char *)ListMasterG,sizeof(ListMasterG))!=sizeof(ListMasterG))
		return false;
	if(f->read((char *)ListMasterB,sizeof(ListMasterB))!=sizeof(ListMasterB))
		return false;
	if(f->read((char *)ListTargetR,sizeof(ListTargetR))!=sizeof(ListTargetR))
		return false;
	if(f->read((char *)ListTargetG,sizeof(ListTargetG))!=sizeof(ListTargetG))
		return false;
	if(f->read((char *)ListTargetB,sizeof(ListTargetB))!=sizeof(ListTargetB))
		return false;
	if(::Load(f,CenterBrightR)==false)
		return false;
	if(::Load(f,CenterBrightG)==false)
		return false;
	if(::Load(f,CenterBrightB)==false)
		return false;
	if(::Load(f,CenterTargetBrightR)==false)
		return false;
	if(::Load(f,CenterTargetBrightG)==false)
		return false;
	if(::Load(f,CenterTargetBrightB)==false)
		return false;
	return true;
}
FlatInspectionThresholdReq::FlatInspectionThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	FlatInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	FlatInspectionThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,FlatInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	FlatInspectionThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,FlatInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

FlatInspectionThresholdSend::FlatInspectionThresholdSend(void)
{
	ThresholdValues.GlobalPage=-1;
	ThresholdValues.Layer=-1;
	ThresholdValues.FlatInspectionItemID=-1;
	ThresholdValues.Mastered=true;
	ThresholdValues.Dx=0;
	ThresholdValues.Dy=0;

	ThresholdValues.CenterBrightR		=0;
	ThresholdValues.CenterBrightG		=0;
	ThresholdValues.CenterBrightB		=0;
	ThresholdValues.CenterTargetBrightR	=0;
	ThresholdValues.CenterTargetBrightG	=0;
	ThresholdValues.CenterTargetBrightB	=0;

	ThresholdValues.TargetSDRL			=0;
	ThresholdValues.TargetSDRH			=0;
	ThresholdValues.TargetSDGL			=0;
	ThresholdValues.TargetSDGH			=0;
	ThresholdValues.TargetSDBL			=0;
	ThresholdValues.TargetSDBH			=0;

	ThresholdValues.OrgOKDotB			=0;
	ThresholdValues.OrgOKDotN			=0;
}

void	FlatInspectionThresholdSend::ConstructList(FlatInspectionThresholdReq *reqPacket,FlatInspectionBase *Base)
{
	ThresholdValues.GlobalPage	=reqPacket->GlobalPage;
	ThresholdValues.Layer		=reqPacket->Layer;
	ThresholdValues.FlatInspectionItemID	=reqPacket->FlatInspectionItemID;
	ThresholdValues.Mastered	=reqPacket->Mastered;
	ThresholdValues.Dx			=reqPacket->Dx;
	ThresholdValues.Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(ThresholdValues.GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ThresholdValues.FlatInspectionItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}

			FlatInspectionItem	*BItem=(FlatInspectionItem *)item;
			ImagePointerContainer ImageList;
			BItem->GetMasterBuffList(ImageList);
			int	LayerNumb=Base->GetLayersBase()->GetLayerNumb(localPage);
			if(BItem->CenterBrightR==0){
				float	LVar,HVar;
				BItem->CenterBrightR=BItem->CalcCenterBright(*ImageList[0],0,0,LVar,HVar);
				BItem->CenterTargetBrightR=BItem->CenterBrightR;
			}
			if(BItem->CenterBrightG==0 && LayerNumb>=2){
				float	LVar,HVar;
				BItem->CenterBrightG=BItem->CalcCenterBright(*ImageList[1],0,0,LVar,HVar);
				BItem->CenterTargetBrightG=BItem->CenterBrightG;
			}
			if(BItem->CenterBrightB==0 && LayerNumb>=3){
				float	LVar,HVar;
				BItem->CenterBrightB=BItem->CalcCenterBright(*ImageList[2],0,0,LVar,HVar);
				BItem->CenterTargetBrightB=BItem->CenterBrightB;
			}
			const	FlatInspectionThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			ThresholdValues.CenterBrightR	=BItem->CenterBrightR;
			ThresholdValues.CenterBrightG	=BItem->CenterBrightG;
			ThresholdValues.CenterBrightB	=BItem->CenterBrightB;
			ThresholdValues.OrgOKDotB			=RThr->Broad.OrgOKDot		;
			ThresholdValues.OrgOKDotN			=RThr->Narrow.OrgOKDot		;
			
			BItem->GetTargetBuffList(ImageList);
			ThresholdValues.CenterTargetBrightR=BItem->CalcCenterBright(*ImageList[0],dx,dy,ThresholdValues.TargetSDRL,ThresholdValues.TargetSDRH);
			if(LayerNumb>=2){
				ThresholdValues.CenterTargetBrightG=BItem->CalcCenterBright(*ImageList[1],dx,dy,ThresholdValues.TargetSDGL,ThresholdValues.TargetSDGH);
			}
			if(LayerNumb>=3){
				ThresholdValues.CenterTargetBrightB=BItem->CalcCenterBright(*ImageList[2],dx,dy,ThresholdValues.TargetSDBL,ThresholdValues.TargetSDBH);
			}
		}
	}
}

bool	FlatInspectionThresholdSend::Save(QIODevice *f)
{
	if(f->write((const char *)&ThresholdValues,sizeof(ThresholdValues))!=sizeof(ThresholdValues))
		return false;

	return true;
}
bool	FlatInspectionThresholdSend::Load(QIODevice *f)
{
	if(f->read((char *)&ThresholdValues,sizeof(ThresholdValues))!=sizeof(ThresholdValues))
		return false;

	return true;
}

FlatInspectionReqTryThreshold::FlatInspectionReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	FlatInspectionItemID=-1;
}
bool	FlatInspectionReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,FlatInspectionItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	FlatInspectionReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,FlatInspectionItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

FlatInspectionSendTryThreshold::FlatInspectionSendTryThreshold(void)
{
	Result					=new FlatInspectionResultInItemPI();	//ResultInItemPI();
	NGDot					=0;
	NGLength				=0;
	ResultMoveDx			=0;
	ResultMoveDy			=0;
	Error					=0;
	CurrentRotationPatternNo=0;
	DeviationResultR		=0;
	DeviationResultG		=0;
	DeviationResultB		=0;
}

FlatInspectionSendTryThreshold::FlatInspectionSendTryThreshold(const FlatInspectionSendTryThreshold &src)
{
	Result					=new FlatInspectionResultInItemPI();	//ResultInItemPI();
	NGDot					=src.NGDot					;
	NGLength				=src.NGLength				;
	ResultMoveDx			=src.ResultMoveDx			;
	ResultMoveDy			=src.ResultMoveDy			;
	Error					=src.Error					;
	CurrentRotationPatternNo=src.CurrentRotationPatternNo;
	DeviationResultR		=src.DeviationResultR		;
	DeviationResultG		=src.DeviationResultG		;
	DeviationResultB		=src.DeviationResultB		;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
}

FlatInspectionSendTryThreshold::~FlatInspectionSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
	
FlatInspectionSendTryThreshold &FlatInspectionSendTryThreshold::operator=(const FlatInspectionSendTryThreshold &src)
{
	NGDot					=src.NGDot					;
	NGLength				=src.NGLength				;
	ResultMoveDx			=src.ResultMoveDx			;
	ResultMoveDy			=src.ResultMoveDy			;
	Error					=src.Error					;
	CurrentRotationPatternNo=src.CurrentRotationPatternNo;
	DeviationResultR		=src.DeviationResultR		;
	DeviationResultG		=src.DeviationResultG		;
	DeviationResultB		=src.DeviationResultB		;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
	return *this;
}

bool	FlatInspectionSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,NGDot	)==false)
		return false;
	if(::Save(f,NGLength)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(::Save(f,CurrentRotationPatternNo)==false)
		return false;

	if(::Save(f,DeviationResultR)==false)
		return false;
	if(::Save(f,DeviationResultG)==false)
		return false;
	if(::Save(f,DeviationResultB)==false)
		return false;
	return true;
}
bool	FlatInspectionSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,NGDot	)==false)
		return false;
	if(::Load(f,NGLength)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(::Load(f,CurrentRotationPatternNo)==false)
		return false;

	if(::Load(f,DeviationResultR)==false)
		return false;
	if(::Load(f,DeviationResultG)==false)
		return false;
	if(::Load(f,DeviationResultB)==false)
		return false;
	return true;
}

void	FlatInspectionSendTryThreshold::ConstructList(FlatInspectionReqTryThreshold *reqPacket,FlatInspectionBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	FlatInspectionInPage		*BP=(FlatInspectionInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		FlatInspectionItem		*BI=(FlatInspectionItem *)BP->SearchIDItem(reqPacket->FlatInspectionItemID);
		if(BI!=NULL){
			BYTE	**TmpMap=MakeMatrixBuff(BP->MaskMapXByte,BP->MaskMapYLen);
			MatrixBuffCopy	(TmpMap		   ,BP->MaskMapXByte,BP->MaskMapYLen
							,(const BYTE **)BP->MaskMap,BP->MaskMapXByte,BP->MaskMapYLen);
			int	SaveResultDx=BI->ResultDx;
			int	SaveResultDy=BI->ResultDy;
			double	SaveResultExpansion=BI->ResultExpansion;

			int	Dx=BP->TargetX1-BP->MasterX1;
			int	Dy=BP->TargetY1-BP->MasterY1;
			if(BI->FIT_Type==FlatInspectionItem::_FIType_MasterArea){
				int	cx,cy;
				BI->GetCenter(cx,cy);
				if((BP->MasterY2-BP->MasterY1)!=0){
					int	dy=(cy-BP->MasterY1)*(BP->TargetY2-BP->TargetY1)/(BP->MasterY2-BP->MasterY1)+BP->MasterY1-cy;
					BI->SearchMax(Dx,Dy+dy,BI->ResultDx,BI->ResultDy);
				}
				else{
					BI->ResultDx=0;
					BI->ResultDy=0;
				}
			}
			else
			if(BI->FIT_Type==FlatInspectionItem::_FIType_Window){
				int	cx,cy;
				BI->GetCenter(cx,cy);
				if((BP->MasterY2-BP->MasterY1)!=0){
					int	dy=(cy-BP->MasterY1)*(BP->TargetY2-BP->TargetY1)/(BP->MasterY2-BP->MasterY1)+BP->MasterY1-cy;
					BI->MakeWindow(Dx,Dy+dy);
				}
				else{
					BI->ResultDx=0;
					BI->ResultDy=0;
				}
			}
			else
			if(BI->FIT_Type==FlatInspectionItem::_FIType_SpecialShape){
				int	cx,cy;
				BI->GetCenter(cx,cy);
				if((BP->MasterY2-BP->MasterY1)!=0){
					int	dy=(cy-BP->MasterY1)*(BP->TargetY2-BP->TargetY1)/(BP->MasterY2-BP->MasterY1)+BP->MasterY1-cy;
					BI->SearchByDot(Dx,Dy+dy,BI->ResultDx,BI->ResultDy,BI->ResultExpansion);
				}
				else{
					BI->ResultDx=0;
					BI->ResultDy=0;
				}
			}

			Calc(&reqPacket->Threshold,BI,Base);
			MatrixBuffCopy	(BP->MaskMap			,BP->MaskMapXByte,BP->MaskMapYLen
							,(const BYTE **)TmpMap	,BP->MaskMapXByte,BP->MaskMapYLen);

			BI->ResultDx=SaveResultDx;
			BI->ResultDy=SaveResultDy;
			BI->ResultExpansion=SaveResultExpansion;

			DeleteMatrixBuff(TmpMap,BP->MaskMapYLen);
		}
	}
}
void	FlatInspectionSendTryThreshold::Calc(FlatInspectionItem *Target,FlatInspectionItem *Src,FlatInspectionBase *Base)
{
	FlatInspectionInPage		*BP=(FlatInspectionInPage *)Base->GetPageData(Src->GetPage());
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());

	int	SaveMaxInspectMilisec	=Base->GetParamGlobal()->MaxInspectMilisec;

	Base->GetParamGlobal()->MaxInspectMilisec	=99999999;

	Target->SetParent(Src->GetParent());

	Target->SetLibID(Src->GetLibID());
	Target->SetMasterNo(Src->GetMasterNo());
	FlatInspectionThreshold			*WThr=Target->GetThresholdW();
	const	FlatInspectionThreshold	*RThr=Src	->GetThresholdR();

	ExecuteInitialAfterEditInfo DummyEInfo;
	DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
	Target->ExecuteInitialAfterEditPost(0,0,Result,DummyEInfo);

	Target->CenterBrightR	=Src->CenterBrightR;
	Target->CenterBrightG	=Src->CenterBrightG;
	Target->CenterBrightB	=Src->CenterBrightB;
	Target->CopyFrom(Src);

	BP->GetDataInPage()->ClearNGCounterWithMutex();

	Target->ExecuteStartByInspection	(0,0,Result);
	Target->ExecuteProcessing			(10000,0,Result);


	Result->SetAddedData(NULL,0);
	NGDot		=Result->GetResult2();
	NGLength	=Result->GetResultDouble();
	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();

	Base->GetParamGlobal()->MaxInspectMilisec	=SaveMaxInspectMilisec	;

}

