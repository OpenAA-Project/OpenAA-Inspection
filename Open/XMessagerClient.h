#if	!defined(XMESSAGERCLIENT_H)
#define	XMESSAGERCLIENT_H

#include<QTcpSocket>
#include<QThread>
#include<QMutex>
#include"NList.h"
#include <time.h>
#include "XTypeDef.h"
#include <QByteArray>

class	ThreadMessageList;

class	MessagerClient : public QObject
{
	Q_OBJECT
	
	ThreadMessageList	*ThreadMessage;
public:
	MessagerClient(QObject * parent);
	virtual ~MessagerClient(void);

	bool	Initial(const QString &IPAddress,int port=13444);
	
	void	Close(void);
	void	Start(void);

	bool	Send(int MType,int GlobalPage,const QString &Message);
	bool	Send(int MType,QByteArray &Data);

	QByteArray	ReceivedData;
private slots:
	void	SlotReceived();
signals:
	void	SignalReceived();
};

class	MessageList : public NPList<MessageList>
{
public:
	int		MType;
	int		GlobalPage;
	QString Message;
	QByteArray	ArrayData;

	MessageList(void){}
	MessageList(int _MType,int _GlobalPage,const QString &_Message){	MType=_MType;GlobalPage=_GlobalPage;	Message=_Message;	}
	MessageList(int _MType,QByteArray &data){	MType=_MType;	GlobalPage=-1;	ArrayData=data;	}
};

class	RecList : public NPList<RecList>
{
public:
	BYTE		*Data;
	int32		Len;

	RecList(int len);
	~RecList(void);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,QByteArray &ret);
};

class	ThreadMessageList : public QThread
{
	Q_OBJECT

	QString IPAddress;
	int		Port;
	QTcpSocket	Socket;
	NPListPack<MessageList>	MessageListContainer;
	QMutex					MutexMessageList;
	int		FastCommLeafRxReEntrant;
	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	RecList		*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		PctLen;
	int32		LastPacketLoadedSize;
	QMutex		MuteRecData;
	NPListPack<RecList>	RecData;
public:
	bool	CloseMode;

	ThreadMessageList(QObject *parent);
	~ThreadMessageList(void);

	virtual void run();
	bool	Initial(const QString &IPAddress,int port=13444);
	void	Send(int MType,int GlobalPage,const QString &Message);
	bool	Send(int MType,QByteArray &Data);

	RecList	*UnpackTopRxBuff(void);
	int		GetQueuedCount(void);
private slots:
	void	SlotReadyRead();
signals:
	void	SignalReceived();
};

#endif
