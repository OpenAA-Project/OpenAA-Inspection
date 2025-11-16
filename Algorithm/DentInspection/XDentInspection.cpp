#include "DentInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Dent\XDent.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDentInspection.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XDentLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XDentAlgoPacket.h"
#include "XDisplaySimPanel.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//=====================================================================================
DentThreshold::DentThreshold(DentItem *parent)
:AlgorithmThreshold(parent)
{
	Difference		=100;
	BandWidth		=100;
	MinNGSize		=100;
	MaxNGSize		=3000;
	MaxDiffCoef		=15;
	LinesForAverage	=5;
}


void	DentThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const DentThreshold *s=(const DentThreshold *)&src;
	Difference		=s->Difference;
	BandWidth		=s->BandWidth	;
	MinNGSize		=s->MinNGSize	;
	MaxNGSize		=s->MaxNGSize	;
	MaxDiffCoef		=s->MaxDiffCoef		;
	LinesForAverage	=s->LinesForAverage	;

}
bool	DentThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const DentThreshold *s=(const DentThreshold *)&src;
	if(Difference		!=s->Difference		)	return false;
	if(BandWidth		!=s->BandWidth		)	return false;
	if(MinNGSize		!=s->MinNGSize		)	return false;
	if(MaxNGSize		!=s->MaxNGSize		)	return false;
	if(MaxDiffCoef		!=s->MaxDiffCoef	)	return false;
	if(LinesForAverage	!=s->LinesForAverage)	return false;
	return true;
}
bool	DentThreshold::Save(QIODevice *f)
{
	WORD	Ver=DentVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,Difference)==false)
		return false;
	if(::Save(f,BandWidth)==false)
		return false;
	if(::Save(f,MinNGSize)==false)
		return false;
	if(::Save(f,MaxNGSize)==false)
		return false;
	if(::Save(f,MaxDiffCoef)==false)
		return false;
	if(::Save(f,LinesForAverage)==false)
		return false;

	return true;
}

bool	DentThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,Difference)==false)
		return false;
	if(::Load(f,BandWidth)==false)
		return false;
	if(::Load(f,MinNGSize)==false)
		return false;
	if(::Load(f,MaxNGSize)==false)
		return false;
	if(::Load(f,MaxDiffCoef)==false)
		return false;
	if(::Load(f,LinesForAverage)==false)
		return false;

	return true;
}

void	DentThreshold::FromLibrary(AlgorithmLibrary *src)
{
	DentLibrary	*LSrc=dynamic_cast<DentLibrary *>(src);
	if(LSrc==NULL)
		return;

	Difference		=LSrc->Difference	;
	BandWidth		=LSrc->BandWidth;	
	MinNGSize		=LSrc->MinNGSize;
	MaxNGSize		=LSrc->MaxNGSize;
	MaxDiffCoef		=LSrc->MaxDiffCoef		;
	LinesForAverage	=LSrc->LinesForAverage	;
}
void	DentThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	DentLibrary	*LDst=dynamic_cast<DentLibrary *>(Dest);
	if(LDst==NULL)
		return;

	LDst->Difference		=Difference	;
	LDst->BandWidth			=BandWidth	;
	LDst->MinNGSize			=MinNGSize	;
	LDst->MaxNGSize			=MaxNGSize	;
	LDst->MaxDiffCoef		=MaxDiffCoef		;
	LDst->LinesForAverage	=LinesForAverage	;
}

