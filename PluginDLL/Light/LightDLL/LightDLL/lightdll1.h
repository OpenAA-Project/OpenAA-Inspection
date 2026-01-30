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