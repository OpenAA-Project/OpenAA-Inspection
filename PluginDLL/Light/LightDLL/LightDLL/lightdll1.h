/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Light\LightDLL\LightDLL\lightdll1.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef LightDLL1H
#define LightDLL1H
//---------------------------------------------------------------------------
#include "LED64CTRLib.h"
#include "LightDLLBase.h"
#include "XLightClass.h"

class   LightDLL1 : public LightDLLBase ,public LightDLLBaseClass
{
public:

	short	LEDBright[LEDBARNUMB][LEDsNumb];
	short	SaveLEDBright[LEDBARNUMB][LEDsNumb];
	double	Gain[LEDBARNUMB][LEDsNumb];

	static	LED64ctr	CLED[LEDBARNUMB];
	static	BYTE		LEDBrightCondition[LEDConditionNumb][LEDBarNumb][LEDNumbPerLine];

	static	LED64ctr	SaveCLED[LEDBARNUMB];
	static	BYTE		SaveLEDBrightCondition[LEDConditionNumb][LEDBarNumb][LEDNumbPerLine];
	static	int			BarIndexTable[LEDBarNumb];
	static	char		*LEDBarIndexFileName;

	int		LightLineCounter[LEDBarCommentNumb];
	QString		BarComment[LEDBARNUMB];

private:
    static	bool	ModeOn;

	WDC_DEVICE_HANDLE	hDev;
	DWORD				dwStatus;
	WDC_ADDR_MODE		mode;
	DWORD				dwAddrSpace;

public:
	LightDLL1(LayersBase *base);
	~LightDLL1();

	LightDLL1	&operator=(LightDLL1 &src);
	LightDLL1	&operator=(LightDLLBase &src);
	bool	operator==(LightDLLBase &src2);
	bool	operator!=(LightDLL1 &src2);
	bool	operator!=(LightDLLBase &src2);

	char	*GetName(){     return("LED5-8-NT1"); }                 
	bool	LEDSave(QIODevice &str);
	bool	LEDLoad(QIODevice &str);
	bool	LEDSaveDefault();
	bool	LEDLoadDefault();
	
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	ShowSettingDialog(void)			;
	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param);
	virtual	bool	ReflectPhysical(void)		;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		;

	void   *InitialLED();
//	void	TransferLED(TProgressBar *PBar);
	void	TransferLED();
	//void	ChangeTransferLED(int ledbar ,int led ,TProgressBar *PBar);
	void	Clear();

	bool	LEDConditionSave(QIODevice &str);
	bool	LEDConditionLoad(QIODevice &str);

	bool	GetLighting();
	void	SetLighting(bool mode);
	void	SetPowerRate(int BarID,double rate);
	double	GetPowerRate(int BarID);
	void	ResetPowerRate();

	bool	IsEnabled();

	int		GetBarCount();
	void	SetLEDBarBright(int BarID ,int brightness);
	void	GetNowLEDBarAveragedLevel(int BarLevel[100]);
	int		GetMaxLEDLevel(){   return(LEDLevels);   }
	int		GetMaxBrightness(int BarID , int LEDID){   return(LEDLevels);   }
	int		GetMaxSheetNumb(){  return(1);  }
	bool	SetDisplaySheet(int sheet){	return true;	}

	int		GetOneBrightDirectly(int sheet ,int row, int col)       ;
	void	SetOneBrightDirectly(int sheet ,int row, int col ,int b);
	int		GetBarComment(int BarID,char *Buff);

	void	SetWaitTime(int WaitTime);

	bool	LightOn();
	bool	LightOff();

	WDC_DEVICE_HANDLE	GetHandle(void)	{	return hDev;	}
};

#endif
