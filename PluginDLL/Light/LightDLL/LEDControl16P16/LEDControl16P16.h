#ifndef LEDCONTROL16P16_H
#define LEDCONTROL16P16_H

#include "ledcontrol16p16_global.h"
#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include <QTimer>
#include "LightUnitStruct.h"

class	HidCommand;
class	SettingDialog;

class	BoardInfoStruct
{
public:
	struct        LightUnit   EPROMData[2];
	int           ADData[16];
	int           BaseCounter;
	int           ADSel;
	int           PortSel;
	int           PWMSelector;
	unsigned char InputData[4];
};

class	LEDControl16P16Panel : public LightDLLBaseClass
{
	Q_OBJECT

	HidCommand	*Commander;
	bool	Opened;
	QString Param;
	int		Number;
	QMutex	AccessHID;
	bool	WhileInput;
	bool	StopInput;
	BYTE	LastInput;
	QTimer	TM;
	int32	ContinuousMode;

	SettingDialog	*LightForm;
public:

	BoardInfoStruct	BoardData[4];


	class	LineValue
	{
	public:
		struct	LightLineUnit	*Pointer;
		int32					BoardNumber;
		int32					LineNumber;

		unsigned short			Value;
		QString					Comment;

		LineValue(void);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	class	LightPattern
	{
	public:
		QString		Comment;
		LineValue	LineValues[16];

		LightPattern(void){}
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	class	PortData
	{
	public:
		unsigned char	UsageLines;
		LightPattern	PatternData[8];
		QString			Comment;

		PortData(void);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	int32		LightDataNumb;
	PortData	LightData[4];

	QString		VersionStr;
	int			BoardCount;

	int	CurrentPattern;

	LEDControl16P16Panel(LayersBase *base ,const QString &LightParamStr);
	~LEDControl16P16Panel(void);

	bool	Initial(bool OutputMode);
	bool	Open(void);
	bool	Close(void);

	void	GetVersion(void);
	void	Transfer(int PatternNumber,QProgressBar *Bar);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	SetOnOff(bool OnMode);
	bool	ShowPattern(int PatternNo);

	virtual	bool	ShowSettingDialog(void)				override;

	bool	LoadADData(int BoardNumber ,int ADNumber);
	bool	LoadInputData(int BoardNumber);

	bool	SetTestLED(bool ONMode);
	bool	ReadEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data);
	bool	WriteEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data);
	int		ReadEPRomStatus(int BoardNumber ,int PortNumber);

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

private slots:
	void	SlotTimeOut();
};


class	CmdReqInput : public GUIDirectMessage
{
public:
	BYTE	Data;

	CmdReqInput(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdSetMode : public GUIDirectMessage
{
public:
	BYTE	LightMode;	//0  :Normal
						//1  :ExtIn1==Off  -> LightON
						//2  :ExtIn1==On   -> LightON

	CmdSetMode(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdStopMode : public GUIDirectMessage
{
public:
	CmdStopMode(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdRestartMode : public GUIDirectMessage
{
public:
	CmdRestartMode(LayersBase *base)
		:GUIDirectMessage(base){}
};

#endif // LEDCONTROL16P16_H
