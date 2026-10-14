#pragma once

#include "alignmentshiftrotationimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAlignmentShiftRotation.h"


class	AlignmentShiftRotationImagePanel : public DisplayImageWithAlgorithm
{
public:

	AlignmentShiftRotationImagePanel(LayersBase *Base ,QWidget *parent);
	~AlignmentShiftRotationImagePanel(void);

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
};