#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

// 送られた場合、ReviewStructureに問い合わせてNG画像一覧を取得する
class GUICmdReqUpdateNGList : public GUIDirectMessage
{
public:
	// Send

	// Recieve
	bool Ret;
public:
	GUICmdReqUpdateNGList(LayersBase *Base)
		:GUIDirectMessage(Base),Ret(false){};
};

// 特定のNGImageを選択するためのパケット
class GUICmdReqSelectNGNailItem : public GUIDirectMessage
{
public:
	// Send
	NGNailIndex targetNG; // ターゲットのNGImageインスタンス(のポインタ)

	// Recieve
	bool Ret;
public:
	GUICmdReqSelectNGNailItem(LayersBase *Base)
		:GUIDirectMessage(Base),Ret(false),targetNG(NULL){};
};


//////////////////////////////////////
// 送るコマンド(他GUIのパケット)
//
// ・ShowHistoryListForReview
//   [履歴リストの移動要求]
//    GUICmdReqMoveHistoryList
// 