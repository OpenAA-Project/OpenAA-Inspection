#include "BuslineInspectionResource.h"
#include "XBuslineInspection.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XCriticalFunc.h"

bool	AreaWithBrightness::Save(QIODevice *f)
{
	if(FlexArea::Save(f)==false)
		return false;
	if(::Save(f,PeakH)==false)
		return false;
	if(::Save(f,PeakL)==false)
		return false;
	if(::Save(f,ThresholdBrightness)==false)
		return false;
	return false;
}
bool	AreaWithBrightness::Load(QIODevice *f)
{
	if(FlexArea::Load(f)==false)
		return false;
	if(::Load(f,PeakH)==false)
		return false;
	if(::Load(f,PeakL)==false)
		return false;
	if(::Load(f,ThresholdBrightness)==false)
		return false;
	return false;
}

void	FlexAreaWithBrightnessListContainer::MoveNoClip(int dx ,int dy)
{
	for(AreaWithBrightness *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
}

void	FlexAreaWithBrightnessListContainer::MoveClip(int dx ,int dy ,int Left ,int Top ,int Right ,int Bottom)
{
	for(AreaWithBrightness *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToClip(dx,dy,Left ,Top ,Right ,Bottom);
	}
}

FlexAreaWithBrightnessListContainer	&FlexAreaWithBrightnessListContainer::operator=(FlexAreaWithBrightnessListContainer &src)
{
	RemoveAll();
	for(AreaWithBrightness *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AreaWithBrightness	*b=new AreaWithBrightness();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

FlexAreaWithBrightnessListContainer	&FlexAreaWithBrightnessListContainer::operator+=(FlexAreaWithBrightnessListContainer &src)
{
	for(AreaWithBrightness *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AreaWithBrightness	*b=new AreaWithBrightness();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

bool	FlexAreaWithBrightnessListContainer::IsInclude(int x ,int y)
{
	for(AreaWithBrightness *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y)==true)
			return true;
	}
	return false;
}
AreaWithBrightness	*FlexAreaWithBrightnessListContainer::SearchArea(int x ,int y)
{
	for(AreaWithBrightness *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(x,y)==true)
			return a;
	}
	return NULL;
}

//==========================================================================================================
BuslineThreshold::BuslineThreshold(BuslineItem *parent)
	:AlgorithmThreshold(parent)
{
	MinWidth			=3;	//最小線幅
	MinGap				=3;
	LimitDot			=200;	//限界サイズ
	MinArea				=0;
	MaxArea				=0x7FFFFFFF;
	MinSize				=0;
	Darkside			=true;
	CompareToMaster		=false;
	AutoBinarize		=true;
	ReduceNoise			=true;
	BinarizedLength		=200;	//局所２値化領域サイズ
	ReferredBrightness	=100;
	SearchDotToMaster	=5;
	WidthToIgnoreEdge	=2;
	OKNickRate			=50;			//0-100% for MinWidth
	OKShortRate			=50;		//0-100% for MinGap
	BrightnessWidthInsideL	=20;
	BrightnessWidthInsideH	=20;
	BrightnessWidthOutsideL	=20;
	BrightnessWidthOutsideH	=20;
}

void	BuslineThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	AlgorithmThreshold::CopyFrom(src);

	const BuslineThreshold	*s=dynamic_cast<const BuslineThreshold *>(&src);
	MinWidth			=s->MinWidth;
	MinGap				=s->MinGap;
	LimitDot			=s->LimitDot;
	MinArea				=s->MinArea;
	MaxArea				=s->MaxArea;
	MinSize				=s->MinSize;
	Darkside			=s->Darkside;
	CompareToMaster		=s->CompareToMaster;
	AutoBinarize		=s->AutoBinarize;
	ReduceNoise			=s->ReduceNoise;
	BinarizedLength		=s->BinarizedLength;
	ReferredBrightness	=s->ReferredBrightness;
	SearchDotToMaster	=s->SearchDotToMaster;
	WidthToIgnoreEdge	=s->WidthToIgnoreEdge;
	OKNickRate			=s->OKNickRate;
	OKShortRate			=s->OKShortRate;
	BrightnessWidthInsideL	=s->BrightnessWidthInsideL	;
	BrightnessWidthInsideH	=s->BrightnessWidthInsideH	;
	BrightnessWidthOutsideL	=s->BrightnessWidthOutsideL;
	BrightnessWidthOutsideH	=s->BrightnessWidthOutsideH;
}

bool	BuslineThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const BuslineThreshold	*s=dynamic_cast<const BuslineThreshold *>(&src);
	if(MinWidth					!=s->MinWidth				)	return false;
	if(MinGap					!=s->MinGap					)	return false;
	if(LimitDot					!=s->LimitDot				)	return false;
	if(MinArea					!=s->MinArea				)	return false;
	if(MaxArea					!=s->MaxArea				)	return false;
	if(MinSize					!=s->MinSize				)	return false;
	if(Darkside					!=s->Darkside				)	return false;
	if(CompareToMaster			!=s->CompareToMaster		)	return false;
	if(AutoBinarize				!=s->AutoBinarize			)	return false;
	if(ReduceNoise				!=s->ReduceNoise			)	return false;
	if(BinarizedLength			!=s->BinarizedLength		)	return false;
	if(ReferredBrightness		!=s->ReferredBrightness		)	return false;
	if(SearchDotToMaster		!=s->SearchDotToMaster		)	return false;
	if(WidthToIgnoreEdge		!=s->WidthToIgnoreEdge		)	return false;
	if(OKNickRate				!=s->OKNickRate				)	return false;
	if(OKShortRate				!=s->OKShortRate			)	return false;
	if(BrightnessWidthInsideL	!=s->BrightnessWidthInsideL	)	return false;
	if(BrightnessWidthInsideH	!=s->BrightnessWidthInsideH	)	return false;
	if(BrightnessWidthOutsideL	!=s->BrightnessWidthOutsideL)	return false;
	if(BrightnessWidthOutsideH	!=s->BrightnessWidthOutsideH)	return false;
	return true;
}

