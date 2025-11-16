#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

class GUICmdUpdateCurrentHistoryChecked : public GUIDirectMessage
{
public:
	GUICmdUpdateCurrentHistoryChecked(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

//class GUICmdUpdateCurrentHistory : public GUIDirectMessage
//{
//public:
//	GUICmdUpdateCurrentHistory(LayersBase *Base)
//		:GUIDirectMessage(Base){};
//};
//
//class GUICmdUpdateCurrentHistoryChecked : public GUIDirectMessage
//{
//public:
//	GUICmdUpdateCurrentHistoryChecked(LayersBase *Base)
//		:GUIDirectMessage(Base){};
//};


//////////////////////////////////////
// 送るコマンド(他GUIのパケット)
//
// ・NGImageListForReview
//   [履歴リストの行の変更よるリスト更新要求]
//    GUICmdReqShowNGImageList
//