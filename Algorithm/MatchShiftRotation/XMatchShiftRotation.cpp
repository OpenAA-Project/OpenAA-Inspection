/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMatchShiftRotation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XMatchShiftRotationResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XMatchShiftRotation.h"
#include "XMatchShiftRotationPacket.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
//#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XImageProcess.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//==========================================================================================
MatchShiftRotationInPage::MatchShiftRotationInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
	ModeParallel.ModeParallelExecuteInitialAfterEdit	=true; 
}
MatchShiftRotationInPage::~MatchShiftRotationInPage(void)
{
}
AlgorithmItemRoot	*MatchShiftRotationInPage::CreateItem(int ItemClassType)
{
	MatchShiftRotationItem	*Item=new MatchShiftRotationItem();
	Item->SetParent(this);
	return Item;
}

bool	MatchShiftRotationInPage::ExistArea(int localX,int localY)
{
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Area.IsInclude(localX,localY)==true){
			return true;
		}
	}
	return false;
}

bool	MatchShiftRotationInPage::AppendItem(AlgorithmItemRoot *item)
{
	MatchShiftRotationItem	*AItem=dynamic_cast<MatchShiftRotationItem *>(item);
	if(AItem!=NULL){
		XMatchShiftRotationArea *A;
		for(A=Areas.GetFirst();A!=NULL;A=A->GetNext()){
			if(A->AreaID==AItem->AreaID){
				break;
			}
		}
		if(A==NULL){
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			//AItem->SetParent(this);
			//AItem->MakeArea(AItem->Threshold ,*GetMasterBuff());
			//AlgorithmInLayer::AppendItem(AItem,AItem->GetID());
			return true;
		}

		AItem->SetParent(this);
		item->SetItemID();

		return AlgorithmInPagePI::AppendItem(AItem);
	}
	return false;
}
void		MatchShiftRotationInPage::RemoveItem(AlgorithmItemRoot *item)
{
	AlgorithmInPagePI::RemoveItem(item);
	MatchShiftRotationItem	*AItem=dynamic_cast<MatchShiftRotationItem *>(item);
	if(AItem!=NULL){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			for(AlgorithmItemPointerList *L=a->ItemPack.GetFirst();L!=NULL;){
				AlgorithmItemPointerList *LNext=L->GetNext();
				if(L->GetItem()->GetID()==AItem->GetID()){
					a->ItemPack.RemoveList(L);
					delete	L;
				}
				L=LNext;
			}
		}
	}
}

XMatchShiftRotationArea	*MatchShiftRotationInPage::GetMatchShiftRotationArea(int AreaID)
{
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID==AreaID)
			return a;
	}
	return NULL;
}
void	MatchShiftRotationInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		MatchShiftRotationItem	*BI=(MatchShiftRotationItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

bool	MatchShiftRotationInPage::UseLibraryForMaskingInOtherPage(int LibID)
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

int	MatchShiftRotationInPage::GetMatchShiftRotationCount(void)
{
	return Areas.GetCount();
}
ExeResult	MatchShiftRotationInPage::ExecuteInitialAfterEdit	(int ExeID 
																,ResultInPageRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		Item->SetEffective(true);
	}
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->ExecuteInitialAfterEdit(EInfo);
	}

	return AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
ExeResult	MatchShiftRotationInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res) 
{
	for(XMatchShiftRotationArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		p->ExecuteStartByInspection();
	}
	return AlgorithmInPagePI::ExecuteStartByInspection(ExeID ,Res);
}
ExeResult	MatchShiftRotationInPage::ExecuteProcessing(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=_ER_true;
	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	for(XMatchShiftRotationArea *p=Areas.GetFirst();p!=NULL;p=p->GetNext()){
		p->ExecuteProcessing(GetFirstData());
	}
	AlgorithmInPagePI::ExecuteProcessing(ExeID ,R);

	return _ER_true;
}

