/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "XTrueColorBlock.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XTrueColorBlockLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XPropertyTrueColorBlockPacket.h"
#include "TrueColorChangeCreateBlockForm.h"
#include "XMaskingFromGeneral.h"
#include "XTrueColorBlockAlgoPacket.h"
#include "XCriticalFunc.h"

//#include "ColorChangeCreateBlockForm.h"
//#include "XPropertyColorBlockPacket.h"
extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================

TrueColorBlockHistogramListReq::TrueColorBlockHistogramListReq(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	TrueColorBlockHistogramListReq::Save(QIODevice *f)
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
bool	TrueColorBlockHistogramListReq::Load(QIODevice *f)
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


TrueColorBlockHistogramListSend::TrueColorBlockHistogramListSend(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
void	TrueColorBlockHistogramListSend::ConstructList(TrueColorBlockHistogramListReq *reqPacket ,TrueColorBlockBase *Base)
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
			try{
				RGBStock Stocker;
				ImagePointerContainer Images;
				Ap->GetDataInPage()->GetTargetImages(Images);
				item->GetArea().CreateRGBStock(Images, Stocker);
				ColorSphere	*b=new ColorSphere();
				b->Create(Stocker);
				MasterColor.AddBase(b);
			}
			catch(...){}
			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				if(Rp!=NULL){
					ResultInItemPI		*rItem=Rp->GetItem(item->GetID());
					if(rItem!=NULL){
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						RGBStock Stocker;
						ImagePointerContainer Images;
						Ap->GetDataInPage()->GetTargetImages(Images);
						item->GetArea().CreateRGBStock(Images, Stocker ,sx,sy);
						ColorSphere	*b=new ColorSphere();
						b->Create(Stocker);
						TargetColor.AddBase(b);
					}
					else{
						RGBStock Stocker;
						ImagePointerContainer Images;
						Ap->GetDataInPage()->GetTargetImages(Images);
						item->GetArea().CreateRGBStock(Images, Stocker);
						ColorSphere	*b=new ColorSphere();
						b->Create(Stocker);
						TargetColor.AddBase(b);
					}
				}
			}
		}
	}
}

bool	TrueColorBlockHistogramListSend::Save(QIODevice *f)
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
	if(MasterColor.Save(f)==false)
		return false;
	if(TargetColor.Save(f)==false)
		return false;
	return true;
}
bool	TrueColorBlockHistogramListSend::Load(QIODevice *f)
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
	if(MasterColor.Load(f)==false)
		return false;
	if(TargetColor.Load(f)==false)
		return false;
	return true;
}

TrueColorBlockThresholdReq::TrueColorBlockThresholdReq(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	TrueColorBlockThresholdReq::Save(QIODevice *f)
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
bool	TrueColorBlockThresholdReq::Load(QIODevice *f)
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
TrueColorBlockThresholdSend::TrueColorBlockThresholdSend(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	Multiplier=1.0;
}

void	TrueColorBlockThresholdSend::ConstructList(TrueColorBlockThresholdReq *reqPacket,TrueColorBlockBase *Base)
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
			TrueColorBlockItem	*BItem=(TrueColorBlockItem *)item;
			CenterBright	=BItem->CenterBright;
			if(CenterBright==qRgb(0,0,0)){
				BItem->MakeInsideEdgeArea();
				ImageBuffer *MasterImageList[100];
				int	N=BItem->GetMasterBuffList(MasterImageList);
				BItem->CenterBright=BItem->CalcCenterBright(MasterImageList ,0,0);
				CenterBright	=BItem->CenterBright;
			}
			const TrueColorBlockThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			NInsColor	=*((ColorLogic *)&RThr->NInsColor);
			BInsColor	=*((ColorLogic *)&RThr->BInsColor);

			AbsNInsColor=NInsColor;
			AbsBInsColor=BInsColor;

			NMinNGCount	=RThr->NMinNGCount;
			BMinNGCount	=RThr->BMinNGCount;

			BOKLength	=RThr->BOKLength;
			NOKLength	=RThr->NOKLength;


			if(RThr->PointMove.ModeAdjustable==true){
				Multiplier=BItem->EnAverage(dx,dy ,AbsNInsColor);
				BItem->EnAverage(dx,dy ,AbsBInsColor);
			}
		}
	}
}

bool	TrueColorBlockThresholdSend::Save(QIODevice *f)
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
	if(::Save(f,CenterBright)==false)
		return false;
	if(NInsColor.Save(f)==false)
		return false;
	if(BInsColor.Save(f)==false)
		return false;
	if(AbsNInsColor.Save(f)==false)
		return false;
	if(AbsBInsColor.Save(f)==false)
		return false;
	if(::Save(f,Multiplier)==false)
		return false;

	if(::Save(f,NMinNGCount)==false)
		return false;
	if(::Save(f,BMinNGCount)==false)
		return false;

	if(::Save(f,BOKLength)==false)
		return false;
	if(::Save(f,NOKLength)==false)
		return false;
	return true;
}
bool	TrueColorBlockThresholdSend::Load(QIODevice *f)
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
	if(::Load(f,CenterBright)==false)
		return false;
	if(NInsColor.Load(f)==false)
		return false;
	if(BInsColor.Load(f)==false)
		return false;
	if(AbsNInsColor.Load(f)==false)
		return false;
	if(AbsBInsColor.Load(f)==false)
		return false;
	if(::Load(f,Multiplier)==false)
		return false;

	if(::Load(f,NMinNGCount)==false)
		return false;
	if(::Load(f,BMinNGCount)==false)
		return false;

	if(::Load(f,BOKLength)==false)
		return false;
	if(::Load(f,NOKLength)==false)
		return false;
	return true;
}

