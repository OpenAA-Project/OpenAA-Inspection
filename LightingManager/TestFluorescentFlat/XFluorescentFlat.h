/*
 * Copyright (C) 2013
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

#if	!defined(XFLUORESCENTFLAT_H)
#define	XFLUORESCENTFLAT_H

#include <QIODevice>
#include "windows.h"
#include "ftd2xx.h"
#include "XTypeDef.h"

const	int		LEDCountInSheet=7;
const	int		SheetCountInSystem=36;


class	DirectLightControl
{
	FT_HANDLE Handle;
	static  struct	InitializedMicrosecTimerStruct IWaitFunc;
	static  int		LEDWaitTime;

	BYTE	Data;
	BYTE	FifiData[256];
	int		FifiCount;
	bool	Opened;

public:
	DirectLightControl(void){	Data=0;	FifiCount=0;	Handle=0;	Opened=false;	}

protected:

	bool	Initial(void);
	bool	Release(void);
	bool	Open(void);
	bool	Close(void);

	void	Start(void);
	void    WaitLoop(void);

	void	SetShftClk		(int n);
	void	SetEnableAddr	(int n);
	void	SetShiftIn		(int n);
	void	SetEnableLatch	(int n);
	void	OutEnable		(int n);
	void	Reset			(int n);

	void	PutFifo(void);
	void	FlushFifo(void);

};
/*
	Serial Port bit
		Bit0	ShiftClk
		Bit1	EnableAddr
		Bit2	ShiftIn
		Bit3	EnableLatch
		Bit4	OutEnable
		Bit5	Reset
		Bit6
		Bit7
*/

//========================================================

class	OneLEDSheet
{
public:
	int		Data[LEDCountInSheet];
	bool	OutEnable[LEDCountInSheet];

	OneLEDSheet(void);

	void	SetAll(int n);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	SystemLEDSheet : public DirectLightControl
{
public:
	OneLEDSheet		Sheet[SheetCountInSystem];

	SystemLEDSheet(void){}

	void	Initial(void);
	void	SetAll(int n);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Transfer(void);
	void	SetOn(bool d);
	void	SetOn(int sheet ,bool d);
	void	SetOnTransfer(void);
};

//=========================================================


#endif
