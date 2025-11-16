/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\XColorBlockInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ColorBlockFormResource.h"
#include "XColorBlockInspection.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XColorBlockLibrary.h"
#include "XPropertyColorBlockPacket.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "ColorChangeCreateBlockForm.h"
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XColorBlockAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "XCriticalFunc.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

ColorBlockHistogramListReq::ColorBlockHistogramListReq(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	ColorBlockHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
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
bool	ColorBlockHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
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


ColorBlockHistogramListSend::ColorBlockHistogramListSend(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMasterR,0,sizeof(ListMasterR));
	memset(ListTargetR,0,sizeof(ListTargetR));
	memset(ListMasterG,0,sizeof(ListMasterG));
	memset(ListTargetG,0,sizeof(ListTargetG));
	memset(ListMasterB,0,sizeof(ListMasterB));
	memset(ListTargetB,0,sizeof(ListTargetB));
}
void	ColorBlockHistogramListSend::ConstructList(ColorBlockHistogramListReq *reqPacket ,ColorBlockBase *Base)
{
	memset(ListMasterR,0,sizeof(ListMasterR));
	memset(ListMasterG,0,sizeof(ListMasterG));
	memset(ListMasterB,0,sizeof(ListMasterB));
	memset(ListTargetR,0,sizeof(ListTargetR));
	memset(ListTargetG,0,sizeof(ListTargetG));
	memset(ListTargetB,0,sizeof(ListTargetB));

	GlobalPage	=reqPacket->GlobalPage;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			ColorBlockItem	*Item=dynamic_cast<ColorBlockItem *>(item);
			ImageBuffer *TargetImageList[10];
			int	N=Item->GetTargetBuffList(TargetImageList);
			bool	BuiltList=false;
			const	ColorBlockThreshold	*RThr=Item->GetThresholdR(Ap->GetLayersBase());
			if(item->IsOriginParts()==true && RThr->PointMove.ModeCenterBrightFromParts==true){
				QString ErrorMessageOfFalse;
				PieceClass	*PClass=Base->GetEntryPoint()->SearchAndLoadPiece(item->GetPartsID(),ErrorMessageOfFalse);
				if(PClass!=NULL){
					QString DLLRoot ,DLLName;
					Base->GetAlgorithmRootName(DLLRoot ,DLLName);
					AlgorithmItemRoot	*citem=PClass->GetAlgorithmItem(DLLRoot,DLLName,0,item->GetPartsItemID());
					if(citem!=NULL){
						AlgorithmItemPI	*pcitem=dynamic_cast<AlgorithmItemPI *>(citem);
						if(pcitem!=NULL){
							ImageBuffer *MasterImageList[10];
							int	N=pcitem->GetMasterBuffList(MasterImageList);
							pcitem->GetArea().MakeBrightList(ListMasterR ,pcitem->GetDotPerLine(),pcitem->GetMaxLines(),*MasterImageList[0],0 ,0);
							pcitem->GetArea().MakeBrightList(ListMasterG ,pcitem->GetDotPerLine(),pcitem->GetMaxLines(),*MasterImageList[1],0 ,0);
							pcitem->GetArea().MakeBrightList(ListMasterB ,pcitem->GetDotPerLine(),pcitem->GetMaxLines(),*MasterImageList[2],0 ,0);
							BuiltList=true;
						}
					}
				}
				else{
					if(ErrorMessageOfFalse.isEmpty()==false){
						QMessageBox::critical(NULL,"Load masterdata Error",ErrorMessageOfFalse);
					}
				}
			}
			if(BuiltList==false){
				ImageBuffer *MasterImageList[10];
				int	N=Item->GetMasterBuffList(MasterImageList);
				item->GetArea().MakeBrightList(ListMasterR ,item->GetDotPerLine(),item->GetMaxLines(),*MasterImageList[0],0 ,0);
				item->GetArea().MakeBrightList(ListMasterG ,item->GetDotPerLine(),item->GetMaxLines(),*MasterImageList[1],0 ,0);
				item->GetArea().MakeBrightList(ListMasterB ,item->GetDotPerLine(),item->GetMaxLines(),*MasterImageList[2],0 ,0);
			}

			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				if(Rp!=NULL){
					ResultInItemPI		*rItem=Rp->SearchItem(item->GetID());
					if(rItem!=NULL){
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						item->GetArea().MakeBrightList(ListTargetR ,item->GetDotPerLine(),item->GetMaxLines(),*TargetImageList[0],sx ,sy);
						item->GetArea().MakeBrightList(ListTargetG ,item->GetDotPerLine(),item->GetMaxLines(),*TargetImageList[1],sx ,sy);
						item->GetArea().MakeBrightList(ListTargetB ,item->GetDotPerLine(),item->GetMaxLines(),*TargetImageList[2],sx ,sy);
					}
					else{
						item->GetArea().MakeBrightList(ListTargetR ,item->GetDotPerLine(),item->GetMaxLines(),*TargetImageList[0],0 ,0);
						item->GetArea().MakeBrightList(ListTargetG ,item->GetDotPerLine(),item->GetMaxLines(),*TargetImageList[1],0 ,0);
						item->GetArea().MakeBrightList(ListTargetB ,item->GetDotPerLine(),item->GetMaxLines(),*TargetImageList[2],0 ,0);
					}
				}
			}
		}
	}
}

bool	ColorBlockHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(f->write((const char *)ListMasterR,sizeof(ListMasterR))!=sizeof(ListMasterR))
		return false;
	if(f->write((const char *)ListTargetR,sizeof(ListTargetR))!=sizeof(ListTargetR))
		return false;
	if(f->write((const char *)ListMasterG,sizeof(ListMasterG))!=sizeof(ListMasterG))
		return false;
	if(f->write((const char *)ListTargetG,sizeof(ListTargetG))!=sizeof(ListTargetG))
		return false;
	if(f->write((const char *)ListMasterB,sizeof(ListMasterB))!=sizeof(ListMasterB))
		return false;
	if(f->write((const char *)ListTargetB,sizeof(ListTargetB))!=sizeof(ListTargetB))
		return false;
	return true;
}
bool	ColorBlockHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(f->read((char *)ListMasterR,sizeof(ListMasterR))!=sizeof(ListMasterR))
		return false;
	if(f->read((char *)ListTargetR,sizeof(ListTargetR))!=sizeof(ListTargetR))
		return false;
	if(f->read((char *)ListMasterG,sizeof(ListMasterG))!=sizeof(ListMasterG))
		return false;
	if(f->read((char *)ListTargetG,sizeof(ListTargetG))!=sizeof(ListTargetG))
		return false;
	if(f->read((char *)ListMasterB,sizeof(ListMasterB))!=sizeof(ListMasterB))
		return false;
	if(f->read((char *)ListTargetB,sizeof(ListTargetB))!=sizeof(ListTargetB))
		return false;
	return true;
}
ColorBlockThresholdReq::ColorBlockThresholdReq(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	ColorBlockThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
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
bool	ColorBlockThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
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

ColorBlockThresholdSend::ColorBlockThresholdSendClass::ColorBlockThresholdSendClass(void)
{
}
bool	ColorBlockThresholdSend::ColorBlockThresholdSendClass::Save(QIODevice *f)
{
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,CenterTargetBright)==false)
		return false;
	if(::Save(f,NBrightWidthL)==false)
		return false;
	if(::Save(f,NBrightWidthH)==false)
		return false;
	if(::Save(f,BBrightWidthL)==false)
		return false;
	if(::Save(f,BBrightWidthH)==false)
		return false;

	if(::Save(f,AbsNBrightWidthL)==false)
		return false;
	if(::Save(f,AbsNBrightWidthH)==false)
		return false;
	if(::Save(f,AbsBBrightWidthL)==false)
		return false;
	if(::Save(f,AbsBBrightWidthH)==false)
		return false;

	if(::Save(f,NMinNGCountL)==false)
		return false;
	if(::Save(f,NMinNGCountH)==false)
		return false;
	if(::Save(f,BMinNGCountL)==false)
		return false;
	if(::Save(f,BMinNGCountH)==false)
		return false;

	if(::Save(f,BOKLengthL)==false)
		return false;
	if(::Save(f,BOKLengthH)==false)
		return false;
	if(::Save(f,NOKLengthL)==false)
		return false;
	if(::Save(f,NOKLengthH)==false)
		return false;
	return true;
}
bool	ColorBlockThresholdSend::ColorBlockThresholdSendClass::Load(QIODevice *f)
{
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,CenterTargetBright)==false)
		return false;
	if(::Load(f,NBrightWidthL)==false)
		return false;
	if(::Load(f,NBrightWidthH)==false)
		return false;
	if(::Load(f,BBrightWidthL)==false)
		return false;
	if(::Load(f,BBrightWidthH)==false)
		return false;

	if(::Load(f,AbsNBrightWidthL)==false)
		return false;
	if(::Load(f,AbsNBrightWidthH)==false)
		return false;
	if(::Load(f,AbsBBrightWidthL)==false)
		return false;
	if(::Load(f,AbsBBrightWidthH)==false)
		return false;

	if(::Load(f,NMinNGCountL)==false)
		return false;
	if(::Load(f,NMinNGCountH)==false)
		return false;
	if(::Load(f,BMinNGCountL)==false)
		return false;
	if(::Load(f,BMinNGCountH)==false)
		return false;

	if(::Load(f,BOKLengthL)==false)
		return false;
	if(::Load(f,BOKLengthH)==false)
		return false;
	if(::Load(f,NOKLengthL)==false)
		return false;
	if(::Load(f,NOKLengthH)==false)
		return false;

	return true;
}
		
