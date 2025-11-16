/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XBlockInLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "BlockFormResource.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include "XPropertyBlockPacket.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "ChangeCreateBlockForm.h"
//#include "XMasking.h"
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XDynamicMaskingPICommon.h"
#include "XUndo.h"
#include "XBlockAlgoPacket.h"
#include "swap.h"
#include "XAlignmentCommon.h"
#include "XAlgorithmDLL.h"
#include "XDisplaySimPanel.h"
#include "XPropertyBlockCommon.h"
#include "XBlockManualExecuter.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	DbgID=3158;
static	int	DbgLayer=1;
static	int	DbgNumer=0;


ExecutablePointerList::ExecutablePointerList(void)
{
	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;

	Container	=NULL;
	ParentLayer	=NULL;
}
ExecutablePointerList::~ExecutablePointerList(void)
{
	if(DynamicMaskMap!=NULL){
		DeleteMatrixBuff(DynamicMaskMap,DynamicMaskMapYLen);
		DynamicMaskMap		=NULL;
		DynamicMaskMapXByte	=0;
		DynamicMaskMapYLen	=0;
	}
}

void	ExecutablePointerList::SplitSubtraction(ExecutablePointerContainer &ChildFormer,ExecutablePointerContainer &ChildLater)
{
	IntList	LibList;
	for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;p=p->GetNext()){
		if(LibList.IsInclude(p->GetItem()->GetLibID())==false)
			LibList.Add(p->GetItem()->GetLibID());
	}
	
	if(LibList.GetCount()>1){
		AlgorithmLibraryContainer	*LibContainer=ParentLayer->GetLibraryContainer();
		for(IntClass *c=LibList.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmLibraryLevelContainer	LLib(LibContainer);
			if(LibContainer->GetLibrary(c->GetValue(),LLib)==true){
				BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(LLib.GetLibrary());
				ExecutablePointerList	*W=NULL;
				for(IntClass *d=ALib->SubtractBlock.GetFirst();d!=NULL;d=d->GetNext()){
					if(LibList.IsInclude(d->GetValue())==true && c->GetValue()!=d->GetValue()){
						for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;){
							AlgorithmItemPointerList *NextA=p->GetNext();
							if(p->GetItem()->GetLibID()==d->GetValue()){
								ItemPointer.RemoveList(p);
								if(W==NULL){
									W=new ExecutablePointerList();
									W->Container	=Container;
									W->ParentLayer	=ParentLayer;
								}
								W->ItemPointer.AppendList(p);
							}
							p=NextA;
						}
					}
				}
				if(W!=NULL){
					ChildFormer.AppendList(W);
				}

				W=NULL;
				for(IntClass *d=ALib->SubtractBlock.GetFirst();d!=NULL;d=d->GetNext()){
					if(LibList.IsInclude(d->GetValue())==true && c->GetValue()!=d->GetValue()){
						for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;){
							AlgorithmItemPointerList *NextA=p->GetNext();
							if(p->GetItem()->GetLibID()==c->GetValue()){
								ItemPointer.RemoveList(p);
								if(W==NULL){
									W=new ExecutablePointerList();
									W->Container	=Container;
									W->ParentLayer	=ParentLayer;
								}
								W->ItemPointer.AppendList(p);
							}
							p=NextA;
						}
					}
				}
				if(W!=NULL){
					ChildLater.AppendList(W);
				}
			}
		}
	}
}

void		ExecutablePointerList::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInLayerRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ItemLibList.RemoveAll();
	for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;p=p->GetNext()){
		if(ItemLibList.IsInclude(p->GetItem()->GetLibID())==false)
			ItemLibList.Add(p->GetItem()->GetLibID());
	}
	MaskLinkedLibList.RemoveAll();
	AlgorithmLibraryContainer	*LibContainer=ParentLayer->GetLibraryContainer();
	for(IntClass *c=ItemLibList.GetFirst();c!=NULL;c=c->GetNext()){
		AlgorithmLibraryLevelContainer	LLib(LibContainer);
		if(LibContainer->GetLibrary(c->GetValue(),LLib)==true){
			BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(LLib.GetLibrary());
			if(ALib->SubtractBlock.GetCount()>0){
				MaskLinkedLibList.Merge(ALib->SubtractBlock);
			}
		}
	}
	if(DynamicMaskMap!=NULL){
		DeleteMatrixBuff(DynamicMaskMap,DynamicMaskMapYLen);
		DynamicMaskMap		=NULL;
		DynamicMaskMapXByte	=0;
		DynamicMaskMapYLen	=0;
	}

	if(MaskLinkedLibList.GetCount()>0){
		DynamicMaskMapXByte	=(ParentLayer->GetDotPerLine()+7)/8;
		DynamicMaskMapYLen	= ParentLayer->GetMaxLines();
		DynamicMaskMap	=MakeMatrixBuff(DynamicMaskMapXByte,DynamicMaskMapYLen);
	}
	MaskLinkedItems.RemoveAll();
	for(IntClass *c=MaskLinkedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		for(AlgorithmItemPLI *p=ParentLayer->GetFirstData();p!=NULL;p=p->GetNext()){
			if(p->GetLibID()==c->GetValue()){
				MaskLinkedItems.Add(p);
			}
		}
	}
}
void		ExecutablePointerList::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	if(DynamicMaskMap!=NULL){
		MatrixBuffClear	(DynamicMaskMap ,0 ,DynamicMaskMapXByte ,DynamicMaskMapYLen);
	}
}

