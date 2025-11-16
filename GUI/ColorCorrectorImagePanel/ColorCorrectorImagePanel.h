#pragma once

#include "colorcorrectorimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	ColorCorrectorImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ColorCorrectorImagePanel(LayersBase *Base ,QWidget *parent);
	~ColorCorrectorImagePanel(void){}

	virtual void	Prepare(void)		override;

	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void				StartPage(void)	override;


private slots:

};
