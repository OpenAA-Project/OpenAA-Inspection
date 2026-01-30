/*
 * Copyright (C) 2018
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
#include "XGeneralFunc.h"

#include "XGUIReviewGlobal.h"
#include "XReviewCommon.h"

// Review��GUI�ւ̋��ʃp�P�b�g
// ReviewGUI��TransmitDirectry�Ŋe�X���`����

// ���[�J���p�P�b�g
// 
// �������v��
// 
//// �傫�ȕύX��������(�}�X�^�[�f�[�^���ǂݍ��񂾂��A���b�g���ύX�����肵���Ƃ��Ȃ�)�ɁAReview�A���S���Y���̃f�[�^�փ|�C���^�Q�Ƃ��Ă����ꍇ
//// delete�Ȃǂŏ��������C���X�^���X�փA�N�Z�X�����Ȃ����߂̏��������߃p�P�b�g
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

// �X�V�v��
class GUICmdReviewUpdateLocal : public GUIDirectMessage
{
public:
	// Recieve
	bool Ret;
public:
	GUICmdReviewUpdateLocal(LayersBase *Base)
		:GUIDirectMessage(Base),Ret(false){};
};

// �t�H�[�J�X���ڂ�
class GUICmdSetFocus : public GUIDirectMessage
{
public:
	GUICmdSetFocus(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// CurrentNGNail���ύX����
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


// �������ύX���ꂽ���Ƃ��ʒm����
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

// NGNail���ύX���ꂽ���Ƃ��ʒm����
class GUICmdUpdateCurrentNGNail : public GUIDirectMessage
{
public:
	GUICmdUpdateCurrentNGNail(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// �}�X�^�[�X���[�u�ԒʐM�p�P�b�g

// ���M�̂݃p�P�b�g

//// �������v�� : �\�����Ă����f�[�^������������ -> ���ɏ������֐��̎��s�𑣂�
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

// �X�V�v�� : RviewStructure�����f�[�^���Ď擾���ĕێ����Ă����f�[�^���X�V������ -> ���ɏ������֐� > �X�V�����s������
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