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

#if	!defined(XCCSContro2l_h)
#define	XCCSContro2l_h

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"


class	HidCommand;


class	LightCCSControl2 : public LightDLLBaseClass ,public QWidget
{
	HidCommand	*Commander;
	bool	Opened;
	QString Param;
public:

	int		Brightness[16];
	bool	OnMode[16];

	BYTE	InData;

	QString		VersionStr;

	int	CurrentPattern;

	LightCCSControl2(LayersBase *base ,const QString &LightParamStr);
	~LightCCSControl2(void);

	bool	Initial(bool OutputMode){	return true;	}
	bool	Close(void)				{	return true;	}

	void	Transfer(int PatternNumber,QProgressBar *Bar);
	void	Transfer1(int PatternNumber ,QProgressBar *Bar);
	void	Transfer2(int PatternNumber ,QProgressBar *Bar);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	SetOnOff(bool OnMode);
	bool	SetOnOff(int number ,bool OnMode);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	LoopOnIdle(void)	override;

	virtual	bool	ShowSettingDialog(void)					override;
	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;
protected:
	bool	SendOutData(int n);
	bool	SendInt(bool n);
	bool	SendWR(bool n);
	bool	SendOnOff(bool OnMode);
	bool	SendCH(int n);
	bool	SendON2(bool n);
	bool	SendExtOut(bool n);
};


class	CmdLightSetValue1 : public GUIDirectMessage
{
public:
	BYTE	Value1;

	CmdLightSetValue1(LayersBase *base)
		:GUIDirectMessage(base){}
};
class	CmdLightSetValue2 : public GUIDirectMessage
{
public:
	BYTE	Value2;

	CmdLightSetValue2(LayersBase *base)
		:GUIDirectMessage(base){}
};
class	CmdLightReqData : public GUIDirectMessage
{
public:
	BYTE	Value1;
	BYTE	Value2;
	bool	OnMode1;
	bool	OnMode2;

	CmdLightReqData(LayersBase *base)
		:GUIDirectMessage(base){}
};
class	CmdLightSetOnOff : public GUIDirectMessage
{
public:
	bool	OnMode1;
	bool	OnMode2;

	CmdLightSetOnOff(LayersBase *base)
		:GUIDirectMessage(base){}
};
class	CmdReqInput : public GUIDirectMessage
{
public:
	BYTE	Data;

	CmdReqInput(LayersBase *base)
		:GUIDirectMessage(base){}
};

#endif