//===========================================================================================
DentInLayer::DentInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLITemplate<DentItem,DentInPage,DentBase>(parent)
{
	ModeParallel.ModeParallelExecuteInitialAfterEdit=true;
}
DentInLayer::~DentInLayer(void)
{
}
void	DentInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdDentInfoListPacket	*CmdDentInfoListPacketVar=dynamic_cast<CmdDentInfoListPacket *>(packet);
	if(CmdDentInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
			DentInfoList	*a=new DentInfoList();
			a->LibID		=L->GetLibID();
			a->GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			a->Layer		=GetLayer();
			a->ItemID		=L->GetID();
			a->ItemName		=L->GetItemName();
			L->GetXY(a->x1,a->y1,a->x2,a->y2);
			CmdDentInfoListPacketVar->DentInfos->AppendList(a);
		}
		return;
	}

	CmdAddDentItemPacket	*AddBItem=dynamic_cast<CmdAddDentItemPacket *>(packet);
	if(AddBItem!=NULL){
		DentItem	*Item=new DentItem();
		Item->SetArea	 (AddBItem->Area);
		Item->SetItemName(AddBItem->ItemName);
		Item->SetLibID	 (AddBItem->LibID);
		DentBase	*BBase=(DentBase *)GetParentBase();
		AlgorithmLibraryLevelContainer	LLib(BBase);
		if(BBase->GetLibraryContainer()->GetLibrary(AddBItem->LibID,LLib)==true){
			DentLibrary	*ALib=dynamic_cast<DentLibrary *>(LLib.GetLibrary());
			if(ALib!=NULL){
				((DentItem *)Item)->CopyThresholdFromLibrary(&LLib);
			}
		}
		Item->SetManualCreated(true);
		GetParentBase()->ClearManagedCacheLib();
		if(AppendItem(Item)==false){
			delete	Item;
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		DentItem *Item=(DentItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);

			//for(DentItem::DentBand *b=Item->DentBandPack.GetFirst();b!=NULL;b=b->GetNext()){
			//	b->DrawInHistogram(*CmdAlgoSimulateVar->Image,Col.rgba()
			//			,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			//}
			for(DentItem::DentBand *b=Item->DentBandPack.GetFirst();b!=NULL;b=b->GetNext()){
				b->Area.Draw(b->ResultDx,b->ResultDy
								,CmdAlgoSimulateVar->Image,Col.rgba()
								,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}

			char	*p=CmdAlgoSimulateVar->Something.data();
			bool	ModeShowResult=*((bool *)p);
			if(ModeShowResult==true){
				Item->MakeImageMap(*CmdAlgoSimulateVar->Image 
								,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY,CmdAlgoSimulateVar->ZoomRate
								,Item->GetArea().GetMinX(), Item->GetArea().GetMinY());
			}
		}
		return;
	}
	CmdDentReqItemResult	*CmdDentReqItemResultVar=dynamic_cast<CmdDentReqItemResult *>(packet);
	if(CmdDentReqItemResultVar!=NULL){
		DentItem *Item=(DentItem *)SearchIDItem(CmdDentReqItemResultVar->ItemID);
		if(Item!=NULL){
			int	Y=CmdDentReqItemResultVar->GlobalY-Item->GetArea().GetMinY();
			if(0<=Y && Y<Item->ResultMapYLen){
				CmdDentReqItemResultVar->ResultMaxD		=Item->ResultMaxD[Y];
				CmdDentReqItemResultVar->ResultWaveLen	=Item->WaveLenList[Y];
			}
		}
		return;
	}
}

void	DentInLayer::GenerateItems(BYTE **PickedMap ,int XByte,int XLen ,int YLen
									, DentLibrary	*BLib)
{
	UndoElement<DentInLayer>	*UPointer=new UndoElement<DentInLayer>(this,&DentInLayer::UndoGenerateItems);
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

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

	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());

	int	LibID=BLib->GetLibID();
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetLibID()==LibID){
			L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
		}
	}
	int	BSpaceToOutline;
	BSpaceToOutline=BLib->SpaceToOutline;
	GetLayersBase()->FatAreaN(TempMap,TempMap2 ,XByte,GetMaxLines(),BSpaceToOutline);

	MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());

	DeleteMatrixBuff(TempMap	,GetMaxLines());
	DeleteMatrixBuff(TempMap2	,GetMaxLines());

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());

	ConstMapBuffer MaskMap;
	if(BLib->GetAdaptedGenLayers().IsInclude(GetLayer())==true){
		GetReflectionMap(_Reflection_Mask,MaskMap,BLib);
		const BYTE	**MaskBitmap=MaskMap.GetBitMap();
		
		bool	LimitedMaskInOtherPage=((DentInPage *)GetParentInPage())->UseLibraryForMaskingInOtherPage(LibID);
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,BLib,NULL);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){

			MatrixBuffCopy	(CurrentMap					,XByte ,GetMaxLines()
							,(const BYTE **)PickedMap	,XByte ,GetMaxLines());
			MatrixBuffAnd	(CurrentMap ,MaskBitmap ,XByte ,GetMaxLines());
			MatrixBuffNotAnd (CurrentMap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());

			NPListPack<AlgorithmItemPLI>	TmpDentData;
			BLib->MakeDent(
					 CurrentMap,LastOcupyMap
					 ,GetPage()
					,XByte ,GetDotPerLine(),GetMaxLines()
					,TmpDentData);

			AlgorithmItemPLI	*q;
			while((q=TmpDentData.GetFirst())!=NULL){
				TmpDentData.RemoveList(q);
				AppendItem(q);
			}
		}
	}

	DeleteMatrixBuff(CurrentMap				,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
}

