#ifndef STARTINSPECTIONWITHOUTCAPTURE_H
#define STARTINSPECTIONWITHOUTCAPTURE_H

#include "startinspectionwithoutcapture_global.h"
#include <QPushButton>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	StartInspectionWithoutCapture : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	bool	SyncMode;
	bool	Started;
	volatile	bool	Calculating;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QColor	NormalColor;
	QColor	PushedColor;
	bool	IsNecessaryLot;
	int32		WaitingMilisecForSlave;
	bool	CheckExecuteInNoMaster;

	StartInspectionWithoutCapture(LayersBase *Base ,QWidget *parent);
	~StartInspectionWithoutCapture(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

	virtual	void keyPressEvent ( QKeyEvent * event )	override;
	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandStart(void);
protected:
	virtual	bool OnIdle(void)	override;
public slots:
	//void SlotClicked (bool checked);
	void	SlotToggled (bool checked);
private slots:
	void	ResizeAction();
};

//==============================================================
class	GUICmdStartInspectWithoutCapture : public GUICmdPacketBase
{
public:
	XDateTime	StartInspectionTime;
	int64		CurrentInspectID;
	int32		Layer;
	int32		StrategicNumber;

	GUICmdStartInspectWithoutCapture(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdStartInspectWithoutCapture(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyInspectWithoutCapture : public GUICmdPacketBase
{
public:

	GUICmdReplyInspectWithoutCapture(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReplyInspectWithoutCapture(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdGetStateStartInspectionWithoutCapture : public GUIDirectMessage
{
public:
	bool		StartInspectionOn;

	CmdGetStateStartInspectionWithoutCapture(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStateStartInspectionWithoutCapture(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif // STARTINSPECTIONWITHOUTCAPTURE_H
