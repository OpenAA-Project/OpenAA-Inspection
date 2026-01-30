/*
 * Copyright (C) 2014
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

#ifndef NGIMAGEFORREVIEWPACKET_H_
#define NGIMAGEFORREVIEWPACKET_H_

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// ��GUI���瑗�M�������R�}���h

// NG�摜�̍X�V�\���v��
// NG�摜�Ɗ܂܂���NG�ӏ��̃��X�g���܂܂ꂽ�N���X�C���X�^���X�̃|�C���^�����ANG�摜�ƃ}�X�^�[�摜���X�V����
class GUICmdReqSetNGImage : public GUIDirectMessage
{
public:
	// Send
	NGNailIndex NGNailPtr;
	Review::SideType side;// �S�̉摜���f�p
	
	// Recieve
	bool Ret;
public:
	GUICmdReqSetNGImage(LayersBase *Base)
		:GUIDirectMessage(Base),Ret(false){};
};

class GUICmdExchangeNGVisible : public GUIDirectMessage
{
public:
	GUICmdExchangeNGVisible(LayersBase *Base)
		:GUIDirectMessage(Base){};
};

// �}�X�^�[�摜�̎擾�v��
// �}�X�^�[�f�[�^���ǂݍ��܂ꂽ�Ƃ��ɑ��M������
// ���̃R�}���h���������Ă����Ƃ��Aside�̑��̃}�X�^�[�摜�̈ꕔ���v������
//class GUICmdReqSetMasterImage : public GUIDirectMessage
//{
//public:
//	// Send
//	Review::SideType side;// �S�̉摜���f�p
//	// Recieve
//	bool Ret;
//public:
//	bool Save(QIODevice *f){ return true; };
//	bool Load(QIODevice *f){ return true; };
//public:
//	GUICmdReqSetMasterImage(LayersBase *Base)
//		:GUIDirectMessage(Base),Ret(false){};
//};

//////////////////////////////////////
// �����R�}���h(��GUI�̃p�P�b�g)

// �EWholeImageForReview
//   [���݊m�F���̃}�X�^�[�摜�̈ʒu�̏����𑗂�]
//    GUICmdReqSetCurrentPosOnMaster
//

//////////////////////////////////////
// �}�X�^�[�X���[�u�R�}���h
//  GUI���ʍ���
//   �������Ȃ�(NGImageListForReview�̃p�P�b�g�҂�)
// 

#endif