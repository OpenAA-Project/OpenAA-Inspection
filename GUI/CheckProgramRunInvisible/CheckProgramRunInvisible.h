#ifndef CHECKPROGRAMRUNINVISIBLE_H
#define CHECKPROGRAMRUNINVISIBLE_H

#include "checkprogramruninvisible_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include "XMessagerClient.h"

class	ThreadCheckProgramRun : public QThread,public ServiceForLayers
{
	Q_OBJECT

	bool	StopRunning;
public:
	bool	FinMode;

	ThreadCheckProgramRun(LayersBase *Base ,QObject * parent):QThread(parent),ServiceForLayers(Base){	StopRunning=false;	FinMode=false;	}

	virtual void run ();
signals:
	void	MessageOutFunc(void);
};


class	CheckProgramRunInvisible : public GUIFormBase
{
	Q_OBJECT

	ThreadCheckProgramRun	ThreadCheckProgramRunInst;
public:
	QString	ProcessName;
	bool	BlockExecute;
	QString	MessageerIPAddress;
	bool	MessageOut;
	bool	NowOnMessageOut;
	MessagerClient	MClient;

	CheckProgramRunInvisible(LayersBase *Base ,QWidget *parent);
	~CheckProgramRunInvisible(void);

	virtual	void	Prepare(void)	override;

private slots:
	void	SlotMessageOutFunc(void);
};

#endif // CHECKPROGRAMRUNINVISIBLE_H
