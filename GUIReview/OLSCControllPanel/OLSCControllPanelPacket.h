#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"

#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

// 無し

//////////////////////////////////////
// 送るコマンド(他GUIのパケット)

// 無し

//////////////////////////////////////
// マスタースレーブコマンド
//  GUI共通項目
//   [更新] -> NGPosListの更新
//   GUICmdReviewUpdateLocal
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

// 受信側
class GUIAckXXX : public GUICmdPacketBase
{
public:
	// 送信するデータ
	int data_ack;
	// 受信するデータ
	bool Ret;
public:
	GUIAckXXX(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

public:
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
*/