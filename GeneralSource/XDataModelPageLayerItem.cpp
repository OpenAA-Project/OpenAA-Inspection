/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataModelPageLayerItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XPointer.h"
//#include "XAlignment.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XDataModelPageLayerItem.h"
#include "XCriticalFunc.h"
#include "XCrossObj.h"
#include"XModelPLICommander.h"
#include "XErrorMessage.h"
#include "XResultAnalizer.h"
#include "XDisplayImagePacket.h"
#include "XFileThread.h"
#include "XDataAlgorithmList.h"
#include "XDataAlgorithmConfirm.h"

//===========================================================================================================
void	AlgorithmItemPLI::SetItemID(void)
{	
	if(Parent!=NULL){
		ItemID=Parent->GetIncStartItemID();	
	}
}
XYData	AlgorithmItemPLI::GetOutlineOffset(void)	
{	
	if(GetDataInLayer()!=NULL){
		return *GetDataInLayer()->GetOutlineOffset();
	}
	XYData	d;
	return d;
}
AlgorithmBase			*AlgorithmItemPLI::GetParentBase(void)	const	
{	
	if(Parent==NULL){
		return NULL;
	}
	return Parent->GetParentBase();	
}
AlgorithmInPageRoot		*AlgorithmItemPLI::GetParentInPage(void)	const
{	
	if(Parent==NULL){
		return NULL;
	}
	return Parent->Parent;	
}
AlgorithmInLayerRoot	*AlgorithmItemPLI::GetParentInLayer(void)	const
{	
	return Parent;	
}
ImageBuffer				&AlgorithmItemPLI::GetMasterBuff(void)		
{	
	int	iMasterNo=GetMasterNo();
	if(iMasterNo<0){
		iMasterNo=0;
	}
	if(iMasterNo>=GetCountAllMasterBuff()){
		iMasterNo=GetCountAllMasterBuff()-1;
	}
	return(Parent->GetMasterBuff(iMasterNo));		
}
ImageBuffer				&AlgorithmItemPLI::GetMasterBuff(int n)		
{	
	return(Parent->GetMasterBuff(n));		
}

ImageBuffer				&AlgorithmItemPLI::GetBackGroundBuff(void)		
{	
	int	iMasterNo=GetMasterNo();
	if(iMasterNo<0){
		iMasterNo=0;
	}
	if(iMasterNo>=GetCountAllBackGroundBuff()){
		iMasterNo=GetCountAllBackGroundBuff()-1;
	}
	return(Parent->GetBackGroundBuff(iMasterNo));		
}
ImageBuffer				&AlgorithmItemPLI::GetBackGroundBuff(int n)		
{	
	return(Parent->GetBackGroundBuff(n));		
}
ImageBuffer				&AlgorithmItemPLI::GetBitBuff(void)		
{	
	return(Parent->GetBitBuff());		
}
ImageBuffer				&AlgorithmItemPLI::GetTargetBuff(void)		
{	
	return(Parent->GetTargetBuff());		
}
ImageBuffer				&AlgorithmItemPLI::GetTargetTRBuff(void)		
{	
	return(Parent->GetTargetTRBuff());		
}
ImageBuffer				&AlgorithmItemPLI::GetTrialTargetBuff(void)		
{	
	return(Parent->GetTrialTargetBuff());		
}

ImageBuffer		&AlgorithmItemPLI::GetMasterBuffByLayerNo(int LayerNo)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetMasterBuff(GetMasterNo());
				}
			}
		}
	}
	return GetMasterBuff();
}
ImageBuffer		&AlgorithmItemPLI::GetMasterBuffByLayerNo(int LayerNo,int n)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetMasterBuff(n);
				}
			}
		}
	}
	return GetMasterBuff(n);
}

ImageBuffer		&AlgorithmItemPLI::GetBackGroundBuffByLayerNo(int LayerNo)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetBackGroundBuff(GetMasterNo());
				}
			}
		}
	}
	return GetBackGroundBuff();
}
ImageBuffer		&AlgorithmItemPLI::GetBackGroundBuffByLayerNo(int LayerNo,int n)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetBackGroundBuff(n);
				}
			}
		}
	}
	return GetBackGroundBuff(n);
}
ImageBuffer		&AlgorithmItemPLI::GetTargetBuffByLayerNo		(int LayerNo)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetTargetBuff();
				}
			}
		}
	}
	return GetTargetBuff();
}
ImageBuffer		&AlgorithmItemPLI::GetTargetTRBuffByLayerNo		(int LayerNo)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetTargetTRBuff();
				}
			}
		}
	}
	return GetTargetTRBuff();
}
ImageBuffer		&AlgorithmItemPLI::GetBitBuffByLayerNo			(int LayerNo)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetBitBuff();
				}
			}
		}
	}
	return GetBitBuff();
}
ImageBuffer		&AlgorithmItemPLI::GetTrialTargetBuffByLayerNo	(int LayerNo)
{
	if(LayerNo>=0){
		AlgorithmInPageRoot	*Ap=GetParentInPage();
		if(Ap!=NULL){
			DataInPage	*Dp=Ap->GetDataInPage();
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(LayerNo);
				if(Lp!=NULL){
					return Lp->GetTrialTargetBuff();
				}
			}
		}
	}
	return GetTrialTargetBuff();
}

AlgorithmBase			*AlgorithmInLayerPLI::GetParentBase(void)	const
{	
	if(Parent==NULL){
		return NULL;
	}
	return Parent->GetParentBase();			
}
AlgorithmInPageRoot		*AlgorithmInLayerPLI::GetParentInPage(void)	const
{	
	return Parent;				
}

AlgorithmInLayerRoot	*AlgorithmInLayerPLI::GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(_DLLRoot ,_DLLName);
	if(Ab==NULL){
		return NULL;
	}
	AlgorithmInPagePLI	*p=dynamic_cast<AlgorithmInPagePLI *>(Ab->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage()));
	if(p==NULL){
		return NULL;
	}
	return p->GetLayerData(GetLayer());
}

AlgorithmInPageInOnePhase	*AlgorithmInLayerPLI::GetAlgorithmInPageInOnePhase(void)	const
{
	return GetParentInPage()->GetParentPhase();
}
XYData	*AlgorithmInLayerPLI::GetOutlineOffset(void)	const
{	
	return GetDataInLayer()->GetOutlineOffset();	
}
void	AlgorithmInLayerPLI::IncrementNGCounterWithMutex(int result)
{
	if(Parent!=NULL){
		Parent->IncrementNGCounterWithMutex(result);
	}
}
int		AlgorithmInLayerPLI::GetNGCounter(void)
{
	if(Parent!=NULL){
		return Parent->GetNGCounter();
	}
	return 0;
}
AlgorithmInPageRoot	*AlgorithmInPagePLI::GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)	const
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(_DLLRoot ,_DLLName);
	if(Ab==NULL){
		return NULL;
	}
	AlgorithmInPageRoot	*p=dynamic_cast<AlgorithmInPageRoot *>(Ab->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage()));
	return p;
}

AlgorithmItemRoot	*ResultInItemPLI::GetAlgorithmItemRoot(void)	const
{
	if(GetAlgorithmItem()!=NULL)
		return GetAlgorithmItem();
	AlgorithmInLayerPLI *cParent=(AlgorithmInLayerPLI *)Parent->GetAlgorithmInLayer();
	return cParent->SearchIDItem(GetItemID());
}

//===========================================================================================================
ResultInItemRoot	*ResultInItemPLI::Clone(void)
{
	ResultInItemPLI	*r=new ResultInItemPLI();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Save(&Buff);
	Buff.seek(0);
	r->Load(&Buff);
	return r;
}

LogicDLL		*ResultInItemPLI::GetLogicDLL(void)	const
{
	if(Parent==NULL || Parent->Parent==NULL || Parent->Parent->Parent==NULL){
		return NULL;
	}
	return Parent->Parent->Parent->GetLogicDLL();
}
AlgorithmBase		*ResultInItemPLI::GetAlgorithmBase(void)	const
{
	if(Parent!=NULL){
		return Parent->GetAlgorithmBase();
	}
	return NULL;
}

int		ResultInItemPLI::GetDotPerLine(void)	const
{
	if(Parent==NULL)
		return 0;
	if(Parent->GetAlgorithmInPage()==NULL)
		return 0;
	return Parent->GetAlgorithmInPage()->GetDotPerLine();
}
int		ResultInItemPLI::GetMaxLines(void)	const
{
	if(Parent==NULL)
		return 0;
	if(Parent->GetAlgorithmInPage()==NULL)
		return 0;
	return Parent->GetAlgorithmInPage()->GetMaxLines();
}

ResultInLayerPLI::ResultInLayerPLI(DataInLayer *pDataInLayer,ResultInPagePLI *parent)
:ResultInLayerRoot(pDataInLayer)
{
	Parent				=parent;
	Result				=NULL;
	AllocatedResultCount=-1;
}
ResultInLayerPLI::~ResultInLayerPLI(void)
{
	if(Result!=NULL){
		delete	[]Result;
	}
	Result=NULL;
	AllocatedResultCount=0;
}

void	ResultInLayerPLI::Initial(ResultBaseForAlgorithmRoot *parent)
{
	AlgoPointer	=Parent->AlgoPointer->GetLayerData(Layer);
}

void	ResultInLayerPLI::Alloc(AlgorithmInLayerPLI *ALayer)
{
	if(ALayer!=NULL
	&& ALayer->GetParentBase()->GetLogicDLL()!=NULL 
	&& ALayer->GetParentBase()->GetLogicDLL()->CheckAlgorithmType(AlgorithmBit_TypePreAlignment
																	| AlgorithmBit_TypePreAlignment
																	| AlgorithmBit_TypeAlignment	
																	| AlgorithmBit_TypePreProcessing
																	| AlgorithmBit_TypeProcessing		
																	| AlgorithmBit_TypeProcessingRevived
																	| AlgorithmBit_TypePostProcessing
																	| AlgorithmBit_TypePieceProcessing)==true){

		int	N=ALayer->GetTotalItemCount();
		if(AllocatedResultCount!=N){
			if(Result!=NULL){
				delete	[]Result;
			}
			AllocatedResultCount=N;
			Result=(ResultInItemPLI *)CreateItemDim(AllocatedResultCount);
			for(int i=0;i<AllocatedResultCount;i++){
				Result[i].SetParent(this);
			}
		}
		int	i=0;
		for(AlgorithmItemPLI *a=ALayer->GetFirstData();a!=NULL;a=a->GetNext(),i++){
			Result[i].SetItemID(a->GetID());
		}
	}
}

bool    ResultInLayerPLI::Save(QIODevice *f)
{
	if(ResultInLayerRoot::Save(f)==false){
		return false;
	}
	if(::Save(f,AllocatedResultCount)==false){
		return(false);
	}
	for(int i=0;i<AllocatedResultCount;i++){
		if(Result[i].Save(f)==false){
			return(false);
		}
	}
	return(true);
}
bool    ResultInLayerPLI::Load(QIODevice *f)
{
	if(ResultInLayerRoot::Load(f)==false){
		return false;
	}
	int32	N;
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	if(AllocatedResultCount!=N){
		if(Result!=NULL){
			delete	[]Result;
		}
		AllocatedResultCount=N;
		Result=(ResultInItemPLI *)CreateItemDim(AllocatedResultCount);
		for(int i=0;i<AllocatedResultCount;i++){
			Result[i].SetParent(this);
		}
	}
	for(int i=0;i<AllocatedResultCount;i++){
		if(Result[i].Load(f)==false){
			return(false);
		}
	}
	return(true);
}

void	ResultInLayerPLI::InitialInspection(void)
{
	for(int i=0;i<AllocatedResultCount;i++){
		Result[i].InitialInspection();
	}
	CalcDone=false;
}

void	ResultInLayerPLI::MoveMerge(ResultInLayerRoot &dst)
{
	ResultInLayerPLI	*D= (ResultInLayerPLI	*)&dst;
	if(Result!=NULL){
		delete	[]Result;
	}
	Result=D->Result;
	AllocatedResultCount=D->AllocatedResultCount;
	D->Result=NULL;
	D->AllocatedResultCount=0;

	D->Alloc((AlgorithmInLayerPLI *)GetAlgorithmInLayer());
}
ResultInItemPLI		*ResultInLayerPLI::FindResultInItem(int ItemID)	const
{
	for(int i=0;i<AllocatedResultCount;i++){
		if(Result[i].GetItemID()==ItemID){
			return &Result[i];
		}
	}
	return NULL;
}

ResultInItemRoot	*ResultInLayerPLI::FastSearchIDItem(int ItemID)	const
{
	if(ItemDimPointer==NULL){
		ResultInItemRoot	*r=FindResultInItem(ItemID);
		return r;
	}
	ResultInItemRoot	*r=FastSearchIDItemInside(ItemID);
	return r;
}
AlgorithmInLayerRoot	*ResultInLayerPLI::GetAlgorithmInLayer(void)	const
{
	return ((AlgorithmInPagePLI *)GetAlgorithmInPage())->GetLayerData(GetLayer());
}
AlgorithmInPageRoot	*ResultInLayerPLI::GetAlgorithmInPage(void)	const
{
	int	phase=Parent->GetPhaseParent()->GetPhaseCode();
	return GetAlgorithmBase()->GetPageDataPhase(phase)->GetPageData(Parent->GetPage());
}
AlgorithmBase		*ResultInLayerPLI::GetAlgorithmBase(void)	const
{
	return Parent->Parent->GetLogicDLL()->GetInstance();
}


int		ResultInLayerPLI::GetNGCount(void)	const
{
	int	NGCount=0;
	for(int i=0;i<AllocatedResultCount;i++){
		if(Result[i].IsOk()==false){
			NGCount++;
		}
	}
	return NGCount;
}
int		ResultInLayerPLI::GetNGPointCount(void)	const
{
	int	NGCount=0;
	for(int i=0;i<AllocatedResultCount;i++){
		NGCount+=Result[i].GetNGPointCount();
	}
	return NGCount;
}


bool	ResultInLayerPLI::GatherResult(bool3 &OK)
{
	if(CalcDone==false){
		OK=none3;
		return true;
	}
	OK=true3;
	for(int i=0;i<AllocatedResultCount;i++){
		//if(AlgoPointer->IsCalcDone()==false && r->IsDone()==false){
		if(Result[i].IsOk()==false){
			OK=false3;
			return true;
		}
	}
	return true;
}
bool	ResultInLayerPLI::GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const
{
	if(CalcDone==false){
		OK=none3;
		return true;
	}
	OK=true3;
	for(int i=0;i<AllocatedResultCount;i++){
		if(Result[i].IsOk()==false){
			for(ResultPosList *a=Result[i].GetPosList().GetFirst();a!=NULL;a=a->GetNext()){
				ResultPosInfo	*E=new ResultPosInfo();
				E->AItem=Result[i].GetAlgorithmItem();
				E->RItem=&Result[i];
				E->RPos	=a;
				RContainer.AppendList(E);
			}
			OK=false3;
		}
	}
	return true;
}

void	ResultInLayerPLI::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ErrorGroupPack EGroup;
		Result[i].BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect,EGroup);
		SpecializedGroup+=EGroup;
	}
}
void	ResultInLayerPLI::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ErrorGroupPack EGroup;
		Result[i].BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRectDim,EGroup);
		SpecializedGroup+=EGroup;
	}
}
void	ResultInLayerPLI::ExecuteInAllItems(void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	for(int i=0;i<AllocatedResultCount;i++){
		Func(&Result[i],Something);
	}
}
void	ResultInLayerPLI::GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		if(r->IsNGNearXY(area)==true){
			ResultInItemRootPointerList	*d=new ResultInItemRootPointerList(r);
			Ret.AppendList(d);
		}
	}
}
void	ResultInLayerPLI::GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)
{
	for(int i=0;i<AllocatedResultCount;i++){
		if(Result[i].GetErrorGroupID()==ErrorGroupID){
			ResultInItemRootPointerList	*d=new ResultInItemRootPointerList(&Result[i]);
			Ret.AppendList(d);
		}
	}
}
void	ResultInLayerPLI::BindNGAreaListContainer(NGAreaListContainer &List)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		r->BindNGAreaListContainer(List);
	}
}
void	ResultInLayerPLI::ExecuteFuncInAllItems(void (*ItemFunc)(ResultInItemRoot *Item,void *_Something),void *Something)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		ItemFunc(r,Something);
	}
}
void	ResultInLayerPLI::ExecuteFuncInAllItemPos(void (*PosFunc)(ResultInItemRoot *Item, ResultPosList *RPos,void *_Something),void *Something)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		for(ResultPosList *p=r->GetPosListFirst();p!=NULL;p=p->GetNext()){
			PosFunc(r,p,Something);
		}
	}
}
void	ResultInLayerPLI::SetResultMarkForLearning(void)
{
	DataInPage		*dp=GetAlgorithmInPage()->GetDataInPage();
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		if(r!=NULL && r->IsOk()==false){
			for(ResultPosList *p=r->GetPosListFirst();p!=NULL;p=p->GetNext()){
				dp->SetResultMarkForLearning(GetLayer(),p->Px,p->Py);
			}
		}
	}
}

void	ResultInLayerPLI::ReviveResult(LearningImage *c)
{
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		r->ReviveResult(c);
	}
}

int		ResultInLayerPLI::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *r=&Result[i];
		int	count=r->GetPointerListOfResultPosList(OverlapArea ,&RetDim[N] ,MaxCount-N);
		N+=count;
	}
	return N;
}

AlgorithmInPageInOnePhase	*ResultInLayerPLI::GetAlgorithmInPageInOnePhase(void)	const
{
	return Parent->GetAlgorithmInPageInOnePhase();
}
void	ResultInLayerPLI::MakeResultDetailInNG(DetailResultInfoListContainerAll &List)
{
	AlgorithmBase	*ABase=GetAlgorithmBase();
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPLI *R=&Result[i];
		if(R->IsOk()==false){
			AlgorithmItemRoot	*Item=R->GetAlgorithmItem();
			DetailResultInfoListContainer *RetList=new DetailResultInfoListContainer();
			for(ResultPosList *r=R->GetPosListFirst();r!=NULL;r=r->GetNext()){
				ABase->GetDrawResultDetail(Item,r,*RetList);
			}
			List.AppendList(RetList);
		}
	}
}

ExeResult	ResultInLayerPLI::ExecuteInitialAfterEditPrev(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteInitialAfterEdit	(int ExeID)
{
	AlgoPointer	=Parent->AlgoPointer->GetLayerData(Layer);
	LayersBase	*LBase=GetLayersBase();

	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecuteInitialAfterEditPost(ExeID,c);
			}
		}
	}
	int	ResultCount=GetItemCount();
	AllocateForFastSearch(ResultCount);
	for(int i=0;i<GetItemCount();i++){
		ResultInItemPLI *c=GetResultItem(i);
		ItemDimPointer[i]=c;
	}
	SortResultDimPointer();

	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteInitialAfterEditPost(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteStartByInspection	(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecuteStartByInspectionPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteCaptured(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecuteCapturedPost(ExeID,c,CapturedList);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecutePreAlignment		(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecutePreAlignmentPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteAlignment			(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecuteAlignmentPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecutePreProcessing		(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecutePreProcessingPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteProcessing			(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecuteProcessingPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteProcessingRevived	(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecutePostProcessing		(int ExeID)
{
	CalcDone	=true;
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(int i=0;i<GetItemCount();i++){
				ResultInItemPLI *c=GetResultItem(i);
				A->ExecutePostProcessingPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecutePreScanning		(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecuteScanning			(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInLayerPLI::ExecutePostScanning		(int ExeID)
{
	return _ER_true;
}
void	ResultInLayerPLI::SetCurentCalcDone(bool b)
{
	CalcDone=b;
}
void	ResultInLayerPLI::ClearResult(void)
{
	for(int i=0;i<GetItemCount();i++){
		ResultInItemPLI *c=GetResultItem(i);
		c->ClearResult();
	}
}

ResultInPagePLI::ResultInPagePLI(ResultBasePhase *pPhaseParent,DataInPage *pPage)
:ResultInPageRoot(pPhaseParent,pPage)
{
	Parent			=NULL;
	Release();
}
ResultInPagePLI::~ResultInPagePLI(void)
{
	Release();
}

bool	ResultInPagePLI::Initial(ResultBaseForAlgorithmRoot *parent)
{
	SetDataInPage(parent->GetLayersBase()->GetPageData(GetPage()));
	AlgoPointer=PhaseParent->AlgoPointer->GetPageData(Page);

	int	LayerNumb=GetLayerNumb(GetPage());
	if(LayerData.GetNumber()!=LayerNumb){
		Release();
		Parent=parent;
		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	*a=new ResultInLayerPLI(GetLayersBase()->GetPageData(GetPage())->GetLayerData(layer)
												,this);
			//a->SetLayer(layer);
			//a->Initial(parent);
			LayerData.AppendList(a);
		}
	}
	SetDataInPage(parent->GetLayersBase()->GetPageData(GetPage()));
	for(int layer=0;layer<LayerNumb;layer++){
		ResultInLayerPLI	*a=LayerData[layer];
		a->SetLayer(layer);
		a->Initial(parent);
	}
	return true;
}
void	ResultInPagePLI::Release(void)
{
	LayerData	.RemoveAll();
}
bool	ResultInPagePLI::Reallocate(int newLayerNumb)
{
	int	AllocatedLayerNumb=LayerData.GetCount();
	if(AllocatedLayerNumb<newLayerNumb){
		for(int layer=AllocatedLayerNumb;layer<newLayerNumb;layer++){
			ResultInLayerPLI	*a=new ResultInLayerPLI(GetLayersBase()->GetPageData(GetPage())->GetLayerData(layer)
												,this);
			a->SetLayer(layer);
			LayerData.AppendList(a);
		}
	}
	else if(AllocatedLayerNumb>newLayerNumb){
		while(LayerData.GetCount()>newLayerNumb){
			ResultInLayerPLI	*p=LayerData.GetLast();
			LayerData.RemoveList(p);
			delete	p;
		}
	}
	return true;
}
bool    ResultInPagePLI::Save(QIODevice *file)
{
	if(ResultInPageRoot::Save(file)==false)
		return false;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Save(file)==false){
			return(false);
		}
	}
	return(true);
}
bool    ResultInPagePLI::Load(QIODevice *file)
{
	if(ResultInPageRoot::Load(file)==false){
		return false;
	}
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Load(file)==false){
			return(false);
		}
	}
	return(true);
}

void	ResultInPagePLI::MoveMerge(ResultInPageRoot &Dst)
{
	ResultInPagePLI *D=(ResultInPagePLI *)&Dst;
	ResultInLayerPLI *src=D->LayerData.GetFirst();
	ResultInLayerPLI *dst=LayerData.GetFirst();
	for(;dst!=NULL && src!=NULL;src=src->GetNext(),dst=dst->GetNext()){
		dst->MoveMerge(*src);
	}
	for(;src!=NULL;src=src->GetNext()){
		dst=new ResultInLayerPLI(GetLayersBase()->GetPageData(GetPage())->GetLayerData(src->GetLayer())
							,this);
		dst->SetLayer(src->GetLayer());
		LayerData.AppendList(dst);
		dst->MoveMerge(*src);
	}
	while(dst!=NULL){
		ResultInLayerPLI *NextDst=dst->GetNext();
		LayerData.RemoveList(dst);
		delete	dst;
		dst=NextDst;
	}
}

ExeResult	ResultInPagePLI::ExecuteInitialAfterEditPrev(int ExeID)
{
	AlgoPointer=PhaseParent->AlgoPointer->GetPageData(Page);
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteInitialAfterEditPrev(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}

ExeResult	ResultInPagePLI::ExecuteInitialAfterEdit	(int ExeID)
{
	AlgoPointer=PhaseParent->AlgoPointer->GetPageData(Page);
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteInitialAfterEdit	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}

ExeResult	ResultInPagePLI::ExecuteInitialAfterEditPost(int ExeID)
{
	AlgoPointer=PhaseParent->AlgoPointer->GetPageData(Page);
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteInitialAfterEditPost(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}

ExeResult	ResultInPagePLI::ExecuteStartByInspection(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteStartByInspection	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecuteCaptured(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteCaptured	(ExeID,CapturedList);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecutePreAlignment		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecutePreAlignment	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecuteAlignment			(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteAlignment	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecutePreProcessing		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecutePreProcessing	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecuteProcessing			(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteProcessing	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecuteProcessingRevived	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteProcessingRevived	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecutePostProcessing		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecutePostProcessing	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	CalcDone	=true;
	return Ret;
}
ExeResult	ResultInPagePLI::ExecutePreScanning			(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecutePreScanning	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecuteScanning			(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecuteScanning	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultInPagePLI::ExecutePostScanning		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		ExeResult	RR=r->ExecutePostScanning	(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}

bool	ResultInPagePLI::GatherResult(bool3 &OK)	const
{
	OK=true3;
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		bool3	tOK;
		L->GatherResult(tOK);
		if(tOK==none3){
			OK=none3;
			return true;
		}
		if(tOK==false3){
			OK=false3;
		}
	}
	return true;
}

bool	ResultInPagePLI::GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const
{
	OK=true3;
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		bool3	tOK;
		L->GatherResult(RContainer,tOK);
		if(tOK==none3){
			OK=none3;
			return true;
		}
		if(tOK==false3){
			OK=false3;
		}
	}
	return true;
}


void	ResultInPagePLI::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)
{
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		L->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect,SpecializedGroup);
	}
}
void	ResultInPagePLI::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)
{
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		L->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRectDim,SpecializedGroup);
	}
}

void	ResultInPagePLI::InitialInspection(void)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->InitialInspection();
	}
	CalcDone=false;
	DoneBindImage=false;
}
void	ResultInPagePLI::ExecuteFuncInAllItems(void (*ItemFunc)(ResultInItemRoot *Item,void *_Something),void *Something)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->ExecuteFuncInAllItems(ItemFunc,Something);
	}
}
void	ResultInPagePLI::ExecuteFuncInAllItemPos(void (*PosFunc)(ResultInItemRoot *Item, ResultPosList *RPos,void *_Something),void *Something)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->ExecuteFuncInAllItemPos(PosFunc,Something);
	}
}
AlgorithmInPageInOnePhase	*ResultInPagePLI::GetAlgorithmInPageInOnePhase(void)	const
{
	return GetAlgorithmBase()->GetPageDataPhase(GetPhaseCode());
}

