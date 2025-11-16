#if	!defined(XVirtualPIOAdapter_h)
#define	XVirtualPIOAdapter_h


#include "NList.h"
#include <QString>
#include "XTypeDef.h"
#include <QBuffer>
#include "XVirtualPIOCommon.h"
#include <QWidget>
#include <QSharedMemory>
#include <QMutex>

class	PIOAdapter
{
	struct	PIOMemoryMap	*MemMap;
	QSharedMemory		AttachedMem;
	int32				MemHandle;
	QMutex				Mutex;
public:

	PIOAdapter(QWidget *parent,const QString &IPAddress,int PortNumber=28200 ,const QString &MemName=/**/"VirtualPIO");
	~PIOAdapter(void);

	bool	LoadDefFile(const QString &FileName);
	int		GetBitCountIn(void);
	int		GetBitCountOut(void);

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



#endif