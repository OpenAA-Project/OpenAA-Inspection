/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBsearch.h
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#ifndef XBSearchH
#define XBSearchH
#include "XTypeDef.h"
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/


void *EqualSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      同じ要素を探す
//      これは key に等しいデータが複数あるとき、どのデータがリターンするかわからない

void *EqualLeastSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      Bn-1 < Bn <= key となる Bn を探す
//      key に等しいものが複数あるとき、その中の最もbaseに近いものが返る
//      key に等しいデータは存在していなくてはならない
//      このようなデータが存在しないとき NULL が返る

void *EqualGreatestSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      key <= Bn < Bn+1 となる Bn を探す
//      key に等しいものが複数あるとき、その中の最もbaseから遠いものが返る
//      key に等しいデータは存在していなくてはならない
//      このようなデータが存在しないとき NULL が返る

void *LessSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      Bn-1 < Bn <= key となる Bn を探す
//      key に等しいものが複数あるとき、その中の最もbaseに近いものが返る
//      key に等しいデータは存在しなくてもよい
//      このようなデータが存在しないとき NULL が返る

void *GreaterSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      key <= Bn < Bn+1 となる Bn を探す
//      key に等しいものが複数あるとき、その中の最もbaseから遠いものが返る
//      key に等しいデータは存在しなくてもよい
//      このようなデータが存在しないとき NULL が返る

void QSort(void *base, unsigned num, unsigned width, int (*comp)(const void *a, const void *b, const void *reference),void *sortref);

#endif
