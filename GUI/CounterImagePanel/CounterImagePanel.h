#pragma once

#include "counterimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XCounter.h"

class	CounterImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	CounterImagePanel(LayersBase *Base ,QWidget *parent);
	~CounterImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)			override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;

protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;
};