void	ColorBlockThresholdSend::ColorBlockThresholdSendClass::Transform(ColorBlockThreshold::ThresholdByLayer &Ins 
																		 ,int CenterBright 
																		 ,ColorBlockItem *BItem
																		 ,ImageBuffer &TargetBuff ,int dx,int dy)
{
	NBrightWidthL	=Ins.NBrightWidthL;
	NBrightWidthH	=Ins.NBrightWidthH;
	BBrightWidthL	=Ins.BBrightWidthL;
	BBrightWidthH	=Ins.BBrightWidthH;

	NMinNGCountL	=Ins.NMinNGCountL;
	NMinNGCountH	=Ins.NMinNGCountH;
	BMinNGCountL	=Ins.BMinNGCountL;
	BMinNGCountH	=Ins.BMinNGCountH;

	int	TmpNBrightWidthL=NBrightWidthL;
	int	TmpNBrightWidthH=NBrightWidthH;
	int	TmpBBrightWidthL=BBrightWidthL;
	int	TmpBBrightWidthH=BBrightWidthH;
	const	ColorBlockThreshold	*RThr=BItem->GetThresholdR();
	if(RThr->PointMove.ModeAbsoluteBright==true){
		AbsNBrightWidthL=TmpNBrightWidthL;
		AbsNBrightWidthH=TmpNBrightWidthH;
		AbsBBrightWidthL=TmpBBrightWidthL;
		AbsBBrightWidthH=TmpBBrightWidthH;
	}
	else{
		AbsNBrightWidthL=CenterBright-TmpNBrightWidthL;
		AbsNBrightWidthH=CenterBright+TmpNBrightWidthH;
		AbsBBrightWidthL=CenterBright-TmpBBrightWidthL;
		AbsBBrightWidthH=CenterBright+TmpBBrightWidthH;
	}
	BOKLengthL		=Ins.BOKLengthL;
	BOKLengthH		=Ins.BOKLengthH;
	NOKLengthL		=Ins.NOKLengthL;
	NOKLengthH		=Ins.NOKLengthH;
}

ColorBlockThresholdSend::ColorBlockThresholdSend(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}

void	ColorBlockThresholdSend::ConstructList(ColorBlockThresholdReq *reqPacket,ColorBlockBase *Base,ImageBuffer *TargetImageList[])
{
	GlobalPage	=reqPacket->GlobalPage;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			ColorBlockItem	*BItem=(ColorBlockItem *)item;
			const	ColorBlockThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			ImageBuffer *TargetImageList[10];
			int	N=BItem->GetTargetBuffList(TargetImageList);

			if(BItem->CenterBrightR==0 && BItem->CenterBrightG==0 && BItem->CenterBrightB==0){
				BItem->MakeInsideEdgeArea();
				ImageBuffer *MasterImageList[100];
				int	N=BItem->GetMasterBuffList(MasterImageList);
				BItem->CalcCenterBright(MasterImageList,0,0
							 ,BItem->CenterBrightR
							 ,BItem->CenterBrightG
							 ,BItem->CenterBrightB);
			}

			RRes.Transform(((ColorBlockThreshold *)RThr)->InsR
					,BItem->CenterBrightR
					,BItem
					,*TargetImageList[0],dx,dy);
			GRes.Transform(((ColorBlockThreshold *)RThr)->InsG
					,BItem->CenterBrightG
					,BItem
					,*TargetImageList[1],dx,dy);
			BRes.Transform(((ColorBlockThreshold *)RThr)->InsB
					,BItem->CenterBrightB
					,BItem
					,*TargetImageList[2],dx,dy);

			if(RThr->PointMove.ModeAdjustable==true){
				int	iAbsBBrightWidthRL=RRes.AbsBBrightWidthL;
				int	iAbsBBrightWidthRH=RRes.AbsBBrightWidthH;
				int	iAbsBBrightWidthGL=GRes.AbsBBrightWidthL;
				int	iAbsBBrightWidthGH=GRes.AbsBBrightWidthH;
				int	iAbsBBrightWidthBL=BRes.AbsBBrightWidthL;
				int	iAbsBBrightWidthBH=BRes.AbsBBrightWidthH;

				if(TargetImageList[0]->IsNull()==false){
					BItem->EnAverage(dx,dy
								,iAbsBBrightWidthRL,iAbsBBrightWidthRH
								,iAbsBBrightWidthGL,iAbsBBrightWidthGH
								,iAbsBBrightWidthBL,iAbsBBrightWidthBH
								,TargetImageList);
				}
				RRes.AbsBBrightWidthL	=iAbsBBrightWidthRL;
				RRes.AbsBBrightWidthH	=iAbsBBrightWidthRH;
				GRes.AbsBBrightWidthL	=iAbsBBrightWidthGL;
				GRes.AbsBBrightWidthH	=iAbsBBrightWidthGH;
				BRes.AbsBBrightWidthL	=iAbsBBrightWidthBL;
				BRes.AbsBBrightWidthH	=iAbsBBrightWidthBH;

				int	iAbsNBrightWidthRL=RRes.AbsNBrightWidthL;
				int	iAbsNBrightWidthRH=RRes.AbsNBrightWidthH;
				int	iAbsNBrightWidthGL=GRes.AbsNBrightWidthL;
				int	iAbsNBrightWidthGH=GRes.AbsNBrightWidthH;
				int	iAbsNBrightWidthBL=BRes.AbsNBrightWidthL;
				int	iAbsNBrightWidthBH=BRes.AbsNBrightWidthH;
				if(TargetImageList[0]->IsNull()==false){
					BItem->EnAverage(dx,dy
							,iAbsNBrightWidthRL,iAbsNBrightWidthRH
							,iAbsNBrightWidthGL,iAbsNBrightWidthGH
							,iAbsNBrightWidthBL,iAbsNBrightWidthBH
							,TargetImageList);
				}
				RRes.AbsNBrightWidthL	=iAbsNBrightWidthRL;
				RRes.AbsNBrightWidthH	=iAbsNBrightWidthRH;
				GRes.AbsNBrightWidthL	=iAbsNBrightWidthGL;
				GRes.AbsNBrightWidthH	=iAbsNBrightWidthGH;
				BRes.AbsNBrightWidthL	=iAbsNBrightWidthBL;
				BRes.AbsNBrightWidthH	=iAbsNBrightWidthBH;
			}
			RRes.CenterBright=BItem->CenterBrightR;
			GRes.CenterBright=BItem->CenterBrightG;
			BRes.CenterBright=BItem->CenterBrightB;
			BItem->CalcCenterBright(TargetImageList,dx ,dy	,BItem->CenterBrightTargetR
															,BItem->CenterBrightTargetG
															,BItem->CenterBrightTargetB);

			RRes.CenterTargetBright=BItem->CenterBrightTargetR;
			GRes.CenterTargetBright=BItem->CenterBrightTargetG;
			BRes.CenterTargetBright=BItem->CenterBrightTargetB;
		}
	}
}

bool	ColorBlockThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(RRes.Save(f)==false)
		return false;
	if(GRes.Save(f)==false)
		return false;
	if(BRes.Save(f)==false)
		return false;
	return true;
}
bool	ColorBlockThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(RRes.Load(f)==false)
		return false;
	if(GRes.Load(f)==false)
		return false;
	if(BRes.Load(f)==false)
		return false;
	return true;
}

ColorBlockReqTryThreshold::ColorBlockReqTryThreshold(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
}
bool	ColorBlockReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	ColorBlockReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

ColorBlockSendTryThreshold::ColorBlockSendTryThreshold(void)
{
	NGDotInNDark	=0;
	NGDotInNBright	=0;
	NGDotInBDark	=0;
	NGDotInBBright	=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
	Error			=0;
	Result	=new ResultInItemPI();
}
ColorBlockSendTryThreshold::~ColorBlockSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}


