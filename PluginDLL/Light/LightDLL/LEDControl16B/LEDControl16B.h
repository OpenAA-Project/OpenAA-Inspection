#ifndef LEDCONTROL16B_H
#define LEDCONTROL16B_H

#include "ledcontrol16b_global.h"

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
class	LEDControl16BDialog;

class	BoardInfoStruct
{
public:
	struct        LightUnit   EPROMData[2];
	int           ADData[16];
	int           BaseCounter;
	int           ADSel;
	int           PortSel;
	int           PWMSelector;
	unsigned short	InputData[4];
	unsigned short	Gain[16];
};

class	LEDControl16BPanel : public LightDLLBaseClass
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

	LEDControl16BDialog	*LightForm;
	static	QString	DefFileName;
public:

	BoardInfoStruct	BoardData[8];
	int		BaseCounter;
	
	class	DefUnit
	{
	public:
		class	DefBoard
		{
		public:
			class	DefLine
			{
			public:
				int32		UnitNo;
				int32		BoardNo;
				int32		LineNo;
				int32		ColorType;
				int32		LightID;	//Same ID  in same Light unit
				int32		MaxValue;
				QString		Comment;
				int32		EnableComparatorL;
				int32		EnableComparatorH;
				bool		ForceON;

				void	Set(int unitNo ,int boardNo ,int lineNo);

				bool	Save(QIODevice *f);
				bool	Load(QIODevice *f);

			}DefLineDim[64];
			int	CountOfLine;

			DefBoard(void){		CountOfLine=0;	}
			bool	Save(QIODevice *f);
			bool	Load(QIODevice *f);
			int		GetLineCount(void);

		}DefBoardDim[16];
		int	CountOfBoard;

		DefUnit(void){	CountOfBoard=0;	}
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
		int		GetLineCount(void);
	}DefUnitDim[4];
	int	CountOfUnit;

	int		GetLineCount(void);

	class	LightPattern
	{
	public:
		class	LineValue
		{
		public:
			DefUnit::DefBoard::DefLine	*PointerForDefLine;
			int32		Value;

			LineValue(void)	{	PointerForDefLine=NULL;	Value=0;	}
			bool	Save(QIODevice *f);
			bool	Load(QIODevice *f,LEDControl16BPanel *panel);

		}*LineValueDim;
		int32	AllocatedCountOfLines;

		LightPattern(void)	{	AllocatedCountOfLines=0;	LineValueDim=NULL;	}

		void	Initial(LEDControl16BPanel *panel);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f,LEDControl16BPanel *panel);
	};

	class	PatternData
	{
	public:
		unsigned char	UsageLines;
		LightPattern	Pattern;
		QString			Comment;

		PatternData(void){}
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f,LEDControl16BPanel *Panel);
	};
	int32		LightDataNumb;
	PatternData	LightData[16];
	int32		AddedStartOffset;


	QString		VersionStr;
	int			BoardCount;

	int	CurrentPattern;

	LEDControl16BPanel(LayersBase *base ,const QString &LightParamStr);
	~LEDControl16BPanel(void);

	bool	Initial(bool OutputMode);
	bool	Open(void);
	bool	Close(void);

	void	GetVersion(void);
	void	Transfer(int PatternNumber,QProgressBar *Bar);
	bool	GetRegisterData(int BoardNumber ,int datatype ,int adr ,int &RegData);
	bool	GetADRegisterData(int BoardNumber ,BYTE RegData[10]);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	SaveDef(QIODevice *f);
	bool	LoadDef(QIODevice *f);
	bool	LoadDef(void);
	bool	SaveDef(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	bool	SetOnOff(bool OnMode);

	bool	GetPatternComparator(int UnitNumber ,int BoardNumber ,int LineNumber);	//Into DefBuffer
	bool	SetPatternComparator(int UnitNumber ,int BoardNumber ,int LineNumber);	//From DefBuffer
	bool	GetPatternOnOff		(int UnitNumber ,int BoardNumber);					//Into DefBuffer
	bool	SetPatternOnOff		(int UnitNumber ,int BoardNumber);					//From DefBuffer
	bool	SetMotorCounter(int UnitNumber ,int BoardNumber ,int N);
	int		GetMotorCounter(int UnitNumber ,int BoardNumber);
	bool	SetEnableRangeOffset(int UnitNumber ,int AddedOffset);
	bool	SetRelay(bool ON);

	int		ReqVolume(void);
	void	SetManual(bool ON);

	virtual	bool	ShowSettingDialog(void)			override;


	void	InitialEPRom(void);
	void	BuildDataFromEPRom(void);

	bool	LoadADData(int BoardNumber);
	bool	LoadAD_Register(int BoardNumber ,int adr ,int &RegData);
	bool	LoadInputData(int BoardNumber);
	bool	SetTemporaryON(int32 ContinuousCount=10000);

	bool	SetTestLED(bool ONMode);
	bool	ReadEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data);
	bool	WriteEPRom(int BoardNumber ,int PortNumber ,struct LightUnit &Data);
	int		ReadEPRomStatus(int BoardNumber ,int PortNumber);

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

	bool	LoadAllocationFile(QFile *f);

	//For IODeliver
	int		GetCameraResolution(void);
	bool	SetCameraResolution(int n);

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


#endif // LEDCONTROL16B_H
