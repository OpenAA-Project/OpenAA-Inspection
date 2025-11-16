#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// 他GUIから送信されるコマンド

// 更新要求
// 受信すると、ReviewStructureに問い合わせてNGImageに付与されているFキー情報を取得し
// Fキーに対応したNGImageに含まれるNG箇所の合計を計算
// 基板ごとにどのFキーによるものかを算出
// 縦に基板・NG数、横にNG・F1・F2・～・OKとしてリストを表示する
//  GUICmdReviewUpdateLocal

//////////////////////////////////////
// 送るコマンド(他GUIのパケット)
//
// 

//////////////////////////////////////
// マスタースレーブコマンド
//  GUI共通項目
//   [更新]
//   GUICmdReviewUpdateLocal
// 

