#ifndef PARTIALIMAGINGIMAGEPANEL_H
#define PARTIALIMAGINGIMAGEPANEL_H

#include "partialimagingimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPartialImaging.h"

class	PartialImagingImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	PartialImagingImagePanel(LayersBase *Base ,QWidget *parent);
	~PartialImagingImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // PARTIALIMAGINGIMAGEPANEL_H
