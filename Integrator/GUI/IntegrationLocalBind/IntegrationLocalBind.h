#pragma once

#include "integrationlocalbind_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationLocalBind : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool		ReEntrant;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	IntegrationLocalBind(LayersBase *Base ,QWidget *parent);
	~IntegrationLocalBind(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};

