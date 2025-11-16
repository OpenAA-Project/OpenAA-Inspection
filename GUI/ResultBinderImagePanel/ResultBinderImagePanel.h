#ifndef RESULTBINDERIMAGEPANEL_H
#define RESULTBINDERIMAGEPANEL_H

#include "resultbinderimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XResultBinder.h"

class	ResultBinderImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	ResultBinderImagePanel(LayersBase *Base ,QWidget *parent);
	~ResultBinderImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;

	virtual	void	ExecuteMouseLDoubleClick(int globalX ,int globalY)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // RESULTBINDERIMAGEPANEL_H
