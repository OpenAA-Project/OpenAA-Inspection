#ifndef SKIPMARKIMAGEPANEL_H
#define SKIPMARKIMAGEPANEL_H

#include "skipmarkimagepanel_global.h"

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XSkipMark.h"

class	SkipMarkImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	SkipMarkImagePanel(LayersBase *Base ,QWidget *parent);
	~SkipMarkImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // SKIPMARKIMAGEPANEL_H