void	ExecutablePointerList::MakeDynamicMask(void)
{
	if(ParentLayer->IndexDynamicMaskMap!=NULL && DynamicMaskMap!=NULL){
		MatrixBuffCopy(DynamicMaskMap	,DynamicMaskMapXByte,DynamicMaskMapYLen
					,(const BYTE **)ParentLayer->IndexDynamicMaskMap ,ParentLayer->IndexDynamicMaskMapXByte,ParentLayer->IndexDynamicMaskMapYLen);
	}
	if(DynamicMaskMap!=NULL){
		for(AlgorithmItemPointerList *p=MaskLinkedItems.GetFirst();p!=NULL;p=p->GetNext()){
			BlockItem	*BI=(BlockItem *)p->GetItem();
			int	ShiftByAlignmentX,ShiftByAlignmentY;
			BI->GetShiftByAlignemnt(ShiftByAlignmentX,ShiftByAlignmentY);
			int	sx,sy;
			BI->GetCurrentResult()->GetTotalShifted(sx,sy);
			BI->FLineBeforeShrink.MakeBitData(DynamicMaskMap,sx,sy,DynamicMaskMapXByte*8,DynamicMaskMapYLen);
		}
		ParentLayer->DynamicMaskMap		=DynamicMaskMap;
		ParentLayer->DynamicMaskMapXByte=DynamicMaskMapXByte;
		ParentLayer->DynamicMaskMapYLen	=DynamicMaskMapYLen;
	}
	else{
		ParentLayer->DynamicMaskMap		=ParentLayer->IndexDynamicMaskMap;
		ParentLayer->DynamicMaskMapXByte=ParentLayer->IndexDynamicMaskMapXByte;
		ParentLayer->DynamicMaskMapYLen	=ParentLayer->IndexDynamicMaskMapYLen;
	}
}
ExeResult	ExecutablePointerList::ExecuteProcessing		(int ExeID ,bool ThreadMode)
{
	MakeDynamicMask();

	LayersBase	*Base=ParentLayer->GetLayersBase();
	DWORD	StartMilisec=ParentLayer->GetLayersBase()->GetStartInspectionTimeMilisec();
	int		MaxInspectMilisec=ParentLayer->GetParamGlobal()->MaxInspectMilisec;
	DWORD	NowTime=::GetComputerMiliSec();
	int	Counter=0;
	ExeResult	Ret=_ER_true;
	bool	Enabled=true;
	if(ParentLayer->GetParamGlobal()->CalcSingleThread==false && ItemPointer.GetCount()>20){

		AlgorithmItemPointerList **pDim=new AlgorithmItemPointerList *[ItemPointer.GetCount()];
		int	RIndex=0;
		for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;p=p->GetNext()){
			pDim[RIndex]=p;
			RIndex++;
		}
		#pragma omp parallel 
		{
			#pragma omp for schedule(dynamic)
			for(int h=0;h<RIndex;h++){
				if((h&0xff)==0){
					NowTime=::GetComputerMiliSec();
				}
				AlgorithmItemPointerList *p=pDim[h];
				if(Enabled==true){
					if(ParentLayer->GetNGCounter()>ParentLayer->GetParamGlobal()->MaxNGCountsPerCam){
						Enabled=false;
						AlgorithmItemRoot	*Item	=p->GetItem();
						ResultInItemRoot	*Result	=Item->GetCurrentResult();
						ResultInspection	*R=Result->GetResultInspection();
						R->SetMaxErrorBreak(true);
					}
					else if(NowTime-StartMilisec>MaxInspectMilisec){
						Enabled=false;
						AlgorithmItemRoot	*Item	=p->GetItem();
						ResultInItemRoot	*Result	=Item->GetCurrentResult();
						ResultInspection	*R=Result->GetResultInspection();
						R->SetTimeOutBreak(true);
					}
					else{
						AlgorithmItemRoot	*Item	=p->GetItem();
						ResultInItemRoot	*Result	=Item->GetCurrentResult();

						Result->SetAlgorithmItem(Item);
						ExeResult	RR=Item->ExecuteProcessing	(ExeID ,omp_get_thread_num(),Result);
						if(RR!=_ER_true){
							Ret=RR;
						}
						#ifdef _MSC_VER
						if(Item->GetParamGlobal()->DebugLevel>=2){
							if(_CrtCheckMemory()==false){
								ErrorOccurs();
							}
						}
						#endif
						if(Result->GetError()>=2){
							if(Base->GetResultFromAlgorithm()==0){
								Base->SetResultFromAlgorithm(1);
							}
						}
						ParentLayer->IncrementNGCounterWithMutex(Result->GetError());
					}
				}
			}
		}
		delete	[]pDim;
	}
	else{
		for(AlgorithmItemPointerList *p=ItemPointer.GetFirst();p!=NULL;p=p->GetNext()){
			if((Counter&0xff)==0){
				NowTime=::GetComputerMiliSec();
			}
			Counter++;
			if(Enabled==true){
				if(ParentLayer->GetNGCounter()>ParentLayer->GetParamGlobal()->MaxNGCountsPerCam){
					Enabled=false;
					AlgorithmItemRoot	*Item	=p->GetItem();
					ResultInItemRoot	*Result	=Item->GetCurrentResult();
					ResultInspection	*R=Result->GetResultInspection();
					R->SetMaxErrorBreak(true);
				}
				else if(NowTime-StartMilisec>MaxInspectMilisec){
					Enabled=false;
					AlgorithmItemRoot	*Item	=p->GetItem();
					ResultInItemRoot	*Result	=Item->GetCurrentResult();
					ResultInspection	*R=Result->GetResultInspection();
					R->SetTimeOutBreak(true);
				}
				else{
					AlgorithmItemRoot	*Item=p->GetItem();
					ResultInItemRoot	*Result=Item->GetCurrentResult();
					Result->SetAlgorithmItem(Item);
					ExeResult	RR=Item->ExecuteProcessing	(ExeID ,0,Result);
					if(RR!=_ER_true){
						Ret=RR;
					}

					/*
					if(Item->GetInvertLogic()==true){
						if(Result->GetError()==1){
							Result->SetError(2);
						}
						else if(Result->GetError()>=2){
							Result->SetError(1);
						}
						if(Result->GetPosListFirst()==NULL){
							int	cx,cy;
							Item->GetCenter(cx,cy);
							Result->GetPosList().AppendList(new ResultPosList(cx,cy));
						}
					}
					*/

					#ifdef _MSC_VER
					if(Item->GetParamGlobal()->DebugLevel>=2){
						if(_CrtCheckMemory()==false){
							ErrorOccurs();
						}
					}
					#endif
					ParentLayer->IncrementNGCounterWithMutex(Result->GetError());
				}
			}
		}
	}
	return Ret;
}
bool	ExecutablePointerList::IsLinkedToMask(AlgorithmItemRoot *Item)
{
	if(MaskLinkedLibList.IsInclude(Item->GetLibID())==true)
		return true;
	return false;
}

void	ExecutablePointerContainer::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInLayerRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	SplitAgain:;
	for(ExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		ExecutablePointerContainer ChildFormer(ParentLayer),ChildLater(ParentLayer);
		E->SplitSubtraction(ChildFormer,ChildLater);
		ExecutablePointerList	*k;
		bool	RetryFlag=false;
		while((k=ChildFormer.GetFirst())!=NULL){
			ChildFormer.RemoveList(k);
			InsertList(0,k);
			RetryFlag=true;
		}
		while((k=ChildLater.GetFirst())!=NULL){
			ChildLater.RemoveList(k);
			AppendList(k);
		}

		if(RetryFlag==true){
			goto SplitAgain;
		}
	}
	for(ExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		E->ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	}
}
void		ExecutablePointerContainer::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	for(ExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		E->ExecuteStartByInspection(ExeID ,Res);
	}
}
ExeResult	ExecutablePointerContainer::ExecuteProcessing		(int ExeID ,bool ThreadMode)
{
	ExeResult	Ret=_ER_true;
	for(ExecutablePointerList *E=GetFirst();E!=NULL;E=E->GetNext()){
		ExeResult	tRet;
		if((tRet=E->ExecuteProcessing(ExeID ,ThreadMode))!=_ER_true){
			Ret=tRet;
		}
	}
	return Ret;
}
bool	ExecutablePointerContainer::IsLinkedToMask(AlgorithmItemRoot *Item)
{
	for(ExecutablePointerList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->IsLinkedToMask(Item)==true)
			return true;
	}
	return false;
}
ExecutablePointerList	*ExecutablePointerContainer::FindItem(AlgorithmItemRoot *Item)
{
	for(ExecutablePointerList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ItemPointer.IsExist(Item)==true)
			return p;
	}
	return NULL;
}

//===========================================================================================
BlockInLayerForItemBitImage::BlockInLayerForItemBitImage(void)
{
	LibID	=-1;
	Bmp		=NULL;
	BmpXByte=0;
	BmpYLen	=0;
}
BlockInLayerForItemBitImage::~BlockInLayerForItemBitImage(void)
{
	if(Bmp!=NULL){
		DeleteMatrixBuff(Bmp,BmpYLen);
		LibID	=-1;
		Bmp		=NULL;
		BmpXByte=0;
		BmpYLen	=0;
	}
}

