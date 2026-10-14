/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



//#include "XAlignmentShiftRotationResource.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentShiftRotation.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDisplayImagePacket.h"
#include "XYCross.h"
#include "XAlignmentCommon.h"
#include "XImageProcess.h"
#include "XAlignmentShiftRotationCommon.h"
#include "XPacketAlignmentShiftRotation.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//==========================================================================================
AlignmentShiftRotationInPage::AlignmentShiftRotationInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
	ModeParallel.ModeParallelExecuteInitialAfterEdit	=true; 
}
AlignmentShiftRotationInPage::~AlignmentShiftRotationInPage(void)
{
}
AlgorithmItemRoot	*AlignmentShiftRotationInPage::CreateItem(int ItemClassType)
{
	AlignmentShiftRotationItem	*Item=new AlignmentShiftRotationItem();
	Item->SetParent(this);
	return Item;	
}

void	AlignmentShiftRotationInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		AlignmentShiftRotationItem	*BI=(AlignmentShiftRotationItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

//bool	AlignmentShiftRotationInPage::UseLibraryForMaskingInOtherPage(int LibID)
//{
//	bool	LimitedMaskInOtherPage=false;
//	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
//	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
//		if(CurrentGlobalPage==globalpage){
//			continue;
//		}
//		SlaveCommReqLibraryInMaskOfBlock	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
//		SlaveCommAckLibraryInMaskOfBlock	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
//		RCmd.UsedLibraries.Add(LibID);
//		if(RCmd.Send(globalpage,0,ACmd)==true){
//			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
//				LimitedMaskInOtherPage=true;
//			}
//		}
//	}
//	return LimitedMaskInOtherPage;
//}


ExeResult	AlignmentShiftRotationInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID,Res,EInfo);
	return Ret;
}
ExeResult	AlignmentShiftRotationInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res) 
{
	return _ER_true;
}
ExeResult	AlignmentShiftRotationInPage::ExecutePreAlignment(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteAlignment	(ExeID ,R);

	return Ret;
}

ExeResult	AlignmentShiftRotationInPage::ExecuteAlignment	(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteAlignment	(ExeID ,Res);

	return Ret;
}

void	AlignmentShiftRotationInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
}

int	AlignmentShiftRotationLibType=1;
int	AlignmentShiftRotationPage=0;
int	AlignmentShiftRotationLayer=0;
int	AlignmentShiftRotationID	=139;
int	AlignmentShiftRotationDbg;

//bool	AlignmentShiftRotationInPage::GetAlignmentShiftRotation(AlignmentPacket2D &Point)
//{
//	return true;
//}
//
//bool	AlignmentShiftRotationInPage::GetAlignmentShiftRotationGlobal(AlignmentPacket2D &Point)
//{
//	return true;
//}

