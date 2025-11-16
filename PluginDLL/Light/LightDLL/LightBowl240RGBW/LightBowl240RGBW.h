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