void	DentInLayer::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		DentItem	*B=new DentItem();
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
//===========================================================================================
DentInPage::DentInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLITemplate<DentItem,DentInLayer,DentBase>(parent)
{
	PickupBmp		=NULL;
	PickupBmpYLen	=0;
	PickupBmpXByte	=0;
}
DentInPage::~DentInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}
void	DentInPage::CreatePickupBmpBuff(void)
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
void	DentInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdDentInfoListPacket	*CmdDentInfoListPacketVar=dynamic_cast<CmdDentInfoListPacket *>(packet);
	if(CmdDentInfoListPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdAddDentItemPacket	*AddBItem=dynamic_cast<CmdAddDentItemPacket *>(packet);
	if(AddBItem!=NULL){
		IntList AdaptedPickLayers;
		IntList AdaptedGenLayers;
		GetLibraryContainer()->GetLayers(AddBItem->LibID,AdaptedPickLayers ,AdaptedGenLayers);
		for(IntClass *c=AdaptedGenLayers.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdClearTestDentPacket	*CmdClearTestDentPacketVar=dynamic_cast<CmdClearTestDentPacket *>(packet);
	if(CmdClearTestDentPacketVar!=NULL){
		if(PickupBmp!=NULL)
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		return;
	}
	CmdDentGenerate	*CmdDentGenerateVar=dynamic_cast<CmdDentGenerate *>(packet);
	if(CmdDentGenerateVar!=NULL){
		GenerateItems(CmdDentGenerateVar->ItemLibIDs);
		return;
	}
	CmdPickupTestDentPacket	*BPickLib=dynamic_cast<CmdPickupTestDentPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(BPickLib->LibID,SrcLib)==true){
			DentLibrary	*ALib=dynamic_cast<DentLibrary *>(SrcLib.GetLibrary());
			if(ALib!=NULL){
				PickupTest(*ALib);
			}
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdDentReqItemResult	*CmdDentReqItemResultVar=dynamic_cast<CmdDentReqItemResult *>(packet);
	if(CmdDentReqItemResultVar!=NULL){
		GetLayerData(CmdDentReqItemResultVar->Layer)->TransmitDirectly(packet);
		return;
	}
}

bool	DentInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfDent	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfDent	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
void	DentInPage::PickupTest(DentLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibData.GetLibID());
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&LibData,NULL);
		ImageBuffer *ImageList[100];
		GetMasterBuffList(ImageList);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
			LibData.MakePickupTest(ImageList
				,Map.GetBitMap()
				,PickupBmp,NULL
				,GetPage()
				,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
				,((DentBase *)GetParentBase())->OmitZoneDot);
		}
	}
}

void	DentInPage::GenerateItems(IntList &ItemLibIDs)
{
	CreatePickupBmpBuff();

	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	for(IntClass *c=ItemLibIDs.GetFirst();c!=NULL;c=c->GetNext()){		
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(GetParentBase()->GetLibraryContainer()->GetLibrary(c->GetValue(),SrcLib)==true){
			DentLibrary	*ALib=dynamic_cast<DentLibrary *>(SrcLib.GetLibrary());
			if(ALib!=NULL){
				PickupTest(*ALib);
				for(IntClass *v=SrcLib.GetAdaptedGenLayers().GetFirst();v!=NULL;v=v->GetNext()){
					int	Layer=v->GetValue();
					((DentInLayer *)GetLayerData(Layer))->GenerateItems(PickupBmp ,PickupBmpXByte,GetDotPerLine(),PickupBmpYLen
																, ALib);
				}
			}
		}
	}
}
void	DentInPage::GenerateDents(DentLibrary *LibDim[],int LibDimNumb)
{
	IntList	ItemLibIDs;
	for(int i=0;i<LibDimNumb;i++){
		ItemLibIDs.Add(LibDim[i]->GetLibID());
	}
	GenerateItems(ItemLibIDs);
}

void	DentInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DentDrawAttr	*BAttr=dynamic_cast<DentDrawAttr *>(Attr);
			
	if(PickupBmp!=NULL){
		DentBase	*BBase=dynamic_cast<DentBase *>(GetParentBase());
		DrawBitImageOr(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
			,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
				,0,0
				,BBase->ColorPickup);
	}
	if(BAttr!=NULL){
		AlgorithmInPagePLI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
	}
	else{
		AlgorithmInPagePLI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
	}
}

