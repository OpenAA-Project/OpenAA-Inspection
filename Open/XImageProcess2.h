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




#ifndef XIMAGEPROCESS2_H
#define XIMAGEPROCESS2_H

#include <QtGui>
#include "XTypeDef.h"
#include "XFlexArea.h"
#include "XTreeLines.h"

class	ImageBuffer;

bool    MakeHough(BYTE **BmpMap,BYTE **DestMap
				  ,int FreqDots
				  ,int XLen,int YLen
				  ,int HoughResolution=1000);
//�n�t�ϊ��ŁA�������̃h�b�g�������o

void    NarrowizeLine(BYTE **Bmp ,BYTE **Tmp ,int XLen , int YLen);
//	�א���

void	PickupLines(BYTE **BmpMap, int XLen , int YLen
					,TreesContainer &XYCluster);
//	�Q�l���摜�������_���֕ϊ�����
//	���炩���ߍא������Ă����ׂ�
//	BmpMap�͔j�󂳂���


#endif