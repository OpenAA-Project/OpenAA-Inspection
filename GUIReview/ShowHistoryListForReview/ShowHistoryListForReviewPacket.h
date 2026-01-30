/*
 * Copyright (C) 2012
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

#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// ��GUI���瑗�M�������R�}���h

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
// �����R�}���h(��GUI�̃p�P�b�g)
//
// �ENGImageListForReview
//   [�������X�g�̍s�̕ύX���郊�X�g�X�V�v��]
//    GUICmdReqShowNGImageList
//