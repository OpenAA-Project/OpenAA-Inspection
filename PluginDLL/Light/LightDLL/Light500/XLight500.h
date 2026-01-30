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

#if	!defined(XLIGHT500)
#define	XLIGHT500

#include <QIODevice>
#include "XTypeDef.h"
#include "XLightClass.h"

const	int		LEDCountInSheet=7;
const	int		SheetCountInSystem=30;
const	int		MaxBrightness		=4095;
class	QextSerialPort;

class	LED500Panel : public LightDLLBaseClass
{
	static  struct	InitializedMicrosecTimerStruct IWaitFunc;
	static  int		LEDWaitTime;

	 QextSerialPort    *sio;

	unsigned char	*RxData;
	int		RxByte;
	int		RxWPoint;
	int		RxNumb;
	char	RxCmd;
public:

	bool	SyncMode;
	int		SyncForward;
	int		SyncPulsePerBar;
	int		SyncBackward;

	int		CommPort;
	int		Brightness[SheetCountInSystem][LEDCountInSheet];
	qreal	GradValue;


	LED500Panel(LayersBase *base);
	~LED500Panel(void);

	bool	Open(int port);
	bool	Close(void);

	void	SetAll(int brightness, qreal grad=1.0);
	void	SetLeft(int brightness, qreal grad=1.0);
	void	SetRight(int brightness, qreal grad=1.0);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	void	SaveCommon();
	void	LoadCommon();

	bool	SetOnOff(bool OnMode);
	bool	SendSync(void);
	bool	SendBrightness(short _SheetCountInSystem,short _LEDCountInSheet);
	bool	SendBrightnessAllLED(short _SheetCountInSystem);
	bool	IsSameBrightness(short _SheetCountInSystem);
	bool	SendAllBrightness(void);
	bool	SendReflect(void);

	virtual	bool	ShowSettingDialog(void)			;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param);
	virtual	bool	ReflectPhysical(void)		;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		;

private:
	void	SendTx(char Cmd ,char *Buff, unsigned short datalen);
	bool	GetRx(int &Cmd ,unsigned char *data ,int buffsize);
	int		GetChar(void);
	void	SendChar(unsigned char d);
};


#endif