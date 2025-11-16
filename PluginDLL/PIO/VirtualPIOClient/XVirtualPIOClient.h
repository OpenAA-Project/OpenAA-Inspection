#if	!defined(XVirtualPIOClient_h)
#define	XVirtualPIOClient_h


#include "NList.h"
#include <QString>
#include "XTypeDef.h"
#include <QBuffer>
#include "XVirtualPIOCommon.h"
#include <QWidget>
#include <QSharedMemory>

class	PIOServer;

class	PortBit : public NPList<PortBit>
{
public:
	int		BitNumber;
	QString	BitName;
	volatile	bool	RecievedFlag;
	int		CurrentData;

	PortBit(void){}
};




class	PIOAdapter : public PIOSocket
{
	Q_OBJECT
		
	volatile	bool	FlagAckInformation;
	int					MaxBitCountIN;
	int					MaxBitCountOUT;
	BYTE				*RInStreamBitData;
	BYTE				*ROutStreamBitData;
	volatile	bool	RStreamFlag;
	QSharedMemory		MemoryMap;
	struct	PIOMemoryMap	*MemMap;

public:
	NPListPack<PortBit>		PortBitsIn;
	NPListPack<PortBit>		PortBitsOut;
	QString		ServerIPAddress;
	int			ServerPortNumber;

	PIOAdapter(QWidget *parent,const QString &IPAddress,int PortNumber=28200
				,const QString &AccessMemoryName="VertualPIO");
	~PIOAdapter(void);

	bool	LoadDefFile(const QString &FileName);
	int		GetBitCountIn(void);
	int		GetBitCountOut(void);

	int		GetBitData(int bitnumber);
	bool	SetBitData(int bitnumber ,int data);
	int		GetBitOutData(int bitnumber);

	bool	SendInformation(void);

	bool	CommGetBitInDataStream(void);
	bool	CommSetBitOutDataStream(void);
	bool	CommGetBitOutDataStream(void);

	void	MemMapOperator(void);

private:
	void	Received(int cmd ,QByteArray &data);

	PortBit	*FindInBit(int BitNumber);
	PortBit	*FindOutBit(int BitNumber);
	int		GetAckCommand(void);

private slots:
	void	SlotlConnected();
};




#endif