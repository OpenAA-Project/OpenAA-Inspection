#if	!defined(SOCKET_H)
#define	SOCKET_H

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

class	SocketServer;
class	SocketClient;



class	SocketClient : public QObject ,public NPList<SocketClient>
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
		int32		Len;
		int32		ErrorCode;
		BYTE		ErrorLevel;
		BYTE		ErrorMessageLen;
		BYTE		ErrorTimeLen;
		SocketClient	*Client;

		RecList(int len);
		~RecList(void);


		BYTE	*GetError(BYTE *fp,ErrorCodeList &ErrorData);

		BYTE	*GetPointer(void){	return(Data);	}
		BYTE	*GetPointer(BYTE *p ,int32 &ret);
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
	int32				ID;
	QTcpSocket			*Sock;
	bool				Servered;
	QString				IP;
	int32				Port;
	XDateTime			CreatedTime;
	SocketServer		*cParent;
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

	NPListPack<TxList>	TxQueueBuff;

public:
	SocketClient(QObject *parent);
	~SocketClient(void);
	
	void	Set(QObject *parent ,const QString &ip ,int port);
	void	Set(SocketServer *cparent);
	bool	StartConnect(void);

	bool	IsServerMode(void)	{	return(Servered);	}
	bool	IsConnected(void);
	int		GetID(void)			{	return ID;		}

	bool	TxData(BYTE *buff ,int xbyte);
	bool	TxData(QBuffer *f);
	bool	TxData(QByteArray *f);

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
	void	WaitReadyRead(int milisec);
signals:
	void	SignalReceived(int);
private slots:
	void	SlotConnected();
	void	SlotDisconnected();
	void	SlotReadyRead();

};


class	SocketServer : public QObject
{
    Q_OBJECT

	QTcpServer		Server;
	int				TopID;
public:

	QMutex	LeafAccessor;
	NPListPack<SocketClient>	Leaf;

	SocketServer(QObject * parent);
	~SocketServer(void);

	QTcpServer	&GetServer(void){	return Server;	}
	void	StartServer(int port);
	int		GetTopID(void);

	void	DisconnectClient(SocketClient *s);
	virtual	SocketClient	*NewSocket(void);

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