//=====================================================================================
TrueColorBlockThreshold::TrueColorBlockThreshold(TrueColorBlockItem *parent)
:AlgorithmThreshold(parent)
{
	NOKDot			=0;
	BOKDot			=0;
	PointMove.ModeEnabled				=true;
	PointMove.ModeCommonMovable			=false;
	PointMove.ModeNGCluster				=true;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeOnlyMatching			=false;
	PointMove.ModeAdjustable			=false;
	PointMove.ModeCalcBothBN			=false;
	PointMove.ModeInvertLogic			=false;
	GeneratedOriginOld	=_FromUnknown;

	CommonMoveID	=-1;
    CommonMoveDot	=0;

    AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    AdjustWhite		=20;    //?P?x?a?3?I?a?A??
    SelfSearch		=4;     //?c?E?T?o?h?b?g??
	OmitVectorIndex=0xFFFF;//?T?o?O?~?u?u	0xFFFF?I?A??a?A?O?~?E??E
	NMergin			=10;	//??E?a??a?e?I???e?P?x?E
	BMergin			=10;	//??E?a??a?e?I???e?P?x?E
	NMinNGCount		=0;
	BMinNGCount		=0;
	BOKLength		=0;
	NOKLength		=0;
}

void	TrueColorBlockThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const TrueColorBlockThreshold *s=(const TrueColorBlockThreshold *)&src;
	//NInsOKSamples	=((TrueColorBlockThreshold *)&src)->NInsOKSamples;
	//NInsNGSamples	=((TrueColorBlockThreshold *)&src)->NInsNGSamples;
	//BInsOKSamples	=((TrueColorBlockThreshold *)&src)->BInsOKSamples;
	//BInsNGSamples	=((TrueColorBlockThreshold *)&src)->BInsNGSamples;
	NOKDot			=s->NOKDot;
	NInsColor		=s->NInsColor;
	BOKDot			=s->BOKDot;
	BInsColor		=s->BInsColor;
	PointMove		=s->PointMove;
	GeneratedOriginOld	=s->GeneratedOriginOld;

	CommonMoveID	=s->CommonMoveID;
    CommonMoveDot	=s->CommonMoveDot;

    AdjustBlack		=s->AdjustBlack;
    AdjustWhite		=s->AdjustWhite;
    SelfSearch		=s->SelfSearch;
	OmitVectorIndex	=s->OmitVectorIndex;
	NMergin			=s->NMergin;
	BMergin			=s->BMergin;

	NMinNGCount		=s->NMinNGCount;
	BMinNGCount		=s->BMinNGCount;

	BOKLength		=s->BOKLength;
	NOKLength		=s->NOKLength;

	if(NInsColor.IsEnableTable()==true)
		NInsColor.CreateTable(NMergin);
	if(BInsColor.IsEnableTable()==true)
		BInsColor.CreateTable(BMergin);
}
bool	TrueColorBlockThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const TrueColorBlockThreshold *s=(const TrueColorBlockThreshold *)&src;
	if(NOKDot				!=s->NOKDot				)	return	false;
	if(NInsColor			!=s->NInsColor			)	return	false;
	if(BOKDot				!=s->BOKDot				)	return	false;
	if(BInsColor			!=s->BInsColor			)	return	false;
	if(PointMove.ModeEnabled				!=s->PointMove.ModeEnabled				)	return	false;
	if(PointMove.ModeAdjustable				!=s->PointMove.ModeAdjustable			)	return	false;
	if(PointMove.ModeCommonMovable			!=s->PointMove.ModeCommonMovable		)	return	false;
	if(PointMove.ModeNGCluster				!=s->PointMove.ModeNGCluster			)	return	false;
	if(PointMove.ModeCenterBrightFromParts	!=s->PointMove.ModeCenterBrightFromParts)	return	false;
	if(PointMove.ModeOnlyMatching			!=s->PointMove.ModeOnlyMatching			)	return	false;
	if(PointMove.ModeCalcBothBN				!=s->PointMove.ModeCalcBothBN			)	return	false;
	if(PointMove.ModeInvertLogic			!=s->PointMove.ModeInvertLogic			)	return	false;
	if(GeneratedOriginOld	!=s->GeneratedOriginOld	)	return	false;

	if(CommonMoveID			!=s->CommonMoveID		)	return	false;
    if(CommonMoveDot		!=s->CommonMoveDot		)	return	false;

    if(AdjustBlack			!=s->AdjustBlack		)	return	false;
    if(AdjustWhite			!=s->AdjustWhite		)	return	false;
    if(SelfSearch			!=s->SelfSearch			)	return	false;
	if(OmitVectorIndex		!=s->OmitVectorIndex	)	return	false;
	if(NMergin				!=s->NMergin			)	return	false;
	if(BMergin				!=s->BMergin			)	return	false;

	if(NMinNGCount			!=s->NMinNGCount		)	return	false;
	if(BMinNGCount			!=s->BMinNGCount		)	return	false;

	if(BOKLength			!=s->BOKLength			)	return	false;
	if(NOKLength			!=s->NOKLength			)	return	false;

	if(NInsColor			!=s->NInsColor			)	return	false;
	if(BInsColor			!=s->BInsColor			)	return	false;

	return true;
}
bool	TrueColorBlockThreshold::Save(QIODevice *file)
{
	WORD	Ver=TrueColorBlockVersion;

	if(NInsColor.Save(file)==false)
		return false;
	if(::Save(file,NOKDot)==false)
		return false;

	if(BInsColor.Save(file)==false)
		return false;
	if(::Save(file,BOKDot)==false)
		return false;

	if(file->write((const char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(file->write((const char *)&GeneratedOriginOld,sizeof(GeneratedOriginOld))!=sizeof(GeneratedOriginOld))
		return false;
	if(::Save(file,CommonMoveID)==false)
		return false;
	if(::Save(file,CommonMoveDot)==false)
		return false;
	if(::Save(file,AdjustBlack)==false)
		return false;
	if(::Save(file,AdjustWhite)==false)
		return false;
	if(::Save(file,Ver)==false)
		return false;
	if(::Save(file,SelfSearch)==false)
		return false;
	if(::Save(file,OmitVectorIndex)==false)
		return false;
	if(::Save(file,NMergin)==false)
		return false;
	if(::Save(file,BMergin)==false)
		return false;

	if(::Save(file,NMinNGCount)==false)
		return false;
	if(::Save(file,BMinNGCount)==false)
		return false;
	if(::Save(file,BOKLength)==false)
		return false;
	if(::Save(file,NOKLength)==false)
		return false;

	return true;
}
bool	TrueColorBlockThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(NInsColor.Load(file)==false)
		return false;
	if(::Load(file,NOKDot)==false)
		return false;

	if(BInsColor.Load(file)==false)
		return false;
	if(::Load(file,BOKDot)==false)
		return false;

	if(file->read((char *)&PointMove,sizeof(PointMove))!=sizeof(PointMove))
		return false;
	if(file->read((char *)&GeneratedOriginOld,sizeof(GeneratedOriginOld))!=sizeof(GeneratedOriginOld))
		return false;
	if(::Load(file,CommonMoveID)==false)
		return false;
	if(::Load(file,CommonMoveDot)==false)
		return false;
	if(::Load(file,AdjustBlack)==false)
		return false;
	if(::Load(file,AdjustWhite)==false)
		return false;
	if(::Load(file,Ver)==false)
		return false;
	if(Ver>10000){
		if(::Load(file,SelfSearch)==false)
			return false;
	}
	else{
		SelfSearch=Ver;
	}

	if(::Load(file,OmitVectorIndex)==false)
		return false;
	if(::Load(file,NMergin)==false)
		return false;
	if(::Load(file,BMergin)==false)
		return false;

	if(Ver>=20002){
		if(::Load(file,NMinNGCount)==false)
			return false;
		if(::Load(file,BMinNGCount)==false)
			return false;
	}
	if(Ver>=20003){
		if(::Load(file,BOKLength)==false)
			return false;
		if(::Load(file,NOKLength)==false)
			return false;
	}
	return true;
}
void	TrueColorBlockThreshold::FromLibrary(AlgorithmLibrary *src)
{
	TrueColorBlockLibrary	*LSrc=dynamic_cast<TrueColorBlockLibrary *>(src);
	if(LSrc==NULL)
		return;
	NMergin			=LSrc->NMergin;
	NInsColor		=LSrc->NInsColor;
	NOKDot			=LSrc->NOKDot;
	BMergin			=LSrc->BMergin;
	BInsColor		=LSrc->BInsColor;
	BOKDot			=LSrc->BOKDot;

	PointMove.ModeEnabled				=LSrc->PointMove.ModeEnabled;
	PointMove.ModeAdjustable			=LSrc->PointMove.ModeAdjustable;
	PointMove.ModeCommonMovable			=LSrc->PointMove.ModeCommonMovable;
	PointMove.ModeNGCluster				=LSrc->PointMove.ModeNGCluster;
	PointMove.ModeCenterBrightFromParts	=LSrc->PointMove.ModeCenterBrightFromParts;
	PointMove.ModeOnlyMatching			=LSrc->PointMove.ModeOnlyMatching;
	PointMove.ModeInvertLogic			=LSrc->PointMove.ModeInvertLogic;
	GetParentItem()->SetOriginType(_OriginType_FromLibrary);

		//v->CommonMoveID;
	CommonMoveDot=LSrc->CommonMoveDot;

	AdjustBlack		=LSrc->AdjustBlack;
	AdjustWhite		=LSrc->AdjustWhite;
	SelfSearch		=LSrc->SelfSearch;

	NMinNGCount		=LSrc->NMinNGCount;
	BMinNGCount		=LSrc->BMinNGCount;
	BOKLength		=LSrc->BOKLength;
	NOKLength		=LSrc->NOKLength;
}
void	TrueColorBlockThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	TrueColorBlockLibrary	*LDst=dynamic_cast<TrueColorBlockLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->NMergin	=NMergin	;
	LDst->NInsColor	=NInsColor	;
	LDst->NOKDot	=NOKDot		;
	LDst->BMergin	=BMergin	;
	LDst->BInsColor	=BInsColor	;
	LDst->BOKDot	=BOKDot		;

	LDst->PointMove.ModeEnabled					=PointMove.ModeEnabled	;
	LDst->PointMove.ModeAdjustable				=PointMove.ModeAdjustable	;
	LDst->PointMove.ModeCommonMovable			=PointMove.ModeCommonMovable	;
	LDst->PointMove.ModeNGCluster				=PointMove.ModeNGCluster		;
	LDst->PointMove.ModeCenterBrightFromParts	=PointMove.ModeCenterBrightFromParts	;
	LDst->PointMove.ModeOnlyMatching			=PointMove.ModeOnlyMatching	;
	LDst->PointMove.ModeInvertLogic				=PointMove.ModeInvertLogic	;

	LDst->CommonMoveDot							=CommonMoveDot;
	LDst->AdjustBlack							=AdjustBlack	;
	LDst->AdjustWhite							=AdjustWhite	;
	LDst->SelfSearch							=SelfSearch	;

	LDst->NMinNGCount							=NMinNGCount;
	LDst->BMinNGCount							=BMinNGCount;
	LDst->BOKLength								=BOKLength;
	LDst->NOKLength								=NOKLength;
}

//=====================================================================================
void	TrueColorBlockChangeShift::Reflect(TrueColorBlockBase *Base)
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

bool	TrueColorBlockChangeShift::Save(QIODevice *f)
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
bool	TrueColorBlockChangeShift::Load(QIODevice *f)
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

//===========================================================================================

TrueColorBlockItem::TrueColorBlockItem(void)
{
	InitialConstructor();
}
TrueColorBlockItem::TrueColorBlockItem(FlexArea &area)
:AlgorithmItemPI(area)
{
	InitialConstructor();
}

void TrueColorBlockItem::InitialConstructor(void)
{
	AVector=NULL;
}

TrueColorBlockItem::~TrueColorBlockItem(void)
{
}
void    TrueColorBlockItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPI::MoveTo(dx,dy);

    FLineEdge	.MoveToNoClip(dx,dy);
    FLineInside	.MoveToNoClip(dx,dy);
}

