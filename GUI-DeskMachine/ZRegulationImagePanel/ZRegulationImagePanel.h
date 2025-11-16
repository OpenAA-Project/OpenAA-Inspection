#ifndef ZREGULATIONIMAGEPANEL_H
#define ZREGULATIONIMAGEPANEL_H

#include "zregulationimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	ZRegulationImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ZRegulationImagePanel(LayersBase *Base ,QWidget *parent);
	~ZRegulationImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

private slots:
};

#endif // ZREGULATIONIMAGEPANEL_H
