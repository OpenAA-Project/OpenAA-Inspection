#ifndef EASYDOTCOLORMATCHIMAGEPANEL_H
#define EASYDOTCOLORMATCHIMAGEPANEL_H

#include "easydotcolormatchimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XIntegrationSimpleImagePanel.h"

class	EasyDotColorMatchImagePanel : public IntegrationAlgoSimpleImagePanel
{
	Q_OBJECT

public:
	EasyDotColorMatchImagePanel(LayersBase *Base ,QWidget *parent);
	~EasyDotColorMatchImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

private slots:

};

#endif // EASYDOTCOLORMATCHIMAGEPANEL_H
