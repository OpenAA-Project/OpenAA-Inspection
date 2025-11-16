/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ProjectedInspection\XProjectedInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ProjectedInspectionFormResource.h"
#include "XProjectedInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XProjectedInspectionLibrary.h"
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
#include "XProjectedInspectionAlgoPacket.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


const	int		SepNumb=10;


ProjectedInspectionHistogramListReq::ProjectedInspectionHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	ProjectedInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	ProjectedInspectionHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ProjectedInspectionHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


ProjectedInspectionHistogramListSend::ProjectedInspectionHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	ProjectedInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	ProjectedData	=NULL;
	ProjectedDots	=NULL;
	ProjectedDataLen=0;

}

ProjectedInspectionHistogramListSend::~ProjectedInspectionHistogramListSend(void)
{
	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
		ProjectedData=NULL;
	}
	if(ProjectedDots!=NULL){
		delete	[]ProjectedDots;
		ProjectedDots=NULL;
	}
	ProjectedDataLen=0;
}

void	ProjectedInspectionHistogramListSend::ConstructList(ProjectedInspectionHistogramListReq *reqPacket ,ProjectedInspectionBase *Base)
{
	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
		ProjectedData=NULL;
	}
	if(ProjectedDots!=NULL){
		delete	[]ProjectedDots;
		ProjectedDots=NULL;
	}

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ProjectedInspectionItemID	=reqPacket->ProjectedInspectionItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ProjectedInspectionItemID);
			if(item!=NULL){
				ProjectedInspectionItem	*Item=dynamic_cast<ProjectedInspectionItem*>(item);
			
				ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
				if(DRes!=NULL){
					ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());				
					ResultBasePhase	*RPhase=rbase->GetPageDataPhase(item->GetPhaseCode());
					ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(RPhase->GetPageData(item->GetParentInPage()->GetPage()));
					if(Rp!=NULL){
						ResultInLayerPLI	&rLayer=Rp->GetLayerData(Item->GetParent()->GetLayer());
						ResultInItemPLI		*rItem=rLayer.FindResultInItem(Item->GetID());
						if(rItem!=NULL){
							int	sx,sy;
							rItem->GetTotalShifted(sx,sy);
							ProjectedDataLen=Item->ProjectedDataLen;
							ProjectedData=new double[ProjectedDataLen];
							ProjectedDots=new int	[ProjectedDataLen];
							memcpy(ProjectedData,Item->ProjectedData,sizeof(double)*ProjectedDataLen);
						}
					}
				}
			}
		}
	}
}

bool	ProjectedInspectionHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,ProjectedDataLen)==false)
		return false;
	if(f->write((const char *)ProjectedData,sizeof(double)*ProjectedDataLen)!=sizeof(double)*ProjectedDataLen)
		return false;
	if(f->write((const char *)ProjectedDots,sizeof(int)*ProjectedDataLen)!=sizeof(int)*ProjectedDataLen)
		return false;

	return true;
}
bool	ProjectedInspectionHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,ProjectedDataLen)==false)
		return false;
	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
	}
	if(ProjectedDots!=NULL){
		delete	[]ProjectedDots;
	}
	ProjectedData=new double[ProjectedDataLen];
	ProjectedDots=new int	[ProjectedDataLen];
	if(f->read((char *)ProjectedData,sizeof(double)*ProjectedDataLen)!=sizeof(double)*ProjectedDataLen)
		return false;
	if(f->read((char *)ProjectedDots,sizeof(int)*ProjectedDataLen)!=sizeof(int)*ProjectedDataLen)
		return false;
	return true;
}
ProjectedInspectionThresholdReq::ProjectedInspectionThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	ProjectedInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	ProjectedInspectionThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ProjectedInspectionThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

ProjectedInspectionThresholdSend::ProjectedInspectionThresholdSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	ProjectedInspectionItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;

	Angle	=0;
	ExcludeDynamicMask=false;
	TransitWidth	=10;
	OKWidthDiffereceL=128;
	OKWidthDiffereceH=128;
	UseAbsolute		=true;
	EvenLength		=99999999;
}