BlockInLayerForItemBitImage	*BlockInLayerForItemBitImageContainer::FindByLibID(int LibID)
{
	for(BlockInLayerForItemBitImage *f=GetFirst();f!=NULL;f=f->GetNext()){
		if(f->LibID==LibID)
			return f;
	}
	return NULL;
}

//===========================================================================================

BlockInLayer::BlockInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLI(parent)
	,ExecutableContainer(this)
{
	PickupBmp=NULL;
	PickupBmpYLen=0;
	int	ThreadNumb;
	IndexDynamicMaskMap		=NULL;
	IndexDynamicMaskMapXByte=0;
	IndexDynamicMaskMapYLen	=0;
	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
	#pragma omp parallel                             
	{             
		ThreadNumb=omp_get_num_threads();
	}
	SWayListPerCPU=new SearchWayList[ThreadNumb];
	NoBrightnessInMaster=false;
	ModeParallel.ModeParallelExecuteInitialAfterEdit	=true;
}
BlockInLayer::~BlockInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
	delete	[]SWayListPerCPU;
	IndexDynamicMaskMap		=NULL;		//This is only pointer. So memory doesn't leak
	IndexDynamicMaskMapXByte=0;
	IndexDynamicMaskMapYLen	=0;

	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}
bool		BlockInLayer::AppendItem(AlgorithmItemRoot *item)
{
	/*
	AlgorithmLibrary	*LibP=GetParentBase()->GetLibraryContainer()->CreateNew();
	if(GetParentBase()->GetLibraryContainer()->GetLibrary(item->GetLibID(),*LibP)==true){
		if(LibP->HasGenLayer(GetLayer())==true){
			delete	LibP;
			return AlgorithmInLayerPLI::AppendItem(item);
		}
		delete	LibP;
		return false;
	}
	delete	LibP;
	*/
	AlgorithmLibraryContainer	*LibContainer=GetParentBase()->GetLibraryContainer();
	if(item->GetLibID()>=0){
		AlgorithmLibraryLevelContainer	*LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		if(LibP==NULL){
			GetParentBase()->LoadAllManagedCacheLib();
			LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
		}
		if(LibP!=NULL){
			if(LibP->HasGenLayer(GetLayer())==true){
				return AlgorithmInLayerPLI::AppendItem(item);
			}
			return false;
		}
		else{	//Register temporary library
			if(LibContainer!=NULL){
				LibP=new AlgorithmLibraryLevelContainer(LibContainer);
				BlockLibrary	*b=dynamic_cast<BlockLibrary *>(LibP->GetLibrary());
				LibP->SetLibID(item->GetLibID());
				LibP->SetLibName(/**/"Deleted-Once");
				item->GetThresholdBaseWritable()->ToLibrary(b);
				LibContainer->SaveNewWithLibID(*LibP);
				delete	b;
				GetParentBase()->LoadAllManagedCacheLib();
				LibP=GetParentBase()->FindLibFromManagedCacheLib(item->GetLibID());
				if(LibP->HasGenLayer(GetLayer())==true){
					return AlgorithmInLayerPLI::AppendItem(item);
				}
				return false;
			}
		}
	}
	return AlgorithmInLayerPLI::AppendItem(item);
}

bool		BlockInLayer::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}

bool		BlockInLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	return AlgorithmInLayerPLI::AppendItemFromLoad(item);
}

bool		BlockInLayer::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	return AlgorithmInLayerPLI::AppendItem(item,itemID);
}

void	BlockInLayer::CreatePickupBmpBuff(void)
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

bool	BlockInLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
void	BlockInLayer::PickupTest(BlockLibrary &LibData)
{
	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());
	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());

	AlgorithmLibraryContainer	*LibContainer=GetParentBase()->GetLibraryContainer();
	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(LibContainer);
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
		BlockLibrary	*BLib=(BlockLibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline;
		if(BLib->GenerationCategory==BlockLibrary::_AutoSetting_OTHERMASK
		|| BLib->GenerationCategory==BlockLibrary::_AutoSetting_SURROUND){
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

	CreatePickupBmpBuff();

	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);

	bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibData.GetLibID());
	bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&LibData,NULL);
	if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
		if(GetMasterBuff().IsNull()==false){
			LibData.MakePickupTest(GetPage()
				,GetMasterBuff()
				,MaskMap.GetBitMap() ,(const BYTE **)LastOcupyMap
				,PickupBmp,NULL
				,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
				,((BlockBase *)GetParentBase())->OmitZoneDot);
		}
		else if(GetTargetBuff().IsNull()==false){
			LibData.MakePickupTest(GetPage()
				,GetTargetBuff()
				,MaskMap.GetBitMap(),(const BYTE **)LastOcupyMap
				,PickupBmp,NULL
				,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
				,((BlockBase *)GetParentBase())->OmitZoneDot);	
		}
	}
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
}

ExeResult	BlockInLayer::ExecuteInitialAfterEdit	(int ExeID 
													,ResultInLayerRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{	
	IndexDynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	IndexDynamicMaskMapXByte=GetDataInPage()->GetDynamicMaskMapXByte();
	IndexDynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	DynamicMaskMap		=IndexDynamicMaskMap;
	DynamicMaskMapXByte	=IndexDynamicMaskMapXByte;
	DynamicMaskMapYLen	=IndexDynamicMaskMapYLen;

	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	if(BBase->RentalZone!=0){
		QByteArray	Something;
		ReqRentalItem(Something);
	}
	else{
		ClearRentalItem();
	}
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI *NextL=L->GetNext();
		if(L->GetArea().GetPatternByte()<=2){
			RemoveItem(L);
			delete	L;
		}
		L=NextL;
	}

	ItemBitImages.RemoveAll();
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		BlockItem	*Item=dynamic_cast<BlockItem *>(L);
		if(Item!=NULL){
			const	BlockThreshold	*RThr=Item->GetThresholdR(GetLayersBase());
			if((RThr->ThreshouldBag.PointMove.ModeMatchPosition==true
			 || RThr->ThreshouldBag.PointMove.ModeMatchPositionBW==true)){
				BlockInLayerForItemBitImage *B=ItemBitImages.FindByLibID(L->GetLibID());
				if(B==NULL){
					B=new BlockInLayerForItemBitImage();
					B->LibID	=L->GetLibID();
					B->BmpXByte	=(GetDotPerLine()+7)/8;
					B->BmpYLen	=GetMaxLines();
					B->Bmp		=MakeMatrixBuff(B->BmpXByte,B->BmpYLen);
					MatrixBuffClear(B->Bmp ,0 ,B->BmpXByte,B->BmpYLen);
					ItemBitImages.AppendList(B);
				}
				BlockLibrary	*LibP=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Item->GetLibID());
				if(LibP==NULL){
					GetParentBase()->LoadAllManagedCacheLib();
					LibP=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Item->GetLibID());
				}
				if(LibP!=NULL){
					Item->MakeFLineBeforeShrink(*LibP);
				}
				Item->FLineBeforeShrink.MakeBitData(B->Bmp,0,0,GetDotPerLine(),GetMaxLines());
			}
		}
	}

	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);

	RevivedGroup.RemoveAll();
	AlgorithmBasePointerContainer Bases;
	GetLayersBase()->GetAlgorithmByType(Bases ,AlgorithmBit_TypeAlignment);
	if(Bases.IsEmpty()==false){
		AlgorithmBase	*ABase=Bases.GetFirst()->GetAlgorithmBase();
		CmdGetAlignmentAreas	Cmd(GetLayersBase());
		int		Page=GetPage();
		ABase->GetPageData(Page)->TransmitDirectly(&Cmd);

		int	N=Cmd.Areas.GetCount();
		for(int i=0;i<N;i++){
			RevivedGroup.AppendList(new AlgorithmItemPointerLCList(this));
		}
		for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
			int	R=0;
			for(FlexAreaPointerList *a=Cmd.Areas.GetFirst();a!=NULL;a=a->GetNext(),R++){
				if(L->GetArea().CheckOverlap(a->GetArea())==true){
					RevivedGroup[R]->Add(L);
					break;
				}
			}
		}
	}
	for(AlgorithmItemPointerLCList *c=RevivedGroup.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteInitialAfterEdit(EInfo);
	}
	double	AddedCenterBright=0;
	int		AdddedCounter=0;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		BlockItem	*Item=dynamic_cast<BlockItem *>(L);
		if(Item!=NULL){
			if(Item->CenterBright!=0){
				AddedCenterBright+=Item->CenterBright;
				AdddedCounter++;
			}
		}
	}
	if(AdddedCounter!=0){
		int	AvrBrightness=AddedCenterBright/AdddedCounter;
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			BlockItem	*Item=dynamic_cast<BlockItem *>(L);
			if(Item!=NULL){
				if(Item->CenterBright==0){
					Item->CenterBright=AvrBrightness;
				}
			}
		}
	}

	IntList		MatchLineLibIDs;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		BlockItem	*Item=dynamic_cast<BlockItem *>(L);
		if(Item->UseMatchLine()==true){
			if(MatchLineLibIDs.IsInclude(Item->GetLibID())==false){
				MatchLineLibIDs.Add(Item->GetLibID());
			}
		}
	}
	GroupForSearch.RemoveAll();
	for(IntClass *c=MatchLineLibIDs.GetFirst();c!=NULL;c=c->GetNext()){
		MakeGroup(c->GetValue(),EInfo);
	}

	ItemBitImages.RemoveAll();


	ExecutablePointerList	*W=new ExecutablePointerList();
	W->ParentLayer	=this;
	W->Container	=&ExecutableContainer;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		W->ItemPointer.Add(L);
	}
	ExecutableContainer.RemoveAll();
	ExecutableContainer.AppendList(W);
	ExecutableContainer.ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	return Ret;
}

