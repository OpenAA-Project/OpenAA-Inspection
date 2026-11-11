#define _USE_MATH_DEFINES
#include <math.h>
#include "XEdgeMatching.h"
#include "XEdgeMatchingPacket.h"
#include "XDataInLayer.h"
#include "XImageProcess.h"

extern const char *sRoot;
extern const char *sName;

AAAAAAA

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

void EdgeMatchingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
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
    // ライブラリ操作や名称取得のパケット処理（AlignmentShiftRotationBase::TransmitDirectlyを参考に実装）
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
}