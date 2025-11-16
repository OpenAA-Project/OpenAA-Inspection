#include "CheckEverydayResource.h"
#include "XCheckEveryday.h"
#include "XGeneralFunc.h"

CheckEverydayLibrary::CheckEverydayLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
}

CheckEverydayLibraryContainer::CheckEverydayLibraryContainer(LayersBase *base)
	:AlgorithmLibraryContainer(base)
{
}


CheckEverydayThreshold::CheckEverydayThreshold(AlgorithmItemPLI *parent)
	:AlgorithmThreshold(parent)
{
}

void	CheckEverydayThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	AlgorithmThreshold::CopyFrom(src);
}

//=====================================================================

CheckEverydayInLayer::CheckEverydayInLayer(AlgorithmInPageRoot *parent)
	:AlgorithmInLayerPLI(parent)
{
}

AlgorithmItemRoot	*CheckEverydayInLayer::CreateItem(int ItemClassType)
{
	if(ItemClassType==0){
		CheckEverydayLightItem	*a=new CheckEverydayLightItem();
		a->SetParent(this);
		return a;
	}
	else if(ItemClassType==1){
		CheckEverydayFocusItem	*a=new CheckEverydayFocusItem();
		a->SetParent(this);
		return a;
	}
	return NULL;
}

