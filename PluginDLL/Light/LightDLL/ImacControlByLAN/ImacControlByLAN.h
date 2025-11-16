#ifndef IMACCONTROLBYLAN_H
#define IMACCONTROLBYLAN_H

#include "imaccontrolbylan_global.h"
#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QTcpSocket>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "XServiceForLayers.h"


class	ImacControlByLANParam
{
public:
	QString	IPAddress;
	int32	Port;
	QString	SubnetMask;
	QString	DefaultGateway;

	class	ChannelInfo
	{
	public:
		int32	Power;
		BYTE	Mode;
		int32	Delay;
		int32	OutputTime;
		QString	Name;

		ChannelInfo(void);

		ChannelInfo	&operator=(ChannelInfo &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	ChannelInfo	ChannelInfoData[8];

	ImacControlByLANParam(void);

	ImacControlByLANParam	&operator=(ImacControlByLANParam &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	ImacControlByLAN : public LightDLLBaseClass
{
	QTcpSocket	Sock;
public:
	ImacControlByLANParam	Data;
	int		ChannelCount;

	QString		VersionStr;

	ImacControlByLAN(LayersBase *base,const QString &LightParamStr);
	~ImacControlByLAN(void);

	bool	Initial(void);
	bool	Open(void)	;
	bool	Close(void)	;
	bool	SetON(bool ON);

	bool	TransferIPAddress(void);

	bool	Transfer(int PatternNumber,QProgressBar *Bar);
	void	SetIPAddress(ImacControlByLANParam &data);

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
	bool	ReadLine(char *Text,int Len);
};

#endif // IMACCONTROLBYLAN_H