bool	BuslineThreshold::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,MinWidth)==false){
		return false;
	}
	if(::Save(f,MinGap)==false){
		return false;
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	if(::Save(f,Darkside)==false){
		return false;
	}
	if(::Save(f,CompareToMaster)==false){
		return false;
	}
	if(::Save(f,AutoBinarize)==false){
		return false;
	}
	if(::Save(f,ReduceNoise)==false){
		return false;
	}
	if(::Save(f,ReferredBrightness)==false){
		return false;
	}
	if(::Save(f,SearchDotToMaster)==false){
		return false;
	}
	if(::Save(f,MinArea)==false){
		return false;
	}
	if(::Save(f,MaxArea)==false){
		return false;
	}
	if(::Save(f,MinSize)==false){
		return false;
	}
	if(::Save(f,BinarizedLength)==false){
		return false;
	}
	if(::Save(f,WidthToIgnoreEdge)==false){
		return false;
	}
	if(::Save(f,OKNickRate)==false){
		return false;
	}
	if(::Save(f,OKShortRate)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthInsideL)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthInsideH)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthOutsideL)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthOutsideH)==false){
		return false;
	}
	return true;
}

bool	BuslineThreshold::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,MinWidth)==false){
		return false;
	}
	if(::Load(f,MinGap)==false){
		return false;
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	if(::Load(f,Darkside)==false){
		return false;
	}
	if(::Load(f,CompareToMaster)==false){
		return false;
	}
	if(::Load(f,AutoBinarize)==false){
		return false;
	}
	if(::Load(f,ReduceNoise)==false){
		return false;
	}
	if(::Load(f,ReferredBrightness)==false){
		return false;
	}
	if(::Load(f,SearchDotToMaster)==false){
		return false;
	}
	if (::Load(f, MinArea) == false) {
		return false;
	}
	if (::Load(f, MaxArea) == false) {
		return false;
	}
	if (::Load(f, MinSize) == false) {
		return false;
	}
	if(::Load(f,BinarizedLength)==false){
		return false;
	}
	
	if(::Load(f,WidthToIgnoreEdge)==false){
		return false;
	}
	if(::Load(f,OKNickRate)==false){
		return false;
	}
	if(::Load(f,OKShortRate)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthInsideL)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthInsideH)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthOutsideL)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthOutsideH)==false){
		return false;
	}
	return true;
}