void	MatchShiftRotationInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	
	for(XMatchShiftRotationArea *c=Areas.GetFirst();c!=NULL;c=c->GetNext()){
		c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

int	MatchShiftRotationLibType=1;
int	MatchShiftRotationPage=0;
int	MatchShiftRotationLayer=0;
int	MatchShiftRotationID	=139;
int	MatchShiftRotationDbg;


void	MatchShiftRotationInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	/*
	GetMatchShiftRotationConclusion	*GetMatchShiftRotationConclusionVar=dynamic_cast<GetMatchShiftRotationConclusion *>(packet);
	if(GetMatchShiftRotationConclusionVar!=NULL){
		GetMatchShiftRotationConclusionVar->m[0]=1.0;
		GetMatchShiftRotationConclusionVar->m[1]=0.0;
		GetMatchShiftRotationConclusionVar->m[2]=0.0;
		GetMatchShiftRotationConclusionVar->m[3]=0.0;
		GetMatchShiftRotationConclusionVar->m[4]=1.0;
		GetMatchShiftRotationConclusionVar->m[5]=0.0;
		//GetMatchShiftRotationParam(GetMatchShiftRotationConclusionVar->m);
		return;
	}
	CmdReqXYResult	*CmdReqXYResultVar=dynamic_cast<CmdReqXYResult *>(packet);
	if(CmdReqXYResultVar!=NULL){
		if(MVector!=NULL && MVectorXRes!=0 && MVectorYRes!=0){
			int	Rx=CmdReqXYResultVar->localX/MVectorXRes;
			int	Ry=CmdReqXYResultVar->localY/MVectorYRes;
			if(0<=Rx && Rx<MVectorXNumb && 0<=Ry && Ry<MVectorYNumb){
				PointListForGroupIndex	*G=&MVector[Ry*MVectorXNumb+Rx];
				if(G->Plain!=NULL){
					CmdReqXYResultVar->AreaID	=G->Plain->AreaID;
					if(G->Plain->Index[0]!=NULL){
						CmdReqXYResultVar->EnableIndex1=true;
						G->Plain->Index[0]->GetCenter(CmdReqXYResultVar->IndexX1,CmdReqXYResultVar->IndexY1);
					}
					if(G->Plain->Index[1]!=NULL){
						CmdReqXYResultVar->EnableIndex2=true;
						G->Plain->Index[1]->GetCenter(CmdReqXYResultVar->IndexX2,CmdReqXYResultVar->IndexY2);
					}
					if(G->Plain->Index[2]!=NULL){
						CmdReqXYResultVar->EnableIndex3=true;
						G->Plain->Index[2]->GetCenter(CmdReqXYResultVar->IndexX3,CmdReqXYResultVar->IndexY3);
					}
				}
				if(G->Global!=NULL){
					CmdReqXYResultVar->GlobalAreaID	=(G->Global->AreaID);
					XMatchShiftRotationArea	*A=GetMatchShiftRotationArea(G->Global->AreaID);
					if(A!=NULL){
						IndexForGroupList	*AList=A->GetClosedIndexGroup(CmdReqXYResultVar->localX,CmdReqXYResultVar->localY);
						if(AList!=NULL){
							AList->CalcPosition(CmdReqXYResultVar->localX,CmdReqXYResultVar->localY
											, CmdReqXYResultVar->GlobalShiftX,CmdReqXYResultVar->GlobalShiftY);
							CmdReqXYResultVar->GlobalShiftX-=CmdReqXYResultVar->localX;
							CmdReqXYResultVar->GlobalShiftY-=CmdReqXYResultVar->localY;
						}
					}
				}

				CmdReqXYResultVar->TotalShiftX	=G->Vector.x();
				CmdReqXYResultVar->TotalShiftY	=G->Vector.y();
			}
		}
		CmdReqXYResultVar->WholeMatchShiftX=ResultWholeMatchDx;
		CmdReqXYResultVar->WholeMatchShiftY=ResultWholeMatchDy;
		return;
	}
	CmdReqMatchShiftRotationPointPacket	*CmdReqMatchShiftRotationPointPacketVar=dynamic_cast<CmdReqMatchShiftRotationPointPacket *>(packet);
	if(CmdReqMatchShiftRotationPointPacketVar!=NULL){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if((CmdReqMatchShiftRotationPointPacketVar->AreaName.isEmpty()==false && CmdReqMatchShiftRotationPointPacketVar->AreaName==a->AreaName)
			|| a->AreaID==CmdReqMatchShiftRotationPointPacketVar->AreaID){
				for(AlignmentGroup *g=a->GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
					for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
						MatchShiftRotationItem	*Item=dynamic_cast<MatchShiftRotationItem *>(p->GetItem());
						MatchShiftRotationShiftList	*k=new MatchShiftRotationShiftList();
						k->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
						k->ItemID	=Item->GetID();
						k->MasterX	=Item->MasterX;
						k->MasterY	=Item->MasterY;
						CmdReqMatchShiftRotationPointPacketVar->MatchShiftRotationPointData.AppendList(k);
					}
				}
			}
		}
		return;
	}
	CmdReqMatchShiftRotationShiftPacket	*CmdReqMatchShiftRotationShiftPacketVar=dynamic_cast<CmdReqMatchShiftRotationShiftPacket *>(packet);
	if(CmdReqMatchShiftRotationShiftPacketVar!=NULL){
		for(IntClass *a=CmdReqMatchShiftRotationShiftPacketVar->ItemIDPoint->GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemRoot	*item=SearchIDItem(a->GetValue());
			MatchShiftRotationShiftList	*R=new MatchShiftRotationShiftList();
			if(item!=NULL){
				MatchShiftRotationItem	*AItem=dynamic_cast<MatchShiftRotationItem *>(item);
				if(AItem!=NULL){
					if(AItem->CalcDone==true){
						R->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
						R->ItemID	=	AItem->GetID();
						R->CalcDone	=	true;
						R->ShiftX	=	AItem->ResultDx;
						R->ShiftY	=	AItem->ResultDy;
						R->MasterX	=	AItem->MasterX;
						R->MasterY	=	AItem->MasterY;
						CmdReqMatchShiftRotationShiftPacketVar->ShiftDataPoint->AppendList(R);
					}
				}
			}
		}
		return;
	}
	*/
	AddMatchShiftRotationAreaPacket	*AddMatchShiftRotationAreaPacketVar=dynamic_cast<AddMatchShiftRotationAreaPacket *>(packet);
	if(AddMatchShiftRotationAreaPacketVar!=NULL){
		XMatchShiftRotationArea	*a=new XMatchShiftRotationArea(this);
		a->AreaID			=GetMaxAreaID()+1;
		a->Area				=AddMatchShiftRotationAreaPacketVar->Area;
		a->AreaName			=AddMatchShiftRotationAreaPacketVar->AreaName;
		a->LibID			=AddMatchShiftRotationAreaPacketVar->LibID;
		a->ManualCreated=true;
		Areas.AppendList(a);

		UndoElement<MatchShiftRotationInPage>	*UPointer=new UndoElement<MatchShiftRotationInPage>(this,&MatchShiftRotationInPage::UndoAppendManualArea);
		::Save(UPointer->GetWritePointer(),a->AreaID);
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	}
	ModifyMatchShiftRotationAreaPacket	*ModifyMatchShiftRotationAreaPacketVar=dynamic_cast<ModifyMatchShiftRotationAreaPacket *>(packet);
	if(ModifyMatchShiftRotationAreaPacketVar!=NULL){
		XMatchShiftRotationArea	*a=GetMatchShiftRotationArea(ModifyMatchShiftRotationAreaPacketVar->AreaID);
		if(a!=NULL){
			//a->Area		=ModifyMatchShiftRotationAreaPacketVar->Area;
			a->AreaName		=ModifyMatchShiftRotationAreaPacketVar->AreaName;
			a->LibID		=ModifyMatchShiftRotationAreaPacketVar->LibID;
			a->ManualCreated=true;
			return;
		}
	}
	AddMatchShiftRotationPointPacket	*AddMatchShiftRotationPointPacketVar=dynamic_cast<AddMatchShiftRotationPointPacket *>(packet);
	if(AddMatchShiftRotationPointPacketVar!=NULL){
		MatchShiftRotationItem	*Item=dynamic_cast<MatchShiftRotationItem *>(CreateItem(0));
		Item->AreaID	=AddMatchShiftRotationPointPacketVar->AreaID;
		Item->SetLibID(AddMatchShiftRotationPointPacketVar->LibID);
		Item->SetParent(this);
		Item->SetArea(AddMatchShiftRotationPointPacketVar->Area);
		Item->SetManualCreated(true);
		Item->SetItemName(AddMatchShiftRotationPointPacketVar->ItemName);
		MatchShiftRotationLibrary	*TmpLib=(MatchShiftRotationLibrary *)GetParentBase()->FindLibFromManagedCacheLib(AddMatchShiftRotationPointPacketVar->LibID);
		if(TmpLib!=NULL){
			Item->CopyThresholdFromLibrary(TmpLib->GetParentLevelContainer());
		}
		if(AppendItem(Item)==false){
			delete	Item;
		}
		return;
	}
	ModifyMatchShiftRotationPointPacket	*ModifyMatchShiftRotationPointPacketVar=dynamic_cast<ModifyMatchShiftRotationPointPacket *>(packet);
	if(ModifyMatchShiftRotationPointPacketVar!=NULL){
		MatchShiftRotationItem	*Item=(MatchShiftRotationItem	*)SearchIDItem(ModifyMatchShiftRotationPointPacketVar->ItemID);
		if(Item!=NULL){
			Item->SetLibID(ModifyMatchShiftRotationPointPacketVar->LibID);
			Item->SetManualCreated(true);
			Item->SetItemName(ModifyMatchShiftRotationPointPacketVar->ItemName);
			MatchShiftRotationLibrary	*TmpLib=(MatchShiftRotationLibrary *)GetParentBase()->FindLibFromManagedCacheLib(ModifyMatchShiftRotationPointPacketVar->LibID);
			if(TmpLib!=NULL){
				Item->CopyThresholdFromLibrary(TmpLib->GetParentLevelContainer());
			}
		}
		return;
	}
	DeleteMatchShiftRotationPointPacket	*DeleteMatchShiftRotationPointPacketVar=dynamic_cast<DeleteMatchShiftRotationPointPacket *>(packet);
	if(DeleteMatchShiftRotationPointPacketVar!=NULL){
		MatchShiftRotationItem	*Item=(MatchShiftRotationItem	*)SearchIDItem(DeleteMatchShiftRotationPointPacketVar->ItemID);
		if(Item!=NULL){
			RemoveItem(Item);
		}
		return;
	}
	CmdReqMatchShiftRotationInfoListPack	*CmdReqMatchShiftRotationInfoListPackVar=dynamic_cast<CmdReqMatchShiftRotationInfoListPack *>(packet);
	if(CmdReqMatchShiftRotationInfoListPackVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
			if(a->AreaID==CmdReqMatchShiftRotationInfoListPackVar->AreaID){
				MatchShiftRotationInfoList *L;
				for(L=CmdReqMatchShiftRotationInfoListPackVar->Points.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->LibID==a->GetLibID()){
						IntClass	*d=L->MatchShiftRotationCount.GetFirst();
						d->SetValue(d->GetValue()+1);
						break;
					}
				}
				if(L==NULL){
					L=new MatchShiftRotationInfoList();
					L->LibID=a->GetLibID();
					L->MatchShiftRotationCount.Add(1);
					CmdReqMatchShiftRotationInfoListPackVar->Points.AppendList(L);
				}
			}
		}
		return;
	}
	/*
	CmdReqTestByLibID	*CmdReqTestByLibIDVar=dynamic_cast<CmdReqTestByLibID *>(packet);
	if(CmdReqTestByLibIDVar!=NULL){
		XMatchShiftRotationArea	*a=GetMatchShiftRotationArea(CmdReqTestByLibIDVar->AreaID);
		ImagePointerContainer ImageList;
		GetMasterBuffForMakeArea(ImageList);
		a->TestByLibID(ImageList,CmdReqTestByLibIDVar->LibList);
		return;
	}
	CmdReqGenerateByLibID	*CmdReqGenerateByLibIDVar=dynamic_cast<CmdReqGenerateByLibID *>(packet);
	if(CmdReqGenerateByLibIDVar!=NULL){
		XMatchShiftRotationArea	*a=GetMatchShiftRotationArea(CmdReqGenerateByLibIDVar->AreaID);
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;){
			AlgorithmItemPI *NextK=k->GetNext();
			MatchShiftRotationItem	*item=dynamic_cast<MatchShiftRotationItem *>(k);
			if(item->AreaID==CmdReqGenerateByLibIDVar->AreaID && CmdReqGenerateByLibIDVar->LibList.IsInclude(item->GetLibID())==true){
				RemoveItem(item);
			}
			k=NextK;
		}
		//_heapchk();
		ImagePointerContainer ImageList;
		GetMasterBuffForMakeArea(ImageList);		
		for(IntClass *c=CmdReqGenerateByLibIDVar->LibList.GetFirst();c!=NULL;c=c->GetNext()){
			GetParentBase()->LoadManagedCacheLib(c->GetValue());
		}
		//_heapchk();
		a->GenerateByLibID	(ImageList ,CmdReqGenerateByLibIDVar->LibList);
		return;
	}
	CmdReqClearTestMap	*CmdReqClearTestMapVar=dynamic_cast<CmdReqClearTestMap *>(packet);
	if(CmdReqClearTestMapVar!=NULL){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->ClearTestMap();
		}
		return;
	}
	CmdReqAlignmentArea	*CmdReqAlignmentAreaVar=dynamic_cast<CmdReqAlignmentArea *>(packet);
	if(CmdReqAlignmentAreaVar!=NULL){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			CmdReqAlignmentAreaVar->Area+=a->Area;
		}
		return;
	}
	CmdReqGenerateAreaWithItemLibFromMask	*CmdReqGenerateAreaWithItemLibFromMaskVar=dynamic_cast<CmdReqGenerateAreaWithItemLibFromMask *>(packet);
	if(CmdReqGenerateAreaWithItemLibFromMaskVar!=NULL){
		GenerateAreaWithItemLibFromMask(CmdReqGenerateAreaWithItemLibFromMaskVar->Priority
									   ,CmdReqGenerateAreaWithItemLibFromMaskVar->ItemLibID);
		return;
	}
	*/
	RemoveMatchShiftRotationAreaPacket	*RemoveMatchShiftRotationAreaPacketVar=dynamic_cast<RemoveMatchShiftRotationAreaPacket *>(packet);
	if(RemoveMatchShiftRotationAreaPacketVar!=NULL){
		XMatchShiftRotationArea	*a=GetMatchShiftRotationArea(RemoveMatchShiftRotationAreaPacketVar->AreaID);
		if(a!=NULL){
			a->DeleteSelectedItems();
			Areas.RemoveList(a);
			delete	a;
			Changed=true;
			CalcDone =false;
		}
		return;
	}
	/*
	CmdReqMatchShiftRotationItem	*CmdReqMatchShiftRotationItemVar=dynamic_cast<CmdReqMatchShiftRotationItem *>(packet);
	if(CmdReqMatchShiftRotationItemVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
			if(a->AreaID==CmdReqMatchShiftRotationItemVar->AreaID && a->GetArea().IsInclude(CmdReqMatchShiftRotationItemVar->localX,CmdReqMatchShiftRotationItemVar->localY)==true){
				const MatchShiftRotationThreshold	*RThr=a->GetThresholdR(GetLayersBase());
				CmdReqMatchShiftRotationItemVar->RetItemID			=a->GetID();
				CmdReqMatchShiftRotationItemVar->RetLibID			=a->GetLibID();
				CmdReqMatchShiftRotationItemVar->RetSearchDot		=RThr->SearchDot;
				CmdReqMatchShiftRotationItemVar->RetGlobalSearchDot	=RThr->GlobalSearchDot;
				CmdReqMatchShiftRotationItemVar->RetKeepBW			=RThr->KeepBW;
				break;
			}
		}
		return;
	}
	CmdSetMatchShiftRotationItem	*CmdSetMatchShiftRotationItemVar=dynamic_cast<CmdSetMatchShiftRotationItem *>(packet);
	if(CmdSetMatchShiftRotationItemVar!=NULL){
		if(CmdSetMatchShiftRotationItemVar->ModeSetAll==false){
			AlgorithmItemRoot	*k=SearchIDItem(CmdSetMatchShiftRotationItemVar->ItemID);
			if(k!=NULL){
				MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
				a->GetThresholdW()->GlobalSearchDot	=CmdSetMatchShiftRotationItemVar->GlobalSearchDot;
				a->GetThresholdW()->SearchDot		=CmdSetMatchShiftRotationItemVar->SearchDot;
				a->GetThresholdW()->KeepBW			=CmdSetMatchShiftRotationItemVar->KeepBW;
			}
		}
		else{
			for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
				if(k->GetLibID()==CmdSetMatchShiftRotationItemVar->LibID){
					MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
					a->GetThresholdW()->GlobalSearchDot	=CmdSetMatchShiftRotationItemVar->GlobalSearchDot;
					a->GetThresholdW()->SearchDot		=CmdSetMatchShiftRotationItemVar->SearchDot;
					a->GetThresholdW()->KeepBW			=CmdSetMatchShiftRotationItemVar->KeepBW;
				}
			}
		}
		return;
	}
	*/
	CmdReqMatchShiftRotationItemPack	*CmdReqMatchShiftRotationItemPackVar=dynamic_cast<CmdReqMatchShiftRotationItemPack *>(packet);
	if(CmdReqMatchShiftRotationItemPackVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
			if(a->AreaID==CmdReqMatchShiftRotationItemPackVar->AreaID){
				MatchShiftRotationItemList	*p=new MatchShiftRotationItemList();
				p->Data.ItemID	=a->GetID();
				p->Data.LibID	=a->GetLibID();
				p->ItemName		=a->GetItemName();
				a->GetCenter(p->Data.CenterX,p->Data.CenterY);
				a->GetXY(p->Data.x1,p->Data.y1,p->Data.x2,p->Data.y2);
				CmdReqMatchShiftRotationItemPackVar->Items->AppendList(p);
			}
		}
		return;
	}
	CmdReqMatchShiftRotationItemImages	*CmdReqMatchShiftRotationItemImagesVar=dynamic_cast<CmdReqMatchShiftRotationItemImages *>(packet);
	if(CmdReqMatchShiftRotationItemImagesVar!=NULL){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			if(k->GetID()==CmdReqMatchShiftRotationItemImagesVar->ItemID){
				MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
				*CmdReqMatchShiftRotationItemImagesVar->Patterns=a->Patterns;
				break;
			}
		}
		return;
	}
	ReqShiftRotaionResult	*ReqShiftRotaionResultVar=dynamic_cast<ReqShiftRotaionResult *>(packet);
	if(ReqShiftRotaionResultVar!=NULL){
		XMatchShiftRotationArea	*a;
		if(ReqShiftRotaionResultVar->AreaID>=0)
			a=GetMatchShiftRotationArea(ReqShiftRotaionResultVar->AreaID);
		else
			a=Areas.GetFirst();
		if(a!=NULL){
			ReqShiftRotaionResultVar->Angle	=a->ResultAngle*180.0/M_PI;
			ReqShiftRotaionResultVar->ShiftX=a->ResultDx;
			ReqShiftRotaionResultVar->ShiftY=a->ResultDy;
			ReqShiftRotaionResultVar->Found	=true;
		}
		else{
			ReqShiftRotaionResultVar->Found	=false;
		}
		return;
	}
}

