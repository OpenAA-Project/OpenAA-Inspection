/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */




#ifndef XBSearchH
#define XBSearchH
#include "XTypeDef.h"


void *EqualSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      �����v�f���T��
//      ������ key �ɓ������f�[�^�����������Ƃ��A�ǂ̃f�[�^�����^�[�����邩�킩���Ȃ�

void *EqualLeastSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      Bn-1 < Bn <= key �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base�ɋ߂����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ă��Ȃ��Ă͂Ȃ��Ȃ�
//      ���̂悤�ȃf�[�^�����݂��Ȃ��Ƃ� NULL ���Ԃ�

void *EqualGreatestSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      key <= Bn < Bn+1 �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base���牓�����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ă��Ȃ��Ă͂Ȃ��Ȃ�
//      ���̂悤�ȃf�[�^�����݂��Ȃ��Ƃ� NULL ���Ԃ�

void *LessSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      Bn-1 < Bn <= key �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base�ɋ߂����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ȃ��Ă��悢
//      ���̂悤�ȃf�[�^�����݂��Ȃ��Ƃ� NULL ���Ԃ�

void *GreaterSearch(const void *key , const void *base , unsigned int numb , int width , int( *sortFunc)(const void *e1, const void *e2));
//      key <= Bn < Bn+1 �ƂȂ� Bn ���T��
//      key �ɓ��������̂����������Ƃ��A���̒��̍ł�base���牓�����̂��Ԃ�
//      key �ɓ������f�[�^�͑��݂��Ȃ��Ă��悢
//      ���̂悤�ȃf�[�^�����݂��Ȃ��Ƃ� NULL ���Ԃ�

void QSort(void *base, unsigned num, unsigned width, int (*comp)(const void *a, const void *b, const void *reference),void *sortref);

#endif