bool	ColorBlockSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotInNDark	)==false)
		return false;
	if(::Save(f,NGDotInNBright	)==false)
		return false;
	if(::Save(f,NGDotInBDark	)==false)
		return false;
	if(::Save(f,NGDotInBBright	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(Result->Save(f)==false)
		return false;
	return true;
}
bool	ColorBlockSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotInNDark	)==false)
		return false;
	if(::Load(f,NGDotInNBright	)==false)
		return false;
	if(::Load(f,NGDotInBDark	)==false)
		return false;
	if(::Load(f,NGDotInBBright	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(Result->Load(f)==false)
		return false;
	return true;
}

void	ColorBlockSendTryThreshold::ConstructList(ColorBlockReqTryThreshold *reqPacket,ColorBlockBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	ColorBlockInPage	*BP=(ColorBlockInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		ColorBlockItem		*BI=(ColorBlockItem *)BP->SearchIDItem(reqPacket->BlockItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			const	ColorBlockThreshold	*RThr=BI->GetThresholdR(BP->GetLayersBase());
			reqPacket->Threshold.CenterBrightR						=BI->CenterBrightR;
			reqPacket->Threshold.CenterBrightG						=BI->CenterBrightG;
			reqPacket->Threshold.CenterBrightB						=BI->CenterBrightB;
			reqPacket->Threshold.GetThresholdW()->OmitVectorIndex	=RThr->OmitVectorIndex;
			reqPacket->Threshold.AVector							=BI->AVector;
			reqPacket->Threshold.GetThresholdW()->PointMove			=RThr->PointMove;
			reqPacket->Threshold.GetThresholdW()->PointMove.ModeCalcBothBN=true;
			//reqPacket->Threshold.GetThresholdW()->GeneratedOrigin	=RThr->GeneratedOrigin;
			reqPacket->Threshold.GetThresholdW()->CommonMoveID		=RThr->CommonMoveID;
			reqPacket->Threshold.GetThresholdW()->CommonMoveDot		=RThr->CommonMoveDot;
			reqPacket->Threshold.GetThresholdW()->SelfSearch		=RThr->SelfSearch;
			reqPacket->Threshold.SetParent(BI->GetParent());
			reqPacket->Threshold.CopyArea(*BI);
			reqPacket->Threshold.ExecuteProcessing(0,0,Result);
		}
	}
	Result->SetAddedData(NULL,0);

	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();
}


//=====================================================================================
ColorBlockThreshold::ThresholdByLayer::ThresholdByLayer(void)
{
	NBrightWidthL	=0;
	NBrightWidthH	=0;
	NOKDotL			=0;
	NOKDotH			=0;
	BBrightWidthL	=0;
	BBrightWidthH	=0;
	BOKDotL			=0;
	BOKDotH			=0;

    AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    AdjustWhite		=20;    //?P?x?a?3?I?a?A??

	NMinNGCountL	=0;
	NMinNGCountH	=0;
	BMinNGCountL	=0;
	BMinNGCountH	=0;

	BOKLengthL		=0;
	BOKLengthH		=0;
	NOKLengthL		=0;
	NOKLengthH		=0;
}
ColorBlockThreshold::ThresholdByLayer	&ColorBlockThreshold::ThresholdByLayer::operator=(const ThresholdByLayer &src)
{
	NBrightWidthL	=src.NBrightWidthL;
	NBrightWidthH	=src.NBrightWidthH;
	NOKDotL			=src.NOKDotL;
	NOKDotH			=src.NOKDotH;
	BBrightWidthL	=src.BBrightWidthL;
	BBrightWidthH	=src.BBrightWidthH;
	BOKDotL			=src.BOKDotL;
	BOKDotH			=src.BOKDotH;

    AdjustBlack		=src.AdjustBlack;
    AdjustWhite		=src.AdjustWhite;

	NMinNGCountL	=src.NMinNGCountL;
	NMinNGCountH	=src.NMinNGCountH;
	BMinNGCountL	=src.BMinNGCountL;
	BMinNGCountH	=src.BMinNGCountH;

	BOKLengthL		=src.BOKLengthL;
	BOKLengthH		=src.BOKLengthH;
	NOKLengthL		=src.NOKLengthL;
	NOKLengthH		=src.NOKLengthH;

	return *this;
}
bool	ColorBlockThreshold::ThresholdByLayer::Save(QIODevice *file)
{
	if(::Save(file,NBrightWidthL)==false)
		return false;
	if(::Save(file,NBrightWidthH)==false)
		return false;
	if(::Save(file,NOKDotL)==false)
		return false;
	if(::Save(file,NOKDotH)==false)
		return false;
	if(::Save(file,BBrightWidthL)==false)
		return false;
	if(::Save(file,BBrightWidthH)==false)
		return false;
	if(::Save(file,BOKDotL)==false)
		return false;
	if(::Save(file,BOKDotH)==false)
		return false;
	if(::Save(file,AdjustBlack)==false)
		return false;
	if(::Save(file,AdjustWhite)==false)
		return false;

	if(::Save(file,NMinNGCountL)==false)
		return false;
	if(::Save(file,NMinNGCountH)==false)
		return false;
	if(::Save(file,BMinNGCountL)==false)
		return false;
	if(::Save(file,BMinNGCountH)==false)
		return false;

	if(::Save(file,BOKLengthL)==false)
		return false;
	if(::Save(file,BOKLengthH)==false)
		return false;
	if(::Save(file,NOKLengthL)==false)
		return false;
	if(::Save(file,NOKLengthH)==false)
		return false;
	return true;
}
bool	ColorBlockThreshold::ThresholdByLayer::Load(QIODevice *file,int Ver)
{
	if(::Load(file,NBrightWidthL)==false)
		return false;
	if(::Load(file,NBrightWidthH)==false)
		return false;
	if(::Load(file,NOKDotL)==false)
		return false;
	if(::Load(file,NOKDotH)==false)
		return false;
	if(::Load(file,BBrightWidthL)==false)
		return false;
	if(::Load(file,BBrightWidthH)==false)
		return false;
	if(::Load(file,BOKDotL)==false)
		return false;
	if(::Load(file,BOKDotH)==false)
		return false;
	if(::Load(file,AdjustBlack)==false)
		return false;
	if(::Load(file,AdjustWhite)==false)
		return false;

	if(Ver>=10002){
		if(::Load(file,NMinNGCountL)==false)
			return false;
		if(::Load(file,NMinNGCountH)==false)
			return false;
		if(::Load(file,BMinNGCountL)==false)
			return false;
		if(::Load(file,BMinNGCountH)==false)
			return false;
	}
	if(Ver>=10003){
		if(::Load(file,BOKLengthL)==false)
			return false;
		if(::Load(file,BOKLengthH)==false)
			return false;
		if(::Load(file,NOKLengthL)==false)
			return false;
		if(::Load(file,NOKLengthH)==false)
			return false;
	}
	return true;
}
void	ColorBlockThreshold::ThresholdByLayer::FromLibrary(ColorBlockLibrary::InspectionData *src)
{
	NBrightWidthL	=src->NBrightWidthL;
	NBrightWidthH	=src->NBrightWidthH;
	NOKDotL			=src->NOKDotL;
	NOKDotH			=src->NOKDotH;
	BBrightWidthL	=src->BBrightWidthL;
	BBrightWidthH	=src->BBrightWidthH;
	BOKDotL			=src->BOKDotL;
	BOKDotH			=src->BOKDotH;

	NMinNGCountL	=src->NMinNGCountL;
	NMinNGCountH	=src->NMinNGCountH;
	BMinNGCountL	=src->BMinNGCountL;
	BMinNGCountH	=src->BMinNGCountH;

	AdjustBlack		=src->AdjustBlack;
	AdjustWhite		=src->AdjustWhite;

	BOKLengthL		=src->BOKLengthL;
	BOKLengthH		=src->BOKLengthH;
	NOKLengthL		=src->NOKLengthL;
	NOKLengthH		=src->NOKLengthH;

}
void	ColorBlockThreshold::ThresholdByLayer::ToLibrary(ColorBlockLibrary::InspectionData *Dest)
{
	Dest->NBrightWidthL		=NBrightWidthL;
	Dest->NBrightWidthH		=NBrightWidthH;
	Dest->NOKDotL			=NOKDotL	;
	Dest->NOKDotH			=NOKDotH	;
	Dest->BBrightWidthL		=BBrightWidthL;
	Dest->BBrightWidthH		=BBrightWidthH;
	Dest->BOKDotL			=BOKDotL	;
	Dest->BOKDotH			=BOKDotH	;

	Dest->NMinNGCountL		=NMinNGCountL;
	Dest->NMinNGCountH		=NMinNGCountH;
	Dest->BMinNGCountL		=BMinNGCountL;
	Dest->BMinNGCountH		=BMinNGCountH;

	Dest->AdjustBlack		=AdjustBlack			;
	Dest->AdjustWhite		=AdjustWhite			;

	Dest->BOKLengthL		=BOKLengthL;
	Dest->BOKLengthH		=BOKLengthH;
	Dest->NOKLengthL		=NOKLengthL;
	Dest->NOKLengthH		=NOKLengthH;
}
bool	ColorBlockThreshold::ThresholdByLayer::operator==(const ColorBlockThreshold::ThresholdByLayer &src)	const 
{
	if(NBrightWidthL	!=src.NBrightWidthL	)	return false;	
	if(NBrightWidthH	!=src.NBrightWidthH	)	return false;
	if(NOKDotL			!=src.NOKDotL		)	return false;
	if(NOKDotH			!=src.NOKDotH		)	return false;
	if(BBrightWidthL	!=src.BBrightWidthL	)	return false;
	if(BBrightWidthH	!=src.BBrightWidthH	)	return false;
	if(BOKDotL			!=src.BOKDotL		)	return false;
	if(BOKDotH			!=src.BOKDotH		)	return false;
	
	if(AdjustBlack   	!=src.AdjustBlack	)	return false;
	if(AdjustWhite    	!=src.AdjustWhite	)	return false;

	if(NMinNGCountL		!=src.NMinNGCountL	)	return false;
	if(NMinNGCountH		!=src.NMinNGCountH	)	return false;
	if(BMinNGCountL		!=src.BMinNGCountL	)	return false;
	if(BMinNGCountH		!=src.BMinNGCountH	)	return false;
	
	if(BOKLengthL		!=src.BOKLengthL	)	return false;
	if(BOKLengthH		!=src.BOKLengthH	)	return false;
	if(NOKLengthL		!=src.NOKLengthL	)	return false;
	if(NOKLengthH		!=src.NOKLengthH	)	return false;
	return true;
}

ColorBlockThreshold::ColorBlockThreshold(ColorBlockItem *parent)
:AlgorithmThreshold(parent)
{
	PointMove.ModeEnabled				=true;
	PointMove.ModeAbsoluteBright		=true;
	PointMove.ModeCommonMovable			=false;
	PointMove.ModeNGCluster				=true;
	PointMove.ModeDiffer				=false;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeOnlyMatching			=false;
	PointMove.ModeWhiteMask				=false;
	PointMove.ModeBlackMask				=false;
	PointMove.ModeAdjustable			=false;
	PointMove.ModeCalcBothBN			=false;
	GeneratedOriginOld	=_FromUnknown;

	CommonMoveID	=-1;
    CommonMoveDot	=0;
    SelfSearch		=4;     //?c?E?T?o?h?b?g??

	OmitVectorIndex=0xFFFF;//?T?o?O?~?u?u	0xFFFF?I?A??a?A?O?~?E??E
}

void	ColorBlockThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ColorBlockThreshold *s=(const ColorBlockThreshold *)&src;
	InsR	=s->InsR;
	InsG	=s->InsG;
	InsB	=s->InsB;

	PointMove			=s->PointMove;
	GeneratedOriginOld	=s->GeneratedOriginOld;
		
	CommonMoveID		=s->CommonMoveID;
    CommonMoveDot		=s->CommonMoveDot;
    SelfSearch			=s->SelfSearch;

	OmitVectorIndex		=s->OmitVectorIndex;
}
bool	ColorBlockThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ColorBlockThreshold *s=(const ColorBlockThreshold *)&src;

	if(InsR	!=s->InsR)	return false;
	if(InsG	!=s->InsG)	return false;
	if(InsB	!=s->InsB)	return false;

	if(PointMove.ModeEnabled				!=s->PointMove.ModeEnabled			)	return false;	
	if(PointMove.ModeAdjustable				!=s->PointMove.ModeAdjustable		)	return false;	
	if(PointMove.ModeAbsoluteBright			!=s->PointMove.ModeAbsoluteBright	)	return false;	
	if(PointMove.ModeCommonMovable			!=s->PointMove.ModeCommonMovable	)	return false;
	if(PointMove.ModeNGCluster				!=s->PointMove.ModeNGCluster		)	return false;
	if(PointMove.ModeDiffer					!=s->PointMove.ModeDiffer			)	return false;	
	if(PointMove.ModeCenterBrightFromParts	!=s->PointMove.ModeCenterBrightFromParts)	return false;
	if(PointMove.ModeOnlyMatching			!=s->PointMove.ModeOnlyMatching		)	return false;
	if(PointMove.ModeWhiteMask				!=s->PointMove.ModeWhiteMask		)	return false;
	if(PointMove.ModeBlackMask				!=s->PointMove.ModeBlackMask		)	return false;
	if(PointMove.ModeCalcBothBN				!=s->PointMove.ModeCalcBothBN		)	return false;

	if(GeneratedOriginOld	!=s->GeneratedOriginOld	)	return false;
		
	if(CommonMoveID		!=s->CommonMoveID			)	return false;
    if(CommonMoveDot	!=s->CommonMoveDot			)	return false;
    if(SelfSearch		!=s->SelfSearch				)	return false;

	if(OmitVectorIndex	!=s->OmitVectorIndex		)	return false;
	return true;
}
bool	ColorBlockThreshold::Save(QIODevice *f)
{
	WORD	Ver=ColorBlockInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,OmitVectorIndex)==false)
		return false;
	if(InsR.Save(f)==false)
		return false;
	if(InsG.Save(f)==false)
		return false;
	if(InsB.Save(f)==false)
		return false;
	if(f->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(f->write((const char *)&GeneratedOriginOld,sizeof(GeneratedOriginOld))!=sizeof(GeneratedOriginOld))
		return false;
	if(::Save(f,CommonMoveID)==false)
		return false;
	if(::Save(f,CommonMoveDot)==false)
		return false;
	if(::Save(f,SelfSearch)==false)
		return false;
	return true;
}
 bool	ColorBlockThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(Ver>10000 && Ver!=65535){
		if(::Load(f,OmitVectorIndex)==false)
			return false;
	}
	else{
		OmitVectorIndex=Ver;
		Ver=10001;
	}
	if(InsR.Load(f,Ver)==false)
		return false;
	if(InsG.Load(f,Ver)==false)
		return false;
	if(InsB.Load(f,Ver)==false)
		return false;
	if(f->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(f->read((char *)&GeneratedOriginOld,sizeof(GeneratedOriginOld))!=sizeof(GeneratedOriginOld))
		return false;
	if(::Load(f,CommonMoveID)==false)
		return false;
	if(::Load(f,CommonMoveDot)==false)
		return false;
	if(::Load(f,SelfSearch)==false)
		return false;
	return true;
}
void	ColorBlockThreshold::FromLibrary(AlgorithmLibrary *src)
{
	ColorBlockLibrary	*LSrc=dynamic_cast<ColorBlockLibrary *>(src);
	if(LSrc==NULL)
		return;
	InsR.FromLibrary(&LSrc->InsR);
	InsG.FromLibrary(&LSrc->InsG);
	InsB.FromLibrary(&LSrc->InsB);

	PointMove.ModeEnabled				=LSrc->PointMove.ModeEnabled;
	PointMove.ModeAdjustable			=LSrc->PointMove.ModeAdjustable;
	PointMove.ModeAbsoluteBright		=LSrc->PointMove.ModeAbsoluteBright;
	PointMove.ModeCommonMovable			=LSrc->PointMove.ModeCommonMovable;
	PointMove.ModeNGCluster				=LSrc->PointMove.ModeNGCluster;
	PointMove.ModeDiffer				=LSrc->PointMove.ModeDiffer;
	PointMove.ModeCenterBrightFromParts	=LSrc->PointMove.ModeCenterBrightFromParts;
	PointMove.ModeOnlyMatching			=LSrc->PointMove.ModeOnlyMatching;
	PointMove.ModeWhiteMask				=LSrc->PointMove.ModeWhiteMask;
	PointMove.ModeBlackMask				=LSrc->PointMove.ModeBlackMask;
	GetParentItem()->SetOriginType(_OriginType_FromLibrary);

		//v->CommonMoveID;
	CommonMoveDot						=LSrc->CommonMoveDot;
	SelfSearch							=LSrc->SelfSearch;

}

