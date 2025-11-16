#pragma once

#include "replaceimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	ReplaceImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ReplaceImagePanel(LayersBase *Base ,QWidget *parent);
	~ReplaceImagePanel(void){}

	virtual void	Prepare(void)		override;

	virtual	void	ExecuteMouseLDoubleClick(int globalX ,int globalY)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void				StartPage(void)	override;


private slots:

};
