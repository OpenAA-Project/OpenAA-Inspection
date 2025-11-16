#if	!defined(XCommFropmPC)
#define	XCommFropmPC

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class	MainWindow;
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
	
	MainWindow	*Parent;

public:
	TriggerServer(MainWindow *p);
	
	void	StartListen(void);
	void	SetData(struct	TriggerInfo &Data);
	void	ReqData(struct	TriggerInfo &Data);
	
private slots:
	void	SlotNewConnection();
};	






#endif