void	ColorBlockThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	ColorBlockLibrary	*LDst=dynamic_cast<ColorBlockLibrary *>(Dest);
	if(LDst==NULL)
		return;
	InsR.ToLibrary(&LDst->InsR);
	InsG.ToLibrary(&LDst->InsG);
	InsB.ToLibrary(&LDst->InsB);

	LDst->PointMove.ModeEnabled				=PointMove.ModeEnabled	;
	LDst->PointMove.ModeAdjustable			=PointMove.ModeAdjustable	;
	LDst->PointMove.ModeAbsoluteBright		=PointMove.ModeAbsoluteBright;
	LDst->PointMove.ModeCommonMovable		=PointMove.ModeCommonMovable	;
	LDst->PointMove.ModeNGCluster			=PointMove.ModeNGCluster		;
	LDst->PointMove.ModeDiffer				=PointMove.ModeDiffer	;
	LDst->PointMove.ModeCenterBrightFromParts=PointMove.ModeCenterBrightFromParts;
	LDst->PointMove.ModeOnlyMatching		=PointMove.ModeOnlyMatching		;
	LDst->PointMove.ModeWhiteMask			=PointMove.ModeWhiteMask;
	LDst->PointMove.ModeBlackMask			=PointMove.ModeBlackMask;
	LDst->CommonMoveDot						=CommonMoveDot			;
	LDst->SelfSearch						=SelfSearch				;

}
//=====================================================================================
void	ColorBlockChangeShift::Reflect(ColorBlockBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			if(item->GetCurrentResult()!=NULL){
				item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
			}
		}
	}
}

bool	ColorBlockChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ColorBlockChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

//=======================================================================================

ColorBlockItem::ColorBlockItem(void)
{
	InitialConstructor();
}
ColorBlockItem::ColorBlockItem(FlexArea &area)
:AlgorithmItemPI(area)
{
	InitialConstructor();
}