void	AlignmentShiftRotationInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddAlignmentShiftRotationPointPacket *AddAlignmentShiftRotationPointPacketVar = dynamic_cast<AddAlignmentShiftRotationPointPacket *>(packet);
	if(AddAlignmentShiftRotationPointPacketVar !=NULL){
		AlignmentShiftRotationItem	*Item=new AlignmentShiftRotationItem();
		Item->SetParent(this);
		Item->SetArea(AddAlignmentShiftRotationPointPacketVar->Area);
		Item->SetLibID(AddAlignmentShiftRotationPointPacketVar->LibID);

		AlignmentShiftRotationBase	*BBase=(AlignmentShiftRotationBase *)GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(AddAlignmentShiftRotationPointPacketVar->LibID,LLib)==true){
			AlignmentShiftRotationLibrary	*ALib=dynamic_cast<AlignmentShiftRotationLibrary *>(LLib.GetLibrary());
			if(ALib!=NULL){
				((AlignmentShiftRotationItem *)Item)->CopyThresholdFromLibrary(&LLib);
			}
		}
		Item->SetManualCreated(true);
		GetParentBase()->ClearManagedCacheLib();

		AppendItem(Item);
		AddAlignmentShiftRotationPointPacketVar->RetItemID=Item->GetID();
		return;
	}
	CmdReqAlignmentShiftRotationItemtPack *CmdReqAlignmentShiftRotationItemtPackVar = dynamic_cast<CmdReqAlignmentShiftRotationItemtPack *>(packet);
	if(CmdReqAlignmentShiftRotationItemtPackVar!=NULL){
		CmdReqAlignmentShiftRotationItemtPackVar->Items->RemoveAll();
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
			AlignmentShiftRotationItemList *r = new AlignmentShiftRotationItemList();
			r->Data.Page = GetGlobalPage();
			r->Data.Phase= GetPhaseCode();
			r->Data.ItemID	= a->GetID();
			r->Data.LibID	= a->GetLibID();
			r->Data.CenterX	= a->MasterCx;
			r->Data.CenterY = a->MasterCy;
			r->Data.x1 = a->GetArea().GetMinX();
			r->Data.y1 = a->GetArea().GetMinY();
			r->Data.x2 = a->GetArea().GetMaxX();
			r->Data.y2 = a->GetArea().GetMaxY();
			CmdReqAlignmentShiftRotationItemtPackVar->Items->AppendList(r);
		}
		return;
	}
	CmdReqAlignmentShiftRotationItemAngleList	*CmdReqAlignmentShiftRotationItemAngleListVar=dynamic_cast<CmdReqAlignmentShiftRotationItemAngleList *>(packet);
	if(CmdReqAlignmentShiftRotationItemAngleListVar!=NULL){
		AlgorithmItemRoot	*item=GetItemData(0 ,CmdReqAlignmentShiftRotationItemAngleListVar->ItemID);
		if(item!=NULL){
			AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(item);
			if(a!=NULL){
				for(AlignmentShiftRotationItem::VHLines *L=a->VHLinesRotation.GetFirst();L!=NULL;L=L->GetNext()){
					CmdReqAlignmentShiftRotationItemAngleListVar->AngleList.Add(L->AngleRadian*180.0/M_PI);
				}
			}
		}
		return;
	}

	//GetAlignmentShiftRotationConclusion	*GetAlignmentShiftRotationConclusionVar=dynamic_cast<GetAlignmentShiftRotationConclusion *>(packet);
	//if(GetAlignmentShiftRotationConclusionVar!=NULL){
	//	GetAlignmentShiftRotationConclusionVar->m[0]=1.0;
	//	GetAlignmentShiftRotationConclusionVar->m[1]=0.0;
	//	GetAlignmentShiftRotationConclusionVar->m[2]=0.0;
	//	GetAlignmentShiftRotationConclusionVar->m[3]=0.0;
	//	GetAlignmentShiftRotationConclusionVar->m[4]=1.0;
	//	GetAlignmentShiftRotationConclusionVar->m[5]=0.0;
	//	//GetAlignmentShiftRotationParam(GetAlignmentShiftRotationConclusionVar->m);
	//	return;
	//}
	//CmdReqXYResult	*CmdReqXYResultVar=dynamic_cast<CmdReqXYResult *>(packet);
	//if(CmdReqXYResultVar!=NULL){
	//	if(MVector!=NULL && MVectorXRes!=0 && MVectorYRes!=0){
	//		int	Rx=CmdReqXYResultVar->localX/MVectorXRes;
	//		int	Ry=CmdReqXYResultVar->localY/MVectorYRes;
	//		if(0<=Rx && Rx<MVectorXNumb && 0<=Ry && Ry<MVectorYNumb){
	//			PointListForGroupIndex	*G=&MVector[Ry*MVectorXNumb+Rx];
	//			if(G->Plain!=NULL){
	//				CmdReqXYResultVar->AreaID	=G->Plain->AreaID;
	//				if(G->Plain->Index[0]!=NULL){
	//					CmdReqXYResultVar->EnableIndex1=true;
	//					G->Plain->Index[0]->GetCenter(CmdReqXYResultVar->IndexX1,CmdReqXYResultVar->IndexY1);
	//				}
	//				if(G->Plain->Index[1]!=NULL){
	//					CmdReqXYResultVar->EnableIndex2=true;
	//					G->Plain->Index[1]->GetCenter(CmdReqXYResultVar->IndexX2,CmdReqXYResultVar->IndexY2);
	//				}
	//				if(G->Plain->Index[2]!=NULL){
	//					CmdReqXYResultVar->EnableIndex3=true;
	//					G->Plain->Index[2]->GetCenter(CmdReqXYResultVar->IndexX3,CmdReqXYResultVar->IndexY3);
	//				}
	//			}
	//			if(G->Global!=NULL){
	//				CmdReqXYResultVar->GlobalAreaID	=(G->Global->AreaID);
	//				XAlignmentShiftRotationArea	*A=GetAlignmentShiftRotationArea(G->Global->AreaID);
	//				if(A!=NULL){
	//					IndexForGroupList	*AList=A->GetClosedIndexGroup(CmdReqXYResultVar->localX,CmdReqXYResultVar->localY);
	//					if(AList!=NULL){
	//						AList->CalcPosition(CmdReqXYResultVar->localX,CmdReqXYResultVar->localY
	//										, CmdReqXYResultVar->GlobalShiftX,CmdReqXYResultVar->GlobalShiftY);
	//						CmdReqXYResultVar->GlobalShiftX-=CmdReqXYResultVar->localX;
	//						CmdReqXYResultVar->GlobalShiftY-=CmdReqXYResultVar->localY;
	//					}
	//				}
	//			}
	//
	//			CmdReqXYResultVar->TotalShiftX	=G->Vector.x();
	//			CmdReqXYResultVar->TotalShiftY	=G->Vector.y();
	//		}
	//	}
	//	CmdReqXYResultVar->WholeMatchShiftX=ResultWholeMatchDx;
	//	CmdReqXYResultVar->WholeMatchShiftY=ResultWholeMatchDy;
	//	return;
	//}
	//
	//CmdReqAlignmentShiftRotationPointPacket	*CmdReqAlignmentShiftRotationPointPacketVar=dynamic_cast<CmdReqAlignmentShiftRotationPointPacket *>(packet);
	//if(CmdReqAlignmentShiftRotationPointPacketVar!=NULL){
	//	for(XAlignmentShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
	//		if((CmdReqAlignmentShiftRotationPointPacketVar->AreaName.isEmpty()==false && CmdReqAlignmentShiftRotationPointPacketVar->AreaName==a->AreaName)
	//		|| a->AreaID==CmdReqAlignmentShiftRotationPointPacketVar->AreaID){
	//			for(AlignmentGroup *g=a->GroupPack.GetFirst();g!=NULL;g=g->GetNext()){
	//				for(AlgorithmItemPointerList *p=g->ItemPack.GetFirst();p!=NULL;p=p->GetNext()){
	//					AlignmentShiftRotationItem	*Item=dynamic_cast<AlignmentShiftRotationItem *>(p->GetItem());
	//					AlignmentShiftRotationShiftList	*k=new AlignmentShiftRotationShiftList();
	//					k->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	//					k->ItemID	=Item->GetID();
	//					k->MasterX	=Item->MasterX;
	//					k->MasterY	=Item->MasterY;
	//					CmdReqAlignmentShiftRotationPointPacketVar->AlignmentShiftRotationPointData.AppendList(k);
	//				}
	//			}
	//		}
	//	}
	//	return;
	//}
	//CmdReqAlignmentShiftRotationShiftPacket	*CmdReqAlignmentShiftRotationShiftPacketVar=dynamic_cast<CmdReqAlignmentShiftRotationShiftPacket *>(packet);
	//if(CmdReqAlignmentShiftRotationShiftPacketVar!=NULL){
	//	for(IntClass *a=CmdReqAlignmentShiftRotationShiftPacketVar->ItemIDPoint->GetFirst();a!=NULL;a=a->GetNext()){
	//		AlgorithmItemRoot	*item=SearchIDItem(a->GetValue());
	//		AlignmentShiftRotationShiftList	*R=new AlignmentShiftRotationShiftList();
	//		if(item!=NULL){
	//			AlignmentShiftRotationItem	*AItem=dynamic_cast<AlignmentShiftRotationItem *>(item);
	//			if(AItem!=NULL){
	//				if(AItem->IsProcessDone()==true){
	//					R->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	//					R->ItemID	=	AItem->GetID();
	//					R->CalcDone	=	true;
	//					R->ShiftX	=	AItem->ResultDx;
	//					R->ShiftY	=	AItem->ResultDy;
	//					R->MasterX	=	AItem->MasterX;
	//					R->MasterY	=	AItem->MasterY;
	//					CmdReqAlignmentShiftRotationShiftPacketVar->ShiftDataPoint->AppendList(R);
	//				}
	//			}
	//		}
	//	}
	//	return;
	//}
	//
	//AddAlignmentShiftRotationPointPacket	*AddAlignmentShiftRotationPointPacketVar=dynamic_cast<AddAlignmentShiftRotationPointPacket *>(packet);
	//if(AddAlignmentShiftRotationPointPacketVar!=NULL){
	//	PureFlexAreaListContainer ItemArea;
	//	if(GetItemAreas( AddAlignmentShiftRotationPointPacketVar->LibID 
	//					,AddAlignmentShiftRotationPointPacketVar->AreaID 
	//					,AddAlignmentShiftRotationPointPacketVar->Area
	//					,ItemArea)==true){
	//		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	//		AlgorithmLibraryLevelContainer	SrcLib(Container);
	//		Container->GetLibrary(AddAlignmentShiftRotationPointPacketVar->LibID,SrcLib);
	//		AlgorithmLibrary	*ALib=SrcLib.GetLibrary();
	//		if(ALib!=NULL){
	//			for(PureFlexAreaList *f=ItemArea.GetFirst();f!=NULL;f=f->GetNext()){
	//				if(f->GetPatternByte()>10){
	//					AlignmentShiftRotationItem	*Item=dynamic_cast<AlignmentShiftRotationItem *>(CreateItem(0));
	//					Item->AreaID	=AddAlignmentShiftRotationPointPacketVar->AreaID;
	//					Item->SetLibID(AddAlignmentShiftRotationPointPacketVar->LibID);
	//					Item->SetParent(this);
	//					Item->SetArea(*f);
	//					Item->SetManualCreated(true);
	//					Item->CopyThresholdFromLibrary(&SrcLib);
	//					if(AppendItem(Item)==false){
	//						delete	Item;
	//					}
	//				}
	//			}
	//		}
	//	}
	//	return;
	//}
	//CmdReqAlignmentShiftRotationInfoListPack	*CmdReqAlignmentShiftRotationInfoListPackVar=dynamic_cast<CmdReqAlignmentShiftRotationInfoListPack *>(packet);
	//if(CmdReqAlignmentShiftRotationInfoListPackVar!=NULL){
	//	for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
	//		AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
	//		if(a->AreaID==CmdReqAlignmentShiftRotationInfoListPackVar->AreaID){
	//			AlignmentShiftRotationInfoList *L;
	//			for(L=CmdReqAlignmentShiftRotationInfoListPackVar->Points.GetFirst();L!=NULL;L=L->GetNext()){
	//				if(L->LibID==a->GetLibID()){
	//					IntClass	*d=L->AlignmentShiftRotationCount.GetFirst();
	//					d->SetValue(d->GetValue()+1);
	//					break;
	//				}
	//			}
	//			if(L==NULL){
	//				L=new AlignmentShiftRotationInfoList();
	//				L->LibID=a->GetLibID();
	//				L->AlignmentShiftRotationCount.Add(1);
	//				CmdReqAlignmentShiftRotationInfoListPackVar->Points.AppendList(L);
	//			}
	//		}
	//	}
	//	return;
	//}
	//CmdReqTestByLibID	*CmdReqTestByLibIDVar=dynamic_cast<CmdReqTestByLibID *>(packet);
	//if(CmdReqTestByLibIDVar!=NULL){
	//	XAlignmentShiftRotationArea	*a=GetAlignmentShiftRotationArea(CmdReqTestByLibIDVar->AreaID);
	//	if(a!=NULL){
	//		ImagePointerContainer ImageList;
	//		GetMasterBuffForMakeArea(true,ImageList);
	//		a->TestByLibID(ImageList,CmdReqTestByLibIDVar->LibList);
	//	}
	//	return;
	//}
	//
	//CmdReqGenerateAreaWithItemLibFromMask	*CmdReqGenerateAreaWithItemLibFromMaskVar=dynamic_cast<CmdReqGenerateAreaWithItemLibFromMask *>(packet);
	//if(CmdReqGenerateAreaWithItemLibFromMaskVar!=NULL){
	//	GenerateAreaWithItemLibFromMask(CmdReqGenerateAreaWithItemLibFromMaskVar->Priority
	//								   ,CmdReqGenerateAreaWithItemLibFromMaskVar->ItemLibID);
	//	return;
	//}
	//
	//CmdReqAlignmentShiftRotationItem	*CmdReqAlignmentShiftRotationItemVar=dynamic_cast<CmdReqAlignmentShiftRotationItem *>(packet);
	//if(CmdReqAlignmentShiftRotationItemVar!=NULL){
	//	for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
	//		AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
	//		if(a->AreaID==CmdReqAlignmentShiftRotationItemVar->AreaID && a->GetArea().IsInclude(CmdReqAlignmentShiftRotationItemVar->localX,CmdReqAlignmentShiftRotationItemVar->localY)==true){
	//			CmdReqAlignmentShiftRotationItemVar->RetItemID			=a->GetID();
	//			CmdReqAlignmentShiftRotationItemVar->RetLibID			=a->GetLibID();
	//			CmdReqAlignmentShiftRotationItemVar->RetSearchDot		=a->GetThresholdR(GetLayersBase())->SearchDot;
	//			CmdReqAlignmentShiftRotationItemVar->RetGlobalSearchDot	=a->GetThresholdR(GetLayersBase())->GlobalSearchDot;
	//			CmdReqAlignmentShiftRotationItemVar->RetKeepBW			=a->GetThresholdR(GetLayersBase())->KeepBW;
	//			break;
	//		}
	//	}
	//	return;
	//}
	//CmdSetAlignmentShiftRotationItem	*CmdSetAlignmentShiftRotationItemVar=dynamic_cast<CmdSetAlignmentShiftRotationItem *>(packet);
	//if(CmdSetAlignmentShiftRotationItemVar!=NULL){
	//	if(CmdSetAlignmentShiftRotationItemVar->ModeSetAll==false){
	//		AlgorithmItemRoot	*k=SearchIDItem(CmdSetAlignmentShiftRotationItemVar->ItemID);
	//		if(k!=NULL){
	//			AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
	//			a->GetThresholdW()->GlobalSearchDot	=CmdSetAlignmentShiftRotationItemVar->GlobalSearchDot;
	//			a->GetThresholdW()->SearchDot		=CmdSetAlignmentShiftRotationItemVar->SearchDot;
	//			a->GetThresholdW()->KeepBW			=CmdSetAlignmentShiftRotationItemVar->KeepBW;
	//		}
	//	}
	//	else{
	//		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
	//			if(k->GetLibID()==CmdSetAlignmentShiftRotationItemVar->LibID){
	//				AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
	//				a->GetThresholdW()->GlobalSearchDot	=CmdSetAlignmentShiftRotationItemVar->GlobalSearchDot;
	//				a->GetThresholdW()->SearchDot		=CmdSetAlignmentShiftRotationItemVar->SearchDot;
	//				a->GetThresholdW()->KeepBW			=CmdSetAlignmentShiftRotationItemVar->KeepBW;
	//			}
	//		}
	//	}
	//	return;
	//}
	//CmdReqAlignmentShiftRotationItemtPack	*CmdReqAlignmentShiftRotationItemtPackVar=dynamic_cast<CmdReqAlignmentShiftRotationItemtPack *>(packet);
	//if(CmdReqAlignmentShiftRotationItemtPackVar!=NULL){
	//	for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
	//		if(k->GetLibID()==CmdReqAlignmentShiftRotationItemtPackVar->LibID){
	//			AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
	//			if(a->AreaID==CmdReqAlignmentShiftRotationItemtPackVar->AreaID){
	//				AlignmentShiftRotationItemList	*p=new AlignmentShiftRotationItemList();
	//				p->Data.ItemID=a->GetID();
	//				a->GetCenter(p->Data.CenterX,p->Data.CenterY);
	//				a->GetXY(p->Data.x1,p->Data.y1,p->Data.x2,p->Data.y2);
	//				CmdReqAlignmentShiftRotationItemtPackVar->Items->AppendList(p);
	//			}
	//		}
	//	}
	//	return;
	//}
	//ChangeAlignmentShiftRotationThresholdCommon	*ChangeAlignmentShiftRotationThresholdCommonnVar=dynamic_cast<ChangeAlignmentShiftRotationThresholdCommon *>(packet);
	//if(ChangeAlignmentShiftRotationThresholdCommonnVar!=NULL){
	//	SetThresholdAlignmentShiftRotationInfo	ThresholdInfo;
	//	QBuffer	Buff(&ChangeAlignmentShiftRotationThresholdCommonnVar->InfosData);
	//	Buff.open(QIODevice::ReadWrite);
	//	if(ThresholdInfo.Load(&Buff)==true){
	//		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
	//			if(ChangeAlignmentShiftRotationThresholdCommonnVar->LibID==L->GetLibID()){
	//				AlignmentShiftRotationItem	*B=(AlignmentShiftRotationItem *)L;
	//				B->SetThresholdFromCommon(&ThresholdInfo);
	//			}
	//		}
	//	}
	//	return;
	//}
	//CmdRemoveAllOriginalAlignmentShiftRotationItems	*CmdRemoveAllOriginalAlignmentShiftRotationItemsVar=dynamic_cast<CmdRemoveAllOriginalAlignmentShiftRotationItems *>(packet);
	//if(CmdRemoveAllOriginalAlignmentShiftRotationItemsVar!=NULL){
	//	AlgorithmItemPointerListContainer Items;
	//	EnumOriginTypeItems((OriginType)CmdRemoveAllOriginalAlignmentShiftRotationItemsVar->GeneratedOrigin,Items);
	//	for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
	//		AlgorithmItemPointerList *NextP=a->GetNext();
	//		if(a->GetItem()->GetEditLocked()==true){
	//			Items.RemoveList(a);
	//			delete	a;
	//		}
	//		a=NextP;
	//	}
	//	RemoveItems(Items);
	//	return;
	//}
	//CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	//if(CmdAlignmentSetSearchDotVar!=NULL){
	//	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
	//		AlignmentShiftRotationItem	*B=(AlignmentShiftRotationItem *)L;
	//		B->GetThresholdW()->SearchDot		=CmdAlignmentSetSearchDotVar->SearchDotX;
	//		B->GetThresholdW()->GlobalSearchDot	=CmdAlignmentSetSearchDotVar->SearchDotX;
	//	}
	//	return;
	//}
	//CmdCreateAreaInMaskingArea	*CmdCreateAreaInMaskingAreaVar=dynamic_cast<CmdCreateAreaInMaskingArea *>(packet);
	//if(CmdCreateAreaInMaskingAreaVar!=NULL){
	//	PureFlexAreaListContainer FPack;
	//	ConstMapBufferListContainer MaskMap;
	//	if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
	//		ConstMapBuffer Map;
	//		MaskMap.BindOr(Map);		
	//	
	//		::PickupFlexArea(Map.GetBitMap(),Map.GetXByte(),Map.GetXLen(),Map.GetYLen() ,FPack);
	//	}
	//
	//	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
	//		XAlignmentShiftRotationArea	*a=new XAlignmentShiftRotationArea(this);
	//		a->AreaID			=GetMaxAreaID()+1;
	//		a->Area				=*p;
	//		//a->AreaName			="";
	//		//a->LimitedLib		=AddAlignmentShiftRotationAreaPacketVar->LimitedLib;
	//		//a->LibToCreateItems	=AddAlignmentShiftRotationAreaPacketVar->LibToCreateItems;
	//		a->Priority			=(XAlignmentShiftRotationArea::_EnumPriority)CmdCreateAreaInMaskingAreaVar->Priority;
	//		a->ManualCreated=true;
	//		Areas.AppendList(a);
	//
	//		UndoElement<AlignmentShiftRotationInPage>	*UPointer=new UndoElement<AlignmentShiftRotationInPage>(this,&AlignmentShiftRotationInPage::UndoAppendManualArea);
	//		::Save(UPointer->GetWritePointer(),a->AreaID);
	//		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	//	}
	//	return;
	//}
	//CmdReqAlignmentPointList	*CmdReqAlignmentPointListVar=dynamic_cast<CmdReqAlignmentPointList *>(packet);
	//if(CmdReqAlignmentPointListVar!=NULL){
	//	XAlignmentShiftRotationArea	*Area=GetAlignmentShiftRotationArea(CmdReqAlignmentPointListVar->AreaID);
	//	if(Area!=NULL){
	//		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
	//			AlignmentShiftRotationItem	*B=(AlignmentShiftRotationItem *)L;
	//			if(B->AreaID==CmdReqAlignmentPointListVar->AreaID){
	//				AlignmentPointList	*d=new AlignmentPointList();
	//				d->LibID=L->GetLibID();
	//				d->ItemID=L->GetID();
	//				L->GetXY(d->PosX1,d->PosY1,d->PosX2,d->PosY2);
	//				if(Area->Priority==XAlignmentShiftRotationArea::_PriorityGlobal){
	//					d->SearchDot	=B->GetThresholdR(GetLayersBase())->GlobalSearchDot;
	//				}
	//				else{
	//					d->SearchDot	=B->GetThresholdR(GetLayersBase())->SearchDot;
	//				}
	//				CmdReqAlignmentPointListVar->PointList->AppendList(d);
	//			}
	//		}
	//	}
	//	return;
	//}
}