void	BuslineThreshold::FromLibrary(AlgorithmLibrary *src)
{
	BuslineLibrary	*s=dynamic_cast<BuslineLibrary *>(src);
	MinWidth			=s->MinWidth;
	MinGap				=s->MinGap;
	LimitDot			=s->LimitDot;
	MinArea				=s->MinArea;
	MaxArea				=s->MaxArea;
	MinSize				=s->MinSize;
	Darkside			=s->Darkside;
	CompareToMaster		=s->CompareToMaster;
	AutoBinarize		=s->AutoBinarize;
	ReduceNoise			=s->ReduceNoise;
	BinarizedLength		=s->BinarizedLength;
	ReferredBrightness	=s->ReferredBrightness;
	SearchDotToMaster	=s->SearchDotToMaster;
	WidthToIgnoreEdge	=s->WidthToIgnoreEdge;
	OKNickRate			=s->OKNickRate;
	OKShortRate			=s->OKShortRate;
	BrightnessWidthInsideL	=s->BrightnessWidthInsideL	;
	BrightnessWidthInsideH	=s->BrightnessWidthInsideH	;
	BrightnessWidthOutsideL	=s->BrightnessWidthOutsideL;
	BrightnessWidthOutsideH	=s->BrightnessWidthOutsideH;
}

void	BuslineThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	BuslineLibrary	*d=dynamic_cast<BuslineLibrary *>(Dest);
	d->MinWidth				=MinWidth;
	d->MinGap				=MinGap;
	d->LimitDot				=LimitDot;
	d->MinArea				=MinArea;
	d->MaxArea				=MaxArea;
	d->MinSize				=MinSize;
	d->Darkside				=Darkside;
	d->CompareToMaster		=CompareToMaster;
	d->AutoBinarize			=AutoBinarize;
	d->ReduceNoise			=ReduceNoise;
	d->BinarizedLength		=BinarizedLength;
	d->ReferredBrightness	=ReferredBrightness;
	d->SearchDotToMaster	=SearchDotToMaster;
	d->WidthToIgnoreEdge	=WidthToIgnoreEdge;
	d->OKNickRate			=OKNickRate;
	d->OKShortRate			=OKShortRate;
	d->BrightnessWidthInsideL	=BrightnessWidthInsideL	;
	d->BrightnessWidthInsideH	=BrightnessWidthInsideH	;
	d->BrightnessWidthOutsideL	=BrightnessWidthOutsideL;
	d->BrightnessWidthOutsideH	=BrightnessWidthOutsideH;
}


//=====================================================================

BuslineInLayer::BuslineInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLI(parent)
{
}
bool	BuslineInLayer::AppendItem(AlgorithmItemRoot *item)
{
	AlgorithmLibraryContainer	*Container=GetLibraryContainer();
	AlgorithmLibraryLevelContainer	LLib(Container);
	if(Container->GetLibrary(item->GetLibID(),LLib)==true){
		if(LLib.HasGenLayer(GetLayer())==true){
			return AlgorithmInLayerPLI::AppendItem(item);
		}
		return false;
	}
	return AlgorithmInLayerPLI::AppendItem(item);
}
bool	BuslineInLayer::AppendItem(AlgorithmItemRoot* item , AlgorithmLibrary * LibP)
{
	if(LibP!=NULL){
		if (LibP->HasGenLayer(GetLayer()) == true) {
			return AlgorithmInLayerPLI::AppendItem(item);
		}
		return false;
	}
	else{
		return AppendItem(item);
	}
}
bool		BuslineInLayer::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}

bool		BuslineInLayer::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	return AlgorithmInLayerPLI::AppendItemFromLoad(item);
}

bool		BuslineInLayer::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	return AlgorithmInLayerPLI::AppendItem(item,itemID);
}

void	BuslineInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddBuslineItemPacket	*CmdAddBuslineItemVar=dynamic_cast<CmdAddBuslineItemPacket *>(packet);
	if(CmdAddBuslineItemVar!=NULL){
		AlgorithmItemRoot	*Item=CreateItem(0);
		Item->SetArea(CmdAddBuslineItemVar->Area);
		Item->SetLibID(CmdAddBuslineItemVar->LibID);
		BuslineBase	*BBase=(BuslineBase *)GetParentBase();

		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LLib(Container);
		if(Container->GetLibrary(CmdAddBuslineItemVar->LibID,LLib)==true){
			((BuslineItem *)Item)->CopyThresholdFromLibrary(&LLib);
			if(AppendItem(Item)==false){
				delete	Item;
			}
		}
		return;
	}
	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			BuslineItem	*a=dynamic_cast<BuslineItem *>(k);
			if(a!=NULL){
				BuslineListForPacket	*k=new BuslineListForPacket();
				k->ItemID	=a->GetID();
				k->Page		=a->GetPage();
				k->Layer	=a->GetLayer();
				a->GetXY(k->x1,k->y1,k->x2,k->y2);
				k->Angle	=0;
				MakeListPacketVar->ListInfo->AppendList(k);
			}
		}
		return;
	}
	CmdGenerateBuslinePacket	*CmdGenerateBuslinePacketVar=dynamic_cast<CmdGenerateBuslinePacket *>(packet);
	if(CmdGenerateBuslinePacketVar!=NULL){
		GenerateBlocks(CmdGenerateBuslinePacketVar->LibList);
	}
	CmdTestBuslinePacket	*CmdTestBuslinePacketVar=dynamic_cast<CmdTestBuslinePacket *>(packet);
	if(CmdTestBuslinePacketVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			BuslineItem	*a=dynamic_cast<BuslineItem *>(k);
			if(a!=NULL){
				a->MakeBMap();
			}
		}
		return;
	}
	CmdClearBuslinePacket	*CmdClearBuslinePacketVar=dynamic_cast<CmdClearBuslinePacket *>(packet);
	if(CmdClearBuslinePacketVar!=NULL){
		for(AlgorithmItemPLI *k=GetFirstData();k!=NULL;k=k->GetNext()){
			BuslineItem	*a=dynamic_cast<BuslineItem *>(k);
			if(a!=NULL){
				a->ClearBMap();
			}
		}
		return;
	}
}

