#pragma once

#include "integrationcreatethreshold_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationBase.h"


class	IntegrationCreateThreshold : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	double	AddedMMX;
	double	AddedMMY;
	double	AddedMMZ;

	IntegrationCreateThreshold(LayersBase *Base ,QWidget *parent);
	~IntegrationCreateThreshold();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
private:

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};