double    AlignmentShiftRotationInPage::GetThreshLevel(AlgorithmLibrary *Lib,FlexArea &Area ,ImagePointerContainer &Images ,int dx ,int dy)
{
    int LTable[256];

    memset(LTable,0,sizeof(LTable));

	IntList		&GList=Lib->GetAdaptedGenLayers();
	if(GList.GetCount()==0){
		delete	Lib;
		return false;
	}
	ImageBuffer	*Buff=Images[GList.GetFirst()->GetValue()];

	Area.MakeBrightList(LTable,GetDotPerLine(),GetMaxLines(),*Buff,dx ,dy,1);

	int	DotSum=0;
	for(int i=0;i<256;i++){
		DotSum+=LTable[i];
	}

	int	PeakH;
	int	PeakL;
    for(PeakH=255;PeakH>1;PeakH--){
		if(LTable[PeakH]>=LTable[PeakH-1] && LTable[PeakH]>=LTable[PeakH-2] && (LTable[PeakH]+LTable[PeakH-1]+LTable[PeakH-2])>DotSum/32)
			break;
	}
	for(PeakL=0;PeakL<254;PeakL++){
		if(LTable[PeakL]>LTable[PeakL+1] && LTable[PeakL]>LTable[PeakL+2] && (LTable[PeakL]+LTable[PeakL+1]+LTable[PeakL+2])>DotSum/32)
			break;
	}

	int	MinL=0;
	int	MinD=99999999;
	for(int L=PeakL;L<PeakH;L++){
		if(L==0)
			continue;
		if(L==255)
			break;
		if(MinD>LTable[L]){
			MinD=LTable[L];
			MinL=L;
		}
	}

    return(MinL);
}