void	DentInPage::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,int32 ItemID 
											,AlgorithmItemRoot *Data,IntList &EdittedMemberID
											,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_All){
		for(int L=0;L<GetLayerNumb();L++){
			GetLayerData(L)->SetIndependentItemData(Command,LocalPage,L,ItemID,Data,EdittedMemberID,Something,AckData);
		}
	}
	else{
		AlgorithmInPagePLITemplate<DentItem,DentInLayer,DentBase>::SetIndependentItemData(Command,LocalPage,Layer,ItemID,Data,EdittedMemberID,Something,AckData);
	}
}

void	DentInPage::UndoSetIndependentItemNameDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		DentItem	*BI=(DentItem *)Item;
		QString	ItemName;
		if(::Load(f,ItemName)==false)
			return;
		BI->SetItemName(ItemName);
	}
}

//===========================================================================================
DentBase::DentBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorDentNormal		=Qt::darkGreen;
	ColorDentSelected	=Qt::green;
	ColorDentActive		=Qt::red;
	ColorPickup			=Qt::green;
	DentColor0	=Qt::green;
	DentColor1	=Qt::yellow;
	DentColor2	=Qt::darkRed;
	DentColor3	=Qt::cyan;
	DentColor4	=Qt::magenta;
	DentColor5	=Qt::darkGreen;
	DentColor6	=Qt::darkYellow;
	DentColor7	=Qt::darkCyan;
	OmitZoneDot	=100;
	BaseWaveLength	=50;

	for(int w=0;w<WaveCount;w++){
		for(int shift=0;shift<WaveCount*2;shift++){
			WaveTableResult[w][shift]=NULL;
		}
	}
	SetParam(&ColorDentNormal	, /**/"Color" ,/**/"ColorDentNormal"		,LangSolver.GetString(XDentInspection_LS,LID_3)/*"Color for Area"*/);
	SetParam(&ColorDentSelected	, /**/"Color" ,/**/"ColorDentSelected"		,LangSolver.GetString(XDentInspection_LS,LID_4)/*"Color for Selected Area"*/);
	SetParam(&ColorDentActive	, /**/"Color" ,/**/"ColorDentActive"		,LangSolver.GetString(XDentInspection_LS,LID_5)/*"Color for Active Area"*/);
	SetParam(&ColorPickup		, /**/"Color" ,/**/"ColorPickup	"			,LangSolver.GetString(XDentInspection_LS,LID_6)/*"Color for picking up"*/);

	SetParam(&DentColor0		, /**/"Color"	,/**/"DentColor0"		,LangSolver.GetString(XDentInspection_LS,LID_7)/*"Area Color 0"*/);
	SetParam(&DentColor1		, /**/"Color"	,/**/"DentColor1"		,LangSolver.GetString(XDentInspection_LS,LID_8)/*"Area Color 1"*/);
	SetParam(&DentColor2		, /**/"Color"	,/**/"DentColor2"		,LangSolver.GetString(XDentInspection_LS,LID_9)/*"Area Color 2"*/);
	SetParam(&DentColor3		, /**/"Color"	,/**/"DentColor3"		,LangSolver.GetString(XDentInspection_LS,LID_10)/*"Area Color 3"*/);
	SetParam(&DentColor4		, /**/"Color"	,/**/"DentColor4"		,LangSolver.GetString(XDentInspection_LS,LID_11)/*"Area Color 4"*/);
	SetParam(&DentColor5		, /**/"Color"	,/**/"DentColor5"		,LangSolver.GetString(XDentInspection_LS,LID_12)/*"Area Color 5"*/);
	SetParam(&DentColor6		, /**/"Color"	,/**/"DentColor6"		,LangSolver.GetString(XDentInspection_LS,LID_13)/*"Area Color 6"*/);
	SetParam(&DentColor7		, /**/"Color"	,/**/"DentColor7"		,LangSolver.GetString(XDentInspection_LS,LID_14)/*"Area Color 7"*/);

	SetParam(&OmitZoneDot		, /**/"Setting"		,/**/"OmitZoneDot"		,LangSolver.GetString(XDentInspection_LS,LID_15)/*"Omit zone dot in area generation"*/);
	SetParam(&BaseWaveLength	, /**/"Setting"		,/**/"BaseWaveLength"	,LangSolver.GetString(XDentInspection_LS,LID_16)/*"Wave cycle length(Pixels)"*/);
}

