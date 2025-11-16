#pragma once

#include "ledcontrol16hioprn_global.h"

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include <QTimer>
#include "LightUnitStruct.h"
#include "LightDeviceStruct.h"
#include "DeviceStruct.h"
#include <QTcpSocket>
#include "XHioDefineSignal.h"

#define	LEDControllerPort	12777
#define	MaxPatternCount		64

class	LEDControl16HDialog;
class	LEDControl16HPrnDialog;
class	TimingChartForm;

class	LEDControl16HioPanel : public LightDLLBaseClass
{
	Q_OBJECT

	bool	Opened;
	QString Param;
	QTcpSocket	Sock;
	QString		AccessIPAddress;
	int			AccessPort;
	QMutex		AccessHID;
	bool		Received;

	unsigned char	ReceivedDipSW;
	unsigned char	ReceivedCmd;
	unsigned short	ReceivedLen;
	BYTE			*ReceivedData;
	int				ReceivedMaxLen;

	LEDControl16HDialog		*LightForm;
	LEDControl16HPrnDialog	*GIOForm;
	TimingChartForm			*TimingChart;
	static	QString	DefFileName;
	static	QString	DefaultFileName;

public:
	struct  TimingData	*TimingDim;
	int		AllocTimingDim;
	int		WPointTiming;

	QTimer	TM;
public:
	
    LightBoard  BoardData[MaxBoardCount];
    int32		BoardCount;

    int			UsageLines;
    struct      LightLineUnit	LineData[DimCountOfLineData];

	struct HioPortDefinition	HIOPortName;
	struct  HioFixedStruct		HIOFixedData;

	QString		VersionStr;

	int	CurrentPattern;

	LEDControl16HioPanel(LayersBase *base ,const QString &LightParamStr);
	~LEDControl16HioPanel(void);

	bool	Initial(bool OutputMode);
	bool	Open(void);
	bool	Close(void);

	void	GetVersion(void);
	void	Transfer(int PatternNumber,QProgressBar *Bar);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	SaveDef(QIODevice *f);
	bool	LoadDef(QIODevice *f);
	bool	LoadDef(void);
	bool	SaveDef(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	bool	SaveDefault(void);
	bool	LoadDefault(void);

	bool	SetOnOff(bool OnMode);

	bool	GetPatternOnOff		(int UnitNumber ,int BoardNumber);					//Into DefBuffer
	bool	SetPatternOnOff		(int UnitNumber ,int BoardNumber);					//From DefBuffer

	virtual	bool	ShowSettingDialog(void)					override;

	bool	LoadInputData(int BoardNumber);

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

	bool	LoadAllocationFile(QFile *f);

	bool	WriteRegister(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen);
	bool	ReadRegister (BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short SendDataLen 
						,BYTE &RecCmd ,int &ReceivedByte ,int MaxDataLen
						,int WaitingMilisec=2000);

	bool	SendGio(void);
	bool	RequireGio(void);
	void	ShowTimingChart(void);

	int	FindTiming(DWORD st);	//st‚æ‚è‘å‚«‚¢Å‰‚Ì—v‘f‚ð‹‚ß‚é
	struct  TimingData	*GetTiming(int point);

private slots:
	void	SlotTimeOut();
	void    SlotReadyRead();
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