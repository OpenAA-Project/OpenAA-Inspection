#pragma once

#include "showrobotactivity_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XRobotAction.h"

class	mtGraphicUnit;

class	ShowRobotActivity : public GUIFormBase
{
	Q_OBJECT

	mtGraphicUnit			*MainCanvas;
	RobotActionBase			*ABase;
	QImage					PntImage;
public:
	ShowRobotActivity(LayersBase *Base ,QWidget *parent);
	~ShowRobotActivity(void);

	virtual void	Prepare(void)	override;
	//virtual void	StartPage	(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void);

private slots:
	void	SlotOnPaint(QPainter &pnt);

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};
