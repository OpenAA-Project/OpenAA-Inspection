#pragma once

#include "flatinspectionimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QMenu>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
//#include "XDotColorMatching.h"

class	FlatInspectionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;

public:
	FlatInspectionImagePanel(LayersBase *Base ,QWidget *parent);
	~FlatInspectionImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	virtual void	StartPage(void)	override;

private slots:

};
