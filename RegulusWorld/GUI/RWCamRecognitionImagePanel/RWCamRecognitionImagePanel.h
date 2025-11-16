#pragma once

#include "rwcamrecognitionimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	RWCamRecognitionImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	RWCamRecognitionImagePanel(LayersBase *Base ,QWidget *parent);
	~RWCamRecognitionImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void				StartPage(void)	override;


private slots:

};
