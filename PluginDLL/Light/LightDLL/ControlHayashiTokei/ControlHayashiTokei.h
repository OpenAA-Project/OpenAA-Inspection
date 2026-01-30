/*
 * Copyright (C) 2022
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

#ifndef CONTROLHAYASHITOKEI_H
#define CONTROLHAYASHITOKEI_H

#include "controlhayashitokei_global.h"

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "XServiceForLayers.h"

#define	MaxCountOfLED	16
class	PIOClass;

class	BitPort
{
	PIOClass	*PIO;
	int		BoardNo;
	int		Port;
	int		BitNo;

public:
	BitPort(void);

	void	SetInfo(PIOClass *Pio,int _BoardNo,int _PortNo,int _BitNo);
	void	Set(bool b);
	bool	Get(void);
};

class	LightControlHayashiTokei : public LightDLLBaseClass ,public QWidget
{
	bool	Opened;
	QString Param;

	struct	PBitDim
	{
		BitPort		PBit0;
		BitPort		PBit1;
		BitPort		PBit2;
		BitPort		PBit3;
		BitPort		PBit4;
		BitPort		PBit5;
		BitPort		PBit6;
		BitPort		PBit7;
		BitPort		PON;
	}BitDim[MaxCountOfLED];

	int		CountOfLED;
	int		FirstBit[MaxCountOfLED];
public:

	int		Brightness[MaxCountOfLED];
	bool	OnMode[MaxCountOfLED];

	LightControlHayashiTokei(LayersBase *base,const QString &LightParamStr);
	~LightControlHayashiTokei(void);

	bool	Initial(bool OutputMode);
	bool	Close(void)	;

	void	Transfer(QProgressBar *Bar);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	SetOnOff(int number ,bool OnMode);
	bool	SetOnOff(bool OnMode);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ShowSettingDialog(void)					override;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

protected:
	bool	LoadIODefine(QIODevice *f);
};


class	CmdLightSetValue : public GUIDirectMessage
{
public:
	int		Number;
	BYTE	Value;

	CmdLightSetValue(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdLightReqData : public GUIDirectMessage
{
public:
	int		Number;
	BYTE	Value;
	bool	OnMode;

	CmdLightReqData(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdLightSetOnOff : public GUIDirectMessage
{
public:
	int		Number;
	bool	OnMode;

	CmdLightSetOnOff(LayersBase *base)
		:GUIDirectMessage(base){}
};


#endif // CONTROLHAYASHITOKEI_H