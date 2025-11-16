#pragma once

#include "integrationbuttongeneral_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	SignalOperandBit;

class	IntegrationButtonGeneral : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	bool	Checkable;
	int32	SystemRegisterNo;

	IntegrationButtonGeneral(LayersBase *Base ,QWidget *parent);
	~IntegrationButtonGeneral(void);
	
	virtual void	Prepare(void)	override;

	void	SetToggled( bool ButtonState );
	void	SetButtonChecked( bool ButtonState );

private:
	SignalOperandBit	*ioMode;
private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};


class	IntegrationCmdButtonGeneral : public IntegrationCmdPacketBase
{
public:
	bool	ButtonState;

	IntegrationCmdButtonGeneral(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