void	BuslineInLayer::GenerateBlocks(IntList &LibList)
{
	GetParentBase()->LoadAllManagedCacheLib();
	int XByte	=(GetDotPerLine()+7)/8;
	int XLen	= GetDotPerLine();
	int YLen	=GetMaxLines();
	AlgorithmLibraryContainer	*LibContainer=GetLibraryContainer();
	if (LibContainer!= NULL) {
		for(IntClass *Lib=LibList.GetFirst();Lib!=NULL;Lib=Lib->GetNext()){
			AlgorithmLibraryLevelContainer	LLib(LibContainer);
			if(LibContainer->GetLibrary(Lib->GetValue(), LLib)==true){
				BuslineLibrary	*L=dynamic_cast<BuslineLibrary *>(LLib.GetLibrary());
				ConstMapBuffer MaskMap;
				GetReflectionMap(_Reflection_Mask,MaskMap,L);
	
				PureFlexAreaListContainer FPack;
				::PickupFlexArea(MaskMap.GetBitMap(), XByte, XLen, YLen, FPack);

				for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
					PureFlexAreaList	*NextF=f->GetNext();
					if(f->GetPatternByte()<L->BlockMinArea || L->BlockMaxArea<f->GetPatternByte()){
						FPack.RemoveList(f);
						delete	f;
						f=NULL;
					}
					if(f!=NULL){
						PureFlexAreaListContainer Piece;
						f->ChopRect(Piece, L->LimitDot,L->LimitDot/4);
						int		MinPieceSize= L->LimitDot* L->LimitDot/100;
						if(MinPieceSize<20)
							MinPieceSize=20;

						for(PureFlexAreaList *p=Piece.GetFirst();p!=NULL;){
							PureFlexAreaList *NextP=p->GetNext();
							if(p->GetPatternByte()< MinPieceSize){
								for(PureFlexAreaList * t=Piece.GetFirst(); t!=NULL;t=t->GetNext()) {
									if(t==p)
										continue;
									if(p->CheckOverlapNeighbor(t)==true){
										*t += *p;
										break;
									}
								}
								if(p!=NULL){
									Piece.RemoveList(p);
									delete	p;
								}
							}
							p=NextP;
						}
						for(PureFlexAreaList *p=Piece.GetFirst();p!=NULL;p=p->GetNext()) {
							BuslineItem	*b=new BuslineItem();
							b->SetLibID(Lib->GetValue());
							b->SetArea(*p);
							AppendItem(b,L);
							b->CopyThresholdFromLibrary(&LLib);
						}
					}
					f=NextF;
				}
			}
		}
	}
}

void	BuslineInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		BuslineItem	*BI=(BuslineItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

//=====================================================================

BuslineInPage::BuslineInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLI(parent)
{
}

void	BuslineInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddBuslineItemPacket	*CmdAddBuslineItemVar=dynamic_cast<CmdAddBuslineItemPacket *>(packet);
	if(CmdAddBuslineItemVar!=NULL){
		for(IntClass *L=CmdAddBuslineItemVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			AL->TransmitDirectly(packet);
		}
		return;
	}
	MakeListPacket	*MakeListPacketVar=dynamic_cast<MakeListPacket *>(packet);
	if(MakeListPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			AL->TransmitDirectly(packet);
		}
		return;

	}
	CmdGenerateBuslinePacket	*CmdGenerateBuslinePacketVar=dynamic_cast<CmdGenerateBuslinePacket *>(packet);
	if(CmdGenerateBuslinePacketVar!=NULL){
		for(IntClass *L=CmdGenerateBuslinePacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			AL->TransmitDirectly(packet);
		}
		return;
	}
	CmdTestBuslinePacket	*CmdTestBuslinePacketVar=dynamic_cast<CmdTestBuslinePacket *>(packet);
	if(CmdTestBuslinePacketVar!=NULL){
		for(IntClass *L=CmdTestBuslinePacketVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			AL->TransmitDirectly(packet);
		}
		return;
	}
	CmdClearBuslinePacket	*CmdClearBuslinePacketVar=dynamic_cast<CmdClearBuslinePacket *>(packet);
	if(CmdClearBuslinePacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			AL->TransmitDirectly(packet);
		}
		return;
	}
}

