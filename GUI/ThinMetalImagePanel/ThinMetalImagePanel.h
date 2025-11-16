#ifndef THINMETALIMAGEPANEL_H
#define THINMETALIMAGEPANEL_H

#include "thinmetalimagepanel_global.h"

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XThinMetal.h"

class	ThinMetalImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	int32		DefaultLibID;

	ThinMetalImagePanel(LayersBase *Base ,QWidget *parent);
	~ThinMetalImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // THINMETALIMAGEPANEL_H
