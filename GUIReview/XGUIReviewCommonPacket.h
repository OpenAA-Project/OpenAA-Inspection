#pragma once

#include "XDLLOnly.h"
#include "XGeneralFunc.h"

#include "XGUIReviewGlobal.h"
#include "XReviewCommon.h"

// ReviewのGUIへの共通パケット
// ReviewGUIのTransmitDirectryで各々定義する

// ローカルパケット
// 
// 初期化要求
// 
//// 大きな変更をした時(マスターデータを読み込んだり、ロットを変更したりしたときなど)に、Reviewアルゴリズムのデータへポインタ参照している場合
//// deleteなどで消去したインスタンスへアクセスさせないための初期化命令パケット
//class GUICmdReviewInitializeLocal : public GUIDirectMessage
//{
//public:
//	bool Ret;
//public:
//	bool Save(QIODevice *f){ ::Save(f, Ret); return true; };
//	bool Load(QIODevice *f){ ::Load(f, Ret); return true; };
//public:
//	GUICmdReviewInitializeLocal(LayersBase *Base)
//		:GUIDirectMessage(Base),Ret(false){};
//};

// 更新要求
class GUICmdReviewUpdateLocal : public GUIDirectMessage
{
public:
	// Recieve
	bool Ret;
public:
	GUICmdReviewUpdateLocal(LayersBase *Base)
		:GUIDirectMessage(Base),Ret(false){};
};

// フォーカスを移す
class GUICmdSetFocus : public GUIDirectMessage
{
public:
	GUICmdSetFocus(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// CurrentNGNailを変更する
class GUICmdSetCurrentNGNail : public GUIDirectMessage
{
public:
	// Send
	int GlobalIndex;
	// Recieve
	bool Ret;
public:
	GUICmdSetCurrentNGNail(LayersBase *Base)
		:GUIDirectMessage(Base),GlobalIndex(-1){};
};

class	NGNailItemRef;
class	GUICmdReqCurrentNailItem : public GUIDirectMessage
{
public:
	// Send
	NGNailItemRef		*NailIndex;
	Review::SideType	Side;
public:
	GUICmdReqCurrentNailItem(LayersBase *Base)
		:GUIDirectMessage(Base){};
};


class GUICmdSetCurrentNGNailPageTop : public GUIDirectMessage
{
public:
	Review::SideType	Side;
	QString	PieceName;
	// Recieve
	bool Ret;
public:
	GUICmdSetCurrentNGNailPageTop(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

class GUICmdSetCurrentFocusOnNail : public GUIDirectMessage
{
public:
	Review::SideType	Side;
	QString	PieceName;
	// Recieve
	bool Ret;
public:
	GUICmdSetCurrentFocusOnNail(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

class GUICmdReqAreaList : public GUIDirectMessage
{
public:
	Review::SideType	Side;
	QStringList	PieceList;

	bool Ret;
public:
	GUICmdReqAreaList(LayersBase *Base)
		:GUIDirectMessage(Base){};
};


// 履歴が変更されたことを通知する
class GUICmdUpdateCurrentHistory : public GUIDirectMessage
{
public:
	GUICmdUpdateCurrentHistory(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

class GUICmdUpdateCurrentLot : public GUIDirectMessage
{
public:
	GUICmdUpdateCurrentLot(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// NGNailが変更されたことを通知する
class GUICmdUpdateCurrentNGNail : public GUIDirectMessage
{
public:
	GUICmdUpdateCurrentNGNail(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// マスタースレーブ間通信パケット

// 送信のみパケット

//// 初期化要求 : 表示しているデータを初期化する -> 主に初期化関数の実行を促す
//class GUICmdReviewInitialize : public GUICmdPacketBase
//{
//public:
//	bool Ret;
//public:
//	bool Save(QIODevice *f){ ::Save(f, Ret); return true; };
//	bool Load(QIODevice *f){ ::Load(f, Ret); return true; };
//public:
//	GUICmdReviewInitialize(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
//};

// 更新要求 : RviewStructureからデータを再取得して保持しているデータを更新させる -> 主に初期化関数 > 更新を実行させる
class GUICmdReviewUpdate : public GUICmdPacketBase
{
public:
	bool Ret;
public:
	bool Save(QIODevice *f){ ::Save(f, Ret); return true; };
	bool Load(QIODevice *f){ ::Load(f, Ret); return true; };
public:
	GUICmdReviewUpdate(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
};

class GUICmdSetEnable : public GUIDirectMessage
{
public:
	bool enable;
public:
	GUICmdSetEnable(LayersBase *Base)
		:GUIDirectMessage(Base),enable(true){};
};