//=====================================================================
BuslineBase::BuslineBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorMask		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorMask			, /**/"Color" ,/**/"ColorMask"			,LangSolver.GetString(XBuslineInspection_LS,LID_0)/*"Color for Mask"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XBuslineInspection_LS,LID_1)/*"Color for Selected Mask"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XBuslineInspection_LS,LID_2)/*"Color for Active Mask"*/);
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,LangSolver.GetString(XBuslineInspection_LS,LID_3)/*"Color for Negative Mask"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XBuslineInspection_LS,LID_4)/*"Color for Selected Negative Mask"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XBuslineInspection_LS,LID_5)/*"Color for Transparent display level"*/);
}

AlgorithmDrawAttr	*BuslineBase::CreateDrawAttr(void)
{
	return new BuslineDrawAttr();
}

void	BuslineBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetBuslineLibraryListPacket	*AListPacket=dynamic_cast<CmdGetBuslineLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdCreateTempBuslineLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempBuslineLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdLoadBuslineLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadBuslineLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearBuslineLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearBuslineLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteBuslineLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteBuslineLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertBuslineLibraryPacket	*BInsLib=dynamic_cast<CmdInsertBuslineLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(BuslineVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateBuslineLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateBuslineLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(BuslineVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetBuslineLibraryNamePacket	*CmdGetBuslineLibraryNamePacketVar=dynamic_cast<CmdGetBuslineLibraryNamePacket *>(packet);
	if(CmdGetBuslineLibraryNamePacketVar!=NULL){
		AlgorithmLibraryLevelContainer	TmpLib(this);
		if(GetLibraryContainer()!=NULL){
			CmdGetBuslineLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetBuslineLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetBuslineLibraryNamePacketVar->Success=true){
				CmdGetBuslineLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
}

bool	BuslineBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==BuslineReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BuslineReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if (Command == BuslineReqTryThresholdCommand) {
		delete	data;
		return true;
	}
	else if (Command == BuslineSendTryThresholdCommand) {
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*BuslineBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	if(Command==BuslineReqThresholdReqCommand){
		return new BuslineThresholdReq();
	}
	else if(Command==BuslineReqThresholdSendCommand){
		BuslineThresholdSend	*pSend=new BuslineThresholdSend();
		if(reqData!=NULL){
			BuslineThresholdReq	*req=(BuslineThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if (Command == BuslineReqTryThresholdCommand) {
		return new BuslineReqTryThreshold();
	}
	else if (Command == BuslineSendTryThresholdCommand) {
		BuslineSendTryThreshold* pSend = new BuslineSendTryThreshold();
		if (reqData != NULL) {
			BuslineReqTryThreshold* req = (BuslineReqTryThreshold*)reqData;
			pSend->ConstructList(req, this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	BuslineBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==BuslineReqThresholdReqCommand){
		BuslineThresholdReq	*p=(BuslineThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==BuslineReqThresholdSendCommand){
		BuslineThresholdSend	*p=(BuslineThresholdSend *)data;
		return p->Load(f);
	}
	else if (Command == BuslineReqTryThresholdCommand) {
		BuslineReqTryThreshold* p = (BuslineReqTryThreshold*)data;
		return p->Load(f, GetLayersBase());
	}
	else if (Command == BuslineSendTryThresholdCommand) {
		BuslineSendTryThreshold* p = (BuslineSendTryThreshold*)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	BuslineBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==BuslineReqThresholdReqCommand){
		BuslineThresholdReq	*p=(BuslineThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==BuslineReqThresholdSendCommand){
		BuslineThresholdSend	*p=(BuslineThresholdSend *)data;
		return p->Save(f);
	}
	else if (Command == BuslineReqTryThresholdCommand) {
		BuslineReqTryThreshold* p = (BuslineReqTryThreshold*)data;
		return p->Save(f);
	}
	else if (Command == BuslineSendTryThresholdCommand) {
		BuslineSendTryThreshold* p = (BuslineSendTryThreshold*)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	BuslineBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==BuslineReqThresholdReqCommand){
		BuslineThresholdReq	*p=(BuslineThresholdReq *)data;
		return true;
	}
	else if(Command==BuslineReqThresholdSendCommand){
		BuslineThresholdSend	*p=(BuslineThresholdSend *)data;
		return true;
	}
	else if (Command == BuslineReqTryThresholdCommand) {
		BuslineReqTryThreshold* p = (BuslineReqTryThreshold*)data;
		return true;
	}
	else if (Command == BuslineSendTryThresholdCommand) {
		BuslineSendTryThreshold* p = (BuslineSendTryThreshold*)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

//======================================================================

BuslineThresholdReq::BuslineThresholdReq(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Layer		=-1;
	Mastered	=true;
	Dx			=0;
	Dy			=0;
}

bool	BuslineThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}

bool	BuslineThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

BuslineThresholdSend::BuslineThresholdSend(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Layer		=-1;
	Dx			=0;
	Dy			=0;
	MinWidth			=3;
	MinGap				=3;
	MinArea				=0;
	MaxArea				=0x7FFFFFFF;
	MinSize				=0;
	Darkside			=true;
	CompareToMaster		=false;
	AutoBinarize		=false;
	ReduceNoise			=true;
	BinarizedLength		=200;	//局所２値化領域サイズ
	ReferredBrightness	=100;	//２値化参照輝度
	SearchDotToMaster	=5;
	WidthToIgnoreEdge	=2;
	OKNickRate			=50;			//0-100% for MinWidth
	OKShortRate			=50;		//0-100% for MinGap
	BrightnessWidthInsideL	=20;
	BrightnessWidthInsideH	=20;
	BrightnessWidthOutsideL	=20;
	BrightnessWidthOutsideH	=20;
}

void	BuslineThresholdSend::ConstructList(BuslineThresholdReq *reqPacket,BuslineBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	ItemID		=reqPacket->ItemID;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(ItemID);
			if(item!=NULL){
				BuslineItem	*Item=dynamic_cast<BuslineItem*>(item);
				const	BuslineThreshold	*RThr=Item->GetThresholdR(Ap->GetLayersBase());
				MinWidth				=RThr->MinWidth;	//最小線幅
				MinGap					=RThr->MinGap;		//最小間隔
				MinArea					=RThr->MinArea	;
				MaxArea					=RThr->MaxArea	;
				MinSize					=RThr->MinSize;
				Darkside				=RThr->Darkside;
				CompareToMaster			=RThr->CompareToMaster;
				AutoBinarize			=RThr->AutoBinarize;
				ReduceNoise				=RThr->ReduceNoise;
				BinarizedLength			=RThr->BinarizedLength;
				ReferredBrightness		=RThr->ReferredBrightness;
				SearchDotToMaster		=RThr->SearchDotToMaster;				
				WidthToIgnoreEdge		=RThr->WidthToIgnoreEdge;	
				OKNickRate				=RThr->OKNickRate;	
				OKShortRate				=RThr->OKShortRate;
				BrightnessWidthInsideL	=RThr->BrightnessWidthInsideL ;
				BrightnessWidthInsideH	=RThr->BrightnessWidthInsideH ;
				BrightnessWidthOutsideL	=RThr->BrightnessWidthOutsideL;
				BrightnessWidthOutsideH	=RThr->BrightnessWidthOutsideH;
			}
		}
	}
}
	
bool	BuslineThresholdSend::Save(QIODevice *f)
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
	if(::Save(f,MinWidth)==false){
		return false;
	}
	if(::Save(f,MinGap)==false){
		return false;
	}
	if(::Save(f,Darkside)==false){
		return false;
	}
	if(::Save(f,CompareToMaster)==false){
		return false;
	}
	if(::Save(f,AutoBinarize)==false){
		return false;
	}
	if(::Save(f,ReduceNoise)==false){
		return false;
	}
	if(::Save(f,BinarizedLength)==false){
		return false;
	}
	if(::Save(f,ReferredBrightness)==false){
		return false;
	}
	if(::Save(f,SearchDotToMaster)==false){
		return false;
	}
	if(::Save(f,MinArea)==false){
		return false;
	}
	if(::Save(f,MaxArea)==false){
		return false;
	}
	if(::Save(f,MinSize)==false){
		return false;
	}
	if(::Save(f,WidthToIgnoreEdge)==false){
		return false;
	}
	if(::Save(f,OKNickRate)==false){
		return false;
	}
	if(::Save(f,OKShortRate)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthInsideL)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthInsideH)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthOutsideL)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthOutsideH)==false){
		return false;
	}
	return true;
}
	
bool	BuslineThresholdSend::Load(QIODevice *f)
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
	if(::Load(f,MinWidth)==false){
		return false;
	}
	if(::Load(f,MinGap)==false){
		return false;
	}
	if(::Load(f,Darkside)==false){
		return false;
	}
	if(::Load(f,CompareToMaster)==false){
		return false;
	}
	if(::Load(f,AutoBinarize)==false){
		return false;
	}
	if(::Load(f,ReduceNoise)==false){
		return false;
	}
	if(::Load(f,BinarizedLength)==false){
		return false;
	}
	if(::Load(f,ReferredBrightness)==false){
		return false;
	}
	if(::Load(f,SearchDotToMaster)==false){
		return false;
	}
	if(::Load(f,MinArea)==false){
		return false;
	}
	if(::Load(f,MaxArea)==false){
		return false;
	}
	if(::Load(f,MinSize)==false){
		return false;
	}
	if(::Load(f,WidthToIgnoreEdge)==false){
		return false;
	}
	if(::Load(f,OKNickRate)==false){
		return false;
	}
	if(::Load(f,OKShortRate)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthInsideL)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthInsideH)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthOutsideL)==false){
		return false;
	}
	if(::Load(f,BrightnessWidthOutsideH)==false){
		return false;
	}

	return true;
}


