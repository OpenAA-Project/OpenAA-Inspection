/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaShader\XAreaShader.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaShader.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaShaderPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "XDisplayBitImage.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>

//====================================================================================

AreaShaderThreshold::AreaShaderThreshold(AreaShaderItem *parent)
:AlgorithmThreshold(parent)
{
	CellSize=0;
	AdoptRate=0;
	Fixed	=false;
	Average	=0;
	Sigma	=0;
	PreProcessingMode=true;
}

void	AreaShaderThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AreaShaderThreshold	*s=dynamic_cast<const AreaShaderThreshold *>(&src);
	CellSize			=s->CellSize;
	AdoptRate			=s->AdoptRate;	//採用率
	Fixed				=s->Fixed;
	Average				=s->Average;
	Sigma				=s->Sigma;		//標準偏差
	PreProcessingMode	=s->PreProcessingMode;
}
bool	AreaShaderThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AreaShaderThreshold	*s=dynamic_cast<const AreaShaderThreshold *>(&src);
	if(CellSize			!=s->CellSize			)	return false;
	if(AdoptRate		!=s->AdoptRate			)	return false;
	if(Fixed			!=s->Fixed				)	return false;
	if(Average			!=s->Average			)	return false;
	if(Sigma			!=s->Sigma				)	return false;
	if(PreProcessingMode!=s->PreProcessingMode	)	return false;
	return true;
}

bool	AreaShaderThreshold::Save(QIODevice *file)
{
	WORD	Ver=3;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,CellSize)==false)
		return false;
	if(::Save(file,AdoptRate)==false)
		return false;
	if(::Save(file,Fixed)==false)
		return false;
	if(::Save(file,Average)==false)
		return false;
	if(::Save(file,Sigma)==false)
		return false;
	if(::Save(file,PreProcessingMode)==false)
		return false;
	return(true);
}
bool	AreaShaderThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,CellSize)==false)
		return false;
	if(::Load(file,AdoptRate)==false)
		return false;
	if(Ver>=2){
		if(::Load(file,Fixed)==false)
			return false;
		if(::Load(file,Average)==false)
			return false;
		if(::Load(file,Sigma)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(file,PreProcessingMode)==false)
			return false;
	}
	return(true);
}

void	AreaShaderThreshold::FromLibrary(AlgorithmLibrary *src)
{
	AreaShaderLibrary	*s=dynamic_cast<AreaShaderLibrary *>(src);
	CellSize			=s->CellSize;
	AdoptRate			=s->AdoptRate;	//採用率
	Fixed				=s->Fixed;
	Average				=s->Average;
	Sigma				=s->Sigma;		//標準偏差
	PreProcessingMode	=s->PreProcessingMode;
}

void	AreaShaderThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	AreaShaderLibrary	*d=dynamic_cast<AreaShaderLibrary *>(Dest);
	d->CellSize				=CellSize;
	d->AdoptRate			=AdoptRate;	//採用率
	d->Fixed				=Fixed;
	d->Average				=Average;
	d->Sigma				=Sigma;		//標準偏差
	d->PreProcessingMode	=PreProcessingMode;
}

//========================================================

AreaShaderItem::AreaShaderItem(void)
{
	Avr=0.0;
	Var=0.0;
	AVector=NULL;
	SDim=NULL;
	WCount=0;
	HCount=0;
	LCellSize=0;
	LCalcSize=0;
}
AreaShaderItem::~AreaShaderItem(void)
{
	if(SDim!=NULL){
		delete	[]SDim;
		SDim=NULL;
	}
}
AlgorithmItemPLI	&AreaShaderItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    AreaShaderItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaShaderItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}

void	AreaShaderItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			GetThresholdW()->CopyFrom(*((AreaShaderThreshold *)((AreaShaderItem *)Data)->GetThresholdR(GetLayersBase())));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==Data->GetLibID()){
			GetThresholdW()->CopyFrom(*((AreaShaderThreshold *)((AreaShaderItem *)Data)->GetThresholdR(GetLayersBase())));
		}
	}
}

