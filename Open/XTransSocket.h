#if	!defined(XTransSocket_h)
#define	XTransSocket_h


#include "XDateTime.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XErrorCode.h"
#include <QBuffer>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMutex>
#include <time.h>
#include "XFastComm.h"

class	TrSocketServer;


#define	WaitTimeMilisec			1000000

class	TrSocketClient : public QObject ,public NPList<TrSocketClient>
{
    Q_OBJECT

public:
#pragma	pack(push,1)
	struct	TxRxLowPacket
	{
		int32		NowOnXByte;
		int32		ErrorCode;
		BYTE		ErrorLevel;
		BYTE		ErrorMessageLen;
		BYTE		ErrorTimeLen;
	};

#pragma	pack(pop)

	class	RecList : public NPList<RecList>
	{
	public:
		BYTE		*Data;
		BYTE		DataBuff[16384];
		int32		Len;
		int32		ErrorCode;
		BYTE		ErrorLevel;
		BYTE		ErrorMessageLen;
		BYTE		ErrorTimeLen;
		TrSocketClient	*Client;

		RecList(int len);
		~RecList(void);


		BYTE	*GetError(BYTE *fp,ErrorCodeList &ErrorData);

		BYTE	*GetPointer(void){	return(Data);	}
		BYTE	*GetPointer(BYTE *p ,int32 &ret);
		BYTE	*GetPointer(BYTE *p ,qint64 &ret);
		BYTE	*GetPointer(BYTE *p ,WORD &ret );
		BYTE	*GetPointer(BYTE *p ,bool &ret );
		BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
		BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
	};

	class	TxList : public NPList<TxList>
	{
	public:
		int32	Len;
		BYTE	*Data;

		TxList(int len , BYTE *data);
		~TxList(void);
	};
private:
	mutable	int32				ID;
	mutable	QString				IP;
	mutable	int32				Port;
	mutable	QTcpSocket			*Sock;
	bool				Servered;
	XDateTime			CreatedTime;
	TrSocketServer	*cParent;
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

	mutable	QString		PeerIP;

	NPListPack<TxList>	TxQueueBuff;
	mutable	volatile	bool	DataIn;	

public:
	TrSocketClient(void);
	virtual	~TrSocketClient(void);
	
	void	Set(QObject *parent ,const QString &ip ,int port);
	void	Set(QObject *parent ,const QString &ip ,int port) const;
	void	Set(TrSocketServer *cparent);
	bool	StartConnect(void) const;

	bool	IsServerMode(void)	{	return(Servered);	}
	bool	IsConnected(void) const;
	int		GetID(void)	const		{	return ID;		}

	bool	TxData(BYTE *buff ,int xbyte) const;
	bool	TxData(QBuffer *f) const;
	bool	TxData(QByteArray *f) const;
	bool	TxData(BYTE Cmd,QByteArray *f) const;
	bool	TxData(BYTE Cmd,qint64 d) const;
	bool	TxData(BYTE Cmd,int32 d=0) const;
	bool	TxData(BYTE Cmd,bool d) const;
	bool	TxData(BYTE Cmd,BYTE *buff ,int xbyte) const;

	void	TxDataQueueStart(void);
	void	TxDataQueuePush(BYTE *data ,int len);
	void	TxDataQueuePush(int32 data);
	void	TxDataQueuePush(WORD data);
	void	TxDataQueuePush(bool data);
	void	TxDataQueuePush(QBuffer *f);
	bool	TxDataQueueFlush(void);

	RecList	*UnpackTopRxBuff(void);
	QTcpSocket	*GetSocket(void){	return Sock;	}
	XDateTime	&GetCreatedTime(void)	{	return CreatedTime;	}
	void	WaitReadyRead(int milisec) const;

	void	FlushRead(void) const;
	QString	GetPartnerIP(void) const;

signals:
	void	SignalReceived(int);

private slots:
	void	SlotConnected();
	void	SlotDisconnected();
	void	SlotReadyRead();

};


class	TrSocketServer : public QObject
{
    Q_OBJECT

	QTcpServer		Server;
	int				TopID;
public:

	QMutex	LeafAccessor;
	NPListPack<TrSocketClient>	Leaf;

	TrSocketServer(QObject * parent);
	~TrSocketServer(void);

	QTcpServer	&GetServer(void){	return Server;	}
	void	StartServer(int port);
	int		GetTopID(void);

	void	DisconnectClient(TrSocketClient *s);
	virtual	TrSocketClient	*NewSocket(void);

	bool	TxAllData(BYTE *buff ,int xbyte);
	bool	TxAllData(QBuffer *f);
	bool	TxAllData(QByteArray *f);

signals:
	void	ConnectClient();
	void	DisconnectClient();
private slots:
	virtual	void	SlotNewConnection ();
};

	

#endif