BuslineReqTryThreshold::BuslineReqTryThreshold(void)
{
	GlobalPage	= -1;
	Layer		= -1;
	ItemID		= -1;
}
bool	BuslineReqTryThreshold::Save(QIODevice* f)
{
	if (::Save(f, GlobalPage) == false)
		return false;
	if (::Save(f, Layer) == false)
		return false;
	if (::Save(f, ItemID) == false)
		return false;
	if (Threshold.Save(f) == false)
		return false;
	return true;
}
bool	BuslineReqTryThreshold::Load(QIODevice* f, LayersBase* LBase)
{
	if (::Load(f, GlobalPage) == false)
		return false;
	if (::Load(f, Layer) == false)
		return false;
	if (::Load(f, ItemID) == false)
		return false;
	if (Threshold.Load(f, LBase) == false)
		return false;
	return true;
}

BuslineSendTryThreshold::BuslineSendTryThreshold(void)
{
	NGDotOpen	=0;
	NGDotShort	=0;
	ResultMoveDx=0;
	ResultMoveDy=0;
	Error		=0;
	Result		=new ResultInItemPLI();
	BMapOpen	=NULL;
	BMapShort	=NULL;
	BMapBinary	=NULL;
}
BuslineSendTryThreshold::~BuslineSendTryThreshold(void)
{
	if (Result != NULL) {
		delete	Result;
		Result = NULL;
	}
	if (BMapOpen != NULL) {
		DeleteMatrixBuff(BMapOpen, BMapYLen);
		BMapOpen = NULL;
	}
	if (BMapShort != NULL) {
		DeleteMatrixBuff(BMapShort, BMapYLen);
		BMapShort = NULL;
	}
	if (BMapBinary != NULL) {
		DeleteMatrixBuff(BMapBinary, BMapYLen);
		BMapBinary = NULL;
	}
}


