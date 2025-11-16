#if	!defined(XCommFropmPC)
#define	XCommFropmPC

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class	LEDControl16GRP;
class	TriggerServer;

const	int	TriggerControllerPort=25950;
struct	TriggerInfo
{
	long int	TriggerTiming1;
	long int	TriggerTiming2;
	long int	DropTiming	  ;
};


class	TriggerClient : public QObject
{
	Q_OBJECT
    friend  class	TriggerServer;

	QTcpSocket	*Sock;
	TriggerServer	*Parent;
	
public:
	TriggerClient(TriggerServer *p ,QTcpSocket *s);
	
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};

class	TriggerServer : public QTcpServer
{
	Q_OBJECT
    friend  class	TriggerClient;

    LEDControl16GRP	*Parent;

public:
    TriggerServer(LEDControl16GRP *p);
	
	void	StartListen(void);
	void	SetData(struct	TriggerInfo &Data);
	void	ReqData(struct	TriggerInfo &Data);
	
private slots:
	void	SlotNewConnection();
};	

#endif