void	AlignmentShiftRotationInPage::GetMasterBuffForMakeArea(bool ReCalcBitMask ,ImagePointerContainer &ImageList)
{
	//bool	HasAllDataInBitBuff;
	//if(GetParamGlobal()->AllocBitBuffer==true && ((AlignmentShiftRotationBase *)GetParentBase())->UseBitBuff==true){
	//	HasAllDataInBitBuff=true;
	//	for(int Layer=0;Layer<GetLayerNumb();Layer++){
	//		if(ReCalcBitMask==true && RecalcMode==true){
	//			if(GetDataInLayer(Layer)->HasDataInBitBuff()==false){
	//				HasAllDataInBitBuff=false;
	//			}
	//		}
	//		else{
	//			if(HasDataInBitBuffAttr==false){
	//				HasAllDataInBitBuff=false;
	//			}
	//		}
	//	
	//}
	//else{
	//	HasAllDataInBitBuff=false;
	//}
	//
	//if(GetParamGlobal()->AllocBitBuffer==true && ((AlignmentShiftRotationBase *)GetParentBase())->UseBitBuff==true && HasAllDataInBitBuff==true){
	//	GetBitImages	(ImageList);
	//}
	//else{
	//	if(GetParamGlobal()->AllocateMasterBuff==true){
	//		GetMasterImages		(ImageList);
	//	}
	//	if(ImageList.GetCount()==0
	//	&& GetParamGlobal()->AllocateTargetBuff==true){
	//		GetTargetBuffList(ImageList);
	//	}
	//}
}


