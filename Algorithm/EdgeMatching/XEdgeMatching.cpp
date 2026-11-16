#define _USE_MATH_DEFINES
#include <math.h>
#include "XEdgeMatching.h"
#include "XEdgeMatchingPacket.h"
#include "XDataInLayer.h"
#include "XImageProcess.h"
#include "XCriticalFunc.h"
#include "XDisplaySimPanel.h"

extern const char *sRoot;
extern const char *sName;

//==========================================================================================
// EdgeMatchingInPage
//==========================================================================================
EdgeMatchingInPage::EdgeMatchingInPage(AlgorithmBase *parent)
    : AlgorithmInPagePI(parent)
{
    ModeParallel.ModeParallelExecuteInitialAfterEdit = true;
}

EdgeMatchingInPage::~EdgeMatchingInPage(void)
{
}

AlgorithmItemRoot *EdgeMatchingInPage::CreateItem(int ItemClassType)
{
    EdgeMatchingItem *Item = new EdgeMatchingItem();
    Item->SetParent(this);
    return Item;
}

void	EdgeMatchingInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		EdgeMatchingItem	*BI=(EdgeMatchingItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
void EdgeMatchingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqEdgeMatchingByPoint *ReqEdgeMatchingByPoint = dynamic_cast<CmdReqEdgeMatchingByPoint *>(packet);
	if(ReqEdgeMatchingByPoint!=NULL){
        for (AlgorithmItemPI *k = GetFirstData(); k != NULL; k = k->GetNext()) {
            EdgeMatchingItem *a = dynamic_cast<EdgeMatchingItem *>(k);
            if (a != NULL && a->VMap!=NULL && a->RMap!=NULL) {
                if (a->GetArea().IsInclude(ReqEdgeMatchingByPoint->LocalX, ReqEdgeMatchingByPoint->LocalY) == true) {
                    ReqEdgeMatchingByPoint->ItemID = a->GetID();
					ReqEdgeMatchingByPoint->V = (a->VMap[ReqEdgeMatchingByPoint->LocalY - a->GetArea().GetMinY()])[ReqEdgeMatchingByPoint->LocalX - a->GetArea().GetMinX()];
					ReqEdgeMatchingByPoint->R = (a->RMap[ReqEdgeMatchingByPoint->LocalY - a->GetArea().GetMinY()])[ReqEdgeMatchingByPoint->LocalX - a->GetArea().GetMinX()]; 


                    return;
                }
            }
		}
        ReqEdgeMatchingByPoint->ItemID=-1;
        ReqEdgeMatchingByPoint->V=0;
        ReqEdgeMatchingByPoint->R=0;
        return;
    }

    AddEdgeMatchingPointPacket *AddPointPacket = dynamic_cast<AddEdgeMatchingPointPacket *>(packet);
    if (AddPointPacket != NULL) {
        EdgeMatchingItem *Item = new EdgeMatchingItem();
        Item->SetParent(this);
        Item->SetArea(AddPointPacket->Area);
        Item->SetLibID(AddPointPacket->LibID);

        EdgeMatchingBase *BBase = (EdgeMatchingBase *)GetParentBase();
        AlgorithmLibraryLevelContainer LLib(BBase);
        if (BBase->GetLibraryContainer()->GetLibrary(AddPointPacket->LibID, LLib) == true) {
            EdgeMatchingLibrary *ALib = dynamic_cast<EdgeMatchingLibrary *>(LLib.GetLibrary());
            if (ALib != NULL) {
                ((EdgeMatchingItem *)Item)->GetThresholdW()->FromLibrary(ALib);
            }
        }
        Item->SetManualCreated(true);
        GetParentBase()->ClearManagedCacheLib();

        AppendItem(Item);
        AddPointPacket->RetItemID = Item->GetID();
        return;
    }

    CmdReqEdgeMatchingItemtPack *ReqItemPack = dynamic_cast<CmdReqEdgeMatchingItemtPack *>(packet);
    if (ReqItemPack != NULL) {
        ReqItemPack->Items->RemoveAll();
        for (AlgorithmItemPI *k = GetFirstData(); k != NULL; k = k->GetNext()) {
            EdgeMatchingItem *a = dynamic_cast<EdgeMatchingItem *>(k);
            EdgeMatchingItemList *r = new EdgeMatchingItemList();
            r->Data.Page = GetGlobalPage();
            r->Data.Phase = GetPhaseCode();
            r->Data.ItemID = a->GetID();
            r->Data.LibID = a->GetLibID();
            r->Data.CenterX = a->MasterCx;
            r->Data.CenterY = a->MasterCy;
            r->Data.x1 = a->GetArea().GetMinX();
            r->Data.y1 = a->GetArea().GetMinY();
            r->Data.x2 = a->GetArea().GetMaxX();
            r->Data.y2 = a->GetArea().GetMaxY();
            ReqItemPack->Items->AppendList(r);
        }
        return;
    }
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		EdgeMatchingItem *Item=(EdgeMatchingItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);

			Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate 
						,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);

			int32     DividedAreaNumber;
			QBuffer	Buff(&CmdAlgoSimulateVar->Something);
			Buff.open(QIODevice::ReadOnly);
			if(::Load(&Buff,DividedAreaNumber)==true){
				if(DividedAreaNumber>=0){
					EdgeMatchingItem::DividedArea	*a=Item->DividedAreas[DividedAreaNumber];
					QColor	Col=Qt::magenta;
					Col.setAlpha(70);
					if(a!=NULL){
						a->Area.DrawAlpha(0,0, CmdAlgoSimulateVar->Image,Col.rgba()
											,CmdAlgoSimulateVar->ZoomRate 
											,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
					}
				}
			}
		}
		return;
	}
}

