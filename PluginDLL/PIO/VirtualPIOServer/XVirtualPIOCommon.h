#if	!defined(XVirtualPIOCommon_H)
#define	XVirtualPIOCommon_H

#include "XTypeDef.h"
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QTcpSocket>
#include "NList.h"

#pragma	pack(push,1)
struct	TxRxLowPacket
{
	int32		NowOnXByte;
	int32		NowCmd;
};

#pragma	pack(pop)

class	RecList : public NPList<RecList>
{
public:
	BYTE		*Data;
	int32		Cmd;
	int32		Len;


	RecList(int len);
	~RecList(void);


	BYTE	*GetClassNamePointer(int maxByte);
	BYTE	*GetError(BYTE *fp);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};


class	PIOSocket : public QObject
{
	Q_OBJECT
		
	QTcpSocket	*Sock;

	NPListPack<RecList>	RecData;
	QMutex				MuteRecData;
	int32				LastPacketLoadedSize;
	struct	TxRxLowPacket	Pct;
	int32				FastCommLeafRxReEntrant;

	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	RecList		*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		NowCmd;

	QString		IPAddress;
	int			PortNumber;
public:
	PIOSocket(QObject *parent ,const QString &_IPAddress,int _PortNumber);
	PIOSocket(QObject *parent ,QTcpSocket *sv);
	virtual	~PIOSocket(void);

	bool	ConnectToHost(void);
	bool	Send(int32 cmd ,QByteArray &Data);

	bool	IsConnected(void);
	void	WaitReadyRead(int milisec);
	
public slots:
	virtual	void	SlotDisconnected();
	void	ReadyRead ();

signals:
	void	SignalReceived(int Cmd);
private slots:
	void	SlotReceived(int Cmd);
protected:
	virtual	void	Received(int cmd ,QByteArray &data){};

};

#define	MaxCoutOfIOBit			128

#define	SendInfoData			1
#define	ReqInData				2
#define	SendOutData				3
#define	ReqOutData				4
#define	ReqInDataStream			5
#define	SendOutDataStream		6
#define	ReqOutDataStream		7
#define	AckSendInfoData			11
#define	AckReqInData			12
#define	AckSendOutData			13
#define	AckReqOutData			14
#define	AckReqInDataStream		15
#define	AckSendOutDataStream	16
#define	AckReqOutDataStream		17
#define	RegInBit				18
#define	RegOutBit				19

#define	OpenPIO					20
#define	AckPIO					21
#define	NackPIO					22
#define	PIOReqLoadDefFile		23
#define	ReqPIOINBitCount		24
#define	ReqPIOOUTBitCount		25

struct	PIOMemoryMap
{
	int32	Handle;
	int32	ReqCommand;
	int32	AckCommand;
	int32	Index;
	BYTE	ReqData[MaxCoutOfIOBit];
	BYTE	AckData[MaxCoutOfIOBit];
	int32	AckIndex;

	BYTE	INData[MaxCoutOfIOBit];
	BYTE	OUTData[MaxCoutOfIOBit];
};

#endif