#ifndef RESULTKIDAOUTPUT_H
#define RESULTKIDAOUTPUT_H

#include "resultkidaoutput_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include <QObject>
#include "XTypeDef.h"
#include "XServiceForLayers.h"

class	PIOClass;
class	ResultKidaOutput;

enum	_OutputControlMode
{
	_FreeForResult	=0
	,_Abs_OK		=1
	,_Abs_NG		=2
	,_Abs_Blade		=3
};

struct CommandResult
{
	bool	OK;
	bool	NG;
	bool	SwordOK;
	bool	SwordNG;
	int64	InspectionID;
};


class OutThreadInResultKida : public QThread,public ServiceForLayers
{
	Q_OBJECT
	ResultKidaOutput	*Parent;

	struct CommandResult	CommandStack[20];
	int		RPoint;
	int		WPoint;
	int		StoredNumb;
	QMutex	MutexCommand;
	bool	LastPIOTimeOver;
	bool	ReqThreadOff;
	DWORD	ReqOffTimeMiliSec;
	qint64	CouterPerMilisec;
public:
	bool	Terminated;

	OutThreadInResultKida(ResultKidaOutput *p,QObject *parent);

	void	Push(int64 InspectionID
				,bool	OK
				,bool	NG
				,bool	SwordOK
				,bool	SwordNG);
	void	WaitForMilisec(int msec);

signals:
	void	SignalTimeOverOccurs();
protected:
	virtual	void	run()	override;
};

class	ResultKidaOutput : public QObject ,public ResultDLLBaseRoot
{
	Q_OBJECT
	PIOClass	*PIO;
	OutThreadInResultKida	*OutThreadInst;
	bool	TimeOutBreak;
	int		OutCount;
public:
	QString		PIO_OK;
	QString		PIO_NG;
	QString		PIO_SwordOK;
	QString		PIO_SwordNG;
	QString		PIO_PCReady;

	QString		PIO_IDBit0;
	QString		PIO_IDBit1;
	QString		PIO_IDBit2;
	QString		PIO_IDBit3;
	int			PIO_TimeOverBit;
	_OutputControlMode	OutputMode;
	bool		MixModeBladeNG;
	int32		KeepONMilisec;
	int32		WaitingTime;
	int32		MinKeepONMilisec;

	ResultKidaOutput(LayersBase *Base);
	virtual ~ResultKidaOutput(void);

	virtual	void	Prepare(void)		override;

	virtual	QString	GetDataText(void)		override	{	return QString("Result Kida Output");		}
	virtual	QString	GetDefaultFileName(void)override	{	return QString("ResultKidaOutput.dat");	}

	virtual	ExeResult	ExecuteStartByInspection	(int ExeID,ResultInspection *Res)	override;

	virtual	bool	OutputResultDirectly(int mode ,ResultInspection &Res,GUIDirectMessage *packet)	override;
	bool	IsPIO_NG(void);
	bool	IsPIOTimeOver(void);
	void	PIOOff(DWORD PassedMilisec);
	void	SetPIOCommand(int64 InspectionID,bool Ok, bool Ng, bool SwordOk, bool SwordNg);
private:
	void	SetPIO(const QString &BitName);
	void	SetPIOOff(const QString &BitName);
	bool	OutputInLibData(LogicDLL *L ,int32 LibID
									,QIODevice *f);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
private slots:
	void	SlotTimeOverOccurs();
};

class	IntegrationSetControlOutput : public GUIDirectMessage
{
public:
	_OutputControlMode		ControlMode;

	IntegrationSetControlOutput(LayersBase *base):GUIDirectMessage(base){}
	IntegrationSetControlOutput(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // RESULTKIDAOUTPUT_H
