#pragma once

#include "integrationstopupdatethumbnail_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class IntegrationStopUpdateThumbnail: public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
public:
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	IntegrationStopUpdateThumbnail(LayersBase *Base ,QWidget *parent);
	~IntegrationStopUpdateThumbnail();

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};