bool	AlignmentShiftRotationInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	AlignmentShiftRotationBase	*ABase=(AlignmentShiftRotationBase *)GetParentBase();

	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){
		GetParentBase()->LoadAllManagedCacheLib();
		AlgorithmLibraryLevelContainer	*TmpLib=GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			IntList	GenList=TmpLib->GetAdaptedGenLayers();
			for(int Layer=0;Layer<GetLayerNumb();Layer++){
				DataInLayer	*DL=GetDataInPage()->GetLayerData(Layer);
				if(DL->IsBitBuffEnabled()==true){
					DL->GetBitBuff().Memset(0);
				}
			}
			for(IntClass *c=GenList.GetFirst();c!=NULL;c=c->GetNext()){
				int	Layer=c->GetValue();
				DataInLayer	*DL=GetDataInPage()->GetLayerData(Layer);
				if(DL->IsBitBuffEnabled()==true){
					DL->GetBitBuff().CopyFrom(Info.BmpMap,Info.XByte ,Info.YLen);
				}
			}
			if(GenList.GetCount()==0){
				DataInLayer	*DL=GetDataInPage()->GetLayerData(0);
				if(DL->IsBitBuffEnabled()==true){
					DL->GetBitBuff().CopyFrom(Info.BmpMap,Info.XByte ,Info.YLen);
				}
			}

			//int	AreaN=0;
			//for(XAlignmentShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			//	if(a->LibToCreateItems.SearchLibrary(ABase->GetLibType(),Info.LibID)!=NULL){
			//		AreaN++;
			//	}
			//}
			//
			//if(AreaN==0){
			//	ConstMapBufferListContainer MaskMap;
			//	if(GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib)==true){
			//		ConstMapBuffer Map;
			//		MaskMap.BindOr(Map);
			//		BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
			//		XAlignmentShiftRotationArea	*a=new XAlignmentShiftRotationArea(this);
			//		a->AreaID			=GetMaxAreaID()+1;
			//		a->Area.BuildFromRaster((BYTE **)Map.GetBitMap(),Map.GetXByte() ,Map.GetYLen(),0,0);
			//		a->AreaName			=/**/"";
			//
			//		a->LibToCreateItems.Add(ABase->GetLibType() ,*TmpLib);
			//		a->ManualCreated=false;
			//		Areas.AppendList(a);
			//
			//		DeleteMatrixBuff(TmpData,Info.YLen);
			//	}
			//}
			//
			//for(XAlignmentShiftRotationArea *a=Areas.GetFirst();a!=NULL;a=a->GetNext()){
			//	if(a->LibToCreateItems.SearchLibrary(ABase->GetLibType(),Info.LibID)!=NULL){
			//		BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
			//		MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
			//					, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
			//		//ConstMapBufferListContainer MaskMap;
			//		//if(GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib)==true){
			//		//	ConstMapBuffer Map;
			//		//	MaskMap.BindOr(Map);
			//			AlignmentShiftRotationLibrary	*ALib=dynamic_cast<AlignmentShiftRotationLibrary *>(TmpLib->GetLibrary());
			//			bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(Info.LibID);
			//			bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,ALib,NULL);
			//			if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
			//				a->GenerateFromMap(TmpData,Info.XByte ,Info.YLen
			//									,Info.LibID
			//									,Info.OperationOrigin
			//									,Info.Origin
			//									,0,0);
			//			}
			//		//}
			//		DeleteMatrixBuff(TmpData,Info.YLen);
			//	}
			//}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(AlgorithmItemPI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			AlignmentShiftRotationItem	*a=dynamic_cast<AlignmentShiftRotationItem *>(k);
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

	return false;
}
AlignmentPacket2D	*AlignmentShiftRotationInPage::AppendAlignmentShiftRotationPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY ,bool FromGlobal)
{
	return NULL;
}