void	MatchShiftRotationInPage::UndoAppendManualArea(QIODevice *f)
{
	int32	AreaID;
	::Load(f,AreaID);
	XMatchShiftRotationArea	*Area=GetMatchShiftRotationArea(AreaID);
	if(Area!=NULL){
		RemoveArea(Area);
		delete	Area;
	}
}
int		MatchShiftRotationInPage::GetMaxAreaID(void)
{
	int	MaxAreaID=0;
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaID>MaxAreaID){
			MaxAreaID=a->AreaID;
		}
	}
	return MaxAreaID;
}

void	MatchShiftRotationInPage::RemoveArea(XMatchShiftRotationArea *a)
{
	a->DeleteAllItemsFromParent();
	Areas.RemoveList(a);
	//CleanupItems();
}
bool	MatchShiftRotationInPage::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
																,FlexArea &area ,AlgorithmBase *OriginBase
																,int ItemClass)
{
	if(Buff.isOpen()==false){
		Buff.open(QIODevice::ReadOnly);
	}
	else{
		Buff.close();
		Buff.open(QIODevice::ReadOnly);		
	}
	int32	Kind;
	if(::Load(&Buff,Kind)==false)
		return false;
	bool	Ret=false;
	if(Kind==1){
		XMatchShiftRotationArea	*a=new XMatchShiftRotationArea();
		a->AreaID	=GetMaxAreaID()+1;
		a->Area		=area;
		if(::Load(&Buff,a->AreaName)==false)
			return false;
		int32	Priority;
		if(::Load(&Buff,Priority)==false)
			return false;
		a->ManualCreated=true;
		Areas.AppendList(a);

		UndoElement<MatchShiftRotationInPage>	*UPointer=new UndoElement<MatchShiftRotationInPage>(this,&MatchShiftRotationInPage::UndoAppendManualArea);
		::Save(UPointer->GetWritePointer(),a->AreaID);
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		Ret=true;
	}
	else if(Kind==2){
		int32	AreaID;
		if(::Load(&Buff,AreaID)==false)
			return false;
		IntList	LayerList;
		if(LayerList.Load(&Buff)==false)
			return false;
		WORD	MoveDot;
		if(::Load(&Buff,MoveDot)==false)
			return false;
		WORD	GroupNumber;
		if(::Load(&Buff,GroupNumber)==false)
			return false;
		bool	UsageGlobal;
		if(::Load(&Buff,UsageGlobal)==false)
			return false;

		MatchShiftRotationItem	*Item=dynamic_cast<MatchShiftRotationItem *>(CreateItem(ItemClass));
		Item->AreaID								=AreaID;
		Item->GetThresholdW()->SearchLittleInItem	=MoveDot;
		//Item->GetThresholdW()->SearchDot	=MoveDot;

		Item->SetArea(area);

		Item->SetManualCreated(true);
		if(AppendItem(Item)==false){
			delete	Item;
		}
		else{	
			UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
			::Save(UPointer->GetWritePointer(),Item->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		
			Item->SetOrigin(OriginBase);
			Ret=true;
		}
	}
	Changed=true;
	CalcDone =false;
	return Ret;
}

bool	MatchShiftRotationInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	/*
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	MatchShiftRotationBase	*ABase=(MatchShiftRotationBase *)GetParentBase();

	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){

		GetParentBase()->LoadAllManagedCacheLib();
		MatchShiftRotationLibrary	*TmpLib=(MatchShiftRotationLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibToCreateItems.SearchLibrary(ABase->GetLibType(),Info.LibID)!=NULL){
					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					ConstMapBuffer MaskMap;
					GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib);
					bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(Info.LibID);
					bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,TmpLib,NULL);
					if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
						a->GenerateFromMap(TmpData,Info.LibID,Info.OperationOrigin);
					}
					DeleteMatrixBuff(TmpData,Info.YLen);
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			int		Cx,Cy;
			double	AckX,AckY;
			a->GetCenter(Cx,Cy);
			if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
				a->MoveTo(AckX-Cx,AckY-Cy);
			}
		}

		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
			if(a!=NULL){
				double	Cx,Cy;
				double	AckX,AckY;
				a->GetCenter(Cx,Cy);
				if(Info.RequireAlignmentPosition(Cx,Cy,AckX,AckY)==true){
					a->MoveTo(AckX-Cx,AckY-Cy);
				}
			}
		}
		return true;
	}
	*/

	return false;
}
	
