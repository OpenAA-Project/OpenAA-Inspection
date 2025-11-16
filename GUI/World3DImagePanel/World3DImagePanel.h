#pragma once

#include "world3dimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XWorld3D.h"

class	World3DImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	World3DImagePanel(LayersBase *Base ,QWidget *parent);
	~World3DImagePanel(void){}

	virtual void	Prepare(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;

};