AlgorithmBase				*ResultInPagePLI::GetAlgorithmBase(void)	const
{
	return Parent->GetLogicDLL()->GetInstance();
}

ResultDLLBaseRoot	*ResultInPagePLI::GetResultDLLBase(void)	const
{
	return Parent->GetResultDLLBase();
}

ResultInItemRoot	*ResultInPagePLI::FindResultInItem(int layer ,int ItemID)	const
{
	ResultInLayerPLI &L=GetLayerData(layer);
	return L.FindResultInItem(ItemID);
}
ResultInItemRoot	*ResultInPagePLI::FastSearchIDItem(int layer ,int ItemID)	const
{
	ResultInLayerPLI &L=GetLayerData(layer);
	return L.FastSearchIDItem(ItemID);
}

int		ResultInPagePLI::GetNGCount(void)	const
{
	int	NGCount=0;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		NGCount+=r->GetNGCount();
	}
	return NGCount;
}
int		ResultInPagePLI::GetNGPointCount(void)	const
{
	int	NGCount=0;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		NGCount+=r->GetNGPointCount();
	}
	return NGCount;
}
void	ResultInPagePLI::SetCurentCalcDone(bool b)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->SetCurentCalcDone(b);
	}
	if(b==false){
		DoneBindImage=false;
	}
}
void	ResultInPagePLI::ClearResult(void)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->ClearResult();
	}
}

AlgorithmInPageRoot		*ResultInPagePLI::GetAlgorithmInPage(void)	const
{	
	if(Parent==NULL){
		return NULL;
	}
	if(Parent->GetLogicDLL()==NULL){
		return NULL;
	}
	if(Parent->GetLogicDLL()->GetInstance()==NULL){
		return NULL;
	}
	int	phase=GetPhaseParent()->GetPhaseCode();
	return Parent->GetLogicDLL()->GetInstance()->GetPageDataPhase(phase)->GetPageData(GetPage());	
}

void	ResultInPagePLI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;
		int		LayerNumb=GetLayerNumb(GetPage());
		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
						QStringList	AreaNames;
						if(p->AreaNames.count()==0){
							QString	AreaName;
							if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
								AreaName=/**/"";
								AreaNames.append(AreaName);
							}
							else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																								,p->Py	//+a->GetAlignedY()+p->Ry 
																								,AreaName)==true){
								AreaNames.append(AreaName);
							}
						}
						else{
							AreaNames=p->AreaNames;
						}
						int32	cPx=p->Px+a->GetAlignedX()+p->Rx;
						int32	cPy=p->Py+a->GetAlignedY()+p->Ry;
						LBase->ConvertToTop(cPx,cPy);
						int32	aPx=a->GetAlignedX();
						int32	aPy=a->GetAlignedY();
						LBase->ConvertToTop(aPx,aPy);
						int32	rPx=p->Rx;
						int32	rPy=p->Ry;
						LBase->ConvertToTop(rPx,rPy);

						QString	Msg=QString(/**/"<NGP X=\"")
								+QString::number(cPx)
								+QString(/**/"\" Y=\"")
								+QString::number(cPy)
								+QString(/**/"\" MX=\"")
								+QString::number(aPx)
								+QString(/**/"\" MY=\"")
								+QString::number(aPy)
								+QString(/**/"\" HX=\"")
								+QString::number(rPx)
								+QString(/**/"\" HY=\"")
								+QString::number(rPy);

						if(AreaNames.count()!=0){
							int	AreaNameCount=0;
							for(int k=0;k<AreaNames.count();k++){
								if(AreaNames[k].length()!=0){
									AreaNameCount++;
								}
							}
							if(AreaNameCount!=0){
								Msg=Msg+QString(/**/"\" ARA=\"#");
								for(int k=0;k<AreaNames.count();k++){
									Msg=Msg+AreaNames[k];
									if(k<AreaNames.count()-1){
										Msg=Msg+QString(",");
									}
								}
							}
						}
						if(OutputNGCause==true){
							if(a->GetAlgorithmItem()!=NULL){
								Msg=Msg	+QString(/**/"\" LC=\"")
									+QString::number(a->GetAlgorithmItem()->GetLibID());
							}

							if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
								LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
								if(t!=NULL){
									Msg=Msg	+QString(/**/"\" TC=\"")
											+QString::number(t->TypeCode);
								}
							}
						}
						AlgorithmItemRoot	*aitem=a->GetAlgorithmItem();
						QString	m;
						if(aitem!=NULL)
							m=aitem->OutputResult(p);
						if(m.isEmpty()==false){
							Msg =Msg+QString(" ")+m;
						}

						if(p->ResultType==ResultPosList::_ResultDWORD){
							Msg=Msg	+QString(/**/"\" RS1=\"")
									+QString::number(p->GetResult1())
									+QString(/**/"\" RS2=\"")
									+QString::number(p->GetResult2())
									+QString(/**/"\" RAL=\"")
									+LogicDLLPoint->GetDLLRoot()
									+QString(/**/":")
									+LogicDLLPoint->GetDLLName()
									+QString(/**/"\" LY=\"")
									+QString::number(layer)
									+QString(/**/"\"/>");
						}
						else if(p->ResultType==ResultPosList::_ResultDouble){
							Msg=Msg	+QString(/**/"\" RS1=\"")
									+QString::number(p->GetResultDouble(),'f')
									+QString(/**/"\" RAL=\"")
									+LogicDLLPoint->GetDLLRoot()
									+QString(/**/":")
									+LogicDLLPoint->GetDLLName()
									+QString(/**/"\" LY=\"")
									+QString::number(layer)
									+QString(/**/"\"/>");
						}

						ResList<<Msg;
					}
				}
			}
		}
	}
}

void	ResultInPagePLI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,char *ResList)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;

		char	Text[100];
		*ResList=0;
		int		LayerNumb=GetLayerNumb(GetPage());
		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
						QStringList	AreaNames;
						if(p->AreaNames.count()==0){
							QString	AreaName;
							if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage()  ,p->Px	//+a->GetAlignedX()+p->Rx
																							,p->Py	//+a->GetAlignedY()+p->Ry 
																							,AreaName)==true){
								AreaNames.append(AreaName);
							}
						}
						else{
							AreaNames=p->AreaNames;
						}

						int32	cPx=p->Px+a->GetAlignedX()+p->Rx;
						int32	cPy=p->Py+a->GetAlignedY()+p->Ry;
						LBase->ConvertToTop(cPx,cPy);
						int32	aPx=a->GetAlignedX();
						int32	aPy=a->GetAlignedY();
						LBase->ConvertToTop(aPx,aPy);
						int32	rPx=p->Rx;
						int32	rPy=p->Ry;
						LBase->ConvertToTop(rPx,rPy);

						strcat(ResList,/**/"<NGP X=\"");
						::ToStr(Text,cPx);
						strcat(ResList,Text);

						strcat(ResList,/**/"\" Y=\"");
						::ToStr(Text,cPy);
						strcat(ResList,Text);

						strcat(ResList,/**/"\" MX=\"");
						::ToStr(Text,aPx);
						strcat(ResList,Text);

						strcat(ResList,/**/"\" MY=\"");
						::ToStr(Text,aPy);
						strcat(ResList,Text);

						strcat(ResList,/**/"\" HX=\"");
						::ToStr(Text,rPx);
						strcat(ResList,Text);

						strcat(ResList,/**/"\" HY=\"");
						::ToStr(Text,rPy);
						strcat(ResList,Text);


						if(AreaNames.count()!=0){
							int	AreaNameCount=0;
							for(int k=0;k<AreaNames.count();k++){
								if(AreaNames[k].length()!=0){
									AreaNameCount++;
								}
							}
							if(AreaNameCount!=0){
								strcat(ResList,/**/"\" ARA=\"#");

								for(int k=0;k<AreaNames.count();k++){
									::QString2Char(AreaNames[k] ,Text ,sizeof(Text));
									strcat(ResList,Text);
									if(k<AreaNames.count()-1){
										strcat(ResList,/**/",");
									}
								}
							}
						}
						if(OutputNGCause==true){
							if(a->GetAlgorithmItem()!=NULL){
								strcat(ResList,/**/"\" LC=\"");
								::ToStr(Text,a->GetAlgorithmItem()->GetLibID());
								strcat(ResList,Text);
							}
							if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
								LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
								if(t!=NULL){
									strcat(ResList,/**/"\" TC=\"");
									::ToStr(Text,t->TypeCode);
									strcat(ResList,Text);
								}
							}
						}
						
						AlgorithmItemRoot	*aitem=a->GetAlgorithmItem();
						QString	m;
						if(aitem!=NULL)
							m=aitem->OutputResult(p);
						if(m.isEmpty()==false){
							strcat(ResList,/**/" ");
							::QString2Char(m ,Text ,sizeof(Text));
							strcat(ResList,Text);
						}

						if(p->ResultType==ResultPosList::_ResultDWORD){
							strcat(ResList,/**/"\" RS1=\"");
							::ToStr(Text,(int)p->GetResult1());
							strcat(ResList,Text);

							strcat(ResList,/**/"\" RS2=\"");
							::ToStr(Text,(int)p->GetResult2());
							strcat(ResList,Text);
						}
						else if(p->ResultType==ResultPosList::_ResultDouble){
							strcat(ResList,/**/"\" RS1=\"");
							::ToStr(Text,p->GetResultDouble());
							strcat(ResList,Text);
						}

						strcat(ResList,/**/"\" RAL=\"");
						::QString2Char(LogicDLLPoint->GetDLLRoot() ,Text ,sizeof(Text));
						strcat(ResList,Text);
						::QString2Char(LogicDLLPoint->GetDLLName() ,Text ,sizeof(Text));
						strcat(ResList,Text);

						strcat(ResList,/**/"\" LY=\"");
						::ToStr(Text,layer);
						strcat(ResList,Text);
						strcat(ResList,/**/"\"/>");
					}
				}
			}
		}
	}
}

bool	ResultInPagePLI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount)
{
	WrittenNGCount=0;
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;

		int32	N=0;
		int		LayerNumb=GetLayerNumb(GetPage());
		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
						N++;
					}
				}
			}
		}
		if(::Save(f,N)==false){
			return false;
		}

		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					int	UniqueID2=0;
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext(),UniqueID2++){
						QByteArray	EData;
						QStringList	AreaNames;
						if(p->AreaNames.count()==0){
							QString	AreaName;
							if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
								AreaName=/**/"";
								AreaNames.append(AreaName);
							}
							else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																								,p->Py	//+a->GetAlignedY()+p->Ry 
																								,AreaName)==true){
								AreaNames.append(AreaName);
							}
						}
						else{
							AreaNames=p->AreaNames;
						}
						ResultPositionInfomation	RData;
						RData.Error=a->GetError();
						RData.PosResult		=p->result;
						RData.X				=p->Px+a->GetAlignedX()+p->Rx;
						RData.Y				=p->Py+a->GetAlignedY()+p->Ry;
						RData.MX			=a->GetAlignedX();
						RData.MY			=a->GetAlignedY();
						RData.HX			=p->Rx;
						RData.HY			=p->Ry;
						RData.UniqueID2		=UniqueID2;

						LBase->ConvertToTop(RData.X,RData.Y);
						LBase->ConvertToTop(RData.MX,RData.MY);
						LBase->ConvertToTop(RData.HX,RData.HY);

						p->GetExtraData(EData);
						RData.ExtraDataByte	=EData.size();
						
						if(AreaNames.count()!=0){
							QString	AName;
							int	AreaNameCount=0;
							for(int k=0;k<AreaNames.count();k++){
								if(AreaNames[k].length()!=0){
									AreaNameCount++;
								}
							}
							if(AreaNameCount!=0){
								for(int k=0;k<AreaNames.count();k++){
									AName=AName+AreaNames[k];
									if(k<AreaNames.count()-1){
										AName=AName+QString(",");
									}
								}
							}					
							::QString2Char(AName ,RData.AreaName ,sizeof(RData.AreaName));
						}
						else{
							memset(&RData.AreaName,0,sizeof(RData.AreaName));
						}

						AlgorithmItemRoot	*AItem=a->GetAlgorithmItem();
						if(AItem==NULL){
							AlgorithmInLayerRoot		*ALayer=a->GetParent()->GetAlgorithmInLayer();
							if(ALayer!=NULL){
								AItem=ALayer->FastSearchIDItem(a->GetItemID());
							}
						}
						if(AItem!=NULL){
							RData.LibID			=AItem->GetLibID();
							RData.UniqueID1		=AItem->GetID();
						}
						else{
							RData.LibID	=-1;
						}

						RData.NGTypeUniqueCode	=-1;	
						if(OutputNGCause==true && GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
							LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
							if(t!=NULL){
								RData.NGTypeUniqueCode	=t->TypeCode;
							}
						}
						
						if(p->ResultType==ResultPosList::_ResultDWORD){
							RData.ResultType	=_ResultDWORD;
							RData.result1	=p->GetResult1();
							RData.result2	=p->GetResult2();
						}
						else if(p->ResultType==ResultPosList::_ResultDouble){
							RData.ResultType	=_ResultDouble;
							RData.ResultValue.ResultDouble	=p->GetResultDouble();
						}
						AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
						if(pLibContainer!=NULL){
							RData.LibType=pLibContainer->GetLibType();
						}
						else{
							RData.LibType=0;
						}
						RData.Layer		=layer;

						if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
							return false;
						}
						if(RData.ExtraDataByte>0){
							if(f->write(EData)!=RData.ExtraDataByte){
								return false;
							}
						}
						WrittenNGCount++;
					}
				}
			}
		}
	}
	return true;
}

bool	ResultInPagePLI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f,int &WrittenNGCount)
{
	WrittenNGCount=0;
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;

		int32	N=0;
		int		LayerNumb=GetLayerNumb(GetPage());
		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
						N++;
					}
				}
			}
		}
		if(f->Save(N)==false){
			return false;
		}

		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					int	UniqueID2=0;
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext(),UniqueID2++){
						QByteArray	EData;
						QStringList	AreaNames;
						if(p->AreaNames.count()==0){
							QString	AreaName;
							if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
								AreaName=/**/"";
								AreaNames.append(AreaName);
							}
							else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																								,p->Py	//+a->GetAlignedY()+p->Ry 
																								,AreaName)==true){
								AreaNames.append(AreaName);
							}
						}
						else{
							AreaNames=p->AreaNames;
						}
						ResultPositionInfomation	RData;
						RData.Error=a->GetError();
						RData.PosResult	=p->result;
						RData.X			=p->Px+a->GetAlignedX()+p->Rx;
						RData.Y			=p->Py+a->GetAlignedY()+p->Ry;
						RData.MX		=a->GetAlignedX();
						RData.MY		=a->GetAlignedY();
						RData.HX		=p->Rx;
						RData.HY		=p->Ry;
						RData.UniqueID2	=UniqueID2;

						LBase->ConvertToTop(RData.X,RData.Y);
						LBase->ConvertToTop(RData.MX,RData.MY);
						LBase->ConvertToTop(RData.HX,RData.HY);

						p->GetExtraData(EData);
						RData.ExtraDataByte	=EData.size();

						if(AreaNames.count()!=0){
							QString	AName;
							int	AreaNameCount=0;
							for(int k=0;k<AreaNames.count();k++){
								if(AreaNames[k].length()!=0){
									AreaNameCount++;
								}
							}
							if(AreaNameCount!=0){
								for(int k=0;k<AreaNames.count();k++){
									AName=AName+AreaNames[k];
									if(k<AreaNames.count()-1){
										AName=AName+QString(",");
									}
								}
							}					
							::QString2Char(AName ,RData.AreaName ,sizeof(RData.AreaName));
						}
						else{
							memset(&RData.AreaName,0,sizeof(RData.AreaName));
						}

						AlgorithmItemRoot	*AItem=a->GetAlgorithmItem();
						if(AItem==NULL){
							AlgorithmInLayerRoot		*ALayer=a->GetParent()->GetAlgorithmInLayer();
							if(ALayer!=NULL){
								AItem=ALayer->FastSearchIDItem(a->GetItemID());
							}
						}
						if(AItem!=NULL){
							RData.LibID		=AItem->GetLibID();
							RData.UniqueID1	=AItem->GetID();
						}
						else{
							RData.LibID	=-1;
						}

						RData.NGTypeUniqueCode	=-1;	
						if(OutputNGCause==true && GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
							LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
							if(t!=NULL){
								RData.NGTypeUniqueCode	=t->TypeCode;
							}
						}
						
						if(p->ResultType==ResultPosList::_ResultDWORD){
							RData.ResultType	=_ResultDWORD;
							RData.result1	=p->GetResult1();
							RData.result2	=p->GetResult2();
						}
						else if(p->ResultType==ResultPosList::_ResultDouble){
							RData.ResultType	=_ResultDouble;
							RData.ResultValue.ResultDouble	=p->GetResultDouble();
						}
						AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
						if(pLibContainer!=NULL){
							RData.LibType=pLibContainer->GetLibType();
						}
						else{
							RData.LibType=0;
						}
						RData.Layer		=layer;

						if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
							return false;
						}
						if(RData.ExtraDataByte>0){
							if(f->write(EData)!=RData.ExtraDataByte){
								return false;
							}
						}
						WrittenNGCount++;
					}
				}
			}
		}
	}
	return true;
}
void	ResultInPagePLI::OutputResult(FlexArea &Area ,int OffsetX ,int OffsetY
								,int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;
		int		LayerNumb=GetLayerNumb(GetPage());
		for(int layer=0;layer<LayerNumb;layer++){
			ResultInLayerPLI	&L=GetLayerData(layer);
			int	ResItemNumb=L.GetItemCount();
			for(int i=0;i<ResItemNumb;i++){
				ResultInItemPLI *a=L.GetResultItem(i);
				if(a->IsOk()==false){
					for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
						if(Area.IsInclude(p->Px,p->Py)==true){
							QStringList	AreaNames;
							if(p->AreaNames.count()==0){
								QString	AreaName;
								if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
									AreaName=/**/"";
									AreaNames.append(AreaName);
								}
								else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() 
																						,p->Px+a->GetAlignedX()+p->Rx +OffsetX
																						,p->Py+a->GetAlignedY()+p->Ry +OffsetY
																						,AreaName)==true){
									AreaNames.append(AreaName);
								}
							}
							else{
								AreaNames=p->AreaNames;
							}

							int32	cPx=p->Px+a->GetAlignedX()+p->Rx+OffsetX;
							int32	cPy=p->Py+a->GetAlignedY()+p->Ry+OffsetY;
							LBase->ConvertToTop(cPx,cPy);
							int32	aPx=a->GetAlignedX();
							int32	aPy=a->GetAlignedY();
							LBase->ConvertToTop(aPx,aPy);
							int32	rPx=p->Rx;
							int32	rPy=p->Ry;
							LBase->ConvertToTop(rPx,rPy);

							QString	Msg=QString(/**/"<NGP X=\"")
									+QString::number(cPx)
									+QString(/**/"\" Y=\"")
									+QString::number(cPy)
									+QString(/**/"\" MX=\"")
									+QString::number(aPx)
									+QString(/**/"\" MY=\"")
									+QString::number(aPy)
									+QString(/**/"\" HX=\"")
									+QString::number(rPx)
									+QString(/**/"\" HY=\"")
									+QString::number(rPy);

							if(AreaNames.count()!=0){
								int	AreaNameCount=0;
								for(int k=0;k<AreaNames.count();k++){
									if(AreaNames[k].length()!=0){
										AreaNameCount++;
									}
								}
								if(AreaNameCount!=0){
									Msg=Msg+QString(/**/"\" ARA=\"#");
									for(int k=0;k<AreaNames.count();k++){
										Msg=Msg+AreaNames[k];
										if(k<AreaNames.count()-1){
											Msg=Msg+QString(",");
										}
									}
								}
							}
							if(OutputNGCause==true){
								if(a->GetAlgorithmItem()!=NULL){
									Msg=Msg	+QString(/**/"\" LC=\"")
										+QString::number(a->GetAlgorithmItem()->GetLibID());
								}

								if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
									LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
									if(t!=NULL){
										Msg=Msg	+QString(/**/"\" TC=\"")
												+QString::number(t->TypeCode);
									}
								}
							}
							if(p->ResultType==ResultPosList::_ResultDWORD){
								Msg=Msg	+QString(/**/"\" RS1=\"")
										+QString::number(p->GetResult1())
										+QString(/**/"\" RS2=\"")
										+QString::number(p->GetResult2())
										+QString(/**/"\" RAL=\"")
										+LogicDLLPoint->GetDLLRoot()
										+QString(/**/":")
										+LogicDLLPoint->GetDLLName()
										+QString(/**/"\" LY=\"")
										+QString::number(layer)
										+QString(/**/"\"/>");
							}
							else if(p->ResultType==ResultPosList::_ResultDouble){
								Msg=Msg	+QString(/**/"\" RS1=\"")
										+QString::number(p->GetResultDouble(),'f')
										+QString(/**/"\" RAL=\"")
										+LogicDLLPoint->GetDLLRoot()
										+QString(/**/":")
										+LogicDLLPoint->GetDLLName()
										+QString(/**/"\" LY=\"")
										+QString::number(layer)
										+QString(/**/"\"/>");
							}
							ResList<<Msg;
						}
					}
				}
			}
		}
	}
}
void	ResultInPagePLI::ExecuteInAllItems(void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		L->ExecuteInAllItems(Func,Something);
	}
}
void	ResultInPagePLI::GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)
{
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		L->GetNGItemList(Ret ,area);
	}
}
void	ResultInPagePLI::GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)
{
	for(ResultInLayerPLI *L=LayerData.GetFirst();L!=NULL;L=L->GetNext()){
		L->GetItemListByErrorGroupID(Ret ,ErrorGroupID);
	}
}
void	ResultInPagePLI::BindNGAreaListContainer(NGAreaListContainer &List)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->BindNGAreaListContainer(List);
	}
}
void	ResultInPagePLI::SetResultMarkForLearning(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
			r->SetResultMarkForLearning();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
										,GetPage(),LayerList);
		for(IntClass *d=LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			ResultInLayerPLI *r=LayerData[d->GetValue()];
			r->SetResultMarkForLearning();
		}
	}
}

void	ResultInPagePLI::ReviveResult(LearningImage *c)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->ReviveResult(c);
	}
}

int		ResultInPagePLI::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		int	count=r->GetPointerListOfResultPosList(OverlapArea ,&RetDim[N] ,MaxCount-N);
		N+=count;
	}
	return N;
}
void	ResultInPagePLI::MakeResultDetailInNG(DetailResultInfoListContainerAll &List)
{
	for(ResultInLayerPLI *r=LayerData.GetFirst();r!=NULL;r=r->GetNext()){
		r->MakeResultDetailInNG(List);
	}
}

ResultBaseForAlgorithmPLI::ResultBaseForAlgorithmPLI(LogicDLL *parent)
:ResultBaseForAlgorithmRoot(parent)
{
}
ResultBaseForAlgorithmPLI::~ResultBaseForAlgorithmPLI(void)
{
}

ResultInPageRoot	*ResultBaseForAlgorithmPLI::CreatePage(int phase ,int page)					
{	
	if(GetLayersBase()->GetPageDataPhase(phase)!=NULL){
		return new ResultInPagePLI(	 GetPageDataPhase(phase)
									,GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page));	
	}
	return NULL;
}

ResultBaseForAlgorithmRoot	*ResultBaseForAlgorithmPLI::CreateResultBaseForAlgorithm(void)
{
	ResultBaseForAlgorithmPLI	*r=new ResultBaseForAlgorithmPLI(GetLogicDLL());
	r->Initial();
	return r;
}

bool	ResultBaseForAlgorithmPLI::DrawResult(int32 ShowFixedPhase
												,QPainter &PntFromIData ,QImage *IData 
												,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	if(GetLogicDLL()!=NULL){
		return GetLogicDLL()->DrawResultBase(ShowFixedPhase,this ,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
	}
	return true;
}


void	ResultBaseForAlgorithmPLI::ExecuteInAllItems(void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ResultBasePhase		*Ph=GetPageDataPhase(phase);
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			ResultInPageRoot *P=Ph->GetPageData(localPage);
			if(P!=NULL){
				P->ExecuteInAllItems(Func,Something);
			}
		}
	}
}

void	ResultBaseForAlgorithmPLI::ExecuteInAllItems(int phase ,void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	ResultBasePhase		*Ph=GetPageDataPhase(phase);
	for(int localPage=0;localPage<GetPageNumb();localPage++){
		ResultInPageRoot *P=Ph->GetPageData(localPage);
		if(P!=NULL){
			P->ExecuteInAllItems(Func,Something);
		}
	}
}


//===========================================================================================================

AlgorithmItemPLI::AlgorithmItemPLI(void): AlgorithmItemRoot()
{
	Parent=NULL;
}
AlgorithmItemPLI::AlgorithmItemPLI(FlexArea &area) : AlgorithmItemRoot(area)
{
	Parent=NULL;
}
AlgorithmItemPLI::AlgorithmItemPLI(FlexArea *area) : AlgorithmItemRoot(area)
{
	Parent=NULL;
}

void	AlgorithmItemPLI::SetParentVirtual(AlgorithmParentFromItem *parent)
{
	SetParent(dynamic_cast<AlgorithmInLayerPLI *>(parent));
}

void	AlgorithmItemPLI::SetParent(AlgorithmInLayerPLI *parent)
{	
	Parent=parent;	
	if(Parent!=NULL){
		SetLearn(Parent->GetLayersBase());
		GetThresholdBaseWritable()->SetLearn(Parent->GetLayersBase());
	}
}
AlgorithmInPageInOnePhase	*AlgorithmItemPLI::GetAlgorithmInPageInOnePhase(void)	const
{
	return GetParentInPage()->GetParentPhase();
}

AlgorithmParentFromItem	*AlgorithmItemPLI::GetParentAlgorithm(void)	const
{	
	return Parent;	
}

