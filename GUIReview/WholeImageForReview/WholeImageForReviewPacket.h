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


#ifndef WHOLEIMAGEFORREVIEWPACKET_H
#define WHOLEIMAGEFORREVIEWPACKET_H

#include "wholeimageforreview_global.h"

#include "XDLLOnly.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewCommon.h"

//////////////////////////////////
// ��GUI���瑗�M�������R�}���h

// �}�X�^�[�摜�̍X�V�v��
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
	bool doLock;// true�Ń��b�N, false�ŃA�����b�N
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
// �����R�}���h(��GUI�̃p�P�b�g)

// �ENGImageListForReview
//   [�N���b�N�����ʒu�̋߂��ɂ���NG�摜���I�����邽�߂̃N���b�N�ʒu�̑��M]
//   GUICmdSelectNGWithPosition



#endif