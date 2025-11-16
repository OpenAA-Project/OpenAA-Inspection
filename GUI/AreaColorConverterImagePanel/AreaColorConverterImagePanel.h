#pragma once

#include "areacolorconverterimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AreaColorConverterImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	AreaColorConverterImagePanel(LayersBase *Base ,QWidget *parent);
	~AreaColorConverterImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;


private slots:

};
