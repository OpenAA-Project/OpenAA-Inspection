#ifndef LINEENHANCER1LIMAGEPANEL_H
#define LINEENHANCER1LIMAGEPANEL_H

#include "lineenhancer1limagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLineEnhancer1L.h"
#include "XDisplayImage.h"


class	LineEnhancer1LImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	LineEnhancer1LImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage	(void)	override;

	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;

private slots:
};

#endif // LINEENHANCER1LIMAGEPANEL_H