AlgorithmItemPLI	&AlgorithmItemPLI::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemRoot::operator=(src);
	Parent			=((AlgorithmItemPLI *)&src)->Parent;
	return(*this);
}
ExeResult	AlgorithmItemPLI::ExecuteInitialAfterEdit	(int ExeID 
														,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	RR=AlgorithmItemRoot::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	for(SubtractItem *b=SubBlock.GetFirst();b!=NULL;b=b->GetNext()){
		b->IndexAfterEdit=Parent->SearchIDItem(b->ItemID);
	}
	return RR;
}
ResultInItemRoot	*AlgorithmItemPLI::GetCurrentResult(void)
{
	if(AlgorithmItemRoot::GetCurrentResult()!=NULL){
		return AlgorithmItemRoot::GetCurrentResult();
	}

	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase	*Ph=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(GetParentInPage()->GetPage()));
		if(Rp!=NULL){
			ResultInLayerPLI	&rLayer=Rp->GetLayerData(GetParent()->GetLayer());
			ResultInItemPLI		*rItem=rLayer.FindResultInItem(GetID());
			return rItem;
		}
	}
	return NULL;
}
ResultInItemRoot	*AlgorithmItemPLI::GetResult(ResultInPageRoot *Rp)
{
	ResultInPagePLI	*R=dynamic_cast<ResultInPagePLI *>(Rp);
	if(R!=NULL){
		ResultInLayerPLI	&rLayer=R->GetLayerData(GetParent()->GetLayer());
		ResultInItemPLI		*rItem=rLayer.FindResultInItem(GetID());
		return rItem;
	}
	return NULL;
}


void	AlgorithmItemPLI::GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)
{
	if(GetSelected()==true){
		int	gx1,gy1,gx2,gy2;
		int	x1,y1,x2,y2;
		GetXY(gx1 ,gy1 ,gx2 ,gy2);
		LayersBase	*L=GetLayersBase();
		int	globalPage=L->GetGlobalPageFromLocal(GetPage());
		x1=gx1+dx+L->GetGlobalOutlineOffset(globalPage)->x;
		y1=gy1+dy+L->GetGlobalOutlineOffset(globalPage)->y;
		x2=gx2+dx+L->GetGlobalOutlineOffset(globalPage)->x;
		y2=gy2+dy+L->GetGlobalOutlineOffset(globalPage)->y;
		int	Lx1,Ly1,Lx2,Ly2;
		DataInPage	*Pg=GetParentInLayer()->GetDataInPage();
		ItemPointerListInPage	*LPg=OutsideItems.GetFirst();
		for(int page=0;page<MaxGlobalPage && LPg!=NULL;page++,LPg=LPg->GetNext()){
			if(page!=globalPage){
				Lx1=x1 - L->GetGlobalOutlineOffset(page)->x;
				Ly1=y1 - L->GetGlobalOutlineOffset(page)->y;
				Lx2=Lx1+(x2-x1);
				Ly2=Ly1+(y2-y1);
				if(CheckOverlapRectRect(0,0,Pg->GetDotPerLine(), Pg->GetMaxLines()
					,Lx1,Ly1,Lx2,Ly2)==true){
					ItemPointerListInLayer	*LLayer=LPg->LayerList.GetItem(GetLayer());
					LLayer->ItemList.AppendList(new ItemPointerList(this,Lx1-gx1,Ly1-gy1));
				}
			}
		}
	}
}

bool	AlgorithmItemPLI::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInLayerRoot	*p=GetParentInLayer();
	return p->GetReflectionMap(Mode ,Map ,LibData ,Anything);
}
bool	AlgorithmItemPLI::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,void *Anything)
{
	AlgorithmInLayerRoot	*p=GetParentInLayer();
	return p->GetReflectionMap(Mode ,Map ,Anything);
}
bool	AlgorithmItemPLI::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInLayerRoot	*p=GetParentInLayer();
	return p->GetReflectionVector(Mode ,Vector ,LibData ,Anything);
}
bool	AlgorithmItemPLI::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything)
{
	AlgorithmInLayerRoot	*p=GetParentInLayer();
	return p->GetReflectionVector(Mode ,Vector ,Anything);
}
bool	AlgorithmItemPLI::IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInLayerRoot	*p=GetParentInLayer();
	return p->IncludeLibInReflection(Mode ,LibData ,Anything);
}

void	AlgorithmItemPLI::CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)
{
	AlgorithmItemPLI	*s=dynamic_cast<AlgorithmItemPLI *>(src);
	if(s!=NULL){
		if(s->GetParent()!=NULL){
			SetParent(s->GetParent());
		}
		else{
			AlgorithmInLayerPLI	*p=dynamic_cast<AlgorithmInLayerPLI *>(P->GetLayerData(Layer));
			if(p!=NULL){
				SetParent(p);
			}
		}
	}
}
void	AlgorithmItemPLI::CopyFrom(AlgorithmItemRoot *src)
{
	if(GetParent()==NULL){
		SetParent(((AlgorithmItemPLI *)src)->GetParent());
	}
	operator=(*src);
}

bool	AlgorithmItemPLI::SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)
{
	AlgorithmInPageInOnePhase	*Ph=InstBase->GetPageDataPhase(PhaseCode);
	if(Ph!=NULL){
		int	LPage=InstBase->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
		AlgorithmInPageRoot *Pg=Ph->GetPageData(LPage);
		if(Pg!=NULL){
			AlgorithmInLayerRoot	*Ly=Pg->GetLayerData(Layer);
			if(Ly!=NULL){
				Parent=(AlgorithmInLayerPLI *)Ly;
				return true;
			}
		}
	}
	return false;
}

//===========================================================================================================
AlgorithmInLayerPLI::OMPAlgorithmItemStruct::OMPAlgorithmItemStruct(void)
{
	CalcThread	=NULL;
	Result		=NULL;
}
AlgorithmInLayerPLI::OMPAlgorithmItemStruct::~OMPAlgorithmItemStruct(void)
{
	if(CalcThread!=NULL){
		delete	[]CalcThread;
		CalcThread=NULL;
	}
	if(Result!=NULL){
		delete	[]Result;
		Result=NULL;
	}
	CalcThreadCount=0;
}
void	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::Alloc(AlgorithmInLayerPLI *parent,int threadNo,int N)
{
	Parent=parent;
	ThreadNo=threadNo;
	CalcThreadCount=N;
	if(N!=0){
		CalcThread	=new AlgorithmItemPLI*[N];
		Result		=new ResultInItemPLI*[N];
		for(int i=0;i<N;i++){
			CalcThread[i]=NULL;
			Result[i]=NULL;
		}
	}
}
void	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::Set(int n,AlgorithmItemPLI	*c,ResultInItemPLI	*r)
{
	CalcThread[n]=c;
	Result[n]=r;
}

ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteInitialAfterEditPrev(int ExeID,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteInitialAfterEditPrev(ExeID,ThreadNo,Result[i],EInfo);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}

ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteInitialAfterEdit	(ExeID,ThreadNo,Result[i],EInfo);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}

ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteInitialAfterEditPost(int ExeID,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteInitialAfterEditPost(ExeID,ThreadNo,Result[i],EInfo);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteStartByInspection(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteStartByInspection	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteCaptured(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteCaptured	(ExeID,ThreadNo,Result[i],CapturedList);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecutePreAlignment	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePreAlignment	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteAlignment		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteAlignment	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecutePreProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePreProcessing	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteProcessing		(int ExeID)
{
	ExeResult	Ret=_ER_true;

	DWORD	StartMilisec=Parent->GetLayersBase()->GetStartInspectionTimeMilisec();
	int		MaxInspectMilisec=Parent->GetParamGlobal()->MaxInspectMilisec;
	DWORD	NowTime=::GetComputerMiliSec();

	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			if((i&0xff)==0){
				NowTime=::GetComputerMiliSec();
			}
			if(Parent->GetNGCounter()<=Parent->GetParamGlobal()->MaxNGCountsPerCam
			&& NowTime-StartMilisec<=MaxInspectMilisec
			&& CalcThread[i]->IsEffective()==true){
				Result[i]->SetAlgorithmItem(CalcThread[i]);
				ExeResult	RR=CalcThread[i]->ExecuteProcessing	(ExeID,ThreadNo,Result[i]);
				if(RR!=_ER_true){
					Ret=RR;
				}
				if(CalcThread[i]->GetInvertLogic()==true){
					if(Result[i]->GetError()==1){
						Result[i]->SetError(2);
					}
					else if(Result[i]->GetError()>=2){
						Result[i]->SetError(1);
					}
					if(Result[i]->GetPosListFirst()==NULL){
						int	cx,cy;
						CalcThread[i]->GetCenter(cx,cy);
						Result[i]->GetPosList().AppendList(new ResultPosList(cx,cy));
					}
				}
				if(Result[i]->GetError()>=2){
					if(Parent->GetLayersBase()->GetResultFromAlgorithm()==0){
						Parent->GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
				if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
					#ifdef _MSC_VER
					if(_CrtCheckMemory()==false){
						ErrorOccurs();
					}
					#endif
				}

				Parent->IncrementNGCounterWithMutex(Result[i]->GetError());
			}
		}
	}
	/*
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]==NULL)
			continue;
		if(CalcThread[i]->ExecuteProcessing	(ThreadNo,Result[i] ,pInspectionData)==false)
			Ret=1;
	}
	*/
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecutePostProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePostProcessing	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecutePreScanning	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePreScanning	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecuteScanning	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteScanning	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::OMPAlgorithmItemStruct::ExecutePostScanning	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePostScanning	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}

AlgorithmInLayerPLI::AlgorithmInLayerPLI(AlgorithmInPageRoot *parent)
{
	Parent				=(AlgorithmInPagePLI *)parent;
	CalcThreadDim		=NULL;
	ThreadNumb			=0;
	CalcThreadDataCount	=0;
	DrawResultTableNumb	=0;
	DrawResultATable	=NULL;
	DrawResultRTable	=NULL;
	ThresholdDummy		=NULL;
	#pragma omp parallel                             
	{                                                
		ThreadNumb=omp_get_num_threads();
	}
}
AlgorithmInLayerPLI::~AlgorithmInLayerPLI(void)
{
	//_CrtCheckMemory();
	if(CalcThreadDim!=NULL){
		delete	[]CalcThreadDim;
	}
	CalcThreadDim=NULL;

	if(DrawResultATable!=NULL){
		delete	[]DrawResultATable;
	}
	DrawResultATable=NULL;

	if(DrawResultRTable!=NULL){
		delete	[]DrawResultRTable;
	}
	DrawResultRTable=NULL;

	if(ThresholdDummy!=NULL){
		delete	ThresholdDummy;
		ThresholdDummy=NULL;
	}
}
void	AlgorithmInLayerPLI::InitializeToStart(void)
{
	RemoveAllDatas();
}
void	AlgorithmInLayerPLI::InitialAfterParamLoaded(void)
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		c->InitialAfterParamLoaded();
	}
}
ResultInLayerRoot	*AlgorithmInLayerPLI::GetResultPointer(ResultInspection *Res)
{
	ResultBaseForAlgorithmRoot	*R=Res->GetResultBaseForAlgorithm(GetParentBase());
	if(R!=NULL){
		ResultBasePhase		*Rh=R->GetPageDataPhase(GetPhaseCode());
		if(Rh!=NULL){
			ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Rh->GetPageData(GetPage()));
			if(Rp!=NULL){
				ResultInLayerPLI	&RL=Rp->GetLayerData(GetLayer());
				return &RL;
			}
		}
	}
	return NULL;
}
bool    AlgorithmInLayerPLI::Save(QIODevice *f)
{
	if(AlgorithmInLayerRoot::Save(f)==false){
		return false;
	}
	int32	Ver=2;
	if(::Save(f,Ver)==false){
		return false;
	}
	int32	N=Data.GetNumber();
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int32	ItemClassType	=c->GetItemClassType();
		if(::Save(f,ItemClassType)==false){
			return false;
		}
		if(c->Save(f)==false){
            return(false);
		}
	}
    return(true);

}
bool    AlgorithmInLayerPLI::Load(QIODevice *f)
{
	if(AlgorithmInLayerRoot::Load(f)==false){
		return false;
	}
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	N;
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		int32	ItemClassType=0;
		if(Ver>=2){
			if(::Load(f,ItemClassType)==false){
				return false;
			}
		}
		static	int	DbgCounter=149208;
		static	int	TestDbg=0;
		if(i==DbgCounter){
			TestDbg++;
		}
		AlgorithmItemRoot	*c=CreateItem(ItemClassType);
		if(c==NULL){
			::SendErrorMessage(QString(/**/"CreateItem returns NULL in AlgorithmInLayerPLI::Load : ")+QString(typeid(*this).name())+QString(/**/" Arg : ")+QString::number(ItemClassType));
			return false;
		}
		((AlgorithmItemPLI *)c)->SetParent(this);
		if(c->Load(f,GetLayersBase())==false){
			::SendErrorMessage(QString(/**/"Item->Load returns false in AlgorithmInLayerPLI::Load : ")+QString(typeid(*this).name())+QString(/**/" Turn : ")+QString::number(i));
            return(false);
		}
		AppendItemFromLoad(c);
		if(c->GetID()>=StartItemID){
			StartItemID=c->GetID()+1;
		}
	}
	Changed=false;
    return(true);
}
bool    AlgorithmInLayerPLI::LoadByTransform(QIODevice *f ,TransformBase &Param)
{
	if(Load(f)==false){
		return false;
	}
	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),n++){
		if(c->Transform(Param)==false){
			::SendErrorMessage(QString(/**/"Item->Load returns false in AlgorithmInPagePLI::LoadByTransform : ")+QString(typeid(*this).name())+QString(/**/" Turn : ")+QString::number(n));
			return(false);
		}
	}
	Changed=false;
    return(true);
}
bool    AlgorithmInLayerPLI::LoadAppend(QIODevice *f)
{
	if(AlgorithmInLayerRoot::LoadAppend(f)==false){
		return false;
	}
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	N;
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		int32	ItemClassType=0;
		if(Ver>=2){
			if(::Load(f,ItemClassType)==false){
				return false;
			}
		}
		AlgorithmItemRoot	*c=CreateItem(ItemClassType);
		if(c==NULL){
			::SendErrorMessage(QString(/**/"CreateItem returns NULL in AlgorithmInLayerPLI::LoadAppend : ")+QString(typeid(*this).name())+QString(/**/" Arg : ")+QString::number(ItemClassType));
			return false;
		}
		((AlgorithmItemPLI *)c)->SetParent(this);
		if(c->Load(f,GetLayersBase())==false){
			::SendErrorMessage(QString(/**/"Item->Load returns false in AlgorithmInLayerPLI::LoadAppend : ")+QString(typeid(*this).name())+QString(/**/" Turn : ")+QString::number(i));
            return(false);
		}
		for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetID()==c->GetID()){
				c->SetID(StartItemID);
				StartItemID++;
			}
		}
		AppendItemFromLoad(c);
		if(c->GetID()>=StartItemID){
			StartItemID=c->GetID()+1;
		}
	}
	Changed=false;
    return(true);
}
	
bool	AlgorithmInLayerPLI::SaveHistgram(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	int32	N=Data.GetNumber();
	if(::Save(f,N)==false){
		return(false);
	}
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(::Save(f,c->GetID())==false){
			return(false);
		}		
		if(c->SaveHistgram(f)==false){
            return(false);
		}
	}
    return(true);
}

bool	AlgorithmInLayerPLI::LoadHistgram(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return(false);
	}

	FastSearchIDItemStart();
	for(int i=0;i<N;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false){
			return false;
		}
		AlgorithmItemRoot	*c=FastSearchIDItem(ItemID);
		if(c!=NULL){
			if(c->LoadHistgram(f)==false){
				return(false);
			}
		}
		else{
			AlgorithmDummyItem	Dummy;
			if(Dummy.LoadHistgram(f)==false){
				return(false);
			}
		}
	}
    return(true);
}

void	AlgorithmInLayerPLI::ClearHistgram(void)
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		c->ClearHistgram();
	}
}
bool	AlgorithmInLayerPLI::SaveOnlyThreshold(QIODevice *f)
{
	int32	N=GetItemCount();
	if(::Save(f,N)==false){
		return false;
	}

	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetThresholdBaseWritable()!=NULL){
			int32	ID=c->GetID();
			if(::Save(f,ID)==false){
				return false;
			}
			int32	ItemClassType=c->GetItemClassType();
			if(::Save(f,ItemClassType)==false){
				return false;
			}

			if(c->GetThresholdBaseWritable()->Save(f)==false){
				return false;
			}
		}
	}
	return true;
}
bool	AlgorithmInLayerPLI::LoadOnlyThreshold(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	FastSearchIDItemStart();
	for(int i=0;i<N;i++){
		int32	ID;
		if(::Load(f,ID)==false){
			return false;
		}
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return false;
		}
		AlgorithmItemRoot	*c=FastSearchIDItem(ID);
		if(c!=NULL){
			if(c->GetThresholdBaseWritable()->Load(f)==false){
				return false;
			}
		}
		else{
			AlgorithmItemRoot	*d=CreateItem(ItemClassType);
			if(d==NULL){
				return false;
			}
			AlgorithmThreshold	*t=d->CreateThresholdInstance();
			if(t==NULL){
				delete	d;
				return false;
			}
			if(t->Load(f)==false){
				delete	d;
				return false;
			}
			delete	d;
		}
	}
	return true;
}
struct	PriorityMapClass
{
	AlgorithmItemPLI	*Point;
	int					DrawingPriority;
	int					PriorityCode;
};

static	int	PriorityMapSortFunc(const void *a ,const void *b)
{
	if(((struct PriorityMapClass *)a)->PriorityCode<((struct PriorityMapClass *)b)->PriorityCode){
		return -1;
	}
	if (((struct PriorityMapClass*)a)->PriorityCode>((struct PriorityMapClass*)b)->PriorityCode) {
		return 1;
	}

	if(((struct PriorityMapClass *)a)->DrawingPriority>((struct PriorityMapClass *)b)->DrawingPriority){
		return -1;
	}
	if(((struct PriorityMapClass *)a)->DrawingPriority<((struct PriorityMapClass *)b)->DrawingPriority){
		return 1;
	}
	return 0;
}

bool	AlgorithmInLayerPLI::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}

	AlgorithmItemPointerListContainer	Container;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	x1,y1,x2,y2;
		c->GetXY(x1,y1,x2,y2);
		if(x1<0 || NewDotPerLine<=x2 || y1<0 || NewMaxLines<=y2){
			AlgorithmItemPointerList	*k=new AlgorithmItemPointerList(c);
			Container.AppendList(k);
		}
	}
	for(AlgorithmItemPointerList *k=Container.GetFirst();k!=NULL;k=k->GetNext()){
		RemoveItem(k->GetItem());
	}
	return Ret;
}
bool	AlgorithmInLayerPLI::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ReallocateMasterCount(CountMaster)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	AlgorithmInLayerPLI::CopyShadowAlgorithmLayer(ShadowTree *Child ,const AlgorithmInLayerRoot &SrcParent)
{
	bool	Ret=true;
	for(const AlgorithmItemPLI *c=((AlgorithmInLayerPLI *)&SrcParent)->GetFirstData();c!=NULL;c=c->GetNext()){
		if(Child->CopyShadowAlgorithmItem(this,*c)==false){
			Ret=false;
		}
	}
	return Ret;
}


void	AlgorithmInLayerPLI::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	N=Data.GetNumber();
	struct	PriorityMapClass	*PriorityMap=new struct	PriorityMapClass[N];
	int	k=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++){
		PriorityMap[k].Point=c;
		PriorityMap[k].DrawingPriority=0x60000000 | c->GetDrawPriprity(movx ,movy ,ZoomRate ,Attr);
		PriorityMap[k].PriorityCode=0;
		if(c->GetSelected()==true){
			PriorityMap[k].PriorityCode=1;
			PriorityMap[k].DrawingPriority &= ~0x20000000;
		}
		if(c->GetActive()==true){
			PriorityMap[k].PriorityCode=2;
			PriorityMap[k].DrawingPriority &= ~0x40000000;
		}
	}
	QSort(PriorityMap,N,sizeof(struct PriorityMapClass),PriorityMapSortFunc);

	if(N<100){
		for(int i=0;i<N;i++){
			PriorityMap[i].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		int	i=0;
		while(i<N){
			int	StartI=i;
			int	Priprity=PriorityMap[StartI].DrawingPriority;
			int	EndI=N;
			for(int h=StartI;h<N;h++){
				if(Priprity!=PriorityMap[h].DrawingPriority){
					EndI=h;
					break;
				}
			}
			int	iN=EndI-StartI;
			//#pragma omp parallel
			//{                                                
			//	#pragma omp for
				for(int h=0;h<iN;h++){
					int	n=StartI+h;
					PriorityMap[n].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
				}
			//}
			i+=iN;
		}
	}
	delete	[]PriorityMap;

	if(Attr!=NULL && Attr->ModeDrawRental==true){
		N=RentalData.GetNumber();
		PriorityMap=new struct	PriorityMapClass[N];
		int	k=0;
		for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext(),k++){
			PriorityMap[k].Point=c;
			PriorityMap[k].DrawingPriority=0x60000000 | c->GetDrawPriprity(movx ,movy ,ZoomRate ,Attr);
			PriorityMap[k].PriorityCode=0;
			if(c->GetSelected()==true){
				PriorityMap[k].PriorityCode=1;
				PriorityMap[k].DrawingPriority &= ~0x20000000;
			}
			if(c->GetActive()==true){
				PriorityMap[k].PriorityCode=2;
				PriorityMap[k].DrawingPriority &= ~0x40000000;
			}
		}
		QSort(PriorityMap,N,sizeof(struct PriorityMapClass),PriorityMapSortFunc);

		for(int i=0;i<N;i++){
			PriorityMap[i].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
		delete	[]PriorityMap;
	}
}
void	AlgorithmInLayerPLI::DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		c->DrawMove(dx,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
	MutexTemporaryItem.lock();
	for(ItemPointerList *L=TemporaryItemList.GetFirst();L!=NULL;L=L->GetNext()){
		L->ItemPointer->DrawMoveTemporary(L->Dx,L->Dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
	MutexTemporaryItem.unlock();
}
bool	AlgorithmInLayerPLI::DrawResult(ResultInLayerRoot *R,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	if(R!=NULL){
		ResultInLayerPLI	&Res=*((ResultInLayerPLI *)R);
		int	Numb=GetTotalItemCount();
		if(DrawResultTableNumb<Numb){
			int	N=0;
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
				if(N<Numb && N<Res.GetItemCount()){
					ResultInItemPLI		*r=Res.GetResultItem(N);
					a->DrawResult(r,IData ,PData ,MovX ,MovY ,ZoomRate);
				}
			}
			for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
				if(N<Res.GetItemCount()){
					ResultInItemPLI		*r=Res.GetResultItem(N);
					a->DrawResult(r,IData ,PData ,MovX ,MovY ,ZoomRate);
				}
			}
			return true;
		}
		else{
			int	N=0;
			if(Res.GetItemCount()>=0){
				for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
					DrawResultATable[N]=a;
					DrawResultRTable[N]=Res.GetResultItem(N);
				}
				for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
					DrawResultATable[N]=a;
					DrawResultRTable[N]=Res.GetResultItem(N);
				}
			}
			for(int i=0;i<N;i++){
				AlgorithmItemPLI	*a=DrawResultATable[i];
				ResultInItemPLI		*r=DrawResultRTable[i];
				if(a!=NULL && r!=NULL){
					a->DrawResult(r,IData ,PData ,MovX ,MovY ,ZoomRate);
				}
			}
		}
	}
	else{
		int	Numb=GetTotalItemCount();
		if(DrawResultTableNumb<Numb){
			int	N=0;
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
				if(N<Numb){
					a->DrawResult(NULL,IData ,PData ,MovX ,MovY ,ZoomRate);
				}
			}
			for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
				a->DrawResult(NULL,IData ,PData ,MovX ,MovY ,ZoomRate);
			}
			return true;
		}
		else{
			int	N=0;
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
				DrawResultATable[N]=a;
			}
			for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
				DrawResultATable[N]=a;
			}
			for(int i=0;i<N;i++){
				AlgorithmItemPLI	*a=DrawResultATable[i];
				if(a!=NULL){
					a->DrawResult(NULL,IData ,PData ,MovX ,MovY ,ZoomRate);
				}
			}
		}
	}

	return true;
}
bool	AlgorithmInLayerPLI::DrawResultItem(ResultInLayerRoot *R,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(R!=NULL){
		ResultInLayerPLI	&Res=*((ResultInLayerPLI *)R);
		int	Numb=GetItemCount();
		if(DrawResultTableNumb<Numb){
			int	N=0;
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
				if(N<Numb && N<Res.GetItemCount()){
					ResultInItemPLI		*r=Res.GetResultItem(N);
					a->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
				}
			}
			for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
				if(N<Res.GetItemCount()){
					ResultInItemPLI		*r=Res.GetResultItem(N);
					a->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
				}
			}
			return true;

		}
		int	N=0;
		if(Res.GetItemCount()>=0){
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
				DrawResultATable[N]=a;
				DrawResultRTable[N]=Res.GetResultItem(N);
			}
			for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
				DrawResultATable[N]=a;
				DrawResultRTable[N]=Res.GetResultItem(N);
			}
		}

		for(int i=0;i<N;i++){
			AlgorithmItemPLI	*a=DrawResultATable[i];
			ResultInItemPLI	*r=DrawResultRTable[i];
			if(a!=NULL && r!=NULL){
				a->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
			}
		}
	}
	else{
		int	Numb=GetItemCount();
		if(DrawResultTableNumb<Numb){
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
				a->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
			}
			for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext()){
				a->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
			}
			return true;

		}
		int	N=0;
		for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),N++){
			DrawResultATable[N]=a;
		}
		for(AlgorithmItemPLI *a=RentalData.GetFirst();a!=NULL;a=a->GetNext(),N++){
			DrawResultATable[N]=a;
		}

		for(int i=0;i<N;i++){
			AlgorithmItemPLI	*a=DrawResultATable[i];
			if(a!=NULL){
				a->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
			}
		}
	}

	return true;
}
void	AlgorithmInLayerPLI::DrawMonoBitmap(BYTE **BmpPoint)
{
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->DrawMonoBitmap(BmpPoint);
	}
}
void	AlgorithmInLayerPLI::DrawItems(QImage &IData ,QPainter &PData ,int movx ,int movy ,double ZoomRate,DWORD DrawType)
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetSelected()==true && ((DrawType&DrawType_Selected)!=0)){
			c->Draw(IData, movx ,movy ,ZoomRate ,NULL);
		}
		if(c->GetActive()==true && ((DrawType&DrawType_Active)!=0)){
			c->Draw(IData, movx ,movy ,ZoomRate ,NULL);
		}
	}
}
void	AlgorithmInLayerPLI::DrawResultItem(ResultInLayerRoot *R,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)
{
	if(R!=NULL){
		ResultInLayerPLI	&Res=*((ResultInLayerPLI *)R);
		int	N=0;
		int	Numb=GetItemCount();
		for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),N++){
			if(c->GetSelected()==true && ((DrawType&DrawType_Selected)!=0)
			&& N<Numb && N<Res.GetItemCount()){
				ResultInItemPLI		*r=Res.GetResultItem(N);
				c->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
			if(c->GetActive()==true && ((DrawType&DrawType_Active)!=0)
			&& N<Numb && N<Res.GetItemCount()){
				ResultInItemPLI		*r=Res.GetResultItem(N);
				c->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
		}
	}
	else{
		for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetSelected()==true && ((DrawType&DrawType_Selected)!=0)){
				c->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
			if(c->GetActive()==true && ((DrawType&DrawType_Active)!=0)){
				c->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
		}
	}
}
AlgorithmItemPLI	*AlgorithmInLayerPLI::GetItem(int localX ,int localY)
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->IsInclude(localX ,localY)==true){
			return c;
		}
	}
	return NULL;
}

