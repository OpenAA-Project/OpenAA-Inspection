#ifndef OCRIMAGEPANEL_H
#define OCRIMAGEPANEL_H

#include "ocrimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	OCRImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	OCRImagePanel(LayersBase *Base ,QWidget *parent);
	~OCRImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)		override;
private slots:
};
#endif // OCRIMAGEPANEL_H