bool	BuslineSendTryThreshold::Save(QIODevice* f)
{
	if (::Save(f, NGDotOpen) == false)
		return false;
	if (::Save(f, NGDotShort) == false)
		return false;
	if (::Save(f, ResultMoveDx) == false)
		return false;
	if (::Save(f, ResultMoveDy) == false)
		return false;
	if (::Save(f, Error) == false)
		return false;
	if (Result->Save(f) == false)
		return false;

	if (::Save(f, BMapXByte) == false)
		return false;
	if (::Save(f, BMapXLen) == false)
		return false;
	if (::Save(f, BMapYLen) == false)
		return false;
	if (::Save(f, BMapOpen, BMapXByte, BMapYLen) == false)
		return false;
	if (::Save(f, BMapShort, BMapXByte, BMapYLen) == false)
		return false;
	if (::Save(f, BMapBinary, BMapXByte, BMapYLen) == false)
		return false;
	return true;
}
bool	BuslineSendTryThreshold::Load(QIODevice* f)
{
	if (::Load(f, NGDotOpen) == false)
		return false;
	if (::Load(f, NGDotShort) == false)
		return false;
	if (::Load(f, ResultMoveDx) == false)
		return false;
	if (::Load(f, ResultMoveDy) == false)
		return false;
	if (::Load(f, Error) == false)
		return false;
	if (Result->Load(f) == false)
		return false;

	if (BMapOpen != NULL) {
		DeleteMatrixBuff(BMapOpen, BMapYLen);
		BMapOpen = NULL;
	}
	if (BMapShort != NULL) {
		DeleteMatrixBuff(BMapShort, BMapYLen);
		BMapShort = NULL;
	}
	if (BMapBinary != NULL) {
		DeleteMatrixBuff(BMapBinary, BMapYLen);
		BMapBinary = NULL;
	}

	if (::Load(f, BMapXByte) == false)
		return false;
	if (::Load(f, BMapXLen) == false)
		return false;
	if (::Load(f, BMapYLen) == false)
		return false;
	BMapOpen	= MakeMatrixBuff(BMapXByte, BMapYLen);
	BMapShort	= MakeMatrixBuff(BMapXByte, BMapYLen);
	BMapBinary	= MakeMatrixBuff(BMapXByte, BMapYLen);

	if (::Load(f, BMapOpen, BMapXByte, BMapYLen) == false)
		return false;
	if (::Load(f, BMapShort, BMapXByte, BMapYLen) == false)
		return false;
	if (::Load(f, BMapBinary, BMapXByte, BMapYLen) == false)
		return false;

	return true;
}