void	AlgorithmItemPointerLCList::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	MinX=99999999;
	MinY=99999999;
	MaxX=-9999999;
	MaxY=-99999999;

	for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){
		int	x1,y1,x2,y2;
		a->GetItem()->GetArea().GetXY(x1,y1,x2,y2);
		if(MinX>x1)
			MinX=x1;
		if(MinY>y1)
			MinY=y1;
		if(MaxX<x2)
			MaxX=x2;
		if(MaxY<y2)
			MaxY=y2;
	}
}
void	AlgorithmItemPointerLCList::ExecuteProcessingRevived(int Step ,int Shift ,int RevisedRotation)
{
	bool	ReviveOKAgain	=((BlockBase *)(Parent->GetParentBase()))->ReviveOKAgain;
	int	Cx=(MinX+MaxX)/2;
	int	Cy=(MinY+MaxY)/2;

	double	Len=hypot(MaxX-MinX,MaxY-MinY)/2;
	if(Len<1.0)
		return;
	double	SitaStep=atan(1.0/Len);

	int	MinNGCount=99999999;
	int	MinS=0;
	int	MinDx=0;
	int	MinDy=0;

	int	N=AlgorithmItemPointerListContainer::GetCount();
	AlgorithmItemPointerList **Dim=new AlgorithmItemPointerList*[N];
	AlgorithmItemPointerList **NGDim=new AlgorithmItemPointerList*[N];
	int	NGNumb=0;
	for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetItem()->GetCurrentResult()->IsOk()==false){
			NGDim[NGNumb]=a;
			NGNumb++;
		}
	}
	int	k=0;
	for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetItem()->GetCurrentResult()->IsOk()==true){
			int	pcx,pcy;
			a->GetItem()->GetCenter(pcx,pcy);
			for(int j=0;j<NGNumb;j++){
				AlgorithmItemPointerList *b=NGDim[j];
				int	qcx,qcy;
				b->GetItem()->GetCenter(qcx,qcy);
				if(abs(pcx-qcx)+abs(pcy-qcy)<a->GetItem()->GetDotPerLine()/4){
					Dim[k]=a;
					k++;
					break;
				}
			}
		}
	}
	for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetItem()->GetCurrentResult()->IsOk()==false){
			Dim[k]=a;
			k++;
		}
	}
	N=k;

	for(int s=-RevisedRotation;s<=RevisedRotation;s++){
		double	MCos=cos(s*Step*SitaStep);
		double	MSin=sin(s*Step*SitaStep);
		for(int dy=-Shift;dy<=Shift;dy+=Step){
			for(int dx=-Shift;dx<=Shift;dx+=Step){
				int	NGCount=0;

				//for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){

				//#pragma omp parallel
				//{
				//	#pragma omp for
					for(int i=0;i<N;i++){
						AlgorithmItemPointerList *a=Dim[i];
						int	qx,qy;
						a->GetItem()->GetCenter(qx,qy);
						int	Rx=(qx-Cx)*MCos+(qy-Cy)*MSin+Cx-qx;
						int	Ry=-(qx-Cx)*MSin+(qy-Cy)*MCos+Cy-qy;
					
						BlockItem	*BItem=dynamic_cast<BlockItem *>(a->GetItem());
						if(BItem!=NULL){
							int	mx,my;
							if(BItem->AVector!=NULL){
								mx=BItem->AVector->ShiftX;
								my=BItem->AVector->ShiftY;
							}
							else{
								AlignmentPacket2D	V;
								int	cx,cy;
								BItem->GetCenter(cx,cy);
								V.PosXOnTarget=cx;
								V.PosYOnTarget=cy;
								V.ShiftX=0;
								V.ShiftY=0;
								BItem->GetAlignmentForProcessing(V);
								mx=V.ShiftX;
								my=V.ShiftY;
							}
							bool	h=BItem->ExecuteProcessingSimple(mx+dx+Rx,my+dy+Ry);
							if(h==false){
								//#pragma omp atomic
								NGCount++;
							}
						}
					}
				//}
				if(MinNGCount>NGCount){
					MinNGCount=NGCount;
					MinS=s;
					MinDx=dx;
					MinDy=dy;
				}
			}
		}
	}
	delete	[]Dim;
	delete	[]NGDim;

	double	iCos=cos(MinS*Step*SitaStep);
	double	iSin=sin(MinS*Step*SitaStep);
	for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){
		if((a->GetItem()->GetCurrentResult()->IsOk()==false && ReviveOKAgain==false)
		|| ReviveOKAgain==true){
			int	qx,qy;
			a->GetItem()->GetCenter(qx,qy);
			int	Rx=(qx-Cx)*iCos+(qy-Cy)*iSin+Cx-qx;
			int	Ry=-(qx-Cx)*iSin+(qy-Cy)*iCos+Cy-qy;
			BlockItem	*BItem=dynamic_cast<BlockItem *>(a->GetItem());
			if(BItem!=NULL){
				int	mx,my;
				if(BItem->AVector!=NULL){
					mx=BItem->AVector->ShiftX;
					my=BItem->AVector->ShiftY;
				}
				else{
					AlignmentPacket2D	V;
					int	cx,cy;
					BItem->GetCenter(cx,cy);
					V.PosXOnTarget=cx;
					V.PosYOnTarget=cy;
					V.ShiftX=0;
					V.ShiftY=0;
					BItem->GetAlignmentForProcessing(V);
					mx=V.ShiftX;
					my=V.ShiftY;
				}
				BItem->ExecuteProcessingCalc(0,a->GetItem()->GetCurrentResult(),mx+MinDx+Rx,my+MinDy+Ry);
			}
		}
	}
}
int		AlgorithmItemPointerLCList::GetNGCount(void)
{
	int	NGCount=0;
	for(AlgorithmItemPointerList *a=AlgorithmItemPointerListContainer::GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetItem()->GetCurrentResult()->IsOk()==false){
			NGCount++;
		}
	}
	return NGCount;
}
ExeResult	BlockInLayer::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteStartByInspection(ExeID ,Res);
	ExecutableContainer.ExecuteStartByInspection(ExeID ,Res);
	return Ret;
}
ExeResult	BlockInLayer::ExecuteProcessing(int ExeID ,ResultInLayerRoot *Res)
{
	IndexDynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	IndexDynamicMaskMapXByte=GetDataInPage()->GetDynamicMaskMapXByte();
	IndexDynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	if(GetMasterBuff().IsNull()!=true){
		BYTE	*s=GetMasterBuff().GetY(GetMaxLines()/2);
		int	x;
		for(x=0;x<GetDotPerLine();x++){
			if(s[x]!=0){
				break;
			}
		}
		if(x>=GetDotPerLine()){
			NoBrightnessInMaster=true;
		}
		else{
			NoBrightnessInMaster=false;
		}
	}
	else{
		NoBrightnessInMaster=true;
	}
	MatchBeforeExecuteProcessing();

	//return AlgorithmInLayerPLI::ExecuteProcessing(Res ,pInspectionData);
	return ExecutableContainer.ExecuteProcessing	(ExeID ,true);
}

