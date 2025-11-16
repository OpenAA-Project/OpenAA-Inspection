#if	!defined(XTransDatabaseSocket_h)
#define	XTransDatabaseSocket_h


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

class	TrDBSocketServer;
class	TrDBSocketClient;


#define	CMD_ReplyAck			5
#define	CMD_ReplyNack			6
#define	CMD_beginTransaction	10
#define	CMD_close				11
#define	CMD_commitTransaction	12
#define	CMD_isOpen				13
#define	CMD_AckIsOpen			113
#define	CMD_Open				14
#define	CMD_primaryIndex		15
#define	CMD_ReplayPrimaryIndex	115
#define	CMD_record				16
#define	CMD_ReplyRecord			116
#define	CMD_rollbackTransaction	17
#define	CMD_sqlStatement		18
#define	CMD_tables				19
#define	CMD_ReplyTables			119
#define	CMD_ResultBindValue		20
#define	CMD_ResultBindValue2	21
#define	CMD_ReqData				22
#define	CMD_AckData				122
#define	CMD_ReqExec				23
#define	CMD_ReqFetch			24
#define	CMD_ReqFetchFirst		25
#define	CMD_ReqFetchLast		26
#define	CMD_ReqFetchNext		27
#define	CMD_ReqFetchPrevious	28
#define	CMD_ReqIsNull			29
#define	CMD_ReqLastInsertID		30
#define	CMD_AckLastInsertID		130
#define	CMD_numRowsAffected		31
#define	CMD_AcknumRowsAffected	131
#define	CMD_ReqPrepare			32
#define	CMD_ReqReset			33
#define	CMD_ReqSavePrepare		34
#define	CMD_ReqSetActive		35
#define	CMD_ReqSetAt			36
#define	CMD_setForwardOnly		37
#define	CMD_setQuery			38
#define	CMD_setSelect			39
#define	CMD_size				40
#define	CMD_AckSize				140
#define	CMD_ReqRecord			41
#define	CMD_AckRecord			141
#define	CMD_ReqCreateResultID	42
#define	CMD_AckCreateResultID	142
#define	CMD_ReqRemoveResultID	43
#define	CMD_SendValues			143
#define	CMD_GotoNext			44
#define	CMD_ReqHandle			45
#define	CMD_AckHandle			145
#define	CMD_AckSetAt			146
#define	CMD_AckSetActive		147
#define	CMD_AckSetSelect		148
#define	CMD_ReqInit				49
#define	CMD_AckReqInit			149

class	TrDBSocketClient : public QObject ,public NPList<TrDBSocketClient>
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
		TrDBSocketClient	*Client;

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
	mutable	int32				ID;
	mutable	QString				IP;
	mutable	int32				Port;
	mutable	QTcpSocket			*Sock;
	bool				Servered;
	XDateTime			CreatedTime;
	TrDBSocketServer	*cParent;
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
	TrDBSocketClient(void);
	~TrDBSocketClient(void);
	
	void	Set(QObject *parent ,const QString &ip ,int port);
	void	Set(QObject *parent ,const QString &ip ,int port) const;
	void	Set(TrDBSocketServer *cparent);
	bool	StartConnect(void) const;

	bool	IsServerMode(void)	{	return(Servered);	}
	bool	IsConnected(void) const;
	int		GetID(void)	const		{	return ID;		}

	bool	TxData(BYTE *buff ,int xbyte) const;
	bool	TxData(QBuffer *f) const;
	bool	TxData(QByteArray *f) const;

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


class	TrDBSocketServer : public QObject
{
    Q_OBJECT

	QTcpServer		Server;
	int				TopID;
public:

	QMutex	LeafAccessor;
	NPListPack<TrDBSocketClient>	Leaf;

	TrDBSocketServer(QObject * parent);
	~TrDBSocketServer(void);

	QTcpServer	&GetServer(void){	return Server;	}
	void	StartServer(int port);
	int		GetTopID(void);

	void	DisconnectClient(TrDBSocketClient *s);
	virtual	TrDBSocketClient	*NewSocket(void);

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