DentBase::~DentBase(void)
{
	for(int w=0;w<WaveCount;w++){
		for(int shift=0;shift<WaveCount*2;shift++){
			if(WaveTableResult[w][shift]!=NULL){
				delete	[]WaveTableResult[w][shift];
				WaveTableResult[w][shift]=NULL;
			}
		}
	}
}
AlgorithmDrawAttr	*DentBase::CreateDrawAttr(void)
{
	return new DentDrawAttr();
}

void	DentBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetDentLibraryListPacket	*AListPacket=dynamic_cast<CmdGetDentLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetDentLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetDentLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertDentLibraryPacket	*BInsLib=dynamic_cast<CmdInsertDentLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(DentVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateDentLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateDentLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(DentVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadDentLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadDentLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempDentLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempDentLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearDentLibraryPacket	*CmdClearDentLibraryPacketVar=dynamic_cast<CmdClearDentLibraryPacket *>(packet);
	if(CmdClearDentLibraryPacketVar!=NULL){
		CmdClearDentLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteDentLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteDentLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdCreateTempDentItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempDentItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new DentItem();
		return;
	}
	CmdCreateByteArrayFromDentItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromDentItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadDentItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadDentItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
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
	CmdGenerateDentPacket	*BGenerated=dynamic_cast<CmdGenerateDentPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}

		DentLibrary	**DDim=new DentLibrary*[N];
		for(int i=0;i<N;i++){
			DDim[i]=dynamic_cast<DentLibrary *>(LibDim[N]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			DentInPage	*Bp=dynamic_cast<DentInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateDents(DDim,N);		
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
}

bool	DentBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==DentHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==DentHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==DentReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==DentReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==DentReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==DentSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==DentReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*DentBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==DentReqThresholdReqCommand){
		return new DentThresholdReq();
	}
	else if(Command==DentReqThresholdSendCommand){
		DentThresholdSend	*pSend=new DentThresholdSend();
		if(reqData!=NULL){
			DentThresholdReq	*req=(DentThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==DentReqTryThresholdCommand){
		return new DentReqTryThreshold();
	}
	else if(Command==DentSendTryThresholdCommand){
		DentSendTryThreshold	*pSend=new DentSendTryThreshold();
		if(reqData!=NULL){
			DentReqTryThreshold	*req=(DentReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	DentBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==DentReqThresholdReqCommand){
		DentThresholdReq	*p=(DentThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==DentReqThresholdSendCommand){
		DentThresholdSend	*p=(DentThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==DentReqTryThresholdCommand){
		DentReqTryThreshold	*p=(DentReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==DentSendTryThresholdCommand){
		DentSendTryThreshold	*p=(DentSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	DentBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==DentReqThresholdReqCommand){
		DentThresholdReq	*p=(DentThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==DentReqThresholdSendCommand){
		DentThresholdSend	*p=(DentThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==DentReqTryThresholdCommand){
		DentReqTryThreshold	*p=(DentReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==DentSendTryThresholdCommand){
		DentSendTryThreshold	*p=(DentSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	DentBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==DentReqThresholdReqCommand){
		DentThresholdReq	*p=(DentThresholdReq *)data;
		return true;
	}
	else if(Command==DentReqThresholdSendCommand){
		DentThresholdSend	*p=(DentThresholdSend *)data;
		return true;
	}
	else if(Command==DentReqTryThresholdCommand){
		DentReqTryThreshold	*p=(DentReqTryThreshold *)data;
		return true;
	}
	else if(Command==DentSendTryThresholdCommand){
		DentSendTryThreshold	*p=(DentSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}

ExeResult	DentBase::ExecuteInitialAfterEdit(int ExeID 
											,ResultBaseForAlgorithmRoot *Res
											,ExecuteInitialAfterEditInfo &EInfo)
{
	for(int w=0;w<WaveCount;w++){
		double	WaveLen=BaseWaveLength+(w-WaveCount/2);
		for(int i=0;i<WaveTableLen;i++){
			WaveTable[w][i]=sin(i*2*M_PI/WaveLen);
		}
	}
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	QString	DentWaveTableFileName=/**/"DentWaveTable.dat";
	bool	Flag=false;
	{
		QFile	File(DentWaveTableFileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(LoadWavetableResultHeader(&File)==true){
				if(LoadWavetableResult(&File)==true){
					Flag=true;
				}
			}
		}
	}
	if(Flag==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int w=0;w<WaveCount;w++){
				for(int shift=0;shift<WaveCount*2;shift++){
					if(WaveTableResult[w][shift]!=NULL){
						delete	[]WaveTableResult[w][shift];
					}
					WaveTableResult[w][shift]=new struct CalcCoefTableList[WaveTableLen];
					for(int L=1;L<WaveTableLen-shift;L++){
						WaveTableResult[w][shift][L].Count	=0;
						double	A=0;
						double	AA=0;
						double	SkipA=0;
						double	SkipAA=0;
						for(int i=0;i<L;i++){
							double	d=WaveTable[w][i+shift];
							A	+=d;
							AA	+=d*d;
						}
						int	Numb=L;
						for(int i=0;i<L;i+=4){
							double	d=WaveTable[w][shift+i];
							SkipA	+=d;
							SkipAA	+=d*d;
						}
						int	SkipNumb=(L+3)>>2;
						double	AvrS	=A	  /Numb;
						double	SkipAvrS=SkipA/SkipNumb;
						WaveTableResult[w][shift][L].AvrS		=AvrS;
						WaveTableResult[w][shift][L].Da			=AA-Numb*AvrS*AvrS;
						WaveTableResult[w][shift][L].SkipAvrS	=SkipAvrS;
						WaveTableResult[w][shift][L].SkipDa		=SkipAA-SkipNumb*SkipAvrS*SkipAvrS;
						WaveTableResult[w][shift][L].Count		=Numb;
					}
				}
			}
		}
		QFile	File(DentWaveTableFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(SaveWavetableResultHeader(&File)==true){
				SaveWavetableResult(&File);
			}
		}
	}
	return AlgorithmBase::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
}
bool	DentBase::SaveWavetableResultHeader(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)				return false;
	if(::Save(f,(int)WaveCount)==false)		return false;
	if(::Save(f,(int)WaveTableLen)==false)	return false;
	return true;
}

bool	DentBase::LoadWavetableResultHeader(QIODevice *f)
{
	int32	Ver=1;

	int	iWaveCount;
	int	iWaveTableLen;
	if(::Load(f,Ver)==false)			return false;
	if(::Load(f,iWaveCount)==false)		return false;
	if(::Load(f,iWaveTableLen)==false)	return false;
	if(iWaveCount	!=WaveCount)	return false;
	if(iWaveTableLen!=WaveTableLen)	return false;
	return true;

}
bool	DentBase::SaveWavetableResult(QIODevice *f)
{
	for(int w=0;w<WaveCount;w++){
		for(int shift=0;shift<WaveCount*2;shift++){
			for(int L=1;L<WaveTableLen-shift;L++){
				if(WaveTableResult[w][shift][L].Save(f)==false)
					return false;
			}
		}
	}
	return true;
}

bool	DentBase::LoadWavetableResult(QIODevice *f)
{
	for(int w=0;w<WaveCount;w++){
		for(int shift=0;shift<WaveCount*2;shift++){
			if(WaveTableResult[w][shift]!=NULL){
				delete	[]WaveTableResult[w][shift];
			}
			WaveTableResult[w][shift]=new struct CalcCoefTableList[WaveTableLen];
			for(int L=1;L<WaveTableLen-shift;L++){
				if(WaveTableResult[w][shift][L].Load(f)==false)
					return false;
			}
		}
	}
	return true;

}
QString	DentBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XDentInspection_LS,LID_17)/*"打痕検査"*/;
}

bool	CalcCoefTableList::Save(QIODevice *f)
{
	if(::Save(f,AvrS	)==false)	return false;
	if(::Save(f,Da		)==false)	return false;
	if(::Save(f,SkipAvrS)==false)	return false;
	if(::Save(f,SkipDa	)==false)	return false;
	if(::Save(f,Count	)==false)	return false;
	return true;
}
bool	CalcCoefTableList::Load(QIODevice *f)
{
	if(::Load(f,AvrS	)==false)	return false;
	if(::Load(f,Da		)==false)	return false;
	if(::Load(f,SkipAvrS)==false)	return false;
	if(::Load(f,SkipDa	)==false)	return false;
	if(::Load(f,Count	)==false)	return false;
	return true;
}



