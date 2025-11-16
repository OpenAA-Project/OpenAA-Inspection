#ifndef REMOTECONTROLFORSERVER_H
#define REMOTECONTROLFORSERVER_H

#include "remotecontrolforserver_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include <QTcpServer>
#include <QTcpSocket>

class	RemoteControlForServer;

class	RCSocket : public QObject ,public NPList<RCSocket>
{
	Q_OBJECT
	
	RemoteControlForServer	*Parent;
public:
	int	ID;
	QTcpSocket	*Sock;

	RCSocket(RemoteControlForServer *parent);

	void	Initial(void);
signals:
	void	Disconnect(int id);

private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};

class	RemoteControlForServer : public GUIFormBase
{
	Q_OBJECT

	QTcpServer	Server;
	NPListPack<RCSocket>	SocketPointer;
public:
	int32		PortNo;

	RemoteControlForServer(LayersBase *Base ,QWidget *parent);
	~RemoteControlForServer(void);

	virtual	void	Prepare(void)	override;

	int		GetMaxSocketID(void);
	void	RemoveSocket(RCSocket *c);

private slots:
	void SlotNewConnection ();
};
#endif // REMOTECONTROLFORSERVER_H