void ColorBlockItem::InitialConstructor(void)
{
	CenterBrightR	=0;
	CenterBrightG	=0;
	CenterBrightB	=0;
	AVector=NULL;
}

ColorBlockItem::~ColorBlockItem(void)
{}
void    ColorBlockItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPI::MoveTo(dx,dy);

    FLineEdge	.MoveToNoClip(dx,dy);
    FLineInside	.MoveToNoClip(dx,dy);
}

AlgorithmItemPI	&ColorBlockItem::operator=(const AlgorithmItemRoot &src)
{
	const ColorBlockItem	*s=dynamic_cast<const ColorBlockItem *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}
ColorBlockItem &ColorBlockItem::operator=(ColorBlockItem &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(src);
	return *this;
}

void	ColorBlockItem::CopyThreshold(ColorBlockItem &src)
{
	CenterBrightR	=src.CenterBrightR;
	CenterBrightG	=src.CenterBrightG;
	CenterBrightB	=src.CenterBrightB;
	GetThresholdW()->CopyFrom(*((ColorBlockThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	ColorBlockItem::CopyThresholdOnly(ColorBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((ColorBlockThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

bool    ColorBlockItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;
	if(::Save(file,CenterBrightR)==false)
		return false;
	if(::Save(file,CenterBrightG)==false)
		return false;
	if(::Save(file,CenterBrightB)==false)
		return false;
	return true;
}
bool    ColorBlockItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;
	if(::Load(file,CenterBrightR)==false)
		return false;
	if(::Load(file,CenterBrightG)==false)
		return false;
	if(::Load(file,CenterBrightB)==false)
		return false;
	return true;
}

void	ColorBlockItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	ImageBuffer *MasterImageList[10];
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			ColorBlockInPage	*Pg=dynamic_cast<ColorBlockInPage *>(GetParentInPage());
			UndoElement<ColorBlockInPage>	*UPointer=new UndoElement<ColorBlockInPage>(Pg,&ColorBlockInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((ColorBlockItem *)Data));
			int	N=GetMasterBuffList(MasterImageList);
			if(IsOriginParts()==false || GetThresholdR()->PointMove.ModeCenterBrightFromParts==false)
				CalcCenterBright(MasterImageList ,0,0
							 ,CenterBrightR,CenterBrightG,CenterBrightB);
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((ColorBlockItem *)Data)->GetLibID()){
			ColorBlockInPage	*Pg=dynamic_cast<ColorBlockInPage *>(GetParentInPage());
			UndoElement<ColorBlockInPage>	*UPointer=new UndoElement<ColorBlockInPage>(Pg,&ColorBlockInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((ColorBlockItem *)Data));
			int	N=GetMasterBuffList(MasterImageList);
			if(IsOriginParts()==false || GetThresholdR()->PointMove.ModeCenterBrightFromParts==false)
				CalcCenterBright(MasterImageList ,0,0
							 ,CenterBrightR,CenterBrightG,CenterBrightB);
		}
	}
}

void	ColorBlockItem::CopyArea(ColorBlockItem &src)
{
	SetArea(src.GetArea());
    FLineEdge	=src.FLineEdge;
    FLineInside	=src.FLineInside;
}


int		ColorBlockItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}
void	ColorBlockItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	ColorBlockItem	*ASrc=dynamic_cast<ColorBlockItem *>(src);
	if(ASrc!=NULL){
		FLineEdge.SetRefereneFrom(&ASrc->FLineEdge);
		FLineEdge.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		FLineInside.SetRefereneFrom(&ASrc->FLineInside);
		FLineInside.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

		int	OmitZoneDot=((ColorBlockBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineEdge	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineInside	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		CenterBrightR	=ASrc->CenterBrightR;
		CenterBrightG	=ASrc->CenterBrightG;
		CenterBrightB	=ASrc->CenterBrightB;

		CenterBrightTargetR	=ASrc->CenterBrightTargetR;
		CenterBrightTargetG	=ASrc->CenterBrightTargetG;
		CenterBrightTargetB	=ASrc->CenterBrightTargetB;
	}
}

ExeResult	ColorBlockItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	gap=((ColorBlockBase *)GetParentBase())->OmitZoneDot;
	if(GetLayersBase()->GetBootingLevel()>=1){
		gap=5;
	}
	GetArea().ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(IsOriginParts()==false){
		MakeInsideEdgeArea();
	}
	if(IsOriginParts()==false || GetThresholdR()->PointMove.ModeCenterBrightFromParts==false){
		ImageBuffer *MasterImageList[10];
		int	N=GetMasterBuffList(MasterImageList);

		CalcCenterBright(MasterImageList ,0,0
							 ,CenterBrightR,CenterBrightG,CenterBrightB);
	}
	return Ret;
}

void	ColorBlockItem::MakeInsideEdgeArea(void)
{
	FLineInside=GetArea();
	int	mx=FLineInside.GetMinX()-8;
	int	my=FLineInside.GetMinY()-8;
	FLineInside.MoveToNoClip(-mx,-my);
	int	XLen=FLineInside.GetMaxX()+8;
	int	YLen=FLineInside.GetMaxY()+8;
	int	XByte=(XLen+7)/8;
	BYTE	BmpImageBuff[10000];
	BYTE	TmpImageBuff[10000];
	BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen,BmpImageBuff,sizeof(BmpImageBuff));
	//BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(BmpImage,0,XByte,YLen);
	BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen,TmpImageBuff,sizeof(TmpImageBuff));
	//BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(TmpImage,0,XByte,YLen);
	FLineInside.MakeBitData(BmpImage,XLen,YLen);
	int	SelfSearch=GetThresholdR()->SelfSearch;
	GetLayersBase()->ThinAreaN(BmpImage
				,TmpImage
				,XByte ,YLen
				,SelfSearch);

	FLineInside.BuildFromRaster(BmpImage,XByte ,YLen,0,0);
	FLineInside	.MoveToNoClip(mx,my);
	FLineEdge	.Sub(GetArea(),FLineInside);
	if((BYTE	**)BmpImageBuff!=BmpImage){
		DeleteMatrixBuff(BmpImage,YLen);
	}
	if((BYTE	**)TmpImageBuff!=TmpImage){
		DeleteMatrixBuff(TmpImage,YLen);
	}
	int	gap=((ColorBlockBase *)GetParentBase())->OmitZoneDot;
	FLineInside	.ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
	FLineEdge	.ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	ColorBlockItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID)
		DbgNumer++;

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
	ImageBuffer *MasterBuff[10];
	ImageBuffer *TargetBuff[10];
	int	N=GetMasterBuffList(MasterBuff);
		  GetTargetBuffList(TargetBuff);

	int MError=0x0;

	WORD	RMinNGCountL;
	WORD	RMinNGCountH;
	WORD	GMinNGCountL;
	WORD	GMinNGCountH;
	WORD	BMinNGCountL;
	WORD	BMinNGCountH;

	const	ColorBlockThreshold	*RThr=GetThresholdR();
	int	BrightWidthRL=RThr->InsR.BBrightWidthL;
	int	BrightWidthRH=RThr->InsR.BBrightWidthH;
	int	BrightWidthGL=RThr->InsG.BBrightWidthL;
	int	BrightWidthGH=RThr->InsG.BBrightWidthH;
	int	BrightWidthBL=RThr->InsB.BBrightWidthL;
	int	BrightWidthBH=RThr->InsB.BBrightWidthH;

	RMinNGCountL	=RThr->InsR.BMinNGCountL;
	RMinNGCountH	=RThr->InsR.BMinNGCountH;
	GMinNGCountL	=RThr->InsG.BMinNGCountL;
	GMinNGCountH	=RThr->InsG.BMinNGCountH;
	BMinNGCountL	=RThr->InsB.BMinNGCountL;
	BMinNGCountH	=RThr->InsB.BMinNGCountH;

	if(RThr->PointMove.ModeAbsoluteBright==false){
		BrightWidthRL=CenterBrightR-BrightWidthRL;
		BrightWidthRH=CenterBrightR+BrightWidthRH;
		BrightWidthGL=CenterBrightG-BrightWidthGL;
		BrightWidthGH=CenterBrightG+BrightWidthGH;
		BrightWidthBL=CenterBrightB-BrightWidthBL;
		BrightWidthBH=CenterBrightB+BrightWidthBH;
	}
	WORD	OKLengthRL,OKLengthRH;
	WORD	OKLengthGL,OKLengthGH;
	WORD	OKLengthBL,OKLengthBH;

	OKLengthRL	=RThr->InsR.BOKLengthL;
	OKLengthRH	=RThr->InsR.BOKLengthH;
	OKLengthGL	=RThr->InsG.BOKLengthL;
	OKLengthGH	=RThr->InsG.BOKLengthH;
	OKLengthBL	=RThr->InsB.BOKLengthL;
	OKLengthBH	=RThr->InsB.BOKLengthH;

	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->Error		=0;
			}
		}
	}
	short	Error=1;
	if(TargetBuff[0]->IsNull()==false){
	    if(SubBlock.GetFirst()!=NULL){
			if(ExecuteProcessingInner(ThreadNo,Res 
								  ,mx ,my
								  ,BrightWidthRL ,BrightWidthRH ,RThr->InsR.BOKDotL ,RThr->InsR.BOKDotH ,OKLengthRL,OKLengthRH
								  ,BrightWidthGL ,BrightWidthGH ,RThr->InsG.BOKDotL ,RThr->InsG.BOKDotH ,OKLengthGL,OKLengthGH
								  ,BrightWidthBL ,BrightWidthBH ,RThr->InsB.BOKDotL ,RThr->InsB.BOKDotH ,OKLengthBL,OKLengthBH
								  ,CenterBrightR ,CenterBrightG ,CenterBrightB
								  ,MasterBuff ,TargetBuff
								  ,RMinNGCountL,RMinNGCountH
								  ,GMinNGCountL,GMinNGCountH
								  ,BMinNGCountL,BMinNGCountH
								  ,_ThresholdBroad)==false){
				Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(2 | MError | (Res->GetError()&0xF0));	//?L?a?A?m?f?-???€

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInBDark		=Res->GetResult1();
								Q->NGDotInBBright	=Res->GetResult2();
								Q->Error			=Res->GetError();
							}
						}
					}
					GetLayersBase()->SetResultFromAlgorithm(1);
					FinishCalc();
					return _ER_true;
				}
			}
		}
		else{
			if(ExecuteProcessingInnerWithoutSubtract(ThreadNo,Res 
								  ,mx ,my
								  ,BrightWidthRL ,BrightWidthRH ,RThr->InsR.BOKDotL ,RThr->InsR.BOKDotH ,OKLengthRL,OKLengthRH
								  ,BrightWidthGL ,BrightWidthGH ,RThr->InsG.BOKDotL ,RThr->InsG.BOKDotH ,OKLengthGL,OKLengthGH
								  ,BrightWidthBL ,BrightWidthBH ,RThr->InsB.BOKDotL ,RThr->InsB.BOKDotH ,OKLengthBL,OKLengthBH
								  ,MasterBuff ,TargetBuff
								  ,RMinNGCountL,RMinNGCountH
								  ,GMinNGCountL,GMinNGCountH
								  ,BMinNGCountL,BMinNGCountH
								  ,_ThresholdBroad)==false){
				Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(2 | MError | (Res->GetError()&0xF0));	//?L?a?A?m?f?-???€

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInBDark		=Res->GetResult1();
								Q->NGDotInBBright	=Res->GetResult2();
								Q->Error			=Res->GetError();
							}
						}
					}
					GetLayersBase()->SetResultFromAlgorithm(1);
					FinishCalc();
					return _ER_true;
				}
			}
		}
	}
	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->NGDotInBDark		=Res->GetResult1();
				Q->NGDotInBBright	=Res->GetResult2();
				Q->Error			=Error;
			}
		}
	}

	BrightWidthRL=RThr->InsR.NBrightWidthL;
	BrightWidthRH=RThr->InsR.NBrightWidthH;
	BrightWidthGL=RThr->InsG.NBrightWidthL;
	BrightWidthGH=RThr->InsG.NBrightWidthH;
	BrightWidthBL=RThr->InsB.NBrightWidthL;
	BrightWidthBH=RThr->InsB.NBrightWidthH;

	RMinNGCountL	=RThr->InsR.NMinNGCountL;
	RMinNGCountH	=RThr->InsR.NMinNGCountH;
	GMinNGCountL	=RThr->InsG.NMinNGCountL;
	GMinNGCountH	=RThr->InsG.NMinNGCountH;
	BMinNGCountL	=RThr->InsB.NMinNGCountL;
	BMinNGCountH	=RThr->InsB.NMinNGCountH;

	if(RThr->PointMove.ModeAbsoluteBright==false){
		BrightWidthRL=CenterBrightR-BrightWidthRL;
		BrightWidthRH=CenterBrightR+BrightWidthRH;
		BrightWidthGL=CenterBrightG-BrightWidthGL;
		BrightWidthGH=CenterBrightG+BrightWidthGH;
		BrightWidthBL=CenterBrightB-BrightWidthBL;
		BrightWidthBH=CenterBrightB+BrightWidthBH;
	}
	OKLengthRL	=RThr->InsR.NOKLengthL;
	OKLengthRH	=RThr->InsR.NOKLengthH;
	OKLengthGL	=RThr->InsG.NOKLengthL;
	OKLengthGH	=RThr->InsG.NOKLengthH;
	OKLengthBL	=RThr->InsB.NOKLengthL;
	OKLengthBH	=RThr->InsB.NOKLengthH;

	if(TargetBuff[0]->IsNull()==false){
	    if(SubBlock.GetFirst()!=NULL){
			if(ExecuteProcessingInner(ThreadNo,Res
								  ,mx ,my
								  ,BrightWidthRL ,BrightWidthRH ,RThr->InsR.NOKDotL ,RThr->InsR.NOKDotH ,OKLengthRL,OKLengthRH
								  ,BrightWidthGL ,BrightWidthGH ,RThr->InsG.NOKDotL ,RThr->InsG.NOKDotH ,OKLengthGL,OKLengthGH
								  ,BrightWidthBL ,BrightWidthBH ,RThr->InsB.NOKDotL ,RThr->InsB.NOKDotH ,OKLengthBL,OKLengthBH
								  ,CenterBrightR ,CenterBrightG ,CenterBrightB
								  ,MasterBuff ,TargetBuff
								  ,RMinNGCountL,RMinNGCountH
								  ,GMinNGCountL,GMinNGCountH
								  ,BMinNGCountL,BMinNGCountH
								  ,_ThresholdNarrow)==false){
				Error = 0x03 | (Res->GetError()&0xF0);	//??E?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(3 | MError | (Res->GetError()&0xF0));	//??E?a?A?m?f?-???€

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInNDark		=Res->GetResult1();
								Q->NGDotInNBright	=Res->GetResult2();
								Q->Error			=Res->GetError();
							}
						}
					}
					FinishCalc();
					return _ER_true;
				}
			}
		}
		else{
			if(ExecuteProcessingInnerWithoutSubtract(ThreadNo,Res 
								  ,mx ,my
								  ,BrightWidthRL ,BrightWidthRH ,RThr->InsR.NOKDotL ,RThr->InsR.NOKDotH ,OKLengthRL,OKLengthRH
								  ,BrightWidthGL ,BrightWidthGH ,RThr->InsG.NOKDotL ,RThr->InsG.NOKDotH ,OKLengthGL,OKLengthGH
								  ,BrightWidthBL ,BrightWidthBH ,RThr->InsB.NOKDotL ,RThr->InsB.NOKDotH ,OKLengthBL,OKLengthBH
								  ,MasterBuff ,TargetBuff
								  ,RMinNGCountL,RMinNGCountH
								  ,GMinNGCountL,GMinNGCountH
								  ,BMinNGCountL,BMinNGCountH
								  ,_ThresholdNarrow)==false){
				Error = 0x03 | (Res->GetError()&0xF0);	//??E?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(3 | MError | (Res->GetError()&0xF0));	//??E?a?A?m?f?-???€

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInNDark		=Res->GetResult1();
								Q->NGDotInNBright	=Res->GetResult2();
								Q->Error			=Res->GetError();
							}
						}
					}
					FinishCalc();
					return _ER_true;
				}
			}
		}
	}
	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			ColorBlockSendTryThreshold	*Q=dynamic_cast<ColorBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->NGDotInNDark		=Res->GetResult1();
				Q->NGDotInNBright	=Res->GetResult2();
				Q->Error			=Error;
			}
		}
	}
	Res->SetError(Error);
	FinishCalc();
	return _ER_true;
}