AlgorithmItemRoot	*AlgorithmInLayerPLI::SearchIDItem(int itemID)	const
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetID()==itemID){
			return(c);
		}
	}
	return(NULL);
}
AlgorithmItemRoot	*AlgorithmInLayerPLI::SearchItemByName(const QString &ItemName)	const
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetItemName()==ItemName){
			return(c);
		}
	}
	return(NULL);
}
void	AlgorithmInLayerPLI::FastSearchIDItemStart(void)
{
	if(ItemDimPointer!=NULL){
		delete	[]ItemDimPointer;
	}
	ItemDimPointerNumb=Data.GetCount();
	ItemDimPointer=new AlgorithmItemRoot *[ItemDimPointerNumb];
	int	i=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),i++){
		ItemDimPointer[i]=c;
	}
	SortDimPointer();
}
ResultInItemRoot	*ResultInLayerPLI::CreateItem(void)
{	
	ResultInItemRoot	*r;
	AlgorithmInPageRoot	*a=GetAlgorithmInPage();
	if(a!=NULL){
		r=a->CreateResult();
	}
	else{
		r=new ResultInItemPLI();	
	}
	((ResultInItemPLI *)r)->SetParent(this);
	return r;
}
bool	AlgorithmInLayerPLI::AppendItem(AlgorithmItemRoot *item)
{
	((AlgorithmItemPLI *)item)->SetParent(this);
	((AlgorithmItemPLI *)item)->ItemID=GetIncStartItemID();
	item->SetOrigin(item->GetParentBase());
	Data.AppendList((AlgorithmItemPLI *)item);
	//item->GetArea().SetLimit(GetDotPerLine(),GetMaxLines());
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	item->SetEdited(true);
	Changed=true;
	CalcDone=false;
	return true;
}
bool	AlgorithmInLayerPLI::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	if(Layer==GetLayer()){
		return AppendItem(item);
	}
	return false;
}
bool	AlgorithmInLayerPLI::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	((AlgorithmItemPLI *)item)->SetParent(this);
	item->SetOrigin(item->GetParentBase());
	Data.AppendList((AlgorithmItemPLI *)item);
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	Changed=true;
	CalcDone=false;
	return true;
}

void	AlgorithmInLayerPLI::RemoveItem(AlgorithmItemRoot *item)
{
	Data.RemoveList((AlgorithmItemPLI *)item);
	Changed=true;
	CalcDone=false;
}

bool	AlgorithmInLayerPLI::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	((AlgorithmItemPLI *)item)->Parent=this;
	((AlgorithmItemPLI *)item)->ItemID=itemID;
	item->SetOrigin(item->GetParentBase());
	Data.AppendList((AlgorithmItemPLI *)item);
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	Changed=true;
	CalcDone=false;
	return true;
}
bool	AlgorithmInLayerPLI::AppendItems(AlgorithmItemPointerListContainer &items)
{
	for(AlgorithmItemPointerList *L=items.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmItemRoot	*Item=L->GetItem();
		AppendItem(Item);
		Changed=true;
	}
	return true;
}

bool	AlgorithmInLayerPLI::RemoveItems(AlgorithmItemPointerListContainer &items)
{
	for(AlgorithmItemPointerList *L=items.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmItemRoot	*Item=L->GetItem();
		RemoveItem(Item);
		delete	Item;
		Changed=true;
		L->SetPointer(NULL);
	}
	return true;
}
void	AlgorithmInLayerPLI::RemoveAllDatasByManual(bool CreatedManually)
{
	for(AlgorithmItemPLI	*p=GetFirstData();p!=NULL;){
		AlgorithmItemPLI	*NextP=p->GetNext();
		if(p->GetManualCreated()==CreatedManually){
			RemoveItem(p);
			delete	p;
			Changed=true;
		}
		p=NextP;
	}
}
void	AlgorithmInLayerPLI::RemoveAllDatasWithoutLocked(void)
{
	for(AlgorithmItemPLI	*p=GetFirstData();p!=NULL;){
		AlgorithmItemPLI	*NextP=p->GetNext();
		if(p->GetEditLocked()==false){
			RemoveItem(p);
			delete	p;
			Changed=true;
		}
		p=NextP;
	}
}
void	AlgorithmInLayerPLI::RemoveAllDatasWithoutManual(void)
{
	for(AlgorithmItemPLI	*p=GetFirstData();p!=NULL;){
		AlgorithmItemPLI	*NextP=p->GetNext();
		if(p->GetManualCreated()==false){
			RemoveItem(p);
			delete	p;
			Changed=true;
		}
		p=NextP;
	}
}
void	AlgorithmInLayerPLI::RemoveAllDatas(void)
{
	Data.RemoveAll();
	ClearStartItemID();
	Changed=true;
	CalcDone=false;
}
int64		AlgorithmInLayerPLI::GetMaxItemID(void)	const
{
	int64	MaxItemID=0;
	for(AlgorithmItemPLI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		if(p->GetID()>MaxItemID){
			MaxItemID=p->GetID();
		}
	}
	return MaxItemID;
}
void	AlgorithmInLayerPLI::InitialThreadBufferForExecute(void)
{
	int	iCalcThreadDataCount=GetTotalItemCount();
	int	N=(iCalcThreadDataCount+ThreadNumb-1)/ThreadNumb;
	
	if(CalcThreadDataCount!=iCalcThreadDataCount){
		CalcThreadDataCount=iCalcThreadDataCount;
		if(CalcThreadDim!=NULL){
			delete	[]CalcThreadDim;
		}
		CalcThreadDim	=new OMPAlgorithmItemStruct[ThreadNumb];
		for(int i=0;i<ThreadNumb;i++){
			CalcThreadDim[i].Alloc(this,i,N);
		}
	}
}
void	AlgorithmInLayerPLI::LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)
{
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		ItemFunc(c,Something);
	}
}

ExeResult	AlgorithmInLayerPLI::ExecuteInitialAfterEditPrev(int ExeID ,ResultInLayerRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	FastSearchIDItemStart();
	ExeResult	Ret=AlgorithmInLayerRoot::ExecuteInitialAfterEdit(ExeID ,R,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	InitialThreadBufferForExecute();
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;

	Res->Alloc(this);
	volatile	bool	RetryMode;

	FastSearchIDItemStart();
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase		*rPh=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(rPh->GetPageData(GetParentInPage()->GetPage()));
		if(Rp!=NULL){
			ResultInLayerPLI	&rLayer=Rp->GetLayerData(GetLayer());
			int	i=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && i<rLayer.GetItemCount();c=c->GetNext(),i++){
				c->SetCurrentResult(rLayer.GetResultItem(i));
			}
		}
	}

	if(GetParamGlobal()->CalcSingleThread==false && Data.GetCount()>4 && ModeParallel.ModeParallelExecuteInitialAfterEditPrev==true){
		AlgorithmItemPLI	*CDim[10000];
		AlgorithmItemPLI	**C=NULL;
		int	n;
		if(Data.GetCount()<sizeof(CDim)/sizeof(CDim[0])){
			n=0;
			for(AlgorithmItemPLI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				CDim[n]=t;
			}
			C=CDim;
		}
		else{
			C=new AlgorithmItemPLI *[Data.GetCount()];
			n=0;
			for(AlgorithmItemPLI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				C[n]=t;
			}
		}

		volatile	bool	RetryMode;
		do{
			RetryMode=false;

			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					AlgorithmItemPLI	*c=C[i];
					ExeResult	RR=c->ExecuteInitialAfterEditPrev(ExeID ,0,c->GetCurrentResult(),EInfo);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
		if(C!=CDim){
			delete	[]C;
		}
	}
	else{
		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
				ExeResult	RR=c->ExecuteInitialAfterEditPrev(ExeID ,0,c->GetCurrentResult(),EInfo);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	do{
		for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
			ExeResult	RR=c->ExecuteInitialAfterEditPrev(ExeID ,0,c->GetCurrentResult(),EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}
	}while(RetryMode==true);

	FastSearchIDItemStart();

	if(Ret==_ER_true){
		CalcDone=true;
		return Ret;
	}
	return Ret;
}

ExeResult	AlgorithmInLayerPLI::ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	FastSearchIDItemStart();
	ExeResult	Ret=AlgorithmInLayerRoot::ExecuteInitialAfterEdit(ExeID ,R,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	InitialThreadBufferForExecute();
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;

	Res->Alloc(this);
	volatile	bool	RetryMode;

	FastSearchIDItemStart();
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase		*rPh=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(rPh->GetPageData(GetParentInPage()->GetPage()));
		if(Rp!=NULL){
			ResultInLayerPLI	&rLayer=Rp->GetLayerData(GetLayer());
			int	i=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && i<rLayer.GetItemCount();c=c->GetNext(),i++){
				c->SetCurrentResult(rLayer.GetResultItem(i));
			}
		}
	}

	if(GetParamGlobal()->CalcSingleThread==false && Data.GetCount()>4 && ModeParallel.ModeParallelExecuteInitialAfterEdit==true){
		AlgorithmItemPLI	*CDim[10000];
		AlgorithmItemPLI	**C=NULL;
		int	n;
		if(Data.GetCount()<sizeof(CDim)/sizeof(CDim[0])){
			n=0;
			for(AlgorithmItemPLI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				CDim[n]=t;
			}
			C=CDim;
		}
		else{
			C=new AlgorithmItemPLI *[Data.GetCount()];
			n=0;
			for(AlgorithmItemPLI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				C[n]=t;
			}
		}

		volatile	bool	RetryMode;
		do{
			RetryMode=false;

			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					AlgorithmItemPLI	*c=C[i];
					ExeResult	RR=c->ExecuteInitialAfterEdit(ExeID ,0,c->GetCurrentResult(),EInfo);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
		if(C!=CDim){
			delete	[]C;
		}
	}
	else{
		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
				ExeResult	RR=c->ExecuteInitialAfterEdit(ExeID ,0,c->GetCurrentResult(),EInfo);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	do{
		for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
			ExeResult	RR=c->ExecuteInitialAfterEdit(ExeID ,0,c->GetCurrentResult(),EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}
	}while(RetryMode==true);

	FastSearchIDItemStart();

	if(GetParamGlobal()->MakeHistgramData==true){
		for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetMakeHistgramData()==false){	// && c->GetModeReferedAttr()==false){
				c->GetThresholdBaseWritable()->RegistHist();
				c->SetMakeHistgramData(true);
			}
		}
	}
	if(Ret==_ER_true){
		CalcDone=true;
		return Ret;
	}
	return Ret;
}

ExeResult	AlgorithmInLayerPLI::ExecuteInitialAfterEditPost(int ExeID ,ResultInLayerRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	FastSearchIDItemStart();
	ExeResult	Ret=AlgorithmInLayerRoot::ExecuteInitialAfterEditPost(ExeID ,R,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	InitialThreadBufferForExecute();
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;

	Res->Alloc(this);
	volatile	bool	RetryMode;

	FastSearchIDItemStart();
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase		*rPh=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(rPh->GetPageData(GetParentInPage()->GetPage()));
		if(Rp!=NULL){
			ResultInLayerPLI	&rLayer=Rp->GetLayerData(GetLayer());
			int	i=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && i<rLayer.GetItemCount();c=c->GetNext(),i++){
				c->SetCurrentResult(rLayer.GetResultItem(i));
			}
		}
	}

	if(GetParamGlobal()->CalcSingleThread==false && Data.GetCount()>4 && ModeParallel.ModeParallelExecuteInitialAfterEditPost==true){
		AlgorithmItemPLI	*CDim[10000];
		AlgorithmItemPLI	**C=NULL;
		int	n;
		if(Data.GetCount()<sizeof(CDim)/sizeof(CDim[0])){
			n=0;
			for(AlgorithmItemPLI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				CDim[n]=t;
			}
			C=CDim;
		}
		else{
			C=new AlgorithmItemPLI *[Data.GetCount()];
			n=0;
			for(AlgorithmItemPLI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				C[n]=t;
			}
		}

		volatile	bool	RetryMode;
		do{
			RetryMode=false;

			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					AlgorithmItemPLI	*c=C[i];
					ExeResult	RR=c->ExecuteInitialAfterEditPost(ExeID ,0,c->GetCurrentResult(),EInfo);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
		if(C!=CDim){
			delete	[]C;
		}
	}
	else{
		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
				ExeResult	RR=c->ExecuteInitialAfterEditPost(ExeID ,0,c->GetCurrentResult(),EInfo);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	do{
		for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
			ExeResult	RR=c->ExecuteInitialAfterEditPost(ExeID ,0,c->GetCurrentResult(),EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}
	}while(RetryMode==true);

	FastSearchIDItemStart();

	if(Ret==_ER_true){
		CalcDone=true;
		return Ret;
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;

	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecuteStartByInspection==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteStartByInspection(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;

			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteStartByInspection(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;

			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteStartByInspection(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecuteCaptured(int ExeID ,ResultInLayerRoot *R,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false
	&& n>=MIN_COUNT_ForTHREAD
	&& ThreadNumb>=MIN_COUNT_ForTHREAD
	&& ModeParallel.ModeParallelExecuteCaptured==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteCaptured(ExeID,CapturedList);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteCaptured(ExeID ,0,Res->GetResultItem(n),CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteCaptured(ExeID ,0,Res->GetResultItem(n),CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecutePreAlignment		(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePreAlignment==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePreAlignment(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreAlignment(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreAlignment(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecuteAlignment		(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecuteAlignment==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic) 
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteAlignment(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteAlignment(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteAlignment(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecutePreProcessing	(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePreProcessing==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePreProcessing(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreProcessing	(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;
			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreProcessing(ExeID ,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}	
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}


ExeResult	AlgorithmInLayerPLI::ExecuteProcessing		(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	if(GetParamGlobal()->KeepFilteredImage==false){
		GetDataInLayer()->CreateAndCopyTempTargetBuff();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecuteProcessing==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteProcessing(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);


		if(GetParamGlobal()->KeepFilteredImage==false){
			GetDataInLayer()->CopyTempToTargetBuff();
		}
	}
	else{
		DWORD	StartMilisec=GetLayersBase()->GetStartInspectionTimeMilisec();
		int		MaxInspectMilisec=GetParamGlobal()->MaxInspectMilisec;
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				DWORD	NowTime=::GetComputerMiliSec();
				if(GetNGCounter()<=GetParamGlobal()->MaxNGCountsPerCam
				&& NowTime-StartMilisec<=MaxInspectMilisec
				&& c->IsEffective()==true){
					ResultInItemPLI	*r=Res->GetResultItem(n);
					r->SetAlgorithmItem(c);
					ExeResult	RR=c->ExecuteProcessing(ExeID ,0,r);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
					if(c->GetInvertLogic()==true){
						if(r->GetError()==1){
							r->SetError(2);
						}
						else if(r->GetError()>=2){
							r->SetError(1);
						}
						if(r->GetPosListFirst()==NULL){
							int	cx,cy;
							c->GetCenter(cx,cy);
							r->GetPosList().AppendList(new ResultPosList(cx,cy));
						}
					}
					IncrementNGCounterWithMutex(r->GetError());
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;

			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ResultInItemPLI	*r=Res->GetResultItem(n);
				r->SetAlgorithmItem(c);
				ExeResult	RR=c->ExecuteProcessing(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		if(GetParamGlobal()->KeepFilteredImage==false){
			GetDataInLayer()->CopyTempToTargetBuff();
		}
	}
	if(GetParamGlobal()->KeepFilteredImage==false){
		GetDataInLayer()->ReleaseTempTargetBuff();
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecuteProcessingRevived(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	if(GetParamGlobal()->KeepFilteredImage==false){
		GetDataInLayer()->CreateAndCopyTempTargetBuff();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}

	//‰æ‘œ‚ðØ‚è‘Ö‚¦‚é‚½‚ßAOpenMP‚É‚Å‚«‚È‚¢
	DWORD	StartMilisec=GetLayersBase()->GetStartInspectionTimeMilisec();
	int		MaxInspectMilisec=GetParamGlobal()->MaxInspectMilisec;

	/*
	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
		DWORD	NowTime=GetComputerMiliSec();
		if(GetNGCounter()<GetParamGlobal()->MaxNGCountsPerCam
		&& NowTime-StartMilisec<MaxInspectMilisec
		&& c->IsEffective()==true){
			LearningImage	*LF=GetDataInPage()->Find(c->LearningIDTime);
			if(LF!=NULL){
				GetDataInPage()->AddShowingLearningImageMaster(LF);

				if(c->ExecuteProcessingRevived(0,Res->GetResultItem(n) ,pInspectionData)==false){
					Ret++;
				}
				if(c->GetInvertLogic()==true){
					if(Res->GetResultItem(n)->GetError()==1){
						Res->GetResultItem(n)->SetError(2);
					}
						else if(Res->GetResultItem(n)->GetError()>=2){
						Res->GetResultItem(n)->SetError(1);
					}
					if(Res->GetResultItem(n)->GetPosListFirst()==NULL){
						int	cx,cy;
						c->GetCenter(cx,cy);
						Res->GetResultItem(n)->GetPosList().AppendList(new ResultPosList(cx,cy));
					}
				}
				if(GetParamGlobal()->KeepFilteredImage==false){
					GetDataInLayer()->CopyTempToTargetBuff();
				}
				GetDataInPage()->RestoreAllLearningImageMaster();
			}
		}
	}
	*/
	if(GetParamGlobal()->KeepFilteredImage==false){
		GetDataInLayer()->ReleaseTempTargetBuff();
	}
	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecutePostProcessing	(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePostProcessing==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePostProcessing(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePostProcessing(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;

			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePostProcessing(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecutePreScanning	(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>1 && ThreadNumb>1 && ModeParallel.ModeParallelExecutePreScanning==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePreScanning(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreScanning(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;

			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreScanning(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecuteScanning	(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>1 && ThreadNumb>1 && ModeParallel.ModeParallelExecuteScanning==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic) 
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteScanning(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecuteScanning(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;

			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreScanning(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInLayerPLI::ExecutePostScanning	(int ExeID ,ResultInLayerRoot *R)
{
	ExeResult	Ret=_ER_true;
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;

	int	n=0;
	for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,Res->GetResultItem(n));
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>1 && ThreadNumb>1 && ModeParallel.ModeParallelExecutePostScanning==true){
		bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePostScanning(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			n=0;
			for(AlgorithmItemPLI *c=Data.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePostScanning(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		do{
			RetryMode=false;

			for(AlgorithmItemPLI *c=RentalData.GetFirst();c!=NULL && n<Res->GetItemCount();c=c->GetNext(),n++){
				ExeResult	RR=c->ExecutePreScanning(ExeID,0,Res->GetResultItem(n));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}

void	AlgorithmInLayerPLI::MoveForAlignment(void)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->EnableMoveForAlignment==true){
		for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
			L->MoveForAlignment();
		}
		RemoveInvalidItems();
	}
}
void	AlgorithmInLayerPLI::RemoveInvalidItems(void)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI *NextL=L->GetNext();
		if(L->IsValid()==false){
			RemoveItem(L);
		}
		L=NextL;
	}
}

void	AlgorithmInLayerPLI::RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->RefreshByMap(Mode,Map);
	}
}
void	AlgorithmInLayerPLI::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
	MatrixBuffClear(Dst ,0,XByte,YLen);
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true){
			a->GetArea().MakeBitData(Dst,XLen,YLen);
		}
		else{
			a->GetArea().MakeNotBitData(Dst,XLen,YLen);
		}
	}
}

void	AlgorithmInLayerPLI::ReleaseAllSelectedItem(void)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->SetSelected(false);
	}
}
void	AlgorithmInLayerPLI::SelectAll(void)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->SetSelected(true);
	}
}
void	AlgorithmInLayerPLI::SelectItems(const IntList &ItemIDs)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(ItemIDs.IsInclude(L->GetID())==true){
			L->SetSelected(true);
		}
	}
}
void	AlgorithmInLayerPLI::SelectLocked(void)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetEditLocked()==true){
			L->SetSelected(true);
		}
		else{
			L->SetSelected(false);
		}
	}
}
void	AlgorithmInLayerPLI::SelectLibs(AlgorithmLibraryListContainer &SelectedList)
{
	for(AlgorithmLibraryList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
		for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==a->GetLibID()){
				L->SetSelected(true);
			}
		}
	}
}
void	AlgorithmInLayerPLI::SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->IsOriginTypeSelection(SelectMode)==true){
			L->SetSelected(true);
		}
		else{
			L->SetSelected(false);
		}
	}
}
void	AlgorithmInLayerPLI::SelectArea(FlexArea &localArea,bool MultiSelect)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetVisible()==true){
			if(L->IsCrossed(&localArea)==true){
				L->SetSelected(true);
			}
			else if(L->GetVector()!=NULL){
				if(L->GetVector()->CheckOverlap(localArea)==true){
					L->SetSelected(true);
				}
			}
		}
	}
}
void	AlgorithmInLayerPLI::SelectPoint(int localX, int localY)
{
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetVisible()==true){
			if(L->GetArea().IsInclude(localX, localY)==true){
				L->SetSelected(true);
			}
			else if(L->GetVector()!=NULL){
				if(L->GetVector()->GetDistance(localX,localY)<3){
					L->SetSelected(true);
				}
			}
		}
	}
}

class	IDXYList : public NPList<IDXYList>
{
public:
	int	ID,Cx,Cy;
	IDXYList(void){}
	IDXYList(int id ,int cx,int cy):ID(id),Cx(cx),Cy(cy){}
};

void	AlgorithmInLayerPLI::CutArea(FlexArea &localArea,bool MultiSelect,const QByteArray &Something)
{
	int	N=GetItemCount();
	AlgorithmItemPLI **Pointer=new AlgorithmItemPLI *[N];
	int	k=0;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL && k<N;L=L->GetNext(),k++){
		Pointer[k]=L;
	}
	bool	FoundSelected=false;
	#pragma omp parallel                             
	{                                                
		#pragma omp for schedule(dynamic)
		for(int i=0;i<N;i++){
			AlgorithmItemPLI *L=Pointer[i];
			if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
				FoundSelected=true;
			}
		}
	}

	NPListPack<IDXYList>	ChangesIDList;
	if(FoundSelected==false){
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for schedule(dynamic)
			for(int i=0;i<N;i++){
				AlgorithmItemPLI *L=Pointer[i];
				bool	_Changed;
				int	cx,cy;
				L->GetMultiSelectOrign(cx,cy);
				L->CutArea(localArea,_Changed);
				if(_Changed==true){
					Changed=true;
					CalcDone=false;

					if(MultiSelect==true && L->GetSelected()==true){
						#pragma omp critical
						{
							ChangesIDList.AppendList(new IDXYList(i,cx,cy));
						}
					}
				}
			}
		//}
	}
	else{
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for schedule(dynamic)
			for(int i=0;i<N;i++){
				AlgorithmItemPLI *L=Pointer[i];
				if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
					bool	_Changed;
					int	cx,cy;
					L->GetMultiSelectOrign(cx,cy);
					L->CutArea(localArea,_Changed);
					if(_Changed==true){
						Changed=true;
						CalcDone=false;

						if(MultiSelect==true && L->GetSelected()==true){
							#pragma omp critical
							{
								ChangesIDList.AppendList(new IDXYList(i,cx,cy));
							}
						}
					}
				}
			}
		//}
	}
	if(MultiSelect==true){
		for(IDXYList *c=ChangesIDList.GetFirst();c!=NULL;c=c->GetNext()){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for schedule(dynamic)
				for(int i=0;i<N;i++){
					AlgorithmItemPLI *L=Pointer[i];
					if(L->GetSelected()==true){
						bool	Found=false;
						for(IDXYList *d=ChangesIDList.GetFirst();d!=NULL;d=d->GetNext()){
							if(d->ID==i){
								Found=true;
								break;
							}
						}
						if(Found==false){
							int	cx,cy;
							L->GetMultiSelectOrign(cx,cy);
							FlexArea	A=localArea;
							A.MoveToNoClip(cx-c->Cx,cy-c->Cy);

							bool	_Changed;
							L->CutArea(A,_Changed);
							if(_Changed==true){
								Changed=true;
								CalcDone=false;
							}
						}
					}
				}
			//}
		}
	}
	delete	[]Pointer;

	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI *NextL=L->GetNext();
		if(L->IsNull()==true){
			RemoveItem(L);
		}
		L=NextL;
	}
}


void	AlgorithmInLayerPLI::SeparateItems(FlexArea &localArea)
{
	int	N=GetItemCount();
	AlgorithmItemPLI **Pointer=new AlgorithmItemPLI *[N];
	int	k=0;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL && k<N;L=L->GetNext(),k++){
		Pointer[k]=L;
	}
	bool	FoundSelected=false;
	#pragma omp parallel                             
	{                                                
		#pragma omp for schedule(dynamic)
		for(int i=0;i<N;i++){
			AlgorithmItemPLI *L=Pointer[i];
			if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
				FoundSelected=true;
			}
		}
	}
	AlgorithmItemPointerListContainer	AddedItemsContainer;
	if(FoundSelected==false){
		for(int i=0;i<N;i++){
			AlgorithmItemPLI *L=Pointer[i];
			if(L->GetArea().CheckOverlap(&localArea)==true){
				AlgorithmItemRoot	*v=L->SeparateItem(localArea);
				if(v!=NULL){
					AddedItemsContainer.Add(v);
				}
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			AlgorithmItemPLI *L=Pointer[i];
			if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
				AlgorithmItemRoot	*v=L->SeparateItem(localArea);
				if(v!=NULL){
					AddedItemsContainer.Add(v);
				}
			}
		}
	}
	for(AlgorithmItemPointerList *p=AddedItemsContainer.GetFirst();p!=NULL;p=p->GetNext()){
		AppendItem(p->GetItem());
	}

	delete	[]Pointer;
}

void	AlgorithmInLayerPLI::RegistArea(FlexArea &localArea)
{
}

void	AlgorithmInLayerPLI::MasterImageHasChanged(void)
{
	for(AlgorithmItemPLI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->MasterImageHasChanged();
	}
}

void	AlgorithmInLayerPLI::DeleteSelectedItems(void)
{
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoDeleteSelectedItems);
	int32	ItemCount=0;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true && L->GetEditLocked()==false && L->GetVisible()==true){
			ItemCount++;
		}
	}
	::Save(UndoPointer->GetWritePointer(),ItemCount);

	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI *NextL=L->GetNext();
		if(L->GetSelected()==true && L->GetEditLocked()==false && L->GetVisible()==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			L->Save(UndoPointer->GetWritePointer());
			SetChanged();
			RemoveItem(L);
			delete	L;
			Changed=true;
			CalcDone =false;
		}
		L=NextL;
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInLayerPLI::UndoDeleteSelectedItems(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false){
		return;
	}

	for(int i=0;i<ItemCount;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return;
		}
		AlgorithmItemRoot	*L=CreateItem(ItemClassType);
		if(L->Load(f,GetLayersBase())==false){
			delete	L;
			return;
		}
		AppendItem(L);
	}
	Changed=true;
	CalcDone=false;	
}

