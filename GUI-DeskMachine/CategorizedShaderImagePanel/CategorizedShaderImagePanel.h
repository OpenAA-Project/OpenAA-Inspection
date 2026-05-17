#ifndef CATEGORIZEDSHADERIMAGEPANEL_H
#define CATEGORIZEDSHADERIMAGEPANEL_H

#include "categorizedshaderimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	CategorizedShaderImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	CategorizedShaderImagePanel(LayersBase *Base ,QWidget *parent);
	~CategorizedShaderImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

private slots:
};

#endif // CATEGORIZEDSHADERIMAGEPANEL_H
