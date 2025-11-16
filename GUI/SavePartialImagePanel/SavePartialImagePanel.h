#ifndef SAVEPARTIALIMAGEPANEL_H
#define SAVEPARTIALIMAGEPANEL_H

#include "savepartialimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XSavePartialImage.h"

class	SavePartialImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	SavePartialImagePanel(LayersBase *Base ,QWidget *parent);
	~SavePartialImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
	
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // SAVEPARTIALIMAGEPANEL_H