ExeResult	BlockInLayer::ExecuteProcessingRevived(int ExeID ,ResultInLayerRoot *Res)
{
	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	int		Step	=BBase->RevivedStep;
	int		Shift	=BBase->RevivedShift;
	int		RevisedRotation=BBase->RevisedRotation;
	if(Shift>0 && Step>0){
		for(AlgorithmItemPointerLCList *c=RevivedGroup.GetFirst();c!=NULL;c=c->GetNext()){
			int	NGCount=c->GetNGCount();
			if(NGCount!=0){
				c->ExecuteProcessingRevived(Step ,Shift,RevisedRotation);
			}
		}
	}
	return _ER_true;
}

void	BlockInLayer::MakeGroup(int LibID,ExecuteInitialAfterEditInfo &EInfo)
{
	BlockLibrary	*LibP=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(LibID);
	if(LibP==NULL){
		GetParentBase()->LoadAllManagedCacheLib();
		LibP=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(LibID);
	}
	if(LibP==NULL)
		return;
	int	AreaLen=LibP->LimitBlockSize*4;
	int	XDivNumb=GetDotPerLine()/AreaLen;
	if(XDivNumb==0)
		XDivNumb=1;
	int	YDivNumb=GetMaxLines()  /AreaLen;
	if(YDivNumb==0)
		YDivNumb=1;
	int	XAreaLen=(GetDotPerLine()+XDivNumb-1)/XDivNumb;
	int	YAreaLen=(GetMaxLines()  +YDivNumb-1)/YDivNumb;

	AlgorithmItemPointerListContainer	*ItemsInArea[100000];
	for(int yn=0;yn<YDivNumb;yn++){
		ItemsInArea[yn]=new AlgorithmItemPointerListContainer[XDivNumb];
	}
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetLibID()==LibID){
			double	cx,cy;
			L->GetCenter(cx,cy);
			int	ix=cx/XAreaLen;
			int	iy=cy/YAreaLen;
			ItemsInArea[iy][ix].AppendList(new AlgorithmItemPointerList(L));
		}
	}
	for(int yn=0;yn<YDivNumb;yn++){
		for(int xn=0;xn<XDivNumb;xn++){
			if(ItemsInArea[yn][xn].GetCount()<5){
				if(0<xn && ItemsInArea[yn][xn-1].GetCount()>=5)
					ItemsInArea[yn][xn-1].AddMove(ItemsInArea[yn][xn]);
				else if(0<yn && ItemsInArea[yn-1][xn].GetCount()>=5)
					ItemsInArea[yn-1][xn].AddMove(ItemsInArea[yn][xn]);
				else if((xn+1)<XDivNumb && ItemsInArea[yn][xn+1].GetCount()>=5)
					ItemsInArea[yn][xn+1].AddMove(ItemsInArea[yn][xn]);
				else if((yn+1)<YDivNumb && ItemsInArea[yn+1][xn].GetCount()>=5)
					ItemsInArea[yn+1][xn].AddMove(ItemsInArea[yn][xn]);
			}
		}
	}
	for(int yn=0;yn<YDivNumb;yn++){
		for(int xn=0;xn<XDivNumb;xn++){
			if(ItemsInArea[yn][xn].GetCount()>0){
				AlgorithmItemPointerListContainerContainer	*a=new AlgorithmItemPointerListContainerContainer(this,LibID);
				a->ItemPointers.Move(ItemsInArea[yn][xn]);
				GroupForSearch.AppendList(a);
			}
		}
	}
	AlgorithmItemPointerListContainerContainer *L;
	#pragma omp parallel
	#pragma omp single private(L)
	for(L=GroupForSearch.GetFirst();L!=NULL;L=L->GetNext()){
		#pragma omp task
		L->MakeLinePointers(this,EInfo);
	}
	/*
	for(AlgorithmItemPointerListContainerContainer *L=GroupForSearch.GetFirst();L!=NULL;L=L->GetNext()){
		L->MakeLinePointers(this);
	}
	*/

	for(int yn=0;yn<YDivNumb;yn++){
		delete	[]ItemsInArea[yn];
	}
}

static	int	SortMTableFunc(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(*pa>*pb)
		return -1;
	if(*pa<*pb)
		return 1;
	return 0;
}

