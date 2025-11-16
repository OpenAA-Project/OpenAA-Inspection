#ifndef NETWORKSIOCLIENTLIB_H
#define NETWORKSIOCLIENTLIB_H

#include "networksioclientlib_global.h"
#include "XNetworkSIOCommon.h"

class	NetworkSIOClientLib;

class	SocketInClient : public SoESocket
{	
	NetworkSIOClientLib	*Parent;
public:
	QByteArray	RxData;
	int			RxCmd;

	SocketInClient(NetworkSIOClientLib *parent ,const QString &_IPAddress,int _PortNumber);

	void	Clear(void);
private:
	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
};

class  NetworkSIOClientLib : public QObject
{
	Q_OBJECT

	SocketInClient	*Client;
public:
	NetworkSIOClientLib(QObject *parent);
	~NetworkSIOClientLib();

	bool	StartConnection(const QString &IPAddress ,int PortNumber=28210);

	bool	OpenPort(int BaudRate ,int Character ,int Parity ,int StopBit);
	bool	SendData(char *fp ,int Len);
	bool	GetReceivedByte(int &RxLen);
	bool	ReceiveData(char *fp ,int &RxLen ,int MaxLen);

private:

};

#endif // NETWORKSIOCLIENTLIB_H
