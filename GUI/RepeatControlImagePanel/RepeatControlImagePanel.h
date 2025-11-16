#pragma once

#include "repeatcontrolimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	RepeatControlImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	RepeatControlImagePanel(LayersBase *Base ,QWidget *parent);
	~RepeatControlImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void				StartPage(void)	override;


private slots:

};
