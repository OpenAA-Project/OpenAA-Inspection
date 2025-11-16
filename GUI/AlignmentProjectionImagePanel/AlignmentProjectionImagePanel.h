#ifndef ALIGNMENTPROJECTIONIMAGEPANEL_H
#define ALIGNMENTPROJECTIONIMAGEPANEL_H

#include "alignmentprojectionimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AlignmentProjectionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	AlignmentProjectionImagePanel(LayersBase *Base ,QWidget *parent);
	~AlignmentProjectionImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;


private slots:

};


#endif // ALIGNMENTPROJECTIONIMAGEPANEL_H