void	BuslineSendTryThreshold::ConstructList(BuslineReqTryThreshold* reqPacket, BuslineBase* Base)
{
	Result->SetAddedData(this, 1, sizeof(this));
	BuslineInPage* BP = (BuslineInPage*)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if (BP != NULL) {
		BuslineInLayer* BL = (BuslineInLayer*)BP->GetLayerData(reqPacket->Layer);
		if (BL != NULL) {
			BuslineItem* BI = (BuslineItem*)BL->SearchIDItem(reqPacket->ItemID);
			if (BI != NULL) {
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.AVector = BI->AVector;
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.SetArea	(BI->GetArea());
				reqPacket->Threshold.SetLibID	(BI->GetLibID());

				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				reqPacket->Threshold.ExecuteInitialAfterEdit (0, 0, Result,EInfo);
				reqPacket->Threshold.ExecuteStartByInspection(0, 0, Result);
				reqPacket->Threshold.ExecuteProcessing(0, 0, Result);


				NGDotOpen	= reqPacket->Threshold.NGDotOpen;
				NGDotShort	= reqPacket->Threshold.NGDotShort;

				if (BMapOpen != NULL) {
					DeleteMatrixBuff(BMapOpen, BMapYLen);
					BMapOpen = NULL;
				}
				if (BMapShort != NULL) {
					DeleteMatrixBuff(BMapShort, BMapYLen);
					BMapShort = NULL;
				}
				if (BMapBinary != NULL) {
					DeleteMatrixBuff(BMapBinary, BMapYLen);
					BMapBinary = NULL;
				}
				BMapXByte	= reqPacket->Threshold.BMapXByte;
				BMapXLen	= reqPacket->Threshold.BMapXLen;
				BMapYLen	= reqPacket->Threshold.BMapYLen;

				BMapOpen	= MakeMatrixBuff(BMapXByte, BMapYLen);
				BMapShort	= MakeMatrixBuff(BMapXByte, BMapYLen);
				BMapBinary	= MakeMatrixBuff(BMapXByte, BMapYLen);

				::MatrixBuffCopy(BMapOpen, BMapXByte, BMapYLen
								, (const BYTE**)reqPacket->Threshold.BMapOpen
								, reqPacket->Threshold.BMapXByte, reqPacket->Threshold.BMapYLen);
				::MatrixBuffCopy(BMapShort, BMapXByte, BMapYLen
								, (const BYTE**)reqPacket->Threshold.BMapShort
								, reqPacket->Threshold.BMapXByte, reqPacket->Threshold.BMapYLen);
				::MatrixBuffCopy(BMapBinary, BMapXByte, BMapYLen
								, (const BYTE**)reqPacket->Threshold.BMap
								, reqPacket->Threshold.BMapXByte, reqPacket->Threshold.BMapYLen);

				Error	= Result->GetError();
			}
		}
	}
	Result->SetAddedData(NULL, 0);

	ResultMoveDx = Result->GetTotalShiftedX();
	ResultMoveDy = Result->GetTotalShiftedY();
}
