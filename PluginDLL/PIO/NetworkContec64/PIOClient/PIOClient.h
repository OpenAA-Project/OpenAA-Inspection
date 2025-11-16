#ifndef PIOCLIENT_H
#define PIOCLIENT_H

#include "pioclient_global.h"
#include "QTcpSocket"
#include "XTypeDef.h"

class PIOClient : public QTcpSocket
{
	Q_OBJECT
public:
	PIOClient(QObject *parent);
	~PIOClient();

	BYTE	InData[16];
	BYTE	OutData[16];

	void	Initial(const QString &Address);

	void	Outport(int port ,BYTE data);
	BYTE	Inport(int port);
	BYTE	GetOutData(int port);

private:
	
public slots:
	void ReadyRead();
};

#endif // PIOCLIENT_H
