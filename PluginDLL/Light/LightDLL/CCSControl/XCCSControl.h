#if	!defined(XCCSControl_h)
#define	XCCSControl_h

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"


class	HidCommand;


class	LightCCSControl : public LightDLLBaseClass ,public QWidget
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

	LightCCSControl(LayersBase *base ,const QString &LightParamStr);
	~LightCCSControl(void);

	bool	Initial(bool OutputMode)	{	return true;	}
	bool	Close(void)		{	return true;	}

	void	Transfer(int PatternNumber,QProgressBar *Bar);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	SetOnOff(bool OnMode);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	LoopOnIdle(void)	override;

	virtual	bool	ShowSettingDialog(void)		override	;
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


class	CmdLightSetValue : public GUIDirectMessage
{
public:
	BYTE	Value;

	CmdLightSetValue(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdLightReqData : public GUIDirectMessage
{
public:
	BYTE	Value;
	bool	OnMode;

	CmdLightReqData(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdLightSetOnOff : public GUIDirectMessage
{
public:
	bool	OnMode;

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