void	AlgorithmInLayerPLI::LockSelectedItems(void)
{
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoLockSelectedItems);
	int32	ItemCount=GetItemCount();
	::Save(UndoPointer->GetWritePointer(),ItemCount);

	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		int32	ItemID=L->GetID();
		bool	Locked=L->GetEditLocked();
		::Save(UndoPointer->GetWritePointer(),ItemID);
		::Save(UndoPointer->GetWritePointer(),Locked);

		if(L->GetSelected()==true){
			L->SetEditLocked(true);
		}
		else{
			L->SetEditLocked(false);
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInLayerPLI::UndoLockSelectedItems(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false){
		return;
	}
	FastSearchIDItemStart();
	for(int i=0;i<ItemCount;i++){
		int32	ItemID;
		bool	Locked;
		if(::Load(f,ItemID)==false){
			return;
		}
		if(::Load(f,Locked)==false){
			return;
		}
		AlgorithmItemRoot	*L=FastSearchIDItem(ItemID);
		if(L!=NULL){
			L->SetEditLocked(Locked);
		}
	}
}

void	AlgorithmInLayerPLI::UnlockAll(void)
{
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoUnlockAll);
	int32	ItemCount=GetItemCount();
	::Save(UndoPointer->GetWritePointer(),ItemCount);

	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		int32	ItemID=L->GetID();
		bool	Locked=L->GetEditLocked();
		::Save(UndoPointer->GetWritePointer(),ItemID);
		::Save(UndoPointer->GetWritePointer(),Locked);

		L->SetEditLocked(false);
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}

void	AlgorithmInLayerPLI::UndoUnlockAll(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false){
		return;
	}
	FastSearchIDItemStart();
	for(int i=0;i<ItemCount;i++){
		int32	ItemID;
		bool	Locked;
		if(::Load(f,ItemID)==false){
			return;
		}
		if(::Load(f,Locked)==false){
			return;
		}
		AlgorithmItemRoot	*L=FastSearchIDItem(ItemID);
		if(L!=NULL){
			L->SetEditLocked(Locked);
		}
	}
}

void	AlgorithmInLayerPLI::BindSelectedItems(void)
{
	AlgorithmItemPLI *Seed=NULL;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true){
			Seed=L;
			break;
		}
	}
	if(Seed==NULL){
		return;
	}
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoBindSelectedItems);
	int32	ItemID=Seed->GetID();
	::Save(UndoPointer->GetWritePointer(),ItemID);
	Seed->Save(UndoPointer->GetWritePointer());

	int32	SelectedCount=0;
	for(AlgorithmItemPLI *L=Seed->GetNext();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true){
			SelectedCount++;
		}
	}
	::Save(UndoPointer->GetWritePointer(),SelectedCount);

	for(AlgorithmItemPLI *L=Seed->GetNext();L!=NULL;){
		AlgorithmItemPLI *NextL=L->GetNext();
		if(L->GetSelected()==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			L->Save(UndoPointer->GetWritePointer());

			FlexArea	A=Seed->GetArea();
			A+=L->GetArea();
			Seed->SetArea(A);
			RemoveItem(L);
			Changed=true;
			CalcDone=false;
		}
		L=NextL;	
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}

void	AlgorithmInLayerPLI::UndoBindSelectedItems(QIODevice *f)
{
	int32	ItemID;
	if(::Load(f,ItemID)==false){
		return;
	}
	AlgorithmItemRoot	*L=SearchIDItem(ItemID);
	if(L!=NULL){
		if(L->Load(f,GetLayersBase())==false){
			return;
		}
		int32	SelectedCount;
		if(::Load(f,SelectedCount)==false){
			return;
		}

		for(int i=0;i<SelectedCount;i++){
			int32	ItemClassType;
			if(::Load(f,ItemClassType)==false){
				return;
			}
			AlgorithmItemRoot	*L=CreateItem(ItemClassType);
			if(L->Load(f,GetLayersBase())==false){
				delete	L;
				return;
			}
			AppendItem(L);
		}
		Changed=true;
		CalcDone=false;
	}
}

void	AlgorithmInLayerPLI::Activate(int localX ,int localY ,ListLayerAndIDPack &RetItem)
{
	int	Numb=GetItemCount();
	AlgorithmItemPLI **ADim=new AlgorithmItemPLI *[Numb];
	int	k=0;
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			if(ADim[i]->IsInclude(localX,localY)==true){
				ADim[i]->SetActive(true);
			}
			else{
				ADim[i]->SetActive(false);
			}
		}
	}
	for(int i=0;i<Numb;i++){
		if(ADim[i]->GetActive()==true){
			RetItem.AppendList(new ListLayerAndID(GetLayer(),ADim[i]->GetID()));
		}
	}
	delete	[]ADim;
}

void	AlgorithmInLayerPLI::Activate(int ItemID)
{
	int	Numb=GetItemCount();
	AlgorithmItemPLI **ADim=new AlgorithmItemPLI *[Numb];
	int	k=0;
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			if(ADim[i]->GetID()==ItemID){
				ADim[i]->SetActive(true);
			}
			else{
				ADim[i]->SetActive(false);
			}
		}
	}
	delete	[]ADim;
}
void	AlgorithmInLayerPLI::AddActivate(int ItemID)
{
	int	Numb=GetItemCount();
	AlgorithmItemPLI **ADim=new AlgorithmItemPLI *[Numb];
	int	k=0;
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			if(ADim[i]->GetID()==ItemID){
				ADim[i]->SetActive(true);
			}
		}
	}
	delete	[]ADim;
}
void	AlgorithmInLayerPLI::Inactivate(void)
{
	int	Numb=GetItemCount();
	AlgorithmItemPLI **ADim=new AlgorithmItemPLI *[Numb];
	int	k=0;
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			ADim[i]->SetActive(false);
		}
	}
	delete	[]ADim;
}

void		AlgorithmInLayerPLI::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	TransmitDirectly(packet);
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}

void	AlgorithmInLayerPLI::MakeIndependentItems(bool SubResultMoving, ResultInLayerRoot *RLayer ,int localX ,int localY,AlgorithmItemIndependentPack &AData)
{
	if(RLayer!=NULL){
		ResultInLayerPLI	*RL=dynamic_cast<ResultInLayerPLI *>(RLayer);
		if(RL!=NULL){
			if(RL->GetItemCount()<0){
				RL->Alloc(this);
			}
			FastSearchIDItemStart();
			RL->SortResultDimPointer();
			for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
				ResultInItemRoot	*RItem=NULL;
				if(SubResultMoving==true && RL!=NULL){
					RItem=RL->FastSearchIDItem(L->GetID());
				}
				double	RetDistance;
				if((RItem!=NULL && L->IsInclude(localX-RItem->GetTotalShiftedX(),localY-RItem->GetTotalShiftedY())==true)
				|| (RItem!=NULL && L->GetVector()!=NULL &&  L->GetVector()->GetDistance( localX-(RItem->GetAlignedX()+RItem->GetItemSearchedX())
																						,localY-(RItem->GetAlignedY()+RItem->GetItemSearchedY()))<10)
				|| (RItem!=NULL && RItem->GetDistanceVector	(localX,localY,RetDistance)==true && RetDistance<10)
				|| (RItem!=NULL && RItem->GetDistanceArea	(localX,localY,RetDistance)==true && RetDistance<10)
				|| (RItem==NULL && L->IsInclude(localX,localY)==true)){
					AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(GetLayersBase());
					A->Data=CreateItem(L->GetItemClassType());
					((AlgorithmItemPLI *)(A->Data))->SetParent(this);
					*A->Data	=*L;
					A->PhaseCode=L->GetPhaseCode();
					A->Layer	=GetLayer();
					A->ItemID	=L->GetID();
					A->LibID	=L->GetLibID();
					A->Result	=(RItem!=NULL)?RItem->GetError():-1;
					A->ItemClassType=L->GetItemClassType();
					A->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetParentInPage()->GetPage());
					GetParentBase()->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
					L->MakeIndependentItems(A,localX,localY);
					AData.Items.AppendList(A);
				}
			}
			for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
				ResultInItemRoot	*RItem=NULL;
				if(SubResultMoving==true && RL!=NULL){
					RItem=RL->FastSearchIDItem(L->GetID());
				}
				double	RetDistance;
				if((RItem!=NULL && L->IsInclude(localX-RItem->GetTotalShiftedX(),localY-RItem->GetTotalShiftedY())==true)
				|| (RItem!=NULL && L->GetVector()!=NULL &&  L->GetVector()->GetDistance( localX-(RItem->GetAlignedX()+RItem->GetItemSearchedX())
																						,localY-(RItem->GetAlignedY()+RItem->GetItemSearchedY()))<10)
				|| (RItem!=NULL && RItem->GetDistanceVector	(localX,localY,RetDistance)==true && RetDistance<10)
				|| (RItem!=NULL && RItem->GetDistanceArea	(localX,localY,RetDistance)==true && RetDistance<10)
				|| (RItem==NULL && L->IsInclude(localX,localY)==true)){
					AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(GetLayersBase());
					A->Data=CreateItem(L->GetItemClassType());
					((AlgorithmItemPLI *)(A->Data))->SetParent(this);
					*A->Data	=*L;
					A->PhaseCode=L->GetPhaseCode();
					A->Layer	=GetLayer();
					A->ItemID	=L->GetID();
					A->LibID	=L->GetLibID();
					A->Result	=(RItem!=NULL)?RItem->GetError():-1;
					A->ItemClassType=L->GetItemClassType();
					A->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetParentInPage()->GetPage());
					GetParentBase()->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
					L->MakeIndependentItems(A,localX,localY);
					AData.Items.AppendList(A);
				}
			}
		}
	}
}

void	AlgorithmInLayerPLI::MakeIndependentItems(IntList &Items,AlgorithmItemIndependentPack &Data)
{
	FastSearchIDItemStart();
	for(IntClass *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		AlgorithmItemRoot *L=FastSearchIDItem(d->GetValue());
		if(L!=NULL){
			AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(GetLayersBase());
			A->Data=CreateItem(L->GetItemClassType());
			((AlgorithmItemPLI *)(A->Data))->SetParent(this);
			*A->Data	=*L;
			A->PhaseCode=L->GetPhaseCode();
			A->Layer	=GetLayer();
			A->ItemID	=L->GetID();
			A->LibID	=L->GetLibID();
			A->ItemClassType=L->GetItemClassType();
			A->Result	=(L->GetCurrentResult()!=NULL)?L->GetCurrentResult()->GetError():-1;
			A->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			GetParentBase()->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
			Data.Items.AppendList(A);
		}
	}
}
void	AlgorithmInLayerPLI::SetIndependentItemData(int32 Command
													,int32 LocalPage,int32 Layer,int32 ItemID
													,AlgorithmItemRoot *item
													,IntList &EdittedMemberID
													,QByteArray &Something
													,QByteArray &AckData)
{
	if(item==NULL){
		item=SearchIDItem(ItemID);
	}
	if(item!=NULL){
		for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
			L->SetIndependentItemData(Command,LocalPage,Layer,item,EdittedMemberID,Something,AckData);
		}
		for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
			L->SetIndependentItemData(Command,LocalPage,Layer,item,EdittedMemberID,Something,AckData);
		}
	}
}
bool	AlgorithmInLayerPLI::GeneralDataRelease(int32 Command,void *data)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataRelease(Command,data)==false){
			return false;
		}
	}
	for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataRelease(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	*AlgorithmInLayerPLI::GeneralDataCreate(int32 Command,void *reqData)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		void	*ret=L->GeneralDataCreate(Command,reqData);
		if(ret!=NULL){
			return ret;
		}
	}
	for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
		void	*ret=L->GeneralDataCreate(Command,reqData);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}
bool	AlgorithmInLayerPLI::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataLoad(f,Command,data)==false){
			return false;
		}
	}
	for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataLoad(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInLayerPLI::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataSave(f,Command,data)==false){
			return false;
		}
	}
	for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataSave(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInLayerPLI::GeneralDataReply(int32 Command,void *data)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataReply(Command,data)==false){
			return false;
		}
	}
	for(AlgorithmItemPLI *L=RentalData.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataReply(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInLayerPLI::ExecuteCopy(ClipboardAlgorithm &Pack)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		ClipboardAlgorithmItem	*C=L->CreateClipboardItem();
		if(C!=NULL){
			Pack.Items.AppendList(C);
		}
	}
}
int		AlgorithmInLayerPLI::GetSelectedItemCount(void)
{
	int	ret=0;
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true){
			ret++;
		}
	}
	return ret;
}
void	AlgorithmInLayerPLI::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	int	N=0;
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true){
			N++;
		}
	}
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoExecuteMove);
	::Save(UndoPointer->GetWritePointer(),N);
	::Save(UndoPointer->GetWritePointer(),GlobalDx);
	::Save(UndoPointer->GetWritePointer(),GlobalDy);

	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			int	ItemID=L->GetID();
			::Save(UndoPointer->GetWritePointer(),ItemID);
			L->Save(UndoPointer->GetWritePointer());

			L->ExecuteMove(GlobalDx,GlobalDy,AllItems);
			if(L->IsNull()==true){
				AlgorithmItemPLI *NextL=L->GetNext();
				RemoveItem(L);
				delete	L;
				L=NextL;
			}
			else{
				L=L->GetNext();
			}
			Changed=true;
			CalcDone=false;
		}
		else{
			L=L->GetNext();
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInLayerPLI::ExecuteMove(int GlobalDx,int GlobalDy,IntList &Items,bool AllItems)
{
	int	N=0;
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true && Items.IsInclude(L->GetID())==true){
			N++;
		}
	}
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoExecuteMove);
	::Save(UndoPointer->GetWritePointer(),N);
	::Save(UndoPointer->GetWritePointer(),GlobalDx);
	::Save(UndoPointer->GetWritePointer(),GlobalDy);

	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true && Items.IsInclude(L->GetID())==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			int	ItemID=L->GetID();
			::Save(UndoPointer->GetWritePointer(),ItemID);
			L->Save(UndoPointer->GetWritePointer());

			L->ExecuteMove(GlobalDx,GlobalDy,AllItems);
			if(L->IsNull()==true){
				AlgorithmItemPLI *NextL=L->GetNext();
				RemoveItem(L);
				delete	L;
				L=NextL;
			}
			else{
				L=L->GetNext();
			}
			Changed=true;
			CalcDone=false;
		}
		else{
			L=L->GetNext();
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInLayerPLI::UndoExecuteMove(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false){
		return;
	}
	int	GlobalDx,GlobalDy;
	if(::Load(f,GlobalDx)==false){
		return;
	}
	if(::Load(f,GlobalDy)==false){
		return;
	}

	FastSearchIDItemStart();
	for(int i=0;i<N;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return;
		}
		int	ItemID;
		if(::Load(f,ItemID)==false){
			return;
		}
		AlgorithmItemRoot	*L=FastSearchIDItem(ItemID);
		if(L!=NULL){
			if(L->Load(f,GetLayersBase())==false){
				return;
			}
		}
		else{
			L=CreateItem(ItemClassType);
			if(L!=NULL){
				if(L->Load(f,GetLayersBase())==false){
					return;
				}
				AppendItem(L,ItemID);
			}
		}
	}
}
void	AlgorithmInLayerPLI::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true){
			L->GetPageListForExecuteMove(PageList ,GlobalDx,GlobalDy);
		}
	}
}

void	AlgorithmInLayerPLI::GetItemIDListOnPoint(int localX,int localY,IntList &RetList)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsInclude(localX,localY)==true && L->GetVisible()==true){
			RetList.Add(L->GetID());
		}
	}
}

void	AlgorithmInLayerPLI::GetItemIDListOnPoint(FlexArea &CoveredArea,IntList &RetList)
{
	for(AlgorithmItemPLI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsCrossed(&CoveredArea)==true){
			RetList.Add(L->GetID());
		}
	}
}


void	AlgorithmInLayerPLI::CopyFrom(AlgorithmInPageRoot *DestParent
									  ,AlgorithmInLayerRoot *src 
										,int OffsetX,int OffsetY
										,int PartsMaster ,int PartsID
										,bool ReferedThresholdMode)
{
	Parent=(AlgorithmInPagePLI *)DestParent;
	LayersBase	*DestBase=DestParent->GetLayersBase();
	AlgorithmInLayerPLI	*srcD=dynamic_cast<AlgorithmInLayerPLI *>(src);
	if(srcD!=NULL){
		int	N=srcD->GetItemCount();
		AlgorithmItemPLI **ItemList=new AlgorithmItemPLI*[N];
		AlgorithmItemPLI **NewItemList=new AlgorithmItemPLI*[N];
		int	i=0;
		for(AlgorithmItemPLI *Item=srcD->GetFirstData();Item!=NULL;Item=Item->GetNext()){
			ItemList[i]=Item;
			i++;
		}
		#pragma omp parallel                             
		{                                                
			#pragma omp for schedule(dynamic)
			for(int k=0;k<N;k++){
				AlgorithmItemPLI *Item=ItemList[k];
				AlgorithmItemRoot	*d=CreateItem(Item->GetItemClassType());
				((AlgorithmItemPLI *)d)->SetParent(this);
				d->SetPartsData(PartsMaster ,PartsID ,Item->GetID());
				d->SetRefereneFrom(Item,OffsetX,OffsetY);
				d->SetNewThresholdInstance(DestBase);
				if(d->IsNull()==false){
					d->CopyAttrFrom(Item);
				}
				else{
					delete	d;
					d=NULL;
				}
				NewItemList[k]=(AlgorithmItemPLI *)d;
			}
		}
		for(int k=0;k<N;k++){
			if(NewItemList[k]!=NULL){
				AppendItem(NewItemList[k]);
			}
		}
		if(N!=NULL){
			Changed=true;
			CalcDone=false;
		}
		delete	[]ItemList;
		delete	[]NewItemList;
	}
}
void	AlgorithmInLayerPLI::InitializeFromParts(void)
{
	for(AlgorithmItemPLI *Item=GetFirstData();Item!=NULL;){
		AlgorithmItemPLI *NextItem=Item->GetNext();
		if(Item->PartsID>=0){
			RemoveItem(Item);
			delete	Item;
			Changed=true;
		}
		Item=NextItem;
	}	
}

void	AlgorithmInLayerPLI::CopyItems(FlexArea &SrcArea ,int mx ,int my)
{
	for(AlgorithmItemPLI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		if(Item->GetArea().CheckOverlap(&SrcArea)==true){
			FlexArea	A=Item->GetArea();
			A.ClipArea(SrcArea);
			A.MoveToClip(mx,my,0,0,GetDotPerLine(),GetMaxLines());
			if(A.IsNull()==false){
				AlgorithmItemRoot	*d=CreateItem(Item->GetItemClassType());
				((AlgorithmItemPLI *)d)->SetParent(this);
				d->SetArea(A);
				d->CopyAttrFrom(Item);
				AppendItem(d);
				Changed=true;
			}
		}
	}
	CalcDone =false;
}
bool	AlgorithmInLayerPLI::ExecutePasteFromSelected(int Dx,int Dy)
{
	int	ItemCount=GetItemCount();
	AlgorithmItemRoot	**Source=new AlgorithmItemRoot *[ItemCount];
	AlgorithmItemRoot	**Dest  =new AlgorithmItemRoot *[ItemCount];
	int		CopiedCount=0;
	LayersBase	*LBase=GetLayersBase();

	for(AlgorithmItemPLI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		if(Item->GetSelected()==true){
			Source[CopiedCount]=Item;
			Dest[CopiedCount]=NULL;
			CopiedCount++;
		}
	}
	if(CopiedCount>20){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<CopiedCount;i++){
				if(Source[i]->IsCrossed(-Dx, -Dy,GetDotPerLine()-Dx,GetMaxLines()-Dy)==true){
					Dest[i]=CreateItem(Source[i]->GetItemClassType());
					Dest[i]->SetRefereneFrom(Source[i],Dx,Dy);
					Dest[i]->SetNewThresholdInstance(LBase);
					Dest[i]->CopyFrom(Source[i]);
					Dest[i]->MoveTo(Dx,Dy);
				}
			}
		}
	}
	else{
		for(int i=0;i<CopiedCount;i++){
			if(Source[i]->IsCrossed(-Dx, -Dy,GetDotPerLine()-Dx,GetMaxLines()-Dy)==true){
				Dest[i]=CreateItem(Source[i]->GetItemClassType());
				Dest[i]->SetRefereneFrom(Source[i],Dx,Dy);
				Dest[i]->SetNewThresholdInstance(LBase);
				Dest[i]->CopyFrom(Source[i]);
				Dest[i]->MoveTo(Dx,Dy);
			}
		}
	}
	for(int i=0;i<CopiedCount;i++){
		if(Dest[i]!=NULL){
			AppendItem(Dest[i]);
			Dest[i]->ClipPage();
			Dest[i]->SetSelected(false);
			Changed=true;
			CalcDone=false;
		}
	}
	delete	[]Source;
	delete	[]Dest;
	return true;
}

void	AlgorithmInLayerPLI::MoveItemsToDispatcherForLoadingParts(void)
{
	Dispatcher.RemoveAll();
	for(AlgorithmItemPLI *Item=GetFirstData();Item!=NULL;){
		if(Item->IsOriginParts()==true){
			AlgorithmItemPLI *NextItem=Item->GetNext();
			RemoveItem(Item);
			Dispatcher.AppendList(Item);
			Changed=true;
			CalcDone=false;
			Item=NextItem;
		}
		else{
			Item=Item->GetNext();
		}
	}
}

static	int	CopyItemsFormDispatcherForPartsFunc(const void *a , const void *b)
{
	AlgorithmItemPLI	**ka=(AlgorithmItemPLI **)a;
	AlgorithmItemPLI	**kb=(AlgorithmItemPLI **)b;

	if((*ka)->GetPartsID()>(*kb)->GetPartsID()){
		return -1;
	}
	if((*ka)->GetPartsID()<(*kb)->GetPartsID()){
		return 1;
	}
	if((*ka)->GetPartsAllocID()>(*kb)->GetPartsAllocID()){
		return -1;
	}
	if((*ka)->GetPartsAllocID()<(*kb)->GetPartsAllocID()){
		return 1;
	}
	if((*ka)->GetPartsItemID()>(*kb)->GetPartsItemID()){
		return -1;
	}
	if((*ka)->GetPartsItemID()<(*kb)->GetPartsItemID()){
		return 1;
	}
	return 0;
}

void	AlgorithmInLayerPLI::CopyItemsFormDispatcherForParts(void)
{
	int	DestTableNumb=GetItemCount();
	AlgorithmItemPLI	**DestTable=new AlgorithmItemPLI*[DestTableNumb];
	int	N=0;
	for(AlgorithmItemPLI *Dest=GetFirstData();Dest!=NULL;Dest=Dest->GetNext()){
		DestTable[N]=Dest;
		N++;
	}
	QSort(DestTable,N,sizeof(DestTable[0]),CopyItemsFormDispatcherForPartsFunc);

	for(AlgorithmItemPLI *Src=Dispatcher.GetFirst();Src!=NULL;Src=Src->GetNext()){
		AlgorithmItemPLI *Key=Src;
		AlgorithmItemPLI **Dest=(AlgorithmItemPLI **)EqualSearch(&Key,DestTable,N,sizeof(DestTable[0]),CopyItemsFormDispatcherForPartsFunc);

		if(Dest!=NULL){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			Src->SaveUnique(&Buff);
			Buff.seek(0);
			(*Dest)->LoadUnique(&Buff);
		}
	}
	delete	[]DestTable;
}

void	AlgorithmInLayerPLI::RemoveItemFormDispatcher(void)
{
	Dispatcher.RemoveAll();
}

