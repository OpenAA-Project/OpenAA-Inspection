#pragma once

#include "showthresholdlevel_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QWidget>

class SetThresholdLevelForm;

class ShowThresholdLevel: public GUIFormBase
{
	Q_OBJECT

	SetThresholdLevelForm	*SForm;
public:
    ShowThresholdLevel(LayersBase *Base ,QWidget *parent);
	~ShowThresholdLevel(void);

	virtual void	ReadyParam(void)	override;
	virtual void	BuildForShow(void)	override;
private slots:
	void	ResizeAction();
};