ExeResult	AreaShaderItem::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	bool	Ret=true;
	if(GetThresholdR()->PreProcessingMode==true){
		Ret=PPProcessing	(ExeID ,ThreadNo,Res);
	}
	if(Ret==true){
		return _ER_true;
	}
	return _ER_ReqRetryLater;
}
ExeResult	AreaShaderItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	bool	Ret=true;
	if(GetThresholdR()->PreProcessingMode==false){
		Ret=PPProcessing	(ExeID ,ThreadNo,Res);
	}
	if(Ret==true){
		return _ER_true;
	}
	return _ER_ReqRetryLater;
}

//===========================================
AreaShaderInLayer::AreaShaderInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
	XByte				=0;
	YLen				=0;
	PickupBmp=NULL;
	PickupBmpXByte	=0;
	PickupBmpYLen	=0;
}

AreaShaderInLayer::~AreaShaderInLayer(void)
{
	DynamicMaskMap	=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;

	XByte			=0;
	YLen			=0;
	if(PickupBmp!=NULL){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	}
	PickupBmp=NULL;
	PickupBmpYLen=0;
}

AlgorithmItemRoot		*AreaShaderInLayer::CreateItem(AreaShaderLibrary &Lib)
{
	AlgorithmItemPLI	*Item=(AlgorithmItemPLI *)CreateItem(0);
	Item->SetParent(this);
	return Item;	
}

void	AreaShaderInLayer::PickupTest(AreaShaderLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBuffer MaskMap;
	GetReflectionMap(_Reflection_Mask,MaskMap,&LibData);

	ImageBuffer	&MasterImage=GetMasterBuff();
	LibData.MakePickupTest(&MasterImage
		,MaskMap.GetBitMap()
		,PickupBmp,NULL
		,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
		,((AreaShaderBase *)GetParentBase())->OmitZoneDot);
}


void	AreaShaderInLayer::CreateItems(IntList &LayerList ,AlgorithmLibraryListContainer &LibList)
{
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[LibList.GetNumber()];
	int	N=0;
	int	LibType=Container->GetLibType();
	for(AlgorithmLibraryList *L=LibList.GetFirst();L!=NULL;L=L->GetNext()){
		LibDim[N]=new AlgorithmLibraryLevelContainer(Container);
		if(GetLibraryContainer()->GetLibrary(L->GetLibID(),*LibDim[N])==true){
			if(LibDim[N]->HasGenLayer(GetLayer())==true
			|| ((LibDim[N]->GetAdaptedGenLayers().IsEmpty()==true) && LayerList.IsInclude(GetLayer())==true)){
				N++;
			}
			else{
				delete	LibDim[N];
			}
		}
		else{
			delete	LibDim[N];
		}
	}

	for(;;){
		bool	Changed=false;
		for(int i=0;i<N-1;i++){
			AreaShaderLibrary	*L1=dynamic_cast<AreaShaderLibrary *>(LibDim[i  ]->GetLibrary());
			AreaShaderLibrary	*L2=dynamic_cast<AreaShaderLibrary *>(LibDim[i+1]->GetLibrary());
			if(L1->Priority>L2->Priority){
				AlgorithmLibraryLevelContainer	Tmp(Container);
				Tmp=*LibDim[i];
				*LibDim[i]=*LibDim[i+1];
				*LibDim[i+1]=Tmp;
				Changed=true;
			}
		}
		if(Changed==false)
			break;
	}

	AreaShaderLibrary	**DDim=new AreaShaderLibrary*[N];
	for(int i=0;i<N;i++){
		DDim[i]=dynamic_cast<AreaShaderLibrary *>(LibDim[i]->GetLibrary());
	}
	GenerateBlocks(DDim,N);		

	delete	[]DDim;
	for(int i=0;i<N;i++){
		delete	LibDim[i];
	}
	delete	[]LibDim;
}

