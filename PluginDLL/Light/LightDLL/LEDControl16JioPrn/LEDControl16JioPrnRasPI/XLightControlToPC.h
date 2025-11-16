#ifndef XLIGHTCONTROLTOPC_H
#define XLIGHTCONTROLTOPC_H

#include <QIODevice>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include "XCommToTrigger.h"

class   ShowLEDControl16JForm;
class	LightControlToPCServer;

const	int	LightControlToPCPort=25950;


class	LightControlToPCClient : public QObject
{
    Q_OBJECT
    friend  class	LightControlToPCServer;

    QTcpSocket	*Sock;
    LightControlToPCServer	*Parent;

public:
    LightControlToPCClient(LightControlToPCServer *p ,QTcpSocket *s);

private slots:
    void	SlotReadyRead();
    void	SlotDisconnected();
};

class	LightControlToPCServer : public QTcpServer
{
    Q_OBJECT
    friend  class	LightControlToPCClient;

    ShowLEDControl16JForm	*Parent;

public:
    LightControlToPCServer(ShowLEDControl16JForm *p);

    void	StartListen(void);
    void	SetData(struct	TriggerInfo &Data);
    void	ReqData(struct	TriggerInfo &Data);
    void	ReqData(struct	ResultCounterInfo &Data);
    void    ResetCounter(void);
private slots:
    void	SlotNewConnection();
};

#endif // XLIGHTCONTROLTOPC_H
