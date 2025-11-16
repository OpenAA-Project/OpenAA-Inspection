#ifndef BCRIMAGEPANEL_H
#define BCRIMAGEPANEL_H

#include "bcrimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	BCRImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	BCRImagePanel(LayersBase *Base ,QWidget *parent);
	~BCRImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;
private slots:
};

#endif // BCRIMAGEPANEL_H
