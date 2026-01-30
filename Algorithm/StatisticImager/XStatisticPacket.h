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



#if	!defined(XSTATISTICPACKET_H)
#define	XSTATISTICPACKET_H

#include "XDataInLayer.h"
#include "swap.h"

class	CmdMakeAverageStatistic : public GUIDirectMessage
{
public:
	CmdMakeAverageStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAverageStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoMakeAverageStatistic : public GUIDirectMessage
{
public:
	CmdAutoMakeAverageStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoMakeAverageStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLightImageStatistic : public GUIDirectMessage
{
public:
	int			XLen;
	int			YLen;
	int			CurrentPageNumb;
	int			CurrentLayerNumb;
	ImageBuffer	**LightImageList;
	bool		IsLightImage;

	CmdLightImageStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdLightImageStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDarkImageStatistic : public GUIDirectMessage
{
public:
	int			XLen;
	int			YLen;
	int			CurrentPageNumb;
	int			CurrentLayerNumb;
	ImageBuffer	**DarkImageList;
	bool		IsDarkImage;

	CmdDarkImageStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdDarkImageStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDisorderImageStatistic : public GUIDirectMessage
{
public:
	int			XLen;
	int			YLen;
	int			CurrentPageNumb;
	int			CurrentLayerNumb;
	ImageBuffer	**DisorderImageList;
	bool		IsDisorderImage;

	CmdDisorderImageStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdDisorderImageStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAverageImageStatistic : public GUIDirectMessage
{
public:
	int			XLen;
	int			YLen;
	int			CurrentPageNumb;
	int			CurrentLayerNumb;
	ImageBuffer	**AverageImageList;
	bool		IsAverageImage;

	CmdAverageImageStatistic(LayersBase *base):GUIDirectMessage(base){}
	CmdAverageImageStatistic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//�p�b�N
#pragma	pack(push,1)
typedef	struct	_PixelStatisticInLayer
{
	WORD	Added;			//���Z�l						//�Q�o�C�g
	DWORD	Added2;			//�Q���a						//�S�o�C�g

	BYTE	Lightest;		//���Ԗ��邢�P�x				//�P�o�C�g	//A-20090910
	BYTE	Darkest;		//���ԈÂ��P�x					//�P�o�C�g	//A-20090910

//---------------------------------------------------------------------
//	���v													//�W�o�C�g
//
//	<< �J���[�i3���C���[�A���h�b�g�F7296�j�̏ꍇ >>
//		���ő��T�C�Y	330mm �~ 250mm
//		�����\			260mm �� 7296	�� 35��m
//		���C����		330mm �� �����\	�� 9260
//
//	���j10000���C���̏ꍇ
//		�W�o�C�g �~ 10000 �~ 7296 �� 583,680,000�o�C�g �� 583.68MB
//		�P�P�P�P										�~     3�i���C���[�j
//														--------------
//														1,751.04MB
//---------------------------------------------------------------------

	BYTE	Lighter;		//���Ԗڂɖ��邢�P�x			//�P�o�C�g	//A-20100208
	BYTE	Darker;			//���ԖڂɈÂ��P�x				//�P�o�C�g	//A-20100208

//---------------------------------------------------------------------
//	���v													//10�o�C�g
//
//		10�o�C�g �~ 10000 �~ 7296 �� 729,600,000�o�C�g �� 729.60MB
//		�P�P�P�P										�~     3�i���C���[�j
//														--------------
//														2,188.80MB
//---------------------------------------------------------------------

	BYTE	GetAvr(int n);
//	BYTE	GetLight(int n,double Gain);								//D-20100208
//	BYTE	GetDark(int n,double Gain);									//D-20100208
	BYTE	GetDisorder(int n);

}PixelStatisticInLayer;
#pragma	pack(pop)

//============================================================================================================================
class	CmdStatisticBuff : public GUIDirectMessage
{
public:
	PixelStatisticInLayer	**StatisticBuff;

	CmdStatisticBuff(LayersBase *base):GUIDirectMessage(base){}
	CmdStatisticBuff(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//============================================================================================================================
class	CmdExecuteInitialAllocPacket: public GUIDirectMessage
{
public:
	CmdExecuteInitialAllocPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteInitialAllocPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif