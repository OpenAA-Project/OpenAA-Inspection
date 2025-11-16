#pragma once

#include "shiftmarkimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
//#include "XDent.h"

class	ShiftMarkImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;

public:
	ShiftMarkImagePanel(LayersBase *Base ,QWidget *parent);
	~ShiftMarkImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)					override;
	virtual void	StartPage(void)	override;
private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};
