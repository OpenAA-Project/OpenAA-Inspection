#ifndef CHECKEVERYDAYIMAGEPANEL_H
#define CHECKEVERYDAYIMAGEPANEL_H

#include "checkeverydayimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XCheckEveryday.h"

class	CheckEverydayImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	CheckEverydayImagePanel(LayersBase *Base ,QWidget *parent);
	~CheckEverydayImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // CHECKEVERYDAYIMAGEPANEL_H
