#ifndef NETWORKPIOVIRTUAL_H
#define NETWORKPIOVIRTUAL_H

#include "networkpiovirtual_global.h"
#include <QSharedMemory>
#include <QMutex>
#include "XTypeDef.h"


struct	NetworkPIOVirtualPacket
{
	BYTE	Cmd;
	BYTE	InData[4];
	BYTE	OutData[4];
};


class NetworkPIOVirtual
{
	QSharedMemory	MemMap;
	struct	NetworkPIOVirtualPacket	*Pointer;
public:
	int		InNumb;
	int		OutNumb;

	NetworkPIOVirtual(void);
	~NetworkPIOVirtual();

	void	Initial(int _InNumb ,int _OutNumb);
	void	Initial(const QString &Something);

	void	OutByte(int port ,BYTE data);
	BYTE	InByte(int port);
	void	OutBit(int BitIndex,BYTE data);
	BYTE	InBit(int BitIndex);
	BYTE	GetOutByte(int port);

private:

};


#endif // NETWORKPIOVIRTUAL_H
