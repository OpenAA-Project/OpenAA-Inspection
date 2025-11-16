/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\HoleWallInspection\XHoleWallInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XHoleWallInspection.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XHoleWallLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XHoleWallAlgoPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "XPropertyHoleWallCommon.h"
#include "SettingArrayShiftMulInPageDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================
HoleWallThreshold::HoleWallThreshold(HoleWallItem *parent)
:AlgorithmThreshold(parent)
{
    NGSize				=20;
	SearchDot			=0;
}

void	HoleWallThreshold::RegistHist(void)
{
	static	bool	InitialStr	=false;

	static	QString	StrNGSize	;
	static	QString	StrShiftX	;
	static	QString	StrShiftY	;

	if(InitialStr==false){
		StrNGSize	="NG size";
		StrShiftX	="shift X";
		StrShiftY	="shift Y";
		InitialStr=true;
	}

	RegistInt			(StrNGSize,Hist_HoleWall_NGSize	);
	RegistInt			(StrShiftX,Hist_HoleWall_ShiftX	);
	RegistInt			(StrShiftY,Hist_HoleWall_ShiftY	);

}
void	HoleWallThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const HoleWallThreshold *s=(const HoleWallThreshold *)&src;
    NGSize		=s->NGSize;
	SearchDot	=s->SearchDot;
}

bool	HoleWallThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const HoleWallThreshold *s=(const HoleWallThreshold *)&src;
    if(NGSize		!=s->NGSize	)	return false;
	if(SearchDot	!=s->SearchDot)	return false;
	return true;
}
bool	HoleWallThreshold::Save(QIODevice *f)
{
	WORD	Ver=HoleWallVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,NGSize)==false)
		return false;
    if(::Save(f,SearchDot)==false)
		return false;
	return true;
}

bool	HoleWallThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,NGSize)==false)
		return false;
    if(::Load(f,SearchDot)==false)
		return false;

	return true;
}

void	HoleWallThreshold::FromLibrary(AlgorithmLibrary *src)
{
	HoleWallLibrary	*LSrc=dynamic_cast<HoleWallLibrary *>(src);
	if(LSrc==NULL)
		return;
    NGSize		=LSrc->NGSize;
	SearchDot	=LSrc->SearchDot;
}
void	HoleWallThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	HoleWallLibrary	*LDst=dynamic_cast<HoleWallLibrary *>(Dest);
	if(LDst==NULL)
		return;
    LDst->NGSize		=NGSize;
	LDst->SearchDot		=SearchDot;
}

//=====================================================================================


HoleWallInLayer::HoleWallInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLITemplate<HoleWallItem,HoleWallInPage,HoleWallBase>(parent)
{
	PickupBmp=NULL;
	PickupBmpXByte=0;
	PickupBmpYLen=0;
}
HoleWallInLayer::~HoleWallInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}
bool		HoleWallInLayer::AppendItem(AlgorithmItemRoot *item)
{
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
	}
	return AlgorithmInLayerPLI::AppendItem(item);
}

bool		HoleWallInLayer::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}

bool		HoleWallInLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	return AlgorithmInLayerPLI::AppendItemFromLoad(item);
}

bool		HoleWallInLayer::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	return AlgorithmInLayerPLI::AppendItem(item,itemID);
}

ExeResult	HoleWallInLayer::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInLayerRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{	
	ExeResult	Ret=AlgorithmInLayerPLITemplate<HoleWallItem,HoleWallInPage,HoleWallBase>::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);

	return Ret;
}

void	HoleWallInLayer::CreatePickupBmpBuff(void)
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

