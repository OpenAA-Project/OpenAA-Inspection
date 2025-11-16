#ifndef PROJECTEDINSPECTIONIMAGEPANEL_H
#define PROJECTEDINSPECTIONIMAGEPANEL_H

#include "projectedinspectionimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XProjectedInspection.h"
#include "XDisplayImage.h"


class	ProjectedInspectionImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	ProjectedInspectionImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)		override;

	virtual	void	DrawEndAfterOperation(FlexArea &area)					override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;

private slots:
};

#endif // PROJECTEDINSPECTIONIMAGEPANEL_H