void	ProjectedInspectionThresholdSend::ConstructList(ProjectedInspectionThresholdReq *reqPacket,ProjectedInspectionBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ProjectedInspectionItemID	=reqPacket->ProjectedInspectionItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerRoot	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ProjectedInspectionItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				ProjectedInspectionItem	*BItem=(ProjectedInspectionItem *)item;
				const ProjectedInspectionThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				Angle				=RThr->Angle				;
				ExcludeDynamicMask	=RThr->ExcludeDynamicMask	;
				TransitWidth		=RThr->TransitWidth		;
				OKWidthDiffereceL	=RThr->OKWidthDiffereceL	;
				OKWidthDiffereceH	=RThr->OKWidthDiffereceH	;
				UseAbsolute			=RThr->UseAbsolute	;
				EvenLength			=RThr->EvenLength	;
				//CenterTargetBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),dx,dy);
			}
		}
	}
}

bool	ProjectedInspectionThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;

	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,ExcludeDynamicMask)==false)
		return false;
	if(::Save(f,TransitWidth)==false)
		return false;
	if(::Save(f,OKWidthDiffereceL)==false)
		return false;
	if(::Save(f,OKWidthDiffereceH)==false)
		return false;
	if(::Save(f,UseAbsolute)==false)
		return false;
	if(::Save(f,EvenLength)==false)
		return false;
	return true;
}
bool	ProjectedInspectionThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;

	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,ExcludeDynamicMask)==false)
		return false;
	if(::Load(f,TransitWidth)==false)
		return false;
	if(::Load(f,OKWidthDiffereceL)==false)
		return false;
	if(::Load(f,OKWidthDiffereceH)==false)
		return false;
	if(::Load(f,UseAbsolute)==false)
		return false;
	if(::Load(f,EvenLength)==false)
		return false;


	return true;
}

ProjectedInspectionReqTryThreshold::ProjectedInspectionReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	ProjectedInspectionItemID=-1;
}
bool	ProjectedInspectionReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ProjectedInspectionItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	ProjectedInspectionReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ProjectedInspectionItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

ProjectedInspectionSendTryThreshold::ProjectedInspectionSendTryThreshold(void)
{
	NGDots	=0;
	Error			=0;
	Result	=new ResultInItemPLI();
}
ProjectedInspectionSendTryThreshold::~ProjectedInspectionSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}


bool	ProjectedInspectionSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDots	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(Result->Save(f)==false)
		return false;
	return true;
}
bool	ProjectedInspectionSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDots	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(Result->Load(f)==false)
		return false;
	return true;
}

void	ProjectedInspectionSendTryThreshold::ConstructList(ProjectedInspectionReqTryThreshold *reqPacket,ProjectedInspectionBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	ProjectedInspectionInPage		*BP=(ProjectedInspectionInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		ProjectedInspectionInLayer	*BL=(ProjectedInspectionInLayer *)BP->GetLayerData(reqPacket->Layer);
		if(BL!=NULL){
			ProjectedInspectionItem		*BI=(ProjectedInspectionItem *)BL->SearchIDItem(reqPacket->ProjectedInspectionItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.AVector							=BI->AVector;
				reqPacket->Threshold.SetParent(BI->GetParent());
				//reqPacket->Threshold.CopyArea(*BI);
				reqPacket->Threshold.ExecuteProcessing(0,0,Result);
				Error=Result->GetError();
				NGDots=Result->GetResult1();
			}
		}
	}
	Result->SetAddedData(NULL,0);

}


//=====================================================================================
void	ProjectedInspectionChangeShift::Reflect(ProjectedInspectionBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ProjectedInspectionItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	ProjectedInspectionChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	ProjectedInspectionChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ProjectedInspectionItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
//=====================================================================================
//===========================================================================================

ProjectedInspectionInLayer::ProjectedInspectionInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLITemplate<ProjectedInspectionItem,ProjectedInspectionInPage,ProjectedInspectionBase>(parent)
{
	PickupBmp=NULL;
	PickupBmpYLen=0;
}

ProjectedInspectionInLayer::~ProjectedInspectionInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}