void	HoleWallInLayer::PickupTest(HoleWallLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);

	LibData.MakePickupTest(GetPage()
							,GetMasterBuff()
							,MaskMap.GetBitMap()
							,PickupBmp,NULL
							,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
							,((HoleWallBase *)GetParentBase())->OmitZoneDot);
}
void	HoleWallInLayer::GenerateBlocks(HoleWallLibrary *LibDim[],int LibDimNumb)
{
	CreatePickupBmpBuff();

	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPLI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}
	HoleWallInPage	*Ap=(HoleWallInPage	*)GetParentInPage();
	HoleWallBase	*ABase=(HoleWallBase *)GetParentBase();

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
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(Container);
			if(GetParentBase()->GetLibraryContainer()->GetLibrary(L->GetLibID() ,*Lib)==true){
				LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
			}
			else{
				delete	Lib;
				Lib=NULL;
			}
		}
		if(Lib!=NULL){
			HoleWallLibrary	*BLib=dynamic_cast<HoleWallLibrary *>(Lib->GetLibrary());
			L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
		}
	}
	DeleteMatrixBuff(TempMap	 ,GetMaxLines());
	DeleteMatrixBuff(TempMap2	 ,GetMaxLines());

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());

	BYTE **tMaskMap	=MakeMatrixBuff(XByte,GetMaxLines());
	GetParentBase()->LoadAllManagedCacheLib();

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());
		ConstMapBuffer MaskMap;
		GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();

		
		MatrixBuffCopy(tMaskMap,XByte,GetMaxLines()
                     , MaskBitmap,XByte,GetMaxLines());
		MatrixBuffNotAnd (tMaskMap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

		int	Layer=GetLayer();
		if(LibDim[i]->GetAdaptedPickLayers().GetCount()>0){
			Layer=LibDim[i]->GetAdaptedPickLayers()[0];
		}
		
		LibDim[i]->MakePickupTest(GetPage()
								,tGetParentInPage()->GetLayerData(Layer)->GetMasterBuff()
								,(const BYTE **)tMaskMap
								,CurrentMap,OcupyMap
								,XByte ,GetDotPerLine(),GetMaxLines()
								,((HoleWallBase *)GetParentBase())->OmitZoneDot);

		NPListPack<AlgorithmItemPLI>	TmpBlockData;
		LibDim[i]->MakeBlock(GetPage()
			,CurrentMap
			,XByte ,GetDotPerLine(),GetMaxLines()
			,TmpBlockData
			,Ap->ShiftXParamLeft,Ap->ShiftXParamRight
			,Ap->ShiftYRate*ABase->Thickness);

		AlgorithmItemPLI	*q;
		while((q=TmpBlockData.GetFirst())!=NULL){
			TmpBlockData.RemoveList(q);
			AppendItem(q);
		}
		MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(CurrentMap	 ,GetMaxLines());
	DeleteMatrixBuff(OcupyMap	 ,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap,GetMaxLines());
	DeleteMatrixBuff(GeneratedMap,GetMaxLines());
	DeleteMatrixBuff(tMaskMap	 ,GetMaxLines());
}
void	HoleWallInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedHoleWallFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedHoleWallFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		HoleWallItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			HoleWallItem	*B=(HoleWallItem *)L;
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
				HoleWallItem	*B=(HoleWallItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestHoleWallPacket	*CmdClearTestHoleWallPacketVar=dynamic_cast<CmdClearTestHoleWallPacket *>(packet);
	if(CmdClearTestHoleWallPacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}
	CmdHoleWallInfoListPacket	*CmdHoleWallInfoListPacketVar=dynamic_cast<CmdHoleWallInfoListPacket *>(packet);
	if(CmdHoleWallInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			HoleWallInfoList	*a;
			for(a=CmdHoleWallInfoListPacketVar->HoleWallInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->HoleWallCount.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new HoleWallInfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					a->HoleWallCount.Add(0);
				}
				IntClass	*d=a->HoleWallCount.GetItem(GetLayer());
				if(d!=NULL){
					d->SetValue(d->GetValue()+1);
				}
				CmdHoleWallInfoListPacketVar->HoleWallInfos->AppendList(a);
			}
		}
		return;
	}
	CmdGetHoleWallFromList	*CmdGetHoleWallFromListVar=dynamic_cast<CmdGetHoleWallFromList *>(packet);
	if(CmdGetHoleWallFromListVar!=NULL){
		HoleWallItem *Item=(HoleWallItem *)SearchIDItem(CmdGetHoleWallFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetHoleWallFromListVar->HoleWallInfoOnMouse=Item;
		return;
	}
	CmdCreateHoleWallItem	*CmdCreateHoleWallItemVar=dynamic_cast<CmdCreateHoleWallItem *>(packet);
	if(CmdCreateHoleWallItemVar!=NULL){
		CmdCreateHoleWallItemVar->HoleWall=(HoleWallItem *)CreateItem(0);
		return;
	}
	CmdAddByteHoleWallItemPacket	*AddBItem=dynamic_cast<CmdAddByteHoleWallItemPacket *>(packet);
	if(AddBItem!=NULL){
		QBuffer	MBuff(&AddBItem->Buff);
		HoleWallItem	*Item=new HoleWallItem();
		MBuff.open(QIODevice::ReadWrite);
		Item->Load(&MBuff,GetLayersBase());
		Item->SetArea(AddBItem->Area);
		Item->SetManualCreated(true);
		GetParentBase()->ClearManagedCacheLib();
		if(AppendItem(Item)==false){
			delete	Item;
		}
		return;
	}
	CmdRemoveAllOriginalHoleWallItems	*CmdRemoveAllOriginalHoleWallItemsVar=dynamic_cast<CmdRemoveAllOriginalHoleWallItems *>(packet);
	if(CmdRemoveAllOriginalHoleWallItemsVar!=NULL){
		AlgorithmItemPointerListContainer Items;
		EnumOriginTypeItems((OriginType)CmdRemoveAllOriginalHoleWallItemsVar->GeneratedOrigin,Items);
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
	ChangeHoleWallsThresholdCommon	*ChangeHoleWallsThresholdCommonVar=dynamic_cast<ChangeHoleWallsThresholdCommon *>(packet);
	if(ChangeHoleWallsThresholdCommonVar!=NULL){
		SetThresholdHoleWallInfo	ThresholdInfo;
		QBuffer	Buff(&ChangeHoleWallsThresholdCommonVar->InfosData);
		Buff.open(QIODevice::ReadWrite);
		if(ThresholdInfo.Load(&Buff)==true){
			for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
				if(ChangeHoleWallsThresholdCommonVar->BlockLibID==L->GetLibID()){
					HoleWallItem	*B=(HoleWallItem *)L;
					B->SetThresholdFromCommon(&ThresholdInfo);
				}
			}
		}
		return;
	}
	CmdMakeBitBuff	*CmdMakeBitBuffVar=dynamic_cast<CmdMakeBitBuff *>(packet);
	if(CmdMakeBitBuffVar!=NULL){
		DataInLayer	*Ly=GetDataInLayer();
		if(Ly->IsBitBuffEnabled()==true){
			for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
				HoleWallItem *B=(HoleWallItem *)L;
				B->GetArea().MakeBitData(Ly->GetBitBuff(),0,0);
			}
		}
		return;
	}
}

