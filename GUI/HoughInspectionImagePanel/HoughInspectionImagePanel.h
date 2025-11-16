#ifndef HOUGHINSPECTIONIMAGEPANEL_H
#define HOUGHINSPECTIONIMAGEPANEL_H

#include "houghinspectionimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XDisplayImage.h"

class	HoughInspectionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;
public:
	HoughInspectionImagePanel(LayersBase *Base ,QWidget *parent);
	~HoughInspectionImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	//virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	StartPage(void)	override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;

private slots:
	void	SlotTouchItems(ListPageLayerIDPack *ItemInfo);
};

#endif // HOUGHINSPECTIONIMAGEPANEL_H