void	ColorBlockItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ColorBlockDrawAttr	*BAttr=dynamic_cast<ColorBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		ColorBlockDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
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
		if(BAttr->DType==CmdColorBlockDrawModePacket::_Area)
			AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdColorBlockDrawModePacket::_Edge)
			AlgorithmItemPI::DrawArea(FLineEdge,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdColorBlockDrawModePacket::_Inside)
			AlgorithmItemPI::DrawArea(FLineInside,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		//AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	ColorBlockItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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
						,QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())+QString(/**/",")+QString::number((int)Res->GetTotalShiftedY())+QString(/**/")")
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
ColorBlockInPage::ColorBlockInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent)
{
	PickupBmp=NULL;
	PickupBmpYLen=0;
	int	ThreadNumb;
	#pragma omp parallel                             
	{             
		ThreadNumb=omp_get_num_threads();
	}
	SWayListPerCPU=new SearchWayList[ThreadNumb];
}
ColorBlockInPage::~ColorBlockInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
	delete	[]SWayListPerCPU;
	SWayListPerCPU=NULL;
}

bool	ColorBlockInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	if(CommonMoveIDList.Save(f)==false)
		return false;
	return true;
}
bool	ColorBlockInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	if(CommonMoveIDList.Load(f)==false)
		return false;
	return true;
}

void	ColorBlockInPage::CreatePickupBmpBuff(void)
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

