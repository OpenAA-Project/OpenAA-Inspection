#ifndef AUTOCLASSIFYIMAGEPANEL_H
#define AUTOCLASSIFYIMAGEPANEL_H

#include "autoclassifyimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AutoClassifyImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	AutoClassifyImagePanel(LayersBase *Base ,QWidget *parent);
	~AutoClassifyImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

private slots:
};


#endif // AUTOCLASSIFYIMAGEPANEL_H