bool	AlignmentShiftRotationInPage::GetAlignmentShiftRotation(AlignmentPacket2D &Point)
{
	return false;
}

//==========================================================================================
AlignmentShiftRotationBase::AlignmentShiftRotationBase(LayersBase *Base)
	:AlgorithmBase(Base)
{
	ColorArea			=Qt::darkYellow;
	ColorAreaSelected	=Qt::yellow;
	ColorAreaActive		=Qt::red;
	ColorPoint			=Qt::darkGreen;
	ColorPointSelected	=Qt::green;
	ColorPointActive	=Qt::red;
	AlphaLevel	=100;


	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit=false;
	ModeParallelForPhase.ModeParallelExecuteAlignment		=false;

	SetParam(&ColorArea					, /**/"Color"		,/**/"ColorArea"			,"AlignmentShiftRotation Area color");
	SetParam(&ColorAreaSelected			, /**/"Color"		,/**/"ColorAreaSelected"	,"Selected AlignmentShiftRotation Area color");
	SetParam(&ColorAreaActive			, /**/"Color"		,/**/"ColorAreaActive"		,"Active AlignmentShiftRotation Area color");
	SetParam(&ColorPoint				, /**/"Color"		,/**/"ColorPoint"			,"AlignmentShiftRotation Point color");
	SetParam(&ColorPointSelected		, /**/"Color"		,/**/"ColorPointSelected"	,"Selected AlignmentShiftRotation Point color");
	SetParam(&ColorPointActive			, /**/"Color"		,/**/"ColorPointActive"		,"Active AlignmentShiftRotation Point color");
	SetParam(&AlphaLevel				, /**/"Color"		,/**/"AlphaLevel"			,"AlignmentShiftRotation transparent level");
}

