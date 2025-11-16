#ifndef MATCHSHIFTROTATIONIMAGEPANEL_H
#define MATCHSHIFTROTATIONIMAGEPANEL_H

#include "matchshiftrotationimagepanel_global.h"

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	MatchShiftRotationImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	MatchShiftRotationImagePanel(LayersBase *Base ,QWidget *parent);
	~MatchShiftRotationImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // MATCHSHIFTROTATIONIMAGEPANEL_H
