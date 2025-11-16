#ifndef NETWORKPIOCLIENT_H
#define NETWORKPIOCLIENT_H

#include "networkpioclient_global.h"
#include <QTcpSocket>
#include <QMutex>
#include "XTypeDef.h"

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


#endif // NETWORKPIOCLIENT_H