AlgorithmItemRoot	*ProjectedInspectionInLayer::CreateItem(int ItemClassType)
{	
	if(ItemClassType==0){
		ProjectedInspectionItem	*a=new ProjectedInspectionItem();	
		a->SetParent(this);
		return a;
	}
	else{
		return NULL;
	}
}
void	ProjectedInspectionInLayer::CreatePickupBmpBuff(void)
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

void	ProjectedInspectionInLayer::PickupTest(ProjectedInspectionLibrary &LibData)
{
	int	XByte=(GetDotPerLine()+7)/8;

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
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetEditLocked()==true){
				if(L->GetLibID()==B->GetLib().GetLibID()){
					L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
				}
			}
		}
		ProjectedInspectionLibrary	*BLib=(ProjectedInspectionLibrary *)B->GetLib().GetLibrary();
		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2		,GetMaxLines());

	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);

	if(GetMasterBuff().IsNull()==false){
		LibData.MakePickupTest(GetPage()
			,GetMasterBuff()
			,MaskMap.GetBitMap() ,(const BYTE **)LastOcupyMap
			,PickupBmp,NULL
			,GetPage()
			,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
			,((ProjectedInspectionBase *)GetParentBase())->OmitZoneDot);
	}
	else if(GetTargetBuff().IsNull()==false){
		LibData.MakePickupTest(GetPage()
			,GetTargetBuff()
			,MaskMap.GetBitMap(),(const BYTE **)LastOcupyMap
			,PickupBmp,NULL
			,GetPage()
			,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
			,((ProjectedInspectionBase *)GetParentBase())->OmitZoneDot);	
	}
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
}