bool	ColorBlockInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfColorBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfColorBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}

void	ColorBlockInPage::PickupTest(ColorBlockLibrary &LibData)
{
	CreatePickupBmpBuff();

	bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibData.GetLibID());
	bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&LibData,NULL);
	if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);

			ImageBuffer *MasterImageList[10];
			GetMasterBuffList(MasterImageList);
			LibData.MakePickupTest(*MasterImageList[0]
								  ,*MasterImageList[1]
								  ,*MasterImageList[2]
								  ,Map.GetBitMap()
								,PickupBmp,NULL
								,GetPage()
								,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
								,((ColorBlockBase *)GetParentBase())->OmitZoneDot);
		}
	}
}
void	ColorBlockInPage::GenerateBlocks(ColorBlockLibrary *LibDim[],int LibDimNumb)
{
	UndoElement<ColorBlockInPage>	*UPointer=new UndoElement<ColorBlockInPage>(this,&ColorBlockInPage::UndoGenerateItems);
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

	CreatePickupBmpBuff();
	CommonMoveIDList.RemoveAll();

	int	DeletedItemCount=0;
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetEditLocked()==false){
			DeletedItemCount++;
		}
	}
	::Save(UPointer->GetWritePointer(),DeletedItemCount);

	//Data.RemoveAll();
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
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
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(GetParentBase()->GetLibraryContainer());
			if(GetParentBase()->GetLibraryContainer()->GetLibrary(L->GetLibID() ,*Lib)==true){
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
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		ColorBlockLibrary	*BLib=(ColorBlockLibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline;
		if(BLib->GenerationCategory==ColorBlockLibrary::_AutoSetting_OTHERMASK
		|| BLib->GenerationCategory==ColorBlockLibrary::_AutoSetting_SURROUND){
			BSpaceToOutline=0;
		}
		else{
			BSpaceToOutline=BLib->SpaceToOutline;
		}
		GetLayersBase()->FatAreaN(TempMap,TempMap2 ,XByte,GetMaxLines(),BSpaceToOutline);

		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2		,GetMaxLines());

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **OcupyMapSamePriority	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());

	IntList	AddedItemIDList;

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i])==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);
			const BYTE	**MaskBitmap=Map.GetBitMap();

			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

			bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibDim[i]->GetLibID());
			bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,LibDim[i],NULL);
			if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
				ImageBuffer *MasterImageList[10];
				GetMasterBuffList(MasterImageList);
				LibDim[i]->MakePickupTest(*MasterImageList[0]
										 ,*MasterImageList[1]
										 ,*MasterImageList[2]
										,MaskBitmap
										,CurrentMap,OcupyMap
										,GetPage()
										,XByte ,GetDotPerLine(),GetMaxLines()
										,((ColorBlockBase *)GetParentBase())->OmitZoneDot);
				if(LibDim[i]->GenerationMode.LeftPickup==false){
					NPListPack<AlgorithmItemPI>	TmpBlockData;
					int	SearchDot=LibDim[i]->SelfSearch;
					LibDim[i]->MakeBlock(
						 CurrentMap,LastOcupyMap
						 ,GetPage()
						,XByte ,GetDotPerLine(),GetMaxLines()
						,TmpBlockData
						,SearchDot);
					if(LibDim[i]->PointMove.ModeCommonMovable==true){
						int	CommonMoveID=CommonMoveIDList.GetCount()+1;
						CommonMoveIDList.Add(CommonMoveID);
						for(AlgorithmItemPI *a=TmpBlockData.GetFirst();a!=NULL;a=a->GetNext()){
							ColorBlockItem	*b=(ColorBlockItem *)a;
							b->GetThresholdW()->CommonMoveID=CommonMoveID;
						}
					}
					AlgorithmItemPI	*q;
					while((q=TmpBlockData.GetFirst())!=NULL){
						TmpBlockData.RemoveList(q);
						AppendItem(q);
						AddedItemIDList.Add(q->GetID());
					}
				}
			}
			MatrixBuffOr (OcupyMapSamePriority,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
			if((i+1)<LibDimNumb && LibDim[i]->Priority!=LibDim[i+1]->Priority){
				MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMapSamePriority ,XByte,GetMaxLines());
				MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());
			}
		}
	}
	AddedItemIDList.Save(UPointer->GetWritePointer());

	DeleteMatrixBuff(CurrentMap				,GetMaxLines());
	DeleteMatrixBuff(OcupyMap				,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
	DeleteMatrixBuff(OcupyMapSamePriority	,GetMaxLines());
}
void	ColorBlockInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedColorBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedColorBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		ColorBlockItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ColorBlockItem	*B=(ColorBlockItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
	}	
	CmdClearTestColorBlockPacket	*CmdClearTestColorBlockPacketVar=dynamic_cast<CmdClearTestColorBlockPacket *>(packet);
	if(CmdClearTestColorBlockPacketVar!=NULL){
		if(PickupBmp!=NULL)
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
	}
	CmdColorBlockInfoListPacket	*CmdColorBlockInfoListPacketVar=dynamic_cast<CmdColorBlockInfoListPacket *>(packet);
	if(CmdColorBlockInfoListPacketVar!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ColorBlockInfoList	*a;
			for(a=CmdColorBlockInfoListPacketVar->ColorBlockInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					a->ColorBlockCount++;
					break;
				}
			}
			if(a==NULL){
				a=new ColorBlockInfoList();
				a->LibID=L->GetLibID();
				a->ColorBlockCount	=1;
				CmdColorBlockInfoListPacketVar->ColorBlockInfos->AppendList(a);
			}
		}
	}
	CmdGetColorBlockFromList	*CmdGetColorBlockFromListVar=dynamic_cast<CmdGetColorBlockFromList *>(packet);
	if(CmdGetColorBlockFromListVar!=NULL){
		ColorBlockItem *Item=(ColorBlockItem *)SearchIDItem(CmdGetColorBlockFromListVar->CurrentItem.GetValue());
		CmdGetColorBlockFromListVar->ColorBlockInfoOnMouse=Item;
	}
	CmdCreateColorBlockItem	*CmdCreateColorBlockItemVar=dynamic_cast<CmdCreateColorBlockItem *>(packet);
	if(CmdCreateColorBlockItemVar!=NULL){
		CmdCreateColorBlockItemVar->ColorBlock=CreateItem(0);
	}
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				ColorBlockItem	*B=(ColorBlockItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		ColorBlockItem *Item=(ColorBlockItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);
			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
		}
		return;
	}
	CmdFindColorBlockItem	*CmdFindColorBlockItemVar=dynamic_cast<CmdFindColorBlockItem *>(packet);
	if(CmdFindColorBlockItemVar!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->IsInclude(CmdFindColorBlockItemVar->LocalX,CmdFindColorBlockItemVar->LocalY)==true){
				CmdFindColorBlockItemVar->ColorBlock=dynamic_cast<ColorBlockItem *>(L);
				break;
			}
		}
		return;
	}
}
void	ColorBlockInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ColorBlockDrawAttr	*BAttr=dynamic_cast<ColorBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==CmdColorBlockDrawModePacket::_LibTest){
			if(PickupBmp!=NULL){
				ColorBlockBase	*BBase=dynamic_cast<ColorBlockBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==CmdColorBlockDrawModePacket::_CreatedBlock){
			AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	}
}
void	ColorBlockInPage::UndoAppendManualItem(QIODevice *f)
{
	int	ItemID;
	::Load(f,ItemID);
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}
void	ColorBlockInPage::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		ColorBlockItem	*B=new ColorBlockItem();
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
void	ColorBlockInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		ColorBlockItem	*BI=(ColorBlockItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
//===========================================================================================
ColorBlockBase::ColorBlockBase(LayersBase *Base)
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

	SetParam(&ColorPickup		,/**/"Color" ,/**/"ColorPickup"		,LangSolver.GetString(XColorBlockInspection_LS,LID_55)/*"Color for Image to Pickup-Test "*/);
	SetParam(&ColorBlockNormal	,/**/"Color" ,/**/"ColorBlockNormal"	,LangSolver.GetString(XColorBlockInspection_LS,LID_57)/*"Color for Block"*/);
	SetParam(&ColorBlockSelected,/**/"Color" ,/**/"ColorBlockSelected"	,LangSolver.GetString(XColorBlockInspection_LS,LID_59)/*"Color for Selected Block"*/);
	SetParam(&ColorBlockActive	,/**/"Color" ,/**/"ColorBlockActive"	,LangSolver.GetString(XColorBlockInspection_LS,LID_61)/*"Color for Active Block"*/);

	SetParam(&BlockColor0		,/**/"BlockColor" ,/**/"BlockColor0"	,LangSolver.GetString(XColorBlockInspection_LS,LID_63)/*"Block Color 0"*/);
	SetParam(&BlockColor1		,/**/"BlockColor" ,/**/"BlockColor1"	,LangSolver.GetString(XColorBlockInspection_LS,LID_65)/*"Block Color 1"*/);
	SetParam(&BlockColor2		,/**/"BlockColor" ,/**/"BlockColor2"	,LangSolver.GetString(XColorBlockInspection_LS,LID_67)/*"Block Color 2"*/);
	SetParam(&BlockColor3		,/**/"BlockColor" ,/**/"BlockColor3"	,LangSolver.GetString(XColorBlockInspection_LS,LID_69)/*"Block Color 3"*/);
	SetParam(&BlockColor4		,/**/"BlockColor" ,/**/"BlockColor4"	,LangSolver.GetString(XColorBlockInspection_LS,LID_71)/*"Block Color 4"*/);
	SetParam(&BlockColor5		,/**/"BlockColor" ,/**/"BlockColor5"	,LangSolver.GetString(XColorBlockInspection_LS,LID_73)/*"Block Color 5"*/);
	SetParam(&BlockColor6		,/**/"BlockColor" ,/**/"BlockColor6"	,LangSolver.GetString(XColorBlockInspection_LS,LID_75)/*"Block Color 6"*/);
	SetParam(&BlockColor7		,/**/"BlockColor" ,/**/"BlockColor7"	,LangSolver.GetString(XColorBlockInspection_LS,LID_77)/*"Block Color 7"*/);

	SetParam(&OmitZoneDot		,/**/"Setting"		,/**/"OmitZoneDot"	,LangSolver.GetString(XColorBlockInspection_LS,LID_79)/*"Omit zone dot in block generation"*/);
}

