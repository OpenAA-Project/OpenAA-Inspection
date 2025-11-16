#ifndef NETWORKPIOLIB_H
#define NETWORKPIOLIB_H

#include <QTcpSocket>
#include <QTcpServer>
#include "XTypeDef.h"
#include "NList.h"
#include "XIntClass.h"

class	NetworkPIOServer;

class NetworkPIOServerSocket : public QObject ,public NPList<NetworkPIOServerSocket>
{
	Q_OBJECT
		
	NetworkPIOServer	*Server;
public:
	QTcpSocket	*Sock;
	int		ID;
	int		InNumb;
	int		OutNumb;
	int		ErrorCount;

	NetworkPIOServerSocket(QTcpSocket *sock ,NetworkPIOServer *S ,QObject *parent);
	~NetworkPIOServerSocket();

	BYTE	InData[4];
	BYTE	OutData[4];
	bool	WaitToReceive;

	bool	IsConnected(void);

private:
	
public slots:
	void ReadyRead();
	void	SlotDisConnected();
};

struct	DefinePIOStructure
{
	int	InNumb;
	int	OutNumb;
};

class	NetworkPIOServer : public QTcpServer , public NPListPack<NetworkPIOServerSocket>
{
	Q_OBJECT

public:
	NetworkPIOServer(QObject *Obj);

	void	Start(int PortNumber);
	
	int		GetClientCount(void);
	void	GetClientIDList(IntList &IDList);
	int		GetIOInBitCount (int ID);
	int		GetIOOutBitCount(int ID);

	bool	OutByte	(int id ,int port ,BYTE data);
	bool	InByte	(int id ,int port ,BYTE &data);
	bool	OutBit	(int id ,int BitIndex ,BYTE data);
	bool	InBit	(int id ,int BitIndex ,BYTE &data);
	bool	GetOutByte	(int ID ,int port ,BYTE &data);
	bool	GetOutBit	(int ID ,int BitIndex ,BYTE &data);

protected slots:
	void SlotNewConnection ();
};


#pragma	pack(push,1)
struct	CommandNetworkPIO
{
	BYTE	Cmd;	//1:Set outport and , Send inport , 2: Send only inport		3:Send ID
	BYTE	ID;
	BYTE	InNumb;
	BYTE	OutNumb;
	BYTE	InData[4];
	BYTE	OutData[4];
};

#pragma	pack(pop)

#define	GetBitOnDim(BmpMapOnY,x)	(BmpMapOnY[(x)>>3]&(0x01<<((x)&7)))
#define	SetBitOnDim1(BmpMapOnY,x)	(BmpMapOnY[(x)>>3]|=(0x01<<((x)&7)))
#define	SetBitOnDim0(BmpMapOnY,x)	(BmpMapOnY[(x)>>3]&=~(0x01<<((x)&7)))


#endif // NETWORKPIOLIB_H
