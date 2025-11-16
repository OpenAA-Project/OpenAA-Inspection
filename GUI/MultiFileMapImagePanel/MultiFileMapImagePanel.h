#ifndef MULTIFILEMAPIMAGEPANEL_H
#define MULTIFILEMAPIMAGEPANEL_H

#include "multifilemapimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMultiFileMap.h"
#include "XDisplayImage.h"


class	MultiFileMapImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:

	MultiFileMapImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage	(void)	override;

	//void	ExecuteDrawEnd(FlexArea &Area);
	virtual	void	MouseMoveEvent(int globalX ,int globalY)	override;
private slots:
};

#endif // MULTIFILEMAPIMAGEPANEL_H
