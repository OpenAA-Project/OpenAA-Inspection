#ifndef VIAINSPECTIONIMAGEPANEL_H
#define VIAINSPECTIONIMAGEPANEL_H

#include "viainspectionimagepanel_global.h"

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XViaInspection.h"

class	VIAInspectionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	VIAInspectionImagePanel(LayersBase *Base ,QWidget *parent);
	~VIAInspectionImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};
#endif // VIAINSPECTIONIMAGEPANEL_H
