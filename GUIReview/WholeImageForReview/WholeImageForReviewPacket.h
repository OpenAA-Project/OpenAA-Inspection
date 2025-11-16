
#ifndef WHOLEIMAGEFORREVIEWPACKET_H
#define WHOLEIMAGEFORREVIEWPACKET_H

#include "wholeimageforreview_global.h"

#include "XDLLOnly.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewCommon.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

// マスター画像の更新要求
class GUICmdLoadMasterImage : public GUIDirectMessage
{
public:
	// Send
	Review::SideType side;
	// Recieve
	bool Ret;
public:
	GUICmdLoadMasterImage(LayersBase *Base)
		:GUIDirectMessage(Base),side(Review::Front),Ret(false){};
};

class GUICmdLockDrawZoom : public GUIDirectMessage
{
public:
	// Send
	bool doLock;// trueでロック, falseでアンロック
	// Recieve
	bool Ret;
public:
	GUICmdLockDrawZoom(LayersBase *Base)
		:GUIDirectMessage(Base),doLock(true),Ret(false){};
};

//class GUICmdSetHistory : public GUIDirectMessage
//{
//public:
//	// Send
//	HistoryIndex FrontHistoryPtr;
//	HistoryIndex BackHistoryPtr;
//	// Recieve
//	bool Ret;
//public:
//	GUICmdSetHistory(LayersBase *Base)
//		:GUIDirectMessage(Base),FrontHistoryPtr(NULL),BackHistoryPtr(NULL),Ret(false){};
//};

//class	GUICmdReqUpdateHisroty : public GUIDirectMessage
//{
//public:
//	// Recieve
//	bool Ret;
//public:
//	GUICmdReqUpdateHisroty(LayersBase *Base)
//		:GUIDirectMessage(Base),Ret(false){};
//};

class GUICmdSetNGNailDrawType : public GUIDirectMessage
{
public:
	// Send
	QRect	*NGImageSizePtr;
	QColor	*defaultColorPtr;
	QColor	*currentColorPtr;
	bool	redraw;
	// Recieve
	bool Ret;
public:
	GUICmdSetNGNailDrawType(LayersBase *Base)
		:GUIDirectMessage(Base),NGImageSizePtr(NULL),defaultColorPtr(NULL),currentColorPtr(NULL),redraw(false),Ret(false){};
};

class GUICmdSetCurrentNGView : public GUIDirectMessage
{
public:
	bool visible;
	bool redraw;
	bool Ret;
public:
	GUICmdSetCurrentNGView(LayersBase *Base)
		:GUIDirectMessage(Base),visible(true),redraw(false),Ret(false){};
};

class GUICmdUpdateWholeImage : public GUIDirectMessage
{
public:
	GUICmdUpdateWholeImage(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

//////////////////////////////////////
// 送るコマンド(他GUIのパケット)

// ・NGImageListForReview
//   [クリックした位置の近くにあるNG画像を選択するためのクリック位置の送信]
//   GUICmdSelectNGWithPosition



#endif