//==========================================================================================
// EdgeMatchingBase
//==========================================================================================
EdgeMatchingBase::EdgeMatchingBase(LayersBase *Base)
    : AlgorithmBase(Base)
{
    ColorArea = Qt::darkYellow;
    ColorAreaSelected = Qt::yellow;
    ColorAreaActive = Qt::red;
    ColorPoint = Qt::darkGreen;
    ColorPointSelected = Qt::green;
    ColorPointActive = Qt::red;
    AlphaLevel = 100;

    SetParam(&ColorArea         , "Color", "ColorArea"          , "EdgeMatching Area color");
    SetParam(&ColorAreaSelected , "Color", "ColorAreaSelected"  , "Selected EdgeMatching Area color");
    SetParam(&ColorAreaActive   , "Color", "ColorAreaActive"    , "Active EdgeMatching Area color");
    SetParam(&ColorPoint        , "Color", "ColorPoint"         , "EdgeMatching Point color");
    SetParam(&ColorPointSelected, "Color", "ColorPointSelected" , "Selected EdgeMatching Point color");
    SetParam(&ColorPointActive  , "Color", "ColorPointActive"   , "Active EdgeMatching Point color");
    SetParam(&AlphaLevel        , "Color", "AlphaLevel"         , "EdgeMatching transparent level");
}

AlgorithmDrawAttr *EdgeMatchingBase::CreateDrawAttr(void)
{
    return new EdgeMatchingDrawAttr(GetLayersBase(), ColorArea, ColorAreaSelected, ColorAreaActive);
}

void EdgeMatchingBase::MakeReportedTopics(ReportedTopicContainer &RetContainer) const
{
    for (int page = 0; page < GetPageNumb(); page++) {
        ReportedTopic *r = new ReportedTopic(QString("P:") + QString::number(page), QString::number(0));
        RetContainer.AppendList(r);
    }
}

