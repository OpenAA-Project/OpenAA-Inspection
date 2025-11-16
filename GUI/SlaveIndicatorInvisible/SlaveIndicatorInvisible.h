#ifndef SLAVEINDICATORINVISIBLE_H
#define SLAVEINDICATORINVISIBLE_H

#include "slaveindicatorinvisible_global.h"
#include "XServiceForLayers.h"
#include <QTcpSocket>
#include <QThread>
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

class	ThreadSlaveIndicatorRun : public QThread,public ServiceForLayers
{
	Q_OBJECT

	QTcpSocket	Sock;
public:
	volatile	bool	FinMode;

	ThreadSlaveIndicatorRun(LayersBase *Base ,QObject * parent);

	virtual void run ();

	void	ReadInSock(void);
	void	SendAck();

signals:
	void	SignalReboot();
	void	SignalSendAck();
private slots:
	void	SlotRead();
};


class	SlaveIndicatorInvisible : public GUIFormBase
{
	Q_OBJECT

	ThreadSlaveIndicatorRun		ThreadRunInst;
public:
	QString		ComputerName;
	QString	HostIPAddress;
	int32		HostPort;

	SlaveIndicatorInvisible(LayersBase *Base ,QWidget *parent);
	~SlaveIndicatorInvisible(void);

	virtual	void	Prepare(void)	override;


private slots:
	void	SlotReboot();
	void	SlotSendAck();
};

#endif // SLAVEINDICATORINVISIBLE_H
