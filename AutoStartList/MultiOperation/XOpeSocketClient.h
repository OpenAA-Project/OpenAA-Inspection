#if	!defined(XOpeSocketClient_h)
#define	XOpeSocketClient_h


#include "XTypeDef.h"
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QTcpSocket>
#include "NListComp.h"
#include "XDateTime.h"


#define	AutoStartListServerPort	24600


#define	ASLCmd_Req_
#define	ASLCmd_Req_Copy			1
#define	ASLCmd_Req_MkDir		2
#define	ASLCmd_Req_DelFile		3
#define	ASLCmd_Req_DelDir		4
#define	ASLCmd_Req_Execute		5
#define	ASLCmd_Req_Close		6



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


	BYTE	*GetClassName(int maxByte);
	BYTE	*GetError(BYTE *fp);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,int32 &ret);
	BYTE	*GetPointer(BYTE *p ,WORD &ret );
	BYTE	*GetPointer(BYTE *p ,bool &ret );
	BYTE	*GetPointer(BYTE *p ,BYTE *buff ,int buffByte);
	BYTE	*GetPointer(BYTE *p ,QBuffer &ret);
};


class	OpeSocketClient : public QObject ,public NPList<OpeSocketClient>
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

	QMutex		MutexSending;
	bool		Waiting;
	bool		bReceived;
	bool		bAccessed;
	QString		IPAddress;
	int			PortNumber;
	QString		PeerIPAddress;
	int			PeerPort;

public:
	OpeSocketClient(QObject *parent ,const QString &IPAddress,int PortNumber);
	OpeSocketClient(QObject *parent ,QTcpSocket *sv);
	virtual	~OpeSocketClient(void);

	bool	Send(int32 cmd ,QByteArray &Data);
	bool	Send(int32 cmd);

	bool	IsConnected(void);
	bool	WaitReadyRead(int milisec);
	bool	OnWaiting(void)		{	return Waiting;			}
	void	SetReceived(bool b)	{	bReceived=b;			}
	bool	IsReceived(void)	{	return bReceived;		}
	void	SetAccessed(bool b)	{	bAccessed=b;			}
	bool	IsAccessed(void)	{	return bAccessed;		}
		
	QString		GetPeerIPAddress(void)	{	return PeerIPAddress;	}
	int			GetPeerPort(void)		{	return PeerPort;		}

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

//=============================================================================


#endif