bool		MatchShiftRotationInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	int32	N=Areas.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
	
bool		MatchShiftRotationInPage::Load(QIODevice *f)
{
	Areas.RemoveAll();
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		XMatchShiftRotationArea *a=new XMatchShiftRotationArea(this);
		if(a->Load(f,this)==false)
			return false;
		Areas.AppendList(a);
	}
	return true;

}


bool	MatchShiftRotationInPage::IsModeItemEditing(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchShiftRotationForm" ,/**/"");
	CmdIsModeItemEditingPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
	}
	if(MCmd.ItemMode==CmdIsModeItemEditingPacket::_ItemMode)
		return true;
	return false;
}
bool	MatchShiftRotationInPage::IsModeAreaEditing(void)
{
	GUIFormBase	*DProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchShiftRotationForm" ,/**/"");
	CmdIsModeItemEditingPacket	MCmd(GetLayersBase());
	if(DProp!=NULL){
		DProp->TransmitDirectly(&MCmd);
	}
	if(MCmd.ItemMode==CmdIsModeItemEditingPacket::_AreaMode)
		return true;
	return false;
}

int		MatchShiftRotationInPage::GetSelectedItemCount(void)
{
	if(IsModeAreaEditing()==true){
		int	N=0;
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				N++;
		}
		return N;
	}
	return AlgorithmInPagePI::GetSelectedItemCount();
}
void	MatchShiftRotationInPage::ReleaseAllSelectedItem(void)
{
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Selected=false;
	}
	AlgorithmInPagePI::ReleaseAllSelectedItem();
}
void	MatchShiftRotationInPage::SelectAll(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Selected=true;
		}
	}
	else{
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			MatchShiftRotationItem	*a=dynamic_cast<MatchShiftRotationItem *>(k);
			if((CurrentSelectedAreaID.GetCount()==0) || (CurrentSelectedAreaID.IsInclude(a->AreaID)==true)){
				a->SetSelected(true);
			}
			else{
				a->SetSelected(false);
			}
		}
	}
}
void	MatchShiftRotationInPage::SelectLocked(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Locked==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInPagePI::SelectLocked();
}
void	MatchShiftRotationInPage::SelectLibs(SelectLibListContainer &SelectedList)
{
	if(IsModeAreaEditing()==true){
	}
	else{
		SelectLibListContainer	PList;
		for(SelectLibList *L=SelectedList.GetFirst();L!=NULL;L=L->GetNext()){
			SelectLibList	*a=new SelectLibList();
			a->LibType	=	L->LibType;
			a->LibID	=	L->LibID;
			a->Layer	=0;
			PList.AppendList(a);
		}
		AlgorithmInPagePI::SelectLibs(PList);
	}
}