AlgorithmItemPI	&TrueColorBlockItem::operator=(const AlgorithmItemRoot &src)
{
	const TrueColorBlockItem	*s=dynamic_cast<const TrueColorBlockItem *>(&src);
	if(s!=NULL)
		return operator=(*s);
	return *this;
}
TrueColorBlockItem &TrueColorBlockItem::operator=(TrueColorBlockItem &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(src);
	return *this;
}

void	TrueColorBlockItem::CopyThreshold(TrueColorBlockItem &src)
{
	CenterBright	=src.CenterBright;
	GetThresholdW()->CopyFrom(*((TrueColorBlockThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	TrueColorBlockItem::CopyThresholdOnly(TrueColorBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((TrueColorBlockThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

bool    TrueColorBlockItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;
	DWORD	iCenterBright=(DWORD)CenterBright;
	if(::Save(file,iCenterBright)==false)
		return false;
	return true;
}
bool    TrueColorBlockItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;
	DWORD	iCenterBright;
	if(::Load(file,iCenterBright)==false)
		return false;
	CenterBright=(QRgb)iCenterBright;
	return true;
}

void	TrueColorBlockItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			TrueColorBlockInPage	*Pg=dynamic_cast<TrueColorBlockInPage *>(GetParentInPage());
			UndoElement<TrueColorBlockInPage>	*UPointer=new UndoElement<TrueColorBlockInPage>(Pg,&TrueColorBlockInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((TrueColorBlockItem *)Data));
			ImageBuffer **ImageList=new ImageBuffer *[GetLayerNumb()];
			GetMasterBuffList(ImageList);
			const TrueColorBlockThreshold	*RThr=GetThresholdR();
			if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
				CenterBright=CalcCenterBright(ImageList,0,0);
			delete	[]ImageList;

			GetThresholdW()->BInsColor.CreateTable(RThr->BMergin);
			GetThresholdW()->NInsColor.CreateTable(RThr->NMergin);
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((TrueColorBlockItem *)Data)->GetLibID()){
			TrueColorBlockInPage	*Pg=dynamic_cast<TrueColorBlockInPage *>(GetParentInPage());
			UndoElement<TrueColorBlockInPage>	*UPointer=new UndoElement<TrueColorBlockInPage>(Pg,&TrueColorBlockInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			CopyThresholdOnly(*((TrueColorBlockItem *)Data));
			ImageBuffer **ImageList=new ImageBuffer *[GetLayerNumb()];
			GetMasterBuffList(ImageList);
			const TrueColorBlockThreshold	*RThr=GetThresholdR();
			if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
				CenterBright=CalcCenterBright(ImageList,0,0);
			delete	[]ImageList;

			GetThresholdW()->BInsColor.CreateTable(RThr->BMergin);
			GetThresholdW()->NInsColor.CreateTable(RThr->NMergin);
		}
	}
}

void	TrueColorBlockItem::CopyArea(TrueColorBlockItem &src)
{
	SetArea(src.GetArea());
    FLineEdge	=src.FLineEdge;
    FLineInside	=src.FLineInside;
}


int		TrueColorBlockItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}
void	TrueColorBlockItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	TrueColorBlockItem	*ASrc=dynamic_cast<TrueColorBlockItem *>(src);
	if(ASrc!=NULL){
		FLineEdge.SetRefereneFrom(&ASrc->FLineEdge);
		FLineEdge.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		FLineInside.SetRefereneFrom(&ASrc->FLineInside);
		FLineInside.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

		int	OmitZoneDot=((TrueColorBlockBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineEdge	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineInside	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		CenterBright	=ASrc->CenterBright;
	}
}

ExeResult	TrueColorBlockItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int	gap=((TrueColorBlockBase *)GetParentBase())->OmitZoneDot;
	if(GetLayersBase()->GetBootingLevel()>=1){
		gap=5;
	}
	GetArea().ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	const TrueColorBlockThreshold	*RThr=GetThresholdR();
	if(IsOriginParts()==false){
		MakeInsideEdgeArea();
		GetThresholdW()->BInsColor.CreateTable(RThr->BMergin);
		GetThresholdW()->NInsColor.CreateTable(RThr->NMergin);
	}
	if(IsOriginParts()==false || RThr->PointMove.ModeCenterBrightFromParts==false)
		CenterBright=CalcCenterBright(GetMasterBuff(),0,0);

	return Ret;
}

void	TrueColorBlockItem::MakeInsideEdgeArea(void)
{
	const TrueColorBlockThreshold	*RThr=GetThresholdR();
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
	GetLayersBase()->ThinAreaN(BmpImage
				,TmpImage
				,XByte ,YLen
				,RThr->SelfSearch);

	FLineInside.BuildFromRaster(BmpImage,XByte ,YLen,0,0);
	FLineInside	.MoveToNoClip(mx,my);
	FLineEdge	.Sub(GetArea(),FLineInside);
	if((BYTE	**)BmpImageBuff!=BmpImage){
		DeleteMatrixBuff(BmpImage,YLen);
	}
	if((BYTE	**)TmpImageBuff!=TmpImage){
		DeleteMatrixBuff(TmpImage,YLen);
	}
	int	gap=((TrueColorBlockBase *)GetParentBase())->OmitZoneDot;
	FLineInside	.ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
	FLineEdge	.ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	TrueColorBlockItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID)
		DbgNumer++;

	const TrueColorBlockThreshold	*RThr=GetThresholdR();
	ColorLogic	InsColor;
	InsColor=*((ColorLogic *)&RThr->BInsColor);

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
	if(Res->GetAddedDataType()==1){
		if(Res->GetAddedData()!=NULL){
			TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->Error		=0;
			}
		}
	}
	short	Error=1;
	if(GetTargetBuff()[0]->IsNull()==false){
	    if(SubBlock.GetFirst()!=NULL){
			if(ExecuteProcessingInner(ThreadNo,Res
								  ,mx ,my
								  ,InsColor
								  ,RThr->BMergin
								  ,RThr->BOKDot ,RThr->BOKLength
								  ,RThr->BMinNGCount
								  ,_ThresholdBroad)==false){
				Error = 0x02;	//?L?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(2);

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInB		=Res->GetResult1();
								Q->Error		=Res->GetError();
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
								  ,InsColor
								  ,RThr->BMergin
								  ,RThr->BOKDot ,RThr->BOKLength
								  ,RThr->BMinNGCount
								  ,_ThresholdBroad)==false){
				Error = 0x02;	//?L?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(2);

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInB		=Res->GetResult1();
								Q->Error		=Res->GetError();
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
			TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->NGDotInB		=Res->GetResult1();
				Q->Error		=Error;
			}
		}
	}

	InsColor	=*((ColorLogic *)&RThr->NInsColor);
	if(GetTargetBuff()[0]->IsNull()==false){
	    if(SubBlock.GetFirst()!=NULL){
			if(ExecuteProcessingInner(ThreadNo,Res
								  ,mx ,my
								  ,InsColor
								  ,RThr->NMergin
								  ,RThr->NOKDot ,RThr->NOKLength
								  ,RThr->NMinNGCount
								  ,_ThresholdNarrow)==false){
				Error = 0x03;	//??E?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(3);

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInN		=Res->GetResult1();
								Q->Error		=Res->GetError();
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
								  ,InsColor
								  ,RThr->NMergin
								  ,RThr->NOKDot ,RThr->NOKLength
								  ,RThr->NMinNGCount
								  ,_ThresholdNarrow)==false){
				Error = 0x03;	//??E?a?A?m?f?-???€
				if(RThr->PointMove.ModeCalcBothBN==false){
					Res->SetError(3);

					if(Res->GetAddedDataType()==1){
						if(Res->GetAddedData()!=NULL){
							TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
							if(Q!=NULL){
								Q->NGDotInN		=Res->GetResult1();
								Q->Error		=Res->GetError();
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
			TrueColorBlockSendTryThreshold	*Q=dynamic_cast<TrueColorBlockSendTryThreshold *>(Res->GetAddedData());
			if(Q!=NULL){
				Q->NGDotInN		=Res->GetResult1();
				Q->Error		=Error;
			}
		}
	}
	Res->SetError(Error);
	FinishCalc();
	return _ER_true;
}

void	TrueColorBlockItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	TrueColorBlockDrawAttr	*BAttr=dynamic_cast<TrueColorBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		TrueColorBlockDrawAttr	TmpAttr;
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
		if(BAttr->DType==CmdTrueColorBlockDrawModePacket::_Area)
			AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdTrueColorBlockDrawModePacket::_Edge)
			AlgorithmItemPI::DrawArea(FLineEdge,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdTrueColorBlockDrawModePacket::_Inside)
			AlgorithmItemPI::DrawArea(FLineInside,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		//AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	TrueColorBlockItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
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

void	TrueColorBlockItem::SetInvertLogic(bool b)
{
	AlgorithmItemPI::SetInvertLogic(b);
	GetThresholdW()->PointMove.ModeInvertLogic=b;
}
	
bool	TrueColorBlockItem::GetInvertLogic(void)
{
	return GetThresholdR()->PointMove.ModeInvertLogic;
}

void	TrueColorBlockItem::AddMasterColor(int Mergin)
{
	ColorLogic CLogic;
	ImagePointerContainer ImageList;

	GetMasterBuffList(ImageList);
	GetArea().CreateColorLogic(ImageList, CLogic);

	GetThresholdW()->NInsColor.Add(CLogic,Mergin);
	GetThresholdW()->BInsColor.Add(CLogic,Mergin);
}

//===========================================================================================
TrueColorBlockInPage::TrueColorBlockInPage(AlgorithmBase *parent)
:AlgorithmInPagePI(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte=0;
	PickupBmpYLen=0;

	int	ThreadNumb;
	#pragma omp parallel                             
	{             
		ThreadNumb=omp_get_num_threads();
	}
	SWayListPerCPU=new SearchWayList[ThreadNumb];
}
TrueColorBlockInPage::~TrueColorBlockInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
	delete	[]SWayListPerCPU;
	SWayListPerCPU=NULL;
}

void	TrueColorBlockInPage::CreatePickupBmpBuff(void)
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

bool	TrueColorBlockInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfTrueColorBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfTrueColorBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}

void	TrueColorBlockInPage::PickupTest(TrueColorBlockLibrary &LibData)
{
	CreatePickupBmpBuff();
	bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibData.GetLibID());
	bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&LibData,NULL);
	if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
		ConstMapBufferListContainer MaskMap;
		if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
			ConstMapBuffer Map;
			MaskMap.BindOr(Map);
			ImagePointerContainer	ImageList;
			GetDataInPage()->GetMasterImages(ImageList);
			LibData.MakePickupTest(ImageList
									,Map.GetBitMap()
									,PickupBmp,NULL
									,GetPage()
									,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
									,((TrueColorBlockBase *)GetParentBase())->OmitZoneDot);
		}
	}
}
void	TrueColorBlockInPage::GenerateBlocks(TrueColorBlockLibrary *LibDim[],int LibDimNumb)
{
	UndoElement<TrueColorBlockInPage>	*UPointer=new UndoElement<TrueColorBlockInPage>(this,&TrueColorBlockInPage::UndoGenerateItems);
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
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		TrueColorBlockLibrary	*BLib=(TrueColorBlockLibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline;
		if(BLib->GenerationCategory==TrueColorBlockLibrary::_AutoSetting_OTHERMASK
		|| BLib->GenerationCategory==TrueColorBlockLibrary::_AutoSetting_SURROUND){
			BSpaceToOutline=0;
		}
		else{
			BSpaceToOutline=BLib->SpaceToOutline;
		}
		GetLayersBase()->FatAreaN(TempMap,TempMap2 ,XByte,GetMaxLines(),BSpaceToOutline);

		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2	 ,GetMaxLines());

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
				ImagePointerContainer	ImageList;
				GetDataInPage()->GetMasterImages(ImageList);
				LibDim[i]->MakePickupTest(ImageList
										,MaskBitmap
										,CurrentMap,OcupyMap
										,GetPage()
										,XByte ,GetDotPerLine(),GetMaxLines()
										,((TrueColorBlockBase *)GetParentBase())->OmitZoneDot);
				if(LibDim[i]->GenerationMode.LeftPickup==false){
					NPListPack<AlgorithmItemPI>	TmpBlockData;
					LibDim[i]->MakeBlock(
						 CurrentMap,LastOcupyMap
						 ,GetPage()
						,XByte ,GetDotPerLine(),GetMaxLines()
						,TmpBlockData);
					if(LibDim[i]->PointMove.ModeCommonMovable==true){
						int	CommonMoveID=CommonMoveIDList.GetCount()+1;
						CommonMoveIDList.Add(CommonMoveID);
						for(AlgorithmItemPI *a=TmpBlockData.GetFirst();a!=NULL;a=a->GetNext()){
							TrueColorBlockItem	*b=(TrueColorBlockItem *)a;
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
void	TrueColorBlockInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedTrueColorBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedTrueColorBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		TrueColorBlockItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			TrueColorBlockItem	*B=(TrueColorBlockItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				TrueColorBlockItem	*B=(TrueColorBlockItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
	}
	CmdClearTestTrueColorBlockPacket	*CmdClearTestTrueColorBlockPacketVar=dynamic_cast<CmdClearTestTrueColorBlockPacket *>(packet);
	if(CmdClearTestTrueColorBlockPacketVar!=NULL){
		if(PickupBmp!=NULL)
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
	}
	CmdTrueColorBlockInfoListPacket	*CmdTrueColorBlockInfoListPacketVar=dynamic_cast<CmdTrueColorBlockInfoListPacket *>(packet);
	if(CmdTrueColorBlockInfoListPacketVar!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			TrueColorBlockInfoList	*a;
			for(a=CmdTrueColorBlockInfoListPacketVar->TrueColorBlockInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->TrueColorBlockCount.GetItem(0);
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new TrueColorBlockInfoList();
				a->LibID=L->GetLibID();
				a->TrueColorBlockCount.Add(1);
				CmdTrueColorBlockInfoListPacketVar->TrueColorBlockInfos->AppendList(a);
			}
		}
	}
	CmdGetTrueColorBlockFromList	*CmdGetTrueColorBlockFromListVar=dynamic_cast<CmdGetTrueColorBlockFromList *>(packet);
	if(CmdGetTrueColorBlockFromListVar!=NULL){
		TrueColorBlockItem *Item=(TrueColorBlockItem *)SearchIDItem(CmdGetTrueColorBlockFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetTrueColorBlockFromListVar->TrueColorBlockInfoOnMouse=Item;
	}
	CmdCreateTrueColorBlockItem	*CmdCreateTrueColorBlockItemVar=dynamic_cast<CmdCreateTrueColorBlockItem *>(packet);
	if(CmdCreateTrueColorBlockItemVar!=NULL){
		CmdCreateTrueColorBlockItemVar->TrueColorBlock=(TrueColorBlockItem *)CreateItem(0);
	}
	CmdFindTrueColorBlockItem	*CmdFindTrueColorBlockItemVar=dynamic_cast<CmdFindTrueColorBlockItem *>(packet);
	if(CmdFindTrueColorBlockItemVar!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->IsInclude(CmdFindTrueColorBlockItemVar->LocalX,CmdFindTrueColorBlockItemVar->LocalY)==true){
				CmdFindTrueColorBlockItemVar->TrueColorBlock=dynamic_cast<TrueColorBlockItem *>(L);
				break;
			}
		}
		return;
	}
}

bool	TrueColorBlockInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	if(CommonMoveIDList.Save(f)==false)
		return false;
	return true;
}
bool	TrueColorBlockInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	if(CommonMoveIDList.Load(f)==false)
		return false;
	return true;
}

