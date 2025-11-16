#pragma once

#include "palletizeimagepanel_global.h"

#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPalletize.h"

class	PalletizeImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;
public:
	PalletizeImagePanel(LayersBase *Base ,QWidget *parent);
	~PalletizeImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};
