#if	!defined(XCCSControl_h)
#define	XCCSControl_h

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "XServiceForLayers.h"

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


class	LightCCSControlByPIO : public LightDLLBaseClass ,public QWidget
{
	bool	Opened;
	QString Param;

	BitPort		PBit0;
	BitPort		PBit1;
	BitPort		PBit2;
	BitPort		PBit3;
	BitPort		PBit4;
	BitPort		PBit5;
	BitPort		PBit6;
	BitPort		PBit7;
	BitPort		PExt;
	BitPort		PWR;
	BitPort		PON;
public:

	int		Brightness[16];
	bool	OnMode[16];

	BYTE	InData;

	QString		VersionStr;

	int	CurrentPattern;

	LightCCSControlByPIO(LayersBase *base,const QString &LightParamStr);
	~LightCCSControlByPIO(void);

	bool	Initial(void)	{	return true;	}
	bool	Close(void)		{	return true;	}

	void	Transfer(int PatternNumber,QProgressBar *Bar);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	ShowSettingDialog(void)					override;
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
