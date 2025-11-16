#ifndef NICKINSPECTIONIMAGEPANEL_H
#define NICKINSPECTIONIMAGEPANEL_H

#include "nickinspectionimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XDisplayImage.h"

class	NickInspectionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	NickInspectionImagePanel(LayersBase *Base ,QWidget *parent);
	~NickInspectionImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	void	StartPage(void)		override;


private slots:
};

#endif // NICKINSPECTIONIMAGEPANEL_H