void	CheckEverydayInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	AddCheckEverydayAreaLightPacket	*AddCheckEverydayAreaLightPacketVar=dynamic_cast<AddCheckEverydayAreaLightPacket *>(packet);
	if(AddCheckEverydayAreaLightPacketVar!=NULL){
		AlgorithmItemRoot	*item=CreateItem(0);
		item->SetArea(AddCheckEverydayAreaLightPacketVar->Area);
		CheckEverydayLightItem	*Item=(CheckEverydayLightItem *)item;
		Item->SetItemName(AddCheckEverydayAreaLightPacketVar->ItemName);
		Item->BrightnessHigh=AddCheckEverydayAreaLightPacketVar->BrightnessHigh;
		Item->BrightnessLow	=AddCheckEverydayAreaLightPacketVar->BrightnessLow;
		AppendItem(Item);
		return;
	}
	AddCheckEverydayAreaFocusPacket	*AddCheckEverydayAreaFocusPacketVar=dynamic_cast<AddCheckEverydayAreaFocusPacket *>(packet);
	if(AddCheckEverydayAreaFocusPacketVar!=NULL){
		AlgorithmItemRoot	*item=CreateItem(1);
		item->SetArea(AddCheckEverydayAreaFocusPacketVar->Area);
		CheckEverydayFocusItem	*Item=(CheckEverydayFocusItem *)item;
		Item->SetItemName(AddCheckEverydayAreaFocusPacketVar->ItemName);
		Item->FocusLow		=AddCheckEverydayAreaFocusPacketVar->FocusLow;
		AppendItem(Item);
		return;
	}
	ReqCheckEverydayInfo	*ReqCheckEverydayInfoVar=dynamic_cast<ReqCheckEverydayInfo *>(packet);
	if(ReqCheckEverydayInfoVar!=NULL){
		for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			CheckEverydayLightItem	*LItem=dynamic_cast<CheckEverydayLightItem *>(a);
			if(LItem!=NULL){
				CheckEverydayLightInfo	*h=new CheckEverydayLightInfo();
				h->BrightnessHigh	=LItem->BrightnessHigh;
				h->BrightnessLow	=LItem->BrightnessLow;
				h->Page				=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				h->Layer			=GetLayer();
				h->ID				=a->GetID();
				h->CurrentValue		=LItem->Average;
				h->Result			=LItem->Result;
				h->ItemName			=LItem->GetItemName();
				a->GetXY(h->x1,h->y1,h->x2,h->y2);
				ReqCheckEverydayInfoVar->pInfoLight->AppendList(h);
			}
			CheckEverydayFocusItem	*FItem=dynamic_cast<CheckEverydayFocusItem *>(a);
			if(FItem!=NULL){
				CheckEverydayFocusInfo	*h=new CheckEverydayFocusInfo();
				h->FocusLow			=FItem->FocusLow;
				h->Page				=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				h->Layer			=GetLayer();
				h->ID				=a->GetID();
				h->CurrentValue		=FItem->VCoeff;
				h->Result			=FItem->Result;
				h->ItemName			=FItem->GetItemName();
				a->GetXY(h->x1,h->y1,h->x2,h->y2);
				ReqCheckEverydayInfoVar->pInfoFocus->AppendList(h);
			}
		}
		return;
	}
	ModifyCheckEverydayAreaLightPacket	*ModifyCheckEverydayAreaLightPacketVar=dynamic_cast<ModifyCheckEverydayAreaLightPacket *>(packet);
	if(ModifyCheckEverydayAreaLightPacketVar!=NULL){
		AlgorithmItemRoot *a=SearchIDItem(ModifyCheckEverydayAreaLightPacketVar->ItemID);
		if(a!=NULL){
			CheckEverydayLightItem	*LItem=dynamic_cast<CheckEverydayLightItem *>(a);
			if(LItem!=NULL){
				LItem->SetItemName(ModifyCheckEverydayAreaLightPacketVar->ItemName);
				LItem->BrightnessHigh	=ModifyCheckEverydayAreaLightPacketVar->BrightnessHigh;
				LItem->BrightnessLow	=ModifyCheckEverydayAreaLightPacketVar->BrightnessLow;
			}
		}
		return;
	}
	ModifyCheckEverydayAreaFocusPacket	*ModifyCheckEverydayAreaFocusPacketVar=dynamic_cast<ModifyCheckEverydayAreaFocusPacket *>(packet);
	if(ModifyCheckEverydayAreaFocusPacketVar!=NULL){
		AlgorithmItemRoot *a=SearchIDItem(ModifyCheckEverydayAreaFocusPacketVar->ItemID);
		if(a!=NULL){
			CheckEverydayFocusItem	*FItem=dynamic_cast<CheckEverydayFocusItem *>(a);
			if(FItem!=NULL){
				FItem->SetItemName(ModifyCheckEverydayAreaFocusPacketVar->ItemName);
				FItem->FocusLow		=ModifyCheckEverydayAreaFocusPacketVar->FocusLow;
			}
		}
		return;
	}

}
void	CheckEverydayInLayer::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		CheckEverydayItemBase	*BI=(CheckEverydayItemBase *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

//=====================================================================

CheckEverydayInPage::CheckEverydayInPage(AlgorithmBase *parent)
	:AlgorithmInPagePLI(parent)
{
}

void	CheckEverydayInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddCheckEverydayAreaLightPacket	*AddCheckEverydayAreaLightPacketVar=dynamic_cast<AddCheckEverydayAreaLightPacket *>(packet);
	if(AddCheckEverydayAreaLightPacketVar!=NULL){
		for(IntClass *c=AddCheckEverydayAreaLightPacketVar->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			AlgorithmInLayerRoot	*LBase=GetLayerData(Layer);
			LBase->TransmitDirectly(packet);
		}
		return;
	}
	AddCheckEverydayAreaFocusPacket	*AddCheckEverydayAreaFocusPacketVar=dynamic_cast<AddCheckEverydayAreaFocusPacket *>(packet);
	if(AddCheckEverydayAreaFocusPacketVar!=NULL){
		for(IntClass *c=AddCheckEverydayAreaFocusPacketVar->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
			int	Layer=c->GetValue();
			AlgorithmInLayerRoot	*LBase=GetLayerData(Layer);
			LBase->TransmitDirectly(packet);
		}
		return;
	}
	ReqCheckEverydayInfo	*ReqCheckEverydayInfoVar=dynamic_cast<ReqCheckEverydayInfo *>(packet);
	if(ReqCheckEverydayInfoVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			AlgorithmInLayerRoot	*LBase=GetLayerData(Layer);
			LBase->TransmitDirectly(packet);
		}
		return;
	}
	ModifyCheckEverydayAreaLightPacket	*ModifyCheckEverydayAreaLightPacketVar=dynamic_cast<ModifyCheckEverydayAreaLightPacket *>(packet);
	if(ModifyCheckEverydayAreaLightPacketVar!=NULL){
		AlgorithmInLayerRoot	*LBase=GetLayerData(ModifyCheckEverydayAreaLightPacketVar->Layer);
		LBase->TransmitDirectly(packet);
		return;
	}
	ModifyCheckEverydayAreaFocusPacket	*ModifyCheckEverydayAreaFocusPacketVar=dynamic_cast<ModifyCheckEverydayAreaFocusPacket *>(packet);
	if(ModifyCheckEverydayAreaFocusPacketVar!=NULL){
		AlgorithmInLayerRoot	*LBase=GetLayerData(ModifyCheckEverydayAreaFocusPacketVar->Layer);
		LBase->TransmitDirectly(packet);
		return;
	}
}