void	HoleWallInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	HoleWallDrawAttr	*BAttr=dynamic_cast<HoleWallDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==HoleWallDrawAttr::_LibTest){
			if(PickupBmp!=NULL){
				HoleWallBase	*BBase=dynamic_cast<HoleWallBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==HoleWallDrawAttr::_CreatedBlock){
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	HoleWallInLayer::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		HoleWallItem	*BI=(HoleWallItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

bool	HoleWallInLayer::UseLibraryForMaskingInOtherPage(int LibID)
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

void	HoleWallInLayer::MoveFromPipe(GeneralPipeInfo &Info)
{
	for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
		HoleWallItem	*a=dynamic_cast<HoleWallItem *>(k);
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


//===========================================================================================
HoleWallInPage::HoleWallInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLITemplate<HoleWallItem,HoleWallInLayer,HoleWallBase>(parent)
{
	for(int i=0;i<sizeof(ShiftXParamLeft)/sizeof(ShiftXParamLeft[0]);i++){
		ShiftXParamLeft[i]=0;
		ShiftXParamRight[i]=0;
	}
}
HoleWallInPage::~HoleWallInPage(void)
{
}

ExeResult	HoleWallInPage::ExecuteInitialAfterEdit	(int ExeID 
													,ResultInPageRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePLI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
	return Ret;
}

ExeResult	HoleWallInPage::ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)
{
	return AlgorithmInPagePLI::ExecutePreAlignment(ExeID ,Res);
}

void	HoleWallInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPickupTestHoleWallPacket	*BPickLib=dynamic_cast<CmdPickupTestHoleWallPacket *>(packet);
	if(BPickLib!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			if(BPickLib->LibPoint->GetAdaptedPickLayers().IsInclude(Layer)==true){
				HoleWallInLayer	*BL=dynamic_cast<HoleWallInLayer *>(GetLayerData(Layer));
				BL->PickupTest(*(HoleWallLibrary *)BPickLib->LibPoint->GetLibrary());
			}
		}
		return;
	}
	CmdGenerateHoleWallPacket	*BGenerated=dynamic_cast<CmdGenerateHoleWallPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
			int	N=0;
			for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext()){
				AlgorithmLibraryLevelContainer	*Lib=new AlgorithmLibraryLevelContainer(Container);
				GetLibraryContainer()->GetLibrary(L->GetValue(),*Lib);
				if(Lib->GetAdaptedGenLayers().IsInclude(Layer)==true){
					LibDim[N]=Lib;
					N++;
				}
				else{
					delete	Lib;
				}
			}
			if(N>0){
				HoleWallInLayer	*BL=dynamic_cast<HoleWallInLayer *>(GetLayerData(Layer));
				if(BL!=NULL){
					HoleWallLibrary	**DDim=new HoleWallLibrary*[N];
					for(int i=0;i<N;i++){
						DDim[i]=dynamic_cast<HoleWallLibrary *>(LibDim[i]->GetLibrary());
					}
					BL->GenerateBlocks(DDim,N);
					delete	[]DDim;
				}
			}
			for(int i=0;i<N;i++){
				delete	LibDim[i];
			}
			delete	[]LibDim;
		}
		return;
	}
	CmdAddByteHoleWallItemPacket	*AddBItem=dynamic_cast<CmdAddByteHoleWallItemPacket *>(packet);
	if(AddBItem!=NULL){
		for(IntClass *c=AddBItem->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}

	CmdHoleWallInfoListPacket	*CmdHoleWallInfoListPacketVar=dynamic_cast<CmdHoleWallInfoListPacket *>(packet);
	if(CmdHoleWallInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdGetHoleWallFromList	*CmdGetHoleWallFromListVar=dynamic_cast<CmdGetHoleWallFromList *>(packet);
	if(CmdGetHoleWallFromListVar!=NULL){
		if(CmdGetHoleWallFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetHoleWallFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdClearTestHoleWallPacket	*CmdClearTestHoleWallPacketVar=dynamic_cast<CmdClearTestHoleWallPacket *>(packet);
	if(CmdClearTestHoleWallPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdRemoveAllOriginalHoleWallItems	*CmdRemoveAllOriginalHoleWallItemsVar=dynamic_cast<CmdRemoveAllOriginalHoleWallItems *>(packet);
	if(CmdRemoveAllOriginalHoleWallItemsVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	ChangeHoleWallsThresholdCommon	*ChangeHoleWallsThresholdCommonVar=dynamic_cast<ChangeHoleWallsThresholdCommon *>(packet);
	if(ChangeHoleWallsThresholdCommonVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdMakeBitBuff	*CmdMakeBitBuffVar=dynamic_cast<CmdMakeBitBuff *>(packet);
	if(CmdMakeBitBuffVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
}

bool	HoleWallInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	HoleWallBase	*ABase=(HoleWallBase *)GetParentBase();

	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){

		GetParentBase()->LoadAllManagedCacheLib();
		HoleWallLibrary	*TmpLib=(HoleWallLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			for(int layer=0;layer<GetLayerNumb();layer++){
				NPListPack<AlgorithmItemPLI>	TmpBlockData;
				if(TmpLib->HasGenLayer(layer)==true){
					//RemoveAllItems();

					HoleWallInLayer	*BL=(HoleWallInLayer*)GetLayerData(layer);
					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					ConstMapBuffer MaskMap;
					BL->GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib);
					bool	LimitedMaskInOtherPage=BL->UseLibraryForMaskingInOtherPage(Info.LibID);
					bool	LimitedMaskInThisPage =BL->IncludeLibInReflection(_Reflection_Mask,TmpLib,NULL);
					if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
						MatrixBuffAnd	(TmpData ,MaskMap.GetBitMap() ,Info.XByte ,Info.YLen);

						if(Info.Something.count()>0){
							QBuffer	tBuff(&Info.Something);
							tBuff.open(QIODevice::ReadOnly);

							int32	AlgoCount;
							if(::Load(&tBuff,AlgoCount)==false){
								DeleteMatrixBuff(TmpData,Info.YLen);
								return false;
							}
							QByteArray	DataArray;
							bool		Found=false;
							for(int i=0;i<AlgoCount;i++){
								QString	AlgoName;
								if(::Load(&tBuff,AlgoName)==false){
									DeleteMatrixBuff(TmpData,Info.YLen);
									return false;
								}
								if(::Load(&tBuff,DataArray)==false){
									DeleteMatrixBuff(TmpData,Info.YLen);
									return false;
								}
								if(AlgoName==/**/"HoleWall"){
									Found=true;
									break;
								}
							}
							if(Found==true){
								QBuffer	Buff(&DataArray);
								Buff.open(QIODevice::ReadOnly);

								SetThresholdHoleWallInfo	ThresholdHoleWallInfoData;
								if(ThresholdHoleWallInfoData.Load(&Buff)==true){
									//TmpLib->SpaceToOutline	= 0;
									TmpLib->MakeBlock(GetPage(),TmpData,Info.XByte ,Info.XByte*8,Info.YLen,TmpBlockData
														,ShiftXParamLeft,ShiftXParamRight
														,ShiftYRate*ABase->Thickness);
									for(AlgorithmItemPLI *aq=TmpBlockData.GetFirst();aq!=NULL;aq=aq->GetNext()){
										HoleWallItem	*BItem=dynamic_cast<HoleWallItem *>(aq);
										if(BItem!=NULL){	
											BItem->SetThresholdFromCommon(&ThresholdHoleWallInfoData);
										}
									}
								}
							}
						}
						else{
							TmpLib->MakeBlock(GetPage(),TmpData,Info.XByte ,Info.XByte*8,Info.YLen,TmpBlockData
													,ShiftXParamLeft,ShiftXParamRight
													,ShiftYRate*ABase->Thickness);
						}

						AlgorithmItemPointerListContainer ItemPointers;
						GetAllItems(ItemPointers);
						RemoveItems(ItemPointers);

						AlgorithmItemPLI	*q;
						while((q=TmpBlockData.GetFirst())!=NULL){
							TmpBlockData.RemoveList(q);
							q->SetOriginType(Info.OperationOrigin);
							q->SetOrigin(Info.Origin);
							HoleWallItem *HItem=(HoleWallItem *)q;
							BL->AppendItem(q);
							HItem->RebuildWallShape();
						}
					}
					DeleteMatrixBuff(TmpData,Info.YLen);
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(int layer=0;layer<GetLayerNumb();layer++){
			HoleWallInLayer	*L=(HoleWallInLayer *)GetLayerData(layer);
			L->MoveFromPipe(Info);
		}
		return true;
	}

	return false;
}
//===========================================================================================
HoleWallBase::HoleWallBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	HoleWallNormal		=Qt::darkGreen;
	HoleWallSelected	=Qt::green;
	HoleWallActive		=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;
	Thickness 	=1.6;

	SetParam(&ColorPickup			, /**/"Color" ,/**/"ColorPickup"		,"Color for Image to Pickup-Test ");
	SetParam(&HoleWallNormal		, /**/"Color" ,/**/"HoleWallNormal"		,"Color for Area");
	SetParam(&HoleWallSelected		, /**/"Color" ,/**/"HoleWallSelected"	,"Color for Selected Area");
	SetParam(&HoleWallActive		, /**/"Color" ,/**/"HoleWallActive"		,"Color for Active Area");

	SetParam(&BlockColor0			, /**/"BlockColor" ,/**/"BlockColor0"		,"Area Color 0");
	SetParam(&BlockColor1			, /**/"BlockColor" ,/**/"BlockColor1"		,"Area Color 1");
	SetParam(&BlockColor2			, /**/"BlockColor" ,/**/"BlockColor2"		,"Area Color 2");
	SetParam(&BlockColor3			, /**/"BlockColor" ,/**/"BlockColor3"		,"Area Color 3");
	SetParam(&BlockColor4			, /**/"BlockColor" ,/**/"BlockColor4"		,"Area Color 4");
	SetParam(&BlockColor5			, /**/"BlockColor" ,/**/"BlockColor5"		,"Area Color 5");
	SetParam(&BlockColor6			, /**/"BlockColor" ,/**/"BlockColor6"		,"Area Color 6");
	SetParam(&BlockColor7			, /**/"BlockColor" ,/**/"BlockColor7"		,"Area Color 7");

	SetParam(&OmitZoneDot			, /**/"Setting"		,/**/"OmitZoneDot"		,"Omit zone dot in area generation");
	//SetParam(&ShiftYRate			, /**/"Setting"		,/**/"ShiftYRate"		,"Shift-Y rate per thickness mm");
	SetParam(&Thickness				, /**/"Setting"		,/**/"Thickness"		,"Work thickness (mm)");
	SetParam(&ArrayShiftMulInPage	, /**/"Setting"		,/**/"ArrayShiftMulInPage","X-shift parameter in each page");
	SetParam(&ShiftYRateInPage		, /**/"Setting"		,/**/"ShiftYRateInPage	","Shift-Y rate per thickness mm in each page");
}

AlgorithmDrawAttr	*HoleWallBase::CreateDrawAttr(void)
{
	return new HoleWallDrawAttr();
}

void	HoleWallBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetHoleWallLibraryListPacket	*AListPacket=dynamic_cast<CmdGetHoleWallLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetHoleWallLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetHoleWallLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertHoleWallLibraryPacket	*BInsLib=dynamic_cast<CmdInsertHoleWallLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(HoleWallVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateHoleWallLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateHoleWallLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(HoleWallVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadHoleWallLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadHoleWallLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempHoleWallLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempHoleWallLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearHoleWallLibraryPacket	*CmdClearHoleWallLibraryPacketVar=dynamic_cast<CmdClearHoleWallLibraryPacket *>(packet);
	if(CmdClearHoleWallLibraryPacketVar!=NULL){
		CmdClearHoleWallLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteHoleWallLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteHoleWallLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestHoleWallPacket	*BPickLib=dynamic_cast<CmdPickupTestHoleWallPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		HoleWallInPage	*Bp=dynamic_cast<HoleWallInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->TransmitDirectly(packet);	
		return;
	}
	CmdGenerateHoleWallPacket	*BGenerated=dynamic_cast<CmdGenerateHoleWallPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p==NULL)
			return;
		HoleWallInPage	*Bp=dynamic_cast<HoleWallInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->TransmitDirectly(packet);	
		return;
	}
	CmdCreateTempHoleWallItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempHoleWallItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new HoleWallItem();
		return;
	}
	CmdCreateByteArrayFromHoleWallItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromHoleWallItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadHoleWallItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadHoleWallItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
	CmdModifySelectedHoleWallFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedHoleWallFromByteArray *>(packet);
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
	CmdClearTestHoleWallPacket	*CmdClearTestHoleWallPacketVar=dynamic_cast<CmdClearTestHoleWallPacket *>(packet);
	if(CmdClearTestHoleWallPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestHoleWallPacketVar);
		}
	}
	CmdCreateHoleWallItem	*CmdCreateHoleWallItemVar=dynamic_cast<CmdCreateHoleWallItem *>(packet);
	if(CmdCreateHoleWallItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
	}
}

ExeResult	HoleWallBase::ExecuteInitialAfterEdit(int ExeID 
												,ResultBaseForAlgorithmRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ColorLogicWithTable::ClearTable();
	ExeResult	Ret=AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	QBuffer	Buff(&ArrayShiftMulInPage);
	Buff.open(QIODevice::ReadWrite);
	for(int page=0;page<GetPageNumb();page++){
		HoleWallInPage	*Ap=(HoleWallInPage	*)GetPageData(page);
		if(Buff.read((char *)Ap->ShiftXParamLeft	,sizeof(Ap->ShiftXParamLeft	))!=sizeof(Ap->ShiftXParamLeft))
			break;
		if(Buff.read((char *)Ap->ShiftXParamRight	,sizeof(Ap->ShiftXParamRight))!=sizeof(Ap->ShiftXParamRight))
			break;
	}

	return Ret;
}


bool	HoleWallBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==HoleWallHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==HoleWallHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==HoleWallReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==HoleWallReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==HoleWallReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==HoleWallSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==HoleWallReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*HoleWallBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==HoleWallReqThresholdReqCommand){
		return new HoleWallThresholdReq();
	}
	else if(Command==HoleWallReqThresholdSendCommand){
		HoleWallThresholdSend	*pSend=new HoleWallThresholdSend();
		if(reqData!=NULL){
			HoleWallThresholdReq	*req=(HoleWallThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==HoleWallReqTryThresholdCommand){
		return new HoleWallReqTryThreshold();
	}
	else if(Command==HoleWallSendTryThresholdCommand){
		HoleWallSendTryThreshold	*pSend=new HoleWallSendTryThreshold();
		if(reqData!=NULL){
			HoleWallReqTryThreshold	*req=(HoleWallReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==HoleWallReqChangeShiftCommand){
		return new HoleWallChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	HoleWallBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==HoleWallReqThresholdReqCommand){
		HoleWallThresholdReq	*p=(HoleWallThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==HoleWallReqThresholdSendCommand){
		HoleWallThresholdSend	*p=(HoleWallThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==HoleWallReqTryThresholdCommand){
		HoleWallReqTryThreshold	*p=(HoleWallReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==HoleWallSendTryThresholdCommand){
		HoleWallSendTryThreshold	*p=(HoleWallSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==HoleWallReqChangeShiftCommand){
		HoleWallChangeShift	*p=(HoleWallChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	HoleWallBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==HoleWallReqThresholdReqCommand){
		HoleWallThresholdReq	*p=(HoleWallThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==HoleWallReqThresholdSendCommand){
		HoleWallThresholdSend	*p=(HoleWallThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==HoleWallReqTryThresholdCommand){
		HoleWallReqTryThreshold	*p=(HoleWallReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==HoleWallSendTryThresholdCommand){
		HoleWallSendTryThreshold	*p=(HoleWallSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==HoleWallReqChangeShiftCommand){
		HoleWallChangeShift	*p=(HoleWallChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	HoleWallBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==HoleWallReqThresholdReqCommand){
		HoleWallThresholdReq	*p=(HoleWallThresholdReq *)data;
		return true;
	}
	else if(Command==HoleWallReqThresholdSendCommand){
		HoleWallThresholdSend	*p=(HoleWallThresholdSend *)data;
		return true;
	}
	else if(Command==HoleWallReqTryThresholdCommand){
		HoleWallReqTryThreshold	*p=(HoleWallReqTryThreshold *)data;
		return true;
	}
	else if(Command==HoleWallSendTryThresholdCommand){
		HoleWallSendTryThreshold	*p=(HoleWallSendTryThreshold *)data;
		return true;
	}
	else if(Command==HoleWallReqChangeShiftCommand){
		HoleWallChangeShift	*p=(HoleWallChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}

void	HoleWallBase::ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)
{
	SettingArrayShiftMulInPageDialog	D(GetLayersBase(),data,this);
	if(D.exec()==true){
		data=D.ArrayShiftMulInPage;
	}
}

bool	HoleWallBase::LoadParam(QIODevice *f ,int EnableCondition)
{
	if(AlgorithmBase::LoadParam(f,EnableCondition)==false)
		return false;
	for(int page=0;page<GetPageNumb() && page<ShiftYRateInPage.count();page++){
		HoleWallInPage	*Ap=(HoleWallInPage	*)GetPageData(page);
		bool	ok;
		double	d=ShiftYRateInPage[page].toDouble(&ok);
		if(ok==true){
			Ap->ShiftYRate=d;
		}
	}
	return true;
}