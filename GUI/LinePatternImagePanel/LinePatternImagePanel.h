#ifndef LINEPATTERNIMAGEPANEL_H
#define LINEPATTERNIMAGEPANEL_H

#include "linepatternimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XDisplayImage.h"

class	LinePatternImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	LinePatternImagePanel(LayersBase *Base ,QWidget *parent);
	~LinePatternImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;

	virtual	void	StartPage(void)	override;


private slots:
};


#endif // LINEPATTERNIMAGEPANEL_H
