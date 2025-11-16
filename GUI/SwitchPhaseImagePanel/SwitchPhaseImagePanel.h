#ifndef SWITCHPHASEIMAGEPANEL_H
#define SWITCHPHASEIMAGEPANEL_H

#include "switchphaseimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertySwitchPhasePacket.h"

class	SwitchPhaseImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT
	ListPageLayerIDPack	CurrentItem;

public:
	SwitchPhaseImagePanel(LayersBase *Base ,QWidget *parent);
	~SwitchPhaseImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	virtual void	StartPage(void)		override;

private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};

//=========================================================
#endif // SWITCHPHASEIMAGEPANEL_H
