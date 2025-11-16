#ifndef AREASHADERIMAGEPANEL_H
#define AREASHADERIMAGEPANEL_H

#include "areashaderimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AreaShaderImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	AreaShaderImagePanel(LayersBase *Base ,QWidget *parent);
	~AreaShaderImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;
private slots:
};

#endif // AREASHADERIMAGEPANEL_H
