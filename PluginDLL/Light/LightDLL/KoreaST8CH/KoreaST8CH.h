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

#ifndef KOREAST8CH_H
#define KOREAST8CH_H

#include "koreast8ch_global.h"


#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "XServiceForLayers.h"

#define	MaxCountOfLED	8
class	PIOClass;

class	QextSerialPort;

class	KoreaST8ChPanel : public LightDLLBaseClass ,public QWidget
{
	bool	Opened;

	struct	PBitDim
	{
		BYTE	LightValue;
		bool	OnOff;

	}ChannelDim[MaxCountOfLED];

	int		CountOfLED;
	int				CommPort;
	QextSerialPort    *sio;

public:

	KoreaST8ChPanel(LayersBase *base,const QString &LightParamStr);
	~KoreaST8ChPanel(void);

	bool	Initial(bool OutputMode);
	bool	Close(void)	;

	bool	Transfer(int Ch ,QProgressBar *Bar);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	SetOnOff(int number ,bool OnMode);
	bool	SetOnOff(bool OnMode);

	bool	SetValue(int number ,BYTE data,bool OnOff);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ShowSettingDialog(void)					override;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

protected:
	int		GetChar(void);
};


class	CmdLightSetValue : public GUIDirectMessage
{
public:
	int		Number;
	BYTE	Value;
	bool	OnMode;

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
#endif // KOREAST8CH_H