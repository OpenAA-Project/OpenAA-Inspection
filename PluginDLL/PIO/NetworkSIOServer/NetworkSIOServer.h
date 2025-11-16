#ifndef NETWORKSIOSERVER_H
#define NETWORKSIOSERVER_H

#include <QMainWindow>
#include "ui_NetworkSIOServer.h"
#include <QTcpServer>
#include <QTimer>
#include <QTcpSocket>
#include <QBuffer>
#include <QMutex>
#include <QObject>
#include <QSerialPort>
#include "NList.h"
#include "XTypeDef.h"
#include "XNetworkSIOCommon.h"

class NetworkSIOServer;

class	SocketInServer : public NPList<SocketInServer> ,public SoESocket
{	
	NetworkSIOServer	*Parent;
public:
	int		ClientID;
	QString	ClientIP;
	int		ClientPortNumber;
	int		HandleNumber;

	SocketInServer(NetworkSIOServer *parent,QTcpSocket *sv);

private:
	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
};


class NetworkSIOServer : public QMainWindow
{
	Q_OBJECT

	int	ComPort;
	int	LanPort;
	QTcpServer	Server;
	SoESocket	*Client;
	QTimer		Timer;
		
public:
	QSerialPort				*sio;
	struct	CommOpenInfo	SIOInfo;

	NPListPack<SocketInServer>	SocketContainer;
		
	bool	OpenPort(void);
public:
	NetworkSIOServer(int ComPort ,int LanPortNumber ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~NetworkSIOServer();

private slots:
    void	on_pushButtonReOpen_clicked();
	void	SlotNewConnection ();
	void	SlotTimeout();
private:
	Ui::NetworkSIOServerClass ui;
};


#endif // NETWORKSIOSERVER_H
