#ifndef DOTREGULATIONIMAGEPANEL_H
#define DOTREGULATIONIMAGEPANEL_H

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	DotRegulationImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	DotRegulationImagePanel(LayersBase *Base ,QWidget *parent);
	~DotRegulationImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

private slots:
};

#endif // DOTREGULATIONIMAGEPANEL_H
