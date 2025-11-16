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
};

struct	ResultCounterInfo
{
    int32	TotalCount;
    int32	OKCount;
    int32	NGCount;
    int32	TMCount;	//TimeOut
};
#endif
