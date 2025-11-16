#pragma once

#include "showtrialinformation_global.h"
#include <QLabel>
#include <QColor>
#include <QFont>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ThreadCheckTrial;

class	ShowTrialInformation : public GUIFormBase
{
	Q_OBJECT

	int					IdleCount;
	ThreadCheckTrial	*CheckInThread;
	QString				LastMsg;
public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ShowTrialInformation(LayersBase *Base ,QWidget *parent);
	virtual	~ShowTrialInformation(void);

	virtual void	Prepare(void)	override;

	void	ShowMessage(void);

	virtual	bool OnIdle(void)	override;
};

class ThreadCheckTrial : public QThread
{
	ShowTrialInformation	*Parent;
public:
	volatile	int		CheckedCount;
	volatile	bool	Terminated;
	volatile	bool	PassedByHasp;
	volatile	bool	Passed;

	ThreadCheckTrial(ShowTrialInformation *p,QObject *parent);

	
private:
	virtual	void run()	override;
};