void	AreaShaderInLayer::GenerateBlocks(AreaShaderLibrary *LibDim[],int LibDimNumb)
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

	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	AlgorithmLibraryStocker	LibStocker;
	for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->GetArea().MakeBitData(LastOcupyMap,GetDotPerLine() ,GetMaxLines());
	}

	BYTE **OcupyMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());

	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBuffer MaskMap;
		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			AlgorithmInPagePLI	*LPg=(AlgorithmInPagePLI*)GetParentInPage();
			AlgorithmInLayerPLI	*LL=(AlgorithmInLayerPLI *)LPg->GetLayerData(LibDim[i]->GetAdaptedPickLayers().GetFirst()->GetValue());
			LL->GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		else{
			GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}

		const BYTE	**MaskBitmap=MaskMap.GetBitMap();
		
		if(LibDim[i]->GenerateOverlap==false){
			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());
		}
		ImageBuffer	*MasterImage=&GetMasterBuff();
		if(LibDim[i]->GetAdaptedPickLayers().IsEmpty()==false){
			for(int LLayer=0;LLayer<GetLayerNumb();LLayer++){
				if(LibDim[i]->HasPickLayer(LLayer)==true){
					ImagePointerContainer ImagesPointers;
					GetParentInPage()->GetMasterImages(ImagesPointers);
					MasterImage=ImagesPointers[LLayer];
					break;
				}
			}
		}

		LibDim[i]->MakePickupTest(MasterImage
			,MaskBitmap
			,CurrentMap,OcupyMap
			,XByte ,GetDotPerLine(),GetMaxLines()
			,((AreaShaderBase *)GetParentBase())->OmitZoneDot);
			
		NPListPack<AlgorithmItemPLI>	TmpBlockData;
		LibDim[i]->MakeBlock(
				 CurrentMap,LastOcupyMap
				,XByte ,GetDotPerLine(),GetMaxLines()
				,TmpBlockData);
		AlgorithmItemPLI	*q;
		while((q=TmpBlockData.GetFirst())!=NULL){
			TmpBlockData.RemoveList(q);
			AppendItem(q);
		}
		MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
	}

	DeleteMatrixBuff(CurrentMap		,GetMaxLines());
	DeleteMatrixBuff(OcupyMap		,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap	,GetMaxLines());
}
void	AreaShaderInLayer::CreatePickupBmpBuff(void)
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
void	AreaShaderInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	
{
	AreaShaderDrawAttr	*BAttr=dynamic_cast<AreaShaderDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Generated==true && PickupBmp!=NULL){
			AreaShaderBase	*BBase=dynamic_cast<AreaShaderBase *>(GetParentBase());
			DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
						,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
							,0,0
							,BBase->ColorPickup);
		}
		else{
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	AreaShaderInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaShaderItemPacket	*CmdAddAreaShaderItemPacketVar=dynamic_cast<CmdAddAreaShaderItemPacket *>(packet);
	if(CmdAddAreaShaderItemPacketVar!=NULL){
		AlgorithmLibraryLevelContainer	Lib(GetLibraryContainer());
		Lib.SetLibID(-1);
		//GetLibraryContainer()->Load(Lib);
		AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(Lib.GetLibrary());
		AlgorithmItemRoot	*Item=CreateItem(*ALib);
		Item->SetArea(CmdAddAreaShaderItemPacketVar->Area);
		Item->SetLibID(Lib.GetLibID());
		((AreaShaderItem *)Item)->GetThresholdW()->CellSize	=CmdAddAreaShaderItemPacketVar->CellSize;
		((AreaShaderItem *)Item)->GetThresholdW()->AdoptRate=CmdAddAreaShaderItemPacketVar->AdoptRate;
		((AreaShaderItem *)Item)->GetThresholdW()->Fixed	=CmdAddAreaShaderItemPacketVar->Fixed;
		((AreaShaderItem *)Item)->GetThresholdW()->Average	=CmdAddAreaShaderItemPacketVar->Average;
		((AreaShaderItem *)Item)->GetThresholdW()->Sigma	=CmdAddAreaShaderItemPacketVar->Sigma;
		AppendItem(Item);
		return;
	}
	CmdPickupTestAreaShaderPacket	*BPickLib=dynamic_cast<CmdPickupTestAreaShaderPacket *>(packet);
	if(BPickLib!=NULL){
		PickupTest(*(AreaShaderLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdClearTestAreaShaderPacket	*CmdClearTestAreaShaderPacketVar=dynamic_cast<CmdClearTestAreaShaderPacket *>(packet);
	if(CmdClearTestAreaShaderPacketVar!=NULL){
		if(PickupBmp!=NULL)
			DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
		return;
	}
	CmdCreateAreaShaderPacket	*CmdCreateAreaShaderPacketVar=dynamic_cast<CmdCreateAreaShaderPacket *>(packet);
	if(CmdCreateAreaShaderPacketVar!=NULL){
		CreateItems( CmdCreateAreaShaderPacketVar->LayerList
					,CmdCreateAreaShaderPacketVar->SelectedLibList);
		return;
	}
}

struct	ExecuteItemDim
{
	int	LibID;
	int	Priority;
};

static	int	ExecuteItemDimSortFunc(const void *a, const void *b)
{
	struct	ExecuteItemDim	*aa=(struct	ExecuteItemDim *)a;
	struct	ExecuteItemDim	*bb=(struct	ExecuteItemDim *)b;
	if(aa->Priority>bb->Priority)
		return 1;
	if(aa->Priority<bb->Priority)
		return -1;
	return 0;
}

ExeResult	AreaShaderInLayer::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInLayerRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	YLen	=GetMaxLines();
	XByte	=(GetDotPerLine()+7)/8;
	AlgorithmInLayerPLI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	struct	ExecuteItemDim	*D=new struct	ExecuteItemDim[GetItemCount()];
	int	LibN=0;
	for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		bool	Found=false;
		for(int i=0;i<LibN;i++){
			if(D[i].LibID==L->GetLibID()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			D[LibN].LibID	=L->GetLibID();
			LibN++;
		}
	}
	AlgorithmLibraryContainer	*LibContainer=GetLibraryContainer();
	for(int i=0;i<LibN;i++){
		AlgorithmLibraryLevelContainer	SrcLib(LibContainer);
		if(LibContainer->GetLibrary(D[i].LibID,SrcLib)==true){
			AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(SrcLib.GetLibrary());
			D[i].Priority=ALib->Priority;
		}
	}
	QSort(D,LibN,sizeof(struct	ExecuteItemDim),ExecuteItemDimSortFunc);
	ExecutingList.RemoveAll();
	for(int i=0;i<LibN;i++){
		ItemByLibContainerList	*p=new ItemByLibContainerList(D[i].LibID,this);
		int	Index=0;
		for(AlgorithmItemPLI *L=GetFirstData();L!=NULL;L=L->GetNext(),Index++){
			if(D[i].LibID==L->GetLibID()){
				p->Add(Index,L);
			}
		}
		ExecutingList.AppendList(p);
	}
	delete	[]D;
		
	return _ER_true;
}

ExeResult	AreaShaderInLayer::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	return AlgorithmInLayerPLI::ExecuteStartByInspection(ExeID ,Res);
}

void	AreaShaderInLayer::ItemPointerListContainer::Add(int index ,AlgorithmItemRoot *item)
{
	AppendList(new ItemPointerList(index,item));
}

ExeResult	AreaShaderInLayer::ExecutePreProcessing		(int ExeID ,ResultInLayerRoot *R)
{
	if(PPProcessing(ExeID,R)==true){
		return _ER_true;
	}
	return _ER_ReqRetryLater;
}

ExeResult	AreaShaderInLayer::ExecutePostProcessing	(int ExeID ,ResultInLayerRoot *R)
{
	if(PPProcessing(ExeID,R)==true){
		return _ER_true;
	}
	return _ER_ReqRetryLater;
}

bool	AreaShaderInLayer::PPProcessing(int ExeID ,ResultInLayerRoot *R)
{
	DynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	DynamicMaskMapXByte	=GetDataInPage()->GetDynamicMaskMapXByte();
	DynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	ResultInLayerPLI *Res=(ResultInLayerPLI *)R;
	if(Res->GetItemCount()<GetItemCount()){
		Res->Alloc(this);
	}
	int	Ret=0;
	for(ItemByLibContainerList *a=ExecutingList.GetFirst();a!=NULL;a=a->GetNext()){
		ItemPointerList *k;
		#pragma omp parallel
		#pragma omp single private(k)
		for(k=a->ItemPointerListContainer::GetFirst();k!=NULL;k=k->GetNext()){
			#pragma omp task
			{
				if(k->Pointer->ExecutePreProcessing(ExeID,0,Res->GetResultItem(k->Index))!=_ER_true){
					#pragma omp atomic
					Ret++;
				}
			}
		}
	}

	if(Ret==0){
		return true;
	}
	return false;
}


//===========================================

void	AreaShaderInPage::GenerateBlocks(IntList &LayerList, AreaShaderLibrary *LibDim[],int LibDimNumb)
{
	/*
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			BlockInLayer	*BI=dynamic_cast<BlockInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateBlocks(LibDim,LibDimNumb);
			}
		}
	}
	*/
}
void	AreaShaderInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaShaderItemPacket	*CmdAddAreaShaderItemPacketVar=dynamic_cast<CmdAddAreaShaderItemPacket *>(packet);
	if(CmdAddAreaShaderItemPacketVar!=NULL){
		for(IntClass *L=CmdAddAreaShaderItemPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			GetLayerData(L->GetValue())->TransmitDirectly(CmdAddAreaShaderItemPacketVar);
		}
		return;
	}
	CmdPickupTestAreaShaderPacket	*BPickLib=dynamic_cast<CmdPickupTestAreaShaderPacket *>(packet);
	if(BPickLib!=NULL){
		for(IntClass *L=BPickLib->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdClearTestAreaShaderPacket	*CmdClearTestAreaShaderPacketVar=dynamic_cast<CmdClearTestAreaShaderPacket *>(packet);
	if(CmdClearTestAreaShaderPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(layer);
			AL->TransmitDirectly(packet);
		}
		return;
	}
	CmdCreateAreaShaderPacket	*CmdCreateAreaShaderPacketVar=dynamic_cast<CmdCreateAreaShaderPacket *>(packet);
	if(CmdCreateAreaShaderPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			AL->TransmitDirectly(packet);
		}
		/*
		for(IntClass *L=CmdCreateAreaShaderPacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
				AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
				AL->TransmitDirectly(packet);
			}
		}
		*/
		return;
	}

}