void	TrueColorBlockInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	TrueColorBlockDrawAttr	*BAttr=dynamic_cast<TrueColorBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==CmdTrueColorBlockDrawModePacket::_LibTest){
			if(PickupBmp!=NULL){
				TrueColorBlockBase	*BBase=dynamic_cast<TrueColorBlockBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==CmdTrueColorBlockDrawModePacket::_CreatedBlock){
			AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	}
}
void	TrueColorBlockInPage::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,int32 ItemID ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemAddInPlaceColor){
		int	N=GetItemCount();
		AlgorithmItemPI **ATable=new AlgorithmItemPI *[N];
		int	i=0;
		QBuffer	Buff(&Something);
		Buff.open(QIODevice::ReadOnly);
		int	Mergin;
		if(::Load(&Buff,Mergin)==true){
			for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext(),i++){
				ATable[i]=L;
			}
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int i=0;i<N;i++){
					TrueColorBlockItem	*a=(TrueColorBlockItem *)ATable[i];
					a->AddMasterColor(Mergin);
				}
			}
		}
		delete	[]ATable;
	}
	else{
		AlgorithmInPagePI::SetIndependentItemData(Command,LocalPage,Layer,ItemID,Data,EdittedMemberID,Something,AckData);
	}
}
void	TrueColorBlockInPage::UndoAppendManualItem(QIODevice *f)
{
	int	ItemID;
	::Load(f,ItemID);
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}

