#ifndef NETWORKPIOVIRTUALCOMMUNICATOR_H
#define NETWORKPIOVIRTUALCOMMUNICATOR_H

#include <QMainWindow>
#include "ui_NetworkPIOVirtualCommunicator.h"
#include <QSharedMemory>
#include <QTcpSocket>
#include <QMutex>
#include <QThread>
#include "XTypeDef.h"

class NetworkPIOVirtualCommunicator;
class	ThreadIOClass : public QThread
{
	Q_OBJECT

	QSharedMemory	MemMap;	
	NetworkPIOVirtualCommunicator	*Parent;
	struct	NetworkPIOVirtualPacket	*Pointer;
public:
	volatile	bool	Terminated;


	ThreadIOClass(NetworkPIOVirtualCommunicator *p,QObject *parent);

	void	run();

signals:
	void	SignalTransfer();
	void	SignalRequest();
};


class NetworkPIOClient : public QTcpSocket
{
	Q_OBJECT

	QString	IPAddress;
	int		Port;
public:
	int		ID;
	int		InNumb;
	int		OutNumb;

	BYTE	InData[4];
	BYTE	OutData[4];
	bool	WaitToReceive;
	QMutex	AccessMutex;

	NetworkPIOClient(QObject *parent);
	~NetworkPIOClient();

	void	Initial(int _ID ,const QString &Address,int port ,int _InNumb ,int _OutNumb);
	void	Initial(const QString &Something);

	void	OutByte(int port ,BYTE data);
	BYTE	InByte(int port);
	void	OutBit(int BitIndex,BYTE data);
	BYTE	InBit(int BitIndex);
	BYTE	GetOutByte(int port);

	void	ReqData(bool SendOutData=true);
	bool	OpenSocket(void);

private:
	
public slots:
	void ReadyRead();
};


class NetworkPIOVirtualCommunicator : public QMainWindow
{
	Q_OBJECT

public:
	ThreadIOClass		*ThreadIOInst;
	NetworkPIOClient	*NetworkPIOClientInst;

	NetworkPIOVirtualCommunicator(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~NetworkPIOVirtualCommunicator();

	void	Initial(int _ID ,const QString &Address,int port ,int _InNumb ,int _OutNumb);
public:

private slots:
	void	SlotTransfer();
	void	SlotRequest();

private:
	Ui::NetworkPIOVirtualCommunicatorClass ui;
};






#endif // NETWORKPIOVIRTUALCOMMUNICATOR_H
