#if	!defined(XVirtualPIODirectAccess_H)
#define	XVirtualPIODirectAccess_H

#include "XTypeDef.h"
#include <QSharedMemory>
#include "XVirtualPIOCommon.h"

class	PortBit : public NPList<PortBit>
{
public:
	int		BitNumber;
	QString	BitName;
	volatile	bool	RecievedFlag;
	int		CurrentData;

	PortBit(void){}
};

class	PIOServer;

//Client side function
class	XVirtualPIODirectAccessClient
{
	struct	PIOMemoryMap	*MemMap;
	QSharedMemory			AttachedMem;
	int32					MemHandle;
	NPListPack<PortBit>		PortBitsIn;
	NPListPack<PortBit>		PortBitsOut;
	QMutex					Mutex;
public:
	XVirtualPIODirectAccessClient(void);
	~XVirtualPIODirectAccessClient(void);

	bool	InitialClient(void);

	bool	LoadDefFile(const QString &FileName);

	int		GetBitCountIn(void)	{	return PortBitsIn.GetCount();	}
	int		GetBitCountOut(void)	{	return PortBitsOut.GetCount();	}

	bool	RegisterInBit (int BitNumber ,const QString &BitName);
	bool	RegisterOutBit(int BitNumber ,const QString &BitName);

	int		GetBitData(int bitnumber);
	bool	SetBitData(int bitnumber ,int data);
	bool	GetBitInDataStream(BYTE BitData[] ,int BitNumb);
	bool	SetBitOutDataStream(BYTE BitData[] ,int BitNumb);
	bool	GetBitOutDataStream(BYTE BitData[] ,int BitNumb);

	int		GetBitOutData(int bitnumber);

private:
	int		GetAckCommand(void);
	void	ClearAckCommand(void);
};

class	XVirtualPIODirectAccessServer
{
	struct	PIOMemoryMap	*MemMap;
	QSharedMemory			AttachedMem;
	int32					MemHandle;
	PIOServer				*Server;
public:
	XVirtualPIODirectAccessServer(PIOServer *Server);
	~XVirtualPIODirectAccessServer(void);

	bool	InitialServer(void);

	int		GetBitOutData(int bitnumber);

//Server side function
	void	PollingInServer(void);

private:
	int		GetAckCommand(void);
	void	ClearAckCommand(void);
};

#endif