#ifndef LEDCONTROL16E_H
#define LEDCONTROL16E_H

#include "ledcontrol16e_global.h"

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include <QTimer>
#include "LightUnitStruct.h"
#include <QTcpSocket>

#define	LEDControllerPort	17280
#define	MaxPatternCount		64
class	LEDControl16EDialog;


struct	LightPatternTx
{
	struct	LightLine
	{
		unsigned long	MicroAmp;
        bool			ON;

        int GetPGAChannel(void);//1Bit
        int GetDAGainX2(void);  //1Bit
        int GetPGAGain(void);   //3Bit
        int GetDAValue(void);   //12Bit
        int GetDCClock(void);   //8Bit
        
        LightLine(void){
            MicroAmp=100000;
        	ON=false;
        }
	}LineData[16];
    bool    DCEnable;

    LightPatternTx(void){
        DCEnable=true;
    }
    void    SetAllON(bool ONMode=true);

};
struct  LightPacketData
{
    unsigned char   BoardNo;
    unsigned char   PatternNo;
    struct	LightPatternTx    PatternData;
};


class	LEDControl16EPanel : public LightDLLBaseClass
{
	Q_OBJECT


	bool	Opened;
	QString Param;
	QTcpSocket	Sock;
	QString		AccessIPAddress;
	int			AccessPort;

	QMutex	AccessHID;
	bool	Received;

	bool	WhileInput;
	bool	StopInput;
	BYTE	LastInput;
	QTimer	TM;
	int32	ContinuousMode;

	LEDControl16EDialog	*LightForm;
	static	QString	DefFileName;
public:
	
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

				DefLine(void){
					UnitNo	=-1;
					BoardNo	=-1;
					LineNo	=-1;
					ColorType	=0;
					LightID	=0;	//Same ID  in same Light unit
					MaxValue	=1000000;
					EnableComparatorL	=0;
					EnableComparatorH	=0;
					ForceON	=false;
				}
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
			DWORD		Value;
			bool		ON;

			LineValue(void)	{	PointerForDefLine=NULL;	Value=0;	ON=false;	}
			bool	Save(QIODevice *f);
			bool	Load(QIODevice *f,LEDControl16EPanel *panel);

		}*LineValueDim;
		int32	AllocatedCountOfLines;

		LightPattern(void)	{	AllocatedCountOfLines=0;	LineValueDim=NULL;	}

		void	Initial(LEDControl16EPanel *panel);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f,LEDControl16EPanel *panel);
	};

	class	PatternData
	{
	public:
		unsigned char	UsageLines;
		LightPattern	Pattern;
		QString			Comment;

		PatternData(void){}
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f,LEDControl16EPanel *Panel);
	};
	int32		LightDataNumb;
	PatternData	LightData[MaxPatternCount];
	int32		AddedStartOffset;


	QString		VersionStr;

	int	CurrentPattern;

	LEDControl16EPanel(LayersBase *base ,const QString &LightParamStr);
	~LEDControl16EPanel(void);

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

#endif // LEDCONTROL16E_H
