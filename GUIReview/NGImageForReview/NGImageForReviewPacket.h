#ifndef NGIMAGEFORREVIEWPACKET_H_
#define NGIMAGEFORREVIEWPACKET_H_

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

// NG画像の更新表示要求
// NG画像と含まれるNG箇所のリストが含まれたクラスインスタンスのポインタから、NG画像とマスター画像を更新する
class GUICmdReqSetNGImage : public GUIDirectMessage
{
public:
	// Send
	NGNailIndex NGNailPtr;
	Review::SideType side;// 全体画像判断用
	
	// Recieve
	bool Ret;
public:
	GUICmdReqSetNGImage(LayersBase *Base)
		:GUIDirectMessage(Base),Ret(false){};
};

class GUICmdExchangeNGVisible : public GUIDirectMessage
{
public:
	GUICmdExchangeNGVisible(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// マスター画像の取得要求
// マスターデータが読み込まれたときに送信される
// このコマンドが送られてきたとき、sideの側のマスター画像の一部を要求する
//class GUICmdReqSetMasterImage : public GUIDirectMessage
//{
//public:
//	// Send
//	Review::SideType side;// 全体画像判断用
//	// Recieve
//	bool Ret;
//public:
//	bool Save(QIODevice *f){ return true; };
//	bool Load(QIODevice *f){ return true; };
//public:
//	GUICmdReqSetMasterImage(LayersBase *Base)
//		:GUIDirectMessage(Base),Ret(false){};
//};

//////////////////////////////////////
// 送るコマンド(他GUIのパケット)

// ・WholeImageForReview
//   [現在確認中のマスター画像の位置の情報を送る]
//    GUICmdReqSetCurrentPosOnMaster
//

//////////////////////////////////////
// マスタースレーブコマンド
//  GUI共通項目
//   何もしない(NGImageListForReviewのパケット待ち)
// 

#endif