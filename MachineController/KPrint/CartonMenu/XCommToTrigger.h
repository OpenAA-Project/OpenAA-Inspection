#if	!defined(XCommToTrigger_h)
#define	XCommToTrigger_h

#include <QObject>
#include <QTcpSocket>
#include "XTypeDef.h"

class	CartonMenuForm;
const	int	TriggerControllerPort=25950;

struct	TriggerInfo
{
	int32	TriggerTiming1;
	int32	TriggerTiming2;
	int32	DropTiming	  ;
	int32	TriggerTiming3;		//This turn is for Upgrading. Don't change
	int32	TriggerTiming4;
};
struct	DropPassInfo
{
	int32	ConveyerLength;
	int32	GateOpenTerm;
	int32	DefDelayedCount;
};
struct	ResultCounterInfo
{
	int32	TotalCount;
	int32	OKCount;
	int32	NGCount;
	int32	TMCount;	//TimeOut
	bool	Mismatch;
};
struct	ResultCounterInfoOld
{
	int32	TotalCount;
	int32	OKCount;
	int32	NGCount;
	int32	TMCount;	//TimeOut
};

class	CommToTrigger : public QObject
{
    Q_OBJECT
	QTcpSocket		Sock;
	CartonMenuForm	*Parent;
	bool	Received;
	struct	TriggerInfo			ReceivedData;
	struct	DropPassInfo		DropPassData;
	struct ResultCounterInfo	CounterData;
	struct ResultCounterInfoOld	CounterDataOld;
public:
	CommToTrigger(CartonMenuForm *p);

	bool	Connect(void);
	bool	IsConnected(void);
	bool	Send(struct	TriggerInfo &Data);
	bool	Request(struct	TriggerInfo &Data);
	bool	RequestCounter(struct ResultCounterInfo &Data);
	bool	ResetCounter(void);

	bool	Send(struct	DropPassInfo &Data);
	bool	Request(struct	DropPassInfo &Data);
private slots:
	void	SlotReadyRead();
};


#endif