void	AlgorithmInLayerPLI::GetOriginRootNames(NPListPack<OriginNames> &OriginNameList)
{
	AlgorithmBase	*Dim[1000];
	int				DimNumb=0;
	int				ItemNumb[1000];

	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		int i;
		for(i=0;i<DimNumb;i++){
			if(Dim[i]==item->GetOrigin()){
				ItemNumb[i]++;
				break;
			}
		}
		if(i>=DimNumb && i<sizeof(Dim)/sizeof(Dim[0])){
			Dim[DimNumb]=item->GetOrigin();
			ItemNumb[DimNumb]=1;
			DimNumb++;
		}
	}
	for(int i=0;i<DimNumb;i++){
		OriginNames	*v=new OriginNames();
		Dim[i]->GetDLLName(v->DLLRoot ,v->DLLName);
		v->Numb=ItemNumb[i];
		OriginNameList.AppendList(v);
	}
}
void	AlgorithmInLayerPLI::SelectOriginRootNames(AlgorithmBase *OriginBase)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetOrigin()==OriginBase){
			item->SetSelected(true);
		}
	}
}
bool	AlgorithmInLayerPLI::ShrinkItems(int ExpandPixels,bool MaskForSameLib)
{
	bool	Ret=true;
	if(MaskForSameLib==false){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			if(item->GetSelected()==true && item->GetEditLocked()==false && item->GetVisible()==true){
				if(item->ShrinkItems(ExpandPixels)==false){
					Ret=false;
				}
			}
		}
	}
	else{
		int	XLen	=GetDotPerLine();
		int	XByte	=(XLen+7)/8;
		int	YLen	=GetMaxLines();
		BYTE	**Mask=MakeMatrixBuff(XByte,YLen);
		
		IntList	LibIDs;
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			if(item->GetSelected()==true && item->GetEditLocked()==false && item->GetVisible()==true){
				LibIDs.Merge(item->GetLibID());
			}
		}
		for(IntClass *c=LibIDs.GetFirst();c!=NULL;c=c->GetNext()){
			MatrixBuffClear	(Mask ,0 ,XByte,YLen);
			for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
				if(c->GetValue()==item->GetLibID()){
					item->GetArea().MakeBitData(Mask,XLen,YLen);
				}
			}
			for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
				if(item->GetSelected()==true && item->GetEditLocked()==false && item->GetVisible()==true
				&& c->GetValue()==item->GetLibID()){
					if(item->ShrinkItems(ExpandPixels,Mask)==false){
						Ret=false;
					}
				}
			}
		}
		DeleteMatrixBuff(Mask,YLen);
	}
	return Ret;
}
void	AlgorithmInLayerPLI::VisibleAll(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetVisible(true);
	}
}
void	AlgorithmInLayerPLI::InvisibleAll(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetVisible(false);
	}
}
void	AlgorithmInLayerPLI::InvisibleSelected(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->SetVisible(false);
		}
		else{
			item->SetVisible(true);
		}
	}
}
void	AlgorithmInLayerPLI::SelectManualCreature(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetManualCreated()==true){
			item->SetSelected(true);
		}
		else{
			item->SetSelected(false);
		}
	}
}

bool	AlgorithmInLayerPLI::IsEdited(void)
{
	if(Changed==true){
		return true;
	}
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsEdited()==true){
			return true;
		}
	}
	return false;
}
bool	AlgorithmInLayerPLI::IsCalcDone(void)
{
	if(CalcDone==false){
		return false;
	}
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}

void	AlgorithmInLayerPLI::SetEdited(bool edited)
{
	Changed=edited;
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetEdited(edited);
	}
}
void	AlgorithmInLayerPLI::SetCalcDone(bool calcdone)
{
	CalcDone=calcdone;
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetCalcDone(calcdone);
	}
}
void	AlgorithmInLayerPLI::ResetProcessDone(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->ResetProcessDone();
	}
}
bool	AlgorithmInLayerPLI::IsProcessDone(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsProcessDone()==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInLayerPLI::SetProcessDone(bool b)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetProcessDone(b);
	}
}

void	AlgorithmInLayerPLI::GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->GetOutsideItems(dx,dy,OutsideItems,MaxGlobalPage);
	}
}

void	AlgorithmInLayerPLI::ClearTemporaryItems(void)
{
	MutexTemporaryItem.lock();
	TemporaryItemList.RemoveAll();
	MutexTemporaryItem.unlock();
}
void	AlgorithmInLayerPLI::SetTemporaryItems(ItemPointerListInLayer *Ly)
{
	MutexTemporaryItem.lock();
	if(Ly->ItemList.GetFirst()!=NULL){
		TemporaryItemList.AddMove(Ly->ItemList);
	}
	MutexTemporaryItem.unlock();
}
void	AlgorithmInLayerPLI::ClearResult(void)
{
	for(AlgorithmItemPLI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		p->ClearResult();
	}
}
void	AlgorithmInLayerPLI::AddItemsForMove(ItemPointerListInLayer *Ly)
{
	IntList	IDList;
	ItemPointerList	*c;
	while((c=Ly->ItemList.GetFirst())!=NULL){
		Ly->ItemList.RemoveList(c);
		c->ItemPointer->MoveTo(c->Dx,c->Dy);
		AlgorithmItemPLI	*d=dynamic_cast<AlgorithmItemPLI *>(c->ItemPointer);
		if(d!=NULL && d->IsNull()==false){
			AppendItem(d);
			IDList.Add(d->GetID());
		}
		c->ItemPointer=NULL;
		c->Created=false;
	}
	UndoAlgorithmLayer	*UndoPointer=new UndoAlgorithmLayer(this ,&AlgorithmInLayerRoot::UndoAddItemsForMove);
	IDList.Save(UndoPointer->GetWritePointer());
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

	InitialThreadBufferForExecute();
}
void	AlgorithmInLayerPLI::UndoAddItemsForMove(QIODevice *f)
{
	IntList	IDList;

	if(IDList.Load(f)==true){
		FastSearchIDItemStart();
		for(IntClass *c=IDList.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmItemRoot	*L=FastSearchIDItem(c->GetValue());
			if(L!=NULL){
				RemoveItem(L);
				delete	L;
			}
		}
	}
}
void	AlgorithmInLayerPLI::SelectedItemListsForPaste(ExpandedSelectedItemListContainer &Lists)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			ExpandedSelectedItemList	*c=new ExpandedSelectedItemList();
			c->X1=item->GetArea().GetMinX();
			c->Y1=item->GetArea().GetMinY();
			c->X2=item->GetArea().GetMaxX();
			c->Y2=item->GetArea().GetMaxY();
			c->Page=GetPage();
			c->Layer=GetLayer();
			c->ItemID=item->GetID();
			Lists.AppendList(c);
		}
	}
}
void	AlgorithmInLayerPLI::DrawItemListsForPaste(int dx, int dy ,QImage &Pnt,int ItemID ,double ZoomRate ,int movx ,int movy,int turn)
{
	if(turn==0){
		FastSearchIDItemStart();
	}
	AlgorithmItemRoot		*Item=FastSearchIDItem(ItemID);
	if(Item!=NULL){
		Item->DrawItemListsForPaste(dx, dy ,Pnt,ZoomRate ,movx ,movy);
	}
}

void	AlgorithmInLayerPLI::ExecuteTransformSelectedItems(TransformBase &M)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->ExecuteTransformSelectedItem(M);
		}
	}
}
void	AlgorithmInLayerPLI::GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		ItemPointers.Add(item);
	}
}
void	AlgorithmInLayerPLI::EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(LibIDs.IsInclude(item->GetLibID())==true){
			ItemPointers.Add(item);
		}
	}
}
void	AlgorithmInLayerPLI::EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		ItemPointers.Add(item);
	}
}
void	AlgorithmInLayerPLI::GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			ItemPointers.Add(item);
		}
	}
}
void	AlgorithmInLayerPLI::EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetOriginType()==b){
			Items.Add(item);
		}
	}
}
void	AlgorithmInLayerPLI::EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *c))
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(func!=NULL){
			if(func(caller,item)==true){
				Items.Add(item);
			}
		}
		else{
			Items.Add(item);
		}
	}
}
void	AlgorithmInLayerPLI::ScanItems(void *caller, void (*func)(void *caller,AlgorithmItemRoot *c))
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		func(caller,item);
	}
}

void	AlgorithmInLayerPLI::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SwitchThresholdLevel(OldLevel ,NewLevel);
	}
}
void	AlgorithmInLayerPLI::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->CopyThresholdLevel(SourceLevelID ,DestLevelID);
	}
}

void	AlgorithmInLayerPLI::EnumSelectedItems(ListPageLayerIDPack &Items)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			Items.AppendList(new ListPageLayerID(GetPage(),GetLayer(),item->GetID()));
		}
	}
}

void	AlgorithmInLayerPLI::RemoveItems(IntList &IDList)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;){
		AlgorithmItemPLI *NextP=item->GetNext();
		if(IDList.IsInclude(item->GetID())==true){
			RemoveItem(item);
			delete	item;
		}
		item=NextP;
	}
}

bool	AlgorithmInLayerPLI::SaveCSVMasterReport(QStringListListCSV &CSVData)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->SaveCSVMasterReport(CSVData)==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInLayerPLI::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->RotateItem(AngleDegree ,Cx, Cy);
		}
	}
}

void	AlgorithmInLayerPLI::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->MirrorItem(MirrorMode ,PointX ,PointY);
		}
	}
}

bool	AlgorithmInLayerPLI::GetSelectedCenter(int &Cx ,int &Cy)
{
	double	MCx=0.0,MCy=0.0;
	int64	AreaDots=0;
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			FlexArea	&Area=item->GetArea();
			int64		N=Area.GetPatternByte();
			double		x,y;
			item->GetCenter(x,y);
			if(N!=0){
				AreaDots+=N;
				MCx+=x*N;
				MCy+=y*N;
			}
			else{
				AreaDots++;
				MCx+=x;
				MCy+=y;
			}
		}
	}
	if(AreaDots==0){
		return false;
	}
	Cx=MCx/AreaDots;
	Cy=MCy/AreaDots;
	return true;
}
bool	AlgorithmInLayerPLI::GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)
{
	X1=99999999;
	Y1=99999999;
	X2=-99999999;
	Y2=-99999999;
	bool	Ret=false;
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			int	x1,y1,x2,y2;
			item->GetXY(x1,y1,x2,y2);
			if(x1<X1){
				X1=x1;
			}
			if(y1<Y1){
				Y1=y1;
			}
			if(x2>X2){
				X2=x2;
			}
			if(y2>Y2){
				Y2=y2;
			}
			Ret=true;
		}
	}
	return Ret;
}

bool	AlgorithmInLayerPLI::GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)
{
	X1=99999999;
	Y1=99999999;
	X2=-99999999;
	Y2=-99999999;
	bool	Ret=false;
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		int	x1,y1,x2,y2;
		item->GetXY(x1,y1,x2,y2);
		if(x1<X1){
			X1=x1;
		}
		if(y1<Y1){
			Y1=y1;
		}
		if(x2>X2){
			X2=x2;
		}
		if(y2>Y2){
			Y2=y2;
		}
		Ret=true;
	}
	return Ret;
}


bool	AlgorithmInLayerPLI::SaveItemsForLearning(ItemDataListWithIDContainer &Buff 
													,FlexArea &LocalArea
													,AlgorithmLibraryListContainer &LibList
													,int AddedX,int AddedY,bool OkMode)
{
	static	int	DbgItemID=0;
	static	int	DbgCode=0;

	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetID()==DbgItemID)
			DbgCode++;
		if(LibList.IsInclude(item->GetLibType(),item->GetLibID())==true){
			FlexArea	A=item->GetArea();
			ResultInItemRoot	*R=item->GetCurrentResult();
			if(R!=NULL){
				A.MoveToNoClip(R->GetItemSearchedX(),R->GetItemSearchedY());
			}
			if(A.CheckOverlap(&LocalArea)==true){
				ItemDataListWithID	*h=item->MakeItemForLearning(AddedX,AddedY,OkMode);
				if(h!=NULL){
					Buff.AppendList(h);
				}
			}
		}
	}
	return true;
}

bool	AlgorithmInLayerPLI::LoadItemsForLearning(ItemDataListWithIDContainer &Buff  ,int AddedX ,int AddedY)
{
	for(ItemDataListWithID *c=Buff.GetFirst();c!=NULL;c=c->GetNext()){
		QBuffer	HBuff(&c->IData);
		HBuff.open(QIODevice::ReadOnly);

		if(::Load(&HBuff,c->Layer)==false){
			return false;
		}
		if(c->Layer!=GetLayer()){
			continue;
		}
		if(::Load(&HBuff,c->ItemClassType)==false){
			return false;
		}
		AlgorithmItemRoot *m=CreateItem(c->ItemClassType);
		if(m->LoadForLearning(&HBuff,GetLayersBase())==false){
			return false;
		}
		int64	ItemID=m->GetID();
		m->MoveTo(AddedX,AddedY);
		AppendItem(m);
		m->SetID(ItemID);
	}
	return true;
}
bool	AlgorithmInLayerPLI::GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsInclude(LocalX,LocalY)==true){
			ItemPointerList	*c=new ItemPointerList();
			c->ItemPointer=item;
			c->Dx=0;
			c->Dy=0;
			c->Created=false;
			Items.AppendList(c);
		}
	}
	return true;
}

HistgramByParamBase	*AlgorithmInLayerPLI::GetHistgramBase(int ItemID,int HistID)
{
	AlgorithmItemRoot *item=SearchIDItem(ItemID);
	if(item!=NULL){
		HistgramByParamBase	*r=item->GetThresholdBaseWritable()->GetHistgramBase(HistID);
		return r;
	}
	return NULL;
}
void	AlgorithmInLayerPLI::MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->MakeUncoveredMap(BMap, XByte ,YLen);
	}
}

void	AlgorithmInLayerPLI::SetItemName(const QString &ItemName , bool OnlySelected)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetItemName(ItemName , OnlySelected);
	}
}

void	AlgorithmInLayerPLI::UndoExecutePaste(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*L=SearchIDItem(ItemID);
	if(L!=NULL){
		RemoveItem(L);
		delete	L;
	}
}
void	AlgorithmInLayerPLI::EnumLibID(IntList &LibIDList)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetLibID()>=0){
			if(LibIDList.IsInclude(item->GetLibID())==false){
				LibIDList.Add(item->GetLibID());
			}
		}
	}
}
void	AlgorithmInLayerPLI::MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetLibID()==LibID){
			RetContainer.Add(item);
		}
	}
}

void	AlgorithmInLayerPLI::EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetHistgramBase(HistID)!=NULL){
			AlgorithmItemPointerList	*a=new AlgorithmItemPointerList(item);
			RetContainer.AppendList(a);
		}
	}
}

void	AlgorithmInLayerPLI::EnumItemHistgram(int HistID ,int LibID, AlgorithmItemPointerListContainer &RetContainer)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetLibID()==LibID && item->GetHistgramBase(HistID)!=NULL){
			AlgorithmItemPointerList	*a=new AlgorithmItemPointerList(item);
			RetContainer.AppendList(a);
		}
	}
}

void	AlgorithmInLayerPLI::ClearRentalItem(void)
{
	RentalData.RemoveAll();
}
void	AlgorithmInLayerPLI::ReqRentalItem(QByteArray &Something)
{
	ClearRentalItem();
	AlgorithmBase	*ABase=GetParentBase();
	QString		DLLRoot ,DLLName;
	ABase->GetAlgorithmRootName(DLLRoot ,DLLName);

	int	OwnGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	XYData	*OwnP=GetLayersBase()->GetGlobalOutlineOffset(OwnGlobalPage);

	for(int globalPage=0;globalPage<GetLayersBase()->GetGlobalPageNumb();globalPage++){
		if(globalPage==OwnGlobalPage)
			continue;
		SlaveCommReqRentalItems	RCmd(GetLayersBase(),DLLRoot ,DLLName,globalPage);
		SlaveCommAckRentalItems	ACmd(GetLayersBase(),DLLRoot ,DLLName,globalPage);
		RCmd.Layer	=GetLayer();
		RCmd.FromGlobalPage=OwnGlobalPage;
		RCmd.AlgoRoot	=DLLRoot;
		RCmd.AlgoName	=DLLName;
		RCmd.Something	=Something;
		if(RCmd.Send(globalPage,0,ACmd)==true){
			XYData	*OtherP=GetLayersBase()->GetGlobalOutlineOffset(globalPage);
			AlgorithmItemPLI	*p;
			int64	MaxID=GetMaxItemID()+1;

			while((p=ACmd.RentalData.GetFirst())!=NULL){
				ACmd.RentalData.RemoveList(p);
				p->SetFromRental(true);
				p->MoveTo(OtherP->x-OwnP->x , OtherP->y-OwnP->y);
				AddRentalItem(MaxID,p);
				MaxID++;
			}
		}
	}
}

void	AlgorithmInLayerPLI::AddRentalItem(int ItemID ,AlgorithmItemPLI *p)
{
	p->SetID(ItemID);
	p->SetParent(this);
	RentalData.AppendList(p);
}

bool	AlgorithmInLayerPLI::ManualExecuteAll(ManualExecuter &ManualExecuterData)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->ManualExecuteAll(ManualExecuterData)==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInLayerPLI::MakeBindedThreshold(BindedThresholdContainer &Container)
{
	AlgorithmItemPLI	**List=new AlgorithmItemPLI*[GetItemCount()];
	int	n=0;
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		List[n]=item;
	}
	for(int i=0;i<n;i++){
		if(List[i]!=NULL){
			AlgorithmThreshold	*A=List[i]->GetThresholdBaseWritable();
			if(A!=NULL){
				BindedThresholdList	*B=new BindedThresholdList;
				B->ItemIDs.Add(List[i]->GetID());
				B->LibID	=List[i]->GetLibID();
				B->Layer	=GetLayer();
				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				A->Save(&Buff);
				B->ThresholdData=Buff.buffer();
				List[i]=NULL;
				for(int j=i+1;j<n;j++){
					AlgorithmThreshold	*A2=List[j]->GetThresholdBaseWritable();
					if(A2!=NULL && List[j]->GetLibID()==B->LibID){
						if(A2->IsEqual(*A)==true){
							B->ItemIDs.Add(List[j]->GetID());
							List[j]=NULL;
						}
					}
				}
				
				Container.AppendList(B);
			}
		}
	}
	delete	[]List;
}

void	AlgorithmInLayerPLI::GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items)
{
	for(AlgorithmItemPLI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		AlgorithmItemPointerListContainerByLib	*f=Items.FindByLibID(GetLayer(),a->GetLibID());
		if(f==NULL){
			f=new AlgorithmItemPointerListContainerByLib(GetLayer(),a->GetLibID());
			Items.AppendList(f);
		}
		f->Container.Add(a);
	}
}
void	AlgorithmInLayerPLI::UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes)
{
	if(ItemID<0){
		for(AlgorithmItemPLI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetLibID()==LibID){
				a->UpdateThreshold(LearningMenuID,LRes);
			}
		}
	}
	else{
		AlgorithmItemRoot	*a=SearchIDItem(ItemID);
		if(a!=NULL){
			a->UpdateThreshold(LearningMenuID,LRes);
		}
	}
}
void	AlgorithmInLayerPLI::EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)
{
	int	Phase=GetPhaseCode();
	int	Page=GetPage();
	int	Layer=GetLayer();
	for(AlgorithmItemPLI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		int	LibID=a->GetLibID();
		ListPhasePageLayerLibID *L;
		for(L=ItemIDList.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->Data.Phase==Phase
			&& L->Data.Page==Page
			&& L->Data.Layer==Layer
			&& L->Data.LibID==LibID){
				break;
			}
		}
		if(L==NULL){
			L=new ListPhasePageLayerLibID(Phase,Page,Layer,LibID);
			ItemIDList.AppendList(L);
		}
		L->ItemIDs.Add(a->GetID());
	}
}
bool	AlgorithmInLayerPLI::MakeConfirmItem(ConfirmItemListContainer &ItemList)
{
	AlgorithmBase	*ABase=GetParentBase();
	AlgorithmLibraryContainer	*LibC=ABase->GetLibraryContainer();
	for(AlgorithmItemPLI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		ResultInItemRoot	*Res=a->GetCurrentResult();
		if(Res!=NULL){
			if(Res->IsOk()==false){
				ConfirmItemList	*d=new ConfirmItemList();
				d->Page=GetPage();
				d->Phase=GetPhaseCode();
				d->Layer=0;
				d->ItemID	=a->GetID();
				d->CType	=CF_NG;

				ResultPosList	*r=Res->GetPosList().GetFirst();
				if(r!=NULL){
					DetailResultInfoListContainer RetList;
					if(ABase->GetDrawResultDetail(a ,r ,RetList)==true){
						QStringList StrList;
						RetList.GetInfoStringList(StrList);
						QString	s;
						for(int i=0;i<StrList.count();i++){
							s+=StrList[i];
						}
						if(s.isEmpty()==false){
							d->Cause=s;
						}
					}
				}
				if(d->Cause.isEmpty()==true){
					d->Cause=Res->ResultItemToString();
				}
				if(d->Cause.isEmpty()==true && LibC!=NULL){				
					d->Cause=LibC->GetLibraryName(a->GetLibID());
				}
				ItemList.AppendList(d);
			}
		}
	}
	return true;
}
AlgorithmItemRoot	*AlgorithmInLayerPLI::FindItem(const AlgorithmItemIndex &Index)	const
{
	return SearchIDItem(Index.GetItemID());
}
//================================================================================================

AlgorithmInPagePLI::AlgorithmInPagePLI(AlgorithmBase *parent)
{
	LayerData			=NULL;
	AllocatedLayerNumb	=0;
	Parent				=parent;
	SlaveCommReqRentalItemsInst	=NULL;
	SlaveCommAckRentalItemsInst	=NULL;
}
AlgorithmInPagePLI::~AlgorithmInPagePLI(void)
{
	ReleaseData();
	/*
	if(SlaveCommReqRentalItemsInst!=NULL){
		delete	SlaveCommReqRentalItemsInst;
		SlaveCommReqRentalItemsInst=NULL;
	}
	if(SlaveCommAckRentalItemsInst!=NULL){
		delete	SlaveCommAckRentalItemsInst;
		SlaveCommAckRentalItemsInst=NULL;
	}
	*/
}

void	AlgorithmInPagePLI::ReleaseData(void)
{
	if(LayerData!=NULL){
		for(int i=0;i<AllocatedLayerNumb;i++){
			delete	LayerData[i];
		}
		delete	[]LayerData;
	}
	LayerData=NULL;
	AllocatedLayerNumb=0;
}

void	AlgorithmInPagePLI::Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)
{
	AlgorithmInPageRoot::Initial(phaseParent,Base);

	if(LayerData!=NULL){
		ReleaseData();
	}
	LayerData=new AlgorithmInLayerPLI*[GetLayerNumb()];
	AllocatedLayerNumb=GetLayerNumb();
	for(int i=0;i<AllocatedLayerNumb;i++){
		LayerData[i]=(AlgorithmInLayerPLI *)NewChild(this);
		LayerData[i]->SetLayer(i);
		//LayerData[i]->PDataInLayer		=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(i);
		LayerData[i]->SetEntryPoint(GetEntryPoint());
		LayerData[i]->Initial();
	}
}

void	AlgorithmInPagePLI::Release(void)
{
	for(int i=0;i<AllocatedLayerNumb;i++){
		LayerData[i]->Release();
	}
	ReleaseData();
}
bool	AlgorithmInPagePLI::Reallocate(int newLayerNumb)
{
	PDataInPage	=GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage());
	if(AllocatedLayerNumb<newLayerNumb){
		AlgorithmInLayerPLI	**tLayerData	=new AlgorithmInLayerPLI*[newLayerNumb];
		int	Ly;
		for(Ly=0;Ly<AllocatedLayerNumb;Ly++){
			if(LayerData[Ly]==NULL){
				break;
			}
			tLayerData[Ly]=LayerData[Ly];
		}
		LayerData=tLayerData;
		for(;Ly<newLayerNumb;Ly++){
			LayerData[Ly]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Ly]->SetLayer(Ly);
			//LayerData[i]->PDataInLayer		=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(i);
			LayerData[Ly]->SetEntryPoint(GetEntryPoint());
			LayerData[Ly]->Initial();
		}
	}
	else if(AllocatedLayerNumb>newLayerNumb){
		for(int Ly=newLayerNumb;Ly<AllocatedLayerNumb;Ly++){
			if(LayerData[Ly]!=NULL){
				delete	LayerData[Ly];
				LayerData[Ly]=NULL;
			}
		}
	}
	AllocatedLayerNumb=newLayerNumb;
	return true;
}
bool	AlgorithmInPagePLI::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(int i=0;i<AllocatedLayerNumb;i++){
		if(LayerData[i]->ReallocateMasterCount(CountMaster)==false){
			Ret=false;
		}
	}
	return Ret;
}
void	AlgorithmInPagePLI::InitializeToStart(void)
{
	for(int i=0;i<AllocatedLayerNumb;i++){
		LayerData[i]->InitializeToStart();
	}
}
void	AlgorithmInPagePLI::InitialAfterParamLoaded(void)
{
	for(int i=0;i<AllocatedLayerNumb;i++){
		LayerData[i]->InitialAfterParamLoaded();
	}
	if(GetPage()==0){
		QString	sRoot,sName;
		if(GetParentBase()!=NULL){
			GetParentBase()->GetAlgorithmRootName(sRoot,sName);
		}

		if(SlaveCommReqRentalItemsInst!=NULL){
			delete	SlaveCommReqRentalItemsInst;
			SlaveCommReqRentalItemsInst=NULL;
		}
		if(SlaveCommAckRentalItemsInst!=NULL){
			delete	SlaveCommAckRentalItemsInst;
			SlaveCommAckRentalItemsInst=NULL;
		}
		SlaveCommReqRentalItemsInst	=new SlaveCommReqRentalItems(GetLayersBase(),sRoot,sName);
		SlaveCommAckRentalItemsInst	=new SlaveCommAckRentalItems(GetLayersBase(),sRoot,sName);
	}
}

