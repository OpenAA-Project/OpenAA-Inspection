#pragma once

#include "robotactioneditpanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XRobotAction.h"

class	mtGraphicUnit;

class	RobotActionEditPanel : public GUIFormBase
{
	Q_OBJECT

	mtGraphicUnit			*MainCanvas;
	RobotActionBase			*ABase;
	QImage					PntImage;
public:
	RobotActionEditPanel(LayersBase *Base ,QWidget *parent);
	~RobotActionEditPanel(void);

	virtual void	Prepare(void)	override;
	//virtual void	StartPage	(void)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void);

private slots:
	void	SlotOnPaint(QPainter &pnt);
	void	SlotJustMouseLRelease(int UniversalDx,int UniversalDy);

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

};
