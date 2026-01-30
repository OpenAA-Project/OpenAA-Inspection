/*
 * Copyright (C) 2025
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

#pragma once

#include "lightbowl240rgbw_global.h"
#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QTcpSocket>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "XServiceForLayers.h"
#include "XParamRobot.h"


#define	WaitingMilisecForConnection		2000
#define	MaxDimCountLightBowl240RGBW		1000


class ParamLightInfo : public ParamLight
{
public:
	QString	PatternName;

	ParamLightInfo(void){}

	ParamLightInfo	&operator=(const ParamLightInfo &src);

    bool    SaveInfo(QIODevice *f);
    bool    LoadInfo(QIODevice *f);
};



class	LightBowl240RGBW : public LightDLLBaseClass
{
	QTcpSocket	Sock;
public:
	QString     IPAddress;
    int         CountOfLightDataDim;
    ParamLightInfo  LightDataDim[MaxDimCountLightBowl240RGBW];

	bool		ONMode;
	int			CurrentIndex;

	QString		VersionStr;

	LightBowl240RGBW(LayersBase *base,const QString &LightParamStr);
	~LightBowl240RGBW(void);

	bool	Initial(void);
	bool	Open(void)	;
	bool	Close(void)	;
	bool	SetON(bool ON);

	bool	Transfer(ParamLightInfo &Ptn ,bool _OnMode);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ShowSettingDialog(void)			override;
	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

};