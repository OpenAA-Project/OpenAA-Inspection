#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

// NGリストの更新要求
// 保持してあるRefHistoryからNG情報を取得してリストを作成して表示する
// GUICmdReviewUpdateLocal 共通にある

// NG画像の選択要求
// セットされたx,yから近いNG画像を選択する
// ただし、ある程度まで近くないと無視される
class GUICmdSelectNearNG : public GUIDirectMessage
{
public:
	// Send
	int x;
	int y;

	// Recieve
	bool Ret; // 正常終了ならtrue
	bool Ignored; // 指定した近くのNG箇所が無くて要求が無視された場合true
public:
	bool Save(QIODevice *f){ return true; };
	bool Load(QIODevice *f){ return true; };
public:
	GUICmdSelectNearNG(LayersBase *Base)
		:GUIDirectMessage(Base),x(-1),y(-1),Ret(false),Ignored(false){};
};

//////////////////////////////////////
// 送るコマンド(他GUIのパケット)

// ・ShowHistoryListForReview
//   [履歴リストの移動要求]
//    GUICmdReqMoveHistoryList
//
// ・NGImageForReview
//   [NGImageの更新要求]
//    GUICmdReqSetNGImage
//
// ・WholeImageForReview
//   [確認中のNG画像情報の送信]
//    GUICmdReqSetNGImagePos


// //////////////////////////////////////
// マスタースレーブコマンド
//  GUI共通項目
//   [更新] -> NGPosListの更新
//   GUICmdReviewUpdate
// 

/*
// 送信側
class GUIReqXXX : public GUICmdPacketBase
{
public:
	// 送信するデータ
	int data_req;
	// 受信するデータ
	bool Ret;
public:
	GUIReqXXX(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

public:
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};