void	MatchShiftRotationInPage::SelectArea(FlexArea &localArea,bool MultiSelect)		
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.CheckOverlap(&localArea)==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else{
		AlgorithmInPagePI::SelectArea(localArea,MultiSelect);
	}
}

void	MatchShiftRotationInPage::SelectPoint(int localX, int localY)
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Area.IsInclude(localX,localY)==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else{
		AlgorithmInPagePI::SelectPoint(localX,localY);
	}
}

void	MatchShiftRotationInPage::CutArea(FlexArea &localArea,const IntList &LayerList ,bool MultiSelect,const QByteArray &Something)
{
	if(IsModeAreaEditing()==true){
	}
	else{
		AlgorithmInPagePI::CutArea(localArea,LayerList ,MultiSelect,Something);
	}
}
void	MatchShiftRotationInPage::RegistArea(FlexArea &localArea ,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInPagePI::RegistArea(localArea ,LayerList);
}
void	MatchShiftRotationInPage::DeleteSelectedItems(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInPagePI::DeleteSelectedItems();
}
void	MatchShiftRotationInPage::LockSelectedItems(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				a->Locked=true;
			else
				a->Locked=false;
		}
	}
	else
		AlgorithmInPagePI::SelectLocked();
}
void	MatchShiftRotationInPage::BindSelectedItems(const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		XMatchShiftRotationArea *M;
		for(M=Areas.GetFirst();M!=NULL;M=M->GetNext()){
			if(M->Selected==true){
				break;
			}
		}
		/*
		if(M!=NULL){
			for(XMatchShiftRotationArea *a=M->GetNext();a!=NULL;){
				if(a->Selected==true){
					XAlignmentLargePointer *p;
					while((p=a->GPack.GetFirst())!=NULL){
						a->GPack.RemoveList(p);
						M->GPack.AppendList(p);
					}
				}
				M->Area+=a->Area;
				XMatchShiftRotationArea *NextA=a->GetNext();
				Areas.RemoveList(a);
				Changed=true;
				CalcDone =false;
				delete	a;
				a=NextA;
			}
		}
		*/
	}
	else
		AlgorithmInPagePI::BindSelectedItems();
}
void	MatchShiftRotationInPage::Activate(int localX ,int localY ,IntList &LayerList,ListLayerAndIDPack &RetItem)	
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsInclude(localX,localY)==true)
				a->Active=true;
			else
				a->Active=false;
		}
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Active==true){
				RetItem.AppendList(new ListLayerAndID(0,a->AreaID));
			}
		}
	}
	else{
		IntList LayerList;
		AlgorithmInPagePI::Activate(localX ,localY ,LayerList,RetItem);
	}
}
void	MatchShiftRotationInPage::Activate(int Layer ,int ItemID)
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->AreaID==ItemID)
				a->Active=true;
			else
				a->Active=false;
		}
	}
	else
		AlgorithmInPagePI::Activate(0,ItemID);
}
void	MatchShiftRotationInPage::Inactivate(void)
{
	for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
		a->Active=false;
	}
	AlgorithmInPagePI::Inactivate();
}