//===========================================
AreaShaderBase::AreaShaderBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup				=Qt::yellow;
	AreaColor				=Qt::green;
	NegAreaColorSelected	=Qt::yellow;
	NegAreaColor			=Qt::red;
	TransparentLevel		=80;
	OmitZoneDot				=100;

	SetParam(&ColorPickup			, /**/"Color"	,/**/"ColorPickup"				,"Color for Image to Pickup-Test ");
	SetParam(&AreaColor				, /**/"Color"	,/**/"AreaColor"				,"filtered Area Color");
	SetParam(&NegAreaColorSelected	, /**/"Color"	,/**/"NegAreaColorSelected"		,"Color for Selected filtered area");
	SetParam(&NegAreaColor			, /**/"Color"	,/**/"NegAreaColor"				,"Color for Active filtered area");
	SetParam(&TransparentLevel		, /**/"Color"	,/**/"TransparentLevel"			,"Color for Transparent display level");
	SetParam(&OmitZoneDot			, /**/"Setting"	,/**/"OmitZoneDot"				,"Omit zone dot in block generation");
}


AlgorithmDrawAttr	*AreaShaderBase::CreateDrawAttr(void)
{
	return new AreaShaderDrawAttr();
}

bool	AreaShaderBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

void	AreaShaderBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetAreaShaderLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAreaShaderLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetAreaShaderLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAreaShaderLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertAreaShaderLibraryPacket	*BInsLib=dynamic_cast<CmdInsertAreaShaderLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(AreaShaderVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateAreaShaderLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateAreaShaderLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(AreaShaderVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadAreaShaderLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadAreaShaderLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempAreaShaderLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempAreaShaderLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdDeleteAreaShaderLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteAreaShaderLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	/*
	CmdCreateByteArrayFromAreaShaderItemPacket	*BAFromAreaShaderItem=dynamic_cast<CmdCreateByteArrayFromAreaShaderItemPacket *>(packet);
	if(BAFromAreaShaderItem!=NULL){
		QBuffer	Buff(&BAFromAreaShaderItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromAreaShaderItem->Point->Save(&Buff);
	}
	*/
	CmdAddAreaShaderItemPacket	*CmdAddAreaShaderItemPacketVar=dynamic_cast<CmdAddAreaShaderItemPacket *>(packet);
	if(CmdAddAreaShaderItemPacketVar!=NULL){
		GetPageData(CmdAddAreaShaderItemPacketVar->LocalPage)->TransmitDirectly(CmdAddAreaShaderItemPacketVar);
	}
	CmdClearAreaShaderLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearAreaShaderLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
}

bool	AreaShaderBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==AreaShaderReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==AreaShaderReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*AreaShaderBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==AreaShaderReqThresholdReqCommand){
		return new AreaShaderThresholdReq();
	}
	else if(Command==AreaShaderReqThresholdSendCommand){
		AreaShaderThresholdSend	*pSend=new AreaShaderThresholdSend();
		if(reqData!=NULL){
			AreaShaderThresholdReq	*req=(AreaShaderThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	AreaShaderBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==AreaShaderReqThresholdReqCommand){
		AreaShaderThresholdReq	*p=(AreaShaderThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==AreaShaderReqThresholdSendCommand){
		AreaShaderThresholdSend	*p=(AreaShaderThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	AreaShaderBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==AreaShaderReqThresholdReqCommand){
		AreaShaderThresholdReq	*p=(AreaShaderThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==AreaShaderReqThresholdSendCommand){
		AreaShaderThresholdSend	*p=(AreaShaderThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	AreaShaderBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==AreaShaderReqThresholdReqCommand){
		AreaShaderThresholdReq	*p=(AreaShaderThresholdReq *)data;
		return true;
	}
	else if(Command==AreaShaderReqThresholdSendCommand){
		AreaShaderThresholdSend	*p=(AreaShaderThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

//=======================================================================================
AreaShaderThresholdReq::AreaShaderThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Layer	=-1;
	Dx=0;
	Dy=0;
}
bool	AreaShaderThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	AreaShaderThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

AreaShaderThresholdSend::AreaShaderThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Dx=0;
	Dy=0;
}

void	AreaShaderThresholdSend::ConstructList(AreaShaderThresholdReq *reqPacket,AreaShaderBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerRoot	*Al=Ap->GetLayerData(reqPacket->Layer);
		if(Al!=NULL){
			AlgorithmItemRoot	*item	=Al->SearchIDItem(ItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				AreaShaderItem	*BItem=(AreaShaderItem *)item;
				const AreaShaderThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				CellSize	=RThr->CellSize;
				AdoptRate	=RThr->AdoptRate;
				Fixed		=RThr->Fixed;
				Average		=RThr->Average;
				Sigma		=RThr->Sigma;
			}
		}
	}
}

bool	AreaShaderThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;

	if(::Save(f,CellSize)==false)
		return false;
	if(::Save(f,AdoptRate)==false)
		return false;
	if(::Save(f,Fixed)==false)
		return false;
	if(::Save(f,Average)==false)
		return false;
	if(::Save(f,Sigma)==false)
		return false;

	return true;
}
bool	AreaShaderThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;

	if(::Load(f,CellSize)==false)
		return false;
	if(::Load(f,AdoptRate)==false)
		return false;
	if(::Load(f,Fixed)==false)
		return false;
	if(::Load(f,Average)==false)
		return false;
	if(::Load(f,Sigma)==false)
		return false;
	return true;
}