AlgorithmDrawAttr	*ColorBlockBase::CreateDrawAttr(void)
{
	return new ColorBlockDrawAttr();
}

void	ColorBlockBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetColorBlockLibraryListPacket	*AListPacket=dynamic_cast<CmdGetColorBlockLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetColorBlockLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetColorBlockLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertColorBlockLibraryPacket	*BInsLib=dynamic_cast<CmdInsertColorBlockLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(ColorBlockInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateColorBlockLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateColorBlockLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(ColorBlockInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadColorBlockLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadColorBlockLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempColorBlockLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempColorBlockLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearColorBlockLibraryPacket	*CmdClearColorBlockLibraryPacketVar=dynamic_cast<CmdClearColorBlockLibraryPacket *>(packet);
	if(CmdClearColorBlockLibraryPacketVar!=NULL){
		CmdClearColorBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteColorBlockLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteColorBlockLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestColorBlockPacket	*BPickLib=dynamic_cast<CmdPickupTestColorBlockPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		ColorBlockInPage	*Bp=dynamic_cast<ColorBlockInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(*(ColorBlockLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateColorBlockPacket	*BGenerated=dynamic_cast<CmdGenerateColorBlockPacket *>(packet);
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
				ColorBlockLibrary	*L1=dynamic_cast<ColorBlockLibrary *>(LibDim[i  ]->GetLibrary());
				ColorBlockLibrary	*L2=dynamic_cast<ColorBlockLibrary *>(LibDim[i+1]->GetLibrary());
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
		ColorBlockLibrary	**LDim=new ColorBlockLibrary*[N];
		for(int i=0;i<N;i++){
			LDim[i]=dynamic_cast<ColorBlockLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			ColorBlockInPage	*Bp=dynamic_cast<ColorBlockInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateBlocks(LDim,N);		
			}
		}
		delete	[]LDim;
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempColorBlockItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempColorBlockItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new ColorBlockItem();
		return;
	}
	CmdCreateByteArrayFromColorBlockItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromColorBlockItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdAddByteColorBlockItemPacket	*AddBItem=dynamic_cast<CmdAddByteColorBlockItemPacket *>(packet);
	if(AddBItem!=NULL){
		ColorBlockInPage		*PData=dynamic_cast<ColorBlockInPage *>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			ColorBlockItem	*Item=new ColorBlockItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);

			UndoElement<ColorBlockInPage>	*UPointer=new UndoElement<ColorBlockInPage>(PData,&ColorBlockInPage::UndoAppendManualItem);
			::Save(UPointer->GetWritePointer(),Item->GetID());
			Item->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		}
	}
	CmdLoadColorBlockItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadColorBlockItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedColorBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedColorBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
	}
	CmdClearTestColorBlockPacket	*CmdClearTestColorBlockPacketVar=dynamic_cast<CmdClearTestColorBlockPacket *>(packet);
	if(CmdClearTestColorBlockPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestColorBlockPacketVar);
		}
	}
	CmdColorBlockInfoListPacket	*CmdColorBlockInfoListPacketVar=dynamic_cast<CmdColorBlockInfoListPacket *>(packet);
	if(CmdColorBlockInfoListPacketVar!=NULL){
		GetPageData(CmdColorBlockInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetColorBlockFromList	*CmdGetColorBlockFromListVar=dynamic_cast<CmdGetColorBlockFromList *>(packet);
	if(CmdGetColorBlockFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetColorBlockFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateColorBlockItem	*CmdCreateColorBlockItemVar=dynamic_cast<CmdCreateColorBlockItem *>(packet);
	if(CmdCreateColorBlockItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

bool	ColorBlockBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ColorBlockReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*ColorBlockBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==BlockHistogramListSendCommand){
		ColorBlockHistogramListSend	*pSend=new ColorBlockHistogramListSend();
		if(reqData!=NULL){
			ColorBlockHistogramListReq	*req=(ColorBlockHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==BlockHistogramListReqCommand){
		return new ColorBlockHistogramListReq();
	}
	else if(Command==BlockReqThresholdReqCommand){
		return new ColorBlockThresholdReq();
	}
	else if(Command==BlockReqThresholdSendCommand){
		ColorBlockThresholdSend	*pSend=new ColorBlockThresholdSend();
		if(reqData!=NULL){
			ColorBlockThresholdReq	*req=(ColorBlockThresholdReq *)reqData;
			int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(req->GlobalPage);
			ImageBuffer *ImageList[10];
			GetPageData(LocalPage)->GetTargetBuffList(ImageList);
			pSend->ConstructList(req,this,ImageList);
		}
		return pSend;
	}
	else if(Command==BlockReqTryThresholdCommand){
		return new ColorBlockReqTryThreshold();
	}
	else if(Command==BlockSendTryThresholdCommand){
		ColorBlockSendTryThreshold	*pSend=new ColorBlockSendTryThreshold();
		if(reqData!=NULL){
			ColorBlockReqTryThreshold	*req=(ColorBlockReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ColorBlockReqChangeShiftCommand){
		return new ColorBlockChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	ColorBlockBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		ColorBlockHistogramListSend	*p=(ColorBlockHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==BlockHistogramListReqCommand){
		ColorBlockHistogramListReq	*p=(ColorBlockHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqThresholdReqCommand){
		ColorBlockThresholdReq	*p=(ColorBlockThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqThresholdSendCommand){
		ColorBlockThresholdSend	*p=(ColorBlockThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqTryThresholdCommand){
		ColorBlockReqTryThreshold	*p=(ColorBlockReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==BlockSendTryThresholdCommand){
		ColorBlockSendTryThreshold	*p=(ColorBlockSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==ColorBlockReqChangeShiftCommand){
		ColorBlockChangeShift	*p=(ColorBlockChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	ColorBlockBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		ColorBlockHistogramListSend	*p=(ColorBlockHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==BlockHistogramListReqCommand){
		ColorBlockHistogramListReq	*p=(ColorBlockHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqThresholdReqCommand){
		ColorBlockThresholdReq	*p=(ColorBlockThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqThresholdSendCommand){
		ColorBlockThresholdSend	*p=(ColorBlockThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqTryThresholdCommand){
		ColorBlockReqTryThreshold	*p=(ColorBlockReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==BlockSendTryThresholdCommand){
		ColorBlockSendTryThreshold	*p=(ColorBlockSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==ColorBlockReqChangeShiftCommand){
		ColorBlockChangeShift	*p=(ColorBlockChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	ColorBlockBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		ColorBlockHistogramListSend	*p=(ColorBlockHistogramListSend *)data;
		return true;
	}
	else if(Command==BlockHistogramListReqCommand){
		ColorBlockHistogramListReq	*p=(ColorBlockHistogramListReq *)data;
		return true;
	}
	else if(Command==BlockReqThresholdReqCommand){
		ColorBlockThresholdReq	*p=(ColorBlockThresholdReq *)data;
		return true;
	}
	else if(Command==BlockReqThresholdSendCommand){
		ColorBlockThresholdSend	*p=(ColorBlockThresholdSend *)data;
		return true;
	}
	else if(Command==BlockReqTryThresholdCommand){
		ColorBlockReqTryThreshold	*p=(ColorBlockReqTryThreshold *)data;
		return true;
	}
	else if(Command==BlockSendTryThresholdCommand){
		ColorBlockSendTryThreshold	*p=(ColorBlockSendTryThreshold *)data;
		return true;
	}
	else if(Command==ColorBlockReqChangeShiftCommand){
		ColorBlockChangeShift	*p=(ColorBlockChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	ColorBlockBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	ColorChangeCreateBlockForm	Q(this);
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultBlock.Save(&Buff)==false)
			return false;
	}
	return ret;
}


//===========================================================================================