void	ProjectedInspectionInLayer::GenerateBlocks(ProjectedInspectionLibrary *LibDim[],int LibDimNumb)
{
	UndoElement<ProjectedInspectionInLayer>	*UPointer=new UndoElement<ProjectedInspectionInLayer>(this,&ProjectedInspectionInLayer::UndoGenerateItems);
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
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		ProjectedInspectionLibrary	*BLib=(ProjectedInspectionLibrary *)B->GetLib().GetLibrary();
		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2		,GetMaxLines());

	BYTE **OcupyMap				=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **OcupyMapSamePriority	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());

	GetParentBase()->LoadAllManagedCacheLib();
	IntList	AddedItemIDList;
	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBuffer MaskMap;
		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			AlgorithmInPagePLI	*LPg=(AlgorithmInPagePLI*)GetParentInPage();
			AlgorithmInLayerPLI	*LL;
			if(LibDim[i]->GetAdaptedPickLayers().IsInclude(GetLayer())==true){
				LL=(AlgorithmInLayerPLI *)LPg->GetLayerData(GetLayer());
			}
			else{
				LL=(AlgorithmInLayerPLI *)LPg->GetLayerData(LibDim[i]->GetAdaptedPickLayers().GetFirst()->GetValue());
			}
			LL->GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		else{
			GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();
		
		//if(LibDim[i]->GenerationMode.Transparent==false){
		//	MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());
		//}

		ImageBuffer	*MImage=NULL;
		if(GetMasterBuff().IsNull()==false)
			MImage=&GetMasterBuff();
		else if(GetTargetBuff().IsNull()==false)
			MImage=&GetTargetBuff();

		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			for(int LLayer=0;LLayer<GetLayerNumb();LLayer++){
				if(LibDim[i]->HasPickLayer(LLayer)==true){
					ImagePointerContainer ImagesPointers;
					if(GetMasterBuff().IsNull()==false)
						GetParentInPage()->GetMasterImages(ImagesPointers);
					else if(GetTargetBuff().IsNull()==false)
						GetParentInPage()->GetTargetImages(ImagesPointers);
					MImage=ImagesPointers[LLayer];
					break;
				}
			}
		}

		LibDim[i]->MakePickupTest(GetPage()
			,*MImage
			,MaskBitmap,(const BYTE **)LastOcupyMap
			,CurrentMap,OcupyMap
			,GetPage()
			,XByte ,GetDotPerLine(),GetMaxLines()
			,((ProjectedInspectionBase *)GetParentBase())->OmitZoneDot);

		NPListPack<AlgorithmItemPLI>	TmpBlockData;
		LibDim[i]->MakeBlock(GetPage()
				,CurrentMap,LastOcupyMap
				,GetPage()
				,XByte ,GetDotPerLine(),GetMaxLines()
				,TmpBlockData);

		AlgorithmItemPLI	*q;

		while((q=TmpBlockData.GetFirst())!=NULL){
			TmpBlockData.RemoveList(q);
			if(AppendItem(q)==true){
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

void	ProjectedInspectionInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedProjectedInspectionFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedProjectedInspectionFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		ProjectedInspectionItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ProjectedInspectionItem	*B=(ProjectedInspectionItem *)L;
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
				ProjectedInspectionItem	*B=(ProjectedInspectionItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestProjectedInspectionPacket	*CmdClearTestProjectedInspectionPacketVar=dynamic_cast<CmdClearTestProjectedInspectionPacket *>(packet);
	if(CmdClearTestProjectedInspectionPacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}
	CmdProjectedInspectionInfoListPacket	*CmdProjectedInspectionInfoListPacketVar=dynamic_cast<CmdProjectedInspectionInfoListPacket *>(packet);
	if(CmdProjectedInspectionInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			ProjectedInspectionInfoList	*a=new ProjectedInspectionInfoList();
			a->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			a->Layer		=GetLayer();
			a->ItemID		=L->GetID();
			a->LibID		=L->GetLibID();
			L->GetXY(a->x1,a->y1,a->x2,a->y2);
			CmdProjectedInspectionInfoListPacketVar->ProjectedInspectionInfos->AppendList(a);
		}
		return;
	}
	CmdGetProjectedInspectionFromList	*CmdGetProjectedInspectionFromListVar=dynamic_cast<CmdGetProjectedInspectionFromList *>(packet);
	if(CmdGetProjectedInspectionFromListVar!=NULL){
		ProjectedInspectionItem *Item=(ProjectedInspectionItem *)SearchIDItem(CmdGetProjectedInspectionFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetProjectedInspectionFromListVar->ProjectedInspectionInfoOnMouse=Item;
		return;
	}
	CmdCreateProjectedInspectionItem	*CmdCreateProjectedInspectionItemVar=dynamic_cast<CmdCreateProjectedInspectionItem *>(packet);
	if(CmdCreateProjectedInspectionItemVar!=NULL){
		CmdCreateProjectedInspectionItemVar->ProjectedInspection=(ProjectedInspectionItem *)CreateItem(0);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		ProjectedInspectionItem *Item=(ProjectedInspectionItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);
			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
		}
		return;
	}
}

void	ProjectedInspectionInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ProjectedInspectionDrawAttr	*BAttr=dynamic_cast<ProjectedInspectionDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(PickupBmp!=NULL){
			ProjectedInspectionBase	*BBase=dynamic_cast<ProjectedInspectionBase *>(GetParentBase());
			DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
				,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
					,0,0
					,BBase->ColorPickup);
		}
	}

	AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
}
void	ProjectedInspectionInLayer::UndoAppendManualItem(QIODevice *f)
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

void	ProjectedInspectionInLayer::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		ProjectedInspectionItem	*B=new ProjectedInspectionItem();
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

void	ProjectedInspectionInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		ProjectedInspectionItem	*BI=(ProjectedInspectionItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

void	ProjectedInspectionInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		ProjectedInspectionItem	*BI=(ProjectedInspectionItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

//===========================================================================================
ProjectedInspectionInPage::ProjectedInspectionInPage(AlgorithmBase *parent)
:AlgorithmInPagePLITemplate<ProjectedInspectionItem,ProjectedInspectionInLayer,ProjectedInspectionBase>(parent)
{
}
ProjectedInspectionInPage::~ProjectedInspectionInPage(void)
{
}

void	ProjectedInspectionInPage::PickupTest(IntList &LayerList ,ProjectedInspectionLibrary &LibData)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			ProjectedInspectionInLayer	*BI=dynamic_cast<ProjectedInspectionInLayer *>(AL);
			if(BI!=NULL){
				BI->PickupTest(LibData);
			}
		}
	}
}

void	ProjectedInspectionInPage::GenerateBlocks(IntList &LayerList, ProjectedInspectionLibrary *LibDim[],int LibDimNumb)
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		ProjectedInspectionLibrary *TmpLibDim[1000];
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
			ProjectedInspectionInLayer	*BI=dynamic_cast<ProjectedInspectionInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateBlocks(TmpLibDim,LibN);
			}
		}
	}
}

