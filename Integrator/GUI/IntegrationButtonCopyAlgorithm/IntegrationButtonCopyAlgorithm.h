#pragma once

#include "integrationbuttoncopyalgorithm_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntClass.h"

class	IntegrationButtonCopyAlgorithm : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	SlaveNo;
	QString	IntegrationAlgoSimpleImagePanelInst;
	IntList	DestSlaveNo;
	bool	ClearBeforeCopy;

	IntegrationButtonCopyAlgorithm(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};
