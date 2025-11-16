#ifndef CCSCONTROLBYLAN_H
#define CCSCONTROLBYLAN_H

#include "ccscontrolbylan_global.h"
#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QTcpSocket>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "XServiceForLayers.h"


class	CCSControlByLANParam
{
public:
	QString	IPAddress;
	int32	Port;
	QString	SubnetMask;
	QString	DefaultGateway;
	QString	ReturnToIPAddress;
	int32	ReturnToPort;

	class	ChannelInfo
	{
	public:
		int32	Power;
		BYTE	Mode;
		bool	ON;
		QString	Name;

		ChannelInfo(void);

		ChannelInfo	&operator=(ChannelInfo &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	ChannelInfo	ChannelInfoData[8];

	CCSControlByLANParam(void);

	CCSControlByLANParam	&operator=(CCSControlByLANParam &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CCSControlByLAN : public LightDLLBaseClass
{
	QTcpSocket	Sock;
public:
	CCSControlByLANParam	Data;

	QString		VersionStr;

	CCSControlByLAN(LayersBase *base,const QString &LightParamStr);
	~CCSControlByLAN(void);

	bool	Initial(void);
	bool	Close(void)	;
	bool	SetON(bool ON);
	bool	SetON(bool ON,int Ch);

	bool	TransferIPAddress(void);

	bool	Transfer(int PatternNumber,QProgressBar *Bar);
	void	SetIPAddress(CCSControlByLANParam &data);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ShowSettingDialog(void)			override;
	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;
protected:
	bool	SendOutData(int n);
	bool	SendExt(bool n);
	bool	SendWR(bool n);
	bool	SendOnOff(bool OnMode);

	bool	LoadIODefine(QIODevice *f);
	bool	ReadLine(char *Text);
};

class	CmdSetOnOffByChannel : public GUIDirectMessage
{
public:
	bool	ON;
	int		Channel;

	CmdSetOnOffByChannel(LayersBase *base)		:GUIDirectMessage(base)	{}
	CmdSetOnOffByChannel(GUICmdPacketBase *base)	:GUIDirectMessage(base)	{}
	~CmdSetOnOffByChannel(void){}
};


#endif // CCSCONTROLBYLAN_H
