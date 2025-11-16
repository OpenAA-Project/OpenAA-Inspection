#ifndef LEDCONTROL32_H
#define LEDCONTROL32_H

#include "ledcontrol32_global.h"
#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include <QTimer>

const	int		LEDCountInSheet		=32;
const	int		LEDPatternCount		=32;
const   int     LEDBoardCount		=16;
const	int		MaxBrightness		=1024;

class	HidCommand;


class	LEDControl32 : public LightDLLBaseClass
{
	Q_OBJECT

	HidCommand	*Commander;
	bool	Opened;
	QString Param;

	QMutex	AccessHID;
	bool	WhileInput;
	bool	StopInput;
	BYTE	LastInput;
	//QTimer	TM;
public:
	QString	VersionStr;
	int		IDNumber;
	int		BoardCount;
	int		MaxValue;

	int		BaseCounter;
	int		IndexBuffer1;
	int		IndexBuffer2;
	int		OutputNumber;	//0 or 1

	class	LEDPattern
	{
	public:
		short	Brightness[LEDCountInSheet];

		LEDPattern(void);
		LEDPattern	&operator=(LEDPattern &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	class	LEDBoard
	{
	public:
		QString	BoardName;
		QString	Text[LEDCountInSheet];
		LEDPattern	Pattern[LEDPatternCount];

		LEDBoard	&operator=(LEDBoard &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	class	LEDDataStruct
	{
	public:
		LEDBoard	Board[LEDBoardCount];

		LEDDataStruct	&operator=(LEDDataStruct &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	LEDDataStruct	LEDData;

	//int	CurrentPattern;

	LEDControl32(LayersBase *base ,const QString &LightParamStr);
	~LEDControl32(void);

	bool	Initial(bool OutputMode);
	bool	Open(void);
	bool	Close(void);
	QString	GetClassName(void)			{	return "LEDControl32";	}

	void	GetVersion(void);
	void	Transfer(int PatternNumber,QProgressBar *Bar);;
	void	SetAll(int brightness,int PatternNumber);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	ShowSettingDialog(void)			override;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;


	bool	CommGetVersion(void);
	bool	CommSetBoardCount(int n);
	bool	CommSendBaseCounter(int BoardNo ,int BaseCounter);
	bool	CommOutEnable(int BoardNo ,bool OnMode);
	bool	CommOutEnableAll(bool OnMode);
	bool	CommSendData(int BoardNo ,QProgressBar *bar);
	bool	CommSendData(int BoardNo,int PatternNo);
	bool	CommTransferAll(int BoardNo,int PatternNo,int OutputNumber);
	bool	CommGetPWMData(int BoardNo,int PatternNo ,int Addr, int Data[]);
	bool	CommGetAD(int BoardNo ,int SelectNo,int &Data);
	bool	CommOutPatternNo(int BoardNo ,int PatternNo);
	bool	CommOutPatternNoAll(int PatternNo);
	bool	CommRequireData(int BoardNo ,int addr ,int Cmd ,int &Data);
	bool	CommSetOutputNumber(int SelectNo);


private slots:
	//void	SlotTimeOut();
};


class	CmdSetMode : public GUIDirectMessage
{
public:
	BYTE	LightMode;	//0  :Normal

	CmdSetMode(LayersBase *base)
		:GUIDirectMessage(base){}
};

#endif // LEDCONTROL32_H
