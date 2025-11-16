#ifndef SIGNALRESULTDONETOMASTER_H
#define SIGNALRESULTDONETOMASTER_H

#include "signalresultdonetomaster_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QIODevice>
#include <QTimer>

#define		SignalResultCommandCount	20
#define		WaitForSignalKnock			3000
//#define		MaxSignalCountForResult		20

class	DelayedResult
{
public:
	int		SlaveNo;
	int64	InspectionID;
	bool	OK;

	DWORD	StartTime;
	bool	Alive;

	DelayedResult(void){	Alive=false;	}
};

class	CmdReqSignalResultDoneToMaster	;
class	CmdSignalResultDoneToMaster		;


class	SignalResultDoneToMaster: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QPushButton	Button;

	CmdReqSignalResultDoneToMaster	*ReqCommand[SignalResultCommandCount];
	CmdSignalResultDoneToMaster		*AckCommand[SignalResultCommandCount];


	DelayedResult	SignalRingBuffer[300];
	int64	ResultBuff[1000];
	bool	ResultOKBuff[1000];
	int		ResultButtPointW;
	QMutex	MutexResultBuff;
	QTimer	Timer;
	bool	ReEntrant;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;
	int32	SpoolingMilisec;
	int32	RefreshCycleMilisec;
	int32	MaxSignalCountForResult;

	SignalResultDoneToMaster(LayersBase *Base ,QWidget *parent);

	virtual	void	Prepare(void)	override;
	virtual void	RunByEveryInspection(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

	void	BroadcastInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
	void	BroadcastScanningDone(int SlaveNo,int64 InspectionID );

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool OnIdle(void)	override;

signals:
	void	SignalTimeOutInMaster();
private slots:
	void	SlotClicked();
	void	ResizeAction();
	void	SlotTimeOutInMaster();

private:
	void	PushResultDone(bool OK,int64 shownInspectionID);
};

class	CmdReqSignalResultDoneToMaster : public IntegrationCmdPacketBase
{
public:
	CmdReqSignalResultDoneToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdSignalResultDoneToMaster : public IntegrationCmdPacketBase
{
public:
	struct 
	{
		int64	InspectionID[SignalResultCommandCount];
		bool	OK[SignalResultCommandCount];
		int		ResultCount;
		bool	UseSystemResultStocker;
	}ResultDoneInfo;

	QByteArray	SystemResultData;

	CmdSignalResultDoneToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdSignalScanningDoneToMaster : public IntegrationCmdPacketBase
{
public:
	int64	InspectionID;

	CmdSignalScanningDoneToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SIGNALRESULTDONETOMASTER_H
