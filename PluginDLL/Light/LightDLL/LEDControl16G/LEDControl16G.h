#ifndef LEDCONTROL16G_H
#define LEDCONTROL16G_H

#include "ledcontrol16g_global.h"
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
#include <QTcpSocket>

#define	LEDControllerPort	17280
#define	MaxPatternCount		64
class	LEDControl16GDialog;


class	LEDControl16GPanel : public LightDLLBaseClass
{
	Q_OBJECT

	bool	Opened;
	QString Param;
	QTcpSocket	Sock;
	QString		AccessIPAddress;
	int			AccessPort;
	QMutex		AccessHID;
	bool		Received;

	unsigned char	ReceivedCmd;
	QByteArray	ReceivedData;

	LEDControl16GDialog	*LightForm;
	static	QString	DefFileName;
public:
	
    LightBoard  BoardData[MaxBoardCount];
    int32		BoardCount;

    int			UsageLines;
    struct      LightLineUnit	LineData[DimCountOfLineData];

	QString		VersionStr;

	int	CurrentPattern;

	LEDControl16GPanel(LayersBase *base ,const QString &LightParamStr);
	~LEDControl16GPanel(void);

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

	bool	SetOnOff(bool OnMode);

	bool	GetPatternOnOff		(int UnitNumber ,int BoardNumber);					//Into DefBuffer
	bool	SetPatternOnOff		(int UnitNumber ,int BoardNumber);					//From DefBuffer

	virtual	bool	ShowSettingDialog(void)			override;

	bool	LoadInputData(int BoardNumber);

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

	bool	LoadAllocationFile(QFile *f);

	bool	WriteRegister(int DipSW ,BYTE Data[] ,int DataLen);
	bool	ReadRegister (int DipSW ,BYTE Data[] ,int DataLen ,int &ReceivedByte ,int MaxDataLen);

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
#endif // LEDCONTROL16G_H
