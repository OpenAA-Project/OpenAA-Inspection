#pragma once

#include "integrationshowthresholdlevel_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QWidget>
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class SetThresholdLevelForm;

class IntegrationShowThresholdLevel: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	SetThresholdLevelForm	*SForm;
public:
    IntegrationShowThresholdLevel(LayersBase *Base ,QWidget *parent);
	~IntegrationShowThresholdLevel(void);

	virtual void	ReadyParam(void)	override;
private slots:
	void	ResizeAction();
	void	SlotChangeThresholdLevel(int oldLevel ,int newLevel);
	void    SlotChangeThresholdLevelID(int ThresholdLevelID);
};