bool	AlgorithmInPagePLI::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	PDataInPage	=GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage());
	for(int i=0;i<AllocatedLayerNumb;i++){
		if(LayerData[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	AlgorithmInPagePLI::CopyShadowAlgorithmPage(ShadowTree *Child ,const AlgorithmInPageRoot &SrcParent)
{
	bool	Ret=true;
	for(int i=0;i<AllocatedLayerNumb;i++){
		const AlgorithmInLayerRoot	*PL=((AlgorithmInPagePLI *)&SrcParent)->GetLayerData(i);
		AlgorithmInLayerRoot	*CL=GetLayerData(i);
		if(PL!=NULL && CL!=NULL){
			if(Child->CopyShadowAlgorithmLayer(*PL,CL)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

bool	AlgorithmInPagePLI::Save(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::Save(f)==false){
			return false;
		}
		int32	Ver=1;
		if(::Save(f,Ver)==false){
			return(false);
		}
		if(::Save(f,AllocatedLayerNumb)==false){
			return(false);
		}
		for(int i=0;i<AllocatedLayerNumb;i++){
			if(LayerData[i]->Save(f)==false){
                return(false);
			}
		}
	}
    return(true);
}
bool	AlgorithmInPagePLI::Load(QIODevice *f)
{
	if(LayerData!=NULL){
		//_CrtCheckMemory();
		ReleaseData();
		AllocatedLayerNumb=0;
	}
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::Load(f)==false){
			return false;
		}
		int32	Ver;
		if(::Load(f,Ver)==false){
			return(false);
		}

		int32	N;
		if(::Load(f,N)==false){
			return(false);
		}
		int	iLayerNumb=GetLayerNumb();
		LayerData=new AlgorithmInLayerPLI*[iLayerNumb];
		int	Layer;
		for(Layer=0;Layer<N && Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			//LayerData[Layer]->PDataInLayer		=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
			if(LayerData[Layer]->Load(f)==false){
				Layer++;
                break;
			}
		}
		for(;Layer<N && Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			//LayerData[Layer]->PDataInLayer		=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
		}
		for(;Layer<N;Layer++){
			AlgorithmInLayerPLI  *L=(AlgorithmInLayerPLI *)NewChild(this);
			L->SetLayer(Layer);
			L->SetEntryPoint(GetEntryPoint());
			if(L->Load(f)==false){
                return(false);
			}
			delete	L;
		}
		for(;Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			//LayerData[Layer]->PDataInLayer=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
		}
		Changed=false;
	}
	else{
		int	iLayerNumb=GetLayerNumb();
		LayerData=new AlgorithmInLayerPLI*[iLayerNumb];
		int	Layer;
		for(Layer=0;Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
		}
	}
    return(true);
}
bool	AlgorithmInPagePLI::LoadByTransform(QIODevice *f ,TransformBase &Param)
{
	if(LayerData!=NULL){
		//_CrtCheckMemory();
		ReleaseData();
		AllocatedLayerNumb=0;
	}
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::Load(f)==false){
			return false;
		}
		int32	Ver;
		if(::Load(f,Ver)==false){
			return(false);
		}

		int32	N;
		if(::Load(f,N)==false){
			return(false);
		}
		int	iLayerNumb=GetLayerNumb();
		LayerData=new AlgorithmInLayerPLI*[iLayerNumb];
		int	Layer;
		for(Layer=0;Layer<N && Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			//LayerData[Layer]->PDataInLayer		=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
			if(LayerData[Layer]->LoadByTransform(f,Param)==false){
				Layer++;
                break;
			}
		}
		for(;Layer<N && Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			//LayerData[Layer]->PDataInLayer		=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
		}
		for(;Layer<N;Layer++){
			AlgorithmInLayerPLI  *L=(AlgorithmInLayerPLI *)NewChild(this);
			L->SetLayer(Layer);
			L->SetEntryPoint(GetEntryPoint());
			if(L->LoadByTransform(f,Param)==false){
                return(false);
			}
			delete	L;
		}
		for(;Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			//LayerData[Layer]->PDataInLayer=PInspectionData->GetLayersBase()->GetPageData(Page)->GetLayerData(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
		}
		Changed=false;
	}
	else{
		int	iLayerNumb=GetLayerNumb();
		LayerData=new AlgorithmInLayerPLI*[iLayerNumb];
		int	Layer;
		for(Layer=0;Layer<iLayerNumb;Layer++){
			AllocatedLayerNumb++;
			LayerData[Layer]=(AlgorithmInLayerPLI *)NewChild(this);
			LayerData[Layer]->SetLayer(Layer);
			LayerData[Layer]->SetEntryPoint(GetEntryPoint());
		}
	}
    return(true);
}
bool	AlgorithmInPagePLI::LoadAppend(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::LoadAppend(f)==false){
			return false;
		}
		int32	Ver;
		if(::Load(f,Ver)==false){
			return(false);
		}

		int32	N;
		if(::Load(f,N)==false){
			return(false);
		}
		int	i;
		for(i=0;i<N && i<GetLayerNumb();i++){
			if(LayerData[i]->LoadAppend(f)==false){
				return(false);
			}
		}
		for(;i<N;i++){
			AlgorithmInLayerPLI  *L=(AlgorithmInLayerPLI *)NewChild(this);
			L->SetLayer(i);
			L->SetEntryPoint(GetEntryPoint());
			if(L->LoadAppend(f)==false){
				return(false);
			}
			delete	L;
		}
		Changed=true;
	}
    return(true);
}

bool		AlgorithmInPagePLI::SaveHistgram(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return(false);
	}
	if(::Save(f,AllocatedLayerNumb)==false){
		return(false);
	}
	for(int i=0;i<AllocatedLayerNumb;i++){
		if(LayerData[i]->SaveHistgram(f)==false){
            return(false);
		}
	}
    return(true);
}
bool		AlgorithmInPagePLI::LoadHistgram(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return(false);
	}

	int32	N;
	if(::Load(f,N)==false){
		return(false);
	}
	int	i;
	for(i=0;i<N && i<GetLayerNumb();i++){
		if(LayerData[i]->LoadHistgram(f)==false){
            return(false);
		}
	}
	for(;i<N;i++){
		AlgorithmInLayerPLI  *L=(AlgorithmInLayerPLI *)NewChild(this);
		L->SetLayer(i);
		L->SetEntryPoint(GetEntryPoint());
		if(L->LoadHistgram(f)==false){
            return(false);
		}
		delete	L;
	}
	return true;
}
void	AlgorithmInPagePLI::ClearHistgram(void)
{
	for(int i=0;i<AllocatedLayerNumb;i++){
		LayerData[i]->ClearHistgram();
	}
}
bool	AlgorithmInPagePLI::SaveOnlyThreshold(QIODevice *f)
{
	for(int i=0;i<AllocatedLayerNumb;i++){
		if(LayerData[i]->SaveOnlyThreshold(f)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPagePLI::LoadOnlyThreshold(QIODevice *f)
{
	for(int i=0;i<AllocatedLayerNumb;i++){
		if(LayerData[i]->LoadOnlyThreshold(f)==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInPagePLI::RemoveAllDatas(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		LayerData[layer]->RemoveAllDatas();
	}
	Changed=true;
	CalcDone=false;
}
void	AlgorithmInPagePLI::RemoveAllDatasWithoutLocked(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		LayerData[layer]->RemoveAllDatasWithoutLocked();
	}
	Changed=true;
	CalcDone=false;
}
void	AlgorithmInPagePLI::RemoveAllDatasWithoutManual(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		LayerData[layer]->RemoveAllDatasWithoutManual();
	}
	Changed=true;
	CalcDone=false;
}

int64		AlgorithmInPagePLI::GetMaxItemID(void)	const
{
	int64	MaxItemID=0;
	for(int layer=0;layer<GetLayerNumb();layer++){
		int64	d=LayerData[layer]->GetMaxItemID();
		if(d>MaxItemID){
			MaxItemID=d;
		}
	}
	return MaxItemID;
}
void	AlgorithmInPagePLI::FastSearchIDItemStart(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		LayerData[layer]->FastSearchIDItemStart();
	}
}
AlgorithmItemRoot	*AlgorithmInPagePLI::GetItemData(int layer ,int itemID)	const
{
	AlgorithmInLayerPLI	*Ly=GetLayerDataPLI(layer);
	if(Ly==NULL){
		return NULL;
	}
	for(AlgorithmItemPLI *p=Ly->GetFirstData();p!=NULL;p=p->GetNext()){
		if(p->GetID()==itemID){
			return p;
		}
	}
	return NULL;
}
AlgorithmItemRoot	*AlgorithmInPagePLI::FindFastItemData(int layer ,int itemID)	const
{
	AlgorithmInLayerPLI	*Ly=GetLayerDataPLI(layer);
	if(Ly==NULL){
		return NULL;
	}
	return Ly->FastSearchIDItem(itemID);
}
bool	AlgorithmInPagePLI::AppendItem(int layer ,AlgorithmItemRoot *item)
{
	AlgorithmInLayerPLI	*Ly=GetLayerDataPLI(layer);
	if(Ly!=NULL){
		return Ly->AppendItem(item);
	}
	return false;
}

void	AlgorithmInPagePLI::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	AlgorithmInPagePLI::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	TransmitDirectly(packet);
	for(int layer=0;layer<GetLayerNumb();layer++){
		LayerData[layer]->DeliverTransmitDirectly(packet);
	}
}
void	AlgorithmInPagePLI::RemoveAllDatasByManual(bool CreatedManually)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		LayerData[layer]->RemoveAllDatasByManual(CreatedManually);
	}
}

void	AlgorithmInPagePLI::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(LayerList.GetFirst()!=NULL){
		for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetValue()<0 || AllocatedLayerNumb<=c->GetValue()){
				continue;
			}
			//LayerData[c->d]->Draw(pnt, movx+GetDataInPage()->GetOutlineOffset()->x ,movy+GetDataInPage()->GetOutlineOffset()->y ,ZoomRate ,Attr);
			LayerData[c->GetValue()]->Draw(pnt, movx,movy,ZoomRate ,Attr);
		}
	}
	else{
		for(int layer=0;layer<GetLayerNumb();layer++){
			LayerData[layer]->Draw(pnt, movx,movy,ZoomRate ,Attr);
		}
	}
}
void	AlgorithmInPagePLI::DrawMove(int dx ,int dy ,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	for(int layer=0;layer<AllocatedLayerNumb;layer++){
		LayerData[layer]->DrawMove(dx,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
}
bool	AlgorithmInPagePLI::DrawResult(ResultInPageRoot *R,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	ResultInPagePLI &Res=*((ResultInPagePLI *)R);
	for(int layer=0;layer<AllocatedLayerNumb;layer++){
		ResultInLayerPLI	&R=Res.GetLayerData(layer);
		if(LayerData[layer]->DrawResult(&R,IData ,PData ,MovX ,MovY ,ZoomRate)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPagePLI::DrawResultItem(ResultInPageRoot *R,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	ResultInPagePLI &Res=*((ResultInPagePLI *)R);
	if(LayerList.GetFirst()!=NULL){
		for(int layer=0;layer<AllocatedLayerNumb;layer++){
			for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetValue()==layer){
					ResultInLayerPLI	&R=Res.GetLayerData(layer);
					if(LayerData[layer]->DrawResultItem(&R,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG)==false){
						return false;
					}
					break;
				}
			}
		}
	}
	else{
		for(int layer=0;layer<GetLayerNumb();layer++){
			ResultInLayerPLI	&R=Res.GetLayerData(layer);
			if(LayerData[layer]->DrawResultItem(&R,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG)==false){
				return false;
			}
		}
	}
	return true;
}
void	AlgorithmInPagePLI::DrawMonoBitmap(BYTE **BmpPoint)
{
	for(int layer=0;layer<AllocatedLayerNumb;layer++){
		LayerData[layer]->DrawMonoBitmap(BmpPoint);
	}
}
void	AlgorithmInPagePLI::DrawItems(QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)
{
	if(LayerList.GetFirst()!=NULL){
		for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetValue()<0 || AllocatedLayerNumb<=c->GetValue()){
				continue;
			}
			//LayerData[c->d]->Draw(pnt, movx+GetDataInPage()->GetOutlineOffset()->x ,movy+GetDataInPage()->GetOutlineOffset()->y ,ZoomRate ,Attr);
			LayerData[c->GetValue()]->DrawItems(IData ,PData ,MovX ,MovY ,ZoomRate,DrawType);
		}
	}
	else{
		for(int layer=0;layer<GetLayerNumb();layer++){
			LayerData[layer]->DrawItems(IData ,PData ,MovX ,MovY ,ZoomRate,DrawType);
		}
	}
}
void	AlgorithmInPagePLI::DrawResultItem(ResultInPageRoot *R,QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)
{
	if(R!=NULL){
		ResultInPagePLI &Res=*((ResultInPagePLI *)R);
		if(LayerList.GetFirst()!=NULL){
			for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				int layer=c->GetValue();
				if(layer<0 || AllocatedLayerNumb<=layer){
					continue;
				}
				ResultInLayerPLI	&RL=Res.GetLayerData(layer);
				LayerData[c->GetValue()]->DrawResultItem(&RL,IData ,PData,MovX ,MovY ,ZoomRate,DrawType);
			}
		}
		else{
			for(int layer=0;layer<GetLayerNumb();layer++){
				ResultInLayerPLI	&RL=Res.GetLayerData(layer);
				LayerData[layer]->DrawResultItem(&RL,IData ,PData,MovX ,MovY ,ZoomRate,DrawType);
			}
		}
	}
	else{
		if(LayerList.GetFirst()!=NULL){
			for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
				int layer=c->GetValue();
				if(layer<0 || AllocatedLayerNumb<=layer){
					continue;
				}
				LayerData[c->GetValue()]->DrawResultItem(NULL,IData ,PData,MovX ,MovY ,ZoomRate,DrawType);
			}
		}
		else{
			for(int layer=0;layer<GetLayerNumb();layer++){
				LayerData[layer]->DrawResultItem(NULL,IData ,PData,MovX ,MovY ,ZoomRate,DrawType);
			}
		}
	}
}

void	AlgorithmInPagePLI::LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)
{
	for(int layer=0;layer<AllocatedLayerNumb;layer++){
		LayerData[layer]->LoopforAllItems(ItemFunc,Something);
	}
}

ExeResult	AlgorithmInPagePLI::ExecuteInitialAfterEditPrev(int ExeID 
														,ResultInPageRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	StartMilisecExecuteInitialAfterEditPrev();
	ExeResult	Ret=FuncExecuteInitialAfterEditPrev(ExeID ,Res,EInfo);
	CalcDone=true;
	EndMilisecExecuteInitialAfterEditPrev();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecuteInitialAfterEditPrev(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteInitialAfterEditPrev(ExeID ,Res,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;
	bool	RetryMode;
	do{
		RetryMode=false;
		for(int layer=0;layer<AllocatedLayerNumb;layer++){
			ExeResult	RR=LayerData[layer]->ExecuteInitialAfterEditPrev(ExeID ,&R->GetLayerData(layer),EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}
	}while(RetryMode==true);

	return Ret;
}

ExeResult	AlgorithmInPagePLI::ExecuteInitialAfterEdit(int ExeID 
														,ResultInPageRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	StartMilisecExecuteInitialAfterEdit();
	ExeResult	Ret=FuncExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	CalcDone=true;
	EndMilisecExecuteInitialAfterEdit();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;
	bool	RetryMode;
	do{
		RetryMode=false;
		for(int layer=0;layer<AllocatedLayerNumb;layer++){
			ExeResult	RR=LayerData[layer]->ExecuteInitialAfterEdit(ExeID ,&R->GetLayerData(layer),EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}
	}while(RetryMode==true);

	return Ret;
}

ExeResult	AlgorithmInPagePLI::ExecuteInitialAfterEditPost(int ExeID 
														,ResultInPageRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	StartMilisecExecuteInitialAfterEditPost();
	ExeResult	Ret=FuncExecuteInitialAfterEditPost(ExeID ,Res,EInfo);
	CalcDone=true;
	EndMilisecExecuteInitialAfterEditPost();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecuteInitialAfterEditPost(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteInitialAfterEditPost(ExeID ,Res,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;
	bool	RetryMode;
	do{
		RetryMode=false;
		for(int layer=0;layer<AllocatedLayerNumb;layer++){
			ExeResult	RR=LayerData[layer]->ExecuteInitialAfterEditPost(ExeID ,&R->GetLayerData(layer),EInfo);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}
	}while(RetryMode==true);

	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecuteStartByInspection();
	ExeResult	Ret=FuncExecuteStartByInspection(ExeID ,Res);
	EndMilisecExecuteStartByInspection();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteStartByInspection(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteStartByInspection(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteStartByInspection(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
		/*
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecuteStartByInspection(&R->GetLayerData(layer),pInspectionData);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
		*/
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecuteStartByInspection(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}

ExeResult	AlgorithmInPagePLI::ExecuteCaptured	(int ExeID ,ResultInPageRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	StartMilisecExecuteCaptured();
	ExeResult	Ret=FuncExecuteCaptured(ExeID ,Res,CapturedList);
	EndMilisecExecuteCaptured();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecuteCaptured	(int ExeID ,ResultInPageRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteCaptured(ExeID ,Res ,CapturedList);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteCaptured(ExeID ,&R->GetLayerData(layer),CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);

		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecuteCaptured(ExeID ,&R->GetLayerData(layer),CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecuteCaptured(ExeID 
										,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()),CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	return Ret;
}

ExeResult	AlgorithmInPagePLI::ExecutePreAlignment	(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecutePreAlignment();
	ExeResult	Ret=FuncExecutePreAlignment	(ExeID ,Res);
	EndMilisecExecutePreAlignment();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecutePreAlignment	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePreAlignment(ExeID ,Res );
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecutePreAlignment(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);

		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecutePreAlignment(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecutePreAlignment(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecuteAlignment();
	ExeResult	Ret=FuncExecuteAlignment	(ExeID ,Res);
	EndMilisecExecuteAlignment();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteAlignment(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteAlignment(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		for(int LoopCount=0;LoopCount<2;LoopCount++){
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecuteAlignment(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
			if(RetryMode==false){
				break;
			}
		}
		if(RetryMode==true){
			Ret=_ER_ReqRetryLater;
		}
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecuteAlignment(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecutePreProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecutePreProcessing();
	ExeResult	Ret=FuncExecutePreProcessing	(ExeID ,Res);
	EndMilisecExecutePreProcessing();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecutePreProcessing	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePreProcessing(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecutePreProcessing(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecutePreProcessing(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecutePreProcessing(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecuteProcessing			(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecuteProcessing();
	ExeResult	Ret=FuncExecuteProcessing	(ExeID ,Res);
	EndMilisecExecuteProcessing();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteProcessing(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteProcessing(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecuteProcessing(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecuteProcessing(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecuteProcessingRevived	(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecuteProcessingRevived();
	ExeResult	Ret=FuncExecuteProcessingRevived(ExeID ,Res);
	EndMilisecExecuteProcessingRevived();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecuteProcessingRevived(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteProcessingRevived(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}
	ResultInPagePLI *R=(ResultInPagePLI *)Res;
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteProcessingRevived(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecuteProcessingRevived(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecuteProcessingRevived(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}

	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecutePostProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecutePostProcessing();
	ExeResult	Ret=FuncExecutePostProcessing	(ExeID ,Res);
	EndMilisecExecutePostProcessing();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecutePostProcessing	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePostProcessing(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecutePostProcessing(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecutePostProcessing(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecutePostProcessing(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecutePreScanning		(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecutePreScanning();
	ExeResult	Ret=FuncExecutePreScanning	(ExeID ,Res);
	EndMilisecExecutePreScanning();
	return Ret;
}

ExeResult	AlgorithmInPagePLI::FuncExecutePreScanning	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePreScanning(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecutePreScanning(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecutePreScanning(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecutePreScanning(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecuteScanning		(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecuteScanning();
	ExeResult	Ret=FuncExecuteScanning	(ExeID ,Res);
	EndMilisecExecuteScanning();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecuteScanning	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteScanning(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecuteScanning(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecuteScanning(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecuteScanning(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePLI::ExecutePostScanning		(int ExeID ,ResultInPageRoot *Res)
{
	StartMilisecExecutePostScanning();
	ExeResult	Ret=FuncExecutePostScanning	(ExeID ,Res);
	EndMilisecExecutePostScanning();
	return Ret;
}
ExeResult	AlgorithmInPagePLI::FuncExecutePostScanning	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePostScanning(ExeID ,Res);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePLI *R=(ResultInPagePLI *)Res;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		bool	RetryMode;
		do{
			RetryMode=false;
			for(int layer=0;layer<AllocatedLayerNumb;layer++){
				ExeResult	RR=LayerData[layer]->ExecutePostScanning(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,GetPage(),LayerList);
		bool	RetryMode;
		do{
			RetryMode=false;
			for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
				int	layer=s->GetValue();
				ExeResult	RR=LayerData[layer]->ExecutePostScanning(ExeID ,&R->GetLayerData(layer));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	else{
		if(GetLayersBase()->GetTopLayerInCapturedPageLayer()>=0){
			bool	RetryMode;
			do{
				RetryMode=false;
				ExeResult	RR=LayerData[GetLayersBase()->GetTopLayerInCapturedPageLayer()]->ExecutePostScanning(ExeID ,&R->GetLayerData(GetLayersBase()->GetTopLayerInCapturedPageLayer()));
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}while(RetryMode==true);
		}
	}
	return Ret;
}

void	AlgorithmInPagePLI::MoveForAlignment(void)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->EnableMoveForAlignment==true){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot	*L=GetLayerData(layer);
			if(L!=NULL){
				L->MoveForAlignment();
			}
		}
	}
}

void	AlgorithmInPagePLI::RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->RefreshByMap(Mode,Map);
		}
	}
}
void	AlgorithmInPagePLI::RefreshByMap(int layer,ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	AlgorithmInLayerRoot	*L=GetLayerData(layer);
	if(L!=NULL){
		L->RefreshByMap(Mode,Map);
	}
}
void	AlgorithmInPagePLI::ClearResult(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->ClearResult();
		}
	}
}
void	AlgorithmInPagePLI::MakeIndependentItems(bool SubResultMoving, ResultInPageRoot *RPage,int localX ,int localY,AlgorithmItemIndependentPack &Data)
{
	if(RPage!=NULL){
		ResultInPagePLI	*RP=dynamic_cast<ResultInPagePLI *>(RPage);
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot	*L=GetLayerData(layer);
			if(L!=NULL){
				L->MakeIndependentItems(SubResultMoving, (RP==NULL)?NULL:&RP->GetLayerData(layer),localX ,localY,Data);
			}
		}
	}
}
void	AlgorithmInPagePLI::MakeIndependentItems(int Layer ,IntList	&Items,AlgorithmItemIndependentPack &Data)
{
	AlgorithmInLayerRoot	*L=GetLayerData(Layer);
	if(L!=NULL){
		L->MakeIndependentItems(Items,Data);
	}
}

void	AlgorithmInPagePLI::SetIndependentItemData(int32 Command
													,int32 LocalPage,int32 Layer,int32 ItemID
													,AlgorithmItemRoot *Data
													,IntList &EdittedMemberID
													,QByteArray &Something
													,QByteArray &AckData)
{
	AlgorithmInLayerRoot	*L=GetLayerData(Layer);
	if(L!=NULL){
		L->SetIndependentItemData(Command,LocalPage,Layer,ItemID,Data,EdittedMemberID,Something,AckData);
	}
}

bool	AlgorithmInPagePLI::GeneralDataRelease(int32 Command,void *data)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL && L->GeneralDataRelease(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	*AlgorithmInPagePLI::GeneralDataCreate(int32 Command,void *reqData)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			void	*ret=L->GeneralDataCreate(Command,reqData);
			if(ret!=NULL){
				return ret;
			}
		}
	}
	return NULL;
}
bool	AlgorithmInPagePLI::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			if(L->GeneralDataLoad(f,Command,data)==false){
				return false;
			}
		}
	}
	return true;
}
bool	AlgorithmInPagePLI::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			if(L->GeneralDataSave(f,Command,data)==false){
				return false;
			}
		}
	}
	return true;
}
bool	AlgorithmInPagePLI::GeneralDataReply(int32 Command,void *data)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			if(L->GeneralDataReply(Command,data)==false){
				return false;
			}
		}
	}
	return true;
}
void	AlgorithmInPagePLI::ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList)
{
	for(IntClass *d=LayerList.GetFirst();d!=NULL;d=d->GetNext()){
		int layer=d->GetValue();
		if(layer<GetLayerNumb()){
			AlgorithmInLayerRoot	*L=GetLayerData(layer);
			if(L!=NULL){
				L->ExecuteCopy(Pack);
			}
		}
	}
}
int		AlgorithmInPagePLI::GetSelectedItemCount(void)
{
	int	ret=0;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			ret+=L->GetSelectedItemCount();
		}
	}
	return ret;
}
int		AlgorithmInPagePLI::GetItemCount(void)
{
	int	ret=0;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			ret+=L->GetItemCount();
		}
	}
	return ret;
}

void	AlgorithmInPagePLI::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->ExecuteMove(GlobalDx,GlobalDy,AllItems);
		}
	}
	Changed=true;
	CalcDone=false;
}
void	AlgorithmInPagePLI::ExecuteMove(int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items ,bool AllItems)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			IntList	iList;
			for(ListPageLayerID *p=Items.GetFirst();p!=NULL;p=p->GetNext()){
				iList.Add(p->ID);
			}
			L->ExecuteMove(GlobalDx,GlobalDy,iList,AllItems);
		}
	}
	Changed=true;
	CalcDone=false;
}
void	AlgorithmInPagePLI::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->GetPageListForExecuteMove(PageList,GlobalDx,GlobalDy);
		}
	}
}

void	AlgorithmInPagePLI::ReleaseAllSelectedItem(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->ReleaseAllSelectedItem();
		}
	}
}

void	AlgorithmInPagePLI::SelectItems(FlexArea &Area ,const IntList &LayerList,bool MultiSelect)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->SelectArea(Area,MultiSelect);
			}
		}
	}
}

void	AlgorithmInPagePLI::SelectAll(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->SelectAll();
			}
		}
	}
}
void	AlgorithmInPagePLI::SelectLocked(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->SelectLocked();
			}
		}
	}
}
void	AlgorithmInPagePLI::SelectLibs(SelectLibListContainer &SelectedList)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmLibraryListContainer SList;
		for(SelectLibList *L=SelectedList.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->Layer==layer){
				SList.AppendList(new AlgorithmLibraryList(L->LibType,L->LibID,/**/""));
			}
		}
		if(SList.GetNumber()!=0){
			AlgorithmInLayerRoot	*Al=GetLayerData(layer);
			if(Al!=NULL){
				Al->ReleaseAllSelectedItem();
				Al->SelectLibs(SList);
			}
		}
	}
}
void	AlgorithmInPagePLI::SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode	,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->SelectItemsByOriginType(SelectMode);
			}
		}
	}
}

