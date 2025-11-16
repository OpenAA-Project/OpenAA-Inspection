#ifndef SHOWRESULTALARM_H
#define SHOWRESULTALARM_H

#include "showresultalarm_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XIntClass.h"

class	SignalOperandBit;

class	ShowResultAlarm :public GUIFormBase
{
    Q_OBJECT

	int		CurrentNGCount;
	IntList	LastLotAutoCountList;
	int		ContinuousNG;
public:
	QFont		MessageSize;
	QColor		ColorNormal;
	QColor		ColorAlarm;
	QString		MsgNormal;
	QString		MsgAlarm;
	int32		AlarmNGCountInOneResult;
	int32		AlarmNGContinuous;
	int32		SystemRegisterNo;

	ShowResultAlarm(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private:
	SignalOperandBit	*ioMode;

private slots:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	GUICmdReqResult : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendResult : public GUICmdPacketBase
{
public:
	bool	ResultOk;
	int		NGCount;

	GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // SHOWRESULTALARM_H
