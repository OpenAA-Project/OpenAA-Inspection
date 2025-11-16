#if	!defined(XLightUSB8PortARM_h)
#define	XLightUSB8PortARM_h


#include <QIODevice>
#include <QWidget>
#include <QTimer>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"

const	int		LEDCountInSheet=8;
const	int		LEDPatternCount=16;
const	int		MaxBrightness		=4095;

class	HidCommand;


class	LightUSB8PortARMPanel :  public LightDLLBaseClass 
{
	Q_OBJECT
	HidCommand	*Commander;
	bool	Opened;
	QString Param;
	int		Number;
public:
	class	LEDOnController
	{
	public:
		int32	BarNo;
		int32	ColumnNo;
		int32	LED;
		int32	MaxLevel;

		LEDOnController(void){	BarNo=0;	ColumnNo=0;	LED=0;	MaxLevel=64;	}
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);

		void	Transfer(LightUSB8PortARMPanel *d);
	};

	class	LEDBarOnController
	{
	public:
		int				BarNo;
		int				ColumnCount;
		LEDOnController	*Bar;
		QString			Comment;

		LEDBarOnController(void);
		~LEDBarOnController(void);
		void	Alloc(int barNo,int ColumnCount);
		void	SetMaxLevel(int MaxLevel);
		LEDOnController	*GetLED(int column);
		int		GetLEDBrightness(int column);
		void	SetLEDBrightness(int column ,int brightness);
		void	Transfer(LightUSB8PortARMPanel *d);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	int					BoardCount;
	LEDBarOnController	*Board;
	QTimer				WatchingTimer;
	bool				CurrentON;

	QString		VersionStr;

	int	CurrentPattern;

	LightUSB8PortARMPanel(LayersBase *base ,const QString &LightParamStr);
	~LightUSB8PortARMPanel(void);

	bool	Initial(bool OutputMode)	{	return true;	}
	bool	Open(void);
	bool	Close(void)		{	return true;	}

	void	GetVersion(void);
	void	OutputLED(int BarNo,int ColumnNo
					,int LED[]);
	void	DoneTransfer(void);
	void	Transfer(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	SetOnOff(bool OnMode);

	virtual	bool	ShowSettingDialog(void)			;

	int		GetLEDBrightness(int brd ,int column);
	void	SetLEDBrightness(int brd ,int column ,int brightness);
	QString	GetBoardComment(int brd);
	void	SetBoardComment(int brd ,const QString &comment);
	LEDOnController	*GetLED(int brd ,int column);
	LightUSB8PortARMPanel	&operator=(LightUSB8PortARMPanel &src);


	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param);
	virtual	bool	ReflectPhysical(void)		;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		;
private slots:
	void	WatchingFunc();
};


class	CmdReqInput : public GUIDirectMessage
{
public:
	BYTE	Data;

	CmdReqInput(LayersBase *base)
		:GUIDirectMessage(base){}
};



#endif