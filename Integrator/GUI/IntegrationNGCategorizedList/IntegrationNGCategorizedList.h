#pragma once

#include "integrationngcategorizedlist_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "libxl.h"
using namespace libxl;

class	IntegrationNGCategorizedListForm;

class	IntegrationNGCategorizedList : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QToolButton	Button;
	IntegrationNGCategorizedListForm	*Form;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	SlaveNo;

	IntegrationNGCategorizedList(LayersBase *Base ,QWidget *parent);
	~IntegrationNGCategorizedList();

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};