void	BlockInLayer::MatchBeforeExecuteProcessing(void)
{
	ImageBuffer &DBuff=GetTargetBuff();

	if(GetParamGlobal()->CalcSingleThread==false){
		AlgorithmItemPointerListContainerContainer *L; 
		#pragma omp parallel 
		#pragma omp single private(L) 
		for(L=GroupForSearch.GetFirst();L!=NULL;L=L->GetNext()){
			#pragma omp task 
			{ 
				int		CommonMoveDot=0;
				bool	ModeUseGlobalLine=true;
				if(L->ItemPointers.GetFirst()!=NULL){
					BlockItem	*B=dynamic_cast<BlockItem *>(L->ItemPointers.GetFirst()->GetItem());
					const	BlockThreshold	*RThr=B->GetThresholdR(GetLayersBase());
					CommonMoveDot		=RThr->ThreshouldBag.CommonMoveDot;
					ModeUseGlobalLine	=RThr->ThreshouldBag.PointMove.ModeUseGlobalLine;
				}
				int	MaxDx=0;
				int	MaxDy=0;

				L->Match(DBuff,CommonMoveDot,MaxDx,MaxDy,ModeUseGlobalLine);

				for(AlgorithmItemPointerList *P=L->ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
					BlockItem	*B=dynamic_cast<BlockItem *>(P->GetItem());
					B->ShiftX=MaxDx;
					B->ShiftY=MaxDy;
				}
			}
		}
	}
	else{
		for(AlgorithmItemPointerListContainerContainer *L=GroupForSearch.GetFirst();L!=NULL;L=L->GetNext()){
			for(AlgorithmItemPointerList *P=L->ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
				if(P->GetItem()->GetID()==DbgID && GetLayer()==DbgLayer){
					DbgNumer++;
				}
			}

			int		CommonMoveDot=0;
			bool	ModeUseGlobalLine=true;
			if(L->ItemPointers.GetFirst()!=NULL){
				BlockItem	*B=dynamic_cast<BlockItem *>(L->ItemPointers.GetFirst()->GetItem());
				const	BlockThreshold	*RThr=B->GetThresholdR(GetLayersBase());
				CommonMoveDot		=RThr->ThreshouldBag.CommonMoveDot;
				ModeUseGlobalLine	=RThr->ThreshouldBag.PointMove.ModeUseGlobalLine;
			}
			int	MaxDx=0;
			int	MaxDy=0;

			L->Match(DBuff,CommonMoveDot,MaxDx,MaxDy,ModeUseGlobalLine);

			for(AlgorithmItemPointerList *P=L->ItemPointers.GetFirst();P!=NULL;P=P->GetNext()){
				BlockItem	*B=dynamic_cast<BlockItem *>(P->GetItem());
				B->ShiftX=MaxDx;
				B->ShiftY=MaxDy;
			}
		}
	}
}

AlgorithmItemPointerListContainerContainer	*BlockInLayer::FindGroup(int ItemID)
{
	for(AlgorithmItemPointerListContainerContainer *L=GroupForSearch.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsItemIncluded(ItemID)==true){
			return L;
		}
	}
	return NULL;
}

void	BlockInLayer::GenerateBlocks(BlockLibrary *LibDim[],int LibDimNumb)
{
	UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(this,&BlockInLayer::UndoGenerateItems);
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

	CreatePickupBmpBuff();
	CommonMoveIDList.RemoveAll();
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

	AlgorithmLibraryContainer	*LibContainer=GetParentBase()->GetLibraryContainer();
	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(LibContainer);
			if(LibContainer->GetLibrary(L->GetLibID() ,*Lib)==true){
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
		BlockLibrary	*BLib=(BlockLibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline;
		if(BLib->GenerationCategory==BlockLibrary::_AutoSetting_OTHERMASK
		|| BLib->GenerationCategory==BlockLibrary::_AutoSetting_SURROUND){
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

		bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibDim[i]->GetLibID());
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,LibDim[i],NULL);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){

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
				,XByte ,GetDotPerLine(),GetMaxLines()
				,((BlockBase *)GetParentBase())->OmitZoneDot);
			if(LibDim[i]->GenerationMode.LeftPickup==false){
				NPListPack<AlgorithmItemPLI>	TmpBlockData;
				LibDim[i]->MakeBlock(GetPage()
					,CurrentMap,LastOcupyMap
					,XByte ,GetDotPerLine(),GetMaxLines()
					,TmpBlockData);
				if(LibDim[i]->PointMove.ModeCommonMovable==true){
					int	CommonMoveID=CommonMoveIDList.GetCount()+1;
					CommonMoveIDList.Add(CommonMoveID);
					for(AlgorithmItemPLI *a=TmpBlockData.GetFirst();a!=NULL;a=a->GetNext()){
						BlockItem	*b=(BlockItem *)a;
						b->GetThresholdW()->ThreshouldBag.CommonMoveID=CommonMoveID;
					}
				}
				AlgorithmItemPLI	*q;

				while((q=TmpBlockData.GetFirst())!=NULL){
					TmpBlockData.RemoveList(q);
					if(AppendItem(q)==true){
						AddedItemIDList.Add(q->GetID());
					}
					((BlockItem *)q)->MakeFLineBeforeShrink(*LibDim[i]);
				}
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
bool	BlockInLayer::Save(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Save(f)==false)
		return false;
	if(CommonMoveIDList.Save(f)==false)
		return false;
	return true;
}
bool	BlockInLayer::Load(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Load(f)==false)
		return false;
	if(CommonMoveIDList.Load(f)==false)
		return false;
	return true;
}

void	BlockInLayer::AckRentalItem(int ForOtherGlobalPage ,QByteArray &Something , NPListPack<AlgorithmItemPLI> &_RentalData)
{
	BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
	int	OwnGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	XYData	*p=GetLayersBase()->GetGlobalOutlineOffset(OwnGlobalPage);
	int	RentalZone	=BBase->RentalZone;
	int	Wx1=p->x;
	int	Wy1=p->y;
	int	Wx2=p->x+GetDotPerLine();
	int	Wy2=p->y+GetMaxLines();

	XYData	*q=GetLayersBase()->GetGlobalOutlineOffset(ForOtherGlobalPage);
	int	Zx1=q->x-RentalZone;
	int	Zy1=q->y-RentalZone;
	int	Zx2=q->x+GetDotPerLine()+RentalZone;
	int	Zy2=q->y+GetMaxLines()+RentalZone;

	int	x1=max(Wx1,Zx1);
	int	y1=max(Wy1,Zy1);
	int	x2=min(Wx2,Zx2);
	int	y2=min(Wy2,Zy2);
	if(x1>=x2 || y1>=y2)
		return;

	x1-=p->x;
	y1-=p->y;
	x2-=p->x;
	y2-=p->y;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetArea().CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			BlockItem	*Bp=new BlockItem();
			*Bp=*L;
			_RentalData.AppendList(Bp);
		}
	}
}

void	BlockInLayer::AddRentalItem(int ItemID ,AlgorithmItemPLI *p)
{
	AlgorithmInLayerPLI::AddRentalItem(ItemID ,p);
}

