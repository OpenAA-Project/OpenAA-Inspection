#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"
#include "../XGUIReviewCommonPacket.h"

//////////////////////////////////
// 他GUIから送信されるコマンド
//
// ロットを表示させる
// 
class GUICmdReviewLotList : public GUIDirectMessage
{
public:
	// Send
	Review::SideType side;
	LotInfoList	lotList;

	int MasterCode;
	int MachineID;

	// Recieve
	bool Ret;

public:
	bool Save(QIODevice *f);
	bool Load(QIODevice *f);

public:
	GUICmdReviewLotList(LayersBase *base):GUIDirectMessage(base),side(Review::Front),lotList(),MasterCode(-1),MachineID(-1),Ret(false){};
	GUICmdReviewLotList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase),side(Review::Front),lotList(),MasterCode(-1),MachineID(-1),Ret(false){};
};

class GUICmdSetCancelButtonVisible : public GUIDirectMessage
{
public:
	bool visible;
public:
	GUICmdSetCancelButtonVisible(LayersBase *base):GUIDirectMessage(base),visible(true){};
};