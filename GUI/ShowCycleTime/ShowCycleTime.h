#ifndef SHOWCYCLETIME_H
#define SHOWCYCLETIME_H

#include "showcycletime_global.h"
#include <QLabel>
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ShowCycleTime : public GUIFormBase
{
	Q_OBJECT

	QLabel	Button;
	DWORD	CapturedTime[50];
	int		CapturedCount;
	int		CapturedWIndex;
	DWORD	LastTime;
	DWORD	CurrentTime;
	int32	UpdateCounter;
	bool	ModeSignalCaptured;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxFPS;
	int32	Precision;
	double	FPS;

	ShowCycleTime(LayersBase *Base ,QWidget *parent);
	virtual void	ReadyParam(void)	override;
	virtual void	Prepare(void)		override;

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual	void	SetSignal(QObject *target,const char *signal,const char *slotfunc)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowMessage(void);
private slots:
	void	ResizeAction();
	void	SlotCaptured(int);

signals:
	void	SignalCycleTime(double FPS);
};

class	CmdReqCycleTimeFPS: public GUIDirectMessage
{
public:
	double	FPS;

	CmdReqCycleTimeFPS(LayersBase *base):GUIDirectMessage(base){}
	CmdReqCycleTimeFPS(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif // SHOWCYCLETIME_H
