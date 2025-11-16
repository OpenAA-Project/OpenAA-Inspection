#ifndef IMAGECHECKERPANEL_H
#define IMAGECHECKERPANEL_H

#include "imagecheckerpanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XImageChecker.h"

class	ImageCheckerPanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ImageCheckerPanel(LayersBase *Base ,QWidget *parent);
	~ImageCheckerPanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)	override;
	virtual void	StartPage	(void)	override;

private slots:
};


//=========================================================

#endif // IMAGECHECKERPANEL_H