void	TrueColorBlockInPage::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		TrueColorBlockItem	*B=new TrueColorBlockItem();
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
void	TrueColorBlockInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		TrueColorBlockItem	*BI=(TrueColorBlockItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
//===========================================================================================
TrueColorBlockBase::TrueColorBlockBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup				=Qt::yellow;
	TrueColorBlockNormal	=Qt::darkGreen;
	TrueColorBlockSelected	=Qt::green;
	TrueColorBlockActive	=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;

	SetParam(&ColorPickup			, /**/"Color" ,/**/"ColorPickup"			,LangSolver.GetString(XTrueColorBlock_LS,LID_1)/*"Color for Image to Pickup-Test "*/);
	SetParam(&TrueColorBlockNormal	, /**/"Color" ,/**/"TrueColorBlockNormal"	,LangSolver.GetString(XTrueColorBlock_LS,LID_3)/*"Color for Block"*/);
	SetParam(&TrueColorBlockSelected, /**/"Color" ,/**/"TrueColorBlockSelected"	,LangSolver.GetString(XTrueColorBlock_LS,LID_5)/*"Color for Selected Block"*/);
	SetParam(&TrueColorBlockActive	, /**/"Color" ,/**/"TrueColorBlockActive"	,LangSolver.GetString(XTrueColorBlock_LS,LID_7)/*"Color for Active Block"*/);

	SetParam(&BlockColor0	, /**/"BlockColor" ,/**/"BlockColor0"	,LangSolver.GetString(XTrueColorBlock_LS,LID_9)/*"Block Color 0"*/);
	SetParam(&BlockColor1	, /**/"BlockColor" ,/**/"BlockColor1"	,LangSolver.GetString(XTrueColorBlock_LS,LID_11)/*"Block Color 1"*/);
	SetParam(&BlockColor2	, /**/"BlockColor" ,/**/"BlockColor2"	,LangSolver.GetString(XTrueColorBlock_LS,LID_13)/*"Block Color 2"*/);
	SetParam(&BlockColor3	, /**/"BlockColor" ,/**/"BlockColor3"	,LangSolver.GetString(XTrueColorBlock_LS,LID_15)/*"Block Color 3"*/);
	SetParam(&BlockColor4	, /**/"BlockColor" ,/**/"BlockColor4"	,LangSolver.GetString(XTrueColorBlock_LS,LID_17)/*"Block Color 4"*/);
	SetParam(&BlockColor5	, /**/"BlockColor" ,/**/"BlockColor5"	,LangSolver.GetString(XTrueColorBlock_LS,LID_19)/*"Block Color 5"*/);
	SetParam(&BlockColor6	, /**/"BlockColor" ,/**/"BlockColor6"	,LangSolver.GetString(XTrueColorBlock_LS,LID_21)/*"Block Color 6"*/);
	SetParam(&BlockColor7	, /**/"BlockColor" ,/**/"BlockColor7"	,LangSolver.GetString(XTrueColorBlock_LS,LID_23)/*"Block Color 7"*/);

	SetParam(&OmitZoneDot	, /**/"Setting"		,/**/"OmitZoneDot"	,LangSolver.GetString(XTrueColorBlock_LS,LID_25)/*"Omit zone dot in block generation"*/);
}

