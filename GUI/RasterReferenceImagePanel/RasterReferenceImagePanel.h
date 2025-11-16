#pragma once

#include "rasterreferenceimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include <QImage>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XRaster.h"
#include <QTimer>

class	RasterReferenceImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	RasterReferenceImagePanel(LayersBase *Base ,QWidget *parent);
	~RasterReferenceImagePanel(void);
	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	virtual void	StartPage(void)	override;
private slots:

};
