/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StatisticImager\XStatisticPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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

//パック
#pragma	pack(push,1)
typedef	struct	_PixelStatisticInLayer
{
	WORD	Added;			//加算値						//２バイト
	DWORD	Added2;			//２乗和						//４バイト

	BYTE	Lightest;		//一番明るい輝度				//１バイト	//A-20090910
	BYTE	Darkest;		//一番暗い輝度					//１バイト	//A-20090910

//---------------------------------------------------------------------
//	合計													//８バイト
//
//	<< カラー（3レイヤー、横ドット：7296）の場合 >>
//		基板最大サイズ	330mm × 250mm
//		分解能			260mm ÷ 7296	≒ 35μm
//		ライン数		330mm ÷ 分解能	≒ 9260
//
//	例）10000ラインの場合
//		８バイト × 10000 × 7296 ＝ 583,680,000バイト ＝ 583.68MB
//		￣￣￣￣										×     3（レイヤー）
//														--------------
//														1,751.04MB
//---------------------------------------------------------------------

	BYTE	Lighter;		//二番目に明るい輝度			//１バイト	//A-20100208
	BYTE	Darker;			//二番目に暗い輝度				//１バイト	//A-20100208

//---------------------------------------------------------------------
//	合計													//10バイト
//
//		10バイト × 10000 × 7296 ＝ 729,600,000バイト ＝ 729.60MB
//		￣￣￣￣										×     3（レイヤー）
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