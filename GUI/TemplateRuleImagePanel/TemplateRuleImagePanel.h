#pragma once

#include "templateruleimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	TemplateRuleImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	TemplateRuleImagePanel(LayersBase *Base ,QWidget *parent);
	~TemplateRuleImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void				StartPage(void)	override;

private slots:

};