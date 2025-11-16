#if	!defined(XLIGHT500)
#define	XLIGHT500

#include <QIODevice>
#include "XTypeDef.h"
#include "XLightClass.h"

const	int		LEDCountInSheet=7;
const	int		SheetCountInSystem=30;
const	int		MaxBrightness		=4095;
class	QextSerialPort;

class	LED500Panel : public LightDLLBaseClass
{
	static  struct	InitializedMicrosecTimerStruct IWaitFunc;
	static  int		LEDWaitTime;

	 QextSerialPort    *sio;

	unsigned char	*RxData;
	int		RxByte;
	int		RxWPoint;
	int		RxNumb;
	char	RxCmd;
public:

	bool	SyncMode;
	int		SyncForward;
	int		SyncPulsePerBar;
	int		SyncBackward;

	int		CommPort;
	int		Brightness[SheetCountInSystem][LEDCountInSheet];
	qreal	GradValue;


	LED500Panel(LayersBase *base);
	~LED500Panel(void);

	bool	Open(int port);
	bool	Close(void);

	void	SetAll(int brightness, qreal grad=1.0);
	void	SetLeft(int brightness, qreal grad=1.0);
	void	SetRight(int brightness, qreal grad=1.0);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	void	SaveCommon();
	void	LoadCommon();

	bool	SetOnOff(bool OnMode);
	bool	SendSync(void);
	bool	SendBrightness(short _SheetCountInSystem,short _LEDCountInSheet);
	bool	SendBrightnessAllLED(short _SheetCountInSystem);
	bool	IsSameBrightness(short _SheetCountInSystem);
	bool	SendAllBrightness(void);
	bool	SendReflect(void);

	virtual	bool	ShowSettingDialog(void)			;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param);
	virtual	bool	ReflectPhysical(void)		;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		;

private:
	void	SendTx(char Cmd ,char *Buff, unsigned short datalen);
	bool	GetRx(int &Cmd ,unsigned char *data ,int buffsize);
	int		GetChar(void);
	void	SendChar(unsigned char d);
};


#endif