void	BlockInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		BlockItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			BlockItem	*B=(BlockItem *)L;
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
				BlockItem	*B=(BlockItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestBlockPacket	*CmdClearTestBlockPacketVar=dynamic_cast<CmdClearTestBlockPacket *>(packet);
	if(CmdClearTestBlockPacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}
	CmdBlockInfoListPacket	*CmdBlockInfoListPacketVar=dynamic_cast<CmdBlockInfoListPacket *>(packet);
	if(CmdBlockInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			BlockInfoList	*a;
			for(a=CmdBlockInfoListPacketVar->BlockInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->BlockCount.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new BlockInfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					if(layer==GetLayer())
						a->BlockCount.Add(1);
					else
						a->BlockCount.Add(0);
				}
				CmdBlockInfoListPacketVar->BlockInfos->AppendList(a);
			}
		}
		return;
	}
	CmdGetBlockFromList	*CmdGetBlockFromListVar=dynamic_cast<CmdGetBlockFromList *>(packet);
	if(CmdGetBlockFromListVar!=NULL){
		BlockItem *Item=(BlockItem *)SearchIDItem(CmdGetBlockFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetBlockFromListVar->BlockInfoOnMouse=Item;
		return;
	}
	CmdCreateBlockItem	*CmdCreateBlockItemVar=dynamic_cast<CmdCreateBlockItem *>(packet);
	if(CmdCreateBlockItemVar!=NULL){
		CmdCreateBlockItemVar->Block=(BlockItem *)CreateItem(0);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		BlockItem *Item=(BlockItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);
			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
		}
		return;
	}
	CmdReqShrinkArea	*CmdReqShrinkAreaVar=dynamic_cast<CmdReqShrinkArea *>(packet);
	if(CmdReqShrinkAreaVar!=NULL){
		UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(this,&BlockInLayer::UndoShrinkArea);
		int32	ItemCount=GetItemCount();
		::Save(UPointer->GetWritePointer(),ItemCount);

		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				::Save(UPointer->GetWritePointer(),L->GetID());
				L->GetArea().Save(UPointer->GetWritePointer());
				L->ShrinkArea(CmdReqShrinkAreaVar->ShrinkDot);
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdGetUsedLibID	*CmdGetUsedLibIDVar=dynamic_cast<CmdGetUsedLibID *>(packet);
	if(CmdGetUsedLibIDVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(CmdGetUsedLibIDVar->LibIDs.IsInclude(L->GetLibID())==false){
				CmdGetUsedLibIDVar->LibIDs.Add(L->GetLibID());
			}
		}
		return;
	}
	CmdReqShrinkHalf	*CmdReqShrinkHalfVar=dynamic_cast<CmdReqShrinkHalf *>(packet);
	if(CmdReqShrinkHalfVar!=NULL){
		UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(this,&BlockInLayer::UndoShrinkArea);
		int32	ItemCount=GetItemCount();
		::Save(UPointer->GetWritePointer(),ItemCount);

		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				::Save(UPointer->GetWritePointer(),L->GetID());
				L->GetArea().Save(UPointer->GetWritePointer());
				L->ShrinkHalf();
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdReqExpandHalf	*CmdReqExpandHalfVar=dynamic_cast<CmdReqExpandHalf *>(packet);
	if(CmdReqExpandHalfVar!=NULL){
		UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(this,&BlockInLayer::UndoShrinkArea);
		int32	ItemCount=GetItemCount();
		::Save(UPointer->GetWritePointer(),ItemCount);

		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				::Save(UPointer->GetWritePointer(),L->GetID());
				L->GetArea().Save(UPointer->GetWritePointer());
				L->ExpandHalf();
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdSetNGSizeInBlock	*CmdSetNGSizeInBlockVar=dynamic_cast<CmdSetNGSizeInBlock *>(packet);
	if(CmdSetNGSizeInBlockVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==CmdSetNGSizeInBlockVar->LibID){
				BlockItem	*B=(BlockItem *)L;
				if(CmdSetNGSizeInBlockVar->BlockType==1)
					B->GetThresholdW()->ThreshouldBag.BOKDotL	=CmdSetNGSizeInBlockVar->NGSize;
				else if(CmdSetNGSizeInBlockVar->BlockType==2)
					B->GetThresholdW()->ThreshouldBag.BOKDotH	=CmdSetNGSizeInBlockVar->NGSize;
				else if(CmdSetNGSizeInBlockVar->BlockType==3)
					B->GetThresholdW()->ThreshouldBag.NOKDotL	=CmdSetNGSizeInBlockVar->NGSize;
				else if(CmdSetNGSizeInBlockVar->BlockType==4)
					B->GetThresholdW()->ThreshouldBag.NOKDotH	=CmdSetNGSizeInBlockVar->NGSize;
			}
		}
		return;
	}
	CmdSetSearchDotInBlock	*CmdSetSearchDotInBlockVar=dynamic_cast<CmdSetSearchDotInBlock *>(packet);
	if(CmdSetSearchDotInBlockVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==CmdSetSearchDotInBlockVar->LibID){
				BlockItem	*B=(BlockItem *)L;
				B->GetThresholdW()->ThreshouldBag.SelfSearch	=CmdSetSearchDotInBlockVar->SearchDot;
			}
		}
		return;
	}
	CmdUpdateBlockCommon	*CmdUpdateBlockCommonVar=dynamic_cast<CmdUpdateBlockCommon *>(packet);
	if(CmdUpdateBlockCommonVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==CmdUpdateBlockCommonVar->LibID){
				BlockItem	*B=(BlockItem *)L;
				B->SetThresholdFromCommon(&CmdUpdateBlockCommonVar->ThresholdInfo);
			}
		}
		return;
	}
	CmdGenerateBlockCommon	*CmdGenerateBlockCommonVar=dynamic_cast<CmdGenerateBlockCommon *>(packet);
	if(CmdGenerateBlockCommonVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			for(BlockLibraryWithThresholdList *a=CmdGenerateBlockCommonVar->Infos.GetFirst();a!=NULL;a=a->GetNext()){	
				if(L->GetLibID()==a->LibID){
					BlockItem	*B=(BlockItem *)L;
					B->SetThresholdFromCommon(&a->ThresholdInfo);
					break;
				}
			}
		}
		return;
	}
	CmdRemoveAllOriginalBlockItems	*CmdRemoveAllOriginalBlockItemsVar=dynamic_cast<CmdRemoveAllOriginalBlockItems *>(packet);
	if(CmdRemoveAllOriginalBlockItemsVar!=NULL){
		AlgorithmItemPointerListContainer Items;
		EnumOriginTypeItems((OriginType)CmdRemoveAllOriginalBlockItemsVar->GeneratedOrigin,Items);
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
			AlgorithmItemPointerList *NextP=a->GetNext();
			if(a->GetItem()->GetEditLocked()==true){
				Items.RemoveList(a);
				delete	a;
			}
			a=NextP;
		}
		RemoveItems(Items);
		return;
	}
	ChangeBlocksThresholdCommon	*ChangeBlocksThresholdCommonVar=dynamic_cast<ChangeBlocksThresholdCommon *>(packet);
	if(ChangeBlocksThresholdCommonVar!=NULL){
		SetThresholdBlockInfo	ThresholdInfo;
		QBuffer	Buff(&ChangeBlocksThresholdCommonVar->InfosData);
		Buff.open(QIODevice::ReadWrite);
		if(ThresholdInfo.Load(&Buff)==true){
			for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
				if(ChangeBlocksThresholdCommonVar->BlockLibID==L->GetLibID()){
					BlockItem	*B=(BlockItem *)L;
					B->SetThresholdFromCommon(&ThresholdInfo);
				}
			}
		}
		return;
	}
	CmdTryProcess	*CmdTryProcessVar=dynamic_cast<CmdTryProcess *>(packet);
	if(CmdTryProcessVar!=NULL){
		ResultInItemPLI	*Result	=new ResultInItemPLI();

		int32		SavedShiftX	=CmdTryProcessVar->BItemPoint->ShiftX;
		int32		SavedShiftY	=CmdTryProcessVar->BItemPoint->ShiftY;
		AlgorithmItemPointerListContainerContainer	*CC=FindGroup(CmdTryProcessVar->BItemPoint->GetID());
		if(CC!=NULL){
			ImageBuffer &DBuff=GetTargetBuff();
			int	CommonMoveDot=CmdTryProcessVar->BItemPoint->GetThresholdR(GetLayersBase())->ThreshouldBag.CommonMoveDot;
			int	MaxDx=0;
			int	MaxDy=0;
			CC->Match(DBuff,CommonMoveDot,MaxDx,MaxDy,CmdTryProcessVar->BItemPoint->GetThresholdW()->ThreshouldBag.PointMove.ModeUseGlobalLine);
			CmdTryProcessVar->BItemPoint->ShiftX=MaxDx;
			CmdTryProcessVar->BItemPoint->ShiftY=MaxDy;
		}
		
		bool	Masked=CmdTryProcessVar->BItemPoint->RewindDynamicMask(this);
		ExecutablePointerList	*E=ExecutableContainer.FindItem(CmdTryProcessVar->BItemPoint);
		if(E!=NULL){
			E->MakeDynamicMask();
		}
		CmdTryProcessVar->BItemPoint->ExecuteProcessing(0,0,Result);
		if(Masked==true){
			CmdTryProcessVar->BItemPoint->SetDynamicMask(this);		
		}
		if(Result->IsOk()==true)
			CmdTryProcessVar->OK=true;
		else
			CmdTryProcessVar->OK=false;
		delete	Result;
		CmdTryProcessVar->BItemPoint->ShiftX	=SavedShiftX;
		CmdTryProcessVar->BItemPoint->ShiftY	=SavedShiftY;
		return;
	}
}

