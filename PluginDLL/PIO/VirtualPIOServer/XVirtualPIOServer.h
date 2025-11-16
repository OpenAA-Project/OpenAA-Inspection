#if	!defined(XVIRTUALPIOSERVER_H)
#define	XVIRTUALPIOSERVER_H

#include "NList.h"
#include <QString>
#include "XTypeDef.h"
#include <QBuffer>
#include "XVirtualPIOCommon.h"
#include <QWidget>
#include <QTcpServer>

class	PIOServer;

class	ClientBitPort : public NPList<ClientBitPort>
{
public:
	int		BitNumber;
	bool	Output;
	QString	BitName;

	int		CurrentOutput;

	ClientBitPort(void){}
};


class	AllocatedClient : public NPList<AllocatedClient> ,public PIOSocket
{	
	PIOServer	*Parent;
public:
	int		ClientID;
	QString	ClientIP;
	int		ClientPortNumber;
	int		HandleNumber;

	NPListPack<ClientBitPort>	BitPorts;

	AllocatedClient(PIOServer *parent,QTcpSocket *sv);

	int		GetBitCountIn(void);
	int		GetBitCountOut(void);
private:
	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
	ClientBitPort	*FindInBit(int BitNumber);
	ClientBitPort	*FindOutBit(int BitNumber);
	int		GetOutData(const QString &BitName);
};


class	BindedBit : public NPList<BindedBit>
{
public:
	ClientBitPort	*BitPoint;
	AllocatedClient	*ClientPoint;
};

class	BindedIOBit : public NPList<BindedIOBit>
{
public:
	BindedBit				*BitOut;
	NPListPack<BindedBit>	BitIn;
	bool			Duplicated;

	BindedIOBit(void);
	virtual	~BindedIOBit(void);
};

class	BindedIOBitContainer : public NPListPack<BindedIOBit>
{
public:
	BindedIOBitContainer(void){}

	BindedIOBit	*FindOutBit(const QString &BitName);
};


class	PIOServer : public QTcpServer ,public NPListPack<AllocatedClient>
{
	Q_OBJECT
		
public:
	BindedIOBitContainer	IOBitsToShow;

	PIOServer(QObject *parent);

	void	StartServer(int PortNumber=28200);

	void	BindData(void);
	ClientBitPort	*SearchOutputBit(const QString &BitName);
	void	DeleteDirectAccess(void);
	AllocatedClient	*GetAllocatedClient(int handle);
signals:
	void	SignalStructureChanged();
private slots:
	void SlotNewConnection ();

};

#endif