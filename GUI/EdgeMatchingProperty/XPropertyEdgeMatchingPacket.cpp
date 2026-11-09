#include "EdgeMatchingPropertyForm.h"
#include "XGeneralFunc.h"
#include "SelectLibFolderDialog.h"
#include "XEdgeMatchingPacket.h"
#include "XDisplayImagePacket.h"
#include "XPropertyEdgeMatchingPacket.h"

extern const char *sRoot;
extern const char *sName;

//==============================================================================
GUICmdAddEdgeMatching::GUICmdAddEdgeMatching(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
    : GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool GUICmdAddEdgeMatching::Load(QIODevice *f)
{
    if (::Load(f, LibID) == false)
        return false;
    if (Area.Load(f) == false)
        return false;
    return true;
}

bool GUICmdAddEdgeMatching::Save(QIODevice *f)
{
    if (::Save(f, LibID) == false)
        return false;
    if (Area.Save(f) == false)
        return false;
    return true;
}

void GUICmdAddEdgeMatching::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
    GUICmdSendEdgeMatching *SendBack = GetSendBack(GUICmdSendEdgeMatching, GetLayersBase(), EmitterRoot, EmitterName, localPage);

    AlgorithmBase *AlignBase = GetLayersBase()->GetAlgorithmBase("Basic", "EdgeMatching");
    if (AlignBase == NULL)
        return;
    AlgorithmInPageRoot *AP = AlignBase->GetPageData(localPage);
    if (AP == NULL)
        return;

    AddEdgeMatchingPointPacket DPacket(GetLayersBase());
    DPacket.LibID = LibID;
    DPacket.Area  = Area;
    AP->TransmitDirectly(&DPacket);

    SendBack->ItemID = DPacket.RetItemID;
    
    SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
    CloseSendBack(SendBack);
}

//==============================================================================
GUICmdSendEdgeMatching::GUICmdSendEdgeMatching(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
    : GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool GUICmdSendEdgeMatching::Load(QIODevice *f)
{
    if (::Load(f, ItemID) == false)
        return false;
    return true;
}

bool GUICmdSendEdgeMatching::Save(QIODevice *f)
{
    if (::Save(f, ItemID) == false)
        return false;
    return true;
}

//==============================================================================
GUICmdReqModifyEdgeMatching::GUICmdReqModifyEdgeMatching(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage)
    : GUICmdPacketBase(Base, emitterRoot, emitterName, typeid(this).name(), globalPage)
{
}

bool GUICmdReqModifyEdgeMatching::Load(QIODevice *f)
{
    if (::Load(f, ItemID) == false)
        return false;
    return true;
}

bool GUICmdReqModifyEdgeMatching::Save(QIODevice *f)
{
    if (::Save(f, ItemID) == false)
        return false;
    return true;
}

void GUICmdReqModifyEdgeMatching::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
}

//==============================================================================
GUICmdReqEdgeMatchingItemList::GUICmdReqEdgeMatchingItemList(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage)
    : GUICmdPacketBase(Base, emitterRoot, emitterName, typeid(this).name(), globalPage)
{
}

bool GUICmdReqEdgeMatchingItemList::Load(QIODevice *f)
{
    if (::Load(f, Phase) == false) return false;
    return true;
}

bool GUICmdReqEdgeMatchingItemList::Save(QIODevice *f)
{
    if (::Save(f, Phase) == false) return false;
    return true;
}

void GUICmdReqEdgeMatchingItemList::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
    GUICmdSendEdgeMatchingItemList *SendBack = GetSendBack(GUICmdSendEdgeMatchingItemList, GetLayersBase(), EmitterRoot, EmitterName, localPage);

    AlgorithmBase *AlignBase = GetLayersBase()->GetAlgorithmBase("Basic", "EdgeMatching");
    if (AlignBase == NULL)
        return;
    AlgorithmInPageInOnePhase *Ph = AlignBase->GetPageDataPhase(Phase);
    if (Ph == NULL)
        return;
    AlgorithmInPageRoot *AP = Ph->GetPageData(localPage);
    if (AP == NULL)
        return;

    CmdReqEdgeMatchingItemtPack DPacket(GetLayersBase());
    DPacket.Items = &SendBack->ItemList;
    AP->TransmitDirectly(&DPacket);

    SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
    CloseSendBack(SendBack);
}

//==============================================================================
GUICmdSendEdgeMatchingItemList::GUICmdSendEdgeMatchingItemList(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage)
    : GUICmdPacketBase(Base, emitterRoot, emitterName, typeid(this).name(), globalPage)
{
}

bool GUICmdSendEdgeMatchingItemList::Load(QIODevice *f)
{
    if (ItemList.Load(f) == false)
        return false;
    return true;
}

bool GUICmdSendEdgeMatchingItemList::Save(QIODevice *f)
{
    if (ItemList.Save(f) == false)
        return false;
    return true;
}