void EdgeMatchingBase::TransmitDirectly(GUIDirectMessage *packet)
{
    // ライブラリ操作や名称取得のパケット処理（EdgeMatchingBase::TransmitDirectlyを参考に実装）
    CmdGetEdgeMatchingLibraryNamePacket *CmdGetName = dynamic_cast<CmdGetEdgeMatchingLibraryNamePacket *>(packet);
    if (CmdGetName != NULL) {
        AlgorithmLibraryLevelContainer LibData(this);
        if (GetLibraryContainer() != NULL) {
            CmdGetName->Success = GetLibraryContainer()->GetLibrary(CmdGetName->LibID, LibData);
            CmdGetName->LibName = LibData.GetLibName();
        }
        return;
    }

    CmdCreateTempEdgeMatchingItemPacket *CmdCreateTempItem = dynamic_cast<CmdCreateTempEdgeMatchingItemPacket *>(packet);
    if (CmdCreateTempItem != NULL) {
        CmdCreateTempItem->Point = new EdgeMatchingItem();
        return;
    }

	CmdCreateTempEdgeMatchingLibraryPacket *CmdCreateTempLib = dynamic_cast<CmdCreateTempEdgeMatchingLibraryPacket *>(packet);
    if (CmdCreateTempLib != NULL) {
        CmdCreateTempLib->Point = new AlgorithmLibraryLevelContainer(this);
        return;
	}
	CmdGetEdgeMatchingLibraryListPacket *CmdGetLibList = dynamic_cast<CmdGetEdgeMatchingLibraryListPacket *>(packet);
    if (CmdGetLibList != NULL) {
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),CmdGetLibList->LibFolderID 
												,CmdGetLibList->AList);
		}
        return;
	}
	CmdLoadEdgeMatchingLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadEdgeMatchingLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdClearEdgeMatchingLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearEdgeMatchingLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteEdgeMatchingLibraryPacket 	*BDeleteLib=dynamic_cast<CmdDeleteEdgeMatchingLibraryPacket  *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdInsertEdgeMatchingLibraryPacket	*BInsLib=dynamic_cast<CmdInsertEdgeMatchingLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(EdgeMatchingVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateEdgeMatchingLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateEdgeMatchingLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(EdgeMatchingVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
}
QString	EdgeMatchingBase::GetNameByCurrentLanguage(void)
{
	return "エッジマッチング";
}
bool	EdgeMatchingBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==EdgeMatchingReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==EdgeMatchingSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*EdgeMatchingBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==EdgeMatchingReqTryThresholdCommand){
		return new EdgeMatchingReqTryThreshold();
	}
	else if(Command==EdgeMatchingSendTryThresholdCommand){
		EdgeMatchingSendTryThreshold	*pSend=new EdgeMatchingSendTryThreshold();
		if(reqData!=NULL){
			EdgeMatchingReqTryThreshold	*req=(EdgeMatchingReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	EdgeMatchingBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==EdgeMatchingReqTryThresholdCommand){
		EdgeMatchingReqTryThreshold	*p=(EdgeMatchingReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==EdgeMatchingSendTryThresholdCommand){
		EdgeMatchingSendTryThreshold	*p=(EdgeMatchingSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	EdgeMatchingBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==EdgeMatchingReqTryThresholdCommand){
		EdgeMatchingReqTryThreshold	*p=(EdgeMatchingReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==EdgeMatchingSendTryThresholdCommand){
		EdgeMatchingSendTryThreshold	*p=(EdgeMatchingSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	EdgeMatchingBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==EdgeMatchingReqTryThresholdCommand){
		EdgeMatchingReqTryThreshold	*p=(EdgeMatchingReqTryThreshold *)data;
		return true;
	}
	else if(Command==EdgeMatchingSendTryThresholdCommand){
		EdgeMatchingSendTryThreshold	*p=(EdgeMatchingSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

//==========================================================================================

EdgeMatchingReqTryThreshold::EdgeMatchingReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	EdgeMatchingItemID=-1;
}
bool	EdgeMatchingReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,EdgeMatchingItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	EdgeMatchingReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,EdgeMatchingItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

EdgeMatchingSendTryThreshold::EdgeMatchingSendTryThreshold(void)
{
	Result			=new ResultInItemPI();	//ResultInItemPI();
	ResultValue		=0;
	ResultDx		=0;
	ResultDy		=0;
	ResultRotation	=0;
	ShiftByGlobalX	=0;
	ShiftByGlobalY	=0;
	Error			=0;
}

EdgeMatchingSendTryThreshold::EdgeMatchingSendTryThreshold(const EdgeMatchingSendTryThreshold &src)
{
	Result					=new ResultInItemPI();	//ResultInItemPI();
	ResultValue		= src.ResultValue;
	ResultDx		= src.ResultDx;
	ResultDy		= src.ResultDy;
	ResultRotation	= src.ResultRotation;
	ShiftByGlobalX	= src.ShiftByGlobalX;
	ShiftByGlobalY	= src.ShiftByGlobalY;
	Error			=src.Error					;
	CoefList		= src.CoefList;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
}

EdgeMatchingSendTryThreshold::~EdgeMatchingSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
	
EdgeMatchingSendTryThreshold &EdgeMatchingSendTryThreshold::operator=(const EdgeMatchingSendTryThreshold &src)
{
	ResultValue		= src.ResultValue;
	ResultDx		= src.ResultDx;
	ResultDy		= src.ResultDy;
	ResultRotation	= src.ResultRotation;
	ShiftByGlobalX	= src.ShiftByGlobalX;
	ShiftByGlobalY	= src.ShiftByGlobalY;
	Error			=src.Error					;
	CoefList		= src.CoefList;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
	return *this;
}

bool	EdgeMatchingSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ResultValue)==false)
		return false;
	if(::Save(f,ResultDx)==false)
		return false;
	if(::Save(f,ResultDy)==false)
		return false;
	if(::Save(f,ResultRotation)==false)
		return false;
	if(::Save(f,ShiftByGlobalX)==false)
		return false;
	if(::Save(f,ShiftByGlobalY)==false)
		return false;
	if(::Save(f,Error)==false)
		return false;
	if(CoefList.Save(f)==false)
		return false;

	return true;
}
bool	EdgeMatchingSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
		
	if(::Load(f,ResultValue)==false)
		return false;
	if(::Load(f,ResultDx)==false)
		return false;
	if(::Load(f,ResultDy)==false)
		return false;
	if(::Load(f,ResultRotation)==false)
		return false;
	if(::Load(f,ShiftByGlobalX)==false)
		return false;
	if(::Load(f,ShiftByGlobalY)==false)
		return false;
	if(::Load(f,Error)==false)
		return false;
	if(CoefList.Load(f)==false)
		return false;
	return true;
}

void	EdgeMatchingSendTryThreshold::ConstructList(EdgeMatchingReqTryThreshold *reqPacket,EdgeMatchingBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	EdgeMatchingInPage		*BP=(EdgeMatchingInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		EdgeMatchingItem		*BI=(EdgeMatchingItem *)BP->SearchIDItem(reqPacket->EdgeMatchingItemID);
		if(BI!=NULL){
			Calc(&reqPacket->Threshold,BI,Base);
		}
	}
}
void	EdgeMatchingSendTryThreshold::Calc(EdgeMatchingItem *Target,EdgeMatchingItem *Src,EdgeMatchingBase *Base)
{
	EdgeMatchingInPage		*BP=(EdgeMatchingInPage *)Base->GetPageData(Src->GetPage());
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());

	int	SaveMaxInspectMilisec	=Base->GetParamGlobal()->MaxInspectMilisec;
	Base->GetParamGlobal()->MaxInspectMilisec	=99999999;

	Target->SetParent(Src->GetParent());

	Target->SetLibID(Src->GetLibID());
	Target->SetMasterNo(Src->GetMasterNo());
	Target->SetArea(Src->GetArea());
	EdgeMatchingThreshold			*WThr=Target->GetThresholdW();
	const	EdgeMatchingThreshold	*RThr=Src	->GetThresholdR();

	ExecuteInitialAfterEditInfo DummyEInfo;
	DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
	Target->ExecuteInitialAfterEdit	(0,0,Result,DummyEInfo);

	Target->DividedAreas=Src->DividedAreas;
	Target->AVector	=Src->AVector;
	Target->MapXLen = Src->MapXLen;
	Target->MapYLen = Src->MapYLen;
	Target->VMap = new float *[Target->MapYLen];
	for(int y=0;y<Target->MapYLen;y++){
		Target->VMap[y]=new float[Target->MapXLen];
		memcpy(Target->VMap[y],Src->VMap[y],sizeof(float)*Target->MapXLen);
	}
	Target->RMap = new float *[Target->MapYLen];
	for(int y=0;y<Target->MapYLen;y++){
		Target->RMap[y]=new float[Target->MapXLen];
		memcpy(Target->RMap[y],Src->RMap[y],sizeof(float)*Target->MapXLen);
	}

	Target->AdoptedLayer = Src->AdoptedLayer;
	Target->TargetMapXLen	=Src->TargetMapXLen;
	Target->TargetMapYLen	=Src->TargetMapYLen;
	Target->TargetMap = new float *[Target->TargetMapYLen];
	for(int y=0;y<Target->TargetMapYLen;y++){
		Target->TargetMap[y] = new float[Target->TargetMapXLen];
		memcpy(Target->TargetMap[y],Src->TargetMap[y],sizeof(float)*Target->TargetMapXLen);
	}
	Target->TargetX1=Src->TargetX1;
	Target->TargetY1=Src->TargetY1;

	Target->AA	=Src->AA;
	Target->A	=Src->A;
	Target->MasterCx	=Src->MasterCx;
	Target->MasterCy	=Src->MasterCy;
	BP->GetDataInPage()->ClearNGCounterWithMutex();

	Target->ExecuteStartByInspection	(0,0,Result);
	Target->ExecuteProcessing			(10000,0,Result);

	ResultValue		=Result->GetResultDouble();
	ResultDx		=Target->ResultDx		;
	ResultDy		=Target->ResultDy		;	//Calculated position
	ResultRotation	=Target->ResultRotation	;
	ShiftByGlobalX	=Target->ShiftByGlobalX	;
	ShiftByGlobalY	=Target->ShiftByGlobalY	;
	CoefList.RemoveAll();
	for(EdgeMatchingItem::DividedArea *a=Target->DividedAreas.GetFirst();a!=NULL;a=a->GetNext()){
		CoefList.Add(a->ResultCoef);
	}

	Base->GetParamGlobal()->MaxInspectMilisec	=SaveMaxInspectMilisec	;
}