void	MatchShiftRotationInPage::ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
	}
	else
		AlgorithmInPagePI::ExecuteCopy(Pack);
}
void	MatchShiftRotationInPage::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(IsModeAreaEditing()==true || AllItems==true){
	}
	else
		AlgorithmInPagePI::ExecuteMove(GlobalDx,GlobalDy,AllItems);
}

void	MatchShiftRotationInPage::GetOriginRootNames(NPListPack<OriginNames> &OriginNameList,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		AlgorithmBase	*Dim[1000];
		int				DimNumb=0;
		int				ItemNumb[1000];

		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			int i;
			for(i=0;i<DimNumb;i++){
				if(Dim[i]==a->Origin){
					ItemNumb[i]++;
					break;
				}
			}
			if(i>=DimNumb && i<sizeof(Dim)/sizeof(Dim[0])){
				Dim[DimNumb]=a->Origin;
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
	else
		AlgorithmInPagePI::GetOriginRootNames(OriginNameList,LayerList);
}

void	MatchShiftRotationInPage::SelectOriginRootNames(AlgorithmBase *OriginBase,const IntList &LayerList)
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Origin==OriginBase)
				a->Selected=true;
		}
	}
	else
		AlgorithmInPagePI::SelectOriginRootNames(OriginBase);
}
void	MatchShiftRotationInPage::VisibleAll(const IntList &LayerList)			
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Visible=true;
		}
	}
	else
		AlgorithmInPagePI::VisibleAll();
}
void	MatchShiftRotationInPage::InvisibleAll(const IntList &LayerList)			
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			a->Visible=false;
		}
	}
	else
		AlgorithmInPagePI::InvisibleAll();
}
void	MatchShiftRotationInPage::InvisibleSelected(const IntList &LayerList)		
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Selected==true)
				a->Visible=false;
			else
				a->Visible=true;
		}
	}
	else
		AlgorithmInPagePI::InvisibleSelected();
}
void	MatchShiftRotationInPage::SelectManualCreature(const IntList &LayerList)	
{
	if(IsModeAreaEditing()==true){
		for(XMatchShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->ManualCreated==true)
				a->Selected=true;
			else
				a->Selected=false;
		}
	}
	else
		AlgorithmInPagePI::SelectManualCreature();
}
void	MatchShiftRotationInPage::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		MatchShiftRotationItem	*BI=(MatchShiftRotationItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}
//==========================================================================================
MatchShiftRotationBase::MatchShiftRotationBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea			=Qt::darkYellow;
	ColorAreaSelected	=Qt::yellow;
	ColorAreaActive		=Qt::red;
	ColorPoint			=Qt::darkGreen;
	ColorPointSelected	=Qt::green;
	ColorPointActive	=Qt::red;
	AlphaLevel	=100;
	RoughSeparationAngle	=4;
	RoughSeparationShift	=3;
	RoughSeparationIsolation=7;

	SetParam(&ColorArea					, /**/"Color"		,/**/"ColorArea"			,"MatchShiftRotation Area color");
	SetParam(&ColorAreaSelected			, /**/"Color"		,/**/"ColorAreaSelected"	,"Selected MatchShiftRotation Area color");
	SetParam(&ColorAreaActive			, /**/"Color"		,/**/"ColorAreaActive"		,"Active MatchShiftRotation Area color");
	SetParam(&ColorPoint				, /**/"Color"		,/**/"ColorPoint"			,"MatchShiftRotation Point color");
	SetParam(&ColorPointSelected		, /**/"Color"		,/**/"ColorPointSelected"	,"Selected MatchShiftRotation Point color");
	SetParam(&ColorPointActive			, /**/"Color"		,/**/"ColorPointActive"		,"Active MatchShiftRotation Point color");
	SetParam(&AlphaLevel				, /**/"Color"		,/**/"AlphaLevel"			,"MatchShiftRotation transparent level");
	SetParam(&RoughSeparationAngle		, /**/"Setting"		,/**/"RoughSeparationAngle"		,"Separation angle for rough search");
	SetParam(&RoughSeparationShift		, /**/"Setting"		,/**/"RoughSeparationShift"		,"Separation shift for rough search");
	SetParam(&RoughSeparationIsolation	, /**/"Setting"		,/**/"RoughSeparationIsolation"	,"Separation isolation for rough search");
	
}

