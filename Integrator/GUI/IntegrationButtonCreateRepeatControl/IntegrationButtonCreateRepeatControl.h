#pragma once

#include "integrationbuttoncreaterepeatcontrol_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationButtonCreateRepeatControl : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	IntegrationButtonCreateRepeatControl(LayersBase *Base ,QWidget *parent);
	~IntegrationButtonCreateRepeatControl();

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};
