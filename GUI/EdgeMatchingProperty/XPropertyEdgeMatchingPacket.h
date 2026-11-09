#pragma once

#include "XGUIPacketForDLL.h"
#include "XEdgeMatching.h"
#include "XEdgeMatchingPacket.h"

class CmdEdgeMatchingDrawModePacket : public GUIDirectMessage
{
public:
    bool DrawModeArea;
    bool DrawModeEdge;
    bool DrawModeDirection;

    CmdEdgeMatchingDrawModePacket(LayersBase *base) : GUIDirectMessage(base) {}
    CmdEdgeMatchingDrawModePacket(GUICmdPacketBase *gbase) : GUIDirectMessage(gbase) {}
};

class EdgeMatchingImagePanel;

class CmdEdgeMatchingDrawEnd : public GUIDirectMessage
{
public:
    FlexArea Area;
    IntList LayerList;
    EdgeMatchingImagePanel *ImagePanelPoint;

    CmdEdgeMatchingDrawEnd(LayersBase *base) : GUIDirectMessage(base) { ImagePanelPoint = NULL; }
    CmdEdgeMatchingDrawEnd(GUICmdPacketBase *gbase) : GUIDirectMessage(gbase) { ImagePanelPoint = NULL; }
};

class GUICmdAddEdgeMatching : public GUICmdPacketBase
{
public:
    int LibID;
    FlexArea Area;

    GUICmdAddEdgeMatching(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage = -1);

    virtual bool Load(QIODevice *f);
    virtual bool Save(QIODevice *f);

    virtual void Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};

class GUICmdSendEdgeMatching : public GUICmdPacketBase
{
public:
    int ItemID;

    GUICmdSendEdgeMatching(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage = -1);

    virtual bool Load(QIODevice *f);
    virtual bool Save(QIODevice *f);

    virtual void Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName) {}
};

class GUICmdReqModifyEdgeMatching : public GUICmdPacketBase
{
public:
    int ItemID;

    GUICmdReqModifyEdgeMatching(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage = -1);

    virtual bool Load(QIODevice *f);
    virtual bool Save(QIODevice *f);

    virtual void Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};

//==============================================================================

class GUICmdReqEdgeMatchingItemList : public GUICmdPacketBase
{
public:
    int Phase;
    GUICmdReqEdgeMatchingItemList(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage = -1);

    virtual bool Load(QIODevice *f);
    virtual bool Save(QIODevice *f);
    virtual void Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};

class GUICmdSendEdgeMatchingItemList : public GUICmdPacketBase
{
public:
    EdgeMatchingItemListPack ItemList;

    GUICmdSendEdgeMatchingItemList(LayersBase *Base, const QString &emitterRoot, const QString &emitterName, int globalPage = -1);
    virtual bool Load(QIODevice *f);
    virtual bool Save(QIODevice *f);
    virtual void Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName) {}
};