//=====================================================================
CheckEverydayBase::CheckEverydayBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	TransparentLevel=80;
	UseFocusLayer	=-1;

	SetParam(&ColorArea			, /**/"Color" ,/**/"ColorArea"			,LangSolver.GetString(XCheckEveryday_LS,LID_0)/*"Color for Area"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XCheckEveryday_LS,LID_1)/*"Color for Selected Area"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XCheckEveryday_LS,LID_2)/*"Color for Active Area"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XCheckEveryday_LS,LID_3)/*"Color for Transparent display level"*/);

	SetParam(&UseFocusLayer		, /**/"Setting" ,/**/"UseFocusLayer"	,LangSolver.GetString(XCheckEveryday_LS,LID_4)/*"Use layer for Focus"*/);
}

AlgorithmDrawAttr	*CheckEverydayBase::CreateDrawAttr(void)
{
	return new CheckEverydayDrawAttr();
}

void	CheckEverydayBase::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdGetCheckEverydayLibraryListPacket	*AListPacket=dynamic_cast<CmdGetCheckEverydayLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	/*
	CmdCreateTempCheckEverydayLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempCheckEverydayLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new CheckEverydayLibrary(GetLibType(),GetLayersBase());
		return;
	}
	*/
	CmdLoadCheckEverydayLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadCheckEverydayLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearCheckEverydayLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearCheckEverydayLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteCheckEverydayLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteCheckEverydayLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertCheckEverydayLibraryPacket	*BInsLib=dynamic_cast<CmdInsertCheckEverydayLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(CheckEverydayVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateCheckEverydayLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateCheckEverydayLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(CheckEverydayVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}

	CmdGetCheckEverydayLibraryNamePacket	*CmdGetCheckEverydayLibraryNamePacketVar=dynamic_cast<CmdGetCheckEverydayLibraryNamePacket *>(packet);
	if(CmdGetCheckEverydayLibraryNamePacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	TmpLib(this);
			CmdGetCheckEverydayLibraryNamePacketVar->Success=GetLibraryContainer()->GetLibrary(CmdGetCheckEverydayLibraryNamePacketVar->LibID,TmpLib);
			if(CmdGetCheckEverydayLibraryNamePacketVar->Success==true){
				CmdGetCheckEverydayLibraryNamePacketVar->LibName=TmpLib.GetLibName();
			}
		}
		return;
	}
}

bool	CheckEverydayBase::GeneralDataRelease(int32 Command,void *data)
{
	return AlgorithmBase::GeneralDataRelease(Command,data);
}
void	*CheckEverydayBase::GeneralDataCreate(int32 Command ,void *reqData)
{

	return AlgorithmBase::GeneralDataCreate(Command,reqData);
}
bool	CheckEverydayBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	return AlgorithmBase::GeneralDataLoad(f,Command,data);
}
bool	CheckEverydayBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	return AlgorithmBase::GeneralDataSave(f,Command,data);
}
bool	CheckEverydayBase::GeneralDataReply(int32 Command,void *data)
{
	return AlgorithmBase::GeneralDataReply(Command,data);
}

