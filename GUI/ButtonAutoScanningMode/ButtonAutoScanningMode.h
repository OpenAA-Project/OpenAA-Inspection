#pragma once

#include "buttonautoscanningmode_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

class	SignalOperandBit;

class	ButtonAutoScanningMode : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
	bool	SyncMode;
	SignalOperandBit	*iFlagSet;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	int32	RegNoInFlagSet;

	ButtonAutoScanningMode(LayersBase *Base ,QWidget *parent);
	~ButtonAutoScanningMode(void);
	virtual void	Prepare(void)	override;
	virtual void	AfterStartSequence(void)	override;
	QTranslator Translator;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandAutoModeON(void);
	void	CommandAutoModeOFF(void);
private:
	void	ExecuteToggled( bool checked );

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};
//--------------------------------------------------------------------------
class	CmdGetScanningStateOnAutoMode : public GUIDirectMessage
{
public:
	bool		AutoModeOn;

	CmdGetScanningStateOnAutoMode(LayersBase *base):GUIDirectMessage(base){}
	CmdGetScanningStateOnAutoMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetScanningStateOnAutoMode : public GUIDirectMessage
{
public:
	bool		AutoModeOn;

	CmdSetScanningStateOnAutoMode(LayersBase *base):GUIDirectMessage(base){}
	CmdSetScanningStateOnAutoMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLockAutoScanningMode : public GUIDirectMessage
{
public:
	bool		Enabled;

	CmdLockAutoScanningMode(LayersBase *base):GUIDirectMessage(base){}
	CmdLockAutoScanningMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//--------------------------------------------------------------------------

class	GUICmdSetAutoScanningMode : public GUICmdPacketBase
{
public:
	bool	Clicked;

	GUICmdSetAutoScanningMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};