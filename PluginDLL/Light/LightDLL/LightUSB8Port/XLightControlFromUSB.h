#if	!defined(XLightControlFromUSB_h)
#define	XLightControlFromUSB_h

#include "XTypeDef.h"
#include <QIODevice>
#include "windows.h"
#include "ftd2xx.h"
#include "XLightClass.h"

class	DirectLightControl;

class	LightControlFromUSB : public LightDLLBaseClass
{
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

		void	Transfer(DirectLightControl *d);
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
		void	Transfer(DirectLightControl *d);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	int					BoardCount;
	LEDBarOnController	*Board;
	DirectLightControl	*DirectAccessor;

public:
	LightControlFromUSB(LayersBase *base ,int boardCount=8, int LEDsPerPort=64 ,int MaxLevel=64);
	~LightControlFromUSB(void);

	void	Initial(DirectLightControl *directAccessor)	{	DirectAccessor=directAccessor;	}
	DirectLightControl	*GetDirectAccessor(void)		{	return DirectAccessor;			}

	int		GetLEDBrightness(int brd ,int column);
	void	SetLEDBrightness(int brd ,int column ,int brightness);

	LEDOnController	*GetLED(int brd ,int column);

	QString	GetBoardComment(int brd);
	void	SetBoardComment(int brd , const QString &comment);

	void	BeginTranster(void);
	void	Transfer(void);
	void	EndTranster(void);

	LightControlFromUSB	&operator=(LightControlFromUSB &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	virtual	bool	ShowSettingDialog(void)			;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param);
	virtual	bool	ReflectPhysical(void)		;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		;
};

class	DirectLightControl
{
	FT_HANDLE Handle;
	BYTE	Data;
	static  struct	InitializedMicrosecTimerStruct IWaitFunc;
	static  int		LEDWaitTime;

	BYTE	FifiData[256];
	int		FifiCount;
	bool	Opened;
	QString	Param;
	bool	TurnedOn;
public:
	DirectLightControl(const QString &LightParamStr);

	bool	Initial(bool OutputMode);
	bool	Release(void);
	bool	Open(void);
	bool	Close(void);

	bool	OutputLED(int brd ,int colum ,int value);
	bool	OutputLighting(bool modeOn);

private:
	void	Start(void);
	void    WaitLoop(void);

	void	OutBit(int bit, bool data);

	void    OutBits(BYTE d,int bitnumb);
    void    Strobe(bool H);
    void    Clock(bool H);
    void    Reset(bool H);
    void    Enable(bool H);
    void    Din(bool H);

	void	FlushFifo(void);

};
/*
	Serial Port bit
		Bit0	Clock
		Bit1	Din
		Bit2	Strobe
		Bit3	Enable
		Bit4	Reset
		Bit5
		Bit6
		Bit7



*/


#endif