void	ProjectedInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedProjectedInspectionFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedProjectedInspectionFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(IntClass *L=ModifyItemFromBA->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}	
	CmdClearTestProjectedInspectionPacket	*CmdClearTestProjectedInspectionPacketVar=dynamic_cast<CmdClearTestProjectedInspectionPacket *>(packet);
	if(CmdClearTestProjectedInspectionPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdClearTestProjectedInspectionPacketVar);
		}
		return;
	}
	CmdProjectedInspectionInfoListPacket	*CmdProjectedInspectionInfoListPacketVar=dynamic_cast<CmdProjectedInspectionInfoListPacket *>(packet);
	if(CmdProjectedInspectionInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdProjectedInspectionInfoListPacketVar);
		}
		return;
	}
	CmdGetProjectedInspectionFromList	*CmdGetProjectedInspectionFromListVar=dynamic_cast<CmdGetProjectedInspectionFromList *>(packet);
	if(CmdGetProjectedInspectionFromListVar!=NULL){
		if(CmdGetProjectedInspectionFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetProjectedInspectionFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdCreateProjectedInspectionItem	*CmdCreateProjectedInspectionItemVar=dynamic_cast<CmdCreateProjectedInspectionItem *>(packet);
	if(CmdCreateProjectedInspectionItemVar!=NULL){
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
	CmdAddByteProjectedInspectionItemPacket	*AddBItem=dynamic_cast<CmdAddByteProjectedInspectionItemPacket *>(packet);
	if(AddBItem!=NULL){
		for(IntClass *L=AddBItem->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			ProjectedInspectionInLayer	*BL=dynamic_cast<ProjectedInspectionInLayer *>(GetLayerData(L->GetValue()));
			if(BL!=NULL){
				QBuffer	MBuff(&AddBItem->Buff);
				ProjectedInspectionItem	*Item=new ProjectedInspectionItem();
				MBuff.open(QIODevice::ReadWrite);
				Item->SetParent(BL);
				Item->Load(&MBuff,GetLayersBase());
				Item->SetLibID(AddBItem->LibID);

				AlgorithmLibraryContainer	*Container=GetLibraryContainer();
				AlgorithmLibraryLevelContainer	LLib(Container);
				if(GetParentBase()->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
					Item->CopyThresholdFromLibrary(&LLib);
				}

				Item->SetArea(AddBItem->Area);
				Item->SetManualCreated(true);
				BL->AppendItem(Item);

				UndoElement<ProjectedInspectionInLayer>	*UPointer=new UndoElement<ProjectedInspectionInLayer>(BL,&ProjectedInspectionInLayer::UndoAppendManualItem);
				::Save(UPointer->GetWritePointer(),Item->GetID());
				Item->Save(UPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			}
		}
		return;
	}
}

//===========================================================================================
ProjectedInspectionBase::ProjectedInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup		=Qt::yellow;
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;
	OmitZoneDot	=100;

	SetParam(&ColorPickup				, /**/"Color"	,/**/"ColorPickup"			,"Color for Image to Pickup-Test ");
	SetParam(&ColorArea					, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected				, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive				, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea				, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected			, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel			, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");

	SetParam(&OmitZoneDot	, /**/"Setting"		,/**/"OmitZoneDot"	,"Omit zone dot");
}

AlgorithmDrawAttr	*ProjectedInspectionBase::CreateDrawAttr(void)
{
	return new ProjectedInspectionDrawAttr(GetLayersBase());
}

void	ProjectedInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetProjectedInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetProjectedInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetProjectedInspectionLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetProjectedInspectionLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertProjectedInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertProjectedInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(ProjectedInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateProjectedInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateProjectedInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(ProjectedInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadProjectedInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadProjectedInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempProjectedInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempProjectedInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearProjectedInspectionLibraryPacket	*CmdClearProjectedInspectionLibraryPacketVar=dynamic_cast<CmdClearProjectedInspectionLibraryPacket *>(packet);
	if(CmdClearProjectedInspectionLibraryPacketVar!=NULL){
		CmdClearProjectedInspectionLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteProjectedInspectionLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteProjectedInspectionLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestProjectedInspectionPacket	*BPickLib=dynamic_cast<CmdPickupTestProjectedInspectionPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		ProjectedInspectionInPage	*Bp=dynamic_cast<ProjectedInspectionInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(BPickLib->LayerList,*(ProjectedInspectionLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateProjectedInspectionPacket	*BGenerated=dynamic_cast<CmdGenerateProjectedInspectionPacket *>(packet);
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
				ProjectedInspectionLibrary	*L1=dynamic_cast<ProjectedInspectionLibrary *>(LibDim[i  ]->GetLibrary());
				ProjectedInspectionLibrary	*L2=dynamic_cast<ProjectedInspectionLibrary *>(LibDim[i+1]->GetLibrary());
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

		ProjectedInspectionLibrary	**DDim=new ProjectedInspectionLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<ProjectedInspectionLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			ProjectedInspectionInPage	*Bp=dynamic_cast<ProjectedInspectionInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateBlocks(BGenerated->LayerList,DDim,N);		
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
	CmdCreateTempProjectedInspectionItemPacket	*CreateProjectedInspectionItem=dynamic_cast<CmdCreateTempProjectedInspectionItemPacket *>(packet);
	if(CreateProjectedInspectionItem!=NULL){
		CreateProjectedInspectionItem->Point=new ProjectedInspectionItem();
		return;
	}
	CmdCreateByteArrayFromProjectedInspectionItemPacket	*BAFromProjectedInspectionItem=dynamic_cast<CmdCreateByteArrayFromProjectedInspectionItemPacket *>(packet);
	if(BAFromProjectedInspectionItem!=NULL){
		QBuffer	Buff(&BAFromProjectedInspectionItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromProjectedInspectionItem->Point->Save(&Buff);
	}
	CmdLoadProjectedInspectionItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadProjectedInspectionItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedProjectedInspectionFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedProjectedInspectionFromByteArray *>(packet);
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
	CmdClearTestProjectedInspectionPacket	*CmdClearTestProjectedInspectionPacketVar=dynamic_cast<CmdClearTestProjectedInspectionPacket *>(packet);
	if(CmdClearTestProjectedInspectionPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestProjectedInspectionPacketVar);
		}
	}
	CmdProjectedInspectionInfoListPacket	*CmdProjectedInspectionInfoListPacketVar=dynamic_cast<CmdProjectedInspectionInfoListPacket *>(packet);
	if(CmdProjectedInspectionInfoListPacketVar!=NULL){
		GetPageData(CmdProjectedInspectionInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetProjectedInspectionFromList	*CmdGetProjectedInspectionFromListVar=dynamic_cast<CmdGetProjectedInspectionFromList *>(packet);
	if(CmdGetProjectedInspectionFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetProjectedInspectionFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
	CmdCreateProjectedInspectionItem	*CmdCreateProjectedInspectionItemVar=dynamic_cast<CmdCreateProjectedInspectionItem *>(packet);
	if(CmdCreateProjectedInspectionItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

bool	ProjectedInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==ProjectedInspectionHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ProjectedInspectionHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ProjectedInspectionReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==ProjectedInspectionReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==ProjectedInspectionReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ProjectedInspectionSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==ProjectedInspectionReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*ProjectedInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==ProjectedInspectionHistogramListSendCommand){
		ProjectedInspectionHistogramListSend	*pSend=new ProjectedInspectionHistogramListSend();
		if(reqData!=NULL){
			ProjectedInspectionHistogramListReq	*req=(ProjectedInspectionHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ProjectedInspectionHistogramListReqCommand){
		return new ProjectedInspectionHistogramListReq();
	}
	else if(Command==ProjectedInspectionReqThresholdReqCommand){
		return new ProjectedInspectionThresholdReq();
	}
	else if(Command==ProjectedInspectionReqThresholdSendCommand){
		ProjectedInspectionThresholdSend	*pSend=new ProjectedInspectionThresholdSend();
		if(reqData!=NULL){
			ProjectedInspectionThresholdReq	*req=(ProjectedInspectionThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ProjectedInspectionReqTryThresholdCommand){
		return new ProjectedInspectionReqTryThreshold();
	}
	else if(Command==ProjectedInspectionSendTryThresholdCommand){
		ProjectedInspectionSendTryThreshold	*pSend=new ProjectedInspectionSendTryThreshold();
		if(reqData!=NULL){
			ProjectedInspectionReqTryThreshold	*req=(ProjectedInspectionReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==ProjectedInspectionReqChangeShiftCommand){
		return new ProjectedInspectionChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	ProjectedInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==ProjectedInspectionHistogramListSendCommand){
		ProjectedInspectionHistogramListSend	*p=(ProjectedInspectionHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==ProjectedInspectionHistogramListReqCommand){
		ProjectedInspectionHistogramListReq	*p=(ProjectedInspectionHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==ProjectedInspectionReqThresholdReqCommand){
		ProjectedInspectionThresholdReq	*p=(ProjectedInspectionThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==ProjectedInspectionReqThresholdSendCommand){
		ProjectedInspectionThresholdSend	*p=(ProjectedInspectionThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==ProjectedInspectionReqTryThresholdCommand){
		ProjectedInspectionReqTryThreshold	*p=(ProjectedInspectionReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==ProjectedInspectionSendTryThresholdCommand){
		ProjectedInspectionSendTryThreshold	*p=(ProjectedInspectionSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==ProjectedInspectionReqChangeShiftCommand){
		ProjectedInspectionChangeShift	*p=(ProjectedInspectionChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	ProjectedInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==ProjectedInspectionHistogramListSendCommand){
		ProjectedInspectionHistogramListSend	*p=(ProjectedInspectionHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==ProjectedInspectionHistogramListReqCommand){
		ProjectedInspectionHistogramListReq	*p=(ProjectedInspectionHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==ProjectedInspectionReqThresholdReqCommand){
		ProjectedInspectionThresholdReq	*p=(ProjectedInspectionThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==ProjectedInspectionReqThresholdSendCommand){
		ProjectedInspectionThresholdSend	*p=(ProjectedInspectionThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==ProjectedInspectionReqTryThresholdCommand){
		ProjectedInspectionReqTryThreshold	*p=(ProjectedInspectionReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==ProjectedInspectionSendTryThresholdCommand){
		ProjectedInspectionSendTryThreshold	*p=(ProjectedInspectionSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==ProjectedInspectionReqChangeShiftCommand){
		ProjectedInspectionChangeShift	*p=(ProjectedInspectionChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	ProjectedInspectionBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==ProjectedInspectionHistogramListSendCommand){
		ProjectedInspectionHistogramListSend	*p=(ProjectedInspectionHistogramListSend *)data;
		return true;
	}
	else if(Command==ProjectedInspectionHistogramListReqCommand){
		ProjectedInspectionHistogramListReq	*p=(ProjectedInspectionHistogramListReq *)data;
		return true;
	}
	else if(Command==ProjectedInspectionReqThresholdReqCommand){
		ProjectedInspectionThresholdReq	*p=(ProjectedInspectionThresholdReq *)data;
		return true;
	}
	else if(Command==ProjectedInspectionReqThresholdSendCommand){
		ProjectedInspectionThresholdSend	*p=(ProjectedInspectionThresholdSend *)data;
		return true;
	}
	else if(Command==ProjectedInspectionReqTryThresholdCommand){
		ProjectedInspectionReqTryThreshold	*p=(ProjectedInspectionReqTryThreshold *)data;
		return true;
	}
	else if(Command==ProjectedInspectionSendTryThresholdCommand){
		ProjectedInspectionSendTryThreshold	*p=(ProjectedInspectionSendTryThreshold *)data;
		return true;
	}
	else if(Command==ProjectedInspectionReqChangeShiftCommand){
		ProjectedInspectionChangeShift	*p=(ProjectedInspectionChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	ProjectedInspectionBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	/*
	ChangeCreateProjectedInspectionForm	Q(this,GetLayersBase()->GetMainWidget());
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultProjectedInspection.Save(&Buff)==false)
			return false;
	}
	return ret;
	*/
	return true;
}


//===========================================================================================