AlgorithmDrawAttr	*MatchShiftRotationBase::CreateDrawAttr(void)
{
	return new MatchShiftRotationDrawAttr();
}

bool	MatchShiftRotationBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	MatchShiftRotationItem	AItem();
	//GetSelectedMatchShiftRotationAreaPacket	SMode(GetLayersBase());
	//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" 
	//											,/**/"PropertyMatchShiftRotationForm" 
	//											,/**/"");
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&SMode);
	//}
	//templateData=SMode.BuffData;
	return true;
}

bool	MatchShiftRotationBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	FlexArea	area=item->Area;
	area.MoveToNoClip(globalDx,globalDy);
	for(int page=0;page<GetPageNumb();page++){
		if(GetLayersBase()->GetPageData(page)->IsOverlapped(area)==true){
			GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(area);

			AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(GetPageData(page));
			if(Ap!=NULL){

				AlgorithmItemRoot	*a=Ap->CreateItem(item->ItemClassType);
				QBuffer	Buff(&item->ItemData);
				Buff.open(QIODevice::ReadOnly);
				ListLayerAndIDPack	SelectedArea;
				SelectedArea.Load(&Buff);
				for(ListLayerAndID *s=SelectedArea.GetFirst();s!=NULL;s=s->GetNext()){
					if(s->Layer!=PastedLayer)
						continue;
					((MatchShiftRotationItem *)a)->AreaID=s->ID;
					a->SetArea(area);
					if(Ap->AppendItem(a)==false){
						delete	a;
					}
				}
			}
		}
	}
	return true;
}

