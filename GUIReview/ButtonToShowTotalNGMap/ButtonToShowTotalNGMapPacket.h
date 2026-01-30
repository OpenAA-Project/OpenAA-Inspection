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

#pragma once

#include "XDLLOnly.h"
#include "XReviewCommon.h"

#include "../XGUIReviewCommonPacket.h"

#include "XReviewStructure.h"

//////////////////////////////////
// ��GUI���瑗�M�������R�}���h

// ����

//////////////////////////////////////
// �����R�}���h(��GUI�̃p�P�b�g)

// ����

//////////////////////////////////////
// �}�X�^�[�X���[�u�R�}���h
//  GUI���ʍ���
//   [�X�V] -> NGPosList�̍X�V
//   GUICmdReviewUpdateLocal
//   GUICmdReviewUpdate
// 

/*
// ���M��
class GUIReqXXX : public GUICmdPacketBase
{
public:
	// ���M�����f�[�^
	int data_req;
	// ���M�����f�[�^
	bool Ret;
public:
	GUIReqXXX(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

public:
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

// ���M��
class GUIAckXXX : public GUICmdPacketBase
{
public:
	// ���M�����f�[�^
	int data_ack;
	// ���M�����f�[�^
	bool Ret;
public:
	GUIAckXXX(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

public:
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
*/