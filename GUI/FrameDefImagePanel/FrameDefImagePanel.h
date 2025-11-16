#ifndef FrameDEFIMAGEPANEL_H
#define FrameDEFIMAGEPANEL_H

#include "Framedefimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XFrameDef.h"

class	FrameDefImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	FrameDefImagePanel(LayersBase *Base ,QWidget *parent);
	~FrameDefImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // FrameDEFIMAGEPANEL_H