void	MatchShiftRotationBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}

	CmdGetMatchShiftRotationLibraryListInPastePacket	*ACmdGetMatchShiftRotationLibraryListInPastePacketVar=dynamic_cast<CmdGetMatchShiftRotationLibraryListInPastePacket *>(packet);
	if(ACmdGetMatchShiftRotationLibraryListInPastePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),ACmdGetMatchShiftRotationLibraryListInPastePacketVar->LibFolderID 
				,ACmdGetMatchShiftRotationLibraryListInPastePacketVar->AList);
		}
		return;
	}
	CmdGetMatchShiftRotationLibraryListPacket	*AListPacket=dynamic_cast<CmdGetMatchShiftRotationLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempMatchShiftRotationLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempMatchShiftRotationLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadMatchShiftRotationLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadMatchShiftRotationLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearMatchShiftRotationLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearMatchShiftRotationLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteMatchShiftRotationLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteMatchShiftRotationLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertMatchShiftRotationLibraryPacket	*BInsLib=dynamic_cast<CmdInsertMatchShiftRotationLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(MatchShiftRotationVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateMatchShiftRotationLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateMatchShiftRotationLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(MatchShiftRotationVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetMatchShiftRotationLibraryNamePacket	*CmdGetMatchShiftRotationLibraryNamePacketVar=dynamic_cast<CmdGetMatchShiftRotationLibraryNamePacket *>(packet);
	if(CmdGetMatchShiftRotationLibraryNamePacketVar!=NULL){
		AlgorithmLibraryLevelContainer	TmpLib(this);
		if(GetLibraryContainer()!=NULL){
			CmdGetMatchShiftRotationLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetMatchShiftRotationLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetMatchShiftRotationLibraryNamePacketVar->Success==true){
				CmdGetMatchShiftRotationLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
	CmdCreateTempMatchShiftRotationItemPacket	*CmdCreateTempMatchShiftRotationItemPacketVar=dynamic_cast<CmdCreateTempMatchShiftRotationItemPacket *>(packet);
	if(CmdCreateTempMatchShiftRotationItemPacketVar!=NULL){
		CmdCreateTempMatchShiftRotationItemPacketVar->Point=new MatchShiftRotationItem();
		return;
	}
}


bool	MatchShiftRotationBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==MatchShiftRotationHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==MatchShiftRotationHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==MatchShiftRotationReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==MatchShiftRotationReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==MatchShiftRotationReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==MatchShiftRotationSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==MatchShiftRotationReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*MatchShiftRotationBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==MatchShiftRotationHistogramListSendCommand){
		//MatchShiftRotationHistogramListSend	*pSend=new MatchShiftRotationHistogramListSend();
		//if(reqData!=NULL){
		//	MatchShiftRotationHistogramListReq	*req=(MatchShiftRotationHistogramListReq *)reqData;
		//	pSend->ConstructList(req,this);
		//}
		//return pSend;
		return NULL;
	}
	else if(Command==MatchShiftRotationHistogramListReqCommand){
		//return new MatchShiftRotationHistogramListReq();
		return NULL;
	}
	else if(Command==MatchShiftRotationReqThresholdReqCommand){
		return new MatchShiftRotationThresholdReq();
	}
	else if(Command==MatchShiftRotationReqThresholdSendCommand){
		MatchShiftRotationThresholdSend	*pSend=new MatchShiftRotationThresholdSend();
		if(reqData!=NULL){
			MatchShiftRotationThresholdReq	*req=(MatchShiftRotationThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==MatchShiftRotationReqTryThresholdCommand){
		return new MatchShiftRotationReqTryThreshold();
	}
	else if(Command==MatchShiftRotationSendTryThresholdCommand){
		MatchShiftRotationSendTryThreshold	*pSend=new MatchShiftRotationSendTryThreshold();
		if(reqData!=NULL){
			MatchShiftRotationReqTryThreshold	*req=(MatchShiftRotationReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==MatchShiftRotationReqChangeShiftCommand){
		//return new MatchShiftRotationChangeShift();
		return NULL;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	MatchShiftRotationBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==MatchShiftRotationHistogramListSendCommand){
		//MatchShiftRotationHistogramListSend	*p=(MatchShiftRotationHistogramListSend *)data;
		//return p->Load(f);
		return true;
	}
	else if(Command==MatchShiftRotationHistogramListReqCommand){
		//MatchShiftRotationHistogramListReq	*p=(MatchShiftRotationHistogramListReq *)data;
		//return p->Load(f);
		return true;
	}
	else if(Command==MatchShiftRotationReqThresholdReqCommand){
		MatchShiftRotationThresholdReq	*p=(MatchShiftRotationThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==MatchShiftRotationReqThresholdSendCommand){
		MatchShiftRotationThresholdSend	*p=(MatchShiftRotationThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==MatchShiftRotationReqTryThresholdCommand){
		MatchShiftRotationReqTryThreshold	*p=(MatchShiftRotationReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==MatchShiftRotationSendTryThresholdCommand){
		MatchShiftRotationSendTryThreshold	*p=(MatchShiftRotationSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==MatchShiftRotationReqChangeShiftCommand){
		//MatchShiftRotationChangeShift	*p=(MatchShiftRotationChangeShift *)data;
		//return p->Load(f);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	MatchShiftRotationBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==MatchShiftRotationHistogramListSendCommand){
		//MatchShiftRotationHistogramListSend	*p=(MatchShiftRotationHistogramListSend *)data;
		//return p->Save(f);
		return true;
	}
	else if(Command==MatchShiftRotationHistogramListReqCommand){
		//MatchShiftRotationHistogramListReq	*p=(MatchShiftRotationHistogramListReq *)data;
		//return p->Save(f);
		return true;
	}
	else if(Command==MatchShiftRotationReqThresholdReqCommand){
		MatchShiftRotationThresholdReq	*p=(MatchShiftRotationThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==MatchShiftRotationReqThresholdSendCommand){
		MatchShiftRotationThresholdSend	*p=(MatchShiftRotationThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==MatchShiftRotationReqTryThresholdCommand){
		MatchShiftRotationReqTryThreshold	*p=(MatchShiftRotationReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==MatchShiftRotationSendTryThresholdCommand){
		MatchShiftRotationSendTryThreshold	*p=(MatchShiftRotationSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==MatchShiftRotationReqChangeShiftCommand){
		//MatchShiftRotationChangeShift	*p=(MatchShiftRotationChangeShift *)data;
		//return p->Save(f);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	MatchShiftRotationBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==MatchShiftRotationHistogramListSendCommand){
		//MatchShiftRotationHistogramListSend	*p=(MatchShiftRotationHistogramListSend *)data;
		return true;
	}
	else if(Command==MatchShiftRotationHistogramListReqCommand){
		//MatchShiftRotationHistogramListReq	*p=(MatchShiftRotationHistogramListReq *)data;
		return true;
	}
	else if(Command==MatchShiftRotationReqThresholdReqCommand){
		MatchShiftRotationThresholdReq	*p=(MatchShiftRotationThresholdReq *)data;
		return true;
	}
	else if(Command==MatchShiftRotationReqThresholdSendCommand){
		MatchShiftRotationThresholdSend	*p=(MatchShiftRotationThresholdSend *)data;
		return true;
	}
	else if(Command==MatchShiftRotationReqTryThresholdCommand){
		MatchShiftRotationReqTryThreshold	*p=(MatchShiftRotationReqTryThreshold *)data;
		return true;
	}
	else if(Command==MatchShiftRotationSendTryThresholdCommand){
		MatchShiftRotationSendTryThreshold	*p=(MatchShiftRotationSendTryThreshold *)data;
		return true;
	}
	else if(Command==MatchShiftRotationReqChangeShiftCommand){
		//MatchShiftRotationChangeShift	*p=(MatchShiftRotationChangeShift *)data;
		//p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}

//====================================================================================