void	AlgorithmInPagePLI::CutArea(FlexArea &Area ,const IntList &LayerList,bool MultiSelect,const QByteArray &Something)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->CutArea(Area,MultiSelect,Something);
			}
		}
	}
}

void	AlgorithmInPagePLI::SeparateItems(FlexArea &Area ,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->SeparateItems(Area);
			}
		}
	}
}
void	AlgorithmInPagePLI::RegistArea(FlexArea &Area ,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->RegistArea(Area);
			}
		}
	}
}
void	AlgorithmInPagePLI::LockSelectedItems(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->LockSelectedItems();
			}
		}
	}
}
void	AlgorithmInPagePLI::UnlockAll(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->UnlockAll();
			}
		}
	}
}
void	AlgorithmInPagePLI::BindSelectedItems(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->BindSelectedItems();
			}
		}
	}
}


void	AlgorithmInPagePLI::DeleteSelectedItems(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->DeleteSelectedItems();
			}
		}
	}
}
void	AlgorithmInPagePLI::GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->GetAllItems(ItemPointers);
		}
	}
}
void	AlgorithmInPagePLI::EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		EnumItemsByLib(layer ,LibIDs ,ItemPointers);
	}
}
void	AlgorithmInPagePLI::EnumItemsByLib(int layer ,IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)
{
	AlgorithmInLayerRoot	*L=GetLayerData(layer);
	if(L!=NULL){
		L->EnumItemsByLib(LibIDs ,ItemPointers);
	}
}
void	AlgorithmInPagePLI::EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		EnumAllItems(layer ,ItemPointers);
	}
}
void	AlgorithmInPagePLI::EnumAllItems(int layer ,AlgorithmItemPointerListContainer &ItemPointers)
{
	AlgorithmInLayerRoot	*L=GetLayerData(layer);
	if(L!=NULL){
		L->EnumAllItems(ItemPointers);
	}
}
void	AlgorithmInPagePLI::GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->GetSelectedItems(ItemPointers);
		}
	}
}
void	AlgorithmInPagePLI::EnumSelectedItems(ListPageLayerIDPack &Items)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->EnumSelectedItems(Items);
		}
	}
}

void	AlgorithmInPagePLI::AppendItemsInPage(int Layer,AlgorithmItemPointerListContainer &SrcPointers)
{
	AlgorithmInLayerPLI	*L=(AlgorithmInLayerPLI *)GetLayerData(Layer);
	if(L!=NULL){
		L->AppendItems(SrcPointers);
	}
}

void	AlgorithmInPagePLI::RemoveItemsInPage(int Layer,IntList &IDList)
{
	AlgorithmInLayerPLI	*L=(AlgorithmInLayerPLI *)GetLayerData(Layer);
	if(L!=NULL){
		L->RemoveItems(IDList);
	}
}
void	AlgorithmInPagePLI::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->SwitchThresholdLevel(OldLevel ,NewLevel);
		}
	}
}
void	AlgorithmInPagePLI::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->CopyThresholdLevel(SourceLevelID ,DestLevelID);
		}
	}
}

void	AlgorithmInPagePLI::Activate(int PosX,int PosY ,IntList &LayerList,ListLayerAndIDPack &RetItem)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*Al=GetLayerData(L->GetValue());
			if(Al!=NULL){
				Al->Activate(PosX,PosY,RetItem);
			}
		}
	}
}
void	AlgorithmInPagePLI::Activate(int Layer ,int ItemID)
{
	AlgorithmInLayerRoot	*Al=GetLayerData(Layer);
	if(Al!=NULL){
		Al->Activate(ItemID);
	}
}
void	AlgorithmInPagePLI::AddActivate(int Layer ,int ItemID)
{
	AlgorithmInLayerRoot	*Al=GetLayerData(Layer);
	if(Al!=NULL){
		Al->AddActivate(ItemID);
	}
}
void	AlgorithmInPagePLI::Inactivate(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*L=GetLayerData(layer);
		if(L!=NULL){
			L->Inactivate();
		}
	}
}

void	AlgorithmInPagePLI::GetLayerAndItemID(int LocalX ,int LocalY ,ListLayerIDLibNamePack &ItemList ,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		IntList RetList;
		AlgorithmInLayerPLI	*AL=GetLayerDataPLI(L->GetValue());
		if(AL!=NULL){
			AL->GetItemIDListOnPoint(LocalX,LocalY,RetList);
			AL->FastSearchIDItemStart();
			for(IntClass *d=RetList.GetFirst();d!=NULL;d=d->GetNext()){
				int	ItemID=d->GetValue();
				AlgorithmItemRoot	*item=AL->FastSearchIDItem(ItemID);
				if(item!=NULL){
					ListLayerIDLibName	*k=new ListLayerIDLibName(L->GetValue(),ItemID,item->GetLibID());
					ItemList.AppendList(k);		
				}
			}
		}
	}
}
void	AlgorithmInPagePLI::GetLayerAndItemID(FlexArea &CoveredArea ,ListLayerAndIDPack &ItemList ,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		IntList RetList;
		AlgorithmInLayerPLI	*AL=GetLayerDataPLI(L->GetValue());
		if(AL!=NULL){
			AL->GetItemIDListOnPoint(CoveredArea,RetList);
			for(IntClass *d=RetList.GetFirst();d!=NULL;d=d->GetNext()){
				ItemList.AppendList(new ListLayerAndID(L->GetValue(),d->GetValue()));
			}
		}
	}
}
void	AlgorithmInPagePLI::GetItems(ListLayerAndIDPack &ItemList ,AlgorithmItemPointerListContainer &Items)
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		AlgorithmInLayerPLI	*AL=GetLayerDataPLI(Layer);
		if(AL!=NULL){
			AL->FastSearchIDItemStart();
		}
	}
	for(ListLayerAndID *L=ItemList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerPLI	*AL=GetLayerDataPLI(L->Layer);
		if(AL!=NULL){
			AlgorithmItemRoot	*item=AL->FastSearchIDItem(L->ID);
			if(item!=NULL){
				Items.Add(item);
			}
		}
	}
}
void	AlgorithmInPagePLI::EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		GetLayerDataPLI(Layer)->EnumOriginTypeItems(b ,Items);
	}
}
void	AlgorithmInPagePLI::EnumOriginTypeItems(int Layer ,OriginType b ,AlgorithmItemPointerListContainer &Items)
{
	GetLayerDataPLI(Layer)->EnumOriginTypeItems(b ,Items);
}
void	AlgorithmInPagePLI::EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		EnumItems(Layer ,caller,Items , func);
	}
}
void	AlgorithmInPagePLI::EnumItems(int Layer ,void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))
{
	AlgorithmInLayerPLI	*AL=GetLayerDataPLI(Layer);
	if(AL!=NULL){
		AL->EnumItems(caller,Items , func);
	}
}
void	AlgorithmInPagePLI::ScanItems(void *caller, void (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		ScanItems(Layer,caller, func);
	}
}
void	AlgorithmInPagePLI::ScanItems(int Layer,void *caller, void (*func)(void *caller,AlgorithmItemRoot *item))
{
	AlgorithmInLayerPLI	*AL=GetLayerDataPLI(Layer);
	if(AL!=NULL){
		AL->ScanItems(caller,func);
	}
}
void	AlgorithmInPagePLI::SelectItemByID(ListLayerAndIDPack &SelectedItem)
{
	for(ListLayerAndID *L=SelectedItem.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerPLI	*AL=GetLayerDataPLI(L->Layer);
		if(AL!=NULL){
			AlgorithmItemRoot	*a=AL->SearchIDItem(L->ID);
			if(a!=NULL){
				a->SetSelected(true);
			}
		}
	}
}


bool	AlgorithmInPagePLI::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy
														,FlexArea &area ,AlgorithmBase *OriginBase
														,int ItemClass)
{
	AlgorithmInLayerPLI	*L;
	if(PastedLayer==-1){
		L=(AlgorithmInLayerPLI	*)GetLayerData(item->Layer);
	}
	else{
		L=(AlgorithmInLayerPLI	*)GetLayerData(PastedLayer);
	}
	bool	Ret=false;
	if(L!=NULL){
		AlgorithmItemRoot	*a=L->CreateItem(ItemClass);
		if(Buff.isOpen()==false){
			Buff.open(QIODevice::ReadOnly);
		}
		else{
			Buff.close();
			Buff.open(QIODevice::ReadOnly);		
		}
		if(a!=NULL && a->Load(&Buff,GetLayersBase())==true){
			a->SetArea(area);
			if(L->AppendItem(a)==true){
				UndoElement<AlgorithmInLayerPLI>	*UPointer	=new UndoElement<AlgorithmInLayerPLI>(L,&AlgorithmInLayerPLI::UndoExecutePaste);
				::Save(UPointer->GetWritePointer(),a->GetID());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

				a->SetOrigin(OriginBase);
				Changed=true;
				CalcDone =false;
				Ret=true;
			}
			else{
				delete	a;
			}
		}
		else{
			delete	a;
		}
	}
	return Ret;
}

bool	AlgorithmInPagePLI::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste)
{
	AlgorithmInLayerPLI	*L;
	if(PastedLayer==-1){
		L=GetLayerDataPLI(item->Layer);
	}
	else{
		L=GetLayerDataPLI(PastedLayer);
	}
	bool	Ret=false;
	if(L!=NULL){
		AlgorithmItemRoot	*a=L->CreateItem(item->ItemClassType);
		QBuffer	Buff(&item->ItemData);
		Buff.open(QIODevice::ReadOnly);
		if(a->Load(&Buff,GetLayersBase())==true){
			a->SetArea(area);
			if(L->AppendItem(a)==true){
				if(SelectModeAfterPaste==true){
					a->SetSelected(true);
				}

				UndoElement<AlgorithmInLayerPLI>	*UPointer	=new UndoElement<AlgorithmInLayerPLI>(L,&AlgorithmInLayerPLI::UndoExecutePaste);
				::Save(UPointer->GetWritePointer(),a->GetID());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
					
				Changed=true;
				CalcDone =false;
				Ret=true;
			}
			else{
				delete	a;
			}
		}
		else{
			delete	a;
		}
	}
	return Ret;
}
bool	AlgorithmInPagePLI::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,VectorLineBase *Vector,bool SelectModeAfterPaste)
{
	AlgorithmInLayerPLI	*L;
	if(PastedLayer==-1){
		L=GetLayerDataPLI(item->Layer);
	}
	else{
		L=GetLayerDataPLI(PastedLayer);
	}
	bool	Ret=false;
	if(L!=NULL){
		AlgorithmItemRoot	*a=L->CreateItem(item->ItemClassType);
		QBuffer	Buff(&item->ItemData);
		Buff.open(QIODevice::ReadOnly);
		if(a->Load(&Buff,GetLayersBase())==true){
			a->SetVector(*Vector);
			if(L->AppendItem(a)==true){
				if(SelectModeAfterPaste==true){
					a->SetSelected(true);
				}

				UndoElement<AlgorithmInLayerPLI>	*UPointer	=new UndoElement<AlgorithmInLayerPLI>(L,&AlgorithmInLayerPLI::UndoExecutePaste);
				::Save(UPointer->GetWritePointer(),a->GetID());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

				Changed=true;
				CalcDone =false;
				Ret=true;
			}
			else{
				delete	a;
			}
		}
		else{
			delete	a;
		}
	}
	return Ret;
}

void	AlgorithmInPagePLI::GenerateAlgorithmItemCount(AlgorithmItemCountInPage &Ret)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot *Al=GetLayerData(layer);
		if(Al!=NULL){
			int	N=Al->GetItemCount();
			Ret.CountInLayer.Add(N);
		}
	}
}

void	AlgorithmInPagePLI::CopyFrom(AlgorithmBase *DestParent
									,AlgorithmInPageRoot *src 
									,int OffsetX,int OffsetY
									,int PartsMaster ,int PartsID
									,bool ReferedThresholdMode)
{
	Parent=DestParent;
	AlgorithmInPagePLI	*srcD=dynamic_cast<AlgorithmInPagePLI *>(src);
	if(srcD!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot	*d=GetLayerData(layer);
			AlgorithmInLayerRoot	*s=srcD->GetLayerData(layer);
			if(d!=NULL && s!=NULL){
				d->CopyFrom(this,s	,OffsetX,OffsetY
								,PartsMaster ,PartsID
								,ReferedThresholdMode);
			}
		}
	}
}
void	AlgorithmInPagePLI::InitializeFromParts(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->InitializeFromParts();
		}
	}
}
void	AlgorithmInPagePLI::CopyItems(FlexArea &SrcArea ,int mx ,int my)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->CopyItems(SrcArea ,mx ,my);
		}
	}
}

void	AlgorithmInPagePLI::MoveItemsToDispatcherForLoadingParts(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->MoveItemsToDispatcherForLoadingParts();
		}
	}
}
void	AlgorithmInPagePLI::CopyItemsFormDispatcherForParts(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->CopyItemsFormDispatcherForParts();
		}
	}
}
void	AlgorithmInPagePLI::RemoveItemFormDispatcher(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->RemoveItemFormDispatcher();
		}
	}
}

void	AlgorithmInPagePLI::GetOriginRootNames(NPListPack<OriginNames> &OriginNameList ,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerRoot	*d=GetLayerData(L->GetValue());
		if(d!=NULL){
			d->GetOriginRootNames(OriginNameList);
		}
	}
}

void	AlgorithmInPagePLI::SelectOriginRootNames(AlgorithmBase *OriginBase ,const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerRoot	*d=GetLayerData(L->GetValue());
		if(d!=NULL){
			d->SelectOriginRootNames(OriginBase);
		}
	}
}
void	AlgorithmInPagePLI::VisibleAll(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerRoot	*d=GetLayerData(L->GetValue());
		if(d!=NULL){
			d->VisibleAll();
		}
	}
}
void	AlgorithmInPagePLI::InvisibleAll(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerRoot	*d=GetLayerData(L->GetValue());
		if(d!=NULL){
			d->InvisibleAll();
		}
	}
}
void	AlgorithmInPagePLI::InvisibleSelected(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerRoot	*d=GetLayerData(L->GetValue());
		if(d!=NULL){
			d->InvisibleSelected();
		}
	}
}
void	AlgorithmInPagePLI::SelectManualCreature(const IntList &LayerList)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmInLayerRoot	*d=GetLayerData(L->GetValue());
		if(d!=NULL){
			d->SelectManualCreature();
		}
	}
}
bool	AlgorithmInPagePLI::IsEdited(void)
{
	if(Changed==true){
		return true;
	}
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			if(d->IsEdited()==true){
				return true;
			}
		}
	}
	return false;
}
bool	AlgorithmInPagePLI::IsCalcDone(void)
{
	if(CalcDone==false){
		return false;
	}
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			if(d->IsCalcDone()==false){
				return false;
			}
		}
	}
	return true;
}

void	AlgorithmInPagePLI::SetEdited(bool edited)
{
	Changed=edited;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->SetEdited(edited);
		}
	}
}
void	AlgorithmInPagePLI::SetCalcDone(bool calcdone)
{
	CalcDone=calcdone;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->SetCalcDone(calcdone);
		}
	}
}
void	AlgorithmInPagePLI::ResetProcessDone(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->ResetProcessDone();
		}
	}
}
bool	AlgorithmInPagePLI::IsProcessDone(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			if(d->IsProcessDone()==false){
				return false;
			}
		}
	}
	return true;
}
void	AlgorithmInPagePLI::SetProcessDone(bool b)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->SetProcessDone(b);
		}
	}
}
void	AlgorithmInPagePLI::GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)
{
	for(ItemPointerListInPage *pg=OutsideItems.GetFirst();pg!=NULL;pg=pg->GetNext()){
		for(int layer=0;layer<GetLayerNumb();layer++){
			ItemPointerListInLayer	*L=pg->LayerList.GetItem(layer);
			if(L==NULL){
				pg->LayerList.AppendList(new ItemPointerListInLayer(layer));
			}
		}
	}
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->GetOutsideItems(dx,dy,OutsideItems,MaxGlobalPage);
		}
	}
}

void	AlgorithmInPagePLI::ClearTemporaryItems(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*d=GetLayerData(layer);
		if(d!=NULL){
			d->ClearTemporaryItems();
		}
	}
}

void	AlgorithmInPagePLI::SetTemporaryItems(ItemPointerListInPage *Pg)
{
	for(ItemPointerListInLayer	*d=Pg->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
		for(int layer=0;layer<GetLayerNumb() && d!=NULL;layer++){
			if(d->Layer==layer){
				AlgorithmInLayerRoot	*k=GetLayerData(layer);
				if(k!=NULL){
					k->SetTemporaryItems(d);
				}
			}
		}
	}
}

void	AlgorithmInPagePLI::AddItemsForMove(ItemPointerListInPage *Pg)
{
	for(ItemPointerListInLayer	*d=Pg->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
		for(int layer=0;layer<GetLayerNumb() && d!=NULL;layer++){
			if(d->Layer==layer){
				AlgorithmInLayerRoot	*k=GetLayerData(layer);
				if(k!=NULL){
					k->AddItemsForMove(d);
				}
			}
		}
	}
}
bool	AlgorithmInPagePLI::ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy)
{
	bool	Ret=true;
	for(IntClass *c=PastedLayer.GetFirst();c!=NULL;c=c->GetNext()){
		AlgorithmInLayerRoot	*k=GetLayerData(c->GetValue());
		if(k!=NULL){
			if(k->ExecutePasteFromSelected(Dx,Dy)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

void	AlgorithmInPagePLI::SelectedItemListsForPaste(IntList &LayerList ,ExpandedSelectedItemListContainer &Lists)
{
	for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
		AlgorithmInLayerRoot	*k=GetLayerData(c->GetValue());
		if(k!=NULL){
			k->SelectedItemListsForPaste(Lists);
		}
	}
}
void	AlgorithmInPagePLI::DrawItemListsForPaste(int dx, int dy ,QImage &Pnt,int Layer,int ItemID ,double ZoomRate ,int movx ,int movy,int turn)
{
	AlgorithmInLayerRoot	*k=GetLayerData(Layer);
	if(k!=NULL){
		k->DrawItemListsForPaste(dx, dy ,Pnt,ItemID,ZoomRate ,movx ,movy,turn);
	}
}
void	AlgorithmInPagePLI::ExecuteTransformSelectedItems(TransformBase &M)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			k->ExecuteTransformSelectedItems(M);
		}
	}
}

bool	AlgorithmInPagePLI::SaveCSVMasterReport(QStringListListCSV &CSVData)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			if(k->SaveCSVMasterReport(CSVData)==false){
				return false;
			}
		}
	}
	return true;
}

void	AlgorithmInPagePLI::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			k->RotateItem(AngleDegree ,Cx, Cy);
		}
	}
}

void	AlgorithmInPagePLI::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			k->MirrorItem(MirrorMode ,PointX ,PointY);
		}
	}
}

bool	AlgorithmInPagePLI::GetSelectedCenter(DotListContainer &CenterByLayer)
{
	bool	Ret=false;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			int	Cx,Cy;
			if(k->GetSelectedCenter(Cx,Cy)==true){
				DotList	*a=new DotList(Cx,Cy);
				CenterByLayer.AppendList(a);
				Ret=true;
			}
		}
	}
	return Ret;
}
bool	AlgorithmInPagePLI::GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)
{
	X1=99999999;
	Y1=99999999;
	X2=-99999999;
	Y2=-99999999;
	bool	Ret=false;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			int	x1,y1,x2,y2;
			if(k->GetSelectedXY(x1 ,y1 ,x2 ,y2)==true){
				if(x1<X1)
					X1=x1;
				if(y1<Y1)
					Y1=y1;
				if(x2>X2)
					X2=x2;
				if(y2>Y2)
					Y2=y2;
				Ret=true;
			}
		}
	}
	return Ret;
}


bool	AlgorithmInPagePLI::GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)
{
	X1=99999999;
	Y1=99999999;
	X2=-99999999;
	Y2=-99999999;
	bool	Ret=false;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			int	x1,y1,x2,y2;
			if(k->GetOccupiedItemXY(x1 ,y1 ,x2 ,y2)==true)
				Ret=true;
			if(x1<X1)
				X1=x1;
			if(y1<Y1)
				Y1=y1;
			if(x2>X2)
				X2=x2;
			if(y2>Y2)
				Y2=y2;
		}
	}
	return Ret;
}
bool	AlgorithmInPagePLI::SaveItemsForLearning(ItemDataListWithIDContainer &Buff 
												,FlexArea &LocalArea
												,AlgorithmLibraryListContainer &LibList
												,int AddedX,int AddedY ,bool OkMode)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			if(k->SaveItemsForLearning(Buff,LocalArea,LibList,AddedX,AddedY,OkMode)==false){
				return false;
			}
		}
	}
	return true;
}

bool	AlgorithmInPagePLI::LoadItemsForLearning(ItemDataListWithIDContainer &Buff ,int AddedX ,int AddedY)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			if(k->LoadItemsForLearning(Buff,AddedX,AddedY)==false){
				return false;
			}
		}
	}
	return true;
}
bool	AlgorithmInPagePLI::GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			AlgorithmInLayerPLI	*Ly=dynamic_cast<AlgorithmInLayerPLI *>(k);
			if(Ly!=NULL){
				if(Ly->GetPointedItems(LocalX ,LocalY ,Items)==false){
					return false;
				}
			}
		}
	}
	return true;
}

HistgramByParamBase	*AlgorithmInPagePLI::GetHistgramBase(int Layer,int ItemID,int HistID)
{
	AlgorithmInLayerRoot	*k=GetLayerData(Layer);
	if(k!=NULL){
		HistgramByParamBase	*r=k->GetHistgramBase(ItemID,HistID);
		if(r!=NULL){
			return r;
		}
	}
	return NULL;
}
void	AlgorithmInPagePLI::MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			k->MakeUncoveredMap(BMap, XByte ,YLen);
		}
	}
}
void	AlgorithmInPagePLI::SetItemName(const QString &ItemName , bool OnlySelected)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			k->SetItemName(ItemName , OnlySelected);
		}
	}
}
bool	AlgorithmInPagePLI::ShrinkItems(const IntList &LayerList,int ExpandPixels,bool MaskForSameLib)
{
	bool	Ret=true;
	for(IntClass *d=LayerList.GetFirst();d!=NULL;d=d->GetNext()){
		int layer=d->GetValue();
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			if(k->ShrinkItems(ExpandPixels,MaskForSameLib)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

void	AlgorithmInPagePLI::EnumLibID(IntList &LibIDList)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerRoot	*k=GetLayerData(layer);
		if(k!=NULL){
			k->EnumLibID(LibIDList);
		}
	}
}
void	AlgorithmInPagePLI::MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			k->MakeItemList(LibID,RetContainer);
		}
	}
}

void	AlgorithmInPagePLI::EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		AlgorithmItemPointerListContainer	Ret;
		if(k!=NULL){
			k->EnumItemHistgram(HistID ,Ret);
			RetContainer+=Ret;
		}
	}
}

void	AlgorithmInPagePLI::EnumItemHistgram(int HistID ,int LibID ,AlgorithmItemPointerListContainer &RetContainer)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		AlgorithmItemPointerListContainer	Ret;
		if(k!=NULL){
			k->EnumItemHistgram(HistID ,LibID ,Ret);
			RetContainer+=Ret;
		}
	}
}

bool	AlgorithmInPagePLI::ManualExecuteAll(ManualExecuter &ManualExecuterData)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			if(k->ManualExecuteAll(ManualExecuterData)==false){
				return false;
			}
		}
	}
	return true;
}

void	AlgorithmInPagePLI::MakeBindedThreshold(BindedThresholdContainer &Container)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			k->MakeBindedThreshold(Container);
		}
	}
	return;
}

bool	AlgorithmInPagePLI::ExecuteAutoThreshold(ParamAutoThreshold &executer)
{
	bool	Ret=true;
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			if(k->ExecuteAutoThreshold(executer)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}

void	AlgorithmInPagePLI::GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items)
{
	Items.RemoveAll();

	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			k->GenerateItemListForAutoThreshold(Items);
		}
	}
}
AlgorithmItemRoot	*AlgorithmInPagePLI::SearchItemByName(const QString &ItemName)	const
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			AlgorithmItemRoot	*r=k->SearchItemByName(ItemName);
			if(r!=NULL){
				return r;
			}
		}
	}
	return NULL;
}
void	AlgorithmInPagePLI::UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			k->UpdateThreshold(LearningMenuID,LibID,ItemID,LRes);
		}
	}
}
void	AlgorithmInPagePLI::EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		ListPhasePageLayerLibIDPack TmpIDList;
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			k->EnumItems(TmpIDList);
		}
		ItemIDList.AddMove(TmpIDList);
	}
}
void	AlgorithmInPagePLI::EnumItems(int layer,ListPhasePageLayerLibIDPack &ItemIDList)
{
	ListPhasePageLayerLibIDPack TmpIDList;
	AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
	if(k!=NULL){
		k->EnumItems(TmpIDList);
	}
	ItemIDList.AddMove(TmpIDList);
}
bool	AlgorithmInPagePLI::MakeConfirmItem(ConfirmItemListContainer &ItemList)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		if(k!=NULL){
			ConfirmItemListContainer	tItemList;
			k->MakeConfirmItem(tItemList);
			for(ConfirmItemList *a=tItemList.GetFirst();a!=NULL;a=a->GetNext()){
				a->Layer=layer;
			}
			ItemList.AddMove(tItemList);
		}
	}
	return true;
}
AlgorithmItemRoot	*AlgorithmInPagePLI::FindItem(const AlgorithmItemIndex &Index)	const
{
	return GetItemData(Index.GetLayer(),Index.GetItemID());
}
void	AlgorithmInPagePLI::MasterImageHasChanged(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		AlgorithmInLayerPLI	*k=(AlgorithmInLayerPLI *)GetLayerData(layer);
		k->MasterImageHasChanged();
	}
}