void	BlockInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	for(AlgorithmItemPointerListContainerContainer *g=GroupForSearch.GetFirst();g!=NULL;g=g->GetNext()){
		g->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
	BlockDrawAttr	*BAttr=dynamic_cast<BlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==CmdBlockDrawModePacket::_LibTest){
			if(PickupBmp!=NULL){
				BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==CmdBlockDrawModePacket::_CreatedBlock){
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	BlockInLayer::UndoAppendManualItem(QIODevice *f)
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

void	BlockInLayer::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		BlockItem	*B=new BlockItem();
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
	GetParentBase()->ClearManagedCacheLib();
	for(AlgorithmItemPointerList *item=RemovedItems.GetFirst();item!=NULL;item=item->GetNext()){
		AppendItem(item->GetItem());
	}
}
void	BlockInLayer::UndoShrinkArea(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false)
		return;
	for(int i=0;i<ItemCount;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		FlexArea	A;
		if(A.Load(f)==false)
			return;
		AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
		if(Item!=NULL){
			Item->SetArea(A);
		}
	}
}

void	BlockInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		BlockItem	*BI=(BlockItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
void	BlockInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		BlockItem	*BI=(BlockItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}
void	BlockInLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		BlockItem	*a=dynamic_cast<BlockItem *>(k);
		if(a!=NULL){
			double	Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}
	}
}

bool	BlockInLayer::ExecuteAutoThresholdByAlgo(AlgorithmItemPointerListContainerByLibContainer &Items ,ParamAutoThreshold &executer)
{
	if(executer.HistID==Hist_BlockInspection_CenterBright){
		if(executer.ModeOneWork==true && executer.ModeMultiWork==true){
			for(AlgorithmItemPointerListContainerByLib *AL=Items.GetFirst();AL!=NULL;AL=AL->GetNext()){
				HistStepClass	CTable;
				CTable.Create(-255,255,1);
				for(AlgorithmItemPointerList *a=AL->Container.GetFirst();a!=NULL;a=a->GetNext()){
					HistgramByParamBase	*H=a->GetItem()->GetThresholdBaseWritable()->GetHistgramBase(Hist_BlockInspection_CenterBright);
					if(H!=NULL){
						H->AddTo(&CTable);
					}
				}
				double Avr , VAdd;
				if(CTable.GetAverageByTable(executer.AdoptRate ,Avr , VAdd)==true){
					for(AlgorithmItemPointerList *a=AL->Container.GetFirst();a!=NULL;a=a->GetNext()){
						BlockItem	*BI=(BlockItem *)a->GetItem();
						if(BI->GetThresholdW()->ThreshouldBag.PointMove.ModeAbsoluteBright==true){
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=Avr-ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=Avr+ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=Avr-ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=Avr+ceil(VAdd*executer.SigmaMultiply);
						}
						else if(BI->GetThresholdW()->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
							BI->GetThresholdW()->ThreshouldBag.RegularCenterBright	=BI->CenterBright+Avr;
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
						}
						else{
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
						}
					}
				}
			}
		}
		if(executer.ModeOneWork==false && executer.ModeMultiWork==true){
			for(AlgorithmItemPointerListContainerByLib *AL=Items.GetFirst();AL!=NULL;AL=AL->GetNext()){
				for(AlgorithmItemPointerList *a=AL->Container.GetFirst();a!=NULL;a=a->GetNext()){
					HistStepClass	CTable;
					CTable.Create(-255,255,1);
					HistgramByParamBase	*H=a->GetItem()->GetThresholdBaseWritable()->GetHistgramBase(Hist_BlockInspection_CenterBright);
					if(H!=NULL){
						H->AddTo(&CTable);
					}
					double Avr , VAdd;
					if(CTable.GetAverageByTable(executer.AdoptRate ,Avr , VAdd)==true){
						for(AlgorithmItemPointerList *a=AL->Container.GetFirst();a!=NULL;a=a->GetNext()){
							BlockItem	*BI=(BlockItem *)a->GetItem();
							if(BI->GetThresholdW()->ThreshouldBag.PointMove.ModeAbsoluteBright==true){
								BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=Avr-ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=Avr+ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=Avr-ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=Avr+ceil(VAdd*executer.SigmaMultiply);
							}
							else if(BI->GetThresholdW()->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
								BI->GetThresholdW()->ThreshouldBag.RegularCenterBright	=BI->CenterBright+Avr;
								BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
							}
							else{
								BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
								BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
							}
						}
					}
				}
			}
		}
		if(executer.ModeOneWork==true && executer.ModeMultiWork==false){
			for(AlgorithmItemPointerListContainerByLib *AL=Items.GetFirst();AL!=NULL;AL=AL->GetNext()){
				HistStepClass	CTable;
				CTable.Create(-255,255,1);
				for(AlgorithmItemPointerList *a=AL->Container.GetFirst();a!=NULL;a=a->GetNext()){
					HistgramByParamBase	*H=a->GetItem()->GetThresholdBaseWritable()->GetHistgramBase(Hist_BlockInspection_CenterBright);
					if(H!=NULL){
						H->AddTo(&CTable);
					}
				}
				double Avr , VAdd;
				if(CTable.GetAverageByTable(executer.AdoptRate ,Avr , VAdd)==true){
					for(AlgorithmItemPointerList *a=AL->Container.GetFirst();a!=NULL;a=a->GetNext()){
						BlockItem	*BI=(BlockItem *)a->GetItem();
						if(BI->GetThresholdW()->ThreshouldBag.PointMove.ModeAbsoluteBright==true){
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=Avr-ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=Avr+ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=Avr-ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=Avr+ceil(VAdd*executer.SigmaMultiply);
						}
						else if(BI->GetThresholdW()->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
							BI->GetThresholdW()->ThreshouldBag.RegularCenterBright	=BI->CenterBright+Avr;
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
						}
						else{
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.NBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthL=ceil(VAdd*executer.SigmaMultiply);
							BI->GetThresholdW()->ThreshouldBag.BBrightWidthH=ceil(VAdd*executer.SigmaMultiply);
						}
					}
				}
			}
		}
	}
	return true;
}
