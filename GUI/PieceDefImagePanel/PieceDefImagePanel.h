#ifndef PIECEDEFIMAGEPANEL_H
#define PIECEDEFIMAGEPANEL_H

#include "piecedefimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPieceDef.h"

class	PieceDefImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	PieceDefImagePanel(LayersBase *Base ,QWidget *parent);
	~PieceDefImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // PIECEDEFIMAGEPANEL_H