AlgorithmDrawAttr	*TrueColorBlockBase::CreateDrawAttr(void)
{
	return new TrueColorBlockDrawAttr();
}

void	TrueColorBlockBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetTrueColorBlockLibraryListPacket	*AListPacket=dynamic_cast<CmdGetTrueColorBlockLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetTrueColorBlockLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetTrueColorBlockLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertTrueColorBlockLibraryPacket	*BInsLib=dynamic_cast<CmdInsertTrueColorBlockLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(TrueColorBlockVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateTrueColorBlockLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateTrueColorBlockLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(TrueColorBlockVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadTrueColorBlockLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadTrueColorBlockLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempTrueColorBlockLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempTrueColorBlockLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearTrueColorBlockLibraryPacket	*CmdClearTrueColorBlockLibraryPacketVar=dynamic_cast<CmdClearTrueColorBlockLibraryPacket *>(packet);
	if(CmdClearTrueColorBlockLibraryPacketVar!=NULL){
		CmdClearTrueColorBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteTrueColorBlockLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteTrueColorBlockLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestTrueColorBlockPacket	*BPickLib=dynamic_cast<CmdPickupTestTrueColorBlockPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		TrueColorBlockInPage	*Bp=dynamic_cast<TrueColorBlockInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(*(TrueColorBlockLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateTrueColorBlockPacket	*BGenerated=dynamic_cast<CmdGenerateTrueColorBlockPacket *>(packet);
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
				TrueColorBlockLibrary	*L1=dynamic_cast<TrueColorBlockLibrary *>(LibDim[i  ]->GetLibrary());
				TrueColorBlockLibrary	*L2=dynamic_cast<TrueColorBlockLibrary *>(LibDim[i+1]->GetLibrary());
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
		TrueColorBlockLibrary	**DDim=new TrueColorBlockLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<TrueColorBlockLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			TrueColorBlockInPage	*Bp=dynamic_cast<TrueColorBlockInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateBlocks(DDim,N);		
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
	CmdCreateTempTrueColorBlockItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempTrueColorBlockItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new TrueColorBlockItem();
		return;
	}
	CmdCreateByteArrayFromTrueColorBlockItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromTrueColorBlockItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdAddByteTrueColorBlockItemPacket	*AddBItem=dynamic_cast<CmdAddByteTrueColorBlockItemPacket *>(packet);
	if(AddBItem!=NULL){
		TrueColorBlockInPage	*PData=dynamic_cast<TrueColorBlockInPage *>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			TrueColorBlockItem	*Item=new TrueColorBlockItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);

			UndoElement<TrueColorBlockInPage>	*UPointer=new UndoElement<TrueColorBlockInPage>(PData,&TrueColorBlockInPage::UndoAppendManualItem);
			::Save(UPointer->GetWritePointer(),Item->GetID());
			Item->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		}
	}
	CmdLoadTrueColorBlockItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadTrueColorBlockItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedTrueColorBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedTrueColorBlockFromByteArray *>(packet);
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
	CmdClearTestTrueColorBlockPacket	*CmdClearTestTrueColorBlockPacketVar=dynamic_cast<CmdClearTestTrueColorBlockPacket *>(packet);
	if(CmdClearTestTrueColorBlockPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestTrueColorBlockPacketVar);
		}
	}
	CmdTrueColorBlockInfoListPacket	*CmdTrueColorBlockInfoListPacketVar=dynamic_cast<CmdTrueColorBlockInfoListPacket *>(packet);
	if(CmdTrueColorBlockInfoListPacketVar!=NULL){
		GetPageData(CmdTrueColorBlockInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetTrueColorBlockFromList	*CmdGetTrueColorBlockFromListVar=dynamic_cast<CmdGetTrueColorBlockFromList *>(packet);
	if(CmdGetTrueColorBlockFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetTrueColorBlockFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateTrueColorBlockItem	*CmdCreateTrueColorBlockItemVar=dynamic_cast<CmdCreateTrueColorBlockItem *>(packet);
	if(CmdCreateTrueColorBlockItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

ExeResult	TrueColorBlockBase::ExecuteInitialAfterEdit(int ExeID 
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ColorLogicWithTable::ClearTable();
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}


bool	TrueColorBlockBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==TrueColorBlockHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==TrueColorBlockHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==TrueColorBlockReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==TrueColorBlockReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==TrueColorBlockReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==TrueColorBlockSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==TrueColorBlockReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*TrueColorBlockBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==TrueColorBlockHistogramListSendCommand){
		TrueColorBlockHistogramListSend	*pSend=new TrueColorBlockHistogramListSend();
		if(reqData!=NULL){
			TrueColorBlockHistogramListReq	*req=(TrueColorBlockHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==TrueColorBlockHistogramListReqCommand){
		return new TrueColorBlockHistogramListReq();
	}
	else if(Command==TrueColorBlockReqThresholdReqCommand){
		return new TrueColorBlockThresholdReq();
	}
	else if(Command==TrueColorBlockReqThresholdSendCommand){
		TrueColorBlockThresholdSend	*pSend=new TrueColorBlockThresholdSend();
		if(reqData!=NULL){
			TrueColorBlockThresholdReq	*req=(TrueColorBlockThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==TrueColorBlockReqTryThresholdCommand){
		return new TrueColorBlockReqTryThreshold();
	}
	else if(Command==TrueColorBlockSendTryThresholdCommand){
		TrueColorBlockSendTryThreshold	*pSend=new TrueColorBlockSendTryThreshold();
		if(reqData!=NULL){
			TrueColorBlockReqTryThreshold	*req=(TrueColorBlockReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==TrueColorBlockReqChangeShiftCommand){
		return new TrueColorBlockChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
	return NULL;
}
bool	TrueColorBlockBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==TrueColorBlockHistogramListSendCommand){
		TrueColorBlockHistogramListSend	*p=(TrueColorBlockHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==TrueColorBlockHistogramListReqCommand){
		TrueColorBlockHistogramListReq	*p=(TrueColorBlockHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==TrueColorBlockReqThresholdReqCommand){
		TrueColorBlockThresholdReq	*p=(TrueColorBlockThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==TrueColorBlockReqThresholdSendCommand){
		TrueColorBlockThresholdSend	*p=(TrueColorBlockThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==TrueColorBlockReqTryThresholdCommand){
		TrueColorBlockReqTryThreshold	*p=(TrueColorBlockReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==TrueColorBlockSendTryThresholdCommand){
		TrueColorBlockSendTryThreshold	*p=(TrueColorBlockSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==TrueColorBlockReqChangeShiftCommand){
		TrueColorBlockChangeShift	*p=(TrueColorBlockChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	TrueColorBlockBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==TrueColorBlockHistogramListSendCommand){
		TrueColorBlockHistogramListSend	*p=(TrueColorBlockHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==TrueColorBlockHistogramListReqCommand){
		TrueColorBlockHistogramListReq	*p=(TrueColorBlockHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==TrueColorBlockReqThresholdReqCommand){
		TrueColorBlockThresholdReq	*p=(TrueColorBlockThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==TrueColorBlockReqThresholdSendCommand){
		TrueColorBlockThresholdSend	*p=(TrueColorBlockThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==TrueColorBlockReqTryThresholdCommand){
		TrueColorBlockReqTryThreshold	*p=(TrueColorBlockReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==TrueColorBlockSendTryThresholdCommand){
		TrueColorBlockSendTryThreshold	*p=(TrueColorBlockSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==TrueColorBlockReqChangeShiftCommand){
		TrueColorBlockChangeShift	*p=(TrueColorBlockChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
	return false;
}
bool	TrueColorBlockBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==TrueColorBlockHistogramListSendCommand){
		TrueColorBlockHistogramListSend	*p=(TrueColorBlockHistogramListSend *)data;
		return true;
	}
	else if(Command==TrueColorBlockHistogramListReqCommand){
		TrueColorBlockHistogramListReq	*p=(TrueColorBlockHistogramListReq *)data;
		return true;
	}
	else if(Command==TrueColorBlockReqThresholdReqCommand){
		TrueColorBlockThresholdReq	*p=(TrueColorBlockThresholdReq *)data;
		return true;
	}
	else if(Command==TrueColorBlockReqThresholdSendCommand){
		TrueColorBlockThresholdSend	*p=(TrueColorBlockThresholdSend *)data;
		return true;
	}
	else if(Command==TrueColorBlockReqTryThresholdCommand){
		TrueColorBlockReqTryThreshold	*p=(TrueColorBlockReqTryThreshold *)data;
		return true;
	}
	else if(Command==TrueColorBlockSendTryThresholdCommand){
		TrueColorBlockSendTryThreshold	*p=(TrueColorBlockSendTryThreshold *)data;
		return true;
	}
	else if(Command==TrueColorBlockReqChangeShiftCommand){
		TrueColorBlockChangeShift	*p=(TrueColorBlockChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
	return false;
}

bool	TrueColorBlockBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	bool	ret=true;
	
	TrueColorChangeCreateBlockForm	Q(this);
	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultBlock.Save(&Buff)==false)
			return false;
	}
	
	return ret;
}

//=====================================================================================================
TrueColorBlockReqTryThreshold::TrueColorBlockReqTryThreshold(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
}
bool	TrueColorBlockReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	TrueColorBlockReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

TrueColorBlockSendTryThreshold::TrueColorBlockSendTryThreshold(void)
{
	NGDotInN	=0;
	NGDotInB	=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
	Error		=0;
}

bool	TrueColorBlockSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotInN	)==false)
		return false;
	if(::Save(f,NGDotInB	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	return true;
}
bool	TrueColorBlockSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotInN	)==false)
		return false;
	if(::Load(f,NGDotInB	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	return true;
}

void	TrueColorBlockSendTryThreshold::ConstructList(TrueColorBlockReqTryThreshold *reqPacket,TrueColorBlockBase *Base)
{
	ResultInItemPI	Res;
	Res.SetAddedData(this,1,sizeof(this));
	TrueColorBlockInPage	*BP=(TrueColorBlockInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		TrueColorBlockItem	*BI=(TrueColorBlockItem *)BP->SearchIDItem(reqPacket->BlockItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			reqPacket->Threshold.CenterBright						=BI->CenterBright;
			reqPacket->Threshold.GetThresholdW()->OmitVectorIndex	=BI->GetThresholdR(BP->GetLayersBase())->OmitVectorIndex;
			reqPacket->Threshold.AVector							=BI->AVector;
			reqPacket->Threshold.GetThresholdW()->PointMove.ModeCalcBothBN=true;
			reqPacket->Threshold.SetParent(BI->GetParent());
			reqPacket->Threshold.CopyArea(*BI);
			reqPacket->Threshold.GetThresholdW()->NInsColor.CreateTable(reqPacket->Threshold.GetThresholdW()->NMergin);
			reqPacket->Threshold.GetThresholdW()->BInsColor.CreateTable(reqPacket->Threshold.GetThresholdW()->BMergin);
			reqPacket->Threshold.ExecuteProcessing(0,0,&Res);
		}
	}
	Res.SetAddedData(NULL,0);

	ResultMoveDx=Res.GetTotalShiftedX();
	ResultMoveDy=Res.GetTotalShiftedY();
}

