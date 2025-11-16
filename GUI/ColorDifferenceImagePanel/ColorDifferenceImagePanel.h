#ifndef COLORDIFFERENCEIMAGEPANEL_H
#define COLORDIFFERENCEIMAGEPANEL_H

#include "colordifferenceimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XColorDifference.h"

class	ColorDifferenceImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ColorDifferenceImagePanel(LayersBase *Base ,QWidget *parent);
	~ColorDifferenceImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // COLORDIFFERENCEIMAGEPANEL_H
