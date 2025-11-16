/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\lightdllbase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
//---------------------------------------------------------------------------

#ifndef LightDLLBaseH
#define LightDLLBaseH
//---------------------------------------------------------------------------

//#include "XLightBase.h"
#include <QIODevice>
//class   XAIPLightBase : public XLightBase
class   LightDLLBase
{
public:
	LightDLLBase(){}
	virtual ~LightDLLBase(){}

	virtual LightDLLBase &operator=(LightDLLBase &src)	=0;
	virtual bool		operator!=(LightDLLBase &src2)	=0;
	virtual bool		operator==(LightDLLBase &src2){	return !operator!=(src2);	}

	virtual char		*GetName()						=0;
	virtual bool		LEDSave(QIODevice &str)			=0;
	virtual bool		LEDLoad(QIODevice &str)			=0;
	virtual bool		LEDSaveDefault()				=0;
	virtual bool		LEDLoadDefault()				=0;

	virtual void	   *InitialLED()					=0;		//内部編集を初期化する
//	virtual void		TransferLED(TProgressBar *PBar)	=0;		//内部変数をＬＥＤコントローラに転送する
	virtual void		TransferLED()					=0;		//内部変数をＬＥＤコントローラに転送する
	virtual void		Clear()							=0;		//内部変数のクリア

	virtual bool		LEDConditionSave(QIODevice &str)=0;
	virtual bool		LEDConditionLoad(QIODevice &str)=0;

	virtual bool		GetLighting()					=0;		//出力Ｅｎａｂｌｅ信号の状態を返す
	virtual void		SetLighting(bool mode)			=0;		//出力Ｅｎａｂｌｅ信号をmodeに従って出力する

	virtual bool		IsEnabled()						=0;		//内部のＬＥＤ変数が全て０のときfalse

	virtual int			GetBarCount()					=0;
	virtual void		SetLEDBarBright(int BarID ,int brightness)	=0;		//１列分を点灯させる
	virtual void		GetNowLEDBarAveragedLevel(int BarLevel[100])=0;
	virtual int			GetMaxLEDLevel()							=0;		//最大輝度値を返す
	virtual int			GetMaxBrightness(int BarID , int LEDID)		=0;		//固有のＬＥＤ輝度値を返す
	virtual int			GetMaxSheetNumb()							=0;		//内部で保有できるシート数を返す
	virtual bool		SetDisplaySheet(int sheet)					=0;		//表示シートを設定
			void		SetPowerRateAll(double rate);						//照明の出力強度を変更する
	virtual void		SetPowerRate(int BarID,double rate)			=0;		//照明の出力強度を変更する
	virtual double		GetPowerRate(int BarID)						=0;
	virtual void		ResetPowerRate()							=0;
	virtual int			GetBarComment(int BarID,char *Buff)			=0;

	virtual int			GetOneBrightDirectly(int sheet ,int row, int col)		=0;
	virtual void		SetOneBrightDirectly(int sheet ,int row, int col ,int b)=0;

	virtual void		SetWaitTime(int WaitTime)		=0;

	virtual bool		LightOn()						=0;
	virtual bool		LightOff()						=0;
};

#endif