AlgorithmDrawAttr	*AlignmentShiftRotationBase::CreateDrawAttr(void)
{
	return new AlignmentShiftRotationDrawAttr();
}


void	AlignmentShiftRotationBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		AlgorithmLibraryLevelContainer	LibData(this);
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
	CmdGetAlignmentShiftRotationLibraryListInPastePacket	*ACmdGetAlignmentShiftRotationLibraryListInPastePacketVar=dynamic_cast<CmdGetAlignmentShiftRotationLibraryListInPastePacket *>(packet);
	if(ACmdGetAlignmentShiftRotationLibraryListInPastePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),ACmdGetAlignmentShiftRotationLibraryListInPastePacketVar->LibFolderID 
				,ACmdGetAlignmentShiftRotationLibraryListInPastePacketVar->AList);
		}
		return;
	}
	CmdGetAlignmentShiftRotationLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAlignmentShiftRotationLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempAlignmentShiftRotationLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAlignmentShiftRotationLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadAlignmentShiftRotationLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAlignmentShiftRotationLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearAlignmentShiftRotationLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearAlignmentShiftRotationLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteAlignmentShiftRotationLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteAlignmentShiftRotationLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertAlignmentShiftRotationLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAlignmentShiftRotationLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(AlignmentShiftRotationVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAlignmentShiftRotationLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAlignmentShiftRotationLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(AlignmentShiftRotationVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetAlignmentShiftRotationLibraryNamePacket	*CmdGetAlignmentShiftRotationLibraryNamePacketVar=dynamic_cast<CmdGetAlignmentShiftRotationLibraryNamePacket *>(packet);
	if(CmdGetAlignmentShiftRotationLibraryNamePacketVar!=NULL){
		AlgorithmLibraryLevelContainer	TmpLib(this);
		if(GetLibraryContainer()!=NULL){
			CmdGetAlignmentShiftRotationLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetAlignmentShiftRotationLibraryNamePacketVar->LibID,TmpLib);
			CmdGetAlignmentShiftRotationLibraryNamePacketVar->LibName=TmpLib.GetLibName();
		}
		return;
	}
	CmdCreateTempAlignmentShiftRotationItemPacket	*CmdCreateTempAlignmentShiftRotationItemPacketVar=dynamic_cast<CmdCreateTempAlignmentShiftRotationItemPacket *>(packet);
	if(CmdCreateTempAlignmentShiftRotationItemPacketVar!=NULL){
		CmdCreateTempAlignmentShiftRotationItemPacketVar->Point=new AlignmentShiftRotationItem();
		return;
	}

	CmdAlignmentSetSearchDot	*CmdAlignmentSetSearchDotVar=dynamic_cast<CmdAlignmentSetSearchDot *>(packet);
	if(CmdAlignmentSetSearchDotVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(CmdAlignmentSetSearchDotVar);
		}
		return;
	}

}

void	AlignmentShiftRotationBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		AlignmentShiftRotationInPage	*Pg=(AlignmentShiftRotationInPage *)GetPageData(page);

		ReportedTopic	*r=new ReportedTopic(QString("P:")
											+QString::number(page)
											,QString::number(0));
		RetContainer